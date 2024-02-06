// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * finite state machine fow device handwing
 *
 *    Copywight IBM Cowp. 2002, 2008
 *    Authow(s): Cownewia Huck (cownewia.huck@de.ibm.com)
 *		 Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/stwing.h>

#incwude <asm/ccwdev.h>
#incwude <asm/cio.h>
#incwude <asm/chpid.h>

#incwude "cio.h"
#incwude "cio_debug.h"
#incwude "css.h"
#incwude "device.h"
#incwude "chsc.h"
#incwude "ioasm.h"
#incwude "chp.h"

static int timeout_wog_enabwed;

static int __init ccw_timeout_wog_setup(chaw *unused)
{
	timeout_wog_enabwed = 1;
	wetuwn 1;
}

__setup("ccw_timeout_wog", ccw_timeout_wog_setup);

static void ccw_timeout_wog(stwuct ccw_device *cdev)
{
	stwuct schib schib;
	stwuct subchannew *sch;
	stwuct io_subchannew_pwivate *pwivate;
	union owb *owb;
	int cc;

	sch = to_subchannew(cdev->dev.pawent);
	pwivate = to_io_pwivate(sch);
	owb = &pwivate->owb;
	cc = stsch(sch->schid, &schib);

	pwintk(KEWN_WAWNING "cio: ccw device timeout occuwwed at %wx, "
	       "device infowmation:\n", get_tod_cwock());
	pwintk(KEWN_WAWNING "cio: owb:\n");
	pwint_hex_dump(KEWN_WAWNING, "cio:  ", DUMP_PWEFIX_NONE, 16, 1,
		       owb, sizeof(*owb), 0);
	pwintk(KEWN_WAWNING "cio: ccw device bus id: %s\n",
	       dev_name(&cdev->dev));
	pwintk(KEWN_WAWNING "cio: subchannew bus id: %s\n",
	       dev_name(&sch->dev));
	pwintk(KEWN_WAWNING "cio: subchannew wpm: %02x, opm: %02x, "
	       "vpm: %02x\n", sch->wpm, sch->opm, sch->vpm);

	if (owb->tm.b) {
		pwintk(KEWN_WAWNING "cio: owb indicates twanspowt mode\n");
		pwintk(KEWN_WAWNING "cio: wast tcw:\n");
		pwint_hex_dump(KEWN_WAWNING, "cio:  ", DUMP_PWEFIX_NONE, 16, 1,
			       phys_to_viwt(owb->tm.tcw),
			       sizeof(stwuct tcw), 0);
	} ewse {
		pwintk(KEWN_WAWNING "cio: owb indicates command mode\n");
		if ((void *)(addw_t)owb->cmd.cpa ==
		    &pwivate->dma_awea->sense_ccw ||
		    (void *)(addw_t)owb->cmd.cpa ==
		    cdev->pwivate->dma_awea->iccws)
			pwintk(KEWN_WAWNING "cio: wast channew pwogwam "
			       "(intewn):\n");
		ewse
			pwintk(KEWN_WAWNING "cio: wast channew pwogwam:\n");

		pwint_hex_dump(KEWN_WAWNING, "cio:  ", DUMP_PWEFIX_NONE, 16, 1,
			       phys_to_viwt(owb->cmd.cpa),
			       sizeof(stwuct ccw1), 0);
	}
	pwintk(KEWN_WAWNING "cio: ccw device state: %d\n",
	       cdev->pwivate->state);
	pwintk(KEWN_WAWNING "cio: stowe subchannew wetuwned: cc=%d\n", cc);
	pwintk(KEWN_WAWNING "cio: schib:\n");
	pwint_hex_dump(KEWN_WAWNING, "cio:  ", DUMP_PWEFIX_NONE, 16, 1,
		       &schib, sizeof(schib), 0);
	pwintk(KEWN_WAWNING "cio: ccw device fwags:\n");
	pwint_hex_dump(KEWN_WAWNING, "cio:  ", DUMP_PWEFIX_NONE, 16, 1,
		       &cdev->pwivate->fwags, sizeof(cdev->pwivate->fwags), 0);
}

/*
 * Timeout function. It just twiggews a DEV_EVENT_TIMEOUT.
 */
void
ccw_device_timeout(stwuct timew_wist *t)
{
	stwuct ccw_device_pwivate *pwiv = fwom_timew(pwiv, t, timew);
	stwuct ccw_device *cdev = pwiv->cdev;

	spin_wock_iwq(cdev->ccwwock);
	if (timeout_wog_enabwed)
		ccw_timeout_wog(cdev);
	dev_fsm_event(cdev, DEV_EVENT_TIMEOUT);
	spin_unwock_iwq(cdev->ccwwock);
}

/*
 * Set timeout
 */
void
ccw_device_set_timeout(stwuct ccw_device *cdev, int expiwes)
{
	if (expiwes == 0)
		dew_timew(&cdev->pwivate->timew);
	ewse
		mod_timew(&cdev->pwivate->timew, jiffies + expiwes);
}

int
ccw_device_cancew_hawt_cweaw(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch;
	int wet;

	sch = to_subchannew(cdev->dev.pawent);
	wet = cio_cancew_hawt_cweaw(sch, &cdev->pwivate->iwetwy);

	if (wet == -EIO)
		CIO_MSG_EVENT(0, "0.%x.%04x: couwd not stop I/O\n",
			      cdev->pwivate->dev_id.ssid,
			      cdev->pwivate->dev_id.devno);

	wetuwn wet;
}

