#ifndef _SACHDATA_H_
#define _SACHDATA_H_

#include<iostream>
#include<string>
#include "Object.h"
#include "InputOutputText.h"
#include <vector>
#include "Constant.h"
#include "Manipulation.h"
enum Genre
{
	VietNamese,
	English
};
class Book :public Object
{
private:
	Genre genre;
	std::string author;
	std::string publisher;
	unsigned int price;
	int number;
public:
	Book();
	void SetGenreOfBook(Genre gen_);
	void SetAuthor(std::string author_);
	void SetPublisher(std::string publisher_);
	void SetPrice(int cost_);
	void UpdateNumber(int num_);
	Genre GetGenreOfBook();
	std::string Author();
	std::string Publisher();
	int Price();
	int Number();

};


class BookData : public InterractText<Book>,
	protected Manipulation<Book>
{
private:
	std::vector<Book*> data;
	std::vector<Book*> del_data;
private:
	bool Remove(int selection, std::string val);
	int	 ModifyOption();
	void displayOption();
	int ModifyElementOption();
protected:
	virtual std::string GetDtaInSelection(int selection, Book * dt) override;
	virtual void Display(int stt, Book * val) override;
	virtual void SetDtaInSelection(int selection, std::string txt, Book * dt) override;
public:
	BookData();
	~BookData();
	void Pushdata(Book * dt);
	bool Search(int selection, std::string val, bool is_display);
	std::vector<Book*> Getdata();
	void ShowData();
	Book* FindID(std::string txt);
	bool Removedel(Book * dt);
	virtual std::vector<Book*> Getfile() override;
	virtual std::vector<std::string> Setfile(const std::vector<Book*> & data) override;
	virtual bool Remove() override;
	virtual void Create() override;
	virtual void Search() override;
	virtual void Modify() override;
	virtual void Update() override;

};
#endif // !
