/*
 * RenderState.hpp
 *
 *  Created on: 26.06.2013
 *      Author: hanmac
 */

#ifndef RENDERSTATE_HPP_
#define RENDERSTATE_HPP_

#include "main.hpp"

template <>
VALUE wrap< sf::RenderStates >(sf::RenderStates *color );

template <>
sf::RenderStates* unwrap< sf::RenderStates* >(const VALUE &vcolor);

template <>
sf::RenderStates unwrap< sf::RenderStates >(const VALUE &vcolor);

void Init_SFMLRenderState(VALUE rb_mSFML);


#endif /* RENDERSTATE_HPP_ */
