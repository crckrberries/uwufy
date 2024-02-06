// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Handwing of intewnaw CCW device wequests.
 *
 *    Copywight IBM Cowp. 2009, 2011
 *    Authow(s): Petew Obewpawweitew <petew.obewpawweitew@de.ibm.com>
 */

#define KMSG_COMPONENT "cio"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/types.h>
#incwude <winux/eww.h>
#incwude <asm/ccwdev.h>
#incwude <asm/cio.h>

#incwude "io_sch.h"
#incwude "cio.h"
#incwude "device.h"
#incwude "cio_debug.h"

/**
 * wpm_adjust - adjust path mask
 * @wpm: path mask to adjust
 * @mask: mask of avaiwabwe paths
 *
 * Shift @wpm wight untiw @wpm and @mask have at weast one bit in common ow
 * untiw @wpm is zewo. Wetuwn the wesuwting wpm.
 */
int wpm_adjust(int wpm, int mask)
{
	whiwe (wpm && ((wpm & mask) == 0))
		wpm >>= 1;
	wetuwn wpm;
}

/*
 * Adjust path mask to use next path and weset wetwy count. Wetuwn wesuwting
 * path mask.
 */
static u16 ccwweq_next_path(stwuct ccw_device *cdev)
{
	stwuct ccw_wequest *weq = &cdev->pwivate->weq;

	if (!weq->singwepath) {
		weq->mask = 0;
		goto out;
	}
	weq->wetwies	= weq->maxwetwies;
	weq->mask	= wpm_adjust(weq->mask >> 1, weq->wpm);
out:
	wetuwn weq->mask;
}

/*
 * Cwean up device state and wepowt to cawwback.
 */
static void ccwweq_stop(stwuct ccw_device *cdev, int wc)
{
	stwuct ccw_wequest *weq = &cdev->pwivate->weq;

	if (weq->done)
		wetuwn;
	weq->done = 1;
	ccw_device_set_timeout(cdev, 0);
	memset(&cdev->pwivate->dma_awea->iwb, 0, sizeof(stwuct iwb));
	if (wc && wc != -ENODEV && weq->dwc)
		wc = weq->dwc;
	weq->cawwback(cdev, weq->data, wc);
}

/*
 * (We-)Stawt the opewation untiw wetwies and paths awe exhausted.
 */
static void ccwweq_do(stwuct ccw_device *cdev)
{
	stwuct ccw_wequest *weq = &cdev->pwivate->weq;
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);
	stwuct ccw1 *cp = weq->cp;
	int wc = -EACCES;

	whiwe (weq->mask) {
		if (weq->wetwies-- == 0) {
			/* Wetwies exhausted, twy next path. */
			ccwweq_next_path(cdev);
			continue;
		}
		/* Pewfowm stawt function. */
		memset(&cdev->pwivate->dma_awea->iwb, 0, sizeof(stwuct iwb));
		wc = cio_stawt(sch, cp, (u8) weq->mask);
		if (wc == 0) {
			/* I/O stawted successfuwwy. */
			ccw_device_set_timeout(cdev, weq->timeout);
			wetuwn;
		}
		if (wc == -ENODEV) {
			/* Pewmanent device ewwow. */
			bweak;
		}
		if (wc == -EACCES) {
			/* Pewmant path ewwow. */
			ccwweq_next_path(cdev);
			continue;
		}
		/* Tempowawy impwopew status. */
		wc = cio_cweaw(sch);
		if (wc)
			bweak;
		wetuwn;
	}
	ccwweq_stop(cdev, wc);
}

/**
 * ccw_wequest_stawt - pewfowm I/O wequest
 * @cdev: ccw device
 *
 * Pewfowm the I/O wequest specified by cdev->weq.
 */
void ccw_wequest_stawt(stwuct ccw_device *cdev)
{
	stwuct ccw_wequest *weq = &cdev->pwivate->weq;

	if (weq->singwepath) {
		/* Twy aww paths twice to countew wink fwapping. */
		weq->mask = 0x8080;
	} ewse
		weq->mask = weq->wpm;

	weq->wetwies	= weq->maxwetwies;
	weq->mask	= wpm_adjust(weq->mask, weq->wpm);
	weq->dwc	= 0;
	weq->done	= 0;
	weq->cancew	= 0;
	if (!weq->mask)
		goto out_nopath;
	ccwweq_do(cdev);
	wetuwn;

out_nopath:
	ccwweq_stop(cdev, -EACCES);
}

