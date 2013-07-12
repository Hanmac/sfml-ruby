/*
 * CircleShape.hpp
 *
 *  Created on: 10.07.2013
 *      Author: hanmac
 */

#ifndef CIRCLESHAPE_HPP_
#define CIRCLESHAPE_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLCircleShape;
void Init_SFMLCircleShape(VALUE rb_mSFML);

template <>
VALUE wrap< sf::CircleShape >(sf::CircleShape *image );

template <>
sf::CircleShape* unwrap< sf::CircleShape* >(const VALUE &vimage);

template <>
sf::CircleShape& unwrap< sf::CircleShape& >(const VALUE &vimage);

#endif /* CIRCLESHAPE_HPP_ */
