#pragma once
#include <string>
#include <iostream>
namespace rtti {
	class RTTIType;
	class RTTIFieldDescriptor {
		friend class Class;
	protected:
		int flags;
		RTTIType* type;
		int offset;
		size_t size;
		size_t index;
		char const* name;
		RTTIFieldDescriptor* next;
		RTTIFieldDescriptor** chain;
	public:

		RTTIFieldDescriptor(char* const name, int offset, size_t size, int flags, RTTIType* type)
			: name(name), offset(offset), size(size), flags(flags), type(type), next(nullptr), chain(&next) {

		}

		// The macro uses comma separated list to define values
		// this func is called when returning the list and is building the chain
		RTTIFieldDescriptor& operator, (RTTIFieldDescriptor& field) {
			*chain = &field;
			chain = &field.next;
			return *this;
		}

		~RTTIFieldDescriptor() {
			std::cout << "död\n";
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

	class RTTIFieldDescriptor;

	using RTTIDescFieldsFunc = RTTIFieldDescriptor* (*)();

	class Class {
		friend class Object;
		friend class RTTIFieldDescriptor;
	protected:
		std::string name;
		Class* baseClass;
		size_t size;
		RTTIFieldDescriptor* fieldList;
		RTTIFieldDescriptor** fields;
		size_t fieldCount;
	public:
		Class(const char* name, Class* baseClass, size_t size, RTTIDescFieldsFunc fieldFunc)
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
		~Class() {
			delete[] fields;
		}

		RTTIFieldDescriptor* getFieldByName(const char* name) const {

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

	
}

