#include "fb_draw.h"
#include <stdlib.h>

#if 1
struct fb_st {
	struct fb_fix_screeninfo fix;
	struct fb_var_screeninfo var;
	unsigned long bpp;
	int rowlen;
	int bufsize;
	int fd;
	char *fbp;
};
#endif

static struct fb_st fb0;


int fb_open(char *fb_file)
{
	int ret;

	if (NULL == fb_file) {
		fb0.fd = open("/dev/fb0", O_RDWR);
		if (-1 == fb0.fd) {
			perror("open /dev/fb0");
			goto error;
		}
	}
	else {
		printf("fb_open() fb: %s\n", fb_file);
		fb0.fd = open(fb_file, O_RDWR);
		if (-1 == fb0.fd) {
			perror("open");
			goto error;
		}
	}

	/* get fb_var_screeninfo */
	ret = ioctl(fb0.fd, FBIOGET_VSCREENINFO, &fb0.var);
	if (-1 == ret) {
		perror("ioctl(fb0.var)");
		goto close_fd;
	}

	fb0.bpp = fb0.var.bits_per_pixel / 8;
	printf("fb0.bpp=%lu\n", fb0.bpp);
	//rowlen = fb0.var.xres;
	//if( rowlen == 1366 )
	//	rowlen = 1376;

	/* get fb_fix_screeninfo */
	ioctl(fb0.fd, FBIOGET_FSCREENINFO, &fb0.fix);
	if (-1 == ret) {
		perror("ioctl(fb0.fix)");
		goto close_fd;
	}
	fb0.rowlen = fb0.fix.line_length / fb0.bpp;
	fb0.bufsize = xres() * yres() * fb0.bpp;

	/* get framebuffer start address */
	fb0.fbp = mmap(NULL, fb0.fix.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fb0.fd, 0);
	if ((void *)-1 == fb0.fbp) {
		perror("mmap");
		goto close_fd;
	}

	return 0;

close_fd:
	close(fb0.fd);
error:
	return -1;
}

void fb_close()
{
	munmap(fb0.fbp, fb0.fix.smem_len);
	close(fb0.fd);
}

void fb_draw_point(int x, int y, unsigned color)
{
	unsigned long offset;

	offset = fb0.bpp * (x + y * fb0.rowlen );
	// fb0.var.xres

	//memset((void *)(fb0.fbp + offset), color, fb0.bpp*8);

	unsigned int i;
	for(i=0; i<fb0.bpp; i++)
	{
		*(fb0.fbp + offset+i) = color & 0xff;
		color >>= 8;
	}
}

void fb_clear()
{
	memset( fb0.fbp, 0, fb0.fix.smem_len );
}

int xres(void)
{
	return fb0.var.xres;
}

int yres(void)
{
	return fb0.var.yres;
}

int fb_bpp(void)
{
	return fb0.var.bits_per_pixel;
}

int fb_bufsize(void)
{
	return fb0.fix.smem_len;
}

int fb_getfbdata(void *buf)
{
	memcpy(buf, fb0.fbp, fb0.fix.smem_len);
	return fb0.fix.smem_len;
}

int fb_putrawimg(void *buf, size_t img_size)
{
	if (img_size >= fb0.fix.smem_len)
	{
		memcpy(fb0.fbp, buf, fb0.fix.smem_len);
		return fb0.fix.smem_len;
	}
	else
	{
		memcpy(fb0.fbp, buf, img_size);
		return img_size;
	}
}

void fb_printinfo(void)
{
	printf("resolution=%dx%d, bufsize=%d, rowstride=%d\n"
			"bpp=%lu\n",
			xres(), yres(), fb_bufsize(), fb0.fix.line_length, fb0.bpp);
}

