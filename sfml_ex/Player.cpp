#include "stdafx.h"
#include "Player.h"

//Initializer functions
void Player::initVariables()
{
	this->attacking = false;
}

void Player::initComponents()
{

}

void Player::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
}

//Constructors / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, 12.f, 10.f, 40.f, 54.f);
	this->createMovementComponent(200.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->setPosition(x, y);
	this->initAnimations();
}

Player::~Player()
{

}

//Accessors
AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

const std::string Player::toStringCharacterTab() const
{
	std::stringstream ss;
	AttributeComponent* ac = this->attributeComponent;

	ss << "Level: " << ac->level << "\n"
		<< "Exp: " << ac->exp << "\n"
		<< "Exp next: " << ac->expNext << "\n";

	return ss.str();
}


//Functions
void Player::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->gainHP(hp);
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->loseEXP(exp);
}

void Player::gainEXP(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

const bool Player::isDead() const
{
	return this->attributeComponent->isDead();
}

const bool Player::isSprinting() const
{
	return this->sprinting;
}

void Player::loseSprint(const float sprint)
{
	this->attributeComponent->loseSprint(sprint);
}

void Player::gainSprint(const float sprint)
{
	this->attributeComponent->gainSprint(sprint);
}

void Player::sprint()
{
	if (this->getAttributeComponent()->sprint > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		sprinting = true;
		this->setmaxVelocity(600.f);
		loseSprint(0.05f); //decrease sprint timer towards 0
	}
	else
	{
		sprinting = false; //sprint timer is equal or less than 0 change move speed to walking pace
		this->setmaxVelocity(200.f);
		gainSprint(0.02f);
	}

}

void Player::updateAnimation(const float& dt)
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

void Player::update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();

	this->sprint();

}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
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

