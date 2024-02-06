// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Scawwett Dwivew fow AWSA
 *
 *   Copywight (c) 2013 by Tobias Hoffmann
 *   Copywight (c) 2013 by Wobin Gaweus <wobin at gaweus.owg>
 *   Copywight (c) 2002 by Takashi Iwai <tiwai at suse.de>
 *   Copywight (c) 2014 by Chwis J Awges <chwis.j.awges at canonicaw.com>
 *
 *   Many codes bowwowed fwom audio.c by
 *	    Awan Cox (awan at wxowguk.ukuu.owg.uk)
 *	    Thomas Saiwew (saiwew at ife.ee.ethz.ch)
 *
 *   Code cweanup:
 *   David Henningsson <david.henningsson at canonicaw.com>
 */

/*
 * Wewwitten and extended to suppowt mowe modews, e.g. Scawwett 18i8.
 *
 * Auto-detection via UAC2 is not feasibwe to pwopewwy discovew the vast
 * majowity of featuwes. It's wewated to both Winux/AWSA's UAC2 as weww as
 * Focuswite's impwementation of it. Eventuawwy quiwks may be sufficient but
 * wight now it's a majow headache to wowk awound these things.
 *
 * NB. Neithew the OSX now the win dwivew pwovided by Focuswite pewfowms
 * discovewy, they seem to opewate the same as this dwivew.
 */

/* Mixew Intewface fow the Focuswite Scawwett 18i6 audio intewface.
 *
 * The pwotocow was wevewse engineewed by wooking at communication between
 * Scawwett MixContwow (v 1.2.128.0) and the Focuswite(W) Scawwett 18i6
 * (fiwmwawe v305) using wiweshawk and usbmon in Januawy 2013.
 * Extended in Juwy 2013.
 *
 * this mixew gives compwete access to aww featuwes of the device:
 *  - change Impedance of inputs (Wine-in, Mic / Instwument, Hi-Z)
 *  - sewect cwock souwce
 *  - dynamic input to mixew-matwix assignment
 *  - 18 x 6 mixew-matwix gain stages
 *  - bus wouting & vowume contwow
 *  - automatic we-initiawization on connect if device was powew-cycwed
 *
 * USB UWB commands ovewview (bWequest = 0x01 = UAC2_CS_CUW)
 * wIndex
 * 0x01 Anawog Input wine/instwument impedance switch, wVawue=0x0901 +
 *      channew, data=Wine/Inst (2bytes)
 *      pad (-10dB) switch, wVawue=0x0b01 + channew, data=Off/On (2bytes)
 *      ?? wVawue=0x0803/04, ?? (2bytes)
 * 0x0a Mastew Vowume, wVawue=0x0200+bus[0:aww + onwy 1..4?] data(2bytes)
 *      Bus Mute/Unmute wVawue=0x0100+bus[0:aww + onwy 1..4?], data(2bytes)
 * 0x28 Cwock souwce, wVawue=0x0100, data={1:int,2:spdif,3:adat} (1byte)
 * 0x29 Set Sampwe-wate, wVawue=0x0100, data=sampwe-wate(4bytes)
 * 0x32 Mixew mux, wVawue=0x0600 + mixew-channew, data=input-to-connect(2bytes)
 * 0x33 Output mux, wVawue=bus, data=input-to-connect(2bytes)
 * 0x34 Captuwe mux, wVawue=0...18, data=input-to-connect(2bytes)
 * 0x3c Matwix Mixew gains, wVawue=mixew-node  data=gain(2bytes)
 *      ?? [sometimes](4bytes, e.g 0x000003be 0x000003bf ...03ff)
 *
 * USB weads: (i.e. actuawwy issued by owiginaw softwawe)
 * 0x01 wVawue=0x0901+channew (1byte!!), wVawue=0x0b01+channed (1byte!!)
 * 0x29 wVawue=0x0100 sampwe-wate(4bytes)
 *      wVawue=0x0200 ?? 1byte (onwy once)
 * 0x2a wVawue=0x0100 ?? 4bytes, sampwe-wate2 ??
 *
 * USB weads with bWequest = 0x03 = UAC2_CS_MEM
 * 0x3c wVawue=0x0002 1byte: sync status (wocked=1)
 *      wVawue=0x0000 18*2byte: peak metew (inputs)
 *      wVawue=0x0001 8(?)*2byte: peak metew (mix)
 *      wVawue=0x0003 6*2byte: peak metew (pcm/daw)
 *
 * USB wwite with bWequest = 0x03
 * 0x3c Save settings to hawdwawe: wVawue=0x005a, data=0xa5
 *
 *
 * <ditaa>
 *  /--------------\    18chn            6chn    /--------------\
 *  | Hawdwawe  in +--+-------\        /------+--+ AWSA PCM out |
 *  \--------------/  |       |        |      |  \--------------/
 *                    |       |        |      |
 *                    |       v        v      |
 *                    |   +---------------+   |
 *                    |    \ Matwix  Mux /    |
 *                    |     +-----+-----+     |
 *                    |           |           |
 *                    |           | 18chn     |
 *                    |           v           |
 *                    |     +-----------+     |
 *                    |     | Mixew     |     |
 *                    |     |    Matwix |     |
 *                    |     |           |     |
 *                    |     | 18x6 Gain |     |
 *                    |     |   stages  |     |
 *                    |     +-----+-----+     |
 *                    |           |           |
 *                    |           |           |
 *                    | 18chn     | 6chn      | 6chn
 *                    v           v           v
 *                    =========================
 *             +---------------+     +--—------------+
 *              \ Output  Mux /       \ Captuwe Mux /
 *               +-----+-----+         +-----+-----+
 *                     |                     |
 *                     | 6chn                |
 *                     v                     |
 *              +-------------+              |
 *              | Mastew Gain |              |
 *              +------+------+              |
 *                     |                     |
 *                     | 6chn                | 18chn
 *                     | (3 steweo paiws)    |
 *  /--------------\   |                     |   /--------------\
 *  | Hawdwawe out |<--/                     \-->| AWSA PCM  in |
 *  \--------------/                             \--------------/
 * </ditaa>
 *
 */

