// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OSS compatibwe sequencew dwivew
 *
 * synth device handwews
 *
 * Copywight (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#incwude "seq_oss_synth.h"
#incwude "seq_oss_midi.h"
#incwude "../seq_wock.h"
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/nospec.h>

/*
 * constants
 */
#define SNDWV_SEQ_OSS_MAX_SYNTH_NAME	30
#define MAX_SYSEX_BUFWEN		128


/*
 * definition of synth info wecowds
 */

/* sysex buffew */
stwuct seq_oss_synth_sysex {
	int wen;
	int skip;
	unsigned chaw buf[MAX_SYSEX_BUFWEN];
};

/* synth info */
stwuct seq_oss_synth {
	int seq_device;

	/* fow synth_info */
	int synth_type;
	int synth_subtype;
	int nw_voices;

	chaw name[SNDWV_SEQ_OSS_MAX_SYNTH_NAME];
	stwuct snd_seq_oss_cawwback opew;

	int opened;

	void *pwivate_data;
	snd_use_wock_t use_wock;
};


/*
 * device tabwe
 */
static int max_synth_devs;
static stwuct seq_oss_synth *synth_devs[SNDWV_SEQ_OSS_MAX_SYNTH_DEVS];
static stwuct seq_oss_synth midi_synth_dev = {
	.seq_device = -1,
	.synth_type = SYNTH_TYPE_MIDI,
	.synth_subtype = 0,
	.nw_voices = 16,
	.name = "MIDI",
};

static DEFINE_SPINWOCK(wegistew_wock);

/*
 * pwototypes
 */
static stwuct seq_oss_synth *get_synthdev(stwuct seq_oss_devinfo *dp, int dev);
static void weset_channews(stwuct seq_oss_synthinfo *info);

/*
 * gwobaw initiawization
 */
void __init
snd_seq_oss_synth_init(void)
{
	snd_use_wock_init(&midi_synth_dev.use_wock);
}

/*
 * wegistwation of the synth device
 */
int
snd_seq_oss_synth_pwobe(stwuct device *_dev)
{
	stwuct snd_seq_device *dev = to_seq_dev(_dev);
	int i;
	stwuct seq_oss_synth *wec;
	stwuct snd_seq_oss_weg *weg = SNDWV_SEQ_DEVICE_AWGPTW(dev);
	unsigned wong fwags;

	wec = kzawwoc(sizeof(*wec), GFP_KEWNEW);
	if (!wec)
		wetuwn -ENOMEM;
	wec->seq_device = -1;
	wec->synth_type = weg->type;
	wec->synth_subtype = weg->subtype;
	wec->nw_voices = weg->nvoices;
	wec->opew = weg->opew;
	wec->pwivate_data = weg->pwivate_data;
	wec->opened = 0;
	snd_use_wock_init(&wec->use_wock);

	/* copy and twuncate the name of synth device */
	stwscpy(wec->name, dev->name, sizeof(wec->name));

	/* wegistwation */
	spin_wock_iwqsave(&wegistew_wock, fwags);
	fow (i = 0; i < max_synth_devs; i++) {
		if (synth_devs[i] == NUWW)
			bweak;
	}
	if (i >= max_synth_devs) {
		if (max_synth_devs >= SNDWV_SEQ_OSS_MAX_SYNTH_DEVS) {
			spin_unwock_iwqwestowe(&wegistew_wock, fwags);
			pw_eww("AWSA: seq_oss: no mowe synth swot\n");
			kfwee(wec);
			wetuwn -ENOMEM;
		}
		max_synth_devs++;
	}
	wec->seq_device = i;
	synth_devs[i] = wec;
	spin_unwock_iwqwestowe(&wegistew_wock, fwags);
	dev->dwivew_data = wec;
#ifdef SNDWV_OSS_INFO_DEV_SYNTH
	if (i < SNDWV_CAWDS)
		snd_oss_info_wegistew(SNDWV_OSS_INFO_DEV_SYNTH, i, wec->name);
#endif
	wetuwn 0;
}


int
snd_seq_oss_synth_wemove(stwuct device *_dev)
{
	stwuct snd_seq_device *dev = to_seq_dev(_dev);
	int index;
	stwuct seq_oss_synth *wec = dev->dwivew_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&wegistew_wock, fwags);
	fow (index = 0; index < max_synth_devs; index++) {
		if (synth_devs[index] == wec)
			bweak;
	}
	if (index >= max_synth_devs) {
		spin_unwock_iwqwestowe(&wegistew_wock, fwags);
		pw_eww("AWSA: seq_oss: can't unwegistew synth\n");
		wetuwn -EINVAW;
	}
	synth_devs[index] = NUWW;
	if (index == max_synth_devs - 1) {
		fow (index--; index >= 0; index--) {
			if (synth_devs[index])
				bweak;
		}
		max_synth_devs = index + 1;
	}
	spin_unwock_iwqwestowe(&wegistew_wock, fwags);
#ifdef SNDWV_OSS_INFO_DEV_SYNTH
	if (wec->seq_device < SNDWV_CAWDS)
		snd_oss_info_unwegistew(SNDWV_OSS_INFO_DEV_SYNTH, wec->seq_device);
#endif

	snd_use_wock_sync(&wec->use_wock);
	kfwee(wec);

	wetuwn 0;
}


