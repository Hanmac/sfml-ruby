/*
 * Color.cpp
 *
 *  Created on: 09.06.2013
 *      Author: hanmac
 */

#include "Color.hpp"

#define _self unwrap<sf::Color*>(self)

VALUE rb_cSFMLColor;

template <>
VALUE wrap< sf::Color >(sf::Color *color )
{
	return Data_Wrap_Struct(rb_cSFMLColor, NULL, free, color);
}

template <>
bool is_wrapable< sf::Color >(const VALUE &vcolor)
{
	if (rb_obj_is_kind_of(vcolor, rb_cSFMLColor) ||
		rb_obj_is_kind_of(vcolor, rb_cString) || FIXNUM_P(vcolor)){
		return true;
	} else if(rb_respond_to(vcolor,rb_intern("red")) &&
		rb_respond_to(vcolor,rb_intern("blue")) &&
		rb_respond_to(vcolor,rb_intern("green")) &&
		rb_respond_to(vcolor,rb_intern("alpha"))){
		return true;
	}else
		return false;
}

template <>
sf::Color* unwrap< sf::Color* >(const VALUE &vcolor)
{
	return unwrapPtr<sf::Color>(vcolor, rb_cSFMLColor);
}

template <>
sf::Color unwrap< sf::Color >(const VALUE &vcolor)
{
	if(!rb_obj_is_kind_of(vcolor, rb_cSFMLColor) &&
		rb_respond_to(vcolor,rb_intern("red")) &&
		rb_respond_to(vcolor,rb_intern("blue")) &&
		rb_respond_to(vcolor,rb_intern("green")) &&
		rb_respond_to(vcolor,rb_intern("alpha"))){
		double red,blue,green,alpha;
		sf::Color color;
		red = NUM2DBL(rb_funcall(vcolor,rb_intern("red"),0));
		if(red < 1.0)
			red *=256;

		blue = NUM2DBL(rb_funcall(vcolor,rb_intern("blue"),0));
		if(blue < 1.0)
			blue *=256;

		green = NUM2DBL(rb_funcall(vcolor,rb_intern("green"),0));
		if(green < 1.0)
			green *=256;

		alpha = NUM2DBL(rb_funcall(vcolor,rb_intern("alpha"),0));
		if(alpha < 1.0)
			alpha *=256;

		color.r = red;
		color.b = blue;
		color.g = green;
		color.a = alpha;

		return color;
	}else{
		return *unwrap<sf::Color*>(vcolor);
	}


}

namespace RubySFML {
namespace Color {
VALUE _alloc(VALUE self) {
	return wrap(new sf::Color);
}

macro_attr_prop(r,unsigned int)
macro_attr_prop(g,unsigned int)
macro_attr_prop(b,unsigned int)
macro_attr_prop(a,unsigned int)

/*
 * call-seq:
 *   Color.new(red,green,blue[,alpha])
 *
 * creates a new Color Object.
*/
VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE red,green,blue,alpha;
	rb_scan_args(argc, argv, "31",&red,&green,&blue,&alpha);
	_set_r(self,red);
	_set_g(self,green);
	_set_b(self,blue);
	_set_a(self,NIL_P(alpha) ? INT2NUM(255) : alpha);
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_r(self,_get_r(other));
	_set_g(self,_get_g(other));
	_set_b(self,_get_b(other));
	_set_a(self,_get_a(other));
	return result;
}
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
	VALUE array[6];
	array[0]=rb_str_new2("#<%s:(%d, %d, %d, %d)>");
	array[1]=rb_class_of(self);
	array[2]=_get_r(self);
	array[3]=_get_g(self);
	array[4]=_get_b(self);
	array[5]=_get_a(self);
	return rb_f_sprintf(6,array);
}


}
}

void Init_SFMLColor(VALUE rb_mSFML)
{
	using namespace RubySFML::Color;

#if 0
	rb_define_attr(rb_cSFMLColor,"red",1,1);
	rb_define_attr(rb_cSFMLColor,"green",1,1);
	rb_define_attr(rb_cSFMLColor,"blue",1,1);
	rb_define_attr(rb_cSFMLColor,"alpha",1,1);
#endif


	rb_cSFMLColor = rb_define_class_under(rb_mSFML,"Color",rb_cObject);
	rb_define_alloc_func(rb_cSFMLColor,_alloc);

	rb_define_method(rb_cSFMLColor,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_private_method(rb_cSFMLColor,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);


	rb_define_attr_method(rb_cSFMLColor,"red",_get_r,_set_r);
	rb_define_attr_method(rb_cSFMLColor,"green",_get_g,_set_g);
	rb_define_attr_method(rb_cSFMLColor,"blue",_get_b,_set_b);
	rb_define_attr_method(rb_cSFMLColor,"alpha",_get_a,_set_a);

	rb_define_method(rb_cSFMLColor,"inspect",RUBY_METHOD_FUNC(_inspect),0);
}

