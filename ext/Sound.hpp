/*
 * Sound.hpp
 *
 *  Created on: 28.10.2013
 *      Author: hanmac
 */

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLSound;
void Init_SFMLSound(VALUE rb_mSFML);

template <>
sf::Sound* unwrap< sf::Sound* >(const VALUE &vimage);

template <>
sf::Sound& unwrap< sf::Sound& >(const VALUE &vimage);

#endif /* SOUND_HPP_ */
