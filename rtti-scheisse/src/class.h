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
	using RTTICreateInstanceFunc = void* (*)();
	class Class {
		friend class Activator;
		friend class Object;
		friend class RTTIFieldDescriptor;
	protected:
		std::string name;
		size_t size;
		RTTIFieldDescriptor* fieldList;
		RTTIFieldDescriptor** fields;
		size_t fieldCount;
		RTTICreateInstanceFunc instanceFunc;
	public:
		Class(const char* name, size_t size, RTTIDescFieldsFunc fieldFunc, RTTICreateInstanceFunc ctorFunc);
		~Class();

		RTTIFieldDescriptor* getFieldByName(const std::string& name) const;

		const std::string& getTypeName() const;

		static Class* classForName(const std::string& name);

		RTTIFieldDescriptor** getFields(size_t* count);

		size_t getSize() const { return size; }
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
		
		int getTag() const { return tag; }
	private:
		int tag;
	protected:
	};
}

