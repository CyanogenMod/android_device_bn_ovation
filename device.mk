#
# Copyright (C) 2011 The Android Open-Source Project
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
#

# This file includes all definitions that apply to ALL tuna devices, and
# are also specific to tuna devices
#
# Everything in this directory will become public

DEVICE_FOLDER := device/bn/ovation
TARGET_BOOTLOADER_BOARD_NAME := ovation

$(call inherit-product, device/bn/common/common.mk)

# Device overlay
DEVICE_PACKAGE_OVERLAYS += $(DEVICE_FOLDER)/overlay/aosp

PRODUCT_COPY_FILES += \
	$(DEVICE_FOLDER)/root/fstab.ovation:root/fstab.ovation \
	$(DEVICE_FOLDER)/root/init.ovation.rc:root/init.ovation.rc \
	$(DEVICE_FOLDER)/root/init.ovation.usb.rc:root/init.ovation.usb.rc \
	$(DEVICE_FOLDER)/recovery/init.recovery.ovation.rc:/root/init.recovery.ovation.rc \
	$(DEVICE_FOLDER)/root/ueventd.ovation.rc:root/ueventd.ovation.rc \

# Device settings
PRODUCT_PROPERTY_OVERRIDES += \
    usb.vendor=2080 \
    usb.product.adb=0005 \
    usb.product.mtpadb=0005 \

PRODUCT_AAPT_CONFIG := xlarge hdpi xhdpi

$(call inherit-product, frameworks/native/build/tablet-7in-hdpi-1024-dalvik-heap.mk)
$(call inherit-product-if-exists, vendor/bn/hd-common/hd-common-vendor.mk)
