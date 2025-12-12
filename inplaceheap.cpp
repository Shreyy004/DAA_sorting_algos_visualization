#include <iostream>
#include <vector>
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

int heap_swaps = 0;
int heap_comparisons = 0;

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    heap_comparisons++;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Compare right child with the largest
    heap_comparisons++;
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // Swap and heapify if needed
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heap_swaps++;
        heapify(arr, n, largest);
    }
}

void heap_sort(vector<int>& arr) {
    int n = arr.size();

    // Build a max heap
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }

    // Extract elements from heap one by one
    for (int i = n - 1; i >= 0; --i) {
        // Move current root to end
        swap(arr[0], arr[i]);
        heap_swaps++;
        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

SIZE_T getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize / 1024; // Convert to KB
    }
    return 0;
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

    int n;
    input_file >> n; // Read the number of elements

    if (n <= 0) {
        cerr << "Error: The number of elements must be positive." << endl;
        return 1;
    }

    vector<int> arr(n);
    string line;
    getline(input_file, line); // Read the rest of the line containing elements

    istringstream iss(line);
    string temp;
    int index = 0;

    while (getline(iss, temp, ' ')) {
        arr[index++] = stoi(temp);
    }

    input_file.close();

    if (arr.empty()) {
        cerr << "Error: The input file is empty or contains no valid integers." << endl;
        return 1;
    }

    SIZE_T mem_before = getMemoryUsage();
    auto start_time = chrono::high_resolution_clock::now();

    heap_sort(arr);

    auto end_time = chrono::high_resolution_clock::now();
    SIZE_T mem_after = getMemoryUsage();

    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    double duration_in_milliseconds = duration.count() / 1000.0; // Convert microseconds to milliseconds

    cout << fixed << setprecision(6);
    cout << "Total running time: " << duration_in_milliseconds << " milliseconds" << endl;
    cout << "Memory usage before sorting: " << mem_before << " KB" << endl;
    cout << "Memory usage after sorting: " << mem_after << " KB" << endl;
    cout << "Memory change: " << (mem_after - mem_before) << " KB" << endl;
    cout << "Total swaps: " << heap_swaps << endl;
    cout << "Total comparisons: " << heap_comparisons << endl;

    return 0;
}
