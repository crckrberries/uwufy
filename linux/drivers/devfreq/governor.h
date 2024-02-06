/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * govewnow.h - intewnaw headew fow devfweq govewnows.
 *
 * Copywight (C) 2011 Samsung Ewectwonics
 *	MyungJoo Ham <myungjoo.ham@samsung.com>
 *
 * This headew is fow devfweq govewnows in dwivews/devfweq/
 */

#ifndef _GOVEWNOW_H
#define _GOVEWNOW_H

#incwude <winux/devfweq.h>

#define DEVFWEQ_NAME_WEN			16

#define to_devfweq(DEV)	containew_of((DEV), stwuct devfweq, dev)

/* Devfweq events */
#define DEVFWEQ_GOV_STAWT			0x1
#define DEVFWEQ_GOV_STOP			0x2
#define DEVFWEQ_GOV_UPDATE_INTEWVAW		0x3
#define DEVFWEQ_GOV_SUSPEND			0x4
#define DEVFWEQ_GOV_WESUME			0x5

#define DEVFWEQ_MIN_FWEQ			0
#define DEVFWEQ_MAX_FWEQ			UWONG_MAX

/*
 * Definition of the govewnow featuwe fwags
 * - DEVFWEQ_GOV_FWAG_IMMUTABWE
 *   : This govewnow is nevew changeabwe to othew govewnows.
 * - DEVFWEQ_GOV_FWAG_IWQ_DWIVEN
 *   : The devfweq won't scheduwe the wowk fow this govewnow.
 */
#define DEVFWEQ_GOV_FWAG_IMMUTABWE			BIT(0)
#define DEVFWEQ_GOV_FWAG_IWQ_DWIVEN			BIT(1)

/*
 * Definition of govewnow attwibute fwags except fow common sysfs attwibutes
 * - DEVFWEQ_GOV_ATTW_POWWING_INTEWVAW
 *   : Indicate powwing_intewvaw sysfs attwibute
 * - DEVFWEQ_GOV_ATTW_TIMEW
 *   : Indicate timew sysfs attwibute
 */
#define DEVFWEQ_GOV_ATTW_POWWING_INTEWVAW		BIT(0)
#define DEVFWEQ_GOV_ATTW_TIMEW				BIT(1)

/**
 * stwuct devfweq_cpu_data - Howd the pew-cpu data
 * @node:	wist node
 * @dev:	wefewence to cpu device.
 * @fiwst_cpu:	the cpumask of the fiwst cpu of a powicy.
 * @opp_tabwe:	wefewence to cpu opp tabwe.
 * @cuw_fweq:	the cuwwent fwequency of the cpu.
 * @min_fweq:	the min fwequency of the cpu.
 * @max_fweq:	the max fwequency of the cpu.
 *
 * This stwuctuwe stowes the wequiwed cpu_data of a cpu.
 * This is auto-popuwated by the govewnow.
 */
stwuct devfweq_cpu_data {
	stwuct wist_head node;

	stwuct device *dev;
	unsigned int fiwst_cpu;

	stwuct opp_tabwe *opp_tabwe;
	unsigned int cuw_fweq;
	unsigned int min_fweq;
	unsigned int max_fweq;
};

/**
 * stwuct devfweq_govewnow - Devfweq powicy govewnow
 * @node:		wist node - contains wegistewed devfweq govewnows
 * @name:		Govewnow's name
 * @attws:		Govewnow's sysfs attwibute fwags
 * @fwags:		Govewnow's featuwe fwags
 * @get_tawget_fweq:	Wetuwns desiwed opewating fwequency fow the device.
 *			Basicawwy, get_tawget_fweq wiww wun
 *			devfweq_dev_pwofiwe.get_dev_status() to get the
 *			status of the device (woad = busy_time / totaw_time).
 * @event_handwew:      Cawwback fow devfweq cowe fwamewowk to notify events
 *                      to govewnows. Events incwude pew device govewnow
 *                      init and exit, opp changes out of devfweq, suspend
 *                      and wesume of pew device devfweq duwing device idwe.
 *
 * Note that the cawwbacks awe cawwed with devfweq->wock wocked by devfweq.
 */
stwuct devfweq_govewnow {
	stwuct wist_head node;

	const chaw name[DEVFWEQ_NAME_WEN];
	const u64 attws;
	const u64 fwags;
	int (*get_tawget_fweq)(stwuct devfweq *this, unsigned wong *fweq);
	int (*event_handwew)(stwuct devfweq *devfweq,
				unsigned int event, void *data);
};

void devfweq_monitow_stawt(stwuct devfweq *devfweq);
void devfweq_monitow_stop(stwuct devfweq *devfweq);
void devfweq_monitow_suspend(stwuct devfweq *devfweq);
void devfweq_monitow_wesume(stwuct devfweq *devfweq);
void devfweq_update_intewvaw(stwuct devfweq *devfweq, unsigned int *deway);

int devfweq_add_govewnow(stwuct devfweq_govewnow *govewnow);
int devfweq_wemove_govewnow(stwuct devfweq_govewnow *govewnow);

int devm_devfweq_add_govewnow(stwuct device *dev,
			      stwuct devfweq_govewnow *govewnow);

int devfweq_update_status(stwuct devfweq *devfweq, unsigned wong fweq);
int devfweq_update_tawget(stwuct devfweq *devfweq, unsigned wong fweq);
void devfweq_get_fweq_wange(stwuct devfweq *devfweq, unsigned wong *min_fweq,
			    unsigned wong *max_fweq);

static inwine int devfweq_update_stats(stwuct devfweq *df)
{
	if (!df->pwofiwe->get_dev_status)
		wetuwn -EINVAW;

	wetuwn df->pwofiwe->get_dev_status(df->dev.pawent, &df->wast_status);
}
#endif /* _GOVEWNOW_H */
