/*
#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <Windows.h>

using namespace sf;
int width = 1920;
int height = 1080;

int main() {
	srand(time(NULL));

	RenderWindow window(VideoMode(width, height), "ARKANOID");
	window.setFramerateLimit(60);

	Texture t1, t2, t3, t4;
	t1.loadFromFile("images/block.png");
	t2.loadFromFile("images/ball.png");
	t3.loadFromFile("images/background_w.png");
	t4.loadFromFile("images/paddle.png");

	Sprite block(t1), ball(t2), background(t3),paddle(t4);
	block.setTexture(t1);
	background.setTexture(t3);
	ball.setTexture(t2);
	paddle.setTexture(t4);

	// ball.setPosition(width / 2, height / 2);

	paddle.setPosition(width / 2, height * 9 / 10);

	const int size = 100;
	std::vector<Sprite> blocks(100);
	int n = 0;
	auto bsize = t1.getSize();
	for (int i=1; i<=10; i++)
		for (int j = 1; j <= 10; j++)
		{
			blocks[n].setTexture(t1);
			blocks[n].setPosition(i * bsize.x, j * bsize.y);
			n++;
		}
	float dx=3,dy=3;
	//main loop (ends if the window is closed)
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		auto ball_pos = ball.getPosition();

		ball_pos.x += dx;
		for (int i = 0; i < blocks.size(); i++) {
			if (FloatRect(ball_pos.x + 18, ball_pos.y + 18, 36, 36).intersects(
				blocks[i].getGlobalBounds())) {
				blocks.erase(blocks.begin() + i);
				dx = -dx;
			}
		}


		ball_pos.y += dy;
		for (int i = 0; i < blocks.size(); i++) {
			if (FloatRect(ball_pos.x + 18, ball_pos.y + 18, 36, 36).intersects(
					blocks[i].getGlobalBounds())) {
					blocks.erase(blocks.begin() + i);
				dy = -dy;
			}
		}
		if (ball_pos.x < 0 || ball_pos.x>520) dx = -dx;
		if (ball_pos.y < 0 || ball_pos.y>450) dy = -dy;

		if (Keyboard::isKeyPressed(Keyboard::Right))
			paddle.move(5, 0);

		if (Keyboard::isKeyPressed(Keyboard::Left))
			paddle.move(-5, 0);

		if (FloatRect(ball_pos.x, ball_pos.y, 12, 12).intersects(paddle.getGlobalBounds()))
			dy = -(rand() % 5 + 2);
		ball.setPosition(ball_pos.x, ball_pos.y);
		

//		if (Keyboard::isKeyPressed(Keyboard::Left))
//			ball.move(-20.0, 0.0);
//		if (Keyboard::isKeyPressed(Keyboard::Right))
//			ball.move(20.0, 0.0);
//		if (Keyboard::isKeyPressed(Keyboard::Up))
//			ball.move(0.0, -20.0);
//		if (Keyboard::isKeyPressed(Keyboard::Down))
//			ball.move(0.0, 20.0);


		if (Mouse::isButtonPressed(Mouse::Left)) {
			Vector2i localPosition = Mouse::getPosition(window);
			ball.setPosition(localPosition.x, localPosition.y);
		}

		window.clear();

		window.draw(background);
		window.draw(ball);
		window.draw(paddle);

		for (auto& obj : blocks)
			window.draw(obj);

		window.display();
	}

	return 0;
}
*/