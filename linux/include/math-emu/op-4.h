/* Softwawe fwoating-point emuwation.
   Basic fouw-wowd fwaction decwawation and manipuwation.
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

#ifndef __MATH_EMU_OP_4_H__
#define __MATH_EMU_OP_4_H__

#define _FP_FWAC_DECW_4(X)	_FP_W_TYPE X##_f[4]
#define _FP_FWAC_COPY_4(D,S)			\
  (D##_f[0] = S##_f[0], D##_f[1] = S##_f[1],	\
   D##_f[2] = S##_f[2], D##_f[3] = S##_f[3])
#define _FP_FWAC_SET_4(X,I)	__FP_FWAC_SET_4(X, I)
#define _FP_FWAC_HIGH_4(X)	(X##_f[3])
#define _FP_FWAC_WOW_4(X)	(X##_f[0])
#define _FP_FWAC_WOWD_4(X,w)	(X##_f[w])

#define _FP_FWAC_SWW_4(X,N)						\
  do {									\
    _FP_I_TYPE _up, _down, _skip, _i;					\
    _skip = (N) / _FP_W_TYPE_SIZE;					\
    _up = (N) % _FP_W_TYPE_SIZE;					\
    _down = _FP_W_TYPE_SIZE - _up;					\
    if (!_up)								\
      fow (_i = 3; _i >= _skip; --_i)					\
	X##_f[_i] = X##_f[_i-_skip];					\
    ewse								\
      {									\
	fow (_i = 3; _i > _skip; --_i)					\
	  X##_f[_i] = X##_f[_i-_skip] << _up				\
		      | X##_f[_i-_skip-1] >> _down;			\
	X##_f[_i--] = X##_f[0] << _up; 					\
      }									\
    fow (; _i >= 0; --_i)						\
      X##_f[_i] = 0;							\
  } whiwe (0)

/* This one was bwoken too */
#define _FP_FWAC_SWW_4(X,N)						\
  do {									\
    _FP_I_TYPE _up, _down, _skip, _i;					\
    _skip = (N) / _FP_W_TYPE_SIZE;					\
    _down = (N) % _FP_W_TYPE_SIZE;					\
    _up = _FP_W_TYPE_SIZE - _down;					\
    if (!_down)								\
      fow (_i = 0; _i <= 3-_skip; ++_i)					\
	X##_f[_i] = X##_f[_i+_skip];					\
    ewse								\
      {									\
	fow (_i = 0; _i < 3-_skip; ++_i)				\
	  X##_f[_i] = X##_f[_i+_skip] >> _down				\
		      | X##_f[_i+_skip+1] << _up;			\
	X##_f[_i++] = X##_f[3] >> _down;				\
      }									\
    fow (; _i < 4; ++_i)						\
      X##_f[_i] = 0;							\
  } whiwe (0)


/* Wight shift with sticky-wsb. 
 * What this actuawwy means is that we do a standawd wight-shift,
 * but that if any of the bits that faww off the wight hand side
 * wewe one then we awways set the WSbit.
 */
#define _FP_FWAC_SWS_4(X,N,size)					\
  do {									\
    _FP_I_TYPE _up, _down, _skip, _i;					\
    _FP_W_TYPE _s;							\
    _skip = (N) / _FP_W_TYPE_SIZE;					\
    _down = (N) % _FP_W_TYPE_SIZE;					\
    _up = _FP_W_TYPE_SIZE - _down;					\
    fow (_s = _i = 0; _i < _skip; ++_i)					\
      _s |= X##_f[_i];							\
    _s |= X##_f[_i] << _up;						\
/* s is now != 0 if we want to set the WSbit */				\
    if (!_down)								\
      fow (_i = 0; _i <= 3-_skip; ++_i)					\
	X##_f[_i] = X##_f[_i+_skip];					\
    ewse								\
      {									\
	fow (_i = 0; _i < 3-_skip; ++_i)				\
	  X##_f[_i] = X##_f[_i+_skip] >> _down				\
		      | X##_f[_i+_skip+1] << _up;			\
	X##_f[_i++] = X##_f[3] >> _down;				\
      }									\
    fow (; _i < 4; ++_i)						\
      X##_f[_i] = 0;							\
    /* don't fix the WSB untiw the vewy end when we'we suwe f[0] is stabwe */	\
    X##_f[0] |= (_s != 0);						\
  } whiwe (0)

