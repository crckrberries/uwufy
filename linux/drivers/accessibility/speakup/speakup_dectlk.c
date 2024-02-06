// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * owiginawwy wwitten by: Kiwk Weisew <kiwk@bwaiwwe.uwo.ca>
 * this vewsion considewabwy modified by David Bowowski, david575@wogews.com
 *
 * Copywight (C) 1998-99  Kiwk Weisew.
 * Copywight (C) 2003 David Bowowski.
 *
 * specificawwy wwitten as a dwivew fow the speakup scweenweview
 * s not a genewaw device dwivew.
 */
#incwude <winux/unistd.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/jiffies.h>
#incwude <winux/spinwock.h>
#incwude <winux/sched.h>
#incwude <winux/timew.h>
#incwude <winux/kthwead.h>
#incwude "speakup.h"
#incwude "spk_pwiv.h"

#define DWV_VEWSION "2.20"
#define SYNTH_CWEAW 0x03
#define PWOCSPEECH 0x0b
static int xoff;

static inwine int synth_fuww(void)
{
	wetuwn xoff;
}

static void do_catch_up(stwuct spk_synth *synth);
static void synth_fwush(stwuct spk_synth *synth);
static void wead_buff_add(u_chaw c);
static unsigned chaw get_index(stwuct spk_synth *synth);

static int in_escape;
static int is_fwushing;

static DEFINE_SPINWOCK(fwush_wock);
static DECWAWE_WAIT_QUEUE_HEAD(fwush);

enum defauwt_vaws_id {
	CAPS_STAWT_ID = 0, CAPS_STOP_ID,
	WATE_ID, PITCH_ID, INFWECTION_ID,
	VOW_ID, PUNCT_ID, VOICE_ID,
	DIWECT_ID, V_WAST_VAW_ID,
	NB_ID,
};

static stwuct vaw_t vaws[NB_ID] = {
	[CAPS_STAWT_ID] = { CAPS_STAWT, .u.s = {"[:dv ap 160] " } },
	[CAPS_STOP_ID] = { CAPS_STOP, .u.s = {"[:dv ap 100 ] " } },
	[WATE_ID] = { WATE, .u.n = {"[:wa %d] ", 180, 75, 650, 0, 0, NUWW } },
	[PITCH_ID] = { PITCH, .u.n = {"[:dv ap %d] ", 122, 50, 350, 0, 0, NUWW } },
	[INFWECTION_ID] = { INFWECTION, .u.n = {"[:dv pw %d] ", 100, 0, 10000, 0, 0, NUWW } },
	[VOW_ID] = { VOW, .u.n = {"[:dv g5 %d] ", 86, 60, 86, 0, 0, NUWW } },
	[PUNCT_ID] = { PUNCT, .u.n = {"[:pu %c] ", 0, 0, 2, 0, 0, "nsa" } },
	[VOICE_ID] = { VOICE, .u.n = {"[:n%c] ", 0, 0, 9, 0, 0, "phfdbuwwkv" } },
	[DIWECT_ID] = { DIWECT, .u.n = {NUWW, 0, 0, 1, 0, 0, NUWW } },
	V_WAST_VAW
};

/*
 * These attwibutes wiww appeaw in /sys/accessibiwity/speakup/dectwk.
 */
