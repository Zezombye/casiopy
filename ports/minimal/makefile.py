#!/usr/bin/python3

sources1 = "../../py/mpstate.c ../../py/malloc.c ../../py/gc.c ../../py/pystack.c ../../py/qstr.c ../../py/vstr.c ../../py/mpprint.c ../../py/unicode.c ../../py/mpz.c ../../py/reader.c ../../py/lexer.c ../../py/parse.c ../../py/scope.c ../../py/compile.c ../../py/emitcommon.c ../../py/emitbc.c ../../py/asmbase.c ../../py/asmx64.c ../../py/emitnx64.c ../../py/asmx86.c ../../py/emitnx86.c ../../py/asmthumb.c ../../py/emitnthumb.c ../../py/emitinlinethumb.c ../../py/asmarm.c ../../py/emitnarm.c ../../py/asmxtensa.c ../../py/emitnxtensa.c ../../py/emitinlinextensa.c ../../py/formatfloat.c ../../py/parsenumbase.c ../../py/parsenum.c ../../py/emitglue.c ../../py/persistentcode.c ../../py/runtime.c ../../py/runtime_utils.c ../../py/scheduler.c ../../py/nativeglue.c ../../py/stackctrl.c ../../py/argcheck.c ../../py/warning.c ../../py/map.c ../../py/obj.c ../../py/objarray.c ../../py/objattrtuple.c ../../py/objbool.c ../../py/objboundmeth.c ../../py/objcell.c ../../py/objclosure.c ../../py/objcomplex.c ../../py/objdeque.c ../../py/objdict.c ../../py/objenumerate.c ../../py/objexcept.c ../../py/objfilter.c ../../py/objfloat.c ../../py/objfun.c ../../py/objgenerator.c ../../py/objgetitemiter.c ../../py/objint.c ../../py/objint_longlong.c ../../py/objint_mpz.c ../../py/objlist.c ../../py/objmap.c ../../py/objmodule.c ../../py/objobject.c ../../py/objpolyiter.c ../../py/objproperty.c ../../py/objnone.c ../../py/objnamedtuple.c ../../py/objrange.c ../../py/objreversed.c ../../py/objset.c ../../py/objsingleton.c ../../py/objslice.c ../../py/objstr.c ../../py/objstrunicode.c ../../py/objstringio.c ../../py/objtuple.c ../../py/objtype.c ../../py/objzip.c ../../py/opmethods.c ../../py/sequence.c ../../py/stream.c ../../py/binary.c ../../py/builtinimport.c ../../py/builtinevex.c ../../py/builtinhelp.c ../../py/modarray.c ../../py/modbuiltins.c ../../py/modcollections.c ../../py/modgc.c ../../py/modio.c ../../py/modmath.c ../../py/modcmath.c ../../py/modmicropython.c ../../py/modstruct.c ../../py/modsys.c ../../py/moduerrno.c ../../py/modthread.c ../../py/vm.c ../../py/bc.c ../../py/showbc.c ../../py/repl.c ../../py/smallint.c ../../py/frozenmod.c ../../extmod/moductypes.c ../../extmod/modujson.c ../../extmod/modure.c ../../extmod/moduzlib.c ../../extmod/moduheapq.c ../../extmod/modutimeq.c ../../extmod/moduhashlib.c ../../extmod/moducryptolib.c ../../extmod/modubinascii.c ../../extmod/virtpin.c ../../extmod/machine_mem.c ../../extmod/machine_pinbase.c ../../extmod/machine_signal.c ../../extmod/machine_pulse.c ../../extmod/machine_i2c.c ../../extmod/machine_spi.c ../../extmod/modussl_axtls.c ../../extmod/modussl_mbedtls.c ../../extmod/modurandom.c ../../extmod/moduselect.c ../../extmod/modwebsocket.c ../../extmod/modwebrepl.c ../../extmod/modframebuf.c ../../extmod/vfs.c ../../extmod/vfs_reader.c ../../extmod/vfs_posix.c ../../extmod/vfs_posix_file.c ../../extmod/vfs_fat.c ../../extmod/vfs_fat_diskio.c ../../extmod/vfs_fat_file.c ../../extmod/utime_mphal.c ../../extmod/uos_dupterm.c ../../lib/embed/abort_.c ../../lib/utils/printf.c ../../py/mpconfig.h mpconfigport.h"

