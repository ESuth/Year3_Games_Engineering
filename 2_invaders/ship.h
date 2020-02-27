//Ship.h
#pragma once
#include <SFML/Graphics.hpp>


class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	//Default constructor is hidden
	Ship();
	bool _exploded;
	float _fadeTimer;
public:
	static const float initialFadeTimer;
	static bool direction;
	static float speed;
	//Constructor that takes a sprite
	explicit Ship(sf::IntRect ir);
	//Pure virtual deconstructor -- makes this an abstract class and avoids undefined behaviour!
	virtual ~Ship() = 0;
	//Update, virtual so can be overridden, but not pure virtual
	virtual void Update(const float& dt);
	bool isExploded() const;
	virtual void explode();
	virtual bool isPlayer() const;
	virtual bool isInvader() const;
};

class Invader : public Ship {
public:
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void Update(const float& dt) override;
	void explode() override;
	bool isPlayer() const override;
	bool isInvader() const override;
};

class Player : public Ship {
public:
	Player();
	void Update(const float& dt) override;
	void explode() override;
	bool isPlayer() const override;
	bool isInvader() const override;
};