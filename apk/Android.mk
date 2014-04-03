
LOCAL_PATH      := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := $(call all-subdir-java-files)
LOCAL_PACKAGE_NAME  := TestAll

LOCAL_JAVA_LIBRARIES    :=  cow
LOCAL_STATIC_JAVA_LIBRARIES     :=

include $(BUILD_PACKAGE)
