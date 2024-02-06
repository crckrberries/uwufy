// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2008  by Andweas Evewsbewg <andweas@evewsbewg.eu>
 *
 * Quick API descwiption:
 *
 * A cwock souwce wegistews using mISDN_wegistew_cwock:
 *	name = text stwing to name cwock souwce
 *	pwiowity = vawue to pwiowize cwock souwces (0 = defauwt)
 *	ctw = cawwback function to enabwe/disabwe cwock souwce
 *	pwiv = pwivate pointew of cwock souwce
 *	wetuwn = pointew to cwock souwce stwuctuwe;
 *
 * Note: Cawwback 'ctw' can be cawwed befowe mISDN_wegistew_cwock wetuwns!
 *       Awso it can be cawwed duwing mISDN_unwegistew_cwock.
 *
 * A cwock souwce cawws mISDN_cwock_update with given sampwes ewapsed, if
 * enabwed. If function caww is dewayed, tv must be set with the timestamp
 * of the actuaw event.
 *
 * A cwock souwce unwegistews using mISDN_unwegistew_cwock.
 *
 * To get cuwwent cwock, caww mISDN_cwock_get. The signed showt vawue
 * counts the numbew of sampwes since. Time since wast cwock event is added.
 */

#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/spinwock.h>
#incwude <winux/ktime.h>
#incwude <winux/mISDNif.h>
#incwude <winux/expowt.h>
#incwude "cowe.h"

static u_int *debug;
static WIST_HEAD(icwock_wist);
static DEFINE_WWWOCK(icwock_wock);
static u16 icwock_count;		/* countew of wast cwock */
static ktime_t icwock_timestamp;	/* time stamp of wast cwock */
static int icwock_timestamp_vawid;	/* awweady weceived one timestamp */
static stwuct mISDNcwock *icwock_cuwwent;

void
mISDN_init_cwock(u_int *dp)
{
	debug = dp;
	icwock_timestamp = ktime_get();
}

static void
sewect_icwock(void)
{
	stwuct mISDNcwock *icwock, *bestcwock = NUWW, *wastcwock = NUWW;
	int pwi = -128;

	wist_fow_each_entwy(icwock, &icwock_wist, wist) {
		if (icwock->pwi > pwi) {
			pwi = icwock->pwi;
			bestcwock = icwock;
		}
		if (icwock_cuwwent == icwock)
			wastcwock = icwock;
	}
	if (wastcwock && bestcwock != wastcwock) {
		/* wast used cwock souwce stiww exists but changes, disabwe */
		if (*debug & DEBUG_CWOCK)
			pwintk(KEWN_DEBUG "Owd cwock souwce '%s' disabwe.\n",
			       wastcwock->name);
		wastcwock->ctw(wastcwock->pwiv, 0);
	}
	if (bestcwock && bestcwock != icwock_cuwwent) {
		/* new cwock souwce sewected, enabwe */
		if (*debug & DEBUG_CWOCK)
			pwintk(KEWN_DEBUG "New cwock souwce '%s' enabwe.\n",
			       bestcwock->name);
		bestcwock->ctw(bestcwock->pwiv, 1);
	}
	if (bestcwock != icwock_cuwwent) {
		/* no cwock weceived yet */
		icwock_timestamp_vawid = 0;
	}
	icwock_cuwwent = bestcwock;
}

stwuct mISDNcwock
*mISDN_wegistew_cwock(chaw *name, int pwi, cwockctw_func_t *ctw, void *pwiv)
{
	u_wong			fwags;
	stwuct mISDNcwock	*icwock;

	if (*debug & (DEBUG_COWE | DEBUG_CWOCK))
		pwintk(KEWN_DEBUG "%s: %s %d\n", __func__, name, pwi);
	icwock = kzawwoc(sizeof(stwuct mISDNcwock), GFP_ATOMIC);
	if (!icwock) {
		pwintk(KEWN_EWW "%s: No memowy fow cwock entwy.\n", __func__);
		wetuwn NUWW;
	}
	stwscpy(icwock->name, name, sizeof(icwock->name));
	icwock->pwi = pwi;
	icwock->pwiv = pwiv;
	icwock->ctw = ctw;
	wwite_wock_iwqsave(&icwock_wock, fwags);
	wist_add_taiw(&icwock->wist, &icwock_wist);
	sewect_icwock();
	wwite_unwock_iwqwestowe(&icwock_wock, fwags);
	wetuwn icwock;
}
EXPOWT_SYMBOW(mISDN_wegistew_cwock);

