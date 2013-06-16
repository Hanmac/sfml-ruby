/*
 * Sprite.hpp
 *
 *  Created on: 15.06.2013
 *      Author: hanmac
 */

#ifndef SPRITE_HPP_
#define SPRITE_HPP_


#include "main.hpp"

extern VALUE rb_cSFMLSprite;
void Init_SFMLSprite(VALUE rb_mSFML);

template <>
VALUE wrap< sf::Sprite >(sf::Sprite *image );

template <>
sf::Sprite* unwrap< sf::Sprite* >(const VALUE &vimage);

template <>
sf::Sprite& unwrap< sf::Sprite& >(const VALUE &vimage);

#endif /* SPRITE_HPP_ */
