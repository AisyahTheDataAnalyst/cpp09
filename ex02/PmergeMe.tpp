/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:17:51 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/14 20:19:25 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename ContainerE, typename ContainerI>
void PmergeMe::_theFordJohnsonAlgo(ContainerI &cont)
{
	// two main chains in dealing with Ford Johnson Algorithm
	ContainerE	main;
	ContainerE	pend;
	ContainerE	empty;
	
	// ====================================================================================================
	//	STEP 1 ===> PAIRING & CONSTRUCT MAIN CHAIN + PENDING CHAIN
	// ====================================================================================================
	_pairMainPend(cont, main, pend);

	// debug print
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
	_overwriteResult(main, cont);	
}

// this causes recursion
// - numbers processed by LIFO method / lazy / not fair
template <typename ContainerE, typename ContainerI>
void PmergeMe::_pairMainPend(ContainerI &cont, ContainerE &main, ContainerE &pend)
{
	std::size_t i = 0;
	int id = 0;
	for (; i + 1 < cont.size(); i += 2, ++id)
	{
		Pair pair(Element(cont[i], id), Element(cont[i + 1], id));
		main.push_back(pair.getBigger());
		pend.push_back(pair.getSmaller());
	}
	if (i < cont.size())
	{
		Element staggerElement = Element(cont[i], id);
		pend.push_back(staggerElement);
	}
}

// Recursion occurs here
// 1st, MergeSort starts
// when main finally left 1 number only, InsertionSort takes place
// InsertionSort uses BinarySearchInsertion upon main and JacobsthalSequence upon pend 
template <typename ContainerE>
void PmergeMe::_mergeSort(ContainerE &main, ContainerE &pend) //, ContainerE &pend)
{
	ContainerE	newMain;
	ContainerE	newPend;
	
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
template <typename ContainerE>
ContainerE &PmergeMe::_insertionSort(ContainerE &main, ContainerE &pend)
{	
	if (main.empty())
		throw std::invalid_argument("Main is invalidly empty");
	
	// debug print
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

		// debug print
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

		// debug print
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
	
	ContainerE sortedPend;
	
	for (std::size_t i = 0; i < main.size(); ++i)
	{
		sortedPend.push_back(pend[main[i].getId()]);
		sortedPend.back().popId();
		main[i].popId();
	}
	if (pend.size() > main.size())
	{
		sortedPend.push_back(pend.back());
		sortedPend.back().popId();
	}
	
	// debug print
	// std::cerr << "sortedPend: " << std::endl;
	// for (std::size_t i = 0; i < sortedPend.size(); ++i)
	// {
	// 	std::cerr << sortedPend[i].getValue() << std::endl;
	// }
	// std::cerr << std::endl;
	//

	// finally can use jacobSeq upon sortedPend
	const std::vector<int> jacobSeq = _jacobsthalSequence(sortedPend.size());
	
	// debug print
	// std::cerr << "jacobSeq full order:" << std::endl; 
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
	
	// debug print
	// std::cerr << "sortedMain > 1: " << std::endl;
	// for (std::size_t i = 0; i < main.size(); ++i)
	// {
	// 	std::cerr << main[i].getValue() << std::endl;
	// }
	// std::cerr << std::endl;
	//
	
	return main;
}

// Binary search insertion is for:
// upon main chain
// to determine which number of main chain that should pend chain be inserted before it.
template <typename ContainerE>
void PmergeMe::_binarySearchInsertion(ContainerE &sortedMain, Element pendElement)
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
}

template <typename ContainerE, typename ContainerI>
void PmergeMe::_overwriteResult(ContainerE &main, ContainerI &cont)
{
	for(std::size_t i = 0; i < _vector.size(); ++i)
		cont[i] = main[i].getValue();
}


//! make templates function for overriding containers
//! fix PM.hpp to use templates and in this PM.tpp too
//! check comparisonCounts must within ideal numbers , check online or in the book whats the ideal numbers
//! check time is it nicely accurate
//! tidy up
//! cehck if i can use exception invailid_argument for these such cases, is it acceotable to use exception for these kind of events
//! prepaare full understanding why need Jacobstajl sequence, whats benefit of ford johnson algorithm, how to explain this easily to evaluators so they dont get overwhelmed
