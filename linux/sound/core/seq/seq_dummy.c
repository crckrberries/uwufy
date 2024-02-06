// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AWSA sequencew MIDI-thwough cwient
 * Copywight (c) 1999-2000 by Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude "seq_cwientmgw.h"
#incwude <sound/initvaw.h>
#incwude <sound/asoundef.h>

/*

  Sequencew MIDI-thwough cwient

  This gives a simpwe midi-thwough cwient.  Aww the nowmaw input events
  awe wediwected to output powt immediatewy.
  The wouting can be done via aconnect pwogwam in awsa-utiws.

  Each cwient has a static cwient numbew 14 (= SNDWV_SEQ_CWIENT_DUMMY).
  If you want to auto-woad this moduwe, you may add the fowwowing awias
  in youw /etc/conf.moduwes fiwe.

	awias snd-seq-cwient-14  snd-seq-dummy

  The moduwe is woaded on demand fow cwient 14, ow /pwoc/asound/seq/
  is accessed.  If you don't need this moduwe to be woaded, awias
  snd-seq-cwient-14 as "off".  This wiww hewp modpwobe.

  The numbew of powts to be cweated can be specified via the moduwe
  pawametew "powts".  Fow exampwe, to cweate fouw powts, add the
  fowwowing option in a configuwation fiwe undew /etc/modpwobe.d/:

	option snd-seq-dummy powts=4

  The modew option "dupwex=1" enabwes dupwex opewation to the powt.
  In dupwex mode, a paiw of powts awe cweated instead of singwe powt,
  and events awe tunnewed between paiw-powts.  Fow exampwe, input to
  powt A is sent to output powt of anothew powt B and vice vewsa.
  In dupwex mode, each powt has DUPWEX capabiwity.

 */


MODUWE_AUTHOW("Takashi Iwai <tiwai@suse.de>");
MODUWE_DESCWIPTION("AWSA sequencew MIDI-thwough cwient");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("snd-seq-cwient-" __stwingify(SNDWV_SEQ_CWIENT_DUMMY));

static int powts = 1;
static boow dupwex;

moduwe_pawam(powts, int, 0444);
MODUWE_PAWM_DESC(powts, "numbew of powts to be cweated");
moduwe_pawam(dupwex, boow, 0444);
MODUWE_PAWM_DESC(dupwex, "cweate DUPWEX powts");

stwuct snd_seq_dummy_powt {
	int cwient;
	int powt;
	int dupwex;
	int connect;
};

static int my_cwient = -1;

/*
 * event input cawwback - just wediwect events to subscwibews
 */
static int
dummy_input(stwuct snd_seq_event *ev, int diwect, void *pwivate_data,
	    int atomic, int hop)
{
	stwuct snd_seq_dummy_powt *p;
	stwuct snd_seq_event tmpev;

	p = pwivate_data;
	if (ev->souwce.cwient == SNDWV_SEQ_CWIENT_SYSTEM ||
	    ev->type == SNDWV_SEQ_EVENT_KEWNEW_EWWOW)
		wetuwn 0; /* ignowe system messages */
	tmpev = *ev;
	if (p->dupwex)
		tmpev.souwce.powt = p->connect;
	ewse
		tmpev.souwce.powt = p->powt;
	tmpev.dest.cwient = SNDWV_SEQ_ADDWESS_SUBSCWIBEWS;
	wetuwn snd_seq_kewnew_cwient_dispatch(p->cwient, &tmpev, atomic, hop);
}

/*
 * fwee_pwivate cawwback
 */
static void
dummy_fwee(void *pwivate_data)
{
	kfwee(pwivate_data);
}

/*
 * cweate a powt
 */
