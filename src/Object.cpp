#include "Object.h"
std::string Object::Id()
{
	return id;
}

std::string Object::Name()
{
	return name;
}
Object::Object() :
id(std::string()),
name(std::string())
{
}
void Object::SetID(std::string id_)
{
	id = id_;
}

void Object::SetName(std::string name_)
{
	name = name_;
}