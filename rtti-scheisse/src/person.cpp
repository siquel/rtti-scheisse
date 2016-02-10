#include "person.h"
#include "object.h"
#include "rtti.h"
namespace test {
	//DECLARE_TYPEINFO_CLASS(Person, rtti::Object);
	RTTI_REGISTER_CLASS(Person);
}