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
    uint32_t x1 = 0b01001100000000000000000000000000;
    uint32_t x2 = 0b01001000000000000000000000000000;
    uint32_t x3 = 0b00000000000000100000000000000001;
    uint32_t x4 = 0b10000000000000000000000000000010;
    printf("reverseBits(%u) = %x\n", x1, reverseBits(x1));
    printf("reverseBits(%u) = %x\n", x2, reverseBits(x2));
    printf("reverseBits(%u) = %x\n", x3, reverseBits(x3));
    printf("reverseBits(%u) = %x\n", x4, reverseBits(x4));
    return 0;
}
