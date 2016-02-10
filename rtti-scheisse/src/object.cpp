#include "object.h"
#include "class.h"
namespace rtti {

//	DECLARE_TYPEINFO_BASECLASS(Object);

	bool Object::instanceOf(const Class* src, const Class* base) {
		if (src == base) return true;

		Class* parent = src->baseClass;
		while (parent != nullptr) {
			if (parent == base)
				return true;
		}
		return false;
	}

}