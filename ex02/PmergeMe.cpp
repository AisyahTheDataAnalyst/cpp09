/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:59:04 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/11 19:33:01 by aimokhta         ###   ########.fr       */
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
		_vector.cont.push_back(num);
		_deque.cont.push_back(num);
	}
	_rawSequence = _vector.cont;
	
	_isSorted(false, _rawSequence);
}

// Destructor
PmergeMe::~PmergeMe() {}


// Public member functions
void PmergeMe::activate()
{
	struct timeval start, end;
	long sec, microsec;			// get precision both in seconds and remaining microseconds


	gettimeofday(&start, NULL);
	_FordJohnsonAlgo(_vector);
	usleep(10);
	gettimeofday(&end, NULL);
	sec = end.tv_sec - start.tv_sec;
	microsec = end.tv_usec - start.tv_usec;
	_vector.elapseTime = (sec * 1000000) + microsec;

	
	gettimeofday(&start, NULL);
	_FordJohnsonAlgo(_deque);
	usleep(100);
	gettimeofday(&end, NULL);
	sec = end.tv_sec - start.tv_sec;
	microsec = end.tv_usec - start.tv_usec;
	_deque.elapseTime = (sec * 1000000) + microsec;


	_printNumbers(BEFORE);
	_printNumbers(AFTER);
	_printTime(_vector.elapseTime, "vector");
	_printTime(_deque.elapseTime, "deque");
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
	if (sorted == wantedScenario)
		throw std::invalid_argument("Sorted arguments");
}

void PmergeMe::_isSorted(bool wantedScenario, std::deque<int> &container)
{
	bool sorted = (std::adjacent_find(container.begin(), container.end(), std::greater<int>()) == container.end());
	if (sorted == wantedScenario)
		throw std::invalid_argument("Sorted arguments");
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
		for (std::size_t i = 0; i < _vector.cont.size(); ++i)
			std::cout << _vector.cont[i] << " ";
		std::cout << std::endl;		
	}
}

void PmergeMe::_printTime(long elapsedTime, std::string contName)
{
	std::cout 
	<< std::fixed
	<< "Time to process a range of " << _vector.cont.size() << " elements with std::" << contName << " : " << elapsedTime << " us" << std::endl;
}
