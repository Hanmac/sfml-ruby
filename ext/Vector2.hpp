/*
 * Vector2.hpp
 *
 *  Created on: 09.06.2013
 *      Author: hanmac
 */

#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLVector2;
void Init_SFMLVector2(VALUE rb_mSFML);

template <>
VALUE wrap< sf::Vector2f >(sf::Vector2f *color );

template <>
VALUE wrap< sf::Vector2u >(const sf::Vector2u& color );

template <>
VALUE wrap< sf::Vector2i >(const sf::Vector2i& color );

template <>
bool is_wrapable< sf::Vector2f >(const VALUE &vcolor);

template <>
sf::Vector2f* unwrap< sf::Vector2f* >(const VALUE &vcolor);

template <>
sf::Vector2f unwrap< sf::Vector2f >(const VALUE &vcolor);

template <>
sf::Vector2u unwrap< sf::Vector2u >(const VALUE &vcolor);

template <>
sf::Vector2i unwrap< sf::Vector2i >(const VALUE &vcolor);


#endif /* VECTOR2_HPP_ */
