/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:25:56 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/15 11:23:34 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// =========================
//      PUBLIC FUNCTIONS
// =========================

// Public OCF

// Parameterized Constructor
// explicitely open the file via the constructor of std::ifstream
BitcoinExchange::BitcoinExchange(std::string dataFilename, std::string inputFilename)
: _dataFile(dataFilename.c_str()), _inputFile(inputFilename.c_str()), _perfectData_map()
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
void BitcoinExchange::exchange()
{
	// 1. check if file is openable
	if (!_inputFile.is_open())
		throw std::ifstream::failure("Unable to open input file or file dosent exist");

	// 2. check the existing of a valid header
	std::string line;
	if (!(std::getline(_inputFile, line) && line == "date | value"))
		throw std::invalid_argument("Input file dosen't have header of \"date | value\"");
	
	// 3.0 check line by line of input file
	int lineNum = 2;
	while (std::getline(_inputFile, line))
	{
		try
		{
			std::stringstream lineNumSS;
			std::string lineNumStr;
			lineNumSS << lineNum;
			lineNumSS >> lineNumStr;
			std::string initErrorMsg("Line" + lineNumStr + std::string("\t: "));
			
			std::size_t pipePos;
			std::size_t spaceBeforePipe;
			std::size_t spaceAfterPipe;
			std::string date;
			std::string valueStr;
			double value;
			double exchangeRate;
			double result;		
			
			// 3.1 check existing of '|' and its delimeters (1 space before & after '|')
			// make static check, not dynamic
			pipePos = line.find('|');
			spaceBeforePipe = line.find(' ', pipePos - 1);
			spaceAfterPipe = line.find(' ', pipePos + 1);
			if (!(pipePos != std::string::npos && 
				  spaceBeforePipe != std::string::npos && 
				  spaceAfterPipe != std::string::npos   ))
			{
				std::string errMsg = initErrorMsg + "Bad input => \"" + line + "\"";
				throw std::invalid_argument(errMsg);
			}

			// 3.2 check date validity
			date = line.substr(0, pipePos - 1);		// -1 to exclude 1 space before '|' 
			inputDateValidation(date, initErrorMsg);
			
			// 3.3 check value validity
			// getline dosent include newline into target string
			valueStr = line.substr(pipePos + 2);	// +2 to exclude 1 space after '|'
			value = inputValueValidation(valueStr, initErrorMsg);

			// 3.4 check if theres matching lower_bound date to the iput date
			exchangeRate = matchingDataDate(date, initErrorMsg);

			// 3.5 get & print result
			result = value * exchangeRate;
			std::cout << date << " => " << value << " = " << result << std::endl;
		}
		catch (std::exception &e)
		{
			std::cerr << RED << "Error: " << e.what() << RESET << std::endl;
		}
		++lineNum;
	}
	
	_inputFile.close();
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
	double exchangeRate;
	while (std::getline(_dataFile, date, ',') && std::getline(_dataFile, rate))
	{
		std::stringstream rateSS(rate);
		rateSS >> exchangeRate;			// use this method coz std::stoi() exist from C++11 only

		if (!date.empty())
		{
			_perfectData_map[date] = exchangeRate;
			date.clear();
			// std::cout << "i is " << i << std::endl;
		}
	}
	_dataFile.close();
	
	// debug print test
	// std::cout << "done save into map" << std::endl;
	// for (std::map<std::string, double>::iterator it = _perfectData_map.begin(); 
	// 	it != _perfectData_map.end(); ++it)
	// 	std::cout << it->first << " = " << it->second << " ." << std::endl;
	// std::cout << "total lines: " << i << std::endl;
}
