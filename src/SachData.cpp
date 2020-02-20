#include "SachData.h"
#include "GeneralFuncs.h"
Book::Book() :Object(),
genre(VietNamese),
author(std::string()),
publisher(std::string()),
price(0.0),
number(0)
{
}

void Book::SetGenreOfBook(Genre gen)
{
	genre = gen;
}



void Book::SetAuthor(std::string author_)
{
	author = author_;
}

void Book::SetPublisher(std::string publisher_)
{
	publisher = publisher_;
}

void Book::SetPrice(int cost_)
{
	price = cost_;
}

void Book::UpdateNumber(int num_)
{
	number = num_;
}

Genre Book::GetGenreOfBook()
{
	return genre;
}



std::string Book::Author()
{
	return author;
}

std::string Book::Publisher()
{
	return publisher;
}

int Book::Price()
{
	return price;
}

int Book::Number()
{
	return number;
}



std::string BookData::GetDtaInSelection(int selection, Book * dt)
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
		tmp_val = dt->Author();
		break;
	case 3:
		tmp_val = dt->Publisher();
		break;
	case 4:
		tmp_val = GeneralFuncs::ConvertIntToString(dt->Price());
		break;
	default:
		break;
	}
	return tmp_val;
}

bool BookData::Search(int selection, std::string val, bool is_display)
{
	int count = 0;
	for (int i = 0; i < data.size(); i++)
	{
		std::string tmp_val = GetDtaInSelection(selection, data[i]);
		if (strcmp(tmp_val.c_str(), val.c_str()) == 0)
		{
			count++;
			if (is_display)
				Display(count, data[i]);
		}
	}
	if (count == 0)
		return false;
	return true;
}

bool BookData::Remove(int selection, std::string val)
{
	int b_f_size = data.size();
	{
		std::vector<Book*>::iterator iter = data.begin();
		while (iter != data.end())
		{
			std::string tmp_val = GetDtaInSelection(0, *iter);
			if (strcmp(tmp_val.c_str(), val.c_str()) == 0)
			{
				Book* tmp = *iter;
				iter = data.erase(iter);
				tmp->UpdateNumber(0);
				del_data.push_back(*iter);
			}
			else
			{
				++iter;
			}
		}
	}
	if (b_f_size > data.size())
		return true;
	else
		return false;
}

int BookData::ModifyOption()
{
	GeneralFuncs::ClearSceen();
	std::cout << "1:Ten: " << std::endl;
	std::cout << "2:Tac gia: " << std::endl;
	std::cout << "3:NXB: " << std::endl;
	std::cout << "4:Gia: " << std::endl;
	std::cout << "5:So luong: " << std::endl;
	std::cout << "0:thoat: " << std::endl;
	std::cout << "Lua chon cua ban : ";
	return GeneralFuncs::OnlyInputNumber("Lua chon cua ban : ");
}

void BookData::displayOption()
{
}

void BookData::ShowData()
{
	for (int i = 0; i < data.size(); i++)
	{
		Display(i + 1, data[i]);
	}
}

Book* BookData::FindID(std::string txt)
{
	int count = 0;
	for (int i = 0; i < data.size(); i++)
	{
		if (strcmp(data[i]->Id().c_str(), txt.c_str()) == 0)
		{
			return data[i];
		}
	}
	for (int i = 0; i < del_data.size(); i++)
	{
		if (strcmp(del_data[i]->Id().c_str(), txt.c_str()) == 0)
		{
			return del_data[i];
		}
	}
	return NULL;
}

bool BookData::Removedel(Book * dt)
{
	int b_f_size = data.size();
	{
		std::vector<Book*>::iterator iter = del_data.begin();
		while (iter != del_data.end())
		{
			if (dt == *iter)
			{
				iter = del_data.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
	if (b_f_size > data.size())
		return true;
	else
		return false;
}

int BookData::ModifyElementOption()
{
	GeneralFuncs::ClearSceen();
	ShowData();
	std::cout << "0: thoat: " << std::endl;
	std::cout << "**********************" << std::endl;
	std::cout << "Chon so thu tu : ";
	return GeneralFuncs::OnlyInputNumber("Chon so thu tu : ");
}

void BookData::Display(int stt, Book * val)
{
	std::cout << "stt: " << stt << std::endl;
	if (val->GetGenreOfBook() == Genre::VietNamese)
		std::cout << "Loai: TV" << std::endl;
	else
		std::cout << "Loai: NV" << std::endl;
	std::cout << "Id: " << val->Id() << std::endl;
	std::cout << "Ten Sach: " << val->Name() << std::endl;
	std::cout << "Tac Gia: " << val->Author() << std::endl;
	std::cout << "Gia: " << val->Price() << std::endl;
	std::cout << "So luong: " << val->Number() << std::endl;
	std::cout << "----------------------------------------------" << std::endl;
}

void BookData::SetDtaInSelection(int selection, std::string txt, Book * dt)
{
	std::string tmp_val = std::string();
	switch (selection)
	{
	case 0:
		dt->SetID(txt);
		break;
	case 1:
		dt->SetName(txt);
		break;
	case 2:
		dt->SetAuthor(txt);
		break;
	case 3:
		dt->SetPublisher(txt);
		break;
	case 4:
		dt->SetPrice(GeneralFuncs::ConvertStringToInt(txt.c_str()));
		break;
	case 5:
		dt->UpdateNumber(GeneralFuncs::ConvertStringToInt(txt.c_str()));
		break;
	default:
		break;
	}
}

BookData::BookData() :data(std::vector<Book*>()),
del_data(std::vector<Book*>())
{
	data = Getfile();
}

BookData::~BookData()
{
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i] != nullptr)
		{
			delete data[i];
		}
	}
	data.clear();
}

