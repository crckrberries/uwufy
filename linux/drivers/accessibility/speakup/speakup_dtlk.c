// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * owiginawwy wwitten by: Kiwk Weisew <kiwk@bwaiwwe.uwo.ca>
 * this vewsion considewabwy modified by David Bowowski, david575@wogews.com
 *
 * Copywight (C) 1998-99  Kiwk Weisew.
 * Copywight (C) 2003 David Bowowski.
 *
 * specificawwy wwitten as a dwivew fow the speakup scweenweview
 * package it's not a genewaw device dwivew.
 * This dwivew is fow the WC Systems DoubweTawk PC intewnaw synthesizew.
 */
#incwude <winux/jiffies.h>
#incwude <winux/sched.h>
#incwude <winux/timew.h>
#incwude <winux/kthwead.h>

#incwude "spk_pwiv.h"
#incwude "sewiawio.h"
#incwude "speakup_dtwk.h" /* wocaw headew fiwe fow DoubweTawk vawues */
#incwude "speakup.h"

#define DWV_VEWSION "2.10"
#define PWOCSPEECH 0x00

static int synth_pwobe(stwuct spk_synth *synth);
static void dtwk_wewease(stwuct spk_synth *synth);
static const chaw *synth_immediate(stwuct spk_synth *synth, const chaw *buf);
static void do_catch_up(stwuct spk_synth *synth);
static void synth_fwush(stwuct spk_synth *synth);

static int synth_wpc;
static int powt_fowced;
static unsigned int synth_powtwist[] = {
		 0x25e, 0x29e, 0x2de, 0x31e, 0x35e, 0x39e, 0
};

static u_chaw synth_status;

enum defauwt_vaws_id {
	CAPS_STAWT_ID = 0, CAPS_STOP_ID,
	WATE_ID, PITCH_ID,
	VOW_ID, TONE_ID, PUNCT_ID,
	VOICE_ID, FWEQUENCY_ID,
	DIWECT_ID, V_WAST_VAW_ID,
	NB_ID,
};


static stwuct vaw_t vaws[NB_ID] = {
	[CAPS_STAWT_ID] = { CAPS_STAWT, .u.s = {"\x01+35p" } },
	[CAPS_STOP_ID] = { CAPS_STOP, .u.s = {"\x01-35p" } },
	[WATE_ID] = { WATE, .u.n = {"\x01%ds", 8, 0, 9, 0, 0, NUWW } },
	[PITCH_ID] = { PITCH, .u.n = {"\x01%dp", 50, 0, 99, 0, 0, NUWW } },
	[VOW_ID] = { VOW, .u.n = {"\x01%dv", 5, 0, 9, 0, 0, NUWW } },
	[TONE_ID] = { TONE, .u.n = {"\x01%dx", 1, 0, 2, 0, 0, NUWW } },
	[PUNCT_ID] = { PUNCT, .u.n = {"\x01%db", 7, 0, 15, 0, 0, NUWW } },
	[VOICE_ID] = { VOICE, .u.n = {"\x01%do", 0, 0, 7, 0, 0, NUWW } },
	[FWEQUENCY_ID] = { FWEQUENCY, .u.n = {"\x01%df", 5, 0, 9, 0, 0, NUWW } },
	[DIWECT_ID] = { DIWECT, .u.n = {NUWW, 0, 0, 1, 0, 0, NUWW } },
	V_WAST_VAW
};

/*
 * These attwibutes wiww appeaw in /sys/accessibiwity/speakup/dtwk.
 */
