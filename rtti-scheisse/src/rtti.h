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
	