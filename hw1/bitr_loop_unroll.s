.data
test1: .word 0x4c000000
test2: .word 0x0000ffff
test3: .word 0x20001
test4: .word 0x80000002
test5: .word 0x0000ff00
test6: .word 0x0fc00000

.text
main:
    lw a0, test6
    jal ra, bitrev

    # print result
    li a7, 1
    ecall

    # exit program
    li a7, 10
    ecall


clz:
    # prolouge
    addi sp, sp, -16
    sw ra, 12(sp)
    sw s0, 8(sp)
    sw s1, 4(sp)
    sw s2, 0(sp)

    # s0 = x
    add s0, a0, x0
    
    # make sure all bits to the right of the MSB are 1
    srli t0, s0, 1
    or s0, s0, t0
    srli t0, s0, 2
    or s0, s0, t0
    srli t0, s0, 4
    or s0, s0, t0
    srli t0, s0, 8
    or s0, s0, t0
    srli t0, s0, 16
    or s0, s0, t0

    # count ones (population count)
    srli t0, s0, 1
    li t1, 0x55555555
    and s1, t0, t1
    sub s0, s0, s1

    srli t0, s0, 2
    li t1, 0x33333333
    and s1, t0, t1
    and s2, s0, t1
    add s0, s1, s2

    srli t0, s0, 4
    add s0, s0, t0
    li t1, 0x0f0f0f0f
    and s0, s0, t1
    
    srli t0, s0, 8
    add s0, s0, t0

    srli t0, s0, 16
    add s0, s0, t0

    # mask 0x3f for popcount
    andi s0, s0, 0x3f
    
    # 32 - popcnt
    li t0, 0x20
    sub s0, t0, s0

    mv a0, s0

    # epilouge
    lw ra, 12(sp)
    lw s0, 8(sp)
    lw s1, 4(sp)
    lw s2, 0(sp)
    addi sp, sp, 16
    
    jr ra


bitrev:
    # prolouge
    addi sp, sp, -16
    sw ra, 12(sp)
    sw s0, 8(sp)
    sw s1, 4(sp)
    sw s2, 0(sp)

    # s0 = x
    add s0, a0, x0

    # s2 = n
    jal ra, clz
    mv s2, a0

    # s1 = y
    andi s1, s0, 1

bitrev_loop:
    srli s0, s0, 1
    beq s0, x0, bitrev_end
    
    slli s1, s1, 1
    andi t0, s0, 1
    or s1, s1, t0

    srli s0, s0, 1
    beq s0, x0, bitrev_end
    
    slli s1, s1, 1
    andi t0, s0, 1
    or s1, s1, t0

    srli s0, s0, 1
    beq s0, x0, bitrev_end
    
    slli s1, s1, 1
    andi t0, s0, 1
    or s1, s1, t0

    srli s0, s0, 1
    beq s0, x0, bitrev_end
    
    slli s1, s1, 1
    andi t0, s0, 1
    or s1, s1, t0

    srli s0, s0, 1
    beq s0, x0, bitrev_end
    
    slli s1, s1, 1
    andi t0, s0, 1
    or s1, s1, t0

    j bitrev_loop

bitrev_end:
    sll s1, s1, s2
    mv a0, s1

    # epilouge
    lw ra, 12(sp)
    lw s0, 8(sp)
    lw s1, 4(sp)
    lw s2, 0(sp)
    addi sp, sp, 16
    
    jr ra
