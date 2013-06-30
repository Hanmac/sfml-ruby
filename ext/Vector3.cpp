/*
 * Vector3.cpp
 *
 *  Created on: 30.06.2013
 *      Author: hanmac
 */

#include "Vector3.hpp"

#define _self unwrap<sf::Vector3f*>(self)

VALUE rb_cSFMLVector3;

template <>
VALUE wrap< sf::Vector3f >(sf::Vector3f *vector )
{
	return Data_Wrap_Struct(rb_cSFMLVector3, NULL, free, vector);
}

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
	} else if(rb_respond_to(vvector,rb_intern("x")) &&
			rb_respond_to(vvector,rb_intern("y")) &&
			rb_respond_to(vvector,rb_intern("z"))){
		return true;
	}else
		return false;
}

template <>
sf::Vector3f* unwrap< sf::Vector3f* >(const VALUE &vvector)
{
	return unwrapPtr<sf::Vector3f>(vvector, rb_cSFMLVector3);
}

template <>
sf::Vector3f unwrap< sf::Vector3f >(const VALUE &vvector)
{
	if(!rb_obj_is_kind_of(vvector, rb_cSFMLVector3) &&
		rb_respond_to(vvector,rb_intern("x")) &&
		rb_respond_to(vvector,rb_intern("y")) &&
		rb_respond_to(vvector,rb_intern("z"))){
		sf::Vector3f vector;
		vector.x = NUM2DBL(rb_funcall(vvector,rb_intern("x"),0));
		vector.y = NUM2DBL(rb_funcall(vvector,rb_intern("y"),0));
		vector.z = NUM2DBL(rb_funcall(vvector,rb_intern("z"),0));

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
VALUE _alloc(VALUE self) {
	return wrap(new sf::Vector3f);
}

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
	VALUE array[5];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=_get_x(self);
	array[3]=_get_y(self);
	array[4]=_get_z(self);
	return rb_f_sprintf(5,array);
}


}
}

void Init_SFMLVector3(VALUE rb_mSFML)
{
	using namespace RubySFML::Vector3;

#if 0
	rb_mSFML = rb_define_module("SFML");

	rb_define_attr(rb_cSFMLVector3,"x",1,1);
	rb_define_attr(rb_cSFMLVector3,"y",1,1);
#endif


	rb_cSFMLVector3 = rb_define_class_under(rb_mSFML,"Vector3",rb_cObject);
	rb_define_alloc_func(rb_cSFMLVector3,_alloc);

	rb_define_method(rb_cSFMLVector3,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_private_method(rb_cSFMLVector3,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);


	rb_define_attr_method(rb_cSFMLVector3,"x",_get_x,_set_x);
	rb_define_attr_method(rb_cSFMLVector3,"y",_get_y,_set_y);
	rb_define_attr_method(rb_cSFMLVector3,"z",_get_z,_set_z);

	rb_define_method(rb_cSFMLVector3,"inspect",RUBY_METHOD_FUNC(_inspect),0);
}



