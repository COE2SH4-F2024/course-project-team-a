#ifndef SNAKEFOOD_H
#define SNAKEFOOD_H

#include "objPos.h"
#include "objPosArrayList.h"

class SnakeFood {
private:
    objPosArrayList foodPositions;  // Regular food positions
    objPos specialFruit;            // Special fruit that shrinks the snake
    

public:
    SnakeFood();  // Constructor

    void generateFood(const objPosArrayList& playerPosList, int boardSizeX, int boardSizeY, int numFood);
    void generateSpecialFruit(const objPosArrayList& playerPosList, int boardSizeX, int boardSizeY);


    objPosArrayList* getFoodPositions();  // Get regular food positions
    objPos getSpecialFruit() const;       // Get special fruit position
    
};

#endif // SNAKEFOOD_H
