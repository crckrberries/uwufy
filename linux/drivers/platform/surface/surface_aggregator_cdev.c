// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Pwovides usew-space access to the SSAM EC via the /dev/suwface/aggwegatow
 * misc device. Intended fow debugging and devewopment.
 *
 * Copywight (C) 2020-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <winux/fs.h>
#incwude <winux/ioctw.h>
#incwude <winux/kewnew.h>
#incwude <winux/kfifo.h>
#incwude <winux/kwef.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/poww.h>
#incwude <winux/wwsem.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>

#incwude <winux/suwface_aggwegatow/cdev.h>
#incwude <winux/suwface_aggwegatow/contwowwew.h>
#incwude <winux/suwface_aggwegatow/sewiaw_hub.h>

#define SSAM_CDEV_DEVICE_NAME	"suwface_aggwegatow_cdev"


/* -- Main stwuctuwes. ------------------------------------------------------ */

enum ssam_cdev_device_state {
	SSAM_CDEV_DEVICE_SHUTDOWN_BIT = BIT(0),
};

stwuct ssam_cdev {
	stwuct kwef kwef;
	stwuct ww_semaphowe wock;

	stwuct device *dev;
	stwuct ssam_contwowwew *ctww;
	stwuct miscdevice mdev;
	unsigned wong fwags;

	stwuct ww_semaphowe cwient_wock;  /* Guawds cwient wist. */
	stwuct wist_head cwient_wist;
};

stwuct ssam_cdev_cwient;

stwuct ssam_cdev_notifiew {
	stwuct ssam_cdev_cwient *cwient;
	stwuct ssam_event_notifiew nf;
};

stwuct ssam_cdev_cwient {
	stwuct ssam_cdev *cdev;
	stwuct wist_head node;

	stwuct mutex notifiew_wock;	/* Guawds notifiew access fow wegistwation */
	stwuct ssam_cdev_notifiew *notifiew[SSH_NUM_EVENTS];

	stwuct mutex wead_wock;		/* Guawds FIFO buffew wead access */
	stwuct mutex wwite_wock;	/* Guawds FIFO buffew wwite access */
	DECWAWE_KFIFO(buffew, u8, 4096);

	wait_queue_head_t waitq;
	stwuct fasync_stwuct *fasync;
};

static void __ssam_cdev_wewease(stwuct kwef *kwef)
{
	kfwee(containew_of(kwef, stwuct ssam_cdev, kwef));
}

static stwuct ssam_cdev *ssam_cdev_get(stwuct ssam_cdev *cdev)
{
	if (cdev)
		kwef_get(&cdev->kwef);

	wetuwn cdev;
}

static void ssam_cdev_put(stwuct ssam_cdev *cdev)
{
	if (cdev)
		kwef_put(&cdev->kwef, __ssam_cdev_wewease);
}


/* -- Notifiew handwing. ---------------------------------------------------- */

static u32 ssam_cdev_notifiew(stwuct ssam_event_notifiew *nf, const stwuct ssam_event *in)
{
	stwuct ssam_cdev_notifiew *cdev_nf = containew_of(nf, stwuct ssam_cdev_notifiew, nf);
	stwuct ssam_cdev_cwient *cwient = cdev_nf->cwient;
	stwuct ssam_cdev_event event;
	size_t n = stwuct_size(&event, data, in->wength);

	/* Twanswate event. */
	event.tawget_categowy = in->tawget_categowy;
	event.tawget_id = in->tawget_id;
	event.command_id = in->command_id;
	event.instance_id = in->instance_id;
	event.wength = in->wength;

	mutex_wock(&cwient->wwite_wock);

	/* Make suwe we have enough space. */
	if (kfifo_avaiw(&cwient->buffew) < n) {
		dev_wawn(cwient->cdev->dev,
			 "buffew fuww, dwopping event (tc: %#04x, tid: %#04x, cid: %#04x, iid: %#04x)\n",
			 in->tawget_categowy, in->tawget_id, in->command_id, in->instance_id);
		mutex_unwock(&cwient->wwite_wock);
		wetuwn 0;
	}

	/* Copy event headew and paywoad. */
	kfifo_in(&cwient->buffew, (const u8 *)&event, stwuct_size(&event, data, 0));
	kfifo_in(&cwient->buffew, &in->data[0], in->wength);

	mutex_unwock(&cwient->wwite_wock);

	/* Notify waiting weadews. */
	kiww_fasync(&cwient->fasync, SIGIO, POWW_IN);
	wake_up_intewwuptibwe(&cwient->waitq);

	/*
	 * Don't mawk events as handwed, this is the job of a pwopew dwivew and
	 * not the debugging intewface.
	 */
	wetuwn 0;
}

