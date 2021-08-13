LOCAL_PATH := $(call my-dir)
USER_LOCAL_PATH:=$(LOCAL_PATH)
LIBUSB_ROOT_ABS := /home/victor/workdir/ainirobot/libusb/libusb
include $(LIBUSB_ROOT_ABS)/android/jni/libusb.mk
#restore the LOCAL_PATH
LOCAL_PATH:=$(USER_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_C_INCLUDES += $(LIBUSB_ROOT_ABS)
LOCAL_SHARED_LIBRARIES += libusb1.0
LOCAL_SRC_FILES := compliance_mode.c
LOCAL_MODULE := usb_ss_hub_comliance
include $(BUILD_EXECUTABLE)
