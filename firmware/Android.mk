# This is an ugly hack to do a symlink to wifi firmware in /system
# I hope there is a better way, but cannot see any
#

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE:= fw-symlink
LOCAL_MODULE_CLASS := FAKE
LOCAL_MODULE_TAGS := optional

SYMLINKS := $(TARGET_OUT_ETC)/firmware/ti-connectivity/wl1271-nvs.bin

# Nook HD+ wifi firmware location
SYMPATH := /rom/devconf/WiFiBackupCalibration

$(SYMLINKS): $(LOCAL_PATH)/Android.mk
	@echo "Installing wifi fw symlink $@ -> $(SYMPATH)"
	@mkdir -p $(dir $@)
	@rm -rf $@
	$(hide) ln -sf $(SYMPATH) $@

ALL_DEFAULT_INSTALLED_MODULES += $(SYMLINKS)

# We need this so that the installed files could be picked up based on the
# local module name
ALL_MODULES.$(LOCAL_MODULE).INSTALLED := \
    $(ALL_MODULES.$(LOCAL_MODULE).INSTALLED) $(SYMLINKS)
