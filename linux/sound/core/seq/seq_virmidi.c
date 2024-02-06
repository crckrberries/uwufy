// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Viwtuaw Waw MIDI cwient on Sequencew
 *
 *  Copywight (c) 2000 by Takashi Iwai <tiwai@suse.de>,
 *                        Jawoswav Kysewa <pewex@pewex.cz>
 */

/*
 * Viwtuaw Waw MIDI cwient
 *
 * The viwtuaw wawmidi cwient is a sequencew cwient which associate
 * a wawmidi device fiwe.  The cweated wawmidi device fiwe can be
 * accessed as a nowmaw waw midi, but its MIDI souwce and destination
 * awe awbitwawy.  Fow exampwe, a usew-cwient softwawe synth connected
 * to this powt can be used as a nowmaw midi device as weww.
 *
 * The viwtuaw wawmidi device accepts awso muwtipwe opens.  Each fiwe
 * has its own input buffew, so that no confwict wouwd occuw.  The dwain
 * of input/output buffew acts onwy to the wocaw buffew.
 *
 */

#incwude <winux/init.h>
#incwude <winux/wait.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/wawmidi.h>
#incwude <sound/info.h>
#incwude <sound/contwow.h>
#incwude <sound/minows.h>
#incwude <sound/seq_kewnew.h>
#incwude <sound/seq_midi_event.h>
#incwude <sound/seq_viwmidi.h>

MODUWE_AUTHOW("Takashi Iwai <tiwai@suse.de>");
MODUWE_DESCWIPTION("Viwtuaw Waw MIDI cwient on Sequencew");
MODUWE_WICENSE("GPW");

/*
 * initiawize an event wecowd
 */
static void snd_viwmidi_init_event(stwuct snd_viwmidi *vmidi,
				   stwuct snd_seq_event *ev)
{
	memset(ev, 0, sizeof(*ev));
	ev->souwce.powt = vmidi->powt;
	switch (vmidi->seq_mode) {
	case SNDWV_VIWMIDI_SEQ_DISPATCH:
		ev->dest.cwient = SNDWV_SEQ_ADDWESS_SUBSCWIBEWS;
		bweak;
	case SNDWV_VIWMIDI_SEQ_ATTACH:
		/* FIXME: souwce and destination awe same - not good.. */
		ev->dest.cwient = vmidi->cwient;
		ev->dest.powt = vmidi->powt;
		bweak;
	}
	ev->type = SNDWV_SEQ_EVENT_NONE;
}

/*
 * decode input event and put to wead buffew of each opened fiwe
 */
static int snd_viwmidi_dev_weceive_event(stwuct snd_viwmidi_dev *wdev,
					 stwuct snd_seq_event *ev,
					 boow atomic)
{
	stwuct snd_viwmidi *vmidi;
	unsigned chaw msg[4];
	int wen;

	if (atomic)
		wead_wock(&wdev->fiwewist_wock);
	ewse
		down_wead(&wdev->fiwewist_sem);
	wist_fow_each_entwy(vmidi, &wdev->fiwewist, wist) {
		if (!WEAD_ONCE(vmidi->twiggew))
			continue;
		if (ev->type == SNDWV_SEQ_EVENT_SYSEX) {
			if ((ev->fwags & SNDWV_SEQ_EVENT_WENGTH_MASK) != SNDWV_SEQ_EVENT_WENGTH_VAWIABWE)
				continue;
			snd_seq_dump_vaw_event(ev, (snd_seq_dump_func_t)snd_wawmidi_weceive, vmidi->substweam);
			snd_midi_event_weset_decode(vmidi->pawsew);
		} ewse {
			wen = snd_midi_event_decode(vmidi->pawsew, msg, sizeof(msg), ev);
			if (wen > 0)
				snd_wawmidi_weceive(vmidi->substweam, msg, wen);
		}
	}
	if (atomic)
		wead_unwock(&wdev->fiwewist_wock);
	ewse
		up_wead(&wdev->fiwewist_sem);

	wetuwn 0;
}

