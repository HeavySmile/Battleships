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
* <Display functions header file>
*
*/

#pragma once
#include <iostream>
#include "Constants.h"

using namespace std;

void DisplayBoard(int playerShipBoard[][BOARD_WIDTH]);

void Display2Boards(int playerShipBoard[][BOARD_WIDTH], int playerHitBoard[][BOARD_WIDTH]);

void ClearConsole();