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

    vector<vector<char>> map;
    for (int i = 0; i < n; i++)
        map.push_back(vector<char>(n, '.'));

    // game loop
    while (1) {
        string command;
        getline(cin, command);
        char cmd = command[0];
        int val = command[2] - 48;
        if (cmd == 'C') {
            for (int i = 0; i < n; i++) {
                map[i][val] = '#';
            }
        } else {
            for (int i = 0; i < n; i++) {
                map[val][i] = '.';
            }
        }
        for (int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cout << map[i][j];
            }
            cout << endl;
        }
    }
}
