/*
 * Texture.hpp
 *
 *  Created on: 12.06.2013
 *      Author: hanmac
 */

#ifndef ANIMATOR_HPP_
#define ANIMATOR_HPP_

#include "main.hpp"


#ifdef HAVE_THOR_ANIMATION_HPP
#include <Thor/Animation.hpp>
#endif

extern VALUE rb_cSFMLAnimator;
void Init_SFMLAnimator(VALUE rb_mSFML);

#ifdef HAVE_THOR_ANIMATION_HPP
#define RubyAnimatorType thor::Animator<sf::Sprite,ID>

template <>
VALUE wrap< RubyAnimatorType >(RubyAnimatorType *ani );

template <>
RubyAnimatorType* unwrap< RubyAnimatorType* >(const VALUE &vani);

template <>
RubyAnimatorType::AnimationFunction unwrap< RubyAnimatorType::AnimationFunction >(const VALUE &vani);


#endif

#endif /* ANIMATOR_HPP_ */
