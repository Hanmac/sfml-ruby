/*
 * Texture.hpp
 *
 *  Created on: 12.06.2013
 *      Author: hanmac
 */

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLTexture;
void Init_SFMLTexture(VALUE rb_mSFML);

template <>
VALUE wrap< sf::Texture >(sf::Texture *image );

template <>
sf::Texture* unwrap< sf::Texture* >(const VALUE &vimage);

template <>
sf::Texture& unwrap< sf::Texture& >(const VALUE &vimage);

#endif /* TEXTURE_HPP_ */
