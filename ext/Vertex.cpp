/*
 * Vertex.cpp
 *
 *  Created on: 09.06.2013
 *      Author: hanmac
 */

#include "Vertex.hpp"
#include "Color.hpp"
#include "Vector2.hpp"

#define _self unwrap<sf::Vertex*>(self)

VALUE rb_cSFMLVertex;

namespace RubySFML {
namespace Vertex {

VALUE _alloc(VALUE self);
VALUE _from_hash(VALUE self,VALUE hash);

}
}

template <>
VALUE wrap< sf::Vertex >(sf::Vertex *color )
{
	return Data_Wrap_Struct(rb_cSFMLVertex, NULL, free, color);
}

template <>
sf::Vertex* unwrap< sf::Vertex* >(const VALUE &vcolor)
{
	return unwrapPtr<sf::Vertex>(vcolor, rb_cSFMLVertex);
}

template <>
sf::Vertex unwrap< sf::Vertex >(const VALUE &vcolor)
{
	VALUE temp = vcolor;

	if(rb_obj_is_kind_of(temp,rb_cHash))
	{
		temp = RubySFML::Vertex::_from_hash(RubySFML::Vertex::_alloc(Qnil),vcolor);
	}

	return *unwrap<sf::Vertex*>(temp);
}

namespace RubySFML {
namespace Vertex {
VALUE _alloc(VALUE self) {
	return wrap(new sf::Vertex);
}

macro_attr_prop(position,sf::Vector2f)
macro_attr_prop(color,sf::Color)
macro_attr_prop(texCoords,sf::Vector2f)

VALUE _from_hash(VALUE self,VALUE hash)
{
	VALUE temp;

	if(!NIL_P(temp = rb_hash_aref(hash,ID2SYM(rb_intern("position")))))
		_set_position(self,temp);

	if(!NIL_P(temp = rb_hash_aref(hash,ID2SYM(rb_intern("color")))))
		_set_color(self,temp);

	if(!NIL_P(temp = rb_hash_aref(hash,ID2SYM(rb_intern("tex_coords")))))
		_set_texCoords(self,temp);

	return self;
}

/*
 * call-seq:
 *   Vertex.new(red,green,blue[,alpha])
 *
 * creates a new Vertex Object.
*/
VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE position,color,texCoords;
	rb_scan_args(argc, argv, "12",&position,&color,&texCoords);

	if(rb_obj_is_kind_of(position,rb_cHash))
	{
		_from_hash(position,rb_cHash);

	} else {

		_set_position(self,position);

		if(!NIL_P(color))
		{
			if(!is_wrapable<sf::Color>(color) && !NIL_P(texCoords))
				std::swap(color,texCoords);

			_set_color(self,color);
		}

		if(!NIL_P(texCoords))
			_set_texCoords(self,texCoords);

	}

	return self;
}

/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_position(self,_get_position(other));
	_set_color(self,_get_color(other));
	_set_texCoords(self,_get_texCoords(other));
	return result;
}

/*
 * call-seq:
 *   inspect -> String
 *
 * Human-readable description.
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[5];
	array[0]=rb_str_new2("#<%s:(%s, %s, %s)>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(_get_position(self),rb_intern("inspect"),0);
	array[3]=rb_funcall(_get_color(self),rb_intern("inspect"),0);
	array[4]=rb_funcall(_get_texCoords(self),rb_intern("inspect"),0);
	return rb_f_sprintf(5,array);
}


}
}

void Init_SFMLVertex(VALUE rb_mSFML)
{
	using namespace RubySFML::Vertex;
#if 0
	rb_mSFML = rb_define_module("SFML");

	rb_define_attr(rb_cSFMLVertex,"position",1,1);
	rb_define_attr(rb_cSFMLVertex,"color",1,1);
	rb_define_attr(rb_cSFMLVertex,"texCoords",1,1);
#endif


	rb_cSFMLVertex = rb_define_class_under(rb_mSFML,"Vertex",rb_cObject);
	rb_define_alloc_func(rb_cSFMLVertex,_alloc);

	rb_define_method(rb_cSFMLVertex,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_private_method(rb_cSFMLVertex,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);

	rb_define_attr_method(rb_cSFMLVertex,"position",_get_position,_set_position);
	rb_define_attr_method(rb_cSFMLVertex,"color",_get_color,_set_color);
	rb_define_attr_method(rb_cSFMLVertex,"texCoords",_get_texCoords,_set_texCoords);

	rb_define_method(rb_cSFMLVertex,"inspect",RUBY_METHOD_FUNC(_inspect),0);
}

