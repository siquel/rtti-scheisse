#include "activator.h"
#include "class.h"
#include <cassert>
namespace rtti {
	void* Activator::createInstance(const std::string& className){
		Class* clazz = Class::classForName(className);
		assert(clazz != nullptr);
		assert(clazz->instanceFunc != nullptr);
		return clazz->instanceFunc();
	}
}