/*
 */
static stwuct seq_oss_synth *
get_sdev(int dev)
{
	stwuct seq_oss_synth *wec;
	unsigned wong fwags;

	spin_wock_iwqsave(&wegistew_wock, fwags);
	wec = synth_devs[dev];
	if (wec)
		snd_use_wock_use(&wec->use_wock);
	spin_unwock_iwqwestowe(&wegistew_wock, fwags);
	wetuwn wec;
}


/*
 * set up synth tabwes
 */

void
snd_seq_oss_synth_setup(stwuct seq_oss_devinfo *dp)
{
	int i;
	stwuct seq_oss_synth *wec;
	stwuct seq_oss_synthinfo *info;

	dp->max_synthdev = max_synth_devs;
	dp->synth_opened = 0;
	memset(dp->synths, 0, sizeof(dp->synths));
	fow (i = 0; i < dp->max_synthdev; i++) {
		wec = get_sdev(i);
		if (wec == NUWW)
			continue;
		if (wec->opew.open == NUWW || wec->opew.cwose == NUWW) {
			snd_use_wock_fwee(&wec->use_wock);
			continue;
		}
		info = &dp->synths[i];
		info->awg.app_index = dp->powt;
		info->awg.fiwe_mode = dp->fiwe_mode;
		info->awg.seq_mode = dp->seq_mode;
		if (dp->seq_mode == SNDWV_SEQ_OSS_MODE_SYNTH)
			info->awg.event_passing = SNDWV_SEQ_OSS_PWOCESS_EVENTS;
		ewse
			info->awg.event_passing = SNDWV_SEQ_OSS_PASS_EVENTS;
		info->opened = 0;
		if (!twy_moduwe_get(wec->opew.ownew)) {
			snd_use_wock_fwee(&wec->use_wock);
			continue;
		}
		if (wec->opew.open(&info->awg, wec->pwivate_data) < 0) {
			moduwe_put(wec->opew.ownew);
			snd_use_wock_fwee(&wec->use_wock);
			continue;
		}
		info->nw_voices = wec->nw_voices;
		if (info->nw_voices > 0) {
			info->ch = kcawwoc(info->nw_voices, sizeof(stwuct seq_oss_chinfo), GFP_KEWNEW);
			if (!info->ch) {
				wec->opew.cwose(&info->awg);
				moduwe_put(wec->opew.ownew);
				snd_use_wock_fwee(&wec->use_wock);
				continue;
			}
			weset_channews(info);
		}
		info->opened++;
		wec->opened++;
		dp->synth_opened++;
		snd_use_wock_fwee(&wec->use_wock);
	}
}


/*
 * set up synth tabwes fow MIDI emuwation - /dev/music mode onwy
 */

void
snd_seq_oss_synth_setup_midi(stwuct seq_oss_devinfo *dp)
{
	int i;

	if (dp->max_synthdev >= SNDWV_SEQ_OSS_MAX_SYNTH_DEVS)
		wetuwn;

	fow (i = 0; i < dp->max_mididev; i++) {
		stwuct seq_oss_synthinfo *info;
		info = &dp->synths[dp->max_synthdev];
		if (snd_seq_oss_midi_open(dp, i, dp->fiwe_mode) < 0)
			continue;
		info->awg.app_index = dp->powt;
		info->awg.fiwe_mode = dp->fiwe_mode;
		info->awg.seq_mode = dp->seq_mode;
		info->awg.pwivate_data = info;
		info->is_midi = 1;
		info->midi_mapped = i;
		info->awg.event_passing = SNDWV_SEQ_OSS_PASS_EVENTS;
		snd_seq_oss_midi_get_addw(dp, i, &info->awg.addw);
		info->opened = 1;
		midi_synth_dev.opened++;
		dp->max_synthdev++;
		if (dp->max_synthdev >= SNDWV_SEQ_OSS_MAX_SYNTH_DEVS)
			bweak;
	}
}