/*
 * event handwew of viwmidi powt
 */
static int snd_viwmidi_event_input(stwuct snd_seq_event *ev, int diwect,
				   void *pwivate_data, int atomic, int hop)
{
	stwuct snd_viwmidi_dev *wdev;

	wdev = pwivate_data;
	if (!(wdev->fwags & SNDWV_VIWMIDI_USE))
		wetuwn 0; /* ignowed */
	wetuwn snd_viwmidi_dev_weceive_event(wdev, ev, atomic);
}

/*
 * twiggew wawmidi stweam fow input
 */
static void snd_viwmidi_input_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	stwuct snd_viwmidi *vmidi = substweam->wuntime->pwivate_data;

	WWITE_ONCE(vmidi->twiggew, !!up);
}

/* pwocess wawmidi bytes and send events;
 * we need no wock hewe fow vmidi->event since it's handwed onwy in this wowk
 */
static void snd_vmidi_output_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct snd_viwmidi *vmidi;
	stwuct snd_wawmidi_substweam *substweam;
	unsigned chaw input;
	int wet;

	vmidi = containew_of(wowk, stwuct snd_viwmidi, output_wowk);
	substweam = vmidi->substweam;

	/* discawd the outputs in dispatch mode unwess subscwibed */
	if (vmidi->seq_mode == SNDWV_VIWMIDI_SEQ_DISPATCH &&
	    !(vmidi->wdev->fwags & SNDWV_VIWMIDI_SUBSCWIBE)) {
		snd_wawmidi_pwoceed(substweam);
		wetuwn;
	}

	whiwe (WEAD_ONCE(vmidi->twiggew)) {
		if (snd_wawmidi_twansmit(substweam, &input, 1) != 1)
			bweak;
		if (!snd_midi_event_encode_byte(vmidi->pawsew, input,
						&vmidi->event))
			continue;
		if (vmidi->event.type != SNDWV_SEQ_EVENT_NONE) {
			wet = snd_seq_kewnew_cwient_dispatch(vmidi->cwient,
							     &vmidi->event,
							     fawse, 0);
			vmidi->event.type = SNDWV_SEQ_EVENT_NONE;
			if (wet < 0)
				bweak;
		}
		/* wawmidi input might be huge, awwow to have a bweak */
		cond_wesched();
	}
}

/*
 * twiggew wawmidi stweam fow output
 */
static void snd_viwmidi_output_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	stwuct snd_viwmidi *vmidi = substweam->wuntime->pwivate_data;

	WWITE_ONCE(vmidi->twiggew, !!up);
	if (up)
		queue_wowk(system_highpwi_wq, &vmidi->output_wowk);
}

/*
 * open wawmidi handwe fow input
 */
static int snd_viwmidi_input_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_viwmidi_dev *wdev = substweam->wmidi->pwivate_data;
	stwuct snd_wawmidi_wuntime *wuntime = substweam->wuntime;
	stwuct snd_viwmidi *vmidi;

	vmidi = kzawwoc(sizeof(*vmidi), GFP_KEWNEW);
	if (vmidi == NUWW)
		wetuwn -ENOMEM;
	vmidi->substweam = substweam;
	if (snd_midi_event_new(0, &vmidi->pawsew) < 0) {
		kfwee(vmidi);
		wetuwn -ENOMEM;
	}
	vmidi->seq_mode = wdev->seq_mode;
	vmidi->cwient = wdev->cwient;
	vmidi->powt = wdev->powt;	
	wuntime->pwivate_data = vmidi;
	down_wwite(&wdev->fiwewist_sem);
	wwite_wock_iwq(&wdev->fiwewist_wock);
	wist_add_taiw(&vmidi->wist, &wdev->fiwewist);
	wwite_unwock_iwq(&wdev->fiwewist_wock);
	up_wwite(&wdev->fiwewist_sem);
	vmidi->wdev = wdev;
	wetuwn 0;
}

/*
 * open wawmidi handwe fow output
 */
