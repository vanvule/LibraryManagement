#ifndef INPUTOUTPUTTEXT_H_
#define INPUTOUTPUTTEXT_H_
#include <string>
#include <vector>
#include <fstream>

template<typename X>
class InterractText
{
private:
	void BeautiString(std::string & txt);
protected:
	std::vector<std::string> SplitString(std::string txt, char c);
	std::string Inputtext(std::string pmt);
	virtual  std::vector<X*> Getfile() = 0;
	virtual  std::vector<std::string> Setfile(const std::vector<X*> & data) = 0;
public:
	void ReadFile(const std::string * dir, std::vector<std::string> * dta);
	void WriteFile(const std::string & dir, const std::vector<X*> & dta);


};

template<typename X>
inline std::vector<std::string> InterractText<X>::SplitString(std::string txt, char c)
{
	std::vector<std::string> split_str = std::vector<std::string>();
	while (1)
	{
		int pos = std::string::npos;
		pos = txt.find_first_of(c);
		if (pos == std::string::npos || pos >= txt.length())
			break;
		std::string gtext = txt.substr(0, pos);
		BeautiString(gtext);
		if (pos >= txt.length())
			break;
		txt = txt.substr(pos + 1);
		split_str.push_back(gtext);
	}
	BeautiString(txt);
	split_str.push_back(txt);
	return split_str;
}

template<typename X>
inline void InterractText<X>::BeautiString(std::string & txt)
{
	for (int i = 0; i < txt.length(); i++)
	{
		if (txt.at(i) == ' ')
			txt.erase(i, 1);
		else
			break;
	}
}

template<typename X>
inline std::string InterractText<X>::Inputtext(std::string pmt)
{
	std::string txt = std::string();
	std::cout << pmt;
	std::getline(std::cin, txt);
	return txt;
}

template<typename X>
inline void InterractText<X>::ReadFile(const std::string * dir, std::vector<std::string> * dta)
{
	std::ifstream my_read_file(dir->c_str());

	if (my_read_file.fail())
	{
		throw std::exception("Khong tim thay file Input.txt trong text folder.\n");
	}
	std::string output = std::string();
	{
		while (!my_read_file.eof())
		{
			getline(my_read_file, output);
			dta->push_back(output);
		}
	}
}

template<typename X>
inline void InterractText<X>::WriteFile(const std::string & dir, const std::vector<X*> & dta)
{
	std::vector<std::string> out_put_dt = Setfile(dta);
	std::ofstream myfile(dir, std::ios::out);
	if (myfile.fail())
	{
		throw std::exception("Khong tim thay folder text de tao file.\n");
	}
	for (std::vector<std::string>::iterator iter = out_put_dt.begin(); iter != out_put_dt.end(); iter++)
	{
		myfile << *iter << "\n";
	}
	myfile.close();
}

#endif // !INPUTOUTPUTTEXT_H_
