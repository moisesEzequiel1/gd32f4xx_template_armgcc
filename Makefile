# master makefile to build project, several targets have been defined with the aim to ease an
# easy handling of the most common task in a project like
# - make 		- To build the project
# - maek clean	- Remove Build folder with objects and binaries
# - make flash 	- Flash the board
# - make open	- Open a SW connection with the target
# - make debug	- OpenGDB ansd start a debug session
# - make lint	- Run cppcheck with MISRA validation
# - make docs	- Run doxygen to extract documentation from code
# - make test	- Run unit tests with code coverage using ceedling  
# Workspace base: root folder to repo USER DEFINED. 
TARGET = Base_Makefile_GD32f4xx
WORKSPACE ?= /home/moisesdominguez/pruebas/GD32F4


# OpenOCD variables
# Since there is no direct support by the latest binary in the official repo,
# we use the OpenNuvoton/OpenOCD version from GitHub.
OPENOCD_BIN ?= /mnt/c/tools/openocd-v0.12.0-i686-w64-mingw32.tar/openocd-v0.12.0-i686-w64-mingw32/bin/openocd.exe
SCRIPT_INTERFACE ?= interface/cmsis-dap.cfg
SCRIPT_TARGET ?= target/stm32f4x.cfg
HEX_PATH ?= $(WORKSPACE)/Build/$(TARGET).hex

# Project name
# oneliner for extract from keil config file files grep
#  grep -oP '<FilePath>\.\\\K.*?(?=</FilePath>)' MotorActuator.uvprojx \
# | awk -F'\\' '
# {
#     # reconstruir el path sin el nombre del archivo
#     path = $1
#     for (i = 2; i < NF; i++) path = path "\\" $i
#     paths[path]++
#     files = files $NF " "
# }
# END {
#     # Imprimir archivos
#     print "Files:"
#     n = split(files, farr, " ")
#     line = ""
#     for (i = 1; i <= n; i++) {
#         if (length(line farr[i]) > 80) {
#             print line
#             line = ""
#         }
#         line = line farr[i] " "
#     }
#     if (line) print line

#     # Imprimir paths únicos
#     print "\nPaths:"
#     line = ""
#     for (p in paths) {
#         if (length(line p) > 80) {
#             print line
#             line = ""
# }'  if (line) print line"

SRCS += system_gd32f4xx.c startup_gd32f407_427.S main.cpp _syscalls.c

