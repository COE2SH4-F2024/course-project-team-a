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
    MacUILib_printf("GAME OVER\n");
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
        MacUILib_printf("GAME OVER\n");
        exitFlag = true;  // Set exit flag to end the game
    }

    // Pass input to the player
    player.updatePlayerDir();
}

void RunLogic(void) {
    // Move the player based on the updated direction and handle food consumption
    player.movePlayer(food);  // Pass food so that the snake can grow if it eats food

    // Check for collision with the snake's body
    if (player.detectCollision()) {
        MacUILib_printf("GAME OVER\n");
        exitFlag = true;  // End the game if a collision occurs
    }
}

void DrawScreen(void) {
    MacUILib_clearScreen();  // Clear the screen to start fresh

    // Get the board width and height from GameMechs
    int boardWidth = gameMechs.getBoardSizeX();  // Use gameMechs directly
    int boardHeight = gameMechs.getBoardSizeY();  // Use gameMechs directly

    // Draw the top border
    for (int x = 0; x < boardWidth; ++x) {
        MacUILib_printf("#");
    }
    MacUILib_printf("\n");

    // Draw the body of the board (between top and bottom borders)
    for (int y = 1; y < boardHeight - 1; ++y) {
        MacUILib_printf("#");

        for (int x = 1; x < boardWidth - 1; ++x) {
            bool drawn = false;

            // Check if this position has the snake
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
                objPos specialFruit = food.getSpecialFruit();  // Get special fruit position
                if (specialFruit.getX() == x && specialFruit.getY() == y) {
                    MacUILib_printf("X");  // Special fruit
                    drawn = true;
                }
            }

            if (!drawn) {
                // Check for regular food items
                std::vector<objPos> foodPositions = food.getFoodPositions();
                for (const auto& foodPos : foodPositions) {
                    if (foodPos.getX() == x && foodPos.getY() == y) {
                        MacUILib_printf("@");  // Regular food
                        drawn = true;
                        break;
                    }
                }
            }

            if (!drawn) {
                MacUILib_printf(" ");  // Empty space
            }
        }

        MacUILib_printf("#\n");
    }

    // Draw the bottom border
    for (int x = 0; x < boardWidth; ++x) {
        MacUILib_printf("#");
    }
    MacUILib_printf("\n");

    // Display the score at the top right corner
    MacUILib_printf("Score: %d\n", gameMechs.getScore());  // Access score directly from gameMechs
}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay to control game speed
}

void CleanUp(void)
{
    MacUILib_clearScreen();
    MacUILib_uninit();
}
