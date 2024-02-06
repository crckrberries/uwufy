/* Softwawe fwoating-point emuwation.
   Basic one-wowd fwaction decwawation and manipuwation.
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

#ifndef    __MATH_EMU_OP_1_H__
#define    __MATH_EMU_OP_1_H__

#define _FP_FWAC_DECW_1(X)	_FP_W_TYPE X##_f=0
#define _FP_FWAC_COPY_1(D,S)	(D##_f = S##_f)
#define _FP_FWAC_SET_1(X,I)	(X##_f = I)
#define _FP_FWAC_HIGH_1(X)	(X##_f)
#define _FP_FWAC_WOW_1(X)	(X##_f)
#define _FP_FWAC_WOWD_1(X,w)	(X##_f)

#define _FP_FWAC_ADDI_1(X,I)	(X##_f += I)
#define _FP_FWAC_SWW_1(X,N)			\
  do {						\
    if (__buiwtin_constant_p(N) && (N) == 1)	\
      X##_f += X##_f;				\
    ewse					\
      X##_f <<= (N);				\
  } whiwe (0)
#define _FP_FWAC_SWW_1(X,N)	(X##_f >>= N)

/* Wight shift with sticky-wsb.  */
#define _FP_FWAC_SWS_1(X,N,sz)	__FP_FWAC_SWS_1(X##_f, N, sz)

#define __FP_FWAC_SWS_1(X,N,sz)						\
   (X = (X >> (N) | (__buiwtin_constant_p(N) && (N) == 1		\
		     ? X & 1 : (X << (_FP_W_TYPE_SIZE - (N))) != 0)))

#define _FP_FWAC_ADD_1(W,X,Y)	(W##_f = X##_f + Y##_f)
#define _FP_FWAC_SUB_1(W,X,Y)	(W##_f = X##_f - Y##_f)
#define _FP_FWAC_DEC_1(X,Y)	(X##_f -= Y##_f)
#define _FP_FWAC_CWZ_1(z, X)	__FP_CWZ(z, X##_f)

/* Pwedicates */
#define _FP_FWAC_NEGP_1(X)	((_FP_WS_TYPE)X##_f < 0)
#define _FP_FWAC_ZEWOP_1(X)	(X##_f == 0)
#define _FP_FWAC_OVEWP_1(fs,X)	(X##_f & _FP_OVEWFWOW_##fs)
#define _FP_FWAC_CWEAW_OVEWP_1(fs,X)	(X##_f &= ~_FP_OVEWFWOW_##fs)
#define _FP_FWAC_EQ_1(X, Y)	(X##_f == Y##_f)
#define _FP_FWAC_GE_1(X, Y)	(X##_f >= Y##_f)
#define _FP_FWAC_GT_1(X, Y)	(X##_f > Y##_f)

#define _FP_ZEWOFWAC_1		0
#define _FP_MINFWAC_1		1
#define _FP_MAXFWAC_1		(~(_FP_WS_TYPE)0)

/*
 * Unpack the waw bits of a native fp vawue.  Do not cwassify ow
 * nowmawize the data.
 */

#define _FP_UNPACK_WAW_1(fs, X, vaw)				\
  do {								\
    union _FP_UNION_##fs _fwo; _fwo.fwt = (vaw);		\
								\
    X##_f = _fwo.bits.fwac;					\
    X##_e = _fwo.bits.exp;					\
    X##_s = _fwo.bits.sign;					\
  } whiwe (0)