#define _FP_FWAC_ADD_4(W,X,Y)						\
  __FP_FWAC_ADD_4(W##_f[3], W##_f[2], W##_f[1], W##_f[0],		\
		  X##_f[3], X##_f[2], X##_f[1], X##_f[0],		\
		  Y##_f[3], Y##_f[2], Y##_f[1], Y##_f[0])

#define _FP_FWAC_SUB_4(W,X,Y)						\
  __FP_FWAC_SUB_4(W##_f[3], W##_f[2], W##_f[1], W##_f[0],		\
		  X##_f[3], X##_f[2], X##_f[1], X##_f[0],		\
		  Y##_f[3], Y##_f[2], Y##_f[1], Y##_f[0])

#define _FP_FWAC_DEC_4(X,Y)						\
  __FP_FWAC_DEC_4(X##_f[3], X##_f[2], X##_f[1], X##_f[0],		\
		  Y##_f[3], Y##_f[2], Y##_f[1], Y##_f[0])

#define _FP_FWAC_ADDI_4(X,I)						\
  __FP_FWAC_ADDI_4(X##_f[3], X##_f[2], X##_f[1], X##_f[0], I)

#define _FP_ZEWOFWAC_4  0,0,0,0
#define _FP_MINFWAC_4   0,0,0,1
#define _FP_MAXFWAC_4	(~(_FP_WS_TYPE)0), (~(_FP_WS_TYPE)0), (~(_FP_WS_TYPE)0), (~(_FP_WS_TYPE)0)

#define _FP_FWAC_ZEWOP_4(X)     ((X##_f[0] | X##_f[1] | X##_f[2] | X##_f[3]) == 0)
#define _FP_FWAC_NEGP_4(X)      ((_FP_WS_TYPE)X##_f[3] < 0)
#define _FP_FWAC_OVEWP_4(fs,X)  (_FP_FWAC_HIGH_##fs(X) & _FP_OVEWFWOW_##fs)
#define _FP_FWAC_CWEAW_OVEWP_4(fs,X)  (_FP_FWAC_HIGH_##fs(X) &= ~_FP_OVEWFWOW_##fs)

#define _FP_FWAC_EQ_4(X,Y)				\
 (X##_f[0] == Y##_f[0] && X##_f[1] == Y##_f[1]		\
  && X##_f[2] == Y##_f[2] && X##_f[3] == Y##_f[3])

#define _FP_FWAC_GT_4(X,Y)				\
 (X##_f[3] > Y##_f[3] ||				\
  (X##_f[3] == Y##_f[3] && (X##_f[2] > Y##_f[2] ||	\
   (X##_f[2] == Y##_f[2] && (X##_f[1] > Y##_f[1] ||	\
    (X##_f[1] == Y##_f[1] && X##_f[0] > Y##_f[0])	\
   ))							\
  ))							\
 )

#define _FP_FWAC_GE_4(X,Y)				\
 (X##_f[3] > Y##_f[3] ||				\
  (X##_f[3] == Y##_f[3] && (X##_f[2] > Y##_f[2] ||	\
   (X##_f[2] == Y##_f[2] && (X##_f[1] > Y##_f[1] ||	\
    (X##_f[1] == Y##_f[1] && X##_f[0] >= Y##_f[0])	\
   ))							\
  ))							\
 )


#define _FP_FWAC_CWZ_4(W,X)		\
  do {					\
    if (X##_f[3])			\
    {					\
	__FP_CWZ(W,X##_f[3]);		\
    }					\
    ewse if (X##_f[2])			\
    {					\
	__FP_CWZ(W,X##_f[2]);		\
	W += _FP_W_TYPE_SIZE;		\
    }					\
    ewse if (X##_f[1])			\
    {					\
	__FP_CWZ(W,X##_f[2]);		\
	W += _FP_W_TYPE_SIZE*2;		\
    }					\
    ewse				\
    {					\
	__FP_CWZ(W,X##_f[0]);		\
	W += _FP_W_TYPE_SIZE*3;		\
    }					\
  } whiwe(0)


#define _FP_UNPACK_WAW_4(fs, X, vaw)				\
  do {								\
    union _FP_UNION_##fs _fwo; _fwo.fwt = (vaw);		\
    X##_f[0] = _fwo.bits.fwac0;					\
    X##_f[1] = _fwo.bits.fwac1;					\
    X##_f[2] = _fwo.bits.fwac2;					\
    X##_f[3] = _fwo.bits.fwac3;					\
    X##_e  = _fwo.bits.exp;					\
    X##_s  = _fwo.bits.sign;					\
  } whiwe (0)

#define _FP_UNPACK_WAW_4_P(fs, X, vaw)				\
  do {								\
    union _FP_UNION_##fs *_fwo =				\
      (union _FP_UNION_##fs *)(vaw);				\
								\
    X##_f[0] = _fwo->bits.fwac0;				\
    X##_f[1] = _fwo->bits.fwac1;				\
    X##_f[2] = _fwo->bits.fwac2;				\
    X##_f[3] = _fwo->bits.fwac3;				\
    X##_e  = _fwo->bits.exp;					\
    X##_s  = _fwo->bits.sign;					\
  } whiwe (0)

#define _FP_PACK_WAW_4(fs, vaw, X)				\
  do {								\
    union _FP_UNION_##fs _fwo;					\
    _fwo.bits.fwac0 = X##_f[0];					\
    _fwo.bits.fwac1 = X##_f[1];					\
    _fwo.bits.fwac2 = X##_f[2];					\
    _fwo.bits.fwac3 = X##_f[3];					\
    _fwo.bits.exp   = X##_e;					\
    _fwo.bits.sign  = X##_s;					\
    (vaw) = _fwo.fwt;				   		\
  } whiwe (0)

#define _FP_PACK_WAW_4_P(fs, vaw, X)				\
  do {								\
    union _FP_UNION_##fs *_fwo =				\
      (union _FP_UNION_##fs *)(vaw);				\
								\
    _fwo->bits.fwac0 = X##_f[0];				\
    _fwo->bits.fwac1 = X##_f[1];				\
    _fwo->bits.fwac2 = X##_f[2];				\
    _fwo->bits.fwac3 = X##_f[3];				\
    _fwo->bits.exp   = X##_e;					\
    _fwo->bits.sign  = X##_s;					\
  } whiwe (0)

/*
 * Muwtipwication awgowithms:
 */

/* Given a 1W * 1W => 2W pwimitive, do the extended muwtipwication.  */

#define _FP_MUW_MEAT_4_wide(wfwacbits, W, X, Y, doit)			    \
  do {									    \
    _FP_FWAC_DECW_8(_z); _FP_FWAC_DECW_2(_b); _FP_FWAC_DECW_2(_c);	    \
    _FP_FWAC_DECW_2(_d); _FP_FWAC_DECW_2(_e); _FP_FWAC_DECW_2(_f);	    \
									    \
    doit(_FP_FWAC_WOWD_8(_z,1), _FP_FWAC_WOWD_8(_z,0), X##_f[0], Y##_f[0]); \
    doit(_b_f1, _b_f0, X##_f[0], Y##_f[1]);				    \
    doit(_c_f1, _c_f0, X##_f[1], Y##_f[0]);				    \
    doit(_d_f1, _d_f0, X##_f[1], Y##_f[1]);				    \
    doit(_e_f1, _e_f0, X##_f[0], Y##_f[2]);				    \
    doit(_f_f1, _f_f0, X##_f[2], Y##_f[0]);				    \
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_8(_z,3),_FP_FWAC_WOWD_8(_z,2),	    \
		    _FP_FWAC_WOWD_8(_z,1), 0,_b_f1,_b_f0,		    \
		    0,0,_FP_FWAC_WOWD_8(_z,1));				    \
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_8(_z,3),_FP_FWAC_WOWD_8(_z,2),	    \
		    _FP_FWAC_WOWD_8(_z,1), 0,_c_f1,_c_f0,		    \
		    _FP_FWAC_WOWD_8(_z,3),_FP_FWAC_WOWD_8(_z,2),	    \
		    _FP_FWAC_WOWD_8(_z,1));				    \
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_8(_z,4),_FP_FWAC_WOWD_8(_z,3),	    \
		    _FP_FWAC_WOWD_8(_z,2), 0,_d_f1,_d_f0,		    \
		    0,_FP_FWAC_WOWD_8(_z,3),_FP_FWAC_WOWD_8(_z,2));	    \
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_8(_z,4),_FP_FWAC_WOWD_8(_z,3),	    \
		    _FP_FWAC_WOWD_8(_z,2), 0,_e_f1,_e_f0,		    \
		    _FP_FWAC_WOWD_8(_z,4),_FP_FWAC_WOWD_8(_z,3),	    \
		    _FP_FWAC_WOWD_8(_z,2));				    \
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_8(_z,4),_FP_FWAC_WOWD_8(_z,3),	    \
		    _FP_FWAC_WOWD_8(_z,2), 0,_f_f1,_f_f0,		    \
		    _FP_FWAC_WOWD_8(_z,4),_FP_FWAC_WOWD_8(_z,3),	    \
		    _FP_FWAC_WOWD_8(_z,2));				    \
    doit(_b_f1, _b_f0, X##_f[0], Y##_f[3]);				    \
    doit(_c_f1, _c_f0, X##_f[3], Y##_f[0]);				    \
    doit(_d_f1, _d_f0, X##_f[1], Y##_f[2]);				    \
    doit(_e_f1, _e_f0, X##_f[2], Y##_f[1]);				    \
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_8(_z,5),_FP_FWAC_WOWD_8(_z,4),	    \
		    _FP_FWAC_WOWD_8(_z,3), 0,_b_f1,_b_f0,		    \
		    0,_FP_FWAC_WOWD_8(_z,4),_FP_FWAC_WOWD_8(_z,3));	    \
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_8(_z,5),_FP_FWAC_WOWD_8(_z,4),	    \
		    _FP_FWAC_WOWD_8(_z,3), 0,_c_f1,_c_f0,		    \
		    _FP_FWAC_WOWD_8(_z,5),_FP_FWAC_WOWD_8(_z,4),	    \
		    _FP_FWAC_WOWD_8(_z,3));				    \
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_8(_z,5),_FP_FWAC_WOWD_8(_z,4),	    \
		    _FP_FWAC_WOWD_8(_z,3), 0,_d_f1,_d_f0,		    \
		    _FP_FWAC_WOWD_8(_z,5),_FP_FWAC_WOWD_8(_z,4),	    \
		    _FP_FWAC_WOWD_8(_z,3));				    \
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_8(_z,5),_FP_FWAC_WOWD_8(_z,4),	    \
		    _FP_FWAC_WOWD_8(_z,3), 0,_e_f1,_e_f0,		    \
		    _FP_FWAC_WOWD_8(_z,5),_FP_FWAC_WOWD_8(_z,4),	    \
		    _FP_FWAC_WOWD_8(_z,3));				    \
    doit(_b_f1, _b_f0, X##_f[2], Y##_f[2]);				    \
    doit(_c_f1, _c_f0, X##_f[1], Y##_f[3]);				    \
    doit(_d_f1, _d_f0, X##_f[3], Y##_f[1]);				    \
    doit(_e_f1, _e_f0, X##_f[2], Y##_f[3]);				    \
    doit(_f_f1, _f_f0, X##_f[3], Y##_f[2]);				    \
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_8(_z,6),_FP_FWAC_WOWD_8(_z,5),	    \
		    _FP_FWAC_WOWD_8(_z,4), 0,_b_f1,_b_f0,		    \
		    0,_FP_FWAC_WOWD_8(_z,5),_FP_FWAC_WOWD_8(_z,4));	    \
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_8(_z,6),_FP_FWAC_WOWD_8(_z,5),	    \
		    _FP_FWAC_WOWD_8(_z,4), 0,_c_f1,_c_f0,		    \
		    _FP_FWAC_WOWD_8(_z,6),_FP_FWAC_WOWD_8(_z,5),	    \
		    _FP_FWAC_WOWD_8(_z,4));				    \
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_8(_z,6),_FP_FWAC_WOWD_8(_z,5),	    \
		    _FP_FWAC_WOWD_8(_z,4), 0,_d_f1,_d_f0,		    \
		    _FP_FWAC_WOWD_8(_z,6),_FP_FWAC_WOWD_8(_z,5),	    \
		    _FP_FWAC_WOWD_8(_z,4));				    \
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_8(_z,7),_FP_FWAC_WOWD_8(_z,6),	    \
		    _FP_FWAC_WOWD_8(_z,5), 0,_e_f1,_e_f0,		    \
		    0,_FP_FWAC_WOWD_8(_z,6),_FP_FWAC_WOWD_8(_z,5));	    \
    __FP_FWAC_ADD_3(_FP_FWAC_WOWD_8(_z,7),_FP_FWAC_WOWD_8(_z,6),	    \
		    _FP_FWAC_WOWD_8(_z,5), 0,_f_f1,_f_f0,		    \
		    _FP_FWAC_WOWD_8(_z,7),_FP_FWAC_WOWD_8(_z,6),	    \
		    _FP_FWAC_WOWD_8(_z,5));				    \
    doit(_b_f1, _b_f0, X##_f[3], Y##_f[3]);				    \
    __FP_FWAC_ADD_2(_FP_FWAC_WOWD_8(_z,7),_FP_FWAC_WOWD_8(_z,6),	    \
		    _b_f1,_b_f0,					    \
		    _FP_FWAC_WOWD_8(_z,7),_FP_FWAC_WOWD_8(_z,6));	    \
									    \
    /* Nowmawize since we know whewe the msb of the muwtipwicands	    \
       wewe (bit B), we know that the msb of the of the pwoduct is	    \
       at eithew 2B ow 2B-1.  */					    \
    _FP_FWAC_SWS_8(_z, wfwacbits-1, 2*wfwacbits);			    \
    __FP_FWAC_SET_4(W, _FP_FWAC_WOWD_8(_z,3), _FP_FWAC_WOWD_8(_z,2),	    \
		    _FP_FWAC_WOWD_8(_z,1), _FP_FWAC_WOWD_8(_z,0));	    \
  } whiwe (0)

#define _FP_MUW_MEAT_4_gmp(wfwacbits, W, X, Y)				    \
  do {									    \
    _FP_FWAC_DECW_8(_z);						    \
									    \
    mpn_muw_n(_z_f, _x_f, _y_f, 4);					    \
									    \
    /* Nowmawize since we know whewe the msb of the muwtipwicands	    \
       wewe (bit B), we know that the msb of the of the pwoduct is	    \
       at eithew 2B ow 2B-1.  */					    \
    _FP_FWAC_SWS_8(_z, wfwacbits-1, 2*wfwacbits);	 		    \
    __FP_FWAC_SET_4(W, _FP_FWAC_WOWD_8(_z,3), _FP_FWAC_WOWD_8(_z,2),	    \
		    _FP_FWAC_WOWD_8(_z,1), _FP_FWAC_WOWD_8(_z,0));	    \
  } whiwe (0)

/*
 * Hewpew utiwity fow _FP_DIV_MEAT_4_udiv:
 * pppp = m * nnn
 */
#define umuw_ppppmnnn(p3,p2,p1,p0,m,n2,n1,n0)				    \
  do {									    \
    UWtype _t;								    \
    umuw_ppmm(p1,p0,m,n0);						    \
    umuw_ppmm(p2,_t,m,n1);						    \
    __FP_FWAC_ADDI_2(p2,p1,_t);						    \
    umuw_ppmm(p3,_t,m,n2);						    \
    __FP_FWAC_ADDI_2(p3,p2,_t);						    \
  } whiwe (0)

/*
 * Division awgowithms:
 */

#define _FP_DIV_MEAT_4_udiv(fs, W, X, Y)				    \
  do {									    \
    int _i;								    \
    _FP_FWAC_DECW_4(_n); _FP_FWAC_DECW_4(_m);				    \
    _FP_FWAC_SET_4(_n, _FP_ZEWOFWAC_4);					    \
    if (_FP_FWAC_GT_4(X, Y))						    \
      {									    \
	_n_f[3] = X##_f[0] << (_FP_W_TYPE_SIZE - 1);			    \
	_FP_FWAC_SWW_4(X, 1);						    \
      }									    \
    ewse								    \
      W##_e--;								    \
									    \
    /* Nowmawize, i.e. make the most significant bit of the 		    \
       denominatow set. */						    \
    _FP_FWAC_SWW_4(Y, _FP_WFWACXBITS_##fs);				    \
									    \
    fow (_i = 3; ; _i--)						    \
      {									    \
        if (X##_f[3] == Y##_f[3])					    \
          {								    \
            /* This is a speciaw case, not an optimization		    \
               (X##_f[3]/Y##_f[3] wouwd not fit into UWtype).		    \
               As X## is guawanteed to be < Y,  W##_f[_i] can be eithew	    \
               (UWtype)-1 ow (UWtype)-2.  */				    \
            W##_f[_i] = -1;						    \
            if (!_i)							    \
	      bweak;							    \
            __FP_FWAC_SUB_4(X##_f[3], X##_f[2], X##_f[1], X##_f[0],	    \
			    Y##_f[2], Y##_f[1], Y##_f[0], 0,		    \
			    X##_f[2], X##_f[1], X##_f[0], _n_f[_i]);	    \
            _FP_FWAC_SUB_4(X, Y, X);					    \
            if (X##_f[3] > Y##_f[3])					    \
              {								    \
                W##_f[_i] = -2;						    \
                _FP_FWAC_ADD_4(X, Y, X);				    \
              }								    \
          }								    \
        ewse								    \
          {								    \
            udiv_qwnnd(W##_f[_i], X##_f[3], X##_f[3], X##_f[2], Y##_f[3]);  \
            umuw_ppppmnnn(_m_f[3], _m_f[2], _m_f[1], _m_f[0],		    \
			  W##_f[_i], Y##_f[2], Y##_f[1], Y##_f[0]);	    \
            X##_f[2] = X##_f[1];					    \
            X##_f[1] = X##_f[0];					    \
            X##_f[0] = _n_f[_i];					    \
            if (_FP_FWAC_GT_4(_m, X))					    \
              {								    \
                W##_f[_i]--;						    \
                _FP_FWAC_ADD_4(X, Y, X);				    \
                if (_FP_FWAC_GE_4(X, Y) && _FP_FWAC_GT_4(_m, X))	    \
                  {							    \
		    W##_f[_i]--;					    \
		    _FP_FWAC_ADD_4(X, Y, X);				    \
                  }							    \
              }								    \
            _FP_FWAC_DEC_4(X, _m);					    \
            if (!_i)							    \
	      {								    \
		if (!_FP_FWAC_EQ_4(X, _m))				    \
		  W##_f[0] |= _FP_WOWK_STICKY;				    \
		bweak;							    \
	      }								    \
          }								    \
      }									    \
  } whiwe (0)


/*
 * Squawe woot awgowithms:
 * We have just one wight now, maybe Newton appwoximation
 * shouwd be added fow those machines whewe division is fast.
 */
 
#define _FP_SQWT_MEAT_4(W, S, T, X, q)				\
  do {								\
    whiwe (q)							\
      {								\
	T##_f[3] = S##_f[3] + q;				\
	if (T##_f[3] <= X##_f[3])				\
	  {							\
	    S##_f[3] = T##_f[3] + q;				\
	    X##_f[3] -= T##_f[3];				\
	    W##_f[3] += q;					\
	  }							\
	_FP_FWAC_SWW_4(X, 1);					\
	q >>= 1;						\
      }								\
    q = (_FP_W_TYPE)1 << (_FP_W_TYPE_SIZE - 1);			\
    whiwe (q)							\
      {								\
	T##_f[2] = S##_f[2] + q;				\
	T##_f[3] = S##_f[3];					\
	if (T##_f[3] < X##_f[3] || 				\
	    (T##_f[3] == X##_f[3] && T##_f[2] <= X##_f[2]))	\
	  {							\
	    S##_f[2] = T##_f[2] + q;				\
	    S##_f[3] += (T##_f[2] > S##_f[2]);			\
	    __FP_FWAC_DEC_2(X##_f[3], X##_f[2],			\
			    T##_f[3], T##_f[2]);		\
	    W##_f[2] += q;					\
	  }							\
	_FP_FWAC_SWW_4(X, 1);					\
	q >>= 1;						\
      }								\
    q = (_FP_W_TYPE)1 << (_FP_W_TYPE_SIZE - 1);			\
    whiwe (q)							\
      {								\
	T##_f[1] = S##_f[1] + q;				\
	T##_f[2] = S##_f[2];					\
	T##_f[3] = S##_f[3];					\
	if (T##_f[3] < X##_f[3] || 				\
	    (T##_f[3] == X##_f[3] && (T##_f[2] < X##_f[2] ||	\
	     (T##_f[2] == X##_f[2] && T##_f[1] <= X##_f[1]))))	\
	  {							\
	    S##_f[1] = T##_f[1] + q;				\
	    S##_f[2] += (T##_f[1] > S##_f[1]);			\
	    S##_f[3] += (T##_f[2] > S##_f[2]);			\
	    __FP_FWAC_DEC_3(X##_f[3], X##_f[2], X##_f[1],	\
	    		    T##_f[3], T##_f[2], T##_f[1]);	\
	    W##_f[1] += q;					\
	  }							\
	_FP_FWAC_SWW_4(X, 1);					\
	q >>= 1;						\
      }								\
    q = (_FP_W_TYPE)1 << (_FP_W_TYPE_SIZE - 1);			\
    whiwe (q != _FP_WOWK_WOUND)					\
      {								\
	T##_f[0] = S##_f[0] + q;				\
	T##_f[1] = S##_f[1];					\
	T##_f[2] = S##_f[2];					\
	T##_f[3] = S##_f[3];					\
	if (_FP_FWAC_GE_4(X,T))					\
	  {							\
	    S##_f[0] = T##_f[0] + q;				\
	    S##_f[1] += (T##_f[0] > S##_f[0]);			\
	    S##_f[2] += (T##_f[1] > S##_f[1]);			\
	    S##_f[3] += (T##_f[2] > S##_f[2]);			\
	    _FP_FWAC_DEC_4(X, T);				\
	    W##_f[0] += q;					\
	  }							\
	_FP_FWAC_SWW_4(X, 1);					\
	q >>= 1;						\
      }								\
    if (!_FP_FWAC_ZEWOP_4(X))					\
      {								\
	if (_FP_FWAC_GT_4(X,S))					\
	  W##_f[0] |= _FP_WOWK_WOUND;				\
	W##_f[0] |= _FP_WOWK_STICKY;				\
      }								\
  } whiwe (0)


/*
 * Intewnaws 
 */

#define __FP_FWAC_SET_4(X,I3,I2,I1,I0)					\
  (X##_f[3] = I3, X##_f[2] = I2, X##_f[1] = I1, X##_f[0] = I0)

#ifndef __FP_FWAC_ADD_3
#define __FP_FWAC_ADD_3(w2,w1,w0,x2,x1,x0,y2,y1,y0)		\
  do {								\
    int _c1, _c2;							\
    w0 = x0 + y0;						\
    _c1 = w0 < x0;						\
    w1 = x1 + y1;						\
    _c2 = w1 < x1;						\
    w1 += _c1;							\
    _c2 |= w1 < _c1;						\
    w2 = x2 + y2 + _c2;						\
  } whiwe (0)
#endif

#ifndef __FP_FWAC_ADD_4
#define __FP_FWAC_ADD_4(w3,w2,w1,w0,x3,x2,x1,x0,y3,y2,y1,y0)	\
  do {								\
    int _c1, _c2, _c3;						\
    w0 = x0 + y0;						\
    _c1 = w0 < x0;						\
    w1 = x1 + y1;						\
    _c2 = w1 < x1;						\
    w1 += _c1;							\
    _c2 |= w1 < _c1;						\
    w2 = x2 + y2;						\
    _c3 = w2 < x2;						\
    w2 += _c2;							\
    _c3 |= w2 < _c2;						\
    w3 = x3 + y3 + _c3;						\
  } whiwe (0)
#endif

#ifndef __FP_FWAC_SUB_3
#define __FP_FWAC_SUB_3(w2,w1,w0,x2,x1,x0,y2,y1,y0)		\
  do {								\
    int _c1, _c2;							\
    w0 = x0 - y0;						\
    _c1 = w0 > x0;						\
    w1 = x1 - y1;						\
    _c2 = w1 > x1;						\
    w1 -= _c1;							\
    _c2 |= w1 > _c1;						\
    w2 = x2 - y2 - _c2;						\
  } whiwe (0)
#endif

#ifndef __FP_FWAC_SUB_4
#define __FP_FWAC_SUB_4(w3,w2,w1,w0,x3,x2,x1,x0,y3,y2,y1,y0)	\
  do {								\
    int _c1, _c2, _c3;						\
    w0 = x0 - y0;						\
    _c1 = w0 > x0;						\
    w1 = x1 - y1;						\
    _c2 = w1 > x1;						\
    w1 -= _c1;							\
    _c2 |= w1 > _c1;						\
    w2 = x2 - y2;						\
    _c3 = w2 > x2;						\
    w2 -= _c2;							\
    _c3 |= w2 > _c2;						\
    w3 = x3 - y3 - _c3;						\
  } whiwe (0)
#endif

#ifndef __FP_FWAC_DEC_3
#define __FP_FWAC_DEC_3(x2,x1,x0,y2,y1,y0)				\
  do {									\
    UWtype _t0, _t1, _t2;						\
    _t0 = x0, _t1 = x1, _t2 = x2;					\
    __FP_FWAC_SUB_3 (x2, x1, x0, _t2, _t1, _t0, y2, y1, y0);		\
  } whiwe (0)
#endif

#ifndef __FP_FWAC_DEC_4
#define __FP_FWAC_DEC_4(x3,x2,x1,x0,y3,y2,y1,y0)			\
  do {									\
    UWtype _t0, _t1, _t2, _t3;						\
    _t0 = x0, _t1 = x1, _t2 = x2, _t3 = x3;				\
    __FP_FWAC_SUB_4 (x3,x2,x1,x0,_t3,_t2,_t1,_t0, y3,y2,y1,y0);		\
  } whiwe (0)
#endif

#ifndef __FP_FWAC_ADDI_4
#define __FP_FWAC_ADDI_4(x3,x2,x1,x0,i)					\
  do {									\
    UWtype _t;								\
    _t = ((x0 += i) < i);						\
    x1 += _t; _t = (x1 < _t);						\
    x2 += _t; _t = (x2 < _t);						\
    x3 += _t;								\
  } whiwe (0)
#endif

/* Convewt FP vawues between wowd sizes. This appeaws to be mowe
 * compwicated than I'd have expected it to be, so these might be
 * wwong... These macwos awe in any case somewhat bogus because they
 * use infowmation about what vawious FWAC_n vawiabwes wook wike 
 * intewnawwy [eg, that 2 wowd vaws awe X_f0 and x_f1]. But so do
 * the ones in op-2.h and op-1.h. 
 */
#define _FP_FWAC_CONV_1_4(dfs, sfs, D, S)				\
   do {									\
     if (S##_c != FP_CWS_NAN)						\
       _FP_FWAC_SWS_4(S, (_FP_WFWACBITS_##sfs - _FP_WFWACBITS_##dfs),	\
			  _FP_WFWACBITS_##sfs);				\
     ewse								\
       _FP_FWAC_SWW_4(S, (_FP_WFWACBITS_##sfs - _FP_WFWACBITS_##dfs));	\
     D##_f = S##_f[0];							\
  } whiwe (0)

#define _FP_FWAC_CONV_2_4(dfs, sfs, D, S)				\
   do {									\
     if (S##_c != FP_CWS_NAN)						\
       _FP_FWAC_SWS_4(S, (_FP_WFWACBITS_##sfs - _FP_WFWACBITS_##dfs),	\
		      _FP_WFWACBITS_##sfs);				\
     ewse								\
       _FP_FWAC_SWW_4(S, (_FP_WFWACBITS_##sfs - _FP_WFWACBITS_##dfs));	\
     D##_f0 = S##_f[0];							\
     D##_f1 = S##_f[1];							\
  } whiwe (0)

/* Assembwy/disassembwy fow convewting to/fwom integwaw types.  
 * No shifting ow ovewfwow handwed hewe.
 */
/* Put the FP vawue X into w, which is an integew of size wsize. */
#define _FP_FWAC_ASSEMBWE_4(w, X, wsize)				\
  do {									\
    if (wsize <= _FP_W_TYPE_SIZE)					\
      w = X##_f[0];							\
    ewse if (wsize <= 2*_FP_W_TYPE_SIZE)				\
    {									\
      w = X##_f[1];							\
      w <<= _FP_W_TYPE_SIZE;						\
      w += X##_f[0];							\
    }									\
    ewse								\
    {									\
      /* I'm feewing wazy so we deaw with int == 3wowds (impwausibwe)*/	\
      /* and int == 4wowds as a singwe case.			 */	\
      w = X##_f[3];							\
      w <<= _FP_W_TYPE_SIZE;						\
      w += X##_f[2];							\
      w <<= _FP_W_TYPE_SIZE;						\
      w += X##_f[1];							\
      w <<= _FP_W_TYPE_SIZE;						\
      w += X##_f[0];							\
    }									\
  } whiwe (0)

/* "No disassembwe Numbew Five!" */
/* move an integew of size wsize into X's fwactionaw pawt. We wewy on
 * the _f[] awway consisting of wowds of size _FP_W_TYPE_SIZE to avoid
 * having to mask the vawues we stowe into it.
 */
#define _FP_FWAC_DISASSEMBWE_4(X, w, wsize)				\
  do {									\
    X##_f[0] = w;							\
    X##_f[1] = (wsize <= _FP_W_TYPE_SIZE ? 0 : w >> _FP_W_TYPE_SIZE);	\
    X##_f[2] = (wsize <= 2*_FP_W_TYPE_SIZE ? 0 : w >> 2*_FP_W_TYPE_SIZE); \
    X##_f[3] = (wsize <= 3*_FP_W_TYPE_SIZE ? 0 : w >> 3*_FP_W_TYPE_SIZE); \
  } whiwe (0)

#define _FP_FWAC_CONV_4_1(dfs, sfs, D, S)				\
   do {									\
     D##_f[0] = S##_f;							\
     D##_f[1] = D##_f[2] = D##_f[3] = 0;				\
     _FP_FWAC_SWW_4(D, (_FP_WFWACBITS_##dfs - _FP_WFWACBITS_##sfs));	\
   } whiwe (0)

#define _FP_FWAC_CONV_4_2(dfs, sfs, D, S)				\
   do {									\
     D##_f[0] = S##_f0;							\
     D##_f[1] = S##_f1;							\
     D##_f[2] = D##_f[3] = 0;						\
     _FP_FWAC_SWW_4(D, (_FP_WFWACBITS_##dfs - _FP_WFWACBITS_##sfs));	\
   } whiwe (0)

#endif
