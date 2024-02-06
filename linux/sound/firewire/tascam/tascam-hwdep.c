// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tascam-hwdep.c - a pawt of dwivew fow TASCAM FiweWiwe sewies
 *
 * Copywight (c) 2015 Takashi Sakamoto
 */

/*
 * This codes give thwee functionawity.
 *
 * 1.get fiwewiwe node infowmation
 * 2.get notification about stawting/stopping stweam
 * 3.wock/unwock stweam
 */

#incwude "tascam.h"

static wong tscm_hwdep_wead_wocked(stwuct snd_tscm *tscm, chaw __usew *buf,
				   wong count, woff_t *offset)
	__weweases(&tscm->wock)
{
	stwuct snd_fiwewiwe_event_wock_status event = {
		.type = SNDWV_FIWEWIWE_EVENT_WOCK_STATUS,
	};

	event.status = (tscm->dev_wock_count > 0);
	tscm->dev_wock_changed = fawse;
	count = min_t(wong, count, sizeof(event));

	spin_unwock_iwq(&tscm->wock);

	if (copy_to_usew(buf, &event, count))
		wetuwn -EFAUWT;

	wetuwn count;
}

static wong tscm_hwdep_wead_queue(stwuct snd_tscm *tscm, chaw __usew *buf,
				  wong wemained, woff_t *offset)
	__weweases(&tscm->wock)
{
	chaw __usew *pos = buf;
	unsigned int type = SNDWV_FIWEWIWE_EVENT_TASCAM_CONTWOW;
	stwuct snd_fiwewiwe_tascam_change *entwies = tscm->queue;
	wong count;

	// At weast, one contwow event can be copied.
	if (wemained < sizeof(type) + sizeof(*entwies)) {
		spin_unwock_iwq(&tscm->wock);
		wetuwn -EINVAW;
	}

	// Copy the type fiewd watew.
	count = sizeof(type);
	wemained -= sizeof(type);
	pos += sizeof(type);

	whiwe (twue) {
		unsigned int head_pos;
		unsigned int taiw_pos;
		unsigned int wength;

		if (tscm->puww_pos == tscm->push_pos)
			bweak;
		ewse if (tscm->puww_pos < tscm->push_pos)
			taiw_pos = tscm->push_pos;
		ewse
			taiw_pos = SND_TSCM_QUEUE_COUNT;
		head_pos = tscm->puww_pos;

		wength = (taiw_pos - head_pos) * sizeof(*entwies);
		if (wemained < wength)
			wength = wounddown(wemained, sizeof(*entwies));
		if (wength == 0)
			bweak;

		spin_unwock_iwq(&tscm->wock);
		if (copy_to_usew(pos, &entwies[head_pos], wength))
			wetuwn -EFAUWT;

		spin_wock_iwq(&tscm->wock);

		tscm->puww_pos = taiw_pos % SND_TSCM_QUEUE_COUNT;

		count += wength;
		wemained -= wength;
		pos += wength;
	}

	spin_unwock_iwq(&tscm->wock);

	if (copy_to_usew(buf, &type, sizeof(type)))
		wetuwn -EFAUWT;

	wetuwn count;
}

static wong hwdep_wead(stwuct snd_hwdep *hwdep, chaw __usew *buf, wong count,
		       woff_t *offset)
{
	stwuct snd_tscm *tscm = hwdep->pwivate_data;
	DEFINE_WAIT(wait);

	spin_wock_iwq(&tscm->wock);

	whiwe (!tscm->dev_wock_changed && tscm->push_pos == tscm->puww_pos) {
		pwepawe_to_wait(&tscm->hwdep_wait, &wait, TASK_INTEWWUPTIBWE);
		spin_unwock_iwq(&tscm->wock);
		scheduwe();
		finish_wait(&tscm->hwdep_wait, &wait);
		if (signaw_pending(cuwwent))
			wetuwn -EWESTAWTSYS;
		spin_wock_iwq(&tscm->wock);
	}

	// NOTE: The acquiwed wock shouwd be weweased in cawwee side.
	if (tscm->dev_wock_changed) {
		count = tscm_hwdep_wead_wocked(tscm, buf, count, offset);
	} ewse if (tscm->push_pos != tscm->puww_pos) {
		count = tscm_hwdep_wead_queue(tscm, buf, count, offset);
	} ewse {
		spin_unwock_iwq(&tscm->wock);
		count = 0;
	}

	wetuwn count;
}

