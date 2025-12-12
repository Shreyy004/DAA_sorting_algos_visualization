import pandas as pd
import matplotlib.pyplot as plt

# Sample data
data = {
    'input_size': [100, 500, 1000],
    'execution_time_ms': [0.004, 0.014, 0.017],  # Adjusted for accuracy
    'number_of_swaps': [100, 500, 1000],
    'number_of_comparisons': [300, 1500, 3000],
    'memory_change_kb': [12, 12, 12]
}

# Create DataFrame
df = pd.DataFrame(data)

# Plot Execution Time
plt.figure(figsize=(12, 8))
plt.plot(df['input_size'], df['execution_time_ms'], marker='o', color='r', linestyle='-', linewidth=2, markersize=8)
plt.xlabel('Input Size')
plt.ylabel('Execution Time (milliseconds)')
plt.title('Execution Time vs Input Size')
plt.grid(True)
plt.show()

# Plot Number of Swaps
plt.figure(figsize=(12, 8))
plt.plot(df['input_size'], df['number_of_swaps'], marker='o', color='b', linestyle='-', linewidth=2, markersize=8)
plt.xlabel('Input Size')
plt.ylabel('Number of Swaps')
plt.title('Number of Swaps vs Input Size')
plt.grid(True)
plt.show()

# Plot Number of Comparisons
plt.figure(figsize=(12, 8))
plt.plot(df['input_size'], df['number_of_comparisons'], marker='o', color='g', linestyle='-', linewidth=2, markersize=8)
plt.xlabel('Input Size')
plt.ylabel('Number of Comparisons')
plt.title('Number of Comparisons vs Input Size')
plt.grid(True)
plt.show()

# Plot Memory Change
plt.figure(figsize=(12, 8))
plt.plot(df['input_size'], df['memory_change_kb'], marker='o', color='m', linestyle='-', linewidth=2, markersize=8)
plt.xlabel('Input Size')
plt.ylabel('Memory Change (KB)')
plt.title('Memory Change vs Input Size')
plt.grid(True)
plt.show()
