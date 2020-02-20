#include "DocGia.h"
#include "GeneralFuncs.h"
#include "Constant.h"
Reader::Reader() :Object(),
year(0),
time(0),
state(State::Uncompleted)
{
}

void Reader::SetYear(int year_)
{
	year = year_;
}

void Reader::SetTime(int time_)
{
	time = time_;
}

void Reader::SetState(State st)
{
	state = st;
}

void Reader::SetState(int st)
{
	if (st == 0)
	{
		state = State::Uncompleted;
	}
	else
	{
		state = State::Completed;
	}
}

int Reader::GetYear()
{
	return year;
}

int Reader::GetTime()
{
	return time;
}

State Reader::GetState()
{
	return state;
}

bool ReaderData::Search(int selection, std::string val, bool is_display)
{
	int count = 0;
	for (int i = 0; i < reader_data.size(); i++)
	{
		std::string tmp_val = GetDtaInSelection(selection, reader_data[i]);
		if (strcmp(tmp_val.c_str(), val.c_str()) == 0)
		{
			count++;
			if (is_display)
				Display(count, reader_data[i]);
		}
	}
	if (count == 0)
		return false;
	return true;
}

bool ReaderData::Remove(int selection, std::string val)
{
	int b_f_size = reader_data.size();
	{
		std::vector<Reader*>::iterator iter = reader_data.begin();
		while (iter != reader_data.end())
		{
			std::string tmp_val = GetDtaInSelection(0, *iter);
			if (strcmp(tmp_val.c_str(), val.c_str()) == 0)
			{
				Reader* tmp = *iter;
				iter = reader_data.erase(iter);
				del_reader.push_back(tmp);
			}
			else
			{
				++iter;
			}
		}
	}
	if (b_f_size > reader_data.size())
		return true;
	else
		return false;
}

int ReaderData::ModifyOption()
{
	GeneralFuncs::ClearSceen();
	std::cout << "1:Ten: " << std::endl;
	std::cout << "2:Nam Sinh: " << std::endl;
	std::cout << "3:So lan hoan thanh: " << std::endl;
	std::cout << "4:Trang thai: " << std::endl;
	std::cout << "0:thoat: " << std::endl;
	std::cout << "Lua chon cua ban : " << std::endl;
	return GeneralFuncs::OnlyInputNumber("Lua chon cua ban : ");
}

void ReaderData::ShowData()
{
	for (int i = 0; i < reader_data.size(); i++)
	{
		Display(i + 1, reader_data[i]);
	}
}

int ReaderData::ModifyElementOption()
{
	GeneralFuncs::ClearSceen();
	ShowData();
	std::cout << "0: thoat: " << std::endl;
	std::cout << "**********************" << std::endl;
	std::cout << "Lua chon cua ban : ";
	return GeneralFuncs::OnlyInputNumber("Lua chon cua ban : ");
}


ReaderData::ReaderData() :reader_data(std::vector<Reader*>())
{
	reader_data = Getfile();
}

ReaderData::~ReaderData()
{
	for (int i = 0; i < reader_data.size(); i++)
	{
		delete reader_data[i];
	}
	reader_data.clear();
}

Reader * ReaderData::FindId(std::string txt)
{
	int count = 0;
	for (int i = 0; i < reader_data.size(); i++)
	{
		if (strcmp(reader_data[i]->Id().c_str(), txt.c_str()) == 0)
		{
			return reader_data[i];
		}
	}
}

std::vector<Reader*> ReaderData::GetData()
{
	return reader_data;
}

std::vector<Reader*> ReaderData::Getfile()
{
	std::vector<std::string> string_lst = std::vector<std::string>();
	std::string input = INPUTDIRREADER;
	ReadFile(&input, &string_lst);
	std::vector<std::string> arr = std::vector<std::string>();
	std::vector<Reader*> rtrn = std::vector<Reader*>();
	for (int step = 0; step < string_lst.size(); step++)
	{
		arr = SplitString(string_lst[step], SPLITSIGN);
		if (arr.size() >= 5)
		{
			Reader * tmp = new Reader();
			tmp->SetID(arr[0]);
			tmp->SetName(arr[1]);
			tmp->SetYear(GeneralFuncs::ConvertStringToInt(arr[2].c_str()));
			tmp->SetTime(GeneralFuncs::ConvertStringToInt(arr[3].c_str()));
			tmp->SetState(GeneralFuncs::ConvertStringToInt(arr[4].c_str()));
			rtrn.push_back(tmp);
		}
	}
	return rtrn;
}

std::vector<std::string> ReaderData::Setfile(const std::vector<Reader*>& data)
{
	std::vector<std::string> vec = std::vector<std::string>();
	for (std::vector<Reader*>::const_iterator iter = data.begin(); iter != data.end(); iter++)
	{
		std::string tmp = (*iter)->Id() + ", " + (*iter)->Name() + ", " +
			GeneralFuncs::ConvertIntToString((*iter)->GetYear())
			+ ", " + GeneralFuncs::ConvertIntToString((*iter)->GetTime())
			+ ", " + GeneralFuncs::ConvertIntToString((*iter)->GetState());
		vec.push_back(tmp);
	}
	return vec;
}

