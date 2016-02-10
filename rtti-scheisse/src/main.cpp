#include "person.h"
#include "object.h"
#include <iostream>
#include <cassert>

void foo(test::Person& p, rtti::Class* t) {
	t = p.getTypeinfo();
}

int main() {
	using namespace test;
	using namespace rtti;
	Person p;
	rtti::Class* typeinfo = p.getTypeinfo();
	{
		Person a;
		typeinfo = a.getTypeinfo();
		foo(a, typeinfo);
	}
	foo(p, typeinfo);
	typeinfo = p.getTypeinfo();
	rtti::Object o;
	auto a = p.getRTTIFields()[0];
	int age = 500;
	a.setValue(&p, &age);
	int gg = 0;
	a.getValue(&p, &gg);
	std::cout << gg << std::endl;
	
	//std::cout << rtti::Object::instanceOf(p.getTypeinfo(), o.getTypeinfo()) << std::endl;
	return 0;
}