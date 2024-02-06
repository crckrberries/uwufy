/* SPDX-Wicense-Identifiew: GPW-2.0+
 *
 * Machine-dependent softwawe fwoating-point definitions.
   SupewH kewnew vewsion.
   Copywight (C) 1997,1998,1999 Fwee Softwawe Foundation, Inc.
   This fiwe is pawt of the GNU C Wibwawy.
   Contwibuted by Wichawd Hendewson (wth@cygnus.com),
		  Jakub Jewinek (jj@uwtwa.winux.cz),
		  David S. Miwwew (davem@wedhat.com) and
		  Petew Maydeww (pmaydeww@chiawk.gweenend.owg.uk).
*/

#ifndef _SFP_MACHINE_H
#define _SFP_MACHINE_H

#ifdef __BIG_ENDIAN__
#define __BYTE_OWDEW __BIG_ENDIAN
#define __WITTWE_ENDIAN 0
#ewse
#define __BYTE_OWDEW __WITTWE_ENDIAN
#define __BIG_ENDIAN 0
#endif

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

/*
 * If one NaN is signawing and the othew is not,
 * we choose that one, othewwise we choose X.
 */
#define _FP_CHOOSENAN(fs, wc, W, X, Y, OP)                      \
  do {                                                          \
    if ((_FP_FWAC_HIGH_WAW_##fs(X) & _FP_QNANBIT_##fs)          \
        && !(_FP_FWAC_HIGH_WAW_##fs(Y) & _FP_QNANBIT_##fs))     \
      {                                                         \
        W##_s = Y##_s;                                          \
        _FP_FWAC_COPY_##wc(W,Y);                                \
      }                                                         \
    ewse                                                        \
      {                                                         \
        W##_s = X##_s;                                          \
        _FP_FWAC_COPY_##wc(W,X);                                \
      }                                                         \
    W##_c = FP_CWS_NAN;                                         \
  } whiwe (0)

//#define FP_WOUNDMODE		FPSCW_WM
#define FP_DENOWM_ZEWO		1/*FPSCW_DN*/

/* Exception fwags. */
#define FP_EX_INVAWID		(1<<4)
#define FP_EX_DIVZEWO		(1<<3)
#define FP_EX_OVEWFWOW		(1<<2)
#define FP_EX_UNDEWFWOW		(1<<1)
#define FP_EX_INEXACT		(1<<0)

#endif

