#pragma once
#include <cstddef>
#include <cstdint>

extern bool CalcMinMaxU8_Cpp(uint8_t* x_min, uint8_t* x_max, const uint8_t* x, size_t n);
extern bool CalcMinMaxU8_Iavx(uint8_t* x_min, uint8_t* x_max, const uint8_t* x, size_t n);

extern void InitArray(uint8_t* x, size_t n, unsigned int rng_seed);

extern void CalcMinMaxU8_bm();

const size_t c_NumElements = 10000000;
const unsigned int c_RngSeedVal = 23;


