## Environment setup

### riscv-gnu-toolchain
```bash
$ cd riscv-gnu-toolchain
$ mkdir build && cd build
$ ../configure --prefix=$RISCV --with-arch=rv32i --with-abi=ilp32
$ make -j $(nproc)
```

### spike
```bash
$ cd riscv-isa-sim
$ mkdir build && cd build
$ ../configure --prefix=$RISCV
$ make -j $(nproc)
$ sudo make install
```

### riscv proxy kernel
```bash
$ cd riscv-pk
$ mkdir build && cd build
$ ../configure --prefix=$RISCV --host=riscv32-unknown-elf
$ make -j $(nproc)
$ sudo make install
```
