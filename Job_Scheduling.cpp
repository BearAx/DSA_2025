#include <iostream>
#include <vector>

using namespace std;

struct Job {
    int start;
    int finish;
    int profit;
};

void merge(vector<Job>& jobs, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Job> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = jobs[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = jobs[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].finish <= R[j].finish) {
            jobs[k++] = L[i++];
        } else {
            jobs[k++] = R[j++];
        }
    }

    while (i < n1)
        jobs[k++] = L[i++];

    while (j < n2)
        jobs[k++] = R[j++];
}

void mergeSort(vector<Job>& jobs, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(jobs, left, mid);
    mergeSort(jobs, mid + 1, right);
    merge(jobs, left, mid, right);
}

int findLatestNonConflictingJob(const vector<Job>& jobs, int index) {
    int low = 0, high = index - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (jobs[mid].finish <= jobs[index].start) {
            if (mid + 1 <= index - 1 && jobs[mid + 1].finish <= jobs[index].start)
                low = mid + 1;
            else
                return mid;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}
long long maxProfit(vector<Job>& jobs) {
    int n = jobs.size();
    if (n == 0) return 0;

    mergeSort(jobs, 0, n - 1);

    vector<long long> dp(n, 0);
    dp[0] = jobs[0].profit;

    for (int i = 1; i < n; ++i) {
        long long inclProf = jobs[i].profit;
        int l = findLatestNonConflictingJob(jobs, i);
        if (l != -1) {
            inclProf += dp[l];
        }

        long long exclProf = dp[i - 1];

        dp[i] = max(inclProf, exclProf);
    }

    return dp[n - 1];
}

int main() {
    int N;
    cin >> N;

    vector<int> startTimes(N), finishTimes(N), profits(N);
    for (int i = 0; i < N; ++i) cin >> startTimes[i];
    for (int i = 0; i < N; ++i) cin >> finishTimes[i];
    for (int i = 0; i < N; ++i) cin >> profits[i];

    vector<Job> jobs(N);
    for (int i = 0; i < N; ++i) {
        jobs[i].start = startTimes[i];
        jobs[i].finish = finishTimes[i];
        jobs[i].profit = profits[i];
    }

    cout << maxProfit(jobs) << endl;

    return 0;
}