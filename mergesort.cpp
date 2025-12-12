#include <iostream>
#include <vector>
#include <chrono> // for measuring execution time
#include <fstream> // for file input
#include <windows.h> // for Windows API
#include <psapi.h> // for GetProcessMemoryInfo

using namespace std;

int mergesort_comparisons = 0;

void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low;
    int right = mid + 1;

    while (left <= mid && right <= high) {
        mergesort_comparisons++; // Increment comparisons count
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        } else {
            temp.push_back(arr[right]);
            right++;
        }
    }

    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}

void mergesort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergesort(arr, low, mid);
        mergesort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

// Function to get current memory usage (in KB)
SIZE_T getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize / 1024; // Convert bytes to KB
    }
    return 0;
}

int main() {
    string file_name;

    // Prompt the user to enter the input file name
    cout << "Enter the input file name: ";
    cin >> file_name;

    ifstream input_file(file_name);
    if (!input_file.is_open()) {
        cout << "Error: Could not open the file " << file_name << "!" << endl;
        return 1;
    }

    // Read input from the file
    int size;
    input_file >> size;
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        input_file >> arr[i];
    }
    input_file.close();

    // Run multiple trials to average the execution time
    const int num_trials = 10;
    double total_time = 0.0;

    // Capture initial memory usage
    SIZE_T memory_before = getMemoryUsage();

    for (int trial = 0; trial < num_trials; ++trial) {
        // Reset the comparison counter
        mergesort_comparisons = 0;

        // Create a copy of the array for each trial
        vector<int> arr_copy = arr;

        // Start time measurement
        auto start = chrono::high_resolution_clock::now();

        // Perform Merge Sort
        mergesort(arr_copy, 0, arr_copy.size() - 1);

        // End time measurement
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> exec_time = end - start;
        total_time += exec_time.count();
    }

    // Capture final memory usage
    SIZE_T memory_after = getMemoryUsage();
    SIZE_T memory_change = memory_after - memory_before;

    double average_time = total_time / num_trials;

    cout << "Average Execution Time: " << average_time << " seconds" << endl;
    cout << "Number of Comparisons: " << mergesort_comparisons << endl;
    cout << "Memory Usage Before: " << memory_before << " KB" << endl;
    cout << "Memory Usage After: " << memory_after << " KB" << endl;
    cout << "Memory Change: " << memory_change << " KB" << endl;

    return 0;
}