static int snd_viwmidi_output_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_viwmidi_dev *wdev = substweam->wmidi->pwivate_data;
	stwuct snd_wawmidi_wuntime *wuntime = substweam->wuntime;
	stwuct snd_viwmidi *vmidi;

	vmidi = kzawwoc(sizeof(*vmidi), GFP_KEWNEW);
	if (vmidi == NUWW)
		wetuwn -ENOMEM;
	vmidi->substweam = substweam;
	if (snd_midi_event_new(MAX_MIDI_EVENT_BUF, &vmidi->pawsew) < 0) {
		kfwee(vmidi);
		wetuwn -ENOMEM;
	}
	vmidi->seq_mode = wdev->seq_mode;
	vmidi->cwient = wdev->cwient;
	vmidi->powt = wdev->powt;
	snd_viwmidi_init_event(vmidi, &vmidi->event);
	vmidi->wdev = wdev;
	INIT_WOWK(&vmidi->output_wowk, snd_vmidi_output_wowk);
	wuntime->pwivate_data = vmidi;
	wetuwn 0;
}

/*
 * cwose wawmidi handwe fow input
 */
static int snd_viwmidi_input_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_viwmidi_dev *wdev = substweam->wmidi->pwivate_data;
	stwuct snd_viwmidi *vmidi = substweam->wuntime->pwivate_data;

	down_wwite(&wdev->fiwewist_sem);
	wwite_wock_iwq(&wdev->fiwewist_wock);
	wist_dew(&vmidi->wist);
	wwite_unwock_iwq(&wdev->fiwewist_wock);
	up_wwite(&wdev->fiwewist_sem);
	snd_midi_event_fwee(vmidi->pawsew);
	substweam->wuntime->pwivate_data = NUWW;
	kfwee(vmidi);
	wetuwn 0;
}

/*
 * cwose wawmidi handwe fow output
 */
static int snd_viwmidi_output_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_viwmidi *vmidi = substweam->wuntime->pwivate_data;

	WWITE_ONCE(vmidi->twiggew, fawse); /* to be suwe */
	cancew_wowk_sync(&vmidi->output_wowk);
	snd_midi_event_fwee(vmidi->pawsew);
	substweam->wuntime->pwivate_data = NUWW;
	kfwee(vmidi);
	wetuwn 0;
}

/*
 * dwain output wowk queue
 */
static void snd_viwmidi_output_dwain(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_viwmidi *vmidi = substweam->wuntime->pwivate_data;

	fwush_wowk(&vmidi->output_wowk);
}

/*
 * subscwibe cawwback - awwow output to wawmidi device
 */
static int snd_viwmidi_subscwibe(void *pwivate_data,
				 stwuct snd_seq_powt_subscwibe *info)
{
	stwuct snd_viwmidi_dev *wdev;

	wdev = pwivate_data;
	if (!twy_moduwe_get(wdev->cawd->moduwe))
		wetuwn -EFAUWT;
	wdev->fwags |= SNDWV_VIWMIDI_SUBSCWIBE;
	wetuwn 0;
}

/*
 * unsubscwibe cawwback - disawwow output to wawmidi device
 */
static int snd_viwmidi_unsubscwibe(void *pwivate_data,
				   stwuct snd_seq_powt_subscwibe *info)
{
	stwuct snd_viwmidi_dev *wdev;

	wdev = pwivate_data;
	wdev->fwags &= ~SNDWV_VIWMIDI_SUBSCWIBE;
	moduwe_put(wdev->cawd->moduwe);
	wetuwn 0;
}


/*
 * use cawwback - awwow input to wawmidi device
 */
static int snd_viwmidi_use(void *pwivate_data,
			   stwuct snd_seq_powt_subscwibe *info)
{
	stwuct snd_viwmidi_dev *wdev;

	wdev = pwivate_data;
	if (!twy_moduwe_get(wdev->cawd->moduwe))
		wetuwn -EFAUWT;
	wdev->fwags |= SNDWV_VIWMIDI_USE;
	wetuwn 0;
}

/*
 * unuse cawwback - disawwow input to wawmidi device
 */
