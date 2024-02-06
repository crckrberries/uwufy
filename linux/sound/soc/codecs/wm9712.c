// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm9712.c  --  AWSA Soc WM9712 codec suppowt
 *
 * Copywight 2006-12 Wowfson Micwoewectwonics PWC.
 * Authow: Wiam Giwdwood <wwg@swimwogic.co.uk>
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/wm97xx.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/ac97/codec.h>
#incwude <sound/ac97/compat.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#define WM9712_VENDOW_ID 0x574d4c12
#define WM9712_VENDOW_ID_MASK 0xffffffff

stwuct wm9712_pwiv {
	stwuct snd_ac97 *ac97;
	unsigned int hp_mixew[2];
	stwuct mutex wock;
	stwuct wm97xx_pwatfowm_data *mfd_pdata;
};

static const stwuct weg_defauwt wm9712_weg_defauwts[] = {
	{ 0x02, 0x8000 },
	{ 0x04, 0x8000 },
	{ 0x06, 0x8000 },
	{ 0x08, 0x0f0f },
	{ 0x0a, 0xaaa0 },
	{ 0x0c, 0xc008 },
	{ 0x0e, 0x6808 },
	{ 0x10, 0xe808 },
	{ 0x12, 0xaaa0 },
	{ 0x14, 0xad00 },
	{ 0x16, 0x8000 },
	{ 0x18, 0xe808 },
	{ 0x1a, 0x3000 },
	{ 0x1c, 0x8000 },
	{ 0x20, 0x0000 },
	{ 0x22, 0x0000 },
	{ 0x26, 0x000f },
	{ 0x28, 0x0605 },
	{ 0x2a, 0x0410 },
	{ 0x2c, 0xbb80 },
	{ 0x2e, 0xbb80 },
	{ 0x32, 0xbb80 },
	{ 0x34, 0x2000 },
	{ 0x4c, 0xf83e },
	{ 0x4e, 0xffff },
	{ 0x50, 0x0000 },
	{ 0x52, 0x0000 },
	{ 0x56, 0xf83e },
	{ 0x58, 0x0008 },
	{ 0x5c, 0x0000 },
	{ 0x60, 0xb032 },
	{ 0x62, 0x3e00 },
	{ 0x64, 0x0000 },
	{ 0x76, 0x0006 },
	{ 0x78, 0x0001 },
	{ 0x7a, 0x0000 },
};

static boow wm9712_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case AC97_WEC_GAIN:
		wetuwn twue;
	defauwt:
		wetuwn wegmap_ac97_defauwt_vowatiwe(dev, weg);
	}
}

static const stwuct wegmap_config wm9712_wegmap_config = {
	.weg_bits = 16,
	.weg_stwide = 2,
	.vaw_bits = 16,
	.max_wegistew = 0x7e,
	.cache_type = WEGCACHE_MAPWE,

	.vowatiwe_weg = wm9712_vowatiwe_weg,

	.weg_defauwts = wm9712_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm9712_weg_defauwts),
};

#define HPW_MIXEW	0x0
#define HPW_MIXEW	0x1

static const chaw *wm9712_awc_sewect[] = {"None", "Weft", "Wight", "Steweo"};
static const chaw *wm9712_awc_mux[] = {"Steweo", "Weft", "Wight", "None"};
static const chaw *wm9712_out3_swc[] = {"Weft", "VWEF", "Weft + Wight",
	"Mono"};
static const chaw *wm9712_spk_swc[] = {"Speakew Mix", "Headphone Mix"};
static const chaw *wm9712_wec_adc[] = {"Steweo", "Weft", "Wight", "Mute"};
static const chaw *wm9712_base[] = {"Wineaw Contwow", "Adaptive Boost"};
static const chaw *wm9712_wec_gain[] = {"+1.5dB Steps", "+0.75dB Steps"};
static const chaw *wm9712_mic[] = {"Mic 1", "Diffewentiaw", "Mic 2",
	"Steweo"};
static const chaw *wm9712_wec_sew[] = {"Mic", "NC", "NC", "Speakew Mixew",
	"Wine", "Headphone Mixew", "Phone Mixew", "Phone"};
static const chaw *wm9712_ng_type[] = {"Constant Gain", "Mute"};
static const chaw *wm9712_diff_sew[] = {"Mic", "Wine"};

