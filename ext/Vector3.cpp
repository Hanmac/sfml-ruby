/*
 * Vector3.cpp
 *
 *  Created on: 30.06.2013
 *      Author: hanmac
 */

#include "Vector3.hpp"
#include "Vector2.hpp"
#define _self unwrap<sf::Vector3f*>(self)

VALUE rb_cSFMLVector3;
ID rbSFML_IDz;

macro_template(sf::Vector3f,free,rb_cSFMLVector3)

template <>
VALUE wrap< sf::Vector3i >(const sf::Vector3i& vector )
{
	return wrap(sf::Vector3f(vector));
}

template <>
bool is_wrapable< sf::Vector3f >(const VALUE &vvector)
{
	if (rb_obj_is_kind_of(vvector, rb_cSFMLVector3)){
		return true;
	} else if(rb_respond_to(vvector,rbSFML_IDx) &&
			rb_respond_to(vvector,rbSFML_IDy) &&
			rb_respond_to(vvector,rbSFML_IDz)){
		return true;
	}else
		return false;
}

template <>
sf::Vector3f unwrap< sf::Vector3f >(const VALUE &vvector)
{
	if(!rb_obj_is_kind_of(vvector, rb_cSFMLVector3) &&
		rb_respond_to(vvector,rbSFML_IDx) &&
		rb_respond_to(vvector,rbSFML_IDy) &&
		rb_respond_to(vvector,rbSFML_IDz)){
		sf::Vector3f vector;
		vector.x = NUM2DBL(rb_funcall(vvector,rbSFML_IDx,0));
		vector.y = NUM2DBL(rb_funcall(vvector,rbSFML_IDy,0));
		vector.z = NUM2DBL(rb_funcall(vvector,rbSFML_IDz,0));

		return vector;
	}else{
		return *unwrap<sf::Vector3f*>(vvector);
	}


}

template <>
sf::Vector3i unwrap< sf::Vector3i >(const VALUE &vvector)
{
	return sf::Vector3i(unwrap< sf::Vector3f >(vvector));
}


namespace RubySFML {
namespace Vector3 {

macro_alloc(sf::Vector3f)

macro_attr_prop(x,float)
macro_attr_prop(y,float)
macro_attr_prop(z,float)

/*
 * call-seq:
 *   Vector3.new(red,green,blue[,alpha])
 *
 * creates a new Vector3 Object.
*/
VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE x,y,z;
	rb_scan_args(argc, argv, "30",&x,&y,&z);
	_set_x(self,x);
	_set_y(self,y);
	_set_z(self,z);
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_x(self,_get_x(other));
	_set_y(self,_get_y(other));
	_set_z(self,_get_z(other));
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
	rb_sprintf("%s(%f, %f, %f)",
		rb_obj_classname(self),
		NUM2DBL(_get_x(self)),
		NUM2DBL(_get_y(self)),
		NUM2DBL(_get_z(self)));
}

/*
 * call-seq:
 *   marshal_dump -> Array
 *
 * Provides marshalling support for use by the Marshal library.
 * ===Return value
 * Array
 */
VALUE _marshal_dump( VALUE self )
{
    VALUE ptr[3];
    ptr[0] = _get_x(self);
    ptr[1] = _get_y(self);
    ptr[2] = _get_z(self);
    return rb_ary_new4( 3, ptr );
}

/*
 * call-seq:
 *   marshal_load(array) -> nil
 *
 * Provides marshalling support for use by the Marshal library.
 *
 *
 */
VALUE _marshal_load( VALUE self, VALUE data )
{
    _set_x(self, RARRAY_AREF(data,0));
    _set_y(self, RARRAY_AREF(data,1));
    _set_z(self, RARRAY_AREF(data,2));

    return Qnil;
}

/*
*/
VALUE _plus(VALUE self, VALUE other)
{
	return wrap(*_self + unwrap<sf::Vector3f>(other));
}

/*
*/
VALUE _minus(VALUE self, VALUE other)
{
	return wrap(*_self - unwrap<sf::Vector3f>(other));
}

/*
*/
VALUE _mal(VALUE self, VALUE other)
{
	return wrap(*_self * (float)NUM2DBL(other));
}

/*
*/
VALUE _durch(VALUE self, VALUE other)
{
	return wrap(*_self / (float)NUM2DBL(other));
}
}
}

/*
 * Document-class: SFML::Vector3
 *
 * This class represents an three dimensional vector.
*/

/* Document-attr: x
 * returns the x value of Vector. */
/* Document-attr: y
 * returns the y value of Vector. */
/* Document-attr: z
 * returns the z value of Vector. */
void Init_SFMLVector3(VALUE rb_mSFML)
{
	using namespace RubySFML::Vector3;

#if 0
	rb_mSFML = rb_define_module("SFML");

	rb_define_attr(rb_cSFMLVector3,"x",1,1);
	rb_define_attr(rb_cSFMLVector3,"y",1,1);
	rb_define_attr(rb_cSFMLVector3,"z",1,1);
#endif


	rb_cSFMLVector3 = rb_define_class_under(rb_mSFML,"Vector3",rb_cObject);
	rb_define_alloc_func(rb_cSFMLVector3,_alloc);

	rb_define_method(rb_cSFMLVector3,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_private_method(rb_cSFMLVector3,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);


	rb_define_attr_method(rb_cSFMLVector3,"x",_get_x,_set_x);
	rb_define_attr_method(rb_cSFMLVector3,"y",_get_y,_set_y);
	rb_define_attr_method(rb_cSFMLVector3,"z",_get_z,_set_z);

	rb_define_method(rb_cSFMLVector3,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_method(rb_cSFMLVector3,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cSFMLVector3,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

	rb_define_method(rb_cSFMLVector3,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cSFMLVector3,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cSFMLVector3,"*",RUBY_METHOD_FUNC(_mal),1);
	rb_define_method(rb_cSFMLVector3,"/",RUBY_METHOD_FUNC(_durch),1);

	rbSFML_IDz = rb_intern("z");

}



