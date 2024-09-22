#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#define WIDTH 30
#define HEIGHT 15

using namespace std;

#define DELAY_CONST 100000

//initializes exit flag
bool exitFlag = false;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

GameMechs *gameMechs = new GameMechs();

//declares variables for use
Player *player = new Player(gameMechs); 
objPos playerElement{0, 0, 0};
objPosArrayList *playerPos;
objPos foodPos;

int main(void)
{
    Initialize();

    // game keeps on running until either the exit command (space bar) is pressed or the player loses
    while (!gameMechs->getExitFlagStatus())
    {
        // updates food position for every frame/loop
        gameMechs->getFoodPos(foodPos);

        //goes through the functions for each frame (loop)
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();

        // custom end game message
        if (gameMechs->getExitFlagStatus())
        {
            cout << "Game Over! Thank you for playing :)" << endl;
        }
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // initially generates food on board at random position
    exitFlag = gameMechs->getExitFlagStatus();
    gameMechs->generateFood(foodPos);
    gameMechs->getFoodPos(foodPos);
}

void GetInput(void)
{
    // gets input from user and stores it
    gameMechs->clearInput();
    char input = gameMechs->getInput();
    gameMechs->setInput(input);
}

void RunLogic(void)
{
    //updates direction for every frame (loop)
    player->updatePlayerDir();
    player->movePlayer();

    objPosArrayList *playerPosList = player->getPlayerPos(); // get the playerPosList

    objPos headPos;
    playerPosList->getHeadElement(headPos);

    // checks if player and food collides
    // executes the if statement when true
    if (headPos.isPosEqual(&foodPos))
    {
        gameMechs->generateFood(foodPos); // generates a new food position
        gameMechs->getFoodPos(foodPos);
        gameMechs->incrementScore(); // adds +1 to score
        player->increasePlayerLength(); // increases snake length

    }
}

void DrawScreen(void)
{
    // prints and updates score (for every loop)
    cout << "Current Score: " << gameMechs->getScore() << endl;

    //prints rest of screen elements
    cout << "==============================" << endl;
    cout << "Prawin & Aun's Final Project" << endl;
    cout << "==============================" << endl;
    cout << "Board Size: " << gameMechs->getBoardSizeX() << " X " << gameMechs->getBoardSizeY() << endl;

    // Clears screen for every loop (frame)
    MacUILib_clearScreen();

    //declaring and initializing variables which will be used
    objPosArrayList *drawBoardList = player->getPlayerPos();
    objPos currentIndex;
    objPos drawBoard{0, 0, 0};

    //boolean which checks if each element on game board has been printed (except spaces)
    //initially set to false
    bool hasRun = false;

    for (drawBoard.y = 0; drawBoard.y < HEIGHT; (drawBoard.y)++)
    {
        for (drawBoard.x = 0; drawBoard.x < WIDTH; (drawBoard.x)++)
        {
            hasRun = false;

            //trints board outline
            if (drawBoard.x == 0 || drawBoard.x == WIDTH - 1 || drawBoard.y == 0 || drawBoard.y == HEIGHT - 1 && hasRun == false)
            {
                MacUILib_printf("%c", '#');
                //sets to true to avoid repeating
                hasRun = true;
            }

            // Prints the food position
            else if (drawBoard.isPosEqual(&foodPos) && hasRun == false)
            {
                MacUILib_printf("%c", foodPos.getSymbol());
                hasRun = true;
            }

            // prints the snake (goes through each symbol in array list)
            for (int i = 0; i < drawBoardList->getSize(); i++)
            {
                drawBoardList->getElement(currentIndex, i);
                if (drawBoard.isPosEqual(&currentIndex) && hasRun == false)
                {
                    MacUILib_printf("%c", currentIndex.getSymbol());
                    hasRun = true;
                }
            }

            // prints spaces for the rest of the items in the game board
            if (drawBoard.x >= 1 && drawBoard.y < HEIGHT - 1 && hasRun == false)
            {
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("%c", '\n');
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    //MacUILib_clearScreen();

    MacUILib_uninit();
}