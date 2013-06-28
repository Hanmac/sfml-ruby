/*
 * Time.hpp
 *
 *  Created on: 28.06.2013
 *      Author: hanmac
 */

#ifndef TIME_HPP_
#define TIME_HPP_

#include "main.hpp"

extern VALUE rb_cSFMLTime;
void Init_SFMLTime(VALUE rb_mSFML);

template <>
VALUE wrap< sf::Time >(sf::Time *clock );

template <>
sf::Time* unwrap< sf::Time* >(const VALUE &vclock);


#endif /* TIME_HPP_ */
