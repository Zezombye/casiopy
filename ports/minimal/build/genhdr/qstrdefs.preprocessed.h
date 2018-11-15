# 1 "<stdin>"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "<stdin>"
# 27 "<stdin>"
# 1 "../../py/mpconfig.h" 1
# 45 "../../py/mpconfig.h"
# 1 "./mpconfigport.h" 1
# 1 "include/stdint.h" 1
# 16 "include/stdint.h"
# 1 "include/stdint-gcc.h" 1
# 34 "include/stdint-gcc.h"
typedef signed char int8_t;


typedef short int int16_t;


typedef long int int32_t;


typedef long long int int64_t;


typedef unsigned char uint8_t;


typedef short unsigned int uint16_t;


typedef long unsigned int uint32_t;


typedef long long unsigned int uint64_t;




typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef long int int_least32_t;
typedef long long int int_least64_t;
typedef unsigned char uint_least8_t;
typedef short unsigned int uint_least16_t;
typedef long unsigned int uint_least32_t;
typedef long long unsigned int uint_least64_t;



typedef int int_fast8_t;
typedef int int_fast16_t;
typedef int int_fast32_t;
typedef long long int int_fast64_t;
typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef long long unsigned int uint_fast64_t;




typedef int intptr_t;


typedef unsigned int uintptr_t;




typedef long long int intmax_t;
typedef long long unsigned int uintmax_t;
# 17 "include/stdint.h" 2
# 2 "./mpconfigport.h" 2
# 70 "./mpconfigport.h"
typedef int mp_int_t;
typedef unsigned mp_uint_t;

typedef long mp_off_t;
# 82 "./mpconfigport.h"
# 1 "include/alloca.h" 1
# 10 "include/alloca.h"
# 1 "include/_ansi.h" 1
# 10 "include/_ansi.h"
# 1 "include/newlib.h" 1
# 14 "include/newlib.h"
# 1 "include/_newlib_version.h" 1
# 15 "include/newlib.h" 2
# 11 "include/_ansi.h" 2
# 1 "include/sys/config.h" 1



# 1 "include/machine/ieeefp.h" 1
# 5 "include/sys/config.h" 2
# 1 "include/sys/features.h" 1
# 6 "include/sys/config.h" 2
# 12 "include/_ansi.h" 2
# 11 "include/alloca.h" 2
# 1 "include/sys/reent.h" 1
# 13 "include/sys/reent.h"
# 1 "include/_ansi.h" 1
# 14 "include/sys/reent.h" 2
# 1 "include/stddef.h" 1
# 149 "include/stddef.h"
typedef int ptrdiff_t;
# 216 "include/stddef.h"
typedef unsigned int size_t;
# 328 "include/stddef.h"
typedef long int wchar_t;
# 426 "include/stddef.h"
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
# 437 "include/stddef.h"
} max_align_t;
# 15 "include/sys/reent.h" 2
# 1 "include/sys/_types.h" 1
# 24 "include/sys/_types.h"
# 1 "include/machine/_types.h" 1





# 1 "include/machine/_default_types.h" 1
# 41 "include/machine/_default_types.h"
typedef signed char __int8_t;

typedef unsigned char __uint8_t;
# 55 "include/machine/_default_types.h"
typedef short int __int16_t;

typedef short unsigned int __uint16_t;
# 77 "include/machine/_default_types.h"
typedef long int __int32_t;

typedef long unsigned int __uint32_t;
# 103 "include/machine/_default_types.h"
typedef long long int __int64_t;

typedef long long unsigned int __uint64_t;
# 134 "include/machine/_default_types.h"
typedef signed char __int_least8_t;

typedef unsigned char __uint_least8_t;
# 160 "include/machine/_default_types.h"
typedef short int __int_least16_t;

typedef short unsigned int __uint_least16_t;
# 182 "include/machine/_default_types.h"
typedef long int __int_least32_t;

typedef long unsigned int __uint_least32_t;
# 200 "include/machine/_default_types.h"
typedef long long int __int_least64_t;

typedef long long unsigned int __uint_least64_t;
# 214 "include/machine/_default_types.h"
typedef long long int __intmax_t;







typedef long long unsigned int __uintmax_t;







typedef int __intptr_t;

typedef unsigned int __uintptr_t;
# 7 "include/machine/_types.h" 2
# 17 "include/machine/_types.h"
typedef __int64_t __blkcnt_t;


typedef __int32_t __blksize_t;


typedef __uint32_t __dev_t;



