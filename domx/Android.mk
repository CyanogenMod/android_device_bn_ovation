# DOMX not used in OMAP3 program
ifneq ($(TARGET_BOARD_PLATFORM),omap3)

    LOCAL_PATH:= $(call my-dir)
    HARDWARE_TI_OMAP4_BASE:= hardware/ti/omap4xxx
    OMAP4_DEBUG_MEMLEAK:= false

    BUILD_HEAPTRACKED_SHARED_LIBRARY:=$(BUILD_SHARED_LIBRARY)
    BUILD_HEAPTRACKED_EXECUTABLE:= $(BUILD_EXECUTABLE)

    include $(call first-makefiles-under,$(LOCAL_PATH))
endif # ifeq ($(TARGET_BOARD_PLATFORM),omap4)
