/*
 * RectangleShape.cpp
 *
 *  Created on: 10.07.2013
 *      Author: hanmac
 */



#include "Shape.hpp"
#include "Vector2.hpp"

#define _self unwrap<sf::RectangleShape*>(self)

VALUE rb_cSFMLRectangleShape;

macro_template2(sf::RectangleShape,NULL,rb_cSFMLRectangleShape)


namespace RubySFML {
namespace RectangleShape {

macro_alloc(sf::RectangleShape)

macro_attr(Size,sf::Vector2f)

VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE hash;
	rb_scan_args(argc, argv, "01",&hash);

	if(rb_obj_is_kind_of(hash,rb_cHash)) {
		VALUE temp;

		setOption(self,hash,_setSize,"size");

	}

	rb_call_super(argc,argv);

	return self;
}


}
}

void Init_SFMLRectangleShape(VALUE rb_mSFML)
{
	using namespace RubySFML::RectangleShape;

#if 0
	rb_mSFML = rb_define_module("SFML");

	rb_define_attr(rb_cSFMLRectangleShape,"size",1,1);
#endif

	rb_cSFMLRectangleShape = rb_define_class_under(rb_mSFML,"RectangleShape",rb_cSFMLShape);
	rb_define_alloc_func(rb_cSFMLRectangleShape,_alloc);

	rb_undef_method(rb_cSFMLRectangleShape,"initialize_copy");
	rb_undef_method(rb_cSFMLRectangleShape,"_load");

	rb_define_method(rb_cSFMLRectangleShape,"initialize",RUBY_METHOD_FUNC(_initialize),-1);


	rb_define_attr_method(rb_cSFMLRectangleShape,"size",_getSize,_setSize);
}



