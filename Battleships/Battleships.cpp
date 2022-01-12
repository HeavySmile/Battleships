
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAX_SHIPS_AMOUNT = 10;
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

int current6TileAmount = 0;
int current4TileAmount = 0;
int current3TileAmount = 0;
int current2TileAmount = 0;

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
    char posLetter, dirLetter;
    int posNumber, length;

    Point shipCoordinates[6] = {};
    Point hitCoordinates[6] = {};

    void PrintConfig()
    {
        cout << posLetter << posNumber << " ";
        cout << dirLetter << " " << length;
    }

    bool CheckConfig()
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

        if (current6TileAmount > MAX_6TILE_SHIPS_AMOUNT)
        {
            return false;
        }

        if (current4TileAmount > MAX_4TILE_SHIPS_AMOUNT)
        {
            return false;
        }

        if (current3TileAmount > MAX_3TILE_SHIPS_AMOUNT)
        {
            return false;
        }

        if (current2TileAmount > MAX_2TILE_SHIPS_AMOUNT)
        {
            return false;
        }


        return true;
    }

    void InputBattleshipConfig()
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
        case 2: current2TileAmount++; break;
        case 3: current3TileAmount++; break;
        case 4: current4TileAmount++; break;
        case 6: current6TileAmount++; break;
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

    void CorrectConfig()
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

        if (current6TileAmount > MAX_6TILE_SHIPS_AMOUNT)
        {
            cout << "Please input valid length, you reached max number of 6 tile ships" << endl;
            current6TileAmount--;
            trigger = true;
        }

        if (current4TileAmount > MAX_4TILE_SHIPS_AMOUNT)
        {
            std::cout << "Please input valid length, you reached max number of 4 tile ships" << endl;
            current4TileAmount--;
            trigger = true;
        }

        if (current3TileAmount > MAX_3TILE_SHIPS_AMOUNT)
        {
            cout << "Please input valid length, you reached max number of 3 tile ships" << endl;
            current3TileAmount--;
            trigger = true;
        }

        if (current2TileAmount > MAX_2TILE_SHIPS_AMOUNT)
        {
            std::cout << "Please input valid length, you reached max number of 2 tile ships" << endl;
            current2TileAmount--;
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
            InputBattleshipConfig();
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
};
 
int GetHitShipIdx(Battleship config[], Point hitPoint)
{
    
    for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
    {
        for (int j = 0; j < config[i].length; j++)
        {
            if (config[i].shipCoordinates[j].x == hitPoint.x && config[i].shipCoordinates[j].y == hitPoint.y)
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

void GetConfigFromFile(Battleship config[], string filePath, int playerShipBoard[][BOARD_WIDTH])
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
        // C:\\Users\\lenya\\Documents\\Battleships.txt
        if (buffer.length() == 6 || buffer.length() == 7)
        {
            config[i].posLetter = buffer[0];
            if (buffer.length() == 6)
            {
                config[i].posNumber = buffer[1] - '0';
                config[i].dirLetter = buffer[3];
                config[i].length = buffer[5] - '0';
            }
            else if (buffer.length() == 7)
            {
                config[i].posNumber = 0;
                config[i].posNumber += (buffer[1] - '0') * 10;
                config[i].posNumber += buffer[2] - '0';
                config[i].dirLetter = buffer[4];
                config[i].length = buffer[6] - '0';
            }

        }
       
        while (!config[i].CheckConfig())
        {
            config[i].CorrectConfig();
        }
        
        while (!config[i].CheckShip())
        {
            std::cout << endl;
            std::cout << "Move your ship at position ";
            config[i].PrintConfig();
            std::cout << endl;
            std::cout << "It's too long to fit the board" << endl;
            std::cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
            config[i].InputBattleshipConfig();
        }

        config[i].WriteBattleshipCoordinates();
        config[i].AddShipCollision(playerShipBoard);
        config[i].AddToShipBoard(playerShipBoard);
    
    }
    userFile.close();
}

void PlayerStart(Battleship configPlayer[], string playerName, int playerShipBoard[][BOARD_WIDTH])
{
    char answer;
    std::cout << "----------" << endl;
    std::cout << playerName << " :" << endl;
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
        GetConfigFromFile(configPlayer, "C:\\Users\\lenya\\Documents\\Battleships.txt", playerShipBoard);
        DisplayBoard(playerShipBoard);
    }
    else
    {
        std::cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
        for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
        {
            std::cout << endl;
            std::cout << "Input ship " << i + 1 << " : ";
            configPlayer[i].InputBattleshipConfig();
            
            while (!configPlayer[i].CheckConfig())
            {
                configPlayer[i].CorrectConfig();
            }
            
            while (!configPlayer[i].CheckShip())
            {
                std::cout << endl;
                std::cout << "Move your ship at position ";
                configPlayer[i].PrintConfig();
                std::cout << endl;
                std::cout << "It's too long to fit the board" << endl;
                std::cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                configPlayer[i].InputBattleshipConfig();
            }


            configPlayer[i].WriteBattleshipCoordinates();
            configPlayer[i].AddShipCollision(playerShipBoard);
            configPlayer[i].AddToShipBoard(playerShipBoard);
            
            std::cout << endl;
        }
        DisplayBoard(playerShipBoard);
    }

    current6TileAmount = 0;
    current4TileAmount = 0;
    current3TileAmount = 0;
    current2TileAmount = 0;
}

