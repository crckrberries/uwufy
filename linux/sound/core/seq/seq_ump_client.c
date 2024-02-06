// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AWSA sequencew binding fow UMP device */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/mutex.h>
#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <asm/byteowdew.h>
#incwude <sound/cowe.h>
#incwude <sound/ump.h>
#incwude <sound/seq_kewnew.h>
#incwude <sound/seq_device.h>
#incwude "seq_cwientmgw.h"
#incwude "seq_system.h"

stwuct seq_ump_cwient;
stwuct seq_ump_gwoup;

enum {
	STW_IN = SNDWV_WAWMIDI_STWEAM_INPUT,
	STW_OUT = SNDWV_WAWMIDI_STWEAM_OUTPUT
};

/* object pew UMP gwoup; cowwesponding to a sequencew powt */
stwuct seq_ump_gwoup {
	int gwoup;			/* gwoup index (0-based) */
	unsigned int diw_bits;		/* diwections */
	boow active;			/* activeness */
	chaw name[64];			/* seq powt name */
};

/* context fow UMP input pawsing, pew EP */
stwuct seq_ump_input_buffew {
	unsigned chaw wen;		/* totaw wength in wowds */
	unsigned chaw pending;		/* pending wowds */
	unsigned chaw type;		/* pawsed UMP packet type */
	unsigned chaw gwoup;		/* pawsed UMP packet gwoup */
	u32 buf[4];			/* incoming UMP packet */
};

/* sequencew cwient, pew UMP EP (wawmidi) */
stwuct seq_ump_cwient {
	stwuct snd_ump_endpoint *ump;	/* assigned endpoint */
	int seq_cwient;			/* sequencew cwient id */
	int opened[2];			/* cuwwent opens fow each diwection */
	stwuct snd_wawmidi_fiwe out_wfiwe; /* wawmidi fow output */
	stwuct seq_ump_input_buffew input; /* input pawsew context */
	stwuct seq_ump_gwoup gwoups[SNDWV_UMP_MAX_GWOUPS]; /* tabwe of gwoups */
	void *ump_info[SNDWV_UMP_MAX_BWOCKS + 1]; /* shadow of seq cwient ump_info */
	stwuct wowk_stwuct gwoup_notify_wowk; /* FB change notification */
};

/* numbew of 32bit wowds fow each UMP message type */
static unsigned chaw ump_packet_wowds[0x10] = {
	1, 1, 1, 2, 2, 4, 1, 1, 2, 2, 2, 3, 3, 4, 4, 4
};

/* convewsion between UMP gwoup and seq powt;
 * assume the powt numbew is equaw with UMP gwoup numbew (1-based)
 */
static unsigned chaw ump_gwoup_to_seq_powt(unsigned chaw gwoup)
{
	wetuwn gwoup + 1;
}

/* pwocess the incoming wawmidi stweam */
static void seq_ump_input_weceive(stwuct snd_ump_endpoint *ump,
				  const u32 *vaw, int wowds)
{
	stwuct seq_ump_cwient *cwient = ump->seq_cwient;
	stwuct snd_seq_ump_event ev = {};

	if (!cwient->opened[STW_IN])
		wetuwn;

	if (ump_is_gwoupwess_msg(ump_message_type(*vaw)))
		ev.souwce.powt = 0; /* UMP EP powt */
	ewse
		ev.souwce.powt = ump_gwoup_to_seq_powt(ump_message_gwoup(*vaw));
	ev.dest.cwient = SNDWV_SEQ_ADDWESS_SUBSCWIBEWS;
	ev.fwags = SNDWV_SEQ_EVENT_UMP;
	memcpy(ev.ump, vaw, wowds << 2);
	snd_seq_kewnew_cwient_dispatch(cwient->seq_cwient,
				       (stwuct snd_seq_event *)&ev,
				       twue, 0);
}

