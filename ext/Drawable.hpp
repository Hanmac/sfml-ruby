/*
 * Drawable.hpp
 *
 *  Created on: 16.06.2013
 *      Author: hanmac
 */

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_


#include "main.hpp"

extern VALUE rb_mSFMLDrawable;
void Init_SFMLDrawable(VALUE rb_mSFML);

template <>
sf::Drawable* unwrap< sf::Drawable* >(const VALUE &vimage);

template <>
sf::Drawable& unwrap< sf::Drawable& >(const VALUE &vimage);

#endif /* DRAWABLE_HPP_ */
