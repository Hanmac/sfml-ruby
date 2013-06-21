/*
 * VideoMode.cpp
 *
 *  Created on: 21.06.2013
 *      Author: hanmac
 */



#include "VideoMode.hpp"
#include "Color.hpp"
#include "Vector2.hpp"

#define _self unwrap<sf::VideoMode*>(self)

VALUE rb_cSFMLVideoMode;

template <>
VALUE wrap< sf::VideoMode >(sf::VideoMode *height )
{
	return Data_Wrap_Struct(rb_cSFMLVideoMode, NULL, free, height);
}

template <>
sf::VideoMode* unwrap< sf::VideoMode* >(const VALUE &vheight)
{
	return unwrapPtr<sf::VideoMode>(vheight, rb_cSFMLVideoMode);
}

template <>
sf::VideoMode unwrap< sf::VideoMode >(const VALUE &vheight)
{
	if(NIL_P(vheight))
		return sf::VideoMode::getDesktopMode();
	return *unwrap<sf::VideoMode*>(vheight);
}

namespace RubySFML {
namespace VideoMode {
VALUE _alloc(VALUE self) {
	return wrap(new sf::VideoMode);
}

macro_attr_prop(width,unsigned int)
macro_attr_prop(height,unsigned int)
macro_attr_prop(bitsPerPixel,unsigned int)

/*
 * call-seq:
 *   VideoMode.new(red,green,blue[,alpha])
 *
 * creates a new VideoMode Object.
*/
VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE width,height,bitsPerPixel;
	rb_scan_args(argc, argv, "21",&width,&height,&bitsPerPixel);
	_set_width(self,width);
	_set_height(self,height);
	if(!NIL_P(bitsPerPixel))
		_set_bitsPerPixel(self,bitsPerPixel);
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_width(self,_get_width(other));
	_set_height(self,_get_height(other));
	_set_bitsPerPixel(self,_get_bitsPerPixel(other));
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
	VALUE array[5];
	array[0]=rb_str_new2("#<%s:(%s, %s, %s)>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(_get_width(self),rb_intern("inspect"),0);
	array[3]=rb_funcall(_get_height(self),rb_intern("inspect"),0);
	array[4]=rb_funcall(_get_bitsPerPixel(self),rb_intern("inspect"),0);
	return rb_f_sprintf(5,array);
}


}
}

void Init_SFMLVideoMode(VALUE rb_mSFML)
{
	using namespace RubySFML::VideoMode;

#if 0
	rb_define_attr(rb_cSFMLVideoMode,"width",1,1);
	rb_define_attr(rb_cSFMLVideoMode,"height",1,1);
	rb_define_attr(rb_cSFMLVideoMode,"bits",1,1);
#endif


	rb_cSFMLVideoMode = rb_define_class_under(rb_mSFML,"VideoMode",rb_cObject);
	rb_define_alloc_func(rb_cSFMLVideoMode,_alloc);

	rb_define_method(rb_cSFMLVideoMode,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_private_method(rb_cSFMLVideoMode,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);

	rb_define_attr_method(rb_cSFMLVideoMode,"width",_get_width,_set_width);
	rb_define_attr_method(rb_cSFMLVideoMode,"height",_get_height,_set_height);
	rb_define_attr_method(rb_cSFMLVideoMode,"bits",_get_bitsPerPixel,_set_bitsPerPixel);

	rb_define_method(rb_cSFMLVideoMode,"inspect",RUBY_METHOD_FUNC(_inspect),0);
}


