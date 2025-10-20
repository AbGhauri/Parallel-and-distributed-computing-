from mpi4py import MPI
import numpy as np
import platform

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

N = 10000000  # Change as needed

# Detect OS, split data accordingly
if platform.system() == "Windows":
    data = np.arange(1, N//2 + 1)   # Windows: first half
    outfile = 'sum_windows.txt'
else:
    data = np.arange(N//2 + 1, N + 1)  # WSL: second half
    outfile = 'sum_wsl.txt'

local_sum = np.sum(data)

# Each process saves its result
with open(outfile, 'w') as f:
    f.write(str(local_sum))

print(f"Partial sum on {platform.system()} ({outfile}): {local_sum}")

# Optionally, use MPI for future extension (not necessary for only two devices)
# If you want to combine with MPI reduce, you could use:
# total_sum = comm.reduce(local_sum, op=MPI.SUM, root=0)
# if rank == 0:
#     print(f"Total sum (MPI): {total_sum}")

# Otherwise, just run the collector script separately in WSL to combine both .txt files
