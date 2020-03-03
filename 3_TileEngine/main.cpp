#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "game.h"
#include "levelsystem.h"

using namespace sf;
using namespace std;

Entity* player;


bool validmove(Vector2f pos) {
    return (ls::getTileAt(pos) != ls::WALL);
}

bool endGame(Vector2f pos) {
    return (ls::getTileAt(pos) == ls::END);
}

void Reset()
{
    player = new Player();

    ls::loadLevelFile("res/maze_2.txt");

    // Print the level to the console
    for (size_t y = 0; y < ls::getHeight(); ++y) {
        for (size_t x = 0; x < ls::getWidth(); ++x) {
            cout << ls::getTile({ x, y });
            if (ls::getTile({ x, y }) == ls::START) {
                player->setPosition(ls::getTilePosition({ x, y }) + Vector2f(30.0f, 30.0f));
            }
        }
        cout << endl;
    }

}

void Load() 
{
    player = new Player();

    ls::loadLevelFile("res/maze_2.txt");

    // Print the level to the console
    for (size_t y = 0; y < ls::getHeight(); ++y) {
        for (size_t x = 0; x < ls::getWidth(); ++x) {
            cout << ls::getTile({ x, y });
            if (ls::getTile({ x, y }) == ls::START) {
                player->setPosition(ls::getTilePosition({ x, y }) + Vector2f(30.0f, 30.0f));
            }
        }
        cout << endl;
    }

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

    sf::Vector2f previous = player->getPosition();

    player->Update(dt);

    if (!validmove(player->getPosition()))
        player->setPosition(previous);

    if (endGame(player->getPosition()))
        Reset();

    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }
}


void Render(RenderWindow& window) 
{
    player->Render(window);
    ls::Render(window);
}

int main() 
{
    RenderWindow window(VideoMode(gameWidth, gameHeight), "Tile Engine");

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