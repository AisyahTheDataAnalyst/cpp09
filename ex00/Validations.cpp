/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputValidation.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 19:51:24 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/06 19:51:24 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void BitcoinExchange::inputDateValidation(std::string date)
{
	// 1. check any invalid characters, not even a space
	if (!(date.find_first_not_of("-0123456789") == std::string::npos))
		throw std::invalid_argument("Invalid date - have invalid character");

	// 2. check date format (must use - format, not / or .)
	if (!(date[4] == '-' && date[7] == '-'))
		throw std::invalid_argument("Invaid date - not following subject's format requirement, Year-Month-Day");
	
	// 3. must numbers only within year & month & day
	std::string year = date.substr(0, 4);
	std::string month = date.substr(5, 2);
	std::string day = date.substr(8);
	if (!(year.find_first_not_of("0123456789")  == std::string::npos ||
		  month.find_first_not_of("0123456789") == std::string::npos ||
		  day.find_first_not_of("0123456789")   == std::string::npos   ))
		throw std::invalid_argument("Invalid date - year or month or day contains non-digit characters");

	// 4. record current input's yr/mnth/day
	int yrInt = std::atoi(year.c_str());
	int mnthInt = std::atoi(month.c_str());
	int dayInt = std::atoi(day.c_str());

	// 5. year shouldnt be too early
	std::string earliestDate = _perfectData_map.begin()->first;
	int earliestYr = std::atoi(earliestDate.substr(0, 4).c_str());
	if (!(yrInt >= earliestYr))
		throw std::invalid_argument("Invalid date - year date is too early");

	// 6. check leap year
	// =======================================================================================================
	// source : https://learn.microsoft.com/en-us/troubleshoot/microsoft-365-apps/excel/determine-a-leap-year
	// LEAP YEAR DETERMINATION :
	// 1. If the year is evenly divisible by 4, go to step 2. Otherwise, go to step 5.		(Rule 1: %4 - Filters out standard common years.)
	// 2. If the year is evenly divisible by 100, go to step 3. Otherwise, go to step 4.	(Rule 2: %100 - Separates standard leap years from century years; years ending with 00)
	// 3. If the year is evenly divisible by 400, go to step 4. Otherwise, go to step 5.	(Rule 3: %400 - It decides which century years get to be leap years.)
	// 4. The year is a leap year (it has 366 days).
	// 5. The year is not a leap year (it has 365 days).
	//
	// FORMULA TRANSLATION :
	// (NO )	%4 != 0
	// (YES)	%4 == 0 && %100 != 0
	// (NO )	%4 == 0 && %100 == 0 && %400 != 0
	// (YES)	%4 == 0 && %100 == 0 && %400 == 0
	//
	// CODE SHORTCUT :
	// (YES)	%4 == 0 && %100 != 0
	// (YES)	%400 == 0					(same as)		%4 == 0 && %100 == 0 && %400 == 0
	// =======================================================================================================
	bool leapYr = (yrInt % 4 == 0 && yrInt % 100 != 0) || (yrInt % 400 == 0);
	
	// 7. check month validity
	if (!(mnthInt >= 1 && mnthInt <= 12))
		throw std::invalid_argument("Invalid date - invalid month");

	// 8. check day validity (seperatedly depending on month & leapyear or not)
	int totalDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (leapYr == true)
		totalDays[1] = 29;
	if (!(dayInt >= 1 && dayInt <= totalDays[mnthInt]))
		throw std::invalid_argument("Invalid date - invalid days");

	// redundant month validity check
	// 5. check month validity
	// std::string mnthIndex0 = month.substr(0,1);
	// std::string mnthIndex1 = month.substr(1,1);
	//
	// if (!(mnthIndex0.find_first_not_of("01") == std::string::npos))
	// 	throw std::invalid_argument("Invalid date - invalid month");
	// if (mnthIndex0 == "0")
	// 	if (!(mnthIndex1.find_first_not_of("123456789") == std::string::npos))
	// 		throw std::invalid_argument("Invalid date - invalid month");
	// if (mnthIndex0 == "1")
	// 	if (!(mnthIndex1.find_first_not_of("012") == std::string::npos))
	// 		throw std::invalid_argument("Invalid date - invalid month");
	
	// redundant check earliest date validity - smartly solved by std::lower_bound in matchingDateData()
	// std::string earliestDate = _perfectData_map.begin()->first;
	// int earliestYr = std::atoi(earliestDate.substr(0, 4).c_str());
	// int earliestMnth = std::atoi(earliestDate.substr(5, 2).c_str());
	// int earliestDay = std::atoi(earliestDate.substr(8).c_str());
}

float BitcoinExchange::inputValueValidation(std::string valueStr)
{
	// 1. check any invalid characters, not even a space
	// newline is already excluded previously by std::getline from input file
	if (!(valueStr.find_first_not_of(".0123456789") == std::string::npos))
		throw std::invalid_argument("Invalid value - have invalid character");

	// 2. check dot should be 1 only
	// or else it could be inaccurate whole number after strtol, not float
	std::size_t dotPos = valueStr.find('.');
	if (dotPos != std::string::npos)
		if (!(valueStr.substr(dotPos + 1).find('.') == std::string::npos))
			throw std::invalid_argument("Invalid value - have more than one decimal point");

	// 3. check valid float range
	std::stringstream valueSS(valueStr);
	double valueDouble;
	valueSS >> valueDouble;
	if (!(valueDouble >= FLT_MIN && valueDouble <= FLT_MAX))
		throw std::invalid_argument("Invalid value - not within a valid float range");

	// 4. check its a positive interger
	if (!(valueDouble >= 0))
		throw std::invalid_argument("Invalid value - not a positive number");
	
	// 5. check its between 0 - 1000
	if (!(valueDouble <= 1000))
		throw std::invalid_argument("Invalid value - too large a nnumber");
	
	// 6. return float value! yeayy
	float valueFloat = static_cast<float>(valueDouble);
	return valueFloat;
}

float BitcoinExchange::matchingDataDate(std::string date, float value)
{
	// 1. check if its way before the earliest date in perfectData.csv
	// RULE: you must look BACKWARD IN TIME to find the most recent available price. You must never look forward into the future.
	// subject.pdf says,
	// "If the date used in the input does not exist in your DB 
	//  then you must use the closest date contained in your DB. 
	//  Be careful to use the LOWER DATE and not the upper one."
	




}