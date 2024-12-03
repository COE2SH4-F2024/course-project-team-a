#include "GameMechs.h"
#include "MacUILib.h"
#include <iostream>

// Default Constructor
GameMechs::GameMechs()
    : input('\0'), exitFlag(false), loseFlag(false), score(0), boardSizeX(30), boardSizeY(15) {}

// Parameterized Constructor
GameMechs::GameMechs(int boardX, int boardY)
    : input('\0'), exitFlag(false), loseFlag(false), score(0), boardSizeX(boardX), boardSizeY(boardY) {}

// Destructor
GameMechs::~GameMechs() {}

// Getter for exit flag
bool GameMechs::getExitFlagStatus() const {
    return exitFlag;
}

// Setter to mark the game for exiting
void GameMechs::setExitTrue() {
    exitFlag = true;
}

// Getter for lose flag
bool GameMechs::getLoseFlagStatus() const {
    return loseFlag;
}

// Setter to mark the game as lost
void GameMechs::setLoseFlag() {
    loseFlag = true;
}

// Getter for user input
char GameMechs::getInput()  {
    if (MacUILib_hasChar()) {  // Only process if input is available
        input = MacUILib_getChar();  // Capture the latest input
        std::cout << "Input received: " << input << std::endl;  // Debugging the input
    }
    return input;
}

// Actively poll for input
void GameMechs::setInput(char this_input) {
    if (MacUILib_hasChar()) {  // Only process if input is available
        input = MacUILib_getChar();  // Capture the latest input
        std::cout << "Input received: " << input << std::endl;  // Debugging the input
    }
}

// Clears the input field
void GameMechs::clearInput() {
    input = '\0';  // Clear the input field after processing 
} 

// Getter for current score
int GameMechs::getScore() const {
    return score;
}

// Increment the score by 1 (can be extended for variable increments)
void GameMechs::incrementScore() {
    score++;  // Increment the score by 1
}


// Getter for board size X
int GameMechs::getBoardSizeX() const {
    return boardSizeX;
}

// Getter for board size Y
int GameMechs::getBoardSizeY() const {
    return boardSizeY;
}
