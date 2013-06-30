/*
 * Event.cpp
 *
 *  Created on: 16.06.2013
 *      Author: hanmac
 */

#include "Event.hpp"


#define _self unwrap<sf::Event*>(self)

VALUE rb_cSFMLEvent, rb_cSFMLSizeEvent, rb_cSFMLTextEvent, rb_cSFMLMouseMoveEvent,
		rb_cSFMLMouseWheelEvent, rb_cSFMLKeyEvent;

template<>
VALUE wrap<sf::Event>(sf::Event *image) {
	VALUE klass = rb_cSFMLEvent;

	switch (image->type) {
	case sf::Event::Resized:
		klass = rb_cSFMLSizeEvent;
		break;
	case sf::Event::TextEntered:
		klass = rb_cSFMLTextEvent;
		break;
	case sf::Event::MouseMoved:
		klass = rb_cSFMLMouseMoveEvent;
		break;
	case sf::Event::MouseWheelMoved:
		klass = rb_cSFMLMouseWheelEvent;
		break;
	case sf::Event::KeyPressed:
	case sf::Event::KeyReleased:
		klass = rb_cSFMLKeyEvent;
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

macro_attr_prop_enum(type,sf::Event::EventType)

namespace Size {

#undef _self
#define _self (&unwrap<sf::Event*>(self)->size)

macro_attr_prop(width, unsigned int)
macro_attr_prop(height, unsigned int)

}

namespace Text {

#undef _self
#define _self (&unwrap<sf::Event*>(self)->text)

VALUE _getUnicode(VALUE self)
{

	return rb_enc_uint_chr(_self->unicode,rb_utf8_encoding());
}

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

namespace Key {

#undef _self
#define _self (&unwrap<sf::Event*>(self)->key)

macro_attr_prop_enum(code,sf::Keyboard::Key)
macro_attr_prop(alt, bool)
macro_attr_prop(control, bool)
macro_attr_prop(shift, bool)
macro_attr_prop(system, bool)

}

}
}

void Init_SFMLEvent(VALUE rb_mSFML) {
	using namespace RubySFML::Event;

#if 0
	rb_mSFML = rb_define_module("SFML");
#endif

	rb_cSFMLEvent = rb_define_class_under(rb_mSFML, "Event", rb_cObject);
	rb_undef_alloc_func(rb_cSFMLEvent);

	rb_undef_method(rb_cSFMLEvent, "initialize_copy");
	rb_undef_method(rb_cSFMLEvent, "_load");

	rb_define_attr_method(rb_cSFMLEvent, "type", _get_type, _set_type);

	rb_cSFMLSizeEvent = rb_define_class_under(rb_cSFMLEvent, "Size", rb_cSFMLEvent);
	{
		using namespace Size;
		rb_define_attr_method(rb_cSFMLSizeEvent, "width", _get_width, _set_width);
		rb_define_attr_method(rb_cSFMLSizeEvent, "height", _get_height, _set_height);
	}

	rb_cSFMLTextEvent = rb_define_class_under(rb_cSFMLEvent, "Text", rb_cSFMLEvent);
	{
		using namespace Text;
		rb_define_method(rb_cSFMLTextEvent,"unicode",RUBY_METHOD_FUNC(_getUnicode),0);

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
		rb_define_attr_method(rb_cSFMLMouseWheelEvent, "delta", _get_delta, _set_delta);
	}

	rb_cSFMLKeyEvent = rb_define_class_under(rb_cSFMLEvent, "Key", rb_cSFMLEvent);
	{
		using namespace Key;
		rb_define_attr_method(rb_cSFMLKeyEvent, "code", _get_code, _set_code);
		rb_define_attr_method(rb_cSFMLKeyEvent, "alt", _get_alt, _set_alt);
		rb_define_attr_method(rb_cSFMLKeyEvent, "control", _get_control, _set_control);
		rb_define_attr_method(rb_cSFMLKeyEvent, "shift", _get_shift, _set_shift);
		rb_define_attr_method(rb_cSFMLKeyEvent, "system", _get_system, _set_system);
	}


	registerEnum<sf::Event::EventType>("SFML::Event::EventType")
		->add(sf::Event::Closed,"closed")
		->add(sf::Event::Resized,"resized")
		->add(sf::Event::LostFocus,"lost_focus")
		->add(sf::Event::GainedFocus,"gained_focus")
		->add(sf::Event::TextEntered,"text_entered")
		->add(sf::Event::KeyPressed,"key_pressed")
		->add(sf::Event::KeyReleased,"key_released")
		->add(sf::Event::MouseWheelMoved,"mouse_wheel_moved")
		->add(sf::Event::MouseButtonPressed,"mouse_button_pressed")
		->add(sf::Event::MouseButtonReleased,"mouse_button_released")
		->add(sf::Event::MouseMoved,"mouse_moved")
		->add(sf::Event::MouseEntered,"mouse_entered")
		->add(sf::Event::MouseLeft,"mouse_left")
		->add(sf::Event::JoystickButtonPressed,"joystick_button_pressed")
		->add(sf::Event::JoystickButtonReleased,"joystick_button_relased")
		->add(sf::Event::JoystickMoved,"joystick_moved")
		->add(sf::Event::JoystickConnected,"joystick_connected")
		->add(sf::Event::JoystickDisconnected,"joystick_disconnected");
}

