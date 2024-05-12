#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

#include "Functions.h" 
#include "Zombie.h"


Player initializeGameFromLine(int lineNumber, RenderWindow& window) {
    
    ifstream file("FileHandling/data.txt");
    if (!file.is_open()) {
        cerr << "Failed to open player data file." << endl;
        return Player();
    }

    string line;
    string name;
    int level = 0; // Default value
    int score = 0; // Default value
    int lives = 0; // Default value
    int currency = 0; // Default value

    // Read lines until the desired line number is reached
    for (int i = 0; i < lineNumber; ++i) {
        if (!getline(file, line)) {
            cerr << "Error: Line number exceeds file length." << endl;
            // Return a default-initialized Player struct if line number exceeds file length
            return Player();
        }
    }

    // Read the line and extract data using stringstream
    stringstream ss(line);
    string token;
    // Read name
    if (getline(ss, token, ',')) {
        name = token;
    }
    else {
        cerr << "Error: Failed to read player name." << endl;
        // Return a default-initialized Player struct if name cannot be read
        return Player();
    }
    // Read level
    if (getline(ss, token, ',')) {
        level = stoi(token);
    }
    else {
        cerr << "Error: Failed to read player level." << endl;
        // Return a default-initialized Player struct if level cannot be read
        return Player();
    }
    // Read score
    if (getline(ss, token, ',')) {
        score = stoi(token);
    }
    else {
        cerr << "Error: Failed to read player score." << endl;
        // Return a default-initialized Player struct if score cannot be read
        return Player();
    }
    // Read lives
    if (getline(ss, token, ',')) {
        lives = stoi(token);
    }
    else {
        cerr << "Error: Failed to read player lives." << endl;
        // Return a default-initialized Player struct if lives cannot be read
        return Player();
    }
    // Read currency
    if (getline(ss, token, ',')) {
        currency = stoi(token);
    }
    else {
        cerr << "Error: Failed to read player currency." << endl;
        // Return a default-initialized Player struct if currency cannot be read
        return Player();
    }

    file.close();

    cout << "Initializing game for player: " << name << endl;
    cout << "Level: " << level << ", Score: " << score << ", Lives: " << lives << ", Currency: " << currency << endl;

    // Return a Player struct initialized with the read data
    return { name, score, level, lives,"ordinary", currency };
}

class FileHanling {
private:
    string Name;
    int Score;
    int Level;
    string Badge;

    int currentLine;

    void parseLine(const string& line, string& name, int& level, int& score) {
        stringstream ss(line);
        getline(ss, name, ',');
        ss >> level;
        ss.ignore(); // Ignore the comma
        ss >> score;
    }

    // Function to bubble sort lines of text based on score
    void bubbleSort(string* lines, int size) {
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                string name1, name2;
                int level1, level2, score1, score2;
                parseLine(lines[j], name1, level1, score1);
                parseLine(lines[j + 1], name2, level2, score2);
                if (score1 < score2) {
                    swap(lines[j], lines[j + 1]);
                }
            }
        }
    }

    // Function to save sorted data back to the file
    void saveSortedData(string* lines, int size, const string& filename) {
        ofstream outputFile(filename);
        if (outputFile.is_open()) {
            for (int i = 0; i < size; ++i) {
                outputFile << lines[i] << endl;
            }
            outputFile.close();
            cout << "Data sorted and saved successfully." << endl;
        }
        else {
            cerr << "Unable to open file for writing: " << filename << endl;
        }
    }
public:
    // Constructor with default values
    FileHanling(const string& name = "", int score = 0, int level = 1, const string& badge = "Ordinary", int line = 0)
        : Name(name), Score(score), Level(level), Badge(badge),currentLine(line) {}
    
    string GetName() const { return Name; }
    int GetScore() const { return Score; }
    int GetLevel() const { return Level; }
    string GetBadge() const { return Badge; }

    void SetName(const string& name) { Name = name; }
    void SetScore(int score) { Score = score; }
    void SetLevel(int level) { Level = level; }
    void SetBadge(const string& badge) { Badge = badge; }

    void saveData() const {
        ofstream outputFile("FileHandling/data.txt", ios::app); // Open file in append mode
        if (outputFile.is_open()) {
            outputFile.seekp(0, ios::end); // Move to the end of the file
            outputFile << Name << ", ";
            outputFile<< to_string(Score) << ", ";
            outputFile<< to_string(Level) << ", ";
            outputFile<< Badge << endl;
            outputFile.close();
            cout << "Data saved successfully!" << endl;
        }
        else {
            cerr << "Unable to open file for writing!" << endl;
        }
    }
    void setCurrentLine(int line) { currentLine = line; }
    int getCurrentLine() const { return currentLine; }


    
    // Function to perform bubble sort on text file data
    void bubbleSortTextFile(const string& filename) {
        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            const int MAX_LINES = 5; // Adjust as needed
            string lines[MAX_LINES];
            int lineCount = 0;
            string line;
            while (getline(inputFile, line) && lineCount < MAX_LINES) {
                lines[lineCount++] = line;
            }
            inputFile.close();

            bubbleSort(lines, lineCount);

            saveSortedData(lines, lineCount, filename);
        }
        else {
            cerr << "Unable to open file for reading: " << filename << endl;
        }
    }

};  
  