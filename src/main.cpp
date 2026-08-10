#include "game.hpp"
#include "transition.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
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
    sf::RenderWindow window(sf::VideoMode({900, 1650}), "My window",
                            sf::Style::None | sf::Style::Titlebar,
                            sf::State::Windowed);
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

    // Set up for transitioning
    float radius = 50;
    float y = 10;
    uint64_t duration = 2'500'000;

    // Linear
    sf::CircleShape circleTransLinear(radius);
    circleTransLinear.setFillColor(sf::Color({128, 0, 0}));
    circleTransLinear.setPosition({1, y});
    graphics::Transition transitionTransLinear(
        std::make_unique<math::easing::Linear>(), duration,
        [&circleTransLinear, radius, y](float n)
        {
            float x = std::lerp(0, 900 - (radius * 2), n);
            circleTransLinear.setPosition({x, y});
        });

    // EaseInOutQuad
    y += 110;
    sf::CircleShape circleTransEaseInOut(radius);
    circleTransEaseInOut.setFillColor(sf::Color({0, 128, 0}));
    circleTransEaseInOut.setPosition({1, y});
    graphics::Transition transitionTransEaseInOut(
        std::make_unique<math::easing::InOutQuad>(), duration,
        [&circleTransEaseInOut, radius, y](float n)
        {
            float x = std::lerp(0, 900 - (radius * 2), n);
            circleTransEaseInOut.setPosition({x, y});
        });

    // Smoothstep
    y += 110;
    sf::CircleShape circleTransSmoothStep(radius);
    circleTransSmoothStep.setFillColor(sf::Color({0, 0, 255}));
    circleTransSmoothStep.setPosition({1, y});
    graphics::Transition transitionTransSmoothStep(
        std::make_unique<math::easing::InOutSmoothStep>(), duration,
        [&circleTransSmoothStep, radius, y](float n)
        {
            float x = std::lerp(0, 900 - (radius * 2), n);
            circleTransSmoothStep.setPosition({x, y});
        });

    // Smootherstep
    y += 110;
    sf::CircleShape circleTransSmootherStep(radius);
    circleTransSmootherStep.setFillColor(sf::Color({128, 128, 0}));
    circleTransSmootherStep.setPosition({1, y});
    graphics::Transition transitionTransSmootherStep(
        std::make_unique<math::easing::InOutSmootherStep>(), duration,
        [&circleTransSmootherStep, radius, y](float n)
        {
            float x = std::lerp(0, 900 - (radius * 2), n);
            circleTransSmootherStep.setPosition({x, y});
        });

    // Sine
    y += 110;
    sf::CircleShape circleTransSine(radius);
    circleTransSine.setFillColor(sf::Color({0, 128, 255}));
    circleTransSine.setPosition({1, y});
    graphics::Transition transitionTransSine(
        std::make_unique<math::easing::InOutSine>(), duration,
        [&circleTransSine, radius, y](float n)
        {
            float x = std::lerp(0, 900 - (radius * 2), n);
            circleTransSine.setPosition({x, y});
        });

    // Back
    y += 110;
    sf::CircleShape circleTransBack(radius);
    circleTransBack.setFillColor(sf::Color({128, 0, 255}));
    circleTransBack.setPosition({1, y});
    graphics::Transition transitionTransBack(
        std::make_unique<math::easing::InOutBack>(), duration,
        [&circleTransBack, radius, y](float n)
        {
            float x = std::lerp(0, 900 - (radius * 2), n);
            circleTransBack.setPosition({x, y});
        });

    // Cubic
    y += 110;
    sf::CircleShape circleTransCubic(radius);
    circleTransCubic.setFillColor(sf::Color({128, 128, 255}));
    circleTransCubic.setPosition({1, y});
    graphics::Transition transitionTransCubic(
        std::make_unique<math::easing::InOutCubic>(), duration,
        [&circleTransCubic, radius, y](float n)
        {
            float x = std::lerp(0, 900 - (radius * 2), n);
            circleTransCubic.setPosition({x, y});
        });

    // Elastic
    y += 110;
    sf::CircleShape circleTransElastic(radius);
    circleTransElastic.setFillColor(sf::Color({128, 128, 0}));
    circleTransElastic.setPosition({1, y});
    graphics::Transition transitionTransElastic(
        std::make_unique<math::easing::InOutElastic>(), duration,
        [&circleTransElastic, radius, y](float n)
        {
            float x = std::lerp(0, 900 - (radius * 2), n);
            circleTransElastic.setPosition({x, y});
        });

    // Bounce
    y += 110;
    sf::CircleShape circleTransBounce(radius);
    circleTransBounce.setFillColor(sf::Color({128, 0, 0}));
    circleTransBounce.setPosition({1, y});
    graphics::Transition transitionTransBounce(
        std::make_unique<math::easing::InOutBounce>(), duration,
        [&circleTransBounce, radius, y](float n)
        {
            float x = std::lerp(0, 900 - (radius * 2), n);
            circleTransBounce.setPosition({x, y});
        });

    // Quart
    y += 110;
    sf::CircleShape circleTransQuart(radius);
    circleTransQuart.setFillColor(sf::Color({128, 0, 0}));
    circleTransQuart.setPosition({1, y});
    graphics::Transition transitionTransQuart(
        std::make_unique<math::easing::InOutQuart>(), duration,
        [&circleTransQuart, radius, y](float n)
        {
            float x = std::lerp(0, 900 - (radius * 2), n);
            circleTransQuart.setPosition({x, y});
        });

    // Quint
    y += 110;
    sf::CircleShape circleTransQuint(radius);
    circleTransQuint.setFillColor(sf::Color({128, 0, 0}));
    circleTransQuint.setPosition({1, y});
    graphics::Transition transitionTransQuint(
        std::make_unique<math::easing::InOutQuint>(), duration,
        [&circleTransQuint, radius, y](float n)
        {
            float x = std::lerp(0, 900 - (radius * 2), n);
            circleTransQuint.setPosition({x, y});
        });

    // Expo
    y += 110;
    sf::CircleShape circleTransExpo(radius);
    circleTransExpo.setFillColor(sf::Color({128, 0, 0}));
    circleTransExpo.setPosition({1, y});
    graphics::Transition transitionTransExpo(
        std::make_unique<math::easing::InOutExpo>(), duration,
        [&circleTransExpo, radius, y](float n)
        {
            float x = std::lerp(0, 900 - (radius * 2), n);
            circleTransExpo.setPosition({x, y});
        });

    // Circ
    y += 110;
    sf::CircleShape circleTransCirc(radius);
    circleTransCirc.setFillColor(sf::Color({128, 0, 0}));
    circleTransCirc.setPosition({1, y});
    graphics::Transition transitionTransCirc(
        std::make_unique<math::easing::InOutCirc>(), duration,
        [&circleTransCirc, radius, y](float n)
        {
            float x = std::lerp(0, 900 - (radius * 2), n);
            circleTransCirc.setPosition({x, y});
        });

    // Sextic
    y += 110;
    sf::CircleShape circleTransSextic(radius);
    circleTransSextic.setFillColor(sf::Color({128, 0, 0}));
    circleTransSextic.setPosition({1, y});
    graphics::Transition transitionTransSextic(
        std::make_unique<math::easing::InOutSextic>(), duration,
        [&circleTransSextic, radius, y](float n)
        {
            float x = std::lerp(0, 900 - (radius * 2), n);
            circleTransSextic.setPosition({x, y});
        });

    // Poly
    y += 110;
    sf::CircleShape circleTransPoly(radius);
    circleTransPoly.setFillColor(sf::Color({128, 0, 0}));
    circleTransPoly.setPosition({1, y});
    graphics::Transition transitionTransPoly(
        std::make_unique<math::easing::InOutPoly>(32.0f), duration,
        [&circleTransPoly, radius, y](float n)
        {
            float x = std::lerp(0, 900 - (radius * 2), n);
            circleTransPoly.setPosition({x, y});
        });

    sf::Clock clock;
    sf::Clock transitionClock;

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

        // Transition practicing
        auto elapsedTime = transitionClock.getElapsedTime().asMicroseconds();

        transitionTransLinear.tick(elapsedTime);
        window.draw(circleTransLinear);

        transitionTransEaseInOut.tick(elapsedTime);
        window.draw(circleTransEaseInOut);

        transitionTransSmoothStep.tick(elapsedTime);
        window.draw(circleTransSmoothStep);

        transitionTransSmootherStep.tick(elapsedTime);
        window.draw(circleTransSmootherStep);

        transitionTransSine.tick(elapsedTime);
        window.draw(circleTransSine);

        transitionTransBack.tick(elapsedTime);
        window.draw(circleTransBack);

        transitionTransCubic.tick(elapsedTime);
        window.draw(circleTransCubic);

        transitionTransElastic.tick(elapsedTime);
        window.draw(circleTransElastic);

        transitionTransBounce.tick(elapsedTime);
        window.draw(circleTransBounce);

        transitionTransQuart.tick(elapsedTime);
        window.draw(circleTransQuart);

        transitionTransQuint.tick(elapsedTime);
        window.draw(circleTransQuint);

        transitionTransExpo.tick(elapsedTime);
        window.draw(circleTransExpo);

        transitionTransCirc.tick(elapsedTime);
        window.draw(circleTransCirc);

        transitionTransSextic.tick(elapsedTime);
        window.draw(circleTransSextic);

        transitionTransPoly.tick(elapsedTime);
        window.draw(circleTransPoly);

        // End the current frame
        window.display();
    }

    return 0;
}