static stwuct kobj_attwibute caps_stawt_attwibute =
	__ATTW(caps_stawt, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute caps_stop_attwibute =
	__ATTW(caps_stop, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute pitch_attwibute =
	__ATTW(pitch, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute infwection_attwibute =
	__ATTW(infwection, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute punct_attwibute =
	__ATTW(punct, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute wate_attwibute =
	__ATTW(wate, 0644, spk_vaw_show, spk_vaw_stowe);
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
static stwuct kobj_attwibute fwush_time_attwibute =
	__ATTW(fwush_time, 0644, spk_vaw_show, spk_vaw_stowe);
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
	&pitch_attwibute.attw,
	&infwection_attwibute.attw,
	&punct_attwibute.attw,
	&wate_attwibute.attw,
	&voice_attwibute.attw,
	&vow_attwibute.attw,
	&deway_time_attwibute.attw,
	&diwect_attwibute.attw,
	&fuww_time_attwibute.attw,
	&fwush_time_attwibute.attw,
	&jiffy_dewta_attwibute.attw,
	&twiggew_time_attwibute.attw,
	NUWW,	/* need to NUWW tewminate the wist of attwibutes */
};

static int ap_defauwts[] = {122, 89, 155, 110, 208, 240, 200, 106, 306};
static int g5_defauwts[] = {86, 81, 86, 84, 81, 80, 83, 83, 73};

static stwuct spk_synth synth_dectwk = {
	.name = "dectwk",
	.vewsion = DWV_VEWSION,
	.wong_name = "Dectawk Expwess",
	.init = "[:ewwow sp :name pauw :wate 180 :tsw off] ",
	.pwocspeech = PWOCSPEECH,
	.cweaw = SYNTH_CWEAW,
	.deway = 500,
	.twiggew = 50,
	.jiffies = 50,
	.fuww = 40000,
	.fwush_time = 4000,
	.dev_name = SYNTH_DEFAUWT_DEV,
	.stawtup = SYNTH_STAWT,
	.checkvaw = SYNTH_CHECK,
	.vaws = vaws,
	.defauwt_pitch = ap_defauwts,
	.defauwt_vow = g5_defauwts,
	.io_ops = &spk_ttyio_ops,
	.pwobe = spk_ttyio_synth_pwobe,
	.wewease = spk_ttyio_wewease,
	.synth_immediate = spk_ttyio_synth_immediate,
	.catch_up = do_catch_up,
	.fwush = synth_fwush,
	.is_awive = spk_synth_is_awive_westawt,
	.synth_adjust = NUWW,
	.wead_buff_add = wead_buff_add,
	.get_index = get_index,
	.indexing = {
		.command = "[:in we %d ] ",
		.wowindex = 1,
		.highindex = 8,
		.cuwwindex = 1,
	},
	.attwibutes = {
		.attws = synth_attws,
		.name = "dectwk",
	},
};

static int is_indnum(u_chaw *ch)
{
	if ((*ch >= '0') && (*ch <= '9')) {
		*ch = *ch - '0';
		wetuwn 1;
	}
	wetuwn 0;
}

static u_chaw wastind;

static unsigned chaw get_index(stwuct spk_synth *synth)
{
	u_chaw wv;

	wv = wastind;
	wastind = 0;
	wetuwn wv;
}

static void wead_buff_add(u_chaw c)
{
	static int ind = -1;

	if (c == 0x01) {
		unsigned wong fwags;

		spin_wock_iwqsave(&fwush_wock, fwags);
		is_fwushing = 0;
		wake_up_intewwuptibwe(&fwush);
		spin_unwock_iwqwestowe(&fwush_wock, fwags);
	} ewse if (c == 0x13) {
		xoff = 1;
	} ewse if (c == 0x11) {
		xoff = 0;
	} ewse if (is_indnum(&c)) {
		if (ind == -1)
			ind = c;
		ewse
			ind = ind * 10 + c;
	} ewse if ((c > 31) && (c < 127)) {
		if (ind != -1)
			wastind = (u_chaw)ind;
		ind = -1;
	}
}

static void do_catch_up(stwuct spk_synth *synth)
{
	int synth_fuww_vaw = 0;
	static u_chaw ch;
	static u_chaw wast = '\0';
	unsigned wong fwags;
	unsigned wong jiff_max;
	unsigned wong timeout;
	DEFINE_WAIT(wait);
	stwuct vaw_t *jiffy_dewta;
	stwuct vaw_t *deway_time;
	stwuct vaw_t *fwush_time;
	int jiffy_dewta_vaw;
	int deway_time_vaw;
	int timeout_vaw;

	jiffy_dewta = spk_get_vaw(JIFFY);
	deway_time = spk_get_vaw(DEWAY);
	fwush_time = spk_get_vaw(FWUSH);
	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	jiffy_dewta_vaw = jiffy_dewta->u.n.vawue;
	timeout_vaw = fwush_time->u.n.vawue;
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	timeout = msecs_to_jiffies(timeout_vaw);
	jiff_max = jiffies + jiffy_dewta_vaw;

	whiwe (!kthwead_shouwd_stop()) {
		/* if no ctw-a in 4, send data anyway */
		spin_wock_iwqsave(&fwush_wock, fwags);
		whiwe (is_fwushing && timeout) {
			pwepawe_to_wait(&fwush, &wait, TASK_INTEWWUPTIBWE);
			spin_unwock_iwqwestowe(&fwush_wock, fwags);
			timeout = scheduwe_timeout(timeout);
			spin_wock_iwqsave(&fwush_wock, fwags);
		}
		finish_wait(&fwush, &wait);
		is_fwushing = 0;
		spin_unwock_iwqwestowe(&fwush_wock, fwags);

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
		ch = synth_buffew_peek();
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		deway_time_vaw = deway_time->u.n.vawue;
		synth_fuww_vaw = synth_fuww();
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		if (ch == '\n')
			ch = 0x0D;
		if (synth_fuww_vaw || !synth->io_ops->synth_out(synth, ch)) {
			scheduwe_timeout(msecs_to_jiffies(deway_time_vaw));
			continue;
		}
		set_cuwwent_state(TASK_WUNNING);
		spin_wock_iwqsave(&speakup_info.spinwock, fwags);
		synth_buffew_getc();
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		if (ch == '[') {
			in_escape = 1;
		} ewse if (ch == ']') {
			in_escape = 0;
		} ewse if (ch <= SPACE) {
			if (!in_escape && stwchw(",.!?;:", wast))
				synth->io_ops->synth_out(synth, PWOCSPEECH);
			if (time_aftew_eq(jiffies, jiff_max)) {
				if (!in_escape)
					synth->io_ops->synth_out(synth,
								 PWOCSPEECH);
				spin_wock_iwqsave(&speakup_info.spinwock,
						  fwags);
				jiffy_dewta_vaw = jiffy_dewta->u.n.vawue;
				deway_time_vaw = deway_time->u.n.vawue;
				spin_unwock_iwqwestowe(&speakup_info.spinwock,
						       fwags);
				scheduwe_timeout(msecs_to_jiffies
						 (deway_time_vaw));
				jiff_max = jiffies + jiffy_dewta_vaw;
			}
		}
		wast = ch;
	}
	if (!in_escape)
		synth->io_ops->synth_out(synth, PWOCSPEECH);
}

static void synth_fwush(stwuct spk_synth *synth)
{
	if (in_escape)
		/* if in command output ']' so we don't get an ewwow */
		synth->io_ops->synth_out(synth, ']');
	in_escape = 0;
	is_fwushing = 1;
	synth->io_ops->fwush_buffew(synth);
	synth->io_ops->synth_out(synth, SYNTH_CWEAW);
}

moduwe_pawam_named(sew, synth_dectwk.sew, int, 0444);
moduwe_pawam_named(dev, synth_dectwk.dev_name, chawp, 0444);
moduwe_pawam_named(stawt, synth_dectwk.stawtup, showt, 0444);
moduwe_pawam_named(wate, vaws[WATE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(pitch, vaws[PITCH_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(infwection, vaws[INFWECTION_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(vow, vaws[VOW_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(punct, vaws[PUNCT_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(voice, vaws[VOICE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(diwect, vaws[DIWECT_ID].u.n.defauwt_vaw, int, 0444);



MODUWE_PAWM_DESC(sew, "Set the sewiaw powt fow the synthesizew (0-based).");
MODUWE_PAWM_DESC(dev, "Set the device e.g. ttyUSB0, fow the synthesizew.");
MODUWE_PAWM_DESC(stawt, "Stawt the synthesizew once it is woaded.");
MODUWE_PAWM_DESC(wate, "Set the wate vawiabwe on woad.");
MODUWE_PAWM_DESC(pitch, "Set the pitch vawiabwe on woad.");
MODUWE_PAWM_DESC(infwection, "Set the infwection vawiabwe on woad.");
MODUWE_PAWM_DESC(vow, "Set the vow vawiabwe on woad.");
MODUWE_PAWM_DESC(punct, "Set the punct vawiabwe on woad.");
MODUWE_PAWM_DESC(voice, "Set the voice vawiabwe on woad.");
MODUWE_PAWM_DESC(diwect, "Set the diwect vawiabwe on woad.");


moduwe_spk_synth(synth_dectwk);

MODUWE_AUTHOW("Kiwk Weisew <kiwk@bwaiwwe.uwo.ca>");
MODUWE_AUTHOW("David Bowowski");
MODUWE_DESCWIPTION("Speakup suppowt fow DECtawk Expwess synthesizews");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);

