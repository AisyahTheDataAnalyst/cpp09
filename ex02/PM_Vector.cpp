/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PM_Vector.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:17:51 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/11 22:57:26 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void PmergeMe::_FordJohnsonAlgo(Vector &vect)
{
	// two main chains in dealing with Ford Johnson Algorithm
	std::vector<Element>	main;
	std::vector<Element>	pend;
	
	// =============================================================
	//	STEP 1 ===> PAIRING & PUSH TO MAIN CHAIN & PENDING CHAIN
	// =============================================================
	_pairingMainPend(vect, main, pend);
	
	// =============================================================
	//	STEP 2 ===> RECURSIVELY COMPARE BIGGEST WITH BIGGEST
	// =============================================================
	_recursiveMergeSort(main, pend);

	
	

	
}

void PmergeMe::_pairingMainPend(Vector &vect, std::vector<Element> &main, std::vector<Element> &pend)
{
	// all of list of will used/ possibly used initializations: 
	Element a;
	Element b;
	Element staggerElement;
	Pair	pair;

	std::size_t i = 0;
	int id = 0;
	for (; i + 1 < vect.cont.size(); ++i && ++i)
	{
		for (; ; ++id)
		{
			a = Element(vect.cont[i], id);
			b = Element(vect.cont[i + 1], id);
			Pair pair(a, b);
			main.push_back(pair.getBigger());
			pend.push_back(pair.getSmaller());
		}
	}
	if (i < vect.cont.size())
	{
		staggerElement = Element(vect.cont[i], id);
		pend.push_back(staggerElement);
	}
}

void PmergeMe::_recursiveMergeSort(std::vector<Element> &main, std::vector<Element> &pend)
{
	Pair					pair;
	std::vector<Element>	newMain;
	std::vector<Element>	newPend;
	Element					staggerElement;

	if (main.size() <= 1)
	{
		main.insert(main.begin(), *pend.begin());
		pend.erase(pend.begin());						






		return;
	}
		
	std::size_t i = 0;
	for (; i + 1 < main.size(); ++i && ++i)
	{
		pair(main[i], main[i + 1]);
		newMain.push_back(pair.getBigger());
		newPend.push_back(pair.getSmaller());
	}
	if (i < main.size())
	{
		staggerElement = main[i];
		newPend.push_back(staggerElement);
	}
	_recursiveMergeSort(newMain, newPend);
}

std::vector<int> PmergeMe::_jacobthal(std::vector<Element> &main)
{
	// 1. Construct Jacobthal Sequence (0,1,1,3,5,7,11, .....)
	std::vector<int> jacobthal;
	std::size_t prev;
	std::size_t prevPrev;
	std::size_t current;
	std::size_t lastMainIndex;
	
	// these 1st 2 numbers are fixed
	jacobthal.push_back(0);
	jacobthal.push_back(1);
	
	// jacobthalSeq's formula: current = prev + 2 × (prev of the prev)
	prev			= *(jacobthal.end() - 1);
	prevPrev		= *(jacobthal.end() - 2);
	current			= prev + 2 * prevPrev;
	while (current < main.size())
	{
		jacobthal.push_back(current);
		prev		= *(jacobthal.end() - 1);
		prevPrev	= *(jacobthal.end() - 2);
		current		= prev + 2 * prevPrev;
	}
	
	lastMainIndex = main.size() - 1;
	if (current >= main.size() && jacobthal.back() != lastMainIndex)
	{
		current = lastMainIndex;
		jacobthal.push_back(current);
	}
	
	
	// 2. Build full Jacobthal Order (0 -> 1 -> 3,2 -> 5,4 -> 7,6 -> 11,.....)
	std::vector<int>::iterator dupePos;
	std::vector<int>::iterator insertPos;
	int prevNum;
	int nextNum;
	int insertNum;
	std::size_t i = 0;
	
	for (; i + 1 < jacobthal.size(); ++i)
	{
		if (jacobthal[i] + 1 == jacobthal[i + 1])	// first 2 sequence (0,1)
			continue;
		if (jacobthal[i] == jacobthal[i + 1])		// 2nd & 3rd sequence(1,3) -> (1,3)
		{	
			dupePos = find(jacobthal.begin(), jacobthal.end(), jacobthal[i]);
			jacobthal.erase(dupePos);
			++i;
			break;
		}
	}
	
	for (; i < jacobthal.size(); ++i)
	{
		if (jacobthal[i] > jacobthal[i - 1])
		{
			prevNum = jacobthal[i - 1];
			insertNum = jacobthal[i] - 1;
			while (insertNum - 1 != prevNum)
			{
				if (i + 1 < jacobthal.size())
				{
					nextNum = jacobthal[i + 1];
					insertPos = find(jacobthal.begin(), jacobthal.end(), nextNum);
				}
				else
					insertPos = jacobthal.end();

				jacobthal.insert(insertPos, insertNum);
				insertNum -= 1;				
			}
		}
	}

	return jacobthal;
}
