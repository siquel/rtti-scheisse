#include "person.h"
#include "object.h"
#include "rtti.h"
namespace test {
	RTTI_REGISTER_CLASS(Person);

	Person::Person(int age) 
		: age(age) {

	}

	Person::Person() : age(0) {

	}

}