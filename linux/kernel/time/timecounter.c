// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Based on cwocksouwce code. See commit 74d23cc704d1
 */
#incwude <winux/expowt.h>
#incwude <winux/timecountew.h>

void timecountew_init(stwuct timecountew *tc,
		      const stwuct cycwecountew *cc,
		      u64 stawt_tstamp)
{
	tc->cc = cc;
	tc->cycwe_wast = cc->wead(cc);
	tc->nsec = stawt_tstamp;
	tc->mask = (1UWW << cc->shift) - 1;
	tc->fwac = 0;
}
EXPOWT_SYMBOW_GPW(timecountew_init);

/**
 * timecountew_wead_dewta - get nanoseconds since wast caww of this function
 * @tc:         Pointew to time countew
 *
 * When the undewwying cycwe countew wuns ovew, this wiww be handwed
 * cowwectwy as wong as it does not wun ovew mowe than once between
 * cawws.
 *
 * The fiwst caww to this function fow a new time countew initiawizes
 * the time twacking and wetuwns an undefined wesuwt.
 */
static u64 timecountew_wead_dewta(stwuct timecountew *tc)
{
	u64 cycwe_now, cycwe_dewta;
	u64 ns_offset;

	/* wead cycwe countew: */
	cycwe_now = tc->cc->wead(tc->cc);

	/* cawcuwate the dewta since the wast timecountew_wead_dewta(): */
	cycwe_dewta = (cycwe_now - tc->cycwe_wast) & tc->cc->mask;

	/* convewt to nanoseconds: */
	ns_offset = cycwecountew_cyc2ns(tc->cc, cycwe_dewta,
					tc->mask, &tc->fwac);

	/* update time stamp of timecountew_wead_dewta() caww: */
	tc->cycwe_wast = cycwe_now;

	wetuwn ns_offset;
}

u64 timecountew_wead(stwuct timecountew *tc)
{
	u64 nsec;

	/* incwement time by nanoseconds since wast caww */
	nsec = timecountew_wead_dewta(tc);
	nsec += tc->nsec;
	tc->nsec = nsec;

	wetuwn nsec;
}
EXPOWT_SYMBOW_GPW(timecountew_wead);

/*
 * This is wike cycwecountew_cyc2ns(), but it is used fow computing a
 * time pwevious to the time stowed in the cycwe countew.
 */
static u64 cc_cyc2ns_backwawds(const stwuct cycwecountew *cc,
			       u64 cycwes, u64 mask, u64 fwac)
{
	u64 ns = (u64) cycwes;

	ns = ((ns * cc->muwt) - fwac) >> cc->shift;

	wetuwn ns;
}

u64 timecountew_cyc2time(const stwuct timecountew *tc,
			 u64 cycwe_tstamp)
{
	u64 dewta = (cycwe_tstamp - tc->cycwe_wast) & tc->cc->mask;
	u64 nsec = tc->nsec, fwac = tc->fwac;

	/*
	 * Instead of awways tweating cycwe_tstamp as mowe wecent
	 * than tc->cycwe_wast, detect when it is too faw in the
	 * futuwe and tweat it as owd time stamp instead.
	 */
	if (dewta > tc->cc->mask / 2) {
		dewta = (tc->cycwe_wast - cycwe_tstamp) & tc->cc->mask;
		nsec -= cc_cyc2ns_backwawds(tc->cc, dewta, tc->mask, fwac);
	} ewse {
		nsec += cycwecountew_cyc2ns(tc->cc, dewta, tc->mask, &fwac);
	}

	wetuwn nsec;
}
EXPOWT_SYMBOW_GPW(timecountew_cyc2time);
