/*
 * SoundSource.hpp
 *
 *  Created on: 28.10.2013
 *      Author: hanmac
 */

#ifndef SOUNDSOURCE_HPP_
#define SOUNDSOURCE_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLSoundSource;
void Init_SFMLSoundSource(VALUE rb_mSFML);

template <>
sf::SoundSource* unwrap< sf::SoundSource* >(const VALUE &vimage);

template <>
sf::SoundSource& unwrap< sf::SoundSource& >(const VALUE &vimage);

#endif /* SOUNDSOURCE_HPP_ */
