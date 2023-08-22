#include "../boot/multiboot2.h"
#include "../libc/stdio.h"
#include "../drivers/keyboard.h"
#include "../drivers/cpu/interrupts/idt.h"
#include "../drivers/cpu/interrupts/exception.h"
void kernel_main(unsigned long magic, unsigned long addr) {
    struct multiboot_tag *tag;
    struct multiboot_tag_framebuffer *tagfb;

    // taken from https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Example-OS-code

    /*  Am I booted by a Multiboot-compliant boot loader? */
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC)
    {
        return;
    }

    if (addr & 7)
    {
        return;
    }
    for (tag = (struct multiboot_tag *) (addr + 8);
        tag->type != MULTIBOOT_TAG_TYPE_END;
        tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag 
                                        + ((tag->size + 7) & ~7)))
    {
        switch (tag->type)
        {
        case MULTIBOOT_TAG_TYPE_FRAMEBUFFER:
            {
            tagfb = (struct multiboot_tag_framebuffer *) tag;
            
            
            break;
            }

        }
    }
    // interrupts
    init_idt();
    // exception handlers:
    set_idt_desctriptor(0,divide_by_0_exception,TRAP_GATE_FLAGS);
    multiboot_uint32_t color = 0x00ffffffff;
    unsigned x,y;
    x = y = 00;
    unsigned long *fb = (unsigned long) tagfb->common.framebuffer_addr;
    video_init(fb,tagfb->common.framebuffer_pitch);
    set_color(color,0);
    printf("testing 123 ");
    printf("making an interrupt rn");
    int i = 1/0;
    init_keyboard();
    
  
}
void keyboard_input(int scancode) {
    printf("scancode %i",scancode);
}
void kprint(char* c[]) {
    write_string(20,0,c);
}
