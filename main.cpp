#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <ctime>
#include <cstdlib> 
#include <string>

#include "Functions.h"
#include "Zombie.h"
#include "FileHandling.h"
#include "Sun.h"
#include "Plant.h"
#include "Structure.h"
#include "Game.h"

using namespace sf;
using namespace std;


void readGridFromFile(RenderWindow& window, Plant* grid[5][9]) {
    std::ifstream file("FileHandling/Bonus.txt");
    int count = 0;
    if (file.is_open()) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 9; ++j) {
                int plantType;
                char comma;
                file >> plantType >> comma;
                // Depending on the plantType, create the corresponding Plant object
                switch (plantType) {
                case 1:
                    cout << count++ << endl;
                   // grid[i][j] = new SunFlower(200, 200); // Assuming Sunflower is a class derived from Plant
                    continue;
                default:
                    grid[i][j] = nullptr; // Handle unknown plant type (set to nullptr)
                    continue;
                }
            }
        }
        std::cout << "Grid loaded successfully from file." << std::endl;
        file.close();
    }
    else {
        std::cerr << "Error: Unable to open file for reading." << std::endl;
    }
}


void printMouseCoordinates(RenderWindow& window) {
    // Print mouse coordinates
    cout << "Mouse coordinates: (" << Mouse::getPosition(window).x << ", " << Mouse::getPosition(window).y << ")" << endl;
}

