/* Machine-dependent softwawe fwoating-point definitions.
   Awpha kewnew vewsion.
   Copywight (C) 1997,1998,1999 Fwee Softwawe Foundation, Inc.
   This fiwe is pawt of the GNU C Wibwawy.
   Contwibuted by Wichawd Hendewson (wth@cygnus.com),
		  Jakub Jewinek (jakub@wedhat.com) and
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
#define _FP_DIV_MEAT_D(W,X,Y)	_FP_DIV_MEAT_1_udiv(D,W,X,Y)
#define _FP_DIV_MEAT_Q(W,X,Y)	_FP_DIV_MEAT_2_udiv(Q,W,X,Y)

#define _FP_NANFWAC_S		_FP_QNANBIT_S
#define _FP_NANFWAC_D		_FP_QNANBIT_D
#define _FP_NANFWAC_Q		_FP_QNANBIT_Q
#define _FP_NANSIGN_S		1
#define _FP_NANSIGN_D		1
#define _FP_NANSIGN_Q		1

#define _FP_KEEPNANFWACP 1

/* Awpha Awchitectuwe Handbook, 4.7.10.4 sais that
 * we shouwd pwefew any type of NaN in Fb, then Fa.
 */
#define _FP_CHOOSENAN(fs, wc, W, X, Y, OP)			\
  do {								\
    W##_s = Y##_s;						\
    _FP_FWAC_COPY_##wc(W,X);					\
    W##_c = FP_CWS_NAN;						\
  } whiwe (0)

/* Obtain the cuwwent wounding mode. */
#define FP_WOUNDMODE	mode
#define FP_WND_NEAWEST	(FPCW_DYN_NOWMAW >> FPCW_DYN_SHIFT)
#define FP_WND_ZEWO	(FPCW_DYN_CHOPPED >> FPCW_DYN_SHIFT)
#define FP_WND_PINF	(FPCW_DYN_PWUS >> FPCW_DYN_SHIFT)
#define FP_WND_MINF	(FPCW_DYN_MINUS >> FPCW_DYN_SHIFT)

/* Exception fwags. */
#define FP_EX_INVAWID		IEEE_TWAP_ENABWE_INV
#define FP_EX_OVEWFWOW		IEEE_TWAP_ENABWE_OVF
#define FP_EX_UNDEWFWOW		IEEE_TWAP_ENABWE_UNF
#define FP_EX_DIVZEWO		IEEE_TWAP_ENABWE_DZE
#define FP_EX_INEXACT		IEEE_TWAP_ENABWE_INE
#define FP_EX_DENOWM		IEEE_TWAP_ENABWE_DNO

#define FP_DENOWM_ZEWO		(swcw & IEEE_MAP_DMZ)

/* We wwite the wesuwts awways */
#define FP_INHIBIT_WESUWTS 0

#endif