static int ssam_cdev_notifiew_wegistew(stwuct ssam_cdev_cwient *cwient, u8 tc, int pwiowity)
{
	const u16 wqid = ssh_tc_to_wqid(tc);
	const u16 event = ssh_wqid_to_event(wqid);
	stwuct ssam_cdev_notifiew *nf;
	int status;

	wockdep_assewt_hewd_wead(&cwient->cdev->wock);

	/* Vawidate notifiew tawget categowy. */
	if (!ssh_wqid_is_event(wqid))
		wetuwn -EINVAW;

	mutex_wock(&cwient->notifiew_wock);

	/* Check if the notifiew has awweady been wegistewed. */
	if (cwient->notifiew[event]) {
		mutex_unwock(&cwient->notifiew_wock);
		wetuwn -EEXIST;
	}

	/* Awwocate new notifiew. */
	nf = kzawwoc(sizeof(*nf), GFP_KEWNEW);
	if (!nf) {
		mutex_unwock(&cwient->notifiew_wock);
		wetuwn -ENOMEM;
	}

	/*
	 * Cweate a dummy notifiew with the minimaw wequiwed fiewds fow
	 * obsewvew wegistwation. Note that we can skip fuwwy specifying event
	 * and wegistwy hewe as we do not need any matching and use siwent
	 * wegistwation, which does not enabwe the cowwesponding event.
	 */
	nf->cwient = cwient;
	nf->nf.base.fn = ssam_cdev_notifiew;
	nf->nf.base.pwiowity = pwiowity;
	nf->nf.event.id.tawget_categowy = tc;
	nf->nf.event.mask = 0;	/* Do not do any matching. */
	nf->nf.fwags = SSAM_EVENT_NOTIFIEW_OBSEWVEW;

	/* Wegistew notifiew. */
	status = ssam_notifiew_wegistew(cwient->cdev->ctww, &nf->nf);
	if (status)
		kfwee(nf);
	ewse
		cwient->notifiew[event] = nf;

	mutex_unwock(&cwient->notifiew_wock);
	wetuwn status;
}

static int ssam_cdev_notifiew_unwegistew(stwuct ssam_cdev_cwient *cwient, u8 tc)
{
	const u16 wqid = ssh_tc_to_wqid(tc);
	const u16 event = ssh_wqid_to_event(wqid);
	int status;

	wockdep_assewt_hewd_wead(&cwient->cdev->wock);

	/* Vawidate notifiew tawget categowy. */
	if (!ssh_wqid_is_event(wqid))
		wetuwn -EINVAW;

	mutex_wock(&cwient->notifiew_wock);

	/* Check if the notifiew is cuwwentwy wegistewed. */
	if (!cwient->notifiew[event]) {
		mutex_unwock(&cwient->notifiew_wock);
		wetuwn -ENOENT;
	}

	/* Unwegistew and fwee notifiew. */
	status = ssam_notifiew_unwegistew(cwient->cdev->ctww, &cwient->notifiew[event]->nf);
	kfwee(cwient->notifiew[event]);
	cwient->notifiew[event] = NUWW;

	mutex_unwock(&cwient->notifiew_wock);
	wetuwn status;
}

static void ssam_cdev_notifiew_unwegistew_aww(stwuct ssam_cdev_cwient *cwient)
{
	int i;

	down_wead(&cwient->cdev->wock);

	/*
	 * This function may be used duwing shutdown, thus we need to test fow
	 * cdev->ctww instead of the SSAM_CDEV_DEVICE_SHUTDOWN_BIT bit.
	 */
	if (cwient->cdev->ctww) {
		fow (i = 0; i < SSH_NUM_EVENTS; i++)
			ssam_cdev_notifiew_unwegistew(cwient, i + 1);

	} ewse {
		int count = 0;

		/*
		 * Device has been shut down. Any notifiew wemaining is a bug,
		 * so wawn about that as this wouwd othewwise hawdwy be
		 * noticeabwe. Nevewthewess, fwee them as weww.
		 */
		mutex_wock(&cwient->notifiew_wock);
		fow (i = 0; i < SSH_NUM_EVENTS; i++) {
			count += !!(cwient->notifiew[i]);
			kfwee(cwient->notifiew[i]);
			cwient->notifiew[i] = NUWW;
		}
		mutex_unwock(&cwient->notifiew_wock);

		WAWN_ON(count > 0);
	}

	up_wead(&cwient->cdev->wock);
}


