#include "stdafx.h"
#include "Potion.h"

//Initializer functions
void Potion::initVariables()
{
	this->attacking = false;
}

void Potion::initComponents()
{

}

void Potion::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 3, 0, 128, 128);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
}

//Constructors / Destructors
Potion::Potion(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, 12.f, 10.f, 40.f, 54.f);
	this->createMovementComponent(400.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->setPosition(x, y);
	this->initAnimations();
}

Potion::~Potion()
{

}

//Accessors
AttributeComponent* Potion::getAttributeComponent()
{
	return this->attributeComponent;
}

const std::string Potion::toStringCharacterTab() const
{
	std::stringstream ss;
	AttributeComponent* ac = this->attributeComponent;

	ss << "Level: " << ac->level << "\n"
		<< "Exp: " << ac->exp << "\n"
		<< "Exp next: " << ac->expNext << "\n";

	return ss.str();
}

//Functions
void Potion::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Potion::gainHP(const int hp)
{
	this->attributeComponent->gainHP(hp);
}

void Potion::loseEXP(const int exp)
{
	this->attributeComponent->loseEXP(exp);
}

void Potion::gainEXP(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

void Potion::updateAnimation(const float& dt)
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

void Potion::update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();

}

void Potion::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
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
