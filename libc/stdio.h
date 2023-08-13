static void itoa (char *buf, int base, int d);
void putpixel(unsigned long *fb,unsigned int pitch, unsigned x, unsigned y, unsigned int color);
void putchar(unsigned long *fb, unsigned int pitch, unsigned x, unsigned y, unsigned char c, unsigned int fgcolor, unsigned int bgcolor);
void write_string(unsigned long *fb, unsigned int pitch, unsigned char* message, unsigned int fgcolor, unsigned int bgcolor);