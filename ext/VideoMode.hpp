/*
 * VideoMode.hpp
 *
 *  Created on: 21.06.2013
 *      Author: hanmac
 */

#ifndef VIDEOMODE_HPP_
#define VIDEOMODE_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLVideoMode;
void Init_SFMLVideoMode(VALUE rb_mSFML);

template <>
VALUE wrap< sf::VideoMode >(sf::VideoMode *color );

template <>
sf::VideoMode* unwrap< sf::VideoMode* >(const VALUE &vcolor);

template <>
sf::VideoMode unwrap< sf::VideoMode >(const VALUE &vcolor);



#endif /* VIDEOMODE_HPP_ */
