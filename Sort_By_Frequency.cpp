#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

bool customCompare(const pair<int, pair<int, int>>& x, const pair<int, pair<int, int>>& y) {
	if (x.second.first != y.second.first) {
		return x.second.first < y.second.first;
	}
	if (x.first != y.first) {
		return x.first < y.first;
	}
	return x.second.second < y.second.second;
}

void mergeVectors(vector<pair<int, pair<int, int>>>& data, int start, int mid, int end) {
	int sizeLeft = mid - start + 1;
	int sizeRight = end - mid;
	vector<pair<int, pair<int, int>>> leftPart(sizeLeft);
	vector<pair<int, pair<int, int>>> rightPart(sizeRight);

	for (int i = 0; i < sizeLeft; ++i) {
		leftPart[i] = data[start + i];
	}
	for (int j = 0; j < sizeRight; ++j) {
		rightPart[j] = data[mid + 1 + j];
	}

	int i = 0, j = 0, k = start;

	while (i < sizeLeft && j < sizeRight) {
		if (customCompare(leftPart[i], rightPart[j])) {
			data[k++] = leftPart[i++];
		}
		else {
			data[k++] = rightPart[j++];
		}
	}

	while (i < sizeLeft) {
		data[k++] = leftPart[i++];
	}

	while (j < sizeRight) {
		data[k++] = rightPart[j++];
	}
}

void performMergeSort(vector<pair<int, pair<int, int>>>& data, int start, int end) {
	if (start >= end) {
		return;
	}
	int middle = start + (end - start) / 2;
	performMergeSort(data, start, middle);
	performMergeSort(data, middle + 1, end);
	mergeVectors(data, start, middle, end);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int totalElements;
	cin >> totalElements;
	vector<int> inputArray(totalElements);
	unordered_map<int, int> elementFrequency;

	for (int i = 0; i < totalElements; ++i) {
		cin >> inputArray[i];
		elementFrequency[inputArray[i]]++;
	}

	vector<pair<int, pair<int, int>>> indexedData;
	for (int i = 0; i < totalElements; ++i) {
		indexedData.push_back({ inputArray[i], {elementFrequency[inputArray[i]], i} });
	}

	performMergeSort(indexedData, 0, indexedData.size() - 1);

	for (const auto& entry : indexedData) {
		cout << entry.first << " " << entry.second.second << "\n";
	}

	return 0;
}
