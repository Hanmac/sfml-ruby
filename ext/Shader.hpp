/*
 * Shader.hpp
 *
 *  Created on: 26.06.2013
 *      Author: hanmac
 */

#ifndef SHADER_HPP_
#define SHADER_HPP_


#include "main.hpp"

extern VALUE rb_cSFMLShader;
void Init_SFMLShader(VALUE rb_mSFML);

template <>
VALUE wrap< sf::Shader >(sf::Shader *image );

template <>
sf::Shader* unwrap< sf::Shader* >(const VALUE &vimage);

template <>
sf::Shader& unwrap< sf::Shader& >(const VALUE &vimage);



#endif /* SHADER_HPP_ */
