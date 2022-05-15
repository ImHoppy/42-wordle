#include <SFML/Graphics.hpp>
#include <iostream>

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

int main()
{
	sf::RenderWindow	window(sf::VideoMode(650, 900), "Wordle!");
	sf::RectangleShape	wordsShape[5];
	t_grid				grid[6][5];
	sf::Font			font;
	sf::String			input[5];

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
	// for (size_t i = 0; i < 5; i++)
	// {
	// 	wordsShape[i] = sf::RectangleShape(sf::Vector2f(RECT_SIZE, 1));
	// 	wordsShape[i].setPosition((i * (RECT_SIZE+10)) + 55, 900 * 0.95);
	// }
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
					if (len_grid(grid[currentRow]) != 5)
						continue;
					if (join_word(grid[currentRow]) != "TREES")
						continue;
					currentRow++;
					currentLetter = 0;
					std::cout << "Enter" << std::endl; // check word in gridShape
				}
				else if (event.key.code == sf::Keyboard::BackSpace)
				{
					if (currentLetter <= 0)
						continue;
					currentLetter--;
					grid[currentRow][currentLetter].text.setString("");
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
				window.draw(grid[i][j].shape);
				window.draw(grid[i][j].text);
			}
		}
		// for (size_t i = 0; i < 5; i++)
		// {
		// 	window.draw(wordsShape[i]);
		// }
		window.display();
	}

	return 0;
}