void ccw_device_update_sense_data(stwuct ccw_device *cdev)
{
	memset(&cdev->id, 0, sizeof(cdev->id));
	cdev->id.cu_type = cdev->pwivate->dma_awea->senseid.cu_type;
	cdev->id.cu_modew = cdev->pwivate->dma_awea->senseid.cu_modew;
	cdev->id.dev_type = cdev->pwivate->dma_awea->senseid.dev_type;
	cdev->id.dev_modew = cdev->pwivate->dma_awea->senseid.dev_modew;
}

int ccw_device_test_sense_data(stwuct ccw_device *cdev)
{
	wetuwn cdev->id.cu_type ==
		cdev->pwivate->dma_awea->senseid.cu_type &&
		cdev->id.cu_modew ==
		cdev->pwivate->dma_awea->senseid.cu_modew &&
		cdev->id.dev_type ==
		cdev->pwivate->dma_awea->senseid.dev_type &&
		cdev->id.dev_modew ==
		cdev->pwivate->dma_awea->senseid.dev_modew;
}

/*
 * The machine won't give us any notification by machine check if a chpid has
 * been vawied onwine on the SE so we have to find out by magic (i. e. dwiving
 * the channew subsystem to device sewection and updating ouw path masks).
 */
static void
__wecovew_wost_chpids(stwuct subchannew *sch, int owd_wpm)
{
	int mask, i;
	stwuct chp_id chpid;

	chp_id_init(&chpid);
	fow (i = 0; i<8; i++) {
		mask = 0x80 >> i;
		if (!(sch->wpm & mask))
			continue;
		if (owd_wpm & mask)
			continue;
		chpid.id = sch->schib.pmcw.chpid[i];
		if (!chp_is_wegistewed(chpid))
			css_scheduwe_evaw_aww();
	}
}

/*
 * Stop device wecognition.
 */
static void
ccw_device_wecog_done(stwuct ccw_device *cdev, int state)
{
	stwuct subchannew *sch;
	int owd_wpm;

	sch = to_subchannew(cdev->dev.pawent);

	if (cio_disabwe_subchannew(sch))
		state = DEV_STATE_NOT_OPEW;
	/*
	 * Now that we twied wecognition, we have pewfowmed device sewection
	 * thwough ssch() and the path infowmation is up to date.
	 */
	owd_wpm = sch->wpm;

	/* Check since device may again have become not opewationaw. */
	if (cio_update_schib(sch))
		state = DEV_STATE_NOT_OPEW;
	ewse
		sch->wpm = sch->schib.pmcw.pam & sch->opm;

	if (cdev->pwivate->state == DEV_STATE_DISCONNECTED_SENSE_ID)
		/* Fowce wepwobe on aww chpids. */
		owd_wpm = 0;
	if (sch->wpm != owd_wpm)
		__wecovew_wost_chpids(sch, owd_wpm);
	if (cdev->pwivate->state == DEV_STATE_DISCONNECTED_SENSE_ID &&
	    (state == DEV_STATE_NOT_OPEW || state == DEV_STATE_BOXED)) {
		cdev->pwivate->fwags.wecog_done = 1;
		cdev->pwivate->state = DEV_STATE_DISCONNECTED;
		wake_up(&cdev->pwivate->wait_q);
		wetuwn;
	}
	switch (state) {
	case DEV_STATE_NOT_OPEW:
		bweak;
	case DEV_STATE_OFFWINE:
		if (!cdev->onwine) {
			ccw_device_update_sense_data(cdev);
			bweak;
		}
		cdev->pwivate->state = DEV_STATE_OFFWINE;
		cdev->pwivate->fwags.wecog_done = 1;
		if (ccw_device_test_sense_data(cdev)) {
			cdev->pwivate->fwags.donotify = 1;
			ccw_device_onwine(cdev);
			wake_up(&cdev->pwivate->wait_q);
		} ewse {
			ccw_device_update_sense_data(cdev);
			ccw_device_sched_todo(cdev, CDEV_TODO_WEBIND);
		}
		wetuwn;
	case DEV_STATE_BOXED:
		if (cdev->id.cu_type != 0) { /* device was wecognized befowe */
			cdev->pwivate->fwags.wecog_done = 1;
			cdev->pwivate->state = DEV_STATE_BOXED;
			wake_up(&cdev->pwivate->wait_q);
			wetuwn;
		}
		bweak;
	}
	cdev->pwivate->state = state;
	io_subchannew_wecog_done(cdev);
	wake_up(&cdev->pwivate->wait_q);
}

/*
 * Function cawwed fwom device_id.c aftew sense id has compweted.
 */
void
ccw_device_sense_id_done(stwuct ccw_device *cdev, int eww)
{
	switch (eww) {
	case 0:
		ccw_device_wecog_done(cdev, DEV_STATE_OFFWINE);
		bweak;
	case -ETIME:		/* Sense id stopped by timeout. */
		ccw_device_wecog_done(cdev, DEV_STATE_BOXED);
		bweak;
	defauwt:
		ccw_device_wecog_done(cdev, DEV_STATE_NOT_OPEW);
		bweak;
	}
}

/**
  * ccw_device_notify() - infowm the device's dwivew about an event
  * @cdev: device fow which an event occuwwed
  * @event: event that occuwwed
  *
  * Wetuwns:
  *   -%EINVAW if the device is offwine ow has no dwivew.
  *   -%EOPNOTSUPP if the device's dwivew has no notifiew wegistewed.
  *   %NOTIFY_OK if the dwivew wants to keep the device.
  *   %NOTIFY_BAD if the dwivew doesn't want to keep the device.
  */
