#include "type.h"
#include "idt.h"
#include "../../../libc/stdio.h"
__attribute__((interrupt)) void default_exception_handler(interrupt_frame *intframe) {
    printf("default exception handler\n");
}   
__attribute__((interrupt)) void default_exception_handler(interrupt_frame *intframe, uint32_t error_code) {
    printf("default exception handler with error code: %h", error_code);
}

__attribute__((interrupt)) void default_interrupt_handler(interrupt_frame *intframe) {
    printf("default interrupt handler"); 
}

void set_idt_desctriptor(uint8_t entry_number, void *isr, uint8_t flags) {
    idt_entry_t *descriptor = &idt[entry_number];
    descriptor->isr_low = (uint32_t) isr & 0xFFFF; // get lower 16 bits
    descriptor->kernel_cs = (uint32_t) isr & 0xFFFF;
    descriptor->reserved = (uint32_t) isr & 0xFFFF;
    descriptor->attributes = (uint32_t) isr & 0xFFFF;
    descriptor->isr_high = (uint32_t) isr & 0xFFFF;

}