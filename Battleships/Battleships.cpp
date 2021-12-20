#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAX_SHIPS_AMOUNT = 2;

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

bool CheckConfig(char pos[][4], char directions[][2])
{
    for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
    {

        if ((pos[i][0] < 'A' || pos[i][0] > 'J') && (pos[i][0] < 'a' || pos[i][0] > 'j'))
        {
            return false;
        }
        
        if ((myStrlen(pos[i]) == 2 && (pos[i][1] < '1' || pos[i][1] > '9')) ||
            (myStrlen(pos[i]) == 3 && (pos[i][1] != '1' || pos[i][2] != '0')))
        {
            return false;
        }

        if (directions[i][0] != 'r' && directions[i][0] != 'l' && directions[i][0] != 't' && directions[i][0] != 'b' &&
            directions[i][0] != 'R' && directions[i][0] != 'L' && directions[i][0] != 'T' && directions[i][0] != 'B')
        {
            return false;
        }

    }
    return true;
}
void EditConfig(char pos[][4], char directions[][2])
{
    
    for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
    {
        
        if ((pos[i][0] < 'A' || pos[i][0] > 'J') && (pos[i][0] < 'a' || pos[i][0] > 'j'))
        {
            cout << "Please input valid position character from A to J" << endl;
            cout << "Position to edit : " << pos[i] << "  " << directions[i] << endl;
            cout << "Input:";
            cin >> pos[i];
        }
        else if ((myStrlen(pos[i]) == 2 && (pos[i][1] < '1' || pos[i][1] > '9')) ||
                (myStrlen(pos[i]) == 3 && (pos[i][1] != '1' || pos[i][2] != '0')))
        {
            
            cout << "Please input valid position number from 1 to 10" << endl;
            cout << "Position to edit : " << pos[i] << "  " << directions[i] << endl;
            cout << "Input:";
            cin >> pos[i];
        }
        
        if (directions[i][0] != 'r' && directions[i][0] != 'l' && directions[i][0] != 't' && directions[i][0] != 'b' &&
            directions[i][0] != 'R' && directions[i][0] != 'L' && directions[i][0] != 'T' && directions[i][0] != 'B')
        {
            cout << "Please input valid direction for position " << pos[i] << endl;
            cout << "Input:";
            cin >> directions[i];
        }
        
    }
    
}

int main()
{
    char answer;
    char pos[MAX_SHIPS_AMOUNT][4] = {"A11", "A9"};
    char directions[MAX_SHIPS_AMOUNT][2] = {"r", "y" };
    /*cout << "Would you like to upload ship configuration from file?" << endl;
    cout << "Y / N? : ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
    {

    }
    else
    {
        cout << "Input your ship configuration:";
        InputShipConfig(config);
    }*/
    
    while (CheckConfig(pos, directions) == false)
    {
        EditConfig(pos, directions);
        system("CLS");
    }

    for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
    {
        cout << pos[i] << " : " << directions[i] << endl;
    }
    
    return 0;
}

