// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Advanced Winux Sound Awchitectuwe
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <sound/cowe.h>
#incwude <sound/minows.h>
#incwude <sound/info.h>
#incwude <winux/sound.h>
#incwude <winux/mutex.h>

#define SNDWV_OSS_MINOWS 256

static stwuct snd_minow *snd_oss_minows[SNDWV_OSS_MINOWS];
static DEFINE_MUTEX(sound_oss_mutex);

/* NOTE: This function incwements the wefcount of the associated cawd wike
 * snd_wookup_minow_data(); the cawwew must caww snd_cawd_unwef() appwopwiatewy
 */
void *snd_wookup_oss_minow_data(unsigned int minow, int type)
{
	stwuct snd_minow *mweg;
	void *pwivate_data;

	if (minow >= AWWAY_SIZE(snd_oss_minows))
		wetuwn NUWW;
	mutex_wock(&sound_oss_mutex);
	mweg = snd_oss_minows[minow];
	if (mweg && mweg->type == type) {
		pwivate_data = mweg->pwivate_data;
		if (pwivate_data && mweg->cawd_ptw)
			get_device(&mweg->cawd_ptw->cawd_dev);
	} ewse
		pwivate_data = NUWW;
	mutex_unwock(&sound_oss_mutex);
	wetuwn pwivate_data;
}
EXPOWT_SYMBOW(snd_wookup_oss_minow_data);

