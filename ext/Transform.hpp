/*
 * Transform.hpp
 *
 *  Created on: 30.06.2013
 *      Author: hanmac
 */

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_


#include "main.hpp"

extern VALUE rb_cSFMLTransform;
void Init_SFMLTransform(VALUE rb_mSFML);

template <>
VALUE wrap< sf::Transform >(sf::Transform *color );

template <>
sf::Transform* unwrap< sf::Transform* >(const VALUE &vcolor);

template <>
const sf::Transform& unwrap< const sf::Transform& >(const VALUE &vcolor);



#endif /* TRANSFORM_HPP_ */
