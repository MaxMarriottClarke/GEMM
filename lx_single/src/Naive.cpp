#include <chrono>
#include <stdio.h>

#define N 1024

float A[N][N];
float B[N][N];
float C[N][N];

int main() {

    auto flop = 2.0 * N * N * N;
    printf("GFLOPS: %.2f\n", flop * (1e-9));


    for (auto l = 0; l < 10; l++) {

        auto start = std::chrono::steady_clock::now();
        for (auto x = 0; x < N; x++) {
            for (auto y = 0; y < N; y++) {
                float acc = 0.0;
                for (auto k = 0; k < N; k++) {
                    acc += A[x][k] * B[k][y];
                }
                C[x][y] = acc;
            }
        }

        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        auto gflops = flop / (duration * 1e6); 
        printf("GFLOPS/s: %.2f\n", gflops);
        

            
    }
   
    return 0;
}
