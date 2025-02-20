#include <stdio.h>
#include <stdlib.h>


void small_delay() {
    volatile int i;
    for (i = 0; i < 1000; i++); 
}

void instr_access_fault_handler_c(unsigned int mepc) {
    printf("Instruction access fault at : 0x%08X\n", mepc);
    fflush(stdout);  

    small_delay();  

exit(1);
}
void load_access_fault_handler_c(unsigned int mepc) {
printf("Load access fault at : 0x%08X\n", mepc);
    fflush(stdout);  

    small_delay();  

exit(1);
}


void store_access_fault_handler_c(unsigned int mepc) {
    printf("Store access fault at : 0x%08X\n", mepc);
    fflush(stdout);  

    small_delay();  

exit(1);
}
