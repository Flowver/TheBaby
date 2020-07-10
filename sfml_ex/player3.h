#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Player(); //Constructor
    Player(sf::Texture&); //Overload Constructor
    ~Player(); //Destructor

    //PLAYER MOVEMENT FUNCTIONS
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void setSpeed(float, sf::Time);

    //ACCESSOR FUNCTIONS
    sf::Sprite getSprite() const;

private:
    sf::Sprite _Sprite; //Declare Player Sprite
    sf::Vector2i _Source; //Declare Source (Sprite Sheet Crop)
    enum _Direction { Down, Left, Right, Up }; //Declare Direction Enumeration

    //ANIMATION DATA
    float _Speed; //Player Speed
    sf::Clock _AnimClock; //Player Animation Clock
    sf::Time _AnimTime; //Player Animation Time
};

#endif // PLAYER_H