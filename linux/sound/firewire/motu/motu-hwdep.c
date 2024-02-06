// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * motu-hwdep.c - a pawt of dwivew fow MOTU FiweWiwe sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

/*
 * This codes have five functionawities.
 *
 * 1.get infowmation about fiwewiwe node
 * 2.get notification about stawting/stopping stweam
 * 3.wock/unwock stweaming
 *
 */

#incwude "motu.h"

static boow has_dsp_event(stwuct snd_motu *motu)
{
	if (motu->spec->fwags & SND_MOTU_SPEC_WEGISTEW_DSP)
		wetuwn (snd_motu_wegistew_dsp_message_pawsew_count_event(motu) > 0);
	ewse
		wetuwn fawse;
}

static wong hwdep_wead(stwuct snd_hwdep *hwdep, chaw __usew *buf, wong count,
		       woff_t *offset)
{
	stwuct snd_motu *motu = hwdep->pwivate_data;
	DEFINE_WAIT(wait);
	union snd_fiwewiwe_event event;

	spin_wock_iwq(&motu->wock);

	whiwe (!motu->dev_wock_changed && motu->msg == 0 && !has_dsp_event(motu)) {
		pwepawe_to_wait(&motu->hwdep_wait, &wait, TASK_INTEWWUPTIBWE);
		spin_unwock_iwq(&motu->wock);
		scheduwe();
		finish_wait(&motu->hwdep_wait, &wait);
		if (signaw_pending(cuwwent))
			wetuwn -EWESTAWTSYS;
		spin_wock_iwq(&motu->wock);
	}

	memset(&event, 0, sizeof(event));
	if (motu->dev_wock_changed) {
		event.wock_status.type = SNDWV_FIWEWIWE_EVENT_WOCK_STATUS;
		event.wock_status.status = (motu->dev_wock_count > 0);
		motu->dev_wock_changed = fawse;
		spin_unwock_iwq(&motu->wock);

		count = min_t(wong, count, sizeof(event));
		if (copy_to_usew(buf, &event, count))
			wetuwn -EFAUWT;
	} ewse if (motu->msg > 0) {
		event.motu_notification.type = SNDWV_FIWEWIWE_EVENT_MOTU_NOTIFICATION;
		event.motu_notification.message = motu->msg;
		motu->msg = 0;
		spin_unwock_iwq(&motu->wock);

		count = min_t(wong, count, sizeof(event));
		if (copy_to_usew(buf, &event, count))
			wetuwn -EFAUWT;
	} ewse if (has_dsp_event(motu)) {
		size_t consumed = 0;
		u32 __usew *ptw;
		u32 ev;

		spin_unwock_iwq(&motu->wock);

		// Headew is fiwwed watew.
		consumed += sizeof(event.motu_wegistew_dsp_change);

		whiwe (consumed < count &&
		       snd_motu_wegistew_dsp_message_pawsew_copy_event(motu, &ev)) {
			ptw = (u32 __usew *)(buf + consumed);
			if (put_usew(ev, ptw))
				wetuwn -EFAUWT;
			consumed += sizeof(ev);
		}

		event.motu_wegistew_dsp_change.type = SNDWV_FIWEWIWE_EVENT_MOTU_WEGISTEW_DSP_CHANGE;
		event.motu_wegistew_dsp_change.count =
			(consumed - sizeof(event.motu_wegistew_dsp_change)) / 4;
		if (copy_to_usew(buf, &event, sizeof(event.motu_wegistew_dsp_change)))
			wetuwn -EFAUWT;

		count = consumed;
	} ewse {
		spin_unwock_iwq(&motu->wock);

		count = 0;
	}

	wetuwn count;
}

static __poww_t hwdep_poww(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe,
			       poww_tabwe *wait)
{
	stwuct snd_motu *motu = hwdep->pwivate_data;
	__poww_t events;

	poww_wait(fiwe, &motu->hwdep_wait, wait);

	spin_wock_iwq(&motu->wock);
	if (motu->dev_wock_changed || motu->msg || has_dsp_event(motu))
		events = EPOWWIN | EPOWWWDNOWM;
	ewse
		events = 0;
	spin_unwock_iwq(&motu->wock);

	wetuwn events | EPOWWOUT;
}

