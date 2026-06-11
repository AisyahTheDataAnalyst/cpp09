/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Element.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 08:29:10 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/11 17:36:34 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Element.hpp"

Element::Element() : _value(-1), _id(-1) {}

Element::Element(int value, int id) : _value(value), _id(id) {}

Element::Element(const Element &other) : _value(other._value), _id(other._id) {}

Element::~Element() {}

const int &Element::getValue() const {return _value;}

const int &Element::getId() const {return _id;}

bool Element::operator>=(const Element &other) const
{
	if (this->_value >= other._value)
		return true;
	return false;
}

bool Element::operator<=(const Element &other) const
{
	if (this->_value <= other._value)
		return true;
	return false;
}

Element &Element::operator=(const Element &other)
{
	if (this != &other)
	{
		this->_value = other._value;
		this->_id = other._id;
	}
	return *this;
}

bool Element::operator==(const Element &other) const
{
	if (this->_value == other._value)
		return true;
	return false;
}

bool Element::operator>(const Element &other) const
{
	if (this->_value > other._value)
		return true;
	return false;
}

bool Element::operator<(const Element &other) const
{
	if (this->_value < other._value)
		return true;
	return false;
}


