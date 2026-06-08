/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:25:52 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/08 09:10:07 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Must have 2 arguments: ./btc [input file]";
		return 1;
	}
	
	try
	{
		// not related & not suppose to handle - encoding and file extension control - leon said
		// BitcoinExchange bitcoin; -> cannot, coz wont be taking the argument of av[1]
		BitcoinExchange bitcoin("perfectData.csv", av[1]);
		return bitcoin.exchange();
	}
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; 
    }
}
