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
#include "Vector2.hpp"

#include "Transformable.hpp"
#include "Drawable.hpp"

#define _self unwrap<sf::Shape*>(self)

VALUE rb_cSFMLShape;

macro_template2(sf::Shape,NULL,rb_cSFMLShape)

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

		setOption(self,hash,_setTexture,"texture");
		setOption(self,hash,_setTextureRect,"texture_rect");
		setOption(self,hash,_setFillColor,"fill_color");
		setOption(self,hash,_setOutlineColor,"outline_color");
		setOption(self,hash,_setOutlineThickness,"outline_thickness");

	}

	rb_call_super(argc,argv);

	return self;
}

VALUE _getPointCount(VALUE self)
{
	return UINT2NUM(_self->getPointCount());
}

VALUE _getPoint(VALUE self, VALUE idx)
{
	int cidx = NUM2INT(idx);
	if(check_index(cidx,_self->getPointCount()))
		return wrap(_self->getPoint(cidx));
	return Qnil;
}

VALUE _eachPoint(VALUE self)
{
	RETURN_SIZED_ENUMERATOR(self,0,NULL,_getPointCount);

	std::size_t size = _self->getPointCount();

	for(std::size_t i = 0; i < size; ++i)
		rb_yield(wrap(_self->getPoint(i)));

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

	rb_define_attr(rb_cSFMLShape,"point_count",1,0);
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

	rb_define_method(rb_cSFMLShape,"point_count",RUBY_METHOD_FUNC(_getPointCount),0);

	rb_define_method(rb_cSFMLShape,"[]",RUBY_METHOD_FUNC(_getPoint),1);
	rb_define_method(rb_cSFMLShape,"each_point",RUBY_METHOD_FUNC(_eachPoint),0);
}



