/*
 * Font.cpp
 *
 *  Created on: 26.06.2013
 *      Author: hanmac
 */

#include "Font.hpp"
#include "Font.hpp"
#include "Rect.hpp"

#define _self unwrap<sf::Font*>(self)

VALUE rb_cSFMLFont;

template <>
VALUE wrap< sf::Font >(sf::Font *image )
{
	return Data_Wrap_Struct(rb_cSFMLFont, NULL, NULL, image);
}

template <>
sf::Font* unwrap< sf::Font* >(const VALUE &vimage)
{
	return unwrapPtr<sf::Font>(vimage, rb_cSFMLFont);
}

template <>
sf::Font& unwrap< sf::Font& >(const VALUE &vimage)
{
	return *unwrap<sf::Font*>(vimage);
}


namespace RubySFML {
namespace Font {

VALUE _alloc(VALUE self) {
	return wrap(new sf::Font);
}

VALUE _loadFile(int argc,VALUE *argv,VALUE self)
{
	VALUE path;
	rb_scan_args(argc, argv, "10",&path);

	sf::Font *font = new sf::Font;

	if(font->loadFromFile(unwrap<std::string>(path)))
		return wrap(font);
	return Qnil;
}

}
}

void Init_SFMLFont(VALUE rb_mSFML)
{
	using namespace RubySFML::Font;

#if 0
	rb_mSFML = rb_define_module("SFML");
#endif

	rb_cSFMLFont = rb_define_class_under(rb_mSFML,"Font",rb_cObject);
	rb_define_alloc_func(rb_cSFMLFont,_alloc);

	rb_undef_method(rb_cSFMLFont,"initialize");
	rb_undef_method(rb_cSFMLFont,"initialize_copy");
	rb_undef_method(rb_cSFMLFont,"_load");

	rb_define_singleton_method(rb_cSFMLFont,"load_file",RUBY_METHOD_FUNC(_loadFile),-1);

}


