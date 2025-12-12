import pandas as pd
import matplotlib.pyplot as plt
import pandas as pd

# Sample data
data = {
    'input_size': [100, 500, 1000],
    'execution_time_ms': [0.0109, 0.063, 0.0786],
    'number_of_swaps': [311, 2023, 4545],
    'number_of_comparisons': [718, 4542, 10082],
    'memory_change_kb': [12, 12, 12]
}

# Create DataFrame
df = pd.DataFrame(data)

# Save DataFrame to CSV file
df.to_csv('quicksort_results.csv', index=False)

# Load the data
data = pd.read_csv('quicksort_results.csv')

# Extract data
input_sizes = data['input_size']
execution_times = data['execution_time_ms']
number_of_swaps = data['number_of_swaps']
number_of_comparisons = data['number_of_comparisons']
memory_changes = data['memory_change_kb']

# Plot Execution Time
plt.figure(figsize=(12, 8))
plt.plot(input_sizes, execution_times, marker='o', color='r', linestyle='-', linewidth=2, markersize=8)
plt.xlabel('Input Size')
plt.ylabel('Execution Time (milliseconds)')
plt.title('Execution Time vs Input Size')
plt.grid(True)
plt.show()

# Plot Number of Swaps
plt.figure(figsize=(12, 8))
plt.plot(input_sizes, number_of_swaps, marker='o', color='b', linestyle='-', linewidth=2, markersize=8)
plt.xlabel('Input Size')
plt.ylabel('Number of Swaps')
plt.title('Number of Swaps vs Input Size')
plt.grid(True)
plt.show()

# Plot Number of Comparisons
plt.figure(figsize=(12, 8))
plt.plot(input_sizes, number_of_comparisons, marker='o', color='g', linestyle='-', linewidth=2, markersize=8)
plt.xlabel('Input Size')
plt.ylabel('Number of Comparisons')
plt.title('Number of Comparisons vs Input Size')
plt.grid(True)
plt.show()

# Plot Memory Change
plt.figure(figsize=(12, 8))
plt.plot(input_sizes, memory_changes, marker='o', color='m', linestyle='-', linewidth=2, markersize=8)
plt.xlabel('Input Size')
plt.ylabel('Memory Change (KB)')
plt.title('Memory Change vs Input Size')
plt.grid(True)
plt.show()
