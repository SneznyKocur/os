#include "exception.h"

__attribute__((interrupt)) void divide_by_0_exception(interrupt_frame *intframe) {
    printf("default exception handler"); 
    intframe->ebp++;
}