void BookData::Pushdata(Book * dt)
{
	data.push_back(dt);
}

std::vector<Book*> BookData::Getdata()
{
	return data;
}

std::vector<Book*> BookData::Getfile()
{
	std::vector<std::string> string_lst = std::vector<std::string>();
	std::string input = INPUTDIR;
	ReadFile(&input, &string_lst);
	std::vector<std::string> arr = std::vector<std::string>();
	std::vector<Book*> rtrn = std::vector<Book*>();
	for (int step = 0; step < string_lst.size(); step++)
	{
		arr = SplitString(string_lst[step], SPLITSIGN);
		if (arr.size() == 7)
		{
			Book * tmp = new Book();
			if (strcmp(arr[0].c_str(), TV) == 0)
				tmp->SetGenreOfBook(Genre::VietNamese);
			if (strcmp(arr[0].c_str(), NV) == 0)
				tmp->SetGenreOfBook(Genre::English);
			tmp->SetID(arr[1]);
			tmp->SetName(arr[2]);
			tmp->SetAuthor(arr[3]);
			tmp->SetPublisher(arr[4]);
			tmp->SetPrice(GeneralFuncs::ConvertStringToDouble(arr[5].c_str()));
			tmp->UpdateNumber(GeneralFuncs::ConvertStringToInt(arr[6].c_str()));
			rtrn.push_back(tmp);
		}
	}
	return rtrn;
}

std::vector<std::string> BookData::Setfile(const std::vector<Book*> & data)
{
	std::vector<std::string> vec = std::vector<std::string>();
	for (std::vector<Book*>::const_iterator iter = data.begin(); iter != data.end(); iter++)
	{
		if ((*iter)->GetGenreOfBook() == Genre::VietNamese)
		{
			std::string tmp = "TV, " + (*iter)->Id() + ", " + (*iter)->Name() + ", " + (*iter)->Author() + ", "
				+ (*iter)->Publisher() + ", " + GeneralFuncs::ConvertDoubleToString((*iter)->Price())
				+ ", " + GeneralFuncs::ConvertIntToString((*iter)->Number());
			vec.push_back(tmp);
		}
		else
		{
			std::string tmp = "NV, " + (*iter)->Id() + ", " + (*iter)->Name() + ", " + (*iter)->Author() + ", "
				+ (*iter)->Publisher() + ", " + GeneralFuncs::ConvertDoubleToString((*iter)->Price())
				+ ", " + GeneralFuncs::ConvertIntToString((*iter)->Number());
			vec.push_back(tmp);
		}
	}
	return vec;
}

bool BookData::Remove()
{
	GeneralFuncs::ClearSceen();
	int i = INFINITY;
	std::string txt = std::string();
	ShowData();
	std::cout << "Your Selection: " << std::endl;
	i = GeneralFuncs::OnlyInputNumber("Your Selection: ");
	if (i >= data.size() && i > 0)
		return false;
	{

	}
	txt = data.at(i - 1)->Id();
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

void BookData::Create()
{
	GeneralFuncs::ClearSceen();
	Book * dt = new Book();
	while (1)
	{
		std::string txt = Inputtext("Loai Sach <TV/NV>: ");
		if (strcmp(txt.c_str(), TV) == 0)
		{
			dt->SetGenreOfBook(Genre::VietNamese);
			break;
		}
		if (strcmp(txt.c_str(), NV) == 0)
		{
			dt->SetGenreOfBook(Genre::English);
			break;
		}
	}
	{
		dt->SetID(Inputtext("Ma sach: "));
	}
	{
		dt->SetName(Inputtext("Ten sach: "));
	}
	{
		dt->SetAuthor(Inputtext("Ten tac gia: "));
	}
	{
		dt->SetPublisher(Inputtext("Ten nha xuat ban: "));
	}
	{
		std::cout << "Gia: ";
		dt->SetPrice(GeneralFuncs::OnlyInputNumber("Gia: "));
	}
	{
		std::cout << "So luong: ";
		dt->UpdateNumber(GeneralFuncs::OnlyInputNumber("So luong: "));
	}
	if (Search(0, dt->Id(), false))
	{
		delete dt;
		std::cout << "Ma sach da ton tai:" << std::endl;
	}
	data.push_back(dt);
}

void BookData::Search()
{
	GeneralFuncs::ClearSceen();
	int selection = -1;
	ShowData();
	selection = ModifyOption();
	if (selection > VALREMOVEBOOK || selection < 1)
		return;
	std::string val = std::string();
	std::cout << "Gia tri can tim: " << std::endl;
	std::cin >> val;
	if (!Search(selection, val, true))
		std::cout << "Khong tim thay gia tri can tim" << std::endl;
}

void BookData::Modify()
{
	GeneralFuncs::ClearSceen();
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
				if (selection > data.size() || selection < EXIT)
				{
					continue;
				}
				Display(selection, data[selection - 1]);
				std::string txt = Inputtext("Gia tri moi: ");
				SetDtaInSelection(is_break, txt, data[selection - 1]);
			}
		}
	}
}

void BookData::Update()
{
	WriteFile(OUTPUTDIR, data);
}
