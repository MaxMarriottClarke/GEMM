
#include <iostream>
#include "c2_min_max.h"
#include "AlignedMem.h"
#include "BmThreadTimer.h"

static void CalcMinMaxU8()
{
    size_t n = c_NumElements;
    AlignedArray<uint8_t> x_aa(n, 16);
    uint8_t* x = x_aa.Data();

    InitArray(x, n, c_RngSeedVal);

    uint8_t x_min1 = 0, x_max1 = 0;
    uint8_t x_min2 = 0, x_max2 = 0;

    bool rc1 = CalcMinMaxU8_Cpp(&x_min1, &x_max1, x, n);
    bool rc2 = CalcMinMaxU8_Iavx(&x_min2, &x_max2, x, n);

    std::cout << "\nResults for CalcMinMaxU8_Cpp\n";
    std::cout << "rc1: " << rc1 << "  x_min1: " << (int)x_min1;
    std::cout << "  x_max1: " << (int)x_max1 << '\n';
    std::cout << "\nResults for CalcMinMaxU8_Iavx\n";
    std::cout << "rc2: " << rc2 << "  x_min2: " << (int)x_min2;
    std::cout << "  x_max2: " << (int)x_max2 << '\n';
}


void CalcMinMaxU8_bm(void)
{
    std::cout << "\nRunning benchmark function CalcMinMaxU8_bm - please wait\n";

    size_t n = c_NumElements;
    AlignedArray<uint8_t> x_aa(n, 16);
    uint8_t* x = x_aa.Data();

    InitArray(x, n, c_RngSeedVal);

    uint8_t x_min0 = 0, x_max0 = 0;
    uint8_t x_min1 = 0, x_max1 = 0;

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        CalcMinMaxU8_Cpp(&x_min0, &x_max0, x, n);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        CalcMinMaxU8_Iavx(&x_min1, &x_max1, x, n);
        bmtt.Stop(i, 1);
    }

    std::string fn = bmtt.BuildCsvFilenameString("Ch02_06_CalcMinMaxU8_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times save to file " << fn << '\n';
}

int main()
{
    CalcMinMaxU8();
    CalcMinMaxU8_bm();
}
