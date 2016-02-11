#include "descriptor.h"
#include <cstring>

namespace rtti {
	RTTIFieldDescriptor::RTTIFieldDescriptor(char* const name, int offset, size_t size, int flags, RTTIType* type)
		: name(name), offset(offset), size(size), flags(flags), type(type), next(nullptr), chain(&next) {

	}

	void RTTIFieldDescriptor::setValue(void* self, void* args) {
		// get the address of field and copy the data to that position
		std::memcpy((char*)self + offset, args, size);
	}
	// get the value
	void RTTIFieldDescriptor::getValue(void* self, void* to) {
		// copy the value to buffer
		std::memcpy(to, (char*)self + offset, size);
	}
}