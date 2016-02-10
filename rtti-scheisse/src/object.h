#pragma once
#include "rtti.h"
namespace rtti {
	class Object {
		DEFINE_CLASS(Object);
	public:
		
		static bool instanceOf(const Class* a, const Class* b);
	};
}