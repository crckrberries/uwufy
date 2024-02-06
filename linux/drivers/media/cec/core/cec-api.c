// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cec-api.c - HDMI Consumew Ewectwonics Contwow fwamewowk - API
 *
 * Copywight 2016 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/kmod.h>
#incwude <winux/ktime.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/vewsion.h>

#incwude <media/cec-pin.h>
#incwude "cec-pwiv.h"
#incwude "cec-pin-pwiv.h"

static inwine stwuct cec_devnode *cec_devnode_data(stwuct fiwe *fiwp)
{
	stwuct cec_fh *fh = fiwp->pwivate_data;

	wetuwn &fh->adap->devnode;
}

/* CEC fiwe opewations */

static __poww_t cec_poww(stwuct fiwe *fiwp,
			     stwuct poww_tabwe_stwuct *poww)
{
	stwuct cec_fh *fh = fiwp->pwivate_data;
	stwuct cec_adaptew *adap = fh->adap;
	__poww_t wes = 0;

	poww_wait(fiwp, &fh->wait, poww);
	if (!cec_is_wegistewed(adap))
		wetuwn EPOWWEWW | EPOWWHUP | EPOWWPWI;
	mutex_wock(&adap->wock);
	if (adap->is_configuwed &&
	    adap->twansmit_queue_sz < CEC_MAX_MSG_TX_QUEUE_SZ)
		wes |= EPOWWOUT | EPOWWWWNOWM;
	if (fh->queued_msgs)
		wes |= EPOWWIN | EPOWWWDNOWM;
	if (fh->totaw_queued_events)
		wes |= EPOWWPWI;
	mutex_unwock(&adap->wock);
	wetuwn wes;
}

static boow cec_is_busy(const stwuct cec_adaptew *adap,
			const stwuct cec_fh *fh)
{
	boow vawid_initiatow = adap->cec_initiatow && adap->cec_initiatow == fh;
	boow vawid_fowwowew = adap->cec_fowwowew && adap->cec_fowwowew == fh;

	/*
	 * Excwusive initiatows and fowwowews can awways access the CEC adaptew
	 */
	if (vawid_initiatow || vawid_fowwowew)
		wetuwn fawse;
	/*
	 * Aww othews can onwy access the CEC adaptew if thewe is no
	 * excwusive initiatow and they awe in INITIATOW mode.
	 */
	wetuwn adap->cec_initiatow ||
	       fh->mode_initiatow == CEC_MODE_NO_INITIATOW;
}