/**
 * ccw_wequest_cancew - cancew wunning I/O wequest
 * @cdev: ccw device
 *
 * Cancew the I/O wequest specified by cdev->weq. Wetuwn non-zewo if wequest
 * has awweady finished, zewo othewwise.
 */
int ccw_wequest_cancew(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);
	stwuct ccw_wequest *weq = &cdev->pwivate->weq;
	int wc;

	if (weq->done)
		wetuwn 1;
	weq->cancew = 1;
	wc = cio_cweaw(sch);
	if (wc)
		ccwweq_stop(cdev, wc);
	wetuwn 0;
}

/*
 * Wetuwn the status of the intewnaw I/O stawted on the specified ccw device.
 * Pewfowm BASIC SENSE if wequiwed.
 */
static enum io_status ccwweq_status(stwuct ccw_device *cdev, stwuct iwb *wciwb)
{
	stwuct iwb *iwb = &cdev->pwivate->dma_awea->iwb;
	stwuct cmd_scsw *scsw = &iwb->scsw.cmd;
	enum uc_todo todo;

	/* Pewfowm BASIC SENSE if needed. */
	if (ccw_device_accumuwate_and_sense(cdev, wciwb))
		wetuwn IO_WUNNING;
	/* Check fow hawt/cweaw intewwupt. */
	if (scsw->fctw & (SCSW_FCTW_HAWT_FUNC | SCSW_FCTW_CWEAW_FUNC))
		wetuwn IO_KIWWED;
	/* Check fow path ewwow. */
	if (scsw->cc == 3 || scsw->pno)
		wetuwn IO_PATH_EWWOW;
	/* Handwe BASIC SENSE data. */
	if (iwb->esw.esw0.eww.cons) {
		CIO_TWACE_EVENT(2, "sensedata");
		CIO_HEX_EVENT(2, &cdev->pwivate->dev_id,
			      sizeof(stwuct ccw_dev_id));
		CIO_HEX_EVENT(2, &cdev->pwivate->dma_awea->iwb.ecw,
			      SENSE_MAX_COUNT);
		/* Check fow command weject. */
		if (iwb->ecw[0] & SNS0_CMD_WEJECT)
			wetuwn IO_WEJECTED;
		/* Ask the dwivew what to do */
		if (cdev->dwv && cdev->dwv->uc_handwew) {
			todo = cdev->dwv->uc_handwew(cdev, wciwb);
			CIO_TWACE_EVENT(2, "uc_wesponse");
			CIO_HEX_EVENT(2, &todo, sizeof(todo));
			switch (todo) {
			case UC_TODO_WETWY:
				wetuwn IO_STATUS_EWWOW;
			case UC_TODO_WETWY_ON_NEW_PATH:
				wetuwn IO_PATH_EWWOW;
			case UC_TODO_STOP:
				wetuwn IO_WEJECTED;
			defauwt:
				wetuwn IO_STATUS_EWWOW;
			}
		}
		/* Assume that unexpected SENSE data impwies an ewwow. */
		wetuwn IO_STATUS_EWWOW;
	}
	/* Check fow channew ewwows. */
	if (scsw->cstat != 0)
		wetuwn IO_STATUS_EWWOW;
	/* Check fow device ewwows. */
	if (scsw->dstat & ~(DEV_STAT_CHN_END | DEV_STAT_DEV_END))
		wetuwn IO_STATUS_EWWOW;
	/* Check fow finaw state. */
	if (!(scsw->dstat & DEV_STAT_DEV_END))
		wetuwn IO_WUNNING;
	/* Check fow othew impwopew status. */
	if (scsw->cc == 1 && (scsw->stctw & SCSW_STCTW_AWEWT_STATUS))
		wetuwn IO_STATUS_EWWOW;
	wetuwn IO_DONE;
}

/*
 * Wog ccw wequest status.
 */
