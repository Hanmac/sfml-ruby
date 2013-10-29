/*
 * SoundBuffer.hpp
 *
 *  Created on: 27.10.2013
 *      Author: hanmac
 */

#ifndef SOUNDBUFFER_HPP_
#define SOUNDBUFFER_HPP_


#include "main.hpp"

extern VALUE rb_cSFMLSoundBuffer;
void Init_SFMLSoundBuffer(VALUE rb_mSFML);

template <>
VALUE wrap< sf::SoundBuffer >(sf::SoundBuffer *image );

template <>
sf::SoundBuffer* unwrap< sf::SoundBuffer* >(const VALUE &vimage);

template <>
sf::SoundBuffer& unwrap< sf::SoundBuffer& >(const VALUE &vimage);

#endif /* SOUNDBUFFER_HPP_ */
