#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "TextTagSystem.h"
#include "enemy.h"
#include "Potion.h"
#include "Portal.h"

class GameState :
	public State
{
private:

	sf::SoundBuffer buffers_[20];

	sf::View view;
	sf::Vector2i viewGridPosition;
	sf::RenderTexture renderTexture;
	sf::RenderTexture renderTexture2;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pmenu;
	sf::Text gameOverText;
	sf::Text gameWinText;

	sf::Shader core_shader;

	sf::Clock keyTimer;
	float keyTimeMax;

	TileMap* tileMap;

	//Player
	Player* player;
	PlayerGUI* playerGUI;
	sf::Texture texture;

	//Enemy
	std::vector<Enemy*> enemies;
	float spawnTimer;
	float spawnTimerMax;

	//Item
	std::vector<Potion*> potions;
	sf::Clock ItemTimer;
	float ItemTimerMax =5.0f;
	Portal* portal;

	//Systems
	TextTagSystem* tts;

	//Sounds
	bool stepSoundPlaying;
	bool sprintSoundPlaying;
	sf::Sound bgmRain_;
	sf::Sound footsteps_;
	sf::Sound hurtSnd_;
	sf::Sound deathSnd_;

	//Functions
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initShaders();
	void initKeyTime();
	void initPlayers();
	void initPlayerGUI();
	void initTileMap();
	void initSystems();

	void initGameOverText();
	void initGameWinText();
	void initEnemies();
	void initSounds();
	void initBgm();
	void initItems();

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	//Accessors
	const bool getKeyTime();

	//Functions
	void updateView(const float& dt);
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePlayerGUI(const float& dt);
	void updatePauseMenuButtons();
	void updateTileMap(const float& dt);
	void updatePlayer(const float& dt);
	void update(const float& dt);

	void updateEnemiesCollision(Player* player, const float& dt);
	void updateSpawn();
	void updateItems(const float& dt);
	void updateSound(const float& dt);
	void updatePortal(const float& dt);

	void render(sf::RenderTarget* target = NULL);
};

#endif