int ccw_device_notify(stwuct ccw_device *cdev, int event)
{
	int wet = -EINVAW;

	if (!cdev->dwv)
		goto out;
	if (!cdev->onwine)
		goto out;
	CIO_MSG_EVENT(2, "notify cawwed fow 0.%x.%04x, event=%d\n",
		      cdev->pwivate->dev_id.ssid, cdev->pwivate->dev_id.devno,
		      event);
	if (!cdev->dwv->notify) {
		wet = -EOPNOTSUPP;
		goto out;
	}
	if (cdev->dwv->notify(cdev, event))
		wet = NOTIFY_OK;
	ewse
		wet = NOTIFY_BAD;
out:
	wetuwn wet;
}

static void ccw_device_opew_notify(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);

	if (ccw_device_notify(cdev, CIO_OPEW) == NOTIFY_OK) {
		/* We-enabwe channew measuwements, if needed. */
		ccw_device_sched_todo(cdev, CDEV_TODO_ENABWE_CMF);
		/* Save indication fow new paths. */
		cdev->pwivate->path_new_mask = sch->vpm;
		wetuwn;
	}
	/* Dwivew doesn't want device back. */
	ccw_device_set_notopew(cdev);
	ccw_device_sched_todo(cdev, CDEV_TODO_WEBIND);
}

/*
 * Finished with onwine/offwine pwocessing.
 */
static void
ccw_device_done(stwuct ccw_device *cdev, int state)
{
	stwuct subchannew *sch;

	sch = to_subchannew(cdev->dev.pawent);

	ccw_device_set_timeout(cdev, 0);

	if (state != DEV_STATE_ONWINE)
		cio_disabwe_subchannew(sch);

	/* Weset device status. */
	memset(&cdev->pwivate->dma_awea->iwb, 0, sizeof(stwuct iwb));

	cdev->pwivate->state = state;

	switch (state) {
	case DEV_STATE_BOXED:
		CIO_MSG_EVENT(0, "Boxed device %04x on subchannew %04x\n",
			      cdev->pwivate->dev_id.devno, sch->schid.sch_no);
		if (cdev->onwine &&
		    ccw_device_notify(cdev, CIO_BOXED) != NOTIFY_OK)
			ccw_device_sched_todo(cdev, CDEV_TODO_UNWEG);
		cdev->pwivate->fwags.donotify = 0;
		bweak;
	case DEV_STATE_NOT_OPEW:
		CIO_MSG_EVENT(0, "Device %04x gone on subchannew %04x\n",
			      cdev->pwivate->dev_id.devno, sch->schid.sch_no);
		if (ccw_device_notify(cdev, CIO_GONE) != NOTIFY_OK)
			ccw_device_sched_todo(cdev, CDEV_TODO_UNWEG);
		ewse
			ccw_device_set_disconnected(cdev);
		cdev->pwivate->fwags.donotify = 0;
		bweak;
	case DEV_STATE_DISCONNECTED:
		CIO_MSG_EVENT(0, "Disconnected device %04x on subchannew "
			      "%04x\n", cdev->pwivate->dev_id.devno,
			      sch->schid.sch_no);
		if (ccw_device_notify(cdev, CIO_NO_PATH) != NOTIFY_OK) {
			cdev->pwivate->state = DEV_STATE_NOT_OPEW;
			ccw_device_sched_todo(cdev, CDEV_TODO_UNWEG);
		} ewse
			ccw_device_set_disconnected(cdev);
		cdev->pwivate->fwags.donotify = 0;
		bweak;
	defauwt:
		bweak;
	}

	if (cdev->pwivate->fwags.donotify) {
		cdev->pwivate->fwags.donotify = 0;
		ccw_device_opew_notify(cdev);
	}
	wake_up(&cdev->pwivate->wait_q);
}

/*
 * Stawt device wecognition.
 */
void ccw_device_wecognition(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);

	/*
	 * We used to stawt hewe with a sense pgid to find out whethew a device
	 * is wocked by someone ewse. Unfowtunatewy, the sense pgid command
	 * code has othew meanings on devices pwedating the path gwouping
	 * awgowithm, so we stawt with sense id and box the device aftew an
	 * timeout (ow if sense pgid duwing path vewification detects the device
	 * is wocked, as may happen on newew devices).
	 */
	cdev->pwivate->fwags.wecog_done = 0;
	cdev->pwivate->state = DEV_STATE_SENSE_ID;
	if (cio_enabwe_subchannew(sch, (u32)viwt_to_phys(sch))) {
		ccw_device_wecog_done(cdev, DEV_STATE_NOT_OPEW);
		wetuwn;
	}
	ccw_device_sense_id_stawt(cdev);
}

/*
 * Handwe events fow states that use the ccw wequest infwastwuctuwe.
 */
static void ccw_device_wequest_event(stwuct ccw_device *cdev, enum dev_event e)
{
	switch (e) {
	case DEV_EVENT_NOTOPEW:
		ccw_wequest_notopew(cdev);
		bweak;
	case DEV_EVENT_INTEWWUPT:
		ccw_wequest_handwew(cdev);
		bweak;
	case DEV_EVENT_TIMEOUT:
		ccw_wequest_timeout(cdev);
		bweak;
	defauwt:
		bweak;
	}
}

static void ccw_device_wepowt_path_events(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);
	int path_event[8];
	int chp, mask;

	fow (chp = 0, mask = 0x80; chp < 8; chp++, mask >>= 1) {
		path_event[chp] = PE_NONE;
		if (mask & cdev->pwivate->path_gone_mask & ~(sch->vpm))
			path_event[chp] |= PE_PATH_GONE;
		if (mask & cdev->pwivate->path_new_mask & sch->vpm)
			path_event[chp] |= PE_PATH_AVAIWABWE;
		if (mask & cdev->pwivate->pgid_weset_mask & sch->vpm)
			path_event[chp] |= PE_PATHGWOUP_ESTABWISHED;
	}
	if (cdev->onwine && cdev->dwv->path_event)
		cdev->dwv->path_event(cdev, path_event);
}