int main() {
    srand(time(nullptr));
    const int ROWS = 5;
    const int COLS = 9;
    const int MAP_WIDTH = 1920;
    const int MAP_HEIGHT = 1080;

    RenderWindow window(VideoMode(MAP_WIDTH, MAP_HEIGHT), "Plants Vs Zombies");
    Image icon;
    if (!icon.loadFromFile("Images/icon.png")) {
        return 1;
    }
    window.setIcon(32, 32, icon.getPixelsPtr());

    Player play;
    play.score = 0;
    play.level = 1;
    play.lives = 3;
    play.Badge = "ordinary";
    play.playerName;
    play.currency = 1000;
    
    
    int count = 0;
    Game game(play, window);
    Zombie* Army[10] = { nullptr }; 

    Cursor normalCursor;
    if (!normalCursor.loadFromSystem(Cursor::Arrow)) {
        cerr << "Failed to load default cursor" << endl;
        return 1;
    }

    Sun sun;

    bool isPaused = false;
    bool inMainMenu = true;
    bool inGame = 0;
    bool isLevelChoser = false;
    bool LoadedGame = 0;
    bool newGame = 0;

    bool HasShowel = 0;
    bool defaultCursor = 1;
    bool sunCursor = 0;
    bool peeCursor = 0;
    bool snowCursor = 0;
    bool repeaterCursor = 0;
    bool cherryCursor = 0;
    bool wallCursor = 0;

    sf::Sprite cursorSprite;
    FileHanling FileHandler;
    FileHandler.bubbleSortTextFile("FileHandling/data.txt");

    sf::Clock sunrespawnTimer;
    sf::Clock ZombieTimer;


    Plant* Grid[5][9] = { nullptr };
    
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            //Print Coordinates
            if (event.key.code == Keyboard::C) {
                printMouseCoordinates(window);
            }
            if (event.type == Event::KeyPressed) {
                if (inGame) {
                    if (event.key.code == Keyboard::P || event.key.code == Keyboard::Space) {
                        isPaused = !isPaused;
                    }
                }
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    if (peeCursor && play.currency >=100 ) {
                        
                        Coordinates result = getGridIndex(event.mouseButton.x,event.mouseButton.y);
                        if (result.x >= 0 && result.y >= 0) {
                            play.currency -= 100;
                            if (Grid[result.x][result.y] == nullptr) {

                                Grid[result.x][result.y] = new PeaShooter(100, 100, result.Xcordinate, result.Ycordinate, window);
                                std::cout << "Grid Index: [" << result.x << "][" << result.y << "]" << std::endl;
                                std::cout << "Center Coordinates: (" << result.Xcordinate << ", " << result.Ycordinate << ")" << std::endl;
                            }
                        }

                    }
                    if (wallCursor && play.currency >=150 ) {
                    
                        Coordinates result = getGridIndex(event.mouseButton.x, event.mouseButton.y);
                        if (result.x >= 0 && result.y >= 0) {
                            play.currency -= 150;
                            if (Grid[result.x][result.y] == nullptr) {

                                Grid[result.x][result.y] = new WallNut(result.Xcordinate, result.Ycordinate);
                                std::cout << "Grid Index: [" << result.x << "][" << result.y << "]" << std::endl;
                                std::cout << "Center Coordinates: (" << result.Xcordinate << ", " << result.Ycordinate << ")" << std::endl;
                            }
                        }
                    }
                    if (sunCursor && play.currency >= 100) {

                        Coordinates result = getGridIndex(event.mouseButton.x, event.mouseButton.y);
                        if (result.x >= 0 && result.y >= 0) {
                            play.currency -= 100;
                            if (Grid[result.x][result.y] == nullptr) {
                                Grid[result.x][result.y] = new SunFlower(result.Xcordinate, result.Ycordinate);
                                std::cout << "Grid Index: [" << result.x << "][" << result.y << "]" << std::endl;
                                std::cout << "Center Coordinates: (" << result.Xcordinate << ", " << result.Ycordinate << ")" << std::endl;
                            }
                        }
                    }
                    if (cherryCursor&& play.currency >=150 ) {
                  
                        Coordinates result = getGridIndex(event.mouseButton.x, event.mouseButton.y);
                        if (result.x >= 0 && result.y >= 0) {
                            play.currency -= 150;
                            if (Grid[result.x][result.y] == nullptr) {

                                Grid[result.x][result.y] = new CherryBomb(result.Xcordinate, result.Ycordinate);
                                std::cout << "Grid Index: [" << result.x << "][" << result.y << "]" << std::endl;
                                std::cout << "Center Coordinates: (" << result.Xcordinate << ", " << result.Ycordinate << ")" << std::endl;
                            }
                        }
                    }
                    
                    if (snowCursor && play.currency >= 150) {

                        Coordinates result = getGridIndex(event.mouseButton.x, event.mouseButton.y);
                        if (result.x >= 0 && result.y >= 0) {
                            play.currency -= 150;

                            Grid[result.x][result.y] = new SnowPeaShooter(150, 150, result.Xcordinate, result.Ycordinate);
                            std::cout << "Grid Index: [" << result.x << "][" << result.y << "]" << std::endl;
                            std::cout << "Center Coordinates: (" << result.Xcordinate << ", " << result.Ycordinate << ")" << std::endl;

                        }
                    }
                    if (repeaterCursor && play.currency >= 200) {
                        Coordinates result = getGridIndex(event.mouseButton.x, event.mouseButton.y);
                        if (result.x >= 0 && result.y >= 0) {
                            play.currency -= 200;
                            if (Grid[result.x][result.y] == nullptr) {
                                Grid[result.x][result.y] = new Repeater(200,200,result.Xcordinate, result.Ycordinate);
                                std::cout << "Grid Index: [" << result.x << "][" << result.y << "]" << std::endl;
                                std::cout << "Center Coordinates: (" << result.Xcordinate << ", " << result.Ycordinate << ")" << std::endl;
                            }
                        }
                    }

                    if (inMainMenu) {
                        //last game record
                        if (event.mouseButton.x >= 32 && event.mouseButton.x <= 200 && event.mouseButton.y >= 880 && event.mouseButton.y <= 1080) {
                            readGridFromFile(window, Grid);
                            inGame = 1;
                            inMainMenu = 0;
                        }
                        //Exit Button
                        if (event.mouseButton.x >= 1019 && event.mouseButton.x <= 1630 && event.mouseButton.y >= 585 && event.mouseButton.y <= 772) {
                            window.close();
                        }
                        //Load Previous Game
                        if (event.mouseButton.x >= 1003 && event.mouseButton.x <= 1630 && event.mouseButton.y >= 450 && event.mouseButton.y <= 640) {
                            LoadedGame = 1;
                            inMainMenu = false;
                        }
                        //Choose Your Level
                        if (event.mouseButton.x >= 992 && event.mouseButton.x <= 1750 && event.mouseButton.y >= 150 && event.mouseButton.y <= 331) {
                            isLevelChoser = 1;
                            LoadedGame = 0;
                            inMainMenu = false;
                        }
                        // New Game
                        if (event.mouseButton.x >= 995 && event.mouseButton.x <= 1710 && event.mouseButton.y >= 311 && event.mouseButton.y <= 514) {
                            play.playerName = newGameSetup(window, newGame);// Entering new player Name
                            
                            if (play.playerName == "-1") {
                                continue;
                            }
                            
                            FileHandler.SetName(play.playerName);
                            inMainMenu = false;
                            newGame = 1;
                            inGame = 1;
                            play.level = 1;
                            continue;
                        }

                        if (event.mouseButton.x >= 808 && event.mouseButton.x <= 1002 && event.mouseButton.y >= 752 && event.mouseButton.y <= 881) {
                            showInstructions(window);
                        }
                    }
                    if (inGame) {
                        if (!defaultCursor) {
                            defaultCursor = 1;
                            peeCursor = 0;
                            snowCursor = 0;
                            sunCursor = 0;
                            wallCursor = 0;
                            cherryCursor = 0;
                            repeaterCursor = 0;
                            window.setMouseCursor(normalCursor);
                        }
                        if (play.level >= 1) {
                            if ((event.mouseButton.x >= 19 && event.mouseButton.x <= 130 && event.mouseButton.y >= 136 && event.mouseButton.y <= 192)) {
                                defaultCursor = 0;
                                peeCursor = 1;
                                setPlantCursor("Images/PeeCursor.png", window, play.level, play.lives);
                            }
                            if ((event.mouseButton.x >= 19 && event.mouseButton.x <= 132 && event.mouseButton.y >= 217 && event.mouseButton.y <= 276)) {
                                defaultCursor = 0;
                                sunCursor = 1;
                                setPlantCursor("Images/SunFlowerCursor.png", window, play.level, play.lives);
                            }
                        }
                        if (play.level >= 2) {
                            if ((event.mouseButton.x >= 22 && event.mouseButton.x <= 137 && event.mouseButton.y >= 303 && event.mouseButton.y <= 351)) {
                                defaultCursor = 0;
                                wallCursor = 1;
                                setPlantCursor("Images/WallnutCursor.png", window, play.level, play.lives);
                            }
                            if ((event.mouseButton.x >= 25 && event.mouseButton.x <= 128 && event.mouseButton.y >= 390 && event.mouseButton.y <= 430)) {
                                defaultCursor = 0;
                                cherryCursor = 1;
                                setPlantCursor("Images/CherryBombCursor.png", window, play.level, play.lives);
                            }
                        }
                        if (play.level >= 3) {
                            if ((event.mouseButton.x >= 22 && event.mouseButton.x <= 123 && event.mouseButton.y >= 463 && event.mouseButton.y <= 504)) {
                                defaultCursor = 0;
                                snowCursor = 1;
                                setPlantCursor("Images/SnowPeaCursor.png", window, play.level, play.lives);
                            }
                            if ((event.mouseButton.x >= 22 && event.mouseButton.x <= 130 && event.mouseButton.y >= 544 && event.mouseButton.y <= 600)) {
                                defaultCursor = 0;
                                repeaterCursor = 1;;
                                setPlantCursor("Images/RepeaterCursor.png", window, play.level, play.lives);
                            }

                        }
                        if (event.mouseButton.x >= 1800 && event.mouseButton.x <= 1867 && event.mouseButton.y >= 10 && event.mouseButton.y <= 78) {
                            isPaused = true;
                        }
                        if (HasShowel) {
                            Coordinates result = getGridIndex(event.mouseButton.x, event.mouseButton.y);
                            Grid[result.x][result.y] = nullptr;
                            window.setMouseCursor(normalCursor);
                            HasShowel = 0;
                        }

                        if (event.mouseButton.button == Mouse::Left &&
                            event.mouseButton.x >= 1835 && event.mouseButton.x <= 1874 &&
                            event.mouseButton.y >= 878 && event.mouseButton.y <= 934) {
                            initializeAndSetCursor(window);
                            HasShowel = 1;
                        }
                    }
                    if (isLevelChoser) {
                        if (event.mouseButton.button == Mouse::Left &&
                            event.mouseButton.x >= 772 && event.mouseButton.x <= 1184 &&
                            event.mouseButton.y >= 832 && event.mouseButton.y <= 904) {
                            isLevelChoser = 0;
                            inMainMenu = 1;
                        }
                    }

                    if (LoadedGame) {
                        if (event.mouseButton.button == Mouse::Left &&
                            event.mouseButton.x >= 991 && event.mouseButton.x <= 1046 &&
                            event.mouseButton.y >= 270 && event.mouseButton.y <= 317) {
                            LoadedGame = 0;
                            inMainMenu = 1;
                        }
                        if(event.mouseButton.x >= 590 && event.mouseButton.x <= 1045 && event.mouseButton.y >= 348 && event.mouseButton.y <= 404) {
                            Player data = initializeGameFromLine(1, window);
                            play.level = data.level;
                            play.playerName = data.playerName;
                            play.currency = data.currency;
                            play.lives = data.lives;
                            play.score = data.score;
                            play.Badge = "gold";
                            LoadedGame = 0;
                            inGame = 1;

                            game.StartTheGame(play);
                        }
                        if (event.mouseButton.x >= 590 && event.mouseButton.x <= 1045 && event.mouseButton.y >= 425 && event.mouseButton.y <= 482) {
                            Player data = initializeGameFromLine(2, window);
                            play.level = data.level;
                            play.playerName = data.playerName;
                            play.currency = data.currency;
                            play.lives = data.lives;
                            play.score = data.score;
                            play.Badge = "silver";
                            LoadedGame = 0;
                            inGame = 1;

                            game.StartTheGame(play);
                        }
                        if (event.mouseButton.x >= 590 && event.mouseButton.x <= 1045 && event.mouseButton.y >= 495 && event.mouseButton.y <= 550) {
                            Player data = initializeGameFromLine(3, window);
                            play.level = data.level;
                            play.playerName = data.playerName;
                            play.currency = data.currency;
                            play.lives = data.lives;
                            play.score = data.score;
                            play.Badge = "bronze";
                            LoadedGame = 0;
                            inGame = 1;

                            game.StartTheGame(play);
                        }
                        if (event.mouseButton.x >= 590 && event.mouseButton.x <= 1045 && event.mouseButton.y >= 576 && event.mouseButton.y <= 630) {
                            Player data = initializeGameFromLine(4, window);
                            play.level = data.level;
                            play.playerName = data.playerName;
                            play.currency = data.currency;
                            play.lives = data.lives;
                            play.score = data.score;
                            play.Badge = "ordinary";
                            LoadedGame = 0;
                            inGame = 1;

                            game.StartTheGame(play);
                        }
                        if (event.mouseButton.x >= 590 && event.mouseButton.x <= 1045 && event.mouseButton.y >= 650 && event.mouseButton.y <= 700) {
                            Player data = initializeGameFromLine(5, window);
                            play.level = data.level;
                            play.playerName = data.playerName;
                            play.currency = data.currency;
                            play.lives = data.lives;
                            play.score = data.score;
                            play.Badge = "ordinary";
                            LoadedGame = 0;
                            inGame = 1;

                            game.StartTheGame(play);
                        }




                    }
                }
            }
        }

        if (isLevelChoser) {
            chooseLevel(window);
            if (event.mouseButton.button == Mouse::Right) {
                if (event.mouseButton.x >= 40 && event.mouseButton.x <= 432 && event.mouseButton.y >= 76 && event.mouseButton.y <= 408) {
                    play.level = 1;
                    window.clear();
                    inMainMenu = 0;
                    isLevelChoser = 0;
                    LoadedGame = 0;
                    inGame = 1;
                    game.StartTheGame(play);
                }
                if (event.mouseButton.x >= 485 && event.mouseButton.x <= 889 && event.mouseButton.y >= 74 && event.mouseButton.y <= 399) {
                    play.level = 2;
                    window.clear();
                    inMainMenu = 0;
                    isLevelChoser = 0;
                    LoadedGame = 0;
                    inGame = 1;
                    game.StartTheGame(play);
                }
                if (event.mouseButton.x >= 932 && event.mouseButton.x <= 1325 && event.mouseButton.y >= 78 && event.mouseButton.y <= 400) {
                    play.level = 3;
                    window.clear();
                    inMainMenu = 0;
                    isLevelChoser = 0;
                    LoadedGame = 0;
                    inGame = 1;
                    game.StartTheGame(play);
                }
                if (event.mouseButton.x >= 1378 && event.mouseButton.x <= 1765 && event.mouseButton.y >= 79 && event.mouseButton.y <= 384) {
                    play.level = 4;
                    window.clear();
                    inMainMenu = 0;
                    isLevelChoser = 0;
                    LoadedGame = 0;
                    inGame = 1;

                    game.StartTheGame(play);
                }
                if (event.mouseButton.x >= 247 && event.mouseButton.x <= 628 && event.mouseButton.y >= 429 && event.mouseButton.y <= 744) {
                    play.level = 5;
                    window.clear();
                    inMainMenu = 0;
                    isLevelChoser = 0;
                    LoadedGame = 0;
                    inGame = 1;

                    game.StartTheGame(play);
                }
                if (event.mouseButton.x >= 743 && event.mouseButton.x <= 1124 && event.mouseButton.y >= 432 && event.mouseButton.y <= 740) {
                    play.level = 6;
                    window.clear();
                    inMainMenu = 0;
                    isLevelChoser = 0;
                    LoadedGame = 0;
                    inGame = 1;

                    game.StartTheGame(play);

                }
                if (event.mouseButton.x >= 1231 && event.mouseButton.x <= 1591 && event.mouseButton.y >= 435 && event.mouseButton.y <= 734) {
                    srand(time(0));
                    play.level = rand() % 6 + 1;
                    window.clear();
                    inMainMenu = 0;
                    isLevelChoser = 0;
                    inGame = 1;
                    LoadedGame = 0;

                    game.StartTheGame(play);
                }
            }
            continue;
        }
        
        if (LoadedGame) {
            displayPreviousData(window);
            LoadedGameMenu(window);
            continue;
        }
        if (inMainMenu) {
            drawMainMenu(window);
            continue;
        }
        if (inGame) {
            if (ZombieTimer.getElapsedTime().asSeconds() >= 10) {
                // Create a new zombie
                for (int i = 0; i < 10; ++i) {
                    if (Army[i] == nullptr) {
                        Army[i] = new NormalZombie();
                        break;
                    }
                }
                // Restart the timer
                ZombieTimer.restart();
            }
            if (sun.checkSunCollision(event.mouseButton.x, event.mouseButton.y)) {
                play.currency += 50;
                cout << " Score Added" << play.currency << endl;
                sun.toggle();
            }
            if (!sun.getIsVisible() && sunrespawnTimer.getElapsedTime().asSeconds() >= 10) {
                sun.respawn();

                sunrespawnTimer.restart(); // Reset the timer
            }

        }
        if (isPaused) {
            if (event.mouseButton.x >= 871 && event.mouseButton.x <= 1155 && event.mouseButton.y >= 482 && event.mouseButton.y <= 521) {
                inMainMenu = 1;
                inGame = 0;
                isLevelChoser = 0;
                LoadedGame = 0;
                isPaused = 0;
                for (int i = 0; i < 5; ++i) {
                    for (int j = 0; j < 9; ++j) {
                        Grid[i][j] = nullptr;

                        }
                    }   
            }
            if (event.mouseButton.x >= 788 && event.mouseButton.x <= 1230 && event.mouseButton.y >= 567 && event.mouseButton.y <= 642) {
                inMainMenu = 0;
                isLevelChoser = 0;
                LoadedGame = 0;
                inGame = 1;
                isPaused = 0;
            }
            drawPauseMenu(window);

            continue;
        }
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (Grid[i][j] != nullptr) {
                    SunFlower* sunflower = dynamic_cast<SunFlower*>(Grid[i][j]);
                    if (sunflower != nullptr) {
                        if (sunflower->isAutoCollected()) {
                            play.currency+=50;
                         
                        }
                    }
                }
            }
        }
        sun.update(0.1f,window);
        
        window.clear();

        game.StartTheGame(play);
        sun.draw(window);
        window.draw(cursorSprite);
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (Grid[i][j] != nullptr) {
                    Grid[i][j]->draw(window);
                    Grid[i][j]->update();
                }
            }
        }
        for (int i = 0; i < 10; ++i) {
            if (Army[i] != nullptr) {
                Army[i]->draw(window);
                if (Army[i]->check()) {
                    play.lives -= 1;
                    break;
                }
                Army[i]->update(0.1f);
            }
        }
        if (play.lives == 0) {
            // Load the new background texture
            sf::Texture backgroundTexture;
            if (!backgroundTexture.loadFromFile("Images/Exit.jpg")) {
                std::cerr << "Failed to load background texture!" << std::endl;
                return 1; // Consider handling the error in a more appropriate way
            }

            // Create a sprite for the new background
            sf::Sprite backgroundSprite(backgroundTexture);

            // Display the new background for a brief moment
            window.draw(backgroundSprite);
            window.display();

            // Delay before closing the window (optional)
            sf::sleep(sf::seconds(2)); // Adjust the duration as needed

            // Close the window
            window.close();
        }

        window.display();
    }

    return 0;
}
