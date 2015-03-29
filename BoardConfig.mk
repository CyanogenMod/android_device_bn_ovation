# Copyright (C) 2007 The Android Open Source Project
# Copyright (C) 2011 The CyanogenMod Project
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

# BoardConfig.mk
#
# Product-specific compile-time definitions.
#

DEVICE_FOLDER := device/bn/ovation
TARGET_BOOTLOADER_BOARD_NAME := ovation

# inherit from common
-include device/bn/common/BoardConfigCommon.mk

# inherit from the proprietary version
-include vendor/bn/hd-common/BoardConfigVendor.mk

# boot.img creation
BOARD_CUSTOM_BOOTIMG := true
BOARD_CUSTOM_BOOTIMG_MK := $(DEVICE_FOLDER)/boot.mk

TARGET_KERNEL_VARIANT_CONFIG := android_ovation_defconfig

# Recovery
BOARD_RECOVERY_SWIPE := true
BOARD_CUSTOM_RECOVERY_KEYMAPPING := ../../$(DEVICE_FOLDER)/recovery/recovery_keys.c
TARGET_RECOVERY_FSTAB := $(DEVICE_FOLDER)/root/fstab.ovation
RECOVERY_FSTAB_VERSION := 2

#Config for building TWRP
TW_THEME := landscape_hdpi
#DEVICE_RESOLUTION := 1920x1200
#RECOVERY_TOUCHSCREEN_SWAP_XY := true
#RECOVERY_TOUCHSCREEN_FLIP_Y := true
