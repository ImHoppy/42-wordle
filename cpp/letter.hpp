/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:38:58 by wluong            #+#    #+#             */
/*   Updated: 2022/05/15 19:03:28 by wluong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LETTER_HPP
# define LETTER_HPP

# include <SFML/Graphics.hpp>
# include "Colors.hpp"

class letter
{
	private:

		uint32_t			_color;
		sf::Text			_text;
		sf::RectangleShape	_shape;
		

	public:
		
		letter();
		letter( std::string s, sf::Font font, int x, int y );
		letter( letter const & src );
		~letter();

		letter& operator=( letter const & other );

		void				setLetter( std::string s );
		void				setColor( Colors color );
		std::string			getLetter() ;
		Colors				getColor() const;
		sf::Text			getText() const;
		sf::RectangleShape	getShape() const;
};

#endif