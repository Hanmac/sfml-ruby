/*
 * Mouse.cpp
 *
 *  Created on: 27.06.2013
 *      Author: hanmac
 */


#include "Mouse.hpp"

#define _self sf::Mouse

VALUE rb_mSFMLMouse;


namespace RubySFML {
namespace Mouse {

VALUE _getPosition(VALUE self)
{
	return wrap(_self::getPosition());
}

VALUE _setPosition(VALUE self,VALUE val)
{
	_self::setPosition(unwrap<sf::Vector2i>(val));
	return val;
}

}
}

void Init_SFMLMouse(VALUE rb_mSFML)
{
	using namespace RubySFML::Mouse;

#if 0
	rb_mSFML = rb_define_module("SFML");

#endif


	rb_mSFMLMouse = rb_define_module_under(rb_mSFML,"Mouse");

	rb_define_module_function(rb_mSFMLMouse,"position",RUBY_METHOD_FUNC(_getPosition),0);
	rb_define_module_function(rb_mSFMLMouse,"position=",RUBY_METHOD_FUNC(_setPosition),1);

}