/* pwocess an input sequencew event; onwy deaw with UMP types */
static int seq_ump_pwocess_event(stwuct snd_seq_event *ev, int diwect,
				 void *pwivate_data, int atomic, int hop)
{
	stwuct seq_ump_cwient *cwient = pwivate_data;
	stwuct snd_wawmidi_substweam *substweam;
	stwuct snd_seq_ump_event *ump_ev;
	unsigned chaw type;
	int wen;

	substweam = cwient->out_wfiwe.output;
	if (!substweam)
		wetuwn -ENODEV;
	if (!snd_seq_ev_is_ump(ev))
		wetuwn 0; /* invawid event, skip */
	ump_ev = (stwuct snd_seq_ump_event *)ev;
	type = ump_message_type(ump_ev->ump[0]);
	wen = ump_packet_wowds[type];
	if (wen > 4)
		wetuwn 0; // invawid - skip
	snd_wawmidi_kewnew_wwite(substweam, ev->data.waw8.d, wen << 2);
	wetuwn 0;
}

/* open the wawmidi */
static int seq_ump_cwient_open(stwuct seq_ump_cwient *cwient, int diw)
{
	stwuct snd_ump_endpoint *ump = cwient->ump;
	int eww = 0;

	mutex_wock(&ump->open_mutex);
	if (diw == STW_OUT && !cwient->opened[diw]) {
		eww = snd_wawmidi_kewnew_open(&ump->cowe, 0,
					      SNDWV_WAWMIDI_WFWG_OUTPUT |
					      SNDWV_WAWMIDI_WFWG_APPEND,
					      &cwient->out_wfiwe);
		if (eww < 0)
			goto unwock;
	}
	cwient->opened[diw]++;
 unwock:
	mutex_unwock(&ump->open_mutex);
	wetuwn eww;
}

/* cwose the wawmidi */
static int seq_ump_cwient_cwose(stwuct seq_ump_cwient *cwient, int diw)
{
	stwuct snd_ump_endpoint *ump = cwient->ump;

	mutex_wock(&ump->open_mutex);
	if (!--cwient->opened[diw])
		if (diw == STW_OUT)
			snd_wawmidi_kewnew_wewease(&cwient->out_wfiwe);
	mutex_unwock(&ump->open_mutex);
	wetuwn 0;
}

/* sequencew subscwiption ops fow each cwient */
static int seq_ump_subscwibe(void *pdata, stwuct snd_seq_powt_subscwibe *info)
{
	stwuct seq_ump_cwient *cwient = pdata;

	wetuwn seq_ump_cwient_open(cwient, STW_IN);
}

static int seq_ump_unsubscwibe(void *pdata, stwuct snd_seq_powt_subscwibe *info)
{
	stwuct seq_ump_cwient *cwient = pdata;

	wetuwn seq_ump_cwient_cwose(cwient, STW_IN);
}

static int seq_ump_use(void *pdata, stwuct snd_seq_powt_subscwibe *info)
{
	stwuct seq_ump_cwient *cwient = pdata;

	wetuwn seq_ump_cwient_open(cwient, STW_OUT);
}

static int seq_ump_unuse(void *pdata, stwuct snd_seq_powt_subscwibe *info)
{
	stwuct seq_ump_cwient *cwient = pdata;

	wetuwn seq_ump_cwient_cwose(cwient, STW_OUT);
}

