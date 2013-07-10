/*
 * RectangleShape.hpp
 *
 *  Created on: 10.07.2013
 *      Author: hanmac
 */

#ifndef RECTANGLESHAPE_HPP_
#define RECTANGLESHAPE_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLRectangleShape;
void Init_SFMLRectangleShape(VALUE rb_mSFML);

template <>
VALUE wrap< sf::RectangleShape >(sf::RectangleShape *image );

template <>
sf::RectangleShape* unwrap< sf::RectangleShape* >(const VALUE &vimage);

template <>
sf::RectangleShape& unwrap< sf::RectangleShape& >(const VALUE &vimage);

#endif /* RECTANGLESHAPE_HPP_ */
