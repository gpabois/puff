# -- -- #
ARCH 		= xtensa-lx106
BUILD		= elf
TARGET		= puff-$(ARCH)-$(BUILD)

ODIR = obj
SDIR = src
BDIR = bin

# --- Define several toolchains --- #
ifeq ($(ARCH), xtensa-lx106)
	XTENSA_TOOLS_ROOT ?= /opt/Espressif/crosstool-NG/builds/xtensa-lx106-elf/bin
	xtensa-lx106_CC = $(XTENSA_TOOLS_ROOT)/xtensa-lx106-elf-gcc
	xtensa-lx106_LD = $(XTENSA_TOOLS_ROOT)/xtensa-lx106-elf-ld
endif

# C Compiler
CC=$($(ARCH)_CC)

# Linker
LD=$($(ARCH)_LD)

# --- Define the objects --- #
# ABI-related objects
ABI_OBJS = setjmp.o stack.o
ABI_OBJ = $(patsubst %, abi/$(ARCH)/%, $(ABI_OBJS))

OBJS += $(ABI_OBJ)
OBJ = $(patsubst %, $(ODIR)/%, $(OBJS))

# --- Compiler options --- #
CFLAGS  = ${CFLAGS_${PLATFORM}_${BUILD}} -DARCH=$(ARCH)

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

# --- Commands --- #
build: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean: rm -f $(ODIR)/*.o $(OUT)

