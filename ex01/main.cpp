/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:57:20 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/05 16:34:08 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/*
	RPN =  Reverse Polish Notation
	 A calculator for single digit numbers only,
	 with the 4 operations (*, +, -, /)
	* cannot be divided by 0 - rule of subject
	* no dupes processd - my choice
	* 
*/

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Must have 2 arguments: \"./RPN [Reverse Polish Notation's argument]";
		return 1;
	}
	
	RPN calculator(av[1]);
	return calculator.run();
};