/*
 * RenderWindow.cpp
 *
 *  Created on: 16.06.2013
 *      Author: hanmac
 */

#include "RenderTarget.hpp"
#include "Window.hpp"
#include "RenderWindow.hpp"

#define _self unwrap<sf::RenderWindow*>(self)

VALUE rb_cSFMLRenderWindow;

template <>
VALUE wrap< sf::RenderWindow >(sf::RenderWindow *image )
{
	return Data_Wrap_Struct(rb_cSFMLRenderWindow, NULL, NULL, image);
}

template <>
sf::RenderWindow* unwrap< sf::RenderWindow* >(const VALUE &vimage)
{
	return unwrapPtr<sf::RenderWindow>(vimage, rb_cSFMLRenderWindow);
}

namespace RubySFML {
namespace RenderWindow {

VALUE _alloc(VALUE self) {
	return wrap(new sf::RenderWindow);
}

}
}

void Init_SFMLRenderWindow(VALUE rb_mSFML)
{
	using namespace RubySFML::RenderWindow;

	rb_cSFMLRenderWindow = rb_define_class_under(rb_mSFML,"RenderWindow",rb_cSFMLWindow);
	rb_include_module(rb_cSFMLRenderWindow,rb_mSFMLRenderTarget);
	rb_define_alloc_func(rb_cSFMLRenderWindow,_alloc);

}




