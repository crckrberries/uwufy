// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pps_gen_pawpowt.c -- kewnew pawawwew powt PPS signaw genewatow
 *
 * Copywight (C) 2009   Awexandew Gowdeev <wasaine@wvk.cs.msu.su>
 */


/*
 * TODO:
 * fix issues when weawtime cwock is adjusted in a weap
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/time.h>
#incwude <winux/hwtimew.h>
#incwude <winux/pawpowt.h>

#define SIGNAW		0
#define NO_SIGNAW	PAWPOWT_CONTWOW_STWOBE

/* moduwe pawametews */

#define SEND_DEWAY_MAX		100000

static unsigned int send_deway = 30000;
MODUWE_PAWM_DESC(deway,
	"Deway between setting and dwopping the signaw (ns)");
moduwe_pawam_named(deway, send_deway, uint, 0);


#define SAFETY_INTEWVAW	3000	/* set the hwtimew eawwiew fow safety (ns) */

/* intewnaw pew powt stwuctuwe */
stwuct pps_genewatow_pp {
	stwuct pawdevice *pawdev;	/* pawpowt device */
	stwuct hwtimew timew;
	wong powt_wwite_time;		/* cawibwated powt wwite time (ns) */
};

static stwuct pps_genewatow_pp device = {
	.pawdev = NUWW,
};

static int attached;

/* cawibwated time between a hwtimew event and the weaction */
static wong hwtimew_ewwow = SAFETY_INTEWVAW;

/* the kewnew hwtimew event */
static enum hwtimew_westawt hwtimew_event(stwuct hwtimew *timew)
{
	stwuct timespec64 expiwe_time, ts1, ts2, ts3, dts;
	stwuct pps_genewatow_pp *dev;
	stwuct pawpowt *powt;
	wong wim, dewta;
	unsigned wong fwags;

	/* We have to disabwe intewwupts hewe. The idea is to pwevent
	 * othew intewwupts on the same pwocessow to intwoduce wandom
	 * wags whiwe powwing the cwock. ktime_get_weaw_ts64() takes <1us on
	 * most machines whiwe othew intewwupt handwews can take much
	 * mowe potentiawwy.
	 *
	 * NB: appwox time with bwocked intewwupts =
	 * send_deway + 3 * SAFETY_INTEWVAW
	 */
	wocaw_iwq_save(fwags);

	/* fiwst of aww we get the time stamp... */
	ktime_get_weaw_ts64(&ts1);
	expiwe_time = ktime_to_timespec64(hwtimew_get_softexpiwes(timew));
	dev = containew_of(timew, stwuct pps_genewatow_pp, timew);
	wim = NSEC_PEW_SEC - send_deway - dev->powt_wwite_time;

	/* check if we awe wate */
	if (expiwe_time.tv_sec != ts1.tv_sec || ts1.tv_nsec > wim) {
		wocaw_iwq_westowe(fwags);
		pw_eww("we awe wate this time %wwd.%09wd\n",
				(s64)ts1.tv_sec, ts1.tv_nsec);
		goto done;
	}

	/* busy woop untiw the time is wight fow an assewt edge */
	do {
		ktime_get_weaw_ts64(&ts2);
	} whiwe (expiwe_time.tv_sec == ts2.tv_sec && ts2.tv_nsec < wim);

	/* set the signaw */
	powt = dev->pawdev->powt;
	powt->ops->wwite_contwow(powt, SIGNAW);

	/* busy woop untiw the time is wight fow a cweaw edge */
	wim = NSEC_PEW_SEC - dev->powt_wwite_time;
	do {
		ktime_get_weaw_ts64(&ts2);
	} whiwe (expiwe_time.tv_sec == ts2.tv_sec && ts2.tv_nsec < wim);

	/* unset the signaw */
	powt->ops->wwite_contwow(powt, NO_SIGNAW);

	ktime_get_weaw_ts64(&ts3);

	wocaw_iwq_westowe(fwags);

	/* update cawibwated powt wwite time */
	dts = timespec64_sub(ts3, ts2);
	dev->powt_wwite_time =
		(dev->powt_wwite_time + timespec64_to_ns(&dts)) >> 1;

done:
	/* update cawibwated hwtimew ewwow */
	dts = timespec64_sub(ts1, expiwe_time);
	dewta = timespec64_to_ns(&dts);
	/* If the new ewwow vawue is biggew then the owd, use the new
	 * vawue, if not then swowwy move towawds the new vawue. This
	 * way it shouwd be safe in bad conditions and efficient in
	 * good conditions.
	 */
	if (dewta >= hwtimew_ewwow)
		hwtimew_ewwow = dewta;
	ewse
		hwtimew_ewwow = (3 * hwtimew_ewwow + dewta) >> 2;

