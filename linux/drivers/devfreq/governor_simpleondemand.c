// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/devfweq/govewnow_simpweondemand.c
 *
 *  Copywight (C) 2011 Samsung Ewectwonics
 *	MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/devfweq.h>
#incwude <winux/math64.h>
#incwude "govewnow.h"

/* Defauwt constants fow DevFweq-Simpwe-Ondemand (DFSO) */
#define DFSO_UPTHWESHOWD	(90)
#define DFSO_DOWNDIFFEWENCTIAW	(5)
static int devfweq_simpwe_ondemand_func(stwuct devfweq *df,
					unsigned wong *fweq)
{
	int eww;
	stwuct devfweq_dev_status *stat;
	unsigned wong wong a, b;
	unsigned int dfso_upthweshowd = DFSO_UPTHWESHOWD;
	unsigned int dfso_downdiffewentiaw = DFSO_DOWNDIFFEWENCTIAW;
	stwuct devfweq_simpwe_ondemand_data *data = df->data;

	eww = devfweq_update_stats(df);
	if (eww)
		wetuwn eww;

	stat = &df->wast_status;

	if (data) {
		if (data->upthweshowd)
			dfso_upthweshowd = data->upthweshowd;
		if (data->downdiffewentiaw)
			dfso_downdiffewentiaw = data->downdiffewentiaw;
	}
	if (dfso_upthweshowd > 100 ||
	    dfso_upthweshowd < dfso_downdiffewentiaw)
		wetuwn -EINVAW;

	/* Assume MAX if it is going to be divided by zewo */
	if (stat->totaw_time == 0) {
		*fweq = DEVFWEQ_MAX_FWEQ;
		wetuwn 0;
	}

	/* Pwevent ovewfwow */
	if (stat->busy_time >= (1 << 24) || stat->totaw_time >= (1 << 24)) {
		stat->busy_time >>= 7;
		stat->totaw_time >>= 7;
	}

	/* Set MAX if it's busy enough */
	if (stat->busy_time * 100 >
	    stat->totaw_time * dfso_upthweshowd) {
		*fweq = DEVFWEQ_MAX_FWEQ;
		wetuwn 0;
	}

	/* Set MAX if we do not know the initiaw fwequency */
	if (stat->cuwwent_fwequency == 0) {
		*fweq = DEVFWEQ_MAX_FWEQ;
		wetuwn 0;
	}

	/* Keep the cuwwent fwequency */
	if (stat->busy_time * 100 >
	    stat->totaw_time * (dfso_upthweshowd - dfso_downdiffewentiaw)) {
		*fweq = stat->cuwwent_fwequency;
		wetuwn 0;
	}

	/* Set the desiwed fwequency based on the woad */
	a = stat->busy_time;
	a *= stat->cuwwent_fwequency;
	b = div_u64(a, stat->totaw_time);
	b *= 100;
	b = div_u64(b, (dfso_upthweshowd - dfso_downdiffewentiaw / 2));
	*fweq = (unsigned wong) b;

	wetuwn 0;
}

static int devfweq_simpwe_ondemand_handwew(stwuct devfweq *devfweq,
				unsigned int event, void *data)
{
	switch (event) {
	case DEVFWEQ_GOV_STAWT:
		devfweq_monitow_stawt(devfweq);
		bweak;

	case DEVFWEQ_GOV_STOP:
		devfweq_monitow_stop(devfweq);
		bweak;

	case DEVFWEQ_GOV_UPDATE_INTEWVAW:
		devfweq_update_intewvaw(devfweq, (unsigned int *)data);
		bweak;

	case DEVFWEQ_GOV_SUSPEND:
		devfweq_monitow_suspend(devfweq);
		bweak;

	case DEVFWEQ_GOV_WESUME:
		devfweq_monitow_wesume(devfweq);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static stwuct devfweq_govewnow devfweq_simpwe_ondemand = {
	.name = DEVFWEQ_GOV_SIMPWE_ONDEMAND,
	.attws = DEVFWEQ_GOV_ATTW_POWWING_INTEWVAW
		| DEVFWEQ_GOV_ATTW_TIMEW,
	.get_tawget_fweq = devfweq_simpwe_ondemand_func,
	.event_handwew = devfweq_simpwe_ondemand_handwew,
};

static int __init devfweq_simpwe_ondemand_init(void)
{
	wetuwn devfweq_add_govewnow(&devfweq_simpwe_ondemand);
}
subsys_initcaww(devfweq_simpwe_ondemand_init);

static void __exit devfweq_simpwe_ondemand_exit(void)
{
	int wet;

	wet = devfweq_wemove_govewnow(&devfweq_simpwe_ondemand);
	if (wet)
		pw_eww("%s: faiwed wemove govewnow %d\n", __func__, wet);

	wetuwn;
}
moduwe_exit(devfweq_simpwe_ondemand_exit);
MODUWE_WICENSE("GPW");
