/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:25:52 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/15 11:12:32 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Must have 2 arguments: ./btc [input file]" << std::endl;
		return 1;
	}
	
	// std::setprecision(n) 				===> sets the total number of significant digits displayed, n (both before and after the decimal point combined)
	// std::fixed << std::setprecision(n)	===> rule changes to => Exactly n digits only after decimal point
	//! for this exercise 					===> must without std::fixed std::cout can dynamically drop unnecessary trailing 0

	// comment / uncomment below to show the effect of using this to evaluator
	std::cout << std::setprecision(10);
	
	try
	{
		// not related & not suppose to handle - encoding and file extension control - leon said
		// BitcoinExchange bitcoin; -> cannot, coz wont be taking the argument of av[1]
		BitcoinExchange bitcoin("perfectData.csv", av[1]);
		bitcoin.exchange();
	}
    catch (std::exception &e)
    {
        std::cerr << RED << "Error: " << e.what() << RESET << std::endl;
        return 1; 
    }

	// double couldnt print 2nd decomal point number, without setprecision(10)
	// double num = 47115.93;
	// std::cout << "testing only=> printing double num (47115.93): [" << num << "]" << std::endl; 

	return 0;
}
