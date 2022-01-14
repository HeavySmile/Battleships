
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

const int MAX_SHIPS_AMOUNT = 2;
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
    int x = -1, y = -1;
};

bool DoesPointExist(Point p)
{
    if (p.x >= 0 && p.x < 10 && p.y >= 0 && p.y < 10)
    {
        return true;
    }
    else return false;
}

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

    bool CheckConfig(int sixTileShips, int fourTileShips, int threeTileShips, int twoTileShips)
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


        return true;
    }

    void InputBattleshipConfig(int &sixTileShips, int &fourTileShips, int &threeTileShips, int &twoTileShips)
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
            shipCoordinates[i].x = -1;
            shipCoordinates[i].y = -1;
        }
    }

    void CorrectConfig(int& sixTileShips, int& fourTileShips, int& threeTileShips, int& twoTileShips)
    {
        bool trigger = false;

        if ((posLetter < 'A' || posLetter > 'J') && (posLetter < 'a' || posLetter > 'j'))
        {
            std::cout << "Please input valid position character from A to J" << endl;
            trigger = true;
        }
        if (posNumber > 10)
        {
            std::cout << "Please input valid position number from 1 to 10" << endl;
            trigger = true;
        }
        if (dirLetter != 'r' && dirLetter != 'l' && dirLetter != 't' && dirLetter != 'b' &&
            dirLetter != 'R' && dirLetter != 'L' && dirLetter != 'T' && dirLetter != 'B')
        {
            std::cout << "Please input valid direction" << endl;
            trigger = true;
        }
        if (length < 2 || length > 6 || length == 5)
        {
            std::cout << "Please input valid length : 2 , 3 , 4 , 6" << endl;
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
            std::cout << "Please input valid length, you reached max number of 4 tile ships" << endl;
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
            std::cout << "Please input valid length, you reached max number of 2 tile ships" << endl;
            twoTileShips--;
            trigger = true;
        }

        /*if (IsColliding(config, playerShipBoard))
        {
            cout << "Your ship is colliding with previous inputed ships" << endl;
            cout << "Please input valid position";

            switch (config.length)
            {
            case 2: current2TileAmount--; break;
            case 3: current3TileAmount--; break;
            case 4: current4TileAmount--; break;
            case 6: current6TileAmount--; break;
            }

            trigger = true;
        }*/

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
            if (playerShipBoard[y][x] == BOARD_COLLISION_AREA || playerShipBoard[y][x] == BOARD_SHIP)
            {
                return true;
            }
        }
        return false;
    }

    bool CheckShip()
    {
        int widthIndex = TransformBoardChar(posLetter);

        if (dirLetter == 'r' || dirLetter == 'R')
        {
            if (widthIndex + length > BOARD_WIDTH)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        if (dirLetter == 'l' || dirLetter == 'L')
        {
            if (widthIndex - length + 1 < 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        if (dirLetter == 't' || dirLetter == 'T')
        {
            if (posNumber - length < 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        if (dirLetter == 'b' || dirLetter == 'B')
        {
            if (posNumber + length - 1 > BOARD_HEIGHT)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
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

};

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

void DisplayBoard(int playerShipBoard[][BOARD_WIDTH])
{
    std::cout << endl;
    std::cout << "      A B C D E F G H I J" << endl;
    std::cout << "      ___________________" << endl;
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        if (i + 1 == BOARD_HEIGHT)
        {
            std::cout << i + 1;
            std::cout << "  |";
        }
        else
        {
            std::cout << " ";
            std::cout << i + 1;
            std::cout << "  |";
        }

        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            switch (playerShipBoard[i][j])
            {
                case BOARD_SHIP: 
                    std::cout << " X";
                    break;
                case BOARD_COLLISION_AREA:
                    std::cout << " !";
                    break;
                case BOARD_HIT:
                    std::cout << " H";
                    break;
                case BOARD_FAIL_HIT:
                    std::cout << " F";
                    break;
                default:
                    std::cout << " *"; break;
            }
        }
        std::cout << endl;
    }
}

void Display2Boards(int playerShipBoard[][BOARD_WIDTH], int playerHitBoard[][BOARD_WIDTH])
{
    std::cout << endl;
    std::cout << "      A B C D E F G H I J            A B C D E F G H I J" << endl;
    std::cout << "      ___________________            ___________________" << endl;
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        if (i + 1 == BOARD_HEIGHT)
        {
            std::cout << i + 1;
            std::cout << "  |";
        }
        else
        {
            std::cout << " ";
            std::cout << i + 1;
            std::cout << "  |";
        }

        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            switch (playerShipBoard[i][j])
            {
                case BOARD_SHIP:
                    std::cout << " X";
                    break;
                case BOARD_COLLISION_AREA:
                    std::cout << " !";
                    break;
                case BOARD_HIT:
                    std::cout << " H";
                    break;
                case BOARD_FAIL_HIT:
                    std::cout << " F";
                    break;
                default:
                    std::cout << " *"; break;
            }
        }
        
        if (i + 1 == BOARD_HEIGHT)
        {
            std::cout << "      ";
            std::cout << i + 1;
            std::cout << "  |";
        }
        else
        {
            std::cout << "       ";
            std::cout << i + 1;
            std::cout << "  |";
        }

        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            switch (playerHitBoard[i][j])
            {
                case BOARD_SHIP:
                    std::cout << " X";
                    break;
                case BOARD_COLLISION_AREA:
                    std::cout << " !";
                    break;
                case BOARD_HIT:
                    std::cout << " H";
                    break;
                case BOARD_FAIL_HIT:
                    std::cout << " F";
                    break;
                default:
                    std::cout << " *"; break;
            }
        }
        std::cout << endl;
    }
}

void GetConfigFromFile(Player &player, string filePath)//Battleship config[], Player &player , string filePath, int playerShipBoard[][BOARD_WIDTH])
{
    fstream userFile;
    userFile.open(filePath, fstream::in);

    if (!userFile.is_open()) {

        std::cout << "Failed to open file";
        return;
    }
    
    string buffer;
    
    int sixTileShips = player.sixTileShips;
    int fourTileShips = player.fourTileShips;
    int threeTileShips = player.threeTileShips;
    int twoTileShips = player.twoTileShips;
    
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
       
        while (!battleship.CheckConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips))
        {
            battleship.CorrectConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
        }
        
        while (!battleship.CheckShip())
        {
            std::cout << endl;
            std::cout << "Move your ship at position ";
            battleship.PrintConfig();
            std::cout << endl;
            std::cout << "It's too long to fit the board" << endl;
            std::cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
            battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
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

        battleship.WriteBattleshipCoordinates();
        battleship.AddShipCollision(player.ShipBoard);
        battleship.AddToShipBoard(player.ShipBoard);
    
    }
    userFile.close();
}

