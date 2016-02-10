#include "rtti.h"
#include "object.h"

namespace test {
	class Person : public rtti::Object {
	private:
		DEFINE_CLASS(Person);
	public:
		
		DECLARE_PROPERTY(int, age, Age);
	};
}