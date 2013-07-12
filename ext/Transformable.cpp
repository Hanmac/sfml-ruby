/*
 * Transformable.cpp
 *
 *  Created on: 16.06.2013
 *      Author: hanmac
 */

#include "Transformable.hpp"
#include "Transform.hpp"
#include "Vector2.hpp"
#include "Sprite.hpp"
#include "Shape.hpp"
#include "Text.hpp"

#define _self unwrap<sf::Transformable*>(self)

VALUE rb_cSFMLTransformable;

template <>
VALUE wrap< sf::Transformable >(sf::Transformable *image )
{
	return Data_Wrap_Struct(rb_cSFMLTransformable, NULL, NULL, image);
}

template <>
sf::Transformable* unwrap< sf::Transformable* >(const VALUE &vimage)
{
	//otherwise the casting is broken
	if(rb_obj_is_kind_of(vimage,rb_cSFMLSprite))
		return unwrap< sf::Sprite* >(vimage);
	else if(rb_obj_is_kind_of(vimage,rb_cSFMLShape))
		return unwrap< sf::Shape* >(vimage);
	else if(rb_obj_is_kind_of(vimage,rb_cSFMLText))
		return unwrap< sf::Text* >(vimage);

	return unwrapPtr<sf::Transformable>(vimage, rb_cSFMLTransformable);
}

template <>
sf::Transformable& unwrap< sf::Transformable& >(const VALUE &vimage)
{
	return *unwrap<sf::Transformable*>(vimage);
}


namespace RubySFML {
namespace Transformable {

macro_attr(Position,sf::Vector2f)
macro_attr(Rotation,float)
macro_attr(Scale,sf::Vector2f)
macro_attr(Origin,sf::Vector2f)

VALUE _alloc(VALUE self) {
	return wrap(new sf::Transformable);
}

VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE hash;
	rb_scan_args(argc, argv, "01",&hash);

	if(rb_obj_is_kind_of(hash,rb_cHash)) {
		VALUE temp;

		if(!NIL_P(temp = rb_hash_aref(hash,ID2SYM(rb_intern("position")))))
			_setPosition(self,temp);
		if(!NIL_P(temp = rb_hash_aref(hash,ID2SYM(rb_intern("rotation")))))
			_setRotation(self,temp);
		if(!NIL_P(temp = rb_hash_aref(hash,ID2SYM(rb_intern("scale")))))
			_setScale(self,temp);
		if(!NIL_P(temp = rb_hash_aref(hash,ID2SYM(rb_intern("origin")))))
			_setOrigin(self,temp);
	}

	return self;
}

VALUE _move(int argc,VALUE *argv,VALUE self)
{
	VALUE x,y;
	rb_scan_args(argc, argv, "11",&x,&y);
	if(!NIL_P(y))
		_self->move(NUM2DBL(x),NUM2DBL(y));
	else
		_self->move(unwrap<sf::Vector2f>(x));
	return self;
}

}
}


void Init_SFMLTransformable(VALUE rb_mSFML)
{
	using namespace RubySFML::Transformable;

#if 0
	rb_mSFML = rb_define_module("SFML");

	rb_define_attr(rb_cSFMLTransformable,"position",1,1);
	rb_define_attr(rb_cSFMLTransformable,"rotation",1,1);
	rb_define_attr(rb_cSFMLTransformable,"scale",1,1);
	rb_define_attr(rb_cSFMLTransformable,"origin",1,1);
#endif

	rb_cSFMLTransformable = rb_define_class_under(rb_mSFML,"Transformable",rb_cObject);
	rb_define_alloc_func(rb_cSFMLTransformable,_alloc);

	rb_undef_method(rb_cSFMLTransformable,"initialize_copy");
	rb_undef_method(rb_cSFMLTransformable,"_load");

	rb_define_method(rb_cSFMLTransformable,"initialize",RUBY_METHOD_FUNC(_initialize),-1);


	rb_define_attr_method(rb_cSFMLTransformable,"position",_getPosition,_setPosition);
	rb_define_attr_method(rb_cSFMLTransformable,"rotation",_getRotation,_setRotation);
	rb_define_attr_method(rb_cSFMLTransformable,"scale",_getScale,_setScale);
	rb_define_attr_method(rb_cSFMLTransformable,"origin",_getOrigin,_setOrigin);

	rb_define_method(rb_cSFMLTransformable,"move",RUBY_METHOD_FUNC(_move),-1);


}