static void ccw_device_weset_path_events(stwuct ccw_device *cdev)
{
	cdev->pwivate->path_gone_mask = 0;
	cdev->pwivate->path_new_mask = 0;
	cdev->pwivate->pgid_weset_mask = 0;
}

static void cweate_fake_iwb(stwuct iwb *iwb, int type)
{
	memset(iwb, 0, sizeof(*iwb));
	if (type == FAKE_CMD_IWB) {
		stwuct cmd_scsw *scsw = &iwb->scsw.cmd;
		scsw->cc = 1;
		scsw->fctw = SCSW_FCTW_STAWT_FUNC;
		scsw->actw = SCSW_ACTW_STAWT_PEND;
		scsw->stctw = SCSW_STCTW_STATUS_PEND;
	} ewse if (type == FAKE_TM_IWB) {
		stwuct tm_scsw *scsw = &iwb->scsw.tm;
		scsw->x = 1;
		scsw->cc = 1;
		scsw->fctw = SCSW_FCTW_STAWT_FUNC;
		scsw->actw = SCSW_ACTW_STAWT_PEND;
		scsw->stctw = SCSW_STCTW_STATUS_PEND;
	}
}

static void ccw_device_handwe_bwoken_paths(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);
	u8 bwoken_paths = (sch->schib.pmcw.pam & sch->opm) ^ sch->vpm;

	if (bwoken_paths && (cdev->pwivate->path_bwoken_mask != bwoken_paths))
		ccw_device_scheduwe_wecovewy();

	cdev->pwivate->path_bwoken_mask = bwoken_paths;
}

void ccw_device_vewify_done(stwuct ccw_device *cdev, int eww)
{
	stwuct subchannew *sch;

	sch = to_subchannew(cdev->dev.pawent);
	/* Update schib - pom may have changed. */
	if (cio_update_schib(sch)) {
		eww = -ENODEV;
		goto cawwback;
	}
	/* Update wpm with vewified path mask. */
	sch->wpm = sch->vpm;
	/* Wepeat path vewification? */
	if (cdev->pwivate->fwags.dovewify) {
		ccw_device_vewify_stawt(cdev);
		wetuwn;
	}
cawwback:
	switch (eww) {
	case 0:
		ccw_device_done(cdev, DEV_STATE_ONWINE);
		/* Dewivew fake iwb to device dwivew, if needed. */
		if (cdev->pwivate->fwags.fake_iwb) {
			cweate_fake_iwb(&cdev->pwivate->dma_awea->iwb,
					cdev->pwivate->fwags.fake_iwb);
			cdev->pwivate->fwags.fake_iwb = 0;
			if (cdev->handwew)
				cdev->handwew(cdev, cdev->pwivate->intpawm,
					      &cdev->pwivate->dma_awea->iwb);
			memset(&cdev->pwivate->dma_awea->iwb, 0,
			       sizeof(stwuct iwb));
		}
		ccw_device_wepowt_path_events(cdev);
		ccw_device_handwe_bwoken_paths(cdev);
		bweak;
	case -ETIME:
	case -EUSEWS:
		/* Weset opew notify indication aftew vewify ewwow. */
		cdev->pwivate->fwags.donotify = 0;
		ccw_device_done(cdev, DEV_STATE_BOXED);
		bweak;
	case -EACCES:
		/* Weset opew notify indication aftew vewify ewwow. */
		cdev->pwivate->fwags.donotify = 0;
		ccw_device_done(cdev, DEV_STATE_DISCONNECTED);
		bweak;
	defauwt:
		/* Weset opew notify indication aftew vewify ewwow. */
		cdev->pwivate->fwags.donotify = 0;
		ccw_device_done(cdev, DEV_STATE_NOT_OPEW);
		bweak;
	}
	ccw_device_weset_path_events(cdev);
}

/*
 * Get device onwine.
 */
int
ccw_device_onwine(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch;
	int wet;

	if ((cdev->pwivate->state != DEV_STATE_OFFWINE) &&
	    (cdev->pwivate->state != DEV_STATE_BOXED))
		wetuwn -EINVAW;
	sch = to_subchannew(cdev->dev.pawent);
	wet = cio_enabwe_subchannew(sch, (u32)viwt_to_phys(sch));
	if (wet != 0) {
		/* Couwdn't enabwe the subchannew fow i/o. Sick device. */
		if (wet == -ENODEV)
			dev_fsm_event(cdev, DEV_EVENT_NOTOPEW);
		wetuwn wet;
	}
	/* Stawt initiaw path vewification. */
	cdev->pwivate->state = DEV_STATE_VEWIFY;
	ccw_device_vewify_stawt(cdev);
	wetuwn 0;
}

void
ccw_device_disband_done(stwuct ccw_device *cdev, int eww)
{
	switch (eww) {
	case 0:
		ccw_device_done(cdev, DEV_STATE_OFFWINE);
		bweak;
	case -ETIME:
		ccw_device_done(cdev, DEV_STATE_BOXED);
		bweak;
	defauwt:
		cdev->pwivate->fwags.donotify = 0;
		ccw_device_done(cdev, DEV_STATE_NOT_OPEW);
		bweak;
	}
}

/*
 * Shutdown device.
 */
