void itoa (char *buf, int base, int d);
void video_init(unsigned long *fb, unsigned int pitch);
void set_color(unsigned int fgcolor, unsigned int bgcolor);
void putpixel( unsigned x, unsigned y, unsigned int color);
void putchar( unsigned x, unsigned y, unsigned char c);
void write_string(unsigned int x, unsigned int y, unsigned char* message);
void printf(const char *format, ...);