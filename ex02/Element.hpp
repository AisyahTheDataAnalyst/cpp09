/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Element.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 08:29:19 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/11 19:08:12 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_HPP
# define ELEMENT_HPP

struct Element
{
	private:	
		int _value;
		int _id;
		
	public:
		Element();
		Element(int, int);
		Element(const Element &);
		~Element();
		const int &getValue() const;
		const int &getId() const;
		Element &operator=(const Element &);
		bool operator>=(const Element &other) const;
		bool operator<=(const Element &other) const;
		bool operator==(const Element &other) const;
		bool operator>(const Element &other) const;
		bool operator<(const Element &other) const;
};
#endif