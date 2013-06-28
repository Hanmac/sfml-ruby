/*
 * Clock.hpp
 *
 *  Created on: 28.06.2013
 *      Author: hanmac
 */

#ifndef CLOCK_HPP_
#define CLOCK_HPP_


#include "main.hpp"

extern VALUE rb_cSFMLClock;
void Init_SFMLClock(VALUE rb_mSFML);

template <>
VALUE wrap< sf::Clock >(sf::Clock *clock );

template <>
sf::Clock* unwrap< sf::Clock* >(const VALUE &vclock);


#endif /* CLOCK_HPP_ */
