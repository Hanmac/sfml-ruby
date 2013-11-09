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

template <>
VALUE wrap< sf::SoundBufferRecorder >(sf::SoundBufferRecorder *image )
{
	return Data_Wrap_Struct(rb_cSFMLSoundBufferRecorder, NULL, NULL, image);
}

template <>
sf::SoundBufferRecorder* unwrap< sf::SoundBufferRecorder* >(const VALUE &vimage)
{
	return unwrapPtr<sf::SoundBufferRecorder>(vimage, rb_cSFMLSoundBufferRecorder);
}

template <>
sf::SoundBufferRecorder& unwrap< sf::SoundBufferRecorder& >(const VALUE &vimage)
{
	return *unwrap<sf::SoundBufferRecorder*>(vimage);
}


namespace RubySFML {
namespace SoundBufferRecorder {

VALUE _alloc(VALUE self) {
	return wrap(new sf::SoundBufferRecorder);
}

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

