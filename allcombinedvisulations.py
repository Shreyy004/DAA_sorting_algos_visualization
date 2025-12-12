import matplotlib.pyplot as plt

# Data for different sorting algorithms
file_sizes = [100, 500, 1000]

# Radix Sort
radix_times = [0.014, 0.032, 0.0601]
radix_swaps = [0, 0, 0]
radix_comparisons = [0, 0, 0]
radix_memory_change = [12, 12, 15]

# Merge Sort
merge_times = [0.0019692, 0.0082625, 0.0156581]
merge_swaps = [0,0,0]
merge_comparisons = [2800,5000 , 11030]
merge_memory_change = [12, 12, 24]

# Bucket Sort
bucket_times = [0.0003, 0.00096, 0.00142]
bucket_swaps = [99, 499, 999]
bucket_comparisons = [297, 997, 1997]
bucket_memory_change = [0,12 , 32]

# Heap Sort
heap_times = [0.014, 0.045, 0.088]
heap_swaps = [100, 500, 1000]
heap_comparisons = [3000, 10000, 30000]
heap_memory_change = [12, 12, 12]

# Quick Sort
quick_times = [0.0109, 0.063, 0.0786]
quick_swaps = [311, 2023, 4545]
quick_comparisons = [718, 4542, 10082]
quick_memory_change = [12, 12, 12]

# Plot Execution Time
plt.figure(figsize=(12, 8))
plt.plot(file_sizes, radix_times, marker='o', linestyle='-', label='Radix Sort', color='blue')
plt.plot(file_sizes, merge_times, marker='o', linestyle='-', label='Merge Sort', color='green')
plt.plot(file_sizes, bucket_times, marker='o', linestyle='-', label='Bucket Sort', color='red')
plt.plot(file_sizes, heap_times, marker='o', linestyle='-', label='Heap Sort', color='purple')
plt.plot(file_sizes, quick_times, marker='o', linestyle='-', label='Quick Sort', color='orange')
plt.title('Execution Time vs. Number of Elements')
plt.xlabel('Number of Elements')
plt.ylabel('Execution Time (ms)')
plt.legend()
plt.grid(True)
plt.show()

# Plot Number of Swaps
plt.figure(figsize=(12, 8))
plt.plot(file_sizes, radix_swaps, marker='o', linestyle='-', label='Radix Sort', color='blue')
plt.plot(file_sizes, merge_swaps, marker='o', linestyle='-', label='Merge Sort', color='green')
plt.plot(file_sizes, bucket_swaps, marker='o', linestyle='-', label='Bucket Sort', color='red')
plt.plot(file_sizes, heap_swaps, marker='o', linestyle='-', label='Heap Sort', color='purple')
plt.plot(file_sizes, quick_swaps, marker='o', linestyle='-', label='Quick Sort', color='orange')
plt.title('Number of Swaps vs. Number of Elements')
plt.xlabel('Number of Elements')
plt.ylabel('Number of Swaps')
plt.legend()
plt.grid(True)

# Annotate Radix Sort data points
for i, txt in enumerate(radix_swaps):
    plt.annotate(f'{txt}', (file_sizes[i], radix_swaps[i]), textcoords="offset points", xytext=(0,10), ha='center', color='blue')

plt.show()

# Plot Number of Comparisons
plt.figure(figsize=(12, 8))
plt.plot(file_sizes, radix_comparisons, marker='o', linestyle='-', label='Radix Sort', color='blue')
plt.plot(file_sizes, merge_comparisons, marker='o', linestyle='-', label='Merge Sort', color='green')
plt.plot(file_sizes, bucket_comparisons, marker='o', linestyle='-', label='Bucket Sort', color='red')
plt.plot(file_sizes, heap_comparisons, marker='o', linestyle='-', label='Heap Sort', color='purple')
plt.plot(file_sizes, quick_comparisons, marker='o', linestyle='-', label='Quick Sort', color='orange')

# Set y-axis limits based on data range
plt.ylim(0, 50000)

plt.title('Number of Comparisons vs. Number of Elements')
plt.xlabel('Number of Elements')
plt.ylabel('Number of Comparisons')
plt.legend()
plt.grid(True)

# Optionally add annotations for key points
for i, txt in enumerate(quick_comparisons):
    plt.annotate(f'{txt}', (file_sizes[i], quick_comparisons[i]), textcoords="offset points", xytext=(0,10), ha='center', color='orange')

plt.show()

# Plot Memory Change
plt.figure(figsize=(12, 8))
plt.plot(file_sizes, radix_memory_change, marker='o', linestyle='-', label='Radix Sort', color='blue')
plt.plot(file_sizes, merge_memory_change, marker='o', linestyle='-', label='Merge Sort', color='green')
plt.plot(file_sizes, bucket_memory_change, marker='o', linestyle='-', label='Bucket Sort', color='red')
plt.plot(file_sizes, quick_memory_change, marker='o', linestyle='-', label='Quick Sort', color='orange')
plt.plot(file_sizes, heap_memory_change, marker='o', linestyle='-', label='Heap Sort', color='purple')
plt.title('Memory Change vs. Number of Elements')
plt.xlabel('Number of Elements')
plt.ylabel('Memory Change (KB)')
plt.legend()
plt.grid(True)
plt.show()
