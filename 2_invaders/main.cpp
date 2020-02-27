#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ship.h"
#include "bullet.h"

using namespace sf;
using namespace std;

std::vector<Ship*> ships;
Ship* player;

sf::Texture spritesheet;
sf::Sprite invader;

const int gameWidth = 800;
const int gameHeight = 600;

const int invaders_rows = 4;
const int invaders_columns = 13;

float positionX = 32.0;
float positionY = 32.0;

void Load()
{
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png"))
	{
		cerr << "Failed to load spritesheet" << std::endl;
	}


	for (int r = 0; r < invaders_rows; ++r) {
		auto rect = IntRect((r % 3) * 64, 0, 32, 32);
		positionX = 100;
		for (int c = 0; c < invaders_columns; ++c)
		{
			Vector2f position = { positionX,positionY };
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
			positionX = positionX + 50.0;
		}
		positionY = positionY + 50.0;
	}

	Bullet::Init();

	auto player = new Player;
	ships.push_back(player);

	Player::speed = 50.f;
	Bullet::speed = 80.f;
}

void Update(RenderWindow& window)
{
	static Clock clock;
	float dt = clock.restart().asSeconds();
	for (auto& s : ships) {
		s->Update(dt);
	};

	Bullet::Update(dt);

	// Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

}

void Render(RenderWindow& window)
{
	for (const auto s : ships) {
		window.draw(*s);
	}

	Bullet::Render(window);

}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}