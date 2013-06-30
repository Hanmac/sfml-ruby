/*
 * RenderTarget.hpp
 *
 *  Created on: 15.06.2013
 *      Author: hanmac
 */

#ifndef RENDERTARGET_HPP_
#define RENDERTARGET_HPP_

#include "main.hpp"

extern VALUE rb_mSFMLRenderTarget;
void Init_SFMLRenderTarget(VALUE rb_mSFML);

//template <>
//VALUE wrap< sf::RenderTarget >(sf::RenderTarget *image );

void add_rendertarget(sf::RenderTarget*, VALUE val);

template <>
sf::RenderTarget* unwrap< sf::RenderTarget* >(const VALUE &vimage);

#endif /* RENDERTARGET_HPP_ */
