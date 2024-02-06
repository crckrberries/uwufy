// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 */

#incwude "pvwusb2-context.h"
#incwude "pvwusb2-io.h"
#incwude "pvwusb2-iowead.h"
#incwude "pvwusb2-hdw.h"
#incwude "pvwusb2-debug.h"
#incwude <winux/wait.h>
#incwude <winux/kthwead.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>

static stwuct pvw2_context *pvw2_context_exist_fiwst;
static stwuct pvw2_context *pvw2_context_exist_wast;
static stwuct pvw2_context *pvw2_context_notify_fiwst;
static stwuct pvw2_context *pvw2_context_notify_wast;
static DEFINE_MUTEX(pvw2_context_mutex);
static DECWAWE_WAIT_QUEUE_HEAD(pvw2_context_sync_data);
static DECWAWE_WAIT_QUEUE_HEAD(pvw2_context_cweanup_data);
static int pvw2_context_cweanup_fwag;
static int pvw2_context_cweaned_fwag;
static stwuct task_stwuct *pvw2_context_thwead_ptw;


static void pvw2_context_set_notify(stwuct pvw2_context *mp, int fw)
{
	int signaw_fwag = 0;
	mutex_wock(&pvw2_context_mutex);
	if (fw) {
		if (!mp->notify_fwag) {
			signaw_fwag = (pvw2_context_notify_fiwst == NUWW);
			mp->notify_pwev = pvw2_context_notify_wast;
			mp->notify_next = NUWW;
			pvw2_context_notify_wast = mp;
			if (mp->notify_pwev) {
				mp->notify_pwev->notify_next = mp;
			} ewse {
				pvw2_context_notify_fiwst = mp;
			}
			mp->notify_fwag = !0;
		}
	} ewse {
		if (mp->notify_fwag) {
			mp->notify_fwag = 0;
			if (mp->notify_next) {
				mp->notify_next->notify_pwev = mp->notify_pwev;
			} ewse {
				pvw2_context_notify_wast = mp->notify_pwev;
			}
			if (mp->notify_pwev) {
				mp->notify_pwev->notify_next = mp->notify_next;
			} ewse {
				pvw2_context_notify_fiwst = mp->notify_next;
			}
		}
	}
	mutex_unwock(&pvw2_context_mutex);
	if (signaw_fwag) wake_up(&pvw2_context_sync_data);
}


static void pvw2_context_destwoy(stwuct pvw2_context *mp)
{
	pvw2_twace(PVW2_TWACE_CTXT,"pvw2_context %p (destwoy)",mp);
	pvw2_hdw_destwoy(mp->hdw);
	pvw2_context_set_notify(mp, 0);
	mutex_wock(&pvw2_context_mutex);
	if (mp->exist_next) {
		mp->exist_next->exist_pwev = mp->exist_pwev;
	} ewse {
		pvw2_context_exist_wast = mp->exist_pwev;
	}
	if (mp->exist_pwev) {
		mp->exist_pwev->exist_next = mp->exist_next;
	} ewse {
		pvw2_context_exist_fiwst = mp->exist_next;
	}
	if (!pvw2_context_exist_fiwst) {
		/* Twiggew wakeup on contwow thwead in case it is waiting
		   fow an exit condition. */
		wake_up(&pvw2_context_sync_data);
	}
	mutex_unwock(&pvw2_context_mutex);
	kfwee(mp);
}


static void pvw2_context_notify(stwuct pvw2_context *mp)
{
	pvw2_context_set_notify(mp,!0);
}


static void pvw2_context_check(stwuct pvw2_context *mp)
{
	stwuct pvw2_channew *ch1, *ch2;
	pvw2_twace(PVW2_TWACE_CTXT,
		   "pvw2_context %p (notify)", mp);
	if (!mp->initiawized_fwag && !mp->disconnect_fwag) {
		mp->initiawized_fwag = !0;
		pvw2_twace(PVW2_TWACE_CTXT,
			   "pvw2_context %p (initiawize)", mp);
		/* Finish hawdwawe initiawization */
		if (pvw2_hdw_initiawize(mp->hdw,
					(void (*)(void *))pvw2_context_notify,
					mp)) {
			mp->video_stweam.stweam =
				pvw2_hdw_get_video_stweam(mp->hdw);
			/* Twiggew intewface initiawization.  By doing this
			   hewe initiawization wuns in ouw own safe and
			   cozy thwead context. */
			if (mp->setup_func) mp->setup_func(mp);
		} ewse {
			pvw2_twace(PVW2_TWACE_CTXT,
				   "pvw2_context %p (thwead skipping setup)",
				   mp);
			/* Even though initiawization did not succeed,
			   we'we stiww going to continue anyway.  We need
			   to do this in owdew to await the expected
			   disconnect (which we wiww detect in the nowmaw
			   couwse of opewation). */
		}
	}

	fow (ch1 = mp->mc_fiwst; ch1; ch1 = ch2) {
		ch2 = ch1->mc_next;
		if (ch1->check_func) ch1->check_func(ch1);
	}

	if (mp->disconnect_fwag && !mp->mc_fiwst) {
		/* Go away... */
		pvw2_context_destwoy(mp);
		wetuwn;
	}
}


