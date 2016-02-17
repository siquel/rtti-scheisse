#pragma once
#include "class.h"
#include "descriptor.h"
#include "class_repo.h"
#include <cassert>

namespace rtti {

	template <class T>
	inline rtti::RTTIType* RTTITypeOf(T&) {

	}
	template <>
	inline rtti::RTTIType* RTTITypeOf(int&) { return &RTTIType::IntType; }

	template <class R, class C, class P0>
	class RTTIFuncType1 : public RTTIFunc {
	public:
		typedef R(C::*FuncPointer)(P0);
		FuncPointer f;
		RTTIFuncType1(FuncPointer f) : f(f) {
			
		}

		void invoke(void* ret, void* obj, void* params[]) {
			int a = 5;
			(((C*)obj)->*f)(*(P0*)&a);
		}
	};

	template <class R, class C>
	inline void* RTTIFuncTypeOf(R(C::*f)()) {

	}
	
	template <class R, class C, class P0>
	inline RTTIFunc* RTTIFuncTypeOf(R(C::*f)(P0)) {
		return new RTTIFuncType1<R, C, P0>(f);
	}
}

#define DEFINE_CLASS(p_class)\
	public:\
	using ThisClass = p_class;\
	rtti::Class* p_class::getTypeinfo();


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


#define RTTI_FIELD(p_x, p_flags)\
	*new rtti::RTTIFieldDescriptor(#p_x, (char*)&p_x-(char*)this, sizeof(p_x), p_flags, rtti::RTTITypeOf(p_x))

/*#define RTTI_CONSTRUCTOR(p_class, p_signature, p_flags) \
	*new rtti::RTTIFuncDescriptor(#p_class #p_signature, p_flags, rtti::RTTIFuncTypeOf((p_class*(p_class##Factory::*)p_signature)&p_class##Factory::create))*/

#define RTTI_DESCRIBE_CLASS(p_class, p_fields)\
	DEFINE_CLASS(p_class)\
	rtti::RTTIFieldDescriptor* getRTTIFields() { return &p_fields; }\
	


#define RTTI_NO_FIELDS  (*(rtti::RTTIFieldDescriptor*)0)

#define RTTI_REGISTER_CLASS(p_class)\
	static void* createInstance() { return new p_class; }\
	static rtti::RTTIFieldDescriptor* describeRTTIFieldsOf##p_class() {\
		return p_class().getRTTIFields();\
	}\
	static rtti::Class p_class##Typeinfo(#p_class, sizeof(p_class), \
					&describeRTTIFieldsOf##p_class, \
					&createInstance); \
	rtti::Class* p_class::getTypeinfo() { return &p_class##Typeinfo; }\
	//static p_class##::p_class##Factory init##p_class##Factory(&p_class##Typeinfo);