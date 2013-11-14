/*
 * Animation.cpp
 *
 *  Created on: 14.11.2013
 *      Author: hanmac
 */





#include "Animation.hpp"

VALUE rb_cSFMLAnimation;

#ifdef HAVE_THOR_ANIMATION_HPP

#define _self unwrap<RubyAnimation*>(self)


template <>
RubyAnimation* unwrap< RubyAnimation* >(const VALUE &vani)
{
	return unwrapPtr<RubyAnimation>(vani, rb_cSFMLAnimation);
}

namespace RubySFML {
namespace Animation {

VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	_self->ruby_init(argc,argv,self);

	return self;
}

}
}

#endif

void Init_SFMLAnimation(VALUE rb_mSFML)
{
#ifdef HAVE_THOR_ANIMATION_HPP
	using namespace RubySFML::Animation;

#if 0
	rb_mSFML = rb_define_module("SFML");
#endif

	rb_cSFMLAnimation = rb_define_class_under(rb_mSFML,"Animation",rb_cObject);
	rb_undef_alloc_func(rb_cSFMLAnimation);

	rb_define_method(rb_cSFMLAnimation,"initialize",RUBY_METHOD_FUNC(_initialize),-1);

	rb_undef_method(rb_cSFMLAnimation,"initialize_copy");
	rb_undef_method(rb_cSFMLAnimation,"_load");

#endif
}