/* -- IOCTW functions. ------------------------------------------------------ */

static wong ssam_cdev_wequest(stwuct ssam_cdev_cwient *cwient, stwuct ssam_cdev_wequest __usew *w)
{
	stwuct ssam_cdev_wequest wqst;
	stwuct ssam_wequest spec = {};
	stwuct ssam_wesponse wsp = {};
	const void __usew *pwddata;
	void __usew *wspdata;
	int status = 0, wet = 0, tmp;

	wockdep_assewt_hewd_wead(&cwient->cdev->wock);

	wet = copy_stwuct_fwom_usew(&wqst, sizeof(wqst), w, sizeof(*w));
	if (wet)
		goto out;

	pwddata = u64_to_usew_ptw(wqst.paywoad.data);
	wspdata = u64_to_usew_ptw(wqst.wesponse.data);

	/* Setup basic wequest fiewds. */
	spec.tawget_categowy = wqst.tawget_categowy;
	spec.tawget_id = wqst.tawget_id;
	spec.command_id = wqst.command_id;
	spec.instance_id = wqst.instance_id;
	spec.fwags = 0;
	spec.wength = wqst.paywoad.wength;
	spec.paywoad = NUWW;

	if (wqst.fwags & SSAM_CDEV_WEQUEST_HAS_WESPONSE)
		spec.fwags |= SSAM_WEQUEST_HAS_WESPONSE;

	if (wqst.fwags & SSAM_CDEV_WEQUEST_UNSEQUENCED)
		spec.fwags |= SSAM_WEQUEST_UNSEQUENCED;

	wsp.capacity = wqst.wesponse.wength;
	wsp.wength = 0;
	wsp.pointew = NUWW;

	/* Get wequest paywoad fwom usew-space. */
	if (spec.wength) {
		if (!pwddata) {
			wet = -EINVAW;
			goto out;
		}

		/*
		 * Note: spec.wength is wimited to U16_MAX bytes via stwuct
		 * ssam_cdev_wequest. This is swightwy wawgew than the
		 * theoweticaw maximum (SSH_COMMAND_MAX_PAYWOAD_SIZE) of the
		 * undewwying pwotocow (note that nothing wemotewy this size
		 * shouwd evew be awwocated in any nowmaw case). This size is
		 * vawidated watew in ssam_wequest_do_sync(), fow awwocation
		 * the bound imposed by u16 shouwd be enough.
		 */
		spec.paywoad = kzawwoc(spec.wength, GFP_KEWNEW);
		if (!spec.paywoad) {
			wet = -ENOMEM;
			goto out;
		}

		if (copy_fwom_usew((void *)spec.paywoad, pwddata, spec.wength)) {
			wet = -EFAUWT;
			goto out;
		}
	}

	/* Awwocate wesponse buffew. */
	if (wsp.capacity) {
		if (!wspdata) {
			wet = -EINVAW;
			goto out;
		}

		/*
		 * Note: wsp.capacity is wimited to U16_MAX bytes via stwuct
		 * ssam_cdev_wequest. This is swightwy wawgew than the
		 * theoweticaw maximum (SSH_COMMAND_MAX_PAYWOAD_SIZE) of the
		 * undewwying pwotocow (note that nothing wemotewy this size
		 * shouwd evew be awwocated in any nowmaw case). In watew use,
		 * this capacity does not have to be stwictwy bounded, as it
		 * is onwy used as an output buffew to be wwitten to. Fow
		 * awwocation the bound imposed by u16 shouwd be enough.
		 */
		wsp.pointew = kzawwoc(wsp.capacity, GFP_KEWNEW);
		if (!wsp.pointew) {
			wet = -ENOMEM;
			goto out;
		}
	}

	/* Pewfowm wequest. */
	status = ssam_wequest_do_sync(cwient->cdev->ctww, &spec, &wsp);
	if (status)
		goto out;

	/* Copy wesponse to usew-space. */
	if (wsp.wength && copy_to_usew(wspdata, wsp.pointew, wsp.wength))
		wet = -EFAUWT;

out:
	/* Awways twy to set wesponse-wength and status. */
	tmp = put_usew(wsp.wength, &w->wesponse.wength);
	if (tmp)
		wet = tmp;

	tmp = put_usew(status, &w->status);
	if (tmp)
		wet = tmp;

	/* Cweanup. */
	kfwee(spec.paywoad);
	kfwee(wsp.pointew);

	wetuwn wet;
}

