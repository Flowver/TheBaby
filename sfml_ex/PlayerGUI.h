#pragma once

#include "PlayerGUITabs.h"

class PlayerGUI
{
private:
	Player* player;

	sf::VideoMode& vm;
	sf::Font font;

	//Level bar
	std::string levelBarString;
	sf::Text levelBarText;
	sf::RectangleShape levelBarBack;

	//EXP Bar
	gui::ProgressBar* expBar;

	//HP Bar
	gui::ProgressBar* hpBar;

	//Sprint Bar
	gui::ProgressBar* sprintBar;


	void initFont();
	void initLevelBar();
	void initEXPBar();
	void initHPBar();
	void initSprintBar();

public:
	PlayerGUI(Player* player, sf::VideoMode& vm);
	virtual ~PlayerGUI();

	//Functions
	void updateLevelBar();
	void updateEXPBar();
	void updateHPBar();
	void updateSprintBar();

	void update(const float& dt);

	void renderLevelBar(sf::RenderTarget& target);
	void renderEXPBar(sf::RenderTarget& target);
	void renderHPBar(sf::RenderTarget& target);
	void renderSprintBar(sf::RenderTarget& target);

	void render(sf::RenderTarget& target);
};

