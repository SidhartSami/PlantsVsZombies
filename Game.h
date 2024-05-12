#pragma once 
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <ctime>
#include <cstdlib> 
#include <fstream>
#include <sstream>
#include <string>

class ScoreBoard {
private:
    int Currency;
    int Score;
    string Badge;
public:
    ScoreBoard() {
        Currency = 0;
        Score = 0;
    }
    ScoreBoard(int OldScore, int OldCurrency) {
        Currency = OldCurrency;
        Score = OldScore;
    }
    int GetScore() {
        return Score;
    }
    void SetScore(int OldScore) {
        Score = OldScore;
    }

    int GetCurrency() {
        return Currency;
    }
    void SetCurrency(int OldCurrency) {
        Currency = OldCurrency;
    }
    void SetBadge(string& badge) {
        Badge = badge;
    }

    void updateScore(int points) {
        Score += points;
    }
    void updateCurrency(int currency) {
        Currency += currency;
    }

    void displayCurrency(RenderWindow& window) {
        Font font;
        if (!font.loadFromFile("Font/Font.ttf")) {
        }
        Text currencyText;
        currencyText.setFont(font);
        currencyText.setString(to_string(Currency));
        currencyText.setCharacterSize(24);
        currencyText.setFillColor(Color::Yellow);
        currencyText.setPosition(95, 50);

        window.draw(currencyText);
    }
    void displayScore(RenderWindow& window) {
        Font font;
        if (!font.loadFromFile("Font/Font.ttf")) {
            // Handle font loading failure if needed
        }

        // Load the sprite image
        Texture bgTexture;
        if (!bgTexture.loadFromFile("Images/BG.png")) {
            // Handle sprite loading failure if needed
        }

        // Create a sprite with the loaded texture
        Sprite bgSprite(bgTexture);
        bgSprite.setScale(1.5, 1);
        // Set the position of the sprite
        bgSprite.setPosition(180, 30);

        // Draw the sprite on the window
        window.draw(bgSprite);

        // Create and draw the score text
        Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Score: " + to_string(Score));
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(Color::Yellow);
        scoreText.setPosition(200, 50);

        window.draw(scoreText);
    }
    void displayBadge(const string& badgeType, RenderWindow& window) {
        Texture goldBadgeTexture, silverBadgeTexture, bronzeBadgeTexture, ordinaryBadgeTexture;

        if (!goldBadgeTexture.loadFromFile("Images/Gold.png")) {
        }

        if (!silverBadgeTexture.loadFromFile("Images/Silver.png")) {
        }

        if (!bronzeBadgeTexture.loadFromFile("Images/Bronze.png")) {
        }

        if (!ordinaryBadgeTexture.loadFromFile("Images/Ordinary.png")) {
        }

        Sprite badgeSprite;
        badgeSprite.setScale(0.5, 0.5);
        badgeSprite.setPosition(400, 10);

        if (badgeType == "gold") {
            badgeSprite.setTexture(goldBadgeTexture);
        }
        else if (badgeType == "silver") {
            badgeSprite.setTexture(silverBadgeTexture);
        }
        else if (badgeType == "bronze") {
            badgeSprite.setTexture(bronzeBadgeTexture);
        }
        else {
            badgeSprite.setTexture(ordinaryBadgeTexture);
        }

        window.draw(badgeSprite);
    }

};

class Level {
private:
    int levelNumber;

    sf::Sprite backgroundSprite; // Sprite for the background
    sf::Texture backgroundTexture; // Texture for the background
    Zombie* zombies[5];
    Plant* plants[5][9];
public:

    Level(int number) : levelNumber(number) {
        for (int i = 0; i < 5; ++i) {
            zombies[i] = nullptr;
            for (int j = 0; j < 9; ++j) {
                plants[i][j] = nullptr;
            }
        }
           }
    void drawBackground(RenderWindow& window) {
        window.draw(backgroundSprite);
    }
    void drawBack(RenderWindow& window, int level) {
        Image map_image;
        string image_path;
        switch (level) {
        case 1:
            image_path = "Images/BackYardBack.jpg";
            break;
        case 2:
            image_path = "Images/AncientEgyptBack.jpg";
            break;
        case 3:
            image_path = "Images/JapanBack.jpg";
            break;
        case 4:
            image_path = "Images/Level4.jpg";
            break;
        case 5:
            image_path = "Images/Level5.jpg";
            break;
        case 6:
            image_path = "Images/NightBack.jpg";
            break;
        default:
            image_path = "Images/BackYardBack.jpg";
            break;
        }

        // Load the image from file
        if (!map_image.loadFromFile(image_path)) {
            cerr << "Failed to load map image: " << image_path << endl;
            return;
        }

        Texture map_texture;
        map_texture.loadFromImage(map_image);
        Sprite s_map;
        s_map.setTexture(map_texture);
        s_map.setPosition(0, 0);

        window.draw(s_map);
    }
    void createButtons(RenderWindow& window) {
        // Pause Button
        Image pause_image;
        pause_image.loadFromFile("Images/Pause.png");

        Texture pause_texture;
        pause_texture.loadFromImage(pause_image);

        Sprite pauseSprite;
        pauseSprite.setTexture(pause_texture);
        pauseSprite.setPosition(1800, 10);

        // Speedup Button
        Image speedup_image;
        speedup_image.loadFromFile("Images/SpeedUpButton.png");

        Texture speedup_texture;
        speedup_texture.loadFromImage(speedup_image);

        Sprite speedupSprite;
        speedupSprite.setTexture(speedup_texture);
        speedupSprite.setScale(0.5, 0.5);
        speedupSprite.setPosition(1715, 10);

        // Shovel Button
        Image shovel_image;
        shovel_image.loadFromFile("Images/ShovelOption.png");

        Texture shovel_texture;
        shovel_texture.loadFromImage(shovel_image);

        Sprite shovelSprite;
        shovelSprite.setTexture(shovel_texture);
        shovelSprite.setPosition(1800, 950);

        // Draw rectangle
        float rectWidth = 120.0f;
        float rectHeight = 30.0f;
        float rectPosX = 24.0f;
        float rectPosY = 46.0f;

        RectangleShape rectangle(Vector2f(rectWidth, rectHeight));
        rectangle.setPosition(rectPosX, rectPosY);
        rectangle.setFillColor(Color::Black);

        // Sun Image
        Image sun_image; // Should be sun_image instead of shovel_image
        sun_image.loadFromFile("Images/SunImage.png"); // Load sun image

        Texture Sun_Texture;
        Sun_Texture.loadFromImage(sun_image); // Load texture from image

        Sprite Sun_Sprite;

        Sun_Sprite.setTexture(Sun_Texture); // Set texture to sprite
        Sun_Sprite.setScale(0.45, 0.45);
        Sun_Sprite.setPosition(5, 30); // Position the sprite

        window.draw(pauseSprite);
        window.draw(speedupSprite);
        window.draw(shovelSprite);
        window.draw(rectangle);
        window.draw(Sun_Sprite);
    }

