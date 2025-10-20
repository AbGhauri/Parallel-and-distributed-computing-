

# collector.py (run in WSL)
N = 10000000  # This should match the N in your sum_mpi.py run!

sums = []
for fname in ['sum_windows.txt', 'sum_wsl.txt']:
    with open(fname, 'r') as f:
        sums.append(int(f.read().strip()))

total_sum = sum(sums)
expected = N * (N + 1) // 2

print(f"Collected sums: {sums}")
print(f"Total sum: {total_sum}")
print(f"Expected: {expected}")
print(f"Match? {'YES' if total_sum == expected else 'NO'}")
