#include "pipeline.h"
#include "cpu.h"
#include "impl.h"
#include "ora.h"
#include "asl.h"
#include "rel.h"
#include "jmp.h"
#include "and.h"
#include "bit.h"
#include "rol.h"
#include "eor.h"
#include "lsr.h"
#include "ror.h"
#include "adc.h"
#include "sta.h"
#include "sty.h"
#include "stx.h"
#include "ldy.h"
#include "ldx.h"
#include "lda.h"
#include "cpy.h"
#include "cmp.h"
#include "dec.h"
#include "sbc.h"
#include "cpx.h"
#include "inc.h"

#include <stdio.h>

int fetch()
{
    return mem.ram[cpu.pch][cpu.pcl];
}

void execute(int op_ind)
{
    cpu.pcu = 0;
    uint8_t num = opcode_bytes[op_ind];
    void (*func) (void) = opcode_func[op_ind];
    func();
    updatepc(num);
}

void updatepc(uint8_t numbytes)
{
    if (!cpu.pcu) {
        // TODO: verificar que no nos salgamos de la pagina
        cpu.pcu = 0;
        cpu.pcl += numbytes;
    }
}

// look up table
void (*opcode_func[256])(void) = {
    brk, oraxind, NULL, NULL, NULL, orazpg, aslzpg, NULL, php, oraimmd, asla, NULL, NULL, oraabs, aslabs, NULL,
    bpl, oraindy, NULL, NULL, NULL, orazpgx, aslzpgx, NULL, clc, oraabsy, NULL, NULL, NULL, oraabsx, aslabsx, NULL,
    jsrabs, andxind, NULL, NULL, bitzpg, andzpg, rolzpg, NULL, plp, andimm, rola, NULL, bitabs, andabs, rolabs, NULL,
    bmi, andindy, NULL, NULL, NULL, andzpgx, rolzpgx, NULL, sec, andabsy, NULL, NULL, NULL, andabsx, rolabsx, NULL,
    rti, eorxind, NULL, NULL, NULL, eorzpg, lsrzpg, NULL, pha, eorimm, lsra, NULL, jmpabs, eorabs, lsrabs, NULL,
    bvc, eorindy, NULL, NULL, NULL, eorzpgx, lsrzpgx, NULL, cli, eorabsy, NULL, NULL, NULL, eorabsx, lsrabsx, NULL,
    rts, adcxind, NULL, NULL, NULL, adczpg, rorzpg, NULL, pla, adcimm, rora, NULL, jmpind, adcabs, rorabs, NULL,
    bvs, adcindy, NULL, NULL, NULL, adczpgx, rorzpgx, NULL, sei, adcabsy, NULL, NULL, NULL, adcabsx, rorabsx, NULL,
    NULL, staxind, NULL, NULL, styzpg, stazpg, stxzpg, NULL, dey, NULL, txa, NULL, styabs, staabs, stxabs, NULL,
    bcc, staindy, NULL, NULL, styzpgx, stazpgx, stxzpgy, NULL, tya, staabsy, txs, NULL, NULL, staabsx, NULL, NULL,
    ldyimm, ldaxind, ldximm, NULL, ldyzpg, ldazpg, ldxzpg, NULL, tay, ldaimm, tax, NULL, ldyabs, ldaabs, ldxabs, NULL,
    bcs, ldaindy, NULL, NULL, ldyzpgx, ldazpgx, ldxzpgy, NULL, clv, ldaabsy, tsx, NULL, ldyabsx, ldaabsx, ldxabsy, NULL,
    cpyimm, cmpxind, NULL, NULL, cpyzpg, cmpzpg, deczpg, NULL, iny, cmpimm, dex, NULL, cpyabs, cmpabs, decabs, NULL,
    bne, cmpindy, NULL, NULL, NULL, cmpzpgx, deczpgx, NULL, cld, cmpabsy, NULL, NULL, NULL, cmpabsx, decabsx, NULL,
    cpximm, sbcxind, NULL, NULL, cpxzpg, sbczpg, inczpg, NULL, inx, sbcimm, nop, NULL, cpxabs, sbcabs, incabs, NULL,
    beq, sbcindy, NULL, NULL, NULL, sbczpgx, inczpgx, NULL, sed, sbcabsy, NULL, NULL, NULL, sbcabsx, incabsx, NULL
};

uint8_t opcode_bytes[256] = {
        1, 2, 0, 0, 2, 2, 2, 0,
        1, 2, 1, 0, 3, 3, 3, 0,
        2, 2, 0, 0, 2, 2, 2, 0,
        1, 3, 1, 0, 3, 3, 3, 0,
        3, 2, 0, 0, 2, 2, 2, 0,
        1, 2, 1, 0, 3, 3, 3, 0,
        2, 2, 0, 0, 2, 2, 2, 0,
        1, 3, 1, 0, 3, 3, 3, 0,
        1, 2, 0, 0, 2, 2, 2, 0,
        1, 2, 1, 0, 3, 3, 3, 0,
        2, 2, 0, 0, 2, 2, 2, 0,
        1, 3, 1, 0, 3, 3, 3, 0,
        1, 2, 0, 0, 2, 2, 2, 0,
        1, 2, 1, 0, 3, 3, 3, 0,
        2, 2, 0, 0, 2, 2, 2, 0,
        1, 3, 1, 0, 3, 3, 3, 0,
        2, 2, 0, 0, 2, 2, 2, 0,
        1, 0, 1, 0, 3, 3, 3, 0,
        2, 2, 0, 0, 2, 2, 2, 0,
        1, 3, 1, 0, 0, 3, 0, 0,
        2, 2, 2, 0, 2, 2, 2, 0,
        1, 2, 1, 0, 3, 3, 3, 0,
        2, 2, 0, 0, 2, 2, 2, 0,
        1, 3, 1, 0, 3, 3, 3, 0,
        2, 2, 0, 0, 2, 2, 2, 0,
        1, 2, 1, 0, 3, 3, 3, 0,
        2, 2, 0, 0, 2, 2, 2, 0,
        1, 3, 1, 0, 3, 3, 3, 0,
        2, 2, 0, 0, 2, 2, 2, 0,
        1, 2, 1, 0, 3, 3, 3, 0,
        2, 2, 0, 0, 2, 2, 2, 0,
        1, 3, 1, 0, 3, 3, 3, 0
};