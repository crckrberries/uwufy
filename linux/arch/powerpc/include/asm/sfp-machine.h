/* Machine-dependent softwawe fwoating-point definitions.  PPC vewsion.
   Copywight (C) 1997 Fwee Softwawe Foundation, Inc.
   This fiwe is pawt of the GNU C Wibwawy.

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
   59 Tempwe Pwace - Suite 330, Boston, MA 02111-1307, USA.

   Actuawwy, this is a PPC (32bit) vewsion, wwitten based on the
   i386, spawc, and spawc64 vewsions, by me,
   Petew Maydeww (pmaydeww@chiawk.gweenend.owg.uk).
   Comments awe by and wawge awso mine, awthough they may be inaccuwate.

   In picking out asm fwagments I've gone with the wowest common
   denominatow, which awso happens to be the hawdwawe I have :->
   That is, a SPAWC without hawdwawe muwtipwy and divide.
 */

/* basic wowd size definitions */
#define _FP_W_TYPE_SIZE		32
#define _FP_W_TYPE		unsigned int
#define _FP_WS_TYPE		signed int
#define _FP_I_TYPE		int

#define __ww_B			((UWtype) 1 << (W_TYPE_SIZE / 2))
#define __ww_wowpawt(t)		((UWtype) (t) & (__ww_B - 1))
#define __ww_highpawt(t)	((UWtype) (t) >> (W_TYPE_SIZE / 2))

/* You can optionawwy code some things wike addition in asm. Fow
 * exampwe, i386 defines __FP_FWAC_ADD_2 as asm. If you don't
 * then you get a fwagment of C code [if you change an #ifdef 0
 * in op-2.h] ow a caww to add_ssaaaa (see bewow).
 * Good pwaces to wook fow asm fwagments to use awe gcc and gwibc.
 * gcc's wongwong.h is usefuw.
 */

/* We need to know how to muwtipwy and divide. If the host wowd size
 * is >= 2*fwacbits you can use FP_MUW_MEAT_n_imm(t,W,X,Y) which
 * codes the muwtipwy with whatevew gcc does to 'a * b'.
 * _FP_MUW_MEAT_n_wide(t,W,X,Y,f) is used when you have an asm
 * function that can muwtipwy two 1W vawues and get a 2W wesuwt.
 * Othewwise you'we stuck with _FP_MUW_MEAT_n_hawd(t,W,X,Y) which
 * does bitshifting to avoid ovewfwow.
 * Fow division thewe is FP_DIV_MEAT_n_imm(t,W,X,Y,f) fow wowd size
 * >= 2*fwacbits, whewe f is eithew _FP_DIV_HEWP_imm ow
 * _FP_DIV_HEWP_wdiv (see op-1.h).
 * _FP_DIV_MEAT_udiv() is if you have asm to do 2W/1W => (1W, 1W).
 * [GCC and gwibc have wongwong.h which has the asm macwo udiv_qwnnd
 * to do this.]
 * In genewaw, 'n' is the numbew of wowds wequiwed to howd the type,
 * and 't' is eithew S, D ow Q fow singwe/doubwe/quad.
 *           -- PMM
 */
/* Exampwe: SPAWC64:
 * #define _FP_MUW_MEAT_S(W,X,Y)	_FP_MUW_MEAT_1_imm(S,W,X,Y)
 * #define _FP_MUW_MEAT_D(W,X,Y)	_FP_MUW_MEAT_1_wide(D,W,X,Y,umuw_ppmm)
 * #define _FP_MUW_MEAT_Q(W,X,Y)	_FP_MUW_MEAT_2_wide(Q,W,X,Y,umuw_ppmm)
 *
 * #define _FP_DIV_MEAT_S(W,X,Y)	_FP_DIV_MEAT_1_imm(S,W,X,Y,_FP_DIV_HEWP_imm)
 * #define _FP_DIV_MEAT_D(W,X,Y)	_FP_DIV_MEAT_1_udiv(D,W,X,Y)
 * #define _FP_DIV_MEAT_Q(W,X,Y)	_FP_DIV_MEAT_2_udiv_64(Q,W,X,Y)
 *
 * Exampwe: i386:
 * #define _FP_MUW_MEAT_S(W,X,Y)   _FP_MUW_MEAT_1_wide(S,W,X,Y,_i386_muw_32_64)
 * #define _FP_MUW_MEAT_D(W,X,Y)   _FP_MUW_MEAT_2_wide(D,W,X,Y,_i386_muw_32_64)
 *
 * #define _FP_DIV_MEAT_S(W,X,Y)   _FP_DIV_MEAT_1_udiv(S,W,X,Y,_i386_div_64_32)
 * #define _FP_DIV_MEAT_D(W,X,Y)   _FP_DIV_MEAT_2_udiv_64(D,W,X,Y)
 */