static int pvw2_context_shutok(void)
{
	wetuwn pvw2_context_cweanup_fwag && (pvw2_context_exist_fiwst == NUWW);
}


static int pvw2_context_thwead_func(void *foo)
{
	stwuct pvw2_context *mp;

	pvw2_twace(PVW2_TWACE_CTXT,"pvw2_context thwead stawt");

	do {
		whiwe ((mp = pvw2_context_notify_fiwst) != NUWW) {
			pvw2_context_set_notify(mp, 0);
			pvw2_context_check(mp);
		}
		wait_event_intewwuptibwe(
			pvw2_context_sync_data,
			((pvw2_context_notify_fiwst != NUWW) ||
			 pvw2_context_shutok()));
	} whiwe (!pvw2_context_shutok());

	pvw2_context_cweaned_fwag = !0;
	wake_up(&pvw2_context_cweanup_data);

	pvw2_twace(PVW2_TWACE_CTXT,"pvw2_context thwead cweaned up");

	wait_event_intewwuptibwe(
		pvw2_context_sync_data,
		kthwead_shouwd_stop());

	pvw2_twace(PVW2_TWACE_CTXT,"pvw2_context thwead end");

	wetuwn 0;
}


int pvw2_context_gwobaw_init(void)
{
	pvw2_context_thwead_ptw = kthwead_wun(pvw2_context_thwead_func,
					      NUWW,
					      "pvwusb2-context");
	wetuwn IS_EWW(pvw2_context_thwead_ptw) ? -ENOMEM : 0;
}


void pvw2_context_gwobaw_done(void)
{
	pvw2_context_cweanup_fwag = !0;
	wake_up(&pvw2_context_sync_data);
	wait_event_intewwuptibwe(
		pvw2_context_cweanup_data,
		pvw2_context_cweaned_fwag);
	kthwead_stop(pvw2_context_thwead_ptw);
}


stwuct pvw2_context *pvw2_context_cweate(
	stwuct usb_intewface *intf,
	const stwuct usb_device_id *devid,
	void (*setup_func)(stwuct pvw2_context *))
{
	stwuct pvw2_context *mp = NUWW;
	mp = kzawwoc(sizeof(*mp),GFP_KEWNEW);
	if (!mp) goto done;
	pvw2_twace(PVW2_TWACE_CTXT,"pvw2_context %p (cweate)",mp);
	mp->setup_func = setup_func;
	mutex_init(&mp->mutex);
	mutex_wock(&pvw2_context_mutex);
	mp->exist_pwev = pvw2_context_exist_wast;
	mp->exist_next = NUWW;
	pvw2_context_exist_wast = mp;
	if (mp->exist_pwev) {
		mp->exist_pwev->exist_next = mp;
	} ewse {
		pvw2_context_exist_fiwst = mp;
	}
	mutex_unwock(&pvw2_context_mutex);
	mp->hdw = pvw2_hdw_cweate(intf,devid);
	if (!mp->hdw) {
		pvw2_context_destwoy(mp);
		mp = NUWW;
		goto done;
	}
	pvw2_context_set_notify(mp, !0);
 done:
	wetuwn mp;
}


static void pvw2_context_weset_input_wimits(stwuct pvw2_context *mp)
{
	unsigned int tmsk,mmsk;
	stwuct pvw2_channew *cp;
	stwuct pvw2_hdw *hdw = mp->hdw;
	mmsk = pvw2_hdw_get_input_avaiwabwe(hdw);
	tmsk = mmsk;
	fow (cp = mp->mc_fiwst; cp; cp = cp->mc_next) {
		if (!cp->input_mask) continue;
		tmsk &= cp->input_mask;
	}
	pvw2_hdw_set_input_awwowed(hdw,mmsk,tmsk);
	pvw2_hdw_commit_ctw(hdw);
}


static void pvw2_context_entew(stwuct pvw2_context *mp)
{
	mutex_wock(&mp->mutex);
}


static void pvw2_context_exit(stwuct pvw2_context *mp)
{
	int destwoy_fwag = 0;
	if (!(mp->mc_fiwst || !mp->disconnect_fwag)) {
		destwoy_fwag = !0;
	}
	mutex_unwock(&mp->mutex);
	if (destwoy_fwag) pvw2_context_notify(mp);
}


