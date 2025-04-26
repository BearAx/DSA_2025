#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

template <typename T>
class Set {
public:
    virtual void add(const T& element) = 0;
    virtual bool contains(const T& element) const = 0;
    virtual ~Set() {}
};

template <typename T>
struct MyHash;

template <>
struct MyHash<string> {
    size_t operator()(const string& key) const {
        size_t hash = 0;
        const int base = 31;
        for (char c : key) {
            hash = hash * base + static_cast<size_t>(c);
        }
        return hash;
    }
};

template <typename T>
class HashSet : public Set<T> {
private:
    vector<list<T>> buckets;
    static const size_t BUCKET_COUNT = 10007;

    size_t getIndex(const T& element) const {
        MyHash<T> hashFunc;
        return hashFunc(element) % BUCKET_COUNT;
    }

public:
    HashSet() : buckets(BUCKET_COUNT) {}

    void add(const T& element) override {
        size_t index = getIndex(element);
        for (const auto& e : buckets[index]) {
            if (e == element) {
                return;
            }
        }
        buckets[index].push_back(element);
    }

    bool contains(const T& element) const override {
        size_t index = getIndex(element);
        for (const auto& e : buckets[index]) {
            if (e == element) {
                return true;
            }
        }
        return false;
    }

    ~HashSet() override = default;
};

int main() {
    int n, m;
    vector<string> firstWords;

    cin >> n;
    firstWords.reserve(n);
    for (int i = 0; i < n; ++i) {
        string word;
        cin >> word;
        firstWords.push_back(word);
    }

    cin >> m;
    HashSet<string> secondSet;
    for (int i = 0; i < m; ++i) {
        string word;
        cin >> word;
        secondSet.add(word);
    }

    vector<string> uniqueOrder;
    HashSet<string> seenFirst;
    for (const auto& word : firstWords) {
        if (!seenFirst.contains(word)) {
            seenFirst.add(word);
            uniqueOrder.push_back(word);
        }
    }

    vector<string> result;
    for (const auto& word : uniqueOrder) {
        if (!secondSet.contains(word)) {
            result.push_back(word);
        }
    }

    cout << result.size() << endl;
    for (const auto& word : result) {
        cout << word << endl;
    }

    return 0;
}