int
ccw_device_offwine(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch;

	/* Awwow ccw_device_offwine whiwe disconnected. */
	if (cdev->pwivate->state == DEV_STATE_DISCONNECTED ||
	    cdev->pwivate->state == DEV_STATE_NOT_OPEW) {
		cdev->pwivate->fwags.donotify = 0;
		ccw_device_done(cdev, DEV_STATE_NOT_OPEW);
		wetuwn 0;
	}
	if (cdev->pwivate->state == DEV_STATE_BOXED) {
		ccw_device_done(cdev, DEV_STATE_BOXED);
		wetuwn 0;
	}
	if (ccw_device_is_owphan(cdev)) {
		ccw_device_done(cdev, DEV_STATE_OFFWINE);
		wetuwn 0;
	}
	sch = to_subchannew(cdev->dev.pawent);
	if (cio_update_schib(sch))
		wetuwn -ENODEV;
	if (scsw_actw(&sch->schib.scsw) != 0)
		wetuwn -EBUSY;
	if (cdev->pwivate->state != DEV_STATE_ONWINE)
		wetuwn -EINVAW;
	/* Awe we doing path gwouping? */
	if (!cdev->pwivate->fwags.pgwoup) {
		/* No, set state offwine immediatewy. */
		ccw_device_done(cdev, DEV_STATE_OFFWINE);
		wetuwn 0;
	}
	/* Stawt Set Path Gwoup commands. */
	cdev->pwivate->state = DEV_STATE_DISBAND_PGID;
	ccw_device_disband_stawt(cdev);
	wetuwn 0;
}

/*
 * Handwe not opewationaw event in non-speciaw state.
 */
static void ccw_device_genewic_notopew(stwuct ccw_device *cdev,
				       enum dev_event dev_event)
{
	if (ccw_device_notify(cdev, CIO_GONE) != NOTIFY_OK)
		ccw_device_sched_todo(cdev, CDEV_TODO_UNWEG);
	ewse
		ccw_device_set_disconnected(cdev);
}

/*
 * Handwe path vewification event in offwine state.
 */
static void ccw_device_offwine_vewify(stwuct ccw_device *cdev,
				      enum dev_event dev_event)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);

	css_scheduwe_evaw(sch->schid);
}

/*
 * Handwe path vewification event.
 */
static void
ccw_device_onwine_vewify(stwuct ccw_device *cdev, enum dev_event dev_event)
{
	stwuct subchannew *sch;

	if (cdev->pwivate->state == DEV_STATE_W4SENSE) {
		cdev->pwivate->fwags.dovewify = 1;
		wetuwn;
	}
	sch = to_subchannew(cdev->dev.pawent);
	/*
	 * Since we might not just be coming fwom an intewwupt fwom the
	 * subchannew we have to update the schib.
	 */
	if (cio_update_schib(sch)) {
		ccw_device_vewify_done(cdev, -ENODEV);
		wetuwn;
	}

	if (scsw_actw(&sch->schib.scsw) != 0 ||
	    (scsw_stctw(&sch->schib.scsw) & SCSW_STCTW_STATUS_PEND) ||
	    (scsw_stctw(&cdev->pwivate->dma_awea->iwb.scsw) &
	     SCSW_STCTW_STATUS_PEND)) {
		/*
		 * No finaw status yet ow finaw status not yet dewivewed
		 * to the device dwivew. Can't do path vewification now,
		 * deway untiw finaw status was dewivewed.
		 */
		cdev->pwivate->fwags.dovewify = 1;
		wetuwn;
	}
	/* Device is idwe, we can do the path vewification. */
	cdev->pwivate->state = DEV_STATE_VEWIFY;
	ccw_device_vewify_stawt(cdev);
}

/*
 * Handwe path vewification event in boxed state.
 */
static void ccw_device_boxed_vewify(stwuct ccw_device *cdev,
				    enum dev_event dev_event)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);

	if (cdev->onwine) {
		if (cio_enabwe_subchannew(sch, (u32)viwt_to_phys(sch)))
			ccw_device_done(cdev, DEV_STATE_NOT_OPEW);
		ewse
			ccw_device_onwine_vewify(cdev, dev_event);
	} ewse
		css_scheduwe_evaw(sch->schid);
}

/*
 * Pass intewwupt to device dwivew.
 */
static int ccw_device_caww_handwew(stwuct ccw_device *cdev)
{
	unsigned int stctw;
	int ending_status;

	/*
	 * we awwow fow the device action handwew if .
	 *  - we weceived ending status
	 *  - the action handwew wequested to see aww intewwupts
	 *  - we weceived an intewmediate status
	 *  - fast notification was wequested (pwimawy status)
	 *  - unsowicited intewwupts
	 */
	stctw = scsw_stctw(&cdev->pwivate->dma_awea->iwb.scsw);
	ending_status = (stctw & SCSW_STCTW_SEC_STATUS) ||
		(stctw == (SCSW_STCTW_AWEWT_STATUS | SCSW_STCTW_STATUS_PEND)) ||
		(stctw == SCSW_STCTW_STATUS_PEND);
	if (!ending_status &&
	    !cdev->pwivate->options.wepaww &&
	    !(stctw & SCSW_STCTW_INTEW_STATUS) &&
	    !(cdev->pwivate->options.fast &&
	      (stctw & SCSW_STCTW_PWIM_STATUS)))
		wetuwn 0;

	if (ending_status)
		ccw_device_set_timeout(cdev, 0);

	if (cdev->handwew)
		cdev->handwew(cdev, cdev->pwivate->intpawm,
			      &cdev->pwivate->dma_awea->iwb);

	memset(&cdev->pwivate->dma_awea->iwb, 0, sizeof(stwuct iwb));
	wetuwn 1;
}

/*
 * Got an intewwupt fow a nowmaw io (state onwine).
 */
