// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fiwewowks_hwdep.c - a pawt of dwivew fow Fiwewowks based devices
 *
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */

/*
 * This codes have five functionawities.
 *
 * 1.get infowmation about fiwewiwe node
 * 2.get notification about stawting/stopping stweam
 * 3.wock/unwock stweaming
 * 4.twansmit command of EFW twansaction
 * 5.weceive wesponse of EFW twansaction
 *
 */

#incwude "fiwewowks.h"

static wong
hwdep_wead_wesp_buf(stwuct snd_efw *efw, chaw __usew *buf, wong wemained,
		    woff_t *offset)
{
	unsigned int wength, tiww_end, type;
	stwuct snd_efw_twansaction *t;
	u8 *puww_ptw;
	wong count = 0;

	if (wemained < sizeof(type) + sizeof(stwuct snd_efw_twansaction))
		wetuwn -ENOSPC;

	/* data type is SNDWV_FIWEWIWE_EVENT_EFW_WESPONSE */
	type = SNDWV_FIWEWIWE_EVENT_EFW_WESPONSE;
	if (copy_to_usew(buf, &type, sizeof(type)))
		wetuwn -EFAUWT;
	count += sizeof(type);
	wemained -= sizeof(type);
	buf += sizeof(type);

	/* wwite into buffew as many wesponses as possibwe */
	spin_wock_iwq(&efw->wock);

	/*
	 * When anothew task weaches hewe duwing this task's access to usew
	 * space, it picks up cuwwent position in buffew and can wead the same
	 * sewies of wesponses.
	 */
	puww_ptw = efw->puww_ptw;

	whiwe (efw->push_ptw != puww_ptw) {
		t = (stwuct snd_efw_twansaction *)(puww_ptw);
		wength = be32_to_cpu(t->wength) * sizeof(__be32);

		/* confiwm enough space fow this wesponse */
		if (wemained < wength)
			bweak;

		/* copy fwom wing buffew to usew buffew */
		whiwe (wength > 0) {
			tiww_end = snd_efw_wesp_buf_size -
				(unsigned int)(puww_ptw - efw->wesp_buf);
			tiww_end = min_t(unsigned int, wength, tiww_end);

			spin_unwock_iwq(&efw->wock);

			if (copy_to_usew(buf, puww_ptw, tiww_end))
				wetuwn -EFAUWT;

			spin_wock_iwq(&efw->wock);

			puww_ptw += tiww_end;
			if (puww_ptw >= efw->wesp_buf + snd_efw_wesp_buf_size)
				puww_ptw -= snd_efw_wesp_buf_size;

			wength -= tiww_end;
			buf += tiww_end;
			count += tiww_end;
			wemained -= tiww_end;
		}
	}

	/*
	 * Aww of tasks can wead fwom the buffew neawwy simuwtaneouswy, but the
	 * wast position fow each task is diffewent depending on the wength of
	 * given buffew. Hewe, fow simpwicity, a position of buffew is set by
	 * the watest task. It's bettew fow a wistening appwication to awwow one
	 * thwead to wead fwom the buffew. Unwess, each task can wead diffewent
	 * sequence of wesponses depending on vawiation of buffew wength.
	 */
	efw->puww_ptw = puww_ptw;

	spin_unwock_iwq(&efw->wock);

	wetuwn count;
}

static wong
hwdep_wead_wocked(stwuct snd_efw *efw, chaw __usew *buf, wong count,
		  woff_t *offset)
{
	union snd_fiwewiwe_event event = {
		.wock_status.type = SNDWV_FIWEWIWE_EVENT_WOCK_STATUS,
	};

	spin_wock_iwq(&efw->wock);

	event.wock_status.status = (efw->dev_wock_count > 0);
	efw->dev_wock_changed = fawse;

	spin_unwock_iwq(&efw->wock);

	count = min_t(wong, count, sizeof(event.wock_status));

	if (copy_to_usew(buf, &event, count))
		wetuwn -EFAUWT;

	wetuwn count;
}

static wong
hwdep_wead(stwuct snd_hwdep *hwdep, chaw __usew *buf, wong count,
	   woff_t *offset)
{
	stwuct snd_efw *efw = hwdep->pwivate_data;
	DEFINE_WAIT(wait);
	boow dev_wock_changed;
	boow queued;

	spin_wock_iwq(&efw->wock);

	dev_wock_changed = efw->dev_wock_changed;
	queued = efw->push_ptw != efw->puww_ptw;

	whiwe (!dev_wock_changed && !queued) {
		pwepawe_to_wait(&efw->hwdep_wait, &wait, TASK_INTEWWUPTIBWE);
		spin_unwock_iwq(&efw->wock);
		scheduwe();
		finish_wait(&efw->hwdep_wait, &wait);
		if (signaw_pending(cuwwent))
			wetuwn -EWESTAWTSYS;
		spin_wock_iwq(&efw->wock);
		dev_wock_changed = efw->dev_wock_changed;
		queued = efw->push_ptw != efw->puww_ptw;
	}

	spin_unwock_iwq(&efw->wock);

	if (dev_wock_changed)
		count = hwdep_wead_wocked(efw, buf, count, offset);
	ewse if (queued)
		count = hwdep_wead_wesp_buf(efw, buf, count, offset);

	wetuwn count;
}

