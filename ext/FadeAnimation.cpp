/*
 * FadeAnimation.cpp
 *
 *  Created on: 14.11.2013
 *      Author: hanmac
 */

#include "FadeAnimation.hpp"

VALUE rb_cSFMLFadeAnimation;

#ifdef HAVE_THOR_ANIMATION_HPP

#define _self unwrap<RubyFadeAnimation*>(self)

void RubyFadeAnimation::ruby_init(int argc,VALUE *argv,VALUE self)
{
	VALUE in,out;
	rb_scan_args(argc, argv, "20",&in,&out);

	setInAndOut(NUM2DBL(in),NUM2DBL(out));
}

void RubyFadeAnimation::setInAndOut(float in, float out)
{
	if(this->ani)
	{
		free(this->ani);
		this->ani = NULL;
	}
	this->m_in = in;
	this->m_out = out;

	this->ani = new thor::FadeAnimation(in,out);
}

macro_template(RubyFadeAnimation,NULL,rb_cSFMLFadeAnimation)

namespace RubySFML {
namespace FadeAnimation {

macro_alloc(RubyFadeAnimation)

macro_attr(In,float)
macro_attr(Out,float)


/*
 * call-seq:
 *   inspect -> String
 *
 * Human-readable description.
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:(%f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=_getIn(self);
	array[3]=_getOut(self);
	return rb_f_sprintf(4,array);
}

}
}

#endif

void Init_SFMLFadeAnimation(VALUE rb_mSFML)
{
#ifdef HAVE_THOR_ANIMATION_HPP
	using namespace RubySFML::FadeAnimation;

#if 0
	rb_mSFML = rb_define_module("SFML");
#endif

	rb_cSFMLFadeAnimation = rb_define_class_under(rb_mSFML,"FadeAnimation",rb_cSFMLAnimation);
	rb_define_alloc_func(rb_cSFMLFadeAnimation,_alloc);

	rb_define_attr_method(rb_cSFMLFadeAnimation,"in",_getIn,_setIn);
	rb_define_attr_method(rb_cSFMLFadeAnimation,"out",_getOut,_setOut);

	rb_define_method(rb_cSFMLFadeAnimation,"inspect",RUBY_METHOD_FUNC(_inspect),0);

#endif
}
