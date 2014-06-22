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

macro_template2(sf::ConvexShape,NULL,rb_cSFMLConvexShape)

namespace RubySFML {
namespace ConvexShape {

macro_alloc(sf::ConvexShape)

VALUE _setPointCount(VALUE self,VALUE val)
{
	_self->setPointCount(NUM2UINT(val));
	return val;
}

VALUE _setPoint(VALUE self, VALUE idx,VALUE point)
{

	int cidx = NUM2INT(idx);
	if(check_index(cidx,_self->getPointCount()))
		_self->setPoint(cidx,unwrap<sf::Vector2f>(point));
	return point;
}


VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE hash;
	rb_scan_args(argc, argv, "01",&hash);

	if(rb_obj_is_kind_of(hash,rb_cHash)) {
		setOption(self,hash,_setPointCount,"point_count");
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




