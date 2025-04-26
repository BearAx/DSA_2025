#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

template <typename K, typename V>
class Map {
public:
    virtual void insert(K key, V value) = 0;
    virtual bool contains(K key) = 0;
    virtual V get(K key) = 0;
    virtual vector<K> keys() = 0;
    virtual ~Map() {}
};

template <typename K, typename V>
class HashMap : public Map<K, V> {
private:
    struct Entry {
        K key;
        V value;
        Entry* next;
        Entry(K k, V v) : key(k), value(v), next(nullptr) {}
    };

    vector<Entry*> buckets;
    int capacity;
    int size;

    int hash(K key) {
        const int p = 31;
        const int m = 1e9 + 9;
        long long hash_value = 0;
        long long p_pow = 1;
        for (char c : key) {
            hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return abs(hash_value % capacity);
    }

public:
    HashMap(int cap = 1000) : capacity(cap), size(0) {
        buckets.resize(cap, nullptr);
    }

    ~HashMap() {
        for (int i = 0; i < capacity; ++i) {
            Entry* entry = buckets[i];
            while (entry) {
                Entry* prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
    }

    void insert(K key, V value) override {
        int index = hash(key);
        Entry* entry = buckets[index];
        while (entry) {
            if (entry->key == key) {
                entry->value = value;
                return;
            }
            entry = entry->next;
        }
        Entry* new_entry = new Entry(key, value);
        new_entry->next = buckets[index];
        buckets[index] = new_entry;
        size++;
    }

    bool contains(K key) override {
        int index = hash(key);
        Entry* entry = buckets[index];
        while (entry) {
            if (entry->key == key) {
                return true;
            }
            entry = entry->next;
        }
        return false;
    }

    V get(K key) override {
        int index = hash(key);
        Entry* entry = buckets[index];
        while (entry) {
            if (entry->key == key) {
                return entry->value;
            }
            entry = entry->next;
        }
    }

    vector<K> keys() override {
        vector<K> key_list;
        for (int i = 0; i < capacity; ++i) {
            Entry* entry = buckets[i];
            while (entry) {
                key_list.push_back(entry->key);
                entry = entry->next;
            }
        }
        return key_list;
    }
};

struct WordInfo {
    int count;
    int first_occurrence;
};

struct Entry {
    string word;
    int count;
    int first_occurrence;
};

void selectionSort(vector<Entry>& entries) {
    int n = entries.size();
    for (int i = 0; i < n - 1; ++i) {
        int max_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (entries[j].count > entries[max_idx].count) {
                max_idx = j;
            } else if (entries[j].count == entries[max_idx].count) {
                if (entries[j].first_occurrence < entries[max_idx].first_occurrence) {
                    max_idx = j;
                }
            }
        }
        if (max_idx != i) {
            swap(entries[i], entries[max_idx]);
        }
    }
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<string> words(n);
    for (int i = 0; i < n; ++i) {
        cin >> words[i];
    }

    HashMap<string, WordInfo> freqMap;

    for (int i = 0; i < n; ++i) {
        string word = words[i];
        if (freqMap.contains(word)) {
            WordInfo info = freqMap.get(word);
            info.count++;
            freqMap.insert(word, info);
        } else {
            WordInfo info;
            info.count = 1;
            info.first_occurrence = i;
            freqMap.insert(word, info);
        }
    }

    vector<Entry> entries;
    vector<string> keys = freqMap.keys();
    for (string key : keys) {
        WordInfo info = freqMap.get(key);
        entries.push_back({key, info.count, info.first_occurrence});
    }

    selectionSort(entries);

    if (k - 1 < entries.size()) {
        cout << entries[k - 1].word << endl;
    } else {
        cout << "" << endl;
    }

    return 0;
}