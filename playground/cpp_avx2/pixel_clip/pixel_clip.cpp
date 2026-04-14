#include "pixel_clip.h"
#include "AlignedMem.h"
#include <immintrin.h>

bool CheckArgs(const ClipData* clip_data) {
    if (clip_data->m_NumPixels == 0)
        return false;
    if (!AlignedMem::IsAligned(clip_data->m_PbSrc, c_Alignment))
        return false;
    if (!AlignedMem::IsAligned(clip_data->m_PbDes, c_Alignment))
        return false;
    return true;
}

void ClipPixels_Cpp(ClipData* clip_data)
{
    if (!CheckArgs(clip_data))
        throw std::runtime_error("Invalid arguments");

    uint8_t* pb_src = clip_data->m_PbSrc;
    uint8_t* pb_des = clip_data->m_PbDes;
    size_t num_pixels = clip_data->m_NumPixels;
    size_t num_clipped_pixels = 0;
    uint8_t thresh_lo = clip_data->m_ThreshLo;
    uint8_t thresh_hi = clip_data->m_ThreshHi;

    for (size_t i = 0; i < num_pixels; i++)
    {
        uint8_t pixel = pb_src[i];

        if (pixel < thresh_lo)
        {
            pb_des[i] = thresh_lo;
            num_clipped_pixels++;
        }
        else if (pixel > thresh_hi)
        {
            pb_des[i] = thresh_hi;
            num_clipped_pixels++;
        }
        else
            pb_des[i] = pb_src[i];
    }

    clip_data->m_NumClippedPixels = num_clipped_pixels;

}

void ClipPixels_Iavx2(ClipData* clip_data)
{
    if (!CheckArgs(clip_data))
        throw std::runtime_error("ClipPixels_Iavx2() - CheckArgs failed");

    uint8_t* pb_src = clip_data->m_PbSrc;
    uint8_t* pb_des = clip_data->m_PbDes;
    size_t num_pixels = clip_data->m_NumPixels;
    size_t num_clipped_pixels = 0;
    uint8_t thresh_lo = clip_data->m_ThreshLo;
    uint8_t thresh_hi = clip_data->m_ThreshHi;

    size_t i = 0;
    const size_t num_simd_elements = 32;

    // Create packed versions of thresh_lo and thresh_hi
    __m256i packed_thresh_lo = _mm256_set1_epi8(thresh_lo);
    __m256i packed_thresh_hi = _mm256_set1_epi8(thresh_hi);

    for (; num_pixels - i >= num_simd_elements; i += num_simd_elements)
    {
        __m256i pb_src_vals = _mm256_load_si256((__m256i*)&pb_src[i]);
        __m256i temp1 = _mm256_max_epu8(pb_src_vals, packed_thresh_lo);
        __m256i pb_des_vals = _mm256_min_epu8(temp1, packed_thresh_hi);

        _mm256_store_si256((__m256i*)&pb_des[i], pb_des_vals);

        __m256i temp2 = _mm256_cmpeq_epi8(pb_des_vals, pb_src_vals);
        unsigned int count_mask_eq = _mm256_movemask_epi8(temp2);
        num_clipped_pixels += _mm_popcnt_u32(~count_mask_eq);
    }

    for (; i < num_pixels; i++)
    {
        uint8_t pixel = pb_src[i];

        if (pixel < thresh_lo)
        {
            pb_des[i] = thresh_lo;
            num_clipped_pixels++;
        }
        else if (pixel > thresh_hi)
        {
            pb_des[i] = thresh_hi;
            num_clipped_pixels++;
        }
        else
            pb_des[i] = pb_src[i];
    }

    clip_data->m_NumClippedPixels = num_clipped_pixels;
}