typedef unsigned long __fsblkcnt_t;



typedef unsigned long __fsfilcnt_t;


typedef __uint32_t __uid_t;


typedef __uint32_t __gid_t;


typedef __uint64_t __ino_t;


typedef long long __key_t;


typedef __uint16_t __sa_family_t;



typedef int __socklen_t;
# 25 "include/sys/_types.h" 2
# 1 "include/sys/lock.h" 1
# 12 "include/sys/lock.h"
typedef void *_LOCK_T;
# 42 "include/sys/lock.h"
void __cygwin_lock_init(_LOCK_T *);
void __cygwin_lock_init_recursive(_LOCK_T *);
void __cygwin_lock_fini(_LOCK_T *);
void __cygwin_lock_lock(_LOCK_T *);
int __cygwin_lock_trylock(_LOCK_T *);
void __cygwin_lock_unlock(_LOCK_T *);
# 26 "include/sys/_types.h" 2
# 44 "include/sys/_types.h"
typedef long _off_t;





typedef int __pid_t;
# 65 "include/sys/_types.h"
typedef __uint32_t __id_t;
# 88 "include/sys/_types.h"
typedef __uint32_t __mode_t;





__extension__ typedef long long _off64_t;





typedef _off_t __off_t;


typedef _off64_t __loff_t;
# 114 "include/sys/_types.h"
typedef long _fpos_t;
# 129 "include/sys/_types.h"
typedef unsigned int __size_t;
# 145 "include/sys/_types.h"
typedef signed int _ssize_t;
# 156 "include/sys/_types.h"
typedef _ssize_t __ssize_t;


# 1 "include/stddef.h" 1
# 357 "include/stddef.h"
typedef unsigned int wint_t;
# 160 "include/sys/_types.h" 2



typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    unsigned char __wchb[4];
  } __value;
} _mbstate_t;



typedef _LOCK_T _flock_t;




typedef void *_iconv_t;






typedef unsigned long __clock_t;






typedef __int_least64_t __time_t;


typedef unsigned long __clockid_t;


typedef unsigned long __timer_t;
# 210 "include/sys/_types.h"
typedef unsigned short __nlink_t;
typedef long __suseconds_t;
typedef unsigned long __useconds_t;




typedef char * __va_list;
# 16 "include/sys/reent.h" 2






typedef unsigned long __ULong;
# 38 "include/sys/reent.h"
struct _reent;

struct __locale_t;






struct _Bigint
{
  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  __ULong _x[1];
};


struct __tm
{
  int __tm_sec;
  int __tm_min;
  int __tm_hour;
  int __tm_mday;
  int __tm_mon;
  int __tm_year;
  int __tm_wday;
  int __tm_yday;
  int __tm_isdst;
};







struct _on_exit_args {
 void * _fnargs[32];
 void * _dso_handle[32];

 __ULong _fntypes;


 __ULong _is_cxa;
};
# 93 "include/sys/reent.h"
struct _atexit {
 struct _atexit *_next;
 int _ind;

 void (*_fns[32])(void);
        struct _on_exit_args _on_exit_args;
};
# 117 "include/sys/reent.h"
struct __sbuf {
 unsigned char *_base;
 int _size;
};
# 181 "include/sys/reent.h"
struct __sFILE {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;






  void * _cookie;

  int (*_read) (struct _reent *, void *,
        char *, int);
  int (*_write) (struct _reent *, void *,
         const char *,
         int);
  _fpos_t (*_seek) (struct _reent *, void *, _fpos_t, int);
  int (*_close) (struct _reent *, void *);


  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;


  unsigned char _ubuf[3];
  unsigned char _nbuf[1];


  struct __sbuf _lb;


  int _blksize;
  _off_t _offset;


  struct _reent *_data;



  _flock_t _lock;

  _mbstate_t _mbstate;
  int _flags2;
};
# 287 "include/sys/reent.h"
typedef struct __sFILE __FILE;



struct _glue
{
  struct _glue *_next;
  int _niobs;
  __FILE *_iobs;
};
# 319 "include/sys/reent.h"
struct _rand48 {
  unsigned short _seed[3];
  unsigned short _mult[3];
  unsigned short _add;




};
# 569 "include/sys/reent.h"
struct _reent
{
  int _errno;




  __FILE *_stdin, *_stdout, *_stderr;

  int _inc;
  char _emergency[25];


  int _unspecified_locale_info;
  struct __locale_t *_locale;

  int __sdidinit;

  void (*__cleanup) (struct _reent *);


