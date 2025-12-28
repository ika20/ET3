/**
 * \file game.cpp
 * \brief Dedicated functions of the game container.
 * \author Cedric B.
 * \version 0.1
 * \date 2020-10-19
 *
 * This file contains all functions needed to compute game parameters
 * and display the graphical output
 *
 */


#include <ncurses.h>
#include "ncurses_addons.h"
#include "game.h"
#include "constants.h"
#include "brickshapes.h"
#include "levels.h"

//using namespace std;


void displayBall(int yPos, int xPos)
{
    move(yPos, xPos);
    attron(COLOR_PAIR(WHITE_ON_BLACK));
    printw("@");
    attroff(COLOR_PAIR(WHITE_ON_BLACK));
}

void moveBallVertically(int &yPos, int yDir)
{
    if (yDir == UP)
    {
        yPos = yPos - 1;
    }
    else
    {
        yPos = yPos + 1;
    }
}

bool isCollidingEdges(int pos, int posMin, int posMax)
{
    if ( (pos < posMin) || (pos >= posMax) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void convertCoordinatesToIndexes(int yPos, int xPos, unsigned int &index1, unsigned int &index2){
    index1 = yPos/BRICK_PATTERN_SIZE_Y;
    index2 = xPos/BRICK_PATTERN_SIZE_X;
}

bool isCollidingBrick(int yPos, int xPos, unsigned short tabLvl[TAB_LVL_HEIGHT][TAB_LVL_WIDTH]){
    bool isColliding = false;
    unsigned int index_x;
    unsigned int index_y;
    convertCoordinatesToIndexes(yPos, xPos, index_y, index_x);
    if(0<=index_x && index_x<TAB_LVL_WIDTH && 0<=index_y && index_y<TAB_LVL_HEIGHT){
        if(tabLvl[index_y][index_x]!=4){
            isColliding = true;
        }
    }
    return isColliding;
}

int invertDirection(int currentDir){
    int newDir;

    switch(currentDir){
    case LEFT:
        newDir = RIGHT;
        break;
    case RIGHT:
        newDir = LEFT;
        break;
    case DOWN:
        newDir = UP;
        break;
    case UP:
        newDir = DOWN;
        break;
    default :
        newDir = currentDir;
        break;
    }
    return newDir;
}

void displayBrick(int yPos, int xPos, int brickType){
    unsigned int i;
    for(i=0; i<BRICK_PATTERN_SIZE_Y; i=i+1){
        mvprintw(yPos+i, xPos, "%s", TAB_BRICK_PATTERNS[brickType][i]);
    }

}

void loadTabLevel(unsigned short tabLvl[TAB_LVL_HEIGHT][TAB_LVL_WIDTH], unsigned int lvlNumber){
    if(lvlNumber == 1){
        for(int i=0; i<TAB_LVL_HEIGHT; i+=1){
            for(int j=0; j<TAB_LVL_WIDTH; j+=1){
                tabLvl[i][j] = LEVEL_1[i][j];
            }
        }
    }
    else if(lvlNumber == 2){
        for(int i=0; i<TAB_LVL_HEIGHT; i+=1){
            for(int j=0; j<TAB_LVL_WIDTH; j+=1){
                tabLvl[i][j] = LEVEL_2[i][j];
            }
        }
    }
}

void displayLevel(unsigned short tabLvl[TAB_LVL_HEIGHT][TAB_LVL_WIDTH]){
    int x = 0;
    int y = 0;
    for(int i=0; i<TAB_LVL_HEIGHT; i+=1){

         for(int j=0; j<TAB_LVL_WIDTH; j+=1){
            int b_type=tabLvl[i][j];
            if(b_type>=0 && b_type<=3){
                displayBrick(y, x, b_type);
            }
            x += BRICK_PATTERN_SIZE_X;
        }
        x = 0;
        y += BRICK_PATTERN_SIZE_Y;
    }
}

void updateLevelFromCollision(int yPos, int xPos, unsigned short tabLvl[TAB_LVL_HEIGHT][TAB_LVL_WIDTH]){
    unsigned int index_x;
    unsigned int index_y;
    convertCoordinatesToIndexes(yPos, xPos, index_y, index_x);
    if(tabLvl[index_y][index_x]==0){
        tabLvl[index_y][index_x]=4;
    }
    else if(tabLvl[index_y][index_x]==1){
        tabLvl[index_y][index_x]=0;
    }
}
