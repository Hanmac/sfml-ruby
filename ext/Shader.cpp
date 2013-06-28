/*
 * Shader.cpp
 *
 *  Created on: 26.06.2013
 *      Author: hanmac
 */

#include "Image.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Color.hpp"
#include "Vector2.hpp"
#include "Rect.hpp"

#define _self unwrap<sf::Shader*>(self)

VALUE rb_cSFMLShader;

template <>
VALUE wrap< sf::Shader >(sf::Shader *image )
{
	return Data_Wrap_Struct(rb_cSFMLShader, NULL, NULL, image);
}

template <>
sf::Shader* unwrap< sf::Shader* >(const VALUE &vimage)
{
	return unwrapPtr<sf::Shader>(vimage, rb_cSFMLShader);
}

template <>
sf::Shader& unwrap< sf::Shader& >(const VALUE &vimage)
{
	return *unwrap<sf::Shader*>(vimage);
}


namespace RubySFML {
namespace Shader {

VALUE _loadFile(int argc,VALUE *argv,VALUE self)
{
	sf::Shader *image = new sf::Shader;

	VALUE vert,frag;
	rb_scan_args(argc, argv, "11",&vert,&frag);

	if(!NIL_P(frag))
	{
		if(image->loadFromFile(unwrap<std::string>(vert),unwrap<std::string>(frag)))
				return wrap(image);
	}else if(rb_obj_is_kind_of(vert,rb_cHash))
	{
		VALUE temp;
		if(!NIL_P(temp = rb_hash_aref(vert,ID2SYM(rb_intern("vert")))))
			if(!image->loadFromFile(unwrap<std::string>(temp),sf::Shader::Vertex))
				return Qnil;

		if(!NIL_P(temp = rb_hash_aref(vert,ID2SYM(rb_intern("frag")))))
			if(!image->loadFromFile(unwrap<std::string>(temp),sf::Shader::Fragment))
				return Qnil;
		return wrap(image);
	}

	return Qnil;
}


VALUE _setParameter(int argc,VALUE *argv,VALUE self)
{

	VALUE name,obj;
	rb_scan_args(argc, argv, "20",&name,&obj);

	std::string sname(unwrap<std::string>(name));

	if(SYMBOL_P(obj) && SYM2ID(obj) == rb_intern("current"))
		_self->setParameter(sname,sf::Shader::CurrentTexture);
	else if(rb_obj_is_kind_of(obj,rb_cSFMLTexture))
		_self->setParameter(sname,unwrap<sf::Texture&>(obj));
	else if(is_wrapable<sf::Color>(obj))
		_self->setParameter(sname,unwrap<sf::Color>(obj));
	else if(is_wrapable<sf::Vector2f>(obj))
		_self->setParameter(sname,unwrap<sf::Vector2f>(obj));
	else
		_self->setParameter(sname,NUM2DBL(obj));
	return self;

}

}
}

void Init_SFMLShader(VALUE rb_mSFML)
{
	using namespace RubySFML::Shader;

#if 0
	rb_mSFML = rb_define_module("SFML");
#endif

	rb_cSFMLShader = rb_define_class_under(rb_mSFML,"Shader",rb_cObject);
	rb_undef_alloc_func(rb_cSFMLShader);

	rb_undef_method(rb_cSFMLShader,"initialize_copy");
	rb_undef_method(rb_cSFMLShader,"_load");

	rb_define_singleton_method(rb_cSFMLShader,"load_file",RUBY_METHOD_FUNC(_loadFile),-1);

	rb_define_method(rb_cSFMLShader,"set_parameter",RUBY_METHOD_FUNC(_setParameter),-1);

}



