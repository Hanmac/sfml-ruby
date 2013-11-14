/*
 * Animation.hpp
 *
 *  Created on: 14.11.2013
 *      Author: hanmac
 */

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_


#include "main.hpp"


#ifdef HAVE_THOR_ANIMATION_HPP
#include <Thor/Animation.hpp>
#endif

extern VALUE rb_cSFMLAnimation;
void Init_SFMLAnimation(VALUE rb_mSFML);

#ifdef HAVE_THOR_ANIMATION_HPP

class RubyAnimation {
public:
	virtual ~RubyAnimation() {};
	template <class Animated>
	void operator() (Animated& animated, float progress) const;

	virtual void ruby_init(int argc,VALUE *argv,VALUE self) = 0;
};

template <typename T>
class TplRubyAnimation : RubyAnimation {
public:
	TplRubyAnimation() : ani(NULL) {}
	virtual ~TplRubyAnimation() {};
	template <class Animated>
	void operator() (Animated& animated, float progress) const
	{
		ani->operator()(animated,progress);
	}

protected:
	//std::shared_ptr<T> ani;
	T* ani;
};

template <>
RubyAnimation* unwrap< RubyAnimation* >(const VALUE &vani);

#endif


#endif /* ANIMATION_HPP_ */
