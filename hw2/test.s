.data
d1_33: .word 0x33333333
d2_0f: .word 0x0f0f0f0f
d3_55: .word 0x55555555

d_testing: .word 0x01000000
int_max: .word 0x7fffffff

.global main

.text
main:

    addi a0, zero, 5
    addi a1, zero, 7
    call rangeBitwiseAnd
    call print
    
    call end

.text
rangeBitwiseAnd:
    # a0, a1 as input, dword
    #prologue
    addi sp, sp, -12
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    # s0 = a0, s1 = a1
    mv s0, a0
    mv s1, a1
    
    beq s0, s1, rangedBitWiseAndEnd
    
    xor a0, s0, s1
    call count_leading_zeros
    mv t1, a0
    
    # load int max
    la t0, int_max
    lw t0, 0(t0)
    
    srl t0, t0, t1
    not t0, t0
    and s0, s0, t0

    
rangedBitWiseAndEnd:
    #epilogue
    mv a0, s0
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    addi sp, sp, 12
    jr ra


.text
count_leading_zeros:
    #prologue
    addi sp, sp, -12
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    
    # start shifting
    # input : a0
    
    mv s0, a0            # x = input
    srli s1, s0, 1       # x >> 1
    or s0, s1, s0        # x |= (x >> 1)

    srli s1, s0, 2       # x >> 2
    or s0, s1, s0        # x |= (x >> 2)
    
    srli s1, s0, 4       # x >> 4
    or s0, s1, s0        # x |= (x >> 4)
    
    srli s1, s0, 8       # x >> 8
    or s0, s1, s0        # x |= (x >> 8)    
    
    srli s1, s0, 16       # x >> 16
    or s0, s1, s0        # x |= (x >> 16)    
    
    la t0, d3_55
    lw t0, 0(t0)
    
    srli s1, s0, 1    
    and s1, s1, t0
    sub s0, s0, s1    # x -= ((x >> 1) & 0x55555555)
    
    la t0, d1_33
    lw t0, 0(t0)
    
    srli s1, s0, 2
    and s1, s1, t0
    and t1, s0, t0
    add s0, t1, s1     # x = ((x >> 2) & 0x33333333) + (x & 0x33333333);
    
    la t0, d2_0f
    lw t0, 0(t0)
    
    srli s1, s0, 4
    add s1, s1, s0
    and s0, s1, t0     # x = ((x >> 4) + x) & 0x0f0f0f0f;
    
    srli s1, s0, 8
    add s0, s1, s0
    
    srli s1, s0, 16
    add s0, s1, s0
    
    addi t0, zero, 32
    andi s0, s0, 0x7f
    sub a0, t0, s0        # return (32 - (x & 0x7f));
    
    #epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    addi sp, sp, 12
    jr ra
    
print:
    li a7, 1
    ecall
    jr ra
end:
    li a0, 0
    li a7, 63
    ecall
