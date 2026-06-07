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
    if (!(date.find_first_not_of("0123456789-") == std::string::npos))
        throw std::invalid_argument("Invalid date - have invalid character");


    // 2. check date format on specific index (must use - format, not / or .)
    if (!(date[4] == '-' && date[7] == '-'))
        throw std::invalid_argument("Invaid date - date format is not using '-' as per subject requirement");
    

    // 3. must numbers only within year & month & day
    std::string year = date.substr(0, 4);
    std::string month = date.substr(5, 2);
    std::string day = date.substr(8, 2);

    if (!(year.find_first_not_of("0123456789") == std::string::npos ||
        month.find_first_not_of("0123456789") == std::string::npos ||
        day.find_first_not_of("0123456789") == std::string::npos))
        throw std::invalid_argument("Invalid date - year or month or day contains non-digit characters");


    // 4. check year validity

	// 4.1 must not bee toooo ancient old or tooo futuristic
    //* must not bee tooo ancient old or veryy futuristic year lol
    //! incomplete

	// 4.2 check if its a leapYr for day validity
    //* divisable by 400 && divisable by 4 && not divisable by 100 ==> leapYr
    //* must conver to int & float first from istringstream
    //* know differences between istringstream vs ostringstream vs stringstream
    std::istringstream yearSS1(year);
    std::istringstream yearSS2(year);
    float floatYr;
    int intYr;
    bool leapYr = false;

	yearSS1 >> floatYr;
    yearSS2 >> intYr;
    if ((floatYr / 4) == (intYr / 4) &&
        (floatYr / 400) == (intYr / 400) &&
        (floatYr / 100) != (intYr / 100) )
    		leapYr = true;
	

    // 5. check month validity
    std::string mnthIndex0 = month.substr(0,1);
    std::string mnthIndex1 = month.substr(1,1);

    if (!(mnthIndex0.find_first_not_of("01") == std::string::npos))
        throw std::invalid_argument("Invalid date - invalid month");
    if (mnthIndex0 == "0")
        if (!(mnthIndex1.find_first_not_of("123456789") == std::string::npos))
            throw std::invalid_argument("Invalid date - invalid month");
    if (mnthIndex0 == "1")
        if (!(mnthIndex1.find_first_not_of("012") == std::string::npos))
            throw std::invalid_argument("Invalid date - invalid month");
    

    // 6. check day validity (depending on month & leapyear or not seperatedly)
    std::string dayIndex0 = day.substr(0,1);
    std::string dayIndex1 = day.substr(1,1);

	// 6.1 check day validity for leapYr == true
	//! incomplete
	if (leapYr == true)
		if (dayIndex0 == "2" && dayIndex1.find_first_not_of("012345678"))
			throw std::invalid_argument("Inavlid date - invalid day for leap year");

	// 6.2 check day validity on general
    //! incomplete 
	if (!(dayIndex0.find_first_not_of("0123") == std::string::npos && 
		  dayIndex1.find_first_not_of("0123456789") == std::string::npos && 
		  day.end() ==  ))
}

float BitcoinExchange::inputValueValidation(std::string valueStr)
{
    // 1. check any invalid characters, not even a space
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
    
    // 4. return float value! yeayy
    float valueFloat = static_cast<float>(valueDouble);
    return valueFloat;
}

float BitcoinExchange::matchingDataDate(std::string date, float value)
{
    //! incomplete
}