# ------------------------------------------------
# Generic Makefile (based on gcc)
# ------------------------------------------------

######################################
# target
######################################
TARGET = STM32F429ZI

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og

#######################################
# paths
#######################################
# Build path

	BUILD_DIR = build_F429ZI

######################################
# selecting source
######################################
# C sources

	SYS = CMSIS/Devices/STM32F4xx/Src/system_stm32f4xx.c \ CMSIS/Devices/Src/syscalls.c \ CMSIS/Devices/Src/sysmem.c
	ASM = STMDevices/STM32F429ZI/startup_stm32f429xx.s
	CMSIS_INC_DEV = CMSIS/Devices/STM32F4xx/Inc
	CMSIS_INC_UNIT = CMSIS/Devices/STM32F4xx/Inc/STM32F429ZI
	CMSIS_INC = CMSIS/Include
	LD = STMDevices/STM32F429ZI/STM32F429ZITx_FLASH.ld
	DEF = STM32F429xx
	MCPU = cortex-m4
	MFPU = fpv4-sp-d16  #"vfpv4-d16"
	TRGT_CFG = stm32f4x


######################################
# source
######################################
# C sources
C_SOURCES =  \
$(SYS) \
Core/Src/main.c \
Core/Src/init.c \

# ASM sources
ASM_SOURCES =  \
$(ASM)

#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
	CC = $(GCC_PATH)/$(PREFIX)gcc
	AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
	CP = $(GCC_PATH)/$(PREFIX)objcopy
	SZ = $(GCC_PATH)/$(PREFIX)size
else
	CC = $(PREFIX)gcc
	AS = $(PREFIX)gcc -x assembler-with-cpp
	CP = $(PREFIX)objcopy
	SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=$(MCPU)

ifneq ($(MFPU), NONE)
	# fpu
	FPU = -mfpu=$(MFPU)
	# float-abi
	FLOAT-ABI = -mfloat-abi=hard
endif

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-D$(DEF) \

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-I$(CMSIS_INC_DEV) \
-I$(CMSIS_INC_UNIT) \
-I$(CMSIS_INC) \
-ICore/Inc \

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
	CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = $(LD) -Wl,--no-warn-rwx-segment # "-Wl,--no-warn-rwx-segment" - отключает вывод предупреждения о том,
#										   # что .elf содержит сегмент LOAD с правами RWX (Read, Write, X)
#										   # Нужно разбораться с этой проблемой  
#										   #
# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin 
	@echo "==========================================="
	@echo "|| The build was completed successfully! ||"
	@echo "==========================================="

#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@echo "---------------------   SIZE   ----------------------"
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $@  -Wl,--print-memory-usage
	@echo "" 
	@$(SZ) $@
	@echo "-----------------------------------------------------"	

$(BUILD_DIR):
	@"mkdir" -p $@

#######################################
# clean up
#######################################
clean:
	@"rm" -fR $(BUILD_DIR)
  
#######################################
# openocd
#######################################
flash: all
	openocd -f interface/stlink.cfg -f target/$(TRGT_CFG).cfg -c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"
	@echo "=================================="
	@echo "|| The download was successful! ||"
	@echo "=================================="

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***