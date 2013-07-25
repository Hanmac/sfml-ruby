/*
 * Animator.cpp
 *
 *  Created on: 25.07.2013
 *      Author: hanmac
 */



#include "Animator.hpp"
#include "Time.hpp"

#ifdef HAVE_THOR_ANIMATION_HPP
#define _self unwrap<RubyAnimatorType*>(self)
#endif

VALUE rb_cSFMLAnimator;


#ifdef HAVE_THOR_ANIMATION_HPP
template <>
VALUE wrap< RubyAnimatorType >(RubyAnimatorType *ani )
{
	return Data_Wrap_Struct(rb_cSFMLAnimator, NULL, NULL, ani);
}

template <>
RubyAnimatorType* unwrap< RubyAnimatorType* >(const VALUE &vani)
{
	return unwrapPtr<RubyAnimatorType>(vani, rb_cSFMLAnimator);
}

namespace RubySFML {
namespace Animator {

VALUE _alloc(VALUE self) {
	return wrap(new RubyAnimatorType);
}


VALUE _stopAnimation(VALUE self)
{
	_self->stopAnimation();
	return self;
}

VALUE _isPlayingAnimation(VALUE self)
{
	return wrap(_self->isPlayingAnimation());
}

VALUE _getPlayingAnimation(VALUE self)
{
	if(_self->isPlayingAnimation())
		return ID2SYM(_self->getPlayingAnimation());
	return Qnil;
}


VALUE _update(VALUE self,VALUE time)
{
	_self->update(unwrap<sf::Time&>(time));
	return self;
}

}
}

#endif

void Init_SFMLAnimator(VALUE rb_mSFML)
{
#ifdef HAVE_THOR_ANIMATION_HPP
	using namespace RubySFML::Animator;

#if 0
	rb_mSFML = rb_define_module("SFML");
#endif

	rb_cSFMLAnimator = rb_define_class_under(rb_mSFML,"Animator",rb_cObject);
	rb_define_alloc_func(rb_cSFMLAnimator,_alloc);

	rb_undef_method(rb_cSFMLAnimator,"initialize_copy");
	rb_undef_method(rb_cSFMLAnimator,"_load");
#endif
}