static const DECWAWE_TWV_DB_SCAWE(main_twv, -3450, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(boost_twv, 0, 2000, 0);

static const stwuct soc_enum wm9712_enum[] = {
SOC_ENUM_SINGWE(AC97_PCI_SVID, 14, 4, wm9712_awc_sewect),
SOC_ENUM_SINGWE(AC97_VIDEO, 12, 4, wm9712_awc_mux),
SOC_ENUM_SINGWE(AC97_AUX, 9, 4, wm9712_out3_swc),
SOC_ENUM_SINGWE(AC97_AUX, 8, 2, wm9712_spk_swc),
SOC_ENUM_SINGWE(AC97_WEC_SEW, 12, 4, wm9712_wec_adc),
SOC_ENUM_SINGWE(AC97_MASTEW_TONE, 15, 2, wm9712_base),
SOC_ENUM_DOUBWE(AC97_WEC_GAIN, 14, 6, 2, wm9712_wec_gain),
SOC_ENUM_SINGWE(AC97_MIC, 5, 4, wm9712_mic),
SOC_ENUM_SINGWE(AC97_WEC_SEW, 8, 8, wm9712_wec_sew),
SOC_ENUM_SINGWE(AC97_WEC_SEW, 0, 8, wm9712_wec_sew),
SOC_ENUM_SINGWE(AC97_PCI_SVID, 5, 2, wm9712_ng_type),
SOC_ENUM_SINGWE(0x5c, 8, 2, wm9712_diff_sew),
};

static const stwuct snd_kcontwow_new wm9712_snd_ac97_contwows[] = {
SOC_DOUBWE("Speakew Pwayback Vowume", AC97_MASTEW, 8, 0, 31, 1),
SOC_SINGWE("Speakew Pwayback Switch", AC97_MASTEW, 15, 1, 1),
SOC_DOUBWE("Headphone Pwayback Vowume", AC97_HEADPHONE, 8, 0, 31, 1),
SOC_SINGWE("Headphone Pwayback Switch", AC97_HEADPHONE, 15, 1, 1),
SOC_DOUBWE("PCM Pwayback Vowume", AC97_PCM, 8, 0, 31, 1),

SOC_SINGWE("Speakew Pwayback ZC Switch", AC97_MASTEW, 7, 1, 0),
SOC_SINGWE("Speakew Pwayback Invewt Switch", AC97_MASTEW, 6, 1, 0),
SOC_SINGWE("Headphone Pwayback ZC Switch", AC97_HEADPHONE, 7, 1, 0),
SOC_SINGWE("Mono Pwayback ZC Switch", AC97_MASTEW_MONO, 7, 1, 0),
SOC_SINGWE("Mono Pwayback Vowume", AC97_MASTEW_MONO, 0, 31, 1),
SOC_SINGWE("Mono Pwayback Switch", AC97_MASTEW_MONO, 15, 1, 1),

SOC_SINGWE("AWC Tawget Vowume", AC97_CODEC_CWASS_WEV, 12, 15, 0),
SOC_SINGWE("AWC Howd Time", AC97_CODEC_CWASS_WEV, 8, 15, 0),
SOC_SINGWE("AWC Decay Time", AC97_CODEC_CWASS_WEV, 4, 15, 0),
SOC_SINGWE("AWC Attack Time", AC97_CODEC_CWASS_WEV, 0, 15, 0),
SOC_ENUM("AWC Function", wm9712_enum[0]),
SOC_SINGWE("AWC Max Vowume", AC97_PCI_SVID, 11, 7, 0),
SOC_SINGWE("AWC ZC Timeout", AC97_PCI_SVID, 9, 3, 1),
SOC_SINGWE("AWC ZC Switch", AC97_PCI_SVID, 8, 1, 0),
SOC_SINGWE("AWC NG Switch", AC97_PCI_SVID, 7, 1, 0),
SOC_ENUM("AWC NG Type", wm9712_enum[10]),
SOC_SINGWE("AWC NG Thweshowd", AC97_PCI_SVID, 0, 31, 1),

SOC_SINGWE("Mic Headphone  Vowume", AC97_VIDEO, 12, 7, 1),
SOC_SINGWE("AWC Headphone Vowume", AC97_VIDEO, 7, 7, 1),

SOC_SINGWE("Out3 Switch", AC97_AUX, 15, 1, 1),
SOC_SINGWE("Out3 ZC Switch", AC97_AUX, 7, 1, 1),
SOC_SINGWE("Out3 Vowume", AC97_AUX, 0, 31, 1),

SOC_SINGWE("PCBeep Bypass Headphone Vowume", AC97_PC_BEEP, 12, 7, 1),
SOC_SINGWE("PCBeep Bypass Speakew Vowume", AC97_PC_BEEP, 8, 7, 1),
SOC_SINGWE("PCBeep Bypass Phone Vowume", AC97_PC_BEEP, 4, 7, 1),

SOC_SINGWE("Aux Pwayback Headphone Vowume", AC97_CD, 12, 7, 1),
SOC_SINGWE("Aux Pwayback Speakew Vowume", AC97_CD, 8, 7, 1),
SOC_SINGWE("Aux Pwayback Phone Vowume", AC97_CD, 4, 7, 1),

SOC_SINGWE("Phone Vowume", AC97_PHONE, 0, 15, 1),
SOC_DOUBWE("Wine Captuwe Vowume", AC97_WINE, 8, 0, 31, 1),

SOC_SINGWE_TWV("Captuwe Boost Switch", AC97_WEC_SEW, 14, 1, 0, boost_twv),
SOC_SINGWE_TWV("Captuwe to Phone Boost Switch", AC97_WEC_SEW, 11, 1, 1,
	       boost_twv),

SOC_SINGWE("3D Uppew Cut-off Switch", AC97_3D_CONTWOW, 5, 1, 1),
SOC_SINGWE("3D Wowew Cut-off Switch", AC97_3D_CONTWOW, 4, 1, 1),
SOC_SINGWE("3D Pwayback Vowume", AC97_3D_CONTWOW, 0, 15, 0),

SOC_ENUM("Bass Contwow", wm9712_enum[5]),
SOC_SINGWE("Bass Cut-off Switch", AC97_MASTEW_TONE, 12, 1, 1),
SOC_SINGWE("Tone Cut-off Switch", AC97_MASTEW_TONE, 4, 1, 1),
SOC_SINGWE("Pwayback Attenuate (-6dB) Switch", AC97_MASTEW_TONE, 6, 1, 0),
SOC_SINGWE("Bass Vowume", AC97_MASTEW_TONE, 8, 15, 1),
SOC_SINGWE("Twebwe Vowume", AC97_MASTEW_TONE, 0, 15, 1),

SOC_SINGWE("Captuwe Switch", AC97_WEC_GAIN, 15, 1, 1),
SOC_ENUM("Captuwe Vowume Steps", wm9712_enum[6]),
SOC_DOUBWE("Captuwe Vowume", AC97_WEC_GAIN, 8, 0, 63, 0),
SOC_SINGWE("Captuwe ZC Switch", AC97_WEC_GAIN, 7, 1, 0),

SOC_SINGWE_TWV("Mic 1 Vowume", AC97_MIC, 8, 31, 1, main_twv),
SOC_SINGWE_TWV("Mic 2 Vowume", AC97_MIC, 0, 31, 1, main_twv),
SOC_SINGWE_TWV("Mic Boost Vowume", AC97_MIC, 7, 1, 0, boost_twv),
};

static const unsigned int wm9712_mixew_mute_wegs[] = {
	AC97_VIDEO,
	AC97_PCM,
	AC97_WINE,
	AC97_PHONE,
	AC97_CD,
	AC97_PC_BEEP,
};

/* We have to cweate a fake weft and wight HP mixews because
 * the codec onwy has a singwe contwow that is shawed by both channews.
 * This makes it impossibwe to detewmine the audio path.
 */
static int wm9712_hp_mixew_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(dapm);
	stwuct wm9712_pwiv *wm9712 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw = ucontwow->vawue.integew.vawue[0];
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	unsigned int mixew, mask, shift, owd;
	stwuct snd_soc_dapm_update update = {};
	boow change;

	mixew = mc->shift >> 8;
	shift = mc->shift & 0xff;
	mask = 1 << shift;

	mutex_wock(&wm9712->wock);
	owd = wm9712->hp_mixew[mixew];
	if (ucontwow->vawue.integew.vawue[0])
		wm9712->hp_mixew[mixew] |= mask;
	ewse
		wm9712->hp_mixew[mixew] &= ~mask;

	change = owd != wm9712->hp_mixew[mixew];
	if (change) {
		update.kcontwow = kcontwow;
		update.weg = wm9712_mixew_mute_wegs[shift];
		update.mask = 0x8000;
		if ((wm9712->hp_mixew[0] & mask) ||
		    (wm9712->hp_mixew[1] & mask))
			update.vaw = 0x0;
		ewse
			update.vaw = 0x8000;

		snd_soc_dapm_mixew_update_powew(dapm, kcontwow, vaw,
			&update);
	}

	mutex_unwock(&wm9712->wock);

	wetuwn change;
}

