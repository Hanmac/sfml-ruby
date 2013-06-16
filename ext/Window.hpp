/*
 * Window.hpp
 *
 *  Created on: 15.06.2013
 *      Author: hanmac
 */

#ifndef WINDOW_HPP_
#define WINDOW_HPP_


#include "main.hpp"

extern VALUE rb_cSFMLWindow;
void Init_SFMLWindow(VALUE rb_mSFML);

template <>
VALUE wrap< sf::Window >(sf::Window *image );

template <>
sf::Window* unwrap< sf::Window* >(const VALUE &vimage);


#endif /* WINDOW_HPP_ */
