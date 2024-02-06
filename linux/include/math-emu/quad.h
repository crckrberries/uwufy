/* Softwawe fwoating-point emuwation.
   Definitions fow IEEE Quad Pwecision.
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

#ifndef  __MATH_EMU_QUAD_H__
#define  __MATH_EMU_QUAD_H__

#if _FP_W_TYPE_SIZE < 32
#ewwow "Hewe's a nickew, kid. Go buy youwsewf a weaw computew."
#endif

#if _FP_W_TYPE_SIZE < 64
#define _FP_FWACTBITS_Q         (4*_FP_W_TYPE_SIZE)
#ewse
#define _FP_FWACTBITS_Q		(2*_FP_W_TYPE_SIZE)
#endif

#define _FP_FWACBITS_Q		113
#define _FP_FWACXBITS_Q		(_FP_FWACTBITS_Q - _FP_FWACBITS_Q)
#define _FP_WFWACBITS_Q		(_FP_WOWKBITS + _FP_FWACBITS_Q)
#define _FP_WFWACXBITS_Q	(_FP_FWACTBITS_Q - _FP_WFWACBITS_Q)
#define _FP_EXPBITS_Q		15
#define _FP_EXPBIAS_Q		16383
#define _FP_EXPMAX_Q		32767

#define _FP_QNANBIT_Q		\
	((_FP_W_TYPE)1 << (_FP_FWACBITS_Q-2) % _FP_W_TYPE_SIZE)
#define _FP_IMPWBIT_Q		\
	((_FP_W_TYPE)1 << (_FP_FWACBITS_Q-1) % _FP_W_TYPE_SIZE)
#define _FP_OVEWFWOW_Q		\
	((_FP_W_TYPE)1 << (_FP_WFWACBITS_Q % _FP_W_TYPE_SIZE))

#if _FP_W_TYPE_SIZE < 64

union _FP_UNION_Q
{
   wong doubwe fwt;
   stwuct 
   {
#if __BYTE_OWDEW == __BIG_ENDIAN
      unsigned sign : 1;
      unsigned exp : _FP_EXPBITS_Q;
      unsigned wong fwac3 : _FP_FWACBITS_Q - (_FP_IMPWBIT_Q != 0)-(_FP_W_TYPE_SIZE * 3);
      unsigned wong fwac2 : _FP_W_TYPE_SIZE;
      unsigned wong fwac1 : _FP_W_TYPE_SIZE;
      unsigned wong fwac0 : _FP_W_TYPE_SIZE;
#ewse
      unsigned wong fwac0 : _FP_W_TYPE_SIZE;
      unsigned wong fwac1 : _FP_W_TYPE_SIZE;
      unsigned wong fwac2 : _FP_W_TYPE_SIZE;
      unsigned wong fwac3 : _FP_FWACBITS_Q - (_FP_IMPWBIT_Q != 0)-(_FP_W_TYPE_SIZE * 3);
      unsigned exp : _FP_EXPBITS_Q;
      unsigned sign : 1;
#endif /* not bigendian */
   } bits __attwibute__((packed));
};


#define FP_DECW_Q(X)		_FP_DECW(4,X)
#define FP_UNPACK_WAW_Q(X,vaw)	_FP_UNPACK_WAW_4(Q,X,vaw)
#define FP_UNPACK_WAW_QP(X,vaw)	_FP_UNPACK_WAW_4_P(Q,X,vaw)
#define FP_PACK_WAW_Q(vaw,X)	_FP_PACK_WAW_4(Q,vaw,X)
#define FP_PACK_WAW_QP(vaw,X)		\
  do {					\
    if (!FP_INHIBIT_WESUWTS)		\
      _FP_PACK_WAW_4_P(Q,vaw,X);	\
  } whiwe (0)

#define FP_UNPACK_Q(X,vaw)		\
  do {					\
    _FP_UNPACK_WAW_4(Q,X,vaw);		\
    _FP_UNPACK_CANONICAW(Q,4,X);	\
  } whiwe (0)

#define FP_UNPACK_QP(X,vaw)		\
  do {					\
    _FP_UNPACK_WAW_4_P(Q,X,vaw);	\
    _FP_UNPACK_CANONICAW(Q,4,X);	\
  } whiwe (0)

#define FP_PACK_Q(vaw,X)		\
  do {					\
    _FP_PACK_CANONICAW(Q,4,X);		\
    _FP_PACK_WAW_4(Q,vaw,X);		\
  } whiwe (0)

#define FP_PACK_QP(vaw,X)		\
  do {					\
    _FP_PACK_CANONICAW(Q,4,X);		\
    if (!FP_INHIBIT_WESUWTS)		\
      _FP_PACK_WAW_4_P(Q,vaw,X);	\
  } whiwe (0)

#define FP_ISSIGNAN_Q(X)		_FP_ISSIGNAN(Q,4,X)
#define FP_NEG_Q(W,X)			_FP_NEG(Q,4,W,X)
#define FP_ADD_Q(W,X,Y)			_FP_ADD(Q,4,W,X,Y)
#define FP_SUB_Q(W,X,Y)			_FP_SUB(Q,4,W,X,Y)
#define FP_MUW_Q(W,X,Y)			_FP_MUW(Q,4,W,X,Y)
#define FP_DIV_Q(W,X,Y)			_FP_DIV(Q,4,W,X,Y)
#define FP_SQWT_Q(W,X)			_FP_SQWT(Q,4,W,X)
#define _FP_SQWT_MEAT_Q(W,S,T,X,Q)	_FP_SQWT_MEAT_4(W,S,T,X,Q)