bool PlayerTurn(string playerName, Battleship config[], int playerShipBoard[][BOARD_WIDTH], int playerHitBoard[][BOARD_WIDTH], int enemyShipBoard[][BOARD_WIDTH])
{
    string buffer;
    Point hitPoint;
    ClearConsole();
    std::cout << endl;
    std::cout << "________________________________" << endl;
    std::cout << playerName << "'s turn :" << endl;
    std::cout << "--------------------------------" << endl;
    std::cout << endl;
    Display2Boards(playerShipBoard, playerHitBoard);
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
    
    if (enemyShipBoard[hitPoint.x][hitPoint.y] == BOARD_SHIP)
    {
        playerHitBoard[hitPoint.x][hitPoint.y] = BOARD_HIT;
        enemyShipBoard[hitPoint.x][hitPoint.y] = BOARD_HIT;
        
        int hitShipIdx = GetHitShipIdx(config, hitPoint);
        for (int i = 0; i < config[hitShipIdx].length; i++)
        {
            if (config[hitShipIdx].shipCoordinates[i].x == hitPoint.x && config[hitShipIdx].shipCoordinates[i].y == hitPoint.y)
            {
                config[hitShipIdx].hitCoordinates[i].x = config[hitShipIdx].shipCoordinates[i].x;
                config[hitShipIdx].hitCoordinates[i].y = config[hitShipIdx].shipCoordinates[i].y;
                config[hitShipIdx].shipCoordinates[i].x = -1;
                config[hitShipIdx].shipCoordinates[i].y = -1;
            }
        }

        if (config[hitShipIdx].IsShipSunk())
        {
            switch (config[hitShipIdx].length)
            {
                case 2: current2TileAmount--; break;
                case 3: current3TileAmount--; break;
                case 4: current4TileAmount--; break;
                case 6: current6TileAmount--; break;
            }
            config[hitShipIdx].AddHitCollision(playerHitBoard);
            config[hitShipIdx].AddToHitBoard(playerHitBoard);
        }
       

        return true;
    }
    else
    {
        playerHitBoard[hitPoint.x][hitPoint.y] = BOARD_FAIL_HIT;
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

    Battleship configPlayer1[MAX_SHIPS_AMOUNT] = {};
    Battleship configPlayer2[MAX_SHIPS_AMOUNT] = {};

    int player1ShipBoard[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };
    int player1HitBoard[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };
    
    int player2ShipBoard[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };
    int player2HitBoard[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };

    PlayerStart(configPlayer1, "PLAYER 1", player1ShipBoard);
    PlayerStart(configPlayer2, "PLAYER 2", player2ShipBoard);
    
    
    while (PlayerTurn("PLAYER 1", configPlayer1, player1ShipBoard, player1HitBoard, player2ShipBoard));
    
    while (PlayerTurn("PLAYER 2", configPlayer2, player2ShipBoard, player2HitBoard, player1ShipBoard));
    
    return 0;
}

