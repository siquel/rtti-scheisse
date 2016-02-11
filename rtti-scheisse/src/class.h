#pragma once
#include <string>
namespace rtti {
	class RTTIType;
	

	class RTTIFieldDescriptor;
	class RTTIFuncDescriptor;

	enum RTTIBindingFlags : int {
		RTTI_BF_PUBLIC = 0x001,
		RTTI_BF_PRIVATE = 0x002,
		RTTI_BF_PROTECTED = 0x004
	};

	using RTTIDescFieldsFunc = RTTIFieldDescriptor* (*)();
	using RTTIDescCtorsFunc = RTTIFuncDescriptor* (*)();
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
		Class(const char* name, Class* baseClass, size_t size, RTTIDescFieldsFunc fieldFunc, RTTIDescCtorsFunc ctorFunc);
		~Class();

		RTTIFieldDescriptor* getFieldByName(const std::string& name) const;
		void getConstructor(const RTTIBindingFlags bindings);
	};

	class RTTIType {
	public:
		static RTTIType VoidType;
		static RTTIType CharType;
		static RTTIType IntType;
		static RTTIType UintType;

		enum Type {
			RTTI_INT_TYPE,
			RTTI_CHAR_TYPE,
			RTTI_UINT_TYPE,
			RTTI_VOID_TYPE
		}; 
	
		RTTIType(int tag) : tag(tag) {}
	private:
		int tag;
	protected:
	};
}

