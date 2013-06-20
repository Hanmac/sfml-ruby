/*
 * main.hpp
 *
 *  Created on: 09.06.2013
 *      Author: hanmac
 */

#ifndef MAIN_HPP_
#define MAIN_HPP_

#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_DLL
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllexport))
    #else
      #define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllimport))
    #else
      #define DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define DLL_PUBLIC __attribute__ ((visibility ("default")))
    #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define DLL_PUBLIC
    #define DLL_LOCAL
  #endif
#endif

#include <ruby.h>
#include <SFML/Graphics.hpp>

#include <typeinfo>
#include <map>

#include "extconf.h"

#ifdef HAVE_RUBY_ENCODING_H
#include <ruby/encoding.h>
#endif


struct enumtype
{
	std::string name;
	typedef std::map<int,ID> value_type;
	value_type values;

	int defaults;

	enumtype* add(int enumo,const char* sym)
	{
		values.insert(std::make_pair(enumo,rb_intern(sym)));
		return this;
	}
};
//typedef std::map<int,ID > enumtype;
typedef std::map<std::string,enumtype* > enumregistertype;

extern enumregistertype enumregister;


template <typename T>
enumtype* registerEnum(const char* name,int def = 0)
{
	enumtype *type = new enumtype;
	enumregister.insert(std::make_pair(std::string(typeid(T).name()),type));
	type->name = std::string(name);
	type->defaults = def;
	return type;
}




template <typename T>
VALUE wrap(T *arg)
{
	return Qnil;
}


template <class T>
VALUE wrap(const T &arg){
	return wrap(new T(arg));
};

template <typename T>
bool is_wrapable(const VALUE &arg);

template <typename T>
T* unwrapPtr(const VALUE &obj,const VALUE &klass)
{
	if(NIL_P(obj))
		return NULL;

	if(rb_obj_is_instance_of(obj,rb_cClass) && rb_class_inherited(obj,klass)) {
		return unwrapPtr<T>(rb_class_new_instance(0,NULL,obj),klass);
	}else if (rb_obj_is_kind_of(obj, klass)){
		T *temp;
		Data_Get_Struct( obj, T, temp);
		return temp;
	}else{
		rb_raise(rb_eTypeError,
			"Expected %s got %s!",
			rb_class2name(klass),
			rb_obj_classname(obj)
		);
		return NULL;
	}

}

template <typename T>
T unwrap(const VALUE &arg)
{
}


template <typename T>
VALUE wrapenum(const T &arg){
	enumtype::value_type &enummap = enumregister[std::string(typeid(T).name())]->values;
	enumtype::value_type::iterator it = enummap.find((int)arg);
	if(it != enummap.end())
		return ID2SYM(it->second);
	return Qnil;
}
template <typename T>
VALUE wrapenum(int arg){
	return wrapenum((T)arg);
}

template <typename T>
T unwrapenum(const VALUE &arg){
	enumregistertype::iterator it = enumregister.find(typeid(T).name());
	if(it != enumregister.end())
	{
		if(NIL_P(arg))
			return (T)it->second->defaults;
		else if(SYMBOL_P(arg))
		{
			ID id = SYM2ID(arg);

			for(enumtype::value_type::iterator it2 = it->second->values.begin();
					it2 != it->second->values.end();
					++it2)
			{
				if(it2->second == id)
					return (T)it2->first;
			}
			rb_raise(rb_eTypeError,"%s is not a %s-Enum.",rb_id2name(id),it->second->name.c_str());
		}else if(rb_obj_is_kind_of(arg,rb_cArray))
		{
			int result = 0;
			size_t count = RARRAY_LEN(arg);
			for(size_t i = 0; i < count; ++i)
				result = result || unwrapenum<T>(RARRAY_PTR(arg)[i]);
		}else
			return (T)NUM2INT(arg);
	}
	return (T)0;
}



template <>
bool unwrap< bool >(const VALUE &val );
template <>
VALUE wrap< bool >(const bool &st );
template <>

int unwrap< int >(const VALUE &val );
template <>
VALUE wrap< int >(const int &st );

template <>
unsigned int unwrap< unsigned int >(const VALUE &val );
template <>
VALUE wrap< unsigned int >(const unsigned int &st );

template <>
sf::Uint8 unwrap< sf::Uint8 >(const VALUE &val );
template <>
VALUE wrap< sf::Uint8 >(const sf::Uint8 &st );

template <>
float unwrap< float >(const VALUE &val );
template <>
VALUE wrap< float >(const float &st );

#ifdef HAVE_TYPE_SF_STRING

template <>
VALUE wrap< sf::String >(const sf::String &st );

#endif

template <>
VALUE wrap< std::string >(const std::string &st );

template <>
char* unwrap< char* >(const VALUE &val );

#ifdef HAVE_TYPE_SF_STRING
template <>
sf::String unwrap< sf::String >(const VALUE &val );
#endif

template <>
std::string unwrap< std::string >(const VALUE &val );


#define macro_attr_func(attr,funcget,funcset,wrapget,wrapset) \
DLL_LOCAL VALUE _get##attr(VALUE self)\
{ \
	return wrapget(_self->funcget);\
}\
\
DLL_LOCAL VALUE _set##attr(VALUE self,VALUE other)\
{\
	_self->funcset(wrapset(other));\
	return other;\
}




#define macro_attr(attr,type) macro_attr_func(attr,get##attr(),set##attr,wrap,unwrap<type>)
#define macro_attr_enum(attr,type) macro_attr_func(attr,get##attr(),set##attr,wrapenum<type>,unwrapenum<type>)
#define macro_attr_with_func(attr,getf,setf) macro_attr_func(attr,get##attr(),set##attr,getf,setf)

//*/
#define macro_attr_prop(attr,type) macro_attr_func(_##attr,attr,attr = ,wrap,unwrap<type>)
#define macro_attr_prop_enum(attr,type) macro_attr_func(_##attr,attr,attr = ,wrapenum<type>,unwrapenum<type>)
#define macro_attr_prop_with_func(attr,getf,setf) macro_attr_func(_##attr,attr,attr = ,getf,setf)


#define macro_attr_bool(attr) macro_attr_func(attr,is##attr(),set##attr,wrap,unwrap<bool>)

DLL_LOCAL void rb_define_attr_method(VALUE klass,std::string name,VALUE(get)(VALUE),VALUE(set)(VALUE,VALUE));


#endif /* MAIN_HPP_ */
