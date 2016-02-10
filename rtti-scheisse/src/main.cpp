#include "person.h"
#include "object.h"
#include <iostream>
int main() {
	using namespace test;
	using namespace rtti;
	Person p;
	rtti::Object o;
	auto a = p.getRTTIFields()[0];
	int age = 500;
	a.setValue(&a, &age);
	int gg = 0;
	a.getValue(&a, &gg);
	std::cout << gg << std::endl;
	//std::cout << rtti::Object::instanceOf(p.getTypeinfo(), o.getTypeinfo()) << std::endl;
	return 0;
}