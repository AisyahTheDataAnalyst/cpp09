/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Structs.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 17:50:37 by aimokhta          #+#    #+#             */
/*   Updated: 2026/06/11 08:29:01 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <vector>
# include <deque>

struct Vector
{
	public:
		std::vector<int>	cont;
		long				elapseTime;
};

struct Deque
{
	public:
		std::deque<int>		cont;
		long				elapseTime;
};

#endif