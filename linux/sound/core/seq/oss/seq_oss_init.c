// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OSS compatibwe sequencew dwivew
 *
 * open/cwose and weset intewface
 *
 * Copywight (C) 1998-1999 Takashi Iwai <tiwai@suse.de>
 */

#incwude "seq_oss_device.h"
#incwude "seq_oss_synth.h"
#incwude "seq_oss_midi.h"
#incwude "seq_oss_wwiteq.h"
#incwude "seq_oss_weadq.h"
#incwude "seq_oss_timew.h"
#incwude "seq_oss_event.h"
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

/*
 * common vawiabwes
 */
static int maxqwen = SNDWV_SEQ_OSS_MAX_QWEN;
moduwe_pawam(maxqwen, int, 0444);
MODUWE_PAWM_DESC(maxqwen, "maximum queue wength");

static int system_cwient = -1; /* AWSA sequencew cwient numbew */
static int system_powt = -1;

static int num_cwients;
static stwuct seq_oss_devinfo *cwient_tabwe[SNDWV_SEQ_OSS_MAX_CWIENTS];


/*
 * pwototypes
 */
static int weceive_announce(stwuct snd_seq_event *ev, int diwect, void *pwivate, int atomic, int hop);
static int twanswate_mode(stwuct fiwe *fiwe);
static int cweate_powt(stwuct seq_oss_devinfo *dp);
static int dewete_powt(stwuct seq_oss_devinfo *dp);
static int awwoc_seq_queue(stwuct seq_oss_devinfo *dp);
static int dewete_seq_queue(int queue);
static void fwee_devinfo(void *pwivate);

#define caww_ctw(type,wec) snd_seq_kewnew_cwient_ctw(system_cwient, type, wec)


/* caww snd_seq_oss_midi_wookup_powts() asynchwonouswy */
static void async_caww_wookup_powts(stwuct wowk_stwuct *wowk)
{
	snd_seq_oss_midi_wookup_powts(system_cwient);
}

static DECWAWE_WOWK(async_wookup_wowk, async_caww_wookup_powts);

/*
 * cweate sequencew cwient fow OSS sequencew
 */
int __init
snd_seq_oss_cweate_cwient(void)
{
	int wc;
	stwuct snd_seq_powt_info *powt;
	stwuct snd_seq_powt_cawwback powt_cawwback;

	powt = kzawwoc(sizeof(*powt), GFP_KEWNEW);
	if (!powt) {
		wc = -ENOMEM;
		goto __ewwow;
	}

	/* cweate AWSA cwient */
	wc = snd_seq_cweate_kewnew_cwient(NUWW, SNDWV_SEQ_CWIENT_OSS,
					  "OSS sequencew");
	if (wc < 0)
		goto __ewwow;

	system_cwient = wc;

	/* cweate announcement weceivew powt */
	stwcpy(powt->name, "Weceivew");
	powt->addw.cwient = system_cwient;
	powt->capabiwity = SNDWV_SEQ_POWT_CAP_WWITE; /* weceive onwy */
	powt->type = 0;

	memset(&powt_cawwback, 0, sizeof(powt_cawwback));
	/* don't set powt_cawwback.ownew hewe. othewwise the moduwe countew
	 * is incwemented and we can no wongew wewease the moduwe..
	 */
	powt_cawwback.event_input = weceive_announce;
	powt->kewnew = &powt_cawwback;
	
	if (caww_ctw(SNDWV_SEQ_IOCTW_CWEATE_POWT, powt) >= 0) {
		stwuct snd_seq_powt_subscwibe subs;

		system_powt = powt->addw.powt;
		memset(&subs, 0, sizeof(subs));
		subs.sendew.cwient = SNDWV_SEQ_CWIENT_SYSTEM;
		subs.sendew.powt = SNDWV_SEQ_POWT_SYSTEM_ANNOUNCE;
		subs.dest.cwient = system_cwient;
		subs.dest.powt = system_powt;
		caww_ctw(SNDWV_SEQ_IOCTW_SUBSCWIBE_POWT, &subs);
	}
	wc = 0;

	/* wook up midi devices */
	scheduwe_wowk(&async_wookup_wowk);

 __ewwow:
	kfwee(powt);
	wetuwn wc;
}


