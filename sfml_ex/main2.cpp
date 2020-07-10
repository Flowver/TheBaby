/*
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Main_menu.h"
#include "player3.h"
#include "AnimatedSprite.hpp"

using namespace std;
using namespace sf;
const int width = 1600;
const int height = 900;
int page_number;

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
	{
		// load the tileset texture
		if (!m_tileset.loadFromFile(tileset))
			return false;

		// resize the vertex array to fit the level size
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);

		// populate the vertex array, with one quad per tile
		for (unsigned int i = 0; i < width; ++i)
			for (unsigned int j = 0; j < height; ++j)
			{
				// get the current tile number
				int tileNumber = tiles[i + j * width];

				// find its position in the tileset texture
				int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
				int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

				// get a pointer to the current tile's quad
				sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

				// define its 4 texture coordinates
				quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
				quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
			}
		return true;
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &m_tileset;

		// draw the vertex array
		target.draw(m_vertices, states);
	}

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};

class Box : public sf::RectangleShape
{
	float init_x=0, init_y=0;
	float x = 0, y = 0;
public:
	Box() : init_x(x), init_y(y)
	{
		setSize({ 32.0, 32.0 });
		setPosition(width/2, height/2);
		setFillColor(sf::Color(0, 235, 238));
		setOrigin(0, 0);
	}
	void update(int x, int y)
	{
		setPosition(x, y);
	}
};

const float BALL_SPEED = 5.0;

class Ball :public sf::CircleShape
{
public:
	float speedx = BALL_SPEED, speedy = BALL_SPEED;
	float x = 0, y = 0;
	Ball() : CircleShape(12.0)
	{
		setPosition(x, y);
		setFillColor(sf::Color(255, 58, 111));
		setOrigin(0, 0);
	}
	void update();
	bool isIntersecting(Box& box);
	void handleCollision(Box& box);
};

void Ball::update() {
	move(speedx, speedy);
	if ((getPosition().x) < 0)
		speedx = BALL_SPEED;
	else if ((getPosition().x + 2 * 20) > 1600)
		speedx = -BALL_SPEED;
	if (getPosition().y < 0)
		speedy = BALL_SPEED;
	else if ((getPosition().y + 2 * 20) > 900)
		speedy = -BALL_SPEED;
}

bool Ball::isIntersecting(Box& box)
{
	return getGlobalBounds().intersects(box.getGlobalBounds());
}

void Ball::handleCollision(Box& box)
{
	if (!isIntersecting(box)) return;

	if (getPosition().x < box.getPosition().x) {
		speedx = -BALL_SPEED;
		speedy = -BALL_SPEED;
	}
	else {
		speedx = BALL_SPEED;
		speedy = BALL_SPEED;
	}
}

int main() {
	// BGM 재생
	Music bg;
	bg.openFromFile("music/Before_The_Dawn.wav");

	// 무작위 범위 변수 생성
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0.0, width); //객체 시작가로범위
	std::uniform_int_distribution<int> dis2(0.0, height); //객체 시작가로범위

	// Ball 객체 생성  
	const int n = 10;
	Ball ball[n];
	for (int i = 0; i < n; i++) {
		float posx = dis(gen), posy = dis2(gen);
		ball[i].setPosition(posx, posy);
	}

	// 사각형 객체 생성
	Box box;
	float speedV = 0;
	float accelerationV = 0; // If no key is pressed, we won't accelerate
	float maxSpeedV = 10;

	//메인화면 크기 정하기
	sf::Vector2i screenDimensions(1280, 704);

	//플레이어 방향별 텍스쳐 생성
	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("./images/player.png"))
		std::cout << "Texture Error" << std::endl;
	// set up the animations for all four directions (set spritesheet and push frames)
	Animation walkingAnimationDown;
	walkingAnimationDown.setSpriteSheet(playerTexture);
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 32));

	Animation walkingAnimationLeft;
	walkingAnimationLeft.setSpriteSheet(playerTexture);
	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(0, 32, 32, 32));

	Animation walkingAnimationRight;
	walkingAnimationRight.setSpriteSheet(playerTexture);
	walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(0, 64, 32, 32));

	Animation walkingAnimationUp;
	walkingAnimationUp.setSpriteSheet(playerTexture);
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(0, 96, 32, 32));

	Animation* currentAnimation = &walkingAnimationDown;

	// set up AnimatedSprite
	AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
	animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));

	sf::Clock frameClock;

	float speed = 32.f;
	bool noKeyWasPressed = true;

	// 텍스트 생성
	sf::Text message;
	sf::Font font;
	font.loadFromFile("fonts/Sandblast.otf");
	// Set the font to our message
	message.setFont(font);
	// Assign the actual message
	message.setString("Hello world");
	// Make it really big
	message.setCharacterSize(100);
	// Choose a color
	message.setFillColor(sf::Color::White);

	// [particle] 경과 시간을 측정할 clock 생성
	sf::Clock clock;

	// [menu] 메뉴 생성
	while (true)
	{
		RenderWindow window(VideoMode(1280, 720), "Menu", Style::Close);
		Main_menu menu(1280, 720);
		window.setFramerateLimit(60);

		while (window.isOpen())
		{
			window.clear(sf::Color::Black);
			Event eventCheck;
			while (window.pollEvent(eventCheck)) {
				switch (eventCheck.type) {
				case Event::Closed:
					window.close();
					break;

				case Event::KeyPressed:
					switch (eventCheck.key.code) {
					case Keyboard::W:
						if (Keyboard::isKeyPressed(Keyboard::W)) {
							menu.moveUp();
						}
						break;
					case Keyboard::A:
						if (Keyboard::isKeyPressed(Keyboard::A)) {
						}
						break;
					case Keyboard::S:
						if (Keyboard::isKeyPressed(Keyboard::S)) {
							menu.moveDown();
						}
						break;
					case Keyboard::D:
						if (Keyboard::isKeyPressed(Keyboard::D)) {
						}
						break;
					case Keyboard::Return:
						if (Keyboard::isKeyPressed(Keyboard::Return)) {
							if (menu.mainMenuPressed() == 0)
							{
								window.close();
								page_number = 0;
							}
							if (menu.mainMenuPressed() == 1)
							{
								window.close();
								page_number = 1;
							}
							if (menu.mainMenuPressed() == 2)
							{
								window.close();
								page_number = 2;
							}
							break;
						}
					}
				}

			}
		window.clear();
		menu.draw(window);
		window.display();
		}

		// 메뉴 선택
		if (page_number == 0) // 게임 시작
		{
			// create the window
			sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Tilemap");

			// define the level with an array of tile indices
			const int level[] =
			{
				0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
				54, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 56,
			};

			// create the tilemap from the level definition
			TileMap map;
			if (!map.load("C:/Users/0000/Desktop/kenney_rpgurbanpack/Tilemap/tilemap_packed_32.png", sf::Vector2u(32, 32), level, 40, 22))
				return -1;

			// run the main loop
			while (window.isOpen())
			{
				// handle events
				sf::Event event;
				
				while (window.pollEvent(event))
				{	
					if (event.type == sf::Event::Closed)
						window.close();
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
						window.close();
				}

				//Collision Detection


				sf::Time frameTime = frameClock.restart();

				// if a key was pressed set the correct animation and move correctly
				sf::Vector2f movement(0.f, 0.f);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					currentAnimation = &walkingAnimationUp;
					movement.y -= speed;
					noKeyWasPressed = false;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					currentAnimation = &walkingAnimationDown;
					movement.y += speed;
					noKeyWasPressed = false;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					currentAnimation = &walkingAnimationLeft;
					movement.x -= speed;
					noKeyWasPressed = false;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					currentAnimation = &walkingAnimationRight;
					movement.x += speed;
					noKeyWasPressed = false;
				}
				animatedSprite.play(*currentAnimation);
				animatedSprite.move(movement * frameTime.asSeconds());

				// if no key was pressed stop the animation
				if (noKeyWasPressed)
				{
					animatedSprite.stop();
				}
				noKeyWasPressed = true;

				// update AnimatedSprite
				animatedSprite.update(frameTime);

				// draw
				window.clear();
				window.draw(map);
				window.draw(animatedSprite);
				window.display();
			}

			return 0;
		}

		if (page_number == 1)
		{
			//options
			sf::RenderWindow window_play(VideoMode(704, 704), "options", sf::Style::Close);
			while (window_play.isOpen())
			{
				sf::Event event;
				while (window_play.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window_play.close();

				}
				window_play.clear();
				window_play.display();
			}
		}

		if (page_number == 2)
		{
			//exit
			break;
		}
	}
}


*/