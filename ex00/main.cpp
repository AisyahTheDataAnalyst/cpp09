/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:25:52 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/09 17:46:23 by aimokhta         ###   ########.fr       */
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
	
	// std::setprecision(10) => //!learn more
	// std::fixed => //!learn more
	//! must without std::fixed after std::cout so std::cout can dynamically drop unnecessary trailing 0
	// std::cout << std::fixed;
	// std::cout << std::setprecision(10);
	
	try
	{
		// not related & not suppose to handle - encoding and file extension control - leon said
		// BitcoinExchange bitcoin; -> cannot, coz wont be taking the argument of av[1]
		BitcoinExchange bitcoin("perfectData.csv", av[1]);
		bitcoin.exchange();
	}
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; 
    }

	// double couldnt print 2nd decomal point number, without setprecision(10)
	// double num = 47115.93;
	// std::cout << "testing only=> printing double num (47115.93): [" << num << "]" << std::endl; 

	return 0;
}
