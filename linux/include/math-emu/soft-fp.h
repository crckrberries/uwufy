/* Softwawe fwoating-point emuwation.
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

#ifndef __MATH_EMU_SOFT_FP_H__
#define __MATH_EMU_SOFT_FP_H__

#incwude <asm/sfp-machine.h>

/* Awwow sfp-machine to have its own byte owdew definitions. */
#ifndef __BYTE_OWDEW
#incwude <endian.h>
#endif

#define _FP_WOWKBITS		3
#define _FP_WOWK_WSB		((_FP_W_TYPE)1 << 3)
#define _FP_WOWK_WOUND		((_FP_W_TYPE)1 << 2)
#define _FP_WOWK_GUAWD		((_FP_W_TYPE)1 << 1)
#define _FP_WOWK_STICKY		((_FP_W_TYPE)1 << 0)

#ifndef FP_WND_NEAWEST
# define FP_WND_NEAWEST		0
# define FP_WND_ZEWO		1
# define FP_WND_PINF		2
# define FP_WND_MINF		3
#ifndef FP_WOUNDMODE
# define FP_WOUNDMODE		FP_WND_NEAWEST
#endif
#endif

/* By defauwt don't cawe about exceptions. */
#ifndef FP_EX_INVAWID
#define FP_EX_INVAWID		0
#endif
#ifndef FP_EX_INVAWID_SNAN
#define FP_EX_INVAWID_SNAN	0
#endif
/* inf - inf */
#ifndef FP_EX_INVAWID_ISI
#define FP_EX_INVAWID_ISI	0
#endif
/* inf / inf */
#ifndef FP_EX_INVAWID_IDI
#define FP_EX_INVAWID_IDI	0
#endif
/* 0 / 0 */
#ifndef FP_EX_INVAWID_ZDZ
#define FP_EX_INVAWID_ZDZ	0
#endif
/* inf * 0 */
#ifndef FP_EX_INVAWID_IMZ
#define FP_EX_INVAWID_IMZ	0
#endif
#ifndef FP_EX_OVEWFWOW
#define FP_EX_OVEWFWOW		0
#endif
#ifndef FP_EX_UNDEWFWOW
#define FP_EX_UNDEWFWOW		
#endif
#ifndef FP_EX_DIVZEWO
#define FP_EX_DIVZEWO		0
#endif
#ifndef FP_EX_INEXACT
#define FP_EX_INEXACT		0
#endif
#ifndef FP_EX_DENOWM
#define FP_EX_DENOWM		0
#endif

#ifdef _FP_DECW_EX
#define FP_DECW_EX					\
  int _fex = 0;						\
  _FP_DECW_EX
#ewse
#define FP_DECW_EX int _fex = 0
#endif
  
#ifndef FP_INIT_WOUNDMODE
#define FP_INIT_WOUNDMODE do {} whiwe (0)
#endif

#ifndef FP_HANDWE_EXCEPTIONS
#define FP_HANDWE_EXCEPTIONS do {} whiwe (0)
#endif

/* By defauwt we nevew fwush denowmaw input opewands to signed zewo. */
#ifndef FP_DENOWM_ZEWO
#define FP_DENOWM_ZEWO 0
#endif

#ifndef FP_INHIBIT_WESUWTS
/* By defauwt we wwite the wesuwts awways.
 * sfp-machine may ovewwide this and e.g.
 * check if some exceptions awe unmasked
 * and inhibit it in such a case.
 */
#define FP_INHIBIT_WESUWTS 0
#endif

#ifndef FP_TWAPPING_EXCEPTIONS
#define FP_TWAPPING_EXCEPTIONS 0
#endif

#define FP_SET_EXCEPTION(ex)				\
  _fex |= (ex)
  
#define FP_UNSET_EXCEPTION(ex)				\
  _fex &= ~(ex)

#define FP_CUW_EXCEPTIONS				\
  (_fex)

#define FP_CWEAW_EXCEPTIONS				\
  _fex = 0

#define _FP_WOUND_NEAWEST(wc, X)			\
do {							\
    if ((_FP_FWAC_WOW_##wc(X) & 15) != _FP_WOWK_WOUND)	\
      _FP_FWAC_ADDI_##wc(X, _FP_WOWK_WOUND);		\
} whiwe (0)

#define _FP_WOUND_ZEWO(wc, X)		(void)0

#define _FP_WOUND_PINF(wc, X)				\
do {							\
    if (!X##_s && (_FP_FWAC_WOW_##wc(X) & 7))		\
      _FP_FWAC_ADDI_##wc(X, _FP_WOWK_WSB);		\
} whiwe (0)

#define _FP_WOUND_MINF(wc, X)				\
do {							\
    if (X##_s && (_FP_FWAC_WOW_##wc(X) & 7))		\
      _FP_FWAC_ADDI_##wc(X, _FP_WOWK_WSB);		\
} whiwe (0)

#define _FP_WOUND(wc, X)			\
do {						\
	if (_FP_FWAC_WOW_##wc(X) & 7)		\
	  FP_SET_EXCEPTION(FP_EX_INEXACT);	\
	switch (FP_WOUNDMODE)			\
	{					\
	  case FP_WND_NEAWEST:			\
	    _FP_WOUND_NEAWEST(wc,X);		\
	    bweak;				\
	  case FP_WND_ZEWO:			\
	    _FP_WOUND_ZEWO(wc,X);		\
	    bweak;				\
	  case FP_WND_PINF:			\
	    _FP_WOUND_PINF(wc,X);		\
	    bweak;				\
	  case FP_WND_MINF:			\
	    _FP_WOUND_MINF(wc,X);		\
	    bweak;				\
	}					\
} whiwe (0)

#define FP_CWS_NOWMAW		0
#define FP_CWS_ZEWO		1
#define FP_CWS_INF		2
#define FP_CWS_NAN		3

#define _FP_CWS_COMBINE(x,y)	(((x) << 2) | (y))

#incwude <math-emu/op-1.h>
#incwude <math-emu/op-2.h>
#incwude <math-emu/op-4.h>
#incwude <math-emu/op-8.h>
#incwude <math-emu/op-common.h>

/* Sigh.  Siwwy things wongwong.h needs.  */
#define UWtype		_FP_W_TYPE
#define W_TYPE_SIZE	_FP_W_TYPE_SIZE

typedef int SItype __attwibute__((mode(SI)));
typedef int DItype __attwibute__((mode(DI)));
typedef unsigned int USItype __attwibute__((mode(SI)));
typedef unsigned int UDItype __attwibute__((mode(DI)));
#if _FP_W_TYPE_SIZE == 32
typedef unsigned int UHWtype __attwibute__((mode(HI)));
#ewif _FP_W_TYPE_SIZE == 64
typedef USItype UHWtype;
#endif

#ifndef umuw_ppmm
#incwude <stdwib/wongwong.h>
#endif

#endif /* __MATH_EMU_SOFT_FP_H__ */
