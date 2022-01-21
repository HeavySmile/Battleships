/**
*
* Solution to course project # 8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Leonid Shubin
* @idnumber 1MI0600120
* @compiler VC
*
* <Display functions source file>
*
*/

#include <iostream>
#include "Constants.h"
#include "Display.h"

using namespace std;

void DisplayBoard(int playerShipBoard[][BOARD_WIDTH])
{
    cout << endl;
    cout << "      A B C D E F G H I J" << endl;
    cout << "      ___________________" << endl;
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        if (i + 1 == BOARD_HEIGHT)
        {
            cout << i + 1;
            cout << "  |";
        }
        else
        {
            cout << " ";
            cout << i + 1;
            cout << "  |";
        }

        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            switch (playerShipBoard[i][j])
            {
                case BOARD_SHIP:
                    cout << " X";
                    break;
                case BOARD_COLLISION_AREA:
                    cout << " !";
                    break;
                case BOARD_HIT:
                    cout << " H";
                    break;
                case BOARD_FAIL_HIT:
                    cout << " F";
                    break;
                default:
                    cout << " *"; 
                    break;
            }
        }
        cout << endl;
    }
}

void Display2Boards(int playerShipBoard[][BOARD_WIDTH], int playerHitBoard[][BOARD_WIDTH])
{
    cout << endl;
    cout << "      Ship board                     Hit board" << endl;
    cout << endl;
    std::cout << "      A B C D E F G H I J            A B C D E F G H I J" << endl;
    std::cout << "      ___________________            ___________________" << endl;
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        if (i + 1 == BOARD_HEIGHT)
        {
            cout << i + 1;
            cout << "  |";
        }
        else
        {
            cout << " ";
            cout << i + 1;
            cout << "  |";
        }

        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            switch (playerShipBoard[i][j])
            {
            case BOARD_SHIP:
                cout << " X";
                break;
            case BOARD_COLLISION_AREA:
                cout << " !";
                break;
            case BOARD_HIT:
                cout << " H";
                break;
            case BOARD_FAIL_HIT:
                cout << " F";
                break;
            default:
                cout << " *"; break;
            }
        }

        if (i + 1 == BOARD_HEIGHT)
        {
            cout << "      ";
            cout << i + 1;
            cout << "  |";
        }
        else
        {
            cout << "       ";
            cout << i + 1;
            cout << "  |";
        }

        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            switch (playerHitBoard[i][j])
            {
            case BOARD_SHIP:
                cout << " X";
                break;
            case BOARD_COLLISION_AREA:
                cout << " !";
                break;
            case BOARD_HIT:
                cout << " H";
                break;
            case BOARD_FAIL_HIT:
                cout << " F";
                break;
            default:
                cout << " *"; break;
            }
        }
        cout << endl;
    }
}

void ClearConsole()
{
    for (int i = 0; i < 50; i++)
    {
        std::cout << endl;
    }
}