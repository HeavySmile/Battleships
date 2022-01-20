#include <cstring>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Display.h"

using namespace std;

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

int Player::GetHitShipIdx(Battleship enemyBattleships[], Point hitPoint)
{

    for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
    {
        for (int j = 0; j < enemyBattleships[i].length; j++)
        {
            Point shipCoordinate = enemyBattleships[i].shipCoordinates[j];
            if (enemyBattleships[i].shipCoordinates[j].x == hitPoint.x && enemyBattleships[i].shipCoordinates[j].y == hitPoint.y)
            {
                return i;
            }
        }

    }

    return -1;
}

void Player::GetConfigFromFile(string filePath)
{
    fstream userFile;
    userFile.open(filePath, fstream::in);

    if (!userFile.is_open()) {

        std::cout << "Failed to open file";
        return;
    }

    string buffer;

    for (int i = 0; getline(userFile, buffer) && i < MAX_SHIPS_AMOUNT; i++)
    {
        Battleship& battleship = battleships[i];
        if (buffer.length() == 6 || buffer.length() == 7)
        {
            battleship.posLetter = buffer[0];
            if (buffer.length() == 6)
            {
                battleship.posNumber = buffer[1] - '0';
                battleship.dirLetter = buffer[3];
                battleship.length = buffer[5] - '0';
            }
            else if (buffer.length() == 7)
            {
                battleship.posNumber = 0;
                battleship.posNumber += (buffer[1] - '0') * 10;
                battleship.posNumber += buffer[2] - '0';
                battleship.dirLetter = buffer[4];
                battleship.length = buffer[6] - '0';
            }

        }

        switch (battleship.length)
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

        while (!battleship.CheckConfig(ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips))
        {
            battleship.CorrectConfig(ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips);
        }

        while (battleship.IsColliding(ShipBoard))
        {
            switch (battleship.length)
            {
            case 2:
                twoTileShips--;
                break;
            case 3:
                threeTileShips--;
                break;
            case 4:
                fourTileShips--;
                break;
            case 6:
                sixTileShips--;
                break;
            }
            cout << "Your ship is colliding with previously added ships" << endl;
            cout << "Position to edit : ";
            battleship.PrintConfig();
            cout << endl;
            battleship.EraseBattleshipCoordinates();
            battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
            battleship.WriteBattleshipCoordinates();
        }

        battleship.WriteBattleshipCoordinates();
        battleship.AddShipCollision(ShipBoard);
        battleship.AddToShipBoard(ShipBoard);

    }

    userFile.close();
}

