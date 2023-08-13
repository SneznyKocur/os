#include "type.h"
#define TRAP_GATE_FLAGS 0x8F;
#define INT_GATE_FLAGS 0x8E;
#define INT_GATE_USER_FLAGS 0xEE; // privilege level is 3 (syscalls) 
typedef struct {
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     reserved;     // Set to zero
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;
typedef struct {
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed)) idtr_t;

__attribute__((aligned(0x10))) 
static idt_entry_t idt[256]; // Create an array of IDT entries; aligned for performance
static idtr_t idtr;

typedef struct {
    uint32_t ebp;
    uint32_t cs;
    uint32_t eflags;
    uint32_t sp;
    uint32_t ss; 
} __attribute__((packed)) interrupt_frame;

__attribute__((interrupt)) void default_exception_handler(interrupt_frame *intframe);

__attribute__((interrupt)) void default_exception_handler(interrupt_frame *intframe, uint32_t error_code);

__attribute__((interrupt)) void default_int_handler(interrupt_frame *intframe );

void set_idt_desctriptor(uint8_t entry_number, void *isr, uint8_t flags);