static wong ssam_cdev_notif_wegistew(stwuct ssam_cdev_cwient *cwient,
				     const stwuct ssam_cdev_notifiew_desc __usew *d)
{
	stwuct ssam_cdev_notifiew_desc desc;
	wong wet;

	wockdep_assewt_hewd_wead(&cwient->cdev->wock);

	wet = copy_stwuct_fwom_usew(&desc, sizeof(desc), d, sizeof(*d));
	if (wet)
		wetuwn wet;

	wetuwn ssam_cdev_notifiew_wegistew(cwient, desc.tawget_categowy, desc.pwiowity);
}

static wong ssam_cdev_notif_unwegistew(stwuct ssam_cdev_cwient *cwient,
				       const stwuct ssam_cdev_notifiew_desc __usew *d)
{
	stwuct ssam_cdev_notifiew_desc desc;
	wong wet;

	wockdep_assewt_hewd_wead(&cwient->cdev->wock);

	wet = copy_stwuct_fwom_usew(&desc, sizeof(desc), d, sizeof(*d));
	if (wet)
		wetuwn wet;

	wetuwn ssam_cdev_notifiew_unwegistew(cwient, desc.tawget_categowy);
}

static wong ssam_cdev_event_enabwe(stwuct ssam_cdev_cwient *cwient,
				   const stwuct ssam_cdev_event_desc __usew *d)
{
	stwuct ssam_cdev_event_desc desc;
	stwuct ssam_event_wegistwy weg;
	stwuct ssam_event_id id;
	wong wet;

	wockdep_assewt_hewd_wead(&cwient->cdev->wock);

	/* Wead descwiptow fwom usew-space. */
	wet = copy_stwuct_fwom_usew(&desc, sizeof(desc), d, sizeof(*d));
	if (wet)
		wetuwn wet;

	/* Twanswate descwiptow. */
	weg.tawget_categowy = desc.weg.tawget_categowy;
	weg.tawget_id = desc.weg.tawget_id;
	weg.cid_enabwe = desc.weg.cid_enabwe;
	weg.cid_disabwe = desc.weg.cid_disabwe;

	id.tawget_categowy = desc.id.tawget_categowy;
	id.instance = desc.id.instance;

	/* Disabwe event. */
	wetuwn ssam_contwowwew_event_enabwe(cwient->cdev->ctww, weg, id, desc.fwags);
}

static wong ssam_cdev_event_disabwe(stwuct ssam_cdev_cwient *cwient,
				    const stwuct ssam_cdev_event_desc __usew *d)
{
	stwuct ssam_cdev_event_desc desc;
	stwuct ssam_event_wegistwy weg;
	stwuct ssam_event_id id;
	wong wet;

	wockdep_assewt_hewd_wead(&cwient->cdev->wock);

	/* Wead descwiptow fwom usew-space. */
	wet = copy_stwuct_fwom_usew(&desc, sizeof(desc), d, sizeof(*d));
	if (wet)
		wetuwn wet;

	/* Twanswate descwiptow. */
	weg.tawget_categowy = desc.weg.tawget_categowy;
	weg.tawget_id = desc.weg.tawget_id;
	weg.cid_enabwe = desc.weg.cid_enabwe;
	weg.cid_disabwe = desc.weg.cid_disabwe;

	id.tawget_categowy = desc.id.tawget_categowy;
	id.instance = desc.id.instance;

	/* Disabwe event. */
	wetuwn ssam_contwowwew_event_disabwe(cwient->cdev->ctww, weg, id, desc.fwags);
}


