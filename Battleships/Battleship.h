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

int TransformBoardChar(char character)
{
    int widthIndex = 0;
    if (character >= 'A' && character <= 'J')
    {
        widthIndex = character - 'A';
    }
    else if (character >= 'a' && character <= 'j')
    {
        widthIndex = character - 'a';
    }

    return widthIndex;
}

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

    void PrintConfig()
    {
        cout << posLetter << posNumber << " ";
        cout << dirLetter << " " << length;
    }

    bool CheckConfig(int playerShipBoard[][BOARD_WIDTH], int sixTileShips, int fourTileShips, int threeTileShips, int twoTileShips)
    {
        if ((posLetter < 'A' || posLetter > 'J') && (posLetter < 'a' || posLetter > 'j'))
        {
            return false;
        }

        if (posNumber > 10)
        {
            return false;
        }

        if (dirLetter != 'r' && dirLetter != 'l' && dirLetter != 't' && dirLetter != 'b' &&
            dirLetter != 'R' && dirLetter != 'L' && dirLetter != 'T' && dirLetter != 'B')
        {
            return false;
        }

        if (length < 2 || length > 6 || length == 5)
        {
            return false;
        }

        if (sixTileShips > MAX_6TILE_SHIPS_AMOUNT)
        {
            return false;
        }

        if (fourTileShips > MAX_4TILE_SHIPS_AMOUNT)
        {
            return false;
        }

        if (threeTileShips > MAX_3TILE_SHIPS_AMOUNT)
        {
            return false;
        }

        if (twoTileShips > MAX_2TILE_SHIPS_AMOUNT)
        {
            return false;
        }

        int widthIndex = TransformBoardChar(posLetter);

        if (((dirLetter == 'r' || dirLetter == 'R') && (widthIndex + length > BOARD_WIDTH)) ||
            ((dirLetter == 'l' || dirLetter == 'L') && (widthIndex - length + 1 < 0)) ||
            ((dirLetter == 't' || dirLetter == 'T') && (posNumber - length < 0)) ||
            ((dirLetter == 'b' || dirLetter == 'B') && (posNumber + length - 1 > BOARD_HEIGHT)))
        {
            return false;
        }

        return true;
    }

    void InputBattleshipConfig(int& sixTileShips, int& fourTileShips, int& threeTileShips, int& twoTileShips)
    {
        string buffer = " ";
        std::cin >> buffer;

        posLetter = buffer[0];
        if (buffer.length() == 2)
        {
            posNumber = buffer[1] - '0';
        }
        else if (buffer.length() == 3)
        {
            posNumber = 0;
            posNumber += (buffer[1] - '0') * 10;
            posNumber += buffer[2] - '0';
        }

        std::cin >> dirLetter;
        std::cin >> length;

        switch (length)
        {
        case 2:
            twoTileShips++;
            break;
        case 3:
            threeTileShips++;
            break;
        case 4:
            fourTileShips++;
            break;
        case 6:
            sixTileShips++;
            break;
        }
    }

    void WriteBattleshipCoordinates()
    {
        if (dirLetter == 'r' || dirLetter == 'R')
        {
            shipCoordinates[0].x = posNumber - 1;
            shipCoordinates[0].y = TransformBoardChar(posLetter);

            for (int i = 1; i < length; i++)
            {
                shipCoordinates[i].x = shipCoordinates[0].x;
                shipCoordinates[i].y = shipCoordinates[0].y + i;
            }
        }

        if (dirLetter == 'l' || dirLetter == 'L')
        {
            shipCoordinates[length - 1].x = posNumber - 1;
            shipCoordinates[length - 1].y = TransformBoardChar(posLetter);

            for (int i = length - 2; i >= 0; i--)
            {
                shipCoordinates[i].x = shipCoordinates[i + 1].x;
                shipCoordinates[i].y = shipCoordinates[i + 1].y - 1;
            }
        }

        if (dirLetter == 't' || dirLetter == 'T')
        {
            shipCoordinates[length - 1].x = posNumber - 1;
            shipCoordinates[length - 1].y = TransformBoardChar(posLetter);

            for (int i = length - 2; i >= 0; i--)
            {
                shipCoordinates[i].x = shipCoordinates[i + 1].x - 1;
                shipCoordinates[i].y = shipCoordinates[i + 1].y;
            }
        }

        if (dirLetter == 'b' || dirLetter == 'B')
        {
            shipCoordinates[0].x = posNumber - 1;
            shipCoordinates[0].y = TransformBoardChar(posLetter);

            for (int i = 1; i < length; i++)
            {
                shipCoordinates[i].x = shipCoordinates[0].x + i;
                shipCoordinates[i].y = shipCoordinates[0].y;
            }
        }

    }

    void EraseBattleshipCoordinates()
    {
        for (int i = 0; i < MAX_SHIP_SIZE; i++)
        {
            shipCoordinates[i].x = -2;
            shipCoordinates[i].y = -2;
        }
    }

    void CorrectConfig(int playerShipBoard[][BOARD_WIDTH], int& sixTileShips, int& fourTileShips, int& threeTileShips, int& twoTileShips)
    {
        bool trigger = false;

        if ((posLetter < 'A' || posLetter > 'J') && (posLetter < 'a' || posLetter > 'j'))
        {
            cout << "Please input valid position character from A to J" << endl;
            trigger = true;
        }
        if (posNumber > 10)
        {
            cout << "Please input valid position number from 1 to 10" << endl;
            trigger = true;
        }
        if (dirLetter != 'r' && dirLetter != 'l' && dirLetter != 't' && dirLetter != 'b' &&
            dirLetter != 'R' && dirLetter != 'L' && dirLetter != 'T' && dirLetter != 'B')
        {
            cout << "Please input valid direction" << endl;
            trigger = true;
        }
        if (length < 2 || length > 6 || length == 5)
        {
            cout << "Please input valid length : 2 , 3 , 4 , 6" << endl;
            trigger = true;
        }

        if (sixTileShips > MAX_6TILE_SHIPS_AMOUNT)
        {
            cout << "Please input valid length, you reached max number of 6 tile ships" << endl;
            sixTileShips--;
            trigger = true;
        }

        if (fourTileShips > MAX_4TILE_SHIPS_AMOUNT)
        {
            cout << "Please input valid length, you reached max number of 4 tile ships" << endl;
            fourTileShips--;
            trigger = true;
        }

        if (threeTileShips > MAX_3TILE_SHIPS_AMOUNT)
        {
            cout << "Please input valid length, you reached max number of 3 tile ships" << endl;
            threeTileShips--;
            trigger = true;
        }

        if (twoTileShips > MAX_2TILE_SHIPS_AMOUNT)
        {
            cout << "Please input valid length, you reached max number of 2 tile ships" << endl;
            twoTileShips--;
            trigger = true;
        }

        int widthIndex = TransformBoardChar(posLetter);

        if (((dirLetter == 'r' || dirLetter == 'R') && (widthIndex + length > BOARD_WIDTH)) ||
            ((dirLetter == 'l' || dirLetter == 'L') && (widthIndex - length + 1 < 0)) ||
            ((dirLetter == 't' || dirLetter == 'T') && (posNumber - length < 0)) ||
            ((dirLetter == 'b' || dirLetter == 'B') && (posNumber + length - 1 > BOARD_HEIGHT)))
        {
            cout << "Your ship is too long to fit the board" << endl;
            trigger = true;
        }

        if (trigger)
        {
            std::cout << endl;
            std::cout << "Position to edit : ";
            PrintConfig();
            std::cout << endl;
            InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
        }


    }

    bool IsColliding(int playerShipBoard[][BOARD_WIDTH])
    {
        for (int i = 0; i < length; i++)
        {
            int x = shipCoordinates[i].x;
            int y = shipCoordinates[i].y;
            if (playerShipBoard[x][y] == BOARD_COLLISION_AREA || playerShipBoard[x][y] == BOARD_SHIP)
            {
                return true;
            }
        }
        return false;
    }

    bool IsShipSunk()
    {
        for (int i = 0; i < length; i++)
        {
            if (shipCoordinates[i].x != -1 && shipCoordinates[i].y != -1)
            {
                return false;
            }
        }
        return true;
    }

    void AddHitCollision(int playerHitBoard[][BOARD_WIDTH])
    {
        int x1 = hitCoordinates[0].x - 1;
        int y1 = hitCoordinates[0].y - 1;
        int x2 = hitCoordinates[length - 1].x + 1;
        int y2 = hitCoordinates[length - 1].y + 1;

        for (int i = x1; i <= x2; i++)
        {
            for (int j = y1; j <= y2; j++)
            {
                if (i >= 0 && j >= 0 && i < BOARD_HEIGHT && j < BOARD_HEIGHT)
                {
                    playerHitBoard[i][j] = BOARD_COLLISION_AREA;
                }
            }
        }

    }

    void AddShipCollision(int playerShipBoard[][BOARD_WIDTH])
    {
        int x1 = shipCoordinates[0].x - 1;
        int y1 = shipCoordinates[0].y - 1;
        int x2 = shipCoordinates[length - 1].x + 1;
        int y2 = shipCoordinates[length - 1].y + 1;

        for (int i = x1; i <= x2; i++)
        {
            for (int j = y1; j <= y2; j++)
            {
                if (i >= 0 && j >= 0 && i < BOARD_HEIGHT && j < BOARD_HEIGHT)
                {
                    playerShipBoard[i][j] = BOARD_COLLISION_AREA;
                }
            }
        }

    }

    void EraseShipCollision(int playerShipBoard[][BOARD_WIDTH])
    {
        int x1 = shipCoordinates[0].x - 1;
        int y1 = shipCoordinates[0].y - 1;
        int x2 = shipCoordinates[length - 1].x + 1;
        int y2 = shipCoordinates[length - 1].y + 1;

        for (int i = x1; i <= x2; i++)
        {
            for (int j = y1; j <= y2; j++)
            {
                if (i >= 0 && j >= 0 && i < BOARD_HEIGHT && j < BOARD_HEIGHT)
                {
                    playerShipBoard[i][j] = BOARD_BLANKSPACE;
                }
            }
        }

    }

    void AddToHitBoard(int playerHitBoard[][BOARD_WIDTH])
    {
        for (int i = 0; i < length; i++)
        {
            int x = hitCoordinates[i].x;
            int y = hitCoordinates[i].y;
            playerHitBoard[x][y] = BOARD_SHIP;
        }
    }

    void AddToShipBoard(int playerShipBoard[][BOARD_WIDTH])
    {
        for (int i = 0; i < length; i++)
        {
            int x = shipCoordinates[i].x;
            int y = shipCoordinates[i].y;
            playerShipBoard[x][y] = BOARD_SHIP;
        }
    }

    void EraseFromShipBoard(int playerShipBoard[][BOARD_WIDTH])
    {
        for (int i = 0; i < length; i++)
        {
            int x = shipCoordinates[i].x;
            int y = shipCoordinates[i].y;
            playerShipBoard[x][y] = BOARD_BLANKSPACE;
        }
    }
};