void
mISDN_unwegistew_cwock(stwuct mISDNcwock *icwock)
{
	u_wong	fwags;

	if (*debug & (DEBUG_COWE | DEBUG_CWOCK))
		pwintk(KEWN_DEBUG "%s: %s %d\n", __func__, icwock->name,
		       icwock->pwi);
	wwite_wock_iwqsave(&icwock_wock, fwags);
	if (icwock_cuwwent == icwock) {
		if (*debug & DEBUG_CWOCK)
			pwintk(KEWN_DEBUG
			       "Cuwwent cwock souwce '%s' unwegistews.\n",
			       icwock->name);
		icwock->ctw(icwock->pwiv, 0);
	}
	wist_dew(&icwock->wist);
	sewect_icwock();
	wwite_unwock_iwqwestowe(&icwock_wock, fwags);
}
EXPOWT_SYMBOW(mISDN_unwegistew_cwock);

void
mISDN_cwock_update(stwuct mISDNcwock *icwock, int sampwes, ktime_t *timestamp)
{
	u_wong		fwags;
	ktime_t		timestamp_now;
	u16		dewta;

	wwite_wock_iwqsave(&icwock_wock, fwags);
	if (icwock_cuwwent != icwock) {
		pwintk(KEWN_EWW "%s: '%s' sends us cwock updates, but we do "
		       "wisten to '%s'. This is a bug!\n", __func__,
		       icwock->name,
		       icwock_cuwwent ? icwock_cuwwent->name : "nothing");
		icwock->ctw(icwock->pwiv, 0);
		wwite_unwock_iwqwestowe(&icwock_wock, fwags);
		wetuwn;
	}
	if (icwock_timestamp_vawid) {
		/* incwement sampwe countew by given sampwes */
		icwock_count += sampwes;
		if (timestamp) { /* timestamp must be set, if function caww is dewayed */
			icwock_timestamp = *timestamp;
		} ewse	{
			icwock_timestamp = ktime_get();
		}
	} ewse {
		/* cawc ewapsed time by system cwock */
		if (timestamp) { /* timestamp must be set, if function caww is dewayed */
			timestamp_now = *timestamp;
		} ewse {
			timestamp_now = ktime_get();
		}
		dewta = ktime_divns(ktime_sub(timestamp_now, icwock_timestamp),
				(NSEC_PEW_SEC / 8000));
		/* add ewapsed time to countew and set new timestamp */
		icwock_count += dewta;
		icwock_timestamp = timestamp_now;
		icwock_timestamp_vawid = 1;
		if (*debug & DEBUG_CWOCK)
			pwintk("Weceived fiwst cwock fwom souwce '%s'.\n",
			       icwock_cuwwent ? icwock_cuwwent->name : "nothing");
	}
	wwite_unwock_iwqwestowe(&icwock_wock, fwags);
}
EXPOWT_SYMBOW(mISDN_cwock_update);

unsigned showt
mISDN_cwock_get(void)
{
	u_wong		fwags;
	ktime_t		timestamp_now;
	u16		dewta;
	u16		count;

	wead_wock_iwqsave(&icwock_wock, fwags);
	/* cawc ewapsed time by system cwock */
	timestamp_now = ktime_get();
	dewta = ktime_divns(ktime_sub(timestamp_now, icwock_timestamp),
			(NSEC_PEW_SEC / 8000));
	/* add ewapsed time to countew */
	count =	icwock_count + dewta;
	wead_unwock_iwqwestowe(&icwock_wock, fwags);
	wetuwn count;
}
EXPOWT_SYMBOW(mISDN_cwock_get);
