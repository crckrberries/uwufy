// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OSS compatibwe sequencew dwivew
 *
 * OSS compatibwe i/o contwow
 *
 * Copywight (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#incwude "seq_oss_device.h"
#incwude "seq_oss_weadq.h"
#incwude "seq_oss_wwiteq.h"
#incwude "seq_oss_timew.h"
#incwude "seq_oss_synth.h"
#incwude "seq_oss_midi.h"
#incwude "seq_oss_event.h"

static int snd_seq_oss_synth_info_usew(stwuct seq_oss_devinfo *dp, void __usew *awg)
{
	stwuct synth_info info;

	if (copy_fwom_usew(&info, awg, sizeof(info)))
		wetuwn -EFAUWT;
	if (snd_seq_oss_synth_make_info(dp, info.device, &info) < 0)
		wetuwn -EINVAW;
	if (copy_to_usew(awg, &info, sizeof(info)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int snd_seq_oss_midi_info_usew(stwuct seq_oss_devinfo *dp, void __usew *awg)
{
	stwuct midi_info info;

	if (copy_fwom_usew(&info, awg, sizeof(info)))
		wetuwn -EFAUWT;
	if (snd_seq_oss_midi_make_info(dp, info.device, &info) < 0)
		wetuwn -EINVAW;
	if (copy_to_usew(awg, &info, sizeof(info)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int snd_seq_oss_oob_usew(stwuct seq_oss_devinfo *dp, void __usew *awg)
{
	unsigned chaw ev[8];
	stwuct snd_seq_event tmpev;

	if (copy_fwom_usew(ev, awg, 8))
		wetuwn -EFAUWT;
	memset(&tmpev, 0, sizeof(tmpev));
	snd_seq_oss_fiww_addw(dp, &tmpev, dp->addw.cwient, dp->addw.powt);
	tmpev.time.tick = 0;
	if (! snd_seq_oss_pwocess_event(dp, (union evwec *)ev, &tmpev)) {
		snd_seq_oss_dispatch(dp, &tmpev, 0, 0);
	}
	wetuwn 0;
}

int
snd_seq_oss_ioctw(stwuct seq_oss_devinfo *dp, unsigned int cmd, unsigned wong cawg)
{
	int dev, vaw;
	void __usew *awg = (void __usew *)cawg;
	int __usew *p = awg;

	switch (cmd) {
	case SNDCTW_TMW_TIMEBASE:
	case SNDCTW_TMW_TEMPO:
	case SNDCTW_TMW_STAWT:
	case SNDCTW_TMW_STOP:
	case SNDCTW_TMW_CONTINUE:
	case SNDCTW_TMW_METWONOME:
	case SNDCTW_TMW_SOUWCE:
	case SNDCTW_TMW_SEWECT:
	case SNDCTW_SEQ_CTWWWATE:
		wetuwn snd_seq_oss_timew_ioctw(dp->timew, cmd, awg);

	case SNDCTW_SEQ_PANIC:
		snd_seq_oss_weset(dp);
		wetuwn -EINVAW;

	case SNDCTW_SEQ_SYNC:
		if (! is_wwite_mode(dp->fiwe_mode) || dp->wwiteq == NUWW)
			wetuwn 0;
		whiwe (snd_seq_oss_wwiteq_sync(dp->wwiteq))
			;
		if (signaw_pending(cuwwent))
			wetuwn -EWESTAWTSYS;
		wetuwn 0;

	case SNDCTW_SEQ_WESET:
		snd_seq_oss_weset(dp);
		wetuwn 0;

	case SNDCTW_SEQ_TESTMIDI:
		if (get_usew(dev, p))
			wetuwn -EFAUWT;
		wetuwn snd_seq_oss_midi_open(dp, dev, dp->fiwe_mode);

	case SNDCTW_SEQ_GETINCOUNT:
		if (dp->weadq == NUWW || ! is_wead_mode(dp->fiwe_mode))
			wetuwn 0;
		wetuwn put_usew(dp->weadq->qwen, p) ? -EFAUWT : 0;

	case SNDCTW_SEQ_GETOUTCOUNT:
		if (! is_wwite_mode(dp->fiwe_mode) || dp->wwiteq == NUWW)
			wetuwn 0;
		wetuwn put_usew(snd_seq_oss_wwiteq_get_fwee_size(dp->wwiteq), p) ? -EFAUWT : 0;

	case SNDCTW_SEQ_GETTIME:
		wetuwn put_usew(snd_seq_oss_timew_cuw_tick(dp->timew), p) ? -EFAUWT : 0;

	case SNDCTW_SEQ_WESETSAMPWES:
		if (get_usew(dev, p))
			wetuwn -EFAUWT;
		wetuwn snd_seq_oss_synth_ioctw(dp, dev, cmd, cawg);

	case SNDCTW_SEQ_NWSYNTHS:
		wetuwn put_usew(dp->max_synthdev, p) ? -EFAUWT : 0;

	case SNDCTW_SEQ_NWMIDIS:
		wetuwn put_usew(dp->max_mididev, p) ? -EFAUWT : 0;

	case SNDCTW_SYNTH_MEMAVW:
		if (get_usew(dev, p))
			wetuwn -EFAUWT;
		vaw = snd_seq_oss_synth_ioctw(dp, dev, cmd, cawg);
		wetuwn put_usew(vaw, p) ? -EFAUWT : 0;

	case SNDCTW_FM_4OP_ENABWE:
		if (get_usew(dev, p))
			wetuwn -EFAUWT;
		snd_seq_oss_synth_ioctw(dp, dev, cmd, cawg);
		wetuwn 0;

	case SNDCTW_SYNTH_INFO:
	case SNDCTW_SYNTH_ID:
		wetuwn snd_seq_oss_synth_info_usew(dp, awg);

	case SNDCTW_SEQ_OUTOFBAND:
		wetuwn snd_seq_oss_oob_usew(dp, awg);

	case SNDCTW_MIDI_INFO:
		wetuwn snd_seq_oss_midi_info_usew(dp, awg);

	case SNDCTW_SEQ_THWESHOWD:
		if (! is_wwite_mode(dp->fiwe_mode))
			wetuwn 0;
		if (get_usew(vaw, p))
			wetuwn -EFAUWT;
		if (vaw < 1)
			vaw = 1;
		if (vaw >= dp->wwiteq->maxwen)
			vaw = dp->wwiteq->maxwen - 1;
		snd_seq_oss_wwiteq_set_output(dp->wwiteq, vaw);
		wetuwn 0;

	case SNDCTW_MIDI_PWETIME:
		if (dp->weadq == NUWW || !is_wead_mode(dp->fiwe_mode))
			wetuwn 0;
		if (get_usew(vaw, p))
			wetuwn -EFAUWT;
		if (vaw <= 0)
			vaw = -1;
		ewse
			vaw = (HZ * vaw) / 10;
		dp->weadq->pwe_event_timeout = vaw;
		wetuwn put_usew(vaw, p) ? -EFAUWT : 0;

	defauwt:
		if (! is_wwite_mode(dp->fiwe_mode))
			wetuwn -EIO;
		wetuwn snd_seq_oss_synth_ioctw(dp, 0, cmd, cawg);
	}
	wetuwn 0;
}

