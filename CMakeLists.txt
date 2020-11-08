cmake_minimum_required(VERSION 3.17)

project(mos6502 C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/instr)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_library(gc gc)

add_executable(cpu
        main.c
        init.c
        init.h
        pipeline.c
        pipeline.h
        cpu.c
        cpu.h
        debug.c
        debug.h
        instr/adc.c
        instr/adc.h
        instr/and.c
        instr/and.h
        instr/asl.c
        instr/asl.h
        instr/impl.c
        instr/impl.h
        instr/ora.c
        instr/ora.h
        instr/rel.c
        instr/rel.h
        instr/jmp.c
        instr/jmp.h
        instr/bit.c
        instr/bit.h
        instr/rol.c
        instr/rol.h
        instr/eor.c
        instr/eor.h
        instr/lsr.c
        instr/lsr.h
        instr/ror.c
        instr/ror.h
        instr/sta.c
        instr/sta.h
        instr/sty.c
        instr/sty.h
        instr/stx.c
        instr/stx.h
        instr/ldy.c
        instr/ldy.h
        instr/lda.c
        instr/lda.h
        instr/ldx.c
        instr/ldx.h
        instr/cpy.c
        instr/cpy.h
        instr/cmp.c
        instr/cmp.h
        instr/dec.c
        instr/dec.h
        instr/cpx.c
        instr/cpx.h
        instr/sbc.c
        instr/sbc.h
        instr/inc.c
        instr/inc.h)

target_link_libraries(cpu gc)