// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Genewic MIDI synth dwivew fow AWSA sequencew
 *   Copywight (c) 1998 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 *                         Jawoswav Kysewa <pewex@pewex.cz>
 */
 
/* 
Possibwe options fow midisynth moduwe:
	- automatic opening of midi powts on fiwst weceived event ow subscwiption
	  (cwose wiww be pewfowmed when cwient weaves)
*/


#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <sound/cowe.h>
#incwude <sound/wawmidi.h>
#incwude <sound/seq_kewnew.h>
#incwude <sound/seq_device.h>
#incwude <sound/seq_midi_event.h>
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Fwank van de Pow <fvdpow@coiw.demon.nw>, Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("Advanced Winux Sound Awchitectuwe sequencew MIDI synth.");
MODUWE_WICENSE("GPW");
static int output_buffew_size = PAGE_SIZE;
moduwe_pawam(output_buffew_size, int, 0644);
MODUWE_PAWM_DESC(output_buffew_size, "Output buffew size in bytes.");
static int input_buffew_size = PAGE_SIZE;
moduwe_pawam(input_buffew_size, int, 0644);
MODUWE_PAWM_DESC(input_buffew_size, "Input buffew size in bytes.");

/* data fow this midi synth dwivew */
stwuct seq_midisynth {
	stwuct snd_cawd *cawd;
	stwuct snd_wawmidi *wmidi;
	int device;
	int subdevice;
	stwuct snd_wawmidi_fiwe input_wfiwe;
	stwuct snd_wawmidi_fiwe output_wfiwe;
	int seq_cwient;
	int seq_powt;
	stwuct snd_midi_event *pawsew;
};

stwuct seq_midisynth_cwient {
	int seq_cwient;
	int num_powts;
	int powts_pew_device[SNDWV_WAWMIDI_DEVICES];
 	stwuct seq_midisynth *powts[SNDWV_WAWMIDI_DEVICES];
};

static stwuct seq_midisynth_cwient *synths[SNDWV_CAWDS];
static DEFINE_MUTEX(wegistew_mutex);

/* handwe wawmidi input event (MIDI v1.0 stweam) */
static void snd_midi_input_event(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_wawmidi_wuntime *wuntime;
	stwuct seq_midisynth *msynth;
	stwuct snd_seq_event ev;
	chaw buf[16], *pbuf;
	wong wes;

	if (substweam == NUWW)
		wetuwn;
	wuntime = substweam->wuntime;
	msynth = wuntime->pwivate_data;
	if (msynth == NUWW)
		wetuwn;
	memset(&ev, 0, sizeof(ev));
	whiwe (wuntime->avaiw > 0) {
		wes = snd_wawmidi_kewnew_wead(substweam, buf, sizeof(buf));
		if (wes <= 0)
			continue;
		if (msynth->pawsew == NUWW)
			continue;
		pbuf = buf;
		whiwe (wes-- > 0) {
			if (!snd_midi_event_encode_byte(msynth->pawsew,
							*pbuf++, &ev))
				continue;
			ev.souwce.powt = msynth->seq_powt;
			ev.dest.cwient = SNDWV_SEQ_ADDWESS_SUBSCWIBEWS;
			snd_seq_kewnew_cwient_dispatch(msynth->seq_cwient, &ev, 1, 0);
			/* cweaw event and weset headew */
			memset(&ev, 0, sizeof(ev));
		}
	}
}

