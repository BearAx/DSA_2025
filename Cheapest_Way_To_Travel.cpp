//Medvedev Aleksandr DSAI-03
//I use materials from lab 5
#include <iostream>
#include <vector>

using namespace std;

long long find_min(long long a, long long b) {
    if (a < b) return a;
    return b;
}

int main() {
    int rows, cols;
    cin >> rows >> cols;

    vector<vector<int>> cost_map(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> cost_map[i][j];
        }
    }

    vector<vector<long long>> dp_table(rows, vector<long long>(cols, 0));
    dp_table[0][0] = cost_map[0][0];

    for (int i = 1; i < rows; ++i) {
        dp_table[i][0] = dp_table[i - 1][0] + cost_map[i][0];
    }

    for (int j = 1; j < cols; ++j) {
        dp_table[0][j] = dp_table[0][j - 1] + cost_map[0][j];
    }

    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            dp_table[i][j] = cost_map[i][j] + find_min(dp_table[i - 1][j], dp_table[i][j - 1]);
        }
    }

    cout << dp_table[rows - 1][cols - 1] << endl;

    vector<int> path_sequence;
    int x = rows - 1, y = cols - 1;

    while (x > 0 || y > 0) {
        path_sequence.push_back(cost_map[x][y]);
        if (x == 0) {
            y--;
        } else if (y == 0) {
            x--;
        } else {
            if (dp_table[x - 1][y] < dp_table[x][y - 1]) {
                x--;
            } else {
                y--;
            }
        }
    }

    path_sequence.push_back(cost_map[0][0]);

    for (int k = path_sequence.size() - 1; k >= 0; --k) {
        cout << path_sequence[k];
        if (k != 0) cout << ' ';
    }
    cout << endl;

    return 0;
}