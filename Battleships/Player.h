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
* <Player structure header file>
*
*/

#pragma once
#include <cstring>
#include "Constants.h"
#include "Battleship.h"

struct Player
{
    string Name;

    int sixTileShips = 0;
    int fourTileShips = 0;
    int threeTileShips = 0;
    int twoTileShips = 0;

    int ShipBoard[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };
    int HitBoard[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };

    Battleship battleships[MAX_SHIPS_AMOUNT];

    int GetShipIdx(string searchedConfig);
    
    int GetHitShipIdx(Battleship enemyBattleships[], Point hitPoint);

    void GetConfigFromFile(string filePath);

    void PlayerStart();

    bool PlayerTurn(Player& enemy);

};