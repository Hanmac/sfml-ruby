/*
 * Drawable.cpp
 *
 *  Created on: 16.06.2013
 *      Author: hanmac
 */

#include "Drawable.hpp"
#include "Sprite.hpp"

#define _self unwrap<sf::Drawable*>(self)

VALUE rb_mSFMLDrawable;

/*
template <>
VALUE wrap< sf::Drawable >(sf::Drawable *image )
{
	return Data_Wrap_Struct(rb_mSFMLDrawable, NULL, NULL, image);
}
*/

template <>
sf::Drawable* unwrap< sf::Drawable* >(const VALUE &vimage)
{
	return unwrapPtr<sf::Drawable>(vimage, rb_mSFMLDrawable);
}

template <>
sf::Drawable& unwrap< sf::Drawable& >(const VALUE &vimage)
{
	if(rb_obj_is_kind_of(vimage, rb_cSFMLSprite)){
		return *unwrap<sf::Sprite*>(vimage);
	}

	return *unwrap<sf::Drawable*>(vimage);
}


namespace RubySFML {
namespace Drawable {


}
}


void Init_SFMLDrawable(VALUE rb_mSFML)
{
	using namespace RubySFML::Drawable;

#if 0
	rb_mSFML = rb_define_module("SFML");
#endif


	rb_mSFMLDrawable = rb_define_module_under(rb_mSFML,"Drawable");


}


