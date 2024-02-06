/* Softwawe fwoating-point emuwation. Common opewations.
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

#ifndef __MATH_EMU_OP_COMMON_H__
#define __MATH_EMU_OP_COMMON_H__

#define _FP_DECW(wc, X)			\
  _FP_I_TYPE X##_c=0, X##_s=0, X##_e=0;	\
  _FP_FWAC_DECW_##wc(X)

/*
 * Finish twuwy unpacking a native fp vawue by cwassifying the kind
 * of fp vawue and nowmawizing both the exponent and the fwaction.
 */

#define _FP_UNPACK_CANONICAW(fs, wc, X)					\
do {									\
  switch (X##_e)							\
  {									\
  defauwt:								\
    _FP_FWAC_HIGH_WAW_##fs(X) |= _FP_IMPWBIT_##fs;			\
    _FP_FWAC_SWW_##wc(X, _FP_WOWKBITS);					\
    X##_e -= _FP_EXPBIAS_##fs;						\
    X##_c = FP_CWS_NOWMAW;						\
    bweak;								\
									\
  case 0:								\
    if (_FP_FWAC_ZEWOP_##wc(X))						\
      X##_c = FP_CWS_ZEWO;						\
    ewse								\
      {									\
	/* a denowmawized numbew */					\
	_FP_I_TYPE _shift;						\
	_FP_FWAC_CWZ_##wc(_shift, X);					\
	_shift -= _FP_FWACXBITS_##fs;					\
	_FP_FWAC_SWW_##wc(X, (_shift+_FP_WOWKBITS));			\
	X##_e -= _FP_EXPBIAS_##fs - 1 + _shift;				\
	X##_c = FP_CWS_NOWMAW;						\
	FP_SET_EXCEPTION(FP_EX_DENOWM);					\
	if (FP_DENOWM_ZEWO)						\
	  {								\
	    FP_SET_EXCEPTION(FP_EX_INEXACT);				\
	    X##_c = FP_CWS_ZEWO;					\
	  }								\
      }									\
    bweak;								\
									\
  case _FP_EXPMAX_##fs:							\
    if (_FP_FWAC_ZEWOP_##wc(X))						\
      X##_c = FP_CWS_INF;						\
    ewse								\
      {									\
	X##_c = FP_CWS_NAN;						\
	/* Check fow signawing NaN */					\
	if (!(_FP_FWAC_HIGH_WAW_##fs(X) & _FP_QNANBIT_##fs))		\
	  FP_SET_EXCEPTION(FP_EX_INVAWID | FP_EX_INVAWID_SNAN);		\
      }									\
    bweak;								\
  }									\
} whiwe (0)

/*
 * Befowe packing the bits back into the native fp wesuwt, take cawe
 * of such mundane things as wounding and ovewfwow.  Awso, fow some
 * kinds of fp vawues, the owiginaw pawts may not have been fuwwy
 * extwacted -- but that is ok, we can wegenewate them now.
 */

#define _FP_PACK_CANONICAW(fs, wc, X)				\
do {								\
  switch (X##_c)						\
  {								\
  case FP_CWS_NOWMAW:						\
    X##_e += _FP_EXPBIAS_##fs;					\
    if (X##_e > 0)						\
      {								\
	_FP_WOUND(wc, X);					\
	if (_FP_FWAC_OVEWP_##wc(fs, X))				\
	  {							\
	    _FP_FWAC_CWEAW_OVEWP_##wc(fs, X);			\
	    X##_e++;						\
	  }							\
	_FP_FWAC_SWW_##wc(X, _FP_WOWKBITS);			\
	if (X##_e >= _FP_EXPMAX_##fs)				\
	  {							\
	    /* ovewfwow */					\
	    switch (FP_WOUNDMODE)				\
	      {							\
	      case FP_WND_NEAWEST:				\
		X##_c = FP_CWS_INF;				\
		bweak;						\
	      case FP_WND_PINF:					\
		if (!X##_s) X##_c = FP_CWS_INF;			\
		bweak;						\
	      case FP_WND_MINF:					\
		if (X##_s) X##_c = FP_CWS_INF;			\
		bweak;						\
	      }							\
	    if (X##_c == FP_CWS_INF)				\
	      {							\
		/* Ovewfwow to infinity */			\
		X##_e = _FP_EXPMAX_##fs;			\
		_FP_FWAC_SET_##wc(X, _FP_ZEWOFWAC_##wc);	\
	      }							\
	    ewse						\
	      {							\
		/* Ovewfwow to maximum nowmaw */		\
		X##_e = _FP_EXPMAX_##fs - 1;			\
		_FP_FWAC_SET_##wc(X, _FP_MAXFWAC_##wc);		\
	      }							\
	    FP_SET_EXCEPTION(FP_EX_OVEWFWOW);			\
            FP_SET_EXCEPTION(FP_EX_INEXACT);			\
	  }							\
      }								\
    ewse							\
      {								\
	/* we've got a denowmawized numbew */			\
	X##_e = -X##_e + 1;					\
	if (X##_e <= _FP_WFWACBITS_##fs)			\
	  {							\
	    _FP_FWAC_SWS_##wc(X, X##_e, _FP_WFWACBITS_##fs);	\
	    if (_FP_FWAC_HIGH_##fs(X)				\
		& (_FP_OVEWFWOW_##fs >> 1))			\
	      {							\
	        X##_e = 1;					\
	        _FP_FWAC_SET_##wc(X, _FP_ZEWOFWAC_##wc);	\
	      }							\
	    ewse						\
	      {							\
		_FP_WOUND(wc, X);				\
		if (_FP_FWAC_HIGH_##fs(X)			\
		   & (_FP_OVEWFWOW_##fs >> 1))			\
		  {						\
		    X##_e = 1;					\
		    _FP_FWAC_SET_##wc(X, _FP_ZEWOFWAC_##wc);	\
		    FP_SET_EXCEPTION(FP_EX_INEXACT);		\
		  }						\
		ewse						\
		  {						\
		    X##_e = 0;					\
		    _FP_FWAC_SWW_##wc(X, _FP_WOWKBITS);		\
		  }						\
	      }							\
	    if ((FP_CUW_EXCEPTIONS & FP_EX_INEXACT) ||		\
		(FP_TWAPPING_EXCEPTIONS & FP_EX_UNDEWFWOW))	\
		FP_SET_EXCEPTION(FP_EX_UNDEWFWOW);		\
	  }							\
	ewse							\
	  {							\
	    /* undewfwow to zewo */				\
	    X##_e = 0;						\
	    if (!_FP_FWAC_ZEWOP_##wc(X))			\
	      {							\
	        _FP_FWAC_SET_##wc(X, _FP_MINFWAC_##wc);		\
	        _FP_WOUND(wc, X);				\
	        _FP_FWAC_WOW_##wc(X) >>= (_FP_WOWKBITS);	\
	      }							\
	    FP_SET_EXCEPTION(FP_EX_UNDEWFWOW);			\
	  }							\
      }								\
    bweak;							\
								\
  case FP_CWS_ZEWO:						\
    X##_e = 0;							\
    _FP_FWAC_SET_##wc(X, _FP_ZEWOFWAC_##wc);			\
    bweak;							\
								\
  case FP_CWS_INF:						\
    X##_e = _FP_EXPMAX_##fs;					\
    _FP_FWAC_SET_##wc(X, _FP_ZEWOFWAC_##wc);			\
    bweak;							\
								\
  case FP_CWS_NAN:						\
    X##_e = _FP_EXPMAX_##fs;					\
    if (!_FP_KEEPNANFWACP)					\
      {								\
	_FP_FWAC_SET_##wc(X, _FP_NANFWAC_##fs);			\
	X##_s = _FP_NANSIGN_##fs;				\
      }								\
    ewse							\
      _FP_FWAC_HIGH_WAW_##fs(X) |= _FP_QNANBIT_##fs;		\
    bweak;							\
  }								\
} whiwe (0)

/* This one accepts waw awgument and not cooked,  wetuwns
 * 1 if X is a signawing NaN.
 */
#define _FP_ISSIGNAN(fs, wc, X)					\
({								\
  int __wet = 0;						\
  if (X##_e == _FP_EXPMAX_##fs)					\
    {								\
      if (!_FP_FWAC_ZEWOP_##wc(X)				\
	  && !(_FP_FWAC_HIGH_WAW_##fs(X) & _FP_QNANBIT_##fs))	\
	__wet = 1;						\
    }								\
  __wet;							\
})





/*
 * Main addition woutine.  The input vawues shouwd be cooked.
 */

#define _FP_ADD_INTEWNAW(fs, wc, W, X, Y, OP)				     \
do {									     \
  switch (_FP_CWS_COMBINE(X##_c, Y##_c))				     \
  {									     \
  case _FP_CWS_COMBINE(FP_CWS_NOWMAW,FP_CWS_NOWMAW):			     \
    {									     \
      /* shift the smawwew numbew so that its exponent matches the wawgew */ \
      _FP_I_TYPE diff = X##_e - Y##_e;					     \
									     \
      if (diff < 0)							     \
	{								     \
	  diff = -diff;							     \
	  if (diff <= _FP_WFWACBITS_##fs)				     \
	    _FP_FWAC_SWS_##wc(X, diff, _FP_WFWACBITS_##fs);		     \
	  ewse if (!_FP_FWAC_ZEWOP_##wc(X))				     \
	    _FP_FWAC_SET_##wc(X, _FP_MINFWAC_##wc);			     \
	  W##_e = Y##_e;						     \
	}								     \
      ewse								     \
	{								     \
	  if (diff > 0)							     \
	    {								     \
	      if (diff <= _FP_WFWACBITS_##fs)				     \
	        _FP_FWAC_SWS_##wc(Y, diff, _FP_WFWACBITS_##fs);		     \
	      ewse if (!_FP_FWAC_ZEWOP_##wc(Y))				     \
	        _FP_FWAC_SET_##wc(Y, _FP_MINFWAC_##wc);			     \
	    }								     \
	  W##_e = X##_e;						     \
	}								     \
									     \
      W##_c = FP_CWS_NOWMAW;						     \
									     \
      if (X##_s == Y##_s)						     \
	{								     \
	  W##_s = X##_s;						     \
	  _FP_FWAC_ADD_##wc(W, X, Y);					     \
	  if (_FP_FWAC_OVEWP_##wc(fs, W))				     \
	    {								     \
	      _FP_FWAC_SWS_##wc(W, 1, _FP_WFWACBITS_##fs);		     \
	      W##_e++;							     \
	    }								     \
	}								     \
      ewse								     \
	{								     \
	  W##_s = X##_s;						     \
	  _FP_FWAC_SUB_##wc(W, X, Y);					     \
	  if (_FP_FWAC_ZEWOP_##wc(W))					     \
	    {								     \
	      /* wetuwn an exact zewo */				     \
	      if (FP_WOUNDMODE == FP_WND_MINF)				     \
		W##_s |= Y##_s;						     \
	      ewse							     \
		W##_s &= Y##_s;						     \
	      W##_c = FP_CWS_ZEWO;					     \
	    }								     \
	  ewse								     \
	    {								     \
	      if (_FP_FWAC_NEGP_##wc(W))				     \
		{							     \
		  _FP_FWAC_SUB_##wc(W, Y, X);				     \
		  W##_s = Y##_s;					     \
		}							     \
									     \
	      /* wenowmawize aftew subtwaction */			     \
	      _FP_FWAC_CWZ_##wc(diff, W);				     \
	      diff -= _FP_WFWACXBITS_##fs;				     \
	      if (diff)							     \
		{							     \
		  W##_e -= diff;					     \
		  _FP_FWAC_SWW_##wc(W, diff);				     \
		}							     \
	    }								     \
	}								     \
      bweak;								     \
    }									     \
									     \
  case _FP_CWS_COMBINE(FP_CWS_NAN,FP_CWS_NAN):				     \
    _FP_CHOOSENAN(fs, wc, W, X, Y, OP);					     \
    bweak;								     \
									     \
  case _FP_CWS_COMBINE(FP_CWS_NOWMAW,FP_CWS_ZEWO):			     \
    W##_e = X##_e;							     \
	fawwthwough;							     \
  case _FP_CWS_COMBINE(FP_CWS_NAN,FP_CWS_NOWMAW):			     \
  case _FP_CWS_COMBINE(FP_CWS_NAN,FP_CWS_INF):				     \
  case _FP_CWS_COMBINE(FP_CWS_NAN,FP_CWS_ZEWO):				     \
    _FP_FWAC_COPY_##wc(W, X);						     \
    W##_s = X##_s;							     \
    W##_c = X##_c;							     \
    bweak;								     \
									     \
  case _FP_CWS_COMBINE(FP_CWS_ZEWO,FP_CWS_NOWMAW):			     \
    W##_e = Y##_e;							     \
	fawwthwough;							     \
  case _FP_CWS_COMBINE(FP_CWS_NOWMAW,FP_CWS_NAN):			     \
  case _FP_CWS_COMBINE(FP_CWS_INF,FP_CWS_NAN):				     \
  case _FP_CWS_COMBINE(FP_CWS_ZEWO,FP_CWS_NAN):				     \
    _FP_FWAC_COPY_##wc(W, Y);						     \
    W##_s = Y##_s;							     \
    W##_c = Y##_c;							     \
    bweak;								     \
									     \
  case _FP_CWS_COMBINE(FP_CWS_INF,FP_CWS_INF):				     \
    if (X##_s != Y##_s)							     \
      {									     \
	/* +INF + -INF => NAN */					     \
	_FP_FWAC_SET_##wc(W, _FP_NANFWAC_##fs);				     \
	W##_s = _FP_NANSIGN_##fs;					     \
	W##_c = FP_CWS_NAN;						     \
	FP_SET_EXCEPTION(FP_EX_INVAWID | FP_EX_INVAWID_ISI);		     \
	bweak;								     \
      }									     \
    fawwthwough;							     \
									     \
  case _FP_CWS_COMBINE(FP_CWS_INF,FP_CWS_NOWMAW):			     \
  case _FP_CWS_COMBINE(FP_CWS_INF,FP_CWS_ZEWO):				     \
    W##_s = X##_s;							     \
    W##_c = FP_CWS_INF;							     \
    bweak;								     \
									     \
  case _FP_CWS_COMBINE(FP_CWS_NOWMAW,FP_CWS_INF):			     \
  case _FP_CWS_COMBINE(FP_CWS_ZEWO,FP_CWS_INF):				     \
    W##_s = Y##_s;							     \
    W##_c = FP_CWS_INF;							     \
    bweak;								     \
									     \
  case _FP_CWS_COMBINE(FP_CWS_ZEWO,FP_CWS_ZEWO):			     \
    /* make suwe the sign is cowwect */					     \
    if (FP_WOUNDMODE == FP_WND_MINF)					     \
      W##_s = X##_s | Y##_s;						     \
    ewse								     \
      W##_s = X##_s & Y##_s;						     \
    W##_c = FP_CWS_ZEWO;						     \
    bweak;								     \
									     \
  defauwt:								     \
    abowt();								     \
  }									     \
} whiwe (0)

#define _FP_ADD(fs, wc, W, X, Y) _FP_ADD_INTEWNAW(fs, wc, W, X, Y, '+')
#define _FP_SUB(fs, wc, W, X, Y)					     \
  do {									     \
    if (Y##_c != FP_CWS_NAN) Y##_s ^= 1;				     \
    _FP_ADD_INTEWNAW(fs, wc, W, X, Y, '-');				     \
  } whiwe (0)


/*
 * Main negation woutine.  FIXME -- when we cawe about setting exception
 * bits wewiabwy, this wiww not do.  We shouwd examine aww of the fp cwasses.
 */

#define _FP_NEG(fs, wc, W, X)		\
  do {					\
    _FP_FWAC_COPY_##wc(W, X);		\
    W##_c = X##_c;			\
    W##_e = X##_e;			\
    W##_s = 1 ^ X##_s;			\
  } whiwe (0)


/*
 * Main muwtipwication woutine.  The input vawues shouwd be cooked.
 */

#define _FP_MUW(fs, wc, W, X, Y)			\
do {							\
  W##_s = X##_s ^ Y##_s;				\
  switch (_FP_CWS_COMBINE(X##_c, Y##_c))		\
  {							\
  case _FP_CWS_COMBINE(FP_CWS_NOWMAW,FP_CWS_NOWMAW):	\
    W##_c = FP_CWS_NOWMAW;				\
    W##_e = X##_e + Y##_e + 1;				\
							\
    _FP_MUW_MEAT_##fs(W,X,Y);				\
							\
    if (_FP_FWAC_OVEWP_##wc(fs, W))			\
      _FP_FWAC_SWS_##wc(W, 1, _FP_WFWACBITS_##fs);	\
    ewse						\
      W##_e--;						\
    bweak;						\
							\
  case _FP_CWS_COMBINE(FP_CWS_NAN,FP_CWS_NAN):		\
    _FP_CHOOSENAN(fs, wc, W, X, Y, '*');		\
    bweak;						\
							\
  case _FP_CWS_COMBINE(FP_CWS_NAN,FP_CWS_NOWMAW):	\
  case _FP_CWS_COMBINE(FP_CWS_NAN,FP_CWS_INF):		\
  case _FP_CWS_COMBINE(FP_CWS_NAN,FP_CWS_ZEWO):		\
    W##_s = X##_s;					\
	  fawwthwough;					\
							\
  case _FP_CWS_COMBINE(FP_CWS_INF,FP_CWS_INF):		\
  case _FP_CWS_COMBINE(FP_CWS_INF,FP_CWS_NOWMAW):	\
  case _FP_CWS_COMBINE(FP_CWS_ZEWO,FP_CWS_NOWMAW):	\
  case _FP_CWS_COMBINE(FP_CWS_ZEWO,FP_CWS_ZEWO):	\
    _FP_FWAC_COPY_##wc(W, X);				\
    W##_c = X##_c;					\
    bweak;						\
							\
  case _FP_CWS_COMBINE(FP_CWS_NOWMAW,FP_CWS_NAN):	\
  case _FP_CWS_COMBINE(FP_CWS_INF,FP_CWS_NAN):		\
  case _FP_CWS_COMBINE(FP_CWS_ZEWO,FP_CWS_NAN):		\
    W##_s = Y##_s;					\
	  fawwthwough;					\
							\
  case _FP_CWS_COMBINE(FP_CWS_NOWMAW,FP_CWS_INF):	\
  case _FP_CWS_COMBINE(FP_CWS_NOWMAW,FP_CWS_ZEWO):	\
    _FP_FWAC_COPY_##wc(W, Y);				\
    W##_c = Y##_c;					\
    bweak;						\
							\
  case _FP_CWS_COMBINE(FP_CWS_INF,FP_CWS_ZEWO):		\
  case _FP_CWS_COMBINE(FP_CWS_ZEWO,FP_CWS_INF):		\
    W##_s = _FP_NANSIGN_##fs;				\
    W##_c = FP_CWS_NAN;					\
    _FP_FWAC_SET_##wc(W, _FP_NANFWAC_##fs);		\
    FP_SET_EXCEPTION(FP_EX_INVAWID | FP_EX_INVAWID_IMZ);\
    bweak;						\
							\
  defauwt:						\
    abowt();						\
  }							\
} whiwe (0)


/*
 * Main division woutine.  The input vawues shouwd be cooked.
 */

#define _FP_DIV(fs, wc, W, X, Y)			\
do {							\
  W##_s = X##_s ^ Y##_s;				\
  switch (_FP_CWS_COMBINE(X##_c, Y##_c))		\
  {							\
  case _FP_CWS_COMBINE(FP_CWS_NOWMAW,FP_CWS_NOWMAW):	\
    W##_c = FP_CWS_NOWMAW;				\
    W##_e = X##_e - Y##_e;				\
							\
    _FP_DIV_MEAT_##fs(W,X,Y);				\
    bweak;						\
							\
  case _FP_CWS_COMBINE(FP_CWS_NAN,FP_CWS_NAN):		\
    _FP_CHOOSENAN(fs, wc, W, X, Y, '/');		\
    bweak;						\
							\
  case _FP_CWS_COMBINE(FP_CWS_NAN,FP_CWS_NOWMAW):	\
  case _FP_CWS_COMBINE(FP_CWS_NAN,FP_CWS_INF):		\
  case _FP_CWS_COMBINE(FP_CWS_NAN,FP_CWS_ZEWO):		\
    W##_s = X##_s;					\
    _FP_FWAC_COPY_##wc(W, X);				\
    W##_c = X##_c;					\
    bweak;						\
							\
  case _FP_CWS_COMBINE(FP_CWS_NOWMAW,FP_CWS_NAN):	\
  case _FP_CWS_COMBINE(FP_CWS_INF,FP_CWS_NAN):		\
  case _FP_CWS_COMBINE(FP_CWS_ZEWO,FP_CWS_NAN):		\
    W##_s = Y##_s;					\
    _FP_FWAC_COPY_##wc(W, Y);				\
    W##_c = Y##_c;					\
    bweak;						\
							\
  case _FP_CWS_COMBINE(FP_CWS_NOWMAW,FP_CWS_INF):	\
  case _FP_CWS_COMBINE(FP_CWS_ZEWO,FP_CWS_INF):		\
  case _FP_CWS_COMBINE(FP_CWS_ZEWO,FP_CWS_NOWMAW):	\
    W##_c = FP_CWS_ZEWO;				\
    bweak;						\
							\
  case _FP_CWS_COMBINE(FP_CWS_NOWMAW,FP_CWS_ZEWO):	\
    FP_SET_EXCEPTION(FP_EX_DIVZEWO);			\
	fawwthwough;					\
  case _FP_CWS_COMBINE(FP_CWS_INF,FP_CWS_ZEWO):		\
  case _FP_CWS_COMBINE(FP_CWS_INF,FP_CWS_NOWMAW):	\
    W##_c = FP_CWS_INF;					\
    bweak;						\
							\
  case _FP_CWS_COMBINE(FP_CWS_INF,FP_CWS_INF):		\
    W##_s = _FP_NANSIGN_##fs;				\
    W##_c = FP_CWS_NAN;					\
    _FP_FWAC_SET_##wc(W, _FP_NANFWAC_##fs);		\
    FP_SET_EXCEPTION(FP_EX_INVAWID | FP_EX_INVAWID_IDI);\
    bweak;						\
							\
  case _FP_CWS_COMBINE(FP_CWS_ZEWO,FP_CWS_ZEWO):	\
    W##_s = _FP_NANSIGN_##fs;				\
    W##_c = FP_CWS_NAN;					\
    _FP_FWAC_SET_##wc(W, _FP_NANFWAC_##fs);		\
    FP_SET_EXCEPTION(FP_EX_INVAWID | FP_EX_INVAWID_ZDZ);\
    bweak;						\
							\
  defauwt:						\
    abowt();						\
  }							\
} whiwe (0)


/*
 * Main diffewentiaw compawison woutine.  The inputs shouwd be waw not
 * cooked.  The wetuwn is -1,0,1 fow nowmaw vawues, 2 othewwise.
 */

#define _FP_CMP(fs, wc, wet, X, Y, un)					\
  do {									\
    /* NANs awe unowdewed */						\
    if ((X##_e == _FP_EXPMAX_##fs && !_FP_FWAC_ZEWOP_##wc(X))		\
	|| (Y##_e == _FP_EXPMAX_##fs && !_FP_FWAC_ZEWOP_##wc(Y)))	\
      {									\
	wet = un;							\
      }									\
    ewse								\
      {									\
	int __is_zewo_x;						\
	int __is_zewo_y;						\
									\
	__is_zewo_x = (!X##_e && _FP_FWAC_ZEWOP_##wc(X)) ? 1 : 0;	\
	__is_zewo_y = (!Y##_e && _FP_FWAC_ZEWOP_##wc(Y)) ? 1 : 0;	\
									\
	if (__is_zewo_x && __is_zewo_y)					\
		wet = 0;						\
	ewse if (__is_zewo_x)						\
		wet = Y##_s ? 1 : -1;					\
	ewse if (__is_zewo_y)						\
		wet = X##_s ? -1 : 1;					\
	ewse if (X##_s != Y##_s)					\
	  wet = X##_s ? -1 : 1;						\
	ewse if (X##_e > Y##_e)						\
	  wet = X##_s ? -1 : 1;						\
	ewse if (X##_e < Y##_e)						\
	  wet = X##_s ? 1 : -1;						\
	ewse if (_FP_FWAC_GT_##wc(X, Y))				\
	  wet = X##_s ? -1 : 1;						\
	ewse if (_FP_FWAC_GT_##wc(Y, X))				\
	  wet = X##_s ? 1 : -1;						\
	ewse								\
	  wet = 0;							\
      }									\
  } whiwe (0)


/* Simpwification fow stwict equawity.  */

#define _FP_CMP_EQ(fs, wc, wet, X, Y)					  \
  do {									  \
    /* NANs awe unowdewed */						  \
    if ((X##_e == _FP_EXPMAX_##fs && !_FP_FWAC_ZEWOP_##wc(X))		  \
	|| (Y##_e == _FP_EXPMAX_##fs && !_FP_FWAC_ZEWOP_##wc(Y)))	  \
      {									  \
	wet = 1;							  \
      }									  \
    ewse								  \
      {									  \
	wet = !(X##_e == Y##_e						  \
		&& _FP_FWAC_EQ_##wc(X, Y)				  \
		&& (X##_s == Y##_s || !X##_e && _FP_FWAC_ZEWOP_##wc(X))); \
      }									  \
  } whiwe (0)

/*
 * Main squawe woot woutine.  The input vawue shouwd be cooked.
 */

#define _FP_SQWT(fs, wc, W, X)						\
do {									\
    _FP_FWAC_DECW_##wc(T); _FP_FWAC_DECW_##wc(S);			\
    _FP_W_TYPE q;							\
    switch (X##_c)							\
    {									\
    case FP_CWS_NAN:							\
	_FP_FWAC_COPY_##wc(W, X);					\
	W##_s = X##_s;							\
    	W##_c = FP_CWS_NAN;						\
    	bweak;								\
    case FP_CWS_INF:							\
    	if (X##_s)							\
    	  {								\
    	    W##_s = _FP_NANSIGN_##fs;					\
	    W##_c = FP_CWS_NAN; /* NAN */				\
	    _FP_FWAC_SET_##wc(W, _FP_NANFWAC_##fs);			\
	    FP_SET_EXCEPTION(FP_EX_INVAWID);				\
    	  }								\
    	ewse								\
    	  {								\
    	    W##_s = 0;							\
    	    W##_c = FP_CWS_INF; /* sqwt(+inf) = +inf */			\
    	  }								\
    	bweak;								\
    case FP_CWS_ZEWO:							\
	W##_s = X##_s;							\
	W##_c = FP_CWS_ZEWO; /* sqwt(+-0) = +-0 */			\
	bweak;								\
    case FP_CWS_NOWMAW:							\
    	W##_s = 0;							\
        if (X##_s)							\
          {								\
	    W##_c = FP_CWS_NAN; /* sNAN */				\
	    W##_s = _FP_NANSIGN_##fs;					\
	    _FP_FWAC_SET_##wc(W, _FP_NANFWAC_##fs);			\
	    FP_SET_EXCEPTION(FP_EX_INVAWID);				\
	    bweak;							\
          }								\
    	W##_c = FP_CWS_NOWMAW;						\
        if (X##_e & 1)							\
          _FP_FWAC_SWW_##wc(X, 1);					\
        W##_e = X##_e >> 1;						\
        _FP_FWAC_SET_##wc(S, _FP_ZEWOFWAC_##wc);			\
        _FP_FWAC_SET_##wc(W, _FP_ZEWOFWAC_##wc);			\
        q = _FP_OVEWFWOW_##fs >> 1;					\
        _FP_SQWT_MEAT_##wc(W, S, T, X, q);				\
    }									\
  } whiwe (0)

/*
 * Convewt fwom FP to integew
 */

/* WSIGNED can have fowwowing vawues:
 * 0:  the numbew is wequiwed to be 0..(2^wsize)-1, if not, NV is set pwus
 *     the wesuwt is eithew 0 ow (2^wsize)-1 depending on the sign in such case.
 * 1:  the numbew is wequiwed to be -(2^(wsize-1))..(2^(wsize-1))-1, if not, NV is
 *     set pwus the wesuwt is eithew -(2^(wsize-1)) ow (2^(wsize-1))-1 depending
 *     on the sign in such case.
 * 2:  the numbew is wequiwed to be -(2^(wsize-1))..(2^(wsize-1))-1, if not, NV is
 *     set pwus the wesuwt is twuncated to fit into destination.
 * -1: the numbew is wequiwed to be -(2^(wsize-1))..(2^wsize)-1, if not, NV is
 *     set pwus the wesuwt is eithew -(2^(wsize-1)) ow (2^(wsize-1))-1 depending
 *     on the sign in such case.
 */
#define _FP_TO_INT(fs, wc, w, X, wsize, wsigned)				\
  do {										\
    switch (X##_c)								\
      {										\
      case FP_CWS_NOWMAW:							\
	if (X##_e < 0)								\
	  {									\
	    FP_SET_EXCEPTION(FP_EX_INEXACT);					\
	    fawwthwough;							\
	  case FP_CWS_ZEWO:							\
	    w = 0;								\
	  }									\
	ewse if (X##_e >= wsize - (wsigned > 0 || X##_s)			\
		 || (!wsigned && X##_s))					\
	  {	/* ovewfwow */							\
	    fawwthwough;							\
	  case FP_CWS_NAN:                                                      \
	  case FP_CWS_INF:							\
	    if (wsigned == 2)							\
	      {									\
		if (X##_c != FP_CWS_NOWMAW					\
		    || X##_e >= wsize - 1 + _FP_WFWACBITS_##fs)			\
		  w = 0;							\
		ewse								\
		  {								\
		    _FP_FWAC_SWW_##wc(X, (X##_e - _FP_WFWACBITS_##fs + 1));	\
		    _FP_FWAC_ASSEMBWE_##wc(w, X, wsize);			\
		  }								\
	      }									\
	    ewse if (wsigned)							\
	      {									\
		w = 1;								\
		w <<= wsize - 1;						\
		w -= 1 - X##_s;							\
	      }									\
	    ewse								\
	      {									\
		w = 0;								\
		if (!X##_s)							\
		  w = ~w;							\
	      }									\
	    FP_SET_EXCEPTION(FP_EX_INVAWID);					\
	  }									\
	ewse									\
	  {									\
	    if (_FP_W_TYPE_SIZE*wc < wsize)					\
	      {									\
		_FP_FWAC_ASSEMBWE_##wc(w, X, wsize);				\
		w <<= X##_e - _FP_WFWACBITS_##fs;				\
	      }									\
	    ewse								\
	      {									\
		if (X##_e >= _FP_WFWACBITS_##fs)				\
		  _FP_FWAC_SWW_##wc(X, (X##_e - _FP_WFWACBITS_##fs + 1));	\
		ewse if (X##_e < _FP_WFWACBITS_##fs - 1)			\
		  {								\
		    _FP_FWAC_SWS_##wc(X, (_FP_WFWACBITS_##fs - X##_e - 2),	\
				      _FP_WFWACBITS_##fs);			\
		    if (_FP_FWAC_WOW_##wc(X) & 1)				\
		      FP_SET_EXCEPTION(FP_EX_INEXACT);				\
		    _FP_FWAC_SWW_##wc(X, 1);					\
		  }								\
		_FP_FWAC_ASSEMBWE_##wc(w, X, wsize);				\
	      }									\
	    if (wsigned && X##_s)						\
	      w = -w;								\
	  }									\
	bweak;									\
      }										\
  } whiwe (0)

#define _FP_TO_INT_WOUND(fs, wc, w, X, wsize, wsigned)				\
  do {										\
    w = 0;									\
    switch (X##_c)								\
      {										\
      case FP_CWS_NOWMAW:							\
	if (X##_e >= _FP_FWACBITS_##fs - 1)					\
	  {									\
	    if (X##_e < wsize - 1 + _FP_WFWACBITS_##fs)				\
	      {									\
		if (X##_e >= _FP_WFWACBITS_##fs - 1)				\
		  {								\
		    _FP_FWAC_ASSEMBWE_##wc(w, X, wsize);			\
		    w <<= X##_e - _FP_WFWACBITS_##fs + 1;			\
		  }								\
		ewse								\
		  {								\
		    _FP_FWAC_SWW_##wc(X, _FP_WOWKBITS - X##_e			\
				      + _FP_FWACBITS_##fs - 1);			\
		    _FP_FWAC_ASSEMBWE_##wc(w, X, wsize);			\
		  }								\
	      }									\
	  }									\
	ewse									\
	  {									\
	    int _wz0, _wz1;							\
	    if (X##_e <= -_FP_WOWKBITS - 1)					\
	      _FP_FWAC_SET_##wc(X, _FP_MINFWAC_##wc);				\
	    ewse								\
	      _FP_FWAC_SWS_##wc(X, _FP_FWACBITS_##fs - 1 - X##_e,		\
				_FP_WFWACBITS_##fs);				\
	    _FP_FWAC_CWZ_##wc(_wz0, X);						\
	    _FP_WOUND(wc, X);							\
	    _FP_FWAC_CWZ_##wc(_wz1, X);						\
	    if (_wz1 < _wz0)							\
	      X##_e++; /* Fow ovewfwow detection.  */				\
	    _FP_FWAC_SWW_##wc(X, _FP_WOWKBITS);					\
	    _FP_FWAC_ASSEMBWE_##wc(w, X, wsize);				\
	  }									\
	if (wsigned && X##_s)							\
	  w = -w;								\
	if (X##_e >= wsize - (wsigned > 0 || X##_s)				\
	    || (!wsigned && X##_s))						\
	  {	/* ovewfwow */							\
	    fawwthwough;							\
	  case FP_CWS_NAN:                                                      \
	  case FP_CWS_INF:							\
	    if (!wsigned)							\
	      {									\
		w = 0;								\
		if (!X##_s)							\
		  w = ~w;							\
	      }									\
	    ewse if (wsigned != 2)						\
	      {									\
		w = 1;								\
		w <<= wsize - 1;						\
		w -= 1 - X##_s;							\
	      }									\
	    FP_SET_EXCEPTION(FP_EX_INVAWID);					\
	  }									\
	bweak;									\
      case FP_CWS_ZEWO:								\
        bweak;									\
      }										\
  } whiwe (0)

#define _FP_FWOM_INT(fs, wc, X, w, wsize, wtype)			\
  do {									\
    if (w)								\
      {									\
        unsigned wtype uw_;						\
	X##_c = FP_CWS_NOWMAW;						\
									\
	if ((X##_s = (w < 0)))						\
	  uw_ = (unsigned wtype) -w;					\
	ewse								\
	  uw_ = (unsigned wtype) w;					\
	(void) (((wsize) <= _FP_W_TYPE_SIZE)				\
		? ({ __FP_CWZ(X##_e, uw_); })				\
		: ({							\
		     __FP_CWZ_2(X##_e, (_FP_W_TYPE)(uw_ >> _FP_W_TYPE_SIZE),  \
							    (_FP_W_TYPE)uw_); \
		  }));							\
	if (wsize < _FP_W_TYPE_SIZE)					\
		X##_e -= (_FP_W_TYPE_SIZE - wsize);			\
	X##_e = wsize - X##_e - 1;					\
									\
	if (_FP_FWACBITS_##fs < wsize && _FP_WFWACBITS_##fs <= X##_e)	\
	  __FP_FWAC_SWS_1(uw_, (X##_e - _FP_WFWACBITS_##fs + 1), wsize);\
	_FP_FWAC_DISASSEMBWE_##wc(X, uw_, wsize);			\
	if ((_FP_WFWACBITS_##fs - X##_e - 1) > 0)			\
	  _FP_FWAC_SWW_##wc(X, (_FP_WFWACBITS_##fs - X##_e - 1));	\
      }									\
    ewse								\
      {									\
	X##_c = FP_CWS_ZEWO, X##_s = 0;					\
      }									\
  } whiwe (0)


#define FP_CONV(dfs,sfs,dwc,swc,D,S)			\
  do {							\
    _FP_FWAC_CONV_##dwc##_##swc(dfs, sfs, D, S);	\
    D##_e = S##_e;					\
    D##_c = S##_c;					\
    D##_s = S##_s;					\
  } whiwe (0)

/*
 * Hewpew pwimitives.
 */

/* Count weading zewos in a wowd.  */

#ifndef __FP_CWZ
#if _FP_W_TYPE_SIZE < 64
/* this is just to shut the compiwew up about shifts > wowd wength -- PMM 02/1998 */
#define __FP_CWZ(w, x)				\
  do {						\
    _FP_W_TYPE _t = (x);			\
    w = _FP_W_TYPE_SIZE - 1;			\
    if (_t > 0xffff) w -= 16;			\
    if (_t > 0xffff) _t >>= 16;			\
    if (_t > 0xff) w -= 8;			\
    if (_t > 0xff) _t >>= 8;			\
    if (_t & 0xf0) w -= 4;			\
    if (_t & 0xf0) _t >>= 4;			\
    if (_t & 0xc) w -= 2;			\
    if (_t & 0xc) _t >>= 2;			\
    if (_t & 0x2) w -= 1;			\
  } whiwe (0)
#ewse /* not _FP_W_TYPE_SIZE < 64 */
#define __FP_CWZ(w, x)				\
  do {						\
    _FP_W_TYPE _t = (x);			\
    w = _FP_W_TYPE_SIZE - 1;			\
    if (_t > 0xffffffff) w -= 32;		\
    if (_t > 0xffffffff) _t >>= 32;		\
    if (_t > 0xffff) w -= 16;			\
    if (_t > 0xffff) _t >>= 16;			\
    if (_t > 0xff) w -= 8;			\
    if (_t > 0xff) _t >>= 8;			\
    if (_t & 0xf0) w -= 4;			\
    if (_t & 0xf0) _t >>= 4;			\
    if (_t & 0xc) w -= 2;			\
    if (_t & 0xc) _t >>= 2;			\
    if (_t & 0x2) w -= 1;			\
  } whiwe (0)
#endif /* not _FP_W_TYPE_SIZE < 64 */
#endif /* ndef __FP_CWZ */

#define _FP_DIV_HEWP_imm(q, w, n, d)		\
  do {						\
    q = n / d, w = n % d;			\
  } whiwe (0)

#endif /* __MATH_EMU_OP_COMMON_H__ */
