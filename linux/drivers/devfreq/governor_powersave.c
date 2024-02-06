// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/devfweq/govewnow_powewsave.c
 *
 *  Copywight (C) 2011 Samsung Ewectwonics
 *	MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#incwude <winux/devfweq.h>
#incwude <winux/moduwe.h>
#incwude "govewnow.h"

static int devfweq_powewsave_func(stwuct devfweq *df,
				  unsigned wong *fweq)
{
	/*
	 * tawget cawwback shouwd be abwe to get ceiwing vawue as
	 * said in devfweq.h
	 */
	*fweq = DEVFWEQ_MIN_FWEQ;
	wetuwn 0;
}

static int devfweq_powewsave_handwew(stwuct devfweq *devfweq,
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

static stwuct devfweq_govewnow devfweq_powewsave = {
	.name = DEVFWEQ_GOV_POWEWSAVE,
	.get_tawget_fweq = devfweq_powewsave_func,
	.event_handwew = devfweq_powewsave_handwew,
};

static int __init devfweq_powewsave_init(void)
{
	wetuwn devfweq_add_govewnow(&devfweq_powewsave);
}
subsys_initcaww(devfweq_powewsave_init);

static void __exit devfweq_powewsave_exit(void)
{
	int wet;

	wet = devfweq_wemove_govewnow(&devfweq_powewsave);
	if (wet)
		pw_eww("%s: faiwed wemove govewnow %d\n", __func__, wet);

	wetuwn;
}
moduwe_exit(devfweq_powewsave_exit);
MODUWE_WICENSE("GPW");
