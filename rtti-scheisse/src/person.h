#include "rtti.h"
#include "object.h"

namespace test {
	class Person : public rtti::Object {
	private:
		int age;
	public:
		RTTI_DESCRIBE_CLASS(Person,
			(RTTI_FIELD(age, 0)));
	};
}