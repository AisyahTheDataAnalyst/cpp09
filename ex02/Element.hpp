/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Element.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 08:29:19 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/15 08:42:40 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_HPP
# define ELEMENT_HPP

# include <vector>

struct Element
{
	private:	
		int _value;
		std::vector<int> _id;	// does not violate the container constraint because you are not using it to hold, sort, or manage the list of input elements given by the user.
		Element();
		
	public:
		static bool comparisonBool;
		static int comparisonCount;
		Element(int, int);
		Element(const Element &);
		~Element();
		int getValue() const;
		int getId() const;
		void pushId(int additionalId);
		void popId();
		Element &operator=(const Element &);
		bool operator>=(const Element &other) const;
		bool operator<=(const Element &other) const;
		bool operator==(const Element &other) const;
		bool operator>(const Element &other) const;
		bool operator<(const Element &other) const;
};
#endif