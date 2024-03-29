#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int n;
    cin >> n; cin.ignore();

    vector<string> map;
    for (int i = 0; i < n; i++) {
        string l;
        for (int j = 0; j < n; j++) {
            l += '.';
        }
        map.push_back(l);
    }

    // game loop
    while (1) {
        string command;
        getline(cin, command);
        char type = command[0];
        int val = command[2] - 48;
        for (int i = 0; i < n; i++) {
            if (type == 'C')
                map[i][val] = '#';
            else
                map[val][i] = '.';
        }
        for (int i = 0; i < n; i++) {
            cout << map[i] << endl;
        }
    }
}
