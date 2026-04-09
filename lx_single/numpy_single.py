# NumPy GEMM baseline for this machine.
# Reference results from the single-core benchmark:
# - float32: about 78 GFLOP/s (~93.8% of 83.2 GFLOP/s peak)
# - float64: about 34.5 GFLOP/s (~82.9% of 41.6 GFLOP/s peak)
import numpy as np
import time
N = 1024

if __name__ == "__main__":
    A = np.random.rand(N, N).astype(np.float64)
    B = np.random.rand(N, N).astype(np.float64)
    

    flop = 2 * N * N * N
    print(f"{flop / 1e9:.2f} GFLOPS")

    for i in range(10):

        st = time.monotonic()
        C = A @ B
        et = time.monotonic()

        s = et - st
        print(f"GFLOPS/s: {flop/s / 1e9:.2f} GFLOPS/s")

        
