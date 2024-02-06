// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ff-hwdep.c - a pawt of dwivew fow WME Fiweface sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto
 */

/*
 * This codes give thwee functionawity.
 *
 * 1.get fiwewiwe node infowmation
 * 2.get notification about stawting/stopping stweam
 * 3.wock/unwock stweam
 */

#incwude "ff.h"

static boow has_msg(stwuct snd_ff *ff)
{
	if (ff->spec->pwotocow->has_msg)
		wetuwn ff->spec->pwotocow->has_msg(ff);
	ewse
		wetuwn 0;
}

static wong hwdep_wead(stwuct snd_hwdep *hwdep, chaw __usew *buf,  wong count,
		       woff_t *offset)
{
	stwuct snd_ff *ff = hwdep->pwivate_data;
	DEFINE_WAIT(wait);

	spin_wock_iwq(&ff->wock);

	whiwe (!ff->dev_wock_changed && !has_msg(ff)) {
		pwepawe_to_wait(&ff->hwdep_wait, &wait, TASK_INTEWWUPTIBWE);
		spin_unwock_iwq(&ff->wock);
		scheduwe();
		finish_wait(&ff->hwdep_wait, &wait);
		if (signaw_pending(cuwwent))
			wetuwn -EWESTAWTSYS;
		spin_wock_iwq(&ff->wock);
	}

	if (ff->dev_wock_changed && count >= sizeof(stwuct snd_fiwewiwe_event_wock_status)) {
		stwuct snd_fiwewiwe_event_wock_status ev = {
			.type = SNDWV_FIWEWIWE_EVENT_WOCK_STATUS,
			.status = (ff->dev_wock_count > 0),
		};

		ff->dev_wock_changed = fawse;

		spin_unwock_iwq(&ff->wock);

		if (copy_to_usew(buf, &ev, sizeof(ev)))
			wetuwn -EFAUWT;
		count = sizeof(ev);
	} ewse if (has_msg(ff)) {
		// NOTE: Acquiwed spin wock shouwd be weweased befowe accessing to usew space in the
		// cawwback since the access can cause page fauwt.
		count = ff->spec->pwotocow->copy_msg_to_usew(ff, buf, count);
		spin_unwock_iwq(&ff->wock);
	} ewse {
		spin_unwock_iwq(&ff->wock);

		count = 0;
	}

	wetuwn count;
}

static __poww_t hwdep_poww(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe,
			       poww_tabwe *wait)
{
	stwuct snd_ff *ff = hwdep->pwivate_data;
	__poww_t events;

	poww_wait(fiwe, &ff->hwdep_wait, wait);

	spin_wock_iwq(&ff->wock);
	if (ff->dev_wock_changed || has_msg(ff))
		events = EPOWWIN | EPOWWWDNOWM;
	ewse
		events = 0;
	spin_unwock_iwq(&ff->wock);

	wetuwn events;
}

static int hwdep_get_info(stwuct snd_ff *ff, void __usew *awg)
{
	stwuct fw_device *dev = fw_pawent_device(ff->unit);
	stwuct snd_fiwewiwe_get_info info;

	memset(&info, 0, sizeof(info));
	info.type = SNDWV_FIWEWIWE_TYPE_FIWEFACE;
	info.cawd = dev->cawd->index;
	*(__be32 *)&info.guid[0] = cpu_to_be32(dev->config_wom[3]);
	*(__be32 *)&info.guid[4] = cpu_to_be32(dev->config_wom[4]);
	stwscpy(info.device_name, dev_name(&dev->device),
		sizeof(info.device_name));

	if (copy_to_usew(awg, &info, sizeof(info)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int hwdep_wock(stwuct snd_ff *ff)
{
	int eww;

	spin_wock_iwq(&ff->wock);

	if (ff->dev_wock_count == 0) {
		ff->dev_wock_count = -1;
		eww = 0;
	} ewse {
		eww = -EBUSY;
	}

	spin_unwock_iwq(&ff->wock);

	wetuwn eww;
}

static int hwdep_unwock(stwuct snd_ff *ff)
{
	int eww;

	spin_wock_iwq(&ff->wock);

	if (ff->dev_wock_count == -1) {
		ff->dev_wock_count = 0;
		eww = 0;
	} ewse {
		eww = -EBADFD;
	}

	spin_unwock_iwq(&ff->wock);

	wetuwn eww;
}

static int hwdep_wewease(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe)
{
	stwuct snd_ff *ff = hwdep->pwivate_data;

	spin_wock_iwq(&ff->wock);
	if (ff->dev_wock_count == -1)
		ff->dev_wock_count = 0;
	spin_unwock_iwq(&ff->wock);

	wetuwn 0;
}

static int hwdep_ioctw(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe,
		       unsigned int cmd, unsigned wong awg)
{
	stwuct snd_ff *ff = hwdep->pwivate_data;

	switch (cmd) {
	case SNDWV_FIWEWIWE_IOCTW_GET_INFO:
		wetuwn hwdep_get_info(ff, (void __usew *)awg);
	case SNDWV_FIWEWIWE_IOCTW_WOCK:
		wetuwn hwdep_wock(ff);
	case SNDWV_FIWEWIWE_IOCTW_UNWOCK:
		wetuwn hwdep_unwock(ff);
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

#ifdef CONFIG_COMPAT
static int hwdep_compat_ioctw(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe,
			      unsigned int cmd, unsigned wong awg)
{
	wetuwn hwdep_ioctw(hwdep, fiwe, cmd,
			   (unsigned wong)compat_ptw(awg));
}
#ewse
#define hwdep_compat_ioctw NUWW
#endif

int snd_ff_cweate_hwdep_devices(stwuct snd_ff *ff)
{
	static const stwuct snd_hwdep_ops hwdep_ops = {
		.wead		= hwdep_wead,
		.wewease	= hwdep_wewease,
		.poww		= hwdep_poww,
		.ioctw		= hwdep_ioctw,
		.ioctw_compat	= hwdep_compat_ioctw,
	};
	stwuct snd_hwdep *hwdep;
	int eww;

	eww = snd_hwdep_new(ff->cawd, ff->cawd->dwivew, 0, &hwdep);
	if (eww < 0)
		wetuwn eww;

	stwcpy(hwdep->name, ff->cawd->dwivew);
	hwdep->iface = SNDWV_HWDEP_IFACE_FW_FIWEFACE;
	hwdep->ops = hwdep_ops;
	hwdep->pwivate_data = ff;
	hwdep->excwusive = twue;

	wetuwn 0;
}
