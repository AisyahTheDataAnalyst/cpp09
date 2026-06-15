/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:17:51 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/15 11:12:46 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename ContainerE, typename ContainerI>
void PmergeMe::_theFordJohnsonAlgo(ContainerI &cont)
{
	// two main chains in dealing with Ford Johnson Algorithm
	ContainerE	main;
	ContainerE	pend;	
	
	// ====================================================================================================
	//	STEP 1 ===> PAIRING & CONSTRUCT MAIN CHAIN + PENDING CHAIN
	// ====================================================================================================
	_pairMainPend(cont, main, pend);

	// ====================================================================================================
	//	STEP 2 ===> IMPLEMENT mergesort + (insertion sort + binary search insertion + jacobsthal sequence)
	// ====================================================================================================
	_mergeSort(main, pend);

	// ====================================================================================================
	//	STEP 3 ===> overwrite sorted main<Element> into vector/deque<int>
	// ====================================================================================================
	_overwriteResult(main, cont);	
}

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
		Element stragglerElement = Element(cont[i], id);	// Straggler: Someone or something that is left behind or separates from the main group.
		pend.push_back(stragglerElement);
	}
}

// Recursion occurs here
// 1st, MergeSort starts
// when main finally left 1 number only, InsertionSort takes place
// InsertionSort uses BinarySearchInsertion upon main and JacobsthalSequence upon pend 
template <typename ContainerE>
void PmergeMe::_mergeSort(ContainerE &main, ContainerE &pend)// ContainerE &newMain, ContainerE &newPend)
{
	if (main.empty())
		throw std::invalid_argument("Main is invalidly empty");
	
	if (main.size() == 1)
	{
		main = _insertionSort(main, pend);
		return;
	}
	
	// 1. Pairing phase
	ContainerE	newMain;
	ContainerE	newPend;
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
	// handle stragglerElement (odd element)
	if (main.size() % 2 != 0)
	{
		main.back().pushId(id);
		newPend.push_back(main.back());
	}

	// 2. Recursive -> sort the winner chain
	_mergeSort(newMain, newPend);
	
	// 3. Unwind phase -> Assign the sorted winners back to main,
	// then insert this level's pend items into it.	
	main = _insertionSort(newMain, pend);
}

// 2.	InsertionSort = BinarySearchInsertion + JacobsthalSequence
// 1st - reorganize pend to be sorted just as main's id sequence (here the main is sorted already)
// 2nd - index 0 of pend is bruteforced/automatically inserted into index 0 of main -> bruteforcing minimize the comparison count -> crucial for Ford Johnson Algo or F(n)
// 3rd - IS = BSI + JS
template <typename ContainerE>
ContainerE &PmergeMe::_insertionSort(ContainerE &main, ContainerE &pend)
{	
	if (main.empty() || pend.empty())
		throw std::invalid_argument("Main or pend is invalidly empty");
	
	// 2.1	Insertion sort when main.size() == 1 only
	if (main.size() == 1)			
	{
		const std::vector<int> jacobSeq = _jacobsthalSequence(pend.size());		
		main.insert(main.begin(), pend[jacobSeq[0]]);
		for (std::size_t i = 1; i < jacobSeq.size(); ++i)	// when main.size() == 1, pend.size() will either be 1 or 2 only -> will skip this if pend.size() == 1
			if (jacobSeq[i] < static_cast<int>(pend.size()))
				_binarySearchInsertion(main, pend[jacobSeq[i]], 1);									
		for (std::size_t i = 0; i < main.size(); ++i)
			main[i].popId();
		return main;
	}
	
	// 2.2	Insertion sort when main.size() > 1
	// unsorted pend -> sortedPend
	ContainerE sortedPend;
	for (std::size_t i = 0; i < main.size(); ++i)
		sortedPend.push_back(pend[main[i].getId()]);
	if (pend.size() > main.size())
		sortedPend.push_back(pend.back());
	
	// finally can use jacobSeq upon sortedPend
	const std::vector<int> jacobSeq = _jacobsthalSequence(sortedPend.size());
	main.insert(main.begin(), sortedPend[0]);
	for (std::size_t i = 1; i < jacobSeq.size(); ++i)
	{
		int toBeInsertedValueIndex = jacobSeq[i];
		std::size_t winnerIndex = main.size();
		if (toBeInsertedValueIndex < static_cast<int>(winnerIndex)) // Skip this if its a straggler Element -> winnerIndex just will be main.size() 
		{
			for (std::size_t j = 0; j < winnerIndex; ++j)
			{
				if (main[j].getId() == sortedPend[toBeInsertedValueIndex].getId())
				{
					winnerIndex = j; // binary search window shrinks dramatically - > minimize comparison count a lot
					break;
				}
			}
		}
		_binarySearchInsertion(main, sortedPend[toBeInsertedValueIndex], winnerIndex);
	}
				
	for (std::size_t i = 0; i < main.size(); ++i)
		main[i].popId();
	return main;
}

// Binary search insertion is for:
// upon main chain
// to determine which number of main chain that should pend chain be inserted before it.
template <typename ContainerE>
void PmergeMe::_binarySearchInsertion(ContainerE &sortedMain, Element pendElement, std::size_t winnerIndex)
{
	if (sortedMain.empty())
	{
		sortedMain.push_back(pendElement);
		return;
	}
	
	std::size_t low = 0;
	std::size_t high = winnerIndex;
	
	while (low < high)
	{
		std::size_t mid = low + (high - low) / 2;
		if (pendElement < sortedMain[mid])
			high = mid;
		else
			low = mid + 1;
	}

	sortedMain.insert(sortedMain.begin() + low, pendElement);
}

template <typename ContainerE, typename ContainerI>
void PmergeMe::_overwriteResult(ContainerE &main, ContainerI &cont)
{
	for(std::size_t i = 0; i < _vector.size(); ++i)
		cont[i] = main[i].getValue();
}

template <typename ContainerI>
void PmergeMe::_isSorted(bool wantedScenario, ContainerI &container)
{
	bool sorted = (std::adjacent_find(container.begin(), container.end(), std::greater<int>()) == container.end());
	if (sorted != wantedScenario && sorted == true)
		throw std::invalid_argument("Sorted arguments");
	if (sorted != wantedScenario && sorted == false)
		throw std::invalid_argument("Unsorted arguments");
}
