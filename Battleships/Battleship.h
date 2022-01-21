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
* <Battleship structure header file>
*
*/

#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "Constants.h"
using namespace std;

int TransformBoardChar(char character);

struct Point
{
    int x = -2, y = -2;
};

struct Battleship
{
    char posLetter = ' ', dirLetter = ' ';
    int posNumber = -1, length = 0;

    Point shipCoordinates[MAX_SHIP_SIZE] = {};
    Point hitCoordinates[MAX_SHIP_SIZE] = {};

    void PrintConfig();
    

    bool CheckConfig(int playerShipBoard[][BOARD_WIDTH], int sixTileShips, int fourTileShips, int threeTileShips, int twoTileShips);

    void InputBattleshipConfig(int& sixTileShips, int& fourTileShips, int& threeTileShips, int& twoTileShips);

    void WriteBattleshipCoordinates();

    void EraseBattleshipCoordinates();

    void CorrectConfig(int playerShipBoard[][BOARD_WIDTH], int& sixTileShips, int& fourTileShips, int& threeTileShips, int& twoTileShips);

    bool IsColliding(int playerShipBoard[][BOARD_WIDTH]);

    bool IsShipSunk();

    void AddHitCollision(int playerHitBoard[][BOARD_WIDTH]);

    void AddShipCollision(int playerShipBoard[][BOARD_WIDTH]);

    void EraseShipCollision(int playerShipBoard[][BOARD_WIDTH]);

    void AddToHitBoard(int playerHitBoard[][BOARD_WIDTH]);

    void AddToShipBoard(int playerShipBoard[][BOARD_WIDTH]);

    void EraseFromShipBoard(int playerShipBoard[][BOARD_WIDTH]);
};