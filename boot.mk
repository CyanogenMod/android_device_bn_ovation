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
# To use this bootimg 
#  
#  Add to your BoardConfig.mk:
#    BOARD_CUSTOM_BOOTIMG_MK := device/common/uboot-bootimg.mk
#  If using uboot multiimage add:
#    BOARD_USES_UBOOT_MULTIIMAGE := true
# 

#
# Ramdisk/boot image
#
LOCAL_PATH := $(call my-dir)

OVATION_MASTER_KEY := device/bn/ovation/prebuilt/boot/master_boot.key

# this is a copy of the build/core/Makefile target
# $(INSTALLED_BOOTIMAGE_TARGET) renamed to .sdcard
$(INSTALLED_BOOTIMAGE_TARGET).temp :  $(MKBOOTIMG) $(INTERNAL_BOOTIMAGE_FILES)
	$(call pretty,"Making target boot image: $@")
	$(hide) $(MKBOOTIMG) $(INTERNAL_BOOTIMAGE_ARGS) --output $@

$(INSTALLED_BOOTIMAGE_TARGET): \
		$(MKBOOTIMG) $(INSTALLED_BOOTIMAGE_TARGET).temp $(OVATION_MASTER_KEY)
	$(hide) cp $(OVATION_MASTER_KEY) $@
	$(hide) dd if=$@.temp of=$@ bs=1048576 seek=1
	$(hide) $(call assert-max-image-size,$@, \
		$(BOARD_BOOTIMAGE_PARTITION_SIZE),raw)

#
# Recovery Image
#
INSTALLED_RECOVERYIMAGE_TARGET := $(PRODUCT_OUT)/recovery.img
INTERNAL_RECOVERYRAMDISK_IMAGENAME := CWM $(TARGET_DEVICE) Ramdisk
INTERNAL_RECOVERYRAMDISKIMAGE_ARGS := -A ARM -O Linux -T RAMDisk -C none -n "$(INTERNAL_RECOVERYRAMDISK_IMAGENAME)" -d $(recovery_ramdisk)
recovery_uboot_ramdisk := $(recovery_ramdisk:%.img=%.ub)

$(recovery_uboot_ramdisk): $(MKIMAGE) $(recovery_ramdisk)
	@echo ----- Making recovery image ------
	$(MKIMAGE) $(INTERNAL_RECOVERYRAMDISKIMAGE_ARGS) $@
	@echo ----- Made recovery uboot ramdisk -------- $@

ifeq ($(BOARD_USES_UBOOT_MULTIIMAGE),true)
    $(warning We are here.)
    INTERNAL_RECOVERYIMAGE_IMAGENAME := CWM $(TARGET_DEVICE) Multiboot
    INTERNAL_RECOVERYIMAGE_ARGS := -A ARM -O Linux -T multi -C none -n "$(INTERNAL_RECOVERYIMAGE_IMAGENAME)"

    BOARD_UBOOT_ENTRY := $(strip $(BOARD_UBOOT_ENTRY))
    ifdef BOARD_UBOOT_ENTRY
	INTERNAL_RECOVERYIMAGE_ARGS += -e $(BOARD_UBOOT_ENTRY)
    endif

    BOARD_UBOOT_LOAD := $(strip $(BOARD_UBOOT_LOAD))    
    ifdef BOARD_UBOOT_LOAD
	INTERNAL_RECOVERYIMAGE_ARGS += -a $(BOARD_UBOOT_LOAD)
    endif

    INTERNAL_RECOVERYIMAGE_ARGS += -d $(strip $(recovery_kernel)):$(strip $(recovery_uboot_ramdisk))

	$(INSTALLED_RECOVERYIMAGE_TARGET): $(MKIMAGE) $(recovery_uboot_ramdisk) $(recovery_kernel)
		$(MKIMAGE) $(INTERNAL_RECOVERYIMAGE_ARGS) $@
		@echo ----- Made recovery uboot multiimage -------- $@

else #!BOARD_USES_UBOOT_MULTIIMAGE
    # If we are not on a multiimage platform lets zip the kernel with the ramdisk
    # for Rom Manager
    $(INSTALLED_RECOVERYIMAGE_TARGET): $(recovery_uboot_ramdisk) $(recovery_kernel)
		$(hide) rm -f $@
		zip -qDj $@ $(recovery_uboot_ramdisk) $(recovery_kernel)
		@echo ----- Made recovery image \(zip\) -------- $@

endif
