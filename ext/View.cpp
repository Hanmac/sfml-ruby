/*
 * View.cpp
 *
 *  Created on: 12.06.2013
 *      Author: hanmac
 */

#include "View.hpp"
#include "Vector2.hpp"
#include "Rect.hpp"

#define _self unwrap<sf::View*>(self)

VALUE rb_cSFMLView;

template <>
VALUE wrap< sf::View >(sf::View *image )
{
	return Data_Wrap_Struct(rb_cSFMLView, NULL, NULL, image);
}

template <>
VALUE wrap< sf::View >(const sf::View &image )
{
	return wrap(const_cast<sf::View*>(&image));
}
template <>
sf::View* unwrap< sf::View* >(const VALUE &vimage)
{
	return unwrapPtr<sf::View>(vimage, rb_cSFMLView);
}

template <>
sf::View& unwrap< sf::View& >(const VALUE &vimage)
{
	return *unwrap<sf::View*>(vimage);
}


namespace RubySFML {
namespace View {

VALUE _alloc(VALUE self) {
	return wrap(new sf::View);
}

macro_attr(Center,sf::Vector2f)
macro_attr(Size,sf::Vector2f)
macro_attr(Rotation,float)
macro_attr(Viewport,sf::FloatRect)

VALUE _zoom(VALUE self,VALUE val)
{
	_self->zoom(NUM2DBL(val));
	return self;
}

/*
 * call-seq:
 *   View.new(center,size[,rotation])
 *
 * creates a new View Object.
*/
VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE center,size,rotation;
	rb_scan_args(argc, argv, "21",&center,&size,&rotation);

	_setCenter(self,center);
	_setSize(self,size);

	if(!NIL_P(rotation))
		_setRotation(self,rotation);

	return self;
}

}
}

/*
 * Document-class: SFML::View
 *
 * This class represents an View.
*/

/* Document-attr: center
 * returns the center value of View. */
/* Document-attr: size
 * returns the size value of View. */
/* Document-attr: rotation
 * returns the rotation value of View. */
/* Document-attr: viewport
 * returns the viewport value of View. */

void Init_SFMLView(VALUE rb_mSFML)
{
	using namespace RubySFML::View;
#if 0
	rb_mSFML = rb_define_module("SFML");

	rb_define_attr(rb_cSFMLView,"center",1,1);
	rb_define_attr(rb_cSFMLView,"size",1,1);
	rb_define_attr(rb_cSFMLView,"rotation",1,1);
	rb_define_attr(rb_cSFMLView,"viewport",1,1);
#endif

	rb_cSFMLView = rb_define_class_under(rb_mSFML,"View",rb_cObject);
	rb_define_alloc_func(rb_cSFMLView,_alloc);

	rb_define_method(rb_cSFMLView,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_undef_method(rb_cSFMLView,"initialize_copy");
	rb_undef_method(rb_cSFMLView,"_load");

	rb_define_attr_method(rb_cSFMLView,"center",_getCenter,_setCenter);
	rb_define_attr_method(rb_cSFMLView,"size",_getSize,_setSize);
	rb_define_attr_method(rb_cSFMLView,"rotation",_getRotation,_setRotation);
	rb_define_attr_method(rb_cSFMLView,"viewport",_getViewport,_setViewport);

	rb_define_method(rb_cSFMLView,"zoom",RUBY_METHOD_FUNC(_zoom),1);
}


