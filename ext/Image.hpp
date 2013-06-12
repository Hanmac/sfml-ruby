/*
 * Image.hpp
 *
 *  Created on: 11.06.2013
 *      Author: hanmac
 */

#ifndef IMAGE_HPP_
#define IMAGE_HPP_


#include "main.hpp"

extern VALUE rb_cSFMLImage;
void Init_SFMLImage(VALUE rb_mSFML);

template <>
VALUE wrap< sf::Image >(sf::Image *image );

template <>
sf::Image* unwrap< sf::Image* >(const VALUE &vimage);

template <>
sf::Image& unwrap< sf::Image& >(const VALUE &vimage);



#endif /* IMAGE_HPP_ */
