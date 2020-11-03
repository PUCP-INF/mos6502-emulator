#ifndef MOS6502_PIPELINE_H
#define MOS6502_PIPELINE_H

#include <stdint.h>

int fetch();
void execute(int op_ind);
void updatepc(uint8_t numbytes);

extern uint8_t opcode_bytes[256];
extern void (*opcode_func[256])(void);

#endif //MOS6502_PIPELINE_H
