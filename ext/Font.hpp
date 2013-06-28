/*
 * Font.hpp
 *
 *  Created on: 26.06.2013
 *      Author: hanmac
 */

#ifndef FONT_HPP_
#define FONT_HPP_


#include "main.hpp"

extern VALUE rb_cSFMLFont;
void Init_SFMLFont(VALUE rb_mSFML);

template <>
VALUE wrap< sf::Font >(sf::Font *image );

template <>
sf::Font* unwrap< sf::Font* >(const VALUE &vimage);

template <>
sf::Font& unwrap< sf::Font& >(const VALUE &vimage);



#endif /* FONT_HPP_ */
