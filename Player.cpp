#include "Player.h"
#include "MacUILib.h"
#include <iostream>
#include <algorithm> // For std::max


Player::Player(GameMechs* thisGMRef) {
    mainGameMechsRef = thisGMRef;  // Initialize the reference to GameMechs
    myDir = STOP;

    playerPosList = new objPosArrayList();  // Initialize the position list

    // Initialize the snake in the center of the board
    int startX = mainGameMechsRef->getBoardSizeX() / 2;
    int startY = mainGameMechsRef->getBoardSizeY() / 2;

    // Insert initial snake's head position into the player position list
    playerPosList->insertHead(objPos(startX, startY, '*'));
}

// Destructor
Player::~Player() {
    delete playerPosList;
}

// Get the current position of the player's head
objPos Player::getPlayerPos() const {
    return playerPosList->getHeadElement();
}

// Update the player's direction based on user input
void Player::updatePlayerDir() {
    char input = mainGameMechsRef->getInput();  // Get user input

    // Update the direction based on input
    if (input == 'w' && myDir != DOWN) myDir = UP;
    else if (input == 's' && myDir != UP) myDir = DOWN;
    else if (input == 'a' && myDir != RIGHT) myDir = LEFT;
    else if (input == 'd' && myDir != LEFT) myDir = RIGHT;
    else if (input == 'p') myDir = STOP;
}

// Move the player (snake) based on the current direction
void Player::movePlayer(SnakeFood& food) {
    objPos head = playerPosList->getHeadElement();  // Get the current head position
    int newX = head.getX();
    int newY = head.getY();

    // Movement logic
    switch (myDir) {
    case UP:    --newY; break;
    case DOWN:  ++newY; break;
    case LEFT:  --newX; break;
    case RIGHT: ++newX; break;
    case STOP:  return;
    }

    // Wrap-around logic
    if (newX < 0) newX = mainGameMechsRef->getBoardSizeX() - 1;
    if (newX >= mainGameMechsRef->getBoardSizeX()) newX = 0;
    if (newY < 0) newY = mainGameMechsRef->getBoardSizeY() - 1;
    if (newY >= mainGameMechsRef->getBoardSizeY()) newY = 0;

    // Check if the snake eats any fruit 
    bool ateFood = false;
    bool ateSpecialFruit = false;
    

    objPosArrayList* foodPositions = food.getFoodPositions();
    for (int i = 0; i < foodPositions->getSize(); ++i) {
        objPos foodPos = foodPositions->getElement(i);
        if (newX == foodPos.getX() && newY == foodPos.getY()) {
            ateFood = true;
            break;
        }
    }

    objPos specialFruit = food.getSpecialFruit();
    if (newX == specialFruit.getX() && newY == specialFruit.getY()) {
        ateSpecialFruit = true;
    }

    

    // Insert the new head at the front of the snake
    playerPosList->insertHead(objPos(newX, newY, '*'));

    // Handle growth or shrinking based on fruit
    if (!ateFood && !ateSpecialFruit) {
        playerPosList->removeTail();
    } else {
        if (ateFood) {
            food.generateFood(*playerPosList, mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY(), 3);
            mainGameMechsRef->incrementScore();
        }

        if (ateSpecialFruit) {
            int newSize = std::max(1, playerPosList->getSize() / 2);
            while (playerPosList->getSize() > newSize) {
                playerPosList->removeTail();
            }
            for (int i = 0; i < 5; ++i) mainGameMechsRef->incrementScore();
            food.generateSpecialFruit(*playerPosList, mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY());
        }

       
    }
}


// Check if the player collides with its own body
bool Player::detectCollision() const {
    objPos head = playerPosList->getHeadElement();
    for (int i = 1; i < playerPosList->getSize(); ++i) {
        if (head.isPosEqual(&playerPosList->getElement(i))) {
            return true;  // Collision detected with the body
        }
    }
    return false;
}

// Get the player's position list
objPosArrayList* Player::getPlayerPosList() const {
    return playerPosList;  // Return the player's position list
}
