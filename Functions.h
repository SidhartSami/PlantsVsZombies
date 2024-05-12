#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Header.h"
#include "Structure.h"

using namespace sf;
using namespace std;

    void drawPauseMenu(RenderWindow& window) {
        // Clear the screen
        window.clear();

        // Draw pause menu background
        Texture pauseMenuTexture, MenuOptionTexture;
        if (!pauseMenuTexture.loadFromFile("Images/PauseMenu.jpg"), !MenuOptionTexture.loadFromFile("Images/MenuOption.png")) {
            cerr << "Failed to load pause menu background image" << endl;
            return;
        }
        Sprite pauseMenuSprite(pauseMenuTexture);

        Sprite MenuOptionsSprite(MenuOptionTexture);
        MenuOptionsSprite.setPosition(450, 0);
        MenuOptionsSprite.setScale(2, 2);
        window.draw(pauseMenuSprite);
        window.draw(MenuOptionsSprite);
        
        // Display the changes
        window.display();
    }
    // Main MEnu
    void drawMainMenu(RenderWindow& window) {
        window.clear();

        Texture mainMenuTexture;
        if (!mainMenuTexture.loadFromFile("Images/MainMenu.jpg")) {
            cerr << "Failed to load main menu background image" << endl;
            return;
        }
        Sprite mainMenuSprite(mainMenuTexture);
        window.draw(mainMenuSprite);
       
        window.display();
    }

    void displayPreviousData(RenderWindow& window) {
        ifstream inputFile("FileHandling/data.txt");
        if (inputFile.is_open()) {
            sf::Font font;
            if (!font.loadFromFile("Font/Font.ttf")) { // Replace "Font/Font.ttf" with the path to your font file
                cerr << "Failed to load font!" << endl;
                return;
            }

            Text userData("", font, 40); // Text object for user name

            string line;
            int yPosition = 370; // Starting Y position for rendering
            userData.setFillColor(Color::Black); // Set font color to black

            while (getline(inputFile, line)) {
                stringstream ss(line); // stringstream for parsing each line
                string name;
                if (getline(ss, name, ',')) { // Get the name from the line
                    userData.setString(name);
                    userData.setPosition(660, yPosition); // Set position for the name text
                    window.draw(userData); // Draw the name text
                    yPosition += 80; // Move to the next line
                }
            }

            inputFile.close();

            window.display();
        }
        else {
            cerr << "Unable to open file for reading: FileHandling/data.txt" << endl;
        }
    }
    void  chooseLevel(RenderWindow& window) {
        window.clear();

        Texture levelSelectionTexture;
        levelSelectionTexture.loadFromFile("Images/LevelSelect.jpg");

        Sprite levelSelectionSprite;
        levelSelectionSprite.setTexture(levelSelectionTexture);
        levelSelectionSprite.setPosition(0, 0);

        window.draw(levelSelectionSprite);
        window.display();
    }
    void  LoadedGameMenu(RenderWindow& window) {
        Texture levelSelectionTexture;
        levelSelectionTexture.loadFromFile("Images/Design.png");

        Sprite levelSelectionSprite;
        levelSelectionSprite.setScale(2.5, 2.5);
        levelSelectionSprite.setTexture(levelSelectionTexture);
        levelSelectionSprite.setPosition(550, 250);

        window.draw(levelSelectionSprite);
        displayPreviousData(window);

        window.display();
    }
    void initializeAndSetCursor(RenderWindow& window) {
        // Load the cursor image
        Texture cursorTexture;
        if (!cursorTexture.loadFromFile("Images/ShovelCursor.png")) {
            cerr << "Failed to load cursor image" << endl;
            return;
        }

        // Change the cursor to the loaded image
        Cursor cursor;
        cursor.loadFromPixels(cursorTexture.copyToImage().getPixelsPtr(), cursorTexture.getSize(), { 0, 0 });
        window.setMouseCursor(cursor);
    }

    void setPlantCursor(const std::string& imagePath, sf::RenderWindow& window, int level, int lives) {
        Texture cursorTexture;
        if (!cursorTexture.loadFromFile(imagePath)) {
            cerr << "Failed to load cursor texture" << std::endl;
            return;
        }
        Cursor cursor;
        
        cursor.loadFromPixels(cursorTexture.copyToImage().getPixelsPtr(), cursorTexture.getSize(), { 0, 0 });
        window.setMouseCursor(cursor);
    }

 string newGameSetup(RenderWindow& window, bool& newGame) {
    // Load the texture for the text box sprite
    Texture textBoxTexture;
    if (!textBoxTexture.loadFromFile("Images/Name.jpg")) {
        cerr << "Failed to load text box sprite!" << endl;
        return "-1";
    }

    // Create and configure the text box sprite
    Sprite textBoxSprite(textBoxTexture);
    textBoxSprite.setPosition(500, 300); // Set the position of the text box sprite

    // Create and configure the text object for displaying the player's input inside the text box
    Font font;
    if (!font.loadFromFile("Font/Font.ttf")) {
        cerr << "Failed to load font!" << endl;
        return "-1";
    }

    Text inputText("", font, 40);
    inputText.setFillColor(Color::Black);
    inputText.setPosition(575, 525); // Adjust the position as needed

    // Event loop to handle data input
    string playerName;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::TextEntered) {
                if (event.text.unicode < 128 && event.text.unicode != 13) { // 13 is the Enter key
                    if (event.text.unicode == '\b') { // Check for backspace
                        // Remove the last character from playerName
                        if (!playerName.empty()) {
                            playerName.pop_back();
                            inputText.setString(playerName);
                        }
                    }
                    else {
                        playerName += static_cast<char>(event.text.unicode);
                        inputText.setString(playerName);
                    }
                }
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Enter) {
                    newGame = false; // Player name input completed, start the game

                    // Open the file in append mode to add the player's data
                    ofstream outputFile("FileHandling/data.txt", ios::app);
                    if (outputFile.is_open()) {
                        // Write the new player's data
                        outputFile << playerName << ",1,0" << endl; // Default level is 1 and score is 0
                        outputFile.close();
                    } else {
                        cerr << "Failed to open file for writing: FileHandling/data.txt" << endl;
                    }

                    return playerName;
                }
                else if (event.key.code == Keyboard::Escape) {
                    // Return to main menu
                    newGame = false;
                    return "-1";
                }
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    // Check if the mouse coordinates match any of the specified coordinates
                    Vector2i mousePosition = Mouse::getPosition(window);
                    if ((mousePosition.x >= 552 && mousePosition.x <= 851) &&
                        (mousePosition.y >= 579 && mousePosition.y <= 635)) {
                        newGame = false; // Player name input completed, start the game

                        // Open the file in append mode to add the player's data
                        ofstream outputFile("FileHandling/data.txt", ios::app);
                        if (outputFile.is_open()) {
                            // Write the new player's data
                            outputFile << playerName << ",1,0" << endl; // Default level is 1 and score is 0
                            outputFile.close();
                        } else {
                            cerr << "Failed to open file for writing: FileHandling/data.txt" << endl;
                        }

                        return playerName;
                    }
                    else if ((mousePosition.x >= 875 && mousePosition.x <= 1170) &&
                        (mousePosition.y >= 594 && mousePosition.y <= 633)) {
                        newGame = false;
                        return "-1";
                    }
                }
            }
        }

        window.draw(textBoxSprite);
        window.draw(inputText);
        window.display();
    }
    // Shouldn't reach this point, but return "-1" if it does
    return "-1";
}

    void showInstructions(RenderWindow& window) {
        Texture instructionsTexture;
        if (!instructionsTexture.loadFromFile("Images/Instructions.png")) {
            cerr << "Failed to load instructions image!" << endl;
            return;
        }

        Sprite instructionsSprite(instructionsTexture);
        instructionsSprite.setPosition(400, 300);
        instructionsSprite.setScale(1.75, 1.75);
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                if (event.type == Event::KeyPressed || event.type == Event::MouseButtonPressed) {
                    // Return as soon as any key or mouse button is pressed
                    return;
                }
            }
            window.draw(instructionsSprite);
            window.display();
        }
    }

    Coordinates getGridIndex(int x, int y) {
            int topLeftX = 476;
            int topLeftY = 134;
            int bottomRightX = 1869;
            int bottomRightY = 931;

        int rows = 5;
        int cols = 9;

        int gridWidth = bottomRightX - topLeftX;
        int gridHeight = bottomRightY - topLeftY;

        int cellWidth = gridWidth / cols;
        int cellHeight = gridHeight / rows;

        int relativeX = x - topLeftX;
        int relativeY = y - topLeftY;

        int row = relativeY / cellHeight;
        int col = relativeX / cellWidth;

        // Calculate center coordinates of the box
        int centerX = topLeftX + (col * cellWidth) + (cellWidth / 2);
        int centerY = topLeftY + (row * cellHeight) + (cellHeight / 2);
       
        return { row, col, centerX, centerY };
    }
