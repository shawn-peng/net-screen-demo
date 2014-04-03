
LOCAL_PATH      := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := $(call all-subdir-java-files)
LOCAL_MODULE    := cow

LOCAL_JAVA_LIBRARIES    :=
LOCAL_STATIC_JAVA_LIBRARIES :=

include $(BUILD_JAVA_LIBRARY)


