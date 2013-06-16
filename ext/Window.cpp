/*
 * Window.cpp
 *
 *  Created on: 15.06.2013
 *      Author: hanmac
 */


#include "Image.hpp"
#include "Window.hpp"
#include "Vector2.hpp"
#include "Event.hpp"

#define _self unwrap<sf::Window*>(self)

VALUE rb_cSFMLWindow;

template <>
VALUE wrap< sf::Window >(sf::Window *image )
{
	return Data_Wrap_Struct(rb_cSFMLWindow, NULL, NULL, image);
}

template <>
sf::Window* unwrap< sf::Window* >(const VALUE &vimage)
{
	return unwrapPtr<sf::Window>(vimage, rb_cSFMLWindow);
}

template <>
sf::Window& unwrap< sf::Window& >(const VALUE &vimage)
{
	return *unwrap<sf::Window*>(vimage);
}


namespace RubySFML {
namespace Window {
VALUE _alloc(VALUE self) {
	return wrap(new sf::Window);
}

macro_attr(Position,sf::Vector2i)
macro_attr(Size,sf::Vector2u)

VALUE _display(VALUE self)
{
	_self->display();
	return self;
}

VALUE _close(VALUE self)
{
	_self->close();
	return Qnil;
}

VALUE _isOpen(VALUE self)
{
	return wrap(_self->isOpen());
}

/*
 * call-seq:
 *   Window.new(red,green,blue[,alpha])
 *
 * creates a new Window Object.
*/
VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE title;
	rb_scan_args(argc, argv, "10",&title);

	_self->create(sf::VideoMode::getDesktopMode(),unwrap<std::string>(title));

	return self;
}

VALUE _pollEvent(VALUE self)
{
	sf::Event event;
	if(_self->pollEvent(event))
		return wrap(event);
	return Qnil;
}


VALUE _waitEvent(VALUE self)
{
	sf::Event event;
	if(_self->waitEvent(event))
		return wrap(event);
	return Qnil;
}

}
}

void Init_SFMLWindow(VALUE rb_mSFML)
{
	using namespace RubySFML::Window;


	rb_cSFMLWindow = rb_define_class_under(rb_mSFML,"Window",rb_cObject);
	rb_define_alloc_func(rb_cSFMLWindow,_alloc);

	rb_define_method(rb_cSFMLWindow,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_undef_method(rb_cSFMLWindow,"initialize_copy");
	rb_undef_method(rb_cSFMLWindow,"_load");

	rb_define_attr_method(rb_cSFMLWindow,"position",_getPosition,_setPosition);
	rb_define_attr_method(rb_cSFMLWindow,"size",_getSize,_setSize);

	rb_define_method(rb_cSFMLWindow,"display",RUBY_METHOD_FUNC(_display),0);
	rb_define_method(rb_cSFMLWindow,"close",RUBY_METHOD_FUNC(_close),0);
	rb_define_method(rb_cSFMLWindow,"open?",RUBY_METHOD_FUNC(_isOpen),0);

	rb_define_method(rb_cSFMLWindow,"poll_event",RUBY_METHOD_FUNC(_pollEvent),0);
	rb_define_method(rb_cSFMLWindow,"wait_event",RUBY_METHOD_FUNC(_waitEvent),0);

}




