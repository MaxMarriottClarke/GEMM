# lx_single

## Theoretical Limit

Single-core GEMM benchmark on one assigned physical core of an Intel Xeon E5-2640 v3 (Haswell-EP, AVX2 + FMA, 2.60 GHz).

Single-core theoretical peak:

- SGEMM: `83.2 GFLOP/s`
- DGEMM: `41.6 GFLOP/s`

For matrix multiply, FLOP count is `2MNK`, so:

`GFLOP/s = 2MNK / (t x 1e9)`

## Numpy

NumPy baseline on this machine:

- Single precision: about `78 GFLOP/s` = `93.8%` of SGEMM peak
- Double precision: about `34.5 GFLOP/s` = `82.9%` of DGEMM peak

These are the reference numbers to beat.

# C++

## Naive

- Simple Implementation of Just C = A @ B
- Gets about 1/100 of NumPy performance

## Tiled

The tiled version breaks the matrix multiply into small `32 x 32` blocks instead of working on the full rows and columns at once.

It works by looping over tiles of `A`, `B`, and `C`, then doing the multiply and accumulate inside one small block before moving to the next one.

This speeds things up because the data being reused stays in cache for longer, so the CPU spends less time waiting on memory.

With this version we see about a `3x` speedup over the naive implementation.
