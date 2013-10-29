/*
 * SoundSource.cpp
 *
 *  Created on: 28.10.2013
 *      Author: hanmac
 */

#include "SoundSource.hpp"

#define _self unwrap<sf::SoundSource*>(self)

VALUE rb_cSFMLSoundSource;

template <>
VALUE wrap< sf::SoundSource >(sf::SoundSource *image )
{
	return Data_Wrap_Struct(rb_cSFMLSoundSource, NULL, NULL, image);
}

template <>
sf::SoundSource* unwrap< sf::SoundSource* >(const VALUE &vimage)
{
	return unwrapPtr<sf::SoundSource>(vimage, rb_cSFMLSoundSource);
}

template <>
sf::SoundSource& unwrap< sf::SoundSource& >(const VALUE &vimage)
{
	return *unwrap<sf::SoundSource*>(vimage);
}


namespace RubySFML {
namespace SoundSource {

macro_attr(Pitch,float)
macro_attr(Volume,float)
macro_attr(Position,sf::Vector3f)
macro_attr_bool(RelativeToListener)
macro_attr(MinDistance,float)
macro_attr(Attenuation,float)


/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);

	_setPitch(self,_getPitch(other));
	_setVolume(self,_getVolume(other));
	_setPosition(self,_getPosition(other));

	_setRelativeToListener(self,_getRelativeToListener(other));
	_setMinDistance(self,_getMinDistance(other));
	_setAttenuation(self,_getAttenuation(other));

	return result;
}

}
}

void Init_SFMLSoundSource(VALUE rb_mSFML)
{
	using namespace RubySFML::SoundSource;

#if 0
	rb_mSFML = rb_define_module("SFML");

#endif

	rb_cSFMLSoundSource = rb_define_class_under(rb_mSFML,"SoundSource",rb_cObject);

	rb_undef_alloc_func(rb_cSFMLSoundSource);

	rb_undef_method(rb_cSFMLSoundSource,"initialize");

	rb_define_method(rb_cSFMLSoundSource,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);

	rb_undef_method(rb_cSFMLSoundSource,"_dump");
	rb_undef_method(rb_cSFMLSoundSource,"_load");


	registerEnum<sf::SoundSource::Status>("sf::SoundSouce::Status")
		->add(sf::SoundSource::Stopped,"stopped")
		->add(sf::SoundSource::Paused,"paused")
		->add(sf::SoundSource::Playing,"playing");
}

