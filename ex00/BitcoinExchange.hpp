/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:25:49 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/15 11:20:10 by aimokhta         ###   ########.fr       */
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
# include <string>		// std::string, std::getline
# include <map>			// std::map
# include <fstream>		// std::ifstream, .is_open()
# include <sstream>		// std::stringstream
# include <cfloat>		// FLT_MIN, FLT_MAX
# include <cstdlib>		// std::atoi
# include <iomanip>		// std::setprecision()

// Custom Class
class BitcoinExchange
{
	private:
		// private variables
		std::ifstream _dataFile;
		std::ifstream _inputFile;
		std::map<std::string, double> _perfectData_map;	
		// map
		// - for storing perfectData.csv
		// - stores double instead coz float couldnt accurately represents certain numbers
		//   which does not represent exchange rate of 0.32 as in the perfectData.csv
		
		// private OCF
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &);
		BitcoinExchange &operator=(const BitcoinExchange &);		
		
		// private function members 
		void	saveDataIntoMap();
		void	inputDateValidation(std::string, std::string);
		double	inputValueValidation(std::string, std::string);
		double	matchingDataDate(std::string, std::string);
		
	public:
		// public OCF
		BitcoinExchange(std::string, std::string);
		~BitcoinExchange();
		
		// public methods
		void	exchange();
};




#endif