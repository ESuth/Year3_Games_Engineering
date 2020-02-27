#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "game.h"

using namespace sf;
using namespace std;

Player* player;

void Load() {

    player = new Player();

    
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

    player->Update(dt);

    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }

}


void Render(RenderWindow& window) {

    player->Render(window);

}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "Tile Engine");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}