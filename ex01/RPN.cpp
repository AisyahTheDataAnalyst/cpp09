/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:58:00 by aimokhta          #+#    #+#             */
/*   Updated: 2026/05/15 17:27:41 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/*
	============================
	  RPN's private functions
	============================
*/

// Default constructor
// RPN::RPN()
// : _str()
// {}



/*
	==========================
	  RPN's public functions
	==========================
*/


// =========
//    OCF
// =========

// Parameterized constructor
RPN::RPN(std::string str) 
: _str(str)
{}

// Copy constructor
RPN::RPN(const RPN &other)
: _str(other._str)
{}

// Copy Assignment Operator
RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		this->_str = other._str;
	}
	return *this;
}

// Destructor
RPN::~RPN()
{}


// ===============
// RPN's functions
// ===============

int RPN::run()
{
	if (!validChar() || !validTotalDigitsOp());
		return 1;
	
	
}

bool RPN::validChar()
{	
	for (int i = 0; i < _str.size(); ++i)
	{
		if (std::isspace(_str[i]) || std::isdigit(_str[i]))
			continue;
		if (_str[i] == '+' || _str[i] == '-' || _str[i] == '*' || _str[i] == '/')
			continue;
		else
			return false;	
	}
	return true;
}

bool RPN::validTotalDigitsOp()
{
	int digits = 0;
	int operators = 0;

	for (int i = 0; i < _str.size(); ++i)
	{
		if (std::isdigit(_str[i]))
			++digits;
		if (_str[i] == '+' || _str[i] == '-' || _str[i] == '/' || _str[i] == '*')
			++operators;
		continue;
	}
	
	if (!digits || !operators)
		return errMsg("Invalid 0 number of digits and/or operators"), false;
	if (digits <= 1)
		return errMsg("Insufficient number of digits"), false;
	if (!(digits == operators - 1))
		return errMsg("Inbalance total numbers of digits and operators"), false;
	return true;
}

void RPN::errMsg(const char *msg)
{
	std::cerr << RED << msg; 
}


