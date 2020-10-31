#ifndef MOS6502_INIT_H
#define MOS6502_INIT_H

void init_cpu();
void load_file(const char* filename);
void print_ram();
void free_cpu();
void run_program();
void print_cpu();

#endif //MOS6502_INIT_H
