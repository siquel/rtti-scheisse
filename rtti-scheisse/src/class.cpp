#include "class.h"
#include "descriptor.h"
#include "class_repo.h"
namespace rtti {

	RTTIType RTTIType::VoidType(RTTI_VOID_TYPE);
	RTTIType RTTIType::IntType(RTTI_INT_TYPE);
	RTTIType RTTIType::UintType(RTTI_UINT_TYPE);

	Class::Class(const char* name, size_t size, RTTIDescFieldsFunc fieldFunc, RTTICreateInstanceFunc instanceFunc)
		: name(name), size(size), instanceFunc(instanceFunc) {
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
		rtti::ClassRepository::getInstance().addClass(this);
	}

	RTTIFieldDescriptor** Class::getFields(size_t* count) {
		*count = fieldCount;
		return fields;
	}

	RTTIFieldDescriptor* Class::getFieldByName(const std::string& name) const {
		for (size_t i = 0; i < fieldCount; ++i) {
			if (name == fields[i]->name) return fields[i];
		}
		return nullptr;
	}

	Class* Class::classForName(const std::string& name) {
		return ClassRepository::getInstance().classForName(name);
	}

	const std::string& Class::getTypeName() const {
		return name;
	}

	Class::~Class() {
		delete[] fields;
	}
}