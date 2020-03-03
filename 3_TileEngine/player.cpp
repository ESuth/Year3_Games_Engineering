//player.cpp
#include "player.h"
using namespace sf;
using namespace std;

void Player::Update(double dt) {

  //Move in four directions based on keys
	int xdir = 0, ydir = 0;

	if (Keyboard::isKeyPressed(Keyboard::Up)) 
	{
			move(Vector2f(0, -_speed * dt));
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) 
	{
			move(Vector2f(0, _speed * dt));
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) 
	{
			move(Vector2f(-_speed * dt, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) 
	{
			move(Vector2f(_speed * dt, 0));
	}
  
  Entity::Update(dt);
}

Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) 
{
  _shape->setFillColor(Color::Magenta);
  _shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow &window) const 
{
  window.draw(*_shape);
}