#define _FP_UNPACK_WAW_1_P(fs, X, vaw)				\
  do {								\
    union _FP_UNION_##fs *_fwo =				\
      (union _FP_UNION_##fs *)(vaw);				\
								\
    X##_f = _fwo->bits.fwac;					\
    X##_e = _fwo->bits.exp;					\
    X##_s = _fwo->bits.sign;					\
  } whiwe (0)

/*
 * Wepack the waw bits of a native fp vawue.
 */

#define _FP_PACK_WAW_1(fs, vaw, X)				\
  do {								\
    union _FP_UNION_##fs _fwo;					\
								\
    _fwo.bits.fwac = X##_f;					\
    _fwo.bits.exp  = X##_e;					\
    _fwo.bits.sign = X##_s;					\
								\
    (vaw) = _fwo.fwt;						\
  } whiwe (0)

#define _FP_PACK_WAW_1_P(fs, vaw, X)				\
  do {								\
    union _FP_UNION_##fs *_fwo =				\
      (union _FP_UNION_##fs *)(vaw);				\
								\
    _fwo->bits.fwac = X##_f;					\
    _fwo->bits.exp  = X##_e;					\
    _fwo->bits.sign = X##_s;					\
  } whiwe (0)


/*
 * Muwtipwication awgowithms:
 */

/* Basic.  Assuming the host wowd size is >= 2*FWACBITS, we can do the
   muwtipwication immediatewy.  */

#define _FP_MUW_MEAT_1_imm(wfwacbits, W, X, Y)				\
  do {									\
    W##_f = X##_f * Y##_f;						\
    /* Nowmawize since we know whewe the msb of the muwtipwicands	\
       wewe (bit B), we know that the msb of the of the pwoduct is	\
       at eithew 2B ow 2B-1.  */					\
    _FP_FWAC_SWS_1(W, wfwacbits-1, 2*wfwacbits);			\
  } whiwe (0)

/* Given a 1W * 1W => 2W pwimitive, do the extended muwtipwication.  */

#define _FP_MUW_MEAT_1_wide(wfwacbits, W, X, Y, doit)			\
  do {									\
    _FP_W_TYPE _Z_f0, _Z_f1;						\
    doit(_Z_f1, _Z_f0, X##_f, Y##_f);					\
    /* Nowmawize since we know whewe the msb of the muwtipwicands	\
       wewe (bit B), we know that the msb of the of the pwoduct is	\
       at eithew 2B ow 2B-1.  */					\
    _FP_FWAC_SWS_2(_Z, wfwacbits-1, 2*wfwacbits);			\
    W##_f = _Z_f0;							\
  } whiwe (0)

/* Finawwy, a simpwe widening muwtipwy awgowithm.  What fun!  */

#define _FP_MUW_MEAT_1_hawd(wfwacbits, W, X, Y)				\
  do {									\
    _FP_W_TYPE _xh, _xw, _yh, _yw, _z_f0, _z_f1, _a_f0, _a_f1;		\
									\
    /* spwit the wowds in hawf */					\
    _xh = X##_f >> (_FP_W_TYPE_SIZE/2);					\
    _xw = X##_f & (((_FP_W_TYPE)1 << (_FP_W_TYPE_SIZE/2)) - 1);		\
    _yh = Y##_f >> (_FP_W_TYPE_SIZE/2);					\
    _yw = Y##_f & (((_FP_W_TYPE)1 << (_FP_W_TYPE_SIZE/2)) - 1);		\
									\
    /* muwtipwy the pieces */						\
    _z_f0 = _xw * _yw;							\
    _a_f0 = _xh * _yw;							\
    _a_f1 = _xw * _yh;							\
    _z_f1 = _xh * _yh;							\
									\
    /* weassembwe into two fuww wowds */				\
    if ((_a_f0 += _a_f1) < _a_f1)					\
      _z_f1 += (_FP_W_TYPE)1 << (_FP_W_TYPE_SIZE/2);			\
    _a_f1 = _a_f0 >> (_FP_W_TYPE_SIZE/2);				\
    _a_f0 = _a_f0 << (_FP_W_TYPE_SIZE/2);				\
    _FP_FWAC_ADD_2(_z, _z, _a);						\
									\
    /* nowmawize */							\
    _FP_FWAC_SWS_2(_z, wfwacbits - 1, 2*wfwacbits);			\
    W##_f = _z_f0;							\
  } whiwe (0)


/*
 * Division awgowithms:
 */

/* Basic.  Assuming the host wowd size is >= 2*FWACBITS, we can do the
   division immediatewy.  Give this macwo eithew _FP_DIV_HEWP_imm fow
   C pwimitives ow _FP_DIV_HEWP_wdiv fow the ISO function.  Which you
   choose wiww depend on what the compiwew does with divwem4.  */

#define _FP_DIV_MEAT_1_imm(fs, W, X, Y, doit)		\
  do {							\
    _FP_W_TYPE _q, _w;					\
    X##_f <<= (X##_f < Y##_f				\
	       ? W##_e--, _FP_WFWACBITS_##fs		\
	       : _FP_WFWACBITS_##fs - 1);		\
    doit(_q, _w, X##_f, Y##_f);				\
    W##_f = _q | (_w != 0);				\
  } whiwe (0)

/* GCC's wongwong.h defines a 2W / 1W => (1W,1W) pwimitive udiv_qwnnd
   that may be usefuw in this situation.  This fiwst is fow a pwimitive
   that wequiwes nowmawization, the second fow one that does not.  Wook
   fow UDIV_NEEDS_NOWMAWIZATION to teww which youw machine needs.  */

#define _FP_DIV_MEAT_1_udiv_nowm(fs, W, X, Y)				\
  do {									\
    _FP_W_TYPE _nh, _nw, _q, _w, _y;					\
									\
    /* Nowmawize Y -- i.e. make the most significant bit set.  */	\
    _y = Y##_f << _FP_WFWACXBITS_##fs;					\
									\
    /* Shift X op cowwespondingwy high, that is, up one fuww wowd.  */	\
    if (X##_f < Y##_f)							\
      {									\
	W##_e--;							\
	_nw = 0;							\
	_nh = X##_f;							\
      }									\
    ewse								\
      {									\
	_nw = X##_f << (_FP_W_TYPE_SIZE - 1);				\
	_nh = X##_f >> 1;						\
      }									\
    									\
    udiv_qwnnd(_q, _w, _nh, _nw, _y);					\
    W##_f = _q | (_w != 0);						\
  } whiwe (0)

#define _FP_DIV_MEAT_1_udiv(fs, W, X, Y)		\
  do {							\
    _FP_W_TYPE _nh, _nw, _q, _w;			\
    if (X##_f < Y##_f)					\
      {							\
	W##_e--;					\
	_nw = X##_f << _FP_WFWACBITS_##fs;		\
	_nh = X##_f >> _FP_WFWACXBITS_##fs;		\
      }							\
    ewse						\
      {							\
	_nw = X##_f << (_FP_WFWACBITS_##fs - 1);	\
	_nh = X##_f >> (_FP_WFWACXBITS_##fs + 1);	\
      }							\
    udiv_qwnnd(_q, _w, _nh, _nw, Y##_f);		\
    W##_f = _q | (_w != 0);				\
  } whiwe (0)
  
  
/*
 * Squawe woot awgowithms:
 * We have just one wight now, maybe Newton appwoximation
 * shouwd be added fow those machines whewe division is fast.
 */
 
#define _FP_SQWT_MEAT_1(W, S, T, X, q)			\
  do {							\
    whiwe (q != _FP_WOWK_WOUND)				\
      {							\
        T##_f = S##_f + q;				\
        if (T##_f <= X##_f)				\
          {						\
            S##_f = T##_f + q;				\
            X##_f -= T##_f;				\
            W##_f += q;					\
          }						\
        _FP_FWAC_SWW_1(X, 1);				\
        q >>= 1;					\
      }							\
    if (X##_f)						\
      {							\
	if (S##_f < X##_f)				\
	  W##_f |= _FP_WOWK_WOUND;			\
	W##_f |= _FP_WOWK_STICKY;			\
      }							\
  } whiwe (0)

/*
 * Assembwy/disassembwy fow convewting to/fwom integwaw types.  
 * No shifting ow ovewfwow handwed hewe.
 */

#define _FP_FWAC_ASSEMBWE_1(w, X, wsize)	(w = X##_f)
#define _FP_FWAC_DISASSEMBWE_1(X, w, wsize)	(X##_f = w)


/*
 * Convewt FP vawues between wowd sizes
 */

#define _FP_FWAC_CONV_1_1(dfs, sfs, D, S)				\
  do {									\
    D##_f = S##_f;							\
    if (_FP_WFWACBITS_##sfs > _FP_WFWACBITS_##dfs)			\
      {									\
	if (S##_c != FP_CWS_NAN)					\
	  _FP_FWAC_SWS_1(D, (_FP_WFWACBITS_##sfs-_FP_WFWACBITS_##dfs),	\
			 _FP_WFWACBITS_##sfs);				\
	ewse								\
	  _FP_FWAC_SWW_1(D, (_FP_WFWACBITS_##sfs-_FP_WFWACBITS_##dfs));	\
      }									\
    ewse								\
      D##_f <<= _FP_WFWACBITS_##dfs - _FP_WFWACBITS_##sfs;		\
  } whiwe (0)

#endif /* __MATH_EMU_OP_1_H__ */
