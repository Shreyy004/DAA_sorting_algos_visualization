import pandas as pd
import matplotlib.pyplot as plt

# Load the data
data = {
    'input_size': [100, 500, 1000],
    'execution_time': [0.00034734, 0.00106781, 0.00200462],
    'comparisons': [448, 2762, 6033],
    'memory_change': [12, 12, 24]
}

df = pd.DataFrame(data)

# Plot execution time
plt.figure(figsize=(10, 6))
plt.plot(df['input_size'], df['execution_time'], marker='o', linestyle='-', color='b')
plt.xlabel('Input Size')
plt.ylabel('Execution Time (seconds)')
plt.title('Execution Time vs. Input Size')
plt.grid(True)
plt.savefig('execution_time_vs_input_size.png')  # Save plot as PNG
plt.show()



# Plot comparisons
plt.figure(figsize=(10, 6))
plt.plot(df['input_size'], df['comparisons'], marker='o', linestyle='-', color='r')
plt.xlabel('Input Size')
plt.ylabel('Number of Comparisons')
plt.title('Number of Comparisons vs. Input Size')
plt.grid(True)
plt.savefig('comparisons_vs_input_size.png')  # Save plot as PNG
plt.show()

# Plot memory change
plt.figure(figsize=(10, 6))
plt.plot(df['input_size'], df['memory_change'], marker='o', linestyle='-', color='m')
plt.xlabel('Input Size')
plt.ylabel('Memory Change (KB)')
plt.title('Memory Change vs. Input Size')
plt.grid(True)
plt.savefig('memory_change_vs_input_size.png')  # Save plot as PNG
plt.show()
