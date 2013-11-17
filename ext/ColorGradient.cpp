/*
 * ColorGradient.cpp
 *
 *  Created on: 14.11.2013
 *      Author: hanmac
 */

#include "ColorGradient.hpp"
#include "Color.hpp"

#ifdef HAVE_THOR_GRAPHICS_HPP
#define _self unwrap<RubyColorGradient*>(self)


template <>
VALUE wrap< RubyColorGradient >(RubyColorGradient *ani )
{
	return Data_Wrap_Struct(rb_cSFMLColorGradient, NULL, NULL, ani);
}

template <>
RubyColorGradient* unwrap< RubyColorGradient* >(const VALUE &vani)
{
	return unwrapPtr<RubyColorGradient>(vani, rb_cSFMLColorGradient);
}

template <>
thor::ColorGradient* unwrap< thor::ColorGradient* >(const VALUE &vani)
{
	return unwrap<RubyColorGradient*>(vani)->getThor();
}

int grad_from_hash_each(VALUE key,VALUE val,thor::ColorGradient *obj)
{
	double ckey = NUM2DBL(key);
	if((ckey < 0.0) || (ckey > 1.0))
	{
		rb_raise(rb_eKeyError,"%f is out of range, only 0.0 .. 1.0 are allowed for %s",
			ckey,
			rb_class2name(rb_cSFMLColorGradient)
		);
		return 1;
	}
	(*obj)[ckey] = unwrap<sf::Color>(val);
	return 0;
}

template <>
thor::ColorGradient unwrap< thor::ColorGradient >(const VALUE &vani)
{
	if(rb_obj_is_kind_of(vani,rb_cHash))
	{
		if(NIL_P(rb_hash_aref(vani,DBL2NUM(0.0))) ||
			NIL_P(rb_hash_aref(vani,DBL2NUM(1.0))))
		{
			VALUE vani = rb_inspect(vani);

			rb_raise(rb_eArgError,"Hash %s misses the keys 0.0 or 1.0 to be converted into a %s.",
				StringValueCStr(vani),
				rb_class2name(rb_cSFMLColorGradient)
			);
		}
		thor::ColorGradient grad;
		rb_hash_foreach(vani,(int (*)(...))grad_from_hash_each,(VALUE)&grad);
		return grad;
	}

	return (*unwrap<RubyColorGradient*>(vani));
}


#endif

VALUE rb_cSFMLColorGradient;

#ifdef HAVE_THOR_GRAPHICS_HPP

bool RubyColorGradient::hasColor(float val) const
{
	return mColors.find(val) != mColors.end();
}

sf::Color RubyColorGradient::getColor(float val,bool calc) const
{
	if(calc && !m_invalid)
		return m_thor.getColor(val);
	Colors::const_iterator it;
	if((it = mColors.find(val)) != mColors.end())
	{
			return it->second;
	}

	if(!calc)
		return sf::Color::Transparent;

	rebuild();
	return m_thor.getColor(val);

}
void RubyColorGradient::setColor(float val,const sf::Color& col)
{
	this->mColors[val] = col;
	this->m_thor[val] = col;
}

void RubyColorGradient::removeColor(float val,bool rebuild)
{
	this->mColors.erase(val);
	this->m_invalid = true;

	if(rebuild)
		this->rebuild();
}

void RubyColorGradient::iterate(VALUE (*func)(float idx,sf::Color)) const
{
	for(Colors::const_iterator it = mColors.begin();it != mColors.end(); ++it)
	{
		func(it->first,it->second);
	}
}
void RubyColorGradient::iterate(VALUE (*func)(RubyColorGradient*,float,sf::Color))
{
	for(Colors::iterator it = mColors.begin();it != mColors.end(); ++it)
	{
		func(this,it->first,it->second);
	}
}
void RubyColorGradient::rebuild() const
{
	if(!this->m_invalid)
		return;

	this->m_thor = thor::ColorGradient();
	for(Colors::const_iterator it = mColors.begin();it != mColors.end(); ++it)
	{
		this->m_thor[it->first] = it->second;
	}
}

namespace RubySFML {
namespace ColorGradient {
VALUE _alloc(VALUE self) {
	return wrap(new RubyColorGradient);
}

/*
 * call-seq:
 *   Color.new(red,green,blue[,alpha])
 *
 * creates a new Color Object.
*/
VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
//	VALUE red,green,blue,alpha;
//	rb_scan_args(argc, argv, "31",&red,&green,&blue,&alpha);

	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);

	return result;
}

VALUE _getColor(int argc,VALUE *argv,VALUE self)
{
	VALUE ridx,calc;
	rb_scan_args(argc, argv, "11",&ridx,&calc);
	float idx = NUM2DBL(ridx);

	if(!_self->hasColor(idx) && !RTEST(calc))
	{
		return Qnil;
	}



	return wrap(_self->getColor(idx,RTEST(calc)));

}

VALUE _setColor(VALUE self,VALUE ridx, VALUE color)
{
	float idx = NUM2DBL(ridx);

	if(NIL_P(color))
		_self->removeColor(idx);
	else
		_self->setColor(idx,unwrap<sf::Color>(color));

	return self;
}


VALUE _each_size(VALUE self)
{
	return UINT2NUM(_self->getSize());
}

VALUE _each_helper(float idx,sf::Color col)
{
	return rb_yield_values(2,DBL2NUM(idx),wrap(col));
}


VALUE _each(VALUE self)
{
	RETURN_SIZED_ENUMERATOR(self,0,NULL,_each_size);

	_self->iterate(_each_helper);

	return self;
}

VALUE _map_helper(RubyColorGradient *self,float idx, sf::Color col)
{
	VALUE val = _each_helper(idx,col);

	if(NIL_P(val))
		self->removeColor(idx,false);
	else
		self->setColor(idx,unwrap<sf::Color>(val));

	return val;
}


VALUE _map_self(VALUE self)
{
	RETURN_SIZED_ENUMERATOR(self,0,NULL,_each_size);

	_self->iterate(_map_helper);
	_self->rebuild();
	return self;
}

}
}
#endif

void Init_SFMLColorGradient(VALUE rb_mSFML)
{
#ifdef HAVE_THOR_GRAPHICS_HPP

	using namespace RubySFML::ColorGradient;

#if 0
	rb_mSFML = rb_define_module("SFML");

#endif


	rb_cSFMLColorGradient = rb_define_class_under(rb_mSFML,"ColorGradient",rb_cObject);
	rb_define_alloc_func(rb_cSFMLColorGradient,_alloc);

	rb_include_module(rb_cSFMLColorGradient,rb_mEnumerable);

	rb_define_method(rb_cSFMLColorGradient,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_private_method(rb_cSFMLColorGradient,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);

	rb_define_method(rb_cSFMLColorGradient,"[]",RUBY_METHOD_FUNC(_getColor),-1);
	rb_define_method(rb_cSFMLColorGradient,"[]=",RUBY_METHOD_FUNC(_setColor),2);

	rb_define_method(rb_cSFMLColorGradient,"each",RUBY_METHOD_FUNC(_each),0);
	rb_define_method(rb_cSFMLColorGradient,"map!",RUBY_METHOD_FUNC(_map_self),0);
#endif
}
