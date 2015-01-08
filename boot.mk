#
# Copyright (C) 2011 The Cyanogenmod Project
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

#
# Ramdisk/boot image
#
LOCAL_PATH := $(call my-dir)

MASTER_KEY := $(LOCAL_PATH)/prebuilt/boot/master_boot.key
MASTER_RECOVERY_KEY := $(LOCAL_PATH)/prebuilt/boot/master_recovery.key

# this is a copy of the build/core/Makefile target
$(INSTALLED_BOOTIMAGE_TARGET).temp :  $(MKBOOTIMG) $(INTERNAL_BOOTIMAGE_FILES)
	$(call pretty,"Making target boot image: $@")
	$(hide) $(MKBOOTIMG) $(INTERNAL_BOOTIMAGE_ARGS) --output $@

$(INSTALLED_BOOTIMAGE_TARGET): \
		$(MKBOOTIMG) $(INSTALLED_BOOTIMAGE_TARGET).temp $(MASTER_KEY)
	$(hide) cp $(MASTER_KEY) $@
	$(hide) dd if=$@.temp of=$@ bs=1048576 seek=1
	$(hide) $(call assert-max-image-size,$@, \
		$(BOARD_BOOTIMAGE_PARTITION_SIZE),raw)

#
# Recovery Image
#
$(INSTALLED_RECOVERYIMAGE_TARGET).temp : $(MKBOOTIMG) $(recovery_ramdisk) $(recovery_kernel)
	$(call pretty,"Making target recovery image: $@")
	$(hide) $(MKBOOTIMG) $(INTERNAL_RECOVERYIMAGE_ARGS) --output $@

$(INSTALLED_RECOVERYIMAGE_TARGET): \
		$(MKBOOTIMG) $(INSTALLED_RECOVERYIMAGE_TARGET).temp $(MASTER_RECOVERY_KEY)
	$(hide) cp $(MASTER_RECOVERY_KEY) $@
	$(hide) dd if=$@.temp of=$@ bs=1048576 seek=1
	$(hide) $(call assert-max-image-size,$@, \
		$(BOARD_RECOVERYIMAGE_PARTITION_SIZE),raw)
