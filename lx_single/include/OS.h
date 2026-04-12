//------------------------------------------------
//               OS.h
//------------------------------------------------

#pragma once

#include <cstdlib>
#include <cstdint>
#include <malloc.h>
#include <string>

#if defined(_MSC_VER)
#include <windows.h>
#elif defined(__GNUG__)
#include <unistd.h>
#else
#error Unexpected target in OS.h
#endif

class OS
{
public:
    static std::string GetComputerName(void)
    {
        std::string computer_name;
        const size_t cn_len = 256;
        char cn[cn_len] = { '\0' };

#if defined(_MSC_VER)
        size_t cn_len_ret;

        if (getenv_s(&cn_len_ret, cn, cn_len * sizeof(char), "COMPUTERNAME") == 0)
            computer_name = cn;
#endif

#if defined(__GNUG__)
        if (gethostname(cn, cn_len) == 0)
            computer_name = cn;
#endif

        return computer_name;
    }

    static void AlignedFree(void* p)
    {
#if defined(_MSC_VER)
        _aligned_free(p);
#endif

#if defined(__GNUG__)
        free(p);
#endif
    }

    static void* AlignedMalloc(size_t mem_size, size_t mem_alignment)
    {
        void* p;

#if defined(_MSC_VER)
        p = _aligned_malloc(mem_size, mem_alignment);
#endif

#if defined(__GNUG__)
        p = aligned_alloc(mem_alignment, mem_size);
#endif

        return (p != NULL) ? p : nullptr;
    }
};
