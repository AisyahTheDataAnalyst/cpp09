/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:25:56 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/06 17:11:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// =========================
//      PUBLIC FUNCTIONS
// =========================

// Public OCF

// explicitely open the file via the constructor of std::ifstream
BitcoinExchange::BitcoinExchange(const char *dataFile, const char *inputFile)
: _dataFile(dataFile), _inputFile(inputFile), _perfectData_map()
{}

BitcoinExchange::~BitcoinExchange()
{}

// Public member function
int BitcoinExchange::exchange()
{
    try
    {
        saveDataIntoMap();
        // printResult();        
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what();
        return 1; 
    }
    
    return 0;
}

// ===========================
//      PRIVATE FUNCTIONS
// ===========================

// Private OCF - no need to define in .cpp

// Private member functions

void BitcoinExchange::saveDataIntoMap()
{
    if (!_dataFile.is_open())
        throw std::runtime_error("Unable to open file");

    std::string date;
	std::string rate;
	float exchangeRate;
	int i = 0;

   while (std::getline(_dataFile, date, ',') && std::getline(_dataFile, rate))
   {
		std::stringstream tempRate(rate);
		tempRate >> exchangeRate;
		if (i >= 1)
		{
			if (!date.empty())
			{
				// std::cout << "i is " << i << std::endl;
				_perfectData_map[date] = exchangeRate;
				date.clear();
			}
		}
		++i;
	}
	_dataFile.close();
	
	// std::cout << "done save into map" << std::endl;
	// for (std::map<std::string, double>::iterator it = _perfectData_map.begin(); 
	// 	it != _perfectData_map.end(); ++it)
	// 	std::cout << it->first << " = " << it->second << " ." << std::endl;
	// std::cout << "total lines: " << i << std::endl;
}

// void BitcoinExchange::printResult()
// {
//     if (!_inputFile.is_open())
// 		throw std::runtime_error("");

// 	std::string date;
// 	std::string value;
// 	float 
		
// 	while (std::getline())
// 	try
// 	{
		
// 	}
// 	catch (std::exception &e)
// 	{
// 		throw e;
// 	}
// }