/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:59:15 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/09 19:47:03 by aimokhta         ###   ########.fr       */
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
# define RL_CYAN		"\001\033[1;36m\002"
# define RL_COLOR		"\001\033[0m\002"

// Libraries & structs
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
# include "Deque.hpp"
# include "Vector.hpp"

// PMERGEME RULES:
// - must use the merge-insert sort algorithm to sort the positive integer sequence.
// - To clarify, yes, you need to use the Ford-Johnson algorithm. source: subjectpdf hyperlink it
// - If an error occurs during program execution, an error message should be displayed on the standard error.
// - You must use at least two different containers in your code to validate this exercise. 
// - Your program must be able to handle at least 3000 different integers.
// - It is strongly advised to implement your algorithm for each container (same algo on both container) and thus to avoid using a generic function.
// - The format for the display of the time used to carry out your sorting is free 
// 	but the precision chosen must allow to clearly see the difference between the two containers used.
// - The indication of the time is deliberately strange in this example.
// - Of course you have to indicate the time used to perform all your operations, both the sorting part and the data management part.
// - The management of errors related to duplicates is left to your discretion.
// - Warning: The container(s) you used in the previous exercises are forbidden here.
// - PRINTING OUTPUT:
	// Here are some additional guidelines on the information you should display line by line on the standard output:
	// • 1st line - explicit text followed by the unsorted positive integer sequence.
	// • 2nd line - explicit text followed by the sorted positive integer sequence.
	// • 3rd line - explicit text indicating the time taken by your algorithm, specifying the first container used to sort the positive integer sequence.
	// • 4th line - explicit text indicating the time used by your algorithm by specifying the second container used to sort the positive integer sequence.


// Macros
# define BEFORE 0
# define AFTER 1
	
// Custom Class/Structs
class PmergeMe
{
	private:
		// private variables
		Vector				_vector;
		Deque				_deque;
		std::vector<int>	_rawSequence;
		// long				_startTimeV; // maybe this is vect's struct variable
		// long				_finishTimeV; // maybe this is vect's struct variable
		// long				_startTimeD; // maybe this is deque's struct variable
		// long				_finishTimeD; // maybe this is deque's struct variable

		
		// private OCF functions
		PmergeMe();
		PmergeMe(const PmergeMe &);
		PmergeMe &operator=(const PmergeMe &);
		
		// private member functions
			// 1. UTILS
		const char	*_isDigits(const char *);	// check all the characters are just isspace() & isdigit()
		void		_isUnsorted(std::vector<int>);
		void		_printNumbers(int);
		void		_printTimes(long, std::string);

			// 2. SORTING
		

	public:
		// public OCF
		PmergeMe(int, char **);
		~PmergeMe();
		
		// public function members
		void		activate();
};

#endif