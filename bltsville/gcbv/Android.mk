#
# Copyright (c) 2012, 
# Texas Instruments, Inc. and Vivante Corporation. 
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of Texas Instruments, Inc. nor the names of its
#       contributors may be used to endorse or promote products derived from
#       this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL TEXAS INSTRUMENTS, INC. BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
	gcmain.c \
	mirror/gcbv.c \
	mirror/gcparser.c \
	mirror/gcmap.c \
	mirror/gcbuffer.c \
	mirror/gcfill.c \
	mirror/gcblit.c \
	mirror/gcfilter.c \
	mirror/gcdbglog.c

LOCAL_CFLAGS :=

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/mirror \
	$(LOCAL_PATH)/mirror/include \
	$(DEVICE_FOLDER)/bltsville/bltsville/include \
	$(DEVICE_FOLDER)/bltsville/ocd/include

VERSION_H := $(DEVICE_FOLDER)/bltsville/gcbv/version.h
BV_VERSION := $(shell grep "VER_FILEVERSION_STR" $(VERSION_H) | sed "s,.*\"\([0-9.]*\)\\\0.*,\1,")

LOCAL_SHARED_LIBRARIES := \
    libcutils \

LOCAL_MODULE_TAGS    := optional
LOCAL_MODULE         := libbltsville_gc2d
LOCAL_MODULE_SUFFIX  := .$(BV_VERSION).so
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/../vendor/lib

include $(BUILD_SHARED_LIBRARY)

#Creating SymLinks
#libbltsville_gc2d.so -> libbltsville_gc2d.VERSION.so
#libbltsville_hw2d.so -> libbltsville_gc2d.so
SYMLINKS := $(TARGET_OUT_VENDOR)/lib/libbltsville_gc2d.so
$(SYMLINKS): GC2D_BINARY := ./$(LOCAL_MODULE)$(LOCAL_MODULE_SUFFIX)
$(SYMLINKS): $(LOCAL_INSTALLED_MODULE) $(LOCAL_PATH)/Android.mk
	@echo "Symlink: $@ -> $(GC2D_BINARY)"
	@rm -rf $@
	$(hide) ln -fs $(GC2D_BINARY) $@

SYMLINKS1 := $(TARGET_OUT_VENDOR)/lib/libbltsville_hw2d.so
$(SYMLINKS1): LINK_BINARY := ./libbltsville_gc2d.so
$(SYMLINKS1): $(LOCAL_INSTALLED_MODULE) $(LOCAL_PATH)/Android.mk
	@echo "Symlink: $@ -> $(LINK_BINARY)"
	@rm -rf $@
	$(hide) ln -fs $(LINK_BINARY) $@

ALL_DEFAULT_INSTALLED_MODULES += $(SYMLINKS) $(SYMLINKS1)

# for mm/mmm
all_modules: $(SYMLINKS) $(SYMLINKS1)

