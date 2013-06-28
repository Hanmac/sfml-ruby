/*
 * Window.cpp
 *
 *  Created on: 15.06.2013
 *      Author: hanmac
 */

#include "Image.hpp"
#include "Window.hpp"
#include "Vector2.hpp"
#include "VideoMode.hpp"
#include "Event.hpp"

#define _self unwrap<sf::Window*>(self)

VALUE rb_cSFMLWindow;

template<>
VALUE wrap<sf::Window>(sf::Window *image) {
	return Data_Wrap_Struct(rb_cSFMLWindow, NULL, NULL, image);
}

template<>
sf::Window* unwrap<sf::Window*>(const VALUE &vimage) {
	return unwrapPtr<sf::Window>(vimage, rb_cSFMLWindow);
}

template<>
sf::Window& unwrap<sf::Window&>(const VALUE &vimage) {
	return *unwrap<sf::Window*>(vimage);
}

namespace RubySFML {
namespace Window {
VALUE _alloc(VALUE self) {
	return wrap(new sf::Window);
}

macro_attr(Position, sf::Vector2i)
macro_attr(Size, sf::Vector2u)

VALUE _getMousePosition(VALUE self)
{
	return wrap(sf::Mouse::getPosition(*_self));
}

VALUE _setMousePosition(VALUE self,VALUE val)
{
	sf::Mouse::setPosition(unwrap<sf::Vector2i>(val),*_self);
	return val;
}


VALUE _display(VALUE self) {
	_self->display();
	return self;
}

VALUE _close(VALUE self) {
	_self->close();
	return Qnil;
}

VALUE _isOpen(VALUE self) {
	return wrap(_self->isOpen());
}

/*
 * call-seq:
 *   Window.new(red,green,blue[,alpha])
 *
 * creates a new Window Object.
 */
VALUE _initialize(int argc, VALUE *argv, VALUE self) {
	VALUE title, mode, hash, temp;
	rb_scan_args(argc, argv, "12", &title, &mode, &hash);

	if (rb_obj_is_kind_of(mode, rb_cHash))
		std::swap(hash, mode);

	int style = sf::Style::Default;

	if (rb_obj_is_kind_of(hash, rb_cHash)) {
		if (RTEST(rb_hash_aref(hash,ID2SYM(rb_intern("fullscreen"))))) {
			style |= sf::Style::Fullscreen;
		}
		if (!RTEST(rb_hash_lookup2(hash,ID2SYM(rb_intern("titlebar")),Qtrue))) {
			style = sf::Style::None;
		}
		if (!RTEST(rb_hash_lookup2(hash,ID2SYM(rb_intern("resize")),Qtrue))) {
			style &= ~sf::Style::Resize;
		}
		if (!RTEST(rb_hash_lookup2(hash,ID2SYM(rb_intern("close")),Qtrue))) {
			style &= ~sf::Style::Close;
		}
	}

	sf::VideoMode sfmode = unwrap<sf::VideoMode>(mode);

	if ((style & sf::Style::Fullscreen) && !sfmode.isValid())
		sfmode = sf::VideoMode::getDesktopMode();

	_self->create(sfmode,unwrap<std::string>(title),style);

	return self;
}

VALUE _pollEvent(VALUE self) {
	sf::Event event;

	if (rb_block_given_p()) {
		while(_self->pollEvent(event))
		{
			rb_yield(wrap(event));
		}
	} else if (_self->pollEvent(event)) {
		return wrap(event);
	}

	return Qnil;
}

VALUE _waitEvent(VALUE self) {
	sf::Event event;

	if (_self->waitEvent(event)) {
		return wrap(event);
	}

	return Qnil;
}

}
}

void Init_SFMLWindow(VALUE rb_mSFML) {
	using namespace RubySFML::Window;

#if 0
	rb_mSFML = rb_define_module("SFML");
#endif

	rb_cSFMLWindow = rb_define_class_under(rb_mSFML, "Window", rb_cObject);
	rb_define_alloc_func(rb_cSFMLWindow, _alloc);

	rb_define_method(rb_cSFMLWindow, "initialize",
	RUBY_METHOD_FUNC(_initialize), -1);
	rb_undef_method(rb_cSFMLWindow, "initialize_copy");
	rb_undef_method(rb_cSFMLWindow, "_load");

	rb_define_attr_method(rb_cSFMLWindow, "position", _getPosition,
			_setPosition);
	rb_define_attr_method(rb_cSFMLWindow, "mouse_position", _getMousePosition,
				_setMousePosition);
	rb_define_attr_method(rb_cSFMLWindow, "size", _getSize, _setSize);

	rb_define_method(rb_cSFMLWindow, "display", RUBY_METHOD_FUNC(_display), 0);
	rb_define_method(rb_cSFMLWindow, "close", RUBY_METHOD_FUNC(_close), 0);
	rb_define_method(rb_cSFMLWindow, "open?", RUBY_METHOD_FUNC(_isOpen), 0);

	rb_define_method(rb_cSFMLWindow, "poll_event", RUBY_METHOD_FUNC(_pollEvent),
			0);
	rb_define_method(rb_cSFMLWindow, "wait_event", RUBY_METHOD_FUNC(_waitEvent),
			0);

}