#sources2 = ["../../py/mpstate.c", "../../py/nlr.c", "../../py/nlrx86.c", "../../py/nlrx64.c", "../../py/nlrthumb.c", "../../py/nlrxtensa.c", "../../py/nlrsetjmp.c", "../../py/malloc.c", "../../py/gc.c", "../../py/pystack.c", "../../py/qstr.c", "../../py/vstr.c", "../../py/mpprint.c", "../../py/unicode.c", "../../py/mpz.c", "../../py/reader.c", "../../py/lexer.c", "../../py/parse.c", "../../py/scope.c", "../../py/compile.c", "../../py/emitcommon.c", "../../py/emitbc.c", "../../py/asmbase.c", "../../py/asmx64.c", "../../py/emitnx64.c", "../../py/asmx86.c", "../../py/emitnx86.c", "../../py/asmthumb.c", "../../py/emitnthumb.c", "../../py/emitinlinethumb.c", "../../py/asmarm.c", "../../py/emitnarm.c", "../../py/asmxtensa.c", "../../py/emitnxtensa.c", "../../py/emitinlinextensa.c", "../../py/formatfloat.c", "../../py/parsenumbase.c", "../../py/parsenum.c", "../../py/emitglue.c", "../../py/persistentcode.c", "../../py/runtime.c", "../../py/runtime_utils.c", "../../py/scheduler.c", "../../py/nativeglue.c", "../../py/stackctrl.c", "../../py/argcheck.c", "../../py/warning.c", "../../py/map.c", "../../py/obj.c", "../../py/objarray.c", "../../py/objattrtuple.c", "../../py/objbool.c", "../../py/objboundmeth.c", "../../py/objcell.c", "../../py/objclosure.c", "../../py/objcomplex.c", "../../py/objdeque.c", "../../py/objdict.c", "../../py/objenumerate.c", "../../py/objexcept.c", "../../py/objfilter.c", "../../py/objfloat.c", "../../py/objfun.c", "../../py/objgenerator.c", "../../py/objgetitemiter.c", "../../py/objint.c", "../../py/objint_longlong.c", "../../py/objint_mpz.c", "../../py/objlist.c", "../../py/objmap.c", "../../py/objmodule.c", "../../py/objobject.c", "../../py/objpolyiter.c", "../../py/objproperty.c", "../../py/objnone.c", "../../py/objnamedtuple.c", "../../py/objrange.c", "../../py/objreversed.c", "../../py/objset.c", "../../py/objsingleton.c", "../../py/objslice.c", "../../py/objstr.c", "../../py/objstrunicode.c", "../../py/objstringio.c", "../../py/objtuple.c", "../../py/objtype.c", "../../py/objzip.c", "../../py/opmethods.c", "../../py/sequence.c", "../../py/stream.c", "../../py/binary.c", "../../py/builtinimport.c", "../../py/builtinevex.c", "../../py/builtinhelp.c", "../../py/modarray.c", "../../py/modbuiltins.c", "../../py/modcollections.c", "../../py/modgc.c", "../../py/modio.c", "../../py/modmath.c", "../../py/modcmath.c", "../../py/modmicropython.c", "../../py/modstruct.c", "../../py/modsys.c", "../../py/moduerrno.c", "../../py/modthread.c", "../../py/vm.c", "../../py/bc.c", "../../py/showbc.c", "../../py/repl.c", "../../py/smallint.c", "../../py/frozenmod.c", "casiopy.c", "nan.c", "copysign.c", "nearbyint.c", "fesetenv.c", "tinyprintf.c", "MonochromeLib.c", "edit.c", "console.c", "menu.c", "font.c", "main.c", "uart_core.c", "../../lib/utils/printf.c", "../../lib/utils/stdout_helpers.c", "../../lib/utils/pyexec.c", "../../lib/libc/string0.c", "../../lib/mp-readline/readline.c"]

sources2 = ["casiopy.c", "tinyprintf.c"]

#sources3 = "build/firmware.elf build/py/mpstate.o build/py/nlr.o build/py/nlrx86.o build/py/nlrx64.o build/py/nlrthumb.o build/py/nlrxtensa.o build/py/nlrsetjmp.o build/py/malloc.o build/py/gc.o build/py/pystack.o build/py/qstr.o build/py/vstr.o build/py/mpprint.o build/py/unicode.o build/py/mpz.o build/py/reader.o build/py/lexer.o build/py/parse.o build/py/scope.o build/py/compile.o build/py/emitcommon.o build/py/emitbc.o build/py/asmbase.o build/py/asmx64.o build/py/emitnx64.o build/py/asmx86.o build/py/emitnx86.o build/py/asmthumb.o build/py/emitnthumb.o build/py/emitinlinethumb.o build/py/asmarm.o build/py/emitnarm.o build/py/asmxtensa.o build/py/emitnxtensa.o build/py/emitinlinextensa.o build/py/formatfloat.o build/py/parsenumbase.o build/py/parsenum.o build/py/emitglue.o build/py/persistentcode.o build/py/runtime.o build/py/runtime_utils.o build/py/scheduler.o build/py/nativeglue.o build/py/stackctrl.o build/py/argcheck.o build/py/warning.o build/py/map.o build/py/obj.o build/py/objarray.o build/py/objattrtuple.o build/py/objbool.o build/py/objboundmeth.o build/py/objcell.o build/py/objclosure.o build/py/objcomplex.o build/py/objdeque.o build/py/objdict.o build/py/objenumerate.o build/py/objexcept.o build/py/objfilter.o build/py/objfloat.o build/py/objfun.o build/py/objgenerator.o build/py/objgetitemiter.o build/py/objint.o build/py/objint_longlong.o build/py/objint_mpz.o build/py/objlist.o build/py/objmap.o build/py/objmodule.o build/py/objobject.o build/py/objpolyiter.o build/py/objproperty.o build/py/objnone.o build/py/objnamedtuple.o build/py/objrange.o build/py/objreversed.o build/py/objset.o build/py/objsingleton.o build/py/objslice.o build/py/objstr.o build/py/objstrunicode.o build/py/objstringio.o build/py/objtuple.o build/py/objtype.o build/py/objzip.o build/py/opmethods.o build/py/sequence.o build/py/stream.o build/py/binary.o build/py/builtinimport.o build/py/builtinevex.o build/py/builtinhelp.o build/py/modarray.o build/py/modbuiltins.o build/py/modcollections.o build/py/modgc.o build/py/modio.o build/py/modmath.o build/py/modcmath.o build/py/modmicropython.o build/py/modstruct.o build/py/modsys.o build/py/moduerrno.o build/py/modthread.o build/py/vm.o build/py/bc.o build/py/showbc.o build/py/repl.o build/py/smallint.o build/py/frozenmod.o build/casiopy.o build/nan.o build/copysign.o build/nearbyint.o build/fesetenv.o build/tinyprintf.o build/MonochromeLib.o build/edit.o build/console.o build/menu.o build/font.o build/main.o build/uart_core.o build/lib/utils/printf.o build/lib/utils/stdout_helpers.o build/lib/utils/pyexec.o build/lib/libc/string0.o build/lib/mp-readline/readline.o build/build/_frozen_mpy.o"

