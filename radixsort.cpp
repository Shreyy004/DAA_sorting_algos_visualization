#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include <iomanip>
#include <fstream>

using namespace std;

void counting_sort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);

    // Count occurrences of digits
    for (int i = 0; i < n; i++) {
        int index = arr[i] / exp;
        count[index % 10]++;
    }

    // Calculate cumulative count
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        int index = arr[i] / exp;
        output[count[index % 10] - 1] = arr[i];
        count[index % 10]--;
    }

    // Copy the sorted elements back into the original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radix_sort(vector<int>& arr) {
    if (arr.empty()) return;

    int max_val = *max_element(arr.begin(), arr.end());
    int exp = 1;

    while (max_val / exp > 0) {
        counting_sort(arr, exp);
        exp *= 10;
    }
}

SIZE_T getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize / 1024;
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
    input_file >> n;

    if (n <= 0) {
        cerr << "Number of elements must be positive." << endl;
        return 1;
    }

    vector<int> arr(n);

    for (int i = 0; i < n; ++i) {
        input_file >> arr[i];
    }

    input_file.close();

    SIZE_T mem_before = getMemoryUsage();
    auto start_time = chrono::high_resolution_clock::now();

    radix_sort(arr);

    auto end_time = chrono::high_resolution_clock::now();
    SIZE_T mem_after = getMemoryUsage();

    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    float duration_in_milliseconds = duration.count() / 1000.0;

    cout << fixed << setprecision(3);
    cout << "Total running time: " << duration_in_milliseconds << " milliseconds" << endl;
    cout<<"No Swaps"<<endl;
    cout<<"No Comparisosns"<<endl;
    cout << "Memory usage before sorting: " << mem_before << " KB" << endl;
    cout << "Memory usage after sorting: " << mem_after << " KB" << endl;
    cout << "Memory change: " << (mem_after - mem_before) << " KB" << endl;

    return 0;
}
