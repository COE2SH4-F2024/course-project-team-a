#include "SnakeFood.h"
#include <cstdlib>   // For rand()
#include <ctime>     // For time-based randomization

// Constructor
SnakeFood::SnakeFood() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed the random number generator
}

// Method to generate food at random locations, avoiding the player's body
void SnakeFood::generateFood(const objPosArrayList& playerPosList, int boardSizeX, int boardSizeY, int numFood) {
    foodPositions.clear(); // Clear any previous food items

    bool positionValid = false;

    while (foodPositions.size() < numFood) {  // Generate multiple foods
        int x = std::rand() % boardSizeX;  // Random x position
        int y = std::rand() % boardSizeY;  // Random y position

        positionValid = true;

        // Check if the generated position overlaps with the player's body
        for (int i = 0; i < playerPosList.getSize(); ++i) {
            objPos segment = playerPosList.getElement(i);
            if (segment.getX() == x && segment.getY() == y) {
                positionValid = false;  // If overlap, generate new position
                break;
            }
        }

        if (positionValid) {
            foodPositions.push_back(objPos(x, y, 'F'));  // Add the new food position
        }
    }
}

void SnakeFood::generateSpecialFruit(const objPosArrayList& playerPosList, int boardSizeX, int boardSizeY) {
    bool positionValid = false;

    while (!positionValid) {  // Keep generating until position is valid
        int x = std::rand() % boardSizeX;  // Random x position
        int y = std::rand() % boardSizeY;  // Random y position

        positionValid = true;

        // Check if the generated position overlaps with the player's body
        for (int i = 0; i < playerPosList.getSize(); ++i) {
            objPos segment = playerPosList.getElement(i);
            if (segment.getX() == x && segment.getY() == y) {
                positionValid = false;  // If overlap, generate new position
                break;
            }
        }

        if (positionValid) {
            specialFruit = objPos(x, y, 'S');  // Special fruit (different symbol, e.g. 'S')
        }
    }
}

// Getter for the list of food positions (returns a vector of objPos)
std::vector<objPos> SnakeFood::getFoodPositions() const {
    return foodPositions;
}

objPos SnakeFood::getSpecialFruit() const {
    return specialFruit;
}