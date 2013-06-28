/*
 * Text.hpp
 *
 *  Created on: 27.06.2013
 *      Author: hanmac
 */

#ifndef TEXT_HPP_
#define TEXT_HPP_


#include "main.hpp"

extern VALUE rb_cSFMLText;
void Init_SFMLText(VALUE rb_mSFML);

template <>
VALUE wrap< sf::Text >(sf::Text *image );

template <>
sf::Text* unwrap< sf::Text* >(const VALUE &vimage);

template <>
sf::Text& unwrap< sf::Text& >(const VALUE &vimage);



#endif /* TEXT_HPP_ */
