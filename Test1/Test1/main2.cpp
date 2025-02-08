#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main2() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	std::cout << "Game started" << std::endl;

	sf::Texture box_texture;
	if (box_texture.loadFromFile("Data/box.png") == false) {
		std::cout << "Loading failed" << std::endl;
	}

	box_texture.setSmooth(true);

	//Font file
	sf::Font font;
	if (font.loadFromFile("Data/font.otf") == false) {
		//Code when failing
	}


	sf::RectangleShape rectangle(sf::Vector2f(500, 500));

	rectangle.setOrigin(50, 25);
	rectangle.setPosition(400, 300);
	//rectangle.setFillColor(sf::Color(0, 255, 0));
	rectangle.setTexture(&box_texture);

	sf::CircleShape circle(200, 3);

	circle.setRadius(50);

	circle.setOutlineThickness(10);
	circle.setOutlineColor(sf::Color(0, 0, 255));
	//circle.setTexture(&box_texture);

	sf::Sprite box;
	box.setTexture(box_texture);
	box.setScale(2.0f, 2.0f);

	//Text object
	sf::Text text;
	text.setFont(font);
	text.setString("Hello, how are you?");
	text.setCharacterSize(50);
	text.setFillColor(sf::Color(255, 0, 0));
	text.setStyle(sf::Text::Italic);

	text.setPosition(250, 0);

	//Sound
	sf::SoundBuffer ball_buffer;
	if (ball_buffer.loadFromFile("Data/ball.wav") == false) {
		//Code here
	}

	sf::Sound ball_sound;
	ball_sound.setBuffer(ball_buffer);

	ball_sound.play();
	ball_sound.setVolume(30);
	ball_sound.setPitch(1.5f);
	//ball_sound.setLoop(true);

	sf::Music music;
	if (music.openFromFile("Data/music.wav") == false) {
		//Do something here
		return 1;
	}

	music.play();
	music.setPitch(0.5f);
	music.setVolume(50);
	music.setPlayingOffset(sf::seconds(5)); // start 5 seconds into the song

	//bool up_key = false;

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			//Process events
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			//if (event.type == sf::Event::KeyPressed) {
			//	if (event.key.code == sf::Keyboard::Up) {
			//		/*std::cout << "Up was pressed" << std::endl;
			//		std::cout << event.key.control << std::endl;*/
			//		up_key = true;
			//	}
			//}

			//if (event.type == sf::Event::KeyReleased) {
			//	if (event.key.code == sf::Keyboard::Up) {
			//		/*std::cout << "Up was released" << std::endl;
			//		std::cout << event.key.control << std::endl;*/
			//		up_key = false;
			//	}
			//}

			//if (event.type == sf::Event::MouseButtonPressed) {
			//	if (event.mouseButton.button == sf::Mouse::Left) {
			//		std::cout << "Left mouse button was pressed" << std::endl;
			//		std::cout << event.mouseButton.x << std::endl;
			//		std::cout << event.mouseButton.y << std::endl;
			//	}
			//}

			/*if (event.type == sf::Event::MouseMoved) {
				std::cout << event.mouseMove.x << std::endl;
				std::cout << event.mouseMove.y << std::endl;
			}*/
		}

		//Logic handling

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			std::cout << "Up is currently held down" << std::endl;
		}*/
		/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			std::cout << "Left button is currently held down" << std::endl;
		}*/
		//std::cout << sf::Mouse::getPosition().x << std::endl;
		
		rectangle.move(0.2f, 0);
		rectangle.rotate(1.0f);

		circle.move(0.5f, 0.5f);
		circle.rotate(1.0f);

		text.move(0, 1);

		//Rendering part of the main game loop
		window.clear(/*sf::Color(255, 0, 0)*/);

		//Draw things
		window.draw(rectangle);
		window.draw(circle);
		window.draw(box);
		window.draw(text);

		window.display();


	}

	return 0;
}