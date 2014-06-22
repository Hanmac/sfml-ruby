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


template <>
std::vector<std::string> unwrap< std::vector<std::string> >(const VALUE &val )
{
	std::vector<std::string> vec;
	VALUE temp(rb_Array(val));
	std::size_t count = RARRAY_LEN(temp);
	for(std::size_t i = 0; i != count; ++i)
	{
		vec.push_back(unwrap<std::string>(RARRAY_AREF(temp,i)));
	}

	return vec;
}

VALUE wrapenum(const int &arg, const std::string& name)
{
	enumtype::value_type &enummap = enumregister[name]->values;
	enumtype::value_type::iterator it = enummap.find(arg);
	if(it != enummap.end())
		return ID2SYM(it->second);
	bool found = false;

	int carg(arg);

	VALUE result = rb_ary_new();
	for(it = enummap.begin();it != enummap.end();++it)
	{
		if((carg & it->first) != 0)
		{
			found = true;
			rb_ary_push(result,ID2SYM(it->second));
			carg &= ~it->first;
		}
	}
	return found ? result : Qnil;
}

int unwrapenum(const VALUE &arg, const std::string& name)
{
	enumregistertype::iterator it = enumregister.find(name);
	if(it != enumregister.end())
	{
		enumtype* etype = it->second;
		if(NIL_P(arg))
			return etype->defaults;
		else if(SYMBOL_P(arg))
		{
			ID id(SYM2ID(arg));

			for(enumtype::value_type::iterator it2 = etype->values.begin();
					it2 != etype->values.end();
					++it2)
			{
				if(it2->second == id)
					return it2->first;
			}
			rb_raise(rb_eTypeError,"%s is not a %s-Enum.",rb_id2name(id),etype->name.c_str());
		}else if(rb_obj_is_kind_of(arg,rb_cArray) )
		{
			int result = 0;
			size_t count = RARRAY_LEN(arg);
			for(size_t i = 0; i < count; ++i)
				result = result | unwrapenum(RARRAY_AREF(arg,i),name);
		}else
			return NUM2INT(arg);
	}
	return 0;
}

void setOption(VALUE self,VALUE hash, VALUE func(VALUE,VALUE), const char* attr )
{
	VALUE temp;
	if(!NIL_P(temp = rb_hash_aref(hash,ID2SYM(rb_intern(attr)))))
		func(self,temp);
}

bool setOptionFlag(VALUE hash, const char* name, int& val, const int& flag)
{
	VALUE temp;
	if(!NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern(name)))))
	{
		if(RTEST(temp))
			val |= flag;
		else
			val &= ~flag;

		return true;
	}
	return false;
}

bool check_index(int &cidx,const std::size_t &count)
{
	bool raise = false;
	if(cidx >= (int)count){
		raise = true;
	}else if(cidx < 0)
	{
		int tmp = cidx + count;
		if(tmp > 0 && tmp <= (int)count)
			cidx = tmp;
		else
			raise = true;
	}

	if(raise)
		rb_raise(rb_eIndexError,"%d out of index",cidx);
	return !raise;
}
