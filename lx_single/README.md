# lx_single

## Theoretical Limit

This directory contains single-core GEMM benchmarks.

## Hardware

Benchmark machine:

- CPU: Intel Xeon E5-2640 v3 @ 2.60 GHz
- Microarchitecture: Haswell-EP
- ISA: AVX2 + FMA
- Sockets: 2
- Cores per socket: 8
- Total physical cores: 16
- Threads per core: 1

The machine has 16 physical cores in total, but this benchmark was run on only one scheduler-assigned core.

Assigned core for this run:

- CPU ID: 12
- Core ID: 12
- Socket: 0
- NUMA node: 0

Since there is 1 thread per core, this benchmark used exactly one physical core.

Relevant cache sizes:

- L1d: 32 KiB per core
- L2: 256 KiB per core
- L3: 20 MiB per socket

The core assignment can be checked with:

```bash
taskset -pc $$
lscpu -e=CPU,CORE,SOCKET,NODE
```

For this setup, the main reference point is the single-core compute peak.

## Theoretical Limit

This CPU supports 256-bit AVX2 vectors and FMA. On Haswell, one core can sustain up to 2 AVX2 FMA instructions per cycle.

### SGEMM peak

- 256 / 32 = 8 single-precision values per vector
- 1 FMA = 8 multiplies + 8 adds = 16 FLOPs
- 2 FMAs per cycle = 32 FLOPs/cycle/core

Using the base clock of 2.60 GHz:

`32 x 2.60e9 = 83.2e9 FLOP/s`

Single-core SGEMM peak: `83.2 GFLOP/s`

### DGEMM peak

- 256 / 64 = 4 double-precision values per vector
- 1 FMA = 4 multiplies + 4 adds = 8 FLOPs
- 2 FMAs per cycle = 16 FLOPs/cycle/core

Using the base clock of 2.60 GHz:

`16 x 2.60e9 = 41.6e9 FLOP/s`

Single-core DGEMM peak: `41.6 GFLOP/s`

### GEMM FLOP count

For multiplying an `M x K` matrix by a `K x N` matrix, the standard operation count is:

`2MNK`

If the multiplication takes `t` seconds, then:

`GFLOP/s = 2MNK / (t x 1e9)`

### Percent of peak

- SGEMM: `%peak = 100 x GFLOP/s / 83.2`
- DGEMM: `%peak = 100 x GFLOP/s / 41.6`

Example: if SGEMM reaches `65 GFLOP/s`, then:

`100 x 65 / 83.2 = 78.1%`

So that run achieves about `78.1%` of the single-core SGEMM peak.

## Numpy

# C++

## Naive
