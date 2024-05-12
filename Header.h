//#pragma once
//#include <iostream>
//using namespace std;
//#include <string>
//#include <SFML/Graphics.hpp>
//
//
//class ScoreBoard {
//};
//class PlantFactory {
//	Plant plant;
//	Zombie zombie;
//};
//class GameLevel {
//	PlantFactory Plant;
//	ZombieFactory Zombie;
//};
//
//class Level1 :public GameLevel{
//
//};
//class Level2 :public GameLevel {
//
//};
//class Level3 :public GameLevel {
//
//}; 
//class Level4 :public GameLevel {
//
//}; 
//class Level5 :public GameLevel {
//
//};
//class Level6 :public GameLevel {
//
//};
//class GameTime {
//
//};
//class Game {
//	ScoreBoard* Score;
//	GameLevel* Level;//Abstract
//	GameTime Time;
// };
//
//class Plant {
//protected:
//    int health;
//    int price;
//    string type;
//    int locationX;
//    int locationY;
//    static int numberOfPlants;
//
//public:
//    Plant(int h, int p, string t, int x, int y)
//        : health(h), price(p), type(t), locationX(x), locationY(y) {
//        numberOfPlants++;
//    }
//
//     Methods for plant actions
//    virtual void attack() = 0; // Pure virtual function to be overridden by subclasses
//    virtual void takeDamage(int damage) {
//        health -= damage;
//    }
//
//    int getLocationX() const { return locationX; }
//    int getLocationY() const { return locationY; }
//
//    static int getNumberOfPlants() { return numberOfPlants; }
//};
//
//int Plant::numberOfPlants = 0;
//
//class Zombie {
//protected:
//    int health;
//    int speed;
//    string type;
//    int locationX;
//    int locationY;
//public:
//    Zombie(int h, int s, string t, int x, int y)
//        : health(h), speed(s), type(t), locationX(x), locationY(y) {}
//    virtual void move() = 0; 
//
//    virtual void takeDamage(int damage) {
//        health -= damage;
//    }
//};
//
//class Player {
//    static int Lives;
//    static int Level;
//    int Score;
//    string* Inventory;
//    int InventorySize;
//    int Money;
//
//public:
//    Player(int initialLives, int initialLevel, int initialMoney)
//        : Score(0), Inventory(nullptr), InventorySize(0), Money(initialMoney) {
//        Lives = initialLives;
//        Level = initialLevel;
//    }
//
//    ~Player() {
//        delete[] Inventory;
//    }
//
//    static int getLives() { return Lives; }
//    static void setLives(int value) { Lives = value; }
//
//    static int getLevel() { return Level; }
//    static void setLevel(int value) { Level = value; }
//
//    int getScore() const { return Score; }
//    void setScore(int value) { Score = value; }
//
//    string* getInventory() const { return Inventory; }
//    void setInventory(string* inventory, int size) {
//        if (Inventory != nullptr) {
//            delete[] Inventory;
//        }
//        Inventory = inventory;
//        InventorySize = size;
//    }
//
//    int getInventorySize() const { return InventorySize; }
//
//    int getMoney() const { return Money; }
//    void setMoney(int money) { Money = money; }
//    void addMoney(int amount) {
//        Money += amount;
//        cout << "Added " << amount << " money. Total money: " << Money << endl;
//    }
//    void decreaseLives() {
//        Lives -= 1;
//        cout << "Lost " << 1 << " lives. Remaining lives: " << Lives << endl;
//    }
//    void increaseLevel() {
//        Level++;
//        cout << "Increased level to " << Level << endl;
//    }
//};
//
//int Player::Lives = 3;
//int Player::Level = 1;
