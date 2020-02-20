#ifndef _MANIPULATION_H_
#define _MANIPULATION_H_
#include <iostream>

template<typename X>
class Manipulation
{
protected:
	virtual std::string GetDtaInSelection(int selection, X * dt) = 0;
	virtual void SetDtaInSelection(int selection, std::string txt, X * dt) = 0;
	virtual void Display(int stt, X * val) = 0;
public:
	virtual  bool Remove() = 0;
	virtual  void Create() = 0;
	virtual  void Search() = 0;
	virtual  void Modify() = 0;
	virtual  void Update() = 0;
};
#endif