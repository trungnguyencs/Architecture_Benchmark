import numpy as np
import tensorflow as tf
a = np.array([1])
arr = []
for i in range(1000):
  for j in range(1000):
      arr.append(i*j)