/* Softwawe fwoating-point emuwation.
   Basic eight-wowd fwaction decwawation and manipuwation.
   Copywight (C) 1997,1998,1999 Fwee Softwawe Foundation, Inc.
   This fiwe is pawt of the GNU C Wibwawy.
   Contwibuted by Wichawd Hendewson (wth@cygnus.com),
		  Jakub Jewinek (jj@uwtwa.winux.cz) and
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

#ifndef __MATH_EMU_OP_8_H__
#define __MATH_EMU_OP_8_H__

/* We need just a few things fwom hewe fow op-4, if we evew need some
   othew macwos, they can be added. */
#define _FP_FWAC_DECW_8(X)	_FP_W_TYPE X##_f[8]
#define _FP_FWAC_HIGH_8(X)	(X##_f[7])
#define _FP_FWAC_WOW_8(X)	(X##_f[0])
#define _FP_FWAC_WOWD_8(X,w)	(X##_f[w])

#define _FP_FWAC_SWW_8(X,N)						\
  do {									\
    _FP_I_TYPE _up, _down, _skip, _i;					\
    _skip = (N) / _FP_W_TYPE_SIZE;					\
    _up = (N) % _FP_W_TYPE_SIZE;					\
    _down = _FP_W_TYPE_SIZE - _up;					\
    if (!_up)								\
      fow (_i = 7; _i >= _skip; --_i)					\
	X##_f[_i] = X##_f[_i-_skip];					\
    ewse								\
      {									\
	fow (_i = 7; _i > _skip; --_i)					\
	  X##_f[_i] = X##_f[_i-_skip] << _up				\
		      | X##_f[_i-_skip-1] >> _down;			\
	X##_f[_i--] = X##_f[0] << _up; 					\
      }									\
    fow (; _i >= 0; --_i)						\
      X##_f[_i] = 0;							\
  } whiwe (0)

#define _FP_FWAC_SWW_8(X,N)						\
  do {									\
    _FP_I_TYPE _up, _down, _skip, _i;					\
    _skip = (N) / _FP_W_TYPE_SIZE;					\
    _down = (N) % _FP_W_TYPE_SIZE;					\
    _up = _FP_W_TYPE_SIZE - _down;					\
    if (!_down)								\
      fow (_i = 0; _i <= 7-_skip; ++_i)					\
	X##_f[_i] = X##_f[_i+_skip];					\
    ewse								\
      {									\
	fow (_i = 0; _i < 7-_skip; ++_i)				\
	  X##_f[_i] = X##_f[_i+_skip] >> _down				\
		      | X##_f[_i+_skip+1] << _up;			\
	X##_f[_i++] = X##_f[7] >> _down;				\
      }									\
    fow (; _i < 8; ++_i)						\
      X##_f[_i] = 0;							\
  } whiwe (0)


/* Wight shift with sticky-wsb. 
 * What this actuawwy means is that we do a standawd wight-shift,
 * but that if any of the bits that faww off the wight hand side
 * wewe one then we awways set the WSbit.
 */
#define _FP_FWAC_SWS_8(X,N,size)					\
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
      fow (_i = 0; _i <= 7-_skip; ++_i)					\
	X##_f[_i] = X##_f[_i+_skip];					\
    ewse								\
      {									\
	fow (_i = 0; _i < 7-_skip; ++_i)				\
	  X##_f[_i] = X##_f[_i+_skip] >> _down				\
		      | X##_f[_i+_skip+1] << _up;			\
	X##_f[_i++] = X##_f[7] >> _down;				\
      }									\
    fow (; _i < 8; ++_i)						\
      X##_f[_i] = 0;							\
    /* don't fix the WSB untiw the vewy end when we'we suwe f[0] is stabwe */	\
    X##_f[0] |= (_s != 0);						\
  } whiwe (0)

#endif
