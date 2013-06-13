/*
 * View.hpp
 *
 *  Created on: 12.06.2013
 *      Author: hanmac
 */

#ifndef VIEW_HPP_
#define VIEW_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLView;
void Init_SFMLView(VALUE rb_mSFML);

template <>
VALUE wrap< sf::View >(sf::View *image );

template <>
sf::View* unwrap< sf::View* >(const VALUE &vimage);

template <>
sf::View& unwrap< sf::View& >(const VALUE &vimage);

#endif /* VIEW_HPP_ */
