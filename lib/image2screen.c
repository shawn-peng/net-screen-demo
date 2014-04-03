
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "framebuffer/fb_draw.h"
#include "image2screen.h"

static int fb0;
static void *fbdata_buf = NULL;
static int fbdata_bufsize = 0;

extern void image2screen_init(char *fb_file)
{
	fb_open(fb_file);
	fbdata_bufsize = fb_bufsize();
	printf("The buffer size of fb is: %d bytes\n", fbdata_bufsize);
#ifdef __DEBUG__
	fb_printinfo();
#endif
	//fbdata_buf = malloc(fbdata_bufsize);
}

extern void *image2screen_allocbuf(void)
{
	return malloc(fbdata_bufsize);
}

extern void image2screen_freebuf(void *buf)
{
	return free(buf);
}

extern void image2screen_destroy(void)
{
	fb_close();
	if (fbdata_buf)
	{
		free(fbdata_buf);
	}
}

extern int image2screen_dispimg(void *buf)
{
	//int ret = fb_getfbdata(buf);
	int ret = fb_putrawimg(buf, fbdata_bufsize);
	//printf("data gotten.\n");
	return ret;
}

extern void image2screen_getscreensize(int *width, int *height)
{
	*width = xres();
	*height = yres();
}

extern int image2screen_getscreenbpp(void)
{
	return fb_bpp();
}

struct pixel_rgb16 {
	unsigned int blue	: 5;
	unsigned int green	: 6;
	unsigned int red 	: 5;
}__attribute__((packed));

struct pixel_rgb24 {
	unsigned int red 	: 8;
	unsigned int green	: 8;
	unsigned int blue	: 8;
}__attribute__((packed));

union rgb16_short {
	short data;
	struct pixel_rgb16 pixel;
};

union rgb24_int {
	int data : 24;
	struct pixel_rgb24 pixel;
};

extern int image2screen_pixel16to24pack(void *old_buf, int img_size,
		void *new_buf, int buf_size)
{
	int index;
	int num_pixel;
	struct pixel_rgb16 *p16 = old_buf;
	struct pixel_rgb24 *p24 = new_buf;

	num_pixel = img_size / 3;
	if (buf_size < num_pixel * 2)
	{
		return -1;
	}

	for (index = 0; index < num_pixel; index++, p16++, p24++)
	{
		p24->red	= p16->red << 3;
		p24->green	= p16->green << 2;
		p24->blue	= p16->blue << 3;
	}

	return 0;
}

extern void image2screen_wriatetofile()
{
	if (ret < 0)
	{
		perror("when write framebuffer data to file:");
		return ;
	}
}



