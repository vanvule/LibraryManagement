#include "UIGraph.h"

GUI::GUI() :tmp(new Managerment())
{
}

GUI::~GUI()
{
	if (tmp == NULL)
		delete tmp;
}

Managerment * GUI::Getdata()
{
	return tmp;
}

void GUI::graph_1()
{
	bool is_true = true;
	while (is_true)
	{
		GeneralFuncs::ClearSceen();
		std::cout << "1: Tuong tac voi du lieu sach " << std::endl;
		std::cout << "2: Tuong tac voi du lieu nguoi doc " << std::endl;
		std::cout << "3: Lap va trinh sua phieu " << std::endl;
		std::cout << "4: Danh sach nguoi doc qua han" << std::endl;
		std::cout << "0: Thoat " << std::endl;
		std::cout << "-------------------------------------" << std::endl;
		std::cout << "Lua chon: ";
		int selection = GeneralFuncs::OnlyInputNumber("Lua chon: ");
		switch (selection)
		{
		case 1:
			graph_book();
			break;
		case 2:
			graph_reader();
			break;
		case 3:
			graph_lapphieu();
			break;
		case 4:
			tmp->GetDocGiaTreHan();
			break;
		case 0:
			is_true = false;
			break;
		default:
			break;
		}
	}


}

void GUI::graph_reader()
{
	bool is_true = true;
	while (is_true)
	{
		GeneralFuncs::ClearSceen();
		std::cout << "1: Tao moi " << std::endl;
		std::cout << "2: Xoa " << std::endl;
		std::cout << "3: Sua " << std::endl;
		std::cout << "4: Tim kiem" << std::endl;
		std::cout << "5: Hien thi" << std::endl;
		std::cout << "0: Thoat " << std::endl;
		std::cout << "-------------------------------------" << std::endl;
		std::cout << "Lua chon: ";
		int selection = GeneralFuncs::OnlyInputNumber("Lua chon: ");
		switch (selection)
		{
		case 1:
			tmp->reader_data->Create();
			tmp->reader_data->Update();
			break;
		case 2:
			tmp->reader_data->Remove();
			tmp->reader_data->Update();
			break;
		case 3:
			tmp->reader_data->Modify();
			tmp->reader_data->Update();
			break;
		case 4:
			tmp->reader_data->Search();
			tmp->reader_data->Update();
			break;
		case 5:
			GeneralFuncs::ClearSceen();
			tmp->reader_data->ShowData();
			getchar();
			break;
		case 0:
			is_true = false;
			break;
		default:
			break;
		}
	}
}

void GUI::graph_lapphieu()
{
	bool is_true = true;
	while (is_true)
	{
		GeneralFuncs::ClearSceen();
		std::cout << "1: Tao moi " << std::endl;
		std::cout << "2: Cap nhap " << std::endl;
		std::cout << "0: Thoat" << std::endl;
		std::cout << "-------------------------------------" << std::endl;
		std::cout << "Lua chon: ";
		int selection = GeneralFuncs::OnlyInputNumber("Lua chon: ");
		switch (selection)
		{
		case 1:
			tmp->Create();
			tmp->Update();
			break;
		case 2:
			tmp->UpdateState();
			tmp->Update();
			break;
		case 0:
			is_true = false;
			break;
		default:
			break;
		}
	}
}

void GUI::graph_book()
{
	bool is_true = true;
	while (is_true)
	{
		GeneralFuncs::ClearSceen();
		std::cout << "1: Tao moi " << std::endl;
		std::cout << "2: Xoa " << std::endl;
		std::cout << "3: Sua " << std::endl;
		std::cout << "4: Tim kiem" << std::endl;
		std::cout << "5: Hien thi" << std::endl;
		std::cout << "0: Thoat " << std::endl;
		std::cout << "-------------------------------------" << std::endl;
		std::cout << "Lua chon: ";
		int selection = GeneralFuncs::OnlyInputNumber("Lua chon: ");
		switch (selection)
		{
		case 1:
			tmp->book_data->Create();
			tmp->book_data->Update();
			break;
		case 2:
			tmp->book_data->Remove();
			tmp->book_data->Update();
			break;
		case 3:
			tmp->book_data->Modify();
			tmp->book_data->Update();
			break;
		case 4:
			tmp->book_data->Search();
			tmp->book_data->Update();
			break;
		case 5:
			GeneralFuncs::ClearSceen();
			tmp->book_data->ShowData();
			getchar();
		case 0:
			is_true = false;
			break;
		default:
			break;
		}
	}
}
