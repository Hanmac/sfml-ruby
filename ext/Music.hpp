/*
 * Music.hpp
 *
 *  Created on: 28.10.2013
 *      Author: hanmac
 */

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLMusic;
void Init_SFMLMusic(VALUE rb_mSFML);

template <>
sf::Music* unwrap< sf::Music* >(const VALUE &vimage);

template <>
sf::Music& unwrap< sf::Music& >(const VALUE &vimage);

#endif /* MUSIC_HPP_ */
