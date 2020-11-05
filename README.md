# mos6502-emulator

## Instrucciones de compilacion

1. Descargar librerias y programas necesarios
```
$ sudo apt install libgc-dev git build-essential wget
$ wget https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4-Linux-x86_64.tar.gz
$ untar xf cmake-3.18.4-Linux-x86_64.tar.gz
$ export PATH=$PATH:$PWD/cmake-3.18.4-Linux-x86_64/bin/
$ wget https://github.com/PUCP-INF/mos6502-emulator/releases/download/0.1/acme_0.96.4-5_amd64.deb
$ sudo dpkg -i acme_0.96.4-5_amd64.deb
```

2. Compilar el emulador
```
$ git clone https://github.com/PUCP-INF/mos6502-emulator.git
$ cd mos6502-emulator
$ mkdir build && cd build
$ cmake .. && make
$ acme ../test.s
$ ./cpu test
```
