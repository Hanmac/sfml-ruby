/*
 * sfml.cpp
 *
 *  Created on: 09.06.2013
 *      Author: hanmac
 */

#include "Rect.hpp"
#include "Color.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vertex.hpp"
#include "Image.hpp"
#include "Texture.hpp"
#include "Font.hpp"

#include "VideoMode.hpp"

#include "View.hpp"

#include "Window.hpp"
#include "RenderTarget.hpp"
#include "RenderState.hpp"
#include "RenderWindow.hpp"

#include "Transformable.hpp"
#include "Drawable.hpp"
#include "Sprite.hpp"
#include "Text.hpp"

#include "Shader.hpp"

#include "Event.hpp"

#include "Mouse.hpp"

#include "Time.hpp"
#include "Clock.hpp"

#include "VertexArray.hpp"

VALUE rb_mSFML;

void rb_define_attr_method(VALUE klass,std::string name,VALUE(get)(VALUE),VALUE(set)(VALUE,VALUE))
{
	rb_define_method(klass,name.c_str(),RUBY_METHOD_FUNC(get),0);
	rb_define_method(klass,(name + "=").c_str(),RUBY_METHOD_FUNC(set),1);
}



extern "C" void Init_sfml()
{

	rb_mSFML = rb_define_module("SFML");

	Init_SFMLRect(rb_mSFML);
	Init_SFMLColor(rb_mSFML);
	Init_SFMLVector2(rb_mSFML);
	Init_SFMLVector3(rb_mSFML);
	Init_SFMLVertex(rb_mSFML);
	Init_SFMLImage(rb_mSFML);
	Init_SFMLTexture(rb_mSFML);
	Init_SFMLFont(rb_mSFML);

	Init_SFMLView(rb_mSFML);

	Init_SFMLVideoMode(rb_mSFML);

	Init_SFMLWindow(rb_mSFML);

	Init_SFMLRenderTarget(rb_mSFML);
	Init_SFMLRenderState(rb_mSFML);
	Init_SFMLRenderWindow(rb_mSFML);

	Init_SFMLTransformable(rb_mSFML);
	Init_SFMLDrawable(rb_mSFML);
	Init_SFMLSprite(rb_mSFML);
	Init_SFMLText(rb_mSFML);

	Init_SFMLVertexArray(rb_mSFML);

	Init_SFMLShader(rb_mSFML);

	Init_SFMLEvent(rb_mSFML);

	Init_SFMLMouse(rb_mSFML);

	Init_SFMLTime(rb_mSFML);
	Init_SFMLClock(rb_mSFML);
}