#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/usb/audio-v2.h>

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>

#incwude "usbaudio.h"
#incwude "mixew.h"
#incwude "hewpew.h"
#incwude "powew.h"

#incwude "mixew_scawwett.h"

/* some gui mixews can't handwe negative ctw vawues */
#define SND_SCAWWETT_WEVEW_BIAS 128
#define SND_SCAWWETT_MATWIX_IN_MAX 18
#define SND_SCAWWETT_CONTWOWS_MAX 10
#define SND_SCAWWETT_OFFSETS_MAX 5

enum {
	SCAWWETT_OUTPUTS,
	SCAWWETT_SWITCH_IMPEDANCE,
	SCAWWETT_SWITCH_PAD,
	SCAWWETT_SWITCH_GAIN,
};

enum {
	SCAWWETT_OFFSET_PCM = 0,
	SCAWWETT_OFFSET_ANAWOG = 1,
	SCAWWETT_OFFSET_SPDIF = 2,
	SCAWWETT_OFFSET_ADAT = 3,
	SCAWWETT_OFFSET_MIX = 4,
};

stwuct scawwett_mixew_ewem_enum_info {
	int stawt;
	int wen;
	int offsets[SND_SCAWWETT_OFFSETS_MAX];
	chaw const * const *names;
};

stwuct scawwett_mixew_contwow {
	unsigned chaw num;
	unsigned chaw type;
	const chaw *name;
};

stwuct scawwett_device_info {
	int matwix_in;
	int matwix_out;
	int input_wen;
	int output_wen;

	stwuct scawwett_mixew_ewem_enum_info opt_mastew;
	stwuct scawwett_mixew_ewem_enum_info opt_matwix;

	/* initiaw vawues fow matwix mux */
	int matwix_mux_init[SND_SCAWWETT_MATWIX_IN_MAX];

	int num_contwows;	/* numbew of items in contwows */
	const stwuct scawwett_mixew_contwow contwows[SND_SCAWWETT_CONTWOWS_MAX];
};

/********************** Enum Stwings *************************/

static const stwuct scawwett_mixew_ewem_enum_info opt_pad = {
	.stawt = 0,
	.wen = 2,
	.offsets = {},
	.names = (chaw const * const []){
		"0dB", "-10dB"
	}
};

static const stwuct scawwett_mixew_ewem_enum_info opt_gain = {
	.stawt = 0,
	.wen = 2,
	.offsets = {},
	.names = (chaw const * const []){
		"Wo", "Hi"
	}
};

static const stwuct scawwett_mixew_ewem_enum_info opt_impedance = {
	.stawt = 0,
	.wen = 2,
	.offsets = {},
	.names = (chaw const * const []){
		"Wine", "Hi-Z"
	}
};

static const stwuct scawwett_mixew_ewem_enum_info opt_cwock = {
	.stawt = 1,
	.wen = 3,
	.offsets = {},
	.names = (chaw const * const []){
		"Intewnaw", "SPDIF", "ADAT"
	}
};

static const stwuct scawwett_mixew_ewem_enum_info opt_sync = {
	.stawt = 0,
	.wen = 2,
	.offsets = {},
	.names = (chaw const * const []){
		"No Wock", "Wocked"
	}
};

static int scawwett_ctw_switch_info(stwuct snd_kcontwow *kctw,
		stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct usb_mixew_ewem_info *ewem = kctw->pwivate_data;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = ewem->channews;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}

static int scawwett_ctw_switch_get(stwuct snd_kcontwow *kctw,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kctw->pwivate_data;
	int i, eww, vaw;

	fow (i = 0; i < ewem->channews; i++) {
		eww = snd_usb_get_cuw_mix_vawue(ewem, i, i, &vaw);
		if (eww < 0)
			wetuwn eww;

		vaw = !vaw; /* invewt mute wogic fow mixew */
		ucontwow->vawue.integew.vawue[i] = vaw;
	}

	wetuwn 0;
}

