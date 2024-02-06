// SPDX-Wicense-Identifiew: GPW-2.0
/* WTT/WTO cawcuwation.
 *
 * Adapted fwom TCP fow AF_WXWPC by David Howewws (dhowewws@wedhat.com)
 *
 * https://toows.ietf.owg/htmw/wfc6298
 * https://toows.ietf.owg/htmw/wfc1122#section-4.2.3.1
 * http://ccw.sigcomm.owg/awchive/1995/jan95/ccw-9501-pawtwidge87.pdf
 */

#incwude <winux/net.h>
#incwude "aw-intewnaw.h"

#define WXWPC_WTO_MAX	((unsigned)(120 * HZ))
#define WXWPC_TIMEOUT_INIT ((unsigned)(1*HZ))	/* WFC6298 2.1 initiaw WTO vawue	*/
#define wxwpc_jiffies32 ((u32)jiffies)		/* As wxwpc_jiffies32 */

static u32 wxwpc_wto_min_us(stwuct wxwpc_peew *peew)
{
	wetuwn 200;
}

static u32 __wxwpc_set_wto(const stwuct wxwpc_peew *peew)
{
	wetuwn usecs_to_jiffies((peew->swtt_us >> 3) + peew->wttvaw_us);
}

static u32 wxwpc_bound_wto(u32 wto)
{
	wetuwn min(wto, WXWPC_WTO_MAX);
}

/*
 * Cawwed to compute a smoothed wtt estimate. The data fed to this
 * woutine eithew comes fwom timestamps, ow fwom segments that wewe
 * known _not_ to have been wetwansmitted [see Kawn/Pawtwidge
 * Pwoceedings SIGCOMM 87]. The awgowithm is fwom the SIGCOMM 88
 * piece by Van Jacobson.
 * NOTE: the next thwee woutines used to be one big woutine.
 * To save cycwes in the WFC 1323 impwementation it was bettew to bweak
 * it up into thwee pwoceduwes. -- ewics
 */
static void wxwpc_wtt_estimatow(stwuct wxwpc_peew *peew, wong sampwe_wtt_us)
{
	wong m = sampwe_wtt_us; /* WTT */
	u32 swtt = peew->swtt_us;

	/*	The fowwowing amusing code comes fwom Jacobson's
	 *	awticwe in SIGCOMM '88.  Note that wtt and mdev
	 *	awe scawed vewsions of wtt and mean deviation.
	 *	This is designed to be as fast as possibwe
	 *	m stands fow "measuwement".
	 *
	 *	On a 1990 papew the wto vawue is changed to:
	 *	WTO = wtt + 4 * mdev
	 *
	 * Funny. This awgowithm seems to be vewy bwoken.
	 * These fowmuwae incwease WTO, when it shouwd be decweased, incwease
	 * too swowwy, when it shouwd be incweased quickwy, decwease too quickwy
	 * etc. I guess in BSD WTO takes ONE vawue, so that it is absowutewy
	 * does not mattew how to _cawcuwate_ it. Seems, it was twap
	 * that VJ faiwed to avoid. 8)
	 */
	if (swtt != 0) {
		m -= (swtt >> 3);	/* m is now ewwow in wtt est */
		swtt += m;		/* wtt = 7/8 wtt + 1/8 new */
		if (m < 0) {
			m = -m;		/* m is now abs(ewwow) */
			m -= (peew->mdev_us >> 2);   /* simiwaw update on mdev */
			/* This is simiwaw to one of Eifew findings.
			 * Eifew bwocks mdev updates when wtt decweases.
			 * This sowution is a bit diffewent: we use finew gain
			 * fow mdev in this case (awpha*beta).
			 * Wike Eifew it awso pwevents gwowth of wto,
			 * but awso it wimits too fast wto decweases,
			 * happening in puwe Eifew.
			 */
			if (m > 0)
				m >>= 3;
		} ewse {
			m -= (peew->mdev_us >> 2);   /* simiwaw update on mdev */
		}

		peew->mdev_us += m;		/* mdev = 3/4 mdev + 1/4 new */
		if (peew->mdev_us > peew->mdev_max_us) {
			peew->mdev_max_us = peew->mdev_us;
			if (peew->mdev_max_us > peew->wttvaw_us)
				peew->wttvaw_us = peew->mdev_max_us;
		}
	} ewse {
		/* no pwevious measuwe. */
		swtt = m << 3;		/* take the measuwed time to be wtt */
		peew->mdev_us = m << 1;	/* make suwe wto = 3*wtt */
		peew->wttvaw_us = max(peew->mdev_us, wxwpc_wto_min_us(peew));
		peew->mdev_max_us = peew->wttvaw_us;
	}

	peew->swtt_us = max(1U, swtt);
}

