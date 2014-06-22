/*
 * RenderState.cpp
 *
 *  Created on: 26.06.2013
 *      Author: hanmac
 */

#include "RenderState.hpp"
#include "Color.hpp"
#include "Vector2.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

#include "Transform.hpp"

#define _self unwrap<sf::RenderStates*>(self)

VALUE rb_cSFMLRenderState;

namespace RubySFML {
namespace RenderState {

VALUE _merge_self(VALUE self,VALUE hash);

}

}

macro_template(sf::RenderStates,NULL,rb_cSFMLRenderState)

template <>
sf::RenderStates unwrap< sf::RenderStates >(const VALUE &vcolor)
{
	VALUE temp = vcolor;
	if(NIL_P(temp))
		return sf::RenderStates::Default;
	else if(rb_obj_is_kind_of(temp,rb_cHash))
	{
		temp = RubySFML::RenderState::_merge_self(wrap(new sf::RenderStates),temp);
	}
	return *unwrap<sf::RenderStates*>(temp);
}

namespace RubySFML {
namespace RenderState {

macro_alloc(sf::RenderStates);

macro_attr_prop(texture,sf::Texture*)
macro_attr_prop(shader,sf::Shader*)
//macro_attr_prop_enum(blendMode,sf::BlendMode)
macro_attr_prop(transform, const sf::Transform&)

VALUE _merge_self(VALUE self,VALUE hash)
{
	setOption(self,hash,_set_texture,"texture");
	setOption(self,hash,_set_shader,"shader");
	//setOption(self,hash,_set_blendMode,"blend_mode");
	setOption(self,hash,_set_transform,"transform");

	return self;
}

VALUE _merge(VALUE self,VALUE hash)
{

	VALUE result = wrap(new sf::RenderStates(*_self));
	_merge_self(result,hash);

	return result;
}


/*
 * call-seq:
 *   RenderState.new(red,green,blue[,alpha])
 *
 * creates a new RenderState Object.
*/
VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE hash;
	rb_scan_args(argc, argv, "10",&hash);

	_merge_self(self,hash);

	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);

	_set_texture(self,_get_texture(other));
	_set_shader(self,_get_shader(other));
	//_set_blendMode(self,_get_blendMode(other));
	_set_transform(self,_get_transform(other));

	return result;
}


}
}

/*
 * Document-class: SFML::RenderState
 *
 * This class represents an render state.
*/

/* Document-attr: texture
 * returns the texture value of RenderState. */
/* Document-attr: shader
 * returns the shader value of RenderState. */
/* Document-attr: blend_mode
 * returns the blend_mode value of RenderState. */
/* Document-attr: transform
 * returns the transform value of RenderState. */

void Init_SFMLRenderState(VALUE rb_mSFML)
{
	using namespace RubySFML::RenderState;
#if 0
	rb_mSFML = rb_define_module("SFML");

	rb_define_attr(rb_cSFMLRenderState,"texture",1,1);
	rb_define_attr(rb_cSFMLRenderState,"shader",1,1);
	rb_define_attr(rb_cSFMLRenderState,"blend_mode",1,1);
	rb_define_attr(rb_cSFMLRenderState,"transform",1,1);
#endif


	rb_cSFMLRenderState = rb_define_class_under(rb_mSFML,"RenderState",rb_cObject);
	rb_define_alloc_func(rb_cSFMLRenderState,_alloc);

	rb_define_method(rb_cSFMLRenderState,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_private_method(rb_cSFMLRenderState,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);

	rb_undef_method(rb_cSFMLRenderState,"_load");
	rb_undef_method(rb_cSFMLRenderState,"_dump");

	rb_define_method(rb_cSFMLRenderState,"merge!",RUBY_METHOD_FUNC(_merge_self),1);
	rb_define_method(rb_cSFMLRenderState,"merge",RUBY_METHOD_FUNC(_merge),1);

	rb_define_attr_method(rb_cSFMLRenderState,"texture",_get_texture,_set_texture);
	rb_define_attr_method(rb_cSFMLRenderState,"shader",_get_shader,_set_shader);
	//rb_define_attr_method(rb_cSFMLRenderState,"blend_mode",_get_blendMode,_set_blendMode);
	rb_define_attr_method(rb_cSFMLRenderState,"transform",_get_transform,_set_transform);

	//rb_define_method(rb_cSFMLRenderState,"inspect",RUBY_METHOD_FUNC(_inspect),0);

/*
	registerEnum<sf::BlendMode>("SFML::BlendMode")
		->add(sf::BlendAlpha,"alpha")
		->add(sf::BlendAdd,"add")
		->add(sf::BlendMultiply,"multiply")
		->add(sf::BlendNone,"none");
*/
}

