/*
 * Transform.cpp
 *
 *  Created on: 30.06.2013
 *      Author: hanmac
 */

#include "Transform.hpp"
#include "View.hpp"
#include "Transformable.hpp"

#define _self unwrap<sf::Transform*>(self)

VALUE rb_cSFMLTransform;

template <>
VALUE wrap< sf::Transform >(sf::Transform *image )
{
	return Data_Wrap_Struct(rb_cSFMLTransform, NULL, NULL, image);
}

template <>
sf::Transform* unwrap< sf::Transform* >(const VALUE &vimage)
{
	return unwrapPtr<sf::Transform>(vimage, rb_cSFMLTransform);
}

template <>
const sf::Transform& unwrap< const sf::Transform& >(const VALUE &vimage)
{
	if(rb_obj_is_kind_of(vimage,rb_cSFMLView))
		return unwrap< sf::View* >(vimage)->getTransform();
	if(rb_obj_is_kind_of(vimage,rb_cSFMLTransformable))
		return unwrap< sf::Transformable* >(vimage)->getTransform();

	return *unwrap<sf::Transform*>(vimage);
}


namespace RubySFML {
namespace Transform {

VALUE _alloc(VALUE self) {
	return wrap(new sf::Transform);
}

VALUE _getMatrix(VALUE self)
{
	VALUE result = rb_ary_new();
	const float *data(_self->getMatrix());
	for(std::size_t i = 0; i < 16; ++i)
	{
		rb_ary_push(result,DBL2NUM(data[i]));
	}

	return result;
}

}
}


void Init_SFMLTransform(VALUE rb_mSFML)
{
	using namespace RubySFML::Transform;

#if 0
	rb_mSFML = rb_define_module("SFML");

#endif

	rb_cSFMLTransform = rb_define_class_under(rb_mSFML,"Transform",rb_cObject);
	rb_define_alloc_func(rb_cSFMLTransform,_alloc);

	rb_undef_method(rb_cSFMLTransform,"initialize_copy");
	rb_undef_method(rb_cSFMLTransform,"_load");

	//rb_define_method(rb_cSFMLTransform,"initialize",RUBY_METHOD_FUNC(_initialize),-1);

	rb_define_method(rb_cSFMLTransform,"matrix",RUBY_METHOD_FUNC(_getMatrix),0);

	//rb_define_attr_method(rb_cSFMLTransform,"position",_getPosition,_setPosition);
	//rb_define_attr_method(rb_cSFMLTransform,"rotation",_getRotation,_setRotation);
	//rb_define_attr_method(rb_cSFMLTransform,"scale",_getScale,_setScale);
	//rb_define_attr_method(rb_cSFMLTransform,"origin",_getOrigin,_setOrigin);


}