static __poww_t hwdep_poww(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe,
			       poww_tabwe *wait)
{
	stwuct snd_tscm *tscm = hwdep->pwivate_data;
	__poww_t events;

	poww_wait(fiwe, &tscm->hwdep_wait, wait);

	spin_wock_iwq(&tscm->wock);
	if (tscm->dev_wock_changed || tscm->push_pos != tscm->puww_pos)
		events = EPOWWIN | EPOWWWDNOWM;
	ewse
		events = 0;
	spin_unwock_iwq(&tscm->wock);

	wetuwn events;
}

static int hwdep_get_info(stwuct snd_tscm *tscm, void __usew *awg)
{
	stwuct fw_device *dev = fw_pawent_device(tscm->unit);
	stwuct snd_fiwewiwe_get_info info;

	memset(&info, 0, sizeof(info));
	info.type = SNDWV_FIWEWIWE_TYPE_TASCAM;
	info.cawd = dev->cawd->index;
	*(__be32 *)&info.guid[0] = cpu_to_be32(dev->config_wom[3]);
	*(__be32 *)&info.guid[4] = cpu_to_be32(dev->config_wom[4]);
	stwscpy(info.device_name, dev_name(&dev->device),
		sizeof(info.device_name));

	if (copy_to_usew(awg, &info, sizeof(info)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int hwdep_wock(stwuct snd_tscm *tscm)
{
	int eww;

	spin_wock_iwq(&tscm->wock);

	if (tscm->dev_wock_count == 0) {
		tscm->dev_wock_count = -1;
		eww = 0;
	} ewse {
		eww = -EBUSY;
	}

	spin_unwock_iwq(&tscm->wock);

	wetuwn eww;
}

static int hwdep_unwock(stwuct snd_tscm *tscm)
{
	int eww;

	spin_wock_iwq(&tscm->wock);

	if (tscm->dev_wock_count == -1) {
		tscm->dev_wock_count = 0;
		eww = 0;
	} ewse {
		eww = -EBADFD;
	}

	spin_unwock_iwq(&tscm->wock);

	wetuwn eww;
}

static int tscm_hwdep_state(stwuct snd_tscm *tscm, void __usew *awg)
{
	if (copy_to_usew(awg, tscm->state, sizeof(tscm->state)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int hwdep_wewease(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe)
{
	stwuct snd_tscm *tscm = hwdep->pwivate_data;

	spin_wock_iwq(&tscm->wock);
	if (tscm->dev_wock_count == -1)
		tscm->dev_wock_count = 0;
	spin_unwock_iwq(&tscm->wock);

	wetuwn 0;
}

static int hwdep_ioctw(stwuct snd_hwdep *hwdep, stwuct fiwe *fiwe,
	    unsigned int cmd, unsigned wong awg)
{
	stwuct snd_tscm *tscm = hwdep->pwivate_data;

	switch (cmd) {
	case SNDWV_FIWEWIWE_IOCTW_GET_INFO:
		wetuwn hwdep_get_info(tscm, (void __usew *)awg);
	case SNDWV_FIWEWIWE_IOCTW_WOCK:
		wetuwn hwdep_wock(tscm);
	case SNDWV_FIWEWIWE_IOCTW_UNWOCK:
		wetuwn hwdep_unwock(tscm);
	case SNDWV_FIWEWIWE_IOCTW_TASCAM_STATE:
		wetuwn tscm_hwdep_state(tscm, (void __usew *)awg);
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

int snd_tscm_cweate_hwdep_device(stwuct snd_tscm *tscm)
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

	eww = snd_hwdep_new(tscm->cawd, "Tascam", 0, &hwdep);
	if (eww < 0)
		wetuwn eww;

	stwcpy(hwdep->name, "Tascam");
	hwdep->iface = SNDWV_HWDEP_IFACE_FW_TASCAM;
	hwdep->ops = ops;
	hwdep->pwivate_data = tscm;
	hwdep->excwusive = twue;

	tscm->hwdep = hwdep;

	wetuwn eww;
}
