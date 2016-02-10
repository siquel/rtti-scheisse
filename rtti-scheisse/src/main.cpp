#include "person.h"
#include "object.h"
#include <iostream>
int main() {
	using namespace test;
	Person p;
	p.setAge(55);
	rtti::Object o;
	std::cout << p.getAge() << std::endl;
	std::cout << rtti::Object::instanceOf(p.getTypeinfo(), o.getTypeinfo()) << std::endl;
}