/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe2.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:17:51 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/14 14:10:51 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void PmergeMe::_theFordJohnsonAlgo()
{
	// two main chains in dealing with Ford Johnson Algorithm
	std::vector<Element>	main;
	std::vector<Element>	pend;
	std::vector<Element>	empty;
	
	// ====================================================================================================
	//	STEP 1 ===> PAIRING & CONSTRUCT MAIN CHAIN + PENDING CHAIN
	// ====================================================================================================
	_pairMainPend(main, pend);

	//
	// std::cerr << "main numbers: \n" << std::endl;
	// for (std::size_t i = 0; i < main.size(); ++i)
	// 	std::cerr << main[i].getValue() << " " << main[i].getId() << std::endl;
	// std::cerr << "here after pair\n pend numbers: \n" << std::endl;
	// for (std::size_t i = 0; i < pend.size(); ++i)
	// 	std::cerr << pend[i].getValue() << " " << pend[i].getId() << std::endl;
	//
	
	// ====================================================================================================
	//	STEP 2 ===> IMPLEMENT mergesort + (insertion sort + binary search insertion + jacobsthal sequence)
	// ====================================================================================================
	_mergeSort(main, pend);


	// ====================================================================================================
	//	STEP 3 ===> overwrite sortedMain into _vector
	// ====================================================================================================
	_overwriteResult(main);	
}

// this causes recursion
// - numbers processed by LIFO method / lazy / not fair
void PmergeMe::_pairMainPend(std::vector<Element> &main, std::vector<Element> &pend)
{
	std::size_t i = 0;
	int id = 0;
	// std::cerr << "size of vector: " << _vector.size() << std::endl;
	for (; i + 1 < _vector.size(); i += 2, ++id)
	{
		Pair pair(Element(_vector[i], id), Element(_vector[i + 1], id));
		main.push_back(pair.getBigger());
		pend.push_back(pair.getSmaller());
	}
	if (i < _vector.size())
	{
		Element staggerElement = Element(_vector[i], id);
		pend.push_back(staggerElement);
	}
}

// Recursion occurs here
// 1st, MergeSort starts
// when main finally left 1 number only, InsertionSort takes place
// InsertionSort uses BinarySearchInsertion upon main and JacobsthalSequence upon pend 
void PmergeMe::_mergeSort(std::vector<Element> &main, std::vector<Element> &pend) //, std::vector<Element> &pend)
{
	std::vector<Element>	newMain;
	std::vector<Element>	newPend;
	
	if (main.empty())
		throw std::invalid_argument("Main is invalidly empty");
	
	if (main.size() == 1)
	{
		main = _insertionSort(main, pend);
		return;
	}

	// 1. Pairing phase
	std::size_t i = 0;
	int id = 0;
	for (; i + 1 < main.size(); i += 2, ++id)
	{
		main[i].pushId(id);
		main[i + 1].pushId(id);
		Pair pair(main[i], main[i + 1]);
		newMain.push_back(pair.getBigger());
		newPend.push_back(pair.getSmaller());	
	}
	// handle staggler (odd element)
	if (main.size() % 2 != 0)
	{
		main.back().pushId(id);
		newPend.push_back(main.back());
	}


	// 2. Recursive -> sort the winner chain
	_mergeSort(newMain, newPend);
	
	// 3. Unwind phase: Assign the sorted winners back to main,
	// then insert this level's pend items into it.	
	main = newMain;
	main = _insertionSort(main, pend);
}