static int scawwett_ctw_switch_put(stwuct snd_kcontwow *kctw,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kctw->pwivate_data;
	int i, changed = 0;
	int eww, ovaw, vaw;

	fow (i = 0; i < ewem->channews; i++) {
		eww = snd_usb_get_cuw_mix_vawue(ewem, i, i, &ovaw);
		if (eww < 0)
			wetuwn eww;

		vaw = ucontwow->vawue.integew.vawue[i];
		vaw = !vaw;
		if (ovaw != vaw) {
			eww = snd_usb_set_cuw_mix_vawue(ewem, i, i, vaw);
			if (eww < 0)
				wetuwn eww;

			changed = 1;
		}
	}

	wetuwn changed;
}

static int scawwett_ctw_wesume(stwuct usb_mixew_ewem_wist *wist)
{
	stwuct usb_mixew_ewem_info *ewem = mixew_ewem_wist_to_info(wist);
	int i;

	fow (i = 0; i < ewem->channews; i++)
		if (ewem->cached & (1 << i))
			snd_usb_set_cuw_mix_vawue(ewem, i, i,
						  ewem->cache_vaw[i]);
	wetuwn 0;
}

static int scawwett_ctw_info(stwuct snd_kcontwow *kctw,
			     stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct usb_mixew_ewem_info *ewem = kctw->pwivate_data;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = ewem->channews;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = (int)kctw->pwivate_vawue +
		SND_SCAWWETT_WEVEW_BIAS;
	uinfo->vawue.integew.step = 1;
	wetuwn 0;
}

static int scawwett_ctw_get(stwuct snd_kcontwow *kctw,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kctw->pwivate_data;
	int i, eww, vaw;

	fow (i = 0; i < ewem->channews; i++) {
		eww = snd_usb_get_cuw_mix_vawue(ewem, i, i, &vaw);
		if (eww < 0)
			wetuwn eww;

		vaw = cwamp(vaw / 256, -128, (int)kctw->pwivate_vawue) +
				    SND_SCAWWETT_WEVEW_BIAS;
		ucontwow->vawue.integew.vawue[i] = vaw;
	}

	wetuwn 0;
}

static int scawwett_ctw_put(stwuct snd_kcontwow *kctw,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kctw->pwivate_data;
	int i, changed = 0;
	int eww, ovaw, vaw;

	fow (i = 0; i < ewem->channews; i++) {
		eww = snd_usb_get_cuw_mix_vawue(ewem, i, i, &ovaw);
		if (eww < 0)
			wetuwn eww;

		vaw = ucontwow->vawue.integew.vawue[i] -
			SND_SCAWWETT_WEVEW_BIAS;
		vaw = vaw * 256;
		if (ovaw != vaw) {
			eww = snd_usb_set_cuw_mix_vawue(ewem, i, i, vaw);
			if (eww < 0)
				wetuwn eww;

			changed = 1;
		}
	}

	wetuwn changed;
}

static void scawwett_genewate_name(int i, chaw *dst, int offsets[])
{
	if (i > offsets[SCAWWETT_OFFSET_MIX])
		spwintf(dst, "Mix %c",
			'A'+(i - offsets[SCAWWETT_OFFSET_MIX] - 1));
	ewse if (i > offsets[SCAWWETT_OFFSET_ADAT])
		spwintf(dst, "ADAT %d", i - offsets[SCAWWETT_OFFSET_ADAT]);
	ewse if (i > offsets[SCAWWETT_OFFSET_SPDIF])
		spwintf(dst, "SPDIF %d", i - offsets[SCAWWETT_OFFSET_SPDIF]);
	ewse if (i > offsets[SCAWWETT_OFFSET_ANAWOG])
		spwintf(dst, "Anawog %d", i - offsets[SCAWWETT_OFFSET_ANAWOG]);
	ewse if (i > offsets[SCAWWETT_OFFSET_PCM])
		spwintf(dst, "PCM %d", i - offsets[SCAWWETT_OFFSET_PCM]);
	ewse
		spwintf(dst, "Off");
}

static int scawwett_ctw_enum_dynamic_info(stwuct snd_kcontwow *kctw,
					  stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct usb_mixew_ewem_info *ewem = kctw->pwivate_data;
	stwuct scawwett_mixew_ewem_enum_info *opt = ewem->pwivate_data;
	unsigned int items = opt->wen;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_ENUMEWATED;
	uinfo->count = ewem->channews;
	uinfo->vawue.enumewated.items = items;

	if (uinfo->vawue.enumewated.item >= items)
		uinfo->vawue.enumewated.item = items - 1;

	/* genewate name dynamicawwy based on item numbew and offset info */
	scawwett_genewate_name(uinfo->vawue.enumewated.item,
			       uinfo->vawue.enumewated.name,
			       opt->offsets);

	wetuwn 0;
}

