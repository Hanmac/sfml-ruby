/*
 * Image.cpp
 *
 *  Created on: 11.06.2013
 *      Author: hanmac
 */

#include "Texture.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include "Vector2.hpp"

#define _self unwrap<sf::Image*>(self)

VALUE rb_cSFMLImage;

template <>
VALUE wrap< sf::Image >(sf::Image *image )
{
	return Data_Wrap_Struct(rb_cSFMLImage, NULL, NULL, image);
}

template <>
sf::Image* unwrap< sf::Image* >(const VALUE &vimage)
{
	return unwrapPtr<sf::Image>(vimage, rb_cSFMLImage);
}

template <>
sf::Image& unwrap< sf::Image& >(const VALUE &vimage)
{
	return *unwrap<sf::Image*>(vimage);
}


namespace RubySFML {
namespace Image {
VALUE _alloc(VALUE self) {
	return wrap(new sf::Image);
}

VALUE _size(VALUE self)
{
	return wrap(_self->getSize());
}

VALUE _loadFile(VALUE self, VALUE path)
{
	sf::Image *image = new sf::Image;

	if(image->loadFromFile(unwrap<std::string>(path)))
		return wrap(image);
	return Qnil;
}

VALUE _saveFile(VALUE self,VALUE path)
{
	_self->saveToFile(unwrap<std::string>(path));
	return self;
}

VALUE _getColor(VALUE self, VALUE x, VALUE y)
{
	sf::Vector2u size = _self->getSize();
	std::size_t cx = NUM2UINT(x),cy = NUM2UINT(y);
	if(cx >= size.x || cy >= size.y)
		return Qnil;
	return wrap(_self->getPixel(cx,cy));
}

VALUE _setColor(VALUE self, VALUE x, VALUE y, VALUE color)
{
	sf::Vector2u size = _self->getSize();
	std::size_t cx = NUM2UINT(x),cy = NUM2UINT(y);
	if(cx >= size.x || cy >= size.y)
		return self;

	_self->setPixel(cx,cy,unwrap<sf::Color>(color));
	return self;
}

VALUE _toImage(VALUE self)
{
	return self;
}

VALUE _toTexture(int argc,VALUE *argv,VALUE self)
{
	VALUE rect;
	rb_scan_args(argc, argv, "01",&rect);

	sf::Texture *tex = new sf::Texture;
	if(tex->loadFromImage(*_self))
		return wrap(tex);
	return Qnil;
}

/*
 * call-seq:
 *   Image.new(red,green,blue[,alpha])
 *
 * creates a new Image Object.
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

void Init_SFMLImage(VALUE rb_mSFML)
{
	using namespace RubySFML::Image;


	rb_cSFMLImage = rb_define_class_under(rb_mSFML,"Image",rb_cObject);
	rb_define_alloc_func(rb_cSFMLImage,_alloc);

	rb_define_method(rb_cSFMLImage,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_undef_method(rb_cSFMLImage,"initialize_copy");
	rb_undef_method(rb_cSFMLImage,"_load");

	rb_define_method(rb_cSFMLImage,"size",RUBY_METHOD_FUNC(_size),0);

	rb_define_singleton_method(rb_cSFMLImage,"load_file",RUBY_METHOD_FUNC(_loadFile),1);
	rb_define_method(rb_cSFMLImage,"save_file",RUBY_METHOD_FUNC(_saveFile),1);

	rb_define_method(rb_cSFMLImage,"[]",RUBY_METHOD_FUNC(_getColor),2);
	rb_define_method(rb_cSFMLImage,"[]=",RUBY_METHOD_FUNC(_setColor),3);

	rb_define_method(rb_cSFMLImage,"to_image",RUBY_METHOD_FUNC(_toImage),0);
	rb_define_method(rb_cSFMLImage,"to_texture",RUBY_METHOD_FUNC(_toTexture),-1);
}


