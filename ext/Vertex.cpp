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

VALUE _from_hash(VALUE self,VALUE hash);

}
}

macro_template(sf::Vertex,free,rb_cSFMLVertex)

template <>
sf::Vertex unwrap< sf::Vertex >(const VALUE &vcolor)
{
	VALUE temp = vcolor;

	if(rb_obj_is_kind_of(temp,rb_cHash))
	{
		VALUE argv[] = {temp};
		VALUE vertex = rb_class_new_instance(1,argv,rb_cSFMLVertex);
	}

	return *unwrap<sf::Vertex*>(temp);
}

namespace RubySFML {
namespace Vertex {

macro_alloc(sf::Vertex)

macro_attr_prop(position,sf::Vector2f)
macro_attr_prop(color,sf::Color)
macro_attr_prop(texCoords,sf::Vector2f)

VALUE _from_hash(VALUE self,VALUE hash)
{
	VALUE temp;

	setOption(self,hash,_set_position,"position");
	setOption(self,hash,_set_color,"color");
	setOption(self,hash,_set_texCoords,"tex_coords");

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
	array[2]=rb_inspect(_get_position(self));
	array[3]=rb_inspect(_get_color(self));
	array[4]=rb_inspect(_get_texCoords(self));
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

