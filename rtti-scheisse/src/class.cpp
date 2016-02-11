#include "class.h"
#include "descriptor.h"

namespace rtti {
	Class::Class(const char* name, Class* baseClass, size_t size, RTTIDescFieldsFunc fieldFunc)
		: name(name), baseClass(baseClass), size(size) {
		fieldList = (*fieldFunc)();
		size_t n = 0;
		RTTIFieldDescriptor* fd = nullptr;
		for (fd = fieldList, n = 0; fd != nullptr; fd = fd->next) {
			fd->index = n;
			++n;
		}
		fieldCount = n;
		fields = new RTTIFieldDescriptor*[fieldCount];
		for (fd = fieldList, n = 0; fd != nullptr; fd = fd->next) {
			fields[n++] = fd;
		}
	}

	RTTIFieldDescriptor* Class::getFieldByName(const std::string& name) const {
		for (size_t i = 0; i < fieldCount; ++i) {
			if (name == fields[i]->name) return fields[i];
		}
		return nullptr;
	}

	Class::~Class() {
		delete[] fields;
	}
}