  struct _Bigint *_result;
  int _result_k;
  struct _Bigint *_p5s;
  struct _Bigint **_freelist;


  int _cvtlen;
  char *_cvtbuf;

  union
    {
      struct
        {
          unsigned int _unused_rand;
          char * _strtok_last;
          char _asctime_buf[26];
          struct __tm _localtime_buf;
          int _gamma_signgam;
          __extension__ unsigned long long _rand_next;
          struct _rand48 _r48;
          _mbstate_t _mblen_state;
          _mbstate_t _mbtowc_state;
          _mbstate_t _wctomb_state;
          char _l64a_buf[8];
          char _signal_buf[24];
          int _getdate_err;
          _mbstate_t _mbrlen_state;
          _mbstate_t _mbrtowc_state;
          _mbstate_t _mbsrtowcs_state;
          _mbstate_t _wcrtomb_state;
          _mbstate_t _wcsrtombs_state;
   int _h_errno;
        } _reent;



      struct
        {

          unsigned char * _nextf[30];
          unsigned int _nmalloc[30];
        } _unused;
    } _new;



  struct _atexit *_atexit;
  struct _atexit _atexit0;



  void (**(_sig_func))(int);




  struct _glue __sglue;

  __FILE __sf[3];

};
# 775 "include/sys/reent.h"
extern struct _reent *_impure_ptr ;
extern struct _reent *const _global_impure_ptr ;

void _reclaim_reent (struct _reent *);
# 12 "include/alloca.h" 2
# 83 "./mpconfigport.h" 2
# 46 "../../py/mpconfig.h" 2
# 28 "<stdin>" 2





QCFG(BYTES_IN_LEN, (1))
QCFG(BYTES_IN_HASH, (1))

