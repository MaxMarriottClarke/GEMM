#include <chrono>
#include <cstddef>
#include <cstring>
#include <stdio.h>
#include <immintrin.h>
#include "../include/Naive_avx.h"


#define N 1024

float A[N][N];
float B[N][N];
float C[N][N];

void MatrixMulF32_Iavx(float* c, const float* a, const float* b, size_t n) {
    constexpr size_t simd_width = 8;
    std::memset(c, 0, n * n * sizeof(float));

    for (size_t i = 0; i < n; i++) {
        float* c_row = c + i * n;
        const float* a_row = a + i * n;

        for (size_t k = 0; k < n; k++) {
            const __m256 a_vals = _mm256_set1_ps(a_row[k]);
            const float* b_row = b + k * n;
            const float a_scalar = a_row[k];
            const size_t simd_end = n - (n % simd_width);

            size_t j = 0;
            for (; j < simd_end; j += simd_width) {
                __m256 c_vals = _mm256_loadu_ps(c_row + j);
                const __m256 b_vals = _mm256_loadu_ps(b_row + j);
                c_vals = _mm256_fmadd_ps(a_vals, b_vals, c_vals);
                _mm256_storeu_ps(c_row + j, c_vals);
            }

            for (; j < n; j++) {
                c_row[j] += a_scalar * b_row[j];
            }
        }
    }
}

static void InitMatrices() {
    for (size_t x = 0; x < N; x++) {
        for (size_t y = 0; y < N; y++) {
            A[x][y] = static_cast<float>(((x + y) % 13) + 1) * 0.125f;
            B[x][y] = static_cast<float>(((x * 3 + y * 5) % 17) - 8) * 0.125f;
        }
    }
}

static double Checksum() {
    double sum = 0.0;

    for (size_t x = 0; x < N; x++) {
        for (size_t y = 0; y < N; y++) {
            sum += C[x][y];
        }
    }

    return sum;
}


int main() {
    InitMatrices();

    auto flop = 2.0 * N * N * N;
    printf("GFLOPS: %.2f\n", flop * (1e-9));


    for (auto l = 0; l < 10; l++) {

        auto start = std::chrono::steady_clock::now();

        MatrixMulF32_Iavx(&C[0][0], &A[0][0], &B[0][0], N);

        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        auto gflops = flop / (duration * 1e6); 
        printf("GFLOPS/s: %.2f\n", gflops);
        

            
    }

    printf("Checksum: %.5f\n", Checksum());
    
    return 0;
}
