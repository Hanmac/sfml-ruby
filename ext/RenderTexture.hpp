/*
 * RenderTexture.hpp
 *
 *  Created on: 30.06.2013
 *      Author: hanmac
 */

#ifndef RENDERTEXTURE_HPP_
#define RENDERTEXTURE_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLRenderTexture;
void Init_SFMLRenderTexture(VALUE rb_mSFML);

template <>
VALUE wrap< sf::RenderTexture >(sf::RenderTexture *image );

template <>
sf::RenderTexture* unwrap< sf::RenderTexture* >(const VALUE &vimage);

#endif /* RENDERTEXTURE_HPP_ */
