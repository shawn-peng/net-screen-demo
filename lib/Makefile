
CC := arm-linux-gcc
AR := arm-linux-ar
RANLIB := arm-linux-ranlib
CFLAGS += -g -O0

framebuffer/%.o: framebuffer/%.c
	$(CC) -c $< $(CFLAGS) -o $@

%.o: %.c
	$(CC) -c $< $(CFLAGS)

#libscreen2image.a(screen2image.o framebuffer/fb_draw.o): $%
#	$(AR) rcs $@ $%
all: libscreen2image.a libimage2screen.a

libscreen2image.a: screen2image.o framebuffer/fb_draw.o
	$(AR) cr $@ $^
	$(RANLIB) libscreen2image.a

libimage2screen.a: image2screen.o framebuffer/fb_draw.o
	$(AR) cr $@ $^
	$(RANLIB) libimage2screen.a

uninstall:
	rm ../exe/libscreen2image.a -f
	rm ../exe/libimage2screen.a -f

install:
	cp libscreen2image.a ../exe/
	cp libimage2screen.a ../exe/

clean:
	rm libscreen2image.a libimage2screen *.o -rf
