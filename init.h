#ifndef MOS6502_INIT_H
#define MOS6502_INIT_H

void init_cpu();
void load_file(const char* filename);
void run_program();
void init_display();
void end_cpu();

#endif //MOS6502_INIT_H