bool ReaderData::Remove()
{
	GeneralFuncs::ClearSceen();
	int i = INFINITY;
	std::string txt = std::string();
	ShowData();
	std::cout << "Your Selection: ";
	i = GeneralFuncs::OnlyInputNumber("Your Selection: ");
	if (i >= reader_data.size() && i < 0)
		return false;
	{

	}
	txt = reader_data.at(i - 1)->Id();
	bool is_true = Remove(i, txt);
	if (is_true)
	{
		GeneralFuncs::ClearSceen();
		ShowData();
		std::cout << "Xoa thanh cong!" << std::endl;
	}
	else
	{
		GeneralFuncs::ClearSceen();
		ShowData();
		std::cout << "Xoa that bai!" << std::endl;
	}
	getchar();
	return is_true;
}

void ReaderData::Create()
{
	Reader * dt = new Reader();
	{
		dt->SetID(Inputtext("Ma doc gia: "));
	}
	{
		dt->SetName(Inputtext("Ten Doc gia: "));
	}
	{
		std::cout << "Nam sinh: ";
		dt->SetYear(GeneralFuncs::OnlyInputNumber("Nam sinh: "));
	}
	{
		std::cout << "So lan hoan thanh: ";
		dt->SetTime(GeneralFuncs::OnlyInputNumber("So lan hoan thanh: "));
	}
	{
		std::cout << "Gia: ";
		dt->SetState(GeneralFuncs::OnlyInputNumber("Gia: "));
	}
	if (Search(0, dt->Id(), false))
	{
		delete dt;
		std::cout << "Ma nguoi doc da ton tai: " << std::endl;
	}
	reader_data.push_back(dt);
}

void ReaderData::Search()
{
	GeneralFuncs::ClearSceen();
	int selection = -1;
	ShowData();
	ModifyOption();
	std::cout << "selection: " << std::endl;
	std::cin >> selection;
	std::string val = std::string();
	std::cout << "Value: " << std::endl;
	std::cin >> val;
	if (!Search(selection, val, true))
		std::cout << "Khong tim thay gia tri can tim" << std::endl;
}

void ReaderData::Modify()
{
	int is_break = INFINITY;
	while (true)
	{
		is_break = ModifyOption();
		if (is_break == EXIT)
			break;
		if (is_break < 6 && is_break > EXIT)
		{
			while (1)
			{
				int selection = ModifyElementOption();
				if (selection == EXIT)
					break;
				GeneralFuncs::ClearSceen();
				if (selection > reader_data.size() || selection < EXIT)
				{
					continue;
				}
				Display(selection, reader_data[selection - 1]);
				std::string txt = Inputtext("Gia tri moi: ");
				SetDtaInSelection(is_break, txt, reader_data[selection - 1]);
			}
		}
	}
}

std::string ReaderData::GetDtaInSelection(int selection, Reader * dt)
{
	std::string tmp_val = std::string();
	switch (selection)
	{
	case 0:
		tmp_val = dt->Id();
		break;
	case 1:
		tmp_val = dt->Name();
		break;
	case 2:
		tmp_val = dt->GetYear();
		break;
	case 3:
		tmp_val = GeneralFuncs::ConvertIntToString(dt->GetTime());
		break;
	case 4:
		tmp_val = GeneralFuncs::ConvertIntToString(dt->GetState());
		break;
	default:
		break;
	}
	return tmp_val;
}

void ReaderData::Display(int stt, Reader * val)
{
	std::cout << "STT: " << stt << std::endl;
	std::cout << "Id: " << val->Id() << std::endl;
	std::cout << "Ten : " << val->Name() << std::endl;
	std::cout << "Nam sinh: " << val->GetYear() << std::endl;
	std::cout << "So lan hoan thanh: " << val->GetTime() << std::endl;
	std::cout << "Trang thai: " << val->GetState() << std::endl;
	std::cout << "----------------------------------------------" << std::endl;
}

void ReaderData::SetDtaInSelection(int selection, std::string txt, Reader * dt)
{
	switch (selection)
	{
	case 0:
		dt->SetID(txt);
		break;
	case 1:
		dt->SetName(txt);
		break;
	case 2:
		dt->SetYear(GeneralFuncs::ConvertStringToInt(txt.c_str()));
		break;
	case 3:
		dt->SetTime(GeneralFuncs::ConvertStringToInt(txt.c_str()));
		break;
	case 4:
		dt->SetState(GeneralFuncs::ConvertStringToInt(txt.c_str()));
		break;
	default:
		break;
	}
}

void ReaderData::Update()
{
	WriteFile(OUTPUTDIRREADER, reader_data);
}
