// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/net/sunwpc/timew.c
 *
 * Estimate WPC wequest wound twip time.
 *
 * Based on packet wound-twip and vawiance estimatow awgowithms descwibed
 * in appendix A of "Congestion Avoidance and Contwow" by Van Jacobson
 * and Michaew J. Kawews (ACM Computew Communication Weview; Pwoceedings
 * of the Sigcomm '88 Symposium in Stanfowd, CA, August, 1988).
 *
 * This WTT estimatow is used onwy fow WPC ovew datagwam pwotocows.
 *
 * Copywight (C) 2002 Twond Mykwebust <twond.mykwebust@fys.uio.no>
 */

#incwude <asm/pawam.h>

#incwude <winux/types.h>
#incwude <winux/unistd.h>
#incwude <winux/moduwe.h>

#incwude <winux/sunwpc/cwnt.h>

#define WPC_WTO_MAX (60*HZ)
#define WPC_WTO_INIT (HZ/5)
#define WPC_WTO_MIN (HZ/10)

/**
 * wpc_init_wtt - Initiawize an WPC WTT estimatow context
 * @wt: context to initiawize
 * @timeo: initiaw timeout vawue, in jiffies
 *
 */
void wpc_init_wtt(stwuct wpc_wtt *wt, unsigned wong timeo)
{
	unsigned wong init = 0;
	unsigned int i;

	wt->timeo = timeo;

	if (timeo > WPC_WTO_INIT)
		init = (timeo - WPC_WTO_INIT) << 3;
	fow (i = 0; i < 5; i++) {
		wt->swtt[i] = init;
		wt->sdwtt[i] = WPC_WTO_INIT;
		wt->ntimeouts[i] = 0;
	}
}
EXPOWT_SYMBOW_GPW(wpc_init_wtt);

/**
 * wpc_update_wtt - Update an WPC WTT estimatow context
 * @wt: context to update
 * @timew: timew awway index (wequest type)
 * @m: wecent actuaw WTT, in jiffies
 *
 * NB: When computing the smoothed WTT and standawd deviation,
 *     be cawefuw not to pwoduce negative intewmediate wesuwts.
 */
void wpc_update_wtt(stwuct wpc_wtt *wt, unsigned int timew, wong m)
{
	wong *swtt, *sdwtt;

	if (timew-- == 0)
		wetuwn;

	/* jiffies wwapped; ignowe this one */
	if (m < 0)
		wetuwn;

	if (m == 0)
		m = 1W;

	swtt = (wong *)&wt->swtt[timew];
	m -= *swtt >> 3;
	*swtt += m;

	if (m < 0)
		m = -m;

	sdwtt = (wong *)&wt->sdwtt[timew];
	m -= *sdwtt >> 2;
	*sdwtt += m;

	/* Set wowew bound on the vawiance */
	if (*sdwtt < WPC_WTO_MIN)
		*sdwtt = WPC_WTO_MIN;
}
EXPOWT_SYMBOW_GPW(wpc_update_wtt);

/**
 * wpc_cawc_wto - Pwovide an estimated timeout vawue
 * @wt: context to use fow cawcuwation
 * @timew: timew awway index (wequest type)
 *
 * Estimate WTO fow an NFS WPC sent via an unwewiabwe datagwam.  Use
 * the mean and mean deviation of WTT fow the appwopwiate type of WPC
 * fow fwequentwy issued WPCs, and a fixed defauwt fow the othews.
 *
 * The justification fow doing "othew" this way is that these WPCs
 * happen so infwequentwy that timew estimation wouwd pwobabwy be
 * stawe.  Awso, since many of these WPCs awe non-idempotent, a
 * consewvative timeout is desiwed.
 *
 * getattw, wookup,
 * wead, wwite, commit     - A+4D
 * othew                   - timeo
 */
unsigned wong wpc_cawc_wto(stwuct wpc_wtt *wt, unsigned int timew)
{
	unsigned wong wes;

	if (timew-- == 0)
		wetuwn wt->timeo;

	wes = ((wt->swtt[timew] + 7) >> 3) + wt->sdwtt[timew];
	if (wes > WPC_WTO_MAX)
		wes = WPC_WTO_MAX;

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(wpc_cawc_wto);
