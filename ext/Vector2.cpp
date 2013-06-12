/*
 * Vector2.cpp
 *
 *  Created on: 09.06.2013
 *      Author: hanmac
 */



#include "Vector2.hpp"

#define _self unwrap<sf::Vector2f*>(self)

VALUE rb_cSFMLVector2;

template <>
VALUE wrap< sf::Vector2f >(sf::Vector2f *vector )
{
	return Data_Wrap_Struct(rb_cSFMLVector2, NULL, free, vector);
}

template <>
VALUE wrap< sf::Vector2u >(const sf::Vector2u& vector )
{
	return wrap(sf::Vector2f(vector));
}

template <>
bool is_wrapable< sf::Vector2f >(const VALUE &vvector)
{
	if (rb_obj_is_kind_of(vvector, rb_cSFMLVector2) ||
		rb_obj_is_kind_of(vvector, rb_cString) || FIXNUM_P(vvector)){
		return true;
	} else if(rb_respond_to(vvector,rb_intern("x")) &&
		rb_respond_to(vvector,rb_intern("blue")) &&
		rb_respond_to(vvector,rb_intern("green")) &&
		rb_respond_to(vvector,rb_intern("alpha"))){
		return true;
	}else
		return false;
}

template <>
sf::Vector2f* unwrap< sf::Vector2f* >(const VALUE &vvector)
{
	return unwrapPtr<sf::Vector2f>(vvector, rb_cSFMLVector2);
}

template <>
sf::Vector2f unwrap< sf::Vector2f >(const VALUE &vvector)
{
	if(!rb_obj_is_kind_of(vvector, rb_cSFMLVector2) &&
		rb_respond_to(vvector,rb_intern("x")) &&
		rb_respond_to(vvector,rb_intern("y"))){
		sf::Vector2f vector;
		vector.x = NUM2DBL(rb_funcall(vvector,rb_intern("x"),0));
		vector.y = NUM2DBL(rb_funcall(vvector,rb_intern("y"),0));

		return vector;
	}else{
		return *unwrap<sf::Vector2f*>(vvector);
	}


}


template <>
sf::Vector2u unwrap< sf::Vector2u >(const VALUE &vvector)
{
	return sf::Vector2u(unwrap< sf::Vector2f >(vvector));
}


namespace RubySFML {
namespace Vector2 {
VALUE _alloc(VALUE self) {
	return wrap(new sf::Vector2f);
}

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
 * call-seq:
 *   inspect -> String
 *
 * Human-readable description.
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:(%f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=_get_x(self);
	array[3]=_get_y(self);
	return rb_f_sprintf(4,array);
}


}
}

void Init_SFMLVector2(VALUE rb_mSFML)
{
	using namespace RubySFML::Vector2;

#if 0
	rb_define_attr(rb_cSFMLVector2,"x",1,1);
	rb_define_attr(rb_cSFMLVector2,"y",1,1);
#endif


	rb_cSFMLVector2 = rb_define_class_under(rb_mSFML,"Vector2",rb_cObject);
	rb_define_alloc_func(rb_cSFMLVector2,_alloc);

	rb_define_method(rb_cSFMLVector2,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_private_method(rb_cSFMLVector2,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);


	rb_define_attr_method(rb_cSFMLVector2,"x",_get_x,_set_x);
	rb_define_attr_method(rb_cSFMLVector2,"y",_get_y,_set_y);

	rb_define_method(rb_cSFMLVector2,"inspect",RUBY_METHOD_FUNC(_inspect),0);
}