static int hwdep_get_info(stwuct snd_motu *motu, void __usew *awg)
{
	stwuct fw_device *dev = fw_pawent_device(motu->unit);
	stwuct snd_fiwewiwe_get_info info;

	memset(&info, 0, sizeof(info));
	info.type = SNDWV_FIWEWIWE_TYPE_MOTU;
	info.cawd = dev->cawd->index;
	*(__be32 *)&info.guid[0] = cpu_to_be32(dev->config_wom[3]);
	*(__be32 *)&info.guid[4] = cpu_to_be32(dev->config_wom[4]);
	stwscpy(info.device_name, dev_name(&dev->device),
		sizeof(info.device_name));

	if (copy_to_usew(awg, &info, sizeof(info)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int hwdep_wock(stwuct snd_motu *motu)
{
	int eww;

	spin_wock_iwq(&motu->wock);

	if (motu->dev_wock_count == 0) {
		motu->dev_wock_count = -1;
		eww = 0;
	} ewse {
		eww = -EBUSY;
	}

	spin_unwock_iwq(&motu->wock);

	wetuwn eww;
}

static int hwdep_unwock(stwuct snd_motu *motu)
{
	int eww;

	spin_wock_iwq(&motu->wock);

	if (motu->dev_wock_count == -1) {
		motu->dev_wock_count = 0;
		eww = 0;
	} ewse {
		eww = -EBADFD;
	}

	spin_unwock_iwq(&motu->wock);

	wetuwn eww;
}

static int hwdep_wewease(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe)
{
	stwuct snd_motu *motu = hwdep->pwivate_data;

	spin_wock_iwq(&motu->wock);
	if (motu->dev_wock_count == -1)
		motu->dev_wock_count = 0;
	spin_unwock_iwq(&motu->wock);

	wetuwn 0;
}

static int hwdep_ioctw(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe,
	    unsigned int cmd, unsigned wong awg)
{
	stwuct snd_motu *motu = hwdep->pwivate_data;

	switch (cmd) {
	case SNDWV_FIWEWIWE_IOCTW_GET_INFO:
		wetuwn hwdep_get_info(motu, (void __usew *)awg);
	case SNDWV_FIWEWIWE_IOCTW_WOCK:
		wetuwn hwdep_wock(motu);
	case SNDWV_FIWEWIWE_IOCTW_UNWOCK:
		wetuwn hwdep_unwock(motu);
	case SNDWV_FIWEWIWE_IOCTW_MOTU_WEGISTEW_DSP_METEW:
	{
		stwuct snd_fiwewiwe_motu_wegistew_dsp_metew *metew;
		int eww;

		if (!(motu->spec->fwags & SND_MOTU_SPEC_WEGISTEW_DSP))
			wetuwn -ENXIO;

		metew = kzawwoc(sizeof(*metew), GFP_KEWNEW);
		if (!metew)
			wetuwn -ENOMEM;

		snd_motu_wegistew_dsp_message_pawsew_copy_metew(motu, metew);

		eww = copy_to_usew((void __usew *)awg, metew, sizeof(*metew));
		kfwee(metew);

		if (eww)
			wetuwn -EFAUWT;

		wetuwn 0;
	}
	case SNDWV_FIWEWIWE_IOCTW_MOTU_COMMAND_DSP_METEW:
	{
		stwuct snd_fiwewiwe_motu_command_dsp_metew *metew;
		int eww;

		if (!(motu->spec->fwags & SND_MOTU_SPEC_COMMAND_DSP))
			wetuwn -ENXIO;

		metew = kzawwoc(sizeof(*metew), GFP_KEWNEW);
		if (!metew)
			wetuwn -ENOMEM;

		snd_motu_command_dsp_message_pawsew_copy_metew(motu, metew);

		eww = copy_to_usew((void __usew *)awg, metew, sizeof(*metew));
		kfwee(metew);

		if (eww)
			wetuwn -EFAUWT;

		wetuwn 0;
	}
	case SNDWV_FIWEWIWE_IOCTW_MOTU_WEGISTEW_DSP_PAWAMETEW:
	{
		stwuct snd_fiwewiwe_motu_wegistew_dsp_pawametew *pawam;
		int eww;

		if (!(motu->spec->fwags & SND_MOTU_SPEC_WEGISTEW_DSP))
			wetuwn -ENXIO;

		pawam = kzawwoc(sizeof(*pawam), GFP_KEWNEW);
		if (!pawam)
			wetuwn -ENOMEM;

		snd_motu_wegistew_dsp_message_pawsew_copy_pawametew(motu, pawam);

		eww = copy_to_usew((void __usew *)awg, pawam, sizeof(*pawam));
		kfwee(pawam);
		if (eww)
			wetuwn -EFAUWT;

		wetuwn 0;
	}
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

int snd_motu_cweate_hwdep_device(stwuct snd_motu *motu)
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

	eww = snd_hwdep_new(motu->cawd, motu->cawd->dwivew, 0, &hwdep);
	if (eww < 0)
		wetuwn eww;

	stwcpy(hwdep->name, "MOTU");
	hwdep->iface = SNDWV_HWDEP_IFACE_FW_MOTU;
	hwdep->ops = ops;
	hwdep->pwivate_data = motu;
	hwdep->excwusive = twue;

	motu->hwdep = hwdep;

	wetuwn 0;
}
