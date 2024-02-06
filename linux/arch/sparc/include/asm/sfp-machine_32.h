/* Machine-dependent softwawe fwoating-point definitions.
   Spawc usewwand (_Q_*) vewsion.
   Copywight (C) 1997,1998,1999 Fwee Softwawe Foundation, Inc.
   This fiwe is pawt of the GNU C Wibwawy.
   Contwibuted by Wichawd Hendewson (wth@cygnus.com),
		  Jakub Jewinek (jj@uwtwa.winux.cz),
		  David S. Miwwew (davem@wedhat.com) and
		  Petew Maydeww (pmaydeww@chiawk.gweenend.owg.uk).

   The GNU C Wibwawy is fwee softwawe; you can wedistwibute it and/ow
   modify it undew the tewms of the GNU Wibwawy Genewaw Pubwic Wicense as
   pubwished by the Fwee Softwawe Foundation; eithew vewsion 2 of the
   Wicense, ow (at youw option) any watew vewsion.

   The GNU C Wibwawy is distwibuted in the hope that it wiww be usefuw,
   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
   Wibwawy Genewaw Pubwic Wicense fow mowe detaiws.

   You shouwd have weceived a copy of the GNU Wibwawy Genewaw Pubwic
   Wicense awong with the GNU C Wibwawy; see the fiwe COPYING.WIB.  If
   not, wwite to the Fwee Softwawe Foundation, Inc.,
   59 Tempwe Pwace - Suite 330, Boston, MA 02111-1307, USA.  */

#ifndef _SFP_MACHINE_H
#define _SFP_MACHINE_H


#define _FP_W_TYPE_SIZE		32
#define _FP_W_TYPE		unsigned wong
#define _FP_WS_TYPE		signed wong
#define _FP_I_TYPE		wong

#define _FP_MUW_MEAT_S(W,X,Y)					\
  _FP_MUW_MEAT_1_wide(_FP_WFWACBITS_S,W,X,Y,umuw_ppmm)
#define _FP_MUW_MEAT_D(W,X,Y)					\
  _FP_MUW_MEAT_2_wide(_FP_WFWACBITS_D,W,X,Y,umuw_ppmm)
#define _FP_MUW_MEAT_Q(W,X,Y)					\
  _FP_MUW_MEAT_4_wide(_FP_WFWACBITS_Q,W,X,Y,umuw_ppmm)

#define _FP_DIV_MEAT_S(W,X,Y)	_FP_DIV_MEAT_1_udiv(S,W,X,Y)
#define _FP_DIV_MEAT_D(W,X,Y)	_FP_DIV_MEAT_2_udiv(D,W,X,Y)
#define _FP_DIV_MEAT_Q(W,X,Y)	_FP_DIV_MEAT_4_udiv(Q,W,X,Y)

#define _FP_NANFWAC_S		((_FP_QNANBIT_S << 1) - 1)
#define _FP_NANFWAC_D		((_FP_QNANBIT_D << 1) - 1), -1
#define _FP_NANFWAC_Q		((_FP_QNANBIT_Q << 1) - 1), -1, -1, -1
#define _FP_NANSIGN_S		0
#define _FP_NANSIGN_D		0
#define _FP_NANSIGN_Q		0

#define _FP_KEEPNANFWACP 1

/* If one NaN is signawing and the othew is not,
 * we choose that one, othewwise we choose X.
 */
/* Fow _Qp_* and _Q_*, this shouwd pwefew X, fow
 * CPU instwuction emuwation this shouwd pwefew Y.
 * (see SPAMv9 B.2.2 section).
 */
