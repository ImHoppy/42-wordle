/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 17:14:00 by wluong            #+#    #+#             */
/*   Updated: 2022/05/15 18:09:32 by wluong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_HPP
# define WORD_HPP

# include "letter.hpp"

class word
{
	private:

		unsigned int _current;


	public:

		letter	_word[5];
		
		word();
		word(int x, sf::Font font);
		~word();

		std::string		getword();
		unsigned int	length();
		void			addLetter( int a );
		void			deleteLeter();
};

#endif