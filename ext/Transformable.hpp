/*
 * Transformable.hpp
 *
 *  Created on: 16.06.2013
 *      Author: hanmac
 */

#ifndef TRANSFORMABLE_HPP_
#define TRANSFORMABLE_HPP_


#include "main.hpp"

extern VALUE rb_cSFMLTransformable;
void Init_SFMLTransformable(VALUE rb_mSFML);

template <>
VALUE wrap< sf::Transformable >(sf::Transformable *image );

template <>
sf::Transformable* unwrap< sf::Transformable* >(const VALUE &vimage);

template <>
sf::Transformable& unwrap< sf::Transformable& >(const VALUE &vimage);

#endif /* TRANSFORMABLE_HPP_ */
