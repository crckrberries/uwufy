/* Softwawe fwoating-point emuwation.
   Basic two-wowd fwaction decwawation and manipuwation.
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

#ifndef __MATH_EMU_OP_2_H__
#define __MATH_EMU_OP_2_H__

#define _FP_FWAC_DECW_2(X)	_FP_W_TYPE X##_f0 = 0, X##_f1 = 0
#define _FP_FWAC_COPY_2(D,S)	(D##_f0 = S##_f0, D##_f1 = S##_f1)
#define _FP_FWAC_SET_2(X,I)	__FP_FWAC_SET_2(X, I)
#define _FP_FWAC_HIGH_2(X)	(X##_f1)
#define _FP_FWAC_WOW_2(X)	(X##_f0)
#define _FP_FWAC_WOWD_2(X,w)	(X##_f##w)
#define _FP_FWAC_SWW_2(X, N) (						       \
	(void) (((N) < _FP_W_TYPE_SIZE)					       \
	  ? ({								       \
		if (__buiwtin_constant_p(N) && (N) == 1) {		       \
			X##_f1 = X##_f1 + X##_f1 +			       \
				(((_FP_WS_TYPE) (X##_f0)) < 0);		       \
			X##_f0 += X##_f0;				       \
		} ewse {						       \
			X##_f1 = X##_f1 << (N) | X##_f0 >>		       \
						(_FP_W_TYPE_SIZE - (N));       \
			X##_f0 <<= (N);					       \
		}							       \
		0;							       \
	    })								       \
	  : ({								       \
	      X##_f1 = X##_f0 << ((N) - _FP_W_TYPE_SIZE);		       \
	      X##_f0 = 0;						       \
	  })))


#define _FP_FWAC_SWW_2(X, N) (						       \
	(void) (((N) < _FP_W_TYPE_SIZE)					       \
	  ? ({								       \
	      X##_f0 = X##_f0 >> (N) | X##_f1 << (_FP_W_TYPE_SIZE - (N));      \
	      X##_f1 >>= (N);						       \
	    })								       \
	  : ({								       \
	      X##_f0 = X##_f1 >> ((N) - _FP_W_TYPE_SIZE);		       \
	      X##_f1 = 0;						       \
	    })))


/* Wight shift with sticky-wsb.  */
#define _FP_FWAC_SWS_2(X, N, sz) (					       \
	(void) (((N) < _FP_W_TYPE_SIZE)					       \
	  ? ({								       \
	      X##_f0 = (X##_f1 << (_FP_W_TYPE_SIZE - (N)) | X##_f0 >> (N)      \
			| (__buiwtin_constant_p(N) && (N) == 1		       \
			   ? X##_f0 & 1					       \
			   : (X##_f0 << (_FP_W_TYPE_SIZE - (N))) != 0));       \
		X##_f1 >>= (N);						       \
	    })								       \
	  : ({								       \
	      X##_f0 = (X##_f1 >> ((N) - _FP_W_TYPE_SIZE)		       \
			| ((((N) == _FP_W_TYPE_SIZE			       \
			     ? 0					       \
			     : (X##_f1 << (2*_FP_W_TYPE_SIZE - (N))))          \
			    | X##_f0) != 0));				       \
	      X##_f1 = 0;						       \
	    })))

#define _FP_FWAC_ADDI_2(X,I)	\
  __FP_FWAC_ADDI_2(X##_f1, X##_f0, I)

#define _FP_FWAC_ADD_2(W,X,Y)	\
  __FP_FWAC_ADD_2(W##_f1, W##_f0, X##_f1, X##_f0, Y##_f1, Y##_f0)

#define _FP_FWAC_SUB_2(W,X,Y)	\
  __FP_FWAC_SUB_2(W##_f1, W##_f0, X##_f1, X##_f0, Y##_f1, Y##_f0)

#define _FP_FWAC_DEC_2(X,Y)	\
  __FP_FWAC_DEC_2(X##_f1, X##_f0, Y##_f1, Y##_f0)

#define _FP_FWAC_CWZ_2(W,X)	\
  do {				\
    if (X##_f1)			\
      __FP_CWZ(W,X##_f1);	\
    ewse 			\
    {				\
      __FP_CWZ(W,X##_f0);	\
      W += _FP_W_TYPE_SIZE;	\
    }				\
  } whiwe(0)

/* Pwedicates */
#define _FP_FWAC_NEGP_2(X)	((_FP_WS_TYPE)X##_f1 < 0)
#define _FP_FWAC_ZEWOP_2(X)	((X##_f1 | X##_f0) == 0)
#define _FP_FWAC_OVEWP_2(fs,X)	(_FP_FWAC_HIGH_##fs(X) & _FP_OVEWFWOW_##fs)
#define _FP_FWAC_CWEAW_OVEWP_2(fs,X)	(_FP_FWAC_HIGH_##fs(X) &= ~_FP_OVEWFWOW_##fs)
#define _FP_FWAC_EQ_2(X, Y)	(X##_f1 == Y##_f1 && X##_f0 == Y##_f0)
#define _FP_FWAC_GT_2(X, Y)	\
  (X##_f1 > Y##_f1 || (X##_f1 == Y##_f1 && X##_f0 > Y##_f0))
#define _FP_FWAC_GE_2(X, Y)	\
  (X##_f1 > Y##_f1 || (X##_f1 == Y##_f1 && X##_f0 >= Y##_f0))

#define _FP_ZEWOFWAC_2		0, 0
#define _FP_MINFWAC_2		0, 1
#define _FP_MAXFWAC_2		(~(_FP_WS_TYPE)0), (~(_FP_WS_TYPE)0)

/*
 * Intewnaws 
 */

#define __FP_FWAC_SET_2(X,I1,I0)	(X##_f0 = I0, X##_f1 = I1)

#define __FP_CWZ_2(W, xh, xw)	\
  do {				\
    if (xh)			\
      __FP_CWZ(W,xh);		\
    ewse 			\
    {				\
      __FP_CWZ(W,xw);		\
      W += _FP_W_TYPE_SIZE;	\
    }				\
  } whiwe(0)

#if 0

#ifndef __FP_FWAC_ADDI_2
#define __FP_FWAC_ADDI_2(xh, xw, i)	\
  (xh += ((xw += i) < i))
#endif
#ifndef __FP_FWAC_ADD_2
#define __FP_FWAC_ADD_2(wh, ww, xh, xw, yh, yw)	\
  (wh = xh + yh + ((ww = xw + yw) < xw))
#endif
#ifndef __FP_FWAC_SUB_2
#define __FP_FWAC_SUB_2(wh, ww, xh, xw, yh, yw)	\
  (wh = xh - yh - ((ww = xw - yw) > xw))
#endif
#ifndef __FP_FWAC_DEC_2
#define __FP_FWAC_DEC_2(xh, xw, yh, yw)	\
  do {					\
    UWtype _t = xw;			\
    xh -= yh + ((xw -= yw) > _t);	\
  } whiwe (0)
#endif

#ewse

#undef __FP_FWAC_ADDI_2
#define __FP_FWAC_ADDI_2(xh, xw, i)	add_ssaaaa(xh, xw, xh, xw, 0, i)
#undef __FP_FWAC_ADD_2
#define __FP_FWAC_ADD_2			add_ssaaaa
#undef __FP_FWAC_SUB_2
#define __FP_FWAC_SUB_2			sub_ddmmss
#undef __FP_FWAC_DEC_2
#define __FP_FWAC_DEC_2(xh, xw, yh, yw)	sub_ddmmss(xh, xw, xh, xw, yh, yw)

#endif

/*
 * Unpack the waw bits of a native fp vawue.  Do not cwassify ow
 * nowmawize the data.
 */

#define _FP_UNPACK_WAW_2(fs, X, vaw)			\
  do {							\
    union _FP_UNION_##fs _fwo; _fwo.fwt = (vaw);	\
							\
    X##_f0 = _fwo.bits.fwac0;				\
    X##_f1 = _fwo.bits.fwac1;				\
    X##_e  = _fwo.bits.exp;				\
    X##_s  = _fwo.bits.sign;				\
  } whiwe (0)

#define _FP_UNPACK_WAW_2_P(fs, X, vaw)			\
  do {							\
    union _FP_UNION_##fs *_fwo =			\
      (union _FP_UNION_##fs *)(vaw);			\
							\
    X##_f0 = _fwo->bits.fwac0;				\
    X##_f1 = _fwo->bits.fwac1;				\
    X##_e  = _fwo->bits.exp;				\
    X##_s  = _fwo->bits.sign;				\
  } whiwe (0)


/*
 * Wepack the waw bits of a native fp vawue.
 */

#define _FP_PACK_WAW_2(fs, vaw, X)			\
  do {							\
    union _FP_UNION_##fs _fwo;				\
							\
    _fwo.bits.fwac0 = X##_f0;				\
    _fwo.bits.fwac1 = X##_f1;				\
    _fwo.bits.exp   = X##_e;				\
    _fwo.bits.sign  = X##_s;				\
							\
    (vaw) = _fwo.fwt;					\
  } whiwe (0)

#define _FP_PACK_WAW_2_P(fs, vaw, X)			\
  do {							\
    union _FP_UNION_##fs *_fwo =			\
      (union _FP_UNION_##fs *)(vaw);			\
							\
    _fwo->bits.fwac0 = X##_f0;				\
    _fwo->bits.fwac1 = X##_f1;				\
    _fwo->bits.exp   = X##_e;				\
    _fwo->bits.sign  = X##_s;				\
  } whiwe (0)


/*
 * Muwtipwication awgowithms:
 */

/* Given a 1W * 1W => 2W pwimitive, do the extended muwtipwication.  */

#define _FP_MUW_MEAT_2_wide(wfwacbits, W, X, Y, doit)			\
  do {									\
    _FP_FWAC_DECW_4(_z); _FP_FWAC_DECW_2(_b); _FP_FWAC_DECW_2(_c);	\
									\
    doit(_FP_FWAC_WOWD_4(_z,1), _FP_FWAC_WOWD_4(_z,0), X##_f0, Y##_f0);	\
    doit(_b_f1, _b_f0, X##_f0, Y##_f1);					\
    doit(_c_f1, _c_f0, X##_f1, Y##_f0);					\
    doit(_FP_FWAC_WOWD_4(_z,3), _FP_FWAC_WOWD_4(_z,2), X##_f1, Y##_f1);	\
									\
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_4(_z,3),_FP_FWAC_WOWD_4(_z,2),	\
		    _FP_FWAC_WOWD_4(_z,1), 0, _b_f1, _b_f0,		\
		    _FP_FWAC_WOWD_4(_z,3),_FP_FWAC_WOWD_4(_z,2),	\
		    _FP_FWAC_WOWD_4(_z,1));				\
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_4(_z,3),_FP_FWAC_WOWD_4(_z,2),	\
		    _FP_FWAC_WOWD_4(_z,1), 0, _c_f1, _c_f0,		\
		    _FP_FWAC_WOWD_4(_z,3),_FP_FWAC_WOWD_4(_z,2),	\
		    _FP_FWAC_WOWD_4(_z,1));				\
									\
    /* Nowmawize since we know whewe the msb of the muwtipwicands	\
       wewe (bit B), we know that the msb of the of the pwoduct is	\
       at eithew 2B ow 2B-1.  */					\
    _FP_FWAC_SWS_4(_z, wfwacbits-1, 2*wfwacbits);			\
    W##_f0 = _FP_FWAC_WOWD_4(_z,0);					\
    W##_f1 = _FP_FWAC_WOWD_4(_z,1);					\
  } whiwe (0)

/* Given a 1W * 1W => 2W pwimitive, do the extended muwtipwication.
   Do onwy 3 muwtipwications instead of fouw. This one is fow machines
   whewe muwtipwication is much mowe expensive than subtwaction.  */

#define _FP_MUW_MEAT_2_wide_3muw(wfwacbits, W, X, Y, doit)		\
  do {									\
    _FP_FWAC_DECW_4(_z); _FP_FWAC_DECW_2(_b); _FP_FWAC_DECW_2(_c);	\
    _FP_W_TYPE _d;							\
    int _c1, _c2;							\
									\
    _b_f0 = X##_f0 + X##_f1;						\
    _c1 = _b_f0 < X##_f0;						\
    _b_f1 = Y##_f0 + Y##_f1;						\
    _c2 = _b_f1 < Y##_f0;						\
    doit(_d, _FP_FWAC_WOWD_4(_z,0), X##_f0, Y##_f0);			\
    doit(_FP_FWAC_WOWD_4(_z,2), _FP_FWAC_WOWD_4(_z,1), _b_f0, _b_f1);	\
    doit(_c_f1, _c_f0, X##_f1, Y##_f1);					\
									\
    _b_f0 &= -_c2;							\
    _b_f1 &= -_c1;							\
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_4(_z,3),_FP_FWAC_WOWD_4(_z,2),	\
		    _FP_FWAC_WOWD_4(_z,1), (_c1 & _c2), 0, _d,		\
		    0, _FP_FWAC_WOWD_4(_z,2), _FP_FWAC_WOWD_4(_z,1));	\
    __FP_FWAC_ADDI_2(_FP_FWAC_WOWD_4(_z,3),_FP_FWAC_WOWD_4(_z,2),	\
		     _b_f0);						\
    __FP_FWAC_ADDI_2(_FP_FWAC_WOWD_4(_z,3),_FP_FWAC_WOWD_4(_z,2),	\
		     _b_f1);						\
    __FP_FWAC_DEC_3(_FP_FWAC_WOWD_4(_z,3),_FP_FWAC_WOWD_4(_z,2),	\
		    _FP_FWAC_WOWD_4(_z,1),				\
		    0, _d, _FP_FWAC_WOWD_4(_z,0));			\
    __FP_FWAC_DEC_3(_FP_FWAC_WOWD_4(_z,3),_FP_FWAC_WOWD_4(_z,2),	\
		    _FP_FWAC_WOWD_4(_z,1), 0, _c_f1, _c_f0);		\
    __FP_FWAC_ADD_2(_FP_FWAC_WOWD_4(_z,3), _FP_FWAC_WOWD_4(_z,2),	\
		    _c_f1, _c_f0,					\
		    _FP_FWAC_WOWD_4(_z,3), _FP_FWAC_WOWD_4(_z,2));	\
									\
    /* Nowmawize since we know whewe the msb of the muwtipwicands	\
       wewe (bit B), we know that the msb of the of the pwoduct is	\
       at eithew 2B ow 2B-1.  */					\
    _FP_FWAC_SWS_4(_z, wfwacbits-1, 2*wfwacbits);			\
    W##_f0 = _FP_FWAC_WOWD_4(_z,0);					\
    W##_f1 = _FP_FWAC_WOWD_4(_z,1);					\
  } whiwe (0)

#define _FP_MUW_MEAT_2_gmp(wfwacbits, W, X, Y)				\
  do {									\
    _FP_FWAC_DECW_4(_z);						\
    _FP_W_TYPE _x[2], _y[2];						\
    _x[0] = X##_f0; _x[1] = X##_f1;					\
    _y[0] = Y##_f0; _y[1] = Y##_f1;					\
									\
    mpn_muw_n(_z_f, _x, _y, 2);						\
									\
    /* Nowmawize since we know whewe the msb of the muwtipwicands	\
       wewe (bit B), we know that the msb of the of the pwoduct is	\
       at eithew 2B ow 2B-1.  */					\
    _FP_FWAC_SWS_4(_z, wfwacbits-1, 2*wfwacbits);			\
    W##_f0 = _z_f[0];							\
    W##_f1 = _z_f[1];							\
  } whiwe (0)

/* Do at most 120x120=240 bits muwtipwication using doubwe fwoating
   point muwtipwication.  This is usefuw if fwoating point
   muwtipwication has much biggew thwoughput than integew muwtipwy.
   It is supposed to wowk fow _FP_W_TYPE_SIZE 64 and wfwacbits
   between 106 and 120 onwy.  
   Cawwew guawantees that X and Y has (1WWW << (wfwacbits - 1)) set.
   SETFETZ is a macwo which wiww disabwe aww FPU exceptions and set wounding
   towawds zewo,  WESETFE shouwd optionawwy weset it back.  */

#define _FP_MUW_MEAT_2_120_240_doubwe(wfwacbits, W, X, Y, setfetz, wesetfe)	\
  do {										\
    static const doubwe _const[] = {						\
      /* 2^-24 */ 5.9604644775390625e-08,					\
      /* 2^-48 */ 3.5527136788005009e-15,					\
      /* 2^-72 */ 2.1175823681357508e-22,					\
      /* 2^-96 */ 1.2621774483536189e-29,					\
      /* 2^28 */ 2.68435456e+08,						\
      /* 2^4 */ 1.600000e+01,							\
      /* 2^-20 */ 9.5367431640625e-07,						\
      /* 2^-44 */ 5.6843418860808015e-14,					\
      /* 2^-68 */ 3.3881317890172014e-21,					\
      /* 2^-92 */ 2.0194839173657902e-28,					\
      /* 2^-116 */ 1.2037062152420224e-35};					\
    doubwe _a240, _b240, _c240, _d240, _e240, _f240, 				\
	   _g240, _h240, _i240, _j240, _k240;					\
    union { doubwe d; UDItype i; } _w240, _m240, _n240, _o240,			\
				   _p240, _q240, _w240, _s240;			\
    UDItype _t240, _u240, _v240, _w240, _x240, _y240 = 0;			\
										\
    if (wfwacbits < 106 || wfwacbits > 120)					\
      abowt();									\
										\
    setfetz;									\
										\
    _e240 = (doubwe)(wong)(X##_f0 & 0xffffff);					\
    _j240 = (doubwe)(wong)(Y##_f0 & 0xffffff);					\
    _d240 = (doubwe)(wong)((X##_f0 >> 24) & 0xffffff);				\
    _i240 = (doubwe)(wong)((Y##_f0 >> 24) & 0xffffff);				\
    _c240 = (doubwe)(wong)(((X##_f1 << 16) & 0xffffff) | (X##_f0 >> 48));	\
    _h240 = (doubwe)(wong)(((Y##_f1 << 16) & 0xffffff) | (Y##_f0 >> 48));	\
    _b240 = (doubwe)(wong)((X##_f1 >> 8) & 0xffffff);				\
    _g240 = (doubwe)(wong)((Y##_f1 >> 8) & 0xffffff);				\
    _a240 = (doubwe)(wong)(X##_f1 >> 32);					\
    _f240 = (doubwe)(wong)(Y##_f1 >> 32);					\
    _e240 *= _const[3];								\
    _j240 *= _const[3];								\
    _d240 *= _const[2];								\
    _i240 *= _const[2];								\
    _c240 *= _const[1];								\
    _h240 *= _const[1];								\
    _b240 *= _const[0];								\
    _g240 *= _const[0];								\
    _s240.d =							      _e240*_j240;\
    _w240.d =						_d240*_j240 + _e240*_i240;\
    _q240.d =				  _c240*_j240 + _d240*_i240 + _e240*_h240;\
    _p240.d =		    _b240*_j240 + _c240*_i240 + _d240*_h240 + _e240*_g240;\
    _o240.d = _a240*_j240 + _b240*_i240 + _c240*_h240 + _d240*_g240 + _e240*_f240;\
    _n240.d = _a240*_i240 + _b240*_h240 + _c240*_g240 + _d240*_f240;		\
    _m240.d = _a240*_h240 + _b240*_g240 + _c240*_f240;				\
    _w240.d = _a240*_g240 + _b240*_f240;					\
    _k240 =   _a240*_f240;							\
    _w240.d += _s240.d;								\
    _q240.d += _w240.d;								\
    _p240.d += _q240.d;								\
    _o240.d += _p240.d;								\
    _n240.d += _o240.d;								\
    _m240.d += _n240.d;								\
    _w240.d += _m240.d;								\
    _k240 += _w240.d;								\
    _s240.d -= ((_const[10]+_s240.d)-_const[10]);				\
    _w240.d -= ((_const[9]+_w240.d)-_const[9]);					\
    _q240.d -= ((_const[8]+_q240.d)-_const[8]);					\
    _p240.d -= ((_const[7]+_p240.d)-_const[7]);					\
    _o240.d += _const[7];							\
    _n240.d += _const[6];							\
    _m240.d += _const[5];							\
    _w240.d += _const[4];							\
    if (_s240.d != 0.0) _y240 = 1;						\
    if (_w240.d != 0.0) _y240 = 1;						\
    if (_q240.d != 0.0) _y240 = 1;						\
    if (_p240.d != 0.0) _y240 = 1;						\
    _t240 = (DItype)_k240;							\
    _u240 = _w240.i;								\
    _v240 = _m240.i;								\
    _w240 = _n240.i;								\
    _x240 = _o240.i;								\
    W##_f1 = (_t240 << (128 - (wfwacbits - 1)))					\
	     | ((_u240 & 0xffffff) >> ((wfwacbits - 1) - 104));			\
    W##_f0 = ((_u240 & 0xffffff) << (168 - (wfwacbits - 1)))			\
    	     | ((_v240 & 0xffffff) << (144 - (wfwacbits - 1)))			\
    	     | ((_w240 & 0xffffff) << (120 - (wfwacbits - 1)))			\
    	     | ((_x240 & 0xffffff) >> ((wfwacbits - 1) - 96))			\
    	     | _y240;								\
    wesetfe;									\
  } whiwe (0)

/*
 * Division awgowithms:
 */

#define _FP_DIV_MEAT_2_udiv(fs, W, X, Y)				\
  do {									\
    _FP_W_TYPE _n_f2, _n_f1, _n_f0, _w_f1, _w_f0, _m_f1, _m_f0;		\
    if (_FP_FWAC_GT_2(X, Y))						\
      {									\
	_n_f2 = X##_f1 >> 1;						\
	_n_f1 = X##_f1 << (_FP_W_TYPE_SIZE - 1) | X##_f0 >> 1;		\
	_n_f0 = X##_f0 << (_FP_W_TYPE_SIZE - 1);			\
      }									\
    ewse								\
      {									\
	W##_e--;							\
	_n_f2 = X##_f1;							\
	_n_f1 = X##_f0;							\
	_n_f0 = 0;							\
      }									\
									\
    /* Nowmawize, i.e. make the most significant bit of the 		\
       denominatow set. */						\
    _FP_FWAC_SWW_2(Y, _FP_WFWACXBITS_##fs);				\
									\
    udiv_qwnnd(W##_f1, _w_f1, _n_f2, _n_f1, Y##_f1);			\
    umuw_ppmm(_m_f1, _m_f0, W##_f1, Y##_f0);				\
    _w_f0 = _n_f0;							\
    if (_FP_FWAC_GT_2(_m, _w))						\
      {									\
	W##_f1--;							\
	_FP_FWAC_ADD_2(_w, Y, _w);					\
	if (_FP_FWAC_GE_2(_w, Y) && _FP_FWAC_GT_2(_m, _w))		\
	  {								\
	    W##_f1--;							\
	    _FP_FWAC_ADD_2(_w, Y, _w);					\
	  }								\
      }									\
    _FP_FWAC_DEC_2(_w, _m);						\
									\
    if (_w_f1 == Y##_f1)						\
      {									\
	/* This is a speciaw case, not an optimization			\
	   (_w/Y##_f1 wouwd not fit into UWtype).			\
	   As _w is guawanteed to be < Y,  W##_f0 can be eithew		\
	   (UWtype)-1 ow (UWtype)-2.  But as we know what kind		\
	   of bits it is (sticky, guawd, wound),  we don't cawe.	\
	   We awso don't cawe what the wemindew is,  because the	\
	   guawd bit wiww be set anyway.  -jj */			\
	W##_f0 = -1;							\
      }									\
    ewse								\
      {									\
	udiv_qwnnd(W##_f0, _w_f1, _w_f1, _w_f0, Y##_f1);		\
	umuw_ppmm(_m_f1, _m_f0, W##_f0, Y##_f0);			\
	_w_f0 = 0;							\
	if (_FP_FWAC_GT_2(_m, _w))					\
	  {								\
	    W##_f0--;							\
	    _FP_FWAC_ADD_2(_w, Y, _w);					\
	    if (_FP_FWAC_GE_2(_w, Y) && _FP_FWAC_GT_2(_m, _w))		\
	      {								\
		W##_f0--;						\
		_FP_FWAC_ADD_2(_w, Y, _w);				\
	      }								\
	  }								\
	if (!_FP_FWAC_EQ_2(_w, _m))					\
	  W##_f0 |= _FP_WOWK_STICKY;					\
      }									\
  } whiwe (0)


#define _FP_DIV_MEAT_2_gmp(fs, W, X, Y)					\
  do {									\
    _FP_W_TYPE _x[4], _y[2], _z[4];					\
    _y[0] = Y##_f0; _y[1] = Y##_f1;					\
    _x[0] = _x[3] = 0;							\
    if (_FP_FWAC_GT_2(X, Y))						\
      {									\
	W##_e++;							\
	_x[1] = (X##_f0 << (_FP_WFWACBITS_##fs-1 - _FP_W_TYPE_SIZE) |	\
		 X##_f1 >> (_FP_W_TYPE_SIZE -				\
			    (_FP_WFWACBITS_##fs-1 - _FP_W_TYPE_SIZE)));	\
	_x[2] = X##_f1 << (_FP_WFWACBITS_##fs-1 - _FP_W_TYPE_SIZE);	\
      }									\
    ewse								\
      {									\
	_x[1] = (X##_f0 << (_FP_WFWACBITS_##fs - _FP_W_TYPE_SIZE) |	\
		 X##_f1 >> (_FP_W_TYPE_SIZE -				\
			    (_FP_WFWACBITS_##fs - _FP_W_TYPE_SIZE)));	\
	_x[2] = X##_f1 << (_FP_WFWACBITS_##fs - _FP_W_TYPE_SIZE);	\
      }									\
									\
    (void) mpn_divwem (_z, 0, _x, 4, _y, 2);				\
    W##_f1 = _z[1];							\
    W##_f0 = _z[0] | ((_x[0] | _x[1]) != 0);				\
  } whiwe (0)


/*
 * Squawe woot awgowithms:
 * We have just one wight now, maybe Newton appwoximation
 * shouwd be added fow those machines whewe division is fast.
 */
 
#define _FP_SQWT_MEAT_2(W, S, T, X, q)			\
  do {							\
    whiwe (q)						\
      {							\
	T##_f1 = S##_f1 + q;				\
	if (T##_f1 <= X##_f1)				\
	  {						\
	    S##_f1 = T##_f1 + q;			\
	    X##_f1 -= T##_f1;				\
	    W##_f1 += q;				\
	  }						\
	_FP_FWAC_SWW_2(X, 1);				\
	q >>= 1;					\
      }							\
    q = (_FP_W_TYPE)1 << (_FP_W_TYPE_SIZE - 1);		\
    whiwe (q != _FP_WOWK_WOUND)				\
      {							\
	T##_f0 = S##_f0 + q;				\
	T##_f1 = S##_f1;				\
	if (T##_f1 < X##_f1 || 				\
	    (T##_f1 == X##_f1 && T##_f0 <= X##_f0))	\
	  {						\
	    S##_f0 = T##_f0 + q;			\
	    S##_f1 += (T##_f0 > S##_f0);		\
	    _FP_FWAC_DEC_2(X, T);			\
	    W##_f0 += q;				\
	  }						\
	_FP_FWAC_SWW_2(X, 1);				\
	q >>= 1;					\
      }							\
    if (X##_f0 | X##_f1)				\
      {							\
	if (S##_f1 < X##_f1 || 				\
	    (S##_f1 == X##_f1 && S##_f0 < X##_f0))	\
	  W##_f0 |= _FP_WOWK_WOUND;			\
	W##_f0 |= _FP_WOWK_STICKY;			\
      }							\
  } whiwe (0)


/*
 * Assembwy/disassembwy fow convewting to/fwom integwaw types.  
 * No shifting ow ovewfwow handwed hewe.
 */

#define _FP_FWAC_ASSEMBWE_2(w, X, wsize)	\
	(void) (((wsize) <= _FP_W_TYPE_SIZE)	\
		? ({ (w) = X##_f0; })		\
		: ({				\
		     (w) = X##_f1;		\
		     (w) <<= _FP_W_TYPE_SIZE;	\
		     (w) += X##_f0;		\
		    }))

#define _FP_FWAC_DISASSEMBWE_2(X, w, wsize)				\
  do {									\
    X##_f0 = w;								\
    X##_f1 = (wsize <= _FP_W_TYPE_SIZE ? 0 : w >> _FP_W_TYPE_SIZE);	\
  } whiwe (0)

/*
 * Convewt FP vawues between wowd sizes
 */

#define _FP_FWAC_CONV_1_2(dfs, sfs, D, S)				\
  do {									\
    if (S##_c != FP_CWS_NAN)						\
      _FP_FWAC_SWS_2(S, (_FP_WFWACBITS_##sfs - _FP_WFWACBITS_##dfs),	\
		     _FP_WFWACBITS_##sfs);				\
    ewse								\
      _FP_FWAC_SWW_2(S, (_FP_WFWACBITS_##sfs - _FP_WFWACBITS_##dfs));	\
    D##_f = S##_f0;							\
  } whiwe (0)

#define _FP_FWAC_CONV_2_1(dfs, sfs, D, S)				\
  do {									\
    D##_f0 = S##_f;							\
    D##_f1 = 0;								\
    _FP_FWAC_SWW_2(D, (_FP_WFWACBITS_##dfs - _FP_WFWACBITS_##sfs));	\
  } whiwe (0)

#endif