    void drawCard(const string& imagePath, const Vector2f& position, RenderWindow& window) {
        Texture cardTexture;
        if (!cardTexture.loadFromFile(imagePath)) {
            cerr << "Failed to load card image: " << imagePath << endl;
            return;
        }

        Sprite cardSprite(cardTexture);
        cardSprite.setScale(1.25, 1.25);
        cardSprite.setPosition(position);
        window.draw(cardSprite);
    }

    void drawLevelCards(RenderWindow& window, int level) {
        switch (level) {
        case 6:
        case 5:
            //drawCard("Images/FumeShroomCard.png", { 10, 840 });
            //drawCard("Images/PuffShroomCard.png", { 10, 760 });
        case 4:
            //drawCard("Images/TorchWoodCard.png", { 10, 670 });
        case 3:
            drawCard("Images/RepeaterCard.png", { 10, 580 },window);
            drawCard("Images/SnowPeeCard.png", { 10, 490 }, window);
        case 2:
            drawCard("Images/CherryBombCard.png", { 10, 410 }, window);
            drawCard("Images/WallNutCard.png", { 10, 320 }, window);
        case 1:
            drawCard("Images/PeeShooterCard.png", { 10, 140 }, window);
            drawCard("Images/SunFlowerCard.png", { 10, 230 }, window);
            break;
        default:
            break;
        }
    }

    void drawHealthBar(RenderWindow& window, int Lives) {
        Texture HealthBarTexture;
        if (Lives == 3) {
            if (!HealthBarTexture.loadFromFile("Images/HealthBarFull.png")) {
                cerr << "Failed to load HealthBar image: HealthBarFull.png" << endl;
                return;
            }
        }
        else if (Lives == 2) {
            if (!HealthBarTexture.loadFromFile("Images/HealthBarHalf.png")) {
                cerr << "Failed to load HealthBar image: HealthBarHalf.png" << endl;
                return;
            }
        }
        else if (Lives == 1) {
            if (!HealthBarTexture.loadFromFile("Images/HealthBarLast.png")) {
                cerr << "Failed to load HealthBar image: HealthBarLast.png" << endl;
                return;
            }
        }
        else {

            if (!HealthBarTexture.loadFromFile("Images/HealthBarEmpty.png")) {
                cerr << "Failed to load HealthBar image: HealthBarEmpty.png" << endl;
                return;
            }
         
        }
        Sprite healthBarSprite(HealthBarTexture);
        healthBarSprite.setScale(0.6, 0.6);
        healthBarSprite.setPosition(1200, 5);
        window.draw(healthBarSprite);
    }
    void UpdateHealthTexture(RenderWindow& window, int lives) {
        drawHealthBar(window, lives);
    }
    void UpdateLevelCard(RenderWindow& window, int level) {
        drawLevelCards(window, level);
    }
    void update(bool isPaused, RenderWindow& window, int level) {
        if (!isPaused) {
            drawBack(window, level);
        }

    }

    void intializationOfMap(RenderWindow& window, int level, int lives) {
        drawBack(window, level);
        createButtons(window);
        drawHealthBar(window, lives);
        drawLevelCards(window, level);

    }


};

class Game {
    RenderWindow& window;
    ScoreBoard scoreboard; //Composition
    Player& player;
    Level level;
public:
    Game(Player& playerdata,RenderWindow& window)
        : scoreboard(playerdata.score, playerdata.currency),player(playerdata),window(window),level(playerdata.level){}

    void play(int score,int currency) {
        scoreboard.updateScore(score);
        scoreboard.updateCurrency(currency);
    }
    void StartTheGame(Player& player) {
        scoreboard.SetCurrency(player.currency);
        scoreboard.SetScore(player.score);
        scoreboard.SetBadge(player.Badge);
        level.intializationOfMap(window, player.level, player.lives);
        scoreboard.displayCurrency(window);
        scoreboard.displayScore(window);
        scoreboard.displayBadge(player.Badge, window);
    }
    void updateLevel(RenderWindow& window, bool isPaused, int levelNumber) {
        cout << "congracts you processed toward next round" << endl;
        level.update(isPaused, window, levelNumber);
    }
    
};