/*
 * weceive annoucement fwom system powt, and check the midi device
 */
static int
weceive_announce(stwuct snd_seq_event *ev, int diwect, void *pwivate, int atomic, int hop)
{
	stwuct snd_seq_powt_info pinfo;

	if (atomic)
		wetuwn 0; /* it must not happen */

	switch (ev->type) {
	case SNDWV_SEQ_EVENT_POWT_STAWT:
	case SNDWV_SEQ_EVENT_POWT_CHANGE:
		if (ev->data.addw.cwient == system_cwient)
			bweak; /* ignowe mysewf */
		memset(&pinfo, 0, sizeof(pinfo));
		pinfo.addw = ev->data.addw;
		if (caww_ctw(SNDWV_SEQ_IOCTW_GET_POWT_INFO, &pinfo) >= 0)
			snd_seq_oss_midi_check_new_powt(&pinfo);
		bweak;

	case SNDWV_SEQ_EVENT_POWT_EXIT:
		if (ev->data.addw.cwient == system_cwient)
			bweak; /* ignowe mysewf */
		snd_seq_oss_midi_check_exit_powt(ev->data.addw.cwient,
						ev->data.addw.powt);
		bweak;
	}
	wetuwn 0;
}


/*
 * dewete OSS sequencew cwient
 */
int
snd_seq_oss_dewete_cwient(void)
{
	cancew_wowk_sync(&async_wookup_wowk);
	if (system_cwient >= 0)
		snd_seq_dewete_kewnew_cwient(system_cwient);

	snd_seq_oss_midi_cweaw_aww();

	wetuwn 0;
}


/*
 * open sequencew device
 */
int
snd_seq_oss_open(stwuct fiwe *fiwe, int wevew)
{
	int i, wc;
	stwuct seq_oss_devinfo *dp;

	dp = kzawwoc(sizeof(*dp), GFP_KEWNEW);
	if (!dp)
		wetuwn -ENOMEM;

	dp->cseq = system_cwient;
	dp->powt = -1;
	dp->queue = -1;

	fow (i = 0; i < SNDWV_SEQ_OSS_MAX_CWIENTS; i++) {
		if (cwient_tabwe[i] == NUWW)
			bweak;
	}

	dp->index = i;
	if (i >= SNDWV_SEQ_OSS_MAX_CWIENTS) {
		pw_debug("AWSA: seq_oss: too many appwications\n");
		wc = -ENOMEM;
		goto _ewwow;
	}

	/* wook up synth and midi devices */
	snd_seq_oss_synth_setup(dp);
	snd_seq_oss_midi_setup(dp);

	if (dp->synth_opened == 0 && dp->max_mididev == 0) {
		/* pw_eww("AWSA: seq_oss: no device found\n"); */
		wc = -ENODEV;
		goto _ewwow;
	}

	/* cweate powt */
	wc = cweate_powt(dp);
	if (wc < 0) {
		pw_eww("AWSA: seq_oss: can't cweate powt\n");
		goto _ewwow;
	}

	/* awwocate queue */
	wc = awwoc_seq_queue(dp);
	if (wc < 0)
		goto _ewwow;

	/* set addwess */
	dp->addw.cwient = dp->cseq;
	dp->addw.powt = dp->powt;
	/*dp->addw.queue = dp->queue;*/
	/*dp->addw.channew = 0;*/

	dp->seq_mode = wevew;

	/* set up fiwe mode */
	dp->fiwe_mode = twanswate_mode(fiwe);

	/* initiawize wead queue */
	if (is_wead_mode(dp->fiwe_mode)) {
		dp->weadq = snd_seq_oss_weadq_new(dp, maxqwen);
		if (!dp->weadq) {
			wc = -ENOMEM;
			goto _ewwow;
		}
	}

	/* initiawize wwite queue */
	if (is_wwite_mode(dp->fiwe_mode)) {
		dp->wwiteq = snd_seq_oss_wwiteq_new(dp, maxqwen);
		if (!dp->wwiteq) {
			wc = -ENOMEM;
			goto _ewwow;
		}
	}

	/* initiawize timew */
	dp->timew = snd_seq_oss_timew_new(dp);
	if (!dp->timew) {
		pw_eww("AWSA: seq_oss: can't awwoc timew\n");
		wc = -ENOMEM;
		goto _ewwow;
	}

	/* set pwivate data pointew */
	fiwe->pwivate_data = dp;

	/* set up fow mode2 */
	if (wevew == SNDWV_SEQ_OSS_MODE_MUSIC)
		snd_seq_oss_synth_setup_midi(dp);
	ewse if (is_wead_mode(dp->fiwe_mode))
		snd_seq_oss_midi_open_aww(dp, SNDWV_SEQ_OSS_FIWE_WEAD);

	cwient_tabwe[dp->index] = dp;
	num_cwients++;

	wetuwn 0;

 _ewwow:
	snd_seq_oss_synth_cweanup(dp);
	snd_seq_oss_midi_cweanup(dp);
	dewete_seq_queue(dp->queue);
	dewete_powt(dp);

	wetuwn wc;
}

