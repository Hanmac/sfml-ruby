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

VALUE _to_f(VALUE self)
{

	return wrap(_self->asSeconds());
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

	//rb_undef_method(rb_cSFMLTime,"_load");

	rb_define_method(rb_cSFMLTime,"to_f",RUBY_METHOD_FUNC(_to_f),0);

#endif

}





