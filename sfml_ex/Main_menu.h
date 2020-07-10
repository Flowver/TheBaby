#pragma once
#include <SFML/Graphics.hpp>

#define Max_main_menu 3

class Main_menu //menu
{
public:
	Main_menu(float width, float hight);


	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();

	int mainMenuPressed()
	{
		return mainMenuSelected;
	}

	~Main_menu();

private:
	int mainMenuSelected;
	sf::Font font;
	sf::Text mainMenu[Max_main_menu];
};