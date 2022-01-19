#include <iostream>
#include "Constants.h"
#include "Display.h"

using namespace std;

void DisplayBoard(int playerShipBoard[][BOARD_WIDTH])
{
    std::cout << endl;
    std::cout << "      A B C D E F G H I J" << endl;
    std::cout << "      ___________________" << endl;
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        if (i + 1 == BOARD_HEIGHT)
        {
            std::cout << i + 1;
            std::cout << "  |";
        }
        else
        {
            std::cout << " ";
            std::cout << i + 1;
            std::cout << "  |";
        }

        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            switch (playerShipBoard[i][j])
            {
            case BOARD_SHIP:
                std::cout << " X";
                break;
            case BOARD_COLLISION_AREA:
                std::cout << " !";
                break;
            case BOARD_HIT:
                std::cout << " H";
                break;
            case BOARD_FAIL_HIT:
                std::cout << " F";
                break;
            default:
                std::cout << " *"; break;
            }
        }
        std::cout << endl;
    }
}

void Display2Boards(int playerShipBoard[][BOARD_WIDTH], int playerHitBoard[][BOARD_WIDTH])
{
    std::cout << endl;
    cout << "      Ship board                     Hit board" << endl;
    cout << endl;
    std::cout << "      A B C D E F G H I J            A B C D E F G H I J" << endl;
    std::cout << "      ___________________            ___________________" << endl;
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        if (i + 1 == BOARD_HEIGHT)
        {
            std::cout << i + 1;
            std::cout << "  |";
        }
        else
        {
            std::cout << " ";
            std::cout << i + 1;
            std::cout << "  |";
        }

        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            switch (playerShipBoard[i][j])
            {
            case BOARD_SHIP:
                std::cout << " X";
                break;
            case BOARD_COLLISION_AREA:
                std::cout << " !";
                break;
            case BOARD_HIT:
                std::cout << " H";
                break;
            case BOARD_FAIL_HIT:
                std::cout << " F";
                break;
            default:
                std::cout << " *"; break;
            }
        }

        if (i + 1 == BOARD_HEIGHT)
        {
            std::cout << "      ";
            std::cout << i + 1;
            std::cout << "  |";
        }
        else
        {
            std::cout << "       ";
            std::cout << i + 1;
            std::cout << "  |";
        }

        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            switch (playerHitBoard[i][j])
            {
            case BOARD_SHIP:
                std::cout << " X";
                break;
            case BOARD_COLLISION_AREA:
                std::cout << " !";
                break;
            case BOARD_HIT:
                std::cout << " H";
                break;
            case BOARD_FAIL_HIT:
                std::cout << " F";
                break;
            default:
                std::cout << " *"; break;
            }
        }
        std::cout << endl;
    }
}