
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "Player.h"
#include "Display.h"

using namespace std;

bool DoesPointExist(Point p)
{
    if (p.x >= 0 && p.x < 10 && p.y >= 0 && p.y < 10)
    {
        return true;
    }
    else return false;
}

int GetHitShipIdx(Player player, Point hitPoint)
{
    
    for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
    {
        for (int j = 0; j < player.battleships[i].length; j++)
        {
            Point shipCoordinate = player.battleships[i].shipCoordinates[j];
            if (player.battleships[i].shipCoordinates[j].x == hitPoint.x && player.battleships[i].shipCoordinates[j].y == hitPoint.y)
            {
                return i;
            }
        }
        
    }
    
    return -1;
}

int myStrlen(char str[])
{
    int size = 0;

    while (str[size] != '\0') {
        size++;
    }

    return size;
}

void ClearConsole()
{
    for (int i = 0; i < 50; i++)
    {
        std::cout << endl;
    }
}

void GetConfigFromFile(Player &player, string filePath)
{
    fstream userFile;
    userFile.open(filePath, fstream::in);

    if (!userFile.is_open()) {

        std::cout << "Failed to open file";
        return;
    }
    
    string buffer;
    
    int &sixTileShips = player.sixTileShips;
    int &fourTileShips = player.fourTileShips;
    int &threeTileShips = player.threeTileShips;
    int &twoTileShips = player.twoTileShips;
    
    for (int i = 0; getline(userFile, buffer) && i < MAX_SHIPS_AMOUNT; i++)
    {
        Battleship &battleship = player.battleships[i];
        // C:\\Users\\lenya\\Documents\\Battleships.txt
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
            player.twoTileShips++;
            break;
        case 3:
            player.threeTileShips++;
            break;
        case 4:
            player.fourTileShips++;
            break;
        case 6:
            player.sixTileShips++;
            break;
        }

        while (!battleship.CheckConfig(player.ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips))
        {
            battleship.CorrectConfig(player.ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips);
        }
        
        while (battleship.IsColliding(player.ShipBoard))
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
        battleship.AddShipCollision(player.ShipBoard);
        battleship.AddToShipBoard(player.ShipBoard);
    
    }
    
    userFile.close();
}

void PlayerStart(Player &player)
{
    char answer;
    int &sixTileShips = player.sixTileShips;
    int &fourTileShips = player.fourTileShips;
    int &threeTileShips = player.threeTileShips;
    int &twoTileShips = player.twoTileShips;
    
    cout << "----------" << endl;
    cout << player.Name << " :" << endl;
    cout << "----------" << endl;
    cout << endl;
    cout << "Would you like to upload ship configuration from file?" << endl;
    cout << "Y / N? : ";
    
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
    {
        string path;
        cout << "Please input file path : ";
        cin >> path;
        //C:\\Users\\lenya\\Documents\\Battleships.txt
        GetConfigFromFile(player, path);
        DisplayBoard(player.ShipBoard);
        
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
            cout << "2 tile ships: " << player.twoTileShips << endl;
            cout << "3 tile ships: " << player.threeTileShips << endl;
            cout << "4 tile ships: " << player.fourTileShips << endl;
            cout << "6 tile ships: " << player.sixTileShips << endl;
            cout << endl;
            string answer = " ";
            
            if (i < MAX_SHIPS_AMOUNT)
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
                Battleship& battleship = player.battleships[i];
                cout << endl;
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                cout << "Input ship " << i + 1 << " : ";
                
                battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);

                while (!battleship.CheckConfig(player.ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips))
                {
                    battleship.CorrectConfig(player.ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                }
                
                battleship.WriteBattleshipCoordinates();
                
                while (battleship.IsColliding(player.ShipBoard))
                {
                    cout << "Your ship is colliding with previously added ships" << endl;
                    cout << "Position to edit : ";
                    battleship.PrintConfig();
                    cout << endl;
                    battleship.EraseBattleshipCoordinates();
                    battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                    battleship.WriteBattleshipCoordinates();
                }
               
                for (int j = 0; j <= i; j++)
                {
                    player.battleships[j].AddShipCollision(player.ShipBoard);
                    player.battleships[j].AddToShipBoard(player.ShipBoard);
                }
                
                i++;
                std::cout << endl;
            }
            else if ((answer == "2" && i < MAX_SHIPS_AMOUNT) || (answer == "1" && i == MAX_SHIPS_AMOUNT))
            {
                string buffer = " ";
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                cout << "Input ship to be edited : ";
                
                cin.ignore();
                getline(cin, buffer);

                while (player.GetShipIdx(buffer) == -1)
                {
                    cout << "No ship with such config" << endl;
                    cout << "Input ship to be edited : ";
                    getline(cin, buffer);
                }
                
                Battleship& battleship = player.battleships[player.GetShipIdx(buffer)];
                battleship.EraseShipCollision(player.ShipBoard);
                battleship.EraseFromShipBoard(player.ShipBoard);
                battleship.EraseBattleshipCoordinates();
                
                switch (battleship.length)
                {
                    case 2:
                        player.twoTileShips--;
                        break;
                    case 3:
                        player.threeTileShips--;
                        break;
                    case 4:
                        player.fourTileShips--;
                        break;
                    case 6:
                        player.sixTileShips--;
                        break;
                }

                for (int j = 0; j < i; j++)
                {
                    player.battleships[j].AddShipCollision(player.ShipBoard);
                    player.battleships[j].AddToShipBoard(player.ShipBoard);
                }
               
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                
                while (!battleship.CheckConfig(player.ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips))
                {
                    battleship.CorrectConfig(player.ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                }
                
                battleship.WriteBattleshipCoordinates();
                
                while (battleship.IsColliding(player.ShipBoard))
                {
                    cout << "Your ship is colliding with previously added ships" << endl;
                    cout << "Position to edit : ";
                    battleship.PrintConfig();
                    cout << endl;
                    battleship.EraseBattleshipCoordinates();
                    battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                    battleship.WriteBattleshipCoordinates();
                    
                    switch (battleship.length)
                    {
                        case 2:
                            player.twoTileShips--;
                            break;
                        case 3:
                            player.threeTileShips--;
                            break;
                        case 4:
                            player.fourTileShips--;
                            break;
                        case 6:
                            player.sixTileShips--;
                            break;
                    }
                }

                battleship.AddShipCollision(player.ShipBoard);
                battleship.AddToShipBoard(player.ShipBoard);
                
            }
            else if ((answer == "3" && i < MAX_SHIPS_AMOUNT) || (answer == "2" && i == MAX_SHIPS_AMOUNT))
            {
                DisplayBoard(player.ShipBoard);
            }
            else if ((answer == "3" && i == MAX_SHIPS_AMOUNT))
            {
                break;
            }
        }
    }
}