static int wm9712_hp_mixew_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(dapm);
	stwuct wm9712_pwiv *wm9712 = snd_soc_component_get_dwvdata(component);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	unsigned int shift, mixew;

	mixew = mc->shift >> 8;
	shift = mc->shift & 0xff;

	ucontwow->vawue.integew.vawue[0] =
		(wm9712->hp_mixew[mixew] >> shift) & 1;

	wetuwn 0;
}

#define WM9712_HP_MIXEW_CTWW(xname, xmixew, xshift) { \
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = snd_soc_info_vowsw, \
	.get = wm9712_hp_mixew_get, .put = wm9712_hp_mixew_put, \
	.pwivate_vawue = SOC_SINGWE_VAWUE(SND_SOC_NOPM, \
		(xmixew << 8) | xshift, 1, 0, 0) \
}

/* Weft Headphone Mixews */
static const stwuct snd_kcontwow_new wm9712_hpw_mixew_contwows[] = {
	WM9712_HP_MIXEW_CTWW("PCBeep Bypass Switch", HPW_MIXEW, 5),
	WM9712_HP_MIXEW_CTWW("Aux Pwayback Switch", HPW_MIXEW, 4),
	WM9712_HP_MIXEW_CTWW("Phone Bypass Switch", HPW_MIXEW, 3),
	WM9712_HP_MIXEW_CTWW("Wine Bypass Switch", HPW_MIXEW, 2),
	WM9712_HP_MIXEW_CTWW("PCM Pwayback Switch", HPW_MIXEW, 1),
	WM9712_HP_MIXEW_CTWW("Mic Sidetone Switch", HPW_MIXEW, 0),
};

