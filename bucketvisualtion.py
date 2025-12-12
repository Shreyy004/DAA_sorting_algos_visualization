import matplotlib.pyplot as plt

# Data from your updated results
file_sizes = [100, 500, 1000]
swaps = [197, 498, 998]
comparisons = [294, 995, 1995]
running_times = [0.03, 0.096, 0.142]
memory_before = [972, 968, 976]  # KB before sorting
memory_after = [972, 980, 1008]  # KB after sorting
additional_memory = [after - before for after, before in zip(memory_after, memory_before)]  # KB

# Plotting number of swaps
plt.figure(figsize=(12, 8))

plt.figure(figsize=(10, 6))
plt.plot(file_sizes, swaps, marker='o', linestyle='-', color='b')
plt.title('Number of Swaps vs. Number of Elements')
plt.xlabel('Number of Elements')
plt.ylabel('Number of Swaps')
plt.grid(True)
plt.show()

# Plotting number of comparisons
plt.figure(figsize=(10, 6))
plt.plot(file_sizes, comparisons, marker='o', linestyle='-', color='r')
plt.title('Number of Comparisons vs. Number of Elements')
plt.xlabel('Number of Elements')
plt.ylabel('Number of Comparisons')
plt.grid(True)
plt.show()

# Plotting running time
plt.figure(figsize=(10, 6))
plt.plot(file_sizes, running_times, marker='o', linestyle='-', color='g')
plt.title('Running Time vs. Number of Elements')
plt.xlabel('Number of Elements')
plt.ylabel('Running Time (ms)')
plt.grid(True)
plt.show()

# Plotting memory increase
plt.figure(figsize=(10, 6))
plt.plot(file_sizes, additional_memory, marker='o', linestyle='-', color='m')
plt.title('Additional Memory Usage vs. Number of Elements')
plt.xlabel('Number of Elements')
plt.ylabel('Additional Memory (KB)')
plt.grid(True)
plt.show()
