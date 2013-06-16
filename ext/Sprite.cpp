/*
 * Sprite.cpp
 *
 *  Created on: 15.06.2013
 *      Author: hanmac
 */



#include "Sprite.hpp"
#include "Texture.hpp"
#include "Rect.hpp"
#include "Color.hpp"

#include "Transformable.hpp"
#include "Drawable.hpp"

#define _self unwrap<sf::Sprite*>(self)

VALUE rb_cSFMLSprite;

template <>
VALUE wrap< sf::Sprite >(sf::Sprite *image )
{
	return Data_Wrap_Struct(rb_cSFMLSprite, NULL, NULL, image);
}

template <>
sf::Sprite* unwrap< sf::Sprite* >(const VALUE &vimage)
{
	return unwrapPtr<sf::Sprite>(vimage, rb_cSFMLSprite);
}

template <>
sf::Sprite& unwrap< sf::Sprite& >(const VALUE &vimage)
{
	return *unwrap<sf::Sprite*>(vimage);
}


namespace RubySFML {
namespace Sprite {

macro_attr(Texture,sf::Texture&)
macro_attr(TextureRect,sf::IntRect)
macro_attr(Color,sf::Color)

VALUE _alloc(VALUE self) {
	return wrap(new sf::Sprite);
}


}
}

void Init_SFMLSprite(VALUE rb_mSFML)
{
	using namespace RubySFML::Sprite;
#if 0
	rb_define_attr(rb_cSFMLSprite,"texture",1,1);
	rb_define_attr(rb_cSFMLSprite,"texture_rect",1,1);
	rb_define_attr(rb_cSFMLSprite,"color",1,1);
#endif

	rb_cSFMLSprite = rb_define_class_under(rb_mSFML,"Sprite",rb_cSFMLTransformable);
	rb_include_module(rb_cSFMLSprite,rb_mSFMLDrawable);
	rb_define_alloc_func(rb_cSFMLSprite,_alloc);

	rb_undef_method(rb_cSFMLSprite,"initialize_copy");
	rb_undef_method(rb_cSFMLSprite,"_load");

	rb_define_attr_method(rb_cSFMLSprite,"texture",_getTexture,_setTexture);
	rb_define_attr_method(rb_cSFMLSprite,"texture_rect",_getTextureRect,_setTextureRect);
	rb_define_attr_method(rb_cSFMLSprite,"color",_getColor,_setColor);
}

