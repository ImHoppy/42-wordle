#include "dictionary.hpp"

/****************************************************
*				CONSTRUCTORS						*
****************************************************/

Dictionary::Dictionary(void) : _secret(""), _dict() {
	fill_dictionary();
	this->_secret = random_word(_dict);
}

Dictionary::~Dictionary(void) {

}

/****************************************************
*						GETTER						*
****************************************************/

std::string	Dictionary::get_secret(void) const {
	return _secret;
};

std::set<std::string> Dictionary::get_dict() const {
	return _dict;
}

/****************************************************
*				MEMBER FUNCTIONS					*
****************************************************/

std::string Dictionary::random_word( std::set< std::string > data )
{
	std::set< std::string >::iterator it = data.begin();
	int iSecret = rand() % data.size();

	for ( int i = 0; i < iSecret ; i++ )
		it++;
	return *it;
}

void	Dictionary::fill_dictionary() {
	unsigned int			i = 1;
	std::ifstream			words;
	std::string				word_to_insert;

	words.open("words.txt");
	if (!words) 
	{
		std::cerr << "Error : The dictionnary file is not found." << std::endl;
		exit(0);
	}
	while (!words.eof()) 
	{
		std::getline(words, word_to_insert);
		this->_dict.insert( word_to_insert);
		i++;
	}
}

bool		Dictionary::exist_word(std::string const & input) {
	std::set< std::string >::iterator it = _dict.find(input);
	if (it == _dict.end())
		return false;
	return true;

}