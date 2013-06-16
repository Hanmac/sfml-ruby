/*
 * Transformable.cpp
 *
 *  Created on: 16.06.2013
 *      Author: hanmac
 */

#include "Transformable.hpp"

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



}
}


void Init_SFMLTransformable(VALUE rb_mSFML)
{
	using namespace RubySFML::Transformable;
#if 0
	rb_define_attr(rb_cSFMLTransformable,"position",1,1);
	rb_define_attr(rb_cSFMLTransformable,"rotation",1,1);
	rb_define_attr(rb_cSFMLTransformable,"scale",1,1);
	rb_define_attr(rb_cSFMLTransformable,"origin",1,1);
#endif

	rb_cSFMLTransformable = rb_define_class_under(rb_mSFML,"Transformable",rb_cObject);
	rb_define_alloc_func(rb_cSFMLTransformable,_alloc);

	rb_undef_method(rb_cSFMLTransformable,"initialize_copy");
	rb_undef_method(rb_cSFMLTransformable,"_load");

	rb_define_attr_method(rb_cSFMLTransformable,"position",_getPosition,_setPosition);
	rb_define_attr_method(rb_cSFMLTransformable,"rotation",_getRotation,_setRotation);
	rb_define_attr_method(rb_cSFMLTransformable,"scale",_getScale,_setScale);
	rb_define_attr_method(rb_cSFMLTransformable,"origin",_getOrigin,_setOrigin);


}
