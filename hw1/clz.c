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

/*
    popcount(x) = x 的二進位表示法中 1 的個數

    x -= ((x >> 1) & 0x55555555)
    x = 0000 0110 1010 1010 1010 1010 1010 1010
    # 每 2 bits 其 1 的個數，用 2 bits 表示

    x = ((x >> 2) & 0x33333333) + (x & 0x33333333)
    x = 0000 0011 0100 0100 0100 0100 0100 0100
    # 每 4 bits 其 1 的個數，用 3 bits 表示

    x = ((x >> 4) + x) & 0x0f0f0f0f
    x = 0000 0011 0000 1000 0000 1000 0000 1000
    # 每 8 bits 其 1 的個數，用 4 bits 表示

    x += (x >> 8)
    x = 0000 0011 0000 1011 0001 0000 0001 0000
    # 每 16 bits 其 1 的個數，用 5 bits 表示

    x += (x >> 16)
    x = 0000 0011 0000 1011 0001 0011 0001 1011
    # 每 32 bits 其 1 的個數，用 6 bits 表示

    x & 0x3f =
      = 0000 0000 0000 0000 0000 0000 0001 1011
    # 用 mask 0x3f 取出最後 6 bits
*/

int main()
{
    // x1 = 16, x2 = 33
    // clz(x1) = 27, clz(x2) = 26
    uint32_t x1 = 0x00000010;
    uint32_t x2 = 0x00000021;
    printf("clz(%d) = %d\n", x1, count_leading_zeros(x1));
    printf("clz(%d) = %d\n", x2, count_leading_zeros(x2));
    return 0;
}
