/*
 * SoundRecorder.hpp
 *
 *  Created on: 31.10.2013
 *      Author: hanmac
 */

#ifndef SOUNDRECORDER_HPP_
#define SOUNDRECORDER_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLSoundRecorder;
void Init_SFMLSoundRecorder(VALUE rb_mSFML);

template <>
sf::SoundRecorder* unwrap< sf::SoundRecorder* >(const VALUE &vimage);

template <>
sf::SoundRecorder& unwrap< sf::SoundRecorder& >(const VALUE &vimage);

#endif /* SOUNDRECORDER_HPP_ */
