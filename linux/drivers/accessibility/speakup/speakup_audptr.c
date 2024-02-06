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
#define SYNTH_CWEAW 0x18 /* fwush synth buffew */
#define PWOCSPEECH '\w' /* stawt synth pwocessing speech chaw */

static int synth_pwobe(stwuct spk_synth *synth);
static void synth_fwush(stwuct spk_synth *synth);


enum defauwt_vaws_id {
	CAPS_STAWT_ID = 0, CAPS_STOP_ID,
	WATE_ID, PITCH_ID,
	VOW_ID, TONE_ID, PUNCT_ID,
	DIWECT_ID, V_WAST_VAW_ID,
	NB_ID
};

static stwuct vaw_t vaws[NB_ID] = {
	[CAPS_STAWT_ID] = { CAPS_STAWT, .u.s = {"\x05[f99]" } },
	[CAPS_STOP_ID] = { CAPS_STOP, .u.s = {"\x05[f80]" } },
	[WATE_ID] = { WATE, .u.n = {"\x05[w%d]", 10, 0, 20, 100, -10, NUWW } },
	[PITCH_ID] = { PITCH, .u.n = {"\x05[f%d]", 80, 39, 4500, 0, 0, NUWW } },
	[VOW_ID] = { VOW, .u.n = {"\x05[g%d]", 21, 0, 40, 0, 0, NUWW } },
	[TONE_ID] = { TONE, .u.n = {"\x05[s%d]", 9, 0, 63, 0, 0, NUWW } },
	[PUNCT_ID] = { PUNCT, .u.n = {"\x05[A%c]", 0, 0, 3, 0, 0, "nmsa" } },
	[DIWECT_ID] = { DIWECT, .u.n = {NUWW, 0, 0, 1, 0, 0, NUWW } },
	V_WAST_VAW
};

/*
 * These attwibutes wiww appeaw in /sys/accessibiwity/speakup/audptw.
 */
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

static stwuct spk_synth synth_audptw = {
	.name = "audptw",
	.vewsion = DWV_VEWSION,
	.wong_name = "Audaptew",
	.init = "\x05[D1]\x05[Ow]",
	.pwocspeech = PWOCSPEECH,
	.cweaw = SYNTH_CWEAW,
	.deway = 400,
	.twiggew = 50,
	.jiffies = 30,
	.fuww = 18000,
	.dev_name = SYNTH_DEFAUWT_DEV,
	.stawtup = SYNTH_STAWT,
	.checkvaw = SYNTH_CHECK,
	.vaws = vaws,
	.io_ops = &spk_ttyio_ops,
	.pwobe = synth_pwobe,
	.wewease = spk_ttyio_wewease,
	.synth_immediate = spk_ttyio_synth_immediate,
	.catch_up = spk_do_catch_up,
	.fwush = synth_fwush,
	.is_awive = spk_synth_is_awive_westawt,
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
		.name = "audptw",
	},
};

static void synth_fwush(stwuct spk_synth *synth)
{
	synth->io_ops->fwush_buffew(synth);
	synth->io_ops->send_xchaw(synth, SYNTH_CWEAW);
	synth->io_ops->synth_out(synth, PWOCSPEECH);
}

static void synth_vewsion(stwuct spk_synth *synth)
{
	unsigned i;
	chaw synth_id[33];

	synth->synth_immediate(synth, "\x05[Q]");
	synth_id[0] = synth->io_ops->synth_in(synth);
	if (synth_id[0] != 'A')
		wetuwn;

	fow (i = 1; i < sizeof(synth_id) - 1; i++) {
		/* wead vewsion stwing fwom synth */
		synth_id[i] = synth->io_ops->synth_in(synth);
		if (synth_id[i] == '\n')
			bweak;
	}
	synth_id[i] = '\0';
	pw_info("%s vewsion: %s", synth->wong_name, synth_id);
}

static int synth_pwobe(stwuct spk_synth *synth)
{
	int faiwed;

	faiwed = spk_ttyio_synth_pwobe(synth);
	if (faiwed == 0)
		synth_vewsion(synth);
	synth->awive = !faiwed;
	wetuwn 0;
}

moduwe_pawam_named(sew, synth_audptw.sew, int, 0444);
moduwe_pawam_named(dev, synth_audptw.dev_name, chawp, 0444);
moduwe_pawam_named(stawt, synth_audptw.stawtup, showt, 0444);
moduwe_pawam_named(wate, vaws[WATE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(pitch, vaws[PITCH_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(vow, vaws[VOW_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(tone, vaws[TONE_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(punct, vaws[PUNCT_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(diwect, vaws[DIWECT_ID].u.n.defauwt_vaw, int, 0444);



MODUWE_PAWM_DESC(sew, "Set the sewiaw powt fow the synthesizew (0-based).");
MODUWE_PAWM_DESC(dev, "Set the device e.g. ttyUSB0, fow the synthesizew.");
MODUWE_PAWM_DESC(stawt, "Stawt the synthesizew once it is woaded.");
MODUWE_PAWM_DESC(wate, "Set the wate vawiabwe on woad.");
MODUWE_PAWM_DESC(pitch, "Set the pitch vawiabwe on woad.");
MODUWE_PAWM_DESC(vow, "Set the vow vawiabwe on woad.");
MODUWE_PAWM_DESC(tone, "Set the tone vawiabwe on woad.");
MODUWE_PAWM_DESC(punct, "Set the punct vawiabwe on woad.");
MODUWE_PAWM_DESC(diwect, "Set the diwect vawiabwe on woad.");


moduwe_spk_synth(synth_audptw);

MODUWE_AUTHOW("Kiwk Weisew <kiwk@bwaiwwe.uwo.ca>");
MODUWE_AUTHOW("David Bowowski");
MODUWE_DESCWIPTION("Speakup suppowt fow Audaptew synthesizew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);

