#include <SFML/Graphics.hpp>
#include <iostream>
#include "dictionary.hpp"
#include "Colors.hpp"

#define RECT_SIZE 100

/*===========================================
=				SFML STRUCT					=
===========================================*/

typedef struct s_grid {

	sf::Text			text;
	std::string			letter;
	Colors				color;
	sf::RectangleShape	shape;

} t_grid;

/*===========================================
=			UTILS FUNCTIONS					=
===========================================*/

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

/*===========================================
=				ANALYZING INPUT				=
===========================================*/

void analyse_input(t_grid grid[5], std::string line, std::string secret)
{
	std::string		cpy_line = line;
	std::string		cpy_secret = secret;

	for ( unsigned int i = 0; i < 5; i++)
	{
		if ( line.at(i) == cpy_secret.at(i) )
		{
			grid[i].color = Colors::GREEN;
			cpy_line.at(i) = ' ';
			cpy_secret.at(i) = ' ';
		}
	}

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

/*===========================================
=					MAINs					=
===========================================*/

int main()
{
/*===========================================
=					VARIABLES				=
===========================================*/

	sf::RenderWindow	window(sf::VideoMode(650, 1155), "Wordle!");
	t_grid				grid[6][5];
	sf::Font			font;
	sf::Font			titlefont;
	sf::Text			message;
	sf::Text			answer;
	sf::String			input[5];
	sf::Text			title;
	srand(time(NULL));
	Dictionary			dict;

	// std::cout << dict.get_secret() << std::endl;;

/*===========================================
=				LOADING FONTS				=
===========================================*/

	if (!font.loadFromFile("arial.ttf")) {
		exit(1);
	}

		if (!titlefont.loadFromFile("Vacaciones.ttf")) {
		exit(1);
	}

/*===========================================
=		MISE EN FORME DE LA GRILLE			=
===========================================*/

	for (size_t i = 0; i < 6; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{

			grid[i][j].shape = sf::RectangleShape(sf::Vector2f(RECT_SIZE, RECT_SIZE));
			grid[i][j].shape.setFillColor(sf::Color(Colors::BG));
			grid[i][j].shape.setOutlineColor(sf::Color(Colors::BORDER));
			grid[i][j].shape.setOutlineThickness(2);
			grid[i][j].shape.setPosition((j * (RECT_SIZE+10)) + 56, (i * (RECT_SIZE+10)) + 255);
			
			grid[i][j].letter = "";
			grid[i][j].color = Colors::BG;
			grid[i][j].text = sf::Text();
			grid[i][j].text.setFont(font);
			grid[i][j].text.setString(grid[i][j].letter);
			grid[i][j].text.setCharacterSize(40);
			grid[i][j].text.setPosition((j * (RECT_SIZE+10)) + 56 + (RECT_SIZE/3), (i * (RECT_SIZE+10)) + 255 + (RECT_SIZE/4));
		
		}
	}

/*===========================================
=			TITRE ET MESSAGE				=
===========================================*/

	title = sf::Text();
	title.setFont(titlefont);
	title.setString("WORDLE !");
	title.setCharacterSize(40);
	title.setPosition(225, 125);

	message = sf::Text();
	message.setFont(titlefont);
	message.setString("Type a word !");
	message.setCharacterSize(40);
	message.setPosition(200, 950);

	answer = sf::Text();

	std::string ans = "";

	answer.setFont(font);
	answer.setString(ans);
	answer.setCharacterSize(30);
	answer.setPosition(190, 1100);


/*===========================================
=					JEU						=
===========================================*/

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
					if (!dict.exist_word(word)) {
						message.setString("Not an existant word !");
						message.setPosition(100, 950);
						continue;
					}
					message.setString("Type a word");
					message.setPosition(200, 950);
					analyse_input(grid[currentRow], word, dict.get_secret());
					if (word == dict.get_secret()) {
						message.setString("Winning ! ");
						message.setPosition(235, 950);
						break;
					}
					currentRow++;
					currentLetter = 0;
					if (currentRow == 6) {
						message.setString("Loosing ! ");
						message.setPosition(235, 950);
						ans = "The answer was ";
						ans += dict.get_secret();
						answer.setString(ans);
						break ;
					}
				}
				else if (event.key.code == sf::Keyboard::BackSpace)
				{
					if (currentLetter <= 0)
						continue;
					currentLetter--;
					grid[currentRow][currentLetter].text.setString(' ');
					grid[currentRow][currentLetter].letter = "";
				}
				else {
					int keycode = static_cast<int>(event.key.code);
					if (keycode >= 0 && keycode <= 26)
					{
						if (currentLetter > 4)
							continue;
						grid[currentRow][currentLetter].text.setString((char)(keycode + 'A'));
						grid[currentRow][currentLetter].letter = (char)(keycode + 'A');
						currentLetter++;
						// std::cout << (char)(keycode + 'A') << std::endl; // Add letter with keycode + 'A'
					}
				}
				

			}
		}

/*===========================================
=					AFFICHAGE				=
===========================================*/

		window.clear(sf::Color(Colors::BG));
		for (size_t i = 0; i < 6; i++)
		{
			for (size_t j = 0; j < 5; j++)
			{
				grid[i][j].shape.setFillColor(sf::Color(grid[i][j].color));
				if (grid[i][j].color != Colors::BG)
					grid[i][j].shape.setOutlineColor(sf::Color(grid[i][j].color));
				window.draw(title);
				window.draw(message);
				window.draw(grid[i][j].shape);
				window.draw(grid[i][j].text);
				window.draw(answer);

			}
		}
		window.display();
	}

	return 0;
}