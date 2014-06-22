/*
 * SoundBufferRecorder.cpp
 *
 *  Created on: 31.10.2013
 *      Author: hanmac
 */

#include "SoundBufferRecorder.hpp"
#include "SoundRecorder.hpp"

#define _self unwrap<sf::SoundBufferRecorder*>(self)

VALUE rb_cSFMLSoundBufferRecorder;

macro_template2(sf::SoundBufferRecorder,NULL,rb_cSFMLSoundBufferRecorder)

namespace RubySFML {
namespace SoundBufferRecorder {

macro_alloc(sf::SoundBufferRecorder)

}
}

void Init_SFMLSoundBufferRecorder(VALUE rb_mSFML)
{
	using namespace RubySFML::SoundBufferRecorder;

#if 0
	rb_mSFML = rb_define_module("SFML");

#endif

	rb_cSFMLSoundBufferRecorder = rb_define_class_under(rb_mSFML,"SoundBufferRecorder",rb_cSFMLSoundRecorder);

	rb_define_alloc_func(rb_cSFMLSoundBufferRecorder,_alloc);


}

