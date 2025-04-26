#include <iostream>
#include <vector>
#include <string>
using namespace std;

void bubbleSort(vector<pair<int, string>>& students) {
    int n = students.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].first > students[j + 1].first) {
                swap(students[j], students[j + 1]);
            }
        }
    }
}

int main() {
    int N;
    cin >> N;
    cin.ignore();
    
    vector<pair<int, string>> students(N);
    
    for (int i = 0; i < N; ++i) {
        int score;
        string fullName;
        
        cin >> score;
        cin.ignore();
        
        getline(cin, fullName);
        
        students[i] = {score, fullName};
    }
    
    bubbleSort(students);
    
    cout << students[N / 2].second << endl;

    return 0;
}
