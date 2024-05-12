#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


class Plant {
protected:
    int health;
    int price;
    int locationX;
    int locationY;
    
    static int numberOfPlants;

public:
    Plant(int h, int p, int x, int y)
        : health(h), price(p), locationX(x), locationY(y) {
        numberOfPlants++;
    }

   virtual void draw(sf::RenderWindow& window)  = 0;
   virtual void update() = 0;
  
    int getHealth() const { return health; }
    void setHealth(int h) { health = h; }

    int getPrice() const { return price; }
    void setPrice(int p) { price = p; }

    int getLocationX() const { return locationX; }
    void setLocationX(int x) { locationX = x; }

    int getLocationY() const { return locationY; }
    void setLocationY(int y) { locationY = y; }

    static int getNumberOfPlants() { return numberOfPlants; }
};

int Plant::numberOfPlants = 0;

class PeaShooter : public Plant {
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Texture peaTexture;
    sf::Sprite peaSprite;

    bool isVisible;
    int x;
    int y;
public:
    PeaShooter(int health, int price, int x, int y, RenderWindow& window) : Plant(health, price, x, y), isVisible(true) {
        texture.loadFromFile("Images/PeeCursor.png");
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
        this->x = x;
        this->y = y;
        sprite.setScale(1.5, 1.5);
        peaTexture.loadFromFile("Images/PeaBullet.png");
        peaSprite.setTexture(peaTexture);
        peaSprite.setPosition(x, y);
        peaSprite.setScale(1.25, 1.25);
    }
    void draw(RenderWindow& window)  override {
        window.draw(sprite);
        if (isVisible) {
            window.draw(peaSprite);
        }
    }
    void update() {
        if (isVisible) {
            peaSprite.move(8, 0);
            if (peaSprite.getPosition().x > 1910) {
                isVisible = false; // If the bullet goes off-screen, make it invisible
            }
        }
        if (!isVisible) {
            peaSprite.setPosition(x, y);
            isVisible = 1;
        }
    }


};
class SnowPeaShooter : public Plant {
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Texture peaTexture;
    sf::Sprite peaSprite;

    bool isVisible;

public:
    SnowPeaShooter(int h, int price,int x, int y) : Plant(h,price,x, y) {
        texture.loadFromFile("Images/SnowPeaCursor.png");

        sprite.setTexture(texture);
        sprite.setScale(0.5, 0.5);
        sprite.setPosition(x, y);

        peaTexture.loadFromFile("Images/SnowPea.png");
        
        peaSprite.setTexture(peaTexture);
        peaSprite.setScale(1.25, 1.25);
        peaSprite.setPosition(x, y);
    }
    void draw(RenderWindow& window)  override {
        window.draw(sprite);
        if (isVisible) {
            window.draw(peaSprite);
        }
    }
    void update() override {
        if (isVisible) {
            peaSprite.move(8, 0);

            // Check if either pea sprite is out of the screen
            if (peaSprite.getPosition().x > 1910) {
                isVisible = false;
            }
        }
        else {
            // If not visible, reset the positions of both pea sprites
            peaSprite.setPosition(locationX, locationY);
            isVisible = true;
        }

    }
};

class Repeater : public Plant {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Texture peaTexture;
    sf::Sprite peaSprite1; // First pea sprite
    sf::Sprite peaSprite2; // Second pea sprite
    bool isVisible;

public:
    Repeater(int h, int price, int x, int y) : Plant(h, price, x, y), isVisible(false) {
        texture.loadFromFile("Images/RepeaterCursor.png");
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
        sprite.setScale(1.25, 1.25);

        peaTexture.loadFromFile("Images/Peabullet.png");

        // Initialize the positions of both pea sprites
        peaSprite1.setTexture(peaTexture);
        peaSprite1.setPosition(x, y);
        peaSprite2.setTexture(peaTexture);
        peaSprite2.setPosition(x-10, y ); // Adjust the position as needed
    }

    void draw(RenderWindow& window) override {
        window.draw(sprite);
        if (isVisible) {
            window.draw(peaSprite1);
            window.draw(peaSprite2);
        }
    }

    void update() override {
        if (isVisible) {
            // Move both pea sprites
            peaSprite1.move(8, 0);
            peaSprite2.move(8, 0);

            // Check if either pea sprite is out of the screen
            if (peaSprite1.getPosition().x > 1910 || peaSprite2.getPosition().x > 1910) {
                isVisible = false;
            }
        }
        else {
            // If not visible, reset the positions of both pea sprites
            peaSprite1.setPosition(locationX, locationY);
            peaSprite2.setPosition(locationX, locationY + 10); // Adjust the position as needed
            isVisible = true;
        }
       
    }

};



class WallNut : public Plant {
    sf::Texture texture; // Texture for the image
    sf::Sprite sprite;   // Sprite to display the image
public:
    WallNut(int x, int y) : Plant(100, 50, x, y) {
        if (!texture.loadFromFile("Images/WallnutCursor.png")) { // Replace "WallNut.png" with the path to your image
        }
        sprite.setTexture(texture);
        sprite.setScale(0.6, 0.6);
         sprite.setPosition(x, y);
    }
    
    void draw(RenderWindow& window)  override {
        window.draw(sprite);
    }
    virtual void update() {}

};

class CherryBomb : public Plant {
    sf::Texture texture; // Texture for the image
    sf::Sprite sprite;   // Sprite to display the image
public:
    CherryBomb(int x, int y) : Plant(100, 200, x, y) {
        if (!texture.loadFromFile("Images/CherryBombCursor.png")) {
            std::cerr << "Failed to load CherryBomb texture!" << std::endl;
            // Handle the error appropriately
        }
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
        sprite.setScale(0.55, 0.55);
    }
     void update() {}

    void draw(sf::RenderWindow& window)  override {
        window.draw(sprite);
    }
};


class SunFlower : public Plant {
    sf::Texture texture; // Texture for the image
    sf::Sprite sprite;   // Sprite to display the image
    sf::Texture sunTexture;    // Texture for the sun sprite
    sf::Sprite sunSprite;      // Sprite to display the sun

    bool isVisible;  // Flag to control the visibility of the sun

    sf::Clock productionTimer;  // Timer to track the production of sunlight
    sf::Clock autocollect;
public:
    SunFlower(int x, int y) : Plant(100, 100, x, y), isVisible(false) {
        if (!texture.loadFromFile("Images/SunFlowerCursor.png")) {
            // Handle error
        }
        sprite.setTexture(texture);
        sprite.setScale(1.5, 1.5);
        sprite.setPosition(x, y);

        // Load sun texture
        if (!sunTexture.loadFromFile("Images/SunImage.png")) {
            // Handle error
        }
        sunSprite.setTexture(sunTexture);
        sunSprite.setScale(0.5, 0.5);  // Adjust scale as needed
        sunSprite.setPosition(sprite.getPosition().x + 20, sprite.getPosition().y - 30);

    }
    bool isAutoCollected() const {
        return isVisible && autocollect.getElapsedTime().asSeconds() >= 5;
    }
     void update() {
        // Check if the sun timer has exceeded 3 seconds
        if (isVisible && autocollect.getElapsedTime().asSeconds() >= 5) {
            isVisible = false; // Hide the sun sprite
            productionTimer.restart(); // Reset the timer
        }
    }

    void draw(RenderWindow& window)  override {
        window.draw(sprite);
        if (isVisible) {
            window.draw(sunSprite);
        }
        if (!isVisible && productionTimer.getElapsedTime().asSeconds() >= 10) {
            isVisible = 1;
            autocollect.restart();
        }
    }
};