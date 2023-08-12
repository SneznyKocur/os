#include "../boot/multiboot2.h"


void kernel_main(unsigned long magic, unsigned long addr) {
    struct multiboot_tag *tag;
    struct multiboot_tag_framebuffer *tagfb;
    unsigned long *fb;

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
            
            *fb = (unsigned long) tagfb->common.framebuffer_addr;
            break;
            }

        }
    }

    multiboot_uint32_t color = 0x00ffffffff;
    unsigned x,y;
    for (x = 0; x < tagfb->common.framebuffer_width; x++) {
        for (y = 0; y < tagfb->common.framebuffer_height*4; y++) {
            multiboot_uint32_t *pixel = *fb + x + y * tagfb->common.framebuffer_pitch/4;
            *pixel = color;
        }
    }
  
}