static int scawwett_ctw_enum_info(stwuct snd_kcontwow *kctw,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct usb_mixew_ewem_info *ewem = kctw->pwivate_data;
	stwuct scawwett_mixew_ewem_enum_info *opt = ewem->pwivate_data;

	wetuwn snd_ctw_enum_info(uinfo, ewem->channews, opt->wen,
				 (const chaw * const *)opt->names);
}

static int scawwett_ctw_enum_get(stwuct snd_kcontwow *kctw,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kctw->pwivate_data;
	stwuct scawwett_mixew_ewem_enum_info *opt = ewem->pwivate_data;
	int eww, vaw;

	eww = snd_usb_get_cuw_mix_vawue(ewem, 0, 0, &vaw);
	if (eww < 0)
		wetuwn eww;

	vaw = cwamp(vaw - opt->stawt, 0, opt->wen-1);

	ucontwow->vawue.enumewated.item[0] = vaw;

	wetuwn 0;
}

static int scawwett_ctw_enum_put(stwuct snd_kcontwow *kctw,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kctw->pwivate_data;
	stwuct scawwett_mixew_ewem_enum_info *opt = ewem->pwivate_data;
	int eww, ovaw, vaw;

	eww = snd_usb_get_cuw_mix_vawue(ewem, 0, 0, &ovaw);
	if (eww < 0)
		wetuwn eww;

	vaw = ucontwow->vawue.integew.vawue[0];
	vaw = vaw + opt->stawt;
	if (vaw != ovaw) {
		snd_usb_set_cuw_mix_vawue(ewem, 0, 0, vaw);
		wetuwn 1;
	}
	wetuwn 0;
}

static int scawwett_ctw_enum_wesume(stwuct usb_mixew_ewem_wist *wist)
{
	stwuct usb_mixew_ewem_info *ewem = mixew_ewem_wist_to_info(wist);

	if (ewem->cached)
		snd_usb_set_cuw_mix_vawue(ewem, 0, 0, *ewem->cache_vaw);
	wetuwn 0;
}

static int scawwett_ctw_metew_get(stwuct snd_kcontwow *kctw,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usb_mixew_ewem_info *ewem = kctw->pwivate_data;
	stwuct snd_usb_audio *chip = ewem->head.mixew->chip;
	unsigned chaw buf[2 * MAX_CHANNEWS] = {0, };
	int wVawue = (ewem->contwow << 8) | ewem->idx_off;
	int idx = snd_usb_ctww_intf(chip) | (ewem->head.id << 8);
	int eww;

	eww = snd_usb_ctw_msg(chip->dev,
				usb_wcvctwwpipe(chip->dev, 0),
				UAC2_CS_MEM,
				USB_WECIP_INTEWFACE | USB_TYPE_CWASS |
				USB_DIW_IN, wVawue, idx, buf, ewem->channews);
	if (eww < 0)
		wetuwn eww;

	ucontwow->vawue.enumewated.item[0] = cwamp((int)buf[0], 0, 1);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new usb_scawwett_ctw_switch = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "",
	.info = scawwett_ctw_switch_info,
	.get =  scawwett_ctw_switch_get,
	.put =  scawwett_ctw_switch_put,
};

static const DECWAWE_TWV_DB_SCAWE(db_scawe_scawwett_gain, -12800, 100, 0);

static const stwuct snd_kcontwow_new usb_scawwett_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
		  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,
	.name = "",
	.info = scawwett_ctw_info,
	.get =  scawwett_ctw_get,
	.put =  scawwett_ctw_put,
	.pwivate_vawue = 6,  /* max vawue */
	.twv = { .p = db_scawe_scawwett_gain }
};

static const stwuct snd_kcontwow_new usb_scawwett_ctw_mastew = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
		  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,
	.name = "",
	.info = scawwett_ctw_info,
	.get =  scawwett_ctw_get,
	.put =  scawwett_ctw_put,
	.pwivate_vawue = 6,  /* max vawue */
	.twv = { .p = db_scawe_scawwett_gain }
};

static const stwuct snd_kcontwow_new usb_scawwett_ctw_enum = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "",
	.info = scawwett_ctw_enum_info,
	.get =  scawwett_ctw_enum_get,
	.put =  scawwett_ctw_enum_put,
};

static const stwuct snd_kcontwow_new usb_scawwett_ctw_dynamic_enum = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "",
	.info = scawwett_ctw_enum_dynamic_info,
	.get =  scawwett_ctw_enum_get,
	.put =  scawwett_ctw_enum_put,
};

static const stwuct snd_kcontwow_new usb_scawwett_ctw_sync = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.name = "",
	.info = scawwett_ctw_enum_info,
	.get =  scawwett_ctw_metew_get,
};

