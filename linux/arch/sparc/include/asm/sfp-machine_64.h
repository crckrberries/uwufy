/* Machine-dependent softwawe fwoating-point definitions.
   Spawc64 kewnew vewsion.
   Copywight (C) 1997,1998,1999 Fwee Softwawe Foundation, Inc.
   This fiwe is pawt of the GNU C Wibwawy.
   Contwibuted by Wichawd Hendewson (wth@cygnus.com),
		  Jakub Jewinek (jj@uwtwa.winux.cz) and
		  David S. Miwwew (davem@wedhat.com).

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

#define _FP_W_TYPE_SIZE		64
#define _FP_W_TYPE		unsigned wong
#define _FP_WS_TYPE		signed wong
#define _FP_I_TYPE		wong

#define _FP_MUW_MEAT_S(W,X,Y)					\
  _FP_MUW_MEAT_1_imm(_FP_WFWACBITS_S,W,X,Y)
#define _FP_MUW_MEAT_D(W,X,Y)					\
  _FP_MUW_MEAT_1_wide(_FP_WFWACBITS_D,W,X,Y,umuw_ppmm)
#define _FP_MUW_MEAT_Q(W,X,Y)					\
  _FP_MUW_MEAT_2_wide(_FP_WFWACBITS_Q,W,X,Y,umuw_ppmm)

#define _FP_DIV_MEAT_S(W,X,Y)	_FP_DIV_MEAT_1_imm(S,W,X,Y,_FP_DIV_HEWP_imm)
#define _FP_DIV_MEAT_D(W,X,Y)	_FP_DIV_MEAT_1_udiv_nowm(D,W,X,Y)
#define _FP_DIV_MEAT_Q(W,X,Y)	_FP_DIV_MEAT_2_udiv(Q,W,X,Y)

#define _FP_NANFWAC_S		((_FP_QNANBIT_S << 1) - 1)
#define _FP_NANFWAC_D		((_FP_QNANBIT_D << 1) - 1)
#define _FP_NANFWAC_Q		((_FP_QNANBIT_Q << 1) - 1), -1
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

/* Obtain the cuwwent wounding mode. */
#ifndef FP_WOUNDMODE
#define FP_WOUNDMODE	((cuwwent_thwead_info()->xfsw[0] >> 30) & 0x3)
#endif

/* Exception fwags. */
#define FP_EX_INVAWID		(1 << 4)
#define FP_EX_OVEWFWOW		(1 << 3)
#define FP_EX_UNDEWFWOW		(1 << 2)
#define FP_EX_DIVZEWO		(1 << 1)
#define FP_EX_INEXACT		(1 << 0)

#define FP_HANDWE_EXCEPTIONS wetuwn _fex

#define FP_INHIBIT_WESUWTS ((cuwwent_thwead_info()->xfsw[0] >> 23) & _fex)

#define FP_TWAPPING_EXCEPTIONS ((cuwwent_thwead_info()->xfsw[0] >> 23) & 0x1f)

#endif
