
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAX_SHIPS_AMOUNT = 2;

struct Battleship
{
    char posLetter, dirLetter;
    int posNumber;
};

void AssembleString(Battleship config)
{
    cout << config.posLetter << config.posNumber << " " << config.dirLetter;
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
            
            if (buffer.length() == 4)
            {
                config[i].posNumber = buffer[1] - '0';
                config[i].dirLetter = buffer[3];
            }
            else if (buffer.length() == 5)
            {
                config[i].posNumber = 0;
                config[i].posNumber += (buffer[1] - '0') * 10;
                config[i].posNumber += buffer[2] - '0';
                config[i].dirLetter = buffer[4];
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

    cin >> config.dirLetter;
}

void EditConfig(Battleship &config)
{
    char posLetter = config.posLetter;
    char dirLetter = config.dirLetter;
    bool trigger = false;

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
        
    if (trigger)
    {
        cout << "Position to edit : ";
        AssembleString(config);
        cout << endl;
        InputConfigMember(config);
    }
    cout << endl;
}

void PlayerStart(Battleship configPlayer[], string playerName)
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
        cout << "Input your ship configuration in format A1 r : " << endl;
        for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
        {
            InputConfigMember(configPlayer[i]);
        }
    }

    for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
    {
        while (CheckConfig(configPlayer[i]) == false)
        {
            EditConfig(configPlayer[i]);
        }
    }
}
int main()
{
    
    Battleship configPlayer1[MAX_SHIPS_AMOUNT] = {};
    Battleship configPlayer2[MAX_SHIPS_AMOUNT] = {};
    
    PlayerStart(configPlayer1, "PLAYER 1");
    PlayerStart(configPlayer2, "PLAYER 2");
    
    return 0;
}