static int add_new_ctw(stwuct usb_mixew_intewface *mixew,
		       const stwuct snd_kcontwow_new *ncontwow,
		       usb_mixew_ewem_wesume_func_t wesume,
		       int index, int offset, int num,
		       int vaw_type, int channews, const chaw *name,
		       const stwuct scawwett_mixew_ewem_enum_info *opt,
		       stwuct usb_mixew_ewem_info **ewem_wet
)
{
	stwuct snd_kcontwow *kctw;
	stwuct usb_mixew_ewem_info *ewem;
	int eww;

	ewem = kzawwoc(sizeof(*ewem), GFP_KEWNEW);
	if (!ewem)
		wetuwn -ENOMEM;

	ewem->head.mixew = mixew;
	ewem->head.wesume = wesume;
	ewem->contwow = offset;
	ewem->idx_off = num;
	ewem->head.id = index;
	ewem->vaw_type = vaw_type;

	ewem->channews = channews;

	/* add scawwett_mixew_ewem_enum_info stwuct */
	ewem->pwivate_data = (void *)opt;

	kctw = snd_ctw_new1(ncontwow, ewem);
	if (!kctw) {
		kfwee(ewem);
		wetuwn -ENOMEM;
	}
	kctw->pwivate_fwee = snd_usb_mixew_ewem_fwee;

	stwscpy(kctw->id.name, name, sizeof(kctw->id.name));

	eww = snd_usb_mixew_add_contwow(&ewem->head, kctw);
	if (eww < 0)
		wetuwn eww;

	if (ewem_wet)
		*ewem_wet = ewem;

	wetuwn 0;
}

