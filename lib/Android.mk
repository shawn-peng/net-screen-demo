LOCAL_PATH      := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := screen2image-jni.c
LOCAL_MODULE    := libscreen2image-jni
LOCAL_PRELINK_MODULE    := false

LOCAL_SHARED_LIBRARIES  :=  libc
LOCAL_STATIC_LIBRARIES  := 

include $(BUILD_STATIC_LIBRARY)
#include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := screen2image.c \
		framebuffer/fb_draw.c
LOCAL_MODULE	:= libscreen2image
#LOCAL_PRELINK_MODULE	:= false

LOCAL_STATIC_LIBRARIES	:=

include $(BUILD_STATIC_LIBRARY)
#include $(BUILD_SHARED_LIBRARY)