// 2.	InsertionSort = BinarySearchInsertion + JacobsthalSequence
// 1st - reorganize pend as main's id sequence
// 2nd - index 0 of pend is bruteforced/automatically inserted into index 0 of main
// 3rd - BSI + JS
std::vector<Element> &PmergeMe::_insertionSort(std::vector<Element> &main, std::vector<Element> &pend)
{	
	if (main.empty())
		throw std::invalid_argument("Main is invalidly empty");
	
	//
	// std::cerr << "original main:" << std::endl; 
	// for (std::size_t i = 0; i < main.size(); ++i)
	// 	std::cerr << main[i].getValue() << std::endl; 
	// std::cerr << "original pend:" << std::endl; 
	// for (std::size_t i = 0; i < pend.size(); ++i)
	// 	std::cerr << pend[i].getValue() << std::endl;
	// 
		
	// 2.1	Insertion sort when main.size() == 1 only
	if (main.size() == 1)			
	{
		const std::vector<int> jacobSeq = _jacobsthalSequence(pend.size());

		//
		// std::cerr << "jacobSeq full order:" << std::endl; 
		// for (std::size_t i = 0; i < jacobSeq.size(); ++i)
		// 	std::cerr << "order: " << jacobSeq[i] << std::endl; 
		// std::cerr << "\n\n\n" << std::endl; 
		//
		
		std::size_t i = 0;
		
		main.insert(main.begin(), pend[jacobSeq[i]]);
		++i;
		if (jacobSeq.size() > 1)
		{
			for (; i < jacobSeq.size(); ++i)
				if (jacobSeq[i] < static_cast<int>(pend.size()))
					_binarySearchInsertion(main, pend[jacobSeq[i]]);					
		}
				
		pend.clear();

		//
		// std::cerr << "sortedMain size 1: " << std::endl;
		// for (std::size_t i = 0; i < main.size(); ++i)
		// {
		// 	std::cerr << main[i].getValue() << std::endl;
		// }
		// std::cerr << std::endl;
		//

		for (std::size_t i = 0; i < main.size(); ++i)
			main[i].popId();

		return main;
	}
	
	// 2.2	Insertion sort when main.size() > 1
	// unsorted pend -> sortedPend
	// std::cerr << "here b4 loop sortedPend" << std::endl;
	
	std::vector<Element> sortedPend;
	
	for (std::size_t i = 0; i < main.size(); ++i)
	{
		sortedPend.push_back(pend[main[i].getId()]);
		sortedPend.back().popId();
		main[i].popId();
		// no
		// for (std::size_t j = 0; j < pend.size(); ++j)
		// {
		// 	if (pend[j].getId() == targetId)
		// 	{
		// 		sortedPend.push_back(pend[targetId]);
		// 		sortedPend.back().popId();
		// 		break;
		// 	}
		// }
		// no
		// if (targetId  < static_cast<int>(pend.size()))
		// {
		// 	sortedPend.push_back(pend[targetId ]);
		// 	sortedPend.back().popId();
		// }
	}
	if (pend.size() > main.size())
	{
		sortedPend.push_back(pend.back());
		sortedPend.back().popId();
	}
	
	//no
	// {
	// 	for (std::size_t i = 0; i < pend.size(); ++i)
	// 	{
	// 		bool isMatched = false;
	// 		for (std::size_t j = 0; j < main.size(); ++j)
	// 		{
	// 			if (main[j].getId() == pend[i].getId())
	// 			{
	// 				isMatched = true;
	// 				break;
	// 			}
	// 		}
	// 		if (!isMatched)
	// 		{
	// 			sortedPend.push_back(pend[i]);
	// 			sortedPend.back().popId();
	// 			break;
	// 		}
	// 	}
	// }
	//
	
	//
	// std::cerr << "sortedPend: " << std::endl;
	// for (std::size_t i = 0; i < sortedPend.size(); ++i)
	// {
	// 	std::cerr << sortedPend[i].getValue() << std::endl;
	// }
	// std::cerr << std::endl;
	//

	// finally can use jacobSeq upon sortedPend
	const std::vector<int> jacobSeq = _jacobsthalSequence(sortedPend.size());
	
	//
	// // std::cerr << "jacobSeq full order:" << std::endl; 
	// for (std::size_t i = 0; i < jacobSeq.size(); ++i)
	// 	std::cerr << "order: " << jacobSeq[i] << std::endl; 
	// std::cerr << "\n\n\n" << std::endl; 
	//
	
		
	for (std::size_t i = 0; i < jacobSeq.size(); ++i)
	{
		int targetedIndex  = jacobSeq[i];
		if (targetedIndex < static_cast<int>(sortedPend.size()))
		{
			if (i == 0)
				main.insert(main.begin(), sortedPend[targetedIndex]);
			else
				_binarySearchInsertion(main, sortedPend[targetedIndex]);		
		}
	}
	
	sortedPend.clear();
	pend.clear();
	
	// //
	// std::cerr << "sortedMain > 1: " << std::endl;
	// for (std::size_t i = 0; i < main.size(); ++i)
	// {
	// 	std::cerr << main[i].getValue() << std::endl;
	// }
	// std::cerr << std::endl;
	// //
	
	return main;
}

