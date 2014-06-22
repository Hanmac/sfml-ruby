/*
 * SoundBuffer.cpp
 *
 *  Created on: 27.10.2013
 *      Author: hanmac
 */

#include "SoundBuffer.hpp"
#include "SoundBufferRecorder.hpp"

#define _self unwrap<sf::SoundBuffer*>(self)

VALUE rb_cSFMLSoundBuffer;

template <>
VALUE wrap< sf::SoundBuffer >(sf::SoundBuffer *image )
{
	return Data_Wrap_Struct(rb_cSFMLSoundBuffer, NULL, NULL, image);
}

template <>
sf::SoundBuffer* unwrap< sf::SoundBuffer* >(const VALUE &vimage)
{
	if(rb_obj_is_kind_of(vimage,rb_cSFMLSoundBufferRecorder))
	{
		return &const_cast<sf::SoundBuffer&>(unwrap<sf::SoundBufferRecorder*>(vimage)->getBuffer());
	}

	return unwrapPtr<sf::SoundBuffer>(vimage, rb_cSFMLSoundBuffer);
}

template <>
sf::SoundBuffer& unwrap< sf::SoundBuffer& >(const VALUE &vimage)
{
	if(rb_obj_is_kind_of(vimage,rb_cSFMLSoundBufferRecorder))
	{
		return const_cast<sf::SoundBuffer&>(unwrap<sf::SoundBufferRecorder*>(vimage)->getBuffer());
	}

	return *unwrap<sf::SoundBuffer*>(vimage);
}


namespace RubySFML {
namespace SoundBuffer {

macro_alloc(sf::SoundBuffer)

singlereturn(getSampleRate)
singlereturn(getChannelCount)
singlereturn(getDuration)


/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	*_self = *unwrap<sf::SoundBuffer*>(other);
	return result;
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
VALUE _classloadFile(VALUE self,VALUE path)
{
	VALUE buffer = _alloc(self);

	if(RTEST(_loadFile(buffer,path)))
		return buffer;
	return Qnil;
}

/*
 *
 */
VALUE _loadMemory(VALUE self,VALUE memory)
{
	StringValue(memory);
	return wrap(_self->loadFromMemory(RSTRING_PTR(memory), RSTRING_LEN(memory)));
}

/*
 *
 */
VALUE _classloadMemory(VALUE self,VALUE memory)
{
	VALUE buffer = _alloc(self);

	if(RTEST(_loadMemory(buffer,memory)))
		return buffer;
	return Qnil;

}


/*
 *
 */
VALUE _saveFile(VALUE self,VALUE path)
{
	return wrap(_self->saveToFile(unwrap<std::string>(path)));
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


VALUE _marshal_dump(VALUE self)
{
	VALUE ptr[ 3 ];
	const char*  str = (const char*) _self->getSamples();
	std::size_t str_size = _self->getSampleCount() * 2;

#ifdef HAVE_RUBY_ENCODING_H
	ptr[0] = rb_enc_str_new(str,str_size,rb_ascii8bit_encoding());
#else
	ptr[0] = rb_str_new(str,str_size);
#endif

	ptr[ 1 ] = UINT2NUM( _self->getChannelCount() );
	ptr[ 2 ] = UINT2NUM( _self->getSampleRate() );
	return rb_ary_new4( 3, ptr );
}

VALUE _marshal_load(VALUE self,VALUE data)
{

	const sf::Int16* samples = ( const sf::Int16* )RSTRING_PTR( RARRAY_AREF(data,0) );
	std::size_t sampleCount = RSTRING_LEN( RARRAY_AREF(data,0) ) / 2;
	unsigned int channelCount = NUM2UINT(RARRAY_AREF(data,1));
	unsigned int sampleRate = NUM2UINT(RARRAY_AREF(data,2));

	_self->loadFromSamples( samples, sampleCount, channelCount, sampleRate );

	return Qnil;
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

	rb_define_private_method(rb_cSFMLSoundBuffer,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);

	rb_define_method(rb_cSFMLSoundBuffer,"load_file",RUBY_METHOD_FUNC(_loadFile),1);
	rb_define_singleton_method(rb_cSFMLSoundBuffer,"load_file",RUBY_METHOD_FUNC(_classloadFile),1);

	rb_define_method(rb_cSFMLSoundBuffer,"load_memory",RUBY_METHOD_FUNC(_loadMemory),1);
	rb_define_singleton_method(rb_cSFMLSoundBuffer,"load_memory",RUBY_METHOD_FUNC(_classloadMemory),1);

	rb_define_method(rb_cSFMLSoundBuffer,"save_file",RUBY_METHOD_FUNC(_saveFile),1);

	rb_define_method(rb_cSFMLSoundBuffer,"each_sample",RUBY_METHOD_FUNC(_each_sample),0);

	rb_define_method(rb_cSFMLSoundBuffer,"sample_rate",RUBY_METHOD_FUNC(_getSampleRate),0);
	rb_define_method(rb_cSFMLSoundBuffer,"channel_count",RUBY_METHOD_FUNC(_getChannelCount),0);
	rb_define_method(rb_cSFMLSoundBuffer,"duration",RUBY_METHOD_FUNC(_getDuration),0);

	rb_define_method(rb_cSFMLSoundBuffer,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cSFMLSoundBuffer,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

}



