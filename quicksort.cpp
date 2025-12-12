#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <windows.h>
#include <psapi.h>

using namespace std;

// Function to swap elements and count swaps
void swap_elements(int& a, int& b, int& swap_count) {
    int temp = a;
    a = b;
    b = temp;
    swap_count++;
}

// Function to partition the array and count comparisons and swaps
int partition(vector<int>& arr, int low, int high, int& swap_count, int& comparison_count) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparison_count++; // Increment comparison count
        if (arr[j] < pivot) {
            i++;
            if (i != j) {  // Only swap if the indices are different to avoid self-swapping
                swap_elements(arr[i], arr[j], swap_count);
            }
        }
    }
    swap_elements(arr[i + 1], arr[high], swap_count);
    return i + 1;
}

// Quick sort function
void quick_sort(vector<int>& arr, int low, int high, int& swap_count, int& comparison_count) {
    if (low < high) {
        int pivot_index = partition(arr, low, high, swap_count, comparison_count);
        quick_sort(arr, low, pivot_index - 1, swap_count, comparison_count);
        quick_sort(arr, pivot_index + 1, high, swap_count, comparison_count);
    }
}

// Function to get memory usage
SIZE_T getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize / 1024; // Convert to KB
    }
    return 0;
}

// Function to analyze sorting performance
void analyze_sorting(vector<int>& arr) {
    int swap_count = 0;
    int comparison_count = 0;

    SIZE_T mem_before = getMemoryUsage();
    auto start_time = chrono::high_resolution_clock::now();

    quick_sort(arr, 0, arr.size() - 1, swap_count, comparison_count);

    auto end_time = chrono::high_resolution_clock::now();
    SIZE_T mem_after = getMemoryUsage();

    double duration_seconds = chrono::duration<double>(end_time - start_time).count(); // Seconds

    // Print results
    cout << fixed << setprecision(10)
         << "Execution Time (s): " << duration_seconds << endl
         << "Memory Used Before (KB): " << mem_before << endl
         << "Memory Used After (KB): " << mem_after << endl
         << "Memory Change (KB): " << (mem_after - mem_before) << endl
         << "Number of Swaps: " << swap_count << endl
         << "Number of Comparisons: " << comparison_count << endl;
}

int main() {
    string filename;
    cout << "Enter the input file name: ";
    cin >> filename;

    ifstream input_file(filename);
    if (!input_file) {
        cerr << "Error: Cannot open file " << filename << endl;
        return 1;
    }

    int size;
    input_file >> size;

    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        input_file >> arr[i];
    }

    input_file.close();

    analyze_sorting(arr);

    return 0;
}
