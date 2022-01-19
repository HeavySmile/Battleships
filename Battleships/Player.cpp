#include <cstring>
#include "Player.h"

int Player::GetShipIdx(string searchedConfig)
{
    char posLetter = ' ', dirLetter = ' ';
    int posNumber = -1, length = 0;

    posLetter = searchedConfig[0];

    if (searchedConfig.length() == 6)
    {
        posNumber = searchedConfig[1] - '0';
        dirLetter = searchedConfig[3];
        length = searchedConfig[5] - '0';
    }
    else if (searchedConfig.length() == 7)
    {
        posNumber = 0;
        posNumber += (searchedConfig[1] - '0') * 10;
        posNumber += searchedConfig[2] - '0';
        dirLetter = searchedConfig[4];
        length = searchedConfig[6] - '0';
    }

    for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
    {
        Battleship battleship = battleships[i];
        if (battleship.posLetter == posLetter && battleship.posNumber == posNumber &&
            battleship.dirLetter == dirLetter && battleship.length == length)
        {
            return i;
        }
    }
    return -1;
}