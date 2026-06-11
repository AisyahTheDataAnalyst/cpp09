/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pair.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 08:21:21 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/11 17:52:37 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pair.hpp"

Pair::Pair() : _bigger(Element()), _smaller(Element()) {}

Pair::Pair(const Element &a, const Element &b)
:	_bigger(a > b ? a : b),
	_smaller(a < b ? a : b)
{}

Pair::Pair(const Pair &other)
:	_bigger(other._bigger), _smaller(other._smaller) {}

Pair &Pair::operator=(const Pair &other)
{
	if (this != &other)
	{
		this->_bigger = other._bigger;
		this->_smaller = other._smaller;
	}
	return *this;
}

Pair &Pair::operator()(const Element &a, const Element &b)
{
	this->_bigger = a > b ? a : b;
	this->_smaller = a < b ? a : b;
	return *this;
}

Pair::~Pair() {}

const Element &Pair::getBigger() const {return _bigger;}

const Element &Pair::getSmaller() const {return _smaller;}

