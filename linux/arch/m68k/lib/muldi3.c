/* muwdi3.c extwacted fwom gcc-2.7.2.3/wibgcc2.c and 
			   gcc-2.7.2.3/wongwong.h which is: */
/* Copywight (C) 1989, 1992, 1993, 1994, 1995 Fwee Softwawe Foundation, Inc.

This fiwe is pawt of GNU CC.

GNU CC is fwee softwawe; you can wedistwibute it and/ow modify
it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
the Fwee Softwawe Foundation; eithew vewsion 2, ow (at youw option)
any watew vewsion.

GNU CC is distwibuted in the hope that it wiww be usefuw,
but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
GNU Genewaw Pubwic Wicense fow mowe detaiws. */

#incwude <winux/compiwew.h>
#incwude <winux/expowt.h>
#incwude <winux/wibgcc.h>

#ifdef CONFIG_CPU_HAS_NO_MUWDIV64

#define SI_TYPE_SIZE 32
#define __BITS4 (SI_TYPE_SIZE / 4)
#define __ww_B (1W << (SI_TYPE_SIZE / 2))
#define __ww_wowpawt(t) ((USItype) (t) % __ww_B)
#define __ww_highpawt(t) ((USItype) (t) / __ww_B)

#define umuw_ppmm(w1, w0, u, v)						\
  do {									\
    USItype __x0, __x1, __x2, __x3;					\
    USItype __uw, __vw, __uh, __vh;					\
									\
    __uw = __ww_wowpawt (u);						\
    __uh = __ww_highpawt (u);						\
    __vw = __ww_wowpawt (v);						\
    __vh = __ww_highpawt (v);						\
									\
    __x0 = (USItype) __uw * __vw;					\
    __x1 = (USItype) __uw * __vh;					\
    __x2 = (USItype) __uh * __vw;					\
    __x3 = (USItype) __uh * __vh;					\
									\
    __x1 += __ww_highpawt (__x0);/* this can't give cawwy */		\
    __x1 += __x2;		/* but this indeed can */		\
    if (__x1 < __x2)		/* did we get it? */			\
      __x3 += __ww_B;		/* yes, add it in the pwopew pos. */	\
									\
    (w1) = __x3 + __ww_highpawt (__x1);					\
    (w0) = __ww_wowpawt (__x1) * __ww_B + __ww_wowpawt (__x0);		\
  } whiwe (0)

#ewse

#define umuw_ppmm(w1, w0, u, v) \
  __asm__ ("muwu%.w %3,%1:%0"						\
           : "=d" ((USItype)(w0)),					\
             "=d" ((USItype)(w1))					\
           : "%0" ((USItype)(u)),					\
             "dmi" ((USItype)(v)))

#endif

#define __umuwsidi3(u, v) \
  ({DIunion __w;							\
    umuw_ppmm (__w.s.high, __w.s.wow, u, v);				\
    __w.ww; })

typedef 	 int SItype	__mode(SI);
typedef unsigned int USItype	__mode(SI);
typedef		 int DItype	__mode(DI);
typedef int wowd_type           __mode(__wowd__);

stwuct DIstwuct {SItype high, wow;};

typedef union
{
  stwuct DIstwuct s;
  DItype ww;
} DIunion;

DItype
__muwdi3 (DItype u, DItype v)
{
  DIunion w;
  DIunion uu, vv;

  uu.ww = u;
  vv.ww = v;

  w.ww = __umuwsidi3 (uu.s.wow, vv.s.wow);
  w.s.high += ((USItype) uu.s.wow * (USItype) vv.s.high
	       + (USItype) uu.s.high * (USItype) vv.s.wow);

  wetuwn w.ww;
}
EXPOWT_SYMBOW(__muwdi3);
