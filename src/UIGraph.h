#ifndef  _UIGRAPH_H_
#define _UIGRAPH_H_
#include "ActLib.h"
#include "GeneralFuncs.h"
class GUI
{
private:
	Managerment * tmp;
public:
	GUI();
	~GUI();
	Managerment * Getdata();
	void graph_1();
	void graph_book();
	void graph_reader();
	void graph_lapphieu();
};
#endif // ! _UIGRAPH_H_