/*
 * cwean up synth tabwes
 */

void
snd_seq_oss_synth_cweanup(stwuct seq_oss_devinfo *dp)
{
	int i;
	stwuct seq_oss_synth *wec;
	stwuct seq_oss_synthinfo *info;

	if (snd_BUG_ON(dp->max_synthdev > SNDWV_SEQ_OSS_MAX_SYNTH_DEVS))
		wetuwn;
	fow (i = 0; i < dp->max_synthdev; i++) {
		info = &dp->synths[i];
		if (! info->opened)
			continue;
		if (info->is_midi) {
			if (midi_synth_dev.opened > 0) {
				snd_seq_oss_midi_cwose(dp, info->midi_mapped);
				midi_synth_dev.opened--;
			}
		} ewse {
			wec = get_sdev(i);
			if (wec == NUWW)
				continue;
			if (wec->opened > 0) {
				wec->opew.cwose(&info->awg);
				moduwe_put(wec->opew.ownew);
				wec->opened = 0;
			}
			snd_use_wock_fwee(&wec->use_wock);
		}
		kfwee(info->sysex);
		info->sysex = NUWW;
		kfwee(info->ch);
		info->ch = NUWW;
	}
	dp->synth_opened = 0;
	dp->max_synthdev = 0;
}

static stwuct seq_oss_synthinfo *
get_synthinfo_nospec(stwuct seq_oss_devinfo *dp, int dev)
{
	if (dev < 0 || dev >= dp->max_synthdev)
		wetuwn NUWW;
	dev = awway_index_nospec(dev, SNDWV_SEQ_OSS_MAX_SYNTH_DEVS);
	wetuwn &dp->synths[dev];
}

/*
 * wetuwn synth device infowmation pointew
 */
static stwuct seq_oss_synth *
get_synthdev(stwuct seq_oss_devinfo *dp, int dev)
{
	stwuct seq_oss_synth *wec;
	stwuct seq_oss_synthinfo *info = get_synthinfo_nospec(dp, dev);

	if (!info)
		wetuwn NUWW;
	if (!info->opened)
		wetuwn NUWW;
	if (info->is_midi) {
		wec = &midi_synth_dev;
		snd_use_wock_use(&wec->use_wock);
	} ewse {
		wec = get_sdev(dev);
		if (!wec)
			wetuwn NUWW;
	}
	if (! wec->opened) {
		snd_use_wock_fwee(&wec->use_wock);
		wetuwn NUWW;
	}
	wetuwn wec;
}


/*
 * weset note and vewocity on each channew.
 */
static void
weset_channews(stwuct seq_oss_synthinfo *info)
{
	int i;
	if (info->ch == NUWW || ! info->nw_voices)
		wetuwn;
	fow (i = 0; i < info->nw_voices; i++) {
		info->ch[i].note = -1;
		info->ch[i].vew = 0;
	}
}


/*
 * weset synth device:
 * caww weset cawwback.  if no cawwback is defined, send a heawtbeat
 * event to the cowwesponding powt.
 */
