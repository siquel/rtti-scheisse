#include "rtti.h"
#include "object.h"
#include "class.h"

namespace test {
	class Person : public rtti::Object {
	private:
		int age;
		int gg;
	public:
		RTTI_DESCRIBE_CLASS(Person,
			(
			RTTI_FIELD(age, rtti::RTTIBindingFlags::RTTI_BF_PRIVATE),
			RTTI_FIELD(gg, rtti::RTTIBindingFlags::RTTI_BF_PRIVATE)
			)
		);
	};
}