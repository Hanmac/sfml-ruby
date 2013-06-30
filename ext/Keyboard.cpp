/*
 * Keyboard.cpp
 *
 *  Created on: 30.06.2013
 *      Author: hanmac
 */

#include <sstream>

#include "Keyboard.hpp"

#define _self sf::Keyboard

VALUE rb_mSFMLKeyboard;


namespace RubySFML {
namespace Keyboard {

VALUE _isKeyPressed(VALUE self, VALUE key)
{
	return wrap(_self::isKeyPressed(unwrapenum<sf::Keyboard::Key>(key)));
}

}
}

void Init_SFMLKeyboard(VALUE rb_mSFML)
{
	using namespace RubySFML::Keyboard;

#if 0
	rb_mSFML = rb_define_module("SFML");

#endif


	rb_mSFMLKeyboard = rb_define_module_under(rb_mSFML,"Keyboard");
	rb_define_module_function(rb_mSFMLKeyboard,"key_pressed?",RUBY_METHOD_FUNC(_isKeyPressed),1);

	enumtype* e = registerEnum<sf::Keyboard::Key>("SFML::Keyboard::Key");

	// alphabet
	for(std::size_t i = 0; i < 26; ++i)
	{
		e->add(sf::Keyboard::A + i,"a" + i);
	}
	//Number
	for(std::size_t i = 0; i < 10; ++i)
	{
		std::ostringstream oss;
		oss << "num" << i;
		e->add(sf::Keyboard::Num0 + i,oss.str());
	}
	//Numpad Number
	for(std::size_t i = 0; i < 10; ++i)
	{
		std::ostringstream oss;
		oss << "numpad" << i;
		e->add(sf::Keyboard::Numpad0 + i,oss.str());
	}
	//F keys
	for(std::size_t i = 1; i < 16; ++i)
	{
		std::ostringstream oss;
		oss << "F" << i;
		e->add(sf::Keyboard::F1 + i,oss.str());
	}

		e->add(sf::Keyboard::Escape,"escape")
		->add(sf::Keyboard::LControl,"lcontrol")
		->add(sf::Keyboard::LShift,"lshift")
		->add(sf::Keyboard::LAlt,"lalt")
		->add(sf::Keyboard::LSystem,"lsytem")
		->add(sf::Keyboard::RControl,"rcontrol")
		->add(sf::Keyboard::RShift,"rshift")
		->add(sf::Keyboard::RAlt,"ralt")
		->add(sf::Keyboard::RSystem,"rsytem")
		->add(sf::Keyboard::Menu,"Menu")
		->add(sf::Keyboard::LBracket,"(")
		->add(sf::Keyboard::RBracket,")")
		->add(sf::Keyboard::SemiColon,";")
		->add(sf::Keyboard::Comma,",")
		->add(sf::Keyboard::Period,".")
		->add(sf::Keyboard::Quote,"'")
		->add(sf::Keyboard::Slash,"/")
		->add(sf::Keyboard::BackSlash,"\\")
		->add(sf::Keyboard::Tilde,"~")
		->add(sf::Keyboard::Equal,"=")
		->add(sf::Keyboard::Dash,"dash")
		->add(sf::Keyboard::Space,"space")
		->add(sf::Keyboard::Return,"return")
		->add(sf::Keyboard::BackSpace,"backspace")
		->add(sf::Keyboard::Tab,"tab")
		->add(sf::Keyboard::PageUp,"page_up")
		->add(sf::Keyboard::PageDown,"page_down")
		->add(sf::Keyboard::End,"end")
		->add(sf::Keyboard::Home,"home")
		->add(sf::Keyboard::Insert,"insert")
		->add(sf::Keyboard::Delete,"delete")
		->add(sf::Keyboard::Add,"+")
		->add(sf::Keyboard::Subtract,"-")
		->add(sf::Keyboard::Multiply,"*")
		->add(sf::Keyboard::Divide,"/")
		->add(sf::Keyboard::Left,"left")
		->add(sf::Keyboard::Right,"right")
		->add(sf::Keyboard::Up,"up")
		->add(sf::Keyboard::Down,"down")
		->add(sf::Keyboard::Pause,"pause");
}