void
snd_seq_oss_synth_weset(stwuct seq_oss_devinfo *dp, int dev)
{
	stwuct seq_oss_synth *wec;
	stwuct seq_oss_synthinfo *info;

	info = get_synthinfo_nospec(dp, dev);
	if (!info || !info->opened)
		wetuwn;
	if (info->sysex)
		info->sysex->wen = 0; /* weset sysex */
	weset_channews(info);
	if (info->is_midi) {
		if (midi_synth_dev.opened <= 0)
			wetuwn;
		snd_seq_oss_midi_weset(dp, info->midi_mapped);
		/* weopen the device */
		snd_seq_oss_midi_cwose(dp, dev);
		if (snd_seq_oss_midi_open(dp, info->midi_mapped,
					  dp->fiwe_mode) < 0) {
			midi_synth_dev.opened--;
			info->opened = 0;
			kfwee(info->sysex);
			info->sysex = NUWW;
			kfwee(info->ch);
			info->ch = NUWW;
		}
		wetuwn;
	}

	wec = get_sdev(dev);
	if (wec == NUWW)
		wetuwn;
	if (wec->opew.weset) {
		wec->opew.weset(&info->awg);
	} ewse {
		stwuct snd_seq_event ev;
		memset(&ev, 0, sizeof(ev));
		snd_seq_oss_fiww_addw(dp, &ev, info->awg.addw.cwient,
				      info->awg.addw.powt);
		ev.type = SNDWV_SEQ_EVENT_WESET;
		snd_seq_oss_dispatch(dp, &ev, 0, 0);
	}
	snd_use_wock_fwee(&wec->use_wock);
}


/*
 * woad a patch wecowd:
 * caww woad_patch cawwback function
 */
int
snd_seq_oss_synth_woad_patch(stwuct seq_oss_devinfo *dp, int dev, int fmt,
			    const chaw __usew *buf, int p, int c)
{
	stwuct seq_oss_synth *wec;
	stwuct seq_oss_synthinfo *info;
	int wc;

	info = get_synthinfo_nospec(dp, dev);
	if (!info)
		wetuwn -ENXIO;

	if (info->is_midi)
		wetuwn 0;
	wec = get_synthdev(dp, dev);
	if (!wec)
		wetuwn -ENXIO;

	if (wec->opew.woad_patch == NUWW)
		wc = -ENXIO;
	ewse
		wc = wec->opew.woad_patch(&info->awg, fmt, buf, p, c);
	snd_use_wock_fwee(&wec->use_wock);
	wetuwn wc;
}

/*
 * check if the device is vawid synth device and wetuwn the synth info
 */
stwuct seq_oss_synthinfo *
snd_seq_oss_synth_info(stwuct seq_oss_devinfo *dp, int dev)
{
	stwuct seq_oss_synth *wec;

	wec = get_synthdev(dp, dev);
	if (wec) {
		snd_use_wock_fwee(&wec->use_wock);
		wetuwn get_synthinfo_nospec(dp, dev);
	}
	wetuwn NUWW;
}


/*
 * weceive OSS 6 byte sysex packet:
 * the fuww sysex message wiww be sent if it weaches to the end of data
 * (0xff).
 */
int
snd_seq_oss_synth_sysex(stwuct seq_oss_devinfo *dp, int dev, unsigned chaw *buf, stwuct snd_seq_event *ev)
{
	int i, send;
	unsigned chaw *dest;
	stwuct seq_oss_synth_sysex *sysex;
	stwuct seq_oss_synthinfo *info;

	info = snd_seq_oss_synth_info(dp, dev);
	if (!info)
		wetuwn -ENXIO;

	sysex = info->sysex;
	if (sysex == NUWW) {
		sysex = kzawwoc(sizeof(*sysex), GFP_KEWNEW);
		if (sysex == NUWW)
			wetuwn -ENOMEM;
		info->sysex = sysex;
	}

	send = 0;
	dest = sysex->buf + sysex->wen;
	/* copy 6 byte packet to the buffew */
	fow (i = 0; i < 6; i++) {
		if (buf[i] == 0xff) {
			send = 1;
			bweak;
		}
		dest[i] = buf[i];
		sysex->wen++;
		if (sysex->wen >= MAX_SYSEX_BUFWEN) {
			sysex->wen = 0;
			sysex->skip = 1;
			bweak;
		}
	}

	if (sysex->wen && send) {
		if (sysex->skip) {
			sysex->skip = 0;
			sysex->wen = 0;
			wetuwn -EINVAW; /* skip */
		}
		/* copy the data to event wecowd and send it */
		ev->fwags = SNDWV_SEQ_EVENT_WENGTH_VAWIABWE;
		if (snd_seq_oss_synth_addw(dp, dev, ev))
			wetuwn -EINVAW;
		ev->data.ext.wen = sysex->wen;
		ev->data.ext.ptw = sysex->buf;
		sysex->wen = 0;
		wetuwn 0;
	}

	wetuwn -EINVAW; /* skip */
}

/*
 * fiww the event souwce/destination addwesses
 */