// Jacobsthal Sequence is for:
// upon pend chain
// determine sequence of PEND CHAIN'S INDEX that should first be inserted into the main chain
const std::vector<int> PmergeMe::_jacobsthalSequence(std::size_t pendSize)
{
	if (pendSize == 0)
		throw std::invalid_argument("Pend's size is invalidly zero");
	
	
	// 1. Construct JacobsthalSeq Sequence (0,1,1,3,5,11, .....)
	// the 1st 2 numbers are fixed
	std::vector<std::size_t> jacobsthalSeq;
	jacobsthalSeq.push_back(0);
	jacobsthalSeq.push_back(1);
	
	// Jacobsthal Sequence's formula: 
	// current = prev + 2 × (prev of the prev)
	while (1)
	{
		std::size_t current = jacobsthalSeq[jacobsthalSeq.size() - 1] + 2 * jacobsthalSeq[jacobsthalSeq.size() - 2];
		jacobsthalSeq.push_back(current);
		if (current >= pendSize)
			break;
	}
	if (jacobsthalSeq.size() >= 3)
		jacobsthalSeq.erase(jacobsthalSeq.begin() + 1);

	//
	// std::cerr << "JS before full with pendsize of " << pendSize << std::endl; 
	// for (std::size_t i = 0; i < jacobsthalSeq.size(); ++i)
	// 	std::cerr << "order: " << jacobsthalSeq[i] << std::endl; 
	// std::cerr << std::endl; 
	//

	std::vector<int> fullInsertionOrder;
	fullInsertionOrder.push_back(0);
	std::size_t latestSeq = 0;

	for (std::size_t i = 1; i < jacobsthalSeq.size(); ++i) // 0, 1, 1, 3, 5 , pemdsize == 5
	{
		std::size_t currSeq = jacobsthalSeq[i];
		if (currSeq == latestSeq)
			continue;

		if (currSeq >= pendSize)
			currSeq = pendSize - 1;
		
		for (std::size_t order = currSeq; order > latestSeq; --order)
			fullInsertionOrder.push_back(static_cast<int>(order));

		latestSeq = currSeq;
		if (latestSeq >= pendSize - 1)
			break;
	}

	//
	// std::cerr << "fullorderJS" << std::endl; 
	// for (std::size_t i = 0; i < fullInsertionOrder.size(); ++i)
	// 	std::cerr << "order: " << fullInsertionOrder[i] << std::endl; 
	// std::cerr << std::endl; 
	//
		
	return fullInsertionOrder;
	

	// // current = *(jacobsthalSeq.end() - 1) + 2 * *(jacobsthalSeq.end() - 2);
	// // std::cerr << "current = " << current << std::endl;
	// // while (current < pendSize)
	// // {
	// // 	jacobsthalSeq.push_back(current);
	// // 	current = *(jacobsthalSeq.end() - 1) + 2 * *(jacobsthalSeq.end() - 2);
	// // 	std::cerr << "current = " << current << std::endl;
	// // }
	//
	// // ex: size = 8
	// // jacobseq: 0,1,1,3,5 + 7 (instead of 11)
	// int pendLastIndex = pendSize - 1;
	// if (current >= pendSize && jacobsthalSeq.back() != pendLastIndex)
	// 	jacobsthalSeq.push_back(pendLastIndex);
	//
	// // remove 1 at the most beginning
	// // 0 -> auto bruteforced, reduce comparison
	// // first 1 -> remove, duplicate
	// // if (jacobsthalSeq.size() > 2)
	// // 	jacobsthalSeq.erase(jacobsthalSeq.begin() + 1);
	//
	// for (std::size_t j = 0; j < jacobsthalSeq.size(); ++j)
	// 	std::cerr << "jacobseq in index " << j << " = " << jacobsthalSeq[j] << std::endl;
	// std::cerr << "here after some jacobseq is formed" << std::endl;
	// std::cerr << "here b4 full jacobseq is formed" << std::endl;
	// // 2. Build full jacobsthal Order (0 -> 1 -> 3,2 -> 5,4 -> 11,10,9,8,7,6 -> .....)
	// std::vector<int>::iterator dupePos;
	// std::vector<int>::iterator insertPos;
	// int prevNum;
	// int nextNum;
	// int insertNum;
	// std::size_t i = 1;
	//
	// for (; i < jacobsthalSeq.size(); ++i)
	// {
	// 	if (jacobsthalSeq[i] > jacobsthalSeq[i - 1])
	// 	{
	// 		prevNum = jacobsthalSeq[i - 1];
	// 		insertNum = jacobsthalSeq[i] - 1;
	// 		while (insertNum - 1 != prevNum)
	// 		{
	// 			if (i + 1 < jacobsthalSeq.size())
	// 			{
	// 				nextNum = jacobsthalSeq[i + 1];
	// 				insertPos = find(jacobsthalSeq.begin(), jacobsthalSeq.end(), nextNum);
	// 			}
	// 			else
	// 				insertPos = jacobsthalSeq.end();
	//
	// 			jacobsthalSeq.insert(insertPos, insertNum);
	// 			insertNum -= 1;				
	// 		}
	// 	}
	// }
	// std::cerr << "here after full jacobseq is formed" << std::endl;
	// return jacobsthalSeq;
}

