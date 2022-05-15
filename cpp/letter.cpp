/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:43:01 by wluong            #+#    #+#             */
/*   Updated: 2022/05/15 19:56:07 by wluong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "letter.hpp"
#include "Colors.hpp"

#define RECT_SIZE 100

letter::letter() : _color(0x181818FF), _text(sf::Text()) {}

letter::letter( std::string s, sf::Font font, int x, int y ) : _color(0x181818FF) {
	_shape = sf::RectangleShape(sf::Vector2f(RECT_SIZE, RECT_SIZE));
	_shape.setFillColor(sf::Color(Colors::BG));
	_shape.setOutlineColor(sf::Color(Colors::BORDER));
	_shape.setOutlineThickness(2);
	_shape.setPosition((y * (RECT_SIZE+10)) + 55, (x * (RECT_SIZE+10)) + 55);
	_text = sf::Text();
	_text.setFont(font);
	_text.setString(s);
	_text.setCharacterSize(40);
	_text.setPosition(1,2);
}

letter::letter(letter const & src) : _color(src._color), _text(src._text), _shape(src._shape) {}

letter::~letter() {}


letter& 	letter::operator=(letter const & other) {
	this->_color = other._color;
	_text.setString(other._text.getString());
	_text.setCharacterSize(other._text.getCharacterSize());
	_text.setPosition(other._text.getPosition());
	_shape = sf::RectangleShape(sf::Vector2f(RECT_SIZE, RECT_SIZE));
	_shape.setFillColor(other._shape.getFillColor());
	_shape.setOutlineColor(other._shape.getOutlineColor());
	_shape.setOutlineThickness(other._shape.getOutlineThickness());
	_shape.setPosition(other._shape.getPosition());
	return *this;
}

void		letter::setLetter(std::string s) {
	_text.setString(s);
}

void		letter::setColor(Colors color) {
	_shape.setFillColor(sf::Color(color));
	_shape.setOutlineColor(sf::Color(color));
}

std::string	letter::getLetter() {
	return _text.getString().toAnsiString();
}

// Colors		letter::getColor() const {
// 	return _shape.getFillColor() ;
// }

sf::Text			letter::getText() const {
	return _text;
}

sf::RectangleShape	letter::getShape() const {
	return _shape;
}

