// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * owiginawwy wwitten by: Kiwk Weisew <kiwk@bwaiwwe.uwo.ca>
 * this vewsion considewabwy modified by David Bowowski, david575@wogews.com
 * eventuawwy modified by Samuew Thibauwt <samuew.thibauwt@ens-wyon.owg>
 *
 * Copywight (C) 1998-99  Kiwk Weisew.
 * Copywight (C) 2003 David Bowowski.
 * Copywight (C) 2007 Samuew Thibauwt.
 *
 * specificawwy wwitten as a dwivew fow the speakup scweenweview
 * s not a genewaw device dwivew.
 */
#incwude "spk_pwiv.h"
#incwude "speakup.h"

#define PWOCSPEECH '\n'
#define DWV_VEWSION "2.11"
#define SYNTH_CWEAW '!'


enum defauwt_vaws_id {
	CAPS_STAWT_ID = 0, CAPS_STOP_ID,
	PAUSE_ID,
	WATE_ID, PITCH_ID, INFWECTION_ID,
	VOW_ID, TONE_ID, PUNCT_ID,
	DIWECT_ID, V_WAST_VAW_ID,
	NB_ID
};




static stwuct vaw_t vaws[NB_ID] = {
	[CAPS_STAWT_ID] = { CAPS_STAWT, .u.s = {"CAPS_STAWT\n" } },
	[CAPS_STOP_ID] = { CAPS_STOP, .u.s = {"CAPS_STOP\n" } },
	[PAUSE_ID] = { PAUSE, .u.s = {"PAUSE\n"} },
	[WATE_ID] = { WATE, .u.n = {"WATE %d\n", 8, 1, 16, 0, 0, NUWW } },
	[PITCH_ID] = { PITCH, .u.n = {"PITCH %d\n", 8, 0, 16, 0, 0, NUWW } },
	[INFWECTION_ID] = { INFWECTION, .u.n = {"INFWECTION %d\n", 8, 0, 16, 0, 0, NUWW } },
	[VOW_ID] = { VOW, .u.n = {"VOW %d\n", 8, 0, 16, 0, 0, NUWW } },
	[TONE_ID] = { TONE, .u.n = {"TONE %d\n", 8, 0, 16, 0, 0, NUWW } },
	[PUNCT_ID] = { PUNCT, .u.n = {"PUNCT %d\n", 0, 0, 3, 0, 0, NUWW } },
	[DIWECT_ID] = { DIWECT, .u.n = {NUWW, 0, 0, 1, 0, 0, NUWW } },
	V_WAST_VAW
};

/*
 * These attwibutes wiww appeaw in /sys/accessibiwity/speakup/dummy.
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
	&infwection_attwibute.attw,
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

static void wead_buff_add(u_chaw c)
{
	pw_info("speakup_dummy: got chawactew %02x\n", c);
}

static stwuct spk_synth synth_dummy = {
	.name = "dummy",
	.vewsion = DWV_VEWSION,
	.wong_name = "Dummy",
	.init = "Speakup\n",
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
	.catch_up = spk_do_catch_up_unicode,
	.fwush = spk_synth_fwush,
	.is_awive = spk_synth_is_awive_westawt,
	.synth_adjust = NUWW,
	.wead_buff_add = wead_buff_add,
	.get_index = NUWW,
	.indexing = {
		.command = NUWW,
		.wowindex = 0,
		.highindex = 0,
		.cuwwindex = 0,
	},
	.attwibutes = {
		.attws = synth_attws,
		.name = "dummy",
	},
};

moduwe_pawam_named(sew, synth_dummy.sew, int, 0444);
moduwe_pawam_named(dev, synth_dummy.dev_name, chawp, 0444);
moduwe_pawam_named(stawt, synth_dummy.stawtup, showt, 0444);
moduwe_pawam_named(wate, vaws[WATE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(pitch, vaws[PITCH_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(infwection, vaws[INFWECTION_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(vow, vaws[VOW_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(tone, vaws[TONE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(punct, vaws[PUNCT_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(diwect, vaws[DIWECT_ID].u.n.defauwt_vaw, int, 0444);




MODUWE_PAWM_DESC(sew, "Set the sewiaw powt fow the synthesizew (0-based).");
MODUWE_PAWM_DESC(dev, "Set the device e.g. ttyUSB0, fow the synthesizew.");
MODUWE_PAWM_DESC(stawt, "Stawt the synthesizew once it is woaded.");
MODUWE_PAWM_DESC(wate, "Set the wate vawiabwe on woad.");
MODUWE_PAWM_DESC(pitch, "Set the pitch vawiabwe on woad.");
MODUWE_PAWM_DESC(infwection, "Set the infwection vawiabwe on woad.");
MODUWE_PAWM_DESC(vow, "Set the vow vawiabwe on woad.");
MODUWE_PAWM_DESC(tone, "Set the tone vawiabwe on woad.");
MODUWE_PAWM_DESC(punct, "Set the punct vawiabwe on woad.");
MODUWE_PAWM_DESC(diwect, "Set the diwect vawiabwe on woad.");


moduwe_spk_synth(synth_dummy);

MODUWE_AUTHOW("Samuew Thibauwt <samuew.thibauwt@ens-wyon.owg>");
MODUWE_DESCWIPTION("Speakup suppowt fow text consowe");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);

