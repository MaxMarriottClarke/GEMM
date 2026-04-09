#include <cassert>
#include <chrono>
#include <stdio.h>

#define N 1024
#define TILE 32

float A[N][N];
float B[N][N];
float C[N][N];

int main() {
    assert(N % TILE == 0);

    auto flop = 2.0 * N * N * N;
    printf("GFLOPS: %.2f\n", flop * (1e-9));

    for (auto l = 0; l < 10; l++) {
        auto start = std::chrono::steady_clock::now();

        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                C[row][col] = 0.0f;
            }
        }

        for (int ii = 0; ii < N; ii += TILE) {
            for (int kk = 0; kk < N; kk += TILE) {
                for (int jj = 0; jj < N; jj += TILE) {
                    for (int row = ii; row < ii + TILE; row++) {
                        float* c_row = C[row];
                        float* a_row = A[row];

                        for (int k = kk; k < kk + TILE; k++) {
                            const float a_val = a_row[k];
                            float* b_row = B[k];

                            for (int col = jj; col < jj + TILE; col++) {
                                c_row[col] += a_val * b_row[col];
                            }
                        }
                    }
                }
            }
        }

        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        auto gflops = flop / (duration * 1e6);
        printf("GFLOPS/s: %.2f\n", gflops);
    }

    return 0;
}
