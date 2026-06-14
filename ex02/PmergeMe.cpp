/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:59:04 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/14 20:23:12 by aimokhta         ###   ########.fr       */
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
	_isSorted(false, _vector);
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
	double vElapse_microseconds, dElapse_microseconds;

	Element::comparisonBool = true;
	start = std::clock();
	_theFordJohnsonAlgo<std::vector<Element>, std::vector<int> >(_vector);
	end = std::clock();
	Element::comparisonBool = false;
	vElapse_microseconds = double(end - start) * 1000000.0 / CLOCKS_PER_SEC;

	
	// Element::comparisonBool = true;
	start = std::clock();
	_theFordJohnsonAlgo<std::deque<Element>, std::deque<int> >(_deque);
	end = std::clock();
	// Element::comparisonBool = false;
	dElapse_microseconds = double(end - start) * 1000000.0 / CLOCKS_PER_SEC;

	_isSorted(true, _vector);
	// _isSorted(true, _deque);
	_printNumbers(BEFORE);
	_printNumbers(AFTER);
	_printTime(vElapse_microseconds, "vector");
	_printTime(dElapse_microseconds, "deque");
	std::cout << "comparison counts: " << Element::comparisonCount << std::endl;
	std::cout << "total numbers: " << _vector.size() << std::endl;
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

// Jacobsthal Sequence is for:
// upon pend chain
// determine sequence of PEND CHAIN'S INDEX that should first be inserted into the main chain
const std::vector<int> PmergeMe::_jacobsthalSequence(std::size_t pendSize)
{
	if (pendSize == 0)
		throw std::invalid_argument("Pend's size is invalidly zero");
	
	
	// 1. Construct JacobsthalSeq Sequence (0,1,1,3,5,11, .....)
	// the 1st 2 numbers are fixed
	std::vector<int> jacobsthalSeq;
	jacobsthalSeq.push_back(0);
	jacobsthalSeq.push_back(1);
	
	// Jacobsthal Sequence's formula: 
	// current = prev + 2 × (prev of the prev)
	while (1)
	{
		std::size_t current = jacobsthalSeq[jacobsthalSeq.size() - 1] + 2 * jacobsthalSeq[jacobsthalSeq.size() - 2];
		jacobsthalSeq.push_back(static_cast<int>(current));
		if (current >= pendSize)
			break;
	}
	if (jacobsthalSeq.size() >= 3)
		jacobsthalSeq.erase(jacobsthalSeq.begin() + 1);

	// debug print
	// std::cerr << "JS before full with pendsize of " << pendSize << std::endl; 
	// for (std::size_t i = 0; i < jacobsthalSeq.size(); ++i)
	// 	std::cerr << "order: " << jacobsthalSeq[i] << std::endl; 
	// std::cerr << std::endl; 
	//

	std::vector<int> fullInsertionOrder;
	fullInsertionOrder.push_back(0);
	std::size_t latestSeq = 0;

	for (std::size_t i = 1; i < jacobsthalSeq.size(); ++i) // 0, 1, 1, 3, 5 , pemdsize == 5
	{
		std::size_t currSeq = jacobsthalSeq[i];
		if (currSeq == latestSeq)
			continue;

		if (currSeq >= pendSize)
			currSeq = pendSize - 1;
		
		for (std::size_t order = currSeq; order > latestSeq; --order)
			fullInsertionOrder.push_back(static_cast<int>(order));

		latestSeq = currSeq;
		if (latestSeq >= pendSize - 1)
			break;
	}

	// debug print
	// std::cerr << "fullorderJS" << std::endl; 
	// for (std::size_t i = 0; i < fullInsertionOrder.size(); ++i)
	// 	std::cerr << "order: " << fullInsertionOrder[i] << std::endl; 
	// std::cerr << std::endl; 
	//
		
	return fullInsertionOrder;
}

void PmergeMe::_isSorted(bool wantedScenario, std::vector<int> &container)
{
	bool sorted = (std::adjacent_find(container.begin(), container.end(), std::greater<int>()) == container.end());
	if (sorted != wantedScenario && sorted == true)
		throw std::invalid_argument("Sorted arguments");
	if (sorted != wantedScenario && sorted == false)
		throw std::invalid_argument("Unsorted arguments");
}