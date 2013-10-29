/*
 * Sound.cpp
 *
 *  Created on: 28.10.2013
 *      Author: hanmac
 */

#include "SoundSource.hpp"
#include "SoundBuffer.hpp"
#include "Sound.hpp"
#include "Time.hpp"

#define _self unwrap<sf::Sound*>(self)

VALUE rb_cSFMLSound;

template <>
VALUE wrap< sf::Sound >(sf::Sound *image )
{
	return Data_Wrap_Struct(rb_cSFMLSound, NULL, free, image);
}

template <>
sf::Sound* unwrap< sf::Sound* >(const VALUE &vimage)
{
	return unwrapPtr<sf::Sound>(vimage, rb_cSFMLSound);
}

template <>
sf::Sound& unwrap< sf::Sound& >(const VALUE &vimage)
{
	return *unwrap<sf::Sound*>(vimage);
}


namespace RubySFML {
namespace Sound {

VALUE _alloc(VALUE self) {
	return wrap(new sf::Sound);
}

macro_attr(Loop,bool)
macro_attr(PlayingOffset,sf::Time)

singlefunc(play)
singlefunc(pause)
singlefunc(stop)

/*
*/
VALUE _initialize(VALUE self, VALUE buffer)
{
	//VALUE result = rb_call_super(1,&other);
	_self->setBuffer(unwrap<sf::SoundBuffer&>(buffer));

	return self;
}

/*
 *
 */
VALUE _getStatus(VALUE self)
{
	return wrapenum(_self->getStatus());
}

}
}

void Init_SFMLSound(VALUE rb_mSFML)
{
	using namespace RubySFML::Sound;

#if 0
	rb_mSFML = rb_define_module("SFML");

#endif

	rb_cSFMLSound = rb_define_class_under(rb_mSFML,"Sound",rb_cSFMLSoundSource);

	rb_define_alloc_func(rb_cSFMLSound,_alloc);

	rb_define_method(rb_cSFMLSound,"initialize",RUBY_METHOD_FUNC(_initialize),1);

	rb_define_attr_method(rb_cSFMLSound,"loop",_getLoop,_setLoop);
	rb_define_attr_method(rb_cSFMLSound,"playing_offset",_getPlayingOffset,_setPlayingOffset);


	rb_undef_method(rb_cSFMLSound,"_dump");
	rb_undef_method(rb_cSFMLSound,"_load");

	rb_define_method(rb_cSFMLSound,"play",RUBY_METHOD_FUNC(_play),0);
	rb_define_method(rb_cSFMLSound,"pause",RUBY_METHOD_FUNC(_pause),0);
	rb_define_method(rb_cSFMLSound,"stop",RUBY_METHOD_FUNC(_stop),0);

	rb_define_method(rb_cSFMLSound,"status",RUBY_METHOD_FUNC(_getStatus),0);
}

