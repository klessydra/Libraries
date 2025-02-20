#ifndef KLESSYIDRA_EXCEPTION_HANDLER_H
#define KLESSYIDRA_EXCEPTION_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif


void instr_access_fault_handler_c(unsigned int mepc);
void load_access_fault_handler_c(unsigned int mepc);
void store_access_fault_handler_c(unsigned int mepc);
#ifdef __cplusplus
}
#endif

#endif // KLESSYIDRA_EXCEPTION_HANDLER_H
