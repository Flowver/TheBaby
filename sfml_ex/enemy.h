#ifndef Enemy_H
#define Enemy_H

#include "Player.h"
#include "Entity.h"

class Entity;

class Enemy :
	public Entity
{
private:
	bool attacking;
	float speed;
	unsigned pointCount;

	//Initializer functions
	void initVariables();
	void initComponents();
	void initAnimations();

public:
	Enemy(float x, float y, sf::Texture& texture_sheet);
	virtual ~Enemy();

	//Variables
	float spawnTimer;
	float spawnTimerMax;
	int damage;
	sf::Texture enemy;
	std::vector<Enemy*> enemies;


	//Accessors
	AttributeComponent* getAttributeComponent();

	const std::string toStringCharacterTab() const;

	//Functions
	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainEXP(const int exp);
	const int& getDamage() const;

	void updateAnimation(const float& dt);
	void update(const float& dt, sf::Vector2f& mouse_pos_view);
	void movearound();
	void chase(Entity& entity);


	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

#endif