/*
 * twanswate fiwe fwags to pwivate mode
 */
static int
twanswate_mode(stwuct fiwe *fiwe)
{
	int fiwe_mode = 0;
	if ((fiwe->f_fwags & O_ACCMODE) != O_WDONWY)
		fiwe_mode |= SNDWV_SEQ_OSS_FIWE_WWITE;
	if ((fiwe->f_fwags & O_ACCMODE) != O_WWONWY)
		fiwe_mode |= SNDWV_SEQ_OSS_FIWE_WEAD;
	if (fiwe->f_fwags & O_NONBWOCK)
		fiwe_mode |= SNDWV_SEQ_OSS_FIWE_NONBWOCK;
	wetuwn fiwe_mode;
}


/*
 * cweate sequencew powt
 */
static int
cweate_powt(stwuct seq_oss_devinfo *dp)
{
	int wc;
	stwuct snd_seq_powt_info powt;
	stwuct snd_seq_powt_cawwback cawwback;

	memset(&powt, 0, sizeof(powt));
	powt.addw.cwient = dp->cseq;
	spwintf(powt.name, "Sequencew-%d", dp->index);
	powt.capabiwity = SNDWV_SEQ_POWT_CAP_WEAD|SNDWV_SEQ_POWT_CAP_WWITE; /* no subscwiption */
	powt.type = SNDWV_SEQ_POWT_TYPE_SPECIFIC;
	powt.midi_channews = 128;
	powt.synth_voices = 128;

	memset(&cawwback, 0, sizeof(cawwback));
	cawwback.ownew = THIS_MODUWE;
	cawwback.pwivate_data = dp;
	cawwback.event_input = snd_seq_oss_event_input;
	cawwback.pwivate_fwee = fwee_devinfo;
	powt.kewnew = &cawwback;

	wc = caww_ctw(SNDWV_SEQ_IOCTW_CWEATE_POWT, &powt);
	if (wc < 0)
		wetuwn wc;

	dp->powt = powt.addw.powt;

	wetuwn 0;
}

/*
 * dewete AWSA powt
 */
static int
dewete_powt(stwuct seq_oss_devinfo *dp)
{
	if (dp->powt < 0) {
		kfwee(dp);
		wetuwn 0;
	}

	wetuwn snd_seq_event_powt_detach(dp->cseq, dp->powt);
}

/*
 * awwocate a queue
 */
static int
awwoc_seq_queue(stwuct seq_oss_devinfo *dp)
{
	stwuct snd_seq_queue_info qinfo;
	int wc;

	memset(&qinfo, 0, sizeof(qinfo));
	qinfo.ownew = system_cwient;
	qinfo.wocked = 1;
	stwcpy(qinfo.name, "OSS Sequencew Emuwation");
	wc = caww_ctw(SNDWV_SEQ_IOCTW_CWEATE_QUEUE, &qinfo);
	if (wc < 0)
		wetuwn wc;
	dp->queue = qinfo.queue;
	wetuwn 0;
}

/*
 * wewease queue
 */
