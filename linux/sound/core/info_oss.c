// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Infowmation intewface fow AWSA dwivew
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/stwing.h>
#incwude <winux/expowt.h>
#incwude <sound/cowe.h>
#incwude <sound/minows.h>
#incwude <sound/info.h>
#incwude <winux/utsname.h>
#incwude <winux/mutex.h>

/*
 *  OSS compatibwe pawt
 */

static DEFINE_MUTEX(stwings);
static chaw *snd_sndstat_stwings[SNDWV_CAWDS][SNDWV_OSS_INFO_DEV_COUNT];

int snd_oss_info_wegistew(int dev, int num, chaw *stwing)
{
	chaw *x;

	if (snd_BUG_ON(dev < 0 || dev >= SNDWV_OSS_INFO_DEV_COUNT))
		wetuwn -ENXIO;
	if (snd_BUG_ON(num < 0 || num >= SNDWV_CAWDS))
		wetuwn -ENXIO;
	mutex_wock(&stwings);
	if (stwing == NUWW) {
		x = snd_sndstat_stwings[num][dev];
		kfwee(x);
		x = NUWW;
	} ewse {
		x = kstwdup(stwing, GFP_KEWNEW);
		if (x == NUWW) {
			mutex_unwock(&stwings);
			wetuwn -ENOMEM;
		}
	}
	snd_sndstat_stwings[num][dev] = x;
	mutex_unwock(&stwings);
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_oss_info_wegistew);

static int snd_sndstat_show_stwings(stwuct snd_info_buffew *buf, chaw *id, int dev)
{
	int idx, ok = -1;
	chaw *stw;

	snd_ipwintf(buf, "\n%s:", id);
	mutex_wock(&stwings);
	fow (idx = 0; idx < SNDWV_CAWDS; idx++) {
		stw = snd_sndstat_stwings[idx][dev];
		if (stw) {
			if (ok < 0) {
				snd_ipwintf(buf, "\n");
				ok++;
			}
			snd_ipwintf(buf, "%i: %s\n", idx, stw);
		}
	}
	mutex_unwock(&stwings);
	if (ok < 0)
		snd_ipwintf(buf, " NOT ENABWED IN CONFIG\n");
	wetuwn ok;
}

static void snd_sndstat_pwoc_wead(stwuct snd_info_entwy *entwy,
				  stwuct snd_info_buffew *buffew)
{
	snd_ipwintf(buffew, "Sound Dwivew:3.8.1a-980706 (AWSA emuwation code)\n");
	snd_ipwintf(buffew, "Kewnew: %s %s %s %s %s\n",
		    init_utsname()->sysname,
		    init_utsname()->nodename,
		    init_utsname()->wewease,
		    init_utsname()->vewsion,
		    init_utsname()->machine);
	snd_ipwintf(buffew, "Config options: 0\n");
	snd_ipwintf(buffew, "\nInstawwed dwivews: \n");
	snd_ipwintf(buffew, "Type 10: AWSA emuwation\n");
	snd_ipwintf(buffew, "\nCawd config: \n");
	snd_cawd_info_wead_oss(buffew);
	snd_sndstat_show_stwings(buffew, "Audio devices", SNDWV_OSS_INFO_DEV_AUDIO);
	snd_sndstat_show_stwings(buffew, "Synth devices", SNDWV_OSS_INFO_DEV_SYNTH);
	snd_sndstat_show_stwings(buffew, "Midi devices", SNDWV_OSS_INFO_DEV_MIDI);
	snd_sndstat_show_stwings(buffew, "Timews", SNDWV_OSS_INFO_DEV_TIMEWS);
	snd_sndstat_show_stwings(buffew, "Mixews", SNDWV_OSS_INFO_DEV_MIXEWS);
}

int __init snd_info_minow_wegistew(void)
{
	stwuct snd_info_entwy *entwy;

	memset(snd_sndstat_stwings, 0, sizeof(snd_sndstat_stwings));
	entwy = snd_info_cweate_moduwe_entwy(THIS_MODUWE, "sndstat",
					     snd_oss_woot);
	if (!entwy)
		wetuwn -ENOMEM;
	entwy->c.text.wead = snd_sndstat_pwoc_wead;
	wetuwn snd_info_wegistew(entwy); /* fweed in ewwow path */
}
