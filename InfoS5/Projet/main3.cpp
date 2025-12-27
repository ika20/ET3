/**
 * \file main.cpp
 * \brief Main function container
 * \author Cedric B.
 * \version 0.1
 * \date 2020-10-19
 *
 * Program launcher with game architecture skeleton
 *
 */

#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include "ncurses_addons.h"
#include "constants.h"
#include "game.h"


/**
 * \brief Main function: entry point of the program
 *
 * \return EXIT_SUCCESS if all went good, EXIT_FAILURE otherwise.
 */
int main(void)
{
    /************************************************/
    /*          Variables declarations              */
    /************************************************/
    bool cont;
    int key;
    // For game timing
    clock_t currentTime, previousTime;
    double deltaT;
    // Ball movements
    int xBall, yBall, yDirBall;
    int xBallTemp, yBallTemp;
    // Level container
    unsigned short tabLevel[TAB_LVL_HEIGHT][TAB_LVL_WIDTH];
    // Window parameters
    int windowHeight, windowWidth, gameZoneHeight, gameZoneWidth;
    WINDOW* pMainWindow;
    int lives = 5;


    /************************************************/
    /*          ncurses initialization              */
    /************************************************/
    pMainWindow = init_ncurses();
    curs_set(0); // Set cursor invisible
    keypad(pMainWindow, true); // Enable arrows and special keys on keyboard


    /************************************************/
    /*          Beginning of the program            */
    /************************************************/
    /* Window and game zone characteristics */
    getmaxyx(pMainWindow, windowHeight, windowWidth);
    gameZoneHeight = TAB_LVL_HEIGHT * BRICK_PATTERN_SIZE_Y;
    gameZoneWidth = TAB_LVL_WIDTH * (BRICK_PATTERN_SIZE_X + 1);
    /* Ball initial positioning */
    xBall = 1;
    yBall = 1;
    yDirBall = DOWN;

    /* Level initializing */
    loadTabLevel(tabLevel, 1);

    /* Game main loop */
    // First initialization before looping
    previousTime = clock();

    /*initscr();
    mvprintw(1, 1, "Entrez j pour jouer");
    if(kbhit()){
        key = getch();
        if(key == 106){
            cont = true;
        }
        else{
            cont = false;
        }
    }*/

    bool commence = false;
    while(!commence){
        if(kbhit()){
            key = getch();
            if(key==106){
                commence = true;
            }
        }
        werase(pMainWindow);
        mvprintw(1, 1, "Entrez 'j' pour commencer");
        refresh();
    }
    clear();

    /*bool nvchoisi = false;
    while(!nvchoisi){
        if(kbhit()){
            key = getch();
            if(key==49){
                nvchoisi = true;
            }
        }
        werase(pMainWindow);
        mvprintw(1, 1, "Choisissez un niveau");
        refresh();
    }
    clear();*/


    cont = true;
    while(cont){


        /* Keyboard handling */
        if(kbhit()){
            key = getch();
            switch(key){
            case 27: // Escape key code
                cont = false;
                break;
            case KEY_LEFT:
                xBallTemp = xBall;
                xBallTemp -= 1;
                if(!isCollidingEdges(xBallTemp, 0, gameZoneWidth) && !isCollidingBrick(yBall, xBallTemp, tabLevel)){
                    xBall = xBallTemp;
                }
                else if(isCollidingBrick(yBall, xBallTemp, tabLevel)){
                    unsigned int index_x;
                    unsigned int index_y;
                    convertCoordinatesToIndexes(yBall, xBallTemp, index_y, index_x);
                    if(tabLevel[index_y][index_x]==3){
                        lives -= 1;
                    }
                    updateLevelFromCollision(yBall, xBallTemp, tabLevel);
                }
                break;
            case KEY_RIGHT:
                xBallTemp = xBall;
                xBallTemp += 1;
                if(!isCollidingEdges(xBallTemp, 0, gameZoneWidth) && !isCollidingBrick(yBall, xBallTemp, tabLevel)){
                    xBall = xBallTemp;
                }
                 else if(isCollidingBrick(yBall, xBallTemp, tabLevel)){
                    unsigned int index_x;
                    unsigned int index_y;
                    convertCoordinatesToIndexes(yBall, xBallTemp, index_y, index_x);
                    if(tabLevel[index_y][index_x]==3){
                        lives -= 1;
                    }
                    updateLevelFromCollision(yBall, xBallTemp, tabLevel);
                }
                break;
            default:
                break;
            }
        }

        /* Game parameters periodic actualization */
        currentTime = clock();
        // Elapsed time from previous actualization, in milliseconds
        deltaT = (currentTime - previousTime) * 1000 / CLOCKS_PER_SEC;
        if (deltaT > UPDATE_DELAY_MS){
            previousTime = currentTime;

            // Simulate the next move
            yBallTemp = yBall;
            moveBallVertically(yBallTemp, yDirBall);
            // Is next move valid ?
            if (!isCollidingEdges(yBallTemp, 0, gameZoneHeight) && !isCollidingBrick(yBallTemp, xBall, tabLevel)){
                yBall = yBallTemp;
            }
            else{
                if(isCollidingBrick(yBallTemp, xBall, tabLevel)){
                    unsigned int index_x;
                    unsigned int index_y;
                    convertCoordinatesToIndexes(yBallTemp, xBall, index_y, index_x);
                    if(tabLevel[index_y][index_x]){
                        lives -= 1;
                    }
                    updateLevelFromCollision(yBallTemp, xBall, tabLevel);
                }
                yDirBall = invertDirection(yDirBall);
            }
        }

        /* Graphical update */
        // Clear window
        werase(pMainWindow);
        // Display game elements
        displayLevel(tabLevel);
        displayBall(yBall, xBall);

        mvprintw(12, 80, "%d lives", lives);

        // refresh window needed to display all the text
        refresh();


        /*unsigned int indexx;
        unsigned int indexy;
        convertCoordinatesToIndexes(yBall, xBall, indexy, indexx);
        mvprintw(10, 80, "x : %d ; y : %d", xBall, yBall);
        mvprintw(11, 80, "index x : %d ; index y : %d", indexx, indexy);*/

        /*mvprintw(10, 80, "x : %d ; y : %d", xBall, yBall);
        if(isCollidingBrick(yBall, xBall, tabLevel)){
            mvprintw(12, 80, "COLLISION");
        }
        else{
            mvprintw(12, 80, "NO COLLISION");
        }*/
    }

    /************************************************/
    /*          End of the program                  */
    /************************************************/
    // Close properly ncurses


    endwin();

    return EXIT_SUCCESS;
}
