#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "SnakeFood.h"

class Player
{
public:
    // Enum for movement directions (including stop for pausing)
    enum Dir { UP, DOWN, LEFT, RIGHT, STOP };

    // Constructor that takes a reference to the GameMechs object
    Player(GameMechs* thisGMRef);

    // Destructor
    ~Player();

    // Get the current position of the player's head
    objPos getPlayerPos() const;

    // Update the player's direction based on user input
    void updatePlayerDir();

    // Move the player (snake) based on the current direction and handle growth if food is eaten
    void movePlayer(SnakeFood& food);

    // Check if the player collides with its own body
    bool detectCollision() const;

    // Getter for the player's position list (snake body)
    objPosArrayList* getPlayerPosList() const;

    // Optional: Add a getter for direction if needed
    Dir getDirection() const { return myDir; }

private:
    objPosArrayList* playerPosList;   // Tracks all body segments of the snake
    Dir myDir;                         // Current direction of movement
    GameMechs* mainGameMechsRef;       // Reference to the main game mechanics (GameMechs)
   
};

#endif // PLAYER_H
