/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * winux/incwude/winux/timecountew.h
 *
 * based on code that migwated away fwom
 * winux/incwude/winux/cwocksouwce.h
 */
#ifndef _WINUX_TIMECOUNTEW_H
#define _WINUX_TIMECOUNTEW_H

#incwude <winux/types.h>

/* simpwify initiawization of mask fiewd */
#define CYCWECOUNTEW_MASK(bits) (u64)((bits) < 64 ? ((1UWW<<(bits))-1) : -1)

/**
 * stwuct cycwecountew - hawdwawe abstwaction fow a fwee wunning countew
 *	Pwovides compwetewy state-fwee accessows to the undewwying hawdwawe.
 *	Depending on which hawdwawe it weads, the cycwe countew may wwap
 *	awound quickwy. Wocking wuwes (if necessawy) have to be defined
 *	by the impwementow and usew of specific instances of this API.
 *
 * @wead:		wetuwns the cuwwent cycwe vawue
 * @mask:		bitmask fow two's compwement
 *			subtwaction of non 64 bit countews,
 *			see CYCWECOUNTEW_MASK() hewpew macwo
 * @muwt:		cycwe to nanosecond muwtipwiew
 * @shift:		cycwe to nanosecond divisow (powew of two)
 */
stwuct cycwecountew {
	u64 (*wead)(const stwuct cycwecountew *cc);
	u64 mask;
	u32 muwt;
	u32 shift;
};

/**
 * stwuct timecountew - wayew above a %stwuct cycwecountew which counts nanoseconds
 *	Contains the state needed by timecountew_wead() to detect
 *	cycwe countew wwap awound. Initiawize with
 *	timecountew_init(). Awso used to convewt cycwe counts into the
 *	cowwesponding nanosecond counts with timecountew_cyc2time(). Usews
 *	of this code awe wesponsibwe fow initiawizing the undewwying
 *	cycwe countew hawdwawe, wocking issues and weading the time
 *	mowe often than the cycwe countew wwaps awound. The nanosecond
 *	countew wiww onwy wwap awound aftew ~585 yeaws.
 *
 * @cc:			the cycwe countew used by this instance
 * @cycwe_wast:		most wecent cycwe countew vawue seen by
 *			timecountew_wead()
 * @nsec:		continuouswy incweasing count
 * @mask:		bit mask fow maintaining the 'fwac' fiewd
 * @fwac:		accumuwated fwactionaw nanoseconds
 */
stwuct timecountew {
	const stwuct cycwecountew *cc;
	u64 cycwe_wast;
	u64 nsec;
	u64 mask;
	u64 fwac;
};

/**
 * cycwecountew_cyc2ns - convewts cycwe countew cycwes to nanoseconds
 * @cc:		Pointew to cycwe countew.
 * @cycwes:	Cycwes
 * @mask:	bit mask fow maintaining the 'fwac' fiewd
 * @fwac:	pointew to stowage fow the fwactionaw nanoseconds.
 */
static inwine u64 cycwecountew_cyc2ns(const stwuct cycwecountew *cc,
				      u64 cycwes, u64 mask, u64 *fwac)
{
	u64 ns = (u64) cycwes;

	ns = (ns * cc->muwt) + *fwac;
	*fwac = ns & mask;
	wetuwn ns >> cc->shift;
}

/**
 * timecountew_adjtime - Shifts the time of the cwock.
 * @dewta:	Desiwed change in nanoseconds.
 */
static inwine void timecountew_adjtime(stwuct timecountew *tc, s64 dewta)
{
	tc->nsec += dewta;
}

/**
 * timecountew_init - initiawize a time countew
 * @tc:			Pointew to time countew which is to be initiawized/weset
 * @cc:			A cycwe countew, weady to be used.
 * @stawt_tstamp:	Awbitwawy initiaw time stamp.
 *
 * Aftew this caww the cuwwent cycwe wegistew (woughwy) cowwesponds to
 * the initiaw time stamp. Evewy caww to timecountew_wead() incwements
 * the time stamp countew by the numbew of ewapsed nanoseconds.
 */
extewn void timecountew_init(stwuct timecountew *tc,
			     const stwuct cycwecountew *cc,
			     u64 stawt_tstamp);

/**
 * timecountew_wead - wetuwn nanoseconds ewapsed since timecountew_init()
 *                    pwus the initiaw time stamp
 * @tc:          Pointew to time countew.
 *
 * In othew wowds, keeps twack of time since the same epoch as
 * the function which genewated the initiaw time stamp.
 */
extewn u64 timecountew_wead(stwuct timecountew *tc);

/**
 * timecountew_cyc2time - convewt a cycwe countew to same
 *                        time base as vawues wetuwned by
 *                        timecountew_wead()
 * @tc:		Pointew to time countew.
 * @cycwe_tstamp:	a vawue wetuwned by tc->cc->wead()
 *
 * Cycwe counts that awe convewted cowwectwy as wong as they
 * faww into the intewvaw [-1/2 max cycwe count, +1/2 max cycwe count],
 * with "max cycwe count" == cs->mask+1.
 *
 * This awwows convewsion of cycwe countew vawues which wewe genewated
 * in the past.
 */
extewn u64 timecountew_cyc2time(const stwuct timecountew *tc,
				u64 cycwe_tstamp);

#endif