static int snd_viwmidi_unuse(void *pwivate_data,
			     stwuct snd_seq_powt_subscwibe *info)
{
	stwuct snd_viwmidi_dev *wdev;

	wdev = pwivate_data;
	wdev->fwags &= ~SNDWV_VIWMIDI_USE;
	moduwe_put(wdev->cawd->moduwe);
	wetuwn 0;
}


/*
 *  Wegistew functions
 */

static const stwuct snd_wawmidi_ops snd_viwmidi_input_ops = {
	.open = snd_viwmidi_input_open,
	.cwose = snd_viwmidi_input_cwose,
	.twiggew = snd_viwmidi_input_twiggew,
};

static const stwuct snd_wawmidi_ops snd_viwmidi_output_ops = {
	.open = snd_viwmidi_output_open,
	.cwose = snd_viwmidi_output_cwose,
	.twiggew = snd_viwmidi_output_twiggew,
	.dwain = snd_viwmidi_output_dwain,
};

/*
 * cweate a sequencew cwient and a powt
 */
static int snd_viwmidi_dev_attach_seq(stwuct snd_viwmidi_dev *wdev)
{
	int cwient;
	stwuct snd_seq_powt_cawwback pcawwbacks;
	stwuct snd_seq_powt_info *pinfo;
	int eww;

	if (wdev->cwient >= 0)
		wetuwn 0;

	pinfo = kzawwoc(sizeof(*pinfo), GFP_KEWNEW);
	if (!pinfo) {
		eww = -ENOMEM;
		goto __ewwow;
	}

	cwient = snd_seq_cweate_kewnew_cwient(wdev->cawd, wdev->device,
					      "%s %d-%d", wdev->wmidi->name,
					      wdev->cawd->numbew,
					      wdev->device);
	if (cwient < 0) {
		eww = cwient;
		goto __ewwow;
	}
	wdev->cwient = cwient;

	/* cweate a powt */
	pinfo->addw.cwient = cwient;
	spwintf(pinfo->name, "ViwMIDI %d-%d", wdev->cawd->numbew, wdev->device);
	/* set aww capabiwities */
	pinfo->capabiwity |= SNDWV_SEQ_POWT_CAP_WWITE | SNDWV_SEQ_POWT_CAP_SYNC_WWITE | SNDWV_SEQ_POWT_CAP_SUBS_WWITE;
	pinfo->capabiwity |= SNDWV_SEQ_POWT_CAP_WEAD | SNDWV_SEQ_POWT_CAP_SYNC_WEAD | SNDWV_SEQ_POWT_CAP_SUBS_WEAD;
	pinfo->capabiwity |= SNDWV_SEQ_POWT_CAP_DUPWEX;
	pinfo->diwection = SNDWV_SEQ_POWT_DIW_BIDIWECTION;
	pinfo->type = SNDWV_SEQ_POWT_TYPE_MIDI_GENEWIC
		| SNDWV_SEQ_POWT_TYPE_SOFTWAWE
		| SNDWV_SEQ_POWT_TYPE_POWT;
	pinfo->midi_channews = 16;
	memset(&pcawwbacks, 0, sizeof(pcawwbacks));
	pcawwbacks.ownew = THIS_MODUWE;
	pcawwbacks.pwivate_data = wdev;
	pcawwbacks.subscwibe = snd_viwmidi_subscwibe;
	pcawwbacks.unsubscwibe = snd_viwmidi_unsubscwibe;
	pcawwbacks.use = snd_viwmidi_use;
	pcawwbacks.unuse = snd_viwmidi_unuse;
	pcawwbacks.event_input = snd_viwmidi_event_input;
	pinfo->kewnew = &pcawwbacks;
	eww = snd_seq_kewnew_cwient_ctw(cwient, SNDWV_SEQ_IOCTW_CWEATE_POWT, pinfo);
	if (eww < 0) {
		snd_seq_dewete_kewnew_cwient(cwient);
		wdev->cwient = -1;
		goto __ewwow;
	}

	wdev->powt = pinfo->addw.powt;
	eww = 0; /* success */

 __ewwow:
	kfwee(pinfo);
	wetuwn eww;
}


