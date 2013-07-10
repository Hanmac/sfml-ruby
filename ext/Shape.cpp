/*
 * Shape.cpp
 *
 *  Created on: 10.07.2013
 *      Author: hanmac
 */



#include "Shape.hpp"
#include "Texture.hpp"
#include "Rect.hpp"
#include "Color.hpp"

#include "Transformable.hpp"
#include "Drawable.hpp"

#define _self unwrap<sf::Shape*>(self)

VALUE rb_cSFMLShape;

template <>
VALUE wrap< sf::Shape >(sf::Shape *image )
{
	return Data_Wrap_Struct(rb_cSFMLShape, NULL, NULL, image);
}

template <>
sf::Shape* unwrap< sf::Shape* >(const VALUE &vimage)
{
	return unwrapPtr<sf::Shape>(vimage, rb_cSFMLShape);
}

template <>
sf::Shape& unwrap< sf::Shape& >(const VALUE &vimage)
{
	return *unwrap<sf::Shape*>(vimage);
}


namespace RubySFML {
namespace Shape {

macro_attr(Texture,sf::Texture*)
macro_attr(TextureRect,sf::IntRect)
macro_attr(FillColor,sf::Color)
macro_attr(OutlineColor,sf::Color)
macro_attr(OutlineThickness,float)

VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE hash;
	rb_scan_args(argc, argv, "01",&hash);

	if(rb_obj_is_kind_of(hash,rb_cHash)) {
		VALUE temp;

		if(!NIL_P(temp = rb_hash_aref(hash,ID2SYM(rb_intern("texture")))))
			_setTexture(self,temp);
		if(!NIL_P(temp = rb_hash_aref(hash,ID2SYM(rb_intern("texture_rect")))))
			_setTextureRect(self,temp);
		if(!NIL_P(temp = rb_hash_aref(hash,ID2SYM(rb_intern("fill_color")))))
			_setFillColor(self,temp);
		if(!NIL_P(temp = rb_hash_aref(hash,ID2SYM(rb_intern("outline_color")))))
			_setOutlineColor(self,temp);
		if(!NIL_P(temp = rb_hash_aref(hash,ID2SYM(rb_intern("outline_thickness")))))
			_setOutlineThickness(self,temp);

	}

	rb_call_super(argc,argv);

	return self;
}


}
}

void Init_SFMLShape(VALUE rb_mSFML)
{
	using namespace RubySFML::Shape;

#if 0
	rb_mSFML = rb_define_module("SFML");

	rb_define_attr(rb_cSFMLShape,"texture",1,1);
	rb_define_attr(rb_cSFMLShape,"texture_rect",1,1);
	rb_define_attr(rb_cSFMLShape,"fill_color",1,1);
	rb_define_attr(rb_cSFMLShape,"outline_color",1,1);
	rb_define_attr(rb_cSFMLShape,"outline_thickness",1,1);
#endif

	rb_cSFMLShape = rb_define_class_under(rb_mSFML,"Shape",rb_cSFMLTransformable);
	rb_include_module(rb_cSFMLShape,rb_mSFMLDrawable);
	rb_undef_alloc_func(rb_cSFMLShape);

	rb_undef_method(rb_cSFMLShape,"initialize_copy");
	rb_undef_method(rb_cSFMLShape,"_load");

	rb_define_method(rb_cSFMLShape,"initialize",RUBY_METHOD_FUNC(_initialize),-1);


	rb_define_attr_method(rb_cSFMLShape,"texture",_getTexture,_setTexture);
	rb_define_attr_method(rb_cSFMLShape,"texture_rect",_getTextureRect,_setTextureRect);
	rb_define_attr_method(rb_cSFMLShape,"fill_color",_getFillColor,_setFillColor);
	rb_define_attr_method(rb_cSFMLShape,"outline_color",_getOutlineColor,_setOutlineColor);
	rb_define_attr_method(rb_cSFMLShape,"outline_thickness",_getOutlineThickness,_setOutlineThickness);


}



