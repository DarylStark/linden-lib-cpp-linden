#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main()
{
    // Game setup
    uint32_t pairCount = 10;
    game::MemoryGame memory(pairCount);
    memory.reset();
    const std::vector<uint32_t> &cards = memory.getCardIds();

    // Window setup
    sf::RenderWindow window(sf::VideoMode({900, 600}), "My window");
    window.setFramerateLimit(60);

    // Backside of the cards
    sf::Texture textureBackside;
    if (!textureBackside.loadFromFile(
            "../../../res/textures/flags/special_skull.png"))
    {
        return 1;
    }
    sf::Sprite spriteBackside(textureBackside);

    // Border for the backside hover
    sf::RectangleShape spriteBorder({128, 128});
    spriteBorder.setFillColor(sf::Color::Transparent);
    spriteBorder.setOutlineThickness(-1.f);
    spriteBorder.setOutlineColor({0, 255, 0});

    // Textures for the front sides
    std::vector<sf::Texture> frontsideTextures;
    frontsideTextures.resize(pairCount);
    frontsideTextures[0].loadFromFile("../../../res/textures/flags/NL.png");
    frontsideTextures[1].loadFromFile("../../../res/textures/flags/DE.png");
    frontsideTextures[2].loadFromFile("../../../res/textures/flags/AU.png");
    frontsideTextures[3].loadFromFile("../../../res/textures/flags/BE.png");
    frontsideTextures[4].loadFromFile("../../../res/textures/flags/FR.png");
    frontsideTextures[5].loadFromFile("../../../res/textures/flags/ES.png");
    frontsideTextures[6].loadFromFile("../../../res/textures/flags/IT.png");
    frontsideTextures[7].loadFromFile("../../../res/textures/flags/ZW.png");
    frontsideTextures[8].loadFromFile("../../../res/textures/flags/MG.png");
    frontsideTextures[9].loadFromFile("../../../res/textures/flags/DK.png");

    // Sprites for the front sides
    std::vector<sf::Sprite> frontsideSprites;
    frontsideSprites.reserve(frontsideTextures.size());
    for (const auto &texture : frontsideTextures)
    {
        frontsideSprites.emplace_back(texture);
    }

    // Text for the score
    sf::Font fontScore("../../../res/fonts/bitcount.ttf");
    sf::Text textScore(fontScore, std::to_string(memory.getScore()), 30);
    textScore.setPosition({562 + 128 + 10, 10});

    // Text for result
    sf::Text textResult(fontScore, "", 30);
    textResult.setPosition({562 + 128 + 10, 50});

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Vector2i lastClick(0, 0);

        // Event handeling
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto *mouseClick =
                         event->getIf<sf::Event::MouseButtonReleased>())
            {
                lastClick = mouseClick->position;
            }
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Get mouse position
        const auto mousePos =
            static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        // Display the cards
        uint16_t idx = 0;
        for (const auto &card : cards)
        {
            if (card == 0)
            {
                idx++;
                continue;
            }

            float tileX = idx % 5;
            float tileY = idx / 5;

            float winX = 10 + (tileX * 128) + (tileX * 10);
            float winY = 10 + (tileY * 128) + (tileY * 10);

            sf::Vector2f pos(winX, winY);

            if (lastClick.x >= pos.x && lastClick.x <= pos.x + 128 &&
                lastClick.y >= pos.y && lastClick.y <= pos.y + 128)
            {
                if (memory.turnAvailable())
                {
                    memory.makeTurn();
                }

                memory.selectCard(idx);
                if (memory.turnAvailable())
                {
                    clock.restart();
                }
            }

            if (!memory.isSelected(idx))
            {
                spriteBackside.setPosition(pos);
                window.draw(spriteBackside);
                if (spriteBackside.getGlobalBounds().contains(
                        {mousePos.x, mousePos.y}))
                {
                    spriteBorder.setPosition(pos);
                    window.draw(spriteBorder);
                }
            }
            else
            {
                frontsideSprites[card - 1].setPosition(pos);
                window.draw(frontsideSprites[card - 1]);
            }

            ++idx;
        }

        // Display the score
        textScore.setString(std::to_string(memory.getScore()));
        window.draw(textScore);

        if (memory.turnAvailable())
        {
            if (memory.checkTurn())
            {
                textResult.setString("GOOD!");
                textResult.setFillColor(sf::Color::Green);
            }
            else
            {
                textResult.setString("WRONG!");
                textResult.setFillColor(sf::Color::Red);
            }

            if (clock.getElapsedTime().asMilliseconds() >= 750)
            {
                memory.makeTurn();
            }
        }

        window.draw(textResult);

        // End the current frame
        window.display();
    }

    return 0;
}