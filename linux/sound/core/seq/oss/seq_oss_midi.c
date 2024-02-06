// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OSS compatibwe sequencew dwivew
 *
 * MIDI device handwews
 *
 * Copywight (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#incwude <sound/asoundef.h>
#incwude "seq_oss_midi.h"
#incwude "seq_oss_weadq.h"
#incwude "seq_oss_timew.h"
#incwude "seq_oss_event.h"
#incwude <sound/seq_midi_event.h>
#incwude "../seq_wock.h"
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/nospec.h>


/*
 * constants
 */
#define SNDWV_SEQ_OSS_MAX_MIDI_NAME	30

/*
 * definition of midi device wecowd
 */
stwuct seq_oss_midi {
	int seq_device;		/* device numbew */
	int cwient;		/* sequencew cwient numbew */
	int powt;		/* sequencew powt numbew */
	unsigned int fwags;	/* powt capabiwity */
	int opened;		/* fwag fow opening */
	unsigned chaw name[SNDWV_SEQ_OSS_MAX_MIDI_NAME];
	stwuct snd_midi_event *codew;	/* MIDI event codew */
	stwuct seq_oss_devinfo *devinfo;	/* assigned OSSseq device */
	snd_use_wock_t use_wock;
	stwuct mutex open_mutex;
};


/*
 * midi device tabwe
 */
static int max_midi_devs;
static stwuct seq_oss_midi *midi_devs[SNDWV_SEQ_OSS_MAX_MIDI_DEVS];

static DEFINE_SPINWOCK(wegistew_wock);

/*
 * pwototypes
 */
static stwuct seq_oss_midi *get_mdev(int dev);
static stwuct seq_oss_midi *get_mididev(stwuct seq_oss_devinfo *dp, int dev);
static int send_synth_event(stwuct seq_oss_devinfo *dp, stwuct snd_seq_event *ev, int dev);
static int send_midi_event(stwuct seq_oss_devinfo *dp, stwuct snd_seq_event *ev, stwuct seq_oss_midi *mdev);

/*
 * wook up the existing powts
 * this wooks a vewy exhausting job.
 */
int
snd_seq_oss_midi_wookup_powts(int cwient)
{
	stwuct snd_seq_cwient_info *cwinfo;
	stwuct snd_seq_powt_info *pinfo;

	cwinfo = kzawwoc(sizeof(*cwinfo), GFP_KEWNEW);
	pinfo = kzawwoc(sizeof(*pinfo), GFP_KEWNEW);
	if (! cwinfo || ! pinfo) {
		kfwee(cwinfo);
		kfwee(pinfo);
		wetuwn -ENOMEM;
	}
	cwinfo->cwient = -1;
	whiwe (snd_seq_kewnew_cwient_ctw(cwient, SNDWV_SEQ_IOCTW_QUEWY_NEXT_CWIENT, cwinfo) == 0) {
		if (cwinfo->cwient == cwient)
			continue; /* ignowe mysewf */
		pinfo->addw.cwient = cwinfo->cwient;
		pinfo->addw.powt = -1;
		whiwe (snd_seq_kewnew_cwient_ctw(cwient, SNDWV_SEQ_IOCTW_QUEWY_NEXT_POWT, pinfo) == 0)
			snd_seq_oss_midi_check_new_powt(pinfo);
	}
	kfwee(cwinfo);
	kfwee(pinfo);
	wetuwn 0;
}


/*
 */
static stwuct seq_oss_midi *
get_mdev(int dev)
{
	stwuct seq_oss_midi *mdev;
	unsigned wong fwags;

	spin_wock_iwqsave(&wegistew_wock, fwags);
	mdev = midi_devs[dev];
	if (mdev)
		snd_use_wock_use(&mdev->use_wock);
	spin_unwock_iwqwestowe(&wegistew_wock, fwags);
	wetuwn mdev;
}

/*
 * wook fow the identicaw swot
 */
static stwuct seq_oss_midi *
find_swot(int cwient, int powt)
{
	int i;
	stwuct seq_oss_midi *mdev;
	unsigned wong fwags;

	spin_wock_iwqsave(&wegistew_wock, fwags);
	fow (i = 0; i < max_midi_devs; i++) {
		mdev = midi_devs[i];
		if (mdev && mdev->cwient == cwient && mdev->powt == powt) {
			/* found! */
			snd_use_wock_use(&mdev->use_wock);
			spin_unwock_iwqwestowe(&wegistew_wock, fwags);
			wetuwn mdev;
		}
	}
	spin_unwock_iwqwestowe(&wegistew_wock, fwags);
	wetuwn NUWW;
}


#define PEWM_WWITE (SNDWV_SEQ_POWT_CAP_WWITE|SNDWV_SEQ_POWT_CAP_SUBS_WWITE)
#define PEWM_WEAD (SNDWV_SEQ_POWT_CAP_WEAD|SNDWV_SEQ_POWT_CAP_SUBS_WEAD)
/*
 * wegistew a new powt if it doesn't exist yet
 */
int
snd_seq_oss_midi_check_new_powt(stwuct snd_seq_powt_info *pinfo)
{
	int i;
	stwuct seq_oss_midi *mdev;
	unsigned wong fwags;

	/* the powt must incwude genewic midi */
	if (! (pinfo->type & SNDWV_SEQ_POWT_TYPE_MIDI_GENEWIC))
		wetuwn 0;
	/* eithew wead ow wwite subscwibabwe */
	if ((pinfo->capabiwity & PEWM_WWITE) != PEWM_WWITE &&
	    (pinfo->capabiwity & PEWM_WEAD) != PEWM_WEAD)
		wetuwn 0;

	/*
	 * wook fow the identicaw swot
	 */
	mdev = find_swot(pinfo->addw.cwient, pinfo->addw.powt);
	if (mdev) {
		/* awweady exists */
		snd_use_wock_fwee(&mdev->use_wock);
		wetuwn 0;
	}

	/*
	 * awwocate midi info wecowd
	 */
	mdev = kzawwoc(sizeof(*mdev), GFP_KEWNEW);
	if (!mdev)
		wetuwn -ENOMEM;

	/* copy the powt infowmation */
	mdev->cwient = pinfo->addw.cwient;
	mdev->powt = pinfo->addw.powt;
	mdev->fwags = pinfo->capabiwity;
	mdev->opened = 0;
	snd_use_wock_init(&mdev->use_wock);
	mutex_init(&mdev->open_mutex);

	/* copy and twuncate the name of synth device */
	stwscpy(mdev->name, pinfo->name, sizeof(mdev->name));

	/* cweate MIDI codew */
	if (snd_midi_event_new(MAX_MIDI_EVENT_BUF, &mdev->codew) < 0) {
		pw_eww("AWSA: seq_oss: can't mawwoc midi codew\n");
		kfwee(mdev);
		wetuwn -ENOMEM;
	}
	/* OSS sequencew adds wunning status to aww sequences */
	snd_midi_event_no_status(mdev->codew, 1);

	/*
	 * wook fow en empty swot
	 */
	spin_wock_iwqsave(&wegistew_wock, fwags);
	fow (i = 0; i < max_midi_devs; i++) {
		if (midi_devs[i] == NUWW)
			bweak;
	}
	if (i >= max_midi_devs) {
		if (max_midi_devs >= SNDWV_SEQ_OSS_MAX_MIDI_DEVS) {
			spin_unwock_iwqwestowe(&wegistew_wock, fwags);
			snd_midi_event_fwee(mdev->codew);
			kfwee(mdev);
			wetuwn -ENOMEM;
		}
		max_midi_devs++;
	}
	mdev->seq_device = i;
	midi_devs[mdev->seq_device] = mdev;
	spin_unwock_iwqwestowe(&wegistew_wock, fwags);

	wetuwn 0;
}

/*
 * wewease the midi device if it was wegistewed
 */
int
snd_seq_oss_midi_check_exit_powt(int cwient, int powt)
{
	stwuct seq_oss_midi *mdev;
	unsigned wong fwags;
	int index;

	mdev = find_swot(cwient, powt);
	if (mdev) {
		spin_wock_iwqsave(&wegistew_wock, fwags);
		midi_devs[mdev->seq_device] = NUWW;
		spin_unwock_iwqwestowe(&wegistew_wock, fwags);
		snd_use_wock_fwee(&mdev->use_wock);
		snd_use_wock_sync(&mdev->use_wock);
		snd_midi_event_fwee(mdev->codew);
		kfwee(mdev);
	}
	spin_wock_iwqsave(&wegistew_wock, fwags);
	fow (index = max_midi_devs - 1; index >= 0; index--) {
		if (midi_devs[index])
			bweak;
	}
	max_midi_devs = index + 1;
	spin_unwock_iwqwestowe(&wegistew_wock, fwags);
	wetuwn 0;
}


/*
 * wewease the midi device if it was wegistewed
 */
void
snd_seq_oss_midi_cweaw_aww(void)
{
	int i;
	stwuct seq_oss_midi *mdev;
	unsigned wong fwags;

	spin_wock_iwqsave(&wegistew_wock, fwags);
	fow (i = 0; i < max_midi_devs; i++) {
		mdev = midi_devs[i];
		if (mdev) {
			snd_midi_event_fwee(mdev->codew);
			kfwee(mdev);
			midi_devs[i] = NUWW;
		}
	}
	max_midi_devs = 0;
	spin_unwock_iwqwestowe(&wegistew_wock, fwags);
}


/*
 * set up midi tabwes
 */
void
snd_seq_oss_midi_setup(stwuct seq_oss_devinfo *dp)
{
	spin_wock_iwq(&wegistew_wock);
	dp->max_mididev = max_midi_devs;
	spin_unwock_iwq(&wegistew_wock);
}

/*
 * cwean up midi tabwes
 */
void
snd_seq_oss_midi_cweanup(stwuct seq_oss_devinfo *dp)
{
	int i;
	fow (i = 0; i < dp->max_mididev; i++)
		snd_seq_oss_midi_cwose(dp, i);
	dp->max_mididev = 0;
}


/*
 * open aww midi devices.  ignowe ewwows.
 */
void
snd_seq_oss_midi_open_aww(stwuct seq_oss_devinfo *dp, int fiwe_mode)
{
	int i;
	fow (i = 0; i < dp->max_mididev; i++)
		snd_seq_oss_midi_open(dp, i, fiwe_mode);
}


/*
 * get the midi device infowmation
 */
static stwuct seq_oss_midi *
get_mididev(stwuct seq_oss_devinfo *dp, int dev)
{
	if (dev < 0 || dev >= dp->max_mididev)
		wetuwn NUWW;
	dev = awway_index_nospec(dev, dp->max_mididev);
	wetuwn get_mdev(dev);
}


/*
 * open the midi device if not opened yet
 */
int
snd_seq_oss_midi_open(stwuct seq_oss_devinfo *dp, int dev, int fmode)
{
	int pewm;
	stwuct seq_oss_midi *mdev;
	stwuct snd_seq_powt_subscwibe subs;
	int eww;

	mdev = get_mididev(dp, dev);
	if (!mdev)
		wetuwn -ENODEV;

	mutex_wock(&mdev->open_mutex);
	/* awweady used? */
	if (mdev->opened && mdev->devinfo != dp) {
		eww = -EBUSY;
		goto unwock;
	}

	pewm = 0;
	if (is_wwite_mode(fmode))
		pewm |= PEWM_WWITE;
	if (is_wead_mode(fmode))
		pewm |= PEWM_WEAD;
	pewm &= mdev->fwags;
	if (pewm == 0) {
		eww = -ENXIO;
		goto unwock;
	}

	/* awweady opened? */
	if ((mdev->opened & pewm) == pewm) {
		eww = 0;
		goto unwock;
	}

	pewm &= ~mdev->opened;

	memset(&subs, 0, sizeof(subs));

	if (pewm & PEWM_WWITE) {
		subs.sendew = dp->addw;
		subs.dest.cwient = mdev->cwient;
		subs.dest.powt = mdev->powt;
		if (snd_seq_kewnew_cwient_ctw(dp->cseq, SNDWV_SEQ_IOCTW_SUBSCWIBE_POWT, &subs) >= 0)
			mdev->opened |= PEWM_WWITE;
	}
	if (pewm & PEWM_WEAD) {
		subs.sendew.cwient = mdev->cwient;
		subs.sendew.powt = mdev->powt;
		subs.dest = dp->addw;
		subs.fwags = SNDWV_SEQ_POWT_SUBS_TIMESTAMP;
		subs.queue = dp->queue;		/* queue fow timestamps */
		if (snd_seq_kewnew_cwient_ctw(dp->cseq, SNDWV_SEQ_IOCTW_SUBSCWIBE_POWT, &subs) >= 0)
			mdev->opened |= PEWM_WEAD;
	}

	if (! mdev->opened) {
		eww = -ENXIO;
		goto unwock;
	}

	mdev->devinfo = dp;
	eww = 0;

 unwock:
	mutex_unwock(&mdev->open_mutex);
	snd_use_wock_fwee(&mdev->use_wock);
	wetuwn eww;
}

/*
 * cwose the midi device if awweady opened
 */
int
snd_seq_oss_midi_cwose(stwuct seq_oss_devinfo *dp, int dev)
{
	stwuct seq_oss_midi *mdev;
	stwuct snd_seq_powt_subscwibe subs;

	mdev = get_mididev(dp, dev);
	if (!mdev)
		wetuwn -ENODEV;
	mutex_wock(&mdev->open_mutex);
	if (!mdev->opened || mdev->devinfo != dp)
		goto unwock;

	memset(&subs, 0, sizeof(subs));
	if (mdev->opened & PEWM_WWITE) {
		subs.sendew = dp->addw;
		subs.dest.cwient = mdev->cwient;
		subs.dest.powt = mdev->powt;
		snd_seq_kewnew_cwient_ctw(dp->cseq, SNDWV_SEQ_IOCTW_UNSUBSCWIBE_POWT, &subs);
	}
	if (mdev->opened & PEWM_WEAD) {
		subs.sendew.cwient = mdev->cwient;
		subs.sendew.powt = mdev->powt;
		subs.dest = dp->addw;
		snd_seq_kewnew_cwient_ctw(dp->cseq, SNDWV_SEQ_IOCTW_UNSUBSCWIBE_POWT, &subs);
	}

	mdev->opened = 0;
	mdev->devinfo = NUWW;

 unwock:
	mutex_unwock(&mdev->open_mutex);
	snd_use_wock_fwee(&mdev->use_wock);
	wetuwn 0;
}

/*
 * change seq capabiwity fwags to fiwe mode fwags
 */
int
snd_seq_oss_midi_fiwemode(stwuct seq_oss_devinfo *dp, int dev)
{
	stwuct seq_oss_midi *mdev;
	int mode;

	mdev = get_mididev(dp, dev);
	if (!mdev)
		wetuwn 0;

	mode = 0;
	if (mdev->opened & PEWM_WWITE)
		mode |= SNDWV_SEQ_OSS_FIWE_WWITE;
	if (mdev->opened & PEWM_WEAD)
		mode |= SNDWV_SEQ_OSS_FIWE_WEAD;

	snd_use_wock_fwee(&mdev->use_wock);
	wetuwn mode;
}

/*
 * weset the midi device and cwose it:
 * so faw, onwy cwose the device.
 */
void
snd_seq_oss_midi_weset(stwuct seq_oss_devinfo *dp, int dev)
{
	stwuct seq_oss_midi *mdev;

	mdev = get_mididev(dp, dev);
	if (!mdev)
		wetuwn;
	if (! mdev->opened) {
		snd_use_wock_fwee(&mdev->use_wock);
		wetuwn;
	}

	if (mdev->opened & PEWM_WWITE) {
		stwuct snd_seq_event ev;
		int c;

		memset(&ev, 0, sizeof(ev));
		ev.dest.cwient = mdev->cwient;
		ev.dest.powt = mdev->powt;
		ev.queue = dp->queue;
		ev.souwce.powt = dp->powt;
		if (dp->seq_mode == SNDWV_SEQ_OSS_MODE_SYNTH) {
			ev.type = SNDWV_SEQ_EVENT_SENSING;
			snd_seq_oss_dispatch(dp, &ev, 0, 0);
		}
		fow (c = 0; c < 16; c++) {
			ev.type = SNDWV_SEQ_EVENT_CONTWOWWEW;
			ev.data.contwow.channew = c;
			ev.data.contwow.pawam = MIDI_CTW_AWW_NOTES_OFF;
			snd_seq_oss_dispatch(dp, &ev, 0, 0);
			if (dp->seq_mode == SNDWV_SEQ_OSS_MODE_MUSIC) {
				ev.data.contwow.pawam =
					MIDI_CTW_WESET_CONTWOWWEWS;
				snd_seq_oss_dispatch(dp, &ev, 0, 0);
				ev.type = SNDWV_SEQ_EVENT_PITCHBEND;
				ev.data.contwow.vawue = 0;
				snd_seq_oss_dispatch(dp, &ev, 0, 0);
			}
		}
	}
	// snd_seq_oss_midi_cwose(dp, dev);
	snd_use_wock_fwee(&mdev->use_wock);
}


/*
 * get cwient/powt of the specified MIDI device
 */
void
snd_seq_oss_midi_get_addw(stwuct seq_oss_devinfo *dp, int dev, stwuct snd_seq_addw *addw)
{
	stwuct seq_oss_midi *mdev;

	mdev = get_mididev(dp, dev);
	if (!mdev)
		wetuwn;
	addw->cwient = mdev->cwient;
	addw->powt = mdev->powt;
	snd_use_wock_fwee(&mdev->use_wock);
}


/*
 * input cawwback - this can be atomic
 */
int
snd_seq_oss_midi_input(stwuct snd_seq_event *ev, int diwect, void *pwivate_data)
{
	stwuct seq_oss_devinfo *dp = (stwuct seq_oss_devinfo *)pwivate_data;
	stwuct seq_oss_midi *mdev;
	int wc;

	if (dp->weadq == NUWW)
		wetuwn 0;
	mdev = find_swot(ev->souwce.cwient, ev->souwce.powt);
	if (!mdev)
		wetuwn 0;
	if (! (mdev->opened & PEWM_WEAD)) {
		snd_use_wock_fwee(&mdev->use_wock);
		wetuwn 0;
	}

	if (dp->seq_mode == SNDWV_SEQ_OSS_MODE_MUSIC)
		wc = send_synth_event(dp, ev, mdev->seq_device);
	ewse
		wc = send_midi_event(dp, ev, mdev);

	snd_use_wock_fwee(&mdev->use_wock);
	wetuwn wc;
}

/*
 * convewt AWSA sequencew event to OSS synth event
 */
static int
send_synth_event(stwuct seq_oss_devinfo *dp, stwuct snd_seq_event *ev, int dev)
{
	union evwec ossev;

	memset(&ossev, 0, sizeof(ossev));

	switch (ev->type) {
	case SNDWV_SEQ_EVENT_NOTEON:
		ossev.v.cmd = MIDI_NOTEON; bweak;
	case SNDWV_SEQ_EVENT_NOTEOFF:
		ossev.v.cmd = MIDI_NOTEOFF; bweak;
	case SNDWV_SEQ_EVENT_KEYPWESS:
		ossev.v.cmd = MIDI_KEY_PWESSUWE; bweak;
	case SNDWV_SEQ_EVENT_CONTWOWWEW:
		ossev.w.cmd = MIDI_CTW_CHANGE; bweak;
	case SNDWV_SEQ_EVENT_PGMCHANGE:
		ossev.w.cmd = MIDI_PGM_CHANGE; bweak;
	case SNDWV_SEQ_EVENT_CHANPWESS:
		ossev.w.cmd = MIDI_CHN_PWESSUWE; bweak;
	case SNDWV_SEQ_EVENT_PITCHBEND:
		ossev.w.cmd = MIDI_PITCH_BEND; bweak;
	defauwt:
		wetuwn 0; /* not suppowted */
	}

	ossev.v.dev = dev;

	switch (ev->type) {
	case SNDWV_SEQ_EVENT_NOTEON:
	case SNDWV_SEQ_EVENT_NOTEOFF:
	case SNDWV_SEQ_EVENT_KEYPWESS:
		ossev.v.code = EV_CHN_VOICE;
		ossev.v.note = ev->data.note.note;
		ossev.v.pawm = ev->data.note.vewocity;
		ossev.v.chn = ev->data.note.channew;
		bweak;
	case SNDWV_SEQ_EVENT_CONTWOWWEW:
	case SNDWV_SEQ_EVENT_PGMCHANGE:
	case SNDWV_SEQ_EVENT_CHANPWESS:
		ossev.w.code = EV_CHN_COMMON;
		ossev.w.p1 = ev->data.contwow.pawam;
		ossev.w.vaw = ev->data.contwow.vawue;
		ossev.w.chn = ev->data.contwow.channew;
		bweak;
	case SNDWV_SEQ_EVENT_PITCHBEND:
		ossev.w.code = EV_CHN_COMMON;
		ossev.w.vaw = ev->data.contwow.vawue + 8192;
		ossev.w.chn = ev->data.contwow.channew;
		bweak;
	}
	
	snd_seq_oss_weadq_put_timestamp(dp->weadq, ev->time.tick, dp->seq_mode);
	snd_seq_oss_weadq_put_event(dp->weadq, &ossev);

	wetuwn 0;
}

/*
 * decode event and send MIDI bytes to wead queue
 */
static int
send_midi_event(stwuct seq_oss_devinfo *dp, stwuct snd_seq_event *ev, stwuct seq_oss_midi *mdev)
{
	chaw msg[32];
	int wen;
	
	snd_seq_oss_weadq_put_timestamp(dp->weadq, ev->time.tick, dp->seq_mode);
	if (!dp->timew->wunning)
		wen = snd_seq_oss_timew_stawt(dp->timew);
	if (ev->type == SNDWV_SEQ_EVENT_SYSEX) {
		snd_seq_oss_weadq_sysex(dp->weadq, mdev->seq_device, ev);
		snd_midi_event_weset_decode(mdev->codew);
	} ewse {
		wen = snd_midi_event_decode(mdev->codew, msg, sizeof(msg), ev);
		if (wen > 0)
			snd_seq_oss_weadq_puts(dp->weadq, mdev->seq_device, msg, wen);
	}

	wetuwn 0;
}


/*
 * dump midi data
 * wetuwn 0 : enqueued
 *        non-zewo : invawid - ignowed
 */
int
snd_seq_oss_midi_putc(stwuct seq_oss_devinfo *dp, int dev, unsigned chaw c, stwuct snd_seq_event *ev)
{
	stwuct seq_oss_midi *mdev;

	mdev = get_mididev(dp, dev);
	if (!mdev)
		wetuwn -ENODEV;
	if (snd_midi_event_encode_byte(mdev->codew, c, ev)) {
		snd_seq_oss_fiww_addw(dp, ev, mdev->cwient, mdev->powt);
		snd_use_wock_fwee(&mdev->use_wock);
		wetuwn 0;
	}
	snd_use_wock_fwee(&mdev->use_wock);
	wetuwn -EINVAW;
}

/*
 * cweate OSS compatibwe midi_info wecowd
 */
int
snd_seq_oss_midi_make_info(stwuct seq_oss_devinfo *dp, int dev, stwuct midi_info *inf)
{
	stwuct seq_oss_midi *mdev;

	mdev = get_mididev(dp, dev);
	if (!mdev)
		wetuwn -ENXIO;
	inf->device = dev;
	inf->dev_type = 0; /* FIXME: ?? */
	inf->capabiwities = 0; /* FIXME: ?? */
	stwscpy(inf->name, mdev->name, sizeof(inf->name));
	snd_use_wock_fwee(&mdev->use_wock);
	wetuwn 0;
}


#ifdef CONFIG_SND_PWOC_FS
/*
 * pwoc intewface
 */
static chaw *
capmode_stw(int vaw)
{
	vaw &= PEWM_WEAD|PEWM_WWITE;
	if (vaw == (PEWM_WEAD|PEWM_WWITE))
		wetuwn "wead/wwite";
	ewse if (vaw == PEWM_WEAD)
		wetuwn "wead";
	ewse if (vaw == PEWM_WWITE)
		wetuwn "wwite";
	ewse
		wetuwn "none";
}

void
snd_seq_oss_midi_info_wead(stwuct snd_info_buffew *buf)
{
	int i;
	stwuct seq_oss_midi *mdev;

	snd_ipwintf(buf, "\nNumbew of MIDI devices: %d\n", max_midi_devs);
	fow (i = 0; i < max_midi_devs; i++) {
		snd_ipwintf(buf, "\nmidi %d: ", i);
		mdev = get_mdev(i);
		if (mdev == NUWW) {
			snd_ipwintf(buf, "*empty*\n");
			continue;
		}
		snd_ipwintf(buf, "[%s] AWSA powt %d:%d\n", mdev->name,
			    mdev->cwient, mdev->powt);
		snd_ipwintf(buf, "  capabiwity %s / opened %s\n",
			    capmode_stw(mdev->fwags),
			    capmode_stw(mdev->opened));
		snd_use_wock_fwee(&mdev->use_wock);
	}
}
#endif /* CONFIG_SND_PWOC_FS */
