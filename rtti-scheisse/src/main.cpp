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
	RTTIFieldDescriptor* desc = typeinfo->getFieldByName("age");
	return 0;
}