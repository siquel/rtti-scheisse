#include "class.h"
#include "object.h"

namespace test {
	class Person : public rtti::Object {
	private:
		DEFINE_CLASS(Person);
	public:
		DECLARE_TYPEINFO_CLASS(Person, Object);
		
		DEFINE_PROPERTY(int, age, Age);
	};
}