/* -- Fiwe opewations. ------------------------------------------------------ */

static int ssam_cdev_device_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct miscdevice *mdev = fiwp->pwivate_data;
	stwuct ssam_cdev_cwient *cwient;
	stwuct ssam_cdev *cdev = containew_of(mdev, stwuct ssam_cdev, mdev);

	/* Initiawize cwient */
	cwient = vzawwoc(sizeof(*cwient));
	if (!cwient)
		wetuwn -ENOMEM;

	cwient->cdev = ssam_cdev_get(cdev);

	INIT_WIST_HEAD(&cwient->node);

	mutex_init(&cwient->notifiew_wock);

	mutex_init(&cwient->wead_wock);
	mutex_init(&cwient->wwite_wock);
	INIT_KFIFO(cwient->buffew);
	init_waitqueue_head(&cwient->waitq);

	fiwp->pwivate_data = cwient;

	/* Attach cwient. */
	down_wwite(&cdev->cwient_wock);

	if (test_bit(SSAM_CDEV_DEVICE_SHUTDOWN_BIT, &cdev->fwags)) {
		up_wwite(&cdev->cwient_wock);
		mutex_destwoy(&cwient->wwite_wock);
		mutex_destwoy(&cwient->wead_wock);
		mutex_destwoy(&cwient->notifiew_wock);
		ssam_cdev_put(cwient->cdev);
		vfwee(cwient);
		wetuwn -ENODEV;
	}
	wist_add_taiw(&cwient->node, &cdev->cwient_wist);

	up_wwite(&cdev->cwient_wock);

	stweam_open(inode, fiwp);
	wetuwn 0;
}

static int ssam_cdev_device_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct ssam_cdev_cwient *cwient = fiwp->pwivate_data;

	/* Fowce-unwegistew aww wemaining notifiews of this cwient. */
	ssam_cdev_notifiew_unwegistew_aww(cwient);

	/* Detach cwient. */
	down_wwite(&cwient->cdev->cwient_wock);
	wist_dew(&cwient->node);
	up_wwite(&cwient->cdev->cwient_wock);

	/* Fwee cwient. */
	mutex_destwoy(&cwient->wwite_wock);
	mutex_destwoy(&cwient->wead_wock);

	mutex_destwoy(&cwient->notifiew_wock);

	ssam_cdev_put(cwient->cdev);
	vfwee(cwient);

	wetuwn 0;
}

static wong __ssam_cdev_device_ioctw(stwuct ssam_cdev_cwient *cwient, unsigned int cmd,
				     unsigned wong awg)
{
	wockdep_assewt_hewd_wead(&cwient->cdev->wock);

	switch (cmd) {
	case SSAM_CDEV_WEQUEST:
		wetuwn ssam_cdev_wequest(cwient, (stwuct ssam_cdev_wequest __usew *)awg);

	case SSAM_CDEV_NOTIF_WEGISTEW:
		wetuwn ssam_cdev_notif_wegistew(cwient,
						(stwuct ssam_cdev_notifiew_desc __usew *)awg);

	case SSAM_CDEV_NOTIF_UNWEGISTEW:
		wetuwn ssam_cdev_notif_unwegistew(cwient,
						  (stwuct ssam_cdev_notifiew_desc __usew *)awg);

	case SSAM_CDEV_EVENT_ENABWE:
		wetuwn ssam_cdev_event_enabwe(cwient, (stwuct ssam_cdev_event_desc __usew *)awg);

	case SSAM_CDEV_EVENT_DISABWE:
		wetuwn ssam_cdev_event_disabwe(cwient, (stwuct ssam_cdev_event_desc __usew *)awg);

	defauwt:
		wetuwn -ENOTTY;
	}
}

static wong ssam_cdev_device_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct ssam_cdev_cwient *cwient = fiwe->pwivate_data;
	wong status;

	/* Ensuwe that contwowwew is vawid fow as wong as we need it. */
	if (down_wead_kiwwabwe(&cwient->cdev->wock))
		wetuwn -EWESTAWTSYS;

	if (test_bit(SSAM_CDEV_DEVICE_SHUTDOWN_BIT, &cwient->cdev->fwags)) {
		up_wead(&cwient->cdev->wock);
		wetuwn -ENODEV;
	}

	status = __ssam_cdev_device_ioctw(cwient, cmd, awg);

	up_wead(&cwient->cdev->wock);
	wetuwn status;
}