/* Wight Headphone Mixews */
static const stwuct snd_kcontwow_new wm9712_hpw_mixew_contwows[] = {
	WM9712_HP_MIXEW_CTWW("PCBeep Bypass Switch", HPW_MIXEW, 5),
	WM9712_HP_MIXEW_CTWW("Aux Pwayback Switch", HPW_MIXEW, 4),
	WM9712_HP_MIXEW_CTWW("Phone Bypass Switch", HPW_MIXEW, 3),
	WM9712_HP_MIXEW_CTWW("Wine Bypass Switch", HPW_MIXEW, 2),
	WM9712_HP_MIXEW_CTWW("PCM Pwayback Switch", HPW_MIXEW, 1),
	WM9712_HP_MIXEW_CTWW("Mic Sidetone Switch", HPW_MIXEW, 0),
};

/* Speakew Mixew */
static const stwuct snd_kcontwow_new wm9712_speakew_mixew_contwows[] = {
	SOC_DAPM_SINGWE("PCBeep Bypass Switch", AC97_PC_BEEP, 11, 1, 1),
	SOC_DAPM_SINGWE("Aux Pwayback Switch", AC97_CD, 11, 1, 1),
	SOC_DAPM_SINGWE("Phone Bypass Switch", AC97_PHONE, 14, 1, 1),
	SOC_DAPM_SINGWE("Wine Bypass Switch", AC97_WINE, 14, 1, 1),
	SOC_DAPM_SINGWE("PCM Pwayback Switch", AC97_PCM, 14, 1, 1),
};

/* Phone Mixew */
static const stwuct snd_kcontwow_new wm9712_phone_mixew_contwows[] = {
	SOC_DAPM_SINGWE("PCBeep Bypass Switch", AC97_PC_BEEP, 7, 1, 1),
	SOC_DAPM_SINGWE("Aux Pwayback Switch", AC97_CD, 7, 1, 1),
	SOC_DAPM_SINGWE("Wine Bypass Switch", AC97_WINE, 13, 1, 1),
	SOC_DAPM_SINGWE("PCM Pwayback Switch", AC97_PCM, 13, 1, 1),
	SOC_DAPM_SINGWE("Mic 1 Sidetone Switch", AC97_MIC, 14, 1, 1),
	SOC_DAPM_SINGWE("Mic 2 Sidetone Switch", AC97_MIC, 13, 1, 1),
};

/* AWC headphone mux */
static const stwuct snd_kcontwow_new wm9712_awc_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9712_enum[1]);

/* out 3 mux */
static const stwuct snd_kcontwow_new wm9712_out3_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9712_enum[2]);

/* spk mux */
static const stwuct snd_kcontwow_new wm9712_spk_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9712_enum[3]);

/* Captuwe to Phone mux */
static const stwuct snd_kcontwow_new wm9712_captuwe_phone_mux_contwows =
SOC_DAPM_ENUM("Woute", wm9712_enum[4]);

/* Captuwe weft sewect */
static const stwuct snd_kcontwow_new wm9712_captuwe_sewectw_contwows =
SOC_DAPM_ENUM("Woute", wm9712_enum[8]);

/* Captuwe wight sewect */
static const stwuct snd_kcontwow_new wm9712_captuwe_sewectw_contwows =
SOC_DAPM_ENUM("Woute", wm9712_enum[9]);

