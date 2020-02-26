#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;
Texture spritesheet;
Sprite invader;


std::vector<Ship*> ships;
Player* player;
bool gameOver;
Font font;
Text text;



void Load() {
    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }

    float X = 16;
    float Y = 16;

    float originX = 0;

    for (int j = 0; j < 5; j++)
    {        
      
        for (int i = 0; i < 12; i++)
        {
            Invader* inv = new Invader(sf::IntRect(originX, 0, 32, 32), { X,Y });
            X += 50;
            ships.push_back(inv);
        }

        Y += 50;
        originX += 32;
        X = 16;
    }

    Player* plyr = new Player();

    ships.push_back(plyr);

    Invader::speed = 20.f;
    
}

void Update(RenderWindow& window) {

    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();
    // check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    float direction = 0.0f;
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        direction--;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        direction++;
    }

    for (auto& s : ships) {
        s->Update(dt);
    };

    Bullet::Update(dt);

    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }
}


void Render(RenderWindow& window) {

    for (const auto s : ships) {
        window.draw(*s);
    }

    Bullet::Render(window);
}

int main() {
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