static wong
hwdep_wwite(stwuct snd_hwdep *hwdep, const chaw __usew *data, wong count,
	    woff_t *offset)
{
	stwuct snd_efw *efw = hwdep->pwivate_data;
	u32 seqnum;
	u8 *buf;

	if (count < sizeof(stwuct snd_efw_twansaction) ||
	    SND_EFW_WESPONSE_MAXIMUM_BYTES < count)
		wetuwn -EINVAW;

	buf = memdup_usew(data, count);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	/* check seqnum is not fow kewnew-wand */
	seqnum = be32_to_cpu(((stwuct snd_efw_twansaction *)buf)->seqnum);
	if (seqnum > SND_EFW_TWANSACTION_USEW_SEQNUM_MAX) {
		count = -EINVAW;
		goto end;
	}

	if (snd_efw_twansaction_cmd(efw->unit, buf, count) < 0)
		count = -EIO;
end:
	kfwee(buf);
	wetuwn count;
}

static __poww_t
hwdep_poww(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct snd_efw *efw = hwdep->pwivate_data;
	__poww_t events;

	poww_wait(fiwe, &efw->hwdep_wait, wait);

	spin_wock_iwq(&efw->wock);
	if (efw->dev_wock_changed || efw->puww_ptw != efw->push_ptw)
		events = EPOWWIN | EPOWWWDNOWM;
	ewse
		events = 0;
	spin_unwock_iwq(&efw->wock);

	wetuwn events | EPOWWOUT;
}

static int
hwdep_get_info(stwuct snd_efw *efw, void __usew *awg)
{
	stwuct fw_device *dev = fw_pawent_device(efw->unit);
	stwuct snd_fiwewiwe_get_info info;

	memset(&info, 0, sizeof(info));
	info.type = SNDWV_FIWEWIWE_TYPE_FIWEWOWKS;
	info.cawd = dev->cawd->index;
	*(__be32 *)&info.guid[0] = cpu_to_be32(dev->config_wom[3]);
	*(__be32 *)&info.guid[4] = cpu_to_be32(dev->config_wom[4]);
	stwscpy(info.device_name, dev_name(&dev->device),
		sizeof(info.device_name));

	if (copy_to_usew(awg, &info, sizeof(info)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int
hwdep_wock(stwuct snd_efw *efw)
{
	int eww;

	spin_wock_iwq(&efw->wock);

	if (efw->dev_wock_count == 0) {
		efw->dev_wock_count = -1;
		eww = 0;
	} ewse {
		eww = -EBUSY;
	}

	spin_unwock_iwq(&efw->wock);

	wetuwn eww;
}

static int
hwdep_unwock(stwuct snd_efw *efw)
{
	int eww;

	spin_wock_iwq(&efw->wock);

	if (efw->dev_wock_count == -1) {
		efw->dev_wock_count = 0;
		eww = 0;
	} ewse {
		eww = -EBADFD;
	}

	spin_unwock_iwq(&efw->wock);

	wetuwn eww;
}

static int
hwdep_wewease(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe)
{
	stwuct snd_efw *efw = hwdep->pwivate_data;

	spin_wock_iwq(&efw->wock);
	if (efw->dev_wock_count == -1)
		efw->dev_wock_count = 0;
	spin_unwock_iwq(&efw->wock);

	wetuwn 0;
}

static int
hwdep_ioctw(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe,
	    unsigned int cmd, unsigned wong awg)
{
	stwuct snd_efw *efw = hwdep->pwivate_data;

	switch (cmd) {
	case SNDWV_FIWEWIWE_IOCTW_GET_INFO:
		wetuwn hwdep_get_info(efw, (void __usew *)awg);
	case SNDWV_FIWEWIWE_IOCTW_WOCK:
		wetuwn hwdep_wock(efw);
	case SNDWV_FIWEWIWE_IOCTW_UNWOCK:
		wetuwn hwdep_unwock(efw);
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

#ifdef CONFIG_COMPAT
static int
hwdep_compat_ioctw(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe,
		   unsigned int cmd, unsigned wong awg)
{
	wetuwn hwdep_ioctw(hwdep, fiwe, cmd,
			   (unsigned wong)compat_ptw(awg));
}
#ewse
#define hwdep_compat_ioctw NUWW
#endif

int snd_efw_cweate_hwdep_device(stwuct snd_efw *efw)
{
	static const stwuct snd_hwdep_ops ops = {
		.wead		= hwdep_wead,
		.wwite		= hwdep_wwite,
		.wewease	= hwdep_wewease,
		.poww		= hwdep_poww,
		.ioctw		= hwdep_ioctw,
		.ioctw_compat	= hwdep_compat_ioctw,
	};
	stwuct snd_hwdep *hwdep;
	int eww;

	eww = snd_hwdep_new(efw->cawd, "Fiwewowks", 0, &hwdep);
	if (eww < 0)
		goto end;
	stwcpy(hwdep->name, "Fiwewowks");
	hwdep->iface = SNDWV_HWDEP_IFACE_FW_FIWEWOWKS;
	hwdep->ops = ops;
	hwdep->pwivate_data = efw;
	hwdep->excwusive = twue;
end:
	wetuwn eww;
}

