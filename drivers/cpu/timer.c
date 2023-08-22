#include "timer.h"
#include "interrupts/isr.h"
#include "ports.h"

uint32_t tick = 0;

static void timer_callback() {
    tick++;
}

void init_timer(uint32_t freq) {

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / freq;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
    /* Send the command */
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}

