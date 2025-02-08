#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);



	//Font file
	sf::Font font;
	if (font.loadFromFile("Data/font.otf") == false) {
		//Code when failing
	}

	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(30);
	score.setFillColor(sf::Color::Red);
	score.setPosition(350, 10);
	score.setString("0 : 0");

	//Images
	sf::Texture tex_pad;
	sf::Texture tex_ball;
	sf::Texture tex_background;

	if (tex_pad.loadFromFile("Data/pad.png") == false) {
		return -1;
	}

	if (tex_ball.loadFromFile("Data/ball.png") == false) {
		return -1;
	}

	if (tex_background.loadFromFile("Data/background.png") == false) {
		return -1;
	}

	//Sounds
	sf::SoundBuffer buff_hit;

	sf::Sound hit;
	hit.setBuffer(buff_hit);

	if (buff_hit.loadFromFile("Data/hit.wav") == false) {
		return -1;
	}

	//States
	bool up = false, down = false;

	//Variables
	int yVelocityPad1 = 0;
	int xVelocityBall = -4, yVelocityBall = -4;
	int yVelocityPad2 = 0;
	int pad1Score = 0, pad2Score = 0;

	/////////Shapes
	//Background
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(800, 600));
	background.setPosition(0, 0);
	background.setTexture(&tex_background);

	//pad1
	sf::RectangleShape pad2;
	pad2.setSize(sf::Vector2f(50, 100));
	pad2.setPosition(700, 200);
	pad2.setTexture(&tex_pad);

	//pad2
	sf::RectangleShape pad1;
	pad1.setSize(sf::Vector2f(50, 100));
	pad1.setPosition(50, 200);
	pad1.setTexture(&tex_pad);

	//Ball
	sf::RectangleShape ball;
	ball.setSize(sf::Vector2f(50, 50));
	ball.setPosition(400, 200);
	ball.setTexture(&tex_ball);

	//Game loop
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			//Process events
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
				up = true;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
				down = true;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) {
				up = false;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down) {
				down = false;
			}

		}

		//Logic handling
		////Pad1
		if (up) {
			yVelocityPad1 = -5;
		}

		if (down) {
			yVelocityPad1 = 5;
		}

		if ((up && down) || (!up && !down)) {
			yVelocityPad1 = 0;
		}

		pad1.move(0, yVelocityPad1);

		//Out of bounds check
		if (pad1.getPosition().y < 0) {
			pad1.setPosition(50, 0);
		}

		if (pad1.getPosition().y > 500) {
			pad1.setPosition(50, 500);
		}

		////Pad2
		if (ball.getPosition().y < pad2.getPosition().y) {
			yVelocityPad2 = -3;
		}

		if (ball.getPosition().y > pad2.getPosition().y) {
			yVelocityPad2 = 3;
		}

		pad2.move(0, yVelocityPad2);

		////Ball
		ball.move(xVelocityBall, yVelocityBall);

		//Out of bounds check
		if (ball.getPosition().y < 0) {
			yVelocityBall = -yVelocityBall;
		}

		if (ball.getPosition().y > 550) {
			yVelocityBall = -yVelocityBall;
		}

		if (ball.getPosition().x < -50) {
			pad2Score++;
			ball.setPosition(300, 200);
		}

		if (ball.getPosition().x > 800) {
			pad1Score++;
			ball.setPosition(300, 200);
		}

		//Collision
		if (ball.getGlobalBounds().intersects(pad1.getGlobalBounds())) {
			xVelocityBall = -xVelocityBall;
			hit.play();
		}

		if (ball.getGlobalBounds().intersects(pad2.getGlobalBounds())) {
			xVelocityBall = -xVelocityBall;
			hit.play();
		}


		//Rendering part of the main game loop
		window.clear();

		window.draw(background);
		window.draw(pad1);
		window.draw(pad2);
		window.draw(ball);

		//Score
		std::stringstream text;
		text << pad1Score << " : " << pad2Score;
		score.setString(text.str());
		window.draw(score);

		window.display();


	}

	return 0;
}