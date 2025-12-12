#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <windows.h>
#include <psapi.h>

using namespace std;

// Function to perform insertion sort
void insertionSort(vector<float> &arr, int &swapCount, int &comparisonCount) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key to one position ahead
        while (j >= 0) {
            comparisonCount++;  // Counting the comparison in the while condition
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
                swapCount++;  // Counting the swap operation
            } else {
                break;  // Exit loop if no more swaps are needed
            }
        }
        arr[j + 1] = key;
    }
}

// Function to get memory usage in KB
SIZE_T getMemoryUsageKB() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    return pmc.PrivateUsage / 1024;
}

// Function to perform bucket sort
vector<float> bucketSort(float arr[], int n, int &swapCount, int &comparisonCount) {
    vector<vector<float>> buckets(n);

    // Distribute elements into buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = n * arr[i] / 10000;  // Assumes values are in range 0 to 10000
        buckets[bucketIndex].push_back(arr[i]);
    }

    // Sort individual buckets using insertion sort
    for (int i = 0; i < n; i++) {
        if (!buckets[i].empty()) {
            int localSwapCount = 0;
            int localComparisonCount = 0;
            insertionSort(buckets[i], localSwapCount, localComparisonCount);
            swapCount += localSwapCount;
            comparisonCount += localComparisonCount;
        }
    }

    // Concatenate all sorted buckets into a sorted array
    vector<float> sortedArray;
    for (int i = 0; i < n; i++) {
        for (size_t j = 0; j < buckets[i].size(); j++) {
            sortedArray.push_back(buckets[i][j]);
        }
    }

    return sortedArray;
}

int main() {
    string filename;
    cout << "Enter the filename containing the array elements: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return 1;
    }

    int n;
    file >> n;
    float* arr = new float[n];

    for (int i = 0; i < n; i++) {
        file >> arr[i];
    }

    file.close();

    int swapCount = 0;
    int comparisonCount = 0;

    SIZE_T memoryBefore = getMemoryUsageKB();
    auto start = chrono::high_resolution_clock::now();
    vector<float> sortedArray = bucketSort(arr, n, swapCount, comparisonCount);
    auto end = chrono::high_resolution_clock::now();
    SIZE_T memoryAfter = getMemoryUsageKB();

    cout << "Number of swaps: " << swapCount << endl;
    cout << "Number of comparisons: " << comparisonCount << endl;
    cout << "Running time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0 << " ms" << endl;

    cout << "Memory usage before sorting: " << memoryBefore << " KB" << endl;
    cout << "Memory usage after sorting: " << memoryAfter << " KB" << endl;
    cout << "Additional memory used by bucket sort: " << memoryAfter - memoryBefore << " KB" << endl;

    delete[] arr;
    return 0;
}