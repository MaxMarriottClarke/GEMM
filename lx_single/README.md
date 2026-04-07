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