sources3 = "build/crt0.s.o build/casiopy.o build/tinyprintf.o"

include = "-I. -I../.. -Ibuild -I include"
#cflags = include + " -Wall -std=c11 -m3 -mb -mrenesas -Wno-implicit-function-declaration -Wno-incompatible-pointer-types -Wno-parentheses -I include -nostdlib -O2"
cflags = "-m3 -mb -mrenesas -std=c11 -Wall -Wextra -fno-asynchronous-unwind-tables -I include -O2"
ldflags = cflags + " -nostdlib -L . -lfx -T addin.ld -lgcc"
#ldflags = cflags + " -Wl,--gc-sections -nostdlib -T addin.ld crt0.s setjmp.s"
libs = " -L . -lfx -lgcc"

output = "#!/bin/bash\n"


output += "rm -rf build" + "\n"
output += "mkdir -p build/genhdr" + "\n"
#output += "python ../../py/makeversionhdr.py build/genhdr/mpversion.h" + "\n"
#output += "sh3eb-elf-gcc -E -DNO_QSTR -Ibuild/tmp "+sources1+" "+cflags+" >build/genhdr/qstr.i.last" + "\n"
#output += "python ../../py/makeqstrdefs.py split build/genhdr/qstr.i.last build/genhdr/qstr build/genhdr/qstrdefs.collected.h" +"\n"
#output += "touch build/genhdr/qstr.split" +"\n"
#output += "python ../../py/makeqstrdefs.py cat build/genhdr/qstr.i.last build/genhdr/qstr build/genhdr/qstrdefs.collected.h" +"\n"
#output += "cat ../../py/qstrdefs.h qstrdefsport.h build/genhdr/qstrdefs.collected.h | sed 's/^Q(.*)/\"&\"/' | sh3eb-elf-gcc -E "+cflags+" - | sed 's/^\"\\(Q(.*)\\)\"/\\1/' > build/genhdr/qstrdefs.preprocessed.h" +"\n"
#output += "python ../../py/makeqstrdata.py build/genhdr/qstrdefs.preprocessed.h > build/genhdr/qstrdefs.generated.h" +"\n"
output += "mkdir -p build/build/" +"\n"
output += "mkdir -p build/lib/libc/" +"\n"
output += "mkdir -p build/lib/mp-readline/" +"\n"
output += "mkdir -p build/lib/utils/" +"\n"
output += "mkdir -p build/py/" +"\n"
output += "sh3eb-elf-as -c crt0.s -o build/crt0.s.o" + "\n"

output += ""
for i in sources2:
	output += "sh3eb-elf-gcc -c "+i+" -o build/"+i.replace("../../", "").replace(".c", ".o")+" "+cflags+"\n"

#output += "../../tools/mpy-tool.py -f -q build/genhdr/qstrdefs.preprocessed.h -mlongint-impl=none frozentest.mpy > build/_frozen_mpy.c" +"\n"

#output += "sh3eb-elf-gcc -c build/_frozen_mpy.c -o build/build/_frozen_mpy.o -MD "+cflags+"\n"

output += "sh3eb-elf-gcc "+sources3+" -o build/firmware.elf "+ldflags+"\n"
output += "sh3eb-elf-size build/firmware.elf" +"\n"

output += "mv build/firmware.elf ./casiopy.elf" +"\n"
output += "echo \"Finished building firmware; stripping elf\"" +"\n"
output += "sh3eb-elf-objcopy -O binary -R .bss -R .comment casiopy.elf casiopy.bin" +"\n"
output += "echo \"Wrapping g1a\"" +"\n"
output += "g1a-wrapper casiopy.bin -o casiopy.g1a -i icon.bmp" +"\n"



 

outputFile = open("buildpy.sh", "w", newline="\n")
outputFile.write(output)
outputFile.close()