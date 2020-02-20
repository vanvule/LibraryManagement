#ifndef _DOCGIA_H_
#define _DOCGIA_H_

#include "Object.h"
#include "InputOutputText.h"
#include "Manipulation.h"
#include<iostream>
#include<string>
#include <list>
enum State
{
	Uncompleted,
	Completed
};

class Reader :public Object
{
private:
	int year;
	int time;
	State state;
public:
	Reader();
	void SetYear(int year_);
	void SetTime(int time_);
	void SetState(State st);
	int GetYear();
	int GetTime();
	State GetState();
	void SetState(int st);
	// Inherited via InterractText
};

class ReaderData :public InterractText<Reader>,
	protected Manipulation<Reader>
{
	// Inherited via InterractText
private:
	std::vector<Reader*> reader_data;
	std::vector<Reader*> del_reader;
private:
	bool Remove(int selection, std::string val);
	int ModifyOption();
	int ModifyElementOption();
protected:

	virtual void Display(int stt, Reader * val) override;
	virtual std::string GetDtaInSelection(int selection, Reader * dt) override;
	virtual void SetDtaInSelection(int selection, std::string txt, Reader * dt) override;
public:
	ReaderData();
	~ReaderData();
	Reader * FindId(std::string txt);
	std::vector<Reader*> GetData();
	bool Search(int selection, std::string val, bool is_display);
	virtual std::vector<Reader*> Getfile() override;
	virtual std::vector<std::string> Setfile(const std::vector<Reader*>& data) override;
	virtual bool Remove() override;
	virtual void Create() override;
	virtual void Search() override;
	virtual void Modify() override;
	void ShowData();
	// Inherited via InterractText



	// Inherited via InterractText


	// Inherited via Manipulation
	virtual void Update() override;
};

#endif // !_DOCGIA_H_

