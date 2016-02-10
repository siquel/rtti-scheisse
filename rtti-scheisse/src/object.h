#pragma once
#include "rtti.h"
namespace rtti {
	class Object {
		DEFINE_CLASS(Object);
		friend class RTTIFieldDescriptor;
	public:
		
		static bool instanceOf(const Class* a, const Class* b);
	};
}