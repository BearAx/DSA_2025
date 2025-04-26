#include <iostream>
#include <string>
using namespace std;

void BubbleSort(int A[], int N) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = 1; i < N; i++) {
            if (A[i - 1] > A[i]) {
                swap(A[i], A[i - 1]);
                swapped = true;
            }
        }
    }
}

int main() {
    int N;
    cin >> N;

    int* A = new int[N];

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    BubbleSort(A, N);

    for (int i = 0; i < N; i++) {
        cout << A[i];
        if (i < N - 1) {
            cout << " ";
        }
    }
    cout << endl;

    return 0;
}
