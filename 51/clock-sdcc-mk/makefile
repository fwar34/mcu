DEVICE = stc8f2k32s2
# set compiler path & parameters
CC_ROOT =
CC      = sdcc

# MCU = 16f88
# ARCH = pic14

# CFLAGS = -m$(ARCH) -p$(MCU) 
# CFLAGS = --verbose -V
CFLAGS = --opt-code-size
# LDFLAGS = -c -r -w -m I/usr/share/sdcc/lib/$(ARCH)/

# set output folder and target name
# OUTPUT_DIR = ./$(DEVICE)
OUTPUT_DIR = ./out
TARGET     = $(OUTPUT_DIR)/$(DEVICE).hex

# set project folder and files (all *.c)
PRJ_ROOT    = .
PRJ_SRC_DIR = $(PRJ_ROOT)/src
PRJ_INC_DIR = $(PRJ_ROOT)/src
# all project sources included by default
PRJ_SOURCE  = $(notdir $(wildcard $(PRJ_SRC_DIR)/*.c)) #将src目录底下的.c文件列举成空格间隔的文件名列表（每个文件去除目录前缀）
#将上面的PRJ_SOURCE中每个文件的后缀从.c改成.rel，然后给每一个文件都添加一个前缀$(OUTPUT_DIR)
PRJ_OBJECTS := $(addprefix $(OUTPUT_DIR)/, $(PRJ_SOURCE:.c=.rel))

# collect all include folders
INCLUDE = -I$(PRJ_SRC_DIR)

# collect all source directories
VPATH=$(PRJ_SRC_DIR)

# 以创建变量来创建文件夹
dummy_build_folder := $(shell mkdir -p $(OUTPUT_DIR))

#.PHONY 虚假的目标，如果有文件名字叫clean不会影响目标clean执行
.PHONY: clean

all: $(TARGET)

# $(OUTPUT_DIR)/%.rel: %.c
# 	$(CC) $(CFLAGS) $(INCLUDE) -c $?

$(OUTPUT_DIR)/%.rel: %.c #匹配符 %
# @mkdir -p $(@D) #创建文件夹
	$(CC) $(CFLAGS) $(INCLUDE) -c $? -o $@

$(TARGET): $(PRJ_OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $^

flash: $(TARGET)
	stcflash $(TARGET)

clean:
# rm -rf $(OUTPUT_DIR)/*
	rm -rf $(OUTPUT_DIR)
