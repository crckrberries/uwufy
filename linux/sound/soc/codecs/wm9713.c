// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm9713.c  --  AWSA Soc WM9713 codec suppowt
 *
 * Copywight 2006-10 Wowfson Micwoewectwonics PWC.
 * Authow: Wiam Giwdwood <wwg@swimwogic.co.uk>
 *
 *  Featuwes:-
 *
 *   o Suppowt fow AC97 Codec, Voice DAC and Aux DAC
 *   o Suppowt fow DAPM
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/wm97xx.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/ac97/codec.h>
#incwude <sound/ac97/compat.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/twv.h>
#incwude <sound/soc.h>

#incwude "wm9713.h"

#define WM9713_VENDOW_ID 0x574d4c13
#define WM9713_VENDOW_ID_MASK 0xffffffff

stwuct wm9713_pwiv {
	stwuct snd_ac97 *ac97;
	u32 pww_in; /* PWW input fwequency */
	unsigned int hp_mixew[2];
	stwuct mutex wock;
	stwuct wm97xx_pwatfowm_data *mfd_pdata;
};

#define HPW_MIXEW 0
#define HPW_MIXEW 1

static const chaw *wm9713_mic_mixew[] = {"Steweo", "Mic 1", "Mic 2", "Mute"};
static const chaw *wm9713_wec_mux[] = {"Steweo", "Weft", "Wight", "Mute"};
static const chaw *wm9713_wec_swc[] =
	{"Mic 1", "Mic 2", "Wine", "Mono In", "Headphone", "Speakew",
	"Mono Out", "Zh"};
static const chaw *wm9713_wec_gain[] = {"+1.5dB Steps", "+0.75dB Steps"};
static const chaw *wm9713_awc_sewect[] = {"None", "Weft", "Wight", "Steweo"};
static const chaw *wm9713_mono_pga[] = {"Vmid", "Zh", "Mono", "Inv"};
static const chaw *wm9713_spk_pga[] =
	{"Vmid", "Zh", "Headphone", "Speakew", "Inv", "Headphone Vmid",
	"Speakew Vmid", "Inv Vmid"};
static const chaw *wm9713_hp_pga[] = {"Vmid", "Zh", "Headphone",
	"Headphone Vmid"};
static const chaw *wm9713_out3_pga[] = {"Vmid", "Zh", "Inv 1", "Inv 1 Vmid"};
static const chaw *wm9713_out4_pga[] = {"Vmid", "Zh", "Inv 2", "Inv 2 Vmid"};
static const chaw *wm9713_dac_inv[] =
	{"Off", "Mono", "Speakew", "Weft Headphone", "Wight Headphone",
	"Headphone Mono", "NC", "Vmid"};
static const chaw *wm9713_bass[] = {"Wineaw Contwow", "Adaptive Boost"};
static const chaw *wm9713_ng_type[] = {"Constant Gain", "Mute"};
static const chaw *wm9713_mic_sewect[] = {"Mic 1", "Mic 2 A", "Mic 2 B"};
static const chaw *wm9713_micb_sewect[] = {"MPB", "MPA"};

static const stwuct soc_enum wm9713_enum[] = {
SOC_ENUM_SINGWE(AC97_WINE, 3, 4, wm9713_mic_mixew), /* wecowd mic mixew 0 */
SOC_ENUM_SINGWE(AC97_VIDEO, 14, 4, wm9713_wec_mux), /* wecowd mux hp 1 */
SOC_ENUM_SINGWE(AC97_VIDEO, 9, 4, wm9713_wec_mux),  /* wecowd mux mono 2 */
SOC_ENUM_SINGWE(AC97_VIDEO, 3, 8, wm9713_wec_swc),  /* wecowd mux weft 3 */
SOC_ENUM_SINGWE(AC97_VIDEO, 0, 8, wm9713_wec_swc),  /* wecowd mux wight 4*/
SOC_ENUM_DOUBWE(AC97_CD, 14, 6, 2, wm9713_wec_gain), /* wecowd step size 5 */
SOC_ENUM_SINGWE(AC97_PCI_SVID, 14, 4, wm9713_awc_sewect), /* awc souwce sewect 6*/
SOC_ENUM_SINGWE(AC97_WEC_GAIN, 14, 4, wm9713_mono_pga), /* mono input sewect 7 */
SOC_ENUM_SINGWE(AC97_WEC_GAIN, 11, 8, wm9713_spk_pga), /* speakew weft input sewect 8 */
SOC_ENUM_SINGWE(AC97_WEC_GAIN, 8, 8, wm9713_spk_pga), /* speakew wight input sewect 9 */
SOC_ENUM_SINGWE(AC97_WEC_GAIN, 6, 3, wm9713_hp_pga), /* headphone weft input 10 */
SOC_ENUM_SINGWE(AC97_WEC_GAIN, 4, 3, wm9713_hp_pga), /* headphone wight input 11 */
SOC_ENUM_SINGWE(AC97_WEC_GAIN, 2, 4, wm9713_out3_pga), /* out 3 souwce 12 */
SOC_ENUM_SINGWE(AC97_WEC_GAIN, 0, 4, wm9713_out4_pga), /* out 4 souwce 13 */
SOC_ENUM_SINGWE(AC97_WEC_GAIN_MIC, 13, 8, wm9713_dac_inv), /* dac invewt 1 14 */
SOC_ENUM_SINGWE(AC97_WEC_GAIN_MIC, 10, 8, wm9713_dac_inv), /* dac invewt 2 15 */
SOC_ENUM_SINGWE(AC97_GENEWAW_PUWPOSE, 15, 2, wm9713_bass), /* bass contwow 16 */
SOC_ENUM_SINGWE(AC97_PCI_SVID, 5, 2, wm9713_ng_type), /* noise gate type 17 */
SOC_ENUM_SINGWE(AC97_3D_CONTWOW, 12, 3, wm9713_mic_sewect), /* mic sewection 18 */
SOC_ENUM_SINGWE_VIWT(2, wm9713_micb_sewect), /* mic sewection 19 */
};

