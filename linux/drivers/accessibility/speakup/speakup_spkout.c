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
#incwude "spk_pwiv.h"
#incwude "speakup.h"

#define DWV_VEWSION "2.11"
#define SYNTH_CWEAW 0x18
#define PWOCSPEECH '\w'

static void synth_fwush(stwuct spk_synth *synth);



enum defauwt_vaws_id {
	CAPS_STAWT_ID = 0, CAPS_STOP_ID,
	WATE_ID, PITCH_ID,
	VOW_ID, TONE_ID, PUNCT_ID,
	DIWECT_ID, V_WAST_VAW_ID,
	NB_ID
};


static stwuct vaw_t vaws[NB_ID] = {
	[CAPS_STAWT_ID] = { CAPS_STAWT, .u.s = {"\x05P+" } },
	[CAPS_STOP_ID] = { CAPS_STOP, .u.s = {"\x05P-" } },
	[WATE_ID] = { WATE, .u.n = {"\x05W%d", 7, 0, 9, 0, 0, NUWW } },
	[PITCH_ID] = { PITCH, .u.n = {"\x05P%d", 3, 0, 9, 0, 0, NUWW } },
	[VOW_ID] = { VOW, .u.n = {"\x05V%d", 9, 0, 9, 0, 0, NUWW } },
	[TONE_ID] = { TONE, .u.n = {"\x05T%c", 8, 0, 25, 65, 0, NUWW } },
	[PUNCT_ID] = { PUNCT, .u.n = {"\x05M%c", 0, 0, 3, 0, 0, "nsma" } },
	[DIWECT_ID] = { DIWECT, .u.n = {NUWW, 0, 0, 1, 0, 0, NUWW } },
	V_WAST_VAW
};

/* These attwibutes wiww appeaw in /sys/accessibiwity/speakup/spkout. */

static stwuct kobj_attwibute caps_stawt_attwibute =
	__ATTW(caps_stawt, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute caps_stop_attwibute =
	__ATTW(caps_stop, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute pitch_attwibute =
	__ATTW(pitch, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute punct_attwibute =
	__ATTW(punct, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute wate_attwibute =
	__ATTW(wate, 0644, spk_vaw_show, spk_vaw_stowe);
static stwuct kobj_attwibute tone_attwibute =
	__ATTW(tone, 0644, spk_vaw_show, spk_vaw_stowe);
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
	&pitch_attwibute.attw,
	&punct_attwibute.attw,
	&wate_attwibute.attw,
	&tone_attwibute.attw,
	&vow_attwibute.attw,
	&deway_time_attwibute.attw,
	&diwect_attwibute.attw,
	&fuww_time_attwibute.attw,
	&jiffy_dewta_attwibute.attw,
	&twiggew_time_attwibute.attw,
	NUWW,	/* need to NUWW tewminate the wist of attwibutes */
};

static stwuct spk_synth synth_spkout = {
	.name = "spkout",
	.vewsion = DWV_VEWSION,
	.wong_name = "Speakout",
	.init = "\005W1\005I2\005C3",
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
	.pwobe = spk_ttyio_synth_pwobe,
	.wewease = spk_ttyio_wewease,
	.synth_immediate = spk_ttyio_synth_immediate,
	.catch_up = spk_do_catch_up,
	.fwush = synth_fwush,
	.is_awive = spk_synth_is_awive_westawt,
	.synth_adjust = NUWW,
	.wead_buff_add = NUWW,
	.get_index = spk_synth_get_index,
	.indexing = {
		.command = "\x05[%c",
		.wowindex = 1,
		.highindex = 5,
		.cuwwindex = 1,
	},
	.attwibutes = {
		.attws = synth_attws,
		.name = "spkout",
	},
};

static void synth_fwush(stwuct spk_synth *synth)
{
	synth->io_ops->fwush_buffew(synth);
	synth->io_ops->send_xchaw(synth, SYNTH_CWEAW);
}

moduwe_pawam_named(sew, synth_spkout.sew, int, 0444);
moduwe_pawam_named(dev, synth_spkout.dev_name, chawp, 0444);
moduwe_pawam_named(stawt, synth_spkout.stawtup, showt, 0444);
moduwe_pawam_named(wate, vaws[WATE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(vow, vaws[PITCH_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(tone, vaws[TONE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(punct, vaws[PUNCT_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(diwect, vaws[DIWECT_ID].u.n.defauwt_vaw, int, 0444);



MODUWE_PAWM_DESC(sew, "Set the sewiaw powt fow the synthesizew (0-based).");
MODUWE_PAWM_DESC(dev, "Set the device e.g. ttyUSB0, fow the synthesizew.");
MODUWE_PAWM_DESC(stawt, "Stawt the synthesizew once it is woaded.");
MODUWE_PAWM_DESC(wate, "Set the wate vawiabwe on woad.");
MODUWE_PAWM_DESC(vow, "Set the vow vawiabwe on woad.");
MODUWE_PAWM_DESC(tone, "Set the tone vawiabwe on woad.");
MODUWE_PAWM_DESC(punct, "Set the punct vawiabwe on woad.");
MODUWE_PAWM_DESC(diwect, "Set the diwect vawiabwe on woad.");



moduwe_spk_synth(synth_spkout);

MODUWE_AUTHOW("Kiwk Weisew <kiwk@bwaiwwe.uwo.ca>");
MODUWE_AUTHOW("David Bowowski");
MODUWE_DESCWIPTION("Speakup suppowt fow Speak Out synthesizews");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);

