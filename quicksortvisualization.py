import time
import os
import psutil
import matplotlib.pyplot as plt

# Function to read data from file
def read_data_from_file(filename):
    with open(filename, 'r') as file:
        data = file.read().strip()
        # Remove any non-numeric characters (keeping only digits and commas)
        clean_data = ''.join(char if char.isdigit() or char == ',' else '' for char in data)
        # Convert data to list of integers
        return list(map(int, clean_data.split(',')))

# Placeholder for global variables
swaps = 0
comparisons = 0

# Quick sort implementation
def quick_sort(arr, low, high):
    global swaps, comparisons
    if low < high:
        pivot_index = partition(arr, low, high)
        quick_sort(arr, low, pivot_index - 1)
        quick_sort(arr, pivot_index + 1, high)

def partition(arr, low, high):
    global swaps, comparisons
    pivot = arr[high]
    i = low - 1
    for j in range(low, high):
        comparisons += 1
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
            swaps += 1
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    swaps += 1
    return i + 1

# Function to get memory usage in KB
def get_memory_usage():
    process = psutil.Process(os.getpid())
    mem_info = process.memory_info()
    return mem_info.rss / 1024  # Convert to KB

# Function to analyze execution time
def qs_analyze_time(file_list):
    global swaps, comparisons
    execution_times = []
    swaplist = []
    comparelist = []
    memory_changes = []
    input_sizes = []

    for file in file_list:
        arr = read_data_from_file(file)
        swaps = 0
        comparisons = 0

        mem_before = get_memory_usage()
        start_time = time.perf_counter()
        quick_sort(arr, 0, len(arr) - 1)
        end_time = time.perf_counter()
        mem_after = get_memory_usage()

        execution_time = (end_time - start_time) * 1000  # Convert to milliseconds
        memory_change = mem_after - mem_before
        input_size = len(arr)

        execution_times.append(execution_time)
        swaplist.append(swaps)
        comparelist.append(comparisons)
        memory_changes.append(memory_change)
        input_sizes.append(input_size)

        print(f"File: {file}")
        print(f"Execution Time: {execution_time:.3f} milliseconds")
        print(f"Number of Swaps: {swaps}")
        print(f"Number of Comparisons: {comparisons}")
        print(f"Memory Usage Before: {mem_before:.2f} KB")
        print(f"Memory Usage After: {mem_after:.2f} KB")
        print(f"Memory Change: {memory_change:.2f} KB")
        print("-" * 30)
    
    return input_sizes, execution_times, swaplist, comparelist, memory_changes

# List of input files
input_files = ['random100.txt', 'random500.txt', 'random1000.txt']
input_sizes, execution_times, swaplist, comparelist, memory_changes = qs_analyze_time(input_files)

# Plotting
# Plot Execution Time
fig, ax = plt.subplots(figsize=(12, 8))
plt.plot(input_sizes, execution_times, marker='o', color='r', markersize=14, linewidth=3)
plt.xlabel('Input Size')
plt.ylabel('Execution Time (milliseconds)')
plt.title('In-place Quick Sort TIME Performance')
plt.grid(True)
plt.show()

# Plot Number of Swaps
fig, ax = plt.subplots(figsize=(12, 8))
plt.plot(input_sizes, swaplist, marker='o', color='m', markersize=14, linewidth=3)
plt.xlabel('Input Size')
plt.ylabel('Number of Swaps')
plt.title('In-place Quick Sort SWAP Analysis')
plt.grid(True)
plt.show()

# Plot Number of Comparisons
fig, ax = plt.subplots(figsize=(12, 8))
plt.plot(input_sizes, comparelist, marker='o', color='k', markersize=14, linewidth=3)
plt.xlabel('Input Size')
plt.ylabel('Number of Comparisons')
plt.title('In-place Quick Sort COMPARISONS Analysis')
plt.grid(True)
plt.show()

# Plot Memory Change
fig, ax = plt.subplots(figsize=(12, 8))
plt.plot(input_sizes, memory_changes, marker='o', color='b', markersize=14)
plt.xlabel('Input Size')
plt.ylabel('Memory Change (KB)')
plt.title('In-place Quick Sort MEMORY Analysis')
plt.grid(True)
plt.show()
