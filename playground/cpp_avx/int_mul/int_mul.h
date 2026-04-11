#pragma once
#include "XmmVal.h"

extern void MulI16_Iavx(XmmVal c[2], const XmmVal* a, const XmmVal* b);
extern void MulI32a_Iavx(XmmVal* c, const XmmVal* a, const XmmVal* b);
extern void MulI32b_Iavx(XmmVal c[2], const XmmVal* a, const XmmVal* b);
