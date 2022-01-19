#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
using namespace std;

const int MAX_SHIPS_AMOUNT = 10;
const int MAX_SHIP_SIZE = 6;
const int MAX_6TILE_SHIPS_AMOUNT = 1;
const int MAX_4TILE_SHIPS_AMOUNT = 2;
const int MAX_3TILE_SHIPS_AMOUNT = 3;
const int MAX_2TILE_SHIPS_AMOUNT = 4;
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 10;

const int BOARD_FAIL_HIT = 4;
const int BOARD_HIT = 3;
const int BOARD_SHIP = 1;
const int BOARD_COLLISION_AREA = 2;
const int BOARD_BLANKSPACE = 0;

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