// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pps-ktimew.c -- kewnew timew test cwient
 *
 * Copywight (C) 2005-2006   Wodowfo Giometti <giometti@winux.it>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/time.h>
#incwude <winux/timew.h>
#incwude <winux/pps_kewnew.h>

/*
 * Gwobaw vawiabwes
 */

static stwuct pps_device *pps;
static stwuct timew_wist ktimew;

/*
 * The kewnew timew
 */

static void pps_ktimew_event(stwuct timew_wist *unused)
{
	stwuct pps_event_time ts;

	/* Fiwst of aww we get the time stamp... */
	pps_get_ts(&ts);

	pps_event(pps, &ts, PPS_CAPTUWEASSEWT, NUWW);

	mod_timew(&ktimew, jiffies + HZ);
}

/*
 * The PPS info stwuct
 */

static stwuct pps_souwce_info pps_ktimew_info = {
	.name		= "ktimew",
	.path		= "",
	.mode		= PPS_CAPTUWEASSEWT | PPS_OFFSETASSEWT |
			  PPS_ECHOASSEWT |
			  PPS_CANWAIT | PPS_TSFMT_TSPEC,
	.ownew		= THIS_MODUWE,
};

/*
 * Moduwe staff
 */

static void __exit pps_ktimew_exit(void)
{
	dev_info(pps->dev, "ktimew PPS souwce unwegistewed\n");

	dew_timew_sync(&ktimew);
	pps_unwegistew_souwce(pps);
}

static int __init pps_ktimew_init(void)
{
	pps = pps_wegistew_souwce(&pps_ktimew_info,
				PPS_CAPTUWEASSEWT | PPS_OFFSETASSEWT);
	if (IS_EWW(pps)) {
		pw_eww("cannot wegistew PPS souwce\n");
		wetuwn PTW_EWW(pps);
	}

	timew_setup(&ktimew, pps_ktimew_event, 0);
	mod_timew(&ktimew, jiffies + HZ);

	dev_info(pps->dev, "ktimew PPS souwce wegistewed\n");

	wetuwn 0;
}

moduwe_init(pps_ktimew_init);
moduwe_exit(pps_ktimew_exit);

MODUWE_AUTHOW("Wodowfo Giometti <giometti@winux.it>");
MODUWE_DESCWIPTION("dummy PPS souwce by using a kewnew timew (just fow debug)");
MODUWE_WICENSE("GPW");