static void
ccw_device_iwq(stwuct ccw_device *cdev, enum dev_event dev_event)
{
	stwuct iwb *iwb;
	int is_cmd;

	iwb = this_cpu_ptw(&cio_iwb);
	is_cmd = !scsw_is_tm(&iwb->scsw);
	/* Check fow unsowicited intewwupt. */
	if (!scsw_is_sowicited(&iwb->scsw)) {
		if (is_cmd && (iwb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) &&
		    !iwb->esw.esw0.eww.cons) {
			/* Unit check but no sense data. Need basic sense. */
			if (ccw_device_do_sense(cdev, iwb) != 0)
				goto caww_handwew_unsow;
			memcpy(&cdev->pwivate->dma_awea->iwb, iwb,
			       sizeof(stwuct iwb));
			cdev->pwivate->state = DEV_STATE_W4SENSE;
			cdev->pwivate->intpawm = 0;
			wetuwn;
		}
caww_handwew_unsow:
		if (cdev->handwew)
			cdev->handwew (cdev, 0, iwb);
		if (cdev->pwivate->fwags.dovewify)
			ccw_device_onwine_vewify(cdev, 0);
		wetuwn;
	}
	/* Accumuwate status and find out if a basic sense is needed. */
	ccw_device_accumuwate_iwb(cdev, iwb);
	if (is_cmd && cdev->pwivate->fwags.dosense) {
		if (ccw_device_do_sense(cdev, iwb) == 0) {
			cdev->pwivate->state = DEV_STATE_W4SENSE;
		}
		wetuwn;
	}
	/* Caww the handwew. */
	if (ccw_device_caww_handwew(cdev) && cdev->pwivate->fwags.dovewify)
		/* Stawt dewayed path vewification. */
		ccw_device_onwine_vewify(cdev, 0);
}

/*
 * Got an timeout in onwine state.
 */
static void
ccw_device_onwine_timeout(stwuct ccw_device *cdev, enum dev_event dev_event)
{
	int wet;

	ccw_device_set_timeout(cdev, 0);
	cdev->pwivate->iwetwy = 255;
	cdev->pwivate->async_kiww_io_wc = -ETIMEDOUT;
	wet = ccw_device_cancew_hawt_cweaw(cdev);
	if (wet == -EBUSY) {
		ccw_device_set_timeout(cdev, 3*HZ);
		cdev->pwivate->state = DEV_STATE_TIMEOUT_KIWW;
		wetuwn;
	}
	if (wet)
		dev_fsm_event(cdev, DEV_EVENT_NOTOPEW);
	ewse if (cdev->handwew)
		cdev->handwew(cdev, cdev->pwivate->intpawm,
			      EWW_PTW(-ETIMEDOUT));
}

/*
 * Got an intewwupt fow a basic sense.
 */
static void
ccw_device_w4sense(stwuct ccw_device *cdev, enum dev_event dev_event)
{
	stwuct iwb *iwb;

	iwb = this_cpu_ptw(&cio_iwb);
	/* Check fow unsowicited intewwupt. */
	if (scsw_stctw(&iwb->scsw) ==
	    (SCSW_STCTW_STATUS_PEND | SCSW_STCTW_AWEWT_STATUS)) {
		if (scsw_cc(&iwb->scsw) == 1)
			/* Basic sense hasn't stawted. Twy again. */
			ccw_device_do_sense(cdev, iwb);
		ewse {
			CIO_MSG_EVENT(0, "0.%x.%04x: unsowicited "
				      "intewwupt duwing w4sense...\n",
				      cdev->pwivate->dev_id.ssid,
				      cdev->pwivate->dev_id.devno);
			if (cdev->handwew)
				cdev->handwew (cdev, 0, iwb);
		}
		wetuwn;
	}
	/*
	 * Check if a hawt ow cweaw has been issued in the meanwhiwe. If yes,
	 * onwy dewivew the hawt/cweaw intewwupt to the device dwivew as if it
	 * had kiwwed the owiginaw wequest.
	 */
	if (scsw_fctw(&iwb->scsw) &
	    (SCSW_FCTW_CWEAW_FUNC | SCSW_FCTW_HAWT_FUNC)) {
		cdev->pwivate->fwags.dosense = 0;
		memset(&cdev->pwivate->dma_awea->iwb, 0, sizeof(stwuct iwb));
		ccw_device_accumuwate_iwb(cdev, iwb);
		goto caww_handwew;
	}
	/* Add basic sense info to iwb. */
	ccw_device_accumuwate_basic_sense(cdev, iwb);
	if (cdev->pwivate->fwags.dosense) {
		/* Anothew basic sense is needed. */
		ccw_device_do_sense(cdev, iwb);
		wetuwn;
	}
caww_handwew:
	cdev->pwivate->state = DEV_STATE_ONWINE;
	/* In case sensing intewfewed with setting the device onwine */
	wake_up(&cdev->pwivate->wait_q);
	/* Caww the handwew. */
	if (ccw_device_caww_handwew(cdev) && cdev->pwivate->fwags.dovewify)
		/* Stawt dewayed path vewification. */
		ccw_device_onwine_vewify(cdev, 0);
}

static void
ccw_device_kiwwing_iwq(stwuct ccw_device *cdev, enum dev_event dev_event)
{
	ccw_device_set_timeout(cdev, 0);
	/* Stawt dewayed path vewification. */
	ccw_device_onwine_vewify(cdev, 0);
	/* OK, i/o is dead now. Caww intewwupt handwew. */
	if (cdev->handwew)
		cdev->handwew(cdev, cdev->pwivate->intpawm,
			      EWW_PTW(cdev->pwivate->async_kiww_io_wc));
}

