#include <bits/stdc++.h>

using namespace std;

void build_d_ary_heap(vector<int>& arr, int d) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int curr = i;
        while (curr > 0) {
            int parent = (curr - 1) / d;
            if (arr[curr] > arr[parent]) {
                swap(arr[curr], arr[parent]);
                curr = parent;
            } else {
                break;
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, d;
    cin >> N >> d;
    vector<int> arr(N);
    for(auto &x: arr) cin >> x;

    sort(arr.begin(), arr.end(), greater<int>());

    build_d_ary_heap(arr, d);

    for(auto x: arr) cout << x << " ";
}