void Player::PlayerStart()
{
    string answer = " ";
    
    cout << "----------" << endl;
    cout << Name << " :" << endl;
    cout << "----------" << endl;
    cout << endl;
    while (answer != "Y" && answer != "y" && answer != "N" && answer != "n")
    {
        cout << "Would you like to upload ship configuration from file?" << endl;
        cout << "Y / N? : ";
        cin >> answer;
    }
    
    if (answer == "Y" || answer == "y")
    {
        string path;
        cout << "Please input file path : ";
        cin >> path;
        GetConfigFromFile(path);
        DisplayBoard(ShipBoard);

        char answer = ' ';
        while (answer != 'y' && answer != 'Y')
        {
            cout << endl;
            cout << "Proceed?" << endl;
            cout << "Type Y/y : ";
            cin >> answer;
        }
    }
    else
    {

        for (int i = 0; i <= MAX_SHIPS_AMOUNT;)
        {
            cout << endl;
            cout << "2 tile ships: " << twoTileShips << endl;
            cout << "3 tile ships: " << threeTileShips << endl;
            cout << "4 tile ships: " << fourTileShips << endl;
            cout << "6 tile ships: " << sixTileShips << endl;
            cout << endl;
            string answer = " ";

            if (i == 0)
            {
                cout << "1. Input next ship" << endl;
                cout << "2. Show ship board" << endl;
                cout << endl;
                cout << "Choose option : ";
            }
            else if (i < MAX_SHIPS_AMOUNT)
            {
                cout << "1. Input next ship" << endl;
                cout << "2. Edit ship configuration" << endl;
                cout << "3. Show ship board" << endl;
                cout << endl;
                cout << "Choose option : ";
            }
            else if (i == MAX_SHIPS_AMOUNT)
            {
                cout << "1. Edit ship configuration" << endl;
                cout << "2. Show ship board" << endl;
                cout << "3. Finish" << endl;
                cout << endl;
                cout << "Choose option : ";
            }
            cin >> answer;
            if (answer != "1" && answer != "2" && answer != "3")
            {
                ClearConsole();
                continue;
            }

            if (answer == "1" && i < MAX_SHIPS_AMOUNT)
            {
                Battleship& battleship = battleships[i];
                cout << endl;
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                cout << "Input ship " << i + 1 << " : ";

                battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);

                while (!battleship.CheckConfig(ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips))
                {
                    cout << endl;
                    battleship.CorrectConfig(ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                }

                battleship.WriteBattleshipCoordinates();

                while (battleship.IsColliding(ShipBoard))
                {
                    cout << "Your ship is colliding with previously added ships" << endl;
                    cout << endl;
                    cout << "Position to edit : ";
                    battleship.PrintConfig();
                    
                    switch (battleship.length)
                    {
                    case 2:
                        twoTileShips--;
                        break;
                    case 3:
                        threeTileShips--;
                        break;
                    case 4:
                        fourTileShips--;
                        break;
                    case 6:
                        sixTileShips--;
                        break;
                    }
                    
                    cout << endl;
                    battleship.EraseBattleshipCoordinates();
                    cout << "Correct your ship configuration : ";
                    battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                    battleship.PrintConfig();
                    battleship.WriteBattleshipCoordinates();
                }

                for (int j = 0; j <= i; j++)
                {
                    battleships[j].AddShipCollision(ShipBoard);
                    battleships[j].AddToShipBoard(ShipBoard);
                }

                i++;
                std::cout << endl;
            }
            else if ((answer == "2" && i < MAX_SHIPS_AMOUNT) || (answer == "1" && i == MAX_SHIPS_AMOUNT))
            {
                string buffer = " ";
                cout << endl;
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                cout << "Input ship to be edited : ";

                cin.ignore();
                getline(cin, buffer);
                cout << endl;
                while (GetShipIdx(buffer) == -1)
                {
                    cout << "No ship with such config" << endl;
                    cout << "Input ship to be edited : ";
                    getline(cin, buffer);
                }

                Battleship& battleship = battleships[GetShipIdx(buffer)];
                battleship.EraseShipCollision(ShipBoard);
                battleship.EraseFromShipBoard(ShipBoard);
                battleship.EraseBattleshipCoordinates();

                switch (battleship.length)
                {
                case 2:
                    twoTileShips--;
                    break;
                case 3:
                    threeTileShips--;
                    break;
                case 4:
                    fourTileShips--;
                    break;
                case 6:
                    sixTileShips--;
                    break;
                }

                for (int j = 0; j < i; j++)
                {
                    battleships[j].AddShipCollision(ShipBoard);
                    battleships[j].AddToShipBoard(ShipBoard);
                }

                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                cout << "Input new ship configuration : ";
                battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);

                while (!battleship.CheckConfig(ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips))
                {
                    cout << endl;
                    battleship.CorrectConfig(ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                }

                battleship.WriteBattleshipCoordinates();

                while (battleship.IsColliding(ShipBoard))
                {
                    cout << endl;
                    cout << "Your ship is colliding with previously added ships" << endl;
                    cout << "Position to edit : ";
                    battleship.PrintConfig();
                    
                    switch (battleship.length)
                    {
                    case 2:
                        twoTileShips--;
                        break;
                    case 3:
                        threeTileShips--;
                        break;
                    case 4:
                        fourTileShips--;
                        break;
                    case 6:
                        sixTileShips--;
                        break;
                    }
                    
                    cout << endl;
                    battleship.EraseBattleshipCoordinates();
                    cout << "Correct your ship configuration : ";
                    battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                    battleship.WriteBattleshipCoordinates();

                    
                }

                battleship.AddShipCollision(ShipBoard);
                battleship.AddToShipBoard(ShipBoard);

            }
            else if ((answer == "3" && i < MAX_SHIPS_AMOUNT) || (answer == "2" && i == MAX_SHIPS_AMOUNT) || (answer == "2" && i == 0))
            {
                DisplayBoard(ShipBoard);
            }
            else if ((answer == "3" && i == MAX_SHIPS_AMOUNT))
            {
                break;
            }
        }
    }
}

