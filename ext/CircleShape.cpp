/*
 * CircleShape.cpp
 *
 *  Created on: 10.07.2013
 *      Author: hanmac
 */



#include "Shape.hpp"
#include "Vector2.hpp"

#define _self unwrap<sf::CircleShape*>(self)

VALUE rb_cSFMLCircleShape;

template <>
VALUE wrap< sf::CircleShape >(sf::CircleShape *image )
{
	return Data_Wrap_Struct(rb_cSFMLCircleShape, NULL, NULL, image);
}

template <>
sf::CircleShape* unwrap< sf::CircleShape* >(const VALUE &vimage)
{
	return unwrapPtr<sf::CircleShape>(vimage, rb_cSFMLCircleShape);
}

template <>
sf::CircleShape& unwrap< sf::CircleShape& >(const VALUE &vimage)
{
	return *unwrap<sf::CircleShape*>(vimage);
}


namespace RubySFML {
namespace CircleShape {

macro_attr(Radius,float)

VALUE _alloc(VALUE self) {
	return wrap(new sf::CircleShape);
}

VALUE _setPointCount(VALUE self,VALUE val)
{
	_self->setPointCount(NUM2UINT(val));
	return val;
}


VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE hash;
	rb_scan_args(argc, argv, "01",&hash);

	if(rb_obj_is_kind_of(hash,rb_cHash)) {
		VALUE temp;

		if(!NIL_P(temp = rb_hash_aref(hash,ID2SYM(rb_intern("radius")))))
			_setRadius(self,temp);
		if(!NIL_P(temp = rb_hash_aref(hash,ID2SYM(rb_intern("point_count")))))
			_setPointCount(self,temp);
	}

	rb_call_super(argc,argv);

	return self;
}

}
}

void Init_SFMLCircleShape(VALUE rb_mSFML)
{
	using namespace RubySFML::CircleShape;

#if 0
	rb_mSFML = rb_define_module("SFML");

	rb_define_attr(rb_cSFMLCircleShape,"radius",1,1);
	rb_define_attr(rb_cSFMLCircleShape,"point_count",0,1);

#endif

	rb_cSFMLCircleShape = rb_define_class_under(rb_mSFML,"CircleShape",rb_cSFMLShape);
	rb_define_alloc_func(rb_cSFMLCircleShape,_alloc);

	rb_undef_method(rb_cSFMLCircleShape,"initialize_copy");
	rb_undef_method(rb_cSFMLCircleShape,"_load");

	rb_define_method(rb_cSFMLCircleShape,"initialize",RUBY_METHOD_FUNC(_initialize),-1);

	rb_define_method(rb_cSFMLCircleShape,"point_count=",RUBY_METHOD_FUNC(_setPointCount),1);


	rb_define_attr_method(rb_cSFMLCircleShape,"radius",_getRadius,_setRadius);
}




