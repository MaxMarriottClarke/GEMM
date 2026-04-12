#pragma once
#include "YmmVal.h"

extern void PackedMathF32_Iavx(YmmVal c[8], const YmmVal* a, const YmmVal* b);
extern void PackedMathF64_Iavx(YmmVal c[8], const YmmVal* a, const YmmVal* b);
