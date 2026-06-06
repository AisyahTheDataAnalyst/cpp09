/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:58:00 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/06 17:16:29 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

// ================================
// 	  RPN's public functions
// ================================

// === OCF ===

// Parameterized constructor
RPN::RPN(std::string str) 
: _str(str)
{}

// Destructor
RPN::~RPN()
{}


// ====== RPN's functions ======= 

// reject any invalid chars
// also following "You don’t need to process brackets or decimal numbers"
int RPN::run()
{
	// redundant
	// if (!validChar() || !validTotalDigitsOps())
	// 	return 1;
	
	try
	{
		for (std::size_t i = 0; i < _str.size(); ++i)
		{
			// print testing
			// std::cout << "_str[i] now is " << _str[i] << std::endl;
			
			// operator[] of std::string returns char&
			// for isspace && isdigit, casting char to unsigned char
			unsigned char c = static_cast<unsigned char>(_str[i]);
			
			// if & else if conditions - checking arguments' char for char validity & processing them
			if (std::isspace(c))
				continue;
			else if (std::isdigit(c))
				_processDigit(_str[i]); 
			else if (_isValidOperator(_str[i]))
				_processOperator(_str[i]);
			else
			{
				std::cerr << "ERROR: Invalid character";
				return 1;
			}
		}
		
		if (_digitStack.size() != 1)
		{
			std::cerr << "ERROR: Extra digits left in the stack after processing all operators";
			return 1;
		}

		std::cout << _digitStack.top() << std::endl;
		return 0;
	}
	
	// must put & to get the exact what()'s message to avoid object slicing of the derived class 
	// std::runtime_error is the derived class of base class std::exception
	//! wrong: catch(std::exception e)
	//* right: catch(std::exception &e)    #referencing the derived class
	//* right: catch(std::runtime_error e) #specific to the used derived class
	catch (std::runtime_error &e) 
	{
		// insufficient numbers ==> _digitStack <2 
		// invalid operation    ==> division by zero
		std::cerr << "ERROR: " << e.what();
		return 1;
	}
}


// =================================
// 	  RPN's private functions
// =================================

//  ======== Private OCF ==========    - no need to define in .cpp

// Default constructor
// RPN::RPN()
// {}
//
// Copy constructor
// RPN::RPN(const RPN &other)
// : _str(other._str), _digitStack(other._digitStack)
// {}
//
// Copy Assignment Operator
// RPN &RPN::operator=(const RPN &other)
// {
// 	if (this != &other)
// 	{
// 		this->_str = other._str;
// 		this->_digitStack = other._digitStack;
// 	}
// 	return *this;
// }


// ======== RPN's functions =========

void RPN::_processDigit(char c)
{
	// static_cast change the data type only, dosent char '1' to interger '1'
	// 	-	casting dosent change the character number we see on terminal
	//	-	computer dosent understand what we see visually on terminal
	// interger = char - '0';
	// -	needs to minus '0' to get what human see the visual number on terminal
	// -	or else compiler will just return the decimal ascii interger of character c from the ascii table
	int num = c - '0';
	_digitStack.push(num);

	// print testing 
	// to demonstrate & prove that computer understand based on ascii, not what human see visually on terminal
	// try to static_cast<int>(c) instead of [- '0'] -> it dosent work
	// std::cout << "num in string now is " << num << std::endl;
}

bool RPN::_isValidOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return true;
	return false;
}

void RPN::_processOperator(char c)
{
	if (_digitStack.size() < 2)
		throw std::runtime_error("Insufficient digits in stack to process operator");
	
	// 1 - the most top number will be leftsided number in operation
	int leftNum;
	leftNum = _digitStack.top();
	_digitStack.pop();
	
	// 2 - next most top number will be rightsided number in operation
	int rightNum;
	rightNum = _digitStack.top();
	_digitStack.pop();
	
	// print testing
	// std::cout << "rightnum now is << " << rightNum << std::endl;
	// std::cout << "operator now is " << c << std::endl;
	// std::cout << "leftnum now is << " << leftNum << std::endl;

	// 3.0 - push  the result of operation back to the stack
	// 3.1 - for next operation, current result will be the leftNum
	if (c == '+')
		_digitStack.push(rightNum + leftNum);
	else if (c == '-')
		_digitStack.push(rightNum - leftNum);
	else if (c == '*')
		_digitStack.push(rightNum * leftNum);
	else if (c == '/')
	{
		if (leftNum == 0)
			throw std::runtime_error("Invalid division by zero");
		_digitStack.push(rightNum + leftNum);
	}
}

// redundant functions
// bool RPN::validChar()
// {	
// 	for (int i = 0; i < _str.size(); ++i)
// 	{
// 		if (std::isspace(_str[i]) || std::isdigit(_str[i]))
// 			continue;
// 		if (_str[i] == '+' || _str[i] == '-' || _str[i] == '*' || _str[i] == '/')
// 			continue;
// 		else
// 			return _errMsg("Invalid char"), false;	
// 	}
// 	return true;
// }
//
// bool RPN::validTotalDigitsOps()
// {
// 	int digits = 0;
// 	int operators = 0;
//
// 	for (int i = 0; i < _str.size(); ++i)
// 	{
// 		if (std::isdigit(_str[i]))
// 			++digits;
// 		if (_str[i] == '+' || _str[i] == '-' || _str[i] == '/' || _str[i] == '*')
// 			++operators;
// 		continue;
// 	}
//
// 	if (!(digits >= 2 || operators >= 1))
// 		return _errMsg("Insufficient number of digits or operators"), false;
// 	if (!(digits == operators - 1))
// 		return _errMsg("Inbalance total numbers of digits and operators"), false;
// 	return true;
// }