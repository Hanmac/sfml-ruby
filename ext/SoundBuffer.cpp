/*
 * SoundBuffer.cpp
 *
 *  Created on: 27.10.2013
 *      Author: hanmac
 */

#include "SoundBuffer.hpp"

#define _self unwrap<sf::SoundBuffer*>(self)

VALUE rb_cSFMLSoundBuffer;

template <>
VALUE wrap< sf::SoundBuffer >(sf::SoundBuffer *image )
{
	return Data_Wrap_Struct(rb_cSFMLSoundBuffer, NULL, free, image);
}

template <>
sf::SoundBuffer* unwrap< sf::SoundBuffer* >(const VALUE &vimage)
{
	return unwrapPtr<sf::SoundBuffer>(vimage, rb_cSFMLSoundBuffer);
}

template <>
sf::SoundBuffer& unwrap< sf::SoundBuffer& >(const VALUE &vimage)
{
	return *unwrap<sf::SoundBuffer*>(vimage);
}


namespace RubySFML {
namespace SoundBuffer {


VALUE _alloc(VALUE self) {
	return wrap(new sf::SoundBuffer);
}

singlereturn(getSampleRate)
singlereturn(getChannelCount)
singlereturn(getDuration)
/*
 *
 */
VALUE _classloadFile(VALUE self,VALUE path)
{
	sf::SoundBuffer *buffer = new sf::SoundBuffer;

	if(buffer->loadFromFile(unwrap<std::string>(path)))
		return wrap(buffer);
	return Qnil;
}

/*
 *
 */
VALUE _loadFile(VALUE self,VALUE path)
{
	return wrap(_self->loadFromFile(unwrap<std::string>(path)));
}

/*
 *
 */
VALUE _each_sample_size(VALUE self)
{
	return wrap(_self->getSampleCount());
}

/*
 *
 */
VALUE _each_sample(VALUE self)
{
	RETURN_SIZED_ENUMERATOR(self,0,NULL,_each_sample_size);

	std::size_t count = _self->getSampleCount();

	const sf::Int16 *samples = _self->getSamples();

	for(std::size_t i = 0; i < count; ++i)
	{
		rb_yield(INT2FIX(samples[i]));
	}

	return self;
}

}
}

void Init_SFMLSoundBuffer(VALUE rb_mSFML)
{
	using namespace RubySFML::SoundBuffer;

#if 0
	rb_mSFML = rb_define_module("SFML");

#endif

	rb_cSFMLSoundBuffer = rb_define_class_under(rb_mSFML,"SoundBuffer",rb_cObject);

	rb_define_alloc_func(rb_cSFMLSoundBuffer,_alloc);

	rb_undef_method(rb_cSFMLSoundBuffer,"initialize");
	rb_undef_method(rb_cSFMLSoundBuffer,"initialize_copy");
	rb_undef_method(rb_cSFMLSoundBuffer,"_load");

	rb_define_method(rb_cSFMLSoundBuffer,"load_file",RUBY_METHOD_FUNC(_loadFile),1);
	rb_define_singleton_method(rb_cSFMLSoundBuffer,"load_file",RUBY_METHOD_FUNC(_classloadFile),1);

	rb_define_method(rb_cSFMLSoundBuffer,"each_sample",RUBY_METHOD_FUNC(_each_sample),0);

	rb_define_method(rb_cSFMLSoundBuffer,"sample_rate",RUBY_METHOD_FUNC(_getSampleRate),0);
	rb_define_method(rb_cSFMLSoundBuffer,"channel_count",RUBY_METHOD_FUNC(_getChannelCount),0);
	rb_define_method(rb_cSFMLSoundBuffer,"duration",RUBY_METHOD_FUNC(_getDuration),0);
}



