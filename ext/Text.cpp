/*
 * Text.cpp
 *
 *  Created on: 27.06.2013
 *      Author: hanmac
 */

#include "Text.hpp"
#include "Texture.hpp"
#include "Rect.hpp"
#include "Color.hpp"
#include "Font.hpp"
#include "Transformable.hpp"
#include "Drawable.hpp"

#define _self unwrap<sf::Text*>(self)

VALUE rb_cSFMLText;

macro_template2(sf::Text,NULL,rb_cSFMLText)

namespace RubySFML {
namespace Text {

macro_attr(Font,sf::Font&)
macro_attr(CharacterSize,unsigned int)
macro_attr(Color,sf::Color)

macro_attr(String,sf::String)

macro_alloc(sf::Text)

VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE hash;
	rb_scan_args(argc, argv, "01",&hash);

	if(rb_obj_is_kind_of(hash,rb_cHash)) {

		setOption(self,hash,_setString,"string");
		setOption(self,hash,_setFont,"font");
		setOption(self,hash,_setCharacterSize,"character_size");
		setOption(self,hash,_setColor,"color");
	}

	rb_call_super(argc,argv);

	return self;
}


}
}

void Init_SFMLText(VALUE rb_mSFML)
{
	using namespace RubySFML::Text;

#if 0
	rb_mSFML = rb_define_module("SFML");

	rb_define_attr(rb_cSFMLText,"font",1,1);
	rb_define_attr(rb_cSFMLText,"character_size",1,1);
	rb_define_attr(rb_cSFMLText,"color",1,1);
	rb_define_attr(rb_cSFMLText,"string",1,1);
#endif

	rb_cSFMLText = rb_define_class_under(rb_mSFML,"Text",rb_cSFMLTransformable);
	rb_include_module(rb_cSFMLText,rb_mSFMLDrawable);
	rb_define_alloc_func(rb_cSFMLText,_alloc);

	rb_undef_method(rb_cSFMLText,"initialize_copy");
	rb_undef_method(rb_cSFMLText,"_load");

	rb_define_method(rb_cSFMLText,"initialize",RUBY_METHOD_FUNC(_initialize),-1);


	rb_define_attr_method(rb_cSFMLText,"font",_getFont,_setFont);
	rb_define_attr_method(rb_cSFMLText,"character_size",_getCharacterSize,_setCharacterSize);
	rb_define_attr_method(rb_cSFMLText,"color",_getColor,_setColor);
	rb_define_attr_method(rb_cSFMLText,"string",_getString,_setString);
}





