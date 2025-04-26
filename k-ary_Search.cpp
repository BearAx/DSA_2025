#include <iostream>
#include <vector>
using namespace std;

int karySearch(const vector<int>& arr, int target, int K, int low, int high) {
    if (low > high) return -1;
    if (arr[low] == target) return low;
    if (arr[high] == target) return high;

    vector<int> midPoints(K - 1);
    for (int i = 0; i < K - 1; ++i) {
        midPoints[i] = low + (high - low) * (i + 1) / K;
    }

    for (int i = 0; i < K - 1; ++i) {
        if (arr[midPoints[i]] == target) return midPoints[i];
    }

    for (int i = 0; i < K - 1; ++i) {
        if (target < arr[midPoints[i]]) {
            return karySearch(arr, target, K, low, midPoints[i] - 1);
        }
    }

    return karySearch(arr, target, K, midPoints[K - 2] + 1, high);
}

int main() {
    int N, K, M;

    cin >> N >> K;

    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    cin >> M;

    while (M--) {
        int x;
        cin >> x;
        cout << karySearch(arr, x, K, 0, N - 1) << endl;
    }

    return 0;
}