bool PlayerTurn(Player &player, Player &enemy)
{
    
    ClearConsole();
    cout << endl;
    cout << "________________________________" << endl;
    cout << player.Name << "'s turn :" << endl;
    cout << "--------------------------------" << endl;
    cout << endl;
    
    cout << "2 tile ships: " << player.twoTileShips << endl;
    cout << "3 tile ships: " << player.threeTileShips << endl;
    cout << "4 tile ships: " << player.fourTileShips << endl;
    cout << "6 tile ships: " << player.sixTileShips << endl;
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
            DisplayBoard(player.HitBoard);
            answer = " ";
        }
        else if (answer == "2")
        {
            Display2Boards(player.ShipBoard, player.HitBoard);
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
        player.HitBoard[hitPoint.x][hitPoint.y] = BOARD_HIT;
        enemy.ShipBoard[hitPoint.x][hitPoint.y] = BOARD_HIT;
        
        int hitShipIdx = GetHitShipIdx(player, hitPoint);
        
        for (int i = 0; i < player.battleships[hitShipIdx].length; i++)
        {
            Point &shipCoordinate = player.battleships[hitShipIdx].shipCoordinates[i];
            Point &hitCoordinate = player.battleships[hitShipIdx].hitCoordinates[i];
            
            if (shipCoordinate.x == hitPoint.x && shipCoordinate.y == hitPoint.y)
            {
                hitCoordinate.x = shipCoordinate.x;
                hitCoordinate.y = shipCoordinate.y;
                shipCoordinate.x = -1;
                shipCoordinate.y = -1;
            }
        }

        if (player.battleships[hitShipIdx].IsShipSunk())
        {
            switch (player.battleships[hitShipIdx].length)
            {
                case 2: enemy.twoTileShips--; break;
                case 3: enemy.threeTileShips--; break;
                case 4: enemy.fourTileShips--; break;
                case 6: enemy.fourTileShips--; break;
            }
            player.battleships[hitShipIdx].AddHitCollision(player.HitBoard);
            player.battleships[hitShipIdx].AddToHitBoard(player.HitBoard);
        }
       

        return true;
    }
    else
    {
        player.HitBoard[hitPoint.x][hitPoint.y] = BOARD_FAIL_HIT;
        return false;
    }
    
}

int main()
{
    Player player1, player2;
    
    player1.Name = "PLAYER 1";
    player2.Name = "PLAYER 2";

    ClearConsole();
    PlayerStart(player1);
    
    ClearConsole();
    PlayerStart(player2);
    

    while (true)
    {
        while (PlayerTurn(player1, player2))
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

        while (PlayerTurn(player2, player1))
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

