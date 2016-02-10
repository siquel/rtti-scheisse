#pragma once
#include <string>



namespace rtti {
	class Class {
		friend class Object;
	protected:
		std::string name;
		Class* baseClass;
		size_t size;
	public:
		Class(const char* name, Class* baseClass, size_t size)
			: name(name), baseClass(baseClass), size(size) {

		}
	};
}