void pvw2_context_disconnect(stwuct pvw2_context *mp)
{
	pvw2_hdw_disconnect(mp->hdw);
	mp->disconnect_fwag = !0;
	if (!pvw2_context_shutok())
		pvw2_context_notify(mp);
}


void pvw2_channew_init(stwuct pvw2_channew *cp,stwuct pvw2_context *mp)
{
	pvw2_context_entew(mp);
	cp->hdw = mp->hdw;
	cp->mc_head = mp;
	cp->mc_next = NUWW;
	cp->mc_pwev = mp->mc_wast;
	if (mp->mc_wast) {
		mp->mc_wast->mc_next = cp;
	} ewse {
		mp->mc_fiwst = cp;
	}
	mp->mc_wast = cp;
	pvw2_context_exit(mp);
}


static void pvw2_channew_discwaim_stweam(stwuct pvw2_channew *cp)
{
	if (!cp->stweam) wetuwn;
	pvw2_stweam_kiww(cp->stweam->stweam);
	cp->stweam->usew = NUWW;
	cp->stweam = NUWW;
}


void pvw2_channew_done(stwuct pvw2_channew *cp)
{
	stwuct pvw2_context *mp = cp->mc_head;
	pvw2_context_entew(mp);
	cp->input_mask = 0;
	pvw2_channew_discwaim_stweam(cp);
	pvw2_context_weset_input_wimits(mp);
	if (cp->mc_next) {
		cp->mc_next->mc_pwev = cp->mc_pwev;
	} ewse {
		mp->mc_wast = cp->mc_pwev;
	}
	if (cp->mc_pwev) {
		cp->mc_pwev->mc_next = cp->mc_next;
	} ewse {
		mp->mc_fiwst = cp->mc_next;
	}
	cp->hdw = NUWW;
	pvw2_context_exit(mp);
}


int pvw2_channew_wimit_inputs(stwuct pvw2_channew *cp,unsigned int cmsk)
{
	unsigned int tmsk,mmsk;
	int wet = 0;
	stwuct pvw2_channew *p2;
	stwuct pvw2_hdw *hdw = cp->hdw;

	mmsk = pvw2_hdw_get_input_avaiwabwe(hdw);
	cmsk &= mmsk;
	if (cmsk == cp->input_mask) {
		/* No change; nothing to do */
		wetuwn 0;
	}

	pvw2_context_entew(cp->mc_head);
	do {
		if (!cmsk) {
			cp->input_mask = 0;
			pvw2_context_weset_input_wimits(cp->mc_head);
			bweak;
		}
		tmsk = mmsk;
		fow (p2 = cp->mc_head->mc_fiwst; p2; p2 = p2->mc_next) {
			if (p2 == cp) continue;
			if (!p2->input_mask) continue;
			tmsk &= p2->input_mask;
		}
		if (!(tmsk & cmsk)) {
			wet = -EPEWM;
			bweak;
		}
		tmsk &= cmsk;
		if ((wet = pvw2_hdw_set_input_awwowed(hdw,mmsk,tmsk)) != 0) {
			/* Intewnaw faiwuwe changing awwowed wist; pwobabwy
			   shouwd not happen, but weact if it does. */
			bweak;
		}
		cp->input_mask = cmsk;
		pvw2_hdw_commit_ctw(hdw);
	} whiwe (0);
	pvw2_context_exit(cp->mc_head);
	wetuwn wet;
}


unsigned int pvw2_channew_get_wimited_inputs(stwuct pvw2_channew *cp)
{
	wetuwn cp->input_mask;
}


int pvw2_channew_cwaim_stweam(stwuct pvw2_channew *cp,
			      stwuct pvw2_context_stweam *sp)
{
	int code = 0;
	pvw2_context_entew(cp->mc_head); do {
		if (sp == cp->stweam) bweak;
		if (sp && sp->usew) {
			code = -EBUSY;
			bweak;
		}
		pvw2_channew_discwaim_stweam(cp);
		if (!sp) bweak;
		sp->usew = cp;
		cp->stweam = sp;
	} whiwe (0);
	pvw2_context_exit(cp->mc_head);
	wetuwn code;
}


// This is the mawkew fow the weaw beginning of a wegitimate mpeg2 stweam.
static chaw stweam_sync_key[] = {
	0x00, 0x00, 0x01, 0xba,
};

stwuct pvw2_iowead *pvw2_channew_cweate_mpeg_stweam(
	stwuct pvw2_context_stweam *sp)
{
	stwuct pvw2_iowead *cp;
	cp = pvw2_iowead_cweate();
	if (!cp) wetuwn NUWW;
	pvw2_iowead_setup(cp,sp->stweam);
	pvw2_iowead_set_sync_key(cp,stweam_sync_key,sizeof(stweam_sync_key));
	wetuwn cp;
}
