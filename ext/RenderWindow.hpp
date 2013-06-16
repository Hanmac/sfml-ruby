/*
 * RenderRenderWindow.hpp
 *
 *  Created on: 16.06.2013
 *      Author: hanmac
 */

#ifndef RENDERWINDOW_HPP_
#define RENDERWINDOW_HPP_


#include "main.hpp"

extern VALUE rb_cSFMLRenderWindow;
void Init_SFMLRenderWindow(VALUE rb_mSFML);

template <>
VALUE wrap< sf::RenderWindow >(sf::RenderWindow *image );

template <>
sf::RenderWindow* unwrap< sf::RenderWindow* >(const VALUE &vimage);

#endif /* RENDERWINDOW_HPP_ */
