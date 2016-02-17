#include "person.h"
#include "object.h"
#include <iostream>
#include <cassert>
#include "serialization.h"

void foo(test::Person& p, rtti::Class* t) {
	t = p.getTypeinfo();
}

int main() {
	using namespace test;
	using namespace rtti;
	Person p;
	p.age = 555;
	p.gg = 1337;
	rtti::MemoryStream stream;
	rtti::Class* typeinfo = p.getTypeinfo();
	assert(typeinfo == Class::classForName("Person"));
	RTTIFieldDescriptor* desc = typeinfo->getFieldByName("age");
	generateSerializable("Person", &p, stream);

	stream.seek(SeekPosition::Begin, 0);
	Person* ptr = deserialize<Person>(stream);
	return 0;
}