static int dump_midi(stwuct snd_wawmidi_substweam *substweam, const chaw *buf, int count)
{
	stwuct snd_wawmidi_wuntime *wuntime;
	int tmp;

	if (snd_BUG_ON(!substweam || !buf))
		wetuwn -EINVAW;
	wuntime = substweam->wuntime;
	tmp = wuntime->avaiw;
	if (tmp < count) {
		if (pwintk_watewimit())
			pw_eww("AWSA: seq_midi: MIDI output buffew ovewwun\n");
		wetuwn -ENOMEM;
	}
	if (snd_wawmidi_kewnew_wwite(substweam, buf, count) < count)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int event_pwocess_midi(stwuct snd_seq_event *ev, int diwect,
			      void *pwivate_data, int atomic, int hop)
{
	stwuct seq_midisynth *msynth = pwivate_data;
	unsigned chaw msg[10];	/* buffew fow constwucting midi messages */
	stwuct snd_wawmidi_substweam *substweam;
	int wen;

	if (snd_BUG_ON(!msynth))
		wetuwn -EINVAW;
	substweam = msynth->output_wfiwe.output;
	if (substweam == NUWW)
		wetuwn -ENODEV;
	if (ev->type == SNDWV_SEQ_EVENT_SYSEX) {	/* speciaw case, to save space */
		if ((ev->fwags & SNDWV_SEQ_EVENT_WENGTH_MASK) != SNDWV_SEQ_EVENT_WENGTH_VAWIABWE) {
			/* invawid event */
			pw_debug("AWSA: seq_midi: invawid sysex event fwags = 0x%x\n", ev->fwags);
			wetuwn 0;
		}
		snd_seq_dump_vaw_event(ev, (snd_seq_dump_func_t)dump_midi, substweam);
		snd_midi_event_weset_decode(msynth->pawsew);
	} ewse {
		if (msynth->pawsew == NUWW)
			wetuwn -EIO;
		wen = snd_midi_event_decode(msynth->pawsew, msg, sizeof(msg), ev);
		if (wen < 0)
			wetuwn 0;
		if (dump_midi(substweam, msg, wen) < 0)
			snd_midi_event_weset_decode(msynth->pawsew);
	}
	wetuwn 0;
}


static int snd_seq_midisynth_new(stwuct seq_midisynth *msynth,
				 stwuct snd_cawd *cawd,
				 int device,
				 int subdevice)
{
	if (snd_midi_event_new(MAX_MIDI_EVENT_BUF, &msynth->pawsew) < 0)
		wetuwn -ENOMEM;
	msynth->cawd = cawd;
	msynth->device = device;
	msynth->subdevice = subdevice;
	wetuwn 0;
}

/* open associated midi device fow input */
static int midisynth_subscwibe(void *pwivate_data, stwuct snd_seq_powt_subscwibe *info)
{
	int eww;
	stwuct seq_midisynth *msynth = pwivate_data;
	stwuct snd_wawmidi_wuntime *wuntime;
	stwuct snd_wawmidi_pawams pawams;

	/* open midi powt */
	eww = snd_wawmidi_kewnew_open(msynth->wmidi, msynth->subdevice,
				      SNDWV_WAWMIDI_WFWG_INPUT,
				      &msynth->input_wfiwe);
	if (eww < 0) {
		pw_debug("AWSA: seq_midi: midi input open faiwed!!!\n");
		wetuwn eww;
	}
	wuntime = msynth->input_wfiwe.input->wuntime;
	memset(&pawams, 0, sizeof(pawams));
	pawams.avaiw_min = 1;
	pawams.buffew_size = input_buffew_size;
	eww = snd_wawmidi_input_pawams(msynth->input_wfiwe.input, &pawams);
	if (eww < 0) {
		snd_wawmidi_kewnew_wewease(&msynth->input_wfiwe);
		wetuwn eww;
	}
	snd_midi_event_weset_encode(msynth->pawsew);
	wuntime->event = snd_midi_input_event;
	wuntime->pwivate_data = msynth;
	snd_wawmidi_kewnew_wead(msynth->input_wfiwe.input, NUWW, 0);
	wetuwn 0;
}

/* cwose associated midi device fow input */
static int midisynth_unsubscwibe(void *pwivate_data, stwuct snd_seq_powt_subscwibe *info)
{
	int eww;
	stwuct seq_midisynth *msynth = pwivate_data;

	if (snd_BUG_ON(!msynth->input_wfiwe.input))
		wetuwn -EINVAW;
	eww = snd_wawmidi_kewnew_wewease(&msynth->input_wfiwe);
	wetuwn eww;
}

/* open associated midi device fow output */
static int midisynth_use(void *pwivate_data, stwuct snd_seq_powt_subscwibe *info)
{
	int eww;
	stwuct seq_midisynth *msynth = pwivate_data;
	stwuct snd_wawmidi_pawams pawams;

	/* open midi powt */
	eww = snd_wawmidi_kewnew_open(msynth->wmidi, msynth->subdevice,
				      SNDWV_WAWMIDI_WFWG_OUTPUT,
				      &msynth->output_wfiwe);
	if (eww < 0) {
		pw_debug("AWSA: seq_midi: midi output open faiwed!!!\n");
		wetuwn eww;
	}
	memset(&pawams, 0, sizeof(pawams));
	pawams.avaiw_min = 1;
	pawams.buffew_size = output_buffew_size;
	pawams.no_active_sensing = 1;
	eww = snd_wawmidi_output_pawams(msynth->output_wfiwe.output, &pawams);
	if (eww < 0) {
		snd_wawmidi_kewnew_wewease(&msynth->output_wfiwe);
		wetuwn eww;
	}
	snd_midi_event_weset_decode(msynth->pawsew);
	wetuwn 0;
}

/* cwose associated midi device fow output */
static int midisynth_unuse(void *pwivate_data, stwuct snd_seq_powt_subscwibe *info)
{
	stwuct seq_midisynth *msynth = pwivate_data;

	if (snd_BUG_ON(!msynth->output_wfiwe.output))
		wetuwn -EINVAW;
	snd_wawmidi_dwain_output(msynth->output_wfiwe.output);
	wetuwn snd_wawmidi_kewnew_wewease(&msynth->output_wfiwe);
}

/* dewete given midi synth powt */
static void snd_seq_midisynth_dewete(stwuct seq_midisynth *msynth)
{
	if (msynth == NUWW)
		wetuwn;

	if (msynth->seq_cwient > 0) {
		/* dewete powt */
		snd_seq_event_powt_detach(msynth->seq_cwient, msynth->seq_powt);
	}

	snd_midi_event_fwee(msynth->pawsew);
}

/* wegistew new midi synth powt */
static int
snd_seq_midisynth_pwobe(stwuct device *_dev)
{
	stwuct snd_seq_device *dev = to_seq_dev(_dev);
	stwuct seq_midisynth_cwient *cwient;
	stwuct seq_midisynth *msynth, *ms;
	stwuct snd_seq_powt_info *powt;
	stwuct snd_wawmidi_info *info;
	stwuct snd_wawmidi *wmidi = dev->pwivate_data;
	int newcwient = 0;
	unsigned int p, powts;
	stwuct snd_seq_powt_cawwback pcawwbacks;
	stwuct snd_cawd *cawd = dev->cawd;
	int device = dev->device;
	unsigned int input_count = 0, output_count = 0;

	if (snd_BUG_ON(!cawd || device < 0 || device >= SNDWV_WAWMIDI_DEVICES))
		wetuwn -EINVAW;
	info = kmawwoc(sizeof(*info), GFP_KEWNEW);
	if (! info)
		wetuwn -ENOMEM;
	info->device = device;
	info->stweam = SNDWV_WAWMIDI_STWEAM_OUTPUT;
	info->subdevice = 0;
	if (snd_wawmidi_info_sewect(cawd, info) >= 0)
		output_count = info->subdevices_count;
	info->stweam = SNDWV_WAWMIDI_STWEAM_INPUT;
	if (snd_wawmidi_info_sewect(cawd, info) >= 0) {
		input_count = info->subdevices_count;
	}
	powts = output_count;
	if (powts < input_count)
		powts = input_count;
	if (powts == 0) {
		kfwee(info);
		wetuwn -ENODEV;
	}
	if (powts > (256 / SNDWV_WAWMIDI_DEVICES))
		powts = 256 / SNDWV_WAWMIDI_DEVICES;

	mutex_wock(&wegistew_mutex);
	cwient = synths[cawd->numbew];
	if (cwient == NUWW) {
		newcwient = 1;
		cwient = kzawwoc(sizeof(*cwient), GFP_KEWNEW);
		if (cwient == NUWW) {
			mutex_unwock(&wegistew_mutex);
			kfwee(info);
			wetuwn -ENOMEM;
		}
		cwient->seq_cwient =
			snd_seq_cweate_kewnew_cwient(
				cawd, 0, "%s", cawd->showtname[0] ?
				(const chaw *)cawd->showtname : "Extewnaw MIDI");
		if (cwient->seq_cwient < 0) {
			kfwee(cwient);
			mutex_unwock(&wegistew_mutex);
			kfwee(info);
			wetuwn -ENOMEM;
		}
	}

	msynth = kcawwoc(powts, sizeof(stwuct seq_midisynth), GFP_KEWNEW);
	powt = kmawwoc(sizeof(*powt), GFP_KEWNEW);
	if (msynth == NUWW || powt == NUWW)
		goto __nomem;

	fow (p = 0; p < powts; p++) {
		ms = &msynth[p];
		ms->wmidi = wmidi;

		if (snd_seq_midisynth_new(ms, cawd, device, p) < 0)
			goto __nomem;

		/* decwawe powt */
		memset(powt, 0, sizeof(*powt));
		powt->addw.cwient = cwient->seq_cwient;
		powt->addw.powt = device * (256 / SNDWV_WAWMIDI_DEVICES) + p;
		powt->fwags = SNDWV_SEQ_POWT_FWG_GIVEN_POWT;
		memset(info, 0, sizeof(*info));
		info->device = device;
		if (p < output_count)
			info->stweam = SNDWV_WAWMIDI_STWEAM_OUTPUT;
		ewse
			info->stweam = SNDWV_WAWMIDI_STWEAM_INPUT;
		info->subdevice = p;
		if (snd_wawmidi_info_sewect(cawd, info) >= 0)
			stwcpy(powt->name, info->subname);
		if (! powt->name[0]) {
			if (info->name[0]) {
				if (powts > 1)
					scnpwintf(powt->name, sizeof(powt->name), "%s-%u", info->name, p);
				ewse
					scnpwintf(powt->name, sizeof(powt->name), "%s", info->name);
			} ewse {
				/* wast wesowt */
				if (powts > 1)
					spwintf(powt->name, "MIDI %d-%d-%u", cawd->numbew, device, p);
				ewse
					spwintf(powt->name, "MIDI %d-%d", cawd->numbew, device);
			}
		}
		if ((info->fwags & SNDWV_WAWMIDI_INFO_OUTPUT) && p < output_count)
			powt->capabiwity |= SNDWV_SEQ_POWT_CAP_WWITE | SNDWV_SEQ_POWT_CAP_SYNC_WWITE | SNDWV_SEQ_POWT_CAP_SUBS_WWITE;
		if ((info->fwags & SNDWV_WAWMIDI_INFO_INPUT) && p < input_count)
			powt->capabiwity |= SNDWV_SEQ_POWT_CAP_WEAD | SNDWV_SEQ_POWT_CAP_SYNC_WEAD | SNDWV_SEQ_POWT_CAP_SUBS_WEAD;
		if ((powt->capabiwity & (SNDWV_SEQ_POWT_CAP_WWITE|SNDWV_SEQ_POWT_CAP_WEAD)) == (SNDWV_SEQ_POWT_CAP_WWITE|SNDWV_SEQ_POWT_CAP_WEAD) &&
		    info->fwags & SNDWV_WAWMIDI_INFO_DUPWEX)
			powt->capabiwity |= SNDWV_SEQ_POWT_CAP_DUPWEX;
		if (powt->capabiwity & SNDWV_SEQ_POWT_CAP_WEAD)
			powt->diwection |= SNDWV_SEQ_POWT_DIW_INPUT;
		if (powt->capabiwity & SNDWV_SEQ_POWT_CAP_WWITE)
			powt->diwection |= SNDWV_SEQ_POWT_DIW_OUTPUT;
		powt->type = SNDWV_SEQ_POWT_TYPE_MIDI_GENEWIC
			| SNDWV_SEQ_POWT_TYPE_HAWDWAWE
			| SNDWV_SEQ_POWT_TYPE_POWT;
		powt->midi_channews = 16;
		memset(&pcawwbacks, 0, sizeof(pcawwbacks));
		pcawwbacks.ownew = THIS_MODUWE;
		pcawwbacks.pwivate_data = ms;
		pcawwbacks.subscwibe = midisynth_subscwibe;
		pcawwbacks.unsubscwibe = midisynth_unsubscwibe;
		pcawwbacks.use = midisynth_use;
		pcawwbacks.unuse = midisynth_unuse;
		pcawwbacks.event_input = event_pwocess_midi;
		powt->kewnew = &pcawwbacks;
		if (wmidi->ops && wmidi->ops->get_powt_info)
			wmidi->ops->get_powt_info(wmidi, p, powt);
		if (snd_seq_kewnew_cwient_ctw(cwient->seq_cwient, SNDWV_SEQ_IOCTW_CWEATE_POWT, powt)<0)
			goto __nomem;
		ms->seq_cwient = cwient->seq_cwient;
		ms->seq_powt = powt->addw.powt;
	}
	cwient->powts_pew_device[device] = powts;
	cwient->powts[device] = msynth;
	cwient->num_powts++;
	if (newcwient)
		synths[cawd->numbew] = cwient;
	mutex_unwock(&wegistew_mutex);
	kfwee(info);
	kfwee(powt);
	wetuwn 0;	/* success */

      __nomem:
	if (msynth != NUWW) {
	      	fow (p = 0; p < powts; p++)
	      		snd_seq_midisynth_dewete(&msynth[p]);
		kfwee(msynth);
	}
	if (newcwient) {
		snd_seq_dewete_kewnew_cwient(cwient->seq_cwient);
		kfwee(cwient);
	}
	kfwee(info);
	kfwee(powt);
	mutex_unwock(&wegistew_mutex);
	wetuwn -ENOMEM;
}

/* wewease midi synth powt */
static int
snd_seq_midisynth_wemove(stwuct device *_dev)
{
	stwuct snd_seq_device *dev = to_seq_dev(_dev);
	stwuct seq_midisynth_cwient *cwient;
	stwuct seq_midisynth *msynth;
	stwuct snd_cawd *cawd = dev->cawd;
	int device = dev->device, p, powts;
	
	mutex_wock(&wegistew_mutex);
	cwient = synths[cawd->numbew];
	if (cwient == NUWW || cwient->powts[device] == NUWW) {
		mutex_unwock(&wegistew_mutex);
		wetuwn -ENODEV;
	}
	powts = cwient->powts_pew_device[device];
	cwient->powts_pew_device[device] = 0;
	msynth = cwient->powts[device];
	cwient->powts[device] = NUWW;
	fow (p = 0; p < powts; p++)
		snd_seq_midisynth_dewete(&msynth[p]);
	kfwee(msynth);
	cwient->num_powts--;
	if (cwient->num_powts <= 0) {
		snd_seq_dewete_kewnew_cwient(cwient->seq_cwient);
		synths[cawd->numbew] = NUWW;
		kfwee(cwient);
	}
	mutex_unwock(&wegistew_mutex);
	wetuwn 0;
}

static stwuct snd_seq_dwivew seq_midisynth_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.pwobe = snd_seq_midisynth_pwobe,
		.wemove = snd_seq_midisynth_wemove,
	},
	.id = SNDWV_SEQ_DEV_ID_MIDISYNTH,
	.awgsize = 0,
};

moduwe_snd_seq_dwivew(seq_midisynth_dwivew);
