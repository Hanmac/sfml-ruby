/*
 * Font.cpp
 *
 *  Created on: 26.06.2013
 *      Author: hanmac
 */

#include "Font.hpp"
#include "Texture.hpp"
#include "Rect.hpp"

#define _self unwrap<sf::Font*>(self)

VALUE rb_cSFMLFont;

macro_template2(sf::Font,NULL,rb_cSFMLFont)

namespace RubySFML {
namespace Font {

macro_alloc(sf::Font)


VALUE _loadFile(int argc,VALUE *argv,VALUE self)
{
	VALUE path;
	rb_scan_args(argc, argv, "10",&path);

	return wrap(_self->loadFromFile(unwrap<std::string>(path)));
}


VALUE _loadMemory(int argc,VALUE *argv,VALUE self)
{
	VALUE memory;
	rb_scan_args(argc, argv, "10",&memory);
	StringValue(memory);

	return wrap(_self->loadFromMemory(RSTRING_PTR(memory), RSTRING_LEN(memory)));
}

VALUE _classloadFile(int argc,VALUE *argv,VALUE self)
{
	VALUE font(_alloc(self));
	if(RTEST(_loadFile(argc,argv,font)))
		return font;
	return Qnil;
}

VALUE _classloadMemory(int argc,VALUE *argv,VALUE self)
{
	VALUE font(_alloc(self));
	if(RTEST(_loadMemory(argc,argv,font)))
		return font;
	return Qnil;
}

VALUE _to_texture(VALUE self,VALUE size)
{
	return wrap(_self->getTexture(NUM2UINT(size)));
}

VALUE _get_kerning(VALUE self,VALUE first,VALUE last,VALUE size)
{
	return INT2NUM(_self->getKerning(NUM2UINT(first),NUM2UINT(last),NUM2UINT(size)));
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

	rb_define_method(rb_cSFMLFont,"load_file",RUBY_METHOD_FUNC(_loadFile),-1);
	rb_define_method(rb_cSFMLFont,"load_memory",RUBY_METHOD_FUNC(_loadMemory),-1);

	rb_define_singleton_method(rb_cSFMLFont,"load_file",RUBY_METHOD_FUNC(_classloadFile),-1);
	rb_define_singleton_method(rb_cSFMLFont,"load_memory",RUBY_METHOD_FUNC(_classloadMemory),-1);

	rb_define_method(rb_cSFMLFont,"to_texture",RUBY_METHOD_FUNC(_to_texture),1);

}


