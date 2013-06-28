/*
 * main.cpp
 *
 *  Created on: 09.06.2013
 *      Author: hanmac
 */

#include "main.hpp"

#include <string>

enumregistertype enumregister;


template <>
bool unwrap< bool >(const VALUE &val )
{
	return RTEST(val);
}

template <>
VALUE wrap< bool >(const bool &st )
{
	return st ? Qtrue : Qfalse;
}

template <>
int unwrap< int >(const VALUE &val )
{
	return NUM2INT(val);
}

template <>
VALUE wrap< int >(const int &st )
{
	return INT2NUM(st);
}

template <>
unsigned int unwrap< unsigned int >(const VALUE &val )
{
	return NUM2UINT(val);
}

template <>
VALUE wrap< unsigned int >(const unsigned int &st )
{
	return UINT2NUM(st);
}

template <>
std::size_t unwrap< std::size_t >(const VALUE &val )
{
	return NUM2UINT(val);
}

template <>
VALUE wrap< std::size_t >(const std::size_t &st )
{
	return UINT2NUM(st);
}


template <>
sf::Uint8 unwrap< sf::Uint8 >(const VALUE &val )
{
	return NUM2UINT(val);
}

template <>
VALUE wrap< sf::Uint8 >(const sf::Uint8 &st )
{
	return UINT2NUM(st);
}



template <>
float unwrap< float >(const VALUE &val )
{
	return NUM2DBL(val);
}

template <>
VALUE wrap< float >(const float &st )
{
	return DBL2NUM(st);
}

#ifdef HAVE_TYPE_SF_STRING

template <>
VALUE wrap< sf::String >(const sf::String &cstr )
{

	std::string str(cstr.begin(),cstr.end());
#ifdef HAVE_RUBY_ENCODING_H
	return rb_enc_str_new(str.c_str(),strlen(str.c_str()),rb_utf8_encoding());
#else
	return rb_str_new2(str.c_str());
#endif
}

#endif

template <>
VALUE wrap< std::string >(const std::string &st )
{
#ifdef HAVE_RUBY_ENCODING_H
	return rb_enc_str_new(st.c_str(),strlen(st.c_str()),rb_utf8_encoding());
#else
	return rb_str_new2(st.c_str());
#endif
}

template <>
char* unwrap< char* >(const VALUE &val )
{
	if(NIL_P(val))
		return NULL;
	if (rb_obj_is_kind_of(val, rb_cString)){
		return RSTRING_PTR(val);
	}
	else
		return unwrap< char* >(rb_funcall(val,rb_intern("to_s"),0));
}

#ifdef HAVE_TYPE_SF_STRING
template <>
sf::String unwrap< sf::String >(const VALUE &val )
{
	if(NIL_P(val))
		return sf::String();
	else
		return sf::String(unwrap< char* >(val));
}
#endif

template <>
std::string unwrap< std::string >(const VALUE &val )
{
	if(NIL_P(val))
		return std::string();
	else
		return std::string(unwrap< char* >(val));
}
