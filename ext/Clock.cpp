/*
 * Clock.cpp
 *
 *  Created on: 28.06.2013
 *      Author: hanmac
 */

#include "Clock.hpp"

#define _self unwrap<sf::Clock*>(self)

VALUE rb_cSFMLClock;

template <>
VALUE wrap< sf::Clock >(sf::Clock *clock )
{
	return Data_Wrap_Struct(rb_cSFMLClock, NULL, NULL, clock);
}

template <>
sf::Clock* unwrap< sf::Clock* >(const VALUE &vclock)
{
	return unwrapPtr<sf::Clock>(vclock, rb_cSFMLClock);
}

template <>
sf::Clock& unwrap< sf::Clock& >(const VALUE &vclock)
{
	return *unwrap<sf::Clock*>(vclock);
}


namespace RubySFML {
namespace Clock {
VALUE _alloc(VALUE self) {
	return wrap(new sf::Clock);
}

VALUE _getElapsedTime(VALUE self)
{

	return wrap(_self->getElapsedTime());
}

VALUE _restart(VALUE self)
{
	_self->restart();
	return self;
}
}
}

void Init_SFMLClock(VALUE rb_mSFML)
{
	using namespace RubySFML::Clock;

#if 0
	rb_mSFML = rb_define_module("SFML");
#endif

	rb_cSFMLClock = rb_define_class_under(rb_mSFML,"Clock",rb_cObject);
	rb_define_alloc_func(rb_cSFMLClock,_alloc);

	rb_undef_method(rb_cSFMLClock,"_load");

	rb_define_method(rb_cSFMLClock,"time",RUBY_METHOD_FUNC(_getElapsedTime),0);
	rb_define_method(rb_cSFMLClock,"restart",RUBY_METHOD_FUNC(_restart),0);

}


