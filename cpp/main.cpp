#include <SFML/Graphics.hpp>
#include <iostream>
#include "word.hpp"
#include "dictionary.hpp"
#include <string>

#define RECT_SIZE 100

int main()
{
	sf::RenderWindow	window(sf::VideoMode(650, 900), "Wordle!");
	sf::RectangleShape	wordsShape[5];
	// t_grid				grid[6][5];
	sf::Font			font;
	sf::String			input[5];
	word				words[6];
	Dictionary			dico;

	srand(time(NULL));

	if (!font.loadFromFile("arial.ttf")) {
		exit(1);
	}

/*************************************************************
 * 					WALTER
 * 
 ************************************************************/

	for (size_t i = 0; i < 6; i++)
	{
		words[i] = word(i, font);
	}

/******************************************************************
 * 
 * 
 *****************************************************************/

	// for (size_t i = 0; i < 5; i++)
	// {
	// 	wordsShape[i] = sf::RectangleShape(sf::Vector2f(RECT_SIZE, 1));
	// 	wordsShape[i].setPosition((i * (RECT_SIZE+10)) + 55, 900 * 0.95);
	// }
	int currentRow = 0;
	// int currentLetter = 0;
	
	window.setKeyRepeatEnabled(false);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				else if (event.key.code == sf::Keyboard::Enter)
				{
					if (words[currentRow].length() != 5)
						continue;
					if (!dico.exist_word(words[currentRow].getword()))
						continue;
					if (dico.get_secret() == words[currentRow].getword())
					{
						std::cout << "You win" << std::endl;
						window.close();
					}
					currentRow++;
					if (currentRow >= 6)
					{
						std::cout << "You Loose" << std::endl;
						window.close();
					}
					std::cout << "Enter" << std::endl; // check word in gridShape
				}
				else if (event.key.code == sf::Keyboard::BackSpace)
					words[currentRow].deleteLeter();
				else {
					int keycode = static_cast<int>(event.key.code);
					// std::cout << keycode << std::endl;
					if (keycode >= 0 && keycode <= 26) {
						words[currentRow].addLetter((keycode + 'A'));
						std::cout << (char)(keycode + 'A') << std::endl; // Add letter with keycode + 'A'
						
					}
				}
				

			}
		}


		window.clear(sf::Color(Colors::BG));
		// window.clear(sf::Color::White);
		for (size_t i = 0; i < 6; i++)
		{
			for (size_t j = 0; j < 5; j++)
			{
				// window.draw(gridShape[i][j]);
				window.draw(words[i]._word[j].getShape());
				window.draw(words[i]._word[j].getText());
				printf("%d", words[i]._word[j].getText().getCharacterSize());
			}
			std::cout<<	std::endl;
		}
		// for (size_t i = 0; i < 5; i++)
		// {
		// 	window.draw(wordsShape[i]);
		// }
		window.display();
	}

	return 0;
}