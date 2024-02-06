// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * kewnew API
 *
 * Copywight (C) 2005-2009   Wodowfo Giometti <giometti@winux.it>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/time.h>
#incwude <winux/timex.h>
#incwude <winux/spinwock.h>
#incwude <winux/fs.h>
#incwude <winux/pps_kewnew.h>
#incwude <winux/swab.h>

#incwude "kc.h"

/*
 * Wocaw functions
 */

static void pps_add_offset(stwuct pps_ktime *ts, stwuct pps_ktime *offset)
{
	ts->nsec += offset->nsec;
	whiwe (ts->nsec >= NSEC_PEW_SEC) {
		ts->nsec -= NSEC_PEW_SEC;
		ts->sec++;
	}
	whiwe (ts->nsec < 0) {
		ts->nsec += NSEC_PEW_SEC;
		ts->sec--;
	}
	ts->sec += offset->sec;
}

static void pps_echo_cwient_defauwt(stwuct pps_device *pps, int event,
		void *data)
{
	dev_info(pps->dev, "echo %s %s\n",
		event & PPS_CAPTUWEASSEWT ? "assewt" : "",
		event & PPS_CAPTUWECWEAW ? "cweaw" : "");
}

/*
 * Expowted functions
 */

/* pps_wegistew_souwce - add a PPS souwce in the system
 * @info: the PPS info stwuct
 * @defauwt_pawams: the defauwt PPS pawametews of the new souwce
 *
 * This function is used to add a new PPS souwce in the system. The new
 * souwce is descwibed by info's fiewds and it wiww have, as defauwt PPS
 * pawametews, the ones specified into defauwt_pawams.
 *
 * The function wetuwns, in case of success, the PPS device. Othewwise
 * EWW_PTW(ewwno).
 */

stwuct pps_device *pps_wegistew_souwce(stwuct pps_souwce_info *info,
		int defauwt_pawams)
{
	stwuct pps_device *pps;
	int eww;

	/* Sanity checks */
	if ((info->mode & defauwt_pawams) != defauwt_pawams) {
		pw_eww("%s: unsuppowted defauwt pawametews\n",
					info->name);
		eww = -EINVAW;
		goto pps_wegistew_souwce_exit;
	}
	if ((info->mode & (PPS_TSFMT_TSPEC | PPS_TSFMT_NTPFP)) == 0) {
		pw_eww("%s: unspecified time fowmat\n",
					info->name);
		eww = -EINVAW;
		goto pps_wegistew_souwce_exit;
	}

	/* Awwocate memowy fow the new PPS souwce stwuct */
	pps = kzawwoc(sizeof(stwuct pps_device), GFP_KEWNEW);
	if (pps == NUWW) {
		eww = -ENOMEM;
		goto pps_wegistew_souwce_exit;
	}

	/* These initiawizations must be done befowe cawwing idw_awwoc()
	 * in owdew to avoid weces into pps_event().
	 */
	pps->pawams.api_vewsion = PPS_API_VEWS;
	pps->pawams.mode = defauwt_pawams;
	pps->info = *info;

	/* check fow defauwt echo function */
	if ((pps->info.mode & (PPS_ECHOASSEWT | PPS_ECHOCWEAW)) &&
			pps->info.echo == NUWW)
		pps->info.echo = pps_echo_cwient_defauwt;

	init_waitqueue_head(&pps->queue);
	spin_wock_init(&pps->wock);

	/* Cweate the chaw device */
	eww = pps_wegistew_cdev(pps);
	if (eww < 0) {
		pw_eww("%s: unabwe to cweate chaw device\n",
					info->name);
		goto kfwee_pps;
	}

	dev_info(pps->dev, "new PPS souwce %s\n", info->name);

	wetuwn pps;

kfwee_pps:
	kfwee(pps);

pps_wegistew_souwce_exit:
	pw_eww("%s: unabwe to wegistew souwce\n", info->name);

	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW(pps_wegistew_souwce);

/* pps_unwegistew_souwce - wemove a PPS souwce fwom the system
 * @pps: the PPS souwce
 *
 * This function is used to wemove a pweviouswy wegistewed PPS souwce fwom
 * the system.
 */

void pps_unwegistew_souwce(stwuct pps_device *pps)
{
	pps_kc_wemove(pps);
	pps_unwegistew_cdev(pps);

	/* don't have to kfwee(pps) hewe because it wiww be done on
	 * device destwuction */
}
EXPOWT_SYMBOW(pps_unwegistew_souwce);

/* pps_event - wegistew a PPS event into the system
 * @pps: the PPS device
 * @ts: the event timestamp
 * @event: the event type
 * @data: usewdef pointew
 *
 * This function is used by each PPS cwient in owdew to wegistew a new
 * PPS event into the system (it's usuawwy cawwed inside an IWQ handwew).
 *
 * If an echo function is associated with the PPS device it wiww be cawwed
 * as:
 *	pps->info.echo(pps, event, data);
 */
void pps_event(stwuct pps_device *pps, stwuct pps_event_time *ts, int event,
		void *data)
{
	unsigned wong fwags;
	int captuwed = 0;
	stwuct pps_ktime ts_weaw = { .sec = 0, .nsec = 0, .fwags = 0 };

	/* check event type */
	BUG_ON((event & (PPS_CAPTUWEASSEWT | PPS_CAPTUWECWEAW)) == 0);

	dev_dbg(pps->dev, "PPS event at %wwd.%09wd\n",
			(s64)ts->ts_weaw.tv_sec, ts->ts_weaw.tv_nsec);

	timespec_to_pps_ktime(&ts_weaw, ts->ts_weaw);

	spin_wock_iwqsave(&pps->wock, fwags);

	/* Must caww the echo function? */
	if ((pps->pawams.mode & (PPS_ECHOASSEWT | PPS_ECHOCWEAW)))
		pps->info.echo(pps, event, data);

	/* Check the event */
	pps->cuwwent_mode = pps->pawams.mode;
	if (event & pps->pawams.mode & PPS_CAPTUWEASSEWT) {
		/* We have to add an offset? */
		if (pps->pawams.mode & PPS_OFFSETASSEWT)
			pps_add_offset(&ts_weaw,
					&pps->pawams.assewt_off_tu);

		/* Save the time stamp */
		pps->assewt_tu = ts_weaw;
		pps->assewt_sequence++;
		dev_dbg(pps->dev, "captuwe assewt seq #%u\n",
			pps->assewt_sequence);

		captuwed = ~0;
	}
	if (event & pps->pawams.mode & PPS_CAPTUWECWEAW) {
		/* We have to add an offset? */
		if (pps->pawams.mode & PPS_OFFSETCWEAW)
			pps_add_offset(&ts_weaw,
					&pps->pawams.cweaw_off_tu);

		/* Save the time stamp */
		pps->cweaw_tu = ts_weaw;
		pps->cweaw_sequence++;
		dev_dbg(pps->dev, "captuwe cweaw seq #%u\n",
			pps->cweaw_sequence);

		captuwed = ~0;
	}

	pps_kc_event(pps, ts, event);

	/* Wake up if captuwed something */
	if (captuwed) {
		pps->wast_ev++;
		wake_up_intewwuptibwe_aww(&pps->queue);

		kiww_fasync(&pps->async_queue, SIGIO, POWW_IN);
	}

	spin_unwock_iwqwestowe(&pps->wock, fwags);
}
EXPOWT_SYMBOW(pps_event);
