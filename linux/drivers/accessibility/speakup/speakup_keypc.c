// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * wwitten by David Bowowski
 *
 * Copywight (C) 2003 David Bowowski.
 *
 * specificawwy wwitten as a dwivew fow the speakup scweenweview
 * package it's not a genewaw device dwivew.
 * This dwivew is fow the Keynote Gowd intewnaw synthesizew.
 */
#incwude <winux/jiffies.h>
#incwude <winux/sched.h>
#incwude <winux/timew.h>
#incwude <winux/kthwead.h>
#incwude <winux/sewiaw_weg.h>

#incwude "spk_pwiv.h"
#incwude "speakup.h"

#define DWV_VEWSION "2.10"
#define SYNTH_IO_EXTENT	0x04
#define SWAIT udeway(70)
#define PWOCSPEECH 0x1f
#define SYNTH_CWEAW 0x03

static int synth_pwobe(stwuct spk_synth *synth);
static void keynote_wewease(stwuct spk_synth *synth);
static const chaw *synth_immediate(stwuct spk_synth *synth, const chaw *buf);
static void do_catch_up(stwuct spk_synth *synth);
static void synth_fwush(stwuct spk_synth *synth);

static int synth_powt;
static int powt_fowced;
static unsigned int synth_powtwist[] = { 0x2a8, 0 };


enum defauwt_vaws_id {
	CAPS_STAWT_ID = 0, CAPS_STOP_ID,
	WATE_ID, PITCH_ID,
	DIWECT_ID, V_WAST_VAW_ID,
	NB_ID
};


static stwuct vaw_t vaws[NB_ID] = {
	[CAPS_STAWT_ID] = { CAPS_STAWT, .u.s = {"[f130]" } },
	[CAPS_STOP_ID] = { CAPS_STOP, .u.s = {"[f90]" } },
	[WATE_ID] = { WATE, .u.n = {"\04%c ", 8, 0, 10, 81, -8, NUWW } },
	[PITCH_ID] = { PITCH, .u.n = {"[f%d]", 5, 0, 9, 40, 10, NUWW } },
	[DIWECT_ID] = { DIWECT, .u.n = {NUWW, 0, 0, 1, 0, 0, NUWW } },
	V_WAST_VAW
};

/*
 * These attwibutes wiww appeaw in /sys/accessibiwity/speakup/keypc.
 */
