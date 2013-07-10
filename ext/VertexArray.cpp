/*
 * VertexArray.cpp
 *
 *  Created on: 30.06.2013
 *      Author: hanmac
 */

#include "VertexArray.hpp"
#include "Texture.hpp"
#include "Rect.hpp"
#include "Color.hpp"
#include "Vertex.hpp"
#include "Transformable.hpp"
#include "Drawable.hpp"

#define _self unwrap<sf::VertexArray*>(self)

VALUE rb_cSFMLVertexArray;

template <>
VALUE wrap< sf::VertexArray >(sf::VertexArray *image )
{
	return Data_Wrap_Struct(rb_cSFMLVertexArray, NULL, NULL, image);
}

template <>
sf::VertexArray* unwrap< sf::VertexArray* >(const VALUE &vimage)
{
	return unwrapPtr<sf::VertexArray>(vimage, rb_cSFMLVertexArray);
}

template <>
sf::VertexArray& unwrap< sf::VertexArray& >(const VALUE &vimage)
{
	return *unwrap<sf::VertexArray*>(vimage);
}


namespace RubySFML {
namespace VertexArray {

VALUE _alloc(VALUE self) {
	return wrap(new sf::VertexArray);
}


VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE type;
	rb_scan_args(argc, argv, "01",&type);

	_self->setPrimitiveType(unwrapenum<sf::PrimitiveType>(type));

//	rb_call_super(argc,argv);

	return self;
}

VALUE _get(VALUE self,VALUE idx)
{
	if(FIX2UINT(idx) < _self->getVertexCount() )
		return wrap((*_self)[FIX2UINT(idx)]);

	return Qnil;
}


VALUE _append(VALUE self,VALUE vertex)
{
	_self->append(unwrap<sf::Vertex>(vertex));
	return self;
}

}
}

void Init_SFMLVertexArray(VALUE rb_mSFML)
{
	using namespace RubySFML::VertexArray;

#if 0
	rb_mSFML = rb_define_module("SFML");

	rb_define_attr(rb_cSFMLVertexArray,"texture",1,1);
	rb_define_attr(rb_cSFMLVertexArray,"texture_rect",1,1);
	rb_define_attr(rb_cSFMLVertexArray,"color",1,1);
#endif

	rb_cSFMLVertexArray = rb_define_class_under(rb_mSFML,"VertexArray",rb_cObject);
	rb_include_module(rb_cSFMLVertexArray,rb_mSFMLDrawable);
	rb_define_alloc_func(rb_cSFMLVertexArray,_alloc);

	rb_undef_method(rb_cSFMLVertexArray,"initialize_copy");
	rb_undef_method(rb_cSFMLVertexArray,"_load");

	rb_define_method(rb_cSFMLVertexArray,"initialize",RUBY_METHOD_FUNC(_initialize),-1);

	rb_define_method(rb_cSFMLVertexArray,"[]",RUBY_METHOD_FUNC(_get),1);

	rb_define_method(rb_cSFMLVertexArray,"<<",RUBY_METHOD_FUNC(_append),1);

	registerEnum<sf::PrimitiveType>("SFML::PrimitiveType")
			->add(sf::Points,"points")
			->add(sf::Lines,"lines")
			->add(sf::LinesStrip,"lines_strip")
			->add(sf::Triangles,"triangles")
			->add(sf::TrianglesStrip,"triangles_strip")
			->add(sf::TrianglesFan,"triangles_fan")
			->add(sf::Quads,"quads");
}


