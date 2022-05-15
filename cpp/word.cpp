/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluong <wluong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 17:14:01 by wluong            #+#    #+#             */
/*   Updated: 2022/05/15 19:38:21 by wluong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word.hpp"
#include <iostream>
#include <utility>

word::word() : _current(0) {
	for (int i(0); i < 5; i++)
		_word[i] = letter();
}

word::word(int x, sf::Font font) : _current(0) {
	for (int i(0); i < 5; i++)
		_word[i] = letter("", font, x, i);
}

word::~word() {}

word& word::operator=(word const & other) {
	this->_current = other._current;
	for (int i(0); i < 5; i++) {
		_word[i] = other._word[i];
	}
	return *this;
};

std::string		word::getword() {
	std::string ret = "";
	for (int i(0); i < 5; i++) {
		ret += _word[i].getLetter();
	}
	return ret;
}

unsigned int	word::length() {
	return getword().length();
}

void			word::addLetter(int a) {
	char c = a;
	std::string s(1, c);
	if (_current == 5)
		return ;
	_word[_current].setLetter(s);
	std::cout << getword() << std::endl;
	_current++;

}

void			word::deleteLeter() {
	if (_current == 0)
		return ;
	_current--;
	_word[_current].setLetter(" ");
}