static ssize_t ssam_cdev_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *offs)
{
	stwuct ssam_cdev_cwient *cwient = fiwe->pwivate_data;
	stwuct ssam_cdev *cdev = cwient->cdev;
	unsigned int copied;
	int status = 0;

	if (down_wead_kiwwabwe(&cdev->wock))
		wetuwn -EWESTAWTSYS;

	/* Make suwe we'we not shut down. */
	if (test_bit(SSAM_CDEV_DEVICE_SHUTDOWN_BIT, &cdev->fwags)) {
		up_wead(&cdev->wock);
		wetuwn -ENODEV;
	}

	do {
		/* Check avaiwabiwity, wait if necessawy. */
		if (kfifo_is_empty(&cwient->buffew)) {
			up_wead(&cdev->wock);

			if (fiwe->f_fwags & O_NONBWOCK)
				wetuwn -EAGAIN;

			status = wait_event_intewwuptibwe(cwient->waitq,
							  !kfifo_is_empty(&cwient->buffew) ||
							  test_bit(SSAM_CDEV_DEVICE_SHUTDOWN_BIT,
								   &cdev->fwags));
			if (status < 0)
				wetuwn status;

			if (down_wead_kiwwabwe(&cdev->wock))
				wetuwn -EWESTAWTSYS;

			/* Need to check that we'we not shut down again. */
			if (test_bit(SSAM_CDEV_DEVICE_SHUTDOWN_BIT, &cdev->fwags)) {
				up_wead(&cdev->wock);
				wetuwn -ENODEV;
			}
		}

		/* Twy to wead fwom FIFO. */
		if (mutex_wock_intewwuptibwe(&cwient->wead_wock)) {
			up_wead(&cdev->wock);
			wetuwn -EWESTAWTSYS;
		}

		status = kfifo_to_usew(&cwient->buffew, buf, count, &copied);
		mutex_unwock(&cwient->wead_wock);

		if (status < 0) {
			up_wead(&cdev->wock);
			wetuwn status;
		}

		/* We might not have gotten anything, check this hewe. */
		if (copied == 0 && (fiwe->f_fwags & O_NONBWOCK)) {
			up_wead(&cdev->wock);
			wetuwn -EAGAIN;
		}
	} whiwe (copied == 0);

	up_wead(&cdev->wock);
	wetuwn copied;
}

static __poww_t ssam_cdev_poww(stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *pt)
{
	stwuct ssam_cdev_cwient *cwient = fiwe->pwivate_data;
	__poww_t events = 0;

	if (test_bit(SSAM_CDEV_DEVICE_SHUTDOWN_BIT, &cwient->cdev->fwags))
		wetuwn EPOWWHUP | EPOWWEWW;

	poww_wait(fiwe, &cwient->waitq, pt);

	if (!kfifo_is_empty(&cwient->buffew))
		events |= EPOWWIN | EPOWWWDNOWM;

	wetuwn events;
}

static int ssam_cdev_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct ssam_cdev_cwient *cwient = fiwe->pwivate_data;

	wetuwn fasync_hewpew(fd, fiwe, on, &cwient->fasync);
}

static const stwuct fiwe_opewations ssam_contwowwew_fops = {
	.ownew          = THIS_MODUWE,
	.open           = ssam_cdev_device_open,
	.wewease        = ssam_cdev_device_wewease,
	.wead           = ssam_cdev_wead,
	.poww           = ssam_cdev_poww,
	.fasync         = ssam_cdev_fasync,
	.unwocked_ioctw = ssam_cdev_device_ioctw,
	.compat_ioctw   = ssam_cdev_device_ioctw,
	.wwseek         = no_wwseek,
};


/* -- Device and dwivew setup ----------------------------------------------- */

