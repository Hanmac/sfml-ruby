/*
 * Time.cpp
 *
 *  Created on: 28.06.2013
 *      Author: hanmac
 */


#include "Time.hpp"

#ifdef HAVE_TYPE_SF_TIME
#define _self unwrap<sf::Time*>(self)
#endif
VALUE rb_cSFMLTime;

#ifdef HAVE_TYPE_SF_TIME
template <>
VALUE wrap< sf::Time >(sf::Time *clock )
{
	return Data_Wrap_Struct(rb_cSFMLTime, NULL, free, clock);
}

template <>
sf::Time* unwrap< sf::Time* >(const VALUE &vclock)
{
	return unwrapPtr<sf::Time>(vclock, rb_cSFMLTime);
}

template <>
sf::Time& unwrap< sf::Time& >(const VALUE &vclock)
{
	return *unwrap<sf::Time*>(vclock);
}
#endif

#ifdef HAVE_TYPE_SF_TIME

namespace RubySFML {
namespace Time {
VALUE _alloc(VALUE self) {
	return wrap(new sf::Time);
}

VALUE _make_seconds(VALUE self,VALUE val)
{
	return wrap(sf::seconds(NUM2DBL(val)));
}

VALUE _make_milliseconds(VALUE self,VALUE val)
{
	return wrap(sf::milliseconds(NUM2INT(val)));
}

VALUE _make_microseconds(VALUE self,VALUE val)
{
	return wrap(sf::microseconds(NUM2INT(val)));
}


VALUE _to_f(VALUE self)
{

	return wrap(_self->asSeconds());
}

VALUE _compare(VALUE self, VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cSFMLTime))
	{
		sf::Time &cother = unwrap<sf::Time&>(other);
		return INT2FIX(*_self > cother ? 1 : *_self < cother ? -1 : 0);
	}
	return Qnil;

}


VALUE _plus(VALUE self,VALUE other)
{
	return wrap(*_self + unwrap<sf::Time&>(other));
}

VALUE _minus(VALUE self,VALUE other)
{
	return wrap(*_self - unwrap<sf::Time&>(other));
}

VALUE _mal(VALUE self,VALUE other)
{
	return wrap(*_self * (float)NUM2DBL(other));
}

VALUE _durch(VALUE self,VALUE other)
{
	return wrap(*_self / (float)NUM2DBL(other));
}


}
}

#endif

void Init_SFMLTime(VALUE rb_mSFML)
{
#ifdef HAVE_TYPE_SF_TIME
	using namespace RubySFML::Time;

#if 0
	rb_mSFML = rb_define_module("SFML");
#endif

	rb_cSFMLTime = rb_define_class_under(rb_mSFML,"Time",rb_cObject);
	rb_define_alloc_func(rb_cSFMLTime,_alloc);

	rb_include_module(rb_cSFMLTime,rb_mComparable);
	//rb_undef_method(rb_cSFMLTime,"_load");

	rb_define_singleton_method(rb_cSFMLTime,"seconds",RUBY_METHOD_FUNC(_make_seconds),1);
	rb_define_singleton_method(rb_cSFMLTime,"milliseconds",RUBY_METHOD_FUNC(_make_milliseconds),1);
	rb_define_singleton_method(rb_cSFMLTime,"microseconds",RUBY_METHOD_FUNC(_make_macroseconds),1);

	rb_define_method(rb_cSFMLTime,"to_f",RUBY_METHOD_FUNC(_to_f),0);

	rb_define_method(rb_cSFMLTime,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cSFMLTime,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cSFMLTime,"*",RUBY_METHOD_FUNC(_mal),1);
	rb_define_method(rb_cSFMLTime,"/",RUBY_METHOD_FUNC(_durch),1);

	rb_define_method(rb_cSFMLTime,"<=>",RUBY_METHOD_FUNC(_compare),1);
#endif

}





