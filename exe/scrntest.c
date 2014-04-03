
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dlfcn.h>
#include <sys/mman.h>

#include "../lib/screen2image.h"
#include "jpeglib.h"

extern JSAMPLE *image_buffer = NULL;
extern int image_width = 0;
extern int image_height = 0;

//extern FILE *stderr;

int main(int argc, char **argv)
{
	int fd;
	fprintf(stderr, "Test stderr.\n");
	if (argc < 2) {
		printf("Usage: %s <FILE> \n", argv[0]);
		return 0;
	}
	
	printf("output file: %s\n", argv[1]);

	//fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	//if (fd < 0) {
	//	fprintf(stderr, " open %s failed ", argv[1]);
	//	perror(" ");
	//	//dlclose(dlp);
	//	return -1;
	//}

	screen2image_init("/dev/graphics/fb0");

	void *raw_image = screen2image_allocbuf();
	
	screen2image_getscreensize(&image_width, &image_height);
	int bufsize = image_width * image_height * sizeof(JSAMPLE) * 3;
	image_buffer = malloc(bufsize);
	int i;
	for (i = 0; i < 30; i++) // Performance Test
	{
		int img_size = screen2image_getscreen(raw_image);
		int bpp = screen2image_getscreenbpp();

		if (img_size > image_width * image_height * (bpp / 8))
		{
			img_size = image_width * image_height * (bpp / 8);
		}

		//screen2image_writetofile(fd);
		int ret = screen2image_pixel16to24pack(raw_image, img_size, image_buffer, bufsize);
		if (ret < 0)
		{
			printf("pixel conversion failed.\n");
			break;
		}

		char jpgname[200];
		sprintf(jpgname, "%s_%03d.jpg", argv[1], i);

		//size_t imglen = lseek(fd, 0, SEEK_END);

		//image_buffer = mmap(NULL, imglen, PROT_READ, MAP_PRIVATE, fd, 0);

		write_JPEG_file(jpgname, 9);
	}
	
	free(image_buffer);
	screen2image_freebuf(raw_image);

	screen2image_destroy();

	//munmap(image_buffer, imglen);
	//close(fd);
	//dlclose(dlp);

	return 0;
}


#ifdef __cplusplus
}
#endif


