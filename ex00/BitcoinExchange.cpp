/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:25:56 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/08 13:28:42 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// =========================
//      PUBLIC FUNCTIONS
// =========================

// Public OCF

// Parameterized Constructor
// explicitely open the file via the constructor of std::ifstream
BitcoinExchange::BitcoinExchange(const char *dataFile, const char *inputFile)
: _dataFile(dataFile), _inputFile(inputFile), _perfectData_map()
{
	saveDataIntoMap();
}

BitcoinExchange::~BitcoinExchange()
{
	if (_dataFile.is_open() == true)
		_dataFile.close();
	if (_inputFile.is_open() == true)
		_inputFile.close();
}

// Public member function
int BitcoinExchange::exchange()
{
	// 1. check if file is openable
	if (!_inputFile.is_open())
		throw std::ifstream::failure("Unable to open input file");

	// 2. check the existing of a valid header
	std::string line;
	if (!(std::getline(_dataFile, line) && line == "date | value"))
		throw std::invalid_argument("Input file dosen't have header of \"date | value\"");
	
	// 3.0 check line by line of input file
	while (std::getline(_inputFile, line))
	{
		try
		{
			std::size_t pipePos;
			std::size_t dotPos;
			std::string date;
			std::string valueStr;
			float value;
			float exchangeRate;
			float result;		
			
			// 3.1 check existing of '|' and its delimeters (1 space before & after '|')
			// make static check, not dynamic
			pipePos = line.find('|');
			if (!( (pipePos != std::string::npos) || 
				(line[pipePos - 1] == ' ' && line[pipePos + 1] == ' ') ))
			{
				std::string errMsg = "Bad input => " + line;
				throw std::invalid_argument(errMsg);
			}

			date = line.substr(0, pipePos - 1);		// -1 to also exclude 1 space before '|' 
			inputDateValidation(date);
			
			// 											getline dosent include newline into target string
			valueStr = line.substr(pipePos + 2);	// +2 to also exclude 1 space after '|'
			value = inputValueValidation(valueStr);

			exchangeRate = matchingDataDate(date, value);
			result = value * exchangeRate;

			std::cout << date << " => " << value << " = " << result << std::endl;
		}
		catch (std::exception &e)
		{
    	    std::cerr << "Error: " << e.what() << std::endl;
		}
	}
}

// ===========================
//      PRIVATE FUNCTIONS
// ===========================

// Private OCF - no need to define in .cpp

// Private member functions

// data.csv is provided by 42 
// what 42 providedwill always be perfect, just like FdF's maps
// thus no need to be checked & validated
// esp when its not a user input, its a database
void BitcoinExchange::saveDataIntoMap()
{
    if (!_dataFile.is_open())
        throw std::ifstream::failure("Unable to open data file");

	std::string firstLine;
	if (!(std::getline(_dataFile, firstLine) && firstLine == "date,exchange_rate"))
		throw std::invalid_argument("Data file dosen't have header of \"date,exchange_rate\"");
    
	std::string date;
	std::string rate;
	float exchangeRate;
	while (std::getline(_dataFile, date, ',') && std::getline(_dataFile, rate))
	{
		std::stringstream rateSS(rate);
		rateSS >> exchangeRate;

		if (!date.empty())
		{
			// std::cout << "i is " << i << std::endl;
			_perfectData_map[date] = exchangeRate;
			date.clear();
		}
	}
	_dataFile.close();
	
	// std::cout << "done save into map" << std::endl;
	// for (std::map<std::string, double>::iterator it = _perfectData_map.begin(); 
	// 	it != _perfectData_map.end(); ++it)
	// 	std::cout << it->first << " = " << it->second << " ." << std::endl;
	// std::cout << "total lines: " << i << std::endl;
}
