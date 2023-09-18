#include "../type.h"
#include "idt.h"
#include "../../../libc/stdio.h"  

__attribute__((interrupt)) void default_exception_handler(interrupt_frame *intframe) {
	printf("default exception handler"); 
    intframe->ebp++;
}

__attribute__((interrupt)) void default_exception_handler_code(interrupt_frame *intframe, uint32_t error_code) {
	printf("default exception handler: %h",error_code); 
    intframe->ebp++;
}

__attribute__((interrupt)) void default_int_handler(interrupt_frame *intframe ) {
	printf("default interrupt handler"); 
}
void set_idt_desctriptor(uint8_t entry_number, void *isr, uint8_t flags) {
	idt_entry_t *descriptor = &idt[entry_number];
    descriptor->isr_low = (uint32_t) isr & 0xFFFF; // get lower 16 bits
    descriptor->kernel_cs = (uint32_t) 8;
    descriptor->reserved = (uint32_t) 0;
    descriptor->attributes = (uint32_t) flags;
    descriptor->isr_high = ((uint32_t) isr << 16) & 0xFFFF;
}
void init_idt() {
    idtr.limit = (uint16_t) sizeof(idt_entry_t) * 256;
	idtr.base = (uint32_t) &idt[0];
	// exception ISRs
	for (int entry = 0; entry < 32; entry++) {
		if (entry == 8 || entry == 10 || entry == 11 || entry == 12 || entry == 13 || entry == 14 || entry == 17 || entry == 21)  {
			// exception with error code
			set_idt_desctriptor(entry,default_exception_handler_code,TRAP_GATE_FLAGS);
		}
		else {
			// exception with no error code 
			set_idt_desctriptor(entry,default_exception_handler,TRAP_GATE_FLAGS);
		}
		
	}
	// set up regular interrupts 
	for (uint16_t entry = 32; entry < 256; entry++) {
		set_idt_desctriptor(entry,default_int_handler,INT_GATE_FLAGS);
	}
	__asm__ __volatile__ ("lidt %0" : : "memory"(idtr));
}