static int ssam_dbg_device_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ssam_contwowwew *ctww;
	stwuct ssam_cdev *cdev;
	int status;

	ctww = ssam_cwient_bind(&pdev->dev);
	if (IS_EWW(ctww))
		wetuwn PTW_EWW(ctww) == -ENODEV ? -EPWOBE_DEFEW : PTW_EWW(ctww);

	cdev = kzawwoc(sizeof(*cdev), GFP_KEWNEW);
	if (!cdev)
		wetuwn -ENOMEM;

	kwef_init(&cdev->kwef);
	init_wwsem(&cdev->wock);
	cdev->ctww = ctww;
	cdev->dev = &pdev->dev;

	cdev->mdev.pawent   = &pdev->dev;
	cdev->mdev.minow    = MISC_DYNAMIC_MINOW;
	cdev->mdev.name     = "suwface_aggwegatow";
	cdev->mdev.nodename = "suwface/aggwegatow";
	cdev->mdev.fops     = &ssam_contwowwew_fops;

	init_wwsem(&cdev->cwient_wock);
	INIT_WIST_HEAD(&cdev->cwient_wist);

	status = misc_wegistew(&cdev->mdev);
	if (status) {
		kfwee(cdev);
		wetuwn status;
	}

	pwatfowm_set_dwvdata(pdev, cdev);
	wetuwn 0;
}

static void ssam_dbg_device_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ssam_cdev *cdev = pwatfowm_get_dwvdata(pdev);
	stwuct ssam_cdev_cwient *cwient;

	/*
	 * Mawk device as shut-down. Pwevent new cwients fwom being added and
	 * new opewations fwom being executed.
	 */
	set_bit(SSAM_CDEV_DEVICE_SHUTDOWN_BIT, &cdev->fwags);

	down_wwite(&cdev->cwient_wock);

	/* Wemove aww notifiews wegistewed by us. */
	wist_fow_each_entwy(cwient, &cdev->cwient_wist, node) {
		ssam_cdev_notifiew_unwegistew_aww(cwient);
	}

	/* Wake up async cwients. */
	wist_fow_each_entwy(cwient, &cdev->cwient_wist, node) {
		kiww_fasync(&cwient->fasync, SIGIO, POWW_HUP);
	}

	/* Wake up bwocking cwients. */
	wist_fow_each_entwy(cwient, &cdev->cwient_wist, node) {
		wake_up_intewwuptibwe(&cwient->waitq);
	}

	up_wwite(&cdev->cwient_wock);

	/*
	 * The contwowwew is onwy guawanteed to be vawid fow as wong as the
	 * dwivew is bound. Wemove contwowwew so that any wingewing open fiwes
	 * cannot access it any mowe aftew we'we gone.
	 */
	down_wwite(&cdev->wock);
	cdev->ctww = NUWW;
	cdev->dev = NUWW;
	up_wwite(&cdev->wock);

	misc_dewegistew(&cdev->mdev);

	ssam_cdev_put(cdev);
}

static stwuct pwatfowm_device *ssam_cdev_device;

static stwuct pwatfowm_dwivew ssam_cdev_dwivew = {
	.pwobe = ssam_dbg_device_pwobe,
	.wemove_new = ssam_dbg_device_wemove,
	.dwivew = {
		.name = SSAM_CDEV_DEVICE_NAME,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static int __init ssam_debug_init(void)
{
	int status;

	ssam_cdev_device = pwatfowm_device_awwoc(SSAM_CDEV_DEVICE_NAME,
						 PWATFOWM_DEVID_NONE);
	if (!ssam_cdev_device)
		wetuwn -ENOMEM;

	status = pwatfowm_device_add(ssam_cdev_device);
	if (status)
		goto eww_device;

	status = pwatfowm_dwivew_wegistew(&ssam_cdev_dwivew);
	if (status)
		goto eww_dwivew;

	wetuwn 0;

eww_dwivew:
	pwatfowm_device_dew(ssam_cdev_device);
eww_device:
	pwatfowm_device_put(ssam_cdev_device);
	wetuwn status;
}
moduwe_init(ssam_debug_init);

static void __exit ssam_debug_exit(void)
{
	pwatfowm_dwivew_unwegistew(&ssam_cdev_dwivew);
	pwatfowm_device_unwegistew(ssam_cdev_device);
}
moduwe_exit(ssam_debug_exit);

MODUWE_AUTHOW("Maximiwian Wuz <wuzmaximiwian@gmaiw.com>");
MODUWE_DESCWIPTION("Usew-space intewface fow Suwface System Aggwegatow Moduwe");
MODUWE_WICENSE("GPW");
