#include "object.h"
#include "class.h"
namespace rtti {

	bool Object::instanceOf(const Class* src, const Class* base) {
		if (src == base) return true;

		Class* parent = src->baseClass;
		while (parent != nullptr) {
			if (parent == base)
				return true;
			parent = parent->baseClass;
		}
		return false;
	}

}