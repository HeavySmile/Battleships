
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

void InputShipConfig(char pos[][4], char directions[][2])
{
    
   
    for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
    {
        cout << "Input ship position : ";
        cin >> pos[i];
        cout << "Input ship direction : ";
        cin >> directions[i];
    }
     
}
void GetConfigFromFile(char pos[][4], char directions[][2], string filePath)
{
    fstream userFile;
    userFile.open(filePath, fstream::in);
    
    if (userFile.is_open() == false) {

        cout << "Failed to open file";
    }
    string buffer;

    while (getline(userFile, buffer)) 
    {
        //if(buffer.length() < 4 || buffer.length() > 5)
       

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

bool CheckConfig(Battleship config[])
{
    for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
    {

        char posLetter = config[i].posLetter;
        if ((posLetter < 'A' || posLetter > 'J') && (posLetter < 'a' || posLetter > 'j'))
        {
            return false;
        }
        
        if (config[i].posNumber > 10)
        {
            return false;
        }

        char dirLetter = config[i].dirLetter;
        if (dirLetter != 'r' && dirLetter != 'l' && dirLetter != 't' && dirLetter != 'b' &&
            dirLetter != 'R' && dirLetter != 'L' && dirLetter != 'T' && dirLetter != 'B')
        {
            return false;
        }

    }
    return true;
}
void EditConfig(Battleship config[])
{
    
    for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
    {
        char posLetter = config[i].posLetter;
        char dirLetter = config[i].dirLetter;
        bool trigger = false;

        if ((posLetter < 'A' || posLetter > 'J') && (posLetter < 'a' || posLetter > 'j'))
        {
            cout << "Please input valid position character from A to J" << endl;
            trigger = true;
        }
        if (config[i].posNumber > 10)
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
            AssembleString(config[i]);
            cout << endl;
            InputConfigMember(config[i]);
        }
        cout << endl;
    }
    
}

int main()
{
    char answer;
    Battleship config[MAX_SHIPS_AMOUNT] = {};
    
    cout << "Would you like to upload ship configuration from file?" << endl;
    cout << "Y / N? : ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
    {

    }
    else
    {
        cout << "Input your ship configuration in format A1 r : " << endl;
        for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
        {
            InputConfigMember(config[i]);
        }
    }
    
    while (CheckConfig(config) == false)
    {
        EditConfig(config);
    }
    
    
    for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
    {
        AssembleString(config[i]);
        cout << endl;
    }
    
    return 0;
}

