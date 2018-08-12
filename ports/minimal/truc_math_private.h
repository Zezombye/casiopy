#ifndef truc_math_private
#define truc_math_private

#ifndef GET_HIGH_WORD
# define GET_HIGH_WORD(i,d)					\
do {								\
  ieee_double_shape_type gh_u;					\
  gh_u.value = (d);						\
  (i) = gh_u.parts.msw;						\
} while (0)
#endif

/* Set the more significant 32 bits of a double from an int.  */
#ifndef SET_HIGH_WORD
#define SET_HIGH_WORD(d,v)					\
do {								\
  ieee_double_shape_type sh_u;					\
  sh_u.value = (d);						\
  sh_u.parts.msw = (v);						\
  (d) = sh_u.value;						\
} while (0)
#endif

#ifndef math_opt_barrier
# define math_opt_barrier(x) \
({ __typeof (x) __x = (x); __asm ("" : "+m" (__x)); __x; })
# define math_force_eval(x) \
({ __typeof (x) __x = (x); __asm __volatile__ ("" : : "m" (__x)); })
#endif

typedef union
{
  double value;
  struct
  {
    __uint32_t msw;
    __uint32_t lsw;
  } parts;
  __uint64_t word;
} ieee_double_shape_type;

#endif