#pragma once
#include <cstddef>
#include <cstdint>

extern bool CalcMeanU8_Cpp(double* mean_x, uint64_t* sum_x, const uint8_t* x, size_t n);
extern bool CalcMeanU8_Iavx(double* mean_x, uint64_t* sum_x, const uint8_t* x, size_t n);

extern void InitArray(uint8_t* x, size_t n, unsigned int seed);
extern bool CheckArgs(const uint8_t* x, size_t n);

extern void CalcMeanU8_bm(void);

const size_t c_NumElements = 10000000;
const size_t c_Alignment = 16;
const unsigned int c_RngSeedVal = 29;
extern "C" size_t g_NumElementsMax;