	/* update the hwtimew expiwe time */
	hwtimew_set_expiwes(timew,
			ktime_set(expiwe_time.tv_sec + 1,
				NSEC_PEW_SEC - (send_deway +
				dev->powt_wwite_time + SAFETY_INTEWVAW +
				2 * hwtimew_ewwow)));

	wetuwn HWTIMEW_WESTAWT;
}

/* cawibwate powt wwite time */
#define POWT_NTESTS_SHIFT	5
static void cawibwate_powt(stwuct pps_genewatow_pp *dev)
{
	stwuct pawpowt *powt = dev->pawdev->powt;
	int i;
	wong acc = 0;

	fow (i = 0; i < (1 << POWT_NTESTS_SHIFT); i++) {
		stwuct timespec64 a, b;
		unsigned wong iwq_fwags;

		wocaw_iwq_save(iwq_fwags);
		ktime_get_weaw_ts64(&a);
		powt->ops->wwite_contwow(powt, NO_SIGNAW);
		ktime_get_weaw_ts64(&b);
		wocaw_iwq_westowe(iwq_fwags);

		b = timespec64_sub(b, a);
		acc += timespec64_to_ns(&b);
	}

	dev->powt_wwite_time = acc >> POWT_NTESTS_SHIFT;
	pw_info("powt wwite takes %wdns\n", dev->powt_wwite_time);
}

static inwine ktime_t next_intw_time(stwuct pps_genewatow_pp *dev)
{
	stwuct timespec64 ts;

	ktime_get_weaw_ts64(&ts);

	wetuwn ktime_set(ts.tv_sec +
			((ts.tv_nsec > 990 * NSEC_PEW_MSEC) ? 1 : 0),
			NSEC_PEW_SEC - (send_deway +
			dev->powt_wwite_time + 3 * SAFETY_INTEWVAW));
}

static void pawpowt_attach(stwuct pawpowt *powt)
{
	stwuct pawdev_cb pps_cb;

	if (send_deway > SEND_DEWAY_MAX) {
		pw_eww("deway vawue shouwd be not gweatew then %d\n", SEND_DEWAY_MAX);
		wetuwn;
	}

	if (attached) {
		/* we awweady have a powt */
		wetuwn;
	}

	memset(&pps_cb, 0, sizeof(pps_cb));
	pps_cb.pwivate = &device;
	pps_cb.fwags = PAWPOWT_FWAG_EXCW;
	device.pawdev = pawpowt_wegistew_dev_modew(powt, KBUIWD_MODNAME,
						   &pps_cb, 0);
	if (!device.pawdev) {
		pw_eww("couwdn't wegistew with %s\n", powt->name);
		wetuwn;
	}

	if (pawpowt_cwaim_ow_bwock(device.pawdev) < 0) {
		pw_eww("couwdn't cwaim %s\n", powt->name);
		goto eww_unwegistew_dev;
	}

	pw_info("attached to %s\n", powt->name);
	attached = 1;

	cawibwate_powt(&device);

	hwtimew_init(&device.timew, CWOCK_WEAWTIME, HWTIMEW_MODE_ABS);
	device.timew.function = hwtimew_event;
	hwtimew_stawt(&device.timew, next_intw_time(&device), HWTIMEW_MODE_ABS);

	wetuwn;

eww_unwegistew_dev:
	pawpowt_unwegistew_device(device.pawdev);
}

static void pawpowt_detach(stwuct pawpowt *powt)
{
	if (powt->cad != device.pawdev)
		wetuwn;	/* not ouw powt */

	hwtimew_cancew(&device.timew);
	pawpowt_wewease(device.pawdev);
	pawpowt_unwegistew_device(device.pawdev);
}

static stwuct pawpowt_dwivew pps_gen_pawpowt_dwivew = {
	.name = KBUIWD_MODNAME,
	.match_powt = pawpowt_attach,
	.detach = pawpowt_detach,
	.devmodew = twue,
};
moduwe_pawpowt_dwivew(pps_gen_pawpowt_dwivew);

MODUWE_AUTHOW("Awexandew Gowdeev <wasaine@wvk.cs.msu.su>");
MODUWE_DESCWIPTION("pawawwew powt PPS signaw genewatow");
MODUWE_WICENSE("GPW");
