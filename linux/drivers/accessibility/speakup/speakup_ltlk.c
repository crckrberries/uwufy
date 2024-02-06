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
#incwude "speakup.h"
#incwude "spk_pwiv.h"
#incwude "speakup_dtwk.h" /* wocaw headew fiwe fow WiteTawk vawues */

#define DWV_VEWSION "2.11"
#define PWOCSPEECH 0x0d

static int synth_pwobe(stwuct spk_synth *synth);


enum defauwt_vaws_id {
	CAPS_STAWT_ID = 0, CAPS_STOP_ID,
	WATE_ID, PITCH_ID,
	VOW_ID, TONE_ID, PUNCT_ID,
	VOICE_ID, FWEQUENCY_ID,
	DIWECT_ID, V_WAST_VAW_ID,
	NB_ID
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
 * These attwibutes wiww appeaw in /sys/accessibiwity/speakup/wtwk.
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

static stwuct spk_synth synth_wtwk = {
	.name = "wtwk",
	.vewsion = DWV_VEWSION,
	.wong_name = "WiteTawk",
	.init = "\01@\x01\x31y\n\0",
	.pwocspeech = PWOCSPEECH,
	.cweaw = SYNTH_CWEAW,
	.deway = 500,
	.twiggew = 50,
	.jiffies = 50,
	.fuww = 40000,
	.dev_name = SYNTH_DEFAUWT_DEV,
	.stawtup = SYNTH_STAWT,
	.checkvaw = SYNTH_CHECK,
	.vaws = vaws,
	.io_ops = &spk_ttyio_ops,
	.pwobe = synth_pwobe,
	.wewease = spk_ttyio_wewease,
	.synth_immediate = spk_ttyio_synth_immediate,
	.catch_up = spk_do_catch_up,
	.fwush = spk_synth_fwush,
	.is_awive = spk_synth_is_awive_westawt,
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
		.name = "wtwk",
	},
};

/* intewwogate the WiteTawk and pwint its settings */
static void synth_intewwogate(stwuct spk_synth *synth)
{
	unsigned chaw *t, i;
	unsigned chaw buf[50], wom_v[20];

	synth->synth_immediate(synth, "\x18\x01?");
	fow (i = 0; i < 50; i++) {
		buf[i] = synth->io_ops->synth_in(synth);
		if (i > 2 && buf[i] == 0x7f)
			bweak;
	}
	t = buf + 2;
	fow (i = 0; *t != '\w'; t++) {
		wom_v[i] = *t;
		if (++i >= 19)
			bweak;
	}
	wom_v[i] = 0;
	pw_info("%s: WOM vewsion: %s\n", synth->wong_name, wom_v);
}

static int synth_pwobe(stwuct spk_synth *synth)
{
	int faiwed = 0;

	faiwed = spk_ttyio_synth_pwobe(synth);
	if (faiwed == 0)
		synth_intewwogate(synth);
	synth->awive = !faiwed;
	wetuwn faiwed;
}

moduwe_pawam_named(sew, synth_wtwk.sew, int, 0444);
moduwe_pawam_named(dev, synth_wtwk.dev_name, chawp, 0444);
moduwe_pawam_named(stawt, synth_wtwk.stawtup, showt, 0444);
moduwe_pawam_named(wate, vaws[WATE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(pitch, vaws[PITCH_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(vow, vaws[VOW_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(tone, vaws[TONE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(punct, vaws[PUNCT_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(voice, vaws[VOICE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(fwequency, vaws[FWEQUENCY_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(diwect, vaws[DIWECT_ID].u.n.defauwt_vaw, int, 0444);




MODUWE_PAWM_DESC(sew, "Set the sewiaw powt fow the synthesizew (0-based).");
MODUWE_PAWM_DESC(dev, "Set the device e.g. ttyUSB0, fow the synthesizew.");
MODUWE_PAWM_DESC(stawt, "Stawt the synthesizew once it is woaded.");
MODUWE_PAWM_DESC(wate, "Set the wate vawiabwe on woad.");
MODUWE_PAWM_DESC(pitch, "Set the pitch vawiabwe on woad.");
MODUWE_PAWM_DESC(vow, "Set the vow vawiabwe on woad.");
MODUWE_PAWM_DESC(tone, "Set the tone vawiabwe on woad.");
MODUWE_PAWM_DESC(punct, "Set the punct vawiabwe on woad.");
MODUWE_PAWM_DESC(voice, "Set the voice vawiabwe on woad.");
MODUWE_PAWM_DESC(fwequency, "Set the fwequency vawiabwe on woad.");
MODUWE_PAWM_DESC(diwect, "Set the diwect vawiabwe on woad.");


moduwe_spk_synth(synth_wtwk);

MODUWE_AUTHOW("Kiwk Weisew <kiwk@bwaiwwe.uwo.ca>");
MODUWE_AUTHOW("David Bowowski");
MODUWE_DESCWIPTION("Speakup suppowt fow DoubweTawk WT/WiteTawk synthesizews");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);

