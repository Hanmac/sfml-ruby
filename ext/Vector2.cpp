/*
 * Vector2.cpp
 *
 *  Created on: 09.06.2013
 *      Author: hanmac
 */



#include "Vector2.hpp"

#ifdef HAVE_THOR_VECTORS_HPP
#include <Thor/Vectors.hpp>
#endif

#define _self unwrap<sf::Vector2f*>(self)

VALUE rb_cSFMLVector2;

ID rbSFML_IDx,rbSFML_IDy;

macro_template(sf::Vector2f,free,rb_cSFMLVector2)

template <>
VALUE wrap< sf::Vector2i >(const sf::Vector2i& vector )
{
	return wrap(sf::Vector2f(vector));
}

template <>
VALUE wrap< sf::Vector2u >(const sf::Vector2u& vector )
{
	return wrap(sf::Vector2f(vector));
}

template <>
bool is_wrapable< sf::Vector2f >(const VALUE &vvector)
{
	if (rb_obj_is_kind_of(vvector, rb_cSFMLVector2)){
		return true;
	} else if(rb_respond_to(vvector,rbSFML_IDx) &&
		rb_respond_to(vvector,rbSFML_IDy)){
		return true;
	}else
		return false;
}

template <>
sf::Vector2f unwrap< sf::Vector2f >(const VALUE &vvector)
{
	if(!rb_obj_is_kind_of(vvector, rb_cSFMLVector2) &&
		rb_respond_to(vvector,rbSFML_IDx) &&
		rb_respond_to(vvector,rbSFML_IDy)){
		sf::Vector2f vector;
		vector.x = NUM2DBL(rb_funcall(vvector,rbSFML_IDx,0));
		vector.y = NUM2DBL(rb_funcall(vvector,rbSFML_IDy,0));

		return vector;
	}else if(rb_obj_is_kind_of(vvector,rb_cArray)) {
		sf::Vector2f vector;
		vector.x = NUM2DBL(RARRAY_AREF(vvector,0));
		vector.y = NUM2DBL(RARRAY_AREF(vvector,1));
		return vector;
	}else{
		return *unwrap<sf::Vector2f*>(vvector);
	}


}

template <>
sf::Vector2i unwrap< sf::Vector2i >(const VALUE &vvector)
{
	return sf::Vector2i(unwrap< sf::Vector2f >(vvector));
}

template <>
sf::Vector2u unwrap< sf::Vector2u >(const VALUE &vvector)
{
	return sf::Vector2u(unwrap< sf::Vector2f >(vvector));
}


namespace RubySFML {
namespace Vector2 {

macro_alloc(sf::Vector2f)

macro_attr_prop(x,float)
macro_attr_prop(y,float)

/*
 * call-seq:
 *   Vector2.new(red,green,blue[,alpha])
 *
 * creates a new Vector2 Object.
*/
VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE x,y;
	rb_scan_args(argc, argv, "2",&x,&y);
	_set_x(self,x);
	_set_y(self,y);
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_x(self,_get_x(other));
	_set_y(self,_get_y(other));
	return result;
}

/*
*/
VALUE _plus(VALUE self, VALUE other)
{
	return wrap(*_self + unwrap<sf::Vector2f>(other));
}

/*
*/
VALUE _minus(VALUE self, VALUE other)
{
	return wrap(*_self - unwrap<sf::Vector2f>(other));
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
	return rb_sprintf("%s(%f, %f)",
		rb_obj_classname(self),
		NUM2DBL(_get_x(self)),
		NUM2DBL(_get_y(self)));
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
    VALUE ptr[2];
    ptr[0] = _get_x(self);
    ptr[1] = _get_y(self);
    return rb_ary_new4( 2, ptr );
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

    return Qnil;
}


#ifdef HAVE_THOR_VECTORS_HPP
VALUE _getLength(VALUE self)
{
	return DBL2NUM(thor::length(*_self));
}

VALUE _setLength(VALUE self,VALUE val)
{
	thor::setLength<float>(*_self,NUM2DBL(val));
	return val;
}

VALUE _getPolarAngle(VALUE self)
{
	return DBL2NUM(thor::polarAngle(*_self));
}

VALUE _setPolarAngle(VALUE self,VALUE val)
{
	thor::setPolarAngle<float>(*_self,NUM2DBL(val));
	return val;
}
#else
VALUE _getlength(VALUE self)
{
	rb_notimplement();
	return Qnil;
}

VALUE _setlength(VALUE self,VALUE val)
{
	rb_notimplement();
	return val;
}
VALUE _getPolarAngle(VALUE self)
{
	rb_notimplement();
	return Qnil;
}

VALUE _setPolarAngle(VALUE self,VALUE val)
{
	rb_notimplement();
	return val;
}

#endif

}
}

/*
 * Document-class: SFML::Vector2
 *
 * This class represents an two dimensional vector.
*/

/* Document-attr: x
 * returns the x value of Vector. */
/* Document-attr: y
 * returns the y value of Vector. */

/* Document-attr: length
 * returns the length of Vector. Currently Thor only */
/* Document-attr: polar_angle
 * returns the polar_angle of Vector. Currently Thor only */
void Init_SFMLVector2(VALUE rb_mSFML)
{
	using namespace RubySFML::Vector2;

#if 0
	rb_mSFML = rb_define_module("SFML");

	rb_define_attr(rb_cSFMLVector2,"x",1,1);
	rb_define_attr(rb_cSFMLVector2,"y",1,1);

	rb_define_attr(rb_cSFMLVector2,"length",1,1);
	rb_define_attr(rb_cSFMLVector2,"polar_angle",1,1);
#endif


	rb_cSFMLVector2 = rb_define_class_under(rb_mSFML,"Vector2",rb_cObject);
	rb_define_alloc_func(rb_cSFMLVector2,_alloc);

	rb_define_method(rb_cSFMLVector2,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_private_method(rb_cSFMLVector2,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);


	rb_define_attr_method(rb_cSFMLVector2,"x",_get_x,_set_x);
	rb_define_attr_method(rb_cSFMLVector2,"y",_get_y,_set_y);

	rb_define_attr_method(rb_cSFMLVector2,"length",_getLength,_setLength);
	rb_define_attr_method(rb_cSFMLVector2,"polar_angle",_getPolarAngle,_setPolarAngle);

	rb_define_method(rb_cSFMLVector2,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_method(rb_cSFMLVector2,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cSFMLVector2,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

	rb_define_method(rb_cSFMLVector2,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cSFMLVector2,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cSFMLVector2,"*",RUBY_METHOD_FUNC(_mal),1);
	rb_define_method(rb_cSFMLVector2,"/",RUBY_METHOD_FUNC(_durch),1);

	rbSFML_IDx = rb_intern("x");
	rbSFML_IDy = rb_intern("y");
}



