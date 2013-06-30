/*
 * Vector3.hpp
 *
 *  Created on: 30.06.2013
 *      Author: hanmac
 */

#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_


#include "main.hpp"

extern VALUE rb_cSFMLVector3;
void Init_SFMLVector3(VALUE rb_mSFML);

template <>
VALUE wrap< sf::Vector3f >(sf::Vector3f *color );

template <>
VALUE wrap< sf::Vector3i >(const sf::Vector3i& color );

template <>
bool is_wrapable< sf::Vector3f >(const VALUE &vcolor);

template <>
sf::Vector3f* unwrap< sf::Vector3f* >(const VALUE &vcolor);

template <>
sf::Vector3f unwrap< sf::Vector3f >(const VALUE &vcolor);

template <>
sf::Vector3i unwrap< sf::Vector3i >(const VALUE &vcolor);


#endif /* VECTOR3_HPP_ */
