/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:59:04 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/09 19:50:01 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// ==========================
// |	PUBLIC FUNCTIONS	|
// ==========================

// Public OCF

// Parameterized Constructor
PmergeMe::PmergeMe(int ac, char **av)
{
	for (int i = 1; i < ac; ++i)
	{
		int num = std::atoi(_isDigits(av[i]));
		_vector.contnr.push_back(num);
		_deque.contnr.push_back(num);
	}
	_rawSequence = _vector.contnr;
	_isUnsorted(_rawSequence);
}

// Destructor
PmergeMe::~PmergeMe() {}


// Public member functions

void PmergeMe::activate()
{
	struct timeval start, end;
	long sec, microsec;			// get precision both in seconds and remaining microseconds


	gettimeofday(&start, NULL);
	// _vector.sort();
	usleep(10);
	gettimeofday(&end, NULL);
	sec = end.tv_sec - start.tv_sec;
	microsec = end.tv_usec - start.tv_usec;
	_vector.elapseTime = (sec * 1000000) + microsec;

	
	gettimeofday(&start, NULL);
	// _deque.sort();
	usleep(100);
	gettimeofday(&end, NULL);
	sec = end.tv_sec - start.tv_sec;
	microsec = end.tv_usec - start.tv_usec;
	_deque.elapseTime = (sec * 1000000) + microsec;


	_printNumbers(BEFORE);
	_printNumbers(AFTER);
	_printTimes(_vector.elapseTime, "vector");
	_printTimes(_deque.elapseTime, "deque");
}


// ==============================
// |     PRIVATE FUNCTIONS		|
// ==============================

// Private OCF - no need to define in .cpp

// Private member functions

const char *PmergeMe::_isDigits(const char *av)
{
	for (std::size_t i = 0; i < std::strlen(av); ++i)
	{
		unsigned char c = static_cast<unsigned char>(av[i]);	
		if (!std::isdigit(c))
			throw std::invalid_argument("Invalid argument");
	}
	return av;
}

void PmergeMe::_isUnsorted(std::vector<int> container)
{
	std::vector<int>::iterator it = std::adjacent_find(container.begin(), container.end(), std::greater<int>());
	if (it == container.end())
		throw std::invalid_argument("Sorted arguments");
}

void PmergeMe::_printNumbers(int when)
{
	// std::cout << ; 
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
		for (std::size_t i = 0; i < _vector.contnr.size(); ++i)
			std::cout << _vector.contnr[i] << " ";
		std::cout << std::endl;		
	}
}

void PmergeMe::_printTimes(long elapsedTime, std::string container)
{
	std::cout 
	<< std::fixed
	<< "Time to process a range of " << _vector.contnr.size() << " elements with std::" << container << " : " << elapsedTime << " us" << std::endl;
}