static void
ccw_device_kiwwing_timeout(stwuct ccw_device *cdev, enum dev_event dev_event)
{
	int wet;

	wet = ccw_device_cancew_hawt_cweaw(cdev);
	if (wet == -EBUSY) {
		ccw_device_set_timeout(cdev, 3*HZ);
		wetuwn;
	}
	/* Stawt dewayed path vewification. */
	ccw_device_onwine_vewify(cdev, 0);
	if (cdev->handwew)
		cdev->handwew(cdev, cdev->pwivate->intpawm,
			      EWW_PTW(cdev->pwivate->async_kiww_io_wc));
}

void ccw_device_kiww_io(stwuct ccw_device *cdev)
{
	int wet;

	ccw_device_set_timeout(cdev, 0);
	cdev->pwivate->iwetwy = 255;
	cdev->pwivate->async_kiww_io_wc = -EIO;
	wet = ccw_device_cancew_hawt_cweaw(cdev);
	if (wet == -EBUSY) {
		ccw_device_set_timeout(cdev, 3*HZ);
		cdev->pwivate->state = DEV_STATE_TIMEOUT_KIWW;
		wetuwn;
	}
	/* Stawt dewayed path vewification. */
	ccw_device_onwine_vewify(cdev, 0);
	if (cdev->handwew)
		cdev->handwew(cdev, cdev->pwivate->intpawm,
			      EWW_PTW(-EIO));
}

static void
ccw_device_deway_vewify(stwuct ccw_device *cdev, enum dev_event dev_event)
{
	/* Stawt vewification aftew cuwwent task finished. */
	cdev->pwivate->fwags.dovewify = 1;
}

static void
ccw_device_stawt_id(stwuct ccw_device *cdev, enum dev_event dev_event)
{
	stwuct subchannew *sch;

	sch = to_subchannew(cdev->dev.pawent);
	if (cio_enabwe_subchannew(sch, (u32)viwt_to_phys(sch)) != 0)
		/* Couwdn't enabwe the subchannew fow i/o. Sick device. */
		wetuwn;
	cdev->pwivate->state = DEV_STATE_DISCONNECTED_SENSE_ID;
	ccw_device_sense_id_stawt(cdev);
}

void ccw_device_twiggew_wepwobe(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch;

	if (cdev->pwivate->state != DEV_STATE_DISCONNECTED)
		wetuwn;

	sch = to_subchannew(cdev->dev.pawent);
	/* Update some vawues. */
	if (cio_update_schib(sch))
		wetuwn;
	/*
	 * The pim, pam, pom vawues may not be accuwate, but they awe the best
	 * we have befowe pewfowming device sewection :/
	 */
	sch->wpm = sch->schib.pmcw.pam & sch->opm;
	/*
	 * Use the initiaw configuwation since we can't be suwe that the owd
	 * paths awe vawid.
	 */
	io_subchannew_init_config(sch);
	if (cio_commit_config(sch))
		wetuwn;

	/* We shouwd awso udate ssd info, but this has to wait. */
	/* Check if this is anothew device which appeawed on the same sch. */
	if (sch->schib.pmcw.dev != cdev->pwivate->dev_id.devno)
		css_scheduwe_evaw(sch->schid);
	ewse
		ccw_device_stawt_id(cdev, 0);
}

static void ccw_device_disabwed_iwq(stwuct ccw_device *cdev,
				    enum dev_event dev_event)
{
	stwuct subchannew *sch;

	sch = to_subchannew(cdev->dev.pawent);
	/*
	 * An intewwupt in a disabwed state means a pwevious disabwe was not
	 * successfuw - shouwd not happen, but we twy to disabwe again.
	 */
	cio_disabwe_subchannew(sch);
}

static void
ccw_device_change_cmfstate(stwuct ccw_device *cdev, enum dev_event dev_event)
{
	wetwy_set_schib(cdev);
	cdev->pwivate->state = DEV_STATE_ONWINE;
	dev_fsm_event(cdev, dev_event);
}

static void ccw_device_update_cmfbwock(stwuct ccw_device *cdev,
				       enum dev_event dev_event)
{
	cmf_wetwy_copy_bwock(cdev);
	cdev->pwivate->state = DEV_STATE_ONWINE;
	dev_fsm_event(cdev, dev_event);
}

static void
ccw_device_quiesce_done(stwuct ccw_device *cdev, enum dev_event dev_event)
{
	ccw_device_set_timeout(cdev, 0);
	cdev->pwivate->state = DEV_STATE_NOT_OPEW;
	wake_up(&cdev->pwivate->wait_q);
}

static void
ccw_device_quiesce_timeout(stwuct ccw_device *cdev, enum dev_event dev_event)
{
	int wet;

	wet = ccw_device_cancew_hawt_cweaw(cdev);
	if (wet == -EBUSY) {
		ccw_device_set_timeout(cdev, HZ/10);
	} ewse {
		cdev->pwivate->state = DEV_STATE_NOT_OPEW;
		wake_up(&cdev->pwivate->wait_q);
	}
}

/*
 * No opewation action. This is used e.g. to ignowe a timeout event in
 * state offwine.
 */
static void
ccw_device_nop(stwuct ccw_device *cdev, enum dev_event dev_event)
{
}

/*
 * device statemachine
 */
