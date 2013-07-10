/*
 * Shape.hpp
 *
 *  Created on: 10.07.2013
 *      Author: hanmac
 */

#ifndef SHAPE_HPP_
#define SHAPE_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLShape;
void Init_SFMLShape(VALUE rb_mSFML);

template <>
sf::Shape* unwrap< sf::Shape* >(const VALUE &vimage);

template <>
sf::Shape& unwrap< sf::Shape& >(const VALUE &vimage);

#endif /* SHAPE_HPP_ */
