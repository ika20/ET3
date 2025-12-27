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
    int score = 0;
    int best_scores[4] = {0, 0, 0, 0};


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
    //loadTabLevel(tabLevel, 1);

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
        int menu_bienv_x = 38;
        int menu_bienv_y = 10;
        mvprintw(menu_bienv_y, menu_bienv_x, " ---------------------------------------");
        mvprintw(menu_bienv_y+1, menu_bienv_x, "|          BIENVENUE SUR LE JEU         |");
        mvprintw(menu_bienv_y+2, menu_bienv_x, "|                                       |");
        mvprintw(menu_bienv_y+3, menu_bienv_x, "|   Appuyez sur >> J << pour commencer  |");
        mvprintw(menu_bienv_y+4, menu_bienv_x, " ---------------------------------------");
        refresh();
    }
    //clear();

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
    bool rejouer = true;
    bool retour_menu = true;
    int chosen_lvl;

    while(rejouer){
        if(retour_menu){
            bool choisi = false;
            //wclear(pMainWindow);
            clear();
            refresh();
            while(!choisi){
                if(kbhit()){
                    key = getch();
                    if(key==49){
                        chosen_lvl = 1;
                        choisi = true;
                        //loadTabLevel(tabLevel, 1);
                    }
                    else if(key==50){
                        chosen_lvl = 2;
                        choisi = true;
                        //loadTabLevel(tabLevel, 2);
                    }
                    else if(key==51){
                        chosen_lvl = 3;
                        choisi = true;
                        //loadTabLevel(tabLevel, 3);
                    }
                    else if(key==52){
                        chosen_lvl = 4;
                        choisi = true;
                        //loadTabLevel(tabLevel, 4);
                    }
                }
                int x_menu = 30;
                int y_menu = 7;
                werase(pMainWindow);
                mvprintw(y_menu, x_menu, "                   CHOISISSEZ LE NIVEAU");
                mvprintw(y_menu+1, x_menu, "___________________________________________________________");
                mvprintw(y_menu+2, x_menu, "                  ---------------------- ");
                mvprintw(y_menu+3, x_menu, "                 |   Niveau 1  >> 1 <<  |");
                mvprintw(y_menu+4, x_menu, "                  ---------------------- ");
                mvprintw(y_menu+5, x_menu, "                  ---------------------- ");
                mvprintw(y_menu+6, x_menu, "                 |   Niveau 2  >> 2 <<  |");
                mvprintw(y_menu+7, x_menu, "                  ---------------------- ");
                mvprintw(y_menu+8, x_menu, "                  ---------------------- ");
                mvprintw(y_menu+9, x_menu, "                 |   Niveau 3  >> 3 <<  |");
                mvprintw(y_menu+10, x_menu, "                  ---------------------- ");
                mvprintw(y_menu+11, x_menu, "                  ---------------------- ");
                mvprintw(y_menu+12, x_menu, "                 |   Niveau 4  >> 4 <<  |");
                mvprintw(y_menu+13, x_menu, "                  ---------------------- ");

                refresh();
            }
        }

        loadTabLevel(tabLevel, chosen_lvl);
        lives = 5;
        score = 0;

        //cont = true;
        clear();
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
                            if(score >= 100){
                                score -= 100;
                            }
                            else{
                                score = 0;
                            }
                        }
                        else if(tabLevel[index_y][index_x]==1){
                            score += 20;
                        }
                        else if(tabLevel[index_y][index_x]==0){
                            score += 50;
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
                            if(score >= 100){
                                score -= 100;
                            }
                            else{
                                score = 0;
                            }
                        }

                        else if(tabLevel[index_y][index_x]==1){
                            score += 20;
                        }
                        else if(tabLevel[index_y][index_x]==0){
                            score += 50;
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
                        if(tabLevel[index_y][index_x]==3){
                            lives -= 1;
                            if(score >= 100){
                                score -= 100;
                            }
                            else{
                                score = 0;
                            }
                        }
                        else if(tabLevel[index_y][index_x]==1){
                            score += 20;
                        }
                        else if(tabLevel[index_y][index_x]==0){
                            score += 50;
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

            if(lives==5){
                mvprintw(12, 80, "Life : *****");
            }
            else if(lives==4){
                mvprintw(12, 80, "Life : ****");
            }
            else if(lives==3){
                mvprintw(12, 80, "Life : ***");
            }
            else if(lives==2){
                mvprintw(12, 80, "Life : **");
            }
            else if(lives==1){
                mvprintw(12, 80, "Life : *");
            }
            mvprintw(13, 80, "Score : %d", score);
            /*if(score >= best_scores[chosen_lvl-1]){
                best_scores[chosen_lvl-1] = score;
            }*/
            mvprintw(14, 80, "Best score : %d", best_scores[chosen_lvl-1]);

            refresh();

            //mvprintw(12, 80, "%d lives", lives);

            // refresh window needed to display all the text

            if(lives == 0){
                cont = false;
            }

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
        if(score >= best_scores[chosen_lvl-1]){
            best_scores[chosen_lvl-1] = score;
        }
        bool choix_cont = false;
        //bool retour_menu;
        while(!choix_cont){
            if(kbhit()){
                key = getch();
                if(key==114){
                    cont = true;
                    retour_menu=false;
                    //lives = 5;
                    yBall = 0;
                    xBall = 0;
                    //loadTabLevel(tabLevel, chosen_lvl);
                    choix_cont=true;
                }
                else if(key==109){
                    cont = true;
                    retour_menu=true;
                    //lives = 5;
                    yBall = 0;
                    xBall = 0;
                    choix_cont = true;
                }
                else if(key==113){
                    rejouer=false;
                    choix_cont=true;
                }
            }
            werase(pMainWindow);
            //mvprintw(0, 0, " ---------------------------------------------- ");

            int menu_go_x=30;
            int menu_go_y=5;
            mvprintw(menu_go_y, menu_go_x, "                       GAME OVER");
            mvprintw(menu_go_y+1, menu_go_x, " ____________________________________________________");
            mvprintw(menu_go_y+3, menu_go_x, "                  --> Score : %d", score);
            mvprintw(menu_go_y+4, menu_go_x, "                --> Best Score : %d", best_scores[chosen_lvl-1]);
            //mvprintw(0, 0, "                                                           ");
            mvprintw(menu_go_y+6, menu_go_x, "                   -----------------");
            mvprintw(menu_go_y+7, menu_go_x, "                  |  Retry >> R <<  |");
            mvprintw(menu_go_y+8, menu_go_x, "                   -----------------                        ");
            mvprintw(menu_go_y+9, menu_go_x, "                 ---------------------                     ");
            mvprintw(menu_go_y+10, menu_go_x, "                |  Main Menu >> M <<  |                   ");
            mvprintw(menu_go_y+11, menu_go_x, "                 ---------------------                        ");
            mvprintw(menu_go_y+12, menu_go_x, "                  -------------------                       ");
            mvprintw(menu_go_y+13, menu_go_x, "                 |  Quitter >> Q <<  |                   ");
            mvprintw(menu_go_y+14, menu_go_x, "                  -------------------                        ");





            //box(pMainWindow, 0, 0);
            /*mvprintw(10, 10, "GAME OVER");
            mvprintw(11, 10, "Retry : R");
            mvprintw(12, 10, "Main menu : M");
            mvprintw(13, 10, "Quitter : Q");*/


            refresh();
        }



    }
    /************************************************/
    /*          End of the program                  */
    /************************************************/
    // Close properly ncurses


    endwin();

    return EXIT_SUCCESS;
}
