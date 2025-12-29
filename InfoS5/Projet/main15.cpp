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
    // La partie commence avec 5 vies
    int lives = 5;
    int score = 0;
    // Tableau pour stocker le meilleur score de chaque niveau
    int best_scores[4] = {0, 0, 0, 0};

    /* Booleens qui permettent ou non l'affichage des menus et de rejouer/continuer */
    bool pause=false;


    /* Coordonees du coin haut gauche des differents menus */
    // Ecran de bienvenue
    int menu_bienv_x = 38;
    int menu_bienv_y = 11;
    // Menu de choix du niveau
    int menu_x = 30;
    int menu_y = 5;
    // Menu des regles du jeu
    int menu_param_x = 25;
    int menu_param_y = 2;
    // Encadre avec le nb de vies, le score et le meilleur score
    int menu_vie_x = 70;
    int menu_vie_y = 10;
    // Menu de pause
    int menu_pause_x = 30;
    int menu_pause_y = 5;
    // Menu de victoire
    int menu_win_x = 30;
    int menu_win_y = 5;
    // Menu game over
    int menu_go_x=30;
    int menu_go_y=8;




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

    /*Ecran de bienvenue du jeu*/
    bool commence = false;
    while(!commence){ // Tant que le joueur n'a pas appuye sur S on affiche l'ecran
        if(kbhit()){
            key = getch();
            if(key == 83 || key==115){ // Si le joueur a appuye sur S, on sort de la boucle
                commence = true;
            }
        }
        /* Affichage de l'ecran de bienvenue */
        werase(pMainWindow);
        mvprintw(menu_bienv_y+0, menu_bienv_x, " ---------------------------------------");
        mvprintw(menu_bienv_y+1, menu_bienv_x, "|          WELCOME TO THE GAME          |");
        mvprintw(menu_bienv_y+2, menu_bienv_x, "|                                       |");
        mvprintw(menu_bienv_y+3, menu_bienv_x, "|         Press >> S << to start        |");
        mvprintw(menu_bienv_y+4, menu_bienv_x, " ---------------------------------------");
        refresh();
    }

    cont = true;
    bool rejouer = true;
    bool retour_menu = true;
    int chosen_lvl;
    bool win = false;
    bool param = false;

    while(rejouer){ // Boucle principale (tant que le joueur n'a pas quitte le jeu)
        /* Choix du niveau (menu principal) */
        if(retour_menu){ // Condition qui permet de rentrer dans cette boucle si on a decide de revenir au menu principal apres une partie
            bool choisi = false;
            param = false;
            while(!choisi){ // Tant que le joueur n'a pas choisi on attend une reponse et on affiche le menu
                if(kbhit()){
                    key = getch();
                    if(key == 49){ // Le joueur choisit le niveau 1
                        chosen_lvl = 1;
                        choisi = true;
                    }
                    else if(key == 50){ // Le joueur choisit le niveau 2
                        chosen_lvl = 2;
                        choisi = true;
                    }
                    else if(key == 51){ // Le joueur choisit le niveau 3
                        chosen_lvl = 3;
                        choisi = true;
                    }
                    else if(key == 52){ // Le joueur choisit le niveau 4
                        chosen_lvl = 4;
                        choisi = true;
                    }
                    else if(key == 67 || key == 99){ // Le joueur choisit de consulter les regles du jeu et les commandes                               
                        param = true;
                        choisi = true;
                    }
                }
                /* Affichage du menu */
                werase(pMainWindow);
                mvprintw(menu_y, menu_x, "                      CHOOSE THE LEVEL");
                mvprintw(menu_y+1, menu_x, "___________________________________________________________");
                mvprintw(menu_y+2, menu_x, "                   --------------------- ");
                mvprintw(menu_y+3, menu_x, "                  |   Level 1  >> 1 <<  |");
                mvprintw(menu_y+4, menu_x, "                   --------------------- ");
                mvprintw(menu_y+5, menu_x, "                   --------------------- ");
                mvprintw(menu_y+6, menu_x, "                  |   Level 2  >> 2 <<  |");
                mvprintw(menu_y+7, menu_x, "                   --------------------- ");
                mvprintw(menu_y+8, menu_x, "                   --------------------- ");
                mvprintw(menu_y+9, menu_x, "                  |   Level 3  >> 3 <<  |");
                mvprintw(menu_y+10, menu_x, "                   --------------------- ");
                mvprintw(menu_y+11, menu_x, "                   --------------------- ");
                mvprintw(menu_y+12, menu_x, "                  |   Level 4  >> 4 <<  |");
                mvprintw(menu_y+13, menu_x, "                   --------------------- ");
                mvprintw(menu_y+17, menu_x, "             ..................................");
                mvprintw(menu_y+18, menu_x, "             :  Game rules & controls >> C << :");
                mvprintw(menu_y+19, menu_x, "             :................................:");
                refresh();
            }
        }

        /* Menu des regles du jeu */
        if(param){
            bool exit_param = false;
            while(!exit_param){ // Tant que le joueur n'a pas appuye sur M on affiche ce menu
                if(kbhit()){
                    key = getch();
                    if(key == 77 || key == 109){ // Le joueur choisit de retourner au menu principal
                        exit_param = true;
                    }
                }
                /* Affichage du menu */
                werase(pMainWindow);
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
                mvprintw(menu_param_y+16, menu_param_x, ">> Deadly brick : I  XX  I         |  >> 'ESC' : pause the game");
                mvprintw(menu_param_y+17, menu_param_x, "                  WWWWWWWW         |  >> Left arrow : move to the left");
                mvprintw(menu_param_y+18, menu_param_x, "--> -1 life if hit                 |  >> Right arrow : move to the right");
                mvprintw(menu_param_y+19, menu_param_x, "--> -100 pt if hit                 |");
                mvprintw(menu_param_y+20, menu_param_x, "                                   |");
                mvprintw(menu_param_y+21, menu_param_x, "              --------             |");
                mvprintw(menu_param_y+22, menu_param_x, ">> Platform : |      |             |  ..................................");
                mvprintw(menu_param_y+23, menu_param_x, "              --------             |  : >> M << to go back to the menu :");
                mvprintw(menu_param_y+24, menu_param_x, "--> Doesn't break                  |  :................................:");
                mvprintw(menu_param_y+25, menu_param_x, "                                   |");
                refresh();

            }
            exit_param = false;

        }

        /* (Re)initialisation des parametres de jeu */
        if(!pause && !param){ // Condition qui permet d'eviter ces etapes si on est sorti de la page des regles ou si on continue apres avoir fait pause
            loadTabLevel(tabLevel, chosen_lvl);
            lives = 5;
            score = 0;
        }
        pause=false;

        clear();
        /* Boucle de la partie */
        while(cont && !param){ // Tant que le joueur n'a pas perdu et qu'il n'a pas quitte la partie
            /* Keyboard handling */
            if(kbhit()){
                key = getch();
                switch(key){
                case 27: // Le joueur fait pause
                    cont = false;
                    pause = true;
                    break;
                case KEY_LEFT: // Deplacement vers la gauche
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
                case KEY_RIGHT: // Deplacement vers la droite
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

            /* On verifie si le joueur a gagne */
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

            // Encadre avec le nombre de vies et le score/meilleur score
            mvprintw(menu_vie_y, menu_vie_x, " ------------------------------------- ");
            mvprintw(menu_vie_y+1, menu_vie_x, "|                                     |");
            mvprintw(menu_vie_y+3, menu_vie_x, "|   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   |");
            mvprintw(menu_vie_y+4, menu_vie_x, "|                                     |");
            mvprintw(menu_vie_y+7, menu_vie_x, "|                                     |");
            mvprintw(menu_vie_y+8, menu_vie_x, " ------------------------------------- ");
            switch(lives){
                case 5:
                    mvprintw(menu_vie_y+2, menu_vie_x, "|             Life : *****            |");
                    break;
                case 4:
                    mvprintw(menu_vie_y+2, menu_vie_x, "|             Life : ****             |");
                    break;
                case 3:
                    mvprintw(menu_vie_y+2, menu_vie_x, "|             Life : ***              |");
                    break;
                case 2:
                    mvprintw(menu_vie_y+2, menu_vie_x, "|             Life : **               |");
                    break;
                case 1:
                    mvprintw(menu_vie_y+2, menu_vie_x, "|             Life : *                |");
                    break;
                default:
                    break;
            }
            // Adaptation de l'affichage en fonction de la longueur du score et du meilleur score
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

            // refresh window needed to display all the text
            refresh();

            if(lives == 0){ // La partie s'arrete si le joueur n'a plus de vies
                cont = false;
            }

        }

        /* A partir d'ici on a quitte la partie */
        if(!pause && !param){ // Actualisation du meilleur score a part si le joueur a juste faite pause
            if(score >= best_scores[chosen_lvl-1]){
                best_scores[chosen_lvl-1] = score;
            }
        }

        bool choix_cont = false;

        if(pause){ // Si le joueur a quitte la partie car il a fait pause
            while(!choix_cont){
                if(kbhit()){
                    key=getch();
                    if(key == 67 || key == 99){ // Le joueur choisit de reprendre la partie
                        cont = true;
                        retour_menu = false;
                        choix_cont = true;
                    }
                    else if(key == 80 || key == 112){ // Le joueur choisit de recommencer la partie
                        cont = true;
                        retour_menu = false;
                        xBall = 0;
                        yBall = 0;
                        pause = false;
                        choix_cont = true;
                    }
                    else if(key == 77 || key == 109){ // Retour au menu principal
                        cont = true;
                        retour_menu = true;
                        xBall = 0;
                        yBall = 0;
                        pause = false;
                        choix_cont = true;
                    }
                    else if(key == 81 || key == 113){ // Quitter le jeu
                        rejouer = false;
                        choix_cont = true;
                    }
                }

                /* Affichage du menu */
                werase(pMainWindow);
                mvprintw(menu_pause_y, menu_pause_x, "                      GAME PAUSED");
                mvprintw(menu_pause_y+1, menu_pause_x, " ____________________________________________________");
                mvprintw(menu_pause_y+3, menu_pause_x, "                  --> Score : %d", score);
                mvprintw(menu_pause_y+4, menu_pause_x, "                --> Best Score : %d", best_scores[chosen_lvl-1]);
                switch(lives){
                    case 5:
                        mvprintw(menu_pause_y+6, menu_pause_x, "                  --> Life : *****");
                        break;
                    case 4:
                        mvprintw(menu_pause_y+6, menu_pause_x, "                  --> Life : *****");
                        break;
                    case 3:
                        mvprintw(menu_pause_y+6, menu_pause_x, "                   --> Life : ***");
                        break;
                    case 2:
                        mvprintw(menu_pause_y+6, menu_pause_x, "                    --> Life : **");
                        break;
                    case 1:
                        mvprintw(menu_pause_y+6, menu_pause_x, "                    --> Life : *");
                        break;
                    default:
                        break;
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

        }

        else if(win){ // Si la partie s'est terminee car le joueur a gagne
           while(!choix_cont){ // Tant que le joueur n'a pas fait de choix on affiche le menu de victoire
                if(kbhit()){
                    key = getch();
                    if((key == 78 || key == 110) && chosen_lvl != 4){ // Permet de passer au niveau suivant sauf si on est au dernier niveau
                        cont=true;
                        retour_menu = false;
                        chosen_lvl += 1;
                        xBall = 0;
                        yBall = 0;
                        choix_cont = true;
                    }
                    else if(key == 80 || key == 112){ // Rejouer
                        cont = true;
                        retour_menu = false;
                        yBall = 0;
                        xBall = 0;
                        choix_cont = true;
                    }
                    else if(key == 77 || key == 109){ // Retour au menu principal
                        cont = true;
                        retour_menu = true;
                        yBall = 0;
                        xBall = 0;
                        choix_cont = true;
                    }
                    else if(key == 81 || key == 113){ // Quitter le jeu
                        rejouer = false;
                        choix_cont = true;
                    }
                }

                werase(pMainWindow);
                if(chosen_lvl != 4){ // Si on n'est pas au dernier niveau
                    mvprintw(menu_win_y, menu_win_x, "                        YOU WIN");
                    mvprintw(menu_win_y+1, menu_win_x, " ____________________________________________________");
                    mvprintw(menu_win_y+3, menu_win_x, "                  --> Score : %d", score);
                    mvprintw(menu_win_y+4, menu_win_x, "                --> Best Score : %d", best_scores[chosen_lvl-1]);
                    mvprintw(menu_win_y+6, menu_win_x, "                ----------------------");
                    mvprintw(menu_win_y+7, menu_win_x, "               |  Next level >> N <<  |");
                    mvprintw(menu_win_y+8, menu_win_x, "                ----------------------");
                    mvprintw(menu_win_y+9, menu_win_x, "                ----------------------");
                    mvprintw(menu_win_y+10, menu_win_x, "               |  Play again >> P <<  |");
                    mvprintw(menu_win_y+11, menu_win_x, "                ----------------------");
                    mvprintw(menu_win_y+12, menu_win_x, "                ---------------------");
                    mvprintw(menu_win_y+13, menu_win_x, "               |  Main Menu >> M <<  |");
                    mvprintw(menu_win_y+14, menu_win_x, "                ---------------------");
                    mvprintw(menu_win_y+15, menu_win_x, "                 -------------------");
                    mvprintw(menu_win_y+16, menu_win_x, "                |  Quitter >> Q <<  |");
                    mvprintw(menu_win_y+17, menu_win_x, "                 -------------------");
                }
                else{ // Si on est au dernier niveau, l'affichage est different
                    mvprintw(menu_win_y, menu_win_x, "                    CONGRATULATIONS");
                    mvprintw(menu_win_y+1, menu_win_x, " ____________________________________________________");
                    mvprintw(menu_win_y+3, menu_win_x, "                  --> Score : %d", score);
                    mvprintw(menu_win_y+4, menu_win_x, "                --> Best Score : %d", best_scores[chosen_lvl-1]);
                    mvprintw(menu_win_y+6, menu_win_x, "                ----------------------");
                    mvprintw(menu_win_y+7, menu_win_x, "               |  Play again >> P <<  |");
                    mvprintw(menu_win_y+8, menu_win_x, "                ----------------------");
                    mvprintw(menu_win_y+9, menu_win_x, "                ---------------------");
                    mvprintw(menu_win_y+10, menu_win_x, "               |  Main Menu >> M <<  |");
                    mvprintw(menu_win_y+11, menu_win_x, "                ---------------------");
                    mvprintw(menu_win_y+12, menu_win_x, "                 -------------------");
                    mvprintw(menu_win_y+13, menu_win_x, "                |  Quitter >> Q <<  |");
                    mvprintw(menu_win_y+14, menu_win_x, "                 -------------------");
                }
                refresh();
            }
            win = false;
        }

        else if(!win && !param){ // Si le joueur a perdu (!param permet de sauter cette etape si on a quitte le menu des regles du jeu car win sera a false)
            while(!choix_cont){
                if(kbhit()){
                    key = getch();
                    if(key == 82 || key == 114){ // Rejouer
                        cont = true;
                        retour_menu = false;
                        xBall = 0;
                        yBall = 0;
                        choix_cont = true;
                    }
                    else if(key == 77 || key == 109){ // Menu principal
                        cont = true;
                        retour_menu = true;
                        xBall = 0;
                        yBall = 0;
                        choix_cont = true;
                    }
                    else if(key == 81 || key == 113){ // Quitter le jeu
                        rejouer = false;
                        choix_cont = true;
                    }

                }
                werase(pMainWindow);
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