Q()
Q(*)
Q(_)
Q(/)
Q(%#o)
Q(%#x)
Q({:#b})
Q( )
Q(\n)
Q(maximum recursion depth exceeded)
Q(<module>)
Q(<lambda>)
Q(<listcomp>)
Q(<dictcomp>)
Q(<setcomp>)
Q(<genexpr>)
Q(<string>)
Q(<stdin>)
Q(utf-8)





Q(ArithmeticError)

Q(ArithmeticError)

Q(AssertionError)

Q(AssertionError)

Q(AssertionError)

Q(AttributeError)

Q(AttributeError)

Q(BaseException)

Q(BaseException)

Q(BytesIO)

Q(BytesIO)

Q(EOFError)

Q(EOFError)

Q(Ellipsis)

Q(Ellipsis)

Q(Exception)

Q(Exception)

Q(GeneratorExit)

Q(GeneratorExit)

Q(ImportError)

Q(ImportError)

Q(IndentationError)

Q(IndentationError)

Q(IndexError)

Q(IndexError)

Q(KeyError)

Q(KeyError)

Q(KeyboardInterrupt)

Q(KeyboardInterrupt)

Q(LookupError)

Q(LookupError)

Q(MemoryError)

Q(MemoryError)

Q(NameError)

Q(NameError)

Q(NoneType)

Q(NotImplementedError)

Q(NotImplementedError)

Q(OSError)

Q(OSError)

Q(OverflowError)

Q(OverflowError)

Q(RuntimeError)

Q(RuntimeError)

Q(StopIteration)

Q(StopIteration)

Q(StringIO)

Q(StringIO)

Q(SyntaxError)

Q(SyntaxError)

Q(SystemExit)

Q(SystemExit)

Q(TypeError)

Q(TypeError)

Q(ValueError)

Q(ValueError)

Q(ZeroDivisionError)

Q(ZeroDivisionError)

Q(_0x0a_)

Q(__add__)

Q(__bool__)

Q(__build_class__)

Q(__call__)

Q(__class__)

Q(__class__)

Q(__class__)

Q(__class__)

Q(__class__)

Q(__contains__)

Q(__delitem__)

Q(__delitem__)

Q(__enter__)

Q(__enter__)

Q(__eq__)

Q(__eq__)

Q(__exit__)

Q(__exit__)

Q(__ge__)

Q(__getattr__)

Q(__getattr__)

Q(__getitem__)

Q(__getitem__)

Q(__getitem__)

Q(__getitem__)

Q(__gt__)

Q(__hash__)

Q(__iadd__)

Q(__import__)

Q(__init__)

Q(__init__)

Q(__isub__)

Q(__iter__)

Q(__le__)

Q(__len__)

Q(__lt__)

Q(__main__)

Q(__main__)

Q(__main__)

Q(__module__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__new__)

Q(__new__)

Q(__next__)

Q(__next__)

Q(__next__)

Q(__next__)

Q(__path__)

Q(__path__)

Q(__path__)

Q(__qualname__)

Q(__repl_print__)

Q(__repl_print__)

Q(__repr__)

Q(__repr__)

Q(__setitem__)

Q(__setitem__)

Q(__str__)

Q(__sub__)

Q(__traceback__)

Q(_brace_open__colon__hash_b_brace_close_)

Q(_lt_dictcomp_gt_)

Q(_lt_genexpr_gt_)

Q(_lt_lambda_gt_)

Q(_lt_listcomp_gt_)

Q(_lt_module_gt_)

Q(_lt_setcomp_gt_)

Q(_lt_string_gt_)

Q(_percent__hash_o)

Q(_percent__hash_x)

Q(_space_)

Q(_star_)

Q(_star_)

Q(abs)

Q(all)

Q(any)

Q(append)

Q(args)

Q(argv)

Q(big)

Q(bin)

Q(bool)

Q(bool)

Q(bound_method)

Q(builtins)

Q(builtins)

Q(bytecode)

Q(byteorder)

Q(bytes)

Q(bytes)

Q(bytes)

Q(callable)

Q(chr)

Q(classmethod)

Q(classmethod)

Q(clear)

Q(clear)

Q(close)

Q(close)

Q(close)

Q(closure)

Q(closure)

Q(collect)

Q(complex)

Q(const)

Q(copy)

Q(copy)

Q(count)

Q(count)

Q(count)

Q(dict)

Q(dict)

Q(dict_view)

Q(dir)

Q(disable)

Q(divmod)

Q(enable)

Q(end)

Q(endswith)

Q(eval)

Q(exec)

Q(exit)

Q(extend)

Q(find)

Q(float)

Q(flush)

Q(format)

Q(from_bytes)

Q(fromkeys)

Q(function)

Q(function)

Q(function)

Q(function)

Q(function)

Q(function)

Q(function)

Q(function)

Q(gc)

Q(gc)

Q(generator)

Q(generator)

Q(generator)

Q(get)

Q(getattr)

Q(getvalue)

Q(globals)

Q(hasattr)

Q(hash)

Q(heap_lock)

Q(heap_unlock)

Q(hex)

Q(id)

Q(imag)

Q(implementation)

Q(index)

Q(index)

Q(index)

Q(input)

Q(insert)

Q(int)

Q(int)

Q(isalpha)

Q(isdigit)

Q(isenabled)

Q(isinstance)

Q(islower)

Q(isspace)

Q(issubclass)

Q(isupper)

Q(items)

Q(iter)

Q(iterator)

Q(iterator)

Q(iterator)

Q(iterator)

Q(join)

Q(key)

Q(keys)

Q(keys)

Q(len)

Q(list)

Q(list)

Q(little)

Q(little)

Q(little)

Q(locals)

Q(lower)

Q(lstrip)

Q(map)

Q(map)

Q(mem_alloc)

Q(mem_free)

Q(micropython)

Q(micropython)

Q(micropython)

Q(micropython)

Q(module)

Q(modules)

Q(next)

Q(object)

Q(object)

Q(oct)

Q(open)

Q(open)

Q(opt_level)

Q(ord)

Q(path)

Q(pend_throw)

Q(pop)

Q(pop)

Q(popitem)

Q(pow)

Q(print)

Q(print_exception)

Q(range)

Q(range)

Q(range)

Q(read)

Q(readinto)

Q(readline)

Q(real)

Q(remove)

Q(replace)

Q(repr)

Q(reverse)

Q(reverse)

Q(rfind)

Q(rindex)

Q(round)

Q(rsplit)

Q(rstrip)

Q(seek)

Q(send)

Q(send)

Q(sep)

Q(setattr)

Q(setdefault)

Q(sort)

Q(sorted)

Q(split)

Q(start)

Q(startswith)

Q(staticmethod)

Q(staticmethod)

Q(step)

Q(stop)

Q(str)

Q(str)

Q(str)

Q(str)

Q(strip)

Q(sum)

Q(super)

Q(super)

Q(super)

Q(sys)

Q(sys)

Q(throw)

Q(throw)

Q(to_bytes)

Q(tuple)

Q(tuple)

Q(type)

Q(type)

Q(uio)

Q(uio)

Q(update)

Q(upper)

Q(value)

Q(values)

Q(version)

Q(version_info)

Q(write)

Q(zip)

Q(zip)
