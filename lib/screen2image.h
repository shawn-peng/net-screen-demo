

extern void screen2image_init(char *);

extern void screen2image_destroy(void);

extern void *screen2image_allocbuf(void);

extern void screen2image_freebuf(void *buf);

extern int screen2image_getscreen(void *);

extern int screen2image_pixel16to24pack(void *old_buf, int img_size,
		void *new_buf, int buf_size);

extern void screen2image_writetofile(int fd);

extern int screen2image_getscreenbpp(void);


