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
    bool pause=false;


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
        int menu_bienv_y = 11;
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
    bool win = false;
    bool param = false;

    while(rejouer){
        if(retour_menu){
            bool choisi = false;
            param = false;
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
                    else if(key == 99){
                        //cont = false;
                        param = true,
                        choisi = true;
                    }
                }
                int x_menu = 30;
                int y_menu = 5;
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
                mvprintw(y_menu+17, x_menu, "            ..................................");
                mvprintw(y_menu+18, x_menu, "            :  Game rules & controls >> C << :");
                mvprintw(y_menu+19, x_menu, "            :................................:");


                refresh();
            }
        }

        if(param){
            bool exit_param = false;
            while(!exit_param){
                if(kbhit()){
                    key = getch();
                    if(key == 109){
                        exit_param = true;
                    }
                }
                werase(pMainWindow);
                int menu_param_x = 25;
                int menu_param_y = 2;
                mvprintw(menu_param_y, menu_param_x, "  BLOCKS                           |   RULES");
                mvprintw(menu_param_y+1, menu_param_x, "__________________________________ | ___________________________________");
                mvprintw(menu_param_y+2, menu_param_x, "                                   |");
                mvprintw(menu_param_y+3, menu_param_x, "              --------             | You start the game with 5 lives");
                mvprintw(menu_param_y+4, menu_param_x, ">> Standard : 88888888             | and you have to break all the");
                mvprintw(menu_param_y+5, menu_param_x, "              --------             | standard and hard bricks with the");
                mvprintw(menu_param_y+6, menu_param_x, "--> Breaks in 1 hit                | ball (@) to clear the level.");
                mvprintw(menu_param_y+7, menu_param_x, "--> +50 pt if hit                  |");
                mvprintw(menu_param_y+8, menu_param_x, "                                   | There are 4 independent levels");
                mvprintw(menu_param_y+9, menu_param_x, "                ********           | and you can play them in any order.");
                mvprintw(menu_param_y+10, menu_param_x, ">> Hard brick : * *  * *           |");
                mvprintw(menu_param_y+11, menu_param_x, "                ********           |");
                mvprintw(menu_param_y+12, menu_param_x, "--> Breaks in 2 hits               |");
                mvprintw(menu_param_y+13, menu_param_x, "--> +20 pt if hit                  |   CONTROLS");
                mvprintw(menu_param_y+14, menu_param_x, "                                   | ___________________________________");
                mvprintw(menu_param_y+15, menu_param_x, "                  MMMMMMMM         |");
                mvprintw(menu_param_y+16, menu_param_x, ">> Deadly brick : I  XX  I         |  >> 'ESC' : Pauses the game");
                mvprintw(menu_param_y+17, menu_param_x, "                  WWWWWWWW         |  >> Left arrow : move to the left");
                mvprintw(menu_param_y+18, menu_param_x, "--> -100 pt & -1 life if hit       |  >> Right arrow : move to the right");
                mvprintw(menu_param_y+19, menu_param_x, "                                   |");
                mvprintw(menu_param_y+20, menu_param_x, "              --------             |");
                mvprintw(menu_param_y+21, menu_param_x, ">> Platform : |      |             |  ..................................");
                mvprintw(menu_param_y+22, menu_param_x, "              --------             |  : >> M << to go back to the menu :");
                mvprintw(menu_param_y+23, menu_param_x, "--> Doesn't break                  |  :................................:");
                mvprintw(menu_param_y+24, menu_param_x, "--> Doesn't break                  |");
                refresh();



            }
            exit_param = false;
            //cont = false;

        }

        if(!pause && !param){
            loadTabLevel(tabLevel, chosen_lvl);
            lives = 5;
            score = 0;
        }
        pause=false;

        //cont = true;
        clear();
        while(cont && !param){

            /* Keyboard handling */
            if(kbhit()){
                key = getch();
                switch(key){
                case 27: // Escape key code
                    cont = false;
                    pause = true;
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

            // win check
            /*bool winning = true;
            int i=0;
            int j=0;
            while(i<=TAB_LVL_HEIGHT && winning){
                while(j<=TAB_LVL_WIDTH && winning){
                    if(tabLevel[i][j]==2 || tabLevel[i][j]==3){
                        winning = false;
                    }
                    else{
                        j+=1;
                    }
                }
                //if(winning){
                    i+=1;
                //}
            }
            win = winning;*/

            bool winning = true;
            for(int i=0; i<TAB_LVL_HEIGHT; i+=1){
                for(int j=0; j<TAB_LVL_WIDTH; j+=1){
                    if(tabLevel[i][j]==0 || tabLevel[i][j]==1){
                        winning = false;
                    }
                }
            }
            win = winning;
            if(win){
                cont = false;
            }


            /* Graphical update */
            // Clear window
            werase(pMainWindow);
            // Display game elements
            displayLevel(tabLevel);
            displayBall(yBall, xBall);

            int menu_vie_x=70;
            int menu_vie_y=10;

            mvprintw(menu_vie_y, menu_vie_x, " ------------------------------------- ");
            mvprintw(menu_vie_y+1, menu_vie_x, "|                                     |");
            //mvprintw(0, 0, "|             Life : *****            |");
            mvprintw(menu_vie_y+3, menu_vie_x, "|   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   |");
            mvprintw(menu_vie_y+4, menu_vie_x, "|                                     |");
            //mvprintw(0, 0, "|          --> Score : 780            |");
            //mvprintw(menu_vie_y+6, menu_vie_x, "|          --> Best score : 780       |");
            mvprintw(menu_vie_y+7, menu_vie_x, "|                                     |");
            mvprintw(menu_vie_y+8, menu_vie_x, " ------------------------------------- ");

            if(lives==5){
                mvprintw(menu_vie_y+2, menu_vie_x, "|             Life : *****            |");
            }
            else if(lives==4){
                mvprintw(menu_vie_y+2, menu_vie_x, "|             Life : ****             |");
            }
            else if(lives==3){
                mvprintw(menu_vie_y+2, menu_vie_x, "|             Life : ***              |");
            }
            else if(lives==2){
                mvprintw(menu_vie_y+2, menu_vie_x, "|             Life : **               |");
            }
            else if(lives==1){
                mvprintw(menu_vie_y+2, menu_vie_x, "|             Life : *                |");
            }


            if(score < 10){
                mvprintw(menu_vie_y+5, menu_vie_x, "|          --> Score : %d              |", score);
            }
            else if(score < 100){
                mvprintw(menu_vie_y+5, menu_vie_x, "|          --> Score : %d             |", score);
            }
            else if(score < 1000){
                mvprintw(menu_vie_y+5, menu_vie_x, "|          --> Score : %d            |", score);
            }
            else{
                mvprintw(menu_vie_y+5, menu_vie_x, "|          --> Score : %d           |", score);
            }


            if(best_scores[chosen_lvl-1] < 10){
                mvprintw(menu_vie_y+6, menu_vie_x, "|          --> Best score : %d         |", best_scores[chosen_lvl-1]);
            }
            else if(best_scores[chosen_lvl-1] < 100){
                mvprintw(menu_vie_y+6, menu_vie_x, "|          --> Best score : %d        |", best_scores[chosen_lvl-1]);
            }
            else if(best_scores[chosen_lvl-1] < 1000){
                mvprintw(menu_vie_y+6, menu_vie_x, "|          --> Best score : %d       |", best_scores[chosen_lvl-1]);
            }
            else{
                mvprintw(menu_vie_y+6, menu_vie_x, "|          --> Best score : %d      |", best_scores[chosen_lvl-1]);
            }


            //mvprintw(13, 80, "Score : %d", score);
            /*if(score >= best_scores[chosen_lvl-1]){
                best_scores[chosen_lvl-1] = score;
            }*/
            //mvprintw(14, 80, "Best score : %d", best_scores[chosen_lvl-1]);

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
        if(!pause && !param){
            if(score >= best_scores[chosen_lvl-1]){
                best_scores[chosen_lvl-1] = score;
            }
        }

        bool choix_cont = false;

        if(pause){
            while(!choix_cont){
                if(kbhit()){
                    key=getch();
                    if(key == 99){
                        cont=true;
                        retour_menu=false;
                        choix_cont=true;
                    }
                    else if(key==112){
                        cont = true;
                        retour_menu=false;
                        //lives = 5;
                        yBall = 0;
                        xBall = 0;
                        //loadTabLevel(tabLevel, chosen_lvl);
                        choix_cont=true;
                        pause = false;
                    }
                    else if(key==109){
                        cont = true;
                        retour_menu=true;
                        //lives = 5;
                        yBall = 0;
                        xBall = 0;
                        choix_cont = true;
                        pause = false;
                    }
                    else if(key==113){
                        rejouer=false;
                        choix_cont=true;
                    }
                }

                werase(pMainWindow);
                int menu_pause_x=30;
                int menu_pause_y=5;
                mvprintw(menu_pause_y, menu_pause_x, "                      GAME PAUSED");
                mvprintw(menu_pause_y+1, menu_pause_x, " ____________________________________________________");
                mvprintw(menu_pause_y+3, menu_pause_x, "                  --> Score : %d", score);
                mvprintw(menu_pause_y+4, menu_pause_x, "                --> Best Score : %d", best_scores[chosen_lvl-1]);

                if(lives==5){
                    mvprintw(menu_pause_y+6, menu_pause_x, "                  --> Life : *****");
                }
                else if(lives==4){
                    mvprintw(menu_pause_y+6, menu_pause_x, "                  --> Life : ****");
                }
                else if(lives==3){
                    mvprintw(menu_pause_y+6, menu_pause_x, "                   --> Life : ***");
                }
                else if(lives==2){
                    mvprintw(menu_pause_y+6, menu_pause_x, "                    --> Life : **");
                }
                else if(lives==1){
                    mvprintw(menu_pause_y+6, menu_pause_x, "                    --> Life : *");
                }

                mvprintw(menu_pause_y+8, menu_pause_x, "                ----------------------");
                mvprintw(menu_pause_y+9, menu_pause_x, "               |   Continue >> C <<   |");
                mvprintw(menu_pause_y+10, menu_pause_x, "                ----------------------");
                mvprintw(menu_pause_y+11, menu_pause_x, "                ----------------------");
                mvprintw(menu_pause_y+12, menu_pause_x, "               |  Play again >> P <<  |");
                mvprintw(menu_pause_y+13, menu_pause_x, "                ----------------------");
                mvprintw(menu_pause_y+14, menu_pause_x, "                ---------------------");
                mvprintw(menu_pause_y+15, menu_pause_x, "               |  Main Menu >> M <<  |");
                mvprintw(menu_pause_y+16, menu_pause_x, "                ---------------------");
                mvprintw(menu_pause_y+17, menu_pause_x, "                 -------------------");
                mvprintw(menu_pause_y+18, menu_pause_x, "                |  Quitter >> Q <<  |");
                mvprintw(menu_pause_y+19, menu_pause_x, "                 -------------------");

                refresh();
            }
            //pause = false;

        }

        else if(win){
           while(!choix_cont){
                if(kbhit()){
                    key = getch();
                    if(key==110 && chosen_lvl!=4){
                        cont=true;
                        retour_menu=false;
                        chosen_lvl += 1;
                        xBall = 0;
                        yBall = 0;
                        choix_cont=true;
                    }
                    else if(key==112){
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

                if(chosen_lvl != 4){
                    int menu_go_x=30;
                    int menu_go_y=5;
                    mvprintw(menu_go_y, menu_go_x, "                        YOU WIN");
                    mvprintw(menu_go_y+1, menu_go_x, " ____________________________________________________");
                    mvprintw(menu_go_y+3, menu_go_x, "                  --> Score : %d", score);
                    mvprintw(menu_go_y+4, menu_go_x, "                --> Best Score : %d", best_scores[chosen_lvl-1]);
                    mvprintw(menu_go_y+6, menu_go_x, "                ----------------------");
                    mvprintw(menu_go_y+7, menu_go_x, "               |  Next level >> N <<  |");
                    mvprintw(menu_go_y+8, menu_go_x, "                ----------------------");
                    mvprintw(menu_go_y+9, menu_go_x, "                ----------------------");
                    mvprintw(menu_go_y+10, menu_go_x, "               |  Play again >> P <<  |");
                    mvprintw(menu_go_y+11, menu_go_x, "                ----------------------");
                    mvprintw(menu_go_y+12, menu_go_x, "                ---------------------");
                    mvprintw(menu_go_y+13, menu_go_x, "               |  Main Menu >> M <<  |");
                    mvprintw(menu_go_y+14, menu_go_x, "                ---------------------");
                    mvprintw(menu_go_y+15, menu_go_x, "                 -------------------");
                    mvprintw(menu_go_y+16, menu_go_x, "                |  Quitter >> Q <<  |");
                    mvprintw(menu_go_y+17, menu_go_x, "                 -------------------");
                }
                else{
                    int menu_go_x=30;
                    int menu_go_y=5;
                    mvprintw(menu_go_y, menu_go_x, "                    CONGRATULATIONS");
                    mvprintw(menu_go_y+1, menu_go_x, " ____________________________________________________");
                    mvprintw(menu_go_y+3, menu_go_x, "                  --> Score : %d", score);
                    mvprintw(menu_go_y+4, menu_go_x, "                --> Best Score : %d", best_scores[chosen_lvl-1]);
                    mvprintw(menu_go_y+6, menu_go_x, "                ----------------------");
                    mvprintw(menu_go_y+7, menu_go_x, "               |  Play again >> P <<  |");
                    mvprintw(menu_go_y+8, menu_go_x, "                ----------------------");
                    mvprintw(menu_go_y+9, menu_go_x, "                ---------------------");
                    mvprintw(menu_go_y+10, menu_go_x, "               |  Main Menu >> M <<  |");
                    mvprintw(menu_go_y+11, menu_go_x, "                ---------------------");
                    mvprintw(menu_go_y+12, menu_go_x, "                 -------------------");
                    mvprintw(menu_go_y+13, menu_go_x, "                |  Quitter >> Q <<  |");
                    mvprintw(menu_go_y+14, menu_go_x, "                 -------------------");
                }






                //box(pMainWindow, 0, 0);
                /*mvprintw(10, 10, "GAME OVER");
                mvprintw(11, 10, "Retry : R");
                mvprintw(12, 10, "Main menu : M");
                mvprintw(13, 10, "Quitter : Q");*/


                refresh();
            }
            win = false;

        }

        //bool retour_menu;
        else if(!win && !param){
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
                mvprintw(menu_go_y+6, menu_go_x, "                   -----------------");
                mvprintw(menu_go_y+7, menu_go_x, "                  |  Retry >> R <<  |");
                mvprintw(menu_go_y+8, menu_go_x, "                   -----------------");
                mvprintw(menu_go_y+9, menu_go_x, "                 ---------------------");
                mvprintw(menu_go_y+10, menu_go_x, "                |  Main Menu >> M <<  |");
                mvprintw(menu_go_y+11, menu_go_x, "                 ---------------------");
                mvprintw(menu_go_y+12, menu_go_x, "                  -------------------");
                mvprintw(menu_go_y+13, menu_go_x, "                 |  Quitter >> Q <<  |");
                mvprintw(menu_go_y+14, menu_go_x, "                  -------------------");





                //box(pMainWindow, 0, 0);
                /*mvprintw(10, 10, "GAME OVER");
                mvprintw(11, 10, "Retry : R");
                mvprintw(12, 10, "Main menu : M");
                mvprintw(13, 10, "Quitter : Q");*/


                refresh();
            }
        }




    }
    /************************************************/
    /*          End of the program                  */
    /************************************************/
    // Close properly ncurses


    endwin();

    return EXIT_SUCCESS;
}
