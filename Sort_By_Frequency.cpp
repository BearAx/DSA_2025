#include <cstdio>
#include <unordered_map>
#include <vector>
#include <cstdlib>

std::unordered_map<int, int> global_freq;

int compare(const void *a, const void *b) {
    int val1 = *(int*)a;
    int val2 = *(int*)b;
    int freq1 = global_freq[val1];
    int freq2 = global_freq[val2];
    if (freq1 != freq2) {
        return freq1 - freq2;
    } else {
        return val1 - val2;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &nums[i]);
    }

    std::unordered_map<int, int> freq;
    for (int num : nums) {
        freq[num]++;
    }

    std::vector<int> unique;
    for (const auto& pair : freq) {
        unique.push_back(pair.first);
    }

    global_freq = freq;
    qsort(unique.data(), unique.size(), sizeof(int), compare);

    for (int num : unique) {
        printf("%d\n", num);
    }

    return 0;
}