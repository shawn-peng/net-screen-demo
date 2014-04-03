
extern void image2screen_init(char *fb_file);

extern void *image2screen_allocbuf(void);

extern void image2screen_freebuf(void *buf);

extern void image2screen_destroy(void);

extern int image2screen_dispimg(void *buf);

extern void image2screen_getscreensize(int *width, int *height);

extern int image2screen_getscreenbpp(void);

extern int image2screen_pixel24packto16(void *old_buf, int img_size,
		void *new_buf, int buf_size);

extern void image2screen_writetofile(int fd);


