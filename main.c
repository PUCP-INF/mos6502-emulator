#include "init.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Error, missing start file.\n");
        exit(0);
    }
    init_cpu();
    load_file(argv[1]);
    run_program();
    free_cpu();
    return 0;
}