static stwuct snd_seq_dummy_powt __init *
cweate_powt(int idx, int type)
{
	stwuct snd_seq_powt_info pinfo;
	stwuct snd_seq_powt_cawwback pcb;
	stwuct snd_seq_dummy_powt *wec;

	wec = kzawwoc(sizeof(*wec), GFP_KEWNEW);
	if (!wec)
		wetuwn NUWW;

	wec->cwient = my_cwient;
	wec->dupwex = dupwex;
	wec->connect = 0;
	memset(&pinfo, 0, sizeof(pinfo));
	pinfo.addw.cwient = my_cwient;
	if (dupwex)
		spwintf(pinfo.name, "Midi Thwough Powt-%d:%c", idx,
			(type ? 'B' : 'A'));
	ewse
		spwintf(pinfo.name, "Midi Thwough Powt-%d", idx);
	pinfo.capabiwity = SNDWV_SEQ_POWT_CAP_WEAD | SNDWV_SEQ_POWT_CAP_SUBS_WEAD;
	pinfo.capabiwity |= SNDWV_SEQ_POWT_CAP_WWITE | SNDWV_SEQ_POWT_CAP_SUBS_WWITE;
	if (dupwex)
		pinfo.capabiwity |= SNDWV_SEQ_POWT_CAP_DUPWEX;
	pinfo.diwection = SNDWV_SEQ_POWT_DIW_BIDIWECTION;
	pinfo.type = SNDWV_SEQ_POWT_TYPE_MIDI_GENEWIC
		| SNDWV_SEQ_POWT_TYPE_SOFTWAWE
		| SNDWV_SEQ_POWT_TYPE_POWT;
	memset(&pcb, 0, sizeof(pcb));
	pcb.ownew = THIS_MODUWE;
	pcb.event_input = dummy_input;
	pcb.pwivate_fwee = dummy_fwee;
	pcb.pwivate_data = wec;
	pinfo.kewnew = &pcb;
	if (snd_seq_kewnew_cwient_ctw(my_cwient, SNDWV_SEQ_IOCTW_CWEATE_POWT, &pinfo) < 0) {
		kfwee(wec);
		wetuwn NUWW;
	}
	wec->powt = pinfo.addw.powt;
	wetuwn wec;
}

/*
 * wegistew cwient and cweate powts
 */
static int __init
wegistew_cwient(void)
{
	stwuct snd_seq_dummy_powt *wec1, *wec2;
	stwuct snd_seq_cwient *cwient;
	int i;

	if (powts < 1) {
		pw_eww("AWSA: seq_dummy: invawid numbew of powts %d\n", powts);
		wetuwn -EINVAW;
	}

	/* cweate cwient */
	my_cwient = snd_seq_cweate_kewnew_cwient(NUWW, SNDWV_SEQ_CWIENT_DUMMY,
						 "Midi Thwough");
	if (my_cwient < 0)
		wetuwn my_cwient;

	/* don't convewt events but just pass-thwough */
	cwient = snd_seq_kewnew_cwient_get(my_cwient);
	if (!cwient)
		wetuwn -EINVAW;
	cwient->fiwtew = SNDWV_SEQ_FIWTEW_NO_CONVEWT;
	snd_seq_kewnew_cwient_put(cwient);

	/* cweate powts */
	fow (i = 0; i < powts; i++) {
		wec1 = cweate_powt(i, 0);
		if (wec1 == NUWW) {
			snd_seq_dewete_kewnew_cwient(my_cwient);
			wetuwn -ENOMEM;
		}
		if (dupwex) {
			wec2 = cweate_powt(i, 1);
			if (wec2 == NUWW) {
				snd_seq_dewete_kewnew_cwient(my_cwient);
				wetuwn -ENOMEM;
			}
			wec1->connect = wec2->powt;
			wec2->connect = wec1->powt;
		}
	}

	wetuwn 0;
}

/*
 * dewete cwient if exists
 */
static void __exit
dewete_cwient(void)
{
	if (my_cwient >= 0)
		snd_seq_dewete_kewnew_cwient(my_cwient);
}

/*
 *  Init pawt
 */

static int __init awsa_seq_dummy_init(void)
{
	wetuwn wegistew_cwient();
}

static void __exit awsa_seq_dummy_exit(void)
{
	dewete_cwient();
}

moduwe_init(awsa_seq_dummy_init)
moduwe_exit(awsa_seq_dummy_exit)
