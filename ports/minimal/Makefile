include ../../py/mkenv.mk

CROSS = 0

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h

# include py core make definitions
include $(TOP)/py/py.mk

ifeq ($(CROSS), 1)
CROSS_COMPILE = sh3eb-elf-
endif

INC += -I.
INC += -I$(TOP)
INC += -I$(BUILD)

ifeq ($(CROSS), 1)
DFU = $(TOP)/tools/dfu.py
PYDFU = $(TOP)/tools/pydfu.py
CFLAGS_CORTEX_M4 = 
CFLAGS = $(INC) -Wall -m3 -mb -ffreestanding -nostdlib -lgcc -std=c99 $(CFLAGS_CORTEX_M4) $(COPT)
LDFLAGS = -Wl,-Map=$@.map,--cref -Wl,--gc-sections
else
CROSS_COMPILE = sh3eb-elf-
LD = sh3eb-elf-gcc
CFLAGS = $(INC) -Wall -std=c11 -m3 -mb -mrenesas -Wno-implicit-function-declaration -Wno-incompatible-pointer-types -Wno-pointer-sign -Wno-char-subscripts -I include -nostdlib -O2
LDFLAGS = $(CFLAGS) -Wl,--gc-sections -nostdlib crt0.s setjmp.s syscalls.s -T addin.ld
#LDFLAGS = -Wl,-Map=$@.map,--cref -Wl,--gc-sections -nostdlib -T addin.ld crt0.s casiopy.c nan.c copysign.c nearbyint.c fesetenv.c MonochromeLib.c -mrenesas -Wno-implicit-function-declaration -Wno-incompatible-pointer-types -I include setjmp.s
endif

LIBS =

SRC_C = \
	casiopy.c \
	nan.c \
	copysign.c \
	fesetenv.c \
	tinyprintf.c \
	MonochromeLib.c \
	shell.c \
	edit.c \
	console.c \
	menu.c \
	font.c \
	main.c \
	posixio.c \
	uart_core.c \
	lib/utils/printf.c \
	lib/utils/stdout_helpers.c \
	lib/utils/pyexec.c \
	lib/libc/string0.c \
	lib/mp-readline/readline.c \
	extmod/modurandom.c \
        lib/libm_dbl/acos.c \
        lib/libm_dbl/acosh.c \
        lib/libm_dbl/asin.c \
        lib/libm_dbl/asinh.c \
        lib/libm_dbl/atan.c \
        lib/libm_dbl/atan2.c \
        lib/libm_dbl/atanh.c \
        lib/libm_dbl/ceil.c \
        lib/libm_dbl/cos.c \
        lib/libm_dbl/cosh.c \
        lib/libm_dbl/erf.c \
        lib/libm_dbl/exp.c \
        lib/libm_dbl/expm1.c \
        lib/libm_dbl/floor.c \
        lib/libm_dbl/fmod.c \
        lib/libm_dbl/frexp.c \
        lib/libm_dbl/ldexp.c \
        lib/libm_dbl/lgamma.c \
        lib/libm_dbl/log.c \
        lib/libm_dbl/log10.c \
        lib/libm_dbl/log1p.c \
        lib/libm_dbl/modf.c \
        lib/libm_dbl/nearbyint.c \
        lib/libm_dbl/pow.c \
        lib/libm_dbl/rint.c \
        lib/libm_dbl/scalbn.c \
        lib/libm_dbl/sin.c \
        lib/libm_dbl/sinh.c \
        lib/libm_dbl/sqrt.c \
        lib/libm_dbl/tan.c \
        lib/libm_dbl/tanh.c \
        lib/libm_dbl/tgamma.c \
        lib/libm_dbl/trunc.c \
        lib/libm_dbl/__cos.c \
        lib/libm_dbl/__expo2.c \
        lib/libm_dbl/__fpclassify.c \
        lib/libm_dbl/__rem_pio2.c \
        lib/libm_dbl/__rem_pio2_large.c \
        lib/libm_dbl/__signbit.c \
        lib/libm_dbl/__sin.c \
        lib/libm_dbl/__tan.c \
	$(BUILD)/_frozen_mpy.c \

OBJ = $(PY_CORE_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o))

ifeq ($(CROSS), 1)
all: $(BUILD)/firmware.dfu
else
all: $(BUILD)/firmware.elf
endif

$(BUILD)/_frozen_mpy.c: frozentest.mpy $(BUILD)/genhdr/qstrdefs.generated.h
	$(ECHO) "MISC freezing bytecode"
	$(Q)$(TOP)/tools/mpy-tool.py -f -q $(BUILD)/genhdr/qstrdefs.preprocessed.h -mlongint-impl=mpz $< > $@

$(BUILD)/firmware.elf: $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(LD)  -o $@ $^ $(LDFLAGS) $(LIBS) -L . -lfx -lgcc
	$(Q)$(SIZE) $@

$(BUILD)/firmware.bin: $(BUILD)/firmware.elf
	$(Q)$(OBJCOPY) -O binary -j .isr_vector -j .text -j .data $^ $(BUILD)/firmware.bin

$(BUILD)/firmware.dfu: $(BUILD)/firmware.bin
	$(ECHO) "Create $@"
	$(Q)$(PYTHON) $(DFU) -b 0x08000000:$(BUILD)/firmware.bin $@

deploy: $(BUILD)/firmware.dfu
	$(ECHO) "Writing $< to the board"
	$(Q)$(PYTHON) $(PYDFU) -u $<

# Run emulation build on a POSIX system with suitable terminal settings
run:
	stty raw opost -echo
	build/firmware.elf
	@echo Resetting terminal...
# This sleep is useful to spot segfaults
	sleep 1
	reset

test: $(BUILD)/firmware.elf
	$(Q)/bin/echo -e "print('hello world!', list(x+1 for x in range(10)), end='eol\\\\n')\\r\\n\\x04" | $(BUILD)/firmware.elf | tail -n2 | grep "^hello world! \\[1, 2, 3, 4, 5, 6, 7, 8, 9, 10\\]eol"

include $(TOP)/py/mkrules.mk
