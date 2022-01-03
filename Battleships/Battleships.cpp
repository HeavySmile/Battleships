
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAX_SHIPS_AMOUNT = 1;
const int MAX_6TILE_SHIPS_AMOUNT = 1;
const int MAX_4TILE_SHIPS_AMOUNT = 2;
const int MAX_3TILE_SHIPS_AMOUNT = 3;
const int MAX_2TILE_SHIPS_AMOUNT = 4;
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 10;
const int BOARD_SHIP = 1;
const int BOARD_COLLISION_AREA = 2;
const int BOARD_BLANKSPACE = 0;

int current6TileAmount = 0;
int current4TileAmount = 0;
int current3TileAmount = 0;
int current2TileAmount = 0;



struct Battleship
{
    char posLetter, dirLetter;
    int posNumber = 1, length;
};

void AssembleString(Battleship config)
{
    cout << config.posLetter << config.posNumber << " ";
    cout << config.dirLetter << " " << config.length;
}

int myStrlen(char str[])
{
    int size = 0;

    while (str[size] != '\0') {
        size++;
    }

    return size;
}

bool CheckConfig(Battleship config)
{
    char posLetter = config.posLetter;
    if ((posLetter < 'A' || posLetter > 'J') && (posLetter < 'a' || posLetter > 'j'))
    {
        return false;
    }

    if (config.posNumber > 10)
    {
        return false;
    }

    char dirLetter = config.dirLetter;
    if (dirLetter != 'r' && dirLetter != 'l' && dirLetter != 't' && dirLetter != 'b' &&
        dirLetter != 'R' && dirLetter != 'L' && dirLetter != 'T' && dirLetter != 'B')
    {
        return false;
    }

    if (config.length < 2 || config.length > 6 || config.length == 5)
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

void GetConfigFromFile(Battleship config[], string filePath)
{
    fstream userFile;
    userFile.open(filePath, fstream::in);
    
    if (userFile.is_open() == false) {

        cout << "Failed to open file";
    }
    string buffer;

    for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
    {
        // C:\\Users\\lenya\\Documents\\Battleships.txt
        getline(userFile, buffer);
        if (buffer.length() < 6)
        {
            config[i].posLetter = buffer[0];
            
            if (buffer.length() == 6)
            {
                config[i].posNumber = buffer[1] - '0';
                config[i].dirLetter = buffer[3];
                config[i].length = buffer[5];
            }
            else if (buffer.length() == 7)
            {
                config[i].posNumber = 0;
                config[i].posNumber += (buffer[1] - '0') * 10;
                config[i].posNumber += buffer[2] - '0';
                config[i].dirLetter = buffer[4];
                config[i].length = buffer[6];
            }
            
        }

    }
    userFile.close();
}

void InputConfigMember(Battleship &config)
{
    char buffer[4];
    cin >> buffer;
   
    config.posLetter = (int)buffer[0];

    if (myStrlen(buffer) == 2)
    {
        config.posNumber = buffer[1] - '0';
    }
    else if (myStrlen(buffer) == 3)
    {
        config.posNumber = 0;
        config.posNumber += (buffer[1] - '0') * 10;
        config.posNumber += buffer[2] - '0';
    }

    if (config.posNumber < 1 || config.posNumber > 10)
    {

    }

    cin >> config.dirLetter;
    cin >> config.length;

    if (config.length == 6)
    {
        current6TileAmount++;
    }

    if (config.length == 4)
    {
        current4TileAmount++;
    }

    if (config.length == 3)
    {
        current3TileAmount++;
    }

    if (config.length == 2)
    {
        current2TileAmount++;
    }
}

void CorrectConfig(Battleship &config)
{
    char posLetter = config.posLetter;
    char dirLetter = config.dirLetter;
    bool trigger = false;

    cout << endl;
    if ((posLetter < 'A' || posLetter > 'J') && (posLetter < 'a' || posLetter > 'j'))
    {
        cout << "Please input valid position character from A to J" << endl;
        trigger = true;
    }
    if (config.posNumber > 10)
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
    if (config.length < 2 || config.length > 6 || config.length == 5)
    {
        cout << "Please input valid length : 2 , 3 , 4 , 6" << endl;
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
        cout << "Please input valid length, you reached max number of 4 tile ships" << endl;
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
        cout << "Please input valid length, you reached max number of 2 tile ships" << endl;
        current2TileAmount--;
        trigger = true;
    }

    if (trigger)
    {
        cout << "Position to edit : ";
        AssembleString(config);
        cout << endl;
        InputConfigMember(config);
    }
    
}

void ClearConsole()
{
    for (int i = 0; i < 50; i++)
    {
        cout << endl;
    }
}

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

bool IsColliding(Battleship &config, int playerShipBoard[BOARD_HEIGHT][BOARD_WIDTH])
{
    int widthIndex = TransformBoardChar(config.posLetter);
    int heightIndex = config.length - 1;
    
    if (config.dirLetter == 'r' || config.dirLetter == 'R')
    {
        if (widthIndex - 1 >= 0)
        {
            if (playerShipBoard[heightIndex][widthIndex - 1] != 0)
            {
                return false;
            }
        }
        
        if (widthIndex + config.length + 1 < BOARD_WIDTH)
        {
            if (playerShipBoard[heightIndex][widthIndex + config.length + 1] != 0)
            {
                return false;
            }
        }
        
        if (heightIndex - 1 >= 0)
        {
            if (playerShipBoard[heightIndex][widthIndex + config.length + 1] != 0)
            {
                return false;
            }
        }

        for (int i = widthIndex; i < config.length; i++)
        {
            
        }
    }
}

void AddToShipBoard(Battleship config, int playerShipBoard[BOARD_HEIGHT][BOARD_WIDTH])
{
    int widthIndex = TransformBoardChar(config.posLetter);
    
    if (config.dirLetter == 'r' || config.dirLetter == 'R')
    {
        while (widthIndex + config.length > BOARD_WIDTH)
        {
            cout << "Move your ship, it's too long to fit the board" << endl;
            char answer;
            cout << "Do you want to change ship position or just length?" << endl;
            cout << "P / L? : ";
            cin >> answer;
            if (answer == 'P' || answer == 'p')
            {
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                InputConfigMember(config);
            }
            else
            {
                cout << "Input new length : ";
                cin >> config.length;
            }
        }
        
        for (int i = widthIndex; i < widthIndex + config.length; i++)
        {
            playerShipBoard[config.posNumber - 1][i] = BOARD_SHIP;
        }
    }
    
    if (config.dirLetter == 'l' || config.dirLetter == 'L')
    {
        while (widthIndex - config.length + 1 < 0)
        {
            cout << "Move your ship, it's too long to fit the board" << endl;
            char answer;
            cout << "Do you want to change ship position or just length?" << endl;
            cout << "P / L? : ";
            cin >> answer;
            if (answer == 'P' || answer == 'p')
            {
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                InputConfigMember(config);
            }
            else
            {
                cout << "Input new length : ";
                cin >> config.length;
            }
        }

        for (int i = widthIndex - config.length + 1; i <= widthIndex; i++)
        {
            playerShipBoard[config.posNumber - 1][i] = BOARD_SHIP;
        }
    }
    
    if (config.dirLetter == 't' || config.dirLetter == 'T')
    {
        while (config.posNumber - config.length < 0)
        {
            cout << "Move your ship, it's too long to fit the board" << endl;
            char answer;
            cout << "Do you want to change ship position or just length?" << endl;
            cout << "P / L? : ";
            cin >> answer;
            if (answer == 'P' || answer == 'p')
            {
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                InputConfigMember(config);
            }
            else
            {
                cout << "Input new length : ";
                cin >> config.length;
            }
        }

        for (int i = config.posNumber - 1; i >= config.posNumber - config.length; i--)
        {
            playerShipBoard[i][widthIndex] = BOARD_SHIP;
        }
    }
    
    if (config.dirLetter == 'b' || config.dirLetter == 'B')
    {
        while (config.posNumber + config.length > BOARD_HEIGHT)
        {
            cout << "Move your ship, it's too long to fit the board" << endl;
            char answer;
            cout << "Do you want to change ship position or just length?" << endl;
            cout << "P / L? : ";
            cin >> answer;
            if (answer == 'P' || answer == 'p')
            {
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                InputConfigMember(config);
            }
            else
            {
                cout << "Input new length : ";
                cin >> config.length;
            }
        }

        for (int i = config.posNumber - 1; i < config.posNumber + config.length - 1; i++)
        {
            playerShipBoard[i][widthIndex] = BOARD_SHIP;
        }
    }
}

void AddShipCollision(Battleship config, int playerShipBoard[BOARD_HEIGHT][BOARD_WIDTH])
{
    int x1, y1, x2, y2;


    
    
    if (config.dirLetter == 'r' || config.dirLetter == 'R')
    {
        x1 = TransformBoardChar(config.posLetter) - 1;
        y1 = config.posNumber - 2;
        x2 = x1 + config.length + 1;
        y2 = y1 + 2;
    }
    
    if (config.dirLetter == 'l' || config.dirLetter == 'L')
    {
        x1 = TransformBoardChar(config.posLetter) - config.length;
        y1 = config.posNumber - 2;
        x2 = TransformBoardChar(config.posLetter) + 1;
        y2 = config.posNumber;
    }
    
    if (config.dirLetter == 't' || config.dirLetter == 't')
    {
        x1 = TransformBoardChar(config.posLetter) - 1;
        y1 = config.posNumber - config.length - 1;
        x2 = TransformBoardChar(config.posLetter) + 1;
        y2 = config.posNumber;
    }

    if (config.dirLetter == 't' || config.dirLetter == 't')
    {
        x1 = TransformBoardChar(config.posLetter) - 1;
        y1 = config.posNumber - config.length - 1;
        x2 = TransformBoardChar(config.posLetter) + 1;
        y2 = config.posNumber;
    }
    
    for (int i = y1; i <= y2; i++)
    {
        for (int j = x1; j <= x2; j++)
        {
            if (i >= 0 && j >= 0 && i < BOARD_HEIGHT && j < BOARD_HEIGHT)
            {
                playerShipBoard[i][j] = BOARD_COLLISION_AREA;
            }
        }
    }
    

    AddToShipBoard(config, playerShipBoard);
}

void PlayerStart(Battleship configPlayer[], string playerName, int playerShipBoard[BOARD_HEIGHT][BOARD_WIDTH])
{
    char answer;
    cout << "----------" << endl;
    cout << playerName << " :" << endl;
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
        GetConfigFromFile(configPlayer, path);
    }
    else
    {
        cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
        for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
        {
            InputConfigMember(configPlayer[i]);
            while (!CheckConfig(configPlayer[i]))
            {
                CorrectConfig(configPlayer[i]);
            }
            AddToShipBoard(configPlayer[i], playerShipBoard);
        }
    }

    current6TileAmount = 0;
    current4TileAmount = 0;
    current3TileAmount = 0;
    current2TileAmount = 0;
}



int main()
{
    
    Battleship configPlayer1[MAX_SHIPS_AMOUNT] = {};
    Battleship configPlayer2[MAX_SHIPS_AMOUNT] = {};
    
    int player1ShipBoard[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };
    int player2ShipBoard[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };
   
    
     PlayerStart(configPlayer1, "PLAYER 1", player1ShipBoard);
   // PlayerStart(configPlayer2, "PLAYER 2", player2ShipBoard);
     AddShipCollision(configPlayer1[0], player1ShipBoard);

    cout << endl;
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            cout << player1ShipBoard[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

