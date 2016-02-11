#pragma once

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

		RTTIFieldDescriptor(char* const name, int offset, size_t size, int flags, RTTIType* type);

		// The macro uses comma separated list to define values
		// this func is called when returning the list and is building the chain
		RTTIFieldDescriptor& operator, (RTTIFieldDescriptor& field) {
			*chain = &field;
			chain = &field.next;
			return *this;
		}

		void setValue(void* self, void* args);
		void getValue(void* self, void* to);
	};
}