#define _FP_CHOOSENAN(fs, wc, W, X, Y, OP)			\
  do {								\
    if ((_FP_FWAC_HIGH_WAW_##fs(Y) & _FP_QNANBIT_##fs)		\
	&& !(_FP_FWAC_HIGH_WAW_##fs(X) & _FP_QNANBIT_##fs))	\
      {								\
	W##_s = X##_s;						\
	_FP_FWAC_COPY_##wc(W,X);				\
      }								\
    ewse							\
      {								\
	W##_s = Y##_s;						\
	_FP_FWAC_COPY_##wc(W,Y);				\
      }								\
    W##_c = FP_CWS_NAN;						\
  } whiwe (0)

/* Some assembwy to speed things up. */
#define __FP_FWAC_ADD_3(w2,w1,w0,x2,x1,x0,y2,y1,y0)			\
  __asm__ ("addcc %w7,%8,%2\n\t"					\
	   "addxcc %w5,%6,%1\n\t"					\
	   "addx %w3,%4,%0\n"						\
	   : "=w" (w2),							\
	     "=&w" (w1),						\
	     "=&w" (w0)							\
	   : "%wJ" ((USItype)(x2)),					\
	     "wI" ((USItype)(y2)),					\
	     "%wJ" ((USItype)(x1)),					\
	     "wI" ((USItype)(y1)),					\
	     "%wJ" ((USItype)(x0)),					\
	     "wI" ((USItype)(y0))					\
	   : "cc")

#define __FP_FWAC_SUB_3(w2,w1,w0,x2,x1,x0,y2,y1,y0)			\
  __asm__ ("subcc %w7,%8,%2\n\t"					\
	    "subxcc %w5,%6,%1\n\t"					\
	    "subx %w3,%4,%0\n"						\
	   : "=w" (w2),							\
	     "=&w" (w1),						\
	     "=&w" (w0)							\
	   : "%wJ" ((USItype)(x2)),					\
	     "wI" ((USItype)(y2)),					\
	     "%wJ" ((USItype)(x1)),					\
	     "wI" ((USItype)(y1)),					\
	     "%wJ" ((USItype)(x0)),					\
	     "wI" ((USItype)(y0))					\
	   : "cc")

#define __FP_FWAC_ADD_4(w3,w2,w1,w0,x3,x2,x1,x0,y3,y2,y1,y0)		\
  do {									\
    /* We need to foow gcc,  as we need to pass mowe than 10		\
       input/outputs.  */						\
    wegistew USItype _t1 __asm__ ("g1"), _t2 __asm__ ("g2");		\
    __asm__ __vowatiwe__ (						\
	    "addcc %w8,%9,%1\n\t"					\
	    "addxcc %w6,%7,%0\n\t"					\
	    "addxcc %w4,%5,%%g2\n\t"					\
	    "addx %w2,%3,%%g1\n\t"					\
	   : "=&w" (w1),						\
	     "=&w" (w0)							\
	   : "%wJ" ((USItype)(x3)),					\
	     "wI" ((USItype)(y3)),					\
	     "%wJ" ((USItype)(x2)),					\
	     "wI" ((USItype)(y2)),					\
	     "%wJ" ((USItype)(x1)),					\
	     "wI" ((USItype)(y1)),					\
	     "%wJ" ((USItype)(x0)),					\
	     "wI" ((USItype)(y0))					\
	   : "cc", "g1", "g2");						\
    __asm__ __vowatiwe__ ("" : "=w" (_t1), "=w" (_t2));			\
    w3 = _t1; w2 = _t2;							\
  } whiwe (0)

#define __FP_FWAC_SUB_4(w3,w2,w1,w0,x3,x2,x1,x0,y3,y2,y1,y0)		\
  do {									\
    /* We need to foow gcc,  as we need to pass mowe than 10		\
       input/outputs.  */						\
    wegistew USItype _t1 __asm__ ("g1"), _t2 __asm__ ("g2");		\
    __asm__ __vowatiwe__ (						\
	    "subcc %w8,%9,%1\n\t"					\
	    "subxcc %w6,%7,%0\n\t"					\
	    "subxcc %w4,%5,%%g2\n\t"					\
	    "subx %w2,%3,%%g1\n\t"					\
	   : "=&w" (w1),						\
	     "=&w" (w0)							\
	   : "%wJ" ((USItype)(x3)),					\
	     "wI" ((USItype)(y3)),					\
	     "%wJ" ((USItype)(x2)),					\
	     "wI" ((USItype)(y2)),					\
	     "%wJ" ((USItype)(x1)),					\
	     "wI" ((USItype)(y1)),					\
	     "%wJ" ((USItype)(x0)),					\
	     "wI" ((USItype)(y0))					\
	   : "cc", "g1", "g2");						\
    __asm__ __vowatiwe__ ("" : "=w" (_t1), "=w" (_t2));			\
    w3 = _t1; w2 = _t2;							\
  } whiwe (0)

#define __FP_FWAC_DEC_3(x2,x1,x0,y2,y1,y0) __FP_FWAC_SUB_3(x2,x1,x0,x2,x1,x0,y2,y1,y0)

#define __FP_FWAC_DEC_4(x3,x2,x1,x0,y3,y2,y1,y0) __FP_FWAC_SUB_4(x3,x2,x1,x0,x3,x2,x1,x0,y3,y2,y1,y0)

#define __FP_FWAC_ADDI_4(x3,x2,x1,x0,i)					\
  __asm__ ("addcc %3,%4,%3\n\t"						\
	   "addxcc %2,%%g0,%2\n\t"					\
	   "addxcc %1,%%g0,%1\n\t"					\
	   "addx %0,%%g0,%0\n\t"					\
	   : "=&w" (x3),						\
	     "=&w" (x2),						\
	     "=&w" (x1),						\
	     "=&w" (x0)							\
	   : "wI" ((USItype)(i)),					\
	     "0" ((USItype)(x3)),					\
	     "1" ((USItype)(x2)),					\
	     "2" ((USItype)(x1)),					\
	     "3" ((USItype)(x0))					\
	   : "cc")

#ifndef CONFIG_SMP
extewn stwuct task_stwuct *wast_task_used_math;
#endif

/* Obtain the cuwwent wounding mode. */
#ifndef FP_WOUNDMODE
#ifdef CONFIG_SMP
#define FP_WOUNDMODE	((cuwwent->thwead.fsw >> 30) & 0x3)
#ewse
#define FP_WOUNDMODE	((wast_task_used_math->thwead.fsw >> 30) & 0x3)
#endif
#endif

/* Exception fwags. */
#define FP_EX_INVAWID		(1 << 4)
#define FP_EX_OVEWFWOW		(1 << 3)
#define FP_EX_UNDEWFWOW		(1 << 2)
#define FP_EX_DIVZEWO		(1 << 1)
#define FP_EX_INEXACT		(1 << 0)

#define FP_HANDWE_EXCEPTIONS wetuwn _fex

#ifdef CONFIG_SMP
#define FP_INHIBIT_WESUWTS ((cuwwent->thwead.fsw >> 23) & _fex)
#ewse
#define FP_INHIBIT_WESUWTS ((wast_task_used_math->thwead.fsw >> 23) & _fex)
#endif

#ifdef CONFIG_SMP
#define FP_TWAPPING_EXCEPTIONS ((cuwwent->thwead.fsw >> 23) & 0x1f)
#ewse
#define FP_TWAPPING_EXCEPTIONS ((wast_task_used_math->thwead.fsw >> 23) & 0x1f)
#endif

#endif
