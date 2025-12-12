#include <iostream>
#include <vector>
#include <chrono> // for measuring execution time
#include <cstdlib> // for rand() function
#include <fstream> // for file input
#include <sys/resource.h> // for memory usage

using namespace std;

int mergesort_swaps = 0;
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
        mergesort_swaps++; // Increment swaps count
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
long getMemoryUsage() {
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    return r_usage.ru_maxrss; // Memory usage in KB
}

int main() {
    ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        cout << "Error: Could not open the file!" << endl;
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

    // Reset the swap and comparison counters
    mergesort_swaps = 0;
    mergesort_comparisons = 0;

    // Capture initial memory usage
    long memory_before = getMemoryUsage();

    // Start time measurement
    auto start = chrono::high_resolution_clock::now();

    // Perform Merge Sort
    mergesort(arr, 0, arr.size() - 1);

    // End time measurement
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> exec_time = end - start;

    // Capture final memory usage
    long memory_after = getMemoryUsage();
    long memory_change = memory_after - memory_before;

    // Output results
    cout << "Input Size: " << size << endl;
    cout << "Execution Time: " << exec_time.count() << " seconds" << endl;
    cout << "Number of Swaps: " << mergesort_swaps << endl;
    cout << "Number of Comparisons: " << mergesort_comparisons << endl;
    cout << "Memory Usage Change: " << memory_change << " KB" << endl;

    return 0;
}
