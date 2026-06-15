/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Element.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 08:29:10 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/14 23:31:33 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Element.hpp"

int Element::comparisonCount = 0;

bool Element::comparisonBool = false;

Element::Element(int value, int id) : _value(value), _id() 
{ 
	_id.push_back(id); 
}

Element::Element(const Element &other) : _value(other._value), _id(other._id) {}

Element::~Element() {}

int Element::getValue() const {return _value;}

int Element::getId() const {return _id.back();}

void Element::pushId(int additionalId)	{_id.push_back(additionalId);}

void Element::popId()	{_id.pop_back();}

bool Element::operator>=(const Element &other) const
{
	if (comparisonBool == true)
		++comparisonCount;
	if (this->_value >= other._value)
		return true;
	return false;
}

bool Element::operator<=(const Element &other) const
{
	if (comparisonBool == true)
		++comparisonCount;
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
	if (comparisonBool == true)
		++comparisonCount;
	if (this->_value == other._value)
		return true;
	return false;
}

bool Element::operator>(const Element &other) const
{
	if (comparisonBool == true)
		++comparisonCount;
	if (this->_value > other._value)
		return true;
	return false;
}

bool Element::operator<(const Element &other) const
{
	if (comparisonBool == true)
		++comparisonCount;
	if (this->_value < other._value)
		return true;
	return false;
}
