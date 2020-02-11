BUILD_ROOT := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))


SPL_PATH = $(BUILD_ROOT)/stm_spl/
COMMON_PATH = $(BUILD_ROOT)/common
AUDIO_DIR = $(BUILD_ROOT)/projects

.PHONY: labs spl common audio_prj clean

all: labs

labs: audio_prj

spl:
	make -C $(SPL_PATH)

common:
	make -C $(COMMON_PATH)

audio_prj: spl common
	make -C $(AUDIO_DIR)/audio_prj

clean:
	make -C $(SPL_PATH) clean
	make -C $(COMMON_PATH) clean
	make -C $(AUDIO_DIR)/audio_prj clean
