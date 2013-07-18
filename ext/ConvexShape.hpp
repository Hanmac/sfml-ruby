/*
 * ConvexShape.hpp
 *
 *  Created on: 18.07.2013
 *      Author: hanmac
 */

#ifndef CONVEXSHAPE_HPP_
#define CONVEXSHAPE_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLConvexShape;
void Init_SFMLConvexShape(VALUE rb_mSFML);

template <>
VALUE wrap< sf::ConvexShape >(sf::ConvexShape *image );

template <>
sf::ConvexShape* unwrap< sf::ConvexShape* >(const VALUE &vimage);

template <>
sf::ConvexShape& unwrap< sf::ConvexShape& >(const VALUE &vimage);

#endif /* CONVEXSHAPE_HPP_ */
