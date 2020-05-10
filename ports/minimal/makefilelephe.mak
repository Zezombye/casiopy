# Input variables
target	= tests.g1a
src	= $(wildcard *.[cs])
hdr	= $(wildcard *.h)
cflags	= -m3 -mb -mrenesas -std=c11 -Wall -Wextra -I include -O2
ldflags	= -nostdlib -L . -lfx -T addin.ld -lgcc
icon	= icon.bmp

# Tools
as	= sh3eb-elf-as
gcc	= sh3eb-elf-gcc
objcopy	= sh3eb-elf-objcopy
wrapper	= g1a-wrapper

# Deduced variables
obj	= $(patsubst %,build/%.o,$(src) $(res))
elf	= build/$(target:.g1a=.elf)
bin	= build/$(target:.g1a=.bin)

# Rules

all: $(target)

build:
	mkdir -p $@

$(target): $(bin)
	$(wrapper) $< -o $@ -i $(icon)
$(bin): $(elf)
	$(objcopy) -O binary -R .bss -R .comment $< $@
$(elf): $(obj)
	$(gcc) $^ -o $@ $(cflags) $(ldflags)

build/%.c.o: %.c | build
	$(gcc) -c $< -o $@  $(cflags)
build/%.s.o: %.s | build
	$(as) -c $< -o $@

clean:
	rm -rf build
distclean: clean
	rm -f $(target)

.PHONY: all clean distclean
