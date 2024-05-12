#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include <ctime> // For std::time
#include <cstdlib> // For std::srand and std::rand

#include "Header.h"

using namespace sf;
using namespace std;

class Zombie {
    protected:
        int damage;
        int health;
        int speed;
        sf::Sprite sprite; // Sprite for displaying the zombie
    public:

        virtual int getDamage() = 0;
        virtual  void setDamage(int dmg) = 0;
        virtual int getHealth() = 0;
        virtual  void setHealth(int hp) = 0;
        virtual int getSpeed() = 0;
        virtual void setSpeed(int spd) = 0;
        virtual Sprite& getSprite() = 0;
        virtual void attack() = 0; // Virtual function
        virtual void draw(sf::RenderWindow& window) = 0;
        virtual void update(float dt) = 0;
        virtual bool check() = 0;
        
};
    class NormalZombie :public Zombie{
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        sf::IntRect frameRect; // Rectangle for the current frame of animation
        int frameWidth; // Width of each frame in the sprite sheet
        int frameHeight; // Height of each frame in the sprite sheet
        int numFrames; // Total number of frames in the animation
        int currentFrame; // Index of the current frame being displayed
        float frameDuration; // Duration of each frame in seconds
        float frameTimer; // Timer to track the time since the last frame change
    public:
        sf::Sprite& getSprite() {
            return sprite;
        }
        int getDamage() {
            return damage;
        }
        void setDamage(int dmg) {
            health -= dmg;
            if (health <= 0) {
                health = 0;
            }
        }
        int getHealth() {
            return health;
        }
        void setHealth(int hp) {
            health = hp;
        }
        int getSpeed() {
            return speed;
        }

         void setSpeed(int spd) {
            speed = spd;
        }
        void attack() override {
            std::cout << "Normal zombie attacks!" << std::endl;
        }
        NormalZombie() {
            // Load sprite sheet texture
            if (!texture.loadFromFile("Images/normal_zombie.png")) {
                // Handle error if texture loading fails
            }

            // Initialize sprite
            sprite.setTexture(texture);

            // Set initial frame properties
            frameWidth = texture.getSize().x / 5; // Width of each frame in the sprite sheet
            frameHeight = texture.getSize().y / 10; // Height of each frame in the sprite sheet
            numFrames = 46; // Total number of frames in the animation
            currentFrame = 0; // Start from the first frame
            frameDuration = 0.1f; // Duration of each frame in seconds
            frameTimer = 0.0f; // Initialize frame timer
            // Set initial frame rectangle
            frameRect = sf::IntRect(0, 0, frameWidth, frameHeight);
            sprite.setTextureRect(frameRect);
            int startY = 0;
            int random = rand() % 6;
            
            switch (random) {
            case 0:
                startY = 95;
                break;
            case 1:
                startY = 280;
                break;
            case 2:
                startY = 450;
                break;
            case 3:
                startY = 620;
                break;
            case 4:
                startY = 800;
                break;
            case 5:
                startY = 800;
            default:
                break;
            }
            sprite.setPosition(1750, startY);
            sprite.setScale(1.5f, 1.5f); // Adjust the scale factor as needed
        }

        void draw(sf::RenderWindow& window) {
            window.draw(sprite);
        }
        bool check() {
            if (sprite.getPosition().x < 350) {
                return 1;
            }
            return 0;
        }
        void update(float dt) {
            // Update frame timer
            frameTimer += dt;

            // If it's time to change frames, move to the next frame
            if (frameTimer >= frameDuration) {
                frameTimer -= frameDuration; // Reset frame timer

                // Move to the next frame
                currentFrame = (currentFrame + 1) % numFrames;

                // Update frame rectangle
                int column = currentFrame % 5;
                int row = currentFrame / 5;
                frameRect.left = column * frameWidth;
                frameRect.top = row * frameHeight;
                sprite.setTextureRect(frameRect);

            }

            // Move the zombie to the left
            float movementSpeed = 10.0f; // Adjust the movement speed as needed
            float offsetX = movementSpeed * dt; // Calculate the offset based on the elapsed time
            sprite.move(-offsetX, 0); // Move the sprite to the left by subtracting from its x-coordinate

            if (sprite.getPosition().x < 350 ) {
                sprite.setPosition(-1000, -1000); // Move the zombie off-screen
            }
        }

    };

