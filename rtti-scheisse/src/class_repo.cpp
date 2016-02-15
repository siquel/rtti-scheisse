#include "class_repo.h"
#include "class.h"
namespace rtti {
	Class* ClassRepository::classForName(const std::string& name) const {
		if (classSet.count(name)) {
			return classSet.at(name);
		}
		return nullptr;
	}

	void ClassRepository::addClass(Class* clazz) {
		classSet[clazz->getTypeName()] = clazz;
	}
}