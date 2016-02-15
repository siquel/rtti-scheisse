#include "object.h"
#include "class.h"
namespace rtti {

	bool Object::instanceOf(const Class* src, const Class* base) {
		// TODO Fix
		return (src == base);
	}

}