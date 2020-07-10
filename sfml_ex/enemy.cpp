#include "stdafx.h"
#include "enemy.h"

#include "VectorUtils.h"

//Initializer functions
void Enemy::initVariables()
{
	this->attacking = true;
	this->pointCount = rand() % 2 + 3; //min = 3 max = 4
	this->speed = static_cast<float>(this->pointCount / 3);
}

void Enemy::initComponents()
{

}

void Enemy::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 0, 0, 228.5, 278);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 0, 3, 0, 228.5, 278);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 2, 3, 2, 228.5, 278);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 3, 3, 3, 228.5, 278);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 1, 3, 1, 228.5, 278);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 0, 0, 2, 228.5, 278);
}

//Constructors / Destructors
Enemy::Enemy(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, 114.f, 268.f, 40.f, 54.f);
	this->createMovementComponent(70.f, 1000.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->setPosition(x, y);
	this->initAnimations();

}

Enemy::~Enemy()
{

}

//Accessors
AttributeComponent* Enemy::getAttributeComponent()
{
	return this->attributeComponent;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

const std::string Enemy::toStringCharacterTab() const
{
	std::stringstream ss;
	AttributeComponent* ac = this->attributeComponent;

	ss << "Level: " << ac->level << "\n"
		<< "Exp: " << ac->exp << "\n"
		<< "Exp next: " << ac->expNext << "\n";

	return ss.str();
}

//Functions
void Enemy::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Enemy::gainHP(const int hp)
{
	this->attributeComponent->gainHP(hp);
}

void Enemy::loseEXP(const int exp)
{
	this->attributeComponent->loseEXP(exp);
}

void Enemy::gainEXP(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

void Enemy::updateAnimation(const float& dt)
{
	if (this->attacking)
	{

	}
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Enemy::update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();

}


void Enemy::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
	}
	else
	{
		target.draw(this->sprite);
	}

	if (show_hitbox)
		this->hitboxComponent->render(target);
}


void Enemy::movearound()
{
	this->move(0.f, this->speed,1);
}


void Enemy::chase(Entity &entity)
{
	// Make movement
	sf::Vector2f playerPosition = entity.getPosition();
	sf::Vector2f thisPosition = this->getPosition();

	sf::Vector2f direction = normalize(playerPosition - thisPosition);
	move(direction.x,direction.y,speed/5);
}