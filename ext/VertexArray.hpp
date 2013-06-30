/*
 * VertexArray.hpp
 *
 *  Created on: 30.06.2013
 *      Author: hanmac
 */

#ifndef VERTEXARRAY_HPP_
#define VERTEXARRAY_HPP_


#include "main.hpp"

extern VALUE rb_cSFMLVertexArray;
void Init_SFMLVertexArray(VALUE rb_mSFML);

template <>
VALUE wrap< sf::VertexArray >(sf::VertexArray *color );

template <>
sf::VertexArray* unwrap< sf::VertexArray* >(const VALUE &vcolor);


#endif /* VERTEXARRAY_HPP_ */