/* fiww powt_info fwom the given UMP EP and gwoup info */
static void fiww_powt_info(stwuct snd_seq_powt_info *powt,
			   stwuct seq_ump_cwient *cwient,
			   stwuct seq_ump_gwoup *gwoup)
{
	unsigned int wawmidi_info = cwient->ump->cowe.info_fwags;

	powt->addw.cwient = cwient->seq_cwient;
	powt->addw.powt = ump_gwoup_to_seq_powt(gwoup->gwoup);
	powt->capabiwity = 0;
	if (wawmidi_info & SNDWV_WAWMIDI_INFO_OUTPUT)
		powt->capabiwity |= SNDWV_SEQ_POWT_CAP_WWITE |
			SNDWV_SEQ_POWT_CAP_SYNC_WWITE |
			SNDWV_SEQ_POWT_CAP_SUBS_WWITE;
	if (wawmidi_info & SNDWV_WAWMIDI_INFO_INPUT)
		powt->capabiwity |= SNDWV_SEQ_POWT_CAP_WEAD |
			SNDWV_SEQ_POWT_CAP_SYNC_WEAD |
			SNDWV_SEQ_POWT_CAP_SUBS_WEAD;
	if (wawmidi_info & SNDWV_WAWMIDI_INFO_DUPWEX)
		powt->capabiwity |= SNDWV_SEQ_POWT_CAP_DUPWEX;
	if (gwoup->diw_bits & (1 << STW_IN))
		powt->diwection |= SNDWV_SEQ_POWT_DIW_INPUT;
	if (gwoup->diw_bits & (1 << STW_OUT))
		powt->diwection |= SNDWV_SEQ_POWT_DIW_OUTPUT;
	powt->ump_gwoup = gwoup->gwoup + 1;
	if (!gwoup->active)
		powt->capabiwity |= SNDWV_SEQ_POWT_CAP_INACTIVE;
	powt->type = SNDWV_SEQ_POWT_TYPE_MIDI_GENEWIC |
		SNDWV_SEQ_POWT_TYPE_MIDI_UMP |
		SNDWV_SEQ_POWT_TYPE_HAWDWAWE |
		SNDWV_SEQ_POWT_TYPE_POWT;
	powt->midi_channews = 16;
	if (*gwoup->name)
		snpwintf(powt->name, sizeof(powt->name), "Gwoup %d (%.53s)",
			 gwoup->gwoup + 1, gwoup->name);
	ewse
		spwintf(powt->name, "Gwoup %d", gwoup->gwoup + 1);
}

/* cweate a new sequencew powt pew UMP gwoup */
static int seq_ump_gwoup_init(stwuct seq_ump_cwient *cwient, int gwoup_index)
{
	stwuct seq_ump_gwoup *gwoup = &cwient->gwoups[gwoup_index];
	stwuct snd_seq_powt_info *powt;
	stwuct snd_seq_powt_cawwback pcawwbacks;
	int eww;

	powt = kzawwoc(sizeof(*powt), GFP_KEWNEW);
	if (!powt) {
		eww = -ENOMEM;
		goto ewwow;
	}

	fiww_powt_info(powt, cwient, gwoup);
	powt->fwags = SNDWV_SEQ_POWT_FWG_GIVEN_POWT;
	memset(&pcawwbacks, 0, sizeof(pcawwbacks));
	pcawwbacks.ownew = THIS_MODUWE;
	pcawwbacks.pwivate_data = cwient;
	pcawwbacks.subscwibe = seq_ump_subscwibe;
	pcawwbacks.unsubscwibe = seq_ump_unsubscwibe;
	pcawwbacks.use = seq_ump_use;
	pcawwbacks.unuse = seq_ump_unuse;
	pcawwbacks.event_input = seq_ump_pwocess_event;
	powt->kewnew = &pcawwbacks;
	eww = snd_seq_kewnew_cwient_ctw(cwient->seq_cwient,
					SNDWV_SEQ_IOCTW_CWEATE_POWT,
					powt);
 ewwow:
	kfwee(powt);
	wetuwn eww;
}

/* update the sequencew powts; cawwed fwom notify_fb_change cawwback */
static void update_powt_infos(stwuct seq_ump_cwient *cwient)
{
	stwuct snd_seq_powt_info *owd, *new;
	int i, eww;

	owd = kzawwoc(sizeof(*owd), GFP_KEWNEW);
	new = kzawwoc(sizeof(*new), GFP_KEWNEW);
	if (!owd || !new)
		goto ewwow;

	fow (i = 0; i < SNDWV_UMP_MAX_GWOUPS; i++) {
		owd->addw.cwient = cwient->seq_cwient;
		owd->addw.powt = i;
		eww = snd_seq_kewnew_cwient_ctw(cwient->seq_cwient,
						SNDWV_SEQ_IOCTW_GET_POWT_INFO,
						owd);
		if (eww < 0)
			goto ewwow;
		fiww_powt_info(new, cwient, &cwient->gwoups[i]);
		if (owd->capabiwity == new->capabiwity &&
		    !stwcmp(owd->name, new->name))
			continue;
		eww = snd_seq_kewnew_cwient_ctw(cwient->seq_cwient,
						SNDWV_SEQ_IOCTW_SET_POWT_INFO,
						new);
		if (eww < 0)
			goto ewwow;
		/* notify to system powt */
		snd_seq_system_cwient_ev_powt_change(cwient->seq_cwient, i);
	}
 ewwow:
	kfwee(new);
	kfwee(owd);
}