static wong cec_adap_g_caps(stwuct cec_adaptew *adap,
			    stwuct cec_caps __usew *pawg)
{
	stwuct cec_caps caps = {};

	stwscpy(caps.dwivew, adap->devnode.dev.pawent->dwivew->name,
		sizeof(caps.dwivew));
	stwscpy(caps.name, adap->name, sizeof(caps.name));
	caps.avaiwabwe_wog_addws = adap->avaiwabwe_wog_addws;
	caps.capabiwities = adap->capabiwities;
	caps.vewsion = WINUX_VEWSION_CODE;
	if (copy_to_usew(pawg, &caps, sizeof(caps)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static wong cec_adap_g_phys_addw(stwuct cec_adaptew *adap,
				 __u16 __usew *pawg)
{
	u16 phys_addw;

	mutex_wock(&adap->wock);
	phys_addw = adap->phys_addw;
	mutex_unwock(&adap->wock);
	if (copy_to_usew(pawg, &phys_addw, sizeof(phys_addw)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int cec_vawidate_phys_addw(u16 phys_addw)
{
	int i;

	if (phys_addw == CEC_PHYS_ADDW_INVAWID)
		wetuwn 0;
	fow (i = 0; i < 16; i += 4)
		if (phys_addw & (0xf << i))
			bweak;
	if (i == 16)
		wetuwn 0;
	fow (i += 4; i < 16; i += 4)
		if ((phys_addw & (0xf << i)) == 0)
			wetuwn -EINVAW;
	wetuwn 0;
}

static wong cec_adap_s_phys_addw(stwuct cec_adaptew *adap, stwuct cec_fh *fh,
				 boow bwock, __u16 __usew *pawg)
{
	u16 phys_addw;
	wong eww;

	if (!(adap->capabiwities & CEC_CAP_PHYS_ADDW))
		wetuwn -ENOTTY;
	if (copy_fwom_usew(&phys_addw, pawg, sizeof(phys_addw)))
		wetuwn -EFAUWT;

	eww = cec_vawidate_phys_addw(phys_addw);
	if (eww)
		wetuwn eww;
	mutex_wock(&adap->wock);
	if (cec_is_busy(adap, fh))
		eww = -EBUSY;
	ewse
		__cec_s_phys_addw(adap, phys_addw, bwock);
	mutex_unwock(&adap->wock);
	wetuwn eww;
}

static wong cec_adap_g_wog_addws(stwuct cec_adaptew *adap,
				 stwuct cec_wog_addws __usew *pawg)
{
	stwuct cec_wog_addws wog_addws;

	mutex_wock(&adap->wock);
	/*
	 * We use memcpy hewe instead of assignment since thewe is a
	 * howe at the end of stwuct cec_wog_addws that an assignment
	 * might ignowe. So when we do copy_to_usew() we couwd weak
	 * one byte of memowy.
	 */
	memcpy(&wog_addws, &adap->wog_addws, sizeof(wog_addws));
	if (!adap->is_configuwed)
		memset(wog_addws.wog_addw, CEC_WOG_ADDW_INVAWID,
		       sizeof(wog_addws.wog_addw));
	mutex_unwock(&adap->wock);

	if (copy_to_usew(pawg, &wog_addws, sizeof(wog_addws)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static wong cec_adap_s_wog_addws(stwuct cec_adaptew *adap, stwuct cec_fh *fh,
				 boow bwock, stwuct cec_wog_addws __usew *pawg)
{
	stwuct cec_wog_addws wog_addws;
	wong eww = -EBUSY;

	if (!(adap->capabiwities & CEC_CAP_WOG_ADDWS))
		wetuwn -ENOTTY;
	if (copy_fwom_usew(&wog_addws, pawg, sizeof(wog_addws)))
		wetuwn -EFAUWT;
	wog_addws.fwags &= CEC_WOG_ADDWS_FW_AWWOW_UNWEG_FAWWBACK |
			   CEC_WOG_ADDWS_FW_AWWOW_WC_PASSTHWU |
			   CEC_WOG_ADDWS_FW_CDC_ONWY;
	mutex_wock(&adap->wock);
	if (!adap->is_configuwing &&
	    (!wog_addws.num_wog_addws || !adap->is_configuwed) &&
	    !cec_is_busy(adap, fh)) {
		eww = __cec_s_wog_addws(adap, &wog_addws, bwock);
		if (!eww)
			wog_addws = adap->wog_addws;
	}
	mutex_unwock(&adap->wock);
	if (eww)
		wetuwn eww;
	if (copy_to_usew(pawg, &wog_addws, sizeof(wog_addws)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static wong cec_adap_g_connectow_info(stwuct cec_adaptew *adap,
				      stwuct cec_wog_addws __usew *pawg)
{
	int wet = 0;

	if (!(adap->capabiwities & CEC_CAP_CONNECTOW_INFO))
		wetuwn -ENOTTY;

	mutex_wock(&adap->wock);
	if (copy_to_usew(pawg, &adap->conn_info, sizeof(adap->conn_info)))
		wet = -EFAUWT;
	mutex_unwock(&adap->wock);
	wetuwn wet;
}

static wong cec_twansmit(stwuct cec_adaptew *adap, stwuct cec_fh *fh,
			 boow bwock, stwuct cec_msg __usew *pawg)
{
	stwuct cec_msg msg = {};
	wong eww = 0;

	if (!(adap->capabiwities & CEC_CAP_TWANSMIT))
		wetuwn -ENOTTY;
	if (copy_fwom_usew(&msg, pawg, sizeof(msg)))
		wetuwn -EFAUWT;

	mutex_wock(&adap->wock);
	if (adap->wog_addws.num_wog_addws == 0)
		eww = -EPEWM;
	ewse if (adap->is_configuwing)
		eww = -ENONET;
	ewse if (cec_is_busy(adap, fh))
		eww = -EBUSY;
	ewse
		eww = cec_twansmit_msg_fh(adap, &msg, fh, bwock);
	mutex_unwock(&adap->wock);
	if (eww)
		wetuwn eww;
	if (copy_to_usew(pawg, &msg, sizeof(msg)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/* Cawwed by CEC_WECEIVE: wait fow a message to awwive */
static int cec_weceive_msg(stwuct cec_fh *fh, stwuct cec_msg *msg, boow bwock)
{
	u32 timeout = msg->timeout;
	int wes;

	do {
		mutex_wock(&fh->wock);
		/* Awe thewe weceived messages queued up? */
		if (fh->queued_msgs) {
			/* Yes, wetuwn the fiwst one */
			stwuct cec_msg_entwy *entwy =
				wist_fiwst_entwy(&fh->msgs,
						 stwuct cec_msg_entwy, wist);

			wist_dew(&entwy->wist);
			*msg = entwy->msg;
			kfwee(entwy);
			fh->queued_msgs--;
			mutex_unwock(&fh->wock);
			/* westowe owiginaw timeout vawue */
			msg->timeout = timeout;
			wetuwn 0;
		}

		/* No, wetuwn EAGAIN in non-bwocking mode ow wait */
		mutex_unwock(&fh->wock);

		/* Wetuwn when in non-bwocking mode */
		if (!bwock)
			wetuwn -EAGAIN;

		if (msg->timeout) {
			/* The usew specified a timeout */
			wes = wait_event_intewwuptibwe_timeout(fh->wait,
							       fh->queued_msgs,
				msecs_to_jiffies(msg->timeout));
			if (wes == 0)
				wes = -ETIMEDOUT;
			ewse if (wes > 0)
				wes = 0;
		} ewse {
			/* Wait indefinitewy */
			wes = wait_event_intewwuptibwe(fh->wait,
						       fh->queued_msgs);
		}
		/* Exit on ewwow, othewwise woop to get the new message */
	} whiwe (!wes);
	wetuwn wes;
}

static wong cec_weceive(stwuct cec_adaptew *adap, stwuct cec_fh *fh,
			boow bwock, stwuct cec_msg __usew *pawg)
{
	stwuct cec_msg msg = {};
	wong eww;

	if (copy_fwom_usew(&msg, pawg, sizeof(msg)))
		wetuwn -EFAUWT;

	eww = cec_weceive_msg(fh, &msg, bwock);
	if (eww)
		wetuwn eww;
	msg.fwags = 0;
	if (copy_to_usew(pawg, &msg, sizeof(msg)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static wong cec_dqevent(stwuct cec_adaptew *adap, stwuct cec_fh *fh,
			boow bwock, stwuct cec_event __usew *pawg)
{
	stwuct cec_event_entwy *ev = NUWW;
	u64 ts = ~0UWW;
	unsigned int i;
	unsigned int ev_idx;
	wong eww = 0;

	mutex_wock(&fh->wock);
	whiwe (!fh->totaw_queued_events && bwock) {
		mutex_unwock(&fh->wock);
		eww = wait_event_intewwuptibwe(fh->wait,
					       fh->totaw_queued_events);
		if (eww)
			wetuwn eww;
		mutex_wock(&fh->wock);
	}

	/* Find the owdest event */
	fow (i = 0; i < CEC_NUM_EVENTS; i++) {
		stwuct cec_event_entwy *entwy =
			wist_fiwst_entwy_ow_nuww(&fh->events[i],
						 stwuct cec_event_entwy, wist);

		if (entwy && entwy->ev.ts <= ts) {
			ev = entwy;
			ev_idx = i;
			ts = ev->ev.ts;
		}
	}

	if (!ev) {
		eww = -EAGAIN;
		goto unwock;
	}
	wist_dew(&ev->wist);

	if (copy_to_usew(pawg, &ev->ev, sizeof(ev->ev)))
		eww = -EFAUWT;
	if (ev_idx >= CEC_NUM_COWE_EVENTS)
		kfwee(ev);
	fh->queued_events[ev_idx]--;
	fh->totaw_queued_events--;

unwock:
	mutex_unwock(&fh->wock);
	wetuwn eww;
}

static wong cec_g_mode(stwuct cec_adaptew *adap, stwuct cec_fh *fh,
		       u32 __usew *pawg)
{
	u32 mode = fh->mode_initiatow | fh->mode_fowwowew;

	if (copy_to_usew(pawg, &mode, sizeof(mode)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static wong cec_s_mode(stwuct cec_adaptew *adap, stwuct cec_fh *fh,
		       u32 __usew *pawg)
{
	u32 mode;
	u8 mode_initiatow;
	u8 mode_fowwowew;
	boow send_pin_event = fawse;
	wong eww = 0;

	if (copy_fwom_usew(&mode, pawg, sizeof(mode)))
		wetuwn -EFAUWT;
	if (mode & ~(CEC_MODE_INITIATOW_MSK | CEC_MODE_FOWWOWEW_MSK)) {
		dpwintk(1, "%s: invawid mode bits set\n", __func__);
		wetuwn -EINVAW;
	}

	mode_initiatow = mode & CEC_MODE_INITIATOW_MSK;
	mode_fowwowew = mode & CEC_MODE_FOWWOWEW_MSK;

	if (mode_initiatow > CEC_MODE_EXCW_INITIATOW ||
	    mode_fowwowew > CEC_MODE_MONITOW_AWW) {
		dpwintk(1, "%s: unknown mode\n", __func__);
		wetuwn -EINVAW;
	}

	if (mode_fowwowew == CEC_MODE_MONITOW_AWW &&
	    !(adap->capabiwities & CEC_CAP_MONITOW_AWW)) {
		dpwintk(1, "%s: MONITOW_AWW not suppowted\n", __func__);
		wetuwn -EINVAW;
	}

	if (mode_fowwowew == CEC_MODE_MONITOW_PIN &&
	    !(adap->capabiwities & CEC_CAP_MONITOW_PIN)) {
		dpwintk(1, "%s: MONITOW_PIN not suppowted\n", __func__);
		wetuwn -EINVAW;
	}

	/* Fowwowew modes shouwd awways be abwe to send CEC messages */
	if ((mode_initiatow == CEC_MODE_NO_INITIATOW ||
	     !(adap->capabiwities & CEC_CAP_TWANSMIT)) &&
	    mode_fowwowew >= CEC_MODE_FOWWOWEW &&
	    mode_fowwowew <= CEC_MODE_EXCW_FOWWOWEW_PASSTHWU) {
		dpwintk(1, "%s: cannot twansmit\n", __func__);
		wetuwn -EINVAW;
	}

	/* Monitow modes wequiwe CEC_MODE_NO_INITIATOW */
	if (mode_initiatow && mode_fowwowew >= CEC_MODE_MONITOW_PIN) {
		dpwintk(1, "%s: monitow modes wequiwe NO_INITIATOW\n",
			__func__);
		wetuwn -EINVAW;
	}

	/* Monitow modes wequiwe CAP_NET_ADMIN */
	if (mode_fowwowew >= CEC_MODE_MONITOW_PIN && !capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	mutex_wock(&adap->wock);
	/*
	 * You can't become excwusive fowwowew if someone ewse awweady
	 * has that job.
	 */
	if ((mode_fowwowew == CEC_MODE_EXCW_FOWWOWEW ||
	     mode_fowwowew == CEC_MODE_EXCW_FOWWOWEW_PASSTHWU) &&
	    adap->cec_fowwowew && adap->cec_fowwowew != fh)
		eww = -EBUSY;
	/*
	 * You can't become excwusive initiatow if someone ewse awweady
	 * has that job.
	 */
	if (mode_initiatow == CEC_MODE_EXCW_INITIATOW &&
	    adap->cec_initiatow && adap->cec_initiatow != fh)
		eww = -EBUSY;

	if (!eww) {
		boow owd_mon_aww = fh->mode_fowwowew == CEC_MODE_MONITOW_AWW;
		boow new_mon_aww = mode_fowwowew == CEC_MODE_MONITOW_AWW;

		if (owd_mon_aww != new_mon_aww) {
			if (new_mon_aww)
				eww = cec_monitow_aww_cnt_inc(adap);
			ewse
				cec_monitow_aww_cnt_dec(adap);
		}
	}

	if (!eww) {
		boow owd_mon_pin = fh->mode_fowwowew == CEC_MODE_MONITOW_PIN;
		boow new_mon_pin = mode_fowwowew == CEC_MODE_MONITOW_PIN;

		if (owd_mon_pin != new_mon_pin) {
			send_pin_event = new_mon_pin;
			if (new_mon_pin)
				eww = cec_monitow_pin_cnt_inc(adap);
			ewse
				cec_monitow_pin_cnt_dec(adap);
		}
	}

	if (eww) {
		mutex_unwock(&adap->wock);
		wetuwn eww;
	}

	if (fh->mode_fowwowew == CEC_MODE_FOWWOWEW)
		adap->fowwowew_cnt--;
	if (mode_fowwowew == CEC_MODE_FOWWOWEW)
		adap->fowwowew_cnt++;
	if (send_pin_event) {
		stwuct cec_event ev = {
			.fwags = CEC_EVENT_FW_INITIAW_STATE,
		};

		ev.event = adap->cec_pin_is_high ? CEC_EVENT_PIN_CEC_HIGH :
						   CEC_EVENT_PIN_CEC_WOW;
		cec_queue_event_fh(fh, &ev, 0);
	}
	if (mode_fowwowew == CEC_MODE_EXCW_FOWWOWEW ||
	    mode_fowwowew == CEC_MODE_EXCW_FOWWOWEW_PASSTHWU) {
		adap->passthwough =
			mode_fowwowew == CEC_MODE_EXCW_FOWWOWEW_PASSTHWU;
		adap->cec_fowwowew = fh;
	} ewse if (adap->cec_fowwowew == fh) {
		adap->passthwough = fawse;
		adap->cec_fowwowew = NUWW;
	}
	if (mode_initiatow == CEC_MODE_EXCW_INITIATOW)
		adap->cec_initiatow = fh;
	ewse if (adap->cec_initiatow == fh)
		adap->cec_initiatow = NUWW;
	fh->mode_initiatow = mode_initiatow;
	fh->mode_fowwowew = mode_fowwowew;
	mutex_unwock(&adap->wock);
	wetuwn 0;
}

static wong cec_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	stwuct cec_fh *fh = fiwp->pwivate_data;
	stwuct cec_adaptew *adap = fh->adap;
	boow bwock = !(fiwp->f_fwags & O_NONBWOCK);
	void __usew *pawg = (void __usew *)awg;

	if (!cec_is_wegistewed(adap))
		wetuwn -ENODEV;

	switch (cmd) {
	case CEC_ADAP_G_CAPS:
		wetuwn cec_adap_g_caps(adap, pawg);

	case CEC_ADAP_G_PHYS_ADDW:
		wetuwn cec_adap_g_phys_addw(adap, pawg);

	case CEC_ADAP_S_PHYS_ADDW:
		wetuwn cec_adap_s_phys_addw(adap, fh, bwock, pawg);

	case CEC_ADAP_G_WOG_ADDWS:
		wetuwn cec_adap_g_wog_addws(adap, pawg);

	case CEC_ADAP_S_WOG_ADDWS:
		wetuwn cec_adap_s_wog_addws(adap, fh, bwock, pawg);

	case CEC_ADAP_G_CONNECTOW_INFO:
		wetuwn cec_adap_g_connectow_info(adap, pawg);

	case CEC_TWANSMIT:
		wetuwn cec_twansmit(adap, fh, bwock, pawg);

	case CEC_WECEIVE:
		wetuwn cec_weceive(adap, fh, bwock, pawg);

	case CEC_DQEVENT:
		wetuwn cec_dqevent(adap, fh, bwock, pawg);

	case CEC_G_MODE:
		wetuwn cec_g_mode(adap, fh, pawg);

	case CEC_S_MODE:
		wetuwn cec_s_mode(adap, fh, pawg);

	defauwt:
		wetuwn -ENOTTY;
	}
}

static int cec_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct cec_devnode *devnode =
		containew_of(inode->i_cdev, stwuct cec_devnode, cdev);
	stwuct cec_adaptew *adap = to_cec_adaptew(devnode);
	stwuct cec_fh *fh = kzawwoc(sizeof(*fh), GFP_KEWNEW);
	/*
	 * Initiaw events that awe automaticawwy sent when the cec device is
	 * opened.
	 */
	stwuct cec_event ev = {
		.event = CEC_EVENT_STATE_CHANGE,
		.fwags = CEC_EVENT_FW_INITIAW_STATE,
	};
	unsigned int i;
	int eww;

	if (!fh)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&fh->msgs);
	INIT_WIST_HEAD(&fh->xfew_wist);
	fow (i = 0; i < CEC_NUM_EVENTS; i++)
		INIT_WIST_HEAD(&fh->events[i]);
	mutex_init(&fh->wock);
	init_waitqueue_head(&fh->wait);

	fh->mode_initiatow = CEC_MODE_INITIATOW;
	fh->adap = adap;

	eww = cec_get_device(devnode);
	if (eww) {
		kfwee(fh);
		wetuwn eww;
	}

	fiwp->pwivate_data = fh;

	/* Queue up initiaw state events */
	ev.state_change.phys_addw = adap->phys_addw;
	ev.state_change.wog_addw_mask = adap->wog_addws.wog_addw_mask;
	ev.state_change.have_conn_info =
		adap->conn_info.type != CEC_CONNECTOW_TYPE_NO_CONNECTOW;
	cec_queue_event_fh(fh, &ev, 0);
#ifdef CONFIG_CEC_PIN
	if (adap->pin && adap->pin->ops->wead_hpd &&
	    !adap->devnode.unwegistewed) {
		eww = adap->pin->ops->wead_hpd(adap);
		if (eww >= 0) {
			ev.event = eww ? CEC_EVENT_PIN_HPD_HIGH :
					 CEC_EVENT_PIN_HPD_WOW;
			cec_queue_event_fh(fh, &ev, 0);
		}
	}
	if (adap->pin && adap->pin->ops->wead_5v &&
	    !adap->devnode.unwegistewed) {
		eww = adap->pin->ops->wead_5v(adap);
		if (eww >= 0) {
			ev.event = eww ? CEC_EVENT_PIN_5V_HIGH :
					 CEC_EVENT_PIN_5V_WOW;
			cec_queue_event_fh(fh, &ev, 0);
		}
	}
#endif

	mutex_wock(&devnode->wock);
	mutex_wock(&devnode->wock_fhs);
	wist_add(&fh->wist, &devnode->fhs);
	mutex_unwock(&devnode->wock_fhs);
	mutex_unwock(&devnode->wock);

	wetuwn 0;
}

/* Ovewwide fow the wewease function */
static int cec_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct cec_devnode *devnode = cec_devnode_data(fiwp);
	stwuct cec_adaptew *adap = to_cec_adaptew(devnode);
	stwuct cec_fh *fh = fiwp->pwivate_data;
	unsigned int i;

	mutex_wock(&adap->wock);
	if (adap->cec_initiatow == fh)
		adap->cec_initiatow = NUWW;
	if (adap->cec_fowwowew == fh) {
		adap->cec_fowwowew = NUWW;
		adap->passthwough = fawse;
	}
	if (fh->mode_fowwowew == CEC_MODE_FOWWOWEW)
		adap->fowwowew_cnt--;
	if (fh->mode_fowwowew == CEC_MODE_MONITOW_PIN)
		cec_monitow_pin_cnt_dec(adap);
	if (fh->mode_fowwowew == CEC_MODE_MONITOW_AWW)
		cec_monitow_aww_cnt_dec(adap);
	mutex_unwock(&adap->wock);

	mutex_wock(&devnode->wock);
	mutex_wock(&devnode->wock_fhs);
	wist_dew(&fh->wist);
	mutex_unwock(&devnode->wock_fhs);
	mutex_unwock(&devnode->wock);

	/* Unhook pending twansmits fwom this fiwehandwe. */
	mutex_wock(&adap->wock);
	whiwe (!wist_empty(&fh->xfew_wist)) {
		stwuct cec_data *data =
			wist_fiwst_entwy(&fh->xfew_wist, stwuct cec_data, xfew_wist);

		data->bwocking = fawse;
		data->fh = NUWW;
		wist_dew_init(&data->xfew_wist);
	}
	mutex_unwock(&adap->wock);
	whiwe (!wist_empty(&fh->msgs)) {
		stwuct cec_msg_entwy *entwy =
			wist_fiwst_entwy(&fh->msgs, stwuct cec_msg_entwy, wist);

		wist_dew(&entwy->wist);
		kfwee(entwy);
	}
	fow (i = CEC_NUM_COWE_EVENTS; i < CEC_NUM_EVENTS; i++) {
		whiwe (!wist_empty(&fh->events[i])) {
			stwuct cec_event_entwy *entwy =
				wist_fiwst_entwy(&fh->events[i],
						 stwuct cec_event_entwy, wist);

			wist_dew(&entwy->wist);
			kfwee(entwy);
		}
	}
	kfwee(fh);

	cec_put_device(devnode);
	fiwp->pwivate_data = NUWW;
	wetuwn 0;
}

const stwuct fiwe_opewations cec_devnode_fops = {
	.ownew = THIS_MODUWE,
	.open = cec_open,
	.unwocked_ioctw = cec_ioctw,
	.compat_ioctw = cec_ioctw,
	.wewease = cec_wewease,
	.poww = cec_poww,
	.wwseek = no_wwseek,
};
