/*
 * ColorGradient.hpp
 *
 *  Created on: 14.11.2013
 *      Author: hanmac
 */

#ifndef COLORGRADIENT_HPP_
#define COLORGRADIENT_HPP_


#include "main.hpp"


#ifdef HAVE_THOR_GRAPHICS_HPP
#include <Thor/Graphics.hpp>
#endif

extern VALUE rb_cSFMLColorGradient;
void Init_SFMLColorGradient(VALUE rb_mSFML);

#ifdef HAVE_THOR_GRAPHICS_HPP

class RubyColorGradient
{
public:
	typedef std::map<float, sf::Color> Colors;

	operator thor::ColorGradient() {rebuild(); return m_thor; }
	thor::ColorGradient* getThor() {rebuild(); return &m_thor; }

	bool hasColor(float val) const;
	sf::Color getColor(float val,bool calc = false) const;
	void setColor(float val,const sf::Color& col);

	void removeColor(float val,bool rebuild = true);
	//sf::Color getColorbyIdx(std::size_t idx) const;
	//void setColor(float val,const sf::Color& col);

	std::size_t getSize() const {return mColors.size();}
	void iterate(VALUE (*func)(float idx,sf::Color)) const;
	void iterate(VALUE (*func)(RubyColorGradient*,float,sf::Color));

	void rebuild() const;
private:
	Colors	mColors;
	mutable thor::ColorGradient m_thor;

	bool m_invalid;
};


template <>
VALUE wrap< RubyColorGradient >(RubyColorGradient *ani );

template <>
RubyColorGradient* unwrap< RubyColorGradient* >(const VALUE &vani);

template <>
thor::ColorGradient* unwrap< thor::ColorGradient* >(const VALUE &vani);

template <>
thor::ColorGradient unwrap< thor::ColorGradient >(const VALUE &vani);

#endif

#endif /* COLORGRADIENT_HPP_ */
