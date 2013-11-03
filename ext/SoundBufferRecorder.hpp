/*
 * SoundBufferRecorder.hpp
 *
 *  Created on: 31.10.2013
 *      Author: hanmac
 */

#ifndef SOUNDBUFFERRECORDER_HPP_
#define SOUNDBUFFERRECORDER_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLSoundBufferRecorder;
void Init_SFMLSoundBufferRecorder(VALUE rb_mSFML);

template <>
VALUE wrap< sf::SoundBufferRecorder >(sf::SoundBufferRecorder *image );

template <>
sf::SoundBufferRecorder* unwrap< sf::SoundBufferRecorder* >(const VALUE &vimage);

template <>
sf::SoundBufferRecorder& unwrap< sf::SoundBufferRecorder& >(const VALUE &vimage);

#endif /* SOUNDBUFFERRECORDER_HPP_ */
