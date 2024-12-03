#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"
#include "SnakeFood.h"

using namespace std;

#define DELAY_CONST 50000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

GameMechs gameMechs;  // Global gameMechs object
Player player(&gameMechs);  // Player object initialized with gameMechs reference
SnakeFood food;

int main(void)
{
    Initialize();

    while (!exitFlag)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }
    
    CleanUp();
    //MacUILib_printf("GAME OVER3\n");
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    exitFlag = false;
    

    // Initialize food generation with the entire player body and board size
    food.generateFood(*player.getPlayerPosList(), gameMechs.getBoardSizeX(), gameMechs.getBoardSizeY(), 3); // Generate regular food
    food.generateSpecialFruit(*player.getPlayerPosList(), gameMechs.getBoardSizeX(), gameMechs.getBoardSizeY()); // Generate special fruit
}


void GetInput(void)
{
    // Update the input in GameMechs
    gameMechs.setInput('\0');  // Poll for input

    // Check for 'q' to quit the game
    if (gameMechs.getInput() == 'q') {
        exitFlag = true;  // Set exit flag to end the game
        return;  // Skip further input handling
    }

    // Pass input to the player
    player.updatePlayerDir();
}

void RunLogic(void) {
    // Move the player based on the updated direction and handle food consumption
    player.movePlayer(food);  // Pass food so that the snake can grow if it eats food

    
    // Check for collision with the snake's body
    if (player.detectCollision()) {
        exitFlag = true;  // End the game if a collision occurs
    }
}

void DrawScreen(void) {
    MacUILib_clearScreen();  // Clear the screen to start fresh

    // Get the board width and height from GameMechs
    int boardWidth = gameMechs.getBoardSizeX();
    int boardHeight = gameMechs.getBoardSizeY();

    // Draw the top border
    for (int x = 0; x < boardWidth; ++x) {
        MacUILib_printf("#");
    }
    MacUILib_printf("\n");

    // Draw the board contents
    for (int y = 1; y < boardHeight - 1; ++y) {
        MacUILib_printf("#");  // Left border

        for (int x = 1; x < boardWidth - 1; ++x) {
            bool drawn = false;

            // Check for snake body
            for (int i = 0; i < player.getPlayerPosList()->getSize(); ++i) {
                objPos segment = player.getPlayerPosList()->getElement(i);
                if (segment.getX() == x && segment.getY() == y) {
                    MacUILib_printf("*");  // Snake body part
                    drawn = true;
                    break;
                }
            }

            if (!drawn) {
                // Check for special fruit
                objPos specialFruit = food.getSpecialFruit();
                if (specialFruit.getX() == x && specialFruit.getY() == y) {
                    MacUILib_printf("X");  // Special fruit
                    drawn = true;
                }
            }

            if (!drawn) {
                // Check for regular food
                objPosArrayList* foodPositions = food.getFoodPositions();
                for (int i = 0; i < foodPositions->getSize(); ++i) {
                    objPos foodPos = foodPositions->getElement(i);
                    if (foodPos.getX() == x && foodPos.getY() == y) {
                        MacUILib_printf("@");  // Regular food
                        drawn = true;
                        break;
                    }
                }
            }

            if (!drawn) {
                MacUILib_printf(" ");  // Emptyp space
            }
        }

        MacUILib_printf("#\n");  // Right border
    }

    // Draw the bottom border
    for (int x = 0; x < boardWidth; ++x) {
        MacUILib_printf("#");
    }
    MacUILib_printf("\n");

    // Display the score
    MacUILib_printf("Score: %d\n", gameMechs.getScore());
    MacUILib_printf("@ - Regular Fruit: Increases snake length by 1 and score by 1.\n");
    MacUILib_printf("X - Special Fruit: Halves snake length and increases score by 5.\n\n");
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST);  // Control game speed 
}

void CleanUp(void)
{
    MacUILib_clearScreen();
    int finalScore = gameMechs.getScore();
    int snakeLength = player.getPlayerPosList()->getSize();

    MacUILib_printf("GAME OVER\n");
    MacUILib_printf("Final Score: %d\n", finalScore);
    MacUILib_printf("Snake Length: %d\n", snakeLength);


    MacUILib_uninit();
}
