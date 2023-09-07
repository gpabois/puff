# -- -- #
ARCH 		= xtensa-lx106
BUILD		= elf
TARGET		= puff-$(ARCH)-$(BUILD)

OBJ_DIR = obj
SRC_DIR = src
BIN_DIR = bin

# --- Define several toolchains --- #
ifeq ($(ARCH), xtensa-lx106)
	XTENSA_TOOLS_ROOT ?= /opt/Espressif/crosstool-NG/builds/xtensa-lx106-elf/bin
	CC = $(XTENSA_TOOLS_ROOT)/xtensa-lx106-elf-gcc
	LD = $(XTENSA_TOOLS_ROOT)/xtensa-lx106-elf-ld
endif

# ABI files
ABI_SRC_FILES = stack.c
ABI_SRC = $(patsubst %, puff/abi/$(ARCH)/%, $(ABI_SRC_FILES))

# CPU module
CPU_SRC_FILES = cpu.c
CPU_SRC = $(patsubst %, puff/cpu/%, $(CPU_SRC_FILES))

# Exception module
EXCEPTION_SRC_FILES = context.c exception.c sys.c
EXCEPTION_SRC = $(patsubst %, puff/exception/%, $(YARN_SRC_FILES))

# Yarn module
YARN_SRC_FILES = sys.c yarn.c
YARN_SRC = $(patsubst %, puff/yarn/%, $(YARN_SRC_FILES))

# Generator module
GENERATOR_SRC_FILES = allocator.c generator.c
GENERATOR_SRC = $(patsubst %, puff/generator/%, $(GENERATOR_SRC_FILES))

# Async module
ASYNC_SRC_FILES = coro.c coro/queue.c timer/queue.c timer.c
ASYNC_SRC = $(patsubst %, puff/async/%, $(GENERATOR_SRC_FILES))

# Source
SRC = puff/rt.c puff/error.c $(ABI_SRC) $(CPU_SRC) $(EXCEPTION_SRC) $(YARN_SRC) $(GENERATOR_SRC) $(ASYNC_SRC)

# Objects
OBJ = $(patsubst %, $(OBJ_DIR)/%, $(SRC:.c=.o))

# --- Compiler options --- #
CINC = src/
CFLAGS  = ${CFLAGS_${PLATFORM}_${BUILD}} -DARCH=$(ARCH) -I$(CINC)
LDFLAGS = 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	cmd /E:ON /C mkdir $(subst /,\,$(@D))
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

# --- Commands --- #
build: $(OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

clean: rm -f $(ODIR)/*.o $(OUT)

