/*
 * RenderTarget.cpp
 *
 *  Created on: 15.06.2013
 *      Author: hanmac
 */

#include <map>

#include "Window.hpp"
#include "RenderTarget.hpp"
#include "RenderState.hpp"
#include "RenderWindow.hpp"
#include "RenderTexture.hpp"
#include "View.hpp"
#include "Vector2.hpp"
#include "Color.hpp"
#include "View.hpp"
#include "Drawable.hpp"

#define _self unwrap<sf::RenderTarget*>(self)

VALUE rb_mSFMLRenderTarget;


typedef std::map<sf::RenderTarget*,VALUE> renderholdertype;
renderholdertype renderholder;

void add_rendertarget(sf::RenderTarget* taget, VALUE val)
{
	rb_global_variable(&val);
	renderholder.insert(std::make_pair(taget,val));
}

template <>
VALUE wrap< sf::RenderTarget >(sf::RenderTarget *image )
{
	renderholdertype::iterator it = renderholder.find(image);
	if(it != renderholder.end())
		return it->second;

	VALUE result = Qnil;

	if(sf::RenderWindow *win = dynamic_cast<sf::RenderWindow*>(image))
		result = wrap(win);
	else if(sf::RenderTexture *tex = dynamic_cast<sf::RenderTexture*>(image))
		result = wrap(tex);
	if(!NIL_P(result))
		add_rendertarget(image,result);

	return result;
}


template <>
sf::RenderTarget* unwrap< sf::RenderTarget* >(const VALUE &vimage)
{
	if(rb_obj_is_kind_of(vimage, rb_cSFMLRenderWindow))
		return unwrap< sf::RenderWindow* >(vimage);
	if(rb_obj_is_kind_of(vimage, rb_cSFMLRenderTexture))
		return unwrap< sf::RenderTexture* >(vimage);

	return unwrapPtr< sf::RenderTarget >(vimage,rb_mSFMLRenderTarget);
}


namespace RubySFML {
namespace RenderTarget {

macro_attr(View,sf::View&)

VALUE _clear(int argc,VALUE *argv,VALUE self)
{
	VALUE color;
	rb_scan_args(argc, argv, "01",&color);

	if(NIL_P(color))
		_self->clear();
	else
		_self->clear(unwrap<sf::Color>(color));

	return self;
}

VALUE _getDefaultView(VALUE self)
{
	return wrap(_self->getDefaultView());
}

VALUE _mapPixelToCoords(int argc,VALUE *argv,VALUE self)
{
	VALUE point, view;
	rb_scan_args(argc, argv, "11", &point, &view);

	const sf::View *cview = NIL_P(view) ? &_self->getView() :  unwrap<sf::View*>(view);

	return wrap(_self->mapPixelToCoords(unwrap<sf::Vector2i>(point),*cview));
}

VALUE _mapCoordsToPixel(int argc,VALUE *argv,VALUE self)
{
	VALUE point, view;
	rb_scan_args(argc, argv, "11", &point, &view);

	const sf::View *cview = NIL_P(view) ? &_self->getView() :  unwrap<sf::View*>(view);

	return wrap(_self->mapCoordsToPixel(unwrap<sf::Vector2f>(point),*cview));

}

VALUE _draw(int argc,VALUE *argv,VALUE self)
{
	VALUE draw, states;
	rb_scan_args(argc, argv, "11", &draw, &states);

	_self->draw(unwrap<sf::Drawable&>(draw),unwrap<sf::RenderStates>(states));

	return self;
}


VALUE _push_gl(VALUE self)
{
	_self->pushGLStates();

	if(rb_block_given_p())
	{
		rb_yield(Qnil);
		_self->popGLStates();
	}

	return self;
}

VALUE _pop_gl(VALUE self)
{
	_self->popGLStates();

	return self;
}

VALUE _reset_gl(VALUE self)
{
	_self->resetGLStates();

	return self;
}

}
}

void Init_SFMLRenderTarget(VALUE rb_mSFML)
{
	using namespace RubySFML::RenderTarget;

#if 0
	rb_mSFML = rb_define_module("SFML");
#endif

	rb_mSFMLRenderTarget = rb_define_module_under(rb_mSFML,"RenderTarget");

	rb_define_attr_method(rb_mSFMLRenderTarget,"view",_getView,_setView);

	rb_define_method(rb_mSFMLRenderTarget,"clear",RUBY_METHOD_FUNC(_clear),-1);

	rb_define_method(rb_mSFMLRenderTarget,"default_view",RUBY_METHOD_FUNC(_getDefaultView),0);

	rb_define_method(rb_mSFMLRenderTarget,"pixel_to_coords",RUBY_METHOD_FUNC(_mapPixelToCoords),0);
	rb_define_method(rb_mSFMLRenderTarget,"coords_to_pixel",RUBY_METHOD_FUNC(_mapCoordsToPixel),0);

	rb_define_method(rb_mSFMLRenderTarget,"draw",RUBY_METHOD_FUNC(_draw),-1);

	rb_define_method(rb_mSFMLRenderTarget,"push_gl",RUBY_METHOD_FUNC(_push_gl),0);
	rb_define_method(rb_mSFMLRenderTarget,"pop_gl",RUBY_METHOD_FUNC(_pop_gl),0);
	rb_define_method(rb_mSFMLRenderTarget,"reset_gl",RUBY_METHOD_FUNC(_push_gl),0);

}







