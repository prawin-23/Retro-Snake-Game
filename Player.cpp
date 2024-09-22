#include "Player.h"
#include "GameMechs.h"
#include "MacUILib.h"
#include "objPosArrayList.h"

#define DELAY_CONST 1000000

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
   
    playerPos.symbol = '*';
    playerPosList = new objPosArrayList();
    playerPosList -> getHeadElement(playerPos);
    
    // the player is initially stationary
    myDir = STOP;

}


Player::~Player()
{
    delete mainGameMechsRef;

    // delete any heap members here
}

objPosArrayList* Player::getPlayerPos()
{
    // returns the reference to the playerPos arrray list
    return playerPosList;
}

void Player::increasePlayerLength(){
    // gets the current head position of the player
    objPos headPos;
    playerPosList->getHeadElement(headPos);

    // creating a new position for the new head
    objPos newHeadPos;

    // checks the direction of the player
    // determines where the new head of the snake will be added (based on the direction)
    switch (myDir) {
        //creating a set of coordinates for the new head
        case UP:
            newHeadPos.x = headPos.x;
            newHeadPos.y = headPos.y - 1;
            break;
        case DOWN:
            newHeadPos.x = headPos.x;
            newHeadPos.y = headPos.y + 1;
            break;
        case LEFT:
            newHeadPos.x = headPos.x - 1;
            newHeadPos.y = headPos.y;
            break;
        case RIGHT:
            newHeadPos.x = headPos.x + 1;
            newHeadPos.y = headPos.y;
            break;
        default:
            // if current direction isnt set (e.g. stationary), do nothing
            return;
    }

    // adds the new head position to the front of the player's position list
    playerPosList->insertHead(newHeadPos);
}

bool Player::checkSelfCollision(){
    objPos playerHead;
    playerPosList->getHeadElement(playerHead);

    // iterate through the player's body segments (excluding the head)
  
    for (int i = 2; i < playerPosList->getSize(); i++) {
        objPos playerSegment;
        playerPosList->getElement(playerSegment, i);

        // checks if the head position matches any body segment
        if ( playerHead.x == playerSegment.x && playerHead.y == playerSegment.y) {
            return true; // self-collision detected
        }
    }

    return false; 
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    bool exitFlag = mainGameMechsRef->getExitFlagStatus();

    if (input != 0) // if not null character
    {
        // PPA3 input processing logic

        switch (input)
        {
            case ' ': // exit
                mainGameMechsRef->setExitTrue();
                break;

            case 'W':
            case 'w':
                if (myDir != DOWN)
                {
                    myDir = UP;
                }
                break;
            case 'S':
            case 's':
                if (myDir != UP)
                {
                    myDir = DOWN;
                }
                break;
            case 'A':
            case 'a':
                if (myDir != RIGHT)
                {
                    myDir = LEFT;
                }
                break;
            case 'D':
            case 'd':
                if (myDir != LEFT)
                {
                    myDir = RIGHT;
                }
                break;
            default:
                myDir = INITIAL;
                break;
        }
        input = 0;
    }        
}

void Player::movePlayer()
{
    //declaring variables
    //will be needed for wraparound function
    int height = mainGameMechsRef->getBoardSizeY();
    int width = mainGameMechsRef->getBoardSizeX();

    //checks for collision
    if (checkSelfCollision()){
        mainGameMechsRef -> setExitTrue();
        mainGameMechsRef->setLoseFlag();
    }

    // PPA3 Finite State Machine logic
    if (myDir != INITIAL)
    {
        switch (myDir)
        {
            case UP:
                if (playerPos.y > 1) {
                    playerPos.y--;
                    // movement logic for snake (used for all cases)
                    playerPosList->insertHead(playerPos);
                    playerPosList->removeTail();
                }
                //wraparound implementation
                //if snake reaches top of the board, it will set the snake position back to bottom
                else {
                    playerPos.y = height - 2;
                }
                //this wraparound logic is used for all cases below in a similar manner
                break;
            case DOWN:
                if (playerPos.y < height - 2) {
                    playerPos.y++;
                    playerPosList->insertHead(playerPos);
                    playerPosList->removeTail();
                }
                else {
                    playerPos.y = 1;
               
                }
                break;
            case LEFT:
                if (playerPos.x > 1) {
                    playerPos.x--;
                    playerPosList->insertHead(playerPos);
                    playerPosList->removeTail();
                }
                else {
                    playerPos.x = width - 2;
                }
                break;
            case RIGHT:
                if (playerPos.x < width - 2) {
                    playerPos.x++;
                    playerPosList->insertHead(playerPos);
                    playerPosList->removeTail();
                    
                }
                else {
                    playerPos.x = 1;
                }
                break;
            default:
                break;
        }
    }
}
