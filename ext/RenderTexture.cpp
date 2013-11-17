/*
 * RenderTexture.cpp
 *
 *  Created on: 30.06.2013
 *      Author: hanmac
 */

#include "RenderTarget.hpp"
#include "Texture.hpp"
#include "RenderTexture.hpp"

#define _self unwrap<sf::RenderTexture*>(self)

VALUE rb_cSFMLRenderTexture;

template <>
VALUE wrap< sf::RenderTexture >(sf::RenderTexture *image )
{
	return Data_Wrap_Struct(rb_cSFMLRenderTexture, NULL, NULL, image);
}

template <>
sf::RenderTexture* unwrap< sf::RenderTexture* >(const VALUE &vimage)
{
	return unwrapPtr<sf::RenderTexture>(vimage, rb_cSFMLRenderTexture);
}

namespace RubySFML {
namespace RenderTexture {

macro_attr_bool(Smooth)
macro_attr_bool(Repeated)

VALUE _alloc(VALUE self) {
	return wrap(new sf::RenderTexture);
}

/*
 * call-seq:
 *   Texture.new(red,green,blue[,alpha])
 *
 * creates a new Texture Object.
*/
VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE width,height,depth;
	rb_scan_args(argc, argv, "21",&width,&height,&depth);

	_self->create(NUM2UINT(width),NUM2UINT(height),RTEST(depth));

	return self;
}

singlefunc(display)

}
}

void Init_SFMLRenderTexture(VALUE rb_mSFML)
{
	using namespace RubySFML::RenderTexture;

#if 0
	rb_mSFML = rb_define_module("SFML");
	rb_mSFMLRenderTarget = rb_define_module_under(rb_mSFML,"RenderTarget");
#endif

	rb_cSFMLRenderTexture = rb_define_class_under(rb_mSFML,"RenderTexture",rb_cObject);
	rb_include_module(rb_cSFMLRenderTexture,rb_mSFMLRenderTarget);
	rb_define_alloc_func(rb_cSFMLRenderTexture,_alloc);

	rb_define_method(rb_cSFMLRenderTexture,"initialize",RUBY_METHOD_FUNC(_initialize),-1);

	rb_undef_method(rb_cSFMLRenderTexture,"initialize_copy");
	rb_undef_method(rb_cSFMLRenderTexture,"_load");
	rb_undef_method(rb_cSFMLRenderTexture,"_dump");

	rb_define_method(rb_cSFMLRenderTexture,"display",RUBY_METHOD_FUNC(_display),0);

	rb_define_attr_method(rb_cSFMLRenderTexture,"smooth",_getSmooth,_setSmooth);
	rb_define_attr_method(rb_cSFMLRenderTexture,"repeated",_getRepeated,_setRepeated);

}







