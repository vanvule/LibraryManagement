#include "GeneralFuncs.h"

std::string GeneralFuncs::ConvertDoubleToString(const double & val)
{
	std::stringstream ss;
	ss << val;
	return ss.str();
}

double GeneralFuncs::ConvertStringToDouble(const char * val)
{
	double ret = 0.0;
	std::stringstream(std::string(val)) >> ret;
	return ret;
}

std::string GeneralFuncs::ConvertIntToString(const int & val)
{
	std::stringstream ss;
	ss << val;
	return ss.str();
}

int GeneralFuncs::ConvertStringToInt(const char * val)
{
	int ret = 0.0;
	std::stringstream(std::string(val)) >> ret;
	return ret;
}

int GeneralFuncs::OnlyInputNumber(const char * pmt)
{
	char *p, s[100];
	int n;
	//lay gia tri duoc nhap vao
	while (fgets(s, sizeof(s), stdin)) {
		//convert no sang kieu int
		n = strtol(s, &p, 10);
		// neu gia tri truyen vao khpng phai la so thi yeu cau nhap lai:
		if (p == s || *p != '\n') {
			std::cout << pmt;
		}
		else break;
	}
	return n;
}

void GeneralFuncs::ClearSceen()
{
	if (system("CLS")) system("clear");
}