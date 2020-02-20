#ifndef ACTLIB_H_
#define ACTLIB_H_

#include <iostream>
#include "DocGia.h"
#include "SachData.h"
#include "InputOutputText.h"
#include <ctime>

enum Act{
	Borrow,
	Take
};

class Time
{
	int day;
	int month;
	int year;
public:
	Time();
	Time(int d, int m, int y);
	std::string Tostring();
	static bool KiemtraNamNhuan(int year);
	static bool KiemtraNgayHople(int year, int thang, int day);
	static int SubtractDay(Time t1, Time t2);
	int SubCurent();
};

class ActionInfo
{
private:
	Act act;
	std::string docgia;
	std::vector<std::string> books;
	Time b_time;
	Time r_time;
	unsigned int fine;
public:
	ActionInfo();
	Act GetAct();
	void SetAct(Act t);
	void SetAct(int t);
	std::string GetDocGia();
	void SetDocGia(std::string d);
	std::vector<std::string> GetBooks();
	void SetBook(std::vector<std::string> b);
	Time GetBTime();
	void SetBTime(Time t);
	Time GetRTime();
	void SetRTime(Time t);
	int Getfine();
	void Setfine(int t);
};

class Managerment : public InterractText<ActionInfo>
{
public:
	BookData * book_data;
	ReaderData * reader_data;
	std::vector<ActionInfo*> take_actions;
	std::vector<ActionInfo*> borrow_actions;

private:
	void Dislay(int stt, ActionInfo * t);
	bool GetNumberEachAct(std::string txt, int take_num, int borrow_num);
	bool ConvertStringtoTime(std::string txt, Time & t);
	void UnputTime(std::string txt, Time & t);
	std::vector<std::string> InputBookList(Act tmp);
	int GetfinebyOrder(ActionInfo * inf);

protected:
	virtual std::vector<ActionInfo*> Getfile() override;
	virtual std::vector<std::string> Setfile(const std::vector<ActionInfo*>& data) override;
public:
	Managerment();
	~Managerment();
	std::vector<ActionInfo*> Merge();
	void Update();
	void Create();
	void UpdateState();
	void GetLateOrder();
	void GetDocGiaTreHan();

};
#endif
