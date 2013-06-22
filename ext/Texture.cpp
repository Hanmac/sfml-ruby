/*
 * Texture.cpp
 *
 *  Created on: 12.06.2013
 *      Author: hanmac
 */

#include "Image.hpp"
#include "Texture.hpp"
#include "Vector2.hpp"
#include "Rect.hpp"

#define _self unwrap<sf::Texture*>(self)

VALUE rb_cSFMLTexture;

template <>
VALUE wrap< sf::Texture >(sf::Texture *image )
{
	return Data_Wrap_Struct(rb_cSFMLTexture, NULL, NULL, image);
}

template <>
sf::Texture* unwrap< sf::Texture* >(const VALUE &vimage)
{
	return unwrapPtr<sf::Texture>(vimage, rb_cSFMLTexture);
}

template <>
sf::Texture& unwrap< sf::Texture& >(const VALUE &vimage)
{
	return *unwrap<sf::Texture*>(vimage);
}


namespace RubySFML {
namespace Texture {

macro_attr_bool(Smooth)
macro_attr_bool(Repeated)

VALUE _alloc(VALUE self) {
	return wrap(new sf::Texture);
}

VALUE _size(VALUE self)
{
	return wrap(_self->getSize());
}

VALUE _loadFile(int argc,VALUE *argv,VALUE self)
{
	VALUE path,rect;
	rb_scan_args(argc, argv, "11",&path,&rect);

	sf::IntRect crect;
	if(!NIL_P(rect))
		crect = unwrap<sf::IntRect>(rect);

	sf::Texture *image = new sf::Texture;

	if(image->loadFromFile(unwrap<std::string>(path),crect))
		return wrap(image);
	return Qnil;
}

VALUE _toTexture(VALUE self)
{
	return self;
}

VALUE _toImage(VALUE self)
{
	return wrap(_self->copyToImage());
}
/*
 * call-seq:
 *   Texture.new(red,green,blue[,alpha])
 *
 * creates a new Texture Object.
*/
VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE width,height;
	rb_scan_args(argc, argv, "20",&width,&height);

	_self->create(NUM2UINT(width),NUM2UINT(height));

	return self;
}

}
}

void Init_SFMLTexture(VALUE rb_mSFML)
{
	using namespace RubySFML::Texture;

#if 0
	rb_mSFML = rb_define_module("SFML");
#endif

	rb_cSFMLTexture = rb_define_class_under(rb_mSFML,"Texture",rb_cObject);
	rb_define_alloc_func(rb_cSFMLTexture,_alloc);

	rb_define_method(rb_cSFMLTexture,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_undef_method(rb_cSFMLTexture,"initialize_copy");
	rb_undef_method(rb_cSFMLTexture,"_load");

	rb_define_method(rb_cSFMLTexture,"size",RUBY_METHOD_FUNC(_size),0);

	rb_define_singleton_method(rb_cSFMLTexture,"load_file",RUBY_METHOD_FUNC(_loadFile),-1);

	rb_define_method(rb_cSFMLTexture,"to_image",RUBY_METHOD_FUNC(_toImage),0);
	rb_define_method(rb_cSFMLTexture,"to_texture",RUBY_METHOD_FUNC(_toTexture),0);

	rb_define_attr_method(rb_cSFMLTexture,"smooth",_getSmooth,_setSmooth);
	rb_define_attr_method(rb_cSFMLTexture,"repeated",_getRepeated,_setRepeated);

}


