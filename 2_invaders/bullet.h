//bullet.h
#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
public:
	static float speed;



	Bullet(const sf::Vector2f& pos, const bool mode);
	//updates All bullets
	static void Update(const float& dt);
	//Render's All bullets
	static void Render(sf::RenderWindow& window);
	//Chose an inactive bullet and use it.
	static void Fire(const sf::Vector2f& pos, const bool mode);

	static void Init();
	~Bullet() = default;


protected:
	//Never called by our code
	Bullet();
	//static unsigned char bulletPointer;
	static Bullet bullets[256];
	//Called by the static Update()
	void _Update(const float& dt);

	//false=player bullet, true=Enemy bullet
	bool _mode;
};