#include "stdafx.h"
#include "GameState.h"


void GameState::updatePortal(const float& dt)
{
	this->portal->update(dt, this->mousePosView);
}

void GameState::updateSound(const float& dt)
{
	if (this->player->sprinting) { footsteps_.setPitch(2); }
	else {footsteps_.setPitch(1); }


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{ //if a directional key is pressed
		if (!stepSoundPlaying)
		{
			stepSoundPlaying = true;
			footsteps_.play();
		}
	}
		else 
		{
			stepSoundPlaying = false;
			footsteps_.stop();
		}

}

void GameState::initBgm()
{
	bgmRain_.setBuffer(buffers_[0]);
	bgmRain_.setLoop(1);
	bgmRain_.setVolume(20);
	bgmRain_.play();
}

void GameState::initSounds()
{
	std::string root("Resources/Music/");
	if (!buffers_[0].loadFromFile(root + "backgroundRain.ogg"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");
	if (!buffers_[1].loadFromFile(root + "enemyDeath.ogg"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");
	if (!buffers_[2].loadFromFile(root + "enemyHurt.ogg"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");
	if (!buffers_[3].loadFromFile(root + "gunPickup.ogg"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");
	if (!buffers_[4].loadFromFile(root + "gunshot.ogg"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");
	if (!buffers_[5].loadFromFile(root + "playerDeath.ogg"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");
	if (!buffers_[6].loadFromFile(root + "playerHurt.ogg"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");
	if (!buffers_[7].loadFromFile(root + "glassSmash.ogg"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");
	if (!buffers_[8].loadFromFile(root + "breathOfDeath.ogg"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");
	if (!buffers_[9].loadFromFile(root + "deathIsComing.ogg"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");
	if (!buffers_[10].loadFromFile(root + "evilLaugh.ogg"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");
	if (!buffers_[11].loadFromFile(root + "panicScare.ogg"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");
	if (!buffers_[12].loadFromFile(root + "scaryViolins.ogg"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");
	if (!buffers_[13].loadFromFile(root + "screamWoman.ogg"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");
	if (!buffers_[14].loadFromFile(root + "screamZombie.ogg"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");
	if (!buffers_[15].loadFromFile(root + "whatAreYouDoingHere.ogg"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");
	if (!this->buffers_[16].loadFromFile(root + "footstep.wav"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD AUDIO");

	footsteps_.setBuffer(buffers_[16]);
	footsteps_.setLoop(1);
	footsteps_.setVolume(70);

	hurtSnd_.setBuffer(buffers_[6]);
	hurtSnd_.setLoop(0);
	hurtSnd_.setVolume(20);

	deathSnd_.setBuffer(buffers_[5]);
	deathSnd_.setLoop(0);
	deathSnd_.setVolume(20);
}

void GameState::initItems() {
	this->potions.push_back(new Potion(2335, 117, this->textures["EFFECT_SHEET"]));
	this->potions.push_back(new Potion(756, 1515, this->textures["EFFECT_SHEET"]));
	this->potions.push_back(new Potion(1902, 2001, this->textures["EFFECT_SHEET"]));
	this->potions.push_back(new Potion(5248, 1881, this->textures["EFFECT_SHEET"]));
	this->potions.push_back(new Potion(7531, 4542, this->textures["EFFECT_SHEET"]));

	this->portal = new Portal(5221, 4261, this->textures["AURA_SHEET"]);
}

void GameState::updateItems(const float& dt) {

	sf::Time elapsed = this->ItemTimer.getElapsedTime();

	for (auto* potion : this->potions)
	{
		potion->update(dt, this->mousePosView);
		if (player->getGlobalBounds().intersects(potion->getGlobalBounds()))
		{
			ItemTimer.restart();
			this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader2.frag");
		}
		if (elapsed.asSeconds() >= ItemTimerMax)
		{
			this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag");
		}
	}

}

void GameState::initGameOverText() {
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
}

void GameState::initGameWinText() {
	this->gameWinText.setFont(this->font);
	this->gameWinText.setCharacterSize(60);
	this->gameWinText.setFillColor(sf::Color::Blue);
	this->gameWinText.setString("You Survived!");
	this->gameWinText.setPosition(
		this->window->getSize().x / 2.f - this->gameWinText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameWinText.getGlobalBounds().height / 2.f);
}

void GameState::initEnemies() {
	this->spawnTimerMax = 1000.f;
	this->spawnTimer = this->spawnTimerMax;;
}

void GameState::updateSpawn() {

	//Spawning
	this->spawnTimer += 1.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(1911, 2019, this->textures["ENEMY_SHEET"]));
		this->spawnTimer = 0.f;
	}
}

void GameState::updateEnemiesCollision(Player* player, const float& dt)
{
	//Update
	unsigned counter = 0;

	for (auto* enemy : this->enemies)
	{
		enemy->update(dt, this->mousePosView);
		enemy->chase(*player);

		//Enemy player collision
		if (player->getGlobalBounds().intersects(enemy->getGlobalBounds()))
		{
			player->loseHP(1);
			this->enemies.erase(this->enemies.begin() + counter);
			hurtSnd_.play();
		}
		++counter;
	}


}


void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0,
			0,
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height
		)
	);
}

//Initializer functions
void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
			static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
		)
	);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

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

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/BRLNSDB.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/PLAYER_SHEET2.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["EFFECT_SHEET"].loadFromFile("Resources/Images/Effect95.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_EFFECT_TEXTURE";
	}
	if (!this->textures["AURA_SHEET"].loadFromFile("Resources/Images/Aura38.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_AURA_TEXTURE";
	}
	if (!this->textures["ENEMY_SHEET"].loadFromFile("Resources/Images/pngfind.com-running-emoji-png-6361240.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_ENEMY_TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");
}

void GameState::initShaders()
{
	if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER." << "\n";
	}
}

void GameState::initKeyTime()
{
	this->keyTimeMax = 0.3f;
	this->keyTimer.restart();
}

void GameState::initPlayers()
{
	this->player = new Player(220, 220, this->textures["PLAYER_SHEET"]);
}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap("text.slmp");
}

void GameState::initSystems()
{
	this->tts = new TextTagSystem("Resources/Fonts/BRLNSDB.ttf");
}

//Constructors / Destructors
GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initShaders();
	this->initKeyTime();

	this->initPlayers();
	this->initPlayerGUI();
	this->initTileMap();
	this->initSystems();
	this->initEnemies();
	this->initGameOverText();
	this->initGameWinText();
	this->initItems();
	this->initSounds();
	this->initBgm();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->playerGUI;
	delete this->tileMap;
	delete this->tts;

	//Delete enemies
	for (auto *i : this->enemies)
	{
		delete i;
	}
	for (auto* i : this->potions)
	{
		delete i;
	}
}

const bool GameState::getKeyTime()
{
	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}

	return false;
}

//Functions
void GameState::updateView(const float& dt)
{
	this->view.setCenter(
		std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 10.f),
		std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 10.f)
	);

	if (this->tileMap->getMaxSizeF().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x)
		{
			this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}

	if (this->tileMap->getMaxSizeF().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeF().y)
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
		}
	}

	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{

		this->player->move(-1.f, 0.f, dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{

		this->player->move(1.f, 0.f, dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{

		this->player->move(0.f, -1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{

		this->player->move(0.f, 1.f, dt);
	}

}

void GameState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->update(dt);

}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->updateWorldBoundsCollision(this->player, dt);
	this->tileMap->updateTileCollision(this->player, dt);
}

void GameState::updatePlayer(const float& dt)
{
	this->player->update(dt, this->mousePosView);
}



void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //Unpaused update
	{
		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->updateTileMap(dt);

		this->updatePlayer(dt);

		this->updatePlayerGUI(dt);

		this->updateSpawn();

		this->updateEnemiesCollision(player, dt);

		this->updateItems(dt);

		this->updateSound(dt);

		this->updatePortal(dt);

		//Update systems
		this->tts->update(dt);

	}
	else //Paused update
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();

	}

}


void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);

	this->tileMap->render(
		this->renderTexture,
		this->viewGridPosition,
		&this->core_shader,
		this->player->getCenter(),
		false
	);

	this->portal->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);

	this->player->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);

	this->tileMap->renderDeferred(this->renderTexture, &this->core_shader, this->player->getCenter());

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);
	}

	for (auto* potion : this->potions)
	{
		potion->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);
	}


	this->tts->render(this->renderTexture);

	//Render GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);

	if (this->paused) //Pause menu render
	{
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	//FINAL RENDER
	this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);

	//GameOver
	if (player->isDead())
	{
		this->pmenu->menuText.setString("");
		this->pauseState();
		target->draw(this->gameOverText);
		deathSnd_.play();
	}
	//GameWin
	if (player->getGlobalBounds().intersects(portal->getGlobalBounds()))
	{
		this->pmenu->menuText.setString("");
		this->pauseState(); 
		target->draw(this->gameWinText);
	}

}