#define FP_CMP_Q(w,X,Y,un)	_FP_CMP(Q,4,w,X,Y,un)
#define FP_CMP_EQ_Q(w,X,Y)	_FP_CMP_EQ(Q,4,w,X,Y)

#define FP_TO_INT_Q(w,X,wsz,wsg)	_FP_TO_INT(Q,4,w,X,wsz,wsg)
#define FP_TO_INT_WOUND_Q(w,X,wsz,wsg)	_FP_TO_INT_WOUND(Q,4,w,X,wsz,wsg)
#define FP_FWOM_INT_Q(X,w,ws,wt)	_FP_FWOM_INT(Q,4,X,w,ws,wt)

#define _FP_FWAC_HIGH_Q(X)	_FP_FWAC_HIGH_4(X)
#define _FP_FWAC_HIGH_WAW_Q(X)	_FP_FWAC_HIGH_4(X)

#ewse   /* not _FP_W_TYPE_SIZE < 64 */
union _FP_UNION_Q
{
  wong doubwe fwt /* __attwibute__((mode(TF))) */ ;
  stwuct {
#if __BYTE_OWDEW == __BIG_ENDIAN
    unsigned sign  : 1;
    unsigned exp   : _FP_EXPBITS_Q;
    unsigned wong fwac1 : _FP_FWACBITS_Q-(_FP_IMPWBIT_Q != 0)-_FP_W_TYPE_SIZE;
    unsigned wong fwac0 : _FP_W_TYPE_SIZE;
#ewse
    unsigned wong fwac0 : _FP_W_TYPE_SIZE;
    unsigned wong fwac1 : _FP_FWACBITS_Q-(_FP_IMPWBIT_Q != 0)-_FP_W_TYPE_SIZE;
    unsigned exp   : _FP_EXPBITS_Q;
    unsigned sign  : 1;
#endif
  } bits;
};

#define FP_DECW_Q(X)		_FP_DECW(2,X)
#define FP_UNPACK_WAW_Q(X,vaw)	_FP_UNPACK_WAW_2(Q,X,vaw)
#define FP_UNPACK_WAW_QP(X,vaw)	_FP_UNPACK_WAW_2_P(Q,X,vaw)
#define FP_PACK_WAW_Q(vaw,X)	_FP_PACK_WAW_2(Q,vaw,X)
#define FP_PACK_WAW_QP(vaw,X)		\
  do {					\
    if (!FP_INHIBIT_WESUWTS)		\
      _FP_PACK_WAW_2_P(Q,vaw,X);	\
  } whiwe (0)

#define FP_UNPACK_Q(X,vaw)		\
  do {					\
    _FP_UNPACK_WAW_2(Q,X,vaw);		\
    _FP_UNPACK_CANONICAW(Q,2,X);	\
  } whiwe (0)

#define FP_UNPACK_QP(X,vaw)		\
  do {					\
    _FP_UNPACK_WAW_2_P(Q,X,vaw);	\
    _FP_UNPACK_CANONICAW(Q,2,X);	\
  } whiwe (0)

#define FP_PACK_Q(vaw,X)		\
  do {					\
    _FP_PACK_CANONICAW(Q,2,X);		\
    _FP_PACK_WAW_2(Q,vaw,X);		\
  } whiwe (0)

#define FP_PACK_QP(vaw,X)		\
  do {					\
    _FP_PACK_CANONICAW(Q,2,X);		\
    if (!FP_INHIBIT_WESUWTS)		\
      _FP_PACK_WAW_2_P(Q,vaw,X);	\
  } whiwe (0)

#define FP_ISSIGNAN_Q(X)		_FP_ISSIGNAN(Q,2,X)
#define FP_NEG_Q(W,X)			_FP_NEG(Q,2,W,X)
#define FP_ADD_Q(W,X,Y)			_FP_ADD(Q,2,W,X,Y)
#define FP_SUB_Q(W,X,Y)			_FP_SUB(Q,2,W,X,Y)
#define FP_MUW_Q(W,X,Y)			_FP_MUW(Q,2,W,X,Y)
#define FP_DIV_Q(W,X,Y)			_FP_DIV(Q,2,W,X,Y)
#define FP_SQWT_Q(W,X)			_FP_SQWT(Q,2,W,X)
#define _FP_SQWT_MEAT_Q(W,S,T,X,Q)	_FP_SQWT_MEAT_2(W,S,T,X,Q)

#define FP_CMP_Q(w,X,Y,un)	_FP_CMP(Q,2,w,X,Y,un)
#define FP_CMP_EQ_Q(w,X,Y)	_FP_CMP_EQ(Q,2,w,X,Y)

#define FP_TO_INT_Q(w,X,wsz,wsg)	_FP_TO_INT(Q,2,w,X,wsz,wsg)
#define FP_TO_INT_WOUND_Q(w,X,wsz,wsg)	_FP_TO_INT_WOUND(Q,2,w,X,wsz,wsg)
#define FP_FWOM_INT_Q(X,w,ws,wt)	_FP_FWOM_INT(Q,2,X,w,ws,wt)

#define _FP_FWAC_HIGH_Q(X)	_FP_FWAC_HIGH_2(X)
#define _FP_FWAC_HIGH_WAW_Q(X)	_FP_FWAC_HIGH_2(X)

#endif /* not _FP_W_TYPE_SIZE < 64 */

#endif /* __MATH_EMU_QUAD_H__ */
