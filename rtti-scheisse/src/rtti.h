#pragma once
#include "class.h"
#define DEFINE_CLASS(p_class)\
	public:\
	using ThisClass = p_class;\
	rtti::Class* p_class::getTypeinfo();\
	static rtti::Class* p_class::getTypeinfoStatic();

#define CREATE_TYPEINFO_BASECLASS(p_class)\
	rtti::Class p_class##Typeinfo(#p_class, nullptr, sizeof(p_class));

#define CREATE_TYPEINFO_CLASS(p_class, p_base)\
	rtti::Class p_class##Typeinfo(#p_class, p_base::getTypeinfoStatic(), sizeof(p_class));


#define __DECLARE_TYPE_INFO_FUNCTIONS__(p_class)\
	rtti::Class* p_class##::getTypeinfo() { return &p_class##Typeinfo; }\
	rtti::Class* p_class##::getTypeinfoStatic() { return &p_class##Typeinfo; }

#define DECLARE_TYPEINFO_BASECLASS(p_class)\
	CREATE_TYPEINFO_BASECLASS(p_class)\
	__DECLARE_TYPE_INFO_FUNCTIONS__(p_class)

#define DECLARE_TYPEINFO_CLASS(p_class, p_base)\
	CREATE_TYPEINFO_CLASS(p_class, p_base)\
	__DECLARE_TYPE_INFO_FUNCTIONS__(p_class)

#define __DECLARE_GETTER__(p_type, p_name, p_upper)\
	const p_type& get##p_upper() const { return p_name; }

#define __DECLARE_SETTER__(p_type, p_name, p_upper)\
	void set##p_upper(const p_type &v) { p_name = v; }

#define DECLARE_PROPERTY(p_type, p_name, p_upper)\
	private:\
		p_type p_name;\
	public:\
	__DECLARE_GETTER__(p_type, p_name, p_upper) \
	__DECLARE_SETTER__(p_type, p_name, p_upper)\

