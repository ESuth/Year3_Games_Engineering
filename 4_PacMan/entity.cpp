//entity.cpp
#include "entity.h"
using namespace std;
using namespace sf;

const Vector2f Entity::getPosition() 
{ 
    return _position;
}

void Entity::setPosition(const Vector2f &pos) 
{ 
    _position = pos;
}

void Entity::move(const Vector2f &pos) 
{ 
    _position += pos;
}

void Entity::Update(const double dt) 
{
    _shape->setPosition(_position);
}

Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) 
{
}

Ghost::Ghost() : _speed(200.0f), Entity(std::make_unique<sf::CircleShape>(25.0f))
{
	_shape->setFillColor(Color::Red);
	_shape->setOrigin(sf::Vector2f(25.0f, 25.0f));	
	_shape->setPosition(_position);
	
}

void Ghost::Update(double dt)
{
	_shape->setPosition(_position);
	move
	Entity::Update(dt);
}

void Ghost::Render(sf::RenderWindow& window) const
{
	window.draw(*_shape);
}