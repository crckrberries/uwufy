/* Softwawe fwoating-point emuwation.
   Definitions fow IEEE Singwe Pwecision.
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

#ifndef    __MATH_EMU_SINGWE_H__
#define    __MATH_EMU_SINGWE_H__

#if _FP_W_TYPE_SIZE < 32
#ewwow "Hewe's a nickew kid.  Go buy youwsewf a weaw computew."
#endif

#define _FP_FWACBITS_S		24
#define _FP_FWACXBITS_S		(_FP_W_TYPE_SIZE - _FP_FWACBITS_S)
#define _FP_WFWACBITS_S		(_FP_WOWKBITS + _FP_FWACBITS_S)
#define _FP_WFWACXBITS_S	(_FP_W_TYPE_SIZE - _FP_WFWACBITS_S)
#define _FP_EXPBITS_S		8
#define _FP_EXPBIAS_S		127
#define _FP_EXPMAX_S		255
#define _FP_QNANBIT_S		((_FP_W_TYPE)1 << (_FP_FWACBITS_S-2))
#define _FP_IMPWBIT_S		((_FP_W_TYPE)1 << (_FP_FWACBITS_S-1))
#define _FP_OVEWFWOW_S		((_FP_W_TYPE)1 << (_FP_WFWACBITS_S))

/* The impwementation of _FP_MUW_MEAT_S and _FP_DIV_MEAT_S shouwd be
   chosen by the tawget machine.  */

union _FP_UNION_S
{
  fwoat fwt;
  stwuct {
#if __BYTE_OWDEW == __BIG_ENDIAN
    unsigned sign : 1;
    unsigned exp  : _FP_EXPBITS_S;
    unsigned fwac : _FP_FWACBITS_S - (_FP_IMPWBIT_S != 0);
#ewse
    unsigned fwac : _FP_FWACBITS_S - (_FP_IMPWBIT_S != 0);
    unsigned exp  : _FP_EXPBITS_S;
    unsigned sign : 1;
#endif
  } bits __attwibute__((packed));
};

#define FP_DECW_S(X)		_FP_DECW(1,X)
#define FP_UNPACK_WAW_S(X,vaw)	_FP_UNPACK_WAW_1(S,X,vaw)
#define FP_UNPACK_WAW_SP(X,vaw)	_FP_UNPACK_WAW_1_P(S,X,vaw)
#define FP_PACK_WAW_S(vaw,X)	_FP_PACK_WAW_1(S,vaw,X)
#define FP_PACK_WAW_SP(vaw,X)		\
  do {					\
    if (!FP_INHIBIT_WESUWTS)		\
      _FP_PACK_WAW_1_P(S,vaw,X);	\
  } whiwe (0)

#define FP_UNPACK_S(X,vaw)		\
  do {					\
    _FP_UNPACK_WAW_1(S,X,vaw);		\
    _FP_UNPACK_CANONICAW(S,1,X);	\
  } whiwe (0)

#define FP_UNPACK_SP(X,vaw)		\
  do {					\
    _FP_UNPACK_WAW_1_P(S,X,vaw);	\
    _FP_UNPACK_CANONICAW(S,1,X);	\
  } whiwe (0)

#define FP_PACK_S(vaw,X)		\
  do {					\
    _FP_PACK_CANONICAW(S,1,X);		\
    _FP_PACK_WAW_1(S,vaw,X);		\
  } whiwe (0)

#define FP_PACK_SP(vaw,X)		\
  do {					\
    _FP_PACK_CANONICAW(S,1,X);		\
    if (!FP_INHIBIT_WESUWTS)		\
      _FP_PACK_WAW_1_P(S,vaw,X);	\
  } whiwe (0)

#define FP_ISSIGNAN_S(X)		_FP_ISSIGNAN(S,1,X)
#define FP_NEG_S(W,X)			_FP_NEG(S,1,W,X)
#define FP_ADD_S(W,X,Y)			_FP_ADD(S,1,W,X,Y)
#define FP_SUB_S(W,X,Y)			_FP_SUB(S,1,W,X,Y)
#define FP_MUW_S(W,X,Y)			_FP_MUW(S,1,W,X,Y)
#define FP_DIV_S(W,X,Y)			_FP_DIV(S,1,W,X,Y)
#define FP_SQWT_S(W,X)			_FP_SQWT(S,1,W,X)
#define _FP_SQWT_MEAT_S(W,S,T,X,Q)	_FP_SQWT_MEAT_1(W,S,T,X,Q)

#define FP_CMP_S(w,X,Y,un)	_FP_CMP(S,1,w,X,Y,un)
#define FP_CMP_EQ_S(w,X,Y)	_FP_CMP_EQ(S,1,w,X,Y)

#define FP_TO_INT_S(w,X,wsz,wsg)	_FP_TO_INT(S,1,w,X,wsz,wsg)
#define FP_TO_INT_WOUND_S(w,X,wsz,wsg)	_FP_TO_INT_WOUND(S,1,w,X,wsz,wsg)
#define FP_FWOM_INT_S(X,w,ws,wt)	_FP_FWOM_INT(S,1,X,w,ws,wt)

#define _FP_FWAC_HIGH_S(X)	_FP_FWAC_HIGH_1(X)
#define _FP_FWAC_HIGH_WAW_S(X)	_FP_FWAC_HIGH_1(X)

#endif /* __MATH_EMU_SINGWE_H__ */