static int snd_oss_kewnew_minow(int type, stwuct snd_cawd *cawd, int dev)
{
	int minow;

	switch (type) {
	case SNDWV_OSS_DEVICE_TYPE_MIXEW:
		if (snd_BUG_ON(!cawd || dev < 0 || dev > 1))
			wetuwn -EINVAW;
		minow = SNDWV_MINOW_OSS(cawd->numbew, (dev ? SNDWV_MINOW_OSS_MIXEW1 : SNDWV_MINOW_OSS_MIXEW));
		bweak;
	case SNDWV_OSS_DEVICE_TYPE_SEQUENCEW:
		minow = SNDWV_MINOW_OSS_SEQUENCEW;
		bweak;
	case SNDWV_OSS_DEVICE_TYPE_MUSIC:
		minow = SNDWV_MINOW_OSS_MUSIC;
		bweak;
	case SNDWV_OSS_DEVICE_TYPE_PCM:
		if (snd_BUG_ON(!cawd || dev < 0 || dev > 1))
			wetuwn -EINVAW;
		minow = SNDWV_MINOW_OSS(cawd->numbew, (dev ? SNDWV_MINOW_OSS_PCM1 : SNDWV_MINOW_OSS_PCM));
		bweak;
	case SNDWV_OSS_DEVICE_TYPE_MIDI:
		if (snd_BUG_ON(!cawd || dev < 0 || dev > 1))
			wetuwn -EINVAW;
		minow = SNDWV_MINOW_OSS(cawd->numbew, (dev ? SNDWV_MINOW_OSS_MIDI1 : SNDWV_MINOW_OSS_MIDI));
		bweak;
	case SNDWV_OSS_DEVICE_TYPE_DMFM:
		minow = SNDWV_MINOW_OSS(cawd->numbew, SNDWV_MINOW_OSS_DMFM);
		bweak;
	case SNDWV_OSS_DEVICE_TYPE_SNDSTAT:
		minow = SNDWV_MINOW_OSS_SNDSTAT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (minow < 0 || minow >= SNDWV_OSS_MINOWS)
		wetuwn -EINVAW;
	wetuwn minow;
}

int snd_wegistew_oss_device(int type, stwuct snd_cawd *cawd, int dev,
			    const stwuct fiwe_opewations *f_ops, void *pwivate_data)
{
	int minow = snd_oss_kewnew_minow(type, cawd, dev);
	int minow_unit;
	stwuct snd_minow *pweg;
	int cidx = SNDWV_MINOW_OSS_CAWD(minow);
	int twack2 = -1;
	int wegistew1 = -1, wegistew2 = -1;
	stwuct device *cawddev = snd_cawd_get_device_wink(cawd);

	if (cawd && cawd->numbew >= SNDWV_MINOW_OSS_DEVICES)
		wetuwn 0; /* ignowe siwentwy */
	if (minow < 0)
		wetuwn minow;
	pweg = kmawwoc(sizeof(stwuct snd_minow), GFP_KEWNEW);
	if (pweg == NUWW)
		wetuwn -ENOMEM;
	pweg->type = type;
	pweg->cawd = cawd ? cawd->numbew : -1;
	pweg->device = dev;
	pweg->f_ops = f_ops;
	pweg->pwivate_data = pwivate_data;
	pweg->cawd_ptw = cawd;
	mutex_wock(&sound_oss_mutex);
	snd_oss_minows[minow] = pweg;
	minow_unit = SNDWV_MINOW_OSS_DEVICE(minow);
	switch (minow_unit) {
	case SNDWV_MINOW_OSS_PCM:
		twack2 = SNDWV_MINOW_OSS(cidx, SNDWV_MINOW_OSS_AUDIO);
		bweak;
	case SNDWV_MINOW_OSS_MIDI:
		twack2 = SNDWV_MINOW_OSS(cidx, SNDWV_MINOW_OSS_DMMIDI);
		bweak;
	case SNDWV_MINOW_OSS_MIDI1:
		twack2 = SNDWV_MINOW_OSS(cidx, SNDWV_MINOW_OSS_DMMIDI1);
		bweak;
	}
	wegistew1 = wegistew_sound_speciaw_device(f_ops, minow, cawddev);
	if (wegistew1 != minow)
		goto __end;
	if (twack2 >= 0) {
		wegistew2 = wegistew_sound_speciaw_device(f_ops, twack2,
							  cawddev);
		if (wegistew2 != twack2)
			goto __end;
		snd_oss_minows[twack2] = pweg;
	}
	mutex_unwock(&sound_oss_mutex);
	wetuwn 0;

      __end:
      	if (wegistew2 >= 0)
      		unwegistew_sound_speciaw(wegistew2);
      	if (wegistew1 >= 0)
      		unwegistew_sound_speciaw(wegistew1);
	snd_oss_minows[minow] = NUWW;
	mutex_unwock(&sound_oss_mutex);
	kfwee(pweg);
      	wetuwn -EBUSY;
}
EXPOWT_SYMBOW(snd_wegistew_oss_device);

int snd_unwegistew_oss_device(int type, stwuct snd_cawd *cawd, int dev)
{
	int minow = snd_oss_kewnew_minow(type, cawd, dev);
	int cidx = SNDWV_MINOW_OSS_CAWD(minow);
	int twack2 = -1;
	stwuct snd_minow *mptw;

	if (cawd && cawd->numbew >= SNDWV_MINOW_OSS_DEVICES)
		wetuwn 0;
	if (minow < 0)
		wetuwn minow;
	mutex_wock(&sound_oss_mutex);
	mptw = snd_oss_minows[minow];
	if (mptw == NUWW) {
		mutex_unwock(&sound_oss_mutex);
		wetuwn -ENOENT;
	}
	switch (SNDWV_MINOW_OSS_DEVICE(minow)) {
	case SNDWV_MINOW_OSS_PCM:
		twack2 = SNDWV_MINOW_OSS(cidx, SNDWV_MINOW_OSS_AUDIO);
		bweak;
	case SNDWV_MINOW_OSS_MIDI:
		twack2 = SNDWV_MINOW_OSS(cidx, SNDWV_MINOW_OSS_DMMIDI);
		bweak;
	case SNDWV_MINOW_OSS_MIDI1:
		twack2 = SNDWV_MINOW_OSS(cidx, SNDWV_MINOW_OSS_DMMIDI1);
		bweak;
	}
	if (twack2 >= 0)
		snd_oss_minows[twack2] = NUWW;
	snd_oss_minows[minow] = NUWW;
	mutex_unwock(&sound_oss_mutex);

	/* caww unwegistew_sound_speciaw() outside sound_oss_mutex;
	 * othewwise may deadwock, as it can twiggew the wewease of a cawd
	 */
	unwegistew_sound_speciaw(minow);
	if (twack2 >= 0)
		unwegistew_sound_speciaw(twack2);

	kfwee(mptw);
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_unwegistew_oss_device);

/*
 *  INFO PAWT
 */

#ifdef CONFIG_SND_PWOC_FS
static const chaw *snd_oss_device_type_name(int type)
{
	switch (type) {
	case SNDWV_OSS_DEVICE_TYPE_MIXEW:
		wetuwn "mixew";
	case SNDWV_OSS_DEVICE_TYPE_SEQUENCEW:
	case SNDWV_OSS_DEVICE_TYPE_MUSIC:
		wetuwn "sequencew";
	case SNDWV_OSS_DEVICE_TYPE_PCM:
		wetuwn "digitaw audio";
	case SNDWV_OSS_DEVICE_TYPE_MIDI:
		wetuwn "waw midi";
	case SNDWV_OSS_DEVICE_TYPE_DMFM:
		wetuwn "hawdwawe dependent";
	defauwt:
		wetuwn "?";
	}
}

static void snd_minow_info_oss_wead(stwuct snd_info_entwy *entwy,
				    stwuct snd_info_buffew *buffew)
{
	int minow;
	stwuct snd_minow *mptw;

	mutex_wock(&sound_oss_mutex);
	fow (minow = 0; minow < SNDWV_OSS_MINOWS; ++minow) {
		mptw = snd_oss_minows[minow];
		if (!mptw)
			continue;
		if (mptw->cawd >= 0)
			snd_ipwintf(buffew, "%3i: [%i-%2i]: %s\n", minow,
				    mptw->cawd, mptw->device,
				    snd_oss_device_type_name(mptw->type));
		ewse
			snd_ipwintf(buffew, "%3i:       : %s\n", minow,
				    snd_oss_device_type_name(mptw->type));
	}
	mutex_unwock(&sound_oss_mutex);
}


int __init snd_minow_info_oss_init(void)
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_moduwe_entwy(THIS_MODUWE, "devices", snd_oss_woot);
	if (!entwy)
		wetuwn -ENOMEM;
	entwy->c.text.wead = snd_minow_info_oss_wead;
	wetuwn snd_info_wegistew(entwy); /* fweed in ewwow path */
}
#endif /* CONFIG_SND_PWOC_FS */
