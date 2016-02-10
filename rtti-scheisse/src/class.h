#pragma once
#include <string>



namespace rtti {
	class RTTIFieldDescriptor;
	class Class {
		friend class Object;
		friend class RTTIFieldDescriptor;
	protected:
		std::string name;
		Class* baseClass;
		size_t size;
		RTTIFieldDescriptor* fields;
		size_t fieldCount;
	public:
		Class(const char* name, Class* baseClass, size_t size, RTTIFieldDescriptor* fields, size_t fieldCount)
			: name(name), baseClass(baseClass), size(size) {

		}
	};

	class RTTIType {
	public:
		static RTTIType VoidType;
		static RTTIType CharType;
		static RTTIType IntType;
		static RTTIType UintType;

	protected:
	};


	enum RTTIBindingFlags : int {
		RTTI_BF_PUBLIC = 0x001,
		RTTI_BF_PRIVATE = 0x002,
		RTTI_BF_PROTECTED = 0x004
	};

	class RTTIFieldDescriptor {
	protected:
		int flags;
		RTTIType* type;
		int offset;
		size_t size;
		char const* name;
		Class* declaringClass;
	public:

		RTTIFieldDescriptor(char* const name, int offset, size_t size, int flags, RTTIType* type, Class* clazz)
			: name(name), offset(offset), size(size), flags(flags), type(type), declaringClass(clazz) {

		}
		
		void setValue(void* self, void* args) {
			// get the address of field and copy the data to that position
			std::memcpy((char*)self + offset, args, size);
		}
		// get the value
		void getValue(void* self, void* to) {
			// copy the value to buffer
			std::memcpy(to, (char*)self + offset, size);
		}
	};
}

