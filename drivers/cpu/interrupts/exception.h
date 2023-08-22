#include "idt.h"
#include "../../../libc/stdio.h"

__attribute__((interrupt)) void divide_by_0_exception(interrupt_frame *intframe)