bool Player::PlayerTurn(Player& enemy)
{

    ClearConsole();
    cout << endl;
    cout << "________________________________" << endl;
    cout << Name << "'s turn :" << endl;
    cout << "--------------------------------" << endl;
    cout << endl;

    cout << "2 tile ships: " << twoTileShips << endl;
    cout << "3 tile ships: " << threeTileShips << endl;
    cout << "4 tile ships: " << fourTileShips << endl;
    cout << "6 tile ships: " << sixTileShips << endl;
    cout << endl;
    string answer = " ";

    while (answer != "1" && answer != "2" && answer != "3")
    {
        cout << "1. Show hit board" << endl;
        cout << "2. Show ship and hit board" << endl;
        cout << "3. Fire" << endl;
        cout << "Choose option : ";
        cin >> answer;
        cout << endl;

        if (answer == "1")
        {
            DisplayBoard(HitBoard);
            answer = " ";
        }
        else if (answer == "2")
        {
            Display2Boards(ShipBoard, HitBoard);
            answer = " ";
        }
        else if (answer == "3")
        {
            cout << "Input tile coordinates to fire at : ";
            break;
        }
        cout << endl;
    }



    string buffer;
    Point hitPoint;
    cin >> buffer;

    if (buffer.length() == 2)
    {
        hitPoint.x = buffer[1] - '0' - 1;
        hitPoint.y = TransformBoardChar(buffer[0]);
    }
    else if (buffer.length() == 3)
    {
        hitPoint.x = BOARD_WIDTH - 1;
        hitPoint.y = TransformBoardChar(buffer[0]);
    }

    if (enemy.ShipBoard[hitPoint.x][hitPoint.y] == BOARD_SHIP)
    {
        cout << endl;
        cout << "Result : HIT" << endl;
        HitBoard[hitPoint.x][hitPoint.y] = BOARD_HIT;
        enemy.ShipBoard[hitPoint.x][hitPoint.y] = BOARD_HIT;

        int hitShipIdx = GetHitShipIdx(enemy.battleships, hitPoint);

        for (int i = 0; i < enemy.battleships[hitShipIdx].length; i++)
        {
            Point& shipCoordinate = enemy.battleships[hitShipIdx].shipCoordinates[i];
            Point& hitCoordinate = enemy.battleships[hitShipIdx].hitCoordinates[i];

            if (shipCoordinate.x == hitPoint.x && shipCoordinate.y == hitPoint.y)
            {
                hitCoordinate.x = shipCoordinate.x;
                hitCoordinate.y = shipCoordinate.y;
                shipCoordinate.x = -1;
                shipCoordinate.y = -1;
            }
        }

        if (enemy.battleships[hitShipIdx].IsShipSunk())
        {
            switch (enemy.battleships[hitShipIdx].length)
            {
            case 2: enemy.twoTileShips--; break;
            case 3: enemy.threeTileShips--; break;
            case 4: enemy.fourTileShips--; break;
            case 6: enemy.fourTileShips--; break;
            }
            enemy.battleships[hitShipIdx].AddHitCollision(HitBoard);
            enemy.battleships[hitShipIdx].AddToHitBoard(HitBoard);
        }


        return true;
    }
    else
    {
        HitBoard[hitPoint.x][hitPoint.y] = BOARD_FAIL_HIT;
        return false;
    }

}