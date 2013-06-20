/*
 * Rect.hpp
 *
 *  Created on: 12.06.2013
 *      Author: hanmac
 */

#ifndef RECT_HPP_
#define RECT_HPP_


#include "main.hpp"

extern VALUE rb_cSFMLRect;
void Init_SFMLRect(VALUE rb_mSFML);

template <>
VALUE wrap< sf::FloatRect >(sf::FloatRect *color );

template <>
VALUE wrap< sf::IntRect >(const sf::IntRect& color );

template <>
bool is_wrapable< sf::FloatRect >(const VALUE &vcolor);

template <>
sf::FloatRect* unwrap< sf::FloatRect* >(const VALUE &vcolor);

template <>
sf::FloatRect unwrap< sf::FloatRect >(const VALUE &vcolor);


template <>
sf::IntRect unwrap< sf::IntRect >(const VALUE &vcolor);



#endif /* RECT_HPP_ */
