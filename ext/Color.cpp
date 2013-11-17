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
	if (rb_obj_is_kind_of(vcolor, rb_cSFMLColor)){
		return true;
	} else if(rb_respond_to(vcolor,rb_intern("red")) &&
		rb_respond_to(vcolor,rb_intern("green")) &&
		rb_respond_to(vcolor,rb_intern("blue")) &&
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

void set_value(sf::Uint8& attr,VALUE val, const char* name)
{
	VALUE temp = rb_funcall(val,rb_intern(name),0);
	if(rb_obj_is_kind_of(temp,rb_cFloat))
		attr = NUM2DBL(temp) * 256;
	else
		attr = NUM2UINT(temp);
};

template <>
sf::Color unwrap< sf::Color >(const VALUE &vcolor)
{
	if(!rb_obj_is_kind_of(vcolor, rb_cSFMLColor) &&
		rb_respond_to(vcolor,rb_intern("red")) &&
		rb_respond_to(vcolor,rb_intern("green")) &&
		rb_respond_to(vcolor,rb_intern("blue")) &&
		rb_respond_to(vcolor,rb_intern("alpha"))){

		sf::Color color;
		set_value(color.r,vcolor,"red");
		set_value(color.b,vcolor,"blue");
		set_value(color.g,vcolor,"green");
		set_value(color.a,vcolor,"alpha");

		return color;
	}else if(rb_obj_is_kind_of(vcolor,rb_cArray)) {
			sf::Color color;
			color.r = NUM2INT(rb_ary_entry(vcolor,0));
			color.g = NUM2INT(rb_ary_entry(vcolor,1));
			color.b = NUM2INT(rb_ary_entry(vcolor,2));

			VALUE val = rb_ary_entry(vcolor,3);

			if(!NIL_P(val))
				color.a = NUM2INT(val);

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
	_set_b(self,blue);
	_set_g(self,green);
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
	return rb_sprintf( "%s(%i, %i, %i, %i)",
		rb_obj_classname( self ),
		FIX2INT(_get_r(self)),
		FIX2INT(_get_g(self)),
		FIX2INT(_get_b(self)),
		FIX2INT(_get_a(self)));
}

/*
 * call-seq:
 *   marshal_dump -> Array
 *
 * Provides marshalling support for use by the Marshal library.
 * ===Return value
 * Array
 */
VALUE _marshal_dump(VALUE self)
{
    VALUE ptr[4];
    ptr[0] = _get_r(self);
    ptr[1] = _get_g(self);
    ptr[2] = _get_b(self);
    ptr[3] = _get_a(self);
    return rb_ary_new4( 4, ptr );
}

/*
 * call-seq:
 *   marshal_load(array) -> nil
 *
 * Provides marshalling support for use by the Marshal library.
 *
 *
 */
VALUE _marshal_load(VALUE self, VALUE data)
{
    VALUE* ptr = RARRAY_PTR( data );
    _set_r(self, ptr[0]);
    _set_g(self, ptr[1]);
    _set_b(self, ptr[2]);
    _set_a(self, ptr[3]);
    return Qnil;
}

}
}

/*
 * Document-class: SFML::Color
 *
 * This class represents an Color.
*/

/* Document-attr: red
 * returns the red value of Color. */
/* Document-attr: blue
 * returns the blue value of Color. */
/* Document-attr: green
 * returns the green value of Color. */
/* Document-attr: alpha
 * returns the alpha value of Color. */

void Init_SFMLColor(VALUE rb_mSFML)
{
	using namespace RubySFML::Color;

#if 0
	rb_mSFML = rb_define_module("SFML");

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

	rb_define_method(rb_cSFMLColor,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cSFMLColor,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);
}

