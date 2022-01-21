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
* <Main source file>
*
*/

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "Player.h"
#include "Display.h"

using namespace std;

int main()
{
    //C:\\Users\\lenya\\Documents\\Battleships1.txt
    //C:\\Users\\lenya\\Documents\\Battleships2.txt
    Player player1, player2;
    
    player1.Name = "PLAYER 1";
    player2.Name = "PLAYER 2";

    ClearConsole();
    player1.PlayerStart();
    
    ClearConsole();
    player2.PlayerStart();
    

    while (true)
    {
        while (player1.PlayerTurn(player2))
        {

            if (player2.sixTileShips + player2.fourTileShips + player2.threeTileShips + player2.twoTileShips <= 0)
            {
                ClearConsole();
                Display2Boards(player1.ShipBoard, player1.HitBoard);
                std::cout << endl;
                cout << "PLAYER 1 has won" << endl;
                return 0;
            }
            char answer = ' ';
            while (answer != 'y' && answer != 'Y')
            {
                cout << endl;
                cout << "Continue game?" << endl;
                cout << "Type Y/y : ";
                cin >> answer;
            }
        }

        while (player2.PlayerTurn(player1))
        {
            if (player1.sixTileShips + player1.fourTileShips + player1.threeTileShips + player1.twoTileShips <= 0)
            {
                ClearConsole();
                Display2Boards(player2.ShipBoard, player2.HitBoard);
                std::cout << endl;
                cout << "PLAYER 2 has won" << endl;
                return 0;
            }

            char answer = ' ';
            while (answer != 'y' && answer != 'Y')
            {
                cout << endl;
                cout << "Continue game?" << endl;
                cout << "Type Y/y : ";
                cin >> answer;
            }

        }
    }
    
    
    return 0;
}

