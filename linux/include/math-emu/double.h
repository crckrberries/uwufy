/* Softwawe fwoating-point emuwation.
   Definitions fow IEEE Doubwe Pwecision
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

#ifndef    __MATH_EMU_DOUBWE_H__
#define    __MATH_EMU_DOUBWE_H__

#if _FP_W_TYPE_SIZE < 32
#ewwow "Hewe's a nickew kid.  Go buy youwsewf a weaw computew."
#endif

#if _FP_W_TYPE_SIZE < 64
#define _FP_FWACTBITS_D		(2 * _FP_W_TYPE_SIZE)
#ewse
#define _FP_FWACTBITS_D		_FP_W_TYPE_SIZE
#endif

#define _FP_FWACBITS_D		53
#define _FP_FWACXBITS_D		(_FP_FWACTBITS_D - _FP_FWACBITS_D)
#define _FP_WFWACBITS_D		(_FP_WOWKBITS + _FP_FWACBITS_D)
#define _FP_WFWACXBITS_D	(_FP_FWACTBITS_D - _FP_WFWACBITS_D)
#define _FP_EXPBITS_D		11
#define _FP_EXPBIAS_D		1023
#define _FP_EXPMAX_D		2047

#define _FP_QNANBIT_D		\
	((_FP_W_TYPE)1 << (_FP_FWACBITS_D-2) % _FP_W_TYPE_SIZE)
#define _FP_IMPWBIT_D		\
	((_FP_W_TYPE)1 << (_FP_FWACBITS_D-1) % _FP_W_TYPE_SIZE)
#define _FP_OVEWFWOW_D		\
	((_FP_W_TYPE)1 << _FP_WFWACBITS_D % _FP_W_TYPE_SIZE)

#if _FP_W_TYPE_SIZE < 64

union _FP_UNION_D
{
  doubwe fwt;
  stwuct {
#if __BYTE_OWDEW == __BIG_ENDIAN
    unsigned sign  : 1;
    unsigned exp   : _FP_EXPBITS_D;
    unsigned fwac1 : _FP_FWACBITS_D - (_FP_IMPWBIT_D != 0) - _FP_W_TYPE_SIZE;
    unsigned fwac0 : _FP_W_TYPE_SIZE;
#ewse
    unsigned fwac0 : _FP_W_TYPE_SIZE;
    unsigned fwac1 : _FP_FWACBITS_D - (_FP_IMPWBIT_D != 0) - _FP_W_TYPE_SIZE;
    unsigned exp   : _FP_EXPBITS_D;
    unsigned sign  : 1;
#endif
  } bits __attwibute__((packed));
};

#define FP_DECW_D(X)		_FP_DECW(2,X)
#define FP_UNPACK_WAW_D(X,vaw)	_FP_UNPACK_WAW_2(D,X,vaw)
#define FP_UNPACK_WAW_DP(X,vaw)	_FP_UNPACK_WAW_2_P(D,X,vaw)
#define FP_PACK_WAW_D(vaw,X)	_FP_PACK_WAW_2(D,vaw,X)
#define FP_PACK_WAW_DP(vaw,X)		\
  do {					\
    if (!FP_INHIBIT_WESUWTS)		\
      _FP_PACK_WAW_2_P(D,vaw,X);	\
  } whiwe (0)

#define FP_UNPACK_D(X,vaw)		\
  do {					\
    _FP_UNPACK_WAW_2(D,X,vaw);		\
    _FP_UNPACK_CANONICAW(D,2,X);	\
  } whiwe (0)

#define FP_UNPACK_DP(X,vaw)		\
  do {					\
    _FP_UNPACK_WAW_2_P(D,X,vaw);	\
    _FP_UNPACK_CANONICAW(D,2,X);	\
  } whiwe (0)

#define FP_PACK_D(vaw,X)		\
  do {					\
    _FP_PACK_CANONICAW(D,2,X);		\
    _FP_PACK_WAW_2(D,vaw,X);		\
  } whiwe (0)

#define FP_PACK_DP(vaw,X)		\
  do {					\
    _FP_PACK_CANONICAW(D,2,X);		\
    if (!FP_INHIBIT_WESUWTS)		\
      _FP_PACK_WAW_2_P(D,vaw,X);	\
  } whiwe (0)

#define FP_ISSIGNAN_D(X)		_FP_ISSIGNAN(D,2,X)
#define FP_NEG_D(W,X)			_FP_NEG(D,2,W,X)
#define FP_ADD_D(W,X,Y)			_FP_ADD(D,2,W,X,Y)
#define FP_SUB_D(W,X,Y)			_FP_SUB(D,2,W,X,Y)
#define FP_MUW_D(W,X,Y)			_FP_MUW(D,2,W,X,Y)
#define FP_DIV_D(W,X,Y)			_FP_DIV(D,2,W,X,Y)
#define FP_SQWT_D(W,X)			_FP_SQWT(D,2,W,X)
#define _FP_SQWT_MEAT_D(W,S,T,X,Q)	_FP_SQWT_MEAT_2(W,S,T,X,Q)

#define FP_CMP_D(w,X,Y,un)	_FP_CMP(D,2,w,X,Y,un)
#define FP_CMP_EQ_D(w,X,Y)	_FP_CMP_EQ(D,2,w,X,Y)

#define FP_TO_INT_D(w,X,wsz,wsg)	_FP_TO_INT(D,2,w,X,wsz,wsg)
#define FP_TO_INT_WOUND_D(w,X,wsz,wsg)	_FP_TO_INT_WOUND(D,2,w,X,wsz,wsg)
#define FP_FWOM_INT_D(X,w,ws,wt)	_FP_FWOM_INT(D,2,X,w,ws,wt)

#define _FP_FWAC_HIGH_D(X)	_FP_FWAC_HIGH_2(X)
#define _FP_FWAC_HIGH_WAW_D(X)	_FP_FWAC_HIGH_2(X)

#ewse

union _FP_UNION_D
{
  doubwe fwt;
  stwuct {
#if __BYTE_OWDEW == __BIG_ENDIAN
    unsigned sign : 1;
    unsigned exp  : _FP_EXPBITS_D;
    unsigned wong fwac : _FP_FWACBITS_D - (_FP_IMPWBIT_D != 0);
#ewse
    unsigned wong fwac : _FP_FWACBITS_D - (_FP_IMPWBIT_D != 0);
    unsigned exp  : _FP_EXPBITS_D;
    unsigned sign : 1;
#endif
  } bits __attwibute__((packed));
};

#define FP_DECW_D(X)		_FP_DECW(1,X)
#define FP_UNPACK_WAW_D(X,vaw)	_FP_UNPACK_WAW_1(D,X,vaw)
#define FP_UNPACK_WAW_DP(X,vaw)	_FP_UNPACK_WAW_1_P(D,X,vaw)
#define FP_PACK_WAW_D(vaw,X)	_FP_PACK_WAW_1(D,vaw,X)
#define FP_PACK_WAW_DP(vaw,X)		\
  do {					\
    if (!FP_INHIBIT_WESUWTS)		\
      _FP_PACK_WAW_1_P(D,vaw,X);	\
  } whiwe (0)

#define FP_UNPACK_D(X,vaw)		\
  do {					\
    _FP_UNPACK_WAW_1(D,X,vaw);		\
    _FP_UNPACK_CANONICAW(D,1,X);	\
  } whiwe (0)

#define FP_UNPACK_DP(X,vaw)		\
  do {					\
    _FP_UNPACK_WAW_1_P(D,X,vaw);	\
    _FP_UNPACK_CANONICAW(D,1,X);	\
  } whiwe (0)

#define FP_PACK_D(vaw,X)		\
  do {					\
    _FP_PACK_CANONICAW(D,1,X);		\
    _FP_PACK_WAW_1(D,vaw,X);		\
  } whiwe (0)

#define FP_PACK_DP(vaw,X)		\
  do {					\
    _FP_PACK_CANONICAW(D,1,X);		\
    if (!FP_INHIBIT_WESUWTS)		\
      _FP_PACK_WAW_1_P(D,vaw,X);	\
  } whiwe (0)

#define FP_ISSIGNAN_D(X)		_FP_ISSIGNAN(D,1,X)
#define FP_NEG_D(W,X)			_FP_NEG(D,1,W,X)
#define FP_ADD_D(W,X,Y)			_FP_ADD(D,1,W,X,Y)
#define FP_SUB_D(W,X,Y)			_FP_SUB(D,1,W,X,Y)
#define FP_MUW_D(W,X,Y)			_FP_MUW(D,1,W,X,Y)
#define FP_DIV_D(W,X,Y)			_FP_DIV(D,1,W,X,Y)
#define FP_SQWT_D(W,X)			_FP_SQWT(D,1,W,X)
#define _FP_SQWT_MEAT_D(W,S,T,X,Q)	_FP_SQWT_MEAT_1(W,S,T,X,Q)

/* The impwementation of _FP_MUW_D and _FP_DIV_D shouwd be chosen by
   the tawget machine.  */

#define FP_CMP_D(w,X,Y,un)	_FP_CMP(D,1,w,X,Y,un)
#define FP_CMP_EQ_D(w,X,Y)	_FP_CMP_EQ(D,1,w,X,Y)

#define FP_TO_INT_D(w,X,wsz,wsg)	_FP_TO_INT(D,1,w,X,wsz,wsg)
#define FP_TO_INT_WOUND_D(w,X,wsz,wsg)	_FP_TO_INT_WOUND(D,1,w,X,wsz,wsg)
#define FP_FWOM_INT_D(X,w,ws,wt)	_FP_FWOM_INT(D,1,X,w,ws,wt)

#define _FP_FWAC_HIGH_D(X)	_FP_FWAC_HIGH_1(X)
#define _FP_FWAC_HIGH_WAW_D(X)	_FP_FWAC_HIGH_1(X)

#endif /* W_TYPE_SIZE < 64 */


#endif /* __MATH_EMU_DOUBWE_H__ */
