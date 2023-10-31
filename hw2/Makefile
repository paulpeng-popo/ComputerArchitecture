SRC = range
OUT = a.elf
OPT = -O0

.PHONY: clean

ASFLAGS = -march=rv32i_zicsr_zifencei -mabi=ilp32

$(OUT): $(SRC).o
	riscv-none-elf-gcc -o $(OUT) $(SRC).o

$(SRC).o: $(SRC).s
	riscv-none-elf-gcc $(OPT) -c -o $(SRC).o $(SRC).s

$(SRC).s: $(SRC).c
	riscv-none-elf-gcc $(OPT) -S -o $(SRC).s $(SRC).c

clean:
	rm -f $(SRC).s $(SRC).o $(OUT)
