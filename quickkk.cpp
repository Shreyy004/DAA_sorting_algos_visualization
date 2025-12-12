#include <iostream>
#include <vector>
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include <fstream>

using namespace std;

void quicksort(vector<int>& nums, int low, int high, int& Swapcount, int& Comparison) {
    if (low < high) {
        int start = low;
        int end = high;
        int pivot = nums[low];

        while (start <= end) {
            Comparison++;
            while (nums[start] < pivot) {
                start++;
                Comparison++;
            }

            Comparison++;
            while (nums[end] > pivot) {
                end--;
                Comparison++;
            }

            if (start <= end) {
                swap(nums[start], nums[end]);
                Swapcount++;
                start++;
                end--;
            }
        }

        if (low < end) quicksort(nums, low, end, Swapcount, Comparison);
        if (start < high) quicksort(nums, start, high, Swapcount, Comparison);
    }
}

SIZE_T getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memCounter;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter))) {
        return memCounter.WorkingSetSize / 1024;
    }
    return 0;
}

int main() {
    int n;
    int Swapcount = 0;
    int Comparison = 0;
    string filename;

    cout << "Enter the filename containing the array elements: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Error: Could not open the file!" << endl;
        return 1;
    }

    inputFile >> n;

    if (n <= 0) {
        cout << "Array size must be greater than 0!" << endl;
        return 1;
    }

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        inputFile >> arr[i];
    }

    inputFile.close();

    SIZE_T memoryBefore = getMemoryUsage();

    auto start = chrono::high_resolution_clock::now();

    quicksort(arr, 0, arr.size() - 1, Swapcount, Comparison);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    SIZE_T memoryAfter = getMemoryUsage();
    SIZE_T memoryUsed = memoryAfter - memoryBefore;

    cout << "Number of swaps: " << Swapcount << endl;
    cout << "Number of comparisons: " << Comparison << endl;
    cout << "Running time: " << duration.count() << " ms" << endl;
    cout << "Memory utilization before sorting: " << memoryBefore << " KB" << endl;
    cout << "Memory utilization after sorting: " << memoryAfter << " KB" << endl;
    cout << "Additional memory used by quicksort: " << memoryUsed << " KB" << endl;

    return 0;
}