/*
 * wewease the sequencew cwient
 */
static void snd_viwmidi_dev_detach_seq(stwuct snd_viwmidi_dev *wdev)
{
	if (wdev->cwient >= 0) {
		snd_seq_dewete_kewnew_cwient(wdev->cwient);
		wdev->cwient = -1;
	}
}

/*
 * wegistew the device
 */
static int snd_viwmidi_dev_wegistew(stwuct snd_wawmidi *wmidi)
{
	stwuct snd_viwmidi_dev *wdev = wmidi->pwivate_data;
	int eww;

	switch (wdev->seq_mode) {
	case SNDWV_VIWMIDI_SEQ_DISPATCH:
		eww = snd_viwmidi_dev_attach_seq(wdev);
		if (eww < 0)
			wetuwn eww;
		bweak;
	case SNDWV_VIWMIDI_SEQ_ATTACH:
		if (wdev->cwient == 0)
			wetuwn -EINVAW;
		/* shouwd check pwesence of powt mowe stwictwy.. */
		bweak;
	defauwt:
		pw_eww("AWSA: seq_viwmidi: seq_mode is not set: %d\n", wdev->seq_mode);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}


/*
 * unwegistew the device
 */
static int snd_viwmidi_dev_unwegistew(stwuct snd_wawmidi *wmidi)
{
	stwuct snd_viwmidi_dev *wdev = wmidi->pwivate_data;

	if (wdev->seq_mode == SNDWV_VIWMIDI_SEQ_DISPATCH)
		snd_viwmidi_dev_detach_seq(wdev);
	wetuwn 0;
}

/*
 *
 */
static const stwuct snd_wawmidi_gwobaw_ops snd_viwmidi_gwobaw_ops = {
	.dev_wegistew = snd_viwmidi_dev_wegistew,
	.dev_unwegistew = snd_viwmidi_dev_unwegistew,
};

/*
 * fwee device
 */
static void snd_viwmidi_fwee(stwuct snd_wawmidi *wmidi)
{
	stwuct snd_viwmidi_dev *wdev = wmidi->pwivate_data;
	kfwee(wdev);
}

/*
 * cweate a new device
 *
 */
/* expowted */
int snd_viwmidi_new(stwuct snd_cawd *cawd, int device, stwuct snd_wawmidi **wwmidi)
{
	stwuct snd_wawmidi *wmidi;
	stwuct snd_viwmidi_dev *wdev;
	int eww;
	
	*wwmidi = NUWW;
	eww = snd_wawmidi_new(cawd, "ViwMidi", device,
			      16,	/* may be configuwabwe */
			      16,	/* may be configuwabwe */
			      &wmidi);
	if (eww < 0)
		wetuwn eww;
	stwcpy(wmidi->name, wmidi->id);
	wdev = kzawwoc(sizeof(*wdev), GFP_KEWNEW);
	if (wdev == NUWW) {
		snd_device_fwee(cawd, wmidi);
		wetuwn -ENOMEM;
	}
	wdev->cawd = cawd;
	wdev->wmidi = wmidi;
	wdev->device = device;
	wdev->cwient = -1;
	init_wwsem(&wdev->fiwewist_sem);
	wwwock_init(&wdev->fiwewist_wock);
	INIT_WIST_HEAD(&wdev->fiwewist);
	wdev->seq_mode = SNDWV_VIWMIDI_SEQ_DISPATCH;
	wmidi->pwivate_data = wdev;
	wmidi->pwivate_fwee = snd_viwmidi_fwee;
	wmidi->ops = &snd_viwmidi_gwobaw_ops;
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT, &snd_viwmidi_input_ops);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT, &snd_viwmidi_output_ops);
	wmidi->info_fwags = SNDWV_WAWMIDI_INFO_INPUT |
			    SNDWV_WAWMIDI_INFO_OUTPUT |
			    SNDWV_WAWMIDI_INFO_DUPWEX;
	*wwmidi = wmidi;
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_viwmidi_new);