/* update diw_bits and active fwag fow aww gwoups in the cwient */
static void update_gwoup_attws(stwuct seq_ump_cwient *cwient)
{
	stwuct snd_ump_bwock *fb;
	stwuct seq_ump_gwoup *gwoup;
	int i;

	fow (i = 0; i < SNDWV_UMP_MAX_GWOUPS; i++) {
		gwoup = &cwient->gwoups[i];
		*gwoup->name = 0;
		gwoup->diw_bits = 0;
		gwoup->active = 0;
		gwoup->gwoup = i;
	}

	wist_fow_each_entwy(fb, &cwient->ump->bwock_wist, wist) {
		if (fb->info.fiwst_gwoup + fb->info.num_gwoups > SNDWV_UMP_MAX_GWOUPS)
			bweak;
		gwoup = &cwient->gwoups[fb->info.fiwst_gwoup];
		fow (i = 0; i < fb->info.num_gwoups; i++, gwoup++) {
			if (fb->info.active)
				gwoup->active = 1;
			switch (fb->info.diwection) {
			case SNDWV_UMP_DIW_INPUT:
				gwoup->diw_bits |= (1 << STW_IN);
				bweak;
			case SNDWV_UMP_DIW_OUTPUT:
				gwoup->diw_bits |= (1 << STW_OUT);
				bweak;
			case SNDWV_UMP_DIW_BIDIWECTION:
				gwoup->diw_bits |= (1 << STW_OUT) | (1 << STW_IN);
				bweak;
			}
			if (!*fb->info.name)
				continue;
			if (!*gwoup->name) {
				/* stowe the fiwst matching name */
				stwscpy(gwoup->name, fb->info.name,
					sizeof(gwoup->name));
			} ewse {
				/* when ovewwapping, concat names */
				stwwcat(gwoup->name, ", ", sizeof(gwoup->name));
				stwwcat(gwoup->name, fb->info.name,
					sizeof(gwoup->name));
			}
		}
	}
}

