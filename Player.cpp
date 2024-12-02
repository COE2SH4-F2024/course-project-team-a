#include "Player.h"
#include "MacUILib.h"
#include <iostream>

// Constructor
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
    // Check if a key is available
    
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

    // Finite State Machine logic for movement
    switch (myDir) {
    case UP:    --newY; break;
    case DOWN:  ++newY; break;
    case LEFT:  --newX; break;
    case RIGHT: ++newX; break;
    case STOP:  return;  // If the snake is stopped, don't move
    }

    // **Wrap-around logic for horizontal (X) direction**:
    if (newX < 0) {
        newX = mainGameMechsRef->getBoardSizeX() - 1;  // Wrap from left to right
    } else if (newX >= mainGameMechsRef->getBoardSizeX()) {
        newX = 0;  // Wrap from right to left
    }

    // **Wrap-around logic for vertical (Y) direction**:
    if (newY < 0) {
        newY = mainGameMechsRef->getBoardSizeY() - 1;  // Wrap from top to bottom
    } else if (newY >= mainGameMechsRef->getBoardSizeY()) {
        newY = 0;  // Wrap from bottom to top
    }

    // Check if the snake's head moves on top of any food
    bool ateFood = false;
    std::vector<objPos> foodPositions = food.getFoodPositions();  // Get all food positions
    for (const auto& foodPos : foodPositions) {
        if (newX == foodPos.getX() && newY == foodPos.getY()) {
            ateFood = true;
            break;
        }
    }

    // Check if the snake's head moves on top of the special fruit
    bool ateSpecialFruit = false;
    objPos specialFruit = food.getSpecialFruit();  // Get the special fruit position
    if (newX == specialFruit.getX() && newY == specialFruit.getY()) {
        ateSpecialFruit = true;
    }

    // Insert the new head at the front of the snake
    playerPosList->insertHead(objPos(newX, newY, '*'));

    // If food is eaten, don't remove the tail (snake grows)
    if (!ateFood && !ateSpecialFruit) {
    playerPosList->removeTail();  // Normal movement (no growth)
} else {
    if (ateFood) {
        // Regenerate food
        food.generateFood(*playerPosList, mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY(), 3);  // Generate 3 new food items
        mainGameMechsRef->incrementScore();  // Increment score by 1 for regular food
    }

    if (ateSpecialFruit) {
        // Halve the snake's length
        int newSize = std::max(1, playerPosList->getSize() / 2);  // Ensure minimum size of 1
        while (playerPosList->getSize() > newSize) {
            playerPosList->removeTail();  // Remove the tail to shrink the snake
        }

        // Increment the score by 5 for special fruit
        for (int i = 0; i < 5; ++i) {
            mainGameMechsRef->incrementScore();
        }

        // Regenerate the special fruit
        food.generateSpecialFruit(*playerPosList, mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY());

        std::cout << "Special fruit eaten! Score: " << mainGameMechsRef->getScore() << std::endl;  // Debugging
    }
}   
}



/*void Player::grow() {
    if (playerPosList->getSize() > 0) {
        // Get the current tail segment
        objPos tail = playerPosList->getElement(playerPosList->getSize() - 1);

        // Add a new segment at the same position as the current tail
        playerPosList->insertTail(tail);
    }
}*/


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

// Handle food consumption (grow the snake and generate new food)
/*void Player::eatFood(SnakeFood& food) {
    objPos headPos = getPlayerPos();  // Get the current position of the snake's head

    // Check if the snake's head is at the food's position
    if (headPos.isPosEqual(&food.getFoodPos())) {
        grow();  // Grow the snake
        mainGameMechsRef->incrementScore();  // Optional: Increase score
        food.generateFood(*getPlayerPosList(), mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY());  // Generate new food
    }
}*/

// Get the player's position list
objPosArrayList* Player::getPlayerPosList() const {
    return playerPosList;  // Return the player's position list
}
