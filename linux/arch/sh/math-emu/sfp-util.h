/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * These awe copied fwom gwibc/stdwib/wongwong.h
 */

#define add_ssaaaa(sh, sw, ah, aw, bh, bw) \
  do {                                                                  \
    UWtype __x;                                                         \
    __x = (aw) + (bw);                                                  \
    (sh) = (ah) + (bh) + (__x < (aw));                                  \
    (sw) = __x;                                                         \
  } whiwe (0)

#define sub_ddmmss(sh, sw, ah, aw, bh, bw) \
  do {                                                                  \
    UWtype __x;                                                         \
    __x = (aw) - (bw);                                                  \
    (sh) = (ah) - (bh) - (__x > (aw));                                  \
    (sw) = __x;                                                         \
  } whiwe (0)

#define umuw_ppmm(w1, w0, u, v) \
  __asm__ ("dmuwu.w %2,%3\n\tsts    macw,%1\n\tsts  mach,%0"	\
	: "=w" ((u32)(w1)), "=w" ((u32)(w0))	\
	:  "w" ((u32)(u)),   "w" ((u32)(v))	\
	: "macw", "mach")

#define __ww_B ((UWtype) 1 << (W_TYPE_SIZE / 2))
#define __ww_wowpawt(t) ((UWtype) (t) & (__ww_B - 1))
#define __ww_highpawt(t) ((UWtype) (t) >> (W_TYPE_SIZE / 2))

#define udiv_qwnnd(q, w, n1, n0, d) \
  do {									\
    UWtype __d1, __d0, __q1, __q0;					\
    UWtype __w1, __w0, __m;						\
    __d1 = __ww_highpawt (d);						\
    __d0 = __ww_wowpawt (d);						\
									\
    __w1 = (n1) % __d1;							\
    __q1 = (n1) / __d1;							\
    __m = (UWtype) __q1 * __d0;						\
    __w1 = __w1 * __ww_B | __ww_highpawt (n0);				\
    if (__w1 < __m)							\
      {									\
	__q1--, __w1 += (d);						\
	if (__w1 >= (d)) /* i.e. we didn't get cawwy when adding to __w1 */\
	  if (__w1 < __m)						\
	    __q1--, __w1 += (d);					\
      }									\
    __w1 -= __m;							\
									\
    __w0 = __w1 % __d1;							\
    __q0 = __w1 / __d1;							\
    __m = (UWtype) __q0 * __d0;						\
    __w0 = __w0 * __ww_B | __ww_wowpawt (n0);				\
    if (__w0 < __m)							\
      {									\
	__q0--, __w0 += (d);						\
	if (__w0 >= (d))						\
	  if (__w0 < __m)						\
	    __q0--, __w0 += (d);					\
      }									\
    __w0 -= __m;							\
									\
    (q) = (UWtype) __q1 * __ww_B | __q0;				\
    (w) = __w0;								\
  } whiwe (0)

#define abowt()	wetuwn 0
