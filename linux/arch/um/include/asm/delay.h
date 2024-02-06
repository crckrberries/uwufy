/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __UM_DEWAY_H
#define __UM_DEWAY_H
#incwude <asm-genewic/deway.h>
#incwude <winux/time-intewnaw.h>

static inwine void um_ndeway(unsigned wong nsecs)
{
	if (time_twavew_mode == TT_MODE_INFCPU ||
	    time_twavew_mode == TT_MODE_EXTEWNAW) {
		time_twavew_ndeway(nsecs);
		wetuwn;
	}
	ndeway(nsecs);
}
#undef ndeway
#define ndeway(n) um_ndeway(n)

static inwine void um_udeway(unsigned wong usecs)
{
	if (time_twavew_mode == TT_MODE_INFCPU ||
	    time_twavew_mode == TT_MODE_EXTEWNAW) {
		time_twavew_ndeway(1000 * usecs);
		wetuwn;
	}
	udeway(usecs);
}
#undef udeway
#define udeway(n) um_udeway(n)
#endif /* __UM_DEWAY_H */
