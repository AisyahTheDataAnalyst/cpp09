/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:58:12 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/05 18:42:58 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

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

// Libraries
# include <iostream>	// std::cerr 
# include <cctype> 		// std::isspace
# include <string>		// std::string
# include <stack>		// std::stack
# include <exception>	// std::runtime_error
# include <list>		// std::list

class RPN
{
	private:
		// private variables
		std::string _str;
		std::stack<int, std::list<int> > _digitStack;

		// private OCF methods
		RPN();
		RPN(const RPN &);
		RPN &operator=(const RPN &);

		// private class methods
		void _processDigit(char);
		bool _isValidOperator(char);
		void _processOperator(char);
		//
		// bool validChar();
		// bool validTotalDigitsOps();

	public:
		// public OCF methods
		RPN(std::string);
		~RPN();

		// public class methods
		int run();
};

#endif