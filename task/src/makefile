#######
# makefile for STM8*_StdPeriph_Lib and SDCC compiler
#
# note: paths in this Makefile assume unmodified SPL folder structure
#
# usage:
#   1. if SDCC not in PATH set path -> CC_ROOT
#   2. set correct STM8 device -> DEVICE
#   3. set project paths -> PRJ_ROOT, PRJ_SRC_DIR, PRJ_INC_DIR
#   4. set SPL paths -> SPL_ROOT
#   5. add required SPL modules -> SPL_SOURCE
#   6. add required STM8S_EVAL modules -> EVAL_SOURCE, EVAL_128K_SOURCE, EVAL_COMM_SOURCE
#
#######

# STM8 device (for supported devices see stm8s.h)
DEVICE=STM8S105
DEVICE_FLASH=stm8s105k4

# set compiler path & parameters 
CC_ROOT =
CC      = sdcc
# CFLAGS  = -mstm8 -lstm8 --opt-code-size --debug
CFLAGS  = -mstm8 -lstm8 --opt-code-size

ASM     = sdasstm8
ASMFLAGS= -loff

# set output folder and target name
# OUTPUT_DIR = ./$(DEVICE)
OUTPUT_DIR = ../out
TARGET     = $(OUTPUT_DIR)/$(DEVICE).hex
# TARGET     = $(OUTPUT_DIR)/$(DEVICE).ihx
MAP        = $(OUTPUT_DIR)/$(DEVICE).map

# set project folder and files (all *.c)
PRJ_ROOT    = ..
PRJ_SRC_DIR = $(PRJ_ROOT)/src
PRJ_INC_DIR = $(PRJ_ROOT)/src
PRJ_SOURCE  = $(notdir $(wildcard $(PRJ_SRC_DIR)/*.c))
PRJ_OBJECTS := $(addprefix $(OUTPUT_DIR)/, $(PRJ_SOURCE:.c=.rel))

ASM_SOURCE = $(notdir $(wildcard $(PRJ_SRC_DIR)/*.s))
ASM_OBJECTS := $(addprefix $(OUTPUT_DIR)/, $(ASM_SOURCE:.s=.rel))

# set SPL paths
# SPL_ROOT    = ../../..
SPL_ROOT    = $(HOME)/Chip/mcu/stm8/framework-ststm8spl-platformio
SPL_SRC_DIR = $(SPL_ROOT)/Libraries/STM8S_StdPeriph_Driver/src
SPL_INC_DIR = $(SPL_ROOT)/Libraries/STM8S_StdPeriph_Driver/inc
SPL_SOURCE  = stm8s_gpio.c
# SPL_OBJECTS := $(addprefix $(OUTPUT_DIR)/, $(SPL_SOURCE:.c=.rel))

IAR_INC_DIR = $(SPL_ROOT)/Libraries/IAR_Headers

# collect all include folders
INCLUDE = -I$(PRJ_SRC_DIR) -I$(SPL_INC_DIR) -I$(IAR_INC_DIR)

# collect all source directories
VPATH=$(PRJ_SRC_DIR):$(SPL_SRC_DIR)

.PHONY: clean

all: $(OUTPUT_DIR) $(TARGET)
	@grep REL,CON $(MAP) | uniq

$(OUTPUT_DIR):
	@mkdir -p $(OUTPUT_DIR)

$(OUTPUT_DIR)/%.rel: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -D$(DEVICE) -c $? -o $@

$(OUTPUT_DIR)/%.rel: %.s
	$(ASM) $(ASMFLAGS) $(OUTPUT_DIR)/$(notdir $@) $<

$(TARGET): $(PRJ_OBJECTS) $(SPL_OBJECTS) $(ASM_OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $^

flash: $(TARGET)
	stm8flash -c stlinkv2 -p $(DEVICE_FLASH) -s flash -w $(TARGET)

stcflash: $(TARGET)
	python3 /usr/local/bin/stcflash $(TARGET)

space:
	@grep REL,CON $(MAP) | uniq

clean: 

# makefile中的shell命令前加
# @	使命令在被执行前不被回显。
# -	使任何命令行的任何非零退出状态都被忽略。
# +	使命令行可以通过指定 -n、-q 或 -t 选项来执行。
	-rm -fr $(OUTPUT_DIR)

rebuild: clean all
