#ifndef OBJECT_H_
#define OBJECT_H_
#include <iostream>
#include <string>

class Object
{
private:
	std::string id;
	std::string name;
public:
	Object();
	void SetID(std::string id);
	void SetName(std::string name_);
	std::string Id();
	std::string Name();
};

#endif // !1