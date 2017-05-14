#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

int main()
{
	using std::vector;

	sf::ContextSettings aaSettings;
	aaSettings.antialiasingLevel = 8; 

	int_fast32_t winSizeX{ 1360 }, winSizeY{ 600 };

	sf::RenderWindow window(sf::VideoMode(winSizeX, winSizeY), "Magic Manor: Afterlife Alchemy", sf::Style::Default, aaSettings);
	window.setFramerateLimit(60);

	sf::Texture bgTex;
	if (!bgTex.loadFromFile("C:\\Users\\Andy\\OneDrive\\Dokumenter\\Andy hjemme\\Visual Studio 2017\\Projects\\Magic Manor\\Debug\\Tree background.jpg")) {}

	sf::Sprite bg;
	bg.setTexture(bgTex);

	/*
	 *TODO: Put the grid creation (with tiles and textures and stuff) 
	 *inside it's own function. Probably has to do with Map class. 
	 */

	sf::Texture texy;
	if (!texy.loadFromFile("C:\\Users\\Andy\\OneDrive\\Dokumenter\\Andy hjemme\\Visual Studio 2017\\Projects\\Magic Manor\\Debug\\Grass - Actual hexagon.png"))
	{
		//Meh
	}

	texy.setSmooth(true);

	//Amount of hexagons on the y-axis.
	//TODO: Let user change this.
	int_fast32_t hexnum{ 7 };

	//TODO: When having a fullscreen game, find the screen height and use that instead of winSizeY 
	//Why not use double to make stuff fit? Actually, let's try that now.
	//Do I need that double in front of winSizeY? 
	double hexHeight{ double(winSizeY) / hexnum };
	double hexWidht{ hexHeight * ((sqrt(3) / 2)) };
	
	//The hex-grid alternates between columns with more and less hexagons.
	//Used to decide whether the first hexagon of the column should be 
	//offset on the y-axis
	bool shortColumn{ false };

	double gridWidth{ 0 };

	//Vector of tiles, not sprites. Just testing.
	vector<sf::Sprite> tiles;
	
	while (gridWidth + hexWidht <= winSizeX) //Use window size
	{
		//Check if column should start with y-offset
		double gridHeight{ (shortColumn ? ((hexHeight * 3) / 4) : 0) };
		shortColumn = !shortColumn;

		while (gridHeight + hexHeight <= winSizeY) //Use window size
		{
			sf::Sprite tile;
			tile.setTexture(texy);
			//Save computation instead of repeating it?
			tile.scale(double(hexHeight / texy.getSize().y), double(hexHeight / texy.getSize().y));
			tile.setPosition(gridWidth, gridHeight); 
			tiles.emplace_back(tile);

			gridHeight += (hexHeight * 1.5);
		}

		gridWidth += (hexWidht / 2);
	}
	
	//sf::Sprite spritey;
	//spritey.setTexture(texy);

	//spritey.scale(0.3125, 0.3125);
	//
	//sf::Sprite spritex = spritey; 	
	////spritex.scale(0.2, 0.2);
	//spritex.setPosition(spritey.getGlobalBounds().width / 2, double((spritey.getGlobalBounds().height * 3)/4) );

	//sf::Sprite spritez = spritey;
	////spritez.scale(0.2, 0.2);
	//spritez.setPosition(-(spritez.getGlobalBounds().width / 2), double((spritez.getGlobalBounds().height * 3) / 4));
	//
	//std::cout << spritey.getGlobalBounds().height << "\n" << spritey.getGlobalBounds().width << "\n";
	//std::cout << spritex.getPosition().x << "\n" << spritex.getPosition().y << "\n";

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
		window.draw(bg);
		
		for (const sf::Sprite &tile : tiles)
			window.draw(tile);

		window.display();
	}
	return 0;
}