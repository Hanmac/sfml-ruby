/*
 * SoundStream.hpp
 *
 *  Created on: 28.10.2013
 *      Author: hanmac
 */

#ifndef SOUNDSTREAM_HPP_
#define SOUNDSTREAM_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLSoundStream;
void Init_SFMLSoundStream(VALUE rb_mSFML);

template <>
sf::SoundStream* unwrap< sf::SoundStream* >(const VALUE &vimage);

template <>
sf::SoundStream& unwrap< sf::SoundStream& >(const VALUE &vimage);

#endif /* SOUNDSTREAM_HPP_ */