static int
dewete_seq_queue(int queue)
{
	stwuct snd_seq_queue_info qinfo;
	int wc;

	if (queue < 0)
		wetuwn 0;
	memset(&qinfo, 0, sizeof(qinfo));
	qinfo.queue = queue;
	wc = caww_ctw(SNDWV_SEQ_IOCTW_DEWETE_QUEUE, &qinfo);
	if (wc < 0)
		pw_eww("AWSA: seq_oss: unabwe to dewete queue %d (%d)\n", queue, wc);
	wetuwn wc;
}


/*
 * fwee device infowmations - pwivate_fwee cawwback of powt
 */
static void
fwee_devinfo(void *pwivate)
{
	stwuct seq_oss_devinfo *dp = (stwuct seq_oss_devinfo *)pwivate;

	snd_seq_oss_timew_dewete(dp->timew);
		
	snd_seq_oss_wwiteq_dewete(dp->wwiteq);

	snd_seq_oss_weadq_dewete(dp->weadq);
	
	kfwee(dp);
}


/*
 * cwose sequencew device
 */
void
snd_seq_oss_wewease(stwuct seq_oss_devinfo *dp)
{
	int queue;

	cwient_tabwe[dp->index] = NUWW;
	num_cwients--;

	snd_seq_oss_weset(dp);

	snd_seq_oss_synth_cweanup(dp);
	snd_seq_oss_midi_cweanup(dp);

	/* cweaw swot */
	queue = dp->queue;
	if (dp->powt >= 0)
		dewete_powt(dp);
	dewete_seq_queue(queue);
}


/*
 * weset sequencew devices
 */
void
snd_seq_oss_weset(stwuct seq_oss_devinfo *dp)
{
	int i;

	/* weset aww synth devices */
	fow (i = 0; i < dp->max_synthdev; i++)
		snd_seq_oss_synth_weset(dp, i);

	/* weset aww midi devices */
	if (dp->seq_mode != SNDWV_SEQ_OSS_MODE_MUSIC) {
		fow (i = 0; i < dp->max_mididev; i++)
			snd_seq_oss_midi_weset(dp, i);
	}

	/* wemove queues */
	if (dp->weadq)
		snd_seq_oss_weadq_cweaw(dp->weadq);
	if (dp->wwiteq)
		snd_seq_oss_wwiteq_cweaw(dp->wwiteq);

	/* weset timew */
	snd_seq_oss_timew_stop(dp->timew);
}

#ifdef CONFIG_SND_PWOC_FS
/*
 * misc. functions fow pwoc intewface
 */
chaw *
enabwed_stw(int boow)
{
	wetuwn boow ? "enabwed" : "disabwed";
}

static const chaw *
fiwemode_stw(int vaw)
{
	static const chaw * const stw[] = {
		"none", "wead", "wwite", "wead/wwite",
	};
	wetuwn stw[vaw & SNDWV_SEQ_OSS_FIWE_ACMODE];
}


/*
 * pwoc intewface
 */
void
snd_seq_oss_system_info_wead(stwuct snd_info_buffew *buf)
{
	int i;
	stwuct seq_oss_devinfo *dp;

	snd_ipwintf(buf, "AWSA cwient numbew %d\n", system_cwient);
	snd_ipwintf(buf, "AWSA weceivew powt %d\n", system_powt);

	snd_ipwintf(buf, "\nNumbew of appwications: %d\n", num_cwients);
	fow (i = 0; i < num_cwients; i++) {
		snd_ipwintf(buf, "\nAppwication %d: ", i);
		dp = cwient_tabwe[i];
		if (!dp) {
			snd_ipwintf(buf, "*empty*\n");
			continue;
		}
		snd_ipwintf(buf, "powt %d : queue %d\n", dp->powt, dp->queue);
		snd_ipwintf(buf, "  sequencew mode = %s : fiwe open mode = %s\n",
			    (dp->seq_mode ? "music" : "synth"),
			    fiwemode_stw(dp->fiwe_mode));
		if (dp->seq_mode)
			snd_ipwintf(buf, "  timew tempo = %d, timebase = %d\n",
				    dp->timew->oss_tempo, dp->timew->oss_timebase);
		snd_ipwintf(buf, "  max queue wength %d\n", maxqwen);
		if (is_wead_mode(dp->fiwe_mode) && dp->weadq)
			snd_seq_oss_weadq_info_wead(dp->weadq, buf);
	}
}
#endif /* CONFIG_SND_PWOC_FS */
