#pragma once

#include <string>
#include <unordered_map>
namespace rtti {

	class Class;

	class ClassRepository {
	private:
		std::unordered_map<std::string, Class*> classSet;
		ClassRepository() = default;
	public:
		Class* classForName(const std::string& name) const;

		void addClass(Class* clazz);

		static ClassRepository& getInstance() {
			static ClassRepository instance;
			return instance;
		}
	};
}