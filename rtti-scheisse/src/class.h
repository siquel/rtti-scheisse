#pragma once
#include <string>
namespace rtti {
	class RTTIType;
	

	class RTTIFieldDescriptor;

	enum RTTIBindingFlags : int {
		RTTI_BF_PUBLIC = 0x001,
		RTTI_BF_PRIVATE = 0x002,
		RTTI_BF_PROTECTED = 0x004
	};

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
		Class(const char* name, Class* baseClass, size_t size, RTTIDescFieldsFunc fieldFunc);
		~Class();

		RTTIFieldDescriptor* getFieldByName(const std::string& name) const;
	};

	class RTTIType {
	public:
		static RTTIType VoidType;
		static RTTIType CharType;
		static RTTIType IntType;
		static RTTIType UintType;

	protected:
	};
}

