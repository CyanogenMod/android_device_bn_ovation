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
TARGET_BOARD_OMAP_CPU := 4470
TARGET_BOOTLOADER_BOARD_NAME := ovation

# inherit from common
-include device/bn/bn-common/BoardConfigCommon.mk

# inherit from the proprietary version
-include vendor/bn/hd-common/BoardConfigVendor.mk

# Kernel/Boot
BOARD_USES_UBOOT := false

# Recovery
BOARD_CUSTOM_RECOVERY_KEYMAPPING := ../../device/bn/ovation/recovery/recovery_ui.c
TARGET_RECOVERY_INITRC := device/bn/ovation/recovery/init.rc


# boot.img creation
BOARD_CUSTOM_BOOTIMG_MK := device/bn/ovation/boot.mk

TARGET_KERNEL_CONFIG := cyanogenmod_ovation_green_defconfig
TARGET_KERNEL_SOURCE := kernel/bn/ovation
TARGET_KERNEL_CUSTOM_TOOLCHAIN := arm-eabi-4.4.3

SGX_MODULES:
	make clean -C $(COMMON_FOLDER)/pvr-source/eurasiacon/build/linux2/omap4430_android
	cp $(TARGET_KERNEL_SOURCE)/drivers/video/omap2/omapfb/omapfb.h $(KERNEL_OUT)/drivers/video/omap2/omapfb/omapfb.h
	make -j8 -C $(COMMON_FOLDER)/pvr-source/eurasiacon/build/linux2/omap4430_android ARCH=arm KERNEL_CROSS_COMPILE=arm-eabi- CROSS_COMPILE=arm-eabi- KERNELDIR=$(KERNEL_OUT) TARGET_PRODUCT="blaze_tablet" BUILD=release TARGET_SGX=544sc PLATFORM_VERSION=4.0
	mv $(KERNEL_OUT)/../../target/kbuild/pvrsrvkm_sgx544_112.ko $(KERNEL_MODULES_OUT)
	$(ARM_EABI_TOOLCHAIN)/arm-eabi-strip --strip-unneeded $(KERNEL_MODULES_OUT)/pvrsrvkm_sgx544_112.ko

WIFI_MODULES:
	make -C hardware/ti/wlan/mac80211/compat_wl12xx KERNEL_DIR=$(KERNEL_OUT) KLIB=$(KERNEL_OUT) KLIB_BUILD=$(KERNEL_OUT) ARCH=arm CROSS_COMPILE=arm-eabi-
	mv $(KERNEL_OUT)/lib/crc7.ko $(KERNEL_MODULES_OUT)
	mv hardware/ti/wlan/mac80211/compat_wl12xx/compat/compat.ko $(KERNEL_MODULES_OUT)
	mv hardware/ti/wlan/mac80211/compat_wl12xx/net/mac80211/mac80211.ko $(KERNEL_MODULES_OUT)
	mv hardware/ti/wlan/mac80211/compat_wl12xx/net/wireless/cfg80211.ko $(KERNEL_MODULES_OUT)
	mv hardware/ti/wlan/mac80211/compat_wl12xx/drivers/net/wireless/wl12xx/wl12xx.ko $(KERNEL_MODULES_OUT)
	mv hardware/ti/wlan/mac80211/compat_wl12xx/drivers/net/wireless/wl12xx/wl12xx_sdio.ko $(KERNEL_MODULES_OUT)

BT_MODULES:
	make -C kernel/bn/ovation/external/wpan/bluetooth-compat KERNEL_DIR=$(KERNEL_OUT) KLIB=$(KERNEL_OUT) KLIB_BUILD=$(KERNEL_OUT) ARCH=arm CROSS_COMPILE=arm-eabi-
	mv kernel/bn/ovation/external/wpan/bluetooth-compat/drivers/bluetooth/hci_uart.ko $(KERNEL_MODULES_OUT)
	mv kernel/bn/ovation/external/wpan/bluetooth-compat/drivers/bluetooth/btwilink.ko $(KERNEL_MODULES_OUT)
	mv kernel/bn/ovation/external/wpan/bluetooth-compat/net/bluetooth/bluetooth.ko $(KERNEL_MODULES_OUT)
	mv kernel/bn/ovation/external/wpan/bluetooth-compat/net/bluetooth/hidp/hidp.ko $(KERNEL_MODULES_OUT)
	mv kernel/bn/ovation/external/wpan/bluetooth-compat/net/bluetooth/rfcomm/rfcomm.ko $(KERNEL_MODULES_OUT)

TARGET_KERNEL_MODULES := SGX_MODULES WIFI_MODULES BT_MODULES

#Config for building TWRP
DEVICE_RESOLUTION := 1920x1280
RECOVERY_TOUCHSCREEN_SWAP_XY := true
RECOVERY_TOUCHSCREEN_FLIP_Y := true
TW_NO_REBOOT_BOOTLOADER := true
TW_NO_REBOOT_RECOVERY := true
TW_INTERNAL_STORAGE_PATH := "/emmc"
TW_INTERNAL_STORAGE_MOUNT_POINT := "emmc"
TW_EXTERNAL_STORAGE_PATH := "/sdcard"
TW_EXTERNAL_STORAGE_MOUNT_POINT := "sdcard"
TW_DEFAULT_EXTERNAL_STORAGE := true

# Bootanimation
TARGET_BOOTANIMATION_PRELOAD := true
