/*
 * RenderTarget.cpp
 *
 *  Created on: 15.06.2013
 *      Author: hanmac
 */

#include "Window.hpp"
#include "RenderTarget.hpp"
#include "View.hpp"
#include "Vector2.hpp"
#include "Color.hpp"

#include "Drawable.hpp"

#define _self unwrap<sf::RenderTarget*>(self)

VALUE rb_mSFMLRenderTarget;

template <>
sf::RenderTarget* unwrap< sf::RenderTarget* >(const VALUE &vimage)
{
	return unwrap< sf::RenderWindow* >(vimage);
}


namespace RubySFML {
namespace RenderTarget {

macro_attr(View,sf::View)

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

	_self->draw(unwrap<sf::Drawable&>(draw));

	return self;
}


VALUE _push_gl(VALUE self)
{
	_self->pushGLStates();

	if(rb_block_given_p())
	{
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
	_self->popGLStates();

	return self;
}

}
}

void Init_SFMLRenderTarget(VALUE rb_mSFML)
{
	using namespace RubySFML::RenderTarget;


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







