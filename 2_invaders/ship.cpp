//ship.cpp
#include "ship.h"
#include "game.h"
#include "bullet.h"
using namespace sf;
using namespace std;

bool Invader::direction;
float Invader::speed;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
    _sprite = ir;
    setTexture(spritesheet);
    setTextureRect(_sprite);
};

void Ship::Update(const float& dt) {}

void Ship::Explode() {
    setTextureRect(IntRect(128, 32, 32, 32));
    setOrigin(16, 16);
    _exploded = true;
    if (this == player) {
        gameOver = true;
    }
}

bool Ship::isExploded() const {
    return _exploded;
}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;


Invader::Invader() : Ship() {}

Invader::Invader(IntRect ir, Vector2f pos) : Ship(ir) {
    setOrigin(16, 16);
    setPosition(pos);
}

void Invader::Update(const float& dt) {
    Ship::Update(dt);

    move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

    if ((direction && getPosition().x > gameWidth - 16) ||
        (!direction && getPosition().x < 16)) {
        direction = !direction;
        for (int i = 0; i < ships.size() -1; ++i) {
            ships[i]->move(0, 24);
        }
    }

    //invader shooting
    static float firetime = 0.0f;
    firetime -= dt;

    if (firetime <= 0 && rand() % 100 == 0) {
        Bullet::Fire(getPosition(), true);
        firetime = 4.0f + (rand() % 60);
    }

    static float explosiontime = 1.0f;

    //remove exploded ships from the screen	
    for (auto& s : ships) {
        if (s->isExploded()) {
            explosiontime -= dt;
        }
        if (explosiontime <= 0.0f) {
            s->setPosition(-100, -100);
            explosiontime = 1.0f;
        }
    }
}

Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
    setPosition({ gameWidth/2-32, gameHeight - 32.f });
}

void Player::Update(const float& dt) {
    Ship::Update(dt);

    float speed = 90.0f;

    float direction = 0.0f;
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        direction--;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        direction++;
    }

    if (getPosition().x > gameWidth -32)
    {
        setPosition({ gameWidth - 32, gameHeight - 32.f });
    }

    if (getPosition().x < 0)
    {
        setPosition({ 0, gameHeight - 32.f });
    }

    move(dt * direction * speed, 0);

    static float firetime = 0.0f;
    firetime -= dt;

    if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::Space)) {
        Bullet::Fire(getPosition(), false);
        firetime = 0.7f;
    }
}