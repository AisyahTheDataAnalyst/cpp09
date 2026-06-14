/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:59:15 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/14 21:59:26 by aimokhta         ###   ########.fr       */
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
# include <ctime>		// std::clock(), CLOCKS_PER_SEC;
# include <iomanip>		// std::setprecision
# include <vector>
# include <deque>
# include "Pair.hpp"

// Macros
# define BEFORE 0
# define AFTER 1
	
// Custom Class
class PmergeMe
{
	private:
		// variables
		std::vector<int>	_vector;
		std::deque<int>		_deque;
		
		// OCF functions
		PmergeMe();
		PmergeMe(const PmergeMe &);
		PmergeMe &operator=(const PmergeMe &);
		
		// member functions
		int		_isValidArg(std::string);
		void	_printNumbers(int);
		void	_printTime(double, std::string);
		const std::vector<int> _jacobsthalSequence(std::size_t);
		
		template <typename ContainerI>
		void	_isSorted(bool, ContainerI &);
		
		template <typename ContainerE, typename ContainerI>
		void	_theFordJohnsonAlgo(ContainerI &);
		
		template <typename ContainerE, typename ContainerI>
		void	_pairMainPend(ContainerI &, ContainerE &, ContainerE &);
		
		template <typename ContainerE>
		void	_mergeSort(ContainerE &, ContainerE &);
		
		template <typename ContainerE>
		ContainerE &_insertionSort(ContainerE &, ContainerE &);
				
		template <typename ContainerE>
		void	_binarySearchInsertion(ContainerE &, Element);
		
		template <typename ContainerE, typename ContainerI>
		void	_overwriteResult(ContainerE &, ContainerI &);	
		
	public:
		PmergeMe(int, char **);
		~PmergeMe();
		void	activate();
};

# include "PmergeMe.tpp"

#endif