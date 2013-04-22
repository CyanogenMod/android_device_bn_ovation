#
# Copyright (C) 2011 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := $(call my-dir)

#Copying libbltsville_ticpu.BV_CPUVERSION.so
include $(CLEAR_VARS)
BV_CPUVERSION :=$(shell ls $(DEVICE_FOLDER)/bltsville/ticpu/lib/android/libbltsville_*.*.so|\
             sed 's/device\/bn\/ovation\/bltsville\/ticpu\/lib\/android\/libbltsville_ticpu.//')
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE := libbltsville_ticpu.$(BV_CPUVERSION)
LOCAL_SRC_FILES := lib/android/libbltsville_ticpu.$(BV_CPUVERSION)
LOCAL_MODULE_PATH:= $(TARGET_OUT_VENDOR)/lib
include $(BUILD_PREBUILT)

#Creating SymLinks
#libbltsville_ticpu.so -> libbltsville_ticpu.BV_CPUVERSION.so
#libbltsville_cpu.so -> libbltsville_ticpu.so
SYMLINKS := $(TARGET_OUT_VENDOR)/lib/libbltsville_ticpu.so
$(SYMLINKS): TICPU_BINARY := ./libbltsville_ticpu.$(BV_CPUVERSION)
$(SYMLINKS): $(LOCAL_INSTALLED_MODULE) $(LOCAL_PATH)/Android.mk
	@echo "Symlink: $@ -> $(TICPU_BINARY)"
	@mkdir -p $(dir $@)
	@rm -rf $@
	$(hide) ln -fs $(TICPU_BINARY) $@
	@cp -afr $(DEVICE_FOLDER)/bltsville/ticpu/lib/android/libbltsville_ticpu_license.txt $(TARGET_OUT_VENDOR)/lib
ALL_DEFAULT_INSTALLED_MODULES += $(SYMLINKS)

SYMLINKS1 := $(TARGET_OUT_VENDOR)/lib/libbltsville_cpu.so
$(SYMLINKS1): LINK_BINARY := ./libbltsville_ticpu.so
$(SYMLINKS1): $(LOCAL_INSTALLED_MODULE) $(LOCAL_PATH)/Android.mk
	@echo "Symlink: $@ -> $(LINK_BINARY)"
	@mkdir -p $(dir $@)
	@rm -rf $@
	$(hide) ln -fs $(LINK_BINARY) $@
ALL_DEFAULT_INSTALLED_MODULES += $(SYMLINKS1)

# for mm
all_modules: $(SYMLINKS) $(SYMLINKS1)
