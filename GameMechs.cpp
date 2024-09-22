#include <iostream>
#include "GameMechs.h"
#include "MacUILib.h"

void GameMechs::generateFood(objPos blockOff) {

    //generates a random set of food coordinates
    do {
        foodPos.x = rand() % (getBoardSizeX() - 2) + 1;
        foodPos.y = rand() % (getBoardSizeY() - 2) + 1;
        foodPos.symbol = 'O';
    } while (foodPos.isPosEqual(&blockOff)); // generates new food coordinates until it doesn't overlap snake position
}

void GameMechs::getFoodPos(objPos& returnPos) {
    returnPos = foodPos;
}

GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;
    exitFlag = false;
    loseFlag = false;
    score = 0;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = false;
    loseFlag = false;
    score = 0;
}

// do you need a destructor? No, it is not needed. So we commented it out.

// GameMechs::~GameMechs() {
//         // Destructor
// }

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() { 
    return loseFlag; 
}
    
char GameMechs::getInput()
{
    if (MacUILib_hasChar()) {
        input = MacUILib_getChar();
    } 
    return input; 
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag(){ 
    loseFlag = true; 
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

int GameMechs::getScore() { return score; }

void GameMechs::incrementScore() { score++; }
