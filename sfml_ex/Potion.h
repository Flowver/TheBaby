#ifndef POTION_H
#define POTION_H

#include "Entity.h"
#include "Inventory.h"

class Entity;

class Potion :
	public Entity
{
private:
	//Variables
	Inventory* inventory;

	bool attacking;

	//Initializer functions
	void initVariables();
	void initComponents();
	void initAnimations();
	void initInventory();

public:
	Potion(float x, float y, sf::Texture& texture_sheet);
	virtual ~Potion();

	//Accessors
	AttributeComponent* getAttributeComponent();

	const std::string toStringCharacterTab() const;

	//Functions
	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainEXP(const int exp);
	void updateAnimation(const float& dt);
	void update(const float& dt, sf::Vector2f& mouse_pos_view);

	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

#endif