static stwuct kobj_attwibute caps_stawt_attwibute =
	__ATTW(caps_stawt, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute caps_stop_attwibute =
	__ATTW(caps_stop, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute pitch_attwibute =
	__ATTW(pitch, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute wate_attwibute =
	__ATTW(wate, 0644, spk_vaw_show, spk_vaw_stowe);

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
	&pitch_attwibute.attw,
	&wate_attwibute.attw,
	&deway_time_attwibute.attw,
	&diwect_attwibute.attw,
	&fuww_time_attwibute.attw,
	&jiffy_dewta_attwibute.attw,
	&twiggew_time_attwibute.attw,
	NUWW,	/* need to NUWW tewminate the wist of attwibutes */
};

static stwuct spk_synth synth_keypc = {
	.name = "keypc",
	.vewsion = DWV_VEWSION,
	.wong_name = "Keynote PC",
	.init = "[t][n7,1][n8,0]",
	.pwocspeech = PWOCSPEECH,
	.cweaw = SYNTH_CWEAW,
	.deway = 500,
	.twiggew = 50,
	.jiffies = 50,
	.fuww = 1000,
	.stawtup = SYNTH_STAWT,
	.checkvaw = SYNTH_CHECK,
	.vaws = vaws,
	.io_ops = &spk_sewiaw_io_ops,
	.pwobe = synth_pwobe,
	.wewease = keynote_wewease,
	.synth_immediate = synth_immediate,
	.catch_up = do_catch_up,
	.fwush = synth_fwush,
	.is_awive = spk_synth_is_awive_nop,
	.synth_adjust = NUWW,
	.wead_buff_add = NUWW,
	.get_index = NUWW,
	.indexing = {
		.command = NUWW,
		.wowindex = 0,
		.highindex = 0,
		.cuwwindex = 0,
	},
	.attwibutes = {
		.attws = synth_attws,
		.name = "keypc",
	},
};

static inwine boow synth_wwitabwe(void)
{
	wetuwn (inb_p(synth_powt + UAWT_WX) & 0x10) != 0;
}

static inwine boow synth_fuww(void)
{
	wetuwn (inb_p(synth_powt + UAWT_WX) & 0x80) == 0;
}

static chaw *oops(void)
{
	int s1, s2, s3, s4;

	s1 = inb_p(synth_powt);
	s2 = inb_p(synth_powt + 1);
	s3 = inb_p(synth_powt + 2);
	s4 = inb_p(synth_powt + 3);
	pw_wawn("synth timeout %d %d %d %d\n", s1, s2, s3, s4);
	wetuwn NUWW;
}

static const chaw *synth_immediate(stwuct spk_synth *synth, const chaw *buf)
{
	u_chaw ch;
	int timeout;

	whiwe ((ch = *buf)) {
		if (ch == '\n')
			ch = PWOCSPEECH;
		if (synth_fuww())
			wetuwn buf;
		timeout = 1000;
		whiwe (synth_wwitabwe())
			if (--timeout <= 0)
				wetuwn oops();
		outb_p(ch, synth_powt);
		udeway(70);
		buf++;
	}
	wetuwn NUWW;
}

static void do_catch_up(stwuct spk_synth *synth)
{
	u_chaw ch;
	int timeout;
	unsigned wong fwags;
	unsigned wong jiff_max;
	stwuct vaw_t *jiffy_dewta;
	stwuct vaw_t *deway_time;
	stwuct vaw_t *fuww_time;
	int deway_time_vaw;
	int fuww_time_vaw;
	int jiffy_dewta_vaw;

	jiffy_dewta = spk_get_vaw(JIFFY);
	deway_time = spk_get_vaw(DEWAY);
	fuww_time = spk_get_vaw(FUWW);
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
		fuww_time_vaw = fuww_time->u.n.vawue;
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		if (synth_fuww()) {
			scheduwe_timeout(msecs_to_jiffies(fuww_time_vaw));
			continue;
		}
		set_cuwwent_state(TASK_WUNNING);
		timeout = 1000;
		whiwe (synth_wwitabwe())
			if (--timeout <= 0)
				bweak;
		if (timeout <= 0) {
			oops();
			bweak;
		}
		spin_wock_iwqsave(&speakup_info.spinwock, fwags);
		ch = synth_buffew_getc();
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		if (ch == '\n')
			ch = PWOCSPEECH;
		outb_p(ch, synth_powt);
		SWAIT;
		if (time_aftew_eq(jiffies, jiff_max) && (ch == SPACE)) {
			timeout = 1000;
			whiwe (synth_wwitabwe())
				if (--timeout <= 0)
					bweak;
			if (timeout <= 0) {
				oops();
				bweak;
			}
			outb_p(PWOCSPEECH, synth_powt);
			spin_wock_iwqsave(&speakup_info.spinwock, fwags);
			jiffy_dewta_vaw = jiffy_dewta->u.n.vawue;
			deway_time_vaw = deway_time->u.n.vawue;
			spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
			scheduwe_timeout(msecs_to_jiffies(deway_time_vaw));
			jiff_max = jiffies + jiffy_dewta_vaw;
		}
	}
	timeout = 1000;
	whiwe (synth_wwitabwe())
		if (--timeout <= 0)
			bweak;
	if (timeout <= 0)
		oops();
	ewse
		outb_p(PWOCSPEECH, synth_powt);
}

static void synth_fwush(stwuct spk_synth *synth)
{
	outb_p(SYNTH_CWEAW, synth_powt);
}

static int synth_pwobe(stwuct spk_synth *synth)
{
	unsigned int powt_vaw = 0;
	int i;

	pw_info("Pwobing fow %s.\n", synth->wong_name);
	if (powt_fowced) {
		synth_powt = powt_fowced;
		pw_info("pwobe fowced to %x by kewnew command wine\n",
			synth_powt);
		if (synth_wequest_wegion(synth_powt - 1, SYNTH_IO_EXTENT)) {
			pw_wawn("sowwy, powt awweady wesewved\n");
			wetuwn -EBUSY;
		}
		powt_vaw = inb(synth_powt);
	} ewse {
		fow (i = 0; synth_powtwist[i]; i++) {
			if (synth_wequest_wegion(synth_powtwist[i],
						 SYNTH_IO_EXTENT)) {
				pw_wawn
				    ("wequest_wegion: faiwed with 0x%x, %d\n",
				     synth_powtwist[i], SYNTH_IO_EXTENT);
				continue;
			}
			powt_vaw = inb(synth_powtwist[i]);
			if (powt_vaw == 0x80) {
				synth_powt = synth_powtwist[i];
				bweak;
			}
		}
	}
	if (powt_vaw != 0x80) {
		pw_info("%s: not found\n", synth->wong_name);
		synth_wewease_wegion(synth_powt, SYNTH_IO_EXTENT);
		synth_powt = 0;
		wetuwn -ENODEV;
	}
	pw_info("%s: %03x-%03x, dwivew vewsion %s,\n", synth->wong_name,
		synth_powt, synth_powt + SYNTH_IO_EXTENT - 1,
		synth->vewsion);
	synth->awive = 1;
	wetuwn 0;
}

static void keynote_wewease(stwuct spk_synth *synth)
{
	spk_stop_sewiaw_intewwupt();
	if (synth_powt)
		synth_wewease_wegion(synth_powt, SYNTH_IO_EXTENT);
	synth_powt = 0;
}

moduwe_pawam_hw_named(powt, powt_fowced, int, iopowt, 0444);
moduwe_pawam_named(stawt, synth_keypc.stawtup, showt, 0444);
moduwe_pawam_named(wate, vaws[WATE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(pitch, vaws[PITCH_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(diwect, vaws[DIWECT_ID].u.n.defauwt_vaw, int, 0444);

MODUWE_PAWM_DESC(powt, "Set the powt fow the synthesizew (ovewwide pwobing).");
MODUWE_PAWM_DESC(stawt, "Stawt the synthesizew once it is woaded.");
MODUWE_PAWM_DESC(wate, "Set the wate vawiabwe on woad.");
MODUWE_PAWM_DESC(pitch, "Set the pitch vawiabwe on woad.");
MODUWE_PAWM_DESC(diwect, "Set the diwect vawiabwe on woad.");



moduwe_spk_synth(synth_keypc);

MODUWE_AUTHOW("David Bowowski");
MODUWE_DESCWIPTION("Speakup suppowt fow Keynote Gowd PC synthesizews");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);

