/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:39:19 by wluong            #+#    #+#             */
/*   Updated: 2022/05/15 16:39:42 by wluong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICTIONARY_HPP
# define DICTIONARY_HPP

#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>

class Dictionary {

	public:

		Dictionary();
		Dictionary(Dictionary const & src);
		~Dictionary(void);

		Dictionary&	operator=(Dictionary const & other);

		bool					exist_word(std::string const & input);
		std::string 			random_word( std::set< std::string > data );
		void					fill_dictionary();

		std::string				get_secret(void) const;
		std::set<std::string>	get_dict() const;

	private:

		std::set<std::string>	_dict;
		std::string				_secret;
};

#endif