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

#include "extconf.h"

#ifdef HAVE_SFML_AUDIO_HPP
#include <SFML/Audio.hpp>
#endif

#include <typeinfo>
#include <map>


#ifdef HAVE_RUBY_ENCODING_H
#include <ruby/encoding.h>
#endif


#ifndef RARRAY_AREF
#ifdef RARRAY_CONST_PTR
#define RARRAY_AREF(a,i) RARRAY_CONST_PTR(a)[i]
#else
#define RARRAY_AREF(a,i) RARRAY_PTR(a)[i]
#endif

#endif

#ifndef RETURN_SIZED_ENUMERATOR
#define RETURN_SIZED_ENUMERATOR(obj, argc, argv,size_fn) RETURN_ENUMERATOR(obj, argc, argv)
#endif

#define CHECK_SFML_VERSION(mayor,minor) \
  SFML_VERSION_MAJOR > mayor || mayor == SFML_VERSION_MAJOR && SFML_VERSION_MINOR >= minor

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
	enumtype* add(int enumo,const std::string& sym)
	{
		values.insert(std::make_pair(enumo,rb_intern(sym.c_str())));
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
	return rb_str_new2(typeid(*arg).name());
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

VALUE wrapenum(const int &arg, const std::string& name);


template <typename T>
VALUE wrapenum(const T &arg){
	return wrapenum(arg,typeid(T).name());
}

template <typename T>
VALUE wrapenum(int arg){
	return wrapenum((T)arg);
}

int unwrapenum(const VALUE &arg, const std::string& name);

template <typename T>
T unwrapenum(const VALUE &arg){
	return (T)unwrapenum(arg,typeid(T).name());
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

template <>
std::size_t unwrap< std::size_t >(const VALUE &val );
template <>
VALUE wrap< std::size_t >(const std::size_t &st );


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

template <>
std::vector<std::string> unwrap< std::vector<std::string> >(const VALUE &val );


#define macro_attr_func(attr,funcget,funcset,wrapget,wrapset) \
DLL_LOCAL VALUE _get##attr(VALUE self)\
{ \
	return wrapget(_self->funcget);\
}\
\
DLL_LOCAL VALUE _set##attr(VALUE self,VALUE other)\
{\
	rb_check_frozen(self);\
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


#define singlefunc(func) \
DLL_LOCAL VALUE _##func(VALUE self)\
{\
	rb_check_frozen(self);\
	_self->func();\
	return self;\
}


#define singlereturn(func) \
DLL_LOCAL VALUE _##func(VALUE self)\
{\
	return wrap(_self->func());\
}
#define macro_alloc(T) \
DLL_LOCAL VALUE _alloc(VALUE self) {\
	return wrap(new T);\
}

DLL_LOCAL void rb_define_attr_method(VALUE klass,std::string name,VALUE(get)(VALUE),VALUE(set)(VALUE,VALUE));
DLL_LOCAL void setOption(VALUE self,VALUE hash, VALUE func(VALUE,VALUE), const char* attr );


template <typename T>
DLL_LOCAL bool set_hash_option(VALUE hash,const char* name,T& val,T func(const VALUE&) = unwrap<T> )
{
	VALUE temp;
	if(!NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern(name)))))
	{
		val = func(temp);
		return true;
	}
	return false;

}


template <typename T,typename C>
DLL_LOCAL bool set_hash_option(C* self, VALUE hash,const char* name,void (C::*set)(T),T func(const VALUE&) = unwrap<T> )
{
	VALUE temp;
	if(!NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern(name)))))
	{
		((*self).*(set))(func(temp));
		return true;
	}
	return false;

}

DLL_LOCAL bool setOptionFlag(VALUE hash, const char* name, int& val, const int& flag);

DLL_LOCAL bool check_index(int &cidx,const std::size_t &count);


#define macro_template(T,f,c) \
template <>\
VALUE wrap< T >(T *obj )\
{\
	return Data_Wrap_Struct(c, NULL, f, obj);\
}\
template <>\
T* unwrap< T* >(const VALUE &vobj)\
{\
	return unwrapPtr<T>(vobj, c);\
}

#define macro_template2(T,f,c) \
macro_template(T,f,c)\
template <>\
T& unwrap< T& >(const VALUE &vobj)\
{\
	return *unwrap<T*>(vobj);\
}



#endif /* MAIN_HPP_ */
