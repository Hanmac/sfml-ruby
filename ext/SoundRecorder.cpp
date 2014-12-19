/*
 * SoundRecorder.cpp
 *
 *  Created on: 31.10.2013
 *      Author: hanmac
 */

#include "SoundRecorder.hpp"

#define _self unwrap<sf::SoundRecorder*>(self)

VALUE rb_cSFMLSoundRecorder;

template <>
sf::SoundRecorder* unwrap< sf::SoundRecorder* >(const VALUE &vimage)
{
	return unwrapPtr<sf::SoundRecorder>(vimage, rb_cSFMLSoundRecorder);
}

template <>
sf::SoundRecorder& unwrap< sf::SoundRecorder& >(const VALUE &vimage)
{
	return *unwrap<sf::SoundRecorder*>(vimage);
}


namespace RubySFML {
namespace SoundRecorder {

#if CHECK_SFML_VERSION(2,2)
macro_attr(Device,std::string)
#endif

singlefunc(stop)

/*
 *
 */
VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE device;
	rb_scan_args(argc, argv, "01",&device);
	//VALUE result = rb_call_super(1,&other);
#if CHECK_SFML_VERSION(2,2)
	if(!NIL_P(device))
	{
		std::string cdevice = unwrap<std::string>(device);

		typedef const std::vector<std::string> strvec;
		strvec devices = sf::SoundRecorder::getAvailableDevices();

		bool found = false;
		for(strvec::const_iterator it = devices.begin(); it != devices.end(); ++it){
			if(*it == cdevice)
			{
				found = true;
				_self->setDevice(cdevice);
			}
		}
		if(!found)
		{
			rb_raise(rb_eArgError,"unknown audio recording device %s",cdevice.c_str());
		}
	}
#endif
	return self;
}

/*
 *
 */
VALUE _start(int argc,VALUE *argv,VALUE self)
{
	VALUE sample_rate;
	rb_scan_args(argc, argv, "01",&sample_rate);
	if(NIL_P(sample_rate))
	{
		_self->start();
	} else {
		_self->start(FIX2UINT(sample_rate));
	}
	if(rb_block_given_p())
	{
		rb_yield(self);
		_self->stop();
	}
	return self;
}

}
}

void Init_SFMLSoundRecorder(VALUE rb_mSFML)
{
	using namespace RubySFML::SoundRecorder;

#if 0
	rb_mSFML = rb_define_module("SFML");

#endif

	rb_cSFMLSoundRecorder = rb_define_class_under(rb_mSFML,"SoundRecorder",rb_cObject);

	rb_undef_alloc_func(rb_cSFMLSoundRecorder);

	rb_define_method(rb_cSFMLSoundRecorder,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_undef_method(rb_cSFMLSoundRecorder,"initialize_copy");

	rb_undef_method(rb_cSFMLSoundRecorder,"_dump");
	rb_undef_method(rb_cSFMLSoundRecorder,"_load");
#if CHECK_SFML_VERSION(2,2)
	rb_define_attr_method(rb_cSFMLSoundRecorder,"device",_getDevice,_setDevice);
#endif
	rb_define_method(rb_cSFMLSoundRecorder,"start",RUBY_METHOD_FUNC(_start),-1);
	rb_define_method(rb_cSFMLSoundRecorder,"stop",RUBY_METHOD_FUNC(_stop),-1);

}

