#include "bullet.h"
#include "game.h"
using namespace sf;
using namespace std;

//unsigned char bulletPointer;
Bullet Bullet::bullets[256];

float Bullet::speed;
//Create definition for the constructor
//...
Bullet::Bullet() {};

Bullet::Bullet(const sf::Vector2f& pos, const bool mode) {
	setPosition(pos);
	_mode = mode;
	setTexture(spritesheet);

	if (_mode)
	{
		setTextureRect(IntRect(32, 32, 32, 32));
	}
	else
	{
		setTextureRect(IntRect(64, 32, 32, 32));
		
	}

	
}

void Bullet::Init()
{
	for (int i = 0; i < 256; i++)
	{
		bullets[i].setPosition(-999.0f, -999.0f);
	}
}

void Bullet::Update(const float& dt) {
	for (auto& b : bullets) {
		b.move({ 0, 200.0f * dt * (b._mode ? 1.0f : -1.0f) });
		b._Update(dt);
	};
}

void Bullet::Render(sf::RenderWindow& window) {
	for (const auto& b : bullets) {
		window.draw(b);
	};
}

void Bullet::_Update(const float& dt) {
	move(0, dt * speed * (_mode ? 1.0f : -1.0f));
	const sf::FloatRect bulletBounds = getGlobalBounds();

	for (auto ship : ships) {
		// invader bullet on invader collision
		// player bullet on player collision
		if (!_mode && ship->isPlayer())
			continue;
		if (_mode && ship->isPlayer())
			//invader bullets don't collide with other invaders
			continue;
		if (!ship->isExploded() && ship->getGlobalBounds().intersects(bulletBounds)) {
			ship->explode();
			setPosition(-100, -100);
			return;
		}
	}
}

void Bullet::Fire(const sf::Vector2f& pos, const bool mode)
{
	bullets[bulletPointer++] = Bullet(pos, mode);
}