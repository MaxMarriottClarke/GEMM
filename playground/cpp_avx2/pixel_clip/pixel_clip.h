#pragma once
#include <cstddef>
#include <cstdint>

struct ClipData 
{
    uint8_t* m_PbSrc;
    uint8_t* m_PbDes;
    size_t m_NumPixels;
    size_t m_NumClippedPixels;
    uint8_t m_ThreshLo;
    uint8_t m_ThreshHi;
};

extern void ClipPixels_Cpp(ClipData* clip_data);
extern void ClipPixels_Iavx2(ClipData* clip_data);

extern bool CheckArgs(const ClipData* clip_data);

extern void ClipPixels_bm(void);

const size_t c_Alignment = 32; // 256 bits / 8 bits per byte
const int c_RngMinVal = 0;
const int c_RngMaxVal = 255;
const unsigned int c_RngSeed = 157;
const uint8_t c_ThreshLo = 10;
const uint8_t c_ThreshHi = 245;
const size_t c_NumPixels = 8 * 1024 * 1024 + 31;
const size_t c_NumPixelsBM = 10000000;



