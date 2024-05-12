#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;
using namespace std;


    class Sun {
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        sf::IntRect frameRect; 
        int frameWidth; 
        int frameHeight; 
        int numFrames;
        int currentFrame; 
        float frameDuration; 
        float frameTimer; 
        bool isVisible;
    public:
        Sun() {
            !texture.loadFromFile("Images/Sun.png");
            sprite.setTexture(texture);
    
            frameWidth = texture.getSize().x / 5;
            frameHeight = texture.getSize().y / 6; 
            numFrames = 30; 
            currentFrame = 0; 
            frameDuration = 0.1f; 
            frameTimer = 0.0f;
            frameRect = sf::IntRect(0, 0, frameWidth, frameHeight);
            sprite.setTextureRect(frameRect);

            int startX = rand() % (1750 - 450 + 1) + 450;

            sprite.setPosition(startX, 45);
            isVisible = 1;
        }

        void update(float dt, sf::RenderWindow& window) {
            frameTimer += dt;

            if (frameTimer >= frameDuration) {
                frameTimer -= frameDuration; 
                
                currentFrame = (currentFrame + 1) % numFrames;

                int column = currentFrame % 5;
                int row = currentFrame / 5;
                frameRect.left = column * frameWidth;
                frameRect.top = row * frameHeight;
                sprite.setTextureRect(frameRect);
            }

            float movementSpeed = 10.0f; 
            float offsetY = movementSpeed * dt; 
            sprite.move(0, offsetY); 

            if (sprite.getPosition().y >= window.getSize().y) {
                isVisible = false;
            }
        }

        void draw(sf::RenderWindow& window) {
            if (isVisible) {
                window.draw(sprite);
            }
        }
        bool checkSunCollision(int cursorX, int cursorY) const {
            return isVisible && sprite.getGlobalBounds().contains(cursorX, cursorY);
        }
        bool getIsVisible() const {
            return isVisible;
        }
        void toggle() {
            isVisible = !isVisible;
        }
        void respawn() {
            int startX = rand() % (1750 - 450 + 1) + 450;
            sprite.setPosition(startX, -sprite.getGlobalBounds().height);
            isVisible = true; 
        }
};
