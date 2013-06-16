/*
 * Event.hpp
 *
 *  Created on: 16.06.2013
 *      Author: hanmac
 */

#ifndef EVENT_HPP_
#define EVENT_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLEvent;
void Init_SFMLEvent(VALUE rb_mSFML);

template <>
VALUE wrap< sf::Event >(sf::Event *image );

template <>
sf::Event* unwrap< sf::Event* >(const VALUE &vimage);


#endif /* EVENT_HPP_ */
