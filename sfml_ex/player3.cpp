#include <SFML/Graphics.hpp>
#include <iostream>
#include "player3.h"


Player::Player() //Constructor
{

}

Player::Player(sf::Texture& TEMP_Texture) //Overload Constructor
{
    //PLAYER SPRITE
    _Sprite.setTexture(TEMP_Texture); //Set Sprite Texture
    _Sprite.setPosition(600 - 32, 600 - 32); //Set Sprite Position (Centre)
    _Sprite.setScale(2.0f, 2.0f); //Sprite Scale
    sf::Vector2i _Source(1, Down); //Default Sprite Sheet Crop
    _Sprite.setTextureRect(sf::IntRect(_Source.x * 32, _Source.y * 32, 32, 32)); //Crop Sprite Sheet (Default Crop)

    //PLAYER / ANIMATION SPEED
    _AnimTime = sf::milliseconds(80); //Animation Speed
    _Speed = 32; //Player Speed
}

Player::~Player() //Destructor
{
}

//ACCESSOR FUNCTIONS
sf::Sprite Player::getSprite() const //Player Sprite
{
    return _Sprite;
}

//PLAYER MOVEMENT
void Player::moveUp()
{
    _Source.y = Up; //Set '_Source.y' Equal To 'Up' (_Direction Enum)
    _Sprite.move(0, -_Speed); //Move Player Sprite

    if (_AnimClock.getElapsedTime() > _AnimTime)
    {
        _Sprite.setTextureRect(sf::IntRect(_Source.x * 32, _Source.y * 32, 32, 32));  //Crop Sprite Sheet

        //Animation
        _Source.x++;
        if (_Source.x * 32 >= _Sprite.getTexture()->getSize().x)
        {
            _Source.x = 0;
        }
        _AnimClock.restart();

    }

}

void Player::moveDown()
{
    _Source.y = Down; //Set '_Source.y' Equal To 'Up' (_Direction Enum)
    _Sprite.move(0, _Speed); //Move Player Sprite

    if (_AnimClock.getElapsedTime() > _AnimTime)
    {
        _Sprite.setTextureRect(sf::IntRect(_Source.x * 32, _Source.y * 32, 32, 32)); //Crop Sprite Sheet

        //Animation
        _Source.x++;
        if (_Source.x * 32 >= _Sprite.getTexture()->getSize().x)
        {
            _Source.x = 0;
        }
        _AnimClock.restart();

    }
}

void Player::moveRight()
{
    _Source.y = Right; //Set '_Source.y' Equal To 'Up' (_Direction Enum)
    _Sprite.move(_Speed, 0); //Move Player Sprite

    if (_AnimClock.getElapsedTime() > _AnimTime)
    {
        _Sprite.setTextureRect(sf::IntRect(_Source.x * 32, _Source.y * 32, 32, 32)); //Crop Sprite Sheet

        //Animation
        _Source.x++;
        if (_Source.x * 32 >= _Sprite.getTexture()->getSize().x)
        {
            _Source.x = 0;
        }
        _AnimClock.restart();
    }
}


void Player::moveLeft()
{
    _Source.y = Left; //Set '_Source.y' Equal To 'Up' (_Direction Enum)
    _Sprite.move(-_Speed, 0); //Move Player Sprite

    if (_AnimClock.getElapsedTime() > _AnimTime)
    {
        _Sprite.setTextureRect(sf::IntRect(_Source.x * 32, _Source.y * 32, 32, 32)); //Crop Sprite Sheet

        //Animation
        _Source.x++;
        if (_Source.x * 32 >= _Sprite.getTexture()->getSize().x)
        {
            _Source.x = 0;
        }
        _AnimClock.restart();
    }
}

void Player::setSpeed(float TEMP_Speed, sf::Time TEMP__AnimTime) //Sprint Speed
{
    _Speed = TEMP_Speed;
    _AnimTime = TEMP__AnimTime;
}