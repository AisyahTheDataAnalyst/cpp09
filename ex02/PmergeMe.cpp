/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:59:04 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/14 14:12:10 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// ==========================
// |	PUBLIC FUNCTIONS	|
// ==========================

// Public OCF

// Parameterized Constructor
// All parsing is here 
PmergeMe::PmergeMe(int ac, char **av)
{
	for (int i = 1; i < ac; ++i)
	{
		int num = _isValidArg(av[i]);
		_vector.push_back(num);
		_deque.push_back(num);
	}
	_rawSequence = _vector;
	_isSorted(false, _rawSequence);
	// _printNumbers(BEFORE);
}

// Destructor
PmergeMe::~PmergeMe() {}


// Public member functions

// Convert the difference to microseconds
// Multiply by 1,000,000 first to avoid integer division truncation
void PmergeMe::activate()
{
	std::clock_t start, end;
	double vElapse_microseconds; //, dElapse_microseconds;

	start = std::clock();
	_theFordJohnsonAlgo();
	// _isSorted(true, _vector);
	end = std::clock();
	vElapse_microseconds = double(end - start) * 1000000.0 / CLOCKS_PER_SEC;

	
	// start = std::clock();
	// _theFordJohnsonAlgo(_deque);
	// _isSorted(true, _deque);
	// end = std::clock();
	// dElapse_microseconds = double(end - start) * 1000000.0 / CLOCKS_PER_SEC;


	_printNumbers(BEFORE);
	_printNumbers(AFTER);
	_printTime(vElapse_microseconds, "vector");
	std::cout << "comparison counts: " << Element::comparisonCount << std::endl;
	std::cout << "total numbers: " << _vector.size() << std::endl;
	// _printTime(dElapse_microseconds, "deque");
}


// ==============================
// |     PRIVATE FUNCTIONS		|
// ==============================

// Private OCF - no need to define in .cpp

// Private member functions

// Must be: (must use the merge-insert sort algorithm to sort the positive integer sequence)
// 1. Digits
// 2. Positive interger 
// 3. Not overflow
// 4. Dupes? Accept => easier than make it non-dupes only
int PmergeMe::_isValidArg(std::string av)
{
	// 1. Digit characters only
	// - No '-' or '+' too
	if (!(av.find_first_not_of("0123456789") == std::string::npos))
		throw std::invalid_argument("Invalid argument - invalid character or negative number");
	
	// 2. Positive interger
	// 3. not overflow interger
	double avLong = std::atol(av.c_str());
	if (!(avLong >= 0 || avLong <= INT_MAX))
		throw std::invalid_argument("Invalid argument - overflow");

	return std::atoi(av.c_str());
}

void PmergeMe::_isSorted(bool wantedScenario, std::vector<int> &container)
{
	bool sorted = (std::adjacent_find(container.begin(), container.end(), std::greater<int>()) == container.end());
	if (sorted != wantedScenario && sorted == true)
		throw std::invalid_argument("Sorted arguments");
	if (sorted != wantedScenario && sorted == false)
		throw std::invalid_argument("Unsorted arguments");
}

void PmergeMe::_printNumbers(int when)
{
	if (when == BEFORE)
	{
		std::cout << "Before:\t";
		for (std::size_t i = 0; i < _rawSequence.size(); ++i)
			std::cout << _rawSequence[i] << " ";
		std::cout << std::endl;
	}
	else
	{
		std::cout << "After:\t";
		for (std::size_t i = 0; i < _vector.size(); ++i)
			std::cout << _vector[i] << " ";
		std::cout << std::endl;		
	}
}

void PmergeMe::_printTime(double elapsedTime, std::string contName)
{
	std::cout 
	<< std::fixed
	<< "Time to process a range of " << _vector.size() << " elements with std::" << contName << " : " << elapsedTime << " us" << std::endl;
}
