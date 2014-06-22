/*
 * SoundStream.cpp
 *
 *  Created on: 28.10.2013
 *      Author: hanmac
 */

#include "SoundStream.hpp"
#include "SoundSource.hpp"
#include "Time.hpp"

#define _self unwrap<sf::SoundStream*>(self)

VALUE rb_cSFMLSoundStream;

macro_template2(sf::SoundStream,NULL,rb_cSFMLSoundStream)

namespace RubySFML {
namespace SoundStream {

macro_attr(Loop,bool)
macro_attr(PlayingOffset,sf::Time)

singlefunc(play)
singlefunc(pause)
singlefunc(stop)

singlereturn(getSampleRate)
singlereturn(getChannelCount)

}
}

void Init_SFMLSoundStream(VALUE rb_mSFML)
{
	using namespace RubySFML::SoundStream;

#if 0
	rb_mSFML = rb_define_module("SFML");

#endif

	rb_cSFMLSoundStream = rb_define_class_under(rb_mSFML,"SoundStream",rb_cSFMLSoundSource);

	rb_undef_alloc_func(rb_cSFMLSoundStream);

	rb_undef_method(rb_cSFMLSoundStream,"initialize");

	rb_undef_method(rb_cSFMLSoundStream,"_dump");
	rb_undef_method(rb_cSFMLSoundStream,"_load");

	rb_define_method(rb_cSFMLSoundStream,"play",RUBY_METHOD_FUNC(_play),0);
	rb_define_method(rb_cSFMLSoundStream,"pause",RUBY_METHOD_FUNC(_pause),0);
	rb_define_method(rb_cSFMLSoundStream,"stop",RUBY_METHOD_FUNC(_stop),0);

	rb_define_method(rb_cSFMLSoundStream,"sample_rate",RUBY_METHOD_FUNC(_getSampleRate),0);
	rb_define_method(rb_cSFMLSoundStream,"channel_count",RUBY_METHOD_FUNC(_getChannelCount),0);

}


