# import torch

# # Create two random tensors
# x = torch.rand(2, 3)
# y = torch.rand(2, 3)

# print("Tensor X:")
# print(x)
# print("\nTensor Y:")
# print(y)

# # Add tensors
# z = x + y
# print("\nResult of X + Y:")
# print(z)

# # Matrix multiplication
# m = torch.matmul(x, y.T)  # Transpose Y for matrix multiply
# print("\nMatrix Multiplication (X * Y^T):")
# print(m)

# # Check if GPU is available
# if torch.cuda.is_available():
#     device = torch.device("cuda")
#     print("\nCUDA is available. Moving tensors to GPU...")
#     x = x.to(device)
#     y = y.to(device)
#     z = x + y
#     print("Result on GPU:")
#     print(z)
# else:
#     print("\nCUDA not available, running only on CPU.")



# import tensorflow as tf

# # Create two random tensors
# x = tf.random.uniform((2, 3))
# y = tf.random.uniform((2, 3))

# print("Tensor X:")
# print(x.numpy())

# print("\nTensor Y:")
# print(y.numpy())

# # Add tensors
# z = x + y
# print("\nResult of X + Y:")
# print(z.numpy())

# # Matrix multiplication
# m = tf.matmul(x, tf.transpose(y))
# print("\nMatrix Multiplication (X * Y^T):")
# print(m.numpy())

# Check if GPU is available
# print("\nAvailable Devices:")
# print(tf.config.list_physical_devices())



# import torch

# x = torch.rand(5000, 5000, device="mps")  # Runs on Apple GPU
# y = torch.rand(5000, 5000, device="mps")
# z = torch.matmul(x, y)
# print(z.device)  # mps:0 → Metal GPU



# import torch

# # Get number of threads PyTorch is using
# print("PyTorch is using", torch.get_num_threads(), "CPU threads")

# # (Optional) Force PyTorch to use fewer threads
# torch.set_num_threads(2)
# print("Now PyTorch will use", torch.get_num_threads(), "CPU threads")

# # Example computation
# x = torch.rand(5000, 5000)
# y = torch.rand(5000, 5000)
# z = torch.matmul(x, y)


# import tensorflow as tf

# # Get number of physical/logical devices
# print("TensorFlow devices:", tf.config.list_physical_devices('CPU'))

# # Get current thread settings
# print("Intra-op threads:", tf.config.threading.get_intra_op_parallelism_threads())
# print("Inter-op threads:", tf.config.threading.get_inter_op_parallelism_threads())

# # (Optional) Set threads (must be done before running ops)
# tf.config.threading.set_intra_op_parallelism_threads(2)
# tf.config.threading.set_inter_op_parallelism_threads(2)

# # Example computation
# x = tf.random.uniform((5000, 5000))
# y = tf.random.uniform((5000, 5000))
# z = tf.matmul(x, y)

# print("Computation done with limited threads.")


import tensorflow as tf

# Set thread counts before running any ops
tf.config.threading.set_intra_op_parallelism_threads(20)  # per-op parallelism
tf.config.threading.set_inter_op_parallelism_threads(2)  # across ops

print("Intra-op threads:", tf.config.threading.get_intra_op_parallelism_threads())
print("Inter-op threads:", tf.config.threading.get_inter_op_parallelism_threads())
