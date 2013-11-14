/*
 * FadeAnimation.hpp
 *
 *  Created on: 14.11.2013
 *      Author: hanmac
 */

#ifndef FADEANIMATION_HPP_
#define FADEANIMATION_HPP_


#include "Animation.hpp"


#ifdef HAVE_THOR_ANIMATION_HPP
#include <Thor/Animation.hpp>
#endif

extern VALUE rb_cSFMLFadeAnimation;
void Init_SFMLFadeAnimation(VALUE rb_mSFML);

#ifdef HAVE_THOR_ANIMATION_HPP

class RubyFadeAnimation : public TplRubyAnimation<thor::FadeAnimation>
{
public:
	float getIn() const { return m_in;}
	float getOut() const { return m_out;}

	void setIn(float in) {setInAndOut(in,m_out);}
	void setOut(float out) {setInAndOut(m_in,out);}

	void ruby_init(int argc,VALUE *argv,VALUE self);
private:
	float m_in;
	float m_out;

	void setInAndOut(float in,float out);
};

template <>
VALUE wrap< RubyFadeAnimation >(RubyFadeAnimation *ani );

template <>
RubyFadeAnimation* unwrap< RubyFadeAnimation* >(const VALUE &vani);


#endif


#endif /* FADEANIMATION_HPP_ */
