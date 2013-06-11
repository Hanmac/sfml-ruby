/*
 * Color.hpp
 *
 *  Created on: 09.06.2013
 *      Author: hanmac
 */

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLColor;
void Init_SFMLColor(VALUE rb_mSFML);


template <>
VALUE wrap< sf::Color >(sf::Color *color );

template <>
bool is_wrapable< sf::Color >(const VALUE &vcolor);

template <>
sf::Color* unwrap< sf::Color* >(const VALUE &vcolor);

template <>
sf::Color unwrap< sf::Color >(const VALUE &vcolor);


#endif /* COLOR_HPP_ */
