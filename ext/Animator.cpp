/*
 * Animator.cpp
 *
 *  Created on: 25.07.2013
 *      Author: hanmac
 */



#include "Animator.hpp"
#include "Sprite.hpp"
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

class RubyProcAnimation
{
public:
	RubyProcAnimation(VALUE val) : mRuby(val) {}


	template <class Animated>
	void operator() (Animated& animated, float progress) const
	{
		//TODO: it would be cool if the sprite object could be rememberd
		rb_funcall(mRuby,rb_intern("call"),2,wrap(&animated),DBL2NUM(progress));
	}
	
private:
	VALUE mRuby;
};

template <>
RubyAnimatorType::AnimationFunction unwrap< RubyAnimatorType::AnimationFunction >(const VALUE &vani)
{
	return RubyProcAnimation(vani);
}


namespace RubySFML {
namespace Animator {

VALUE _alloc(VALUE self) {
	return wrap(new RubyAnimatorType);
}

VALUE _addAnimation(VALUE self,VALUE id,VALUE time)
{
	_self->addAnimation(SYM2ID(id),unwrap< RubyAnimatorType::AnimationFunction >(rb_block_proc()),unwrap<sf::Time&>(time));
	return self;
}

VALUE _playAnimation(int argc,VALUE *argv,VALUE self)
{
	VALUE id,loop;
	rb_scan_args(argc, argv, "11",&id,&loop);

	_self->playAnimation(SYM2ID(id),RTEST(loop));
	return self;
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

VALUE _animate(VALUE self,VALUE obj)
{
	_self->animate(unwrap<sf::Sprite&>(obj));
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
	
	rb_define_method(rb_cSFMLAnimator,"add_animation",RUBY_METHOD_FUNC(_addAnimation),2);
	rb_define_method(rb_cSFMLAnimator,"play_animation",RUBY_METHOD_FUNC(_playAnimation),-1);
	rb_define_method(rb_cSFMLAnimator,"stop_animation",RUBY_METHOD_FUNC(_stopAnimation),0);
	rb_define_method(rb_cSFMLAnimator,"playing_animation?",RUBY_METHOD_FUNC(_isPlayingAnimation),0);
	rb_define_method(rb_cSFMLAnimator,"playing_animation",RUBY_METHOD_FUNC(_getPlayingAnimation),0);
	rb_define_method(rb_cSFMLAnimator,"update",RUBY_METHOD_FUNC(_update),1);
	rb_define_method(rb_cSFMLAnimator,"animate",RUBY_METHOD_FUNC(_animate),1);
#endif
}
