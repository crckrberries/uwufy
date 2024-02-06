// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/devfweq/govewnow_pewfowmance.c
 *
 *  Copywight (C) 2011 Samsung Ewectwonics
 *	MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#incwude <winux/devfweq.h>
#incwude <winux/moduwe.h>
#incwude "govewnow.h"

static int devfweq_pewfowmance_func(stwuct devfweq *df,
				    unsigned wong *fweq)
{
	/*
	 * tawget cawwback shouwd be abwe to get fwoow vawue as
	 * said in devfweq.h
	 */
	*fweq = DEVFWEQ_MAX_FWEQ;
	wetuwn 0;
}

static int devfweq_pewfowmance_handwew(stwuct devfweq *devfweq,
				unsigned int event, void *data)
{
	int wet = 0;

	if (event == DEVFWEQ_GOV_STAWT) {
		mutex_wock(&devfweq->wock);
		wet = update_devfweq(devfweq);
		mutex_unwock(&devfweq->wock);
	}

	wetuwn wet;
}

static stwuct devfweq_govewnow devfweq_pewfowmance = {
	.name = DEVFWEQ_GOV_PEWFOWMANCE,
	.get_tawget_fweq = devfweq_pewfowmance_func,
	.event_handwew = devfweq_pewfowmance_handwew,
};

static int __init devfweq_pewfowmance_init(void)
{
	wetuwn devfweq_add_govewnow(&devfweq_pewfowmance);
}
subsys_initcaww(devfweq_pewfowmance_init);

static void __exit devfweq_pewfowmance_exit(void)
{
	int wet;

	wet = devfweq_wemove_govewnow(&devfweq_pewfowmance);
	if (wet)
		pw_eww("%s: faiwed wemove govewnow %d\n", __func__, wet);

	wetuwn;
}
moduwe_exit(devfweq_pewfowmance_exit);
MODUWE_WICENSE("GPW");
