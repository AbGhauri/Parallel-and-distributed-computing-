# import numpy as np
# import time

# # Normal Python list
# lst = list(range(1_000_000))
# start = time.time()
# lst_squared = [x**2 for x in lst]
# print("List time:", time.time() - start)

# # NumPy array
# arr = np.arange(1_000_000)
# start = time.time()
# arr_squared = arr**2
# print("NumPy time:", time.time() - start)


# import multiprocessing
# import os
# import time

# # Function to simulate work
# def worker(task_id):
    
#     print(f"Task {task_id} running on process {os.getpid()}")
#     time.sleep(2)  # Simulate work
#     return f"Task {task_id} finished"

# if __name__ == "__main__":
#     num_cores = multiprocessing.cpu_count()   # Detect available CPU cores
#     print(f"Total CPU cores available: {num_cores}")

#     # Use exactly 6 cores (or fewer if system < 6)
#     with multiprocessing.Pool(processes=min(6, num_cores)) as pool:
#         results = pool.map(worker, range(6))

#     print("Results:", results)


# import multiprocessing

# if __name__ == "__main__":
#     num_cores = multiprocessing.cpu_count()   # Detect available CPU cores
#     print(f"Total CPU cores available: {num_cores}")


# hello_mpi.py
# from mpi4py import MPI

# comm = MPI.COMM_WORLD        # global communicator
# rank = comm.Get_rank()       # process ID (0, 1, 2...)
# size = comm.Get_size()       # total number of processes
# print(f"Hello from process {rank} out of {size}")
# mpiexec -n 4 python testingp.py


# send_recv.py
# from mpi4py import MPI

# comm = MPI.COMM_WORLD
# rank = comm.Get_rank()

# if rank == 0:
#     # Process 0 sends a message
#     data = "Hello from process 0"
#     comm.send(data, dest=1, tag=11)
#     print(f"Process {rank} sent: {data}")

# elif rank == 1:
#     # Process 1 receives the message
#     data = comm.recv(source=0, tag=11)
#     print(f"Process {rank} received: {data}")





# Numpy matrix multiplication with multiprocessing
import numpy as np
import time
import multiprocessing

# Check number of CPU cores available
print("CPU cores available:", multiprocessing.cpu_count())

# Create two big matrices (size 10,000 x 10,000)
N = 10
A = np.random.rand(N, N)
B = np.random.rand(N, N)
print("Matrix =",A)

# Time the multiplication
start = time.time()
C = np.dot(A, B)   # or A @ B // This is not pure python, uses optimized libraries
end = time.time()

print("Matrix multiplication finished")
print("Shape of result:", C.shape)
print("Time taken:", round(end - start, 2), "seconds")

# Note: This code uses NumPy which internally leverages optimized libraries (like BLAS, OpenMP) to utilize multiple CPU cores for operations like matrix multiplication. The actual parallelism is handled by these libraries, not explicitly in Python code.


# import numpy as np
# import time
# import multiprocessing

# np.__config__.show()

# Matrix size (make it big enough to see differences, but not crash memory)
N = 200  # Try 1000 if you have enough RAM

# Generate random matrices
# A = np.random.rand(N, N)
# B = np.random.rand(N, N)

# print (A)
# print (B)


# -----------------------------
# 1) Pure Python Implementation (single-core, very slow)
# -----------------------------
# start = time.time()
# C_pure = [[sum(A[i][k] * B[k][j] for k in range(N)) for j in range(N)] for i in range(N)]
# end = time.time()
# print(f"Pure Python (no cores): {round(end - start, 2)} seconds")

# -----------------------------
# 2) NumPy Implementation (multi-core, BLAS/OpenMP under the hood)
# -----------------------------
# start = time.time()
# C_numpy = np.dot(A, B)   # Uses multiple CPU cores
# end = time.time()
# print(f"NumPy (all {multiprocessing.cpu_count()} cores): {round(end - start, 2)} seconds")

# Verify results are close
# print("Results match:", np.allclose(C_pure, C_numpy))