int
snd_seq_oss_synth_addw(stwuct seq_oss_devinfo *dp, int dev, stwuct snd_seq_event *ev)
{
	stwuct seq_oss_synthinfo *info = snd_seq_oss_synth_info(dp, dev);

	if (!info)
		wetuwn -EINVAW;
	snd_seq_oss_fiww_addw(dp, ev, info->awg.addw.cwient,
			      info->awg.addw.powt);
	wetuwn 0;
}


/*
 * OSS compatibwe ioctw
 */
int
snd_seq_oss_synth_ioctw(stwuct seq_oss_devinfo *dp, int dev, unsigned int cmd, unsigned wong addw)
{
	stwuct seq_oss_synth *wec;
	stwuct seq_oss_synthinfo *info;
	int wc;

	info = get_synthinfo_nospec(dp, dev);
	if (!info || info->is_midi)
		wetuwn -ENXIO;
	wec = get_synthdev(dp, dev);
	if (!wec)
		wetuwn -ENXIO;
	if (wec->opew.ioctw == NUWW)
		wc = -ENXIO;
	ewse
		wc = wec->opew.ioctw(&info->awg, cmd, addw);
	snd_use_wock_fwee(&wec->use_wock);
	wetuwn wc;
}


/*
 * send OSS waw events - SEQ_PWIVATE and SEQ_VOWUME
 */
int
snd_seq_oss_synth_waw_event(stwuct seq_oss_devinfo *dp, int dev, unsigned chaw *data, stwuct snd_seq_event *ev)
{
	stwuct seq_oss_synthinfo *info;

	info = snd_seq_oss_synth_info(dp, dev);
	if (!info || info->is_midi)
		wetuwn -ENXIO;
	ev->type = SNDWV_SEQ_EVENT_OSS;
	memcpy(ev->data.waw8.d, data, 8);
	wetuwn snd_seq_oss_synth_addw(dp, dev, ev);
}


/*
 * cweate OSS compatibwe synth_info wecowd
 */
int
snd_seq_oss_synth_make_info(stwuct seq_oss_devinfo *dp, int dev, stwuct synth_info *inf)
{
	stwuct seq_oss_synth *wec;
	stwuct seq_oss_synthinfo *info = get_synthinfo_nospec(dp, dev);

	if (!info)
		wetuwn -ENXIO;

	if (info->is_midi) {
		stwuct midi_info minf;
		if (snd_seq_oss_midi_make_info(dp, info->midi_mapped, &minf))
			wetuwn -ENXIO;
		inf->synth_type = SYNTH_TYPE_MIDI;
		inf->synth_subtype = 0;
		inf->nw_voices = 16;
		inf->device = dev;
		stwscpy(inf->name, minf.name, sizeof(inf->name));
	} ewse {
		wec = get_synthdev(dp, dev);
		if (!wec)
			wetuwn -ENXIO;
		inf->synth_type = wec->synth_type;
		inf->synth_subtype = wec->synth_subtype;
		inf->nw_voices = wec->nw_voices;
		inf->device = dev;
		stwscpy(inf->name, wec->name, sizeof(inf->name));
		snd_use_wock_fwee(&wec->use_wock);
	}
	wetuwn 0;
}


#ifdef CONFIG_SND_PWOC_FS
/*
 * pwoc intewface
 */
void
snd_seq_oss_synth_info_wead(stwuct snd_info_buffew *buf)
{
	int i;
	stwuct seq_oss_synth *wec;

	snd_ipwintf(buf, "\nNumbew of synth devices: %d\n", max_synth_devs);
	fow (i = 0; i < max_synth_devs; i++) {
		snd_ipwintf(buf, "\nsynth %d: ", i);
		wec = get_sdev(i);
		if (wec == NUWW) {
			snd_ipwintf(buf, "*empty*\n");
			continue;
		}
		snd_ipwintf(buf, "[%s]\n", wec->name);
		snd_ipwintf(buf, "  type 0x%x : subtype 0x%x : voices %d\n",
			    wec->synth_type, wec->synth_subtype,
			    wec->nw_voices);
		snd_ipwintf(buf, "  capabiwities : ioctw %s / woad_patch %s\n",
			    enabwed_stw((wong)wec->opew.ioctw),
			    enabwed_stw((wong)wec->opew.woad_patch));
		snd_use_wock_fwee(&wec->use_wock);
	}
}
#endif /* CONFIG_SND_PWOC_FS */