int GetShipIdx(Player player, string searchedConfig)
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
        Battleship battleship = player.battleships[i];
        if (battleship.posLetter == posLetter && battleship.posNumber == posNumber &&
            battleship.dirLetter == dirLetter && battleship.length == length)
        {
            return i;
        }
    }
    return -1;
}

void PlayerStart(Player &player)//Battleship configPlayer[], string playerName, Player &player, int playerShipBoard[][BOARD_WIDTH])
{
    char answer;
    int sixTileShips = player.sixTileShips;
    int fourTileShips = player.fourTileShips;
    int threeTileShips = player.threeTileShips;
    int twoTileShips = player.twoTileShips;
    
    std::cout << "----------" << endl;
    std::cout << player.Name << " :" << endl;
    std::cout << "----------" << endl;
    std::cout << endl;
    std::cout << "Would you like to upload ship configuration from file?" << endl;
    std::cout << "Y / N? : ";
    
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
    {
        //string path;
        //std::cout << "Please input file path : ";
        // cin >> path;
        GetConfigFromFile(player, "C:\\Users\\lenya\\Documents\\Battleships.txt");
        DisplayBoard(player.ShipBoard);
    }
    else
    {
        
        for (int i = 0; i < MAX_SHIPS_AMOUNT;)
        {
            int answer;
            cout << "1. Input next ship" << endl;
            cout << "2. Edit ship configuration" << endl;
            cout << "3. Show ship board" << endl;
            cout << "Choose option : ";
            cin >> answer;

            if (answer == 1)
            {
                Battleship& battleship = player.battleships[i];
                std::cout << endl;
                std::cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                std::cout << "Input ship " << i + 1 << " : ";
                battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);

                while (!battleship.CheckConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips))
                {
                    battleship.CorrectConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                }

                while (!battleship.CheckShip())
                {
                    std::cout << endl;
                    std::cout << "Move your ship at position ";
                    battleship.PrintConfig();
                    std::cout << endl;
                    std::cout << "It's too long to fit the board" << endl;
                    std::cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                    battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                }
               
                battleship.WriteBattleshipCoordinates();
                battleship.AddShipCollision(player.ShipBoard);
                battleship.AddToShipBoard(player.ShipBoard);
                i++;
                std::cout << endl;
            }
            else if (answer == 2)
            {
                string buffer = " ";
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                cout << "Input ship to be edited : ";
                
                cin.ignore();
                getline(cin, buffer);

                while (GetShipIdx(player, buffer) == -1)
                {
                    cout << "No ship with such config" << endl;
                    cout << "Input ship to be edited : ";
                    getline(cin, buffer);
                }
                
                Battleship& battleship = player.battleships[GetShipIdx(player, buffer)];
                battleship.EraseShipCollision(player.ShipBoard);
                battleship.EraseFromShipBoard(player.ShipBoard);
                battleship.EraseBattleshipCoordinates();

                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                
                while (!battleship.CheckConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips))
                {
                    battleship.CorrectConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                }

                battleship.WriteBattleshipCoordinates();
                battleship.AddShipCollision(player.ShipBoard);
                battleship.AddToShipBoard(player.ShipBoard);

                /*while (!battleship.CheckShip())
                {
                    std::cout << endl;
                    std::cout << "Move your ship at position ";
                    battleship.PrintConfig();
                    std::cout << endl;
                    std::cout << "It's too long to fit the board" << endl;
                    std::cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                    battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                }*/
            }
            else if (answer == 3)
            {
                DisplayBoard(player.ShipBoard);
            }
        
        }
    }
}

