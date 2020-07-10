#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"

class HitboxComponent;
class MovementComponent;
class AnimationComponent;
class AttributeComponent;

class Entity
{
private:
	void initVariables();

protected:

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	AttributeComponent* attributeComponent;

public:
	sf::RectangleShape rect;
	sf::Text text;
	sf::Clock clock;
	sf::Time timer;
	sf::Sprite sprite;

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite,
		float offset_x, float offset_y,
		float width, float height);
	void createMovementComponent(float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createAttributeComponent(const unsigned level);

	//Accessors
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2f getCenter() const;
	virtual const sf::Vector2f getGridPosition(const int gridSizeI) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;

	//Modifiers
	virtual void setPosition(const float x, const float y);
	virtual void setmaxVelocity(const float maxVelocity);

	//Functions
	virtual void move(const float x, const float y, const float& dt);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	//Calculations
	virtual const float getDistance(const Entity& entity) const;

	virtual void update(const float& dt, sf::Vector2f& mouse_pos_view) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox) = 0;


};

#endif

