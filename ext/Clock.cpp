/*
 * Clock.cpp
 *
 *  Created on: 28.06.2013
 *      Author: hanmac
 */

#include "Clock.hpp"

#define _self unwrap<sf::Clock*>(self)

VALUE rb_cSFMLClock;

macro_template2(sf::Clock,NULL,rb_cSFMLClock)


namespace RubySFML {
namespace Clock {

macro_alloc(sf::Clock)

singlereturn(getElapsedTime)
singlereturn(restart)

VALUE _measure(VALUE self)
{
	sf::Clock cl;
	rb_yield(Qnil);
	return wrap(cl.getElapsedTime());
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

	rb_define_singleton_method(rb_cSFMLClock,"measure",RUBY_METHOD_FUNC(_measure),0);

}


