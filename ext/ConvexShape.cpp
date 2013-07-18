/*
 * ConvexShape.cpp
 *
 *  Created on: 18.07.2013
 *      Author: hanmac
 */

#include "Shape.hpp"
#include "Vector2.hpp"

#define _self unwrap<sf::ConvexShape*>(self)

VALUE rb_cSFMLConvexShape;

template <>
VALUE wrap< sf::ConvexShape >(sf::ConvexShape *image )
{
	return Data_Wrap_Struct(rb_cSFMLConvexShape, NULL, NULL, image);
}

template <>
sf::ConvexShape* unwrap< sf::ConvexShape* >(const VALUE &vimage)
{
	return unwrapPtr<sf::ConvexShape>(vimage, rb_cSFMLConvexShape);
}

template <>
sf::ConvexShape& unwrap< sf::ConvexShape& >(const VALUE &vimage)
{
	return *unwrap<sf::ConvexShape*>(vimage);
}


namespace RubySFML {
namespace ConvexShape {

VALUE _alloc(VALUE self) {
	return wrap(new sf::ConvexShape);
}

VALUE _setPointCount(VALUE self,VALUE val)
{
	_self->setPointCount(NUM2UINT(val));
	return val;
}

VALUE _setPoint(VALUE self, VALUE idx,VALUE point)
{
	std::size_t cidx = NUM2UINT(idx);
	if(cidx > _self->getPointCount())
		return Qnil;
	_self->setPoint(cidx,unwrap<sf::Vector2f>(point));
	return point;
}


VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE hash;
	rb_scan_args(argc, argv, "01",&hash);

	if(rb_obj_is_kind_of(hash,rb_cHash)) {
		VALUE temp;
		if(!NIL_P(temp = rb_hash_aref(hash,ID2SYM(rb_intern("point_count")))))
			_setPointCount(self,temp);
	}

	rb_call_super(argc,argv);

	return self;
}

}
}

void Init_SFMLConvexShape(VALUE rb_mSFML)
{
	using namespace RubySFML::ConvexShape;

#if 0
	rb_mSFML = rb_define_module("SFML");

	rb_define_attr(rb_cSFMLConvexShape,"point_count",0,1);

#endif

	rb_cSFMLConvexShape = rb_define_class_under(rb_mSFML,"ConvexShape",rb_cSFMLShape);
	rb_define_alloc_func(rb_cSFMLConvexShape,_alloc);

	rb_undef_method(rb_cSFMLConvexShape,"initialize_copy");
	rb_undef_method(rb_cSFMLConvexShape,"_load");

	rb_define_method(rb_cSFMLConvexShape,"initialize",RUBY_METHOD_FUNC(_initialize),-1);

	rb_define_method(rb_cSFMLConvexShape,"point_count=",RUBY_METHOD_FUNC(_setPointCount),1);

	rb_define_method(rb_cSFMLConvexShape,"[]=",RUBY_METHOD_FUNC(_setPoint),2);

}