// Binary search insertion is for:
// upon main chain
// to determine which number of main chain that should pend chain be inserted before it.
void PmergeMe::_binarySearchInsertion(std::vector<Element> &sortedMain, Element pendElement)
{
	std::size_t start = 0;
	std::size_t end = sortedMain.size() - 1;
	
	while (start != end)
	{
		std::size_t mid = start + (end - start) / 2;
		if (pendElement < sortedMain[mid])
			end = mid;
		else
			start = mid + 1;
	}

	if (start < sortedMain.size() && sortedMain[start] < pendElement)
		sortedMain.insert(sortedMain.begin() + start + 1, pendElement);
	else
		sortedMain.insert(sortedMain.begin() + start, pendElement);

	
	// std::vector<Element>::iterator it = std::lower_bound(sortedMain.begin(), sortedMain.end(), pendElement);
	// sortedMain.insert(it, pendElement);
//
	// MIGHT NOT NEED THIS COZ ELEMENT HAS ALREADU AUTO COMPARISONCOUNT++ IN THEIR COMPARISON OPERATOR
	// std::size_t distance = std::distance(sortedMain.begin(), it);
	// Element::comparisonCount += static_cast<int>(std::ceil(std::log2(distance))); // ! study what ceil & log2 does
}

void PmergeMe::_overwriteResult(std::vector<Element> &main)
{
	for(std::size_t i = 0; i < _vector.size(); ++i)
		_vector[i] = main[i].getValue();
}



//! make templates function for overriding containers
//! fix PM.hpp to use templates and in this PM.tpp too
//! optimize jacobsthallSequence function to use more lago maybe
//! check comparisonCounts must within ideal numbers , check online or in the book whats the ideal numbers
//! check time is it nicely accurate
//! tidy up
//! cehck if i can use exception invailid_argument for these such cases, is it acceotable to use exception for these kind of events
//! prepaare full understanding why need Jacobstajl sequence, whats benefit of ford johnson algorithm, how to explain this easily to evaluators so they dont get overwhelmed

