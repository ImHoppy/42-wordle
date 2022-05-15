#include <SFML/Graphics.hpp>
#include <iostream>
#include "dictionary.hpp"

#define RECT_SIZE 100

enum Colors : uint32_t {
	BG			= 0x181818FF,
	BORDER		= 0x696969FF,
	INCORRECT	= 0x939598FF,
	GREEN		= 0x538D4EFF,
	YELLOW		= 0xB59F3BFF
};

typedef struct s_grid {
	sf::Text		text;
	std::string		letter;
	Colors			color;
	sf::RectangleShape	shape;
} t_grid;

int	len_grid(t_grid grid[5])
{
	int	n = 0;
	for (size_t i = 0; i < 5; i++)
	{
		if (!grid[i].letter.empty())
			n++;
		else
			return (n);
	}
	return (n);
}
std::string	join_word(t_grid grid[5])
{
	std::string result = grid[0].letter;
	for (size_t i = 1; i < 5; i++)
	{
		result += grid[i].letter;
	}
	return (result);
}

void analyse_input(t_grid grid[5], std::string line, std::string secret)
{
	std::string            cpy_line = line;
	std::string            cpy_secret = secret;

	/////////////Search for green
	for ( unsigned int i = 0; i < 5; i++)
	{
		if ( line.at(i) == cpy_secret.at(i) )
		{
			grid[i].color = Colors::GREEN;
			cpy_line.at(i) = ' ';
			cpy_secret.at(i) = ' ';
		}
	}
	/////////////search for yellow
	for ( unsigned int i = 0; i < 5; i++ )
	{
		for ( unsigned int j = 0; j < 5; j++ )
		{
			if ( cpy_line.at(i) == cpy_secret.at(j) && cpy_line.at(i) != ' ')
			{
				grid[i].color = Colors::YELLOW;
				cpy_line.at(i) = ' ';
				cpy_secret.at(j) = ' ';
			}	
		}
	}
}

int main()
{
	sf::RenderWindow	window(sf::VideoMode(650, 755 /*900*/), "Wordle!");
	t_grid				grid[6][5];
	sf::Font			font;
	sf::String			input[5];
	srand(time(NULL));
	Dictionary			dict;

	std::cout<<dict.get_secret()<<std::endl;
	if (!font.loadFromFile("arial.ttf")) {
		exit(1);
	}
	for (size_t i = 0; i < 6; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			grid[i][j].shape = sf::RectangleShape(sf::Vector2f(RECT_SIZE, RECT_SIZE));
			grid[i][j].shape.setFillColor(sf::Color(Colors::BG));
			grid[i][j].shape.setOutlineColor(sf::Color(Colors::BORDER));
			grid[i][j].shape.setOutlineThickness(2);
			grid[i][j].shape.setPosition((j * (RECT_SIZE+10)) + 55, (i * (RECT_SIZE+10)) + 55);
			
			grid[i][j].letter = "";
			grid[i][j].color = Colors::BG;
			grid[i][j].text = sf::Text();
			grid[i][j].text.setFont(font);
			grid[i][j].text.setString(grid[i][j].letter);
			grid[i][j].text.setCharacterSize(40);
			grid[i][j].text.setPosition((j * (RECT_SIZE+10)) + 55 + (RECT_SIZE/3), (i * (RECT_SIZE+10)) + 55 + (RECT_SIZE/4));
		}
	}

	int currentRow = 0;
	int currentLetter = 0;
	
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
					std::string word = join_word(grid[currentRow]);
					std::for_each(word.begin(), word.end(), [](char & c) {
						c = ::tolower(c);
					});
					if (word.length() != 5)
						continue;
					if (!dict.exist_word(word))
						continue;
					analyse_input(grid[currentRow], word, dict.get_secret());
					if (word == dict.get_secret()) {
						std::cout << "Winning ! " << dict.get_secret() << std::endl;
						// window.close();
					}
					currentRow++;
					currentLetter = 0;
					std::cout << "Enter" << std::endl; // check word in gridShape
					if (currentRow == 6) {
						std::cout << "Loosing ! " << dict.get_secret() << std::endl;
						// window.close();
					}
				}
				else if (event.key.code == sf::Keyboard::BackSpace)
				{
					if (currentLetter <= 0)
						continue;
					currentLetter--;
					grid[currentRow][currentLetter].text.setString(' ');
					grid[currentRow][currentLetter].letter = "";
					std::cout << "Delete" << std::endl; // delete letter in gridShape
				}
				else {
					int keycode = static_cast<int>(event.key.code);
					// std::cout << keycode << std::endl;
					if (keycode >= 0 && keycode <= 26)
					{
						if (currentLetter > 4)
							continue;
						grid[currentRow][currentLetter].text.setString((char)(keycode + 'A'));
						grid[currentRow][currentLetter].letter = (char)(keycode + 'A');
						currentLetter++;
						std::cout << (char)(keycode + 'A') << std::endl; // Add letter with keycode + 'A'
						
					}
				}
				

			}
		}


		window.clear(sf::Color(Colors::BG));
		for (size_t i = 0; i < 6; i++)
		{
			for (size_t j = 0; j < 5; j++)
			{
				// window.draw(gridShape[i][j]);
				grid[i][j].shape.setFillColor(sf::Color(grid[i][j].color));
				if (grid[i][j].color != Colors::BG)
					grid[i][j].shape.setOutlineColor(sf::Color(grid[i][j].color));
				window.draw(grid[i][j].shape);
				window.draw(grid[i][j].text);
			}
		}
		window.display();
	}

	return 0;
}