SRCS += Gpio.cpp
SRCS += $(wildcard hal/src/*.c)
# library files
LIBF = 
# linker file
LINKER = gcc_arm.ld
# Global symbols (#defines)
SYMBOLS = -DGD32F427 -D__STARTUP_CLEAR_BSS 
# -DFIVE_PORT_ENABLE
# directories with source files to compiler (.c y .s)
SRC_PATHS  = Source
SRC_PATHS += cmsis/startups
SRC_PATHS += hal/src

SRC_PATHS += Source/middleware/input_manager Source/MCU
SRC_PATHS += Source/middleware/
# directories with header files
INC_PATHS  = Source
INC_PATHS += cmsis/core
INC_PATHS += cmsis/registers
INC_PATHS += hal/inc

INC_PATHS += Source/middleware/input_manager Source/MCU
INC_PATHS += Source/middleware/
# directories with library files *.a
LIB_PATHS  =

# -------------------------------------------------------------------------------------------------
# NOTE: From this point do not edit anything unless you know what your are doing
# ------------------------------------------------------------------------------------------------- 
TOOLCHAIN = arm-none-eabi
CPU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

# compiler flags
CFLAGS  = $(CPU)
CFLAGS += -O1                      # Compile with Size Optimizations (O0, O1, O2, O3, Os)
CFLAGS += -g3                        # Debugging information level (g1, g2, g3)
CFLAGS += -fno-builtin               # Don't recognize built-in functions that do not begin with ‘__builtin_’ as prefix
# CFLAGS += -std=c11                   # Comply with C11
CFLAGS += -std=gnu99
CFLAGS += -Wall                      # Be anal Enable All Warnings
CFLAGS += -pedantic                  # Be extra anal More ANSI Checks
CFLAGS += -Wstrict-prototypes        # Warn if a function is declared or defined without specifying the argument types
CFLAGS += -fsigned-char              # char is treated as signed
CFLAGS += -fdiagnostics-color=always # color the output
CFLAGS += -fomit-frame-pointer       # Don't keep the frame pointer in a register for functions that don't need one
CFLAGS += -fverbose-asm              # Put extra commentary information in the generated assembly code
CFLAGS += -MMD -MP					 # flags to enable recompilation of dependencies
CFLAGS += -ffunction-sections -fdata-sections
# CFLAGS += -DOS_USE_SEMIHOSTING
CXXFLAGS = $(CPU)
CXXFLAGS += -O1 -g3 -std=c++14 -Wall -pedantic -fno-exceptions -fno-rtti
CXXFLAGS += -fdiagnostics-color=always
CXXFLAGS += -MMD -MP -ffunction-sections -fdata-sections
# CXXFLAGS += -DOS_USE_SEMIHOSTING
CFLAGS += -nostartfiles -nostdlib
LDFLAGS += -nostartfiles -nostdlib

# assembler flags
AFLAGS = $(CPU)

# linker flags
LFLAGS  = $(CPU) 
LFLAGS += -Wl,--gc-sections
# LFLAGS += --specs=rdimon.specs 			# link with semihosting 
LFLAGS += --specs=nosys.specs
# LFLAGS += --specs=nano.specs 			# nano version of stdlib
# LFLAGS += -lc -lrdimon
LFLAGS += -Wl,--no-wchar-size-warning
LFLAGS += -Wl,-Map=Build/$(TARGET).map	# Generate map file 
# CFLAGS += -flto
# LFLAGS += -flto
# Linter ccpcheck flags
LNFLAGS  = --inline-suppr       # comments to suppress lint warnings
LNFLAGS += --quiet              # spit only useful information
LNFLAGS += --enable=warning,style # enable only warnings
LNFLAGS += --error-exitcode=1	# return error if any warnings
LNFLAGS += --std=c11            # check against C11
LNFLAGS += --template=gcc       # display warning gcc style
LNFLAGS += --force              # evaluate all the #if sentences
LNFLAGS += --platform=unix32    # lint againt a unix32 platform, but we are using arm32
LNFLAGS += --cppcheck-build-dir=Build/lint

# prefix substitution 
# OBJS = $(SRCS:%.c=Build/obj/%.o)
# OBJS := $(OBJS:%.cpp=Build/obj/%.o)
# OBJS := $(OBJS:%.s=Build/obj/%.o)
# OBJS := $(OBJS:%.S=Build/obj/%.o)

OBJS = $(foreach f,$(SRCS),Build/obj/$(notdir $(f:.c=.o)))
OBJS := $(foreach f,$(OBJS),$(f:.cpp=.o))
OBJS := $(foreach f,$(OBJS),$(f:.s=.o))
OBJS := $(foreach f,$(OBJS),$(f:.S=.o))

DEPS = $(OBJS:%.o=%.d)

# set source and header directories variables
VPATH = $(SRC_PATHS)
INCLS = $(addprefix -I ,$(INC_PATHS))
LIBS = $(addprefix -L,$(LIB_PATHS))
LIBSF = $(addprefix -l,$(LIBF))

#---Build project----------------------------------------------------------------------------------
all : build $(TARGET)

$(TARGET) : $(addprefix Build/, $(TARGET).elf)
	@echo "  OBJCOPY  $@.hex"
	@$(TOOLCHAIN)-objcopy -Oihex $< Build/$(TARGET).hex
	@echo "  OBJDUMP  $@.lst"
	@$(TOOLCHAIN)-objdump -S $< > Build/$(TARGET).lst
	@echo "  SIZE     $@"
	@$(TOOLCHAIN)-size --format=berkeley $<

Build/$(TARGET).elf : $(OBJS)
	@echo "  LD       $@"
	@$(TOOLCHAIN)-gcc $(LFLAGS) -T $(LINKER) $(LIBS) -o $@ $^ $(LIBSF)

Build/obj/%.o : %.c
	@echo "  CC       $<"
	@mkdir -p $(dir $@)
	@$(TOOLCHAIN)-gcc $(CFLAGS) $(INCLS) $(SYMBOLS) -o $@ -c $<

Build/obj/%.o : %.cpp
	@echo "  CXX      $<"
	@mkdir -p $(dir $@)
	@$(TOOLCHAIN)-g++ $(CXXFLAGS) $(INCLS) $(SYMBOLS) -o $@ -c $<

Build/obj/%.o : %.s
	@echo "  AS       $<"
	@mkdir -p $(dir $@)
	@$(TOOLCHAIN)-as $(AFLAGS) -o $@ -c $<

Build/obj/%.o : %.S
	@echo "  AS       $<"
	@mkdir -p $(dir $@)
	@$(TOOLCHAIN)-gcc $(AFLAGS) $(INCLS) -o $@ -c $<


-include $(DEPS)

.PHONY : build clean flash flash open debug docs lint test format

#---Make directory to place all the generated bynaries for build, docs, lint and test--------------
build :
	mkdir -p Build/obj

#---Erase fodler with program binaries-------------------------------------------------------------
clean :
	rm -rf Build

#---flash the image into the mcu-------------------------------------------------------------------
flash:
	$(OPENOCD_BIN) \
		-f $(SCRIPT_INTERFACE) \
		-f $(SCRIPT_TARGET) \
		-c "program $(HEX_PATH) verify reset" \
		-c "shutdown"


#---open a debug server conection------------------------------------------------------------------

OPEN_SCRIPT = ./scripts/openocd_win.sh

open:
	@$(OPEN_SCRIPT)
# open:
# 	exec $(OPENOCD_BIN) \
# 		-c "bindto 0.0.0.0" \
# 		-f $(SCRIPT_INTERFACE) \
# 		-f $(SCRIPT_TARGET) \
# 		-c "init" \
# 		-c "reset init"
#---launch a debug session, NOTE: is mandatory to previously open a debug server session-----------
debug :
	gdb-multiarch Build/$(TARGET).elf \
		-ex "set auto-load safe-path /" \
		-ex "target remote 172.20.80.1:3333"
#---Genrete project documentation with doxygen-----------------------------------------------------
docs : build
	mkdir -p Build/doxygen
	doxygen .doxyfile
	firefox Build/doxygen/html/index.html

#---Run Static analysis plus MISRA-----------------------------------------------------------------
lint : build
	mkdir -p Build/lint
	cppcheck --addon=misra.json --suppressions-list=.msupress $(LNFLAGS) app

#---Run unit testing with code coverage using ceedling---------------------------------------------
test : build
	ceedling clobber
	ceedling gcov:all utils:gcov

#---format code using clang format-----------------------------------------------------------------
# clang-format -style=file -i $(shell find test -iname *.h -o -iname *.c)
format:
	clang-format -style=file -i $(shell find Source -iname *.h -o -iname *.c)
	clang-format -style=file -i $(shell find Source -iname *.hpp -o -iname *.cpp)
