LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

res_dir := res

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, src/com/green/usbhostswitcher)
LOCAL_RESOURCE_DIR := $(addprefix $(LOCAL_PATH)/, $(res_dir))

LOCAL_AAPT_FLAGS := --auto-add-overlay

LOCAL_PACKAGE_NAME := USBHostSwitcher

LOCAL_PROGUARD_FLAG_FILES := proguard.flags

LOCAL_SDK_VERSION := current

include $(BUILD_PACKAGE)

# only include rules to build other stuff for the original package, not the derived package.
ifeq ($(strip $(LOCAL_PACKAGE_OVERRIDES)),)
# additionally, build unit tests in a separate .apk
include $(call all-makefiles-under,$(LOCAL_PATH))
endif

