# Copyright (c) 2019 Cristóvão Zuppardo Rufino
# Updated source-code available at https://github.com/cristovaozr/stm32pp

CROSS_COMPILE := arm-none-eabi-

CXX := $(CROSS_COMPILE)g++
CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)g++
AR := $(CROSS_COMPILE)ar
AS := $(CROSS_COMPILE)as
OBJCOPY := $(CROSS_COMPILE)objcopy

ARFLAGS += 
INCLUDEDIR += -I./clib -I./cpp -I./cpp/gpio -I./cpp/usart -I./cpp/comm
CFLAGS += -Wall -ggdb -Os -ffunction-sections -fdata-sections \
	$(INCLUDEDIR) -DSTM32F407xx \
	-DUSE_FULL_LL_DRIVER -DHSE_VALUE=8000000 -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp
CXXFLAGS += -Wall -Wextra -ggdb -Os -ffunction-sections -fdata-sections \
	$(INCLUDEDIR) -DSTM32F407xx \
	-DUSE_FULL_LL_DRIVER -DHSE_VALUE=8000000 -mcpu=cortex-m4 -mthumb -mfloat-abi=soft \
	-fno-rtti
ASFLAGS += -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp
LDFLAGS += -Wl,--gc-sections -Wl,-entry=Reset_Handler -T main/STM32F407ZETx_FLASH.ld \
	-mthumb -mcpu=cortex-m4 -mfloat-abi=softfp

CXX_SRC := $(shell find cpp/ -type f -name '*.cpp')
C_SRC := $(shell find clib/ -type f -name '*.c')
MAIN_C_SRC := $(shell find main/ -type f -name '*.c')
MAIN_CXX_SRC := $(shell find main/ -type f -name '*.cpp')

OBJ_CXX += $(CXX_SRC:.cpp=.o)
OBJ += $(C_SRC:.c=.o)
OBJ_MAIN += $(MAIN_C_SRC:.c=.o)
OBJ_MAIN += $(MAIN_CXX_SRC:.cpp=.o)
OBJ_MAIN += main/startup_stm32f407xx.o

all: $(OBJ) $(OBJ_CXX)
	$(AR) $(ARFLAGS) stm32pp.a $(OBJ) $(OBJ_CXX)

binary: $(OBJ) $(OBJ_CXX) $(OBJ_MAIN)
	$(LD) $(LDFLAGS) -o main.elf $(OBJ_CXX) $(OBJ) $(OBJ_MAIN)
	$(OBJCOPY) -O binary main.elf main.bin

clean:
	$(RM) $(OBJ) $(OBJ_CXX) $(OBJ_MAIN) stm32pp.a main.bin main.elf
