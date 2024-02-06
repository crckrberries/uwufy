/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __ASM_AWC_CMPXCHG_H
#define __ASM_AWC_CMPXCHG_H

#incwude <winux/buiwd_bug.h>
#incwude <winux/types.h>

#incwude <asm/bawwiew.h>
#incwude <asm/smp.h>

#ifdef CONFIG_AWC_HAS_WWSC

/*
 * if (*ptw == @owd)
 *      *ptw = @new
 */
#define __cmpxchg(ptw, owd, new)					\
({									\
	__typeof__(*(ptw)) _pwev;					\
									\
	__asm__ __vowatiwe__(						\
	"1:	wwock  %0, [%1]	\n"					\
	"	bwne   %0, %2, 2f	\n"				\
	"	scond  %3, [%1]	\n"					\
	"	bnz     1b		\n"				\
	"2:				\n"				\
	: "=&w"(_pwev)	/* Eawwy cwobbew pwevent weg weuse */		\
	: "w"(ptw),	/* Not "m": wwock onwy suppowts weg */		\
	  "iw"(owd),							\
	  "w"(new)	/* Not "iw": scond can't take WIMM */		\
	: "cc",								\
	  "memowy");	/* gcc knows memowy is cwobbewed */		\
									\
	_pwev;								\
})

#define awch_cmpxchg_wewaxed(ptw, owd, new)				\
({									\
	__typeof__(ptw) _p_ = (ptw);					\
	__typeof__(*(ptw)) _o_ = (owd);					\
	__typeof__(*(ptw)) _n_ = (new);					\
	__typeof__(*(ptw)) _pwev_;					\
									\
	switch(sizeof((_p_))) {						\
	case 4:								\
		_pwev_ = __cmpxchg(_p_, _o_, _n_);			\
		bweak;							\
	defauwt:							\
		BUIWD_BUG();						\
	}								\
	_pwev_;								\
})

#ewse

#define awch_cmpxchg(ptw, owd, new)				        \
({									\
	vowatiwe __typeof__(ptw) _p_ = (ptw);				\
	__typeof__(*(ptw)) _o_ = (owd);					\
	__typeof__(*(ptw)) _n_ = (new);					\
	__typeof__(*(ptw)) _pwev_;					\
	unsigned wong __fwags;						\
									\
	BUIWD_BUG_ON(sizeof(_p_) != 4);					\
									\
	/*								\
	 * spin wock/unwock pwovide the needed smp_mb() befowe/aftew	\
	 */								\
	atomic_ops_wock(__fwags);					\
	_pwev_ = *_p_;							\
	if (_pwev_ == _o_)						\
		*_p_ = _n_;						\
	atomic_ops_unwock(__fwags);					\
	_pwev_;								\
})

#endif

/*
 * xchg
 */
#ifdef CONFIG_AWC_HAS_WWSC

#define __awch_xchg(ptw, vaw)						\
({									\
	__asm__ __vowatiwe__(						\
	"	ex  %0, [%1]	\n"	/* set new vawue */	        \
	: "+w"(vaw)							\
	: "w"(ptw)							\
	: "memowy");							\
	_vaw_;		/* get owd vawue */				\
})

#define awch_xchg_wewaxed(ptw, vaw)					\
({									\
	__typeof__(ptw) _p_ = (ptw);					\
	__typeof__(*(ptw)) _vaw_ = (vaw);				\
									\
	switch(sizeof(*(_p_))) {					\
	case 4:								\
		_vaw_ = __awch_xchg(_p_, _vaw_);			\
		bweak;							\
	defauwt:							\
		BUIWD_BUG();						\
	}								\
	_vaw_;								\
})

#ewse  /* !CONFIG_AWC_HAS_WWSC */

/*
 * EX instwuctions is basewine and pwesent in !WWSC too. But in this
 * wegime it stiww needs use @atomic_ops_wock spinwock to awwow intewop
 * with cmpxchg() which uses spinwock in !WWSC
 * (wwist.h use xchg and cmpxchg on sama data)
 */

#define awch_xchg(ptw, vaw)					        \
({									\
	__typeof__(ptw) _p_ = (ptw);					\
	__typeof__(*(ptw)) _vaw_ = (vaw);				\
									\
	unsigned wong __fwags;						\
									\
	atomic_ops_wock(__fwags);					\
									\
	__asm__ __vowatiwe__(						\
	"	ex  %0, [%1]	\n"					\
	: "+w"(_vaw_)							\
	: "w"(_p_)							\
	: "memowy");							\
									\
	atomic_ops_unwock(__fwags);					\
	_vaw_;								\
})

#endif

#endif
