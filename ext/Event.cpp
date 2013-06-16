/*
 * Event.cpp
 *
 *  Created on: 16.06.2013
 *      Author: hanmac
 */

#include "Event.hpp"

#define _self unwrap<sf::Event*>(self)

VALUE rb_cSFMLEvent, rb_cSFMLSizeEvent, rb_cSFMLMouseMoveEvent,
		rb_cSFMLMouseWheelEvent;

template<>
VALUE wrap<sf::Event>(sf::Event *image) {
	VALUE klass = rb_cSFMLEvent;

	switch (image->type) {
	case sf::Event::Resized:
		klass = rb_cSFMLSizeEvent;
		break;
	case sf::Event::MouseMoved:
		klass = rb_cSFMLMouseMoveEvent;
		break;
	case sf::Event::MouseWheelMoved:
		klass = rb_cSFMLMouseWheelEvent;
		break;
	default:
		break;
	}
	return Data_Wrap_Struct(klass, NULL, NULL, image);
}

template<>
sf::Event* unwrap<sf::Event*>(const VALUE &vimage) {
	return unwrapPtr<sf::Event>(vimage, rb_cSFMLEvent);
}

namespace RubySFML {
namespace Event {

VALUE _getType(VALUE self) {
	//return wrapenum(_self->type);

	return Qnil;
}

namespace Size {

#undef _self
#define _self (&unwrap<sf::Event*>(self)->size)

macro_attr_prop(width, unsigned int)
macro_attr_prop(height, unsigned int)

}

namespace MouseMove {

#undef _self
#define _self (&unwrap<sf::Event*>(self)->mouseMove)

macro_attr_prop(x, int)
macro_attr_prop(y, int)

}

namespace MouseButton {

#undef _self
#define _self (&unwrap<sf::Event*>(self)->mouseButton)

macro_attr_prop(x, int)
macro_attr_prop(y, int)

}

namespace MouseWheel {

#undef _self
#define _self (&unwrap<sf::Event*>(self)->mouseWheel)

macro_attr_prop(x, int)
macro_attr_prop(y, int)
macro_attr_prop(delta, int)

}

}
}

void Init_SFMLEvent(VALUE rb_mSFML) {
	using namespace RubySFML::Event;

	rb_cSFMLEvent = rb_define_class_under(rb_mSFML, "Event", rb_cObject);
	rb_undef_alloc_func(rb_cSFMLEvent);

	rb_undef_method(rb_cSFMLEvent, "initialize_copy");
	rb_undef_method(rb_cSFMLEvent, "_load");

	rb_cSFMLSizeEvent = rb_define_class_under(rb_cSFMLEvent, "Size", rb_cSFMLEvent);
	{
		using namespace Size;
		rb_define_attr_method(rb_cSFMLSizeEvent, "width", _get_width, _set_width);
		rb_define_attr_method(rb_cSFMLSizeEvent, "height", _get_height, _set_height);
	}

	rb_cSFMLMouseMoveEvent = rb_define_class_under(rb_cSFMLEvent, "MouseMove", rb_cSFMLEvent);
	{
		using namespace MouseMove;
		rb_define_attr_method(rb_cSFMLMouseMoveEvent, "x", _get_x, _set_x);
		rb_define_attr_method(rb_cSFMLMouseMoveEvent, "y", _get_y, _set_y);
	}

	rb_cSFMLMouseWheelEvent = rb_define_class_under(rb_cSFMLEvent, "MouseWheel", rb_cSFMLEvent);
	{
		using namespace MouseWheel;
		rb_define_attr_method(rb_cSFMLMouseWheelEvent, "x", _get_x, _set_x);
		rb_define_attr_method(rb_cSFMLMouseWheelEvent, "y", _get_y, _set_y);
		rb_define_attr_method(rb_cSFMLMouseWheelEvent, "delta", _get_delta,
				_set_delta);
	}

}

