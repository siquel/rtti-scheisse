#include "person.h"
#include "object.h"
#include <iostream>
int main() {
	using namespace test;
	Person p;
	p.setAge(55);
	
	std::cout << rtti::Object::instanceOf(p.getTypeInfo(), p.getTypeInfo()) << std::endl;
}