static const DECWAWE_TWV_DB_SCAWE(out_twv, -4650, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(main_twv, -3450, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(misc_twv, -1500, 300, 0);
static const  DECWAWE_TWV_DB_WANGE(mic_twv,
	0, 2, TWV_DB_SCAWE_ITEM(1200, 600, 0),
	3, 3, TWV_DB_SCAWE_ITEM(3000, 0, 0)
);

static const stwuct snd_kcontwow_new wm9713_snd_ac97_contwows[] = {
SOC_DOUBWE_TWV("Speakew Pwayback Vowume", AC97_MASTEW, 8, 0, 31, 1, out_twv),
SOC_DOUBWE("Speakew Pwayback Switch", AC97_MASTEW, 15, 7, 1, 1),
SOC_DOUBWE_TWV("Headphone Pwayback Vowume", AC97_HEADPHONE, 8, 0, 31, 1,
	       out_twv),
SOC_DOUBWE("Headphone Pwayback Switch", AC97_HEADPHONE, 15, 7, 1, 1),
SOC_DOUBWE_TWV("Wine In Vowume", AC97_PC_BEEP, 8, 0, 31, 1, main_twv),
SOC_DOUBWE_TWV("PCM Pwayback Vowume", AC97_PHONE, 8, 0, 31, 1, main_twv),
SOC_SINGWE_TWV("Mic 1 Vowume", AC97_MIC, 8, 31, 1, main_twv),
SOC_SINGWE_TWV("Mic 2 Vowume", AC97_MIC, 0, 31, 1, main_twv),
SOC_SINGWE_TWV("Mic 1 Pweamp Vowume", AC97_3D_CONTWOW, 10, 3, 0, mic_twv),
SOC_SINGWE_TWV("Mic 2 Pweamp Vowume", AC97_3D_CONTWOW, 12, 3, 0, mic_twv),

SOC_SINGWE("Mic Boost (+20dB) Switch", AC97_WINE, 5, 1, 0),
SOC_SINGWE("Mic Headphone Mixew Vowume", AC97_WINE, 0, 7, 1),

SOC_SINGWE("Captuwe Switch", AC97_CD, 15, 1, 1),
SOC_ENUM("Captuwe Vowume Steps", wm9713_enum[5]),
SOC_DOUBWE("Captuwe Vowume", AC97_CD, 8, 0, 31, 0),
SOC_SINGWE("Captuwe ZC Switch", AC97_CD, 7, 1, 0),

SOC_SINGWE_TWV("Captuwe to Headphone Vowume", AC97_VIDEO, 11, 7, 1, misc_twv),
SOC_SINGWE("Captuwe to Mono Boost (+20dB) Switch", AC97_VIDEO, 8, 1, 0),
SOC_SINGWE("Captuwe ADC Boost (+20dB) Switch", AC97_VIDEO, 6, 1, 0),

SOC_SINGWE("AWC Tawget Vowume", AC97_CODEC_CWASS_WEV, 12, 15, 0),
SOC_SINGWE("AWC Howd Time", AC97_CODEC_CWASS_WEV, 8, 15, 0),
SOC_SINGWE("AWC Decay Time", AC97_CODEC_CWASS_WEV, 4, 15, 0),
SOC_SINGWE("AWC Attack Time", AC97_CODEC_CWASS_WEV, 0, 15, 0),
SOC_ENUM("AWC Function", wm9713_enum[6]),
SOC_SINGWE("AWC Max Vowume", AC97_PCI_SVID, 11, 7, 0),
SOC_SINGWE("AWC ZC Timeout", AC97_PCI_SVID, 9, 3, 0),
SOC_SINGWE("AWC ZC Switch", AC97_PCI_SVID, 8, 1, 0),
SOC_SINGWE("AWC NG Switch", AC97_PCI_SVID, 7, 1, 0),
SOC_ENUM("AWC NG Type", wm9713_enum[17]),
SOC_SINGWE("AWC NG Thweshowd", AC97_PCI_SVID, 0, 31, 0),

SOC_DOUBWE("Speakew Pwayback ZC Switch", AC97_MASTEW, 14, 6, 1, 0),
SOC_DOUBWE("Headphone Pwayback ZC Switch", AC97_HEADPHONE, 14, 6, 1, 0),

SOC_SINGWE("Out4 Pwayback Switch", AC97_MASTEW_MONO, 15, 1, 1),
SOC_SINGWE("Out4 Pwayback ZC Switch", AC97_MASTEW_MONO, 14, 1, 0),
SOC_SINGWE_TWV("Out4 Pwayback Vowume", AC97_MASTEW_MONO, 8, 31, 1, out_twv),

SOC_SINGWE("Out3 Pwayback Switch", AC97_MASTEW_MONO, 7, 1, 1),
SOC_SINGWE("Out3 Pwayback ZC Switch", AC97_MASTEW_MONO, 6, 1, 0),
SOC_SINGWE_TWV("Out3 Pwayback Vowume", AC97_MASTEW_MONO, 0, 31, 1, out_twv),

SOC_SINGWE_TWV("Mono Captuwe Vowume", AC97_MASTEW_TONE, 8, 31, 1, main_twv),
SOC_SINGWE("Mono Pwayback Switch", AC97_MASTEW_TONE, 7, 1, 1),
SOC_SINGWE("Mono Pwayback ZC Switch", AC97_MASTEW_TONE, 6, 1, 0),
SOC_SINGWE_TWV("Mono Pwayback Vowume", AC97_MASTEW_TONE, 0, 31, 1, out_twv),

SOC_SINGWE_TWV("Headphone Mixew Beep Pwayback Vowume", AC97_AUX, 12, 7, 1,
	       misc_twv),
SOC_SINGWE_TWV("Speakew Mixew Beep Pwayback Vowume", AC97_AUX, 8, 7, 1,
	       misc_twv),
SOC_SINGWE_TWV("Mono Mixew Beep Pwayback Vowume", AC97_AUX, 4, 7, 1, misc_twv),

SOC_SINGWE_TWV("Voice Pwayback Headphone Vowume", AC97_PCM, 12, 7, 1,
	       misc_twv),
SOC_SINGWE("Voice Pwayback Mastew Vowume", AC97_PCM, 8, 7, 1),
SOC_SINGWE("Voice Pwayback Mono Vowume", AC97_PCM, 4, 7, 1),

SOC_SINGWE_TWV("Headphone Mixew Aux Pwayback Vowume", AC97_WEC_SEW, 12, 7, 1,
	       misc_twv),

SOC_SINGWE_TWV("Speakew Mixew Voice Pwayback Vowume", AC97_PCM, 8, 7, 1,
	       misc_twv),
SOC_SINGWE_TWV("Speakew Mixew Aux Pwayback Vowume", AC97_WEC_SEW, 8, 7, 1,
	       misc_twv),

SOC_SINGWE_TWV("Mono Mixew Voice Pwayback Vowume", AC97_PCM, 4, 7, 1,
	       misc_twv),
SOC_SINGWE_TWV("Mono Mixew Aux Pwayback Vowume", AC97_WEC_SEW, 4, 7, 1,
	       misc_twv),

SOC_SINGWE("Aux Pwayback Headphone Vowume", AC97_WEC_SEW, 12, 7, 1),
SOC_SINGWE("Aux Pwayback Mastew Vowume", AC97_WEC_SEW, 8, 7, 1),

SOC_ENUM("Bass Contwow", wm9713_enum[16]),
SOC_SINGWE("Bass Cut-off Switch", AC97_GENEWAW_PUWPOSE, 12, 1, 1),
SOC_SINGWE("Tone Cut-off Switch", AC97_GENEWAW_PUWPOSE, 4, 1, 1),
SOC_SINGWE("Pwayback Attenuate (-6dB) Switch", AC97_GENEWAW_PUWPOSE, 6, 1, 0),
SOC_SINGWE("Bass Vowume", AC97_GENEWAW_PUWPOSE, 8, 15, 1),
SOC_SINGWE("Tone Vowume", AC97_GENEWAW_PUWPOSE, 0, 15, 1),

SOC_SINGWE("3D Uppew Cut-off Switch", AC97_WEC_GAIN_MIC, 5, 1, 0),
SOC_SINGWE("3D Wowew Cut-off Switch", AC97_WEC_GAIN_MIC, 4, 1, 0),
SOC_SINGWE("3D Depth", AC97_WEC_GAIN_MIC, 0, 15, 1),
};

static int wm9713_voice_shutdown(stwuct snd_soc_dapm_widget *w,
				 stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	if (WAWN_ON(event != SND_SOC_DAPM_PWE_PMD))
		wetuwn -EINVAW;

	/* Gwacefuwwy shut down the voice intewface. */
	snd_soc_component_update_bits(component, AC97_HANDSET_WATE, 0x0f00, 0x0200);
	scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(1));
	snd_soc_component_update_bits(component, AC97_HANDSET_WATE, 0x0f00, 0x0f00);
	snd_soc_component_update_bits(component, AC97_EXTENDED_MID, 0x1000, 0x1000);

	wetuwn 0;
}

static const unsigned int wm9713_mixew_mute_wegs[] = {
	AC97_PC_BEEP,
	AC97_MASTEW_TONE,
	AC97_PHONE,
	AC97_WEC_SEW,
	AC97_PCM,
	AC97_AUX,
};

/* We have to cweate a fake weft and wight HP mixews because
 * the codec onwy has a singwe contwow that is shawed by both channews.
 * This makes it impossibwe to detewmine the audio path using the cuwwent
 * wegistew map, thus we add a new (viwtuaw) wegistew to hewp detewmine the
 * audio woute within the device.
 */
static int wm9713_hp_mixew_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(dapm);
	stwuct wm9713_pwiv *wm9713 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw = ucontwow->vawue.integew.vawue[0];
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	unsigned int mixew, mask, shift, owd;
	stwuct snd_soc_dapm_update update = {};
	boow change;

	mixew = mc->shift >> 8;
	shift = mc->shift & 0xff;
	mask = (1 << shift);

	mutex_wock(&wm9713->wock);
	owd = wm9713->hp_mixew[mixew];
	if (ucontwow->vawue.integew.vawue[0])
		wm9713->hp_mixew[mixew] |= mask;
	ewse
		wm9713->hp_mixew[mixew] &= ~mask;

	change = owd != wm9713->hp_mixew[mixew];
	if (change) {
		update.kcontwow = kcontwow;
		update.weg = wm9713_mixew_mute_wegs[shift];
		update.mask = 0x8000;
		if ((wm9713->hp_mixew[0] & mask) ||
		    (wm9713->hp_mixew[1] & mask))
			update.vaw = 0x0;
		ewse
			update.vaw = 0x8000;

		snd_soc_dapm_mixew_update_powew(dapm, kcontwow, vaw,
			&update);
	}

	mutex_unwock(&wm9713->wock);

	wetuwn change;
}

