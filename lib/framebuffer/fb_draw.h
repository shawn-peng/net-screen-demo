#ifndef HS_FB_DRAW_H
#define HS_FB_DRAW_H

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <linux/fb.h>

#if 0
struct fb_st {
     struct fb_fix_screeninfo fix;
     struct fb_var_screeninfo var;
     unsigned long bpp;
     int fd;
     char *fbp;
};
#endif

int fb_open(char *);
void fb_close(void);
void fb_draw_point(int x, int y, unsigned color);
void fb_clear();

int xres(void);
int yres(void);
int fb_bpp(void);

#endif
