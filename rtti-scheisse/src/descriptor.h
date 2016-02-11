#pragma once
#include <string>
namespace rtti {

	class RTTIFunc {
	public:
		virtual void invoke(void* ret, void* obj, void* params[]) = 0;
	};

	class RTTIType;
	
	class RTTIFieldDescriptor {
		friend class Class;
	protected:
		int flags;
		RTTIType* type;
		int offset;
		size_t size;
		size_t index;
		std::string name;
		RTTIFieldDescriptor* next;
		RTTIFieldDescriptor** chain;
	public:

		RTTIFieldDescriptor(std::string name, int offset, size_t size, int flags, RTTIType* type);

		// The macro uses comma separated list to define values
		// this func is called when returning the list and is building the chain
		RTTIFieldDescriptor& operator, (RTTIFieldDescriptor& field) {
			*chain = &field;
			chain = &field.next;
			return *this;
		}

		const std::string& getName() const { return name; }

		size_t getSize() const { return size; }

		int getOffset() const { return offset; }

		void setValue(void* self, void* args);
		void getValue(void* self, void* to);
	};

	class RTTIFuncDescriptor {
		friend class Class;
	public:
		RTTIFuncDescriptor(std::string name, int flags, rtti::RTTIFunc*);

	protected:
		std::string name;
		int flags;
		RTTIFuncDescriptor* next;
		RTTIFuncDescriptor** chain;
	};
}