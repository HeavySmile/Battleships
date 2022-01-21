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
    // Player 1 input or loading from file
    player1.PlayerStart();
    
    ClearConsole();
    // Player 2 input or loading from file
    player2.PlayerStart();
    
    // The game begins
    while (true)
    {
        // Player 1 turns
        while (player1.PlayerTurn(player2))
        {

            // If opposite player runs out of ships, the game ends 
            if (player2.sixTileShips + player2.fourTileShips + player2.threeTileShips + player2.twoTileShips <= 0)
            {
                ClearConsole();
                
                // Displays player ship board and hit board
                Display2Boards(player1.ShipBoard, player1.HitBoard);
                
                cout << endl;
                cout << "PLAYER 1 has won" << endl;
                
                return 0;
            }
            
            char answer = ' ';
            // Improvised pause
            while (answer != 'y' && answer != 'Y')
            {
                cout << endl;
                cout << "Continue game?" << endl;
                cout << "Type Y/y : ";
                cin >> answer;
            }
        }

        // Player 2 turns
        while (player2.PlayerTurn(player1))
        {
            // If opposite player runs out of ships, the game ends 
            if (player1.sixTileShips + player1.fourTileShips + player1.threeTileShips + player1.twoTileShips <= 0)
            {
                ClearConsole();
                
                // Displays player ship board and hit board
                Display2Boards(player2.ShipBoard, player2.HitBoard);
                
                cout << endl;
                cout << "PLAYER 2 has won" << endl;
                
                return 0;
            }

            char answer = ' ';
            // Improvised pause
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