// void PmergeMe::_sort(std::vector<Element> &currMain, std::vector<Element> &currPend, std::vector<Element> &prevPend)
// {
// 	std::vector<Element>	newMain;
// 	std::vector<Element>	newPend;
// 	std::vector<Element>	sortedNewMain;
//
// 	std::vector<Element>	empty;
// 	empty.clear();
//	
// 	// 1.	Main chain mainly is merge sorted until only 1 number left in main chain
// 	// focus on currMain only
// 	if (currMain.size() > 1 && !currPend.empty())			
// 	{
// 		std::size_t i = 0;
// 		int id = 0;
// 		for (; i + 1 < currMain.size(); ++i && ++i)
// 		{
// 			for (; ;++id)
// 			{
// 				currMain[i].pushId(id);
// 				currMain[i + 1].pushId(id);
// 				Pair pair(currMain[i], currMain[i + 1]);
// 				newMain.push_back(pair.getBigger());
// 				newPend.push_back(pair.getSmaller());	
// 			}
// 		}
// 		if (i < currMain.size())
// 		{
// 			Element staggerElement = currMain[i];
// 			newPend.push_back(staggerElement);
// 		}
// 		if (newMain.size() != 1)						
// 			_sort(newMain, newPend, currPend);				
// 	}					
//
// 	// 2.	InsertionSort 
// 	// 		InsertionSort = BinarySearchInsertion + JacobsthalSequence
// 	// 1st - reorganize pend as main's id sequence
// 	// 2nd - index 0 of pend is bruteforced/automatically inserted into index 0 of main
// 	// 3rd - BSI + JS
//
//	
// 	// 2.1	Insertion sort when main.size() == 1 only
// 	// focus on newMain & newPend only
// 	if (newMain.size() == 1)			
// 	{
// 		std::vector<int> jacobSeq = _jacobsthalSequence(newPend.size());
// 		std::size_t i = 0;
//		
// 		newMain.insert(newMain.begin(), newPend[jacobSeq[i]]);
// 		++i;
// 		if (jacobSeq.size() > 1)
// 			for (; i < newPend.size(); ++i)
// 				_binarySearchInsertion(newMain, newPend[jacobSeq[i]]);		
//				
// 		sortedNewMain = newMain;
// 		newMain.clear(); // no more used
// 		newPend.clear(); // no more used
//		
// 		_sort(sortedNewMain, currMain, currPend, prevPend);
// 	}
//	
// 	// 2.2	Insertion sort when main.size() > 1
// 	// focus on currMain & prevPend only
// 	if (currMain.size() > 1 && !currPend.empty())				// focus on sortedNewMain && currPend
// 	{
// 		// unsorted prevPend -> sortedPrevPend
// 		std::vector<Element> sortedCurrPend;
//		
// 		for (std::size_t i = 0; i < currPend.size(); ++i)
// 		{
// 			int currPendIndex = currMain[i].getId();
// 			sortedCurrPend.push_back(currPend[currPendIndex]);
// 			sortedCurrPend[i].popId();
// 		}
// 		currPend.clear(); // no more used
//		
// 		// finally can use jacobSeq upon sortedCurrPend
// 		std::vector<int> jacobSeq = _jacobsthalSequence(sortedCurrPend.size());
// 		std::size_t i = 0;
//		
// 		currMain.insert(currMain.begin(), sortedCurrPend[jacobSeq[i]]);
// 		++i;
// 		if (jacobSeq.size() >= 2)
// 			for (; i < sortedCurrPend.size(); ++i)
// 				_binarySearchInsertion(currMain, sortedCurrPend[jacobSeq[i]]);		
// 		sortedCurrPend.clear(); // no more used
//		
// 		_sort(currMain, prevPend, );
// 	}
//
// 	if (currPend.empty() && prevPend.empty())
// 	{
//		
// 	}
// }