//------------------------------------------------
//               AlignedMem.h
//------------------------------------------------

#pragma once

#include <cstdint>
#include <stdexcept>
#include "OS.h"

class AlignedMem
{
public:
    static void* Allocate(size_t mem_size, size_t mem_alignment)
    {
        void* p = OS::AlignedMalloc(mem_size, mem_alignment);

        if (p == nullptr)
            throw std::runtime_error("Memory allocation error: AllocateAlignedMem()");

        return p;
    }

    static void Release(void* p)
    {
        OS::AlignedFree(p);
    }

    template <typename T>
    static bool IsAligned(const T* p, size_t alignment)
    {
        if (p == nullptr)
            return false;

        return ((uintptr_t)p % alignment) == 0;
    }
};
