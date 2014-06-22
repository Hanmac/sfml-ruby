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
#include "Vector3.hpp"
#include "Rect.hpp"

#define _self unwrap<sf::Shader*>(self)

VALUE rb_cSFMLShader;

macro_template2(sf::Shader,NULL,rb_cSFMLShader)

namespace RubySFML {
namespace Shader {

macro_alloc(sf::Shader)

VALUE _loadFile(int argc,VALUE *argv,VALUE self)
{
	VALUE vert,frag;
	rb_scan_args(argc, argv, "11",&vert,&frag);

	if(!NIL_P(frag))
	{
		if(!_self->loadFromFile(unwrap<std::string>(vert),unwrap<std::string>(frag)))
			return Qfalse;
	}else if(rb_obj_is_kind_of(vert,rb_cHash))
	{
		VALUE temp;
		if(!NIL_P(temp = rb_hash_aref(vert,ID2SYM(rb_intern("vert")))))
			if(!_self->loadFromFile(unwrap<std::string>(temp),sf::Shader::Vertex))
				return Qfalse;

		if(!NIL_P(temp = rb_hash_aref(vert,ID2SYM(rb_intern("frag")))))
			if(!_self->loadFromFile(unwrap<std::string>(temp),sf::Shader::Fragment))
				return Qfalse;
	}

	return self;
}


VALUE _singletonloadFile(int argc,VALUE *argv,VALUE self)
{
	VALUE shader = rb_class_new_instance(0,NULL,self);
	return _loadFile(argc,argv,shader);
}


VALUE _setParameter(int argc,VALUE *argv,VALUE self)
{

	VALUE name,obj,arg1,arg2,arg3;
	rb_scan_args(argc, argv, "23",&name,&obj,&arg1,&arg2,&arg3);

	std::string sname(unwrap<std::string>(name));

	if(!NIL_P(arg3))
		_self->setParameter(sname,NUM2DBL(obj),NUM2DBL(arg1),NUM2DBL(arg2),NUM2DBL(arg3));
	else if(!NIL_P(arg2))
		_self->setParameter(sname,NUM2DBL(obj),NUM2DBL(arg1),NUM2DBL(arg2));
	else if(!NIL_P(arg1))
		_self->setParameter(sname,NUM2DBL(obj),NUM2DBL(arg1));
	else if(SYMBOL_P(obj) && SYM2ID(obj) == rb_intern("current"))
		_self->setParameter(sname,sf::Shader::CurrentTexture);
	else if(rb_obj_is_kind_of(obj,rb_cSFMLTexture))
		_self->setParameter(sname,unwrap<sf::Texture&>(obj));
	else if(is_wrapable<sf::Color>(obj))
		_self->setParameter(sname,unwrap<sf::Color>(obj));
	else if(is_wrapable<sf::Vector3f>(obj))
		_self->setParameter(sname,unwrap<sf::Vector3f>(obj));
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
	rb_define_alloc_func(rb_cSFMLShader,_alloc);

	rb_undef_method(rb_cSFMLShader,"initialize_copy");
	rb_undef_method(rb_cSFMLShader,"_load");

	rb_define_method(rb_cSFMLShader,"load_file",RUBY_METHOD_FUNC(_loadFile),-1);
	rb_define_singleton_method(rb_cSFMLShader,"load_file",RUBY_METHOD_FUNC(_singletonloadFile),-1);

	rb_define_method(rb_cSFMLShader,"set_parameter",RUBY_METHOD_FUNC(_setParameter),-1);

}



