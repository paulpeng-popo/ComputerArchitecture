#include <stdio.h>
#include <stdint.h>

uint16_t count_leading_zeros(uint32_t x)
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

uint32_t reverseBits(uint32_t x)
{
    uint16_t n = count_leading_zeros(x);
    uint32_t y = x & 1;

    while (x >>= 1)
    {
        y = ((y << 1) | (x & 1));
    }

    return (y << n);
}

int main()
{
    uint32_t x1 = 0x4c000000;
    uint32_t x2 = 0x0000ffff;
    uint32_t x3 = 0x20001;
    uint32_t x4 = 0x80000002;
    uint32_t x5 = 0x0000ff00;
    uint32_t x6 = 0x0fc00000;
    printf("reverseBits(%x) = %d\n", x1, reverseBits(x1));
    printf("reverseBits(%x) = %d\n", x2, reverseBits(x2));
    printf("reverseBits(%x) = %d\n", x3, reverseBits(x3));
    printf("reverseBits(%x) = %d\n", x4, reverseBits(x4));
    printf("reverseBits(%x) = %d\n", x5, reverseBits(x5));
    printf("reverseBits(%x) = %d\n", x6, reverseBits(x6));
    return 0;
}
