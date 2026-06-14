/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 08:18:44 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/14 17:52:28 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

# include "Element.hpp"

struct Pair
{
	private:	
		Element _bigger;
		Element _smaller;
		Pair();

	public:
		Pair(const Element &, const Element &);
		Pair(const Pair &);
		Pair &operator=(const Pair &);
		Pair &operator()(const Element &, const Element &);
		~Pair();
		const Element &getBigger() const;
		const Element &getSmaller() const;
};


#endif