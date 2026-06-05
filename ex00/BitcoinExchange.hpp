/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:25:49 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/05 19:48:55 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Include Guards or Header Guards
#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

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
# include <iostream>	// std::cout, std::cerr
# include <string>		// std::string
# include <map>			// std::map
// # include <



class BitcoinExchange
{
	private:
		// private variables
		std::map<std::string, double> _perfectData;	// for storing perfectData.csv
		
		// private OCF
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &);
		BitcoinExchange &operator=(const BitcoinExchange &);		
		
		// private function members 
		
		
	public:
		// public OCF
		BitcoinExchange(argument);
		~BitcoinExchange();
		
		// public methods
		
};




#endif