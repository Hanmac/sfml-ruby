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

template <>
sf::FloatRect unwrap< sf::FloatRect >(const VALUE &vrect)
{
	if(!rb_obj_is_kind_of(vrect, rb_cSFMLRect) &&
		rb_respond_to(vrect,rb_intern("left")) &&
		rb_respond_to(vrect,rb_intern("top")) &&
		rb_respond_to(vrect,rb_intern("width")) &&
		rb_respond_to(vrect,rb_intern("height"))){
		sf::FloatRect rect;
		rect.left = NUM2DBL(rb_funcall(vrect,rb_intern("left"),0));
		rect.top = NUM2DBL(rb_funcall(vrect,rb_intern("top"),0));
		rect.width = NUM2DBL(rb_funcall(vrect,rb_intern("width"),0));
		rect.height = NUM2DBL(rb_funcall(vrect,rb_intern("height"),0));

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
	VALUE array[6];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=_get_left(self);
	array[3]=_get_top(self);
	array[4]=_get_width(self);
	array[5]=_get_height(self);
	return rb_f_sprintf(6,array);
}


}
}

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
}