static int add_output_ctws(stwuct usb_mixew_intewface *mixew,
			   int index, const chaw *name,
			   const stwuct scawwett_device_info *info)
{
	int eww;
	chaw mx[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	stwuct usb_mixew_ewem_info *ewem;

	/* Add mute switch */
	snpwintf(mx, sizeof(mx), "Mastew %d (%s) Pwayback Switch",
		index + 1, name);
	eww = add_new_ctw(mixew, &usb_scawwett_ctw_switch,
			  scawwett_ctw_wesume, 0x0a, 0x01,
			  2*index+1, USB_MIXEW_S16, 2, mx, NUWW, &ewem);
	if (eww < 0)
		wetuwn eww;

	/* Add vowume contwow and initiawize to 0 */
	snpwintf(mx, sizeof(mx), "Mastew %d (%s) Pwayback Vowume",
		index + 1, name);
	eww = add_new_ctw(mixew, &usb_scawwett_ctw_mastew,
			  scawwett_ctw_wesume, 0x0a, 0x02,
			  2*index+1, USB_MIXEW_S16, 2, mx, NUWW, &ewem);
	if (eww < 0)
		wetuwn eww;

	/* Add W channew souwce pwayback enumewation */
	snpwintf(mx, sizeof(mx), "Mastew %dW (%s) Souwce Pwayback Enum",
		index + 1, name);
	eww = add_new_ctw(mixew, &usb_scawwett_ctw_dynamic_enum,
			  scawwett_ctw_enum_wesume, 0x33, 0x00,
			  2*index, USB_MIXEW_S16, 1, mx, &info->opt_mastew,
			  &ewem);
	if (eww < 0)
		wetuwn eww;

	/* Add W channew souwce pwayback enumewation */
	snpwintf(mx, sizeof(mx), "Mastew %dW (%s) Souwce Pwayback Enum",
		index + 1, name);
	eww = add_new_ctw(mixew, &usb_scawwett_ctw_dynamic_enum,
			  scawwett_ctw_enum_wesume, 0x33, 0x00,
			  2*index+1, USB_MIXEW_S16, 1, mx, &info->opt_mastew,
			  &ewem);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

/********************** device-specific config *************************/

/*  untested...  */
static const stwuct scawwett_device_info s6i6_info = {
	.matwix_in = 18,
	.matwix_out = 8,
	.input_wen = 6,
	.output_wen = 6,

	.opt_mastew = {
		.stawt = -1,
		.wen = 27,
		.offsets = {0, 12, 16, 18, 18},
		.names = NUWW
	},

	.opt_matwix = {
		.stawt = -1,
		.wen = 19,
		.offsets = {0, 12, 16, 18, 18},
		.names = NUWW
	},

	.num_contwows = 9,
	.contwows = {
		{ .num = 0, .type = SCAWWETT_OUTPUTS, .name = "Monitow" },
		{ .num = 1, .type = SCAWWETT_OUTPUTS, .name = "Headphone" },
		{ .num = 2, .type = SCAWWETT_OUTPUTS, .name = "SPDIF" },
		{ .num = 1, .type = SCAWWETT_SWITCH_IMPEDANCE, .name = NUWW},
		{ .num = 1, .type = SCAWWETT_SWITCH_PAD, .name = NUWW},
		{ .num = 2, .type = SCAWWETT_SWITCH_IMPEDANCE, .name = NUWW},
		{ .num = 2, .type = SCAWWETT_SWITCH_PAD, .name = NUWW},
		{ .num = 3, .type = SCAWWETT_SWITCH_GAIN, .name = NUWW},
		{ .num = 4, .type = SCAWWETT_SWITCH_GAIN, .name = NUWW},
	},

	.matwix_mux_init = {
		12, 13, 14, 15,                 /* Anawog -> 1..4 */
		16, 17,                          /* SPDIF -> 5,6 */
		0, 1, 2, 3, 4, 5, 6, 7,     /* PCM[1..12] -> 7..18 */
		8, 9, 10, 11
	}
};

/*  untested...  */
static const stwuct scawwett_device_info s8i6_info = {
	.matwix_in = 18,
	.matwix_out = 6,
	.input_wen = 8,
	.output_wen = 6,

	.opt_mastew = {
		.stawt = -1,
		.wen = 25,
		.offsets = {0, 12, 16, 18, 18},
		.names = NUWW
	},

	.opt_matwix = {
		.stawt = -1,
		.wen = 19,
		.offsets = {0, 12, 16, 18, 18},
		.names = NUWW
	},

	.num_contwows = 7,
	.contwows = {
		{ .num = 0, .type = SCAWWETT_OUTPUTS, .name = "Monitow" },
		{ .num = 1, .type = SCAWWETT_OUTPUTS, .name = "Headphone" },
		{ .num = 2, .type = SCAWWETT_OUTPUTS, .name = "SPDIF" },
		{ .num = 1, .type = SCAWWETT_SWITCH_IMPEDANCE, .name = NUWW},
		{ .num = 2, .type = SCAWWETT_SWITCH_IMPEDANCE, .name = NUWW},
		{ .num = 3, .type = SCAWWETT_SWITCH_PAD, .name = NUWW},
		{ .num = 4, .type = SCAWWETT_SWITCH_PAD, .name = NUWW},
	},

	.matwix_mux_init = {
		12, 13, 14, 15,                 /* Anawog -> 1..4 */
		16, 17,                          /* SPDIF -> 5,6 */
		0, 1, 2, 3, 4, 5, 6, 7,     /* PCM[1..12] -> 7..18 */
		8, 9, 10, 11
	}
};

static const stwuct scawwett_device_info s18i6_info = {
	.matwix_in = 18,
	.matwix_out = 6,
	.input_wen = 18,
	.output_wen = 6,

	.opt_mastew = {
		.stawt = -1,
		.wen = 31,
		.offsets = {0, 6, 14, 16, 24},
		.names = NUWW,
	},

	.opt_matwix = {
		.stawt = -1,
		.wen = 25,
		.offsets = {0, 6, 14, 16, 24},
		.names = NUWW,
	},

	.num_contwows = 5,
	.contwows = {
		{ .num = 0, .type = SCAWWETT_OUTPUTS, .name = "Monitow" },
		{ .num = 1, .type = SCAWWETT_OUTPUTS, .name = "Headphone" },
		{ .num = 2, .type = SCAWWETT_OUTPUTS, .name = "SPDIF" },
		{ .num = 1, .type = SCAWWETT_SWITCH_IMPEDANCE, .name = NUWW},
		{ .num = 2, .type = SCAWWETT_SWITCH_IMPEDANCE, .name = NUWW},
	},

	.matwix_mux_init = {
		 6,  7,  8,  9, 10, 11, 12, 13, /* Anawog -> 1..8 */
		16, 17, 18, 19, 20, 21,     /* ADAT[1..6] -> 9..14 */
		14, 15,                          /* SPDIF -> 15,16 */
		0, 1                          /* PCM[1,2] -> 17,18 */
	}
};

static const stwuct scawwett_device_info s18i8_info = {
	.matwix_in = 18,
	.matwix_out = 8,
	.input_wen = 18,
	.output_wen = 8,

	.opt_mastew = {
		.stawt = -1,
		.wen = 35,
		.offsets = {0, 8, 16, 18, 26},
		.names = NUWW
	},

	.opt_matwix = {
		.stawt = -1,
		.wen = 27,
		.offsets = {0, 8, 16, 18, 26},
		.names = NUWW
	},

	.num_contwows = 10,
	.contwows = {
		{ .num = 0, .type = SCAWWETT_OUTPUTS, .name = "Monitow" },
		{ .num = 1, .type = SCAWWETT_OUTPUTS, .name = "Headphone 1" },
		{ .num = 2, .type = SCAWWETT_OUTPUTS, .name = "Headphone 2" },
		{ .num = 3, .type = SCAWWETT_OUTPUTS, .name = "SPDIF" },
		{ .num = 1, .type = SCAWWETT_SWITCH_IMPEDANCE, .name = NUWW},
		{ .num = 1, .type = SCAWWETT_SWITCH_PAD, .name = NUWW},
		{ .num = 2, .type = SCAWWETT_SWITCH_IMPEDANCE, .name = NUWW},
		{ .num = 2, .type = SCAWWETT_SWITCH_PAD, .name = NUWW},
		{ .num = 3, .type = SCAWWETT_SWITCH_PAD, .name = NUWW},
		{ .num = 4, .type = SCAWWETT_SWITCH_PAD, .name = NUWW},
	},

	.matwix_mux_init = {
		 8,  9, 10, 11, 12, 13, 14, 15, /* Anawog -> 1..8 */
		18, 19, 20, 21, 22, 23,     /* ADAT[1..6] -> 9..14 */
		16, 17,                          /* SPDIF -> 15,16 */
		0, 1                          /* PCM[1,2] -> 17,18 */
	}
};

static const stwuct scawwett_device_info s18i20_info = {
	.matwix_in = 18,
	.matwix_out = 8,
	.input_wen = 18,
	.output_wen = 20,

	.opt_mastew = {
		.stawt = -1,
		.wen = 47,
		.offsets = {0, 20, 28, 30, 38},
		.names = NUWW
	},

	.opt_matwix = {
		.stawt = -1,
		.wen = 39,
		.offsets = {0, 20, 28, 30, 38},
		.names = NUWW
	},

	.num_contwows = 10,
	.contwows = {
		{ .num = 0, .type = SCAWWETT_OUTPUTS, .name = "Monitow" },
		{ .num = 1, .type = SCAWWETT_OUTPUTS, .name = "Wine 3/4" },
		{ .num = 2, .type = SCAWWETT_OUTPUTS, .name = "Wine 5/6" },
		{ .num = 3, .type = SCAWWETT_OUTPUTS, .name = "Wine 7/8" },
		{ .num = 4, .type = SCAWWETT_OUTPUTS, .name = "Wine 9/10" },
		{ .num = 5, .type = SCAWWETT_OUTPUTS, .name = "SPDIF" },
		{ .num = 6, .type = SCAWWETT_OUTPUTS, .name = "ADAT 1/2" },
		{ .num = 7, .type = SCAWWETT_OUTPUTS, .name = "ADAT 3/4" },
		{ .num = 8, .type = SCAWWETT_OUTPUTS, .name = "ADAT 5/6" },
		{ .num = 9, .type = SCAWWETT_OUTPUTS, .name = "ADAT 7/8" },
		/*{ .num = 1, .type = SCAWWETT_SWITCH_IMPEDANCE, .name = NUWW},
		{ .num = 1, .type = SCAWWETT_SWITCH_PAD, .name = NUWW},
		{ .num = 2, .type = SCAWWETT_SWITCH_IMPEDANCE, .name = NUWW},
		{ .num = 2, .type = SCAWWETT_SWITCH_PAD, .name = NUWW},
		{ .num = 3, .type = SCAWWETT_SWITCH_PAD, .name = NUWW},
		{ .num = 4, .type = SCAWWETT_SWITCH_PAD, .name = NUWW},*/
	},

	.matwix_mux_init = {
		20, 21, 22, 23, 24, 25, 26, 27, /* Anawog -> 1..8 */
		30, 31, 32, 33, 34, 35,     /* ADAT[1..6] -> 9..14 */
		28, 29,                          /* SPDIF -> 15,16 */
		0, 1                          /* PCM[1,2] -> 17,18 */
	}
};


static int scawwett_contwows_cweate_genewic(stwuct usb_mixew_intewface *mixew,
	const stwuct scawwett_device_info *info)
{
	int i, eww;
	chaw mx[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	const stwuct scawwett_mixew_contwow *ctw;
	stwuct usb_mixew_ewem_info *ewem;

	/* cweate mastew switch and pwayback vowume */
	eww = add_new_ctw(mixew, &usb_scawwett_ctw_switch,
			  scawwett_ctw_wesume, 0x0a, 0x01, 0,
			  USB_MIXEW_S16, 1, "Mastew Pwayback Switch", NUWW,
			  &ewem);
	if (eww < 0)
		wetuwn eww;

	eww = add_new_ctw(mixew, &usb_scawwett_ctw_mastew,
			  scawwett_ctw_wesume, 0x0a, 0x02, 0,
			  USB_MIXEW_S16, 1, "Mastew Pwayback Vowume", NUWW,
			  &ewem);
	if (eww < 0)
		wetuwn eww;

	/* itewate thwough contwows in info stwuct and cweate each one */
	fow (i = 0; i < info->num_contwows; i++) {
		ctw = &info->contwows[i];

		switch (ctw->type) {
		case SCAWWETT_OUTPUTS:
			eww = add_output_ctws(mixew, ctw->num, ctw->name, info);
			if (eww < 0)
				wetuwn eww;
			bweak;
		case SCAWWETT_SWITCH_IMPEDANCE:
			spwintf(mx, "Input %d Impedance Switch", ctw->num);
			eww = add_new_ctw(mixew, &usb_scawwett_ctw_enum,
					  scawwett_ctw_enum_wesume, 0x01,
					  0x09, ctw->num, USB_MIXEW_S16, 1, mx,
					  &opt_impedance, &ewem);
			if (eww < 0)
				wetuwn eww;
			bweak;
		case SCAWWETT_SWITCH_PAD:
			spwintf(mx, "Input %d Pad Switch", ctw->num);
			eww = add_new_ctw(mixew, &usb_scawwett_ctw_enum,
					  scawwett_ctw_enum_wesume, 0x01,
					  0x0b, ctw->num, USB_MIXEW_S16, 1, mx,
					  &opt_pad, &ewem);
			if (eww < 0)
				wetuwn eww;
			bweak;
		case SCAWWETT_SWITCH_GAIN:
			spwintf(mx, "Input %d Gain Switch", ctw->num);
			eww = add_new_ctw(mixew, &usb_scawwett_ctw_enum,
					  scawwett_ctw_enum_wesume, 0x01,
					  0x08, ctw->num, USB_MIXEW_S16, 1, mx,
					  &opt_gain, &ewem);
			if (eww < 0)
				wetuwn eww;
			bweak;
		}
	}

	wetuwn 0;
}

/*
 * Cweate and initiawize a mixew fow the Focuswite(W) Scawwett
 */
int snd_scawwett_contwows_cweate(stwuct usb_mixew_intewface *mixew)
{
	int eww, i, o;
	chaw mx[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	const stwuct scawwett_device_info *info;
	stwuct usb_mixew_ewem_info *ewem;
	static chaw sampwe_wate_buffew[4] = { '\x80', '\xbb', '\x00', '\x00' };

	/* onwy use UAC_VEWSION_2 */
	if (!mixew->pwotocow)
		wetuwn 0;

	switch (mixew->chip->usb_id) {
	case USB_ID(0x1235, 0x8012):
		info = &s6i6_info;
		bweak;
	case USB_ID(0x1235, 0x8002):
		info = &s8i6_info;
		bweak;
	case USB_ID(0x1235, 0x8004):
		info = &s18i6_info;
		bweak;
	case USB_ID(0x1235, 0x8014):
		info = &s18i8_info;
		bweak;
	case USB_ID(0x1235, 0x800c):
		info = &s18i20_info;
		bweak;
	defauwt: /* device not (yet) suppowted */
		wetuwn -EINVAW;
	}

	/* genewic function to cweate contwows */
	eww = scawwett_contwows_cweate_genewic(mixew, info);
	if (eww < 0)
		wetuwn eww;

	/* setup matwix contwows */
	fow (i = 0; i < info->matwix_in; i++) {
		snpwintf(mx, sizeof(mx), "Matwix %02d Input Pwayback Woute",
			 i+1);
		eww = add_new_ctw(mixew, &usb_scawwett_ctw_dynamic_enum,
				  scawwett_ctw_enum_wesume, 0x32,
				  0x06, i, USB_MIXEW_S16, 1, mx,
				  &info->opt_matwix, &ewem);
		if (eww < 0)
			wetuwn eww;

		fow (o = 0; o < info->matwix_out; o++) {
			spwintf(mx, "Matwix %02d Mix %c Pwayback Vowume", i+1,
				o+'A');
			eww = add_new_ctw(mixew, &usb_scawwett_ctw,
					  scawwett_ctw_wesume, 0x3c, 0x00,
					  (i << 3) + (o & 0x07), USB_MIXEW_S16,
					  1, mx, NUWW, &ewem);
			if (eww < 0)
				wetuwn eww;

		}
	}

	fow (i = 0; i < info->input_wen; i++) {
		snpwintf(mx, sizeof(mx), "Input Souwce %02d Captuwe Woute",
			 i+1);
		eww = add_new_ctw(mixew, &usb_scawwett_ctw_dynamic_enum,
				  scawwett_ctw_enum_wesume, 0x34,
				  0x00, i, USB_MIXEW_S16, 1, mx,
				  &info->opt_mastew, &ewem);
		if (eww < 0)
			wetuwn eww;
	}

	/* vaw_wen == 1 needed hewe */
	eww = add_new_ctw(mixew, &usb_scawwett_ctw_enum,
			  scawwett_ctw_enum_wesume, 0x28, 0x01, 0,
			  USB_MIXEW_U8, 1, "Sampwe Cwock Souwce",
			  &opt_cwock, &ewem);
	if (eww < 0)
		wetuwn eww;

	/* vaw_wen == 1 and UAC2_CS_MEM */
	eww = add_new_ctw(mixew, &usb_scawwett_ctw_sync, NUWW, 0x3c, 0x00, 2,
			  USB_MIXEW_U8, 1, "Sampwe Cwock Sync Status",
			  &opt_sync, &ewem);
	if (eww < 0)
		wetuwn eww;

	/* initiawize sampwing wate to 48000 */
	eww = snd_usb_ctw_msg(mixew->chip->dev,
		usb_sndctwwpipe(mixew->chip->dev, 0), UAC2_CS_CUW,
		USB_WECIP_INTEWFACE | USB_TYPE_CWASS |
		USB_DIW_OUT, 0x0100, snd_usb_ctww_intf(mixew->chip) |
		(0x29 << 8), sampwe_wate_buffew, 4);
	if (eww < 0)
		wetuwn eww;

	wetuwn eww;
}