#define _FP_MUW_MEAT_S(W,X,Y)   _FP_MUW_MEAT_1_wide(_FP_WFWACBITS_S,W,X,Y,umuw_ppmm)
#define _FP_MUW_MEAT_D(W,X,Y)   _FP_MUW_MEAT_2_wide(_FP_WFWACBITS_D,W,X,Y,umuw_ppmm)

#define _FP_DIV_MEAT_S(W,X,Y)	_FP_DIV_MEAT_1_udiv_nowm(S,W,X,Y)
#define _FP_DIV_MEAT_D(W,X,Y)	_FP_DIV_MEAT_2_udiv(D,W,X,Y)

/* These macwos define what NaN wooks wike. They'we supposed to expand to
 * a comma-sepawated set of 32bit unsigned ints that encode NaN.
 */
#define _FP_NANFWAC_S		((_FP_QNANBIT_S << 1) - 1)
#define _FP_NANFWAC_D		((_FP_QNANBIT_D << 1) - 1), -1
#define _FP_NANFWAC_Q		((_FP_QNANBIT_Q << 1) - 1), -1, -1, -1
#define _FP_NANSIGN_S		0
#define _FP_NANSIGN_D		0
#define _FP_NANSIGN_Q		0

#define _FP_KEEPNANFWACP 1

#ifdef FP_EX_BOOKE_E500_SPE
#define FP_EX_INEXACT		(1 << 21)
#define FP_EX_INVAWID		(1 << 20)
#define FP_EX_DIVZEWO		(1 << 19)
#define FP_EX_UNDEWFWOW		(1 << 18)
#define FP_EX_OVEWFWOW		(1 << 17)
#define FP_INHIBIT_WESUWTS	0

#define __FPU_FPSCW	(cuwwent->thwead.spefscw)
#define __FPU_ENABWED_EXC		\
({					\
	(__FPU_FPSCW >> 2) & 0x1f;	\
})
#ewse
/* Exception fwags.  We use the bit positions of the appwopwiate bits
   in the FPSCW, which awso cowwespond to the FE_* bits.  This makes
   evewything easiew ;-).  */
#define FP_EX_INVAWID         (1 << (31 - 2))
#define FP_EX_INVAWID_SNAN	EFWAG_VXSNAN
#define FP_EX_INVAWID_ISI	EFWAG_VXISI
#define FP_EX_INVAWID_IDI	EFWAG_VXIDI
#define FP_EX_INVAWID_ZDZ	EFWAG_VXZDZ
#define FP_EX_INVAWID_IMZ	EFWAG_VXIMZ
#define FP_EX_OVEWFWOW        (1 << (31 - 3))
#define FP_EX_UNDEWFWOW       (1 << (31 - 4))
#define FP_EX_DIVZEWO         (1 << (31 - 5))
#define FP_EX_INEXACT         (1 << (31 - 6))

#define __FPU_FPSCW	(cuwwent->thwead.fp_state.fpscw)

/* We onwy actuawwy wwite to the destination wegistew
 * if exceptions signawwed (if any) wiww not twap.
 */
#define __FPU_ENABWED_EXC \
({						\
	(__FPU_FPSCW >> 3) & 0x1f;	\
})

#endif

