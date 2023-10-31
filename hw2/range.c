#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

uint16_t clz(uint32_t x)
{
    /* make sure all bits to the right of the MSB are 1 */
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);

    /* count ones (population count) */
    x -= ((x >> 1) & 0x55555555);
    x = ((x >> 2) & 0x33333333) + (x & 0x33333333);
    x = ((x >> 4) + x) & 0x0f0f0f0f;
    x += (x >> 8);
    x += (x >> 16);

    return (32 - (x & 0x3f));
}

// This function returns the cycle count of the CPU.
static inline uint64_t
read_cycles(void)
{
    uint64_t cycles;
    __asm__ volatile("rdcycle %0" : "=r"(cycles));
    return cycles;
}

int rangeBitwiseAnd2(int L, int R)
{
    if (L == R)
        return L;
    return L & ~(0xFFFFFFFF >> clz(L ^ R));
}

int rangeBitwiseAnd(int left, int right)
{
    int res = 0;
    while (left != right)
    {
        left >>= 1;
        right >>= 1;
        res += 1;
    }
    return left << res;
}

int main()
{
    int left = 26, right = 30;
    uint64_t cnt0 = read_cycles();
    printf("%d\n", rangeBitwiseAnd2(left, right));
    uint64_t cyclecount = read_cycles() - cnt0;
    printf("Cycle Count: %u\n", (unsigned int)cyclecount);
    return 0;
}
