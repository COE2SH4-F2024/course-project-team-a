#include "SnakeFood.h"
#include <cstdlib>
#include <ctime>

// Constructor
SnakeFood::SnakeFood() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed RNG
}

// Generate multiple food items within the valid area
void SnakeFood::generateFood(const objPosArrayList& playerPosList, int boardSizeX, int boardSizeY, int numFood) {
    // Clear existing food positions
    while (foodPositions.getSize() > 0) {
        foodPositions.removeTail();
    }

    while (foodPositions.getSize() < numFood) {  // Generate multiple foods
        int x = std::rand() % (boardSizeX - 2) + 1;  // Ensure x is in [1, boardSizeX - 2]
        int y = std::rand() % (boardSizeY - 2) + 1;  // Ensure y is in [1, boardSizeY - 2]

        bool positionValid = true;

        // Check if the generated position overlaps with the player's body
        for (int i = 0; i < playerPosList.getSize(); ++i) {
            objPos segment = playerPosList.getElement(i);
            if (segment.getX() == x && segment.getY() == y) {
                positionValid = false;  // Invalid position
                break;
            }
        }

        if (positionValid) {
            foodPositions.insertTail(objPos(x, y, '@'));  // Add valid food position
        }
    }
}

// Generate a special fruit within the valid area
void SnakeFood::generateSpecialFruit(const objPosArrayList& playerPosList, int boardSizeX, int boardSizeY) {
    bool positionValid = false;

    while (!positionValid) {
        int x = std::rand() % (boardSizeX - 2) + 1;  // Ensure x is in [1, boardSizeX - 2]
        int y = std::rand() % (boardSizeY - 2) + 1;  // Ensure y is in [1, boardSizeY - 2]

        positionValid = true;

        // Check if the position overlaps with the player's body
        for (int i = 0; i < playerPosList.getSize(); ++i) {
            objPos segment = playerPosList.getElement(i);
            if (segment.getX() == x && segment.getY() == y) {
                positionValid = false;  // Invalid position
                break;
            }
        }

        if (positionValid) {
            specialFruit = objPos(x, y, 'X');  // Assign position to special fruit
        }
    }
}



// Getter for the food positions
objPosArrayList* SnakeFood::getFoodPositions() {
    return &foodPositions;
}

// Getter for the special fruit position
objPos SnakeFood::getSpecialFruit() const {
    return specialFruit;
}