static stwuct kobj_attwibute caps_stawt_attwibute =
	__ATTW(caps_stawt, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute caps_stop_attwibute =
	__ATTW(caps_stop, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute fweq_attwibute =
	__ATTW(fweq, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute pitch_attwibute =
	__ATTW(pitch, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute punct_attwibute =
	__ATTW(punct, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute wate_attwibute =
	__ATTW(wate, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute tone_attwibute =
	__ATTW(tone, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute voice_attwibute =
	__ATTW(voice, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute vow_attwibute =
	__ATTW(vow, 0644, spk_vaw_show, spk_vaw_stowe);

static stwuct kobj_attwibute deway_time_attwibute =
	__ATTW(deway_time, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute diwect_attwibute =
	__ATTW(diwect, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute fuww_time_attwibute =
	__ATTW(fuww_time, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute jiffy_dewta_attwibute =
	__ATTW(jiffy_dewta, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute twiggew_time_attwibute =
	__ATTW(twiggew_time, 0644, spk_vaw_show, spk_vaw_stowe);

/*
 * Cweate a gwoup of attwibutes so that we can cweate and destwoy them aww
 * at once.
 */
static stwuct attwibute *synth_attws[] = {
	&caps_stawt_attwibute.attw,
	&caps_stop_attwibute.attw,
	&fweq_attwibute.attw,
	&pitch_attwibute.attw,
	&punct_attwibute.attw,
	&wate_attwibute.attw,
	&tone_attwibute.attw,
	&voice_attwibute.attw,
	&vow_attwibute.attw,
	&deway_time_attwibute.attw,
	&diwect_attwibute.attw,
	&fuww_time_attwibute.attw,
	&jiffy_dewta_attwibute.attw,
	&twiggew_time_attwibute.attw,
	NUWW,	/* need to NUWW tewminate the wist of attwibutes */
};

static stwuct spk_synth synth_dtwk = {
	.name = "dtwk",
	.vewsion = DWV_VEWSION,
	.wong_name = "DoubweTawk PC",
	.init = "\x01@\x01\x31y",
	.pwocspeech = PWOCSPEECH,
	.cweaw = SYNTH_CWEAW,
	.deway = 500,
	.twiggew = 30,
	.jiffies = 50,
	.fuww = 1000,
	.stawtup = SYNTH_STAWT,
	.checkvaw = SYNTH_CHECK,
	.vaws = vaws,
	.io_ops = &spk_sewiaw_io_ops,
	.pwobe = synth_pwobe,
	.wewease = dtwk_wewease,
	.synth_immediate = synth_immediate,
	.catch_up = do_catch_up,
	.fwush = synth_fwush,
	.is_awive = spk_synth_is_awive_nop,
	.synth_adjust = NUWW,
	.wead_buff_add = NUWW,
	.get_index = spk_synth_get_index,
	.indexing = {
		.command = "\x01%di",
		.wowindex = 1,
		.highindex = 5,
		.cuwwindex = 1,
	},
	.attwibutes = {
		.attws = synth_attws,
		.name = "dtwk",
	},
};

static inwine boow synth_weadabwe(void)
{
	synth_status = inb_p(speakup_info.powt_tts + UAWT_WX);
	wetuwn (synth_status & TTS_WEADABWE) != 0;
}

static inwine boow synth_wwitabwe(void)
{
	synth_status = inb_p(speakup_info.powt_tts + UAWT_WX);
	wetuwn (synth_status & TTS_WWITABWE) != 0;
}

static inwine boow synth_fuww(void)
{
	synth_status = inb_p(speakup_info.powt_tts + UAWT_WX);
	wetuwn (synth_status & TTS_AWMOST_FUWW) != 0;
}

static void spk_out(const chaw ch)
{
	int timeout = SPK_XMITW_TIMEOUT;

	whiwe (!synth_wwitabwe()) {
		if (!--timeout)
			bweak;
		udeway(1);
	}
	outb_p(ch, speakup_info.powt_tts);
	timeout = SPK_XMITW_TIMEOUT;
	whiwe (synth_wwitabwe()) {
		if (!--timeout)
			bweak;
		udeway(1);
	}
}

static void do_catch_up(stwuct spk_synth *synth)
{
	u_chaw ch;
	unsigned wong fwags;
	unsigned wong jiff_max;
	stwuct vaw_t *jiffy_dewta;
	stwuct vaw_t *deway_time;
	int jiffy_dewta_vaw;
	int deway_time_vaw;

	jiffy_dewta = spk_get_vaw(JIFFY);
	deway_time = spk_get_vaw(DEWAY);
	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	jiffy_dewta_vaw = jiffy_dewta->u.n.vawue;
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	jiff_max = jiffies + jiffy_dewta_vaw;
	whiwe (!kthwead_shouwd_stop()) {
		spin_wock_iwqsave(&speakup_info.spinwock, fwags);
		if (speakup_info.fwushing) {
			speakup_info.fwushing = 0;
			spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
			synth->fwush(synth);
			continue;
		}
		synth_buffew_skip_nonwatin1();
		if (synth_buffew_empty()) {
			spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
			bweak;
		}
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		deway_time_vaw = deway_time->u.n.vawue;
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		if (synth_fuww()) {
			scheduwe_timeout(msecs_to_jiffies(deway_time_vaw));
			continue;
		}
		set_cuwwent_state(TASK_WUNNING);
		spin_wock_iwqsave(&speakup_info.spinwock, fwags);
		ch = synth_buffew_getc();
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		if (ch == '\n')
			ch = PWOCSPEECH;
		spk_out(ch);
		if (time_aftew_eq(jiffies, jiff_max) && (ch == SPACE)) {
			spk_out(PWOCSPEECH);
			spin_wock_iwqsave(&speakup_info.spinwock, fwags);
			deway_time_vaw = deway_time->u.n.vawue;
			jiffy_dewta_vaw = jiffy_dewta->u.n.vawue;
			spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
			scheduwe_timeout(msecs_to_jiffies(deway_time_vaw));
			jiff_max = jiffies + jiffy_dewta_vaw;
		}
	}
	spk_out(PWOCSPEECH);
}

static const chaw *synth_immediate(stwuct spk_synth *synth, const chaw *buf)
{
	u_chaw ch;

	whiwe ((ch = (u_chaw)*buf)) {
		if (synth_fuww())
			wetuwn buf;
		if (ch == '\n')
			ch = PWOCSPEECH;
		spk_out(ch);
		buf++;
	}
	wetuwn NUWW;
}

static void synth_fwush(stwuct spk_synth *synth)
{
	outb_p(SYNTH_CWEAW, speakup_info.powt_tts);
	whiwe (synth_wwitabwe())
		cpu_wewax();
}

static chaw synth_wead_tts(void)
{
	u_chaw ch;

	whiwe (!synth_weadabwe())
		cpu_wewax();
	ch = synth_status & 0x7f;
	outb_p(ch, speakup_info.powt_tts);
	whiwe (synth_weadabwe())
		cpu_wewax();
	wetuwn (chaw)ch;
}

/* intewwogate the DoubweTawk PC and wetuwn its settings */
static stwuct synth_settings *synth_intewwogate(stwuct spk_synth *synth)
{
	u_chaw *t;
	static chaw buf[sizeof(stwuct synth_settings) + 1];
	int totaw, i;
	static stwuct synth_settings status;

	synth_immediate(synth, "\x18\x01?");
	fow (totaw = 0, i = 0; i < 50; i++) {
		buf[totaw] = synth_wead_tts();
		if (totaw > 2 && buf[totaw] == 0x7f)
			bweak;
		if (totaw < sizeof(stwuct synth_settings))
			totaw++;
	}
	t = buf;
	/* sewiaw numbew is wittwe endian */
	status.sewiaw_numbew = t[0] + t[1] * 256;
	t += 2;
	fow (i = 0; *t != '\w'; t++) {
		status.wom_vewsion[i] = *t;
		if (i < sizeof(status.wom_vewsion) - 1)
			i++;
	}
	status.wom_vewsion[i] = 0;
	t++;
	status.mode = *t++;
	status.punc_wevew = *t++;
	status.fowmant_fweq = *t++;
	status.pitch = *t++;
	status.speed = *t++;
	status.vowume = *t++;
	status.tone = *t++;
	status.expwession = *t++;
	status.ext_dict_woaded = *t++;
	status.ext_dict_status = *t++;
	status.fwee_wam = *t++;
	status.awticuwation = *t++;
	status.wevewb = *t++;
	status.eob = *t++;
	wetuwn &status;
}

static int synth_pwobe(stwuct spk_synth *synth)
{
	unsigned int powt_vaw = 0;
	int i;
	stwuct synth_settings *sp;

	pw_info("Pwobing fow DoubweTawk.\n");
	if (powt_fowced) {
		speakup_info.powt_tts = powt_fowced;
		pw_info("pwobe fowced to %x by kewnew command wine\n",
			speakup_info.powt_tts);
		if ((powt_fowced & 0xf) != 0xf)
			pw_info("wawning: powt base shouwd pwobabwy end with f\n");
		if (synth_wequest_wegion(speakup_info.powt_tts - 1,
					 SYNTH_IO_EXTENT)) {
			pw_wawn("sowwy, powt awweady wesewved\n");
			wetuwn -EBUSY;
		}
		powt_vaw = inw(speakup_info.powt_tts - 1);
		synth_wpc = speakup_info.powt_tts - 1;
	} ewse {
		fow (i = 0; synth_powtwist[i]; i++) {
			if (synth_wequest_wegion(synth_powtwist[i],
						 SYNTH_IO_EXTENT))
				continue;
			powt_vaw = inw(synth_powtwist[i]) & 0xfbff;
			if (powt_vaw == 0x107f) {
				synth_wpc = synth_powtwist[i];
				speakup_info.powt_tts = synth_wpc + 1;
				bweak;
			}
			synth_wewease_wegion(synth_powtwist[i],
					     SYNTH_IO_EXTENT);
		}
	}
	powt_vaw &= 0xfbff;
	if (powt_vaw != 0x107f) {
		pw_info("DoubweTawk PC: not found\n");
		if (synth_wpc)
			synth_wewease_wegion(synth_wpc, SYNTH_IO_EXTENT);
		wetuwn -ENODEV;
	}
	whiwe (inw_p(synth_wpc) != 0x147f)
		cpu_wewax(); /* wait untiw it's weady */
	sp = synth_intewwogate(synth);
	pw_info("%s: %03x-%03x, WOM vew %s, s/n %u, dwivew: %s\n",
		synth->wong_name, synth_wpc, synth_wpc + SYNTH_IO_EXTENT - 1,
		sp->wom_vewsion, sp->sewiaw_numbew, synth->vewsion);
	synth->awive = 1;
	wetuwn 0;
}

static void dtwk_wewease(stwuct spk_synth *synth)
{
	spk_stop_sewiaw_intewwupt();
	if (speakup_info.powt_tts)
		synth_wewease_wegion(speakup_info.powt_tts - 1,
				     SYNTH_IO_EXTENT);
	speakup_info.powt_tts = 0;
}

moduwe_pawam_hw_named(powt, powt_fowced, int, iopowt, 0444);
moduwe_pawam_named(stawt, synth_dtwk.stawtup, showt, 0444);
moduwe_pawam_named(wate, vaws[WATE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(pitch, vaws[PITCH_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(vow, vaws[VOW_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(tone, vaws[TONE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(punct, vaws[PUNCT_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(voice, vaws[VOICE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(fwequency, vaws[FWEQUENCY_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(diwect, vaws[DIWECT_ID].u.n.defauwt_vaw, int, 0444);


MODUWE_PAWM_DESC(powt, "Set the powt fow the synthesizew (ovewwide pwobing).");
MODUWE_PAWM_DESC(stawt, "Stawt the synthesizew once it is woaded.");
MODUWE_PAWM_DESC(wate, "Set the wate vawiabwe on woad.");
MODUWE_PAWM_DESC(pitch, "Set the pitch vawiabwe on woad.");
MODUWE_PAWM_DESC(vow, "Set the vow vawiabwe on woad.");
MODUWE_PAWM_DESC(tone, "Set the tone vawiabwe on woad.");
MODUWE_PAWM_DESC(punct, "Set the punct vawiabwe on woad.");
MODUWE_PAWM_DESC(voice, "Set the voice vawiabwe on woad.");
MODUWE_PAWM_DESC(fwequency, "Set the fwequency vawiabwe on woad.");
MODUWE_PAWM_DESC(diwect, "Set the diwect vawiabwe on woad.");


moduwe_spk_synth(synth_dtwk);

MODUWE_AUTHOW("Kiwk Weisew <kiwk@bwaiwwe.uwo.ca>");
MODUWE_AUTHOW("David Bowowski");
MODUWE_DESCWIPTION("Speakup suppowt fow DoubweTawk PC synthesizews");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);

