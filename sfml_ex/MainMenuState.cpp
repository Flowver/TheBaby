#include "stdafx.h"
#include "MainMenuState.h"

//Initializer functions
void MainMenuState::initVariables()
{

}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/BRLNSDB.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initBgm() {
	
	if (!this->music.openFromFile("Resources/Bgm/horror_piano.wav"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD BGM");
	}
	music.setLoop(true);
	music.play();
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void MainMenuState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//Background
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Background/bg1.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	//Button background
	this->btnBackground.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width/3.5),
			static_cast<float>(vm.height/4)
		)
	);

	this->btnBackground.setPosition(gui::p2pX(46.f, vm), 50.f);
	this->btnBackground.setFillColor(sf::Color(10, 10, 10, 120));

	//Buttons
	this->buttons["GAME_STATE"] = new gui::Button(
		gui::p2pX(62.f, vm), gui::p2pY(52.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Start", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["SETTINGS_STATE"] = new gui::Button(
		gui::p2pX(59.f, vm), gui::p2pY(60.f, vm),
		gui::p2pX(20.f, vm), gui::p2pY(6.f, vm),
		&this->font, "How to Play", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new gui::Button(
		gui::p2pX(62.f, vm), gui::p2pY(68.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Quit", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

}

void MainMenuState::resetGui()
{
	/*
	 * Clears the GUI elements and re-initialises the GUI.
	 *
	 * @return void
	 */

	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	this->initGui();
}

MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->resetGui();
	this->initBgm();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->backgroundTexture.loadFromFile("Resources/Images/Background/bg2.jpg");
		this->states->push(new GameState(this->stateData));
	}

	//Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}

	

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}


}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	target->draw(this->btnBackground);

	this->renderButtons(*target);
}