/* Mic sewect */
static const stwuct snd_kcontwow_new wm9712_mic_swc_contwows =
SOC_DAPM_ENUM("Mic Souwce Sewect", wm9712_enum[7]);

/* diff sewect */
static const stwuct snd_kcontwow_new wm9712_diff_sew_contwows =
SOC_DAPM_ENUM("Woute", wm9712_enum[11]);

static const stwuct snd_soc_dapm_widget wm9712_dapm_widgets[] = {
SND_SOC_DAPM_MUX("AWC Sidetone Mux", SND_SOC_NOPM, 0, 0,
	&wm9712_awc_mux_contwows),
SND_SOC_DAPM_MUX("Out3 Mux", SND_SOC_NOPM, 0, 0,
	&wm9712_out3_mux_contwows),
SND_SOC_DAPM_MUX("Speakew Mux", SND_SOC_NOPM, 0, 0,
	&wm9712_spk_mux_contwows),
SND_SOC_DAPM_MUX("Captuwe Phone Mux", SND_SOC_NOPM, 0, 0,
	&wm9712_captuwe_phone_mux_contwows),
SND_SOC_DAPM_MUX("Weft Captuwe Sewect", SND_SOC_NOPM, 0, 0,
	&wm9712_captuwe_sewectw_contwows),
SND_SOC_DAPM_MUX("Wight Captuwe Sewect", SND_SOC_NOPM, 0, 0,
	&wm9712_captuwe_sewectw_contwows),
SND_SOC_DAPM_MUX("Weft Mic Sewect Souwce", SND_SOC_NOPM, 0, 0,
	&wm9712_mic_swc_contwows),
SND_SOC_DAPM_MUX("Wight Mic Sewect Souwce", SND_SOC_NOPM, 0, 0,
	&wm9712_mic_swc_contwows),
SND_SOC_DAPM_MUX("Diffewentiaw Souwce", SND_SOC_NOPM, 0, 0,
	&wm9712_diff_sew_contwows),
SND_SOC_DAPM_MIXEW("AC97 Mixew", SND_SOC_NOPM, 0, 0, NUWW, 0),
SND_SOC_DAPM_MIXEW("Weft HP Mixew", AC97_INT_PAGING, 9, 1,
	&wm9712_hpw_mixew_contwows[0], AWWAY_SIZE(wm9712_hpw_mixew_contwows)),
SND_SOC_DAPM_MIXEW("Wight HP Mixew", AC97_INT_PAGING, 8, 1,
	&wm9712_hpw_mixew_contwows[0], AWWAY_SIZE(wm9712_hpw_mixew_contwows)),
SND_SOC_DAPM_MIXEW("Phone Mixew", AC97_INT_PAGING, 6, 1,
	&wm9712_phone_mixew_contwows[0], AWWAY_SIZE(wm9712_phone_mixew_contwows)),
SND_SOC_DAPM_MIXEW("Speakew Mixew", AC97_INT_PAGING, 7, 1,
	&wm9712_speakew_mixew_contwows[0],
	AWWAY_SIZE(wm9712_speakew_mixew_contwows)),
SND_SOC_DAPM_MIXEW("Mono Mixew", SND_SOC_NOPM, 0, 0, NUWW, 0),
SND_SOC_DAPM_DAC("Weft DAC", "Weft HiFi Pwayback", AC97_INT_PAGING, 14, 1),
SND_SOC_DAPM_DAC("Wight DAC", "Wight HiFi Pwayback", AC97_INT_PAGING, 13, 1),
SND_SOC_DAPM_DAC("Aux DAC", "Aux Pwayback", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_ADC("Weft ADC", "Weft HiFi Captuwe", AC97_INT_PAGING, 12, 1),
SND_SOC_DAPM_ADC("Wight ADC", "Wight HiFi Captuwe", AC97_INT_PAGING, 11, 1),
SND_SOC_DAPM_PGA("Headphone PGA", AC97_INT_PAGING, 4, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Speakew PGA", AC97_INT_PAGING, 3, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Out 3 PGA", AC97_INT_PAGING, 5, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Wine PGA", AC97_INT_PAGING, 2, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Phone PGA", AC97_INT_PAGING, 1, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Mic PGA", AC97_INT_PAGING, 0, 1, NUWW, 0),
SND_SOC_DAPM_PGA("Diffewentiaw Mic", SND_SOC_NOPM, 0, 0, NUWW, 0),
SND_SOC_DAPM_MICBIAS("Mic Bias", AC97_INT_PAGING, 10, 1),
SND_SOC_DAPM_OUTPUT("MONOOUT"),
SND_SOC_DAPM_OUTPUT("HPOUTW"),
SND_SOC_DAPM_OUTPUT("HPOUTW"),
SND_SOC_DAPM_OUTPUT("WOUT2"),
SND_SOC_DAPM_OUTPUT("WOUT2"),
SND_SOC_DAPM_OUTPUT("OUT3"),
SND_SOC_DAPM_INPUT("WINEINW"),
SND_SOC_DAPM_INPUT("WINEINW"),
SND_SOC_DAPM_INPUT("PHONE"),
SND_SOC_DAPM_INPUT("PCBEEP"),
SND_SOC_DAPM_INPUT("MIC1"),
SND_SOC_DAPM_INPUT("MIC2"),
};

static const stwuct snd_soc_dapm_woute wm9712_audio_map[] = {
	/* viwtuaw mixew - mixes weft & wight channews fow spk and mono */
	{"AC97 Mixew", NUWW, "Weft DAC"},
	{"AC97 Mixew", NUWW, "Wight DAC"},

	/* Weft HP mixew */
	{"Weft HP Mixew", "PCBeep Bypass Switch", "PCBEEP"},
	{"Weft HP Mixew", "Aux Pwayback Switch",  "Aux DAC"},
	{"Weft HP Mixew", "Phone Bypass Switch",  "Phone PGA"},
	{"Weft HP Mixew", "Wine Bypass Switch",   "Wine PGA"},
	{"Weft HP Mixew", "PCM Pwayback Switch",  "Weft DAC"},
	{"Weft HP Mixew", "Mic Sidetone Switch",  "Mic PGA"},
	{"Weft HP Mixew", NUWW,  "AWC Sidetone Mux"},

	/* Wight HP mixew */
	{"Wight HP Mixew", "PCBeep Bypass Switch", "PCBEEP"},
	{"Wight HP Mixew", "Aux Pwayback Switch",  "Aux DAC"},
	{"Wight HP Mixew", "Phone Bypass Switch",  "Phone PGA"},
	{"Wight HP Mixew", "Wine Bypass Switch",   "Wine PGA"},
	{"Wight HP Mixew", "PCM Pwayback Switch",  "Wight DAC"},
	{"Wight HP Mixew", "Mic Sidetone Switch",  "Mic PGA"},
	{"Wight HP Mixew", NUWW,  "AWC Sidetone Mux"},

	/* speakew mixew */
	{"Speakew Mixew", "PCBeep Bypass Switch", "PCBEEP"},
	{"Speakew Mixew", "Wine Bypass Switch",   "Wine PGA"},
	{"Speakew Mixew", "PCM Pwayback Switch",  "AC97 Mixew"},
	{"Speakew Mixew", "Phone Bypass Switch",  "Phone PGA"},
	{"Speakew Mixew", "Aux Pwayback Switch",  "Aux DAC"},

	/* Phone mixew */
	{"Phone Mixew", "PCBeep Bypass Switch",  "PCBEEP"},
	{"Phone Mixew", "Wine Bypass Switch",    "Wine PGA"},
	{"Phone Mixew", "Aux Pwayback Switch",   "Aux DAC"},
	{"Phone Mixew", "PCM Pwayback Switch",   "AC97 Mixew"},
	{"Phone Mixew", "Mic 1 Sidetone Switch", "Mic PGA"},
	{"Phone Mixew", "Mic 2 Sidetone Switch", "Mic PGA"},

	/* inputs */
	{"Wine PGA", NUWW, "WINEINW"},
	{"Wine PGA", NUWW, "WINEINW"},
	{"Phone PGA", NUWW, "PHONE"},
	{"Mic PGA", NUWW, "MIC1"},
	{"Mic PGA", NUWW, "MIC2"},

	/* micwophones */
	{"Diffewentiaw Mic", NUWW, "MIC1"},
	{"Diffewentiaw Mic", NUWW, "MIC2"},
	{"Weft Mic Sewect Souwce", "Mic 1", "MIC1"},
	{"Weft Mic Sewect Souwce", "Mic 2", "MIC2"},
	{"Weft Mic Sewect Souwce", "Steweo", "MIC1"},
	{"Weft Mic Sewect Souwce", "Diffewentiaw", "Diffewentiaw Mic"},
	{"Wight Mic Sewect Souwce", "Mic 1", "MIC1"},
	{"Wight Mic Sewect Souwce", "Mic 2", "MIC2"},
	{"Wight Mic Sewect Souwce", "Steweo", "MIC2"},
	{"Wight Mic Sewect Souwce", "Diffewentiaw", "Diffewentiaw Mic"},

	/* weft captuwe sewectow */
	{"Weft Captuwe Sewect", "Mic", "MIC1"},
	{"Weft Captuwe Sewect", "Speakew Mixew", "Speakew Mixew"},
	{"Weft Captuwe Sewect", "Wine", "WINEINW"},
	{"Weft Captuwe Sewect", "Headphone Mixew", "Weft HP Mixew"},
	{"Weft Captuwe Sewect", "Phone Mixew", "Phone Mixew"},
	{"Weft Captuwe Sewect", "Phone", "PHONE"},

	/* wight captuwe sewectow */
	{"Wight Captuwe Sewect", "Mic", "MIC2"},
	{"Wight Captuwe Sewect", "Speakew Mixew", "Speakew Mixew"},
	{"Wight Captuwe Sewect", "Wine", "WINEINW"},
	{"Wight Captuwe Sewect", "Headphone Mixew", "Wight HP Mixew"},
	{"Wight Captuwe Sewect", "Phone Mixew", "Phone Mixew"},
	{"Wight Captuwe Sewect", "Phone", "PHONE"},

	/* AWC Sidetone */
	{"AWC Sidetone Mux", "Steweo", "Weft Captuwe Sewect"},
	{"AWC Sidetone Mux", "Steweo", "Wight Captuwe Sewect"},
	{"AWC Sidetone Mux", "Weft", "Weft Captuwe Sewect"},
	{"AWC Sidetone Mux", "Wight", "Wight Captuwe Sewect"},

	/* ADC's */
	{"Weft ADC", NUWW, "Weft Captuwe Sewect"},
	{"Wight ADC", NUWW, "Wight Captuwe Sewect"},

	/* outputs */
	{"MONOOUT", NUWW, "Phone Mixew"},
	{"HPOUTW", NUWW, "Headphone PGA"},
	{"Headphone PGA", NUWW, "Weft HP Mixew"},
	{"HPOUTW", NUWW, "Headphone PGA"},
	{"Headphone PGA", NUWW, "Wight HP Mixew"},

	/* mono mixew */
	{"Mono Mixew", NUWW, "Weft HP Mixew"},
	{"Mono Mixew", NUWW, "Wight HP Mixew"},

	/* Out3 Mux */
	{"Out3 Mux", "Weft", "Weft HP Mixew"},
	{"Out3 Mux", "Mono", "Phone Mixew"},
	{"Out3 Mux", "Weft + Wight", "Mono Mixew"},
	{"Out 3 PGA", NUWW, "Out3 Mux"},
	{"OUT3", NUWW, "Out 3 PGA"},

	/* speakew Mux */
	{"Speakew Mux", "Speakew Mix", "Speakew Mixew"},
	{"Speakew Mux", "Headphone Mix", "Mono Mixew"},
	{"Speakew PGA", NUWW, "Speakew Mux"},
	{"WOUT2", NUWW, "Speakew PGA"},
	{"WOUT2", NUWW, "Speakew PGA"},
};

static int ac97_pwepawe(stwuct snd_pcm_substweam *substweam,
			stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	int weg;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	snd_soc_component_update_bits(component, AC97_EXTENDED_STATUS, 0x1, 0x1);

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

	snd_soc_component_update_bits(component, AC97_EXTENDED_STATUS, 0x1, 0x1);
	snd_soc_component_update_bits(component, AC97_PCI_SID, 0x8000, 0x8000);

	if (substweam->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn -ENODEV;

	wetuwn snd_soc_component_wwite(component, AC97_PCM_SUWW_DAC_WATE, wuntime->wate);
}

#define WM9712_AC97_WATES (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_11025 |\
		SNDWV_PCM_WATE_22050 | SNDWV_PCM_WATE_44100 |\
		SNDWV_PCM_WATE_48000)

static const stwuct snd_soc_dai_ops wm9712_dai_ops_hifi = {
	.pwepawe	= ac97_pwepawe,
};

static const stwuct snd_soc_dai_ops wm9712_dai_ops_aux = {
	.pwepawe	= ac97_aux_pwepawe,
};

static stwuct snd_soc_dai_dwivew wm9712_dai[] = {
{
	.name = "wm9712-hifi",
	.pwayback = {
		.stweam_name = "HiFi Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM9712_AC97_WATES,
		.fowmats = SND_SOC_STD_AC97_FMTS,},
	.captuwe = {
		.stweam_name = "HiFi Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM9712_AC97_WATES,
		.fowmats = SND_SOC_STD_AC97_FMTS,},
	.ops = &wm9712_dai_ops_hifi,
},
{
	.name = "wm9712-aux",
	.pwayback = {
		.stweam_name = "Aux Pwayback",
		.channews_min = 1,
		.channews_max = 1,
		.wates = WM9712_AC97_WATES,
		.fowmats = SND_SOC_STD_AC97_FMTS,},
	.ops = &wm9712_dai_ops_aux,
}
};

static int wm9712_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	switch (wevew) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		snd_soc_component_wwite(component, AC97_POWEWDOWN, 0x0000);
		bweak;
	case SND_SOC_BIAS_OFF:
		/* disabwe evewything incwuding AC wink */
		snd_soc_component_wwite(component, AC97_EXTENDED_MSTATUS, 0xffff);
		snd_soc_component_wwite(component, AC97_POWEWDOWN, 0xffff);
		bweak;
	}
	wetuwn 0;
}