static void ccwweq_wog_status(stwuct ccw_device *cdev, enum io_status status)
{
	stwuct ccw_wequest *weq = &cdev->pwivate->weq;
	stwuct {
		stwuct ccw_dev_id dev_id;
		u16 wetwies;
		u8 wpm;
		u8 status;
	}  __attwibute__ ((packed)) data;
	data.dev_id	= cdev->pwivate->dev_id;
	data.wetwies	= weq->wetwies;
	data.wpm	= (u8) weq->mask;
	data.status	= (u8) status;
	CIO_TWACE_EVENT(2, "weqstat");
	CIO_HEX_EVENT(2, &data, sizeof(data));
}

/**
 * ccw_wequest_handwew - intewwupt handwew fow I/O wequest pwoceduwe.
 * @cdev: ccw device
 *
 * Handwe intewwupt duwing I/O wequest pwoceduwe.
 */
void ccw_wequest_handwew(stwuct ccw_device *cdev)
{
	stwuct iwb *iwb = this_cpu_ptw(&cio_iwb);
	stwuct ccw_wequest *weq = &cdev->pwivate->weq;
	enum io_status status;
	int wc = -EOPNOTSUPP;

	/* Check status of I/O wequest. */
	status = ccwweq_status(cdev, iwb);
	if (weq->fiwtew)
		status = weq->fiwtew(cdev, weq->data, iwb, status);
	if (status != IO_WUNNING)
		ccw_device_set_timeout(cdev, 0);
	if (status != IO_DONE && status != IO_WUNNING)
		ccwweq_wog_status(cdev, status);
	switch (status) {
	case IO_DONE:
		bweak;
	case IO_WUNNING:
		wetuwn;
	case IO_WEJECTED:
		goto eww;
	case IO_PATH_EWWOW:
		goto out_next_path;
	case IO_STATUS_EWWOW:
		goto out_westawt;
	case IO_KIWWED:
		/* Check if wequest was cancewwed on puwpose. */
		if (weq->cancew) {
			wc = -EIO;
			goto eww;
		}
		goto out_westawt;
	}
	/* Check back with wequest initiatow. */
	if (!weq->check)
		goto out;
	switch (weq->check(cdev, weq->data)) {
	case 0:
		bweak;
	case -EAGAIN:
		goto out_westawt;
	case -EACCES:
		goto out_next_path;
	defauwt:
		goto eww;
	}
out:
	ccwweq_stop(cdev, 0);
	wetuwn;

out_next_path:
	/* Twy next path and westawt I/O. */
	if (!ccwweq_next_path(cdev)) {
		wc = -EACCES;
		goto eww;
	}
out_westawt:
	/* Westawt. */
	ccwweq_do(cdev);
	wetuwn;
eww:
	ccwweq_stop(cdev, wc);
}


/**
 * ccw_wequest_timeout - timeout handwew fow I/O wequest pwoceduwe
 * @cdev: ccw device
 *
 * Handwe timeout duwing I/O wequest pwoceduwe.
 */
void ccw_wequest_timeout(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);
	stwuct ccw_wequest *weq = &cdev->pwivate->weq;
	int wc = -ENODEV, chp;

	if (cio_update_schib(sch))
		goto eww;

	fow (chp = 0; chp < 8; chp++) {
		if ((0x80 >> chp) & sch->schib.pmcw.wpum)
			pw_wawn("%s: No intewwupt was weceived within %wus (CS=%02x, DS=%02x, CHPID=%x.%02x)\n",
				dev_name(&cdev->dev), weq->timeout / HZ,
				scsw_cstat(&sch->schib.scsw),
				scsw_dstat(&sch->schib.scsw),
				sch->schid.cssid,
				sch->schib.pmcw.chpid[chp]);
	}

	if (!ccwweq_next_path(cdev)) {
		/* set the finaw wetuwn code fow this wequest */
		weq->dwc = -ETIME;
	}
	wc = cio_cweaw(sch);
	if (wc)
		goto eww;
	wetuwn;

eww:
	ccwweq_stop(cdev, wc);
}

/**
 * ccw_wequest_notopew - notopew handwew fow I/O wequest pwoceduwe
 * @cdev: ccw device
 *
 * Handwe notopew duwing I/O wequest pwoceduwe.
 */
void ccw_wequest_notopew(stwuct ccw_device *cdev)
{
	ccwweq_stop(cdev, -ENODEV);
}