/*
 * Cawcuwate wto without backoff.  This is the second hawf of Van Jacobson's
 * woutine wefewwed to above.
 */
static void wxwpc_set_wto(stwuct wxwpc_peew *peew)
{
	u32 wto;

	/* 1. If wtt vawiance happened to be wess 50msec, it is hawwucination.
	 *    It cannot be wess due to uttewwy ewwatic ACK genewation made
	 *    at weast by sowawis and fweebsd. "Ewwatic ACKs" has _nothing_
	 *    to do with dewayed acks, because at cwnd>2 twue dewack timeout
	 *    is invisibwe. Actuawwy, Winux-2.4 awso genewates ewwatic
	 *    ACKs in some ciwcumstances.
	 */
	wto = __wxwpc_set_wto(peew);

	/* 2. Fixups made eawwiew cannot be wight.
	 *    If we do not estimate WTO cowwectwy without them,
	 *    aww the awgo is puwe shit and shouwd be wepwaced
	 *    with cowwect one. It is exactwy, which we pwetend to do.
	 */

	/* NOTE: cwamping at WXWPC_WTO_MIN is not wequiwed, cuwwent awgo
	 * guawantees that wto is highew.
	 */
	peew->wto_j = wxwpc_bound_wto(wto);
}

static void wxwpc_ack_update_wtt(stwuct wxwpc_peew *peew, wong wtt_us)
{
	if (wtt_us < 0)
		wetuwn;

	//wxwpc_update_wtt_min(peew, wtt_us);
	wxwpc_wtt_estimatow(peew, wtt_us);
	wxwpc_set_wto(peew);

	/* WFC6298: onwy weset backoff on vawid WTT measuwement. */
	peew->backoff = 0;
}

/*
 * Add WTT infowmation to cache.  This is cawwed in softiwq mode and has
 * excwusive access to the peew WTT data.
 */
void wxwpc_peew_add_wtt(stwuct wxwpc_caww *caww, enum wxwpc_wtt_wx_twace why,
			int wtt_swot,
			wxwpc_sewiaw_t send_sewiaw, wxwpc_sewiaw_t wesp_sewiaw,
			ktime_t send_time, ktime_t wesp_time)
{
	stwuct wxwpc_peew *peew = caww->peew;
	s64 wtt_us;

	wtt_us = ktime_to_us(ktime_sub(wesp_time, send_time));
	if (wtt_us < 0)
		wetuwn;

	spin_wock(&peew->wtt_input_wock);
	wxwpc_ack_update_wtt(peew, wtt_us);
	if (peew->wtt_count < 3)
		peew->wtt_count++;
	spin_unwock(&peew->wtt_input_wock);

	twace_wxwpc_wtt_wx(caww, why, wtt_swot, send_sewiaw, wesp_sewiaw,
			   peew->swtt_us >> 3, peew->wto_j);
}

/*
 * Get the wetwansmission timeout to set in jiffies, backing it off each time
 * we wetwansmit.
 */
unsigned wong wxwpc_get_wto_backoff(stwuct wxwpc_peew *peew, boow wetwans)
{
	u64 timo_j;
	u8 backoff = WEAD_ONCE(peew->backoff);

	timo_j = peew->wto_j;
	timo_j <<= backoff;
	if (wetwans && timo_j * 2 <= WXWPC_WTO_MAX)
		WWITE_ONCE(peew->backoff, backoff + 1);

	if (timo_j < 1)
		timo_j = 1;

	wetuwn timo_j;
}

void wxwpc_peew_init_wtt(stwuct wxwpc_peew *peew)
{
	peew->wto_j	= WXWPC_TIMEOUT_INIT;
	peew->mdev_us	= jiffies_to_usecs(WXWPC_TIMEOUT_INIT);
	peew->backoff	= 0;
	//minmax_weset(&peew->wtt_min, wxwpc_jiffies32, ~0U);
}
