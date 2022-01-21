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

// Display one board in format of 10x10 matrix
void DisplayBoard(int playerShipBoard[][BOARD_WIDTH]);

// Display two board in format of 10x10 matrix, side by side
void Display2Boards(int playerShipBoard[][BOARD_WIDTH], int playerHitBoard[][BOARD_WIDTH]);

void ClearConsole();