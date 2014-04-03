LOCAL_PATH      := $(call my-dir)


include $(CLEAR_VARS)
LOCAL_MODULE    := libjpeg
#LOCAL_MODULE_CLASS	:= STATIC_LIBRARIES
#LOCAL_MODULE_SUFFIX	:= .a
LOCAL_PREBUILT_LIBS := libjpeg.a
#LOCAL_SRC_FILES := libjpeg.a
include $(BUILD_MULTI_PREBUILT)

#include $(CLEAR_VARS)
#LOCAL_MODULE    := scrntest
#LOCAL_SRC_FILES := scrntest.c jpegtest.c
#LOCAL_CFLAGS += -DLIBUTILS_NATIVE=1
#LOCAL_CXXFLAGS	+= -D_GNUSOURCE
#LOCAL_LDFLAGS	:= -std=C99 -Bstatic
#LOCAL_STATIC_LIBRARIES  := libscreen2image libjpeg

#include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)
LOCAL_MODULE    := scrntest
LOCAL_SRC_FILES := scrntest.c jpegtest.c
#LOCAL_CFLAGS += -DLIBUTILS_NATIVE=1
#LOCAL_LDFLAGS  := -std=C99 -Bstatic -lgcc -lstlport `gcc -print-libgcc-file-name`
LOCAL_SHARED_LIBRARIES	:= libc
LOCAL_STATIC_LIBRARIES  := libscreen2image libjpeg 
include $(BUILD_EXECUTABLE)


