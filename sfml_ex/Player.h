#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Entity;

class Player :
	public Entity
{
private:
	//Variables
	bool attacking;

	//Initializer functions
	void initVariables();
	void initComponents();
	void initAnimations();

public:
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	bool sprinting;

	//Accessors
	AttributeComponent* getAttributeComponent();

	const std::string toStringCharacterTab() const;

	//Functions
	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainEXP(const int exp);
	void loseSprint(const float sprint);
	void gainSprint(const float sprint);
	void sprint();
	const bool isDead() const;
	const bool isSprinting() const;

	void updateAnimation(const float& dt);
	void update(const float& dt, sf::Vector2f& mouse_pos_view);

	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

#endif