BUILD_ROOT := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))


SPL_PATH = $(BUILD_ROOT)/stm_spl/
COMMON_PATH = $(BUILD_ROOT)/common
LCD_DIR = $(BUILD_ROOT)/projects

.PHONY: labs spl common lcd clean

all: labs

labs: lcd

spl:
	make -C $(SPL_PATH)

common:
	make -C $(COMMON_PATH)

lcd: spl common
	make -C $(LCD_DIR)/lcd

clean:
	make -C $(SPL_PATH) clean
	make -C $(COMMON_PATH) clean
	make -C $(LCD_DIR)/lcd clean
