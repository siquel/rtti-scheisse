#include "rtti.h"
#include "object.h"
#include "class.h"

namespace test {

	class Component {
	public:
		Component() = default;
		int val{ 715517 };
		RTTI_DESCRIBE_CLASS(Component, 
			(
				RTTI_FIELD(val, rtti::RTTIBindingFlags::RTTI_BF_PRIVATE)
			)
		);
	};

	class Person  {
	public:
		int age;
		int gg;
		Component test;
	public:
		Person(int age);
		// required
		Person();
		RTTI_DESCRIBE_CLASS(Person,
			(
			RTTI_FIELD(age, rtti::RTTIBindingFlags::RTTI_BF_PRIVATE),
			RTTI_FIELD(gg, rtti::RTTIBindingFlags::RTTI_BF_PRIVATE),
			RTTI_FIELD(test, rtti::RTTIBindingFlags::RTTI_BF_PUBLIC)
			)
		);
		
	};
}