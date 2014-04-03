/**
 * Convert image pixel format.
 */

#ifndef __IMAGE_ADAPTER_H__
#define __IMAGE_ADAPTER_H__

#include <sys/types.h>

typedef enum tagPixelFormat
{
	PIXELTYPE_556;
}PIXEL_FORMAT_E;

size_t convert_img(void *data, size_t len, PIXEL_FORMAT_E pf);

#endif // __IMAGE_ADAPTER_H__