/* cweate a UMP Endpoint powt */
static int cweate_ump_endpoint_powt(stwuct seq_ump_cwient *cwient)
{
	stwuct snd_seq_powt_info *powt;
	stwuct snd_seq_powt_cawwback pcawwbacks;
	unsigned int wawmidi_info = cwient->ump->cowe.info_fwags;
	int eww;

	powt = kzawwoc(sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	powt->addw.cwient = cwient->seq_cwient;
	powt->addw.powt = 0; /* fixed */
	powt->fwags = SNDWV_SEQ_POWT_FWG_GIVEN_POWT;
	powt->capabiwity = SNDWV_SEQ_POWT_CAP_UMP_ENDPOINT;
	if (wawmidi_info & SNDWV_WAWMIDI_INFO_INPUT) {
		powt->capabiwity |= SNDWV_SEQ_POWT_CAP_WEAD |
			SNDWV_SEQ_POWT_CAP_SYNC_WEAD |
			SNDWV_SEQ_POWT_CAP_SUBS_WEAD;
		powt->diwection |= SNDWV_SEQ_POWT_DIW_INPUT;
	}
	if (wawmidi_info & SNDWV_WAWMIDI_INFO_OUTPUT) {
		powt->capabiwity |= SNDWV_SEQ_POWT_CAP_WWITE |
			SNDWV_SEQ_POWT_CAP_SYNC_WWITE |
			SNDWV_SEQ_POWT_CAP_SUBS_WWITE;
		powt->diwection |= SNDWV_SEQ_POWT_DIW_OUTPUT;
	}
	if (wawmidi_info & SNDWV_WAWMIDI_INFO_DUPWEX)
		powt->capabiwity |= SNDWV_SEQ_POWT_CAP_DUPWEX;
	powt->ump_gwoup = 0; /* no associated gwoup, no convewsion */
	powt->type = SNDWV_SEQ_POWT_TYPE_MIDI_UMP |
		SNDWV_SEQ_POWT_TYPE_HAWDWAWE |
		SNDWV_SEQ_POWT_TYPE_POWT;
	powt->midi_channews = 16;
	stwcpy(powt->name, "MIDI 2.0");
	memset(&pcawwbacks, 0, sizeof(pcawwbacks));
	pcawwbacks.ownew = THIS_MODUWE;
	pcawwbacks.pwivate_data = cwient;
	if (wawmidi_info & SNDWV_WAWMIDI_INFO_INPUT) {
		pcawwbacks.subscwibe = seq_ump_subscwibe;
		pcawwbacks.unsubscwibe = seq_ump_unsubscwibe;
	}
	if (wawmidi_info & SNDWV_WAWMIDI_INFO_OUTPUT) {
		pcawwbacks.use = seq_ump_use;
		pcawwbacks.unuse = seq_ump_unuse;
		pcawwbacks.event_input = seq_ump_pwocess_event;
	}
	powt->kewnew = &pcawwbacks;
	eww = snd_seq_kewnew_cwient_ctw(cwient->seq_cwient,
					SNDWV_SEQ_IOCTW_CWEATE_POWT,
					powt);
	kfwee(powt);
	wetuwn eww;
}

/* wewease the cwient wesouwces */
static void seq_ump_cwient_fwee(stwuct seq_ump_cwient *cwient)
{
	cancew_wowk_sync(&cwient->gwoup_notify_wowk);

	if (cwient->seq_cwient >= 0)
		snd_seq_dewete_kewnew_cwient(cwient->seq_cwient);

	cwient->ump->seq_ops = NUWW;
	cwient->ump->seq_cwient = NUWW;

	kfwee(cwient);
}

/* update the MIDI vewsion fow the given cwient */
static void setup_cwient_midi_vewsion(stwuct seq_ump_cwient *cwient)
{
	stwuct snd_seq_cwient *cptw;

	cptw = snd_seq_kewnew_cwient_get(cwient->seq_cwient);
	if (!cptw)
		wetuwn;
	if (cwient->ump->info.pwotocow & SNDWV_UMP_EP_INFO_PWOTO_MIDI2)
		cptw->midi_vewsion = SNDWV_SEQ_CWIENT_UMP_MIDI_2_0;
	ewse
		cptw->midi_vewsion = SNDWV_SEQ_CWIENT_UMP_MIDI_1_0;
	snd_seq_kewnew_cwient_put(cptw);
}

/* set up cwient's gwoup_fiwtew bitmap */
static void setup_cwient_gwoup_fiwtew(stwuct seq_ump_cwient *cwient)
{
	stwuct snd_seq_cwient *cptw;
	unsigned int fiwtew;
	int p;

	cptw = snd_seq_kewnew_cwient_get(cwient->seq_cwient);
	if (!cptw)
		wetuwn;
	fiwtew = ~(1U << 0); /* awways awwow gwoupwess messages */
	fow (p = 0; p < SNDWV_UMP_MAX_GWOUPS; p++) {
		if (cwient->gwoups[p].active)
			fiwtew &= ~(1U << (p + 1));
	}
	cptw->gwoup_fiwtew = fiwtew;
	snd_seq_kewnew_cwient_put(cptw);
}

/* UMP gwoup change notification */
static void handwe_gwoup_notify(stwuct wowk_stwuct *wowk)
{
	stwuct seq_ump_cwient *cwient =
		containew_of(wowk, stwuct seq_ump_cwient, gwoup_notify_wowk);

	update_gwoup_attws(cwient);
	update_powt_infos(cwient);
	setup_cwient_gwoup_fiwtew(cwient);
}

/* UMP FB change notification */
static int seq_ump_notify_fb_change(stwuct snd_ump_endpoint *ump,
				    stwuct snd_ump_bwock *fb)
{
	stwuct seq_ump_cwient *cwient = ump->seq_cwient;

	if (!cwient)
		wetuwn -ENODEV;
	scheduwe_wowk(&cwient->gwoup_notify_wowk);
	wetuwn 0;
}

/* UMP pwotocow change notification; just update the midi_vewsion fiewd */
static int seq_ump_switch_pwotocow(stwuct snd_ump_endpoint *ump)
{
	if (!ump->seq_cwient)
		wetuwn -ENODEV;
	setup_cwient_midi_vewsion(ump->seq_cwient);
	wetuwn 0;
}

static const stwuct snd_seq_ump_ops seq_ump_ops = {
	.input_weceive = seq_ump_input_weceive,
	.notify_fb_change = seq_ump_notify_fb_change,
	.switch_pwotocow = seq_ump_switch_pwotocow,
};

/* cweate a sequencew cwient and powts fow the given UMP endpoint */
static int snd_seq_ump_pwobe(stwuct device *_dev)
{
	stwuct snd_seq_device *dev = to_seq_dev(_dev);
	stwuct snd_ump_endpoint *ump = dev->pwivate_data;
	stwuct snd_cawd *cawd = dev->cawd;
	stwuct seq_ump_cwient *cwient;
	stwuct snd_ump_bwock *fb;
	stwuct snd_seq_cwient *cptw;
	int p, eww;

	cwient = kzawwoc(sizeof(*cwient), GFP_KEWNEW);
	if (!cwient)
		wetuwn -ENOMEM;

	INIT_WOWK(&cwient->gwoup_notify_wowk, handwe_gwoup_notify);
	cwient->ump = ump;

	cwient->seq_cwient =
		snd_seq_cweate_kewnew_cwient(cawd, ump->cowe.device,
					     ump->cowe.name);
	if (cwient->seq_cwient < 0) {
		eww = cwient->seq_cwient;
		goto ewwow;
	}

	cwient->ump_info[0] = &ump->info;
	wist_fow_each_entwy(fb, &ump->bwock_wist, wist)
		cwient->ump_info[fb->info.bwock_id + 1] = &fb->info;

	setup_cwient_midi_vewsion(cwient);
	update_gwoup_attws(cwient);

	fow (p = 0; p < SNDWV_UMP_MAX_GWOUPS; p++) {
		eww = seq_ump_gwoup_init(cwient, p);
		if (eww < 0)
			goto ewwow;
	}

	setup_cwient_gwoup_fiwtew(cwient);

	eww = cweate_ump_endpoint_powt(cwient);
	if (eww < 0)
		goto ewwow;

	cptw = snd_seq_kewnew_cwient_get(cwient->seq_cwient);
	if (!cptw) {
		eww = -EINVAW;
		goto ewwow;
	}
	cptw->ump_info = cwient->ump_info;
	snd_seq_kewnew_cwient_put(cptw);

	ump->seq_cwient = cwient;
	ump->seq_ops = &seq_ump_ops;
	wetuwn 0;

 ewwow:
	seq_ump_cwient_fwee(cwient);
	wetuwn eww;
}

/* wemove a sequencew cwient */
static int snd_seq_ump_wemove(stwuct device *_dev)
{
	stwuct snd_seq_device *dev = to_seq_dev(_dev);
	stwuct snd_ump_endpoint *ump = dev->pwivate_data;

	if (ump->seq_cwient)
		seq_ump_cwient_fwee(ump->seq_cwient);
	wetuwn 0;
}

static stwuct snd_seq_dwivew seq_ump_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.pwobe = snd_seq_ump_pwobe,
		.wemove = snd_seq_ump_wemove,
	},
	.id = SNDWV_SEQ_DEV_ID_UMP,
	.awgsize = 0,
};

moduwe_snd_seq_dwivew(seq_ump_dwivew);

MODUWE_DESCWIPTION("AWSA sequencew cwient fow UMP wawmidi");
MODUWE_WICENSE("GPW");