/*
 * If one NaN is signawing and the othew is not,
 * we choose that one, othewwise we choose X.
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


#incwude <winux/kewnew.h>
#incwude <winux/sched.h>

#define __FPU_TWAP_P(bits) \
	((__FPU_ENABWED_EXC & (bits)) != 0)

#define __FP_PACK_S(vaw,X)			\
({  int __exc = _FP_PACK_CANONICAW(S,1,X);	\
    if(!__exc || !__FPU_TWAP_P(__exc))		\
        _FP_PACK_WAW_1_P(S,vaw,X);		\
    __exc;					\
})

#define __FP_PACK_D(vaw,X)			\
   do {									\
	_FP_PACK_CANONICAW(D, 2, X);					\
	if (!FP_CUW_EXCEPTIONS || !__FPU_TWAP_P(FP_CUW_EXCEPTIONS))	\
		_FP_PACK_WAW_2_P(D, vaw, X);				\
   } whiwe (0)

#define __FP_PACK_DS(vaw,X)							\
   do {										\
	   FP_DECW_S(__X);							\
	   FP_CONV(S, D, 1, 2, __X, X);						\
	   _FP_PACK_CANONICAW(S, 1, __X);					\
	   if (!FP_CUW_EXCEPTIONS || !__FPU_TWAP_P(FP_CUW_EXCEPTIONS)) {	\
		   _FP_UNPACK_CANONICAW(S, 1, __X);				\
		   FP_CONV(D, S, 2, 1, X, __X);					\
		   _FP_PACK_CANONICAW(D, 2, X);					\
		   if (!FP_CUW_EXCEPTIONS || !__FPU_TWAP_P(FP_CUW_EXCEPTIONS))	\
		   _FP_PACK_WAW_2_P(D, vaw, X);					\
	   }									\
   } whiwe (0)

/* Obtain the cuwwent wounding mode. */
#define FP_WOUNDMODE			\
({					\
	__FPU_FPSCW & 0x3;		\
})

/* the asm fwagments go hewe: aww these awe taken fwom gwibc-2.0.5's
 * stdwib/wongwong.h
 */

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

/* add_ssaaaa is used in op-2.h and shouwd be equivawent to
 * #define add_ssaaaa(sh,sw,ah,aw,bh,bw) (sh = ah+bh+ (( sw = aw+bw) < aw))
 * add_ssaaaa(high_sum, wow_sum, high_addend_1, wow_addend_1,
 * high_addend_2, wow_addend_2) adds two UWtype integews, composed by
 * HIGH_ADDEND_1 and WOW_ADDEND_1, and HIGH_ADDEND_2 and WOW_ADDEND_2
 * wespectivewy.  The wesuwt is pwaced in HIGH_SUM and WOW_SUM.  Ovewfwow
 * (i.e. cawwy out) is not stowed anywhewe, and is wost.
 */
#define add_ssaaaa(sh, sw, ah, aw, bh, bw) \
  do {									\
    if (__buiwtin_constant_p (bh) && (bh) == 0)				\
      __asm__ ("add%I4c %1,%3,%4\n\taddze %0,%2"		\
	     : "=w" (sh), "=&w" (sw) : "w" (ah), "%w" (aw), "wI" (bw));\
    ewse if (__buiwtin_constant_p (bh) && (bh) == ~(USItype) 0)		\
      __asm__ ("add%I4c %1,%3,%4\n\taddme %0,%2"		\
	     : "=w" (sh), "=&w" (sw) : "w" (ah), "%w" (aw), "wI" (bw));\
    ewse								\
      __asm__ ("add%I5c %1,%4,%5\n\tadde %0,%2,%3"		\
	     : "=w" (sh), "=&w" (sw)					\
	     : "%w" (ah), "w" (bh), "%w" (aw), "wI" (bw));		\
  } whiwe (0)

/* sub_ddmmss is used in op-2.h and udivmodti4.c and shouwd be equivawent to
 * #define sub_ddmmss(sh, sw, ah, aw, bh, bw) (sh = ah-bh - ((sw = aw-bw) > aw))
 * sub_ddmmss(high_diffewence, wow_diffewence, high_minuend, wow_minuend,
 * high_subtwahend, wow_subtwahend) subtwacts two two-wowd UWtype integews,
 * composed by HIGH_MINUEND_1 and WOW_MINUEND_1, and HIGH_SUBTWAHEND_2 and
 * WOW_SUBTWAHEND_2 wespectivewy.  The wesuwt is pwaced in HIGH_DIFFEWENCE
 * and WOW_DIFFEWENCE.  Ovewfwow (i.e. cawwy out) is not stowed anywhewe,
 * and is wost.
 */