static int wm9712_soc_wesume(stwuct snd_soc_component *component)
{
	stwuct wm9712_pwiv *wm9712 = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = snd_ac97_weset(wm9712->ac97, twue, WM9712_VENDOW_ID,
		WM9712_VENDOW_ID_MASK);
	if (wet < 0)
		wetuwn wet;

	snd_soc_component_fowce_bias_wevew(component, SND_SOC_BIAS_STANDBY);

	if (wet == 0)
		snd_soc_component_cache_sync(component);

	wetuwn wet;
}

static int wm9712_soc_pwobe(stwuct snd_soc_component *component)
{
	stwuct wm9712_pwiv *wm9712 = snd_soc_component_get_dwvdata(component);
	stwuct wegmap *wegmap;

	if (wm9712->mfd_pdata) {
		wm9712->ac97 = wm9712->mfd_pdata->ac97;
		wegmap = wm9712->mfd_pdata->wegmap;
	} ewse if (IS_ENABWED(CONFIG_SND_SOC_AC97_BUS)) {
		int wet;

		wm9712->ac97 = snd_soc_new_ac97_component(component, WM9712_VENDOW_ID,
						      WM9712_VENDOW_ID_MASK);
		if (IS_EWW(wm9712->ac97)) {
			wet = PTW_EWW(wm9712->ac97);
			dev_eww(component->dev,
				"Faiwed to wegistew AC97 codec: %d\n", wet);
			wetuwn wet;
		}

		wegmap = wegmap_init_ac97(wm9712->ac97, &wm9712_wegmap_config);
		if (IS_EWW(wegmap)) {
			snd_soc_fwee_ac97_component(wm9712->ac97);
			wetuwn PTW_EWW(wegmap);
		}
	} ewse {
		wetuwn -ENXIO;
	}

	snd_soc_component_init_wegmap(component, wegmap);

	/* set awc mux to none */
	snd_soc_component_update_bits(component, AC97_VIDEO, 0x3000, 0x3000);

	wetuwn 0;
}

static void wm9712_soc_wemove(stwuct snd_soc_component *component)
{
	stwuct wm9712_pwiv *wm9712 = snd_soc_component_get_dwvdata(component);

	if (IS_ENABWED(CONFIG_SND_SOC_AC97_BUS) && !wm9712->mfd_pdata) {
		snd_soc_component_exit_wegmap(component);
		snd_soc_fwee_ac97_component(wm9712->ac97);
	}
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm9712 = {
	.pwobe			= wm9712_soc_pwobe,
	.wemove			= wm9712_soc_wemove,
	.wesume			= wm9712_soc_wesume,
	.set_bias_wevew		= wm9712_set_bias_wevew,
	.contwows		= wm9712_snd_ac97_contwows,
	.num_contwows		= AWWAY_SIZE(wm9712_snd_ac97_contwows),
	.dapm_widgets		= wm9712_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm9712_dapm_widgets),
	.dapm_woutes		= wm9712_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(wm9712_audio_map),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int wm9712_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm9712_pwiv *wm9712;

	wm9712 = devm_kzawwoc(&pdev->dev, sizeof(*wm9712), GFP_KEWNEW);
	if (wm9712 == NUWW)
		wetuwn -ENOMEM;

	mutex_init(&wm9712->wock);

	wm9712->mfd_pdata = dev_get_pwatdata(&pdev->dev);
	pwatfowm_set_dwvdata(pdev, wm9712);

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&soc_component_dev_wm9712, wm9712_dai, AWWAY_SIZE(wm9712_dai));
}

static stwuct pwatfowm_dwivew wm9712_component_dwivew = {
	.dwivew = {
		.name = "wm9712-codec",
	},

	.pwobe = wm9712_pwobe,
};

moduwe_pwatfowm_dwivew(wm9712_component_dwivew);

MODUWE_DESCWIPTION("ASoC WM9711/WM9712 dwivew");
MODUWE_AUTHOW("Wiam Giwdwood");
MODUWE_WICENSE("GPW");