bool PlayerTurn(Player &player, Player &enemy)
{
    string buffer;
    Point hitPoint;
    ClearConsole();
    std::cout << endl;
    std::cout << "________________________________" << endl;
    std::cout << player.Name << "'s turn :" << endl;
    std::cout << "--------------------------------" << endl;
    std::cout << endl;
    Display2Boards(player.ShipBoard, player.HitBoard);
    std::cout << endl;
    std::cout << endl;
    std::cout << "Input tile coordinates to fire at : ";
    std::cin >> buffer;
    
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
        player.HitBoard[hitPoint.x][hitPoint.y] = BOARD_HIT;
        cout << enemy.ShipBoard[hitPoint.x][hitPoint.y] << endl;
        enemy.ShipBoard[hitPoint.x][hitPoint.y] = BOARD_HIT;
        
        int hitShipIdx = GetHitShipIdx(player, hitPoint);
        
        cout << enemy.ShipBoard[hitPoint.x][hitPoint.y] << endl;
        cout << hitShipIdx << endl;
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

//void DisplayBoard(int playerShipBoard[BOARD_HEIGHT][BOARD_WIDTH])
//{
//    
//    for (int i = 0; i < BOARD_HEIGHT; i++)
//    {
//        for (int j = 0; j < BOARD_WIDTH; j++)
//        {
//            if (i == 0)
//            {
//                cout << "═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╗" << endl;
//                for (int k = 0; k < BOARD_WIDTH; k++)
//                {
//                    cout << "║ " << playerShipBoard[i][j] << " ";
//                    if (k == BOARD_WIDTH - 1)
//                    {
//                        cout << "║";
//                    }
//                }
//            }
//            else
//            {
//                cout << "╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣" << endl;
//                for (int k = 0; k < BOARD_WIDTH; k++)
//                {
//                    cout << "║ " << playerShipBoard[i][j] << " ";
//                    if (k == BOARD_WIDTH - 1)
//                    {
//                        cout << "║";
//                    }
//                }
//            }
//            
//            if (i == BOARD_HEIGHT - 1)
//            {
//                cout << "╚═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╝" << endl;
//            }
//        }
//    }
//}

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
        }
    }
    
    
    return 0;
}

