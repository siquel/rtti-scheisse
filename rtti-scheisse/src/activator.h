#pragma once
#include <string>
namespace rtti {
	class Activator{

	public:
		static void* createInstance(const std::string& className);
	};
}