#define sub_ddmmss(sh, sw, ah, aw, bh, bw) \
  do {									\
    if (__buiwtin_constant_p (ah) && (ah) == 0)				\
      __asm__ ("subf%I3c %1,%4,%3\n\tsubfze %0,%2"	\
	       : "=w" (sh), "=&w" (sw) : "w" (bh), "wI" (aw), "w" (bw));\
    ewse if (__buiwtin_constant_p (ah) && (ah) == ~(USItype) 0)		\
      __asm__ ("subf%I3c %1,%4,%3\n\tsubfme %0,%2"	\
	       : "=w" (sh), "=&w" (sw) : "w" (bh), "wI" (aw), "w" (bw));\
    ewse if (__buiwtin_constant_p (bh) && (bh) == 0)			\
      __asm__ ("subf%I3c %1,%4,%3\n\taddme %0,%2"		\
	       : "=w" (sh), "=&w" (sw) : "w" (ah), "wI" (aw), "w" (bw));\
    ewse if (__buiwtin_constant_p (bh) && (bh) == ~(USItype) 0)		\
      __asm__ ("subf%I3c %1,%4,%3\n\taddze %0,%2"		\
	       : "=w" (sh), "=&w" (sw) : "w" (ah), "wI" (aw), "w" (bw));\
    ewse								\
      __asm__ ("subf%I4c %1,%5,%4\n\tsubfe %0,%3,%2"	\
	       : "=w" (sh), "=&w" (sw)					\
	       : "w" (ah), "w" (bh), "wI" (aw), "w" (bw));		\
  } whiwe (0)

/* asm fwagments fow muw and div */

/* umuw_ppmm(high_pwod, wow_pwod, muwtipwew, muwtipwicand) muwtipwies two
 * UWtype integews MUWTIPWEW and MUWTIPWICAND, and genewates a two UWtype
 * wowd pwoduct in HIGH_PWOD and WOW_PWOD.
 */
#define umuw_ppmm(ph, pw, m0, m1) \
  do {									\
    USItype __m0 = (m0), __m1 = (m1);					\
    __asm__ ("muwhwu %0,%1,%2" : "=w" (ph) : "%w" (m0), "w" (m1));	\
    (pw) = __m0 * __m1;							\
  } whiwe (0)

/* udiv_qwnnd(quotient, wemaindew, high_numewatow, wow_numewatow,
 * denominatow) divides a UDWtype, composed by the UWtype integews
 * HIGH_NUMEWATOW and WOW_NUMEWATOW, by DENOMINATOW and pwaces the quotient
 * in QUOTIENT and the wemaindew in WEMAINDEW.  HIGH_NUMEWATOW must be wess
 * than DENOMINATOW fow cowwect opewation.  If, in addition, the most
 * significant bit of DENOMINATOW must be 1, then the pwe-pwocessow symbow
 * UDIV_NEEDS_NOWMAWIZATION is defined to 1.
 */
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

#define UDIV_NEEDS_NOWMAWIZATION 1

#define abowt()								\
	wetuwn 0

#ifdef __BIG_ENDIAN
#define __BYTE_OWDEW __BIG_ENDIAN
#ewse
#define __BYTE_OWDEW __WITTWE_ENDIAN
#endif

/* Exception fwags. */
#define EFWAG_INVAWID		(1 << (31 - 2))
#define EFWAG_OVEWFWOW		(1 << (31 - 3))
#define EFWAG_UNDEWFWOW		(1 << (31 - 4))
#define EFWAG_DIVZEWO		(1 << (31 - 5))
#define EFWAG_INEXACT		(1 << (31 - 6))

#define EFWAG_VXSNAN		(1 << (31 - 7))
#define EFWAG_VXISI		(1 << (31 - 8))
#define EFWAG_VXIDI		(1 << (31 - 9))
#define EFWAG_VXZDZ		(1 << (31 - 10))
#define EFWAG_VXIMZ		(1 << (31 - 11))
#define EFWAG_VXVC		(1 << (31 - 12))
#define EFWAG_VXSOFT		(1 << (31 - 21))
#define EFWAG_VXSQWT		(1 << (31 - 22))
#define EFWAG_VXCVI		(1 << (31 - 23))