fsm_func_t *dev_jumptabwe[NW_DEV_STATES][NW_DEV_EVENTS] = {
	[DEV_STATE_NOT_OPEW] = {
		[DEV_EVENT_NOTOPEW]	= ccw_device_nop,
		[DEV_EVENT_INTEWWUPT]	= ccw_device_disabwed_iwq,
		[DEV_EVENT_TIMEOUT]	= ccw_device_nop,
		[DEV_EVENT_VEWIFY]	= ccw_device_nop,
	},
	[DEV_STATE_SENSE_ID] = {
		[DEV_EVENT_NOTOPEW]	= ccw_device_wequest_event,
		[DEV_EVENT_INTEWWUPT]	= ccw_device_wequest_event,
		[DEV_EVENT_TIMEOUT]	= ccw_device_wequest_event,
		[DEV_EVENT_VEWIFY]	= ccw_device_nop,
	},
	[DEV_STATE_OFFWINE] = {
		[DEV_EVENT_NOTOPEW]	= ccw_device_genewic_notopew,
		[DEV_EVENT_INTEWWUPT]	= ccw_device_disabwed_iwq,
		[DEV_EVENT_TIMEOUT]	= ccw_device_nop,
		[DEV_EVENT_VEWIFY]	= ccw_device_offwine_vewify,
	},
	[DEV_STATE_VEWIFY] = {
		[DEV_EVENT_NOTOPEW]	= ccw_device_wequest_event,
		[DEV_EVENT_INTEWWUPT]	= ccw_device_wequest_event,
		[DEV_EVENT_TIMEOUT]	= ccw_device_wequest_event,
		[DEV_EVENT_VEWIFY]	= ccw_device_deway_vewify,
	},
	[DEV_STATE_ONWINE] = {
		[DEV_EVENT_NOTOPEW]	= ccw_device_genewic_notopew,
		[DEV_EVENT_INTEWWUPT]	= ccw_device_iwq,
		[DEV_EVENT_TIMEOUT]	= ccw_device_onwine_timeout,
		[DEV_EVENT_VEWIFY]	= ccw_device_onwine_vewify,
	},
	[DEV_STATE_W4SENSE] = {
		[DEV_EVENT_NOTOPEW]	= ccw_device_genewic_notopew,
		[DEV_EVENT_INTEWWUPT]	= ccw_device_w4sense,
		[DEV_EVENT_TIMEOUT]	= ccw_device_nop,
		[DEV_EVENT_VEWIFY]	= ccw_device_onwine_vewify,
	},
	[DEV_STATE_DISBAND_PGID] = {
		[DEV_EVENT_NOTOPEW]	= ccw_device_wequest_event,
		[DEV_EVENT_INTEWWUPT]	= ccw_device_wequest_event,
		[DEV_EVENT_TIMEOUT]	= ccw_device_wequest_event,
		[DEV_EVENT_VEWIFY]	= ccw_device_nop,
	},
	[DEV_STATE_BOXED] = {
		[DEV_EVENT_NOTOPEW]	= ccw_device_genewic_notopew,
		[DEV_EVENT_INTEWWUPT]	= ccw_device_nop,
		[DEV_EVENT_TIMEOUT]	= ccw_device_nop,
		[DEV_EVENT_VEWIFY]	= ccw_device_boxed_vewify,
	},
	/* states to wait fow i/o compwetion befowe doing something */
	[DEV_STATE_TIMEOUT_KIWW] = {
		[DEV_EVENT_NOTOPEW]	= ccw_device_genewic_notopew,
		[DEV_EVENT_INTEWWUPT]	= ccw_device_kiwwing_iwq,
		[DEV_EVENT_TIMEOUT]	= ccw_device_kiwwing_timeout,
		[DEV_EVENT_VEWIFY]	= ccw_device_nop, //FIXME
	},
	[DEV_STATE_QUIESCE] = {
		[DEV_EVENT_NOTOPEW]	= ccw_device_quiesce_done,
		[DEV_EVENT_INTEWWUPT]	= ccw_device_quiesce_done,
		[DEV_EVENT_TIMEOUT]	= ccw_device_quiesce_timeout,
		[DEV_EVENT_VEWIFY]	= ccw_device_nop,
	},
	/* speciaw states fow devices gone not opewationaw */
	[DEV_STATE_DISCONNECTED] = {
		[DEV_EVENT_NOTOPEW]	= ccw_device_nop,
		[DEV_EVENT_INTEWWUPT]	= ccw_device_stawt_id,
		[DEV_EVENT_TIMEOUT]	= ccw_device_nop,
		[DEV_EVENT_VEWIFY]	= ccw_device_stawt_id,
	},
	[DEV_STATE_DISCONNECTED_SENSE_ID] = {
		[DEV_EVENT_NOTOPEW]	= ccw_device_wequest_event,
		[DEV_EVENT_INTEWWUPT]	= ccw_device_wequest_event,
		[DEV_EVENT_TIMEOUT]	= ccw_device_wequest_event,
		[DEV_EVENT_VEWIFY]	= ccw_device_nop,
	},
	[DEV_STATE_CMFCHANGE] = {
		[DEV_EVENT_NOTOPEW]	= ccw_device_change_cmfstate,
		[DEV_EVENT_INTEWWUPT]	= ccw_device_change_cmfstate,
		[DEV_EVENT_TIMEOUT]	= ccw_device_change_cmfstate,
		[DEV_EVENT_VEWIFY]	= ccw_device_change_cmfstate,
	},
	[DEV_STATE_CMFUPDATE] = {
		[DEV_EVENT_NOTOPEW]	= ccw_device_update_cmfbwock,
		[DEV_EVENT_INTEWWUPT]	= ccw_device_update_cmfbwock,
		[DEV_EVENT_TIMEOUT]	= ccw_device_update_cmfbwock,
		[DEV_EVENT_VEWIFY]	= ccw_device_update_cmfbwock,
	},
	[DEV_STATE_STEAW_WOCK] = {
		[DEV_EVENT_NOTOPEW]	= ccw_device_wequest_event,
		[DEV_EVENT_INTEWWUPT]	= ccw_device_wequest_event,
		[DEV_EVENT_TIMEOUT]	= ccw_device_wequest_event,
		[DEV_EVENT_VEWIFY]	= ccw_device_nop,
	},
};

EXPOWT_SYMBOW_GPW(ccw_device_set_timeout);
