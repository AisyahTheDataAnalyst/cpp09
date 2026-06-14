/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:58:35 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/14 17:58:51 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// PMERGEME RULES:
// - must use the merge-insert sort algorithm to sort the positive integer sequence.
// - To clarify, yes, you need to use the Ford-Johnson algorithm. source: subjectpdf hyperlink it
// - If an error occurs during program execution, an error message should be displayed on the standard error.
// - You must use at least two different containers in your code to validate this exercise. 
// - Your program must be able to handle at least 3000 different integers.
// - It is strongly advised to implement your algorithm for each container (same algo on both container) and thus to avoid using a generic function.
// - The format for the display of the time used to carry out your sorting is free but the precision chosen must allow to clearly see the difference between the two containers used.
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

/*
	helpful articles:
	1. https://medium.com/@mohammad.ali.ibrahim.525/ford-johnson-algorithm-merge-insertion-4b024f0c3d42
	2. https://medium.com/@toukmati2000/cpp09-ford-johnson-algorithm-e6ad43288d4b
	3. https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91
	4. breathe and go step by step, you can do this! :))))
*/

int main(int ac, char **av)
{
	if (ac <= 3)
	{
		std::cerr << "Error: Insufficient arguments" << std::endl;
		return 1;
	}

	try 
	{
		PmergeMe jacobs(ac, av);
		jacobs.activate();
		return 0;	
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
}