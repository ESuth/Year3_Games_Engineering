//ship.cpp
#include "Ship.h"
#include "game.h"
#include "bullet.h"
using namespace sf;
using namespace std;

bool Invader::direction;
float Invader::speed = 0.5f;
const float Ship::initialFadeTimer = .5f;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_exploded = false;
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
	_fadeTimer = initialFadeTimer;
};


void Ship::Update(const float& dt)
{
	//if destroyed fade ship
	if (_exploded) {
		_fadeTimer -= dt;
		if (_fadeTimer >= 0)
			setColor({ 255, 255, 255, Uint8(_fadeTimer * 255 / initialFadeTimer) });
	}


}

bool Ship::isExploded() const {
	return _exploded;
}

void Ship::explode() {
	_exploded = true;
}

bool Ship::isPlayer() const {
	return false;
}

bool Ship::isInvader() const {
	return false;
}


//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;

Invader::Invader() : Ship() {};

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
};

void Invader::Update(const float& dt) {
	Ship::Update(dt);

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	if (!_exploded) {
		if ((direction && getPosition().x > gameWidth - 16) ||
			(!direction && getPosition().x < 16)) {
			direction = !direction;
			for (int i = 0; i < ships.size() - 1; ++i) {
				ships[i]->move(0, 24);
			}
		}
	}

	static float firetime = 0.0f;
	firetime -= dt;

		if (firetime <= 0 && rand() % 100 == 0) {
			Bullet::Fire(getPosition(), true);
			firetime = 4.0f + (rand() % 60);
		}
}

void Invader::explode() {
	Ship::explode();

	// set exploded texture
	setTextureRect(IntRect(32 * 4, 32, 32, 32));

}

bool Invader::isPlayer() const {
	return true;
}

bool Invader::isInvader() const {
	return false;
}

const Keyboard::Key controls[3] = {
	Keyboard::Left,   // Player1 Left
	Keyboard::Right,   // Player1 Right
	Keyboard::Space,	//Player1 Fire
};

Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameHeight * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt) {

	Ship::Update(dt);

	//Move left
	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0]))
	{
		direction--;
	}
	//Move Right
	if (Keyboard::isKeyPressed(controls[1]))
	{
		direction++;
	}

	static float fireCooldown = 0.f;
	fireCooldown -= dt;
	if (fireCooldown <= 0 && Keyboard::isKeyPressed(controls[2])) {
		Bullet::Fire(getPosition(), false);
		fireCooldown = .7f;
	}

	move(direction * 100 * dt, 0);
}

void Player::explode() {
	Ship::explode();

	// set exploded texture
	setTextureRect(IntRect(32 * 4, 32, 32, 32));

}

bool Player::isPlayer() const {
	return true;
}

bool Player::isInvader() const {
	return false;
}