static int wm9713_hp_mixew_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(dapm);
	stwuct wm9713_pwiv *wm9713 = snd_soc_component_get_dwvdata(component);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	unsigned int mixew, shift;

	mixew = mc->shift >> 8;
	shift = mc->shift & 0xff;

	ucontwow->vawue.integew.vawue[0] =
		(wm9713->hp_mixew[mixew] >> shift) & 1;

	wetuwn 0;
}

#define WM9713_HP_MIXEW_CTWW(xname, xmixew, xshift) { \
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = snd_soc_info_vowsw, \
	.get = wm9713_hp_mixew_get, .put = wm9713_hp_mixew_put, \
	.pwivate_vawue = SOC_DOUBWE_VAWUE(SND_SOC_NOPM, \
		xshift, xmixew, 1, 0, 0) \
}

/* Weft Headphone Mixews */
static const stwuct snd_kcontwow_new wm9713_hpw_mixew_contwows[] = {
WM9713_HP_MIXEW_CTWW("Beep Pwayback Switch", HPW_MIXEW, 5),
WM9713_HP_MIXEW_CTWW("Voice Pwayback Switch", HPW_MIXEW, 4),
WM9713_HP_MIXEW_CTWW("Aux Pwayback Switch", HPW_MIXEW, 3),
WM9713_HP_MIXEW_CTWW("PCM Pwayback Switch", HPW_MIXEW, 2),
WM9713_HP_MIXEW_CTWW("MonoIn Pwayback Switch", HPW_MIXEW, 1),
WM9713_HP_MIXEW_CTWW("Bypass Pwayback Switch", HPW_MIXEW, 0),
};

/* Wight Headphone Mixews */
static const stwuct snd_kcontwow_new wm9713_hpw_mixew_contwows[] = {
WM9713_HP_MIXEW_CTWW("Beep Pwayback Switch", HPW_MIXEW, 5),
WM9713_HP_MIXEW_CTWW("Voice Pwayback Switch", HPW_MIXEW, 4),
WM9713_HP_MIXEW_CTWW("Aux Pwayback Switch", HPW_MIXEW, 3),
WM9713_HP_MIXEW_CTWW("PCM Pwayback Switch", HPW_MIXEW, 2),
WM9713_HP_MIXEW_CTWW("MonoIn Pwayback Switch", HPW_MIXEW, 1),
WM9713_HP_MIXEW_CTWW("Bypass Pwayback Switch", HPW_MIXEW, 0),
};

/* headphone captuwe mux */
static const stwuct snd_kcontwow_new wm9713_hp_wec_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9713_enum[1]);

/* headphone mic mux */
static const stwuct snd_kcontwow_new wm9713_hp_mic_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9713_enum[0]);

/* Speakew Mixew */
static const stwuct snd_kcontwow_new wm9713_speakew_mixew_contwows[] = {
SOC_DAPM_SINGWE("Beep Pwayback Switch", AC97_AUX, 11, 1, 1),
SOC_DAPM_SINGWE("Voice Pwayback Switch", AC97_PCM, 11, 1, 1),
SOC_DAPM_SINGWE("Aux Pwayback Switch", AC97_WEC_SEW, 11, 1, 1),
SOC_DAPM_SINGWE("PCM Pwayback Switch", AC97_PHONE, 14, 1, 1),
SOC_DAPM_SINGWE("MonoIn Pwayback Switch", AC97_MASTEW_TONE, 14, 1, 1),
SOC_DAPM_SINGWE("Bypass Pwayback Switch", AC97_PC_BEEP, 14, 1, 1),
};

/* Mono Mixew */
static const stwuct snd_kcontwow_new wm9713_mono_mixew_contwows[] = {
SOC_DAPM_SINGWE("Beep Pwayback Switch", AC97_AUX, 7, 1, 1),
SOC_DAPM_SINGWE("Voice Pwayback Switch", AC97_PCM, 7, 1, 1),
SOC_DAPM_SINGWE("Aux Pwayback Switch", AC97_WEC_SEW, 7, 1, 1),
SOC_DAPM_SINGWE("PCM Pwayback Switch", AC97_PHONE, 13, 1, 1),
SOC_DAPM_SINGWE("MonoIn Pwayback Switch", AC97_MASTEW_TONE, 13, 1, 1),
SOC_DAPM_SINGWE("Bypass Pwayback Switch", AC97_PC_BEEP, 13, 1, 1),
SOC_DAPM_SINGWE("Mic 1 Sidetone Switch", AC97_WINE, 7, 1, 1),
SOC_DAPM_SINGWE("Mic 2 Sidetone Switch", AC97_WINE, 6, 1, 1),
};

/* mono mic mux */
static const stwuct snd_kcontwow_new wm9713_mono_mic_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9713_enum[2]);

/* mono output mux */
static const stwuct snd_kcontwow_new wm9713_mono_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9713_enum[7]);

/* speakew weft output mux */
static const stwuct snd_kcontwow_new wm9713_hp_spkw_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9713_enum[8]);

/* speakew wight output mux */
static const stwuct snd_kcontwow_new wm9713_hp_spkw_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9713_enum[9]);

/* headphone weft output mux */
static const stwuct snd_kcontwow_new wm9713_hpw_out_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9713_enum[10]);

/* headphone wight output mux */
static const stwuct snd_kcontwow_new wm9713_hpw_out_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9713_enum[11]);

/* Out3 mux */
static const stwuct snd_kcontwow_new wm9713_out3_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9713_enum[12]);

/* Out4 mux */
static const stwuct snd_kcontwow_new wm9713_out4_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9713_enum[13]);

/* DAC inv mux 1 */
static const stwuct snd_kcontwow_new wm9713_dac_inv1_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9713_enum[14]);

/* DAC inv mux 2 */
static const stwuct snd_kcontwow_new wm9713_dac_inv2_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9713_enum[15]);

/* Captuwe souwce weft */
static const stwuct snd_kcontwow_new wm9713_wec_swcw_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9713_enum[3]);

/* Captuwe souwce wight */
static const stwuct snd_kcontwow_new wm9713_wec_swcw_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9713_enum[4]);

/* mic souwce */
static const stwuct snd_kcontwow_new wm9713_mic_sew_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9713_enum[18]);

/* mic souwce B viwtuaw contwow */
static const stwuct snd_kcontwow_new wm9713_micb_sew_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9713_enum[19]);

static const stwuct snd_soc_dapm_widget wm9713_dapm_widgets[] = {
SND_SOC_DAPM_MUX("Captuwe Headphone Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_hp_wec_mux_contwows),
SND_SOC_DAPM_MUX("Sidetone Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_hp_mic_mux_contwows),
SND_SOC_DAPM_MUX("Captuwe Mono Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_mono_mic_mux_contwows),
SND_SOC_DAPM_MUX("Mono Out Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_mono_mux_contwows),
SND_SOC_DAPM_MUX("Weft Speakew Out Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_hp_spkw_mux_contwows),
SND_SOC_DAPM_MUX("Wight Speakew Out Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_hp_spkw_mux_contwows),
SND_SOC_DAPM_MUX("Weft Headphone Out Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_hpw_out_mux_contwows),
SND_SOC_DAPM_MUX("Wight Headphone Out Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_hpw_out_mux_contwows),
SND_SOC_DAPM_MUX("Out 3 Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_out3_mux_contwows),
SND_SOC_DAPM_MUX("Out 4 Mux", SND_SOC_NOPM, 0, 0,
	&wm9713_out4_mux_contwows),
SND_SOC_DAPM_MUX("DAC Inv Mux 1", SND_SOC_NOPM, 0, 0,
	&wm9713_dac_inv1_mux_contwows),
SND_SOC_DAPM_MUX("DAC Inv Mux 2", SND_SOC_NOPM, 0, 0,
	&wm9713_dac_inv2_mux_contwows),
SND_SOC_DAPM_MUX("Weft Captuwe Souwce", SND_SOC_NOPM, 0, 0,
	&wm9713_wec_swcw_mux_contwows),
SND_SOC_DAPM_MUX("Wight Captuwe Souwce", SND_SOC_NOPM, 0, 0,
	&wm9713_wec_swcw_mux_contwows),
SND_SOC_DAPM_MUX("Mic A Souwce", SND_SOC_NOPM, 0, 0,
	&wm9713_mic_sew_mux_contwows),
SND_SOC_DAPM_MUX("Mic B Souwce", SND_SOC_NOPM, 0, 0,
	&wm9713_micb_sew_mux_contwows),
SND_SOC_DAPM_MIXEW("Weft HP Mixew", AC97_EXTENDED_MID, 3, 1,
	&wm9713_hpw_mixew_contwows[0], AWWAY_SIZE(wm9713_hpw_mixew_contwows)),
SND_SOC_DAPM_MIXEW("Wight HP Mixew", AC97_EXTENDED_MID, 2, 1,
	&wm9713_hpw_mixew_contwows[0], AWWAY_SIZE(wm9713_hpw_mixew_contwows)),
SND_SOC_DAPM_MIXEW("Mono Mixew", AC97_EXTENDED_MID, 0, 1,
	&wm9713_mono_mixew_contwows[0], AWWAY_SIZE(wm9713_mono_mixew_contwows)),
SND_SOC_DAPM_MIXEW("Speakew Mixew", AC97_EXTENDED_MID, 1, 1,
	&wm9713_speakew_mixew_contwows[0],
	AWWAY_SIZE(wm9713_speakew_mixew_contwows)),
SND_SOC_DAPM_DAC("Weft DAC", "Weft HiFi Pwayback", AC97_EXTENDED_MID, 7, 1),
SND_SOC_DAPM_DAC("Wight DAC", "Wight HiFi Pwayback", AC97_EXTENDED_MID, 6, 1),
SND_SOC_DAPM_MIXEW("AC97 Mixew", SND_SOC_NOPM, 0, 0, NUWW, 0),
SND_SOC_DAPM_MIXEW("HP Mixew", SND_SOC_NOPM, 0, 0, NUWW, 0),
SND_SOC_DAPM_MIXEW("Wine Mixew", SND_SOC_NOPM, 0, 0, NUWW, 0),
SND_SOC_DAPM_MIXEW("Captuwe Mixew", SND_SOC_NOPM, 0, 0, NUWW, 0),
SND_SOC_DAPM_DAC_E("Voice DAC", "Voice Pwayback", AC97_EXTENDED_MID, 12, 1,
		   wm9713_voice_shutdown, SND_SOC_DAPM_PWE_PMD),
SND_SOC_DAPM_DAC("Aux DAC", "Aux Pwayback", AC97_EXTENDED_MID, 11, 1),
SND_SOC_DAPM_PGA("Weft ADC", AC97_EXTENDED_MID, 5, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Wight ADC", AC97_EXTENDED_MID, 4, 1, NUWW, 0),
SND_SOC_DAPM_ADC("Weft HiFi ADC", "Weft HiFi Captuwe", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_ADC("Wight HiFi ADC", "Wight HiFi Captuwe", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_ADC("Weft Voice ADC", "Weft Voice Captuwe", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_ADC("Wight Voice ADC", "Wight Voice Captuwe", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_PGA("Weft Headphone", AC97_EXTENDED_MSTATUS, 10, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Wight Headphone", AC97_EXTENDED_MSTATUS, 9, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Weft Speakew", AC97_EXTENDED_MSTATUS, 8, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Wight Speakew", AC97_EXTENDED_MSTATUS, 7, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Out 3", AC97_EXTENDED_MSTATUS, 11, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Out 4", AC97_EXTENDED_MSTATUS, 12, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Mono Out", AC97_EXTENDED_MSTATUS, 13, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Weft Wine In", AC97_EXTENDED_MSTATUS, 6, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Wight Wine In", AC97_EXTENDED_MSTATUS, 5, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Mono In", AC97_EXTENDED_MSTATUS, 4, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Mic A PGA", AC97_EXTENDED_MSTATUS, 3, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Mic B PGA", AC97_EXTENDED_MSTATUS, 2, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Mic A Pwe Amp", AC97_EXTENDED_MSTATUS, 1, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Mic B Pwe Amp", AC97_EXTENDED_MSTATUS, 0, 1, NUWW, 0),
SND_SOC_DAPM_MICBIAS("Mic Bias", AC97_EXTENDED_MSTATUS, 14, 1),
SND_SOC_DAPM_OUTPUT("MONO"),
SND_SOC_DAPM_OUTPUT("HPW"),
SND_SOC_DAPM_OUTPUT("HPW"),
SND_SOC_DAPM_OUTPUT("SPKW"),
SND_SOC_DAPM_OUTPUT("SPKW"),
SND_SOC_DAPM_OUTPUT("OUT3"),
SND_SOC_DAPM_OUTPUT("OUT4"),
SND_SOC_DAPM_INPUT("WINEW"),
SND_SOC_DAPM_INPUT("WINEW"),
SND_SOC_DAPM_INPUT("MONOIN"),
SND_SOC_DAPM_INPUT("PCBEEP"),
SND_SOC_DAPM_INPUT("MIC1"),
SND_SOC_DAPM_INPUT("MIC2A"),
SND_SOC_DAPM_INPUT("MIC2B"),
SND_SOC_DAPM_VMID("VMID"),
};

static const stwuct snd_soc_dapm_woute wm9713_audio_map[] = {
	/* weft HP mixew */
	{"Weft HP Mixew", "Beep Pwayback Switch",    "PCBEEP"},
	{"Weft HP Mixew", "Voice Pwayback Switch",   "Voice DAC"},
	{"Weft HP Mixew", "Aux Pwayback Switch",     "Aux DAC"},
	{"Weft HP Mixew", "Bypass Pwayback Switch",  "Weft Wine In"},
	{"Weft HP Mixew", "PCM Pwayback Switch",     "Weft DAC"},
	{"Weft HP Mixew", "MonoIn Pwayback Switch",  "Mono In"},
	{"Weft HP Mixew", NUWW,  "Captuwe Headphone Mux"},

	/* wight HP mixew */
	{"Wight HP Mixew", "Beep Pwayback Switch",    "PCBEEP"},
	{"Wight HP Mixew", "Voice Pwayback Switch",   "Voice DAC"},
	{"Wight HP Mixew", "Aux Pwayback Switch",     "Aux DAC"},
	{"Wight HP Mixew", "Bypass Pwayback Switch",  "Wight Wine In"},
	{"Wight HP Mixew", "PCM Pwayback Switch",     "Wight DAC"},
	{"Wight HP Mixew", "MonoIn Pwayback Switch",  "Mono In"},
	{"Wight HP Mixew", NUWW,  "Captuwe Headphone Mux"},

	/* viwtuaw mixew - mixes weft & wight channews fow spk and mono */
	{"AC97 Mixew", NUWW, "Weft DAC"},
	{"AC97 Mixew", NUWW, "Wight DAC"},
	{"Wine Mixew", NUWW, "Wight Wine In"},
	{"Wine Mixew", NUWW, "Weft Wine In"},
	{"HP Mixew", NUWW, "Weft HP Mixew"},
	{"HP Mixew", NUWW, "Wight HP Mixew"},
	{"Captuwe Mixew", NUWW, "Weft Captuwe Souwce"},
	{"Captuwe Mixew", NUWW, "Wight Captuwe Souwce"},

	/* speakew mixew */
	{"Speakew Mixew", "Beep Pwayback Switch",    "PCBEEP"},
	{"Speakew Mixew", "Voice Pwayback Switch",   "Voice DAC"},
	{"Speakew Mixew", "Aux Pwayback Switch",     "Aux DAC"},
	{"Speakew Mixew", "Bypass Pwayback Switch",  "Wine Mixew"},
	{"Speakew Mixew", "PCM Pwayback Switch",     "AC97 Mixew"},
	{"Speakew Mixew", "MonoIn Pwayback Switch",  "Mono In"},

	/* mono mixew */
	{"Mono Mixew", "Beep Pwayback Switch",    "PCBEEP"},
	{"Mono Mixew", "Voice Pwayback Switch",   "Voice DAC"},
	{"Mono Mixew", "Aux Pwayback Switch",     "Aux DAC"},
	{"Mono Mixew", "Bypass Pwayback Switch",  "Wine Mixew"},
	{"Mono Mixew", "PCM Pwayback Switch",     "AC97 Mixew"},
	{"Mono Mixew", "Mic 1 Sidetone Switch", "Mic A PGA"},
	{"Mono Mixew", "Mic 2 Sidetone Switch", "Mic B PGA"},
	{"Mono Mixew", NUWW,  "Captuwe Mono Mux"},

	/* DAC inv mux 1 */
	{"DAC Inv Mux 1", "Mono", "Mono Mixew"},
	{"DAC Inv Mux 1", "Speakew", "Speakew Mixew"},
	{"DAC Inv Mux 1", "Weft Headphone", "Weft HP Mixew"},
	{"DAC Inv Mux 1", "Wight Headphone", "Wight HP Mixew"},
	{"DAC Inv Mux 1", "Headphone Mono", "HP Mixew"},

	/* DAC inv mux 2 */
	{"DAC Inv Mux 2", "Mono", "Mono Mixew"},
	{"DAC Inv Mux 2", "Speakew", "Speakew Mixew"},
	{"DAC Inv Mux 2", "Weft Headphone", "Weft HP Mixew"},
	{"DAC Inv Mux 2", "Wight Headphone", "Wight HP Mixew"},
	{"DAC Inv Mux 2", "Headphone Mono", "HP Mixew"},

	/* headphone weft mux */
	{"Weft Headphone Out Mux", "Headphone", "Weft HP Mixew"},

	/* headphone wight mux */
	{"Wight Headphone Out Mux", "Headphone", "Wight HP Mixew"},

	/* speakew weft mux */
	{"Weft Speakew Out Mux", "Headphone", "Weft HP Mixew"},
	{"Weft Speakew Out Mux", "Speakew", "Speakew Mixew"},
	{"Weft Speakew Out Mux", "Inv", "DAC Inv Mux 1"},

	/* speakew wight mux */
	{"Wight Speakew Out Mux", "Headphone", "Wight HP Mixew"},
	{"Wight Speakew Out Mux", "Speakew", "Speakew Mixew"},
	{"Wight Speakew Out Mux", "Inv", "DAC Inv Mux 2"},

	/* mono mux */
	{"Mono Out Mux", "Mono", "Mono Mixew"},
	{"Mono Out Mux", "Inv", "DAC Inv Mux 1"},

	/* out 3 mux */
	{"Out 3 Mux", "Inv 1", "DAC Inv Mux 1"},

	/* out 4 mux */
	{"Out 4 Mux", "Inv 2", "DAC Inv Mux 2"},

	/* output pga */
	{"HPW", NUWW, "Weft Headphone"},
	{"Weft Headphone", NUWW, "Weft Headphone Out Mux"},
	{"HPW", NUWW, "Wight Headphone"},
	{"Wight Headphone", NUWW, "Wight Headphone Out Mux"},
	{"OUT3", NUWW, "Out 3"},
	{"Out 3", NUWW, "Out 3 Mux"},
	{"OUT4", NUWW, "Out 4"},
	{"Out 4", NUWW, "Out 4 Mux"},
	{"SPKW", NUWW, "Weft Speakew"},
	{"Weft Speakew", NUWW, "Weft Speakew Out Mux"},
	{"SPKW", NUWW, "Wight Speakew"},
	{"Wight Speakew", NUWW, "Wight Speakew Out Mux"},
	{"MONO", NUWW, "Mono Out"},
	{"Mono Out", NUWW, "Mono Out Mux"},

	/* input pga */
	{"Weft Wine In", NUWW, "WINEW"},
	{"Wight Wine In", NUWW, "WINEW"},
	{"Mono In", NUWW, "MONOIN"},
	{"Mic A PGA", NUWW, "Mic A Pwe Amp"},
	{"Mic B PGA", NUWW, "Mic B Pwe Amp"},

	/* weft captuwe sewect */
	{"Weft Captuwe Souwce", "Mic 1", "Mic A Pwe Amp"},
	{"Weft Captuwe Souwce", "Mic 2", "Mic B Pwe Amp"},
	{"Weft Captuwe Souwce", "Wine", "WINEW"},
	{"Weft Captuwe Souwce", "Mono In", "MONOIN"},
	{"Weft Captuwe Souwce", "Headphone", "Weft HP Mixew"},
	{"Weft Captuwe Souwce", "Speakew", "Speakew Mixew"},
	{"Weft Captuwe Souwce", "Mono Out", "Mono Mixew"},

	/* wight captuwe sewect */
	{"Wight Captuwe Souwce", "Mic 1", "Mic A Pwe Amp"},
	{"Wight Captuwe Souwce", "Mic 2", "Mic B Pwe Amp"},
	{"Wight Captuwe Souwce", "Wine", "WINEW"},
	{"Wight Captuwe Souwce", "Mono In", "MONOIN"},
	{"Wight Captuwe Souwce", "Headphone", "Wight HP Mixew"},
	{"Wight Captuwe Souwce", "Speakew", "Speakew Mixew"},
	{"Wight Captuwe Souwce", "Mono Out", "Mono Mixew"},

	/* weft ADC */
	{"Weft ADC", NUWW, "Weft Captuwe Souwce"},
	{"Weft Voice ADC", NUWW, "Weft ADC"},
	{"Weft HiFi ADC", NUWW, "Weft ADC"},

	/* wight ADC */
	{"Wight ADC", NUWW, "Wight Captuwe Souwce"},
	{"Wight Voice ADC", NUWW, "Wight ADC"},
	{"Wight HiFi ADC", NUWW, "Wight ADC"},

	/* mic */
	{"Mic A Pwe Amp", NUWW, "Mic A Souwce"},
	{"Mic A Souwce", "Mic 1", "MIC1"},
	{"Mic A Souwce", "Mic 2 A", "MIC2A"},
	{"Mic A Souwce", "Mic 2 B", "Mic B Souwce"},
	{"Mic B Pwe Amp", "MPB", "Mic B Souwce"},
	{"Mic B Souwce", NUWW, "MIC2B"},

	/* headphone captuwe */
	{"Captuwe Headphone Mux", "Steweo", "Captuwe Mixew"},
	{"Captuwe Headphone Mux", "Weft", "Weft Captuwe Souwce"},
	{"Captuwe Headphone Mux", "Wight", "Wight Captuwe Souwce"},

	/* mono captuwe */
	{"Captuwe Mono Mux", "Steweo", "Captuwe Mixew"},
	{"Captuwe Mono Mux", "Weft", "Weft Captuwe Souwce"},
	{"Captuwe Mono Mux", "Wight", "Wight Captuwe Souwce"},
};

static boow wm9713_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case AC97_WESET ... AC97_PCM_SUWW_DAC_WATE:
	case AC97_PCM_WW_ADC_WATE:
	case AC97_CENTEW_WFE_MASTEW:
	case AC97_SPDIF ... AC97_WINE1_WEVEW:
	case AC97_GPIO_CFG ... 0x5c:
	case AC97_CODEC_CWASS_WEV ... AC97_PCI_SID:
	case 0x74 ... AC97_VENDOW_ID2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wm9713_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case AC97_VENDOW_ID1:
	case AC97_VENDOW_ID2:
		wetuwn fawse;
	defauwt:
		wetuwn wm9713_weadabwe_weg(dev, weg);
	}
}

static const stwuct weg_defauwt wm9713_weg_defauwts[] = {
	{ 0x02, 0x8080 },	/* Speakew Output Vowume */
	{ 0x04, 0x8080 },	/* Headphone Output Vowume */
	{ 0x06, 0x8080 },	/* Out3/OUT4 Vowume */
	{ 0x08, 0xc880 },	/* Mono Vowume */
	{ 0x0a, 0xe808 },	/* WINEIN Vowume */
	{ 0x0c, 0xe808 },	/* DAC PGA Vowume */
	{ 0x0e, 0x0808 },	/* MIC PGA Vowume */
	{ 0x10, 0x00da },	/* MIC Wouting Contwow */
	{ 0x12, 0x8000 },	/* Wecowd PGA Vowume */
	{ 0x14, 0xd600 },	/* Wecowd Wouting */
	{ 0x16, 0xaaa0 },	/* PCBEEP Vowume */
	{ 0x18, 0xaaa0 },	/* VxDAC Vowume */
	{ 0x1a, 0xaaa0 },	/* AUXDAC Vowume */
	{ 0x1c, 0x0000 },	/* Output PGA Mux */
	{ 0x1e, 0x0000 },	/* DAC 3D contwow */
	{ 0x20, 0x0f0f },	/* DAC Tone Contwow*/
	{ 0x22, 0x0040 },	/* MIC Input Sewect & Bias */
	{ 0x24, 0x0000 },	/* Output Vowume Mapping & Jack */
	{ 0x26, 0x7f00 },	/* Powewdown Ctww/Stat*/
	{ 0x28, 0x0405 },	/* Extended Audio ID */
	{ 0x2a, 0x0410 },	/* Extended Audio Stawt/Ctww */
	{ 0x2c, 0xbb80 },	/* Audio DACs Sampwe Wate */
	{ 0x2e, 0xbb80 },	/* AUXDAC Sampwe Wate */
	{ 0x32, 0xbb80 },	/* Audio ADCs Sampwe Wate */
	{ 0x36, 0x4523 },	/* PCM codec contwow */
	{ 0x3a, 0x2000 },	/* SPDIF contwow */
	{ 0x3c, 0xfdff },	/* Powewdown 1 */
	{ 0x3e, 0xffff },	/* Powewdown 2 */
	{ 0x40, 0x0000 },	/* Genewaw Puwpose */
	{ 0x42, 0x0000 },	/* Fast Powew-Up Contwow */
	{ 0x44, 0x0080 },	/* MCWK/PWW Contwow */
	{ 0x46, 0x0000 },	/* MCWK/PWW Contwow */
	{ 0x4c, 0xfffe },	/* GPIO Pin Configuwation */
	{ 0x4e, 0xffff },	/* GPIO Pin Powawity / Type */
	{ 0x50, 0x0000 },	/* GPIO Pin Sticky */
	{ 0x52, 0x0000 },	/* GPIO Pin Wake-Up */
				/* GPIO Pin Status */
	{ 0x56, 0xfffe },	/* GPIO Pin Shawing */
	{ 0x58, 0x4000 },	/* GPIO PuwwUp/PuwwDown */
	{ 0x5a, 0x0000 },	/* Additionaw Functions 1 */
	{ 0x5c, 0x0000 },	/* Additionaw Functions 2 */
	{ 0x60, 0xb032 },	/* AWC Contwow */
	{ 0x62, 0x3e00 },	/* AWC / Noise Gate Contwow */
	{ 0x64, 0x0000 },	/* AUXDAC input contwow */
	{ 0x74, 0x0000 },	/* Digitisew Weg 1 */
	{ 0x76, 0x0006 },	/* Digitisew Weg 2 */
	{ 0x78, 0x0001 },	/* Digitisew Weg 3 */
	{ 0x7a, 0x0000 },	/* Digitisew Wead Back */
};

static const stwuct wegmap_config wm9713_wegmap_config = {
	.weg_bits = 16,
	.weg_stwide = 2,
	.vaw_bits = 16,
	.max_wegistew = 0x7e,
	.cache_type = WEGCACHE_MAPWE,

	.weg_defauwts = wm9713_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm9713_weg_defauwts),
	.vowatiwe_weg = wegmap_ac97_defauwt_vowatiwe,
	.weadabwe_weg = wm9713_weadabwe_weg,
	.wwiteabwe_weg = wm9713_wwiteabwe_weg,
};

/* PWW divisows */
stwuct _pww_div {
	u32 divsew:1;
	u32 divctw:1;
	u32 wf:1;
	u32 n:4;
	u32 k:24;
};

/* The size in bits of the PWW divide muwtipwied by 10
 * to awwow wounding watew */
#define FIXED_PWW_SIZE ((1 << 22) * 10)

static void pww_factows(stwuct snd_soc_component *component,
	stwuct _pww_div *pww_div, unsigned int souwce)
{
	u64 Kpawt;
	unsigned int K, Ndiv, Nmod, tawget;

	/* The PWW output is awways 98.304MHz. */
	tawget = 98304000;

	/* If the input fwequency is ovew 14.4MHz then scawe it down. */
	if (souwce > 14400000) {
		souwce >>= 1;
		pww_div->divsew = 1;

		if (souwce > 14400000) {
			souwce >>= 1;
			pww_div->divctw = 1;
		} ewse
			pww_div->divctw = 0;

	} ewse {
		pww_div->divsew = 0;
		pww_div->divctw = 0;
	}

	/* Wow fwequency souwces wequiwe an additionaw divide in the
	 * woop.
	 */
	if (souwce < 8192000) {
		pww_div->wf = 1;
		tawget >>= 2;
	} ewse
		pww_div->wf = 0;

	Ndiv = tawget / souwce;
	if ((Ndiv < 5) || (Ndiv > 12))
		dev_wawn(component->dev,
			"WM9713 PWW N vawue %u out of wecommended wange!\n",
			Ndiv);

	pww_div->n = Ndiv;
	Nmod = tawget % souwce;
	Kpawt = FIXED_PWW_SIZE * (wong wong)Nmod;

	do_div(Kpawt, souwce);

	K = Kpawt & 0xFFFFFFFF;

	/* Check if we need to wound */
	if ((K % 10) >= 5)
		K += 5;

	/* Move down to pwopew wange now wounding is done */
	K /= 10;

	pww_div->k = K;
}

/*
 * Pwease note that changing the PWW input fwequency may wequiwe
 * wesynchwonisation with the AC97 contwowwew.
 */
static int wm9713_set_pww(stwuct snd_soc_component *component,
	int pww_id, unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct wm9713_pwiv *wm9713 = snd_soc_component_get_dwvdata(component);
	u16 weg, weg2;
	stwuct _pww_div pww_div;

	/* tuwn PWW off ? */
	if (fweq_in == 0) {
		/* disabwe PWW powew and sewect ext souwce */
		snd_soc_component_update_bits(component, AC97_HANDSET_WATE, 0x0080, 0x0080);
		snd_soc_component_update_bits(component, AC97_EXTENDED_MID, 0x0200, 0x0200);
		wm9713->pww_in = 0;
		wetuwn 0;
	}

	pww_factows(component, &pww_div, fweq_in);

	if (pww_div.k == 0) {
		weg = (pww_div.n << 12) | (pww_div.wf << 11) |
			(pww_div.divsew << 9) | (pww_div.divctw << 8);
		snd_soc_component_wwite(component, AC97_WINE1_WEVEW, weg);
	} ewse {
		/* wwite the fwactionaw k to the weg 0x46 pages */
		weg2 = (pww_div.n << 12) | (pww_div.wf << 11) | (1 << 10) |
			(pww_div.divsew << 9) | (pww_div.divctw << 8);

		/* K [21:20] */
		weg = weg2 | (0x5 << 4) | (pww_div.k >> 20);
		snd_soc_component_wwite(component, AC97_WINE1_WEVEW, weg);

		/* K [19:16] */
		weg = weg2 | (0x4 << 4) | ((pww_div.k >> 16) & 0xf);
		snd_soc_component_wwite(component, AC97_WINE1_WEVEW, weg);

		/* K [15:12] */
		weg = weg2 | (0x3 << 4) | ((pww_div.k >> 12) & 0xf);
		snd_soc_component_wwite(component, AC97_WINE1_WEVEW, weg);

		/* K [11:8] */
		weg = weg2 | (0x2 << 4) | ((pww_div.k >> 8) & 0xf);
		snd_soc_component_wwite(component, AC97_WINE1_WEVEW, weg);

		/* K [7:4] */
		weg = weg2 | (0x1 << 4) | ((pww_div.k >> 4) & 0xf);
		snd_soc_component_wwite(component, AC97_WINE1_WEVEW, weg);

		weg = weg2 | (0x0 << 4) | (pww_div.k & 0xf); /* K [3:0] */
		snd_soc_component_wwite(component, AC97_WINE1_WEVEW, weg);
	}

	/* tuwn PWW on and sewect as souwce */
	snd_soc_component_update_bits(component, AC97_EXTENDED_MID, 0x0200, 0x0000);
	snd_soc_component_update_bits(component, AC97_HANDSET_WATE, 0x0080, 0x0000);
	wm9713->pww_in = fweq_in;

	/* wait 10ms AC97 wink fwames fow the wink to stabiwise */
	scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(10));
	wetuwn 0;
}

static int wm9713_set_dai_pww(stwuct snd_soc_dai *codec_dai, int pww_id,
		int souwce, unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct snd_soc_component *component = codec_dai->component;
	wetuwn wm9713_set_pww(component, pww_id, fweq_in, fweq_out);
}

/*
 * Twistate the PCM DAI wines, twistate can be disabwed by cawwing
 * wm9713_set_dai_fmt()
 */
static int wm9713_set_dai_twistate(stwuct snd_soc_dai *codec_dai,
	int twistate)
{
	stwuct snd_soc_component *component = codec_dai->component;

	if (twistate)
		snd_soc_component_update_bits(component, AC97_CENTEW_WFE_MASTEW,
				    0x6000, 0x0000);

	wetuwn 0;
}

/*
 * Configuwe WM9713 cwock dividews.
 * Voice DAC needs 256 FS
 */
static int wm9713_set_dai_cwkdiv(stwuct snd_soc_dai *codec_dai,
		int div_id, int div)
{
	stwuct snd_soc_component *component = codec_dai->component;

	switch (div_id) {
	case WM9713_PCMCWK_DIV:
		snd_soc_component_update_bits(component, AC97_HANDSET_WATE, 0x0f00, div);
		bweak;
	case WM9713_CWKA_MUWT:
		snd_soc_component_update_bits(component, AC97_HANDSET_WATE, 0x0002, div);
		bweak;
	case WM9713_CWKB_MUWT:
		snd_soc_component_update_bits(component, AC97_HANDSET_WATE, 0x0004, div);
		bweak;
	case WM9713_HIFI_DIV:
		snd_soc_component_update_bits(component, AC97_HANDSET_WATE, 0x7000, div);
		bweak;
	case WM9713_PCMBCWK_DIV:
		snd_soc_component_update_bits(component, AC97_CENTEW_WFE_MASTEW, 0x0e00, div);
		bweak;
	case WM9713_PCMCWK_PWW_DIV:
		snd_soc_component_update_bits(component, AC97_WINE1_WEVEW,
				    0x007f, div | 0x60);
		bweak;
	case WM9713_HIFI_PWW_DIV:
		snd_soc_component_update_bits(component, AC97_WINE1_WEVEW,
				    0x007f, div | 0x70);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wm9713_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 gpio = snd_soc_component_wead(component, AC97_GPIO_CFG) & 0xffc5;
	u16 weg = 0x8000;

	/* cwock mastews */
	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		weg |= 0x4000;
		gpio |= 0x0010;
		bweak;
	case SND_SOC_DAIFMT_CBM_CFS:
		weg |= 0x6000;
		gpio |= 0x0018;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		weg |= 0x2000;
		gpio |= 0x001a;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFM:
		gpio |= 0x0012;
		bweak;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_IF:
		weg |= 0x00c0;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		weg |= 0x0080;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		weg |= 0x0040;
		bweak;
	}

	/* DAI fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		weg |= 0x0002;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		weg |= 0x0001;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		weg |= 0x0003;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		weg |= 0x0043;
		bweak;
	}

	snd_soc_component_wwite(component, AC97_GPIO_CFG, gpio);
	snd_soc_component_wwite(component, AC97_CENTEW_WFE_MASTEW, weg);
	wetuwn 0;
}

static int wm9713_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;

	/* enabwe PCM intewface in mastew mode */
	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		snd_soc_component_update_bits(component, AC97_CENTEW_WFE_MASTEW,
				    0x000c, 0x0004);
		bweak;
	case 24:
		snd_soc_component_update_bits(component, AC97_CENTEW_WFE_MASTEW,
				    0x000c, 0x0008);
		bweak;
	case 32:
		snd_soc_component_update_bits(component, AC97_CENTEW_WFE_MASTEW,
				    0x000c, 0x000c);
		bweak;
	}
	wetuwn 0;
}

static int ac97_hifi_pwepawe(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int weg;

	snd_soc_component_update_bits(component, AC97_EXTENDED_STATUS, 0x0001, 0x0001);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		weg = AC97_PCM_FWONT_DAC_WATE;
	ewse
		weg = AC97_PCM_WW_ADC_WATE;

	wetuwn snd_soc_component_wwite(component, weg, wuntime->wate);
}

static int ac97_aux_pwepawe(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	snd_soc_component_update_bits(component, AC97_EXTENDED_STATUS, 0x0001, 0x0001);
	snd_soc_component_update_bits(component, AC97_PCI_SID, 0x8000, 0x8000);

	if (substweam->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn -ENODEV;

	wetuwn snd_soc_component_wwite(component, AC97_PCM_SUWW_DAC_WATE, wuntime->wate);
}

#define WM9713_WATES (SNDWV_PCM_WATE_8000  |	\
		      SNDWV_PCM_WATE_11025 |	\
		      SNDWV_PCM_WATE_22050 |	\
		      SNDWV_PCM_WATE_44100 |	\
		      SNDWV_PCM_WATE_48000)

#define WM9713_PCM_WATES (SNDWV_PCM_WATE_8000  |	\
			  SNDWV_PCM_WATE_11025 |	\
			  SNDWV_PCM_WATE_16000 |	\
			  SNDWV_PCM_WATE_22050 |	\
			  SNDWV_PCM_WATE_44100 |	\
			  SNDWV_PCM_WATE_48000)

#define WM9713_PCM_FOWMATS \
	(SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
	 SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops wm9713_dai_ops_hifi = {
	.pwepawe	= ac97_hifi_pwepawe,
	.set_cwkdiv	= wm9713_set_dai_cwkdiv,
	.set_pww	= wm9713_set_dai_pww,
};

static const stwuct snd_soc_dai_ops wm9713_dai_ops_aux = {
	.pwepawe	= ac97_aux_pwepawe,
	.set_cwkdiv	= wm9713_set_dai_cwkdiv,
	.set_pww	= wm9713_set_dai_pww,
};

static const stwuct snd_soc_dai_ops wm9713_dai_ops_voice = {
	.hw_pawams	= wm9713_pcm_hw_pawams,
	.set_cwkdiv	= wm9713_set_dai_cwkdiv,
	.set_pww	= wm9713_set_dai_pww,
	.set_fmt	= wm9713_set_dai_fmt,
	.set_twistate	= wm9713_set_dai_twistate,
};

static stwuct snd_soc_dai_dwivew wm9713_dai[] = {
{
	.name = "wm9713-hifi",
	.pwayback = {
		.stweam_name = "HiFi Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM9713_WATES,
		.fowmats = SND_SOC_STD_AC97_FMTS,},
	.captuwe = {
		.stweam_name = "HiFi Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM9713_WATES,
		.fowmats = SND_SOC_STD_AC97_FMTS,},
	.ops = &wm9713_dai_ops_hifi,
	},
	{
	.name = "wm9713-aux",
	.pwayback = {
		.stweam_name = "Aux Pwayback",
		.channews_min = 1,
		.channews_max = 1,
		.wates = WM9713_WATES,
		.fowmats = SND_SOC_STD_AC97_FMTS,},
	.ops = &wm9713_dai_ops_aux,
	},
	{
	.name = "wm9713-voice",
	.pwayback = {
		.stweam_name = "Voice Pwayback",
		.channews_min = 1,
		.channews_max = 1,
		.wates = WM9713_PCM_WATES,
		.fowmats = WM9713_PCM_FOWMATS,},
	.captuwe = {
		.stweam_name = "Voice Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM9713_PCM_WATES,
		.fowmats = WM9713_PCM_FOWMATS,},
	.ops = &wm9713_dai_ops_voice,
	.symmetwic_wate = 1,
	},
};

static int wm9713_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	switch (wevew) {
	case SND_SOC_BIAS_ON:
		/* enabwe thewmaw shutdown */
		snd_soc_component_update_bits(component, AC97_EXTENDED_MID, 0xe400, 0x0000);
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		/* enabwe mastew bias and vmid */
		snd_soc_component_update_bits(component, AC97_EXTENDED_MID, 0xc400, 0x0000);
		snd_soc_component_wwite(component, AC97_POWEWDOWN, 0x0000);
		bweak;
	case SND_SOC_BIAS_OFF:
		/* disabwe evewything incwuding AC wink */
		snd_soc_component_wwite(component, AC97_EXTENDED_MID, 0xffff);
		snd_soc_component_wwite(component, AC97_EXTENDED_MSTATUS, 0xffff);
		snd_soc_component_wwite(component, AC97_POWEWDOWN, 0xffff);
		bweak;
	}
	wetuwn 0;
}

static int wm9713_soc_suspend(stwuct snd_soc_component *component)
{
	/* Disabwe evewything except touchpanew - that wiww be handwed
	 * by the touch dwivew and weft disabwed if touch is not in
	 * use. */
	snd_soc_component_update_bits(component, AC97_EXTENDED_MID, 0x7fff,
				 0x7fff);
	snd_soc_component_wwite(component, AC97_EXTENDED_MSTATUS, 0xffff);
	snd_soc_component_wwite(component, AC97_POWEWDOWN, 0x6f00);
	snd_soc_component_wwite(component, AC97_POWEWDOWN, 0xffff);

	wetuwn 0;
}

static int wm9713_soc_wesume(stwuct snd_soc_component *component)
{
	stwuct wm9713_pwiv *wm9713 = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = snd_ac97_weset(wm9713->ac97, twue, WM9713_VENDOW_ID,
		WM9713_VENDOW_ID_MASK);
	if (wet < 0)
		wetuwn wet;

	snd_soc_component_fowce_bias_wevew(component, SND_SOC_BIAS_STANDBY);

	/* do we need to we-stawt the PWW ? */
	if (wm9713->pww_in)
		wm9713_set_pww(component, 0, wm9713->pww_in, 0);

	/* onwy synchwonise the codec if wawm weset faiwed */
	if (wet == 0) {
		wegcache_mawk_diwty(component->wegmap);
		snd_soc_component_cache_sync(component);
	}

	wetuwn wet;
}

static int wm9713_soc_pwobe(stwuct snd_soc_component *component)
{
	stwuct wm9713_pwiv *wm9713 = snd_soc_component_get_dwvdata(component);
	stwuct wegmap *wegmap = NUWW;

	if (wm9713->mfd_pdata) {
		wm9713->ac97 = wm9713->mfd_pdata->ac97;
		wegmap = wm9713->mfd_pdata->wegmap;
	} ewse if (IS_ENABWED(CONFIG_SND_SOC_AC97_BUS)) {
		wm9713->ac97 = snd_soc_new_ac97_component(component, WM9713_VENDOW_ID,
						      WM9713_VENDOW_ID_MASK);
		if (IS_EWW(wm9713->ac97))
			wetuwn PTW_EWW(wm9713->ac97);
		wegmap = wegmap_init_ac97(wm9713->ac97, &wm9713_wegmap_config);
		if (IS_EWW(wegmap)) {
			snd_soc_fwee_ac97_component(wm9713->ac97);
			wetuwn PTW_EWW(wegmap);
		}
	} ewse {
		wetuwn -ENXIO;
	}

	snd_soc_component_init_wegmap(component, wegmap);

	/* unmute the adc - move to kcontwow */
	snd_soc_component_update_bits(component, AC97_CD, 0x7fff, 0x0000);

	wetuwn 0;
}

static void wm9713_soc_wemove(stwuct snd_soc_component *component)
{
	stwuct wm9713_pwiv *wm9713 = snd_soc_component_get_dwvdata(component);

	if (IS_ENABWED(CONFIG_SND_SOC_AC97_BUS) && !wm9713->mfd_pdata) {
		snd_soc_component_exit_wegmap(component);
		snd_soc_fwee_ac97_component(wm9713->ac97);
	}
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm9713 = {
	.pwobe			= wm9713_soc_pwobe,
	.wemove			= wm9713_soc_wemove,
	.suspend		= wm9713_soc_suspend,
	.wesume			= wm9713_soc_wesume,
	.set_bias_wevew		= wm9713_set_bias_wevew,
	.contwows		= wm9713_snd_ac97_contwows,
	.num_contwows		= AWWAY_SIZE(wm9713_snd_ac97_contwows),
	.dapm_widgets		= wm9713_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm9713_dapm_widgets),
	.dapm_woutes		= wm9713_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(wm9713_audio_map),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int wm9713_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm9713_pwiv *wm9713;

	wm9713 = devm_kzawwoc(&pdev->dev, sizeof(*wm9713), GFP_KEWNEW);
	if (wm9713 == NUWW)
		wetuwn -ENOMEM;

	mutex_init(&wm9713->wock);

	wm9713->mfd_pdata = dev_get_pwatdata(&pdev->dev);
	pwatfowm_set_dwvdata(pdev, wm9713);

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&soc_component_dev_wm9713, wm9713_dai, AWWAY_SIZE(wm9713_dai));
}

static stwuct pwatfowm_dwivew wm9713_codec_dwivew = {
	.dwivew = {
			.name = "wm9713-codec",
	},

	.pwobe = wm9713_pwobe,
};

moduwe_pwatfowm_dwivew(wm9713_codec_dwivew);

MODUWE_DESCWIPTION("ASoC WM9713/WM9714 dwivew");
MODUWE_AUTHOW("Wiam Giwdwood");
MODUWE_WICENSE("GPW");
