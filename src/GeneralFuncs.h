#ifndef _GENERALFUNCS_H_
#define _GENERALFUNCS_H_
#include <string>
#include <sstream>
#include <iostream>
class GeneralFuncs
{
public:
	static std::string ConvertDoubleToString(const double& val);
	static double ConvertStringToDouble(const char * val);
	static std::string ConvertIntToString(const int& val);
	static int ConvertStringToInt(const char * val);
	static int OnlyInputNumber(const char * pmt);
	static void ClearSceen();
};
#endif // !_GENERALFUNCS_H_

