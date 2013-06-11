/*
 * Vertex.hpp
 *
 *  Created on: 09.06.2013
 *      Author: hanmac
 */

#ifndef VERTEX_HPP_
#define VERTEX_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLVertex;
void Init_SFMLVertex(VALUE rb_mSFML);

template <>
VALUE wrap< sf::Vertex >(sf::Vertex *color );

template <>
sf::Vertex* unwrap< sf::Vertex* >(const VALUE &vcolor);

template <>
sf::Vertex unwrap< sf::Vertex >(const VALUE &vcolor);


#endif /* VERTEX_HPP_ */
