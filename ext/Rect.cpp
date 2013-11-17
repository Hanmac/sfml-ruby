/*
 * Rect.cpp
 *
 *  Created on: 12.06.2013
 *      Author: hanmac
 */



#include "Rect.hpp"

#define _self unwrap<sf::FloatRect*>(self)

VALUE rb_cSFMLRect;

template <>
VALUE wrap< sf::FloatRect >(sf::FloatRect *rect )
{
	return Data_Wrap_Struct(rb_cSFMLRect, NULL, free, rect);
}

template <>
VALUE wrap< sf::IntRect >(const sf::IntRect& rect )
{
	return wrap(sf::FloatRect(rect));
}

template <>
bool is_wrapable< sf::FloatRect >(const VALUE &vrect)
{
	if (rb_obj_is_kind_of(vrect, rb_cSFMLRect)){
		return true;
	} else if(rb_respond_to(vrect,rb_intern("left")) &&
		rb_respond_to(vrect,rb_intern("top")) &&
		rb_respond_to(vrect,rb_intern("width")) &&
		rb_respond_to(vrect,rb_intern("height"))){
		return true;
	}else
		return false;
}

template <>
sf::FloatRect* unwrap< sf::FloatRect* >(const VALUE &vrect)
{
	return unwrapPtr<sf::FloatRect>(vrect, rb_cSFMLRect);
}

void set_value(float& attr,VALUE val, const char* name)
{
	attr = NUM2DBL(rb_funcall(val,rb_intern(name),0));
};


template <>
sf::FloatRect unwrap< sf::FloatRect >(const VALUE &vrect)
{
	if(!rb_obj_is_kind_of(vrect, rb_cSFMLRect) &&
		rb_respond_to(vrect,rb_intern("left")) &&
		rb_respond_to(vrect,rb_intern("top")) &&
		rb_respond_to(vrect,rb_intern("width")) &&
		rb_respond_to(vrect,rb_intern("height"))){
		sf::FloatRect rect;

		set_value(rect.left,vrect,"left");
		set_value(rect.top,vrect,"top");
		set_value(rect.width,vrect,"width");
		set_value(rect.height,vrect,"height");

		return rect;
	}else{
		return *unwrap<sf::FloatRect*>(vrect);
	}


}


template <>
sf::IntRect unwrap< sf::IntRect >(const VALUE &vrect)
{
	return sf::IntRect(unwrap< sf::FloatRect >(vrect));
}


namespace RubySFML {
namespace Rect {
VALUE _alloc(VALUE self) {
	return wrap(new sf::FloatRect);
}

macro_attr_prop(left,float)
macro_attr_prop(top,float)
macro_attr_prop(width,float)
macro_attr_prop(height,float)

/*
 * call-seq:
 *   Rect.new(red,green,blue[,alpha])
 *
 * creates a new Rect Object.
*/
VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE left,top,width,height;
	rb_scan_args(argc, argv, "40",&left,&top,&width,&height);
	_set_left(self,left);
	_set_top(self,top);
	_set_width(self,width);
	_set_height(self,height);
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_left(self,_get_left(other));
	_set_top(self,_get_top(other));
	_set_width(self,_get_width(other));
	_set_height(self,_get_height(other));
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
	rb_sprintf("%s(%f, %f, %f, %f)",
		rb_obj_classname(self),
		NUM2DBL(_get_left(self)),
		NUM2DBL(_get_top(self)),
		NUM2DBL(_get_width(self)),
		NUM2DBL(_get_height(self)));
}


/*
 * call-seq:
 *   marshal_dump -> Array
 *
 * Provides marshalling support for use by the Marshal library.
 * ===Return value
 * Array
 */
VALUE _marshal_dump( VALUE self )
{
    VALUE ptr[4];
    ptr[0] = _get_left(self);
    ptr[1] = _get_top(self);
    ptr[2] = _get_width(self);
    ptr[3] = _get_height(self);
    return rb_ary_new4(4, ptr);
}

/*
 * call-seq:
 *   marshal_load(array) -> nil
 *
 * Provides marshalling support for use by the Marshal library.
 *
 *
 */
VALUE _marshal_load( VALUE self, VALUE data )
{
    VALUE* ptr = RARRAY_PTR(data);
    _set_left(self, ptr[0]);
    _set_top(self, ptr[1]);
    _set_width(self, ptr[2]);
    _set_height(self, ptr[3]);

    return Qnil;
}


}
}

/*
 * Document-class: SFML::Rect
 *
 * This class represents an Rect.
*/

/* Document-attr: left
 * returns the left value of Rect. */
/* Document-attr: top
 * returns the top value of Rect. */
/* Document-attr: width
 * returns the width value of Rect. */
/* Document-attr: height
 * returns the height value of Rect. */

void Init_SFMLRect(VALUE rb_mSFML)
{
	using namespace RubySFML::Rect;

#if 0
	rb_mSFML = rb_define_module("SFML");

	rb_define_attr(rb_cSFMLRect,"left",1,1);
	rb_define_attr(rb_cSFMLRect,"top",1,1);
	rb_define_attr(rb_cSFMLRect,"width",1,1);
	rb_define_attr(rb_cSFMLRect,"height",1,1);
#endif


	rb_cSFMLRect = rb_define_class_under(rb_mSFML,"Rect",rb_cObject);
	rb_define_alloc_func(rb_cSFMLRect,_alloc);

	rb_define_method(rb_cSFMLRect,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_private_method(rb_cSFMLRect,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);

	rb_define_attr_method(rb_cSFMLRect,"left",_get_left,_set_left);
	rb_define_attr_method(rb_cSFMLRect,"top",_get_top,_set_top);
	rb_define_attr_method(rb_cSFMLRect,"width",_get_width,_set_width);
	rb_define_attr_method(rb_cSFMLRect,"height",_get_height,_set_height);

	rb_define_method(rb_cSFMLRect,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_method(rb_cSFMLRect,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cSFMLRect,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

}




