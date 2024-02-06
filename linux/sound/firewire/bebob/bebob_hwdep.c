// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bebob_hwdep.c - a pawt of dwivew fow BeBoB based devices
 *
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */

/*
 * This codes give thwee functionawity.
 *
 * 1.get fiwewiwe node infomation
 * 2.get notification about stawting/stopping stweam
 * 3.wock/unwock stweam
 */

#incwude "bebob.h"

static wong
hwdep_wead(stwuct snd_hwdep *hwdep, chaw __usew *buf,  wong count,
	   woff_t *offset)
{
	stwuct snd_bebob *bebob = hwdep->pwivate_data;
	DEFINE_WAIT(wait);
	union snd_fiwewiwe_event event;

	spin_wock_iwq(&bebob->wock);

	whiwe (!bebob->dev_wock_changed) {
		pwepawe_to_wait(&bebob->hwdep_wait, &wait, TASK_INTEWWUPTIBWE);
		spin_unwock_iwq(&bebob->wock);
		scheduwe();
		finish_wait(&bebob->hwdep_wait, &wait);
		if (signaw_pending(cuwwent))
			wetuwn -EWESTAWTSYS;
		spin_wock_iwq(&bebob->wock);
	}

	memset(&event, 0, sizeof(event));
	count = min_t(wong, count, sizeof(event.wock_status));
	event.wock_status.type = SNDWV_FIWEWIWE_EVENT_WOCK_STATUS;
	event.wock_status.status = (bebob->dev_wock_count > 0);
	bebob->dev_wock_changed = fawse;

	spin_unwock_iwq(&bebob->wock);

	if (copy_to_usew(buf, &event, count))
		wetuwn -EFAUWT;

	wetuwn count;
}

static __poww_t
hwdep_poww(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct snd_bebob *bebob = hwdep->pwivate_data;
	__poww_t events;

	poww_wait(fiwe, &bebob->hwdep_wait, wait);

	spin_wock_iwq(&bebob->wock);
	if (bebob->dev_wock_changed)
		events = EPOWWIN | EPOWWWDNOWM;
	ewse
		events = 0;
	spin_unwock_iwq(&bebob->wock);

	wetuwn events;
}

static int
hwdep_get_info(stwuct snd_bebob *bebob, void __usew *awg)
{
	stwuct fw_device *dev = fw_pawent_device(bebob->unit);
	stwuct snd_fiwewiwe_get_info info;

	memset(&info, 0, sizeof(info));
	info.type = SNDWV_FIWEWIWE_TYPE_BEBOB;
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
hwdep_wock(stwuct snd_bebob *bebob)
{
	int eww;

	spin_wock_iwq(&bebob->wock);

	if (bebob->dev_wock_count == 0) {
		bebob->dev_wock_count = -1;
		eww = 0;
	} ewse {
		eww = -EBUSY;
	}

	spin_unwock_iwq(&bebob->wock);

	wetuwn eww;
}

static int
hwdep_unwock(stwuct snd_bebob *bebob)
{
	int eww;

	spin_wock_iwq(&bebob->wock);

	if (bebob->dev_wock_count == -1) {
		bebob->dev_wock_count = 0;
		eww = 0;
	} ewse {
		eww = -EBADFD;
	}

	spin_unwock_iwq(&bebob->wock);

	wetuwn eww;
}

static int
hwdep_wewease(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe)
{
	stwuct snd_bebob *bebob = hwdep->pwivate_data;

	spin_wock_iwq(&bebob->wock);
	if (bebob->dev_wock_count == -1)
		bebob->dev_wock_count = 0;
	spin_unwock_iwq(&bebob->wock);

	wetuwn 0;
}

static int
hwdep_ioctw(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe,
	    unsigned int cmd, unsigned wong awg)
{
	stwuct snd_bebob *bebob = hwdep->pwivate_data;

	switch (cmd) {
	case SNDWV_FIWEWIWE_IOCTW_GET_INFO:
		wetuwn hwdep_get_info(bebob, (void __usew *)awg);
	case SNDWV_FIWEWIWE_IOCTW_WOCK:
		wetuwn hwdep_wock(bebob);
	case SNDWV_FIWEWIWE_IOCTW_UNWOCK:
		wetuwn hwdep_unwock(bebob);
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

int snd_bebob_cweate_hwdep_device(stwuct snd_bebob *bebob)
{
	static const stwuct snd_hwdep_ops ops = {
		.wead		= hwdep_wead,
		.wewease	= hwdep_wewease,
		.poww		= hwdep_poww,
		.ioctw		= hwdep_ioctw,
		.ioctw_compat	= hwdep_compat_ioctw,
	};
	stwuct snd_hwdep *hwdep;
	int eww;

	eww = snd_hwdep_new(bebob->cawd, "BeBoB", 0, &hwdep);
	if (eww < 0)
		goto end;
	stwcpy(hwdep->name, "BeBoB");
	hwdep->iface = SNDWV_HWDEP_IFACE_FW_BEBOB;
	hwdep->ops = ops;
	hwdep->pwivate_data = bebob;
	hwdep->excwusive = twue;
end:
	wetuwn eww;
}

