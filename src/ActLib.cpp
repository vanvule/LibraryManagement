#include "ActLib.h"
#include "GeneralFuncs.h"
#pragma once

Time::Time() :day(0),
month(0),
year(0)
{
}

Time::Time(int d, int m, int y) :day(d),
month(m),
year(y)
{
}

std::string Time::Tostring()
{
	std::string day_ = GeneralFuncs::ConvertIntToString(day);
	if (day_.length() < 2)
		day_ = "0" + day_;
	std::string month_ = GeneralFuncs::ConvertIntToString(month);
	if (month_.length() < 2)
		month_ = "0" + month_;
	std::string year_ = GeneralFuncs::ConvertIntToString(year);
	while (year_.length() < 4)
	{
		year_ = "0" + year_;
	}
	return day_ + "-" + month_ + "-" + year_;

}

bool Time::KiemtraNamNhuan(int year)
{
	if (year % 100 == 0)
	{
		if (year % 400 == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (year % 4 == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Time::KiemtraNgayHople(int year, int thang, int day)
{
	if (thang == 1 || thang == 3 || thang == 5 || thang == 7 ||
		thang == 8 || thang == 10 || thang == 12)
	{
		if (day <= 31) return true;
	}
	else if (thang == 2)
	{
		if (KiemtraNamNhuan(year))
		{
			if (day <= 29) return true;
		}
		else
		{
			if (day <= 28) return true;
		}
	}
	else
	{
		if (day <= 30) return true;
	}
	return false;

}

int Time::SubtractDay(Time t1, Time t2)
{
	struct tm date_1 = { 0, 0, 12 };  // nominal time midday (arbitrary).
	date_1.tm_year = t1.year - 1900;
	date_1.tm_mon = t1.month - 1;  // note: zero indexed
	date_1.tm_mday = t1.day;
	struct tm date_2 = { 0, 0, 12 };  // nominal time midday (arbitrary).
	date_2.tm_year = t2.year - 1900;
	date_2.tm_mon = t2.month - 1;  // note: zero indexed
	date_2.tm_mday = t2.day;
	time_t date_seconds = mktime(&date_2) - mktime(&date_1);
	return date_seconds / (24 * 60 * 60);
}

int Time::SubCurent()
{
	struct tm date_1 = { 0, 0, 12 };  // nominal time midday (arbitrary).
	date_1.tm_year = year - 1900;
	date_1.tm_mon = month - 1;  // note: zero indexed
	date_1.tm_mday = day;
	std::time_t t = std::time(0);
	std::tm now = { 0, 0, 12 };
	localtime_s(&now, &t);
	time_t date_seconds = mktime(&now) - mktime(&date_1);
	return date_seconds / (24 * 60 * 60);
}

ActionInfo::ActionInfo() :act(Act::Borrow),
docgia(std::string()),
books(std::vector<std::string>()),
b_time(Time()),
r_time(Time()),
fine(0)
{
}


Act ActionInfo::GetAct()
{
	return act;
}

void ActionInfo::SetAct(Act t)
{
	act = t;
}

void ActionInfo::SetAct(int t)
{
	if (t == 0)
		act = Act::Borrow;
	else
		act = Act::Take;
}

std::string ActionInfo::GetDocGia()
{
	return docgia;
}

void ActionInfo::SetDocGia(std::string d)
{
	docgia = d;
}

std::vector<std::string> ActionInfo::GetBooks()
{
	return  books;
}

void ActionInfo::SetBook(std::vector<std::string> b)
{
	books = b;
}

Time ActionInfo::GetBTime()
{
	return b_time;
}

void ActionInfo::SetBTime(Time t)
{
	b_time = t;
}

Time ActionInfo::GetRTime()
{
	return r_time;
}

void ActionInfo::SetRTime(Time t)
{
	r_time = t;
}

int ActionInfo::Getfine()
{
	return fine;
}

void ActionInfo::Setfine(int t)
{
	fine = t;
}

Managerment::Managerment() :book_data(new BookData()),
reader_data(new ReaderData())
{
	std::vector<ActionInfo*> action = Getfile();
	for (int i = 0; i < action.size(); i++)
	{
		if (action[i]->GetAct() == Act::Take)
			take_actions.push_back(action[i]);
		if (action[i]->GetAct() == Act::Borrow)
		{
			if (book_data->Getdata().size() < 1)
				continue;
			if (reader_data->GetData().size() < 1)
				continue;
			bool is_exist = true;
			for (int j = 0; j < action[i]->GetBooks().size(); j++)
			{
				if (!book_data->Search(0, action[i]->GetBooks().at(j), false))
				{
					is_exist = false;
					break;
				}

			}
			if (!reader_data->Search(0, action[i]->GetDocGia(), false))
			{
				continue;
			}
			if (is_exist)
				borrow_actions.push_back(action[i]);
		}
	}
}

Managerment::~Managerment()
{
	if (book_data != NULL)
		delete book_data;
	if (reader_data != NULL)
		delete reader_data;
	for (int i = 0; i < take_actions.size(); i++)
	{
		if (take_actions[i] != NULL)
			delete take_actions[i];
	}
	take_actions.clear();

	for (int i = 0; i < borrow_actions.size(); i++)
	{
		if (borrow_actions[i] != NULL)
			delete borrow_actions[i];
	}
	borrow_actions.clear();
}

void Managerment::Update()
{
	WriteFile(OUNPUTDIRACTION, this->Merge());
	book_data->Update();
	reader_data->Update();
}

void Managerment::Create()
{
	ActionInfo * dt = new ActionInfo();
	{
		while (1)
		{
			std::cout << "Trang Thai <0-Muon/1-Tra>: ";
			int txt = GeneralFuncs::OnlyInputNumber("Trang Thai <0-Muon/1-Tra>: ");
			if (txt == 0)
			{
				dt->SetAct(0);
				break;
			}
			else if (txt == 1)
			{
				dt->SetAct(1);
				break;
			}
		}
		{
			while (1)
			{
				GeneralFuncs::ClearSceen();
				reader_data->ShowData();
				std::cout << "Chon Stt doc gia:";
				int i = GeneralFuncs::OnlyInputNumber("Chon Stt doc gia:");
				if (i > 0 && i <= reader_data->GetData().size())
				{
					dt->SetDocGia(reader_data->GetData().at(i - 1)->Id());
					if (dt->GetAct() == Act::Borrow)
						reader_data->GetData().at(i - 1)->SetTime(reader_data->GetData().at(i - 1)->GetTime() - 1);
					break;
				}
			}
		}
		{
			Time t = Time();
			UnputTime("Thoi gian cho muon: ", t);
			dt->SetBTime(t);
		}
		{
			Time t = Time();
			if (dt->GetAct() == Act::Take)
				UnputTime("Thoi gian tra: ", t);
			dt->SetRTime(t);
		}
		{
			dt->SetBook(InputBookList(dt->GetAct()));
		}
		{
			if (dt->GetAct() == Act::Take)
			{
				std::cout << "Tien phat: ";
				int txt = GeneralFuncs::OnlyInputNumber("Tien phat: ");
				dt->Setfine(txt);
			}
		}
	}
	if (dt->GetAct() == Act::Borrow)
		borrow_actions.push_back(dt);
	else
		take_actions.push_back(dt);
}

bool Managerment::ConvertStringtoTime(std::string txt, Time & t)
{
	std::vector<std::string> time = SplitString(txt, MINUSSIGN);
	if (time.size() == 3)
	{
		t = Time(GeneralFuncs::ConvertStringToInt(time[0].c_str()),
			GeneralFuncs::ConvertStringToInt(time[1].c_str()),
			GeneralFuncs::ConvertStringToInt(time[2].c_str()));
		return true;
	}
	return false;
}

void Managerment::UnputTime(std::string txt, Time & t)
{
	GeneralFuncs::ClearSceen();
	std::cout << txt << std::endl;
	int day = 0;
	int month = 0;
	int year = 0;
	while (1)
	{
		std::cout << "Nam: ";
		year = GeneralFuncs::OnlyInputNumber("Nam: ");
		if (year > 0)
		{
			break;
		}
	}
	while (1)
	{
		std::cout << "Thang: ";
		month = GeneralFuncs::OnlyInputNumber("Thang: ");
		if (month > 0 && month < 13)
		{
			break;
		}
	}
	while (1)
	{
		std::cout << "Ngay: ";
		day = GeneralFuncs::OnlyInputNumber("Ngay: ");
		if (day > 0 && day <= 31)
		{
			if (Time::KiemtraNgayHople(year, month, day))
				break;
		}
	}
	t = Time(day, month, year);
}

std::vector<std::string> Managerment::InputBookList(Act tmp)
{
	GeneralFuncs::ClearSceen();
	std::vector<std::string> books = std::vector<std::string>();
	book_data->ShowData();
	std::cout << "So luong sach cho thue: ";
	int n = GeneralFuncs::OnlyInputNumber("So luong sach cho thue: ");
	for (int i = 0; i < n;)
	{
		std::cout << "Chon Stt sach: ";
		int stt = GeneralFuncs::OnlyInputNumber("Chon Stt sach: ");
		if (stt > 0 && stt <= book_data->Getdata().size())
		{
			books.push_back(book_data->Getdata().at(stt - 1)->Id());
			if (tmp == Act::Take)
				book_data->Getdata().at(stt - 1)->UpdateNumber(book_data->Getdata().at(stt - 1)->Number() + 1);
			if (tmp == Act::Borrow)
				book_data->Getdata().at(stt - 1)->UpdateNumber(book_data->Getdata().at(stt - 1)->Number() - 1);
			i++;
		}
		else
			std::cout << "Sach khong ton tai." << std::endl;
	}
	return books;
}

void Managerment::UpdateState()
{
	GeneralFuncs::ClearSceen();
	for (int i = 0; i < borrow_actions.size(); i++)
	{
		Dislay(i + 1, borrow_actions[i]);
	}
	int choose = GeneralFuncs::OnlyInputNumber("Lua chon Stt: ");
	if (choose > 0 && choose <= borrow_actions.size())
	{
		std::cout << "Ban co muon thay doi trang thai <0/1>: ";
		int select = GeneralFuncs::OnlyInputNumber("Ban co muon thay doi trang thai <0 / 1> : ");
		if (select != 0)
		{
			ActionInfo* tmp = borrow_actions[select - 1];
			Reader * reader = reader_data->FindId(tmp->GetDocGia());
			reader->SetTime(reader->GetTime() + 1);
			reader->SetState(State::Completed);
			tmp->SetAct(Act::Take);
			Time t = Time();
			UnputTime("Nhap ngay tra: ", t);
			tmp->SetRTime(t);
			int day = Time::SubtractDay(tmp->GetRTime(), tmp->GetBTime());
			long fine = 0;
			for (int i = 0; i < tmp->GetBooks().size(); i++)
			{
				Book* book_tmp = book_data->FindID(tmp->GetBooks().at(i));

				if (book_tmp == NULL)
					continue;
				book_tmp->UpdateNumber(book_tmp->Number() + 1);
				if (!book_data->Search(0, book_tmp->Id(), false))
				{
					book_data->Pushdata(book_tmp);
					book_data->Removedel(book_tmp);
				}

				if (book_tmp->GetGenreOfBook() == Genre::VietNamese)
					fine += PHATTV;
				if (book_tmp->GetGenreOfBook() == Genre::English)
					fine += PHATNV;
			}
			tmp->Setfine(fine);
			if (day < DEADLINE)
			{
				fine = 0;
			}
			take_actions.push_back(tmp);
			borrow_actions.erase(borrow_actions.begin() + select - 1);
		}

	}
}

void Managerment::GetLateOrder()
{
	GeneralFuncs::ClearSceen();
	for (int i = 0; i < borrow_actions.size(); i++)
	{
		std::cout << "Id: ";
		std::cout << MUON;
		std::cout << borrow_actions[i]->GetDocGia() << std::endl;
		std::cout << "Thoi gian muon: ";
		std::cout << borrow_actions[i]->GetBTime().Tostring() << std::endl;
		std::cout << "So luong sach: " << borrow_actions[i]->GetBooks().size() << std::endl;
		std::cout << "Sach: ";
		int day = borrow_actions[i]->GetBTime().SubCurent();
		long fine = 0;
		if (day > DEADLINE)
		{
			for (int j = 0; j < borrow_actions[i]->GetBooks().size(); ++j)
			{
				Book* book_tmp = book_data->FindID(borrow_actions[i]->GetBooks().at(j));
				if (book_tmp->GetGenreOfBook() == Genre::VietNamese)
					fine += PHATTV;
				if (book_tmp->GetGenreOfBook() == Genre::English)
					fine += PHATNV;
				std::cout << borrow_actions[i]->GetBooks().at(j) << " ";
			}
		}

		std::cout << std::endl;
		std::cout << "Tien phat: " << fine << std::endl;
	}
	std::cout << "************************************************" << std::endl;
	getchar();
}

void Managerment::GetDocGiaTreHan()
{
	GeneralFuncs::ClearSceen();
	for (int i = 0; i < reader_data->GetData().size(); i++)
	{
		Reader * tmp = reader_data->GetData().at(i);
		long fine = 0;
		bool is_loan = false;
		for (int j = 0; j < borrow_actions.size(); j++)
		{
			if (borrow_actions[j]->GetDocGia() == tmp->Id())
			{
				fine += GetfinebyOrder(borrow_actions[j]);
				is_loan = true;
			}
		}
		if (is_loan)
		{
			std::cout << "Id:" << tmp->Id() << std::endl;
			std::cout << "Name:" << tmp->Name() << std::endl;
			std::cout << "Tien Phat:" << fine << std::endl;
			std::cout << "***********************************" << std::endl;
		}
	}
	getchar();
}

int Managerment::GetfinebyOrder(ActionInfo * inf)
{
	unsigned int fine = 0;
	for (int j = 0; j < inf->GetBooks().size(); ++j)
	{
		Book* book_tmp = book_data->FindID(inf->GetBooks().at(j));
		if (book_tmp->GetGenreOfBook() == Genre::VietNamese)
			fine += PHATTV;
		if (book_tmp->GetGenreOfBook() == Genre::English)
			fine += PHATNV;
	}
	return fine;
}

void Managerment::Dislay(int stt, ActionInfo * t)
{
	std::cout << stt << std::endl;;
	if (t->GetAct() == Act::Borrow)
	{
		std::cout << "Id: ";
		std::cout << MUON;
		std::cout << t->GetDocGia() << std::endl;
		std::cout << "Thoi gian muon: ";
		std::cout << t->GetBTime().Tostring() << std::endl;
		std::cout << "Thoi gian tra: 0" << std::endl;
		std::cout << "So luong sach: " << t->GetBooks().size() << std::endl;
		std::cout << "Sach: ";
		for (int i = 0; i < t->GetBooks().size(); i++)
		{
			std::cout << t->GetBooks().at(i) << " ";
		}
		std::cout << std::endl;
		std::cout << "Tien phat: " << t->Getfine() << std::endl;
		std::cout << "_______________________________________" << std::endl;

	}
	else
	{
		std::cout << "Id: ";
		std::cout << TRA;
		std::cout << t->GetDocGia() << std::endl;
		std::cout << "Thoi gian muon: ";
		std::cout << t->GetBTime().Tostring() << std::endl;
		std::cout << "Thoi gian tra: 0";
		std::cout << "So luong sach: " << t->GetBooks().size();
		std::cout << "Sach: ";
		for (int i = 0; i < t->GetBooks().size(); i++)
		{
			std::cout << t->GetBooks().at(i) << " ";
		}
		std::cout << std::endl;
		std::cout << "Tine phat: " << t->Getfine() << std::endl;
		std::cout << "_______________________________________" << std::endl;
	}
}

bool Managerment::GetNumberEachAct(std::string txt, int take_num, int borrow_num)
{
	std::vector<std::string> sign_lst = SplitString(txt, ' ');
	if (sign_lst.size() < 2)
		return false;
	take_num = GeneralFuncs::ConvertStringToInt(sign_lst[0].c_str());
	borrow_num = GeneralFuncs::ConvertStringToInt(sign_lst[1].c_str());
	return true;
}

std::vector<ActionInfo*> Managerment::Merge()
{
	for (int i = 0; i < take_actions.size(); i++)
	{
		borrow_actions.push_back(take_actions[i]);
	}
	return borrow_actions;
}


std::vector<ActionInfo*> Managerment::Getfile()
{
	std::vector<std::string> string_lst = std::vector<std::string>();
	std::string input = INPUTDIRACTION;
	ReadFile(&input, &string_lst);
	if (string_lst.size() <= 1)
		return std::vector<ActionInfo*>();
	int take_num = 0;
	int borrow_num = 0;
	if (!GetNumberEachAct(string_lst[0], take_num, borrow_num))
		return std::vector<ActionInfo*>();
	std::vector<ActionInfo*> rtrn = std::vector<ActionInfo*>();
	{
		for (int step = 1; step < string_lst.size(); step++)
		{
			std::vector<std::string> arr = SplitString(string_lst[step], SPLITSIGN);
			if (arr.size() > 5)
			{
				{
					ActionInfo * dt = new ActionInfo();
					{
						{
							int pos = INFINITY;
							pos = arr[0].find(MUON);
							if (pos != -1)
							{
								dt->SetAct(Act::Borrow);
								dt->SetDocGia(arr[0].substr(pos + 4));
							}
							else
							{
								pos = arr[0].find(TRA);
								if (pos != INFINITY)
								{
									dt->SetAct(Act::Take);
									dt->SetDocGia(arr[0].substr(pos + 3));
								}
							}
						}
						{
						Time b_t = Time();
						ConvertStringtoTime(arr[1], b_t);
						dt->SetBTime(b_t);
						Time r_t = Time();
						ConvertStringtoTime(arr[2], r_t);
						dt->SetRTime(r_t);
					}
						{
							int soluong = GeneralFuncs::ConvertStringToInt(arr[3].c_str());
							int count = 3;
							std::vector<std::string> books = std::vector<std::string>();
							while (soluong >= 1)
							{
								count++;
								soluong--;
								books.push_back(arr[count]);
							}
							dt->SetBook(books);
							dt->Setfine(GeneralFuncs::ConvertStringToInt(arr[count + 1].c_str()));
						}
					}
					rtrn.push_back(dt);
				}
			}
		}
	}
	return rtrn;
}

std::vector<std::string> Managerment::Setfile(const std::vector<ActionInfo*>& data)
{
	std::vector<std::string> rtrn = std::vector<std::string>();
	int take_num = 0;
	int borrow_num = 0;
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i]->GetAct() == Act::Borrow)
		{
			std::string tmp = MUON + data[i]->GetDocGia() + ", " + data[i]->GetBTime().Tostring() + ", " + " 0, "
				+ GeneralFuncs::ConvertIntToString(data[i]->GetBooks().size()) + ", ";
			for (int j = 0; j < data[i]->GetBooks().size(); j++)
			{
				tmp = tmp + data[i]->GetBooks().at(j) + ", ";
			}
			tmp = tmp + GeneralFuncs::ConvertIntToString(data[i]->Getfine());
			rtrn.push_back(tmp);
			borrow_num++;
		}
		else
		{
			std::string tmp = TRA + data[i]->GetDocGia() + ", " + data[i]->GetBTime().Tostring() + ", "
				+ data[i]->GetRTime().Tostring() + ", "
				+ GeneralFuncs::ConvertIntToString(data[i]->GetBooks().size()) + ", ";
			for (int j = 0; j < data[i]->GetBooks().size(); j++)
			{
				tmp = tmp + data[i]->GetBooks().at(j) + ", ";
			}
			tmp = tmp + GeneralFuncs::ConvertIntToString(data[i]->Getfine());
			rtrn.push_back(tmp);
			take_num++;
		}
	}
	std::string num = GeneralFuncs::ConvertIntToString(borrow_num) + " " + GeneralFuncs::ConvertIntToString(take_num);
	std::vector<std::string>::iterator iter = rtrn.begin();
	rtrn.insert(iter, num);
	return rtrn;
}
