#ifndef SNAKEFOOD_H
#define SNAKEFOOD_H

#include "objPos.h"
#include "objPosArrayList.h"  // Needed to access the player's body
#include <vector>  // To store multiple food positions

class SnakeFood {
private:
    std::vector<objPos> foodPositions; // Store multiple food positions
     objPos specialFruit;

public:
    SnakeFood();  // Constructor to initialize the food object

    // Methods
    void generateFood(const objPosArrayList& playerPosList, int boardSizeX, int boardSizeY, int numFood); // Generate multiple foods
    void generateSpecialFruit(const objPosArrayList& playerPosList, int boardSizeX, int boardSizeY); // Generate special fruit
    std::vector<objPos> getFoodPositions() const;  // Returns the list of food positions
    objPos getSpecialFruit() const;  // Return the special fruit position
};

#endif // SNAKEFOOD_H
