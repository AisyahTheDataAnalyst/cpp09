/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:59:15 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/11 21:50:10 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

// Colours
# define WHITE			"\033[1;37m"
# define CYAN			"\033[1;36m"
# define PURPLE			"\033[1;35m"
# define BLUE			"\033[1;34m"
# define YELLOW			"\033[1;33m"
# define GREEN			"\033[1;32m"
# define RED			"\033[1;31m"
# define BLACK			"\033[1;30m"
# define LIGHT_CYAN		"\033[0;96m"
# define LIGHT_MAGENTA	"\033[0;95m"
# define LIGHT_BLUE		"\033[0;94m"
# define LIGHT_YELLOW	"\033[0;93m"
# define LIGHT_GREEN	"\033[0;92m"
# define LIGHT_RED		"\033[0;91m"
# define GRAY			"\033[0;90m"
# define RESET			"\033[0m"

// Libraries
# include <iostream>	// std::cout, std::cerr
# include <sstream>		// std::stringstream
# include <cctype>		// std::isspace, std::isdigit
# include <cstring>		// std::strlen
# include <ctime>		// std::time(NULL)
# include <cstdlib>		// std::atoi
# include <unistd.h>	// sleep
# include <sys/time.h>	// gettimeofday()
# include <algorithm>	// std::adjacent_find()
# include <functional>	// std::greater<int>()
# include <climits>		// INT_MAX
# include "Containers.hpp"
# include "Pair.hpp"

// Macros
# define BEFORE 0
# define AFTER 1
	
// Custom Class
class PmergeMe : protected Vector, protected Deque
{
	private:
		// variables
		Vector				_vector;
		Deque				_deque;
		std::vector<int>	_rawSequence;
		
		// OCF functions
		PmergeMe();
		PmergeMe(const PmergeMe &);
		PmergeMe &operator=(const PmergeMe &);
		
		// member functions
				// 1. UTILS
		int					_isValidArg(std::string);
		void				_isSorted(bool, std::vector<int> &);
		void				_isSorted(bool, std::deque<int> &);
		void				_printNumbers(int);
		void				_printTime(long, std::string);
				// 2. SORTING [Vector]
		void				_FordJohnsonAlgo(Vector &);
		void				_pairingMainPend(Vector &vect, std::vector<Element> &, std::vector<Element> &);
		void				_recursiveMergeSort(std::vector<Element> &, std::vector<Element> &);
		std::vector<int>	_jacobthal(std::vector<Element> &);
		void				_binarySearch(Vector &);
				// 3. SORTING [Deque]
		void				_FordJohnsonAlgo(Deque &);
		void				_binarySearch(Deque &);
		void				_jacobthalSeq(Deque &);

	public:
		PmergeMe(int, char **);
		~PmergeMe();
		void				activate();
};

#endif