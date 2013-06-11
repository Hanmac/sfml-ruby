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


#ifdef HAVE_RUBY_ENCODING_H
#include <ruby/encoding.h>
#endif


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




#define macro_attr(attr,type) macro_attr_func(attr,Get##attr(),Set##attr,wrap,unwrap<type>)
#define macro_attr_enum(attr,type) macro_attr_func(attr,Get##attr(),Set##attr,wrapenum<type>,unwrapenum<type>)
#define macro_attr_with_func(attr,getf,setf) macro_attr_func(attr,Get##attr(),Set##attr,getf,setf)

//*/
#define macro_attr_prop(attr,type) macro_attr_func(_##attr,attr,attr = ,wrap,unwrap<type>)
#define macro_attr_prop_enum(attr,type) macro_attr_func(_##attr,attr,attr = ,wrapenum<type>,unwrapenum<type>)
#define macro_attr_prop_with_func(attr,getf,setf) macro_attr_func(_##attr,attr,attr = ,getf,setf)


DLL_LOCAL void rb_define_attr_method(VALUE klass,std::string name,VALUE(get)(VALUE),VALUE(set)(VALUE,VALUE));


#endif /* MAIN_HPP_ */
