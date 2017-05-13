#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include <cstdint>
#include <iostream>

int main()
{

	sf::ContextSettings aaSettings;
	aaSettings.antialiasingLevel = 8; 

	int_fast32_t winSizeX{ 1360 }, winSizeY{ 690 };

	sf::RenderWindow window(sf::VideoMode(winSizeX, winSizeY), "Magic Manor: Afterlife Alchemy", sf::Style::Default, aaSettings);
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break; 

				default:
					break;
			}
		}

		window.clear(sf::Color::Black);
		//window.draw
		window.display();
	}
	return 0;
}