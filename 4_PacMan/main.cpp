#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "levelsystem.h"

using namespace sf;
using namespace std;

Entity* player;

Ghost* ghost;

uint16_t gameWidth = 800;
uint16_t gameHeight = 500;

void Reset()
{
    player = new Player();
    ghost = new Ghost();
}

void Load() 
{
    player = new Player();
    ghost = new Ghost();
}

void Update(RenderWindow& window) 
{
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

    player->Update(dt);
    ghost->Update(dt);

    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }
}


void Render(RenderWindow& window) 
{
    player->Render(window);
    ghost->Render(window);
}

int main() 
{
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PacMan");

    Load();

    while (window.isOpen()) 
    {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }

    return 0;
}