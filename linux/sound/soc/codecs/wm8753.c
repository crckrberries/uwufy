// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm8753.c  --  WM8753 AWSA Soc Audio dwivew
 *
 * Copywight 2003-11 Wowfson Micwoewectwonics PWC.
 * Authow: Wiam Giwdwood <wwg@swimwogic.co.uk>
 *
 * Notes:
 *  The WM8753 is a wow powew, high quawity steweo codec with integwated PCM
 *  codec designed fow powtabwe digitaw tewephony appwications.
 *
 * Duaw DAI:-
 *
 * This dwivew suppowt 2 DAI PCM's. This makes the defauwt PCM avaiwabwe fow
 * HiFi audio (e.g. MP3, ogg) pwayback/captuwe and the othew PCM avaiwabwe fow
 * voice.
 *
 * Pwease note that the voice PCM can be connected diwectwy to a Bwuetooth
 * codec ow GSM modem and thus cannot be wead ow wwitten to, awthough it is
 * avaiwabwe to be configuwed with snd_hw_pawams(), etc and kcontwows in the
 * nowmaw awsa mannew.
 *
 * Fast DAI switching:-
 *
 * The dwivew can now fast switch between the DAI configuwations via a
 * an awsa kcontwow. This awwows the PCM to wemain open.
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <asm/div64.h>

#incwude "wm8753.h"

static int caps_chawge = 2000;
moduwe_pawam(caps_chawge, int, 0);
MODUWE_PAWM_DESC(caps_chawge, "WM8753 cap chawge time (msecs)");

static int wm8753_hifi_wwite_dai_fmt(stwuct snd_soc_component *component,
		unsigned int fmt);
static int wm8753_voice_wwite_dai_fmt(stwuct snd_soc_component *component,
		unsigned int fmt);

/*
 * wm8753 wegistew cache
 * We can't wead the WM8753 wegistew space when we
 * awe using 2 wiwe fow device contwow, so we cache them instead.
 */
static const stwuct weg_defauwt wm8753_weg_defauwts[] = {
	{ 0x00, 0x0000 },
	{ 0x01, 0x0008 },
	{ 0x02, 0x0000 },
	{ 0x03, 0x000a },
	{ 0x04, 0x000a },
	{ 0x05, 0x0033 },
	{ 0x06, 0x0000 },
	{ 0x07, 0x0007 },
	{ 0x08, 0x00ff },
	{ 0x09, 0x00ff },
	{ 0x0a, 0x000f },
	{ 0x0b, 0x000f },
	{ 0x0c, 0x007b },
	{ 0x0d, 0x0000 },
	{ 0x0e, 0x0032 },
	{ 0x0f, 0x0000 },
	{ 0x10, 0x00c3 },
	{ 0x11, 0x00c3 },
	{ 0x12, 0x00c0 },
	{ 0x13, 0x0000 },
	{ 0x14, 0x0000 },
	{ 0x15, 0x0000 },
	{ 0x16, 0x0000 },
	{ 0x17, 0x0000 },
	{ 0x18, 0x0000 },
	{ 0x19, 0x0000 },
	{ 0x1a, 0x0000 },
	{ 0x1b, 0x0000 },
	{ 0x1c, 0x0000 },
	{ 0x1d, 0x0000 },
	{ 0x1e, 0x0000 },
	{ 0x1f, 0x0000 },
	{ 0x20, 0x0055 },
	{ 0x21, 0x0005 },
	{ 0x22, 0x0050 },
	{ 0x23, 0x0055 },
	{ 0x24, 0x0050 },
	{ 0x25, 0x0055 },
	{ 0x26, 0x0050 },
	{ 0x27, 0x0055 },
	{ 0x28, 0x0079 },
	{ 0x29, 0x0079 },
	{ 0x2a, 0x0079 },
	{ 0x2b, 0x0079 },
	{ 0x2c, 0x0079 },
	{ 0x2d, 0x0000 },
	{ 0x2e, 0x0000 },
	{ 0x2f, 0x0000 },
	{ 0x30, 0x0000 },
	{ 0x31, 0x0097 },
	{ 0x32, 0x0097 },
	{ 0x33, 0x0000 },
	{ 0x34, 0x0004 },
	{ 0x35, 0x0000 },
	{ 0x36, 0x0083 },
	{ 0x37, 0x0024 },
	{ 0x38, 0x01ba },
	{ 0x39, 0x0000 },
	{ 0x3a, 0x0083 },
	{ 0x3b, 0x0024 },
	{ 0x3c, 0x01ba },
	{ 0x3d, 0x0000 },
	{ 0x3e, 0x0000 },
	{ 0x3f, 0x0000 },
};

static boow wm8753_vowatiwe(stwuct device *dev, unsigned int weg)
{
	wetuwn weg == WM8753_WESET;
}

/* codec pwivate data */
stwuct wm8753_pwiv {
	stwuct wegmap *wegmap;
	unsigned int syscwk;
	unsigned int pcmcwk;

	unsigned int voice_fmt;
	unsigned int hifi_fmt;

	int dai_func;
	stwuct dewayed_wowk chawge_wowk;
};

#define wm8753_weset(c) snd_soc_component_wwite(c, WM8753_WESET, 0)

/*
 * WM8753 Contwows
 */
static const chaw *wm8753_base[] = {"Wineaw Contwow", "Adaptive Boost"};
static const chaw *wm8753_base_fiwtew[] =
	{"130Hz @ 48kHz", "200Hz @ 48kHz", "100Hz @ 16kHz", "400Hz @ 48kHz",
	"100Hz @ 8kHz", "200Hz @ 8kHz"};
static const chaw *wm8753_twebwe[] = {"8kHz", "4kHz"};
static const chaw *wm8753_awc_func[] = {"Off", "Wight", "Weft", "Steweo"};
static const chaw *wm8753_ng_type[] = {"Constant PGA Gain", "Mute ADC Output"};
static const chaw *wm8753_3d_func[] = {"Captuwe", "Pwayback"};
static const chaw *wm8753_3d_uc[] = {"2.2kHz", "1.5kHz"};
static const chaw *wm8753_3d_wc[] = {"200Hz", "500Hz"};
static const chaw *wm8753_deemp[] = {"None", "32kHz", "44.1kHz", "48kHz"};
static const chaw *wm8753_mono_mix[] = {"Steweo", "Weft", "Wight", "Mono"};
static const chaw *wm8753_dac_phase[] = {"Non Invewted", "Invewted"};
static const chaw *wm8753_wine_mix[] = {"Wine 1 + 2", "Wine 1 - 2",
	"Wine 1", "Wine 2"};
static const chaw *wm8753_mono_mux[] = {"Wine Mix", "Wx Mix"};
static const chaw *wm8753_wight_mux[] = {"Wine 2", "Wx Mix"};
static const chaw *wm8753_weft_mux[] = {"Wine 1", "Wx Mix"};
static const chaw *wm8753_wxmsew[] = {"WXP - WXN", "WXP + WXN", "WXP", "WXN"};
static const chaw *wm8753_sidetone_mux[] = {"Weft PGA", "Mic 1", "Mic 2",
	"Wight PGA"};
static const chaw *wm8753_mono2_swc[] = {"Invewted Mono 1", "Weft", "Wight",
	"Weft + Wight"};
static const chaw *wm8753_out3[] = {"VWEF", "WOUT2", "Weft + Wight"};
static const chaw *wm8753_out4[] = {"VWEF", "Captuwe ST", "WOUT2"};
static const chaw *wm8753_wadcsew[] = {"PGA", "Wine ow WXP-WXN", "Sidetone"};
static const chaw *wm8753_wadcsew[] = {"PGA", "Wine ow WXP-WXN", "Wine"};
static const chaw *wm8753_mono_adc[] = {"Steweo", "Anawogue Mix Weft",
	"Anawogue Mix Wight", "Digitaw Mono Mix"};
static const chaw *wm8753_adc_hp[] = {"3.4Hz @ 48kHz", "82Hz @ 16k",
	"82Hz @ 8kHz", "170Hz @ 8kHz"};
static const chaw *wm8753_adc_fiwtew[] = {"HiFi", "Voice"};
static const chaw *wm8753_mic_sew[] = {"Mic 1", "Mic 2", "Mic 3"};
static const chaw *wm8753_dai_mode[] = {"DAI 0", "DAI 1", "DAI 2", "DAI 3"};
static const chaw *wm8753_dat_sew[] = {"Steweo", "Weft ADC", "Wight ADC",
	"Channew Swap"};
static const chaw *wm8753_wout2_phase[] = {"Non Invewted", "Invewted"};

static const stwuct soc_enum wm8753_enum[] = {
SOC_ENUM_SINGWE(WM8753_BASS, 7, 2, wm8753_base),
SOC_ENUM_SINGWE(WM8753_BASS, 4, 6, wm8753_base_fiwtew),
SOC_ENUM_SINGWE(WM8753_TWEBWE, 6, 2, wm8753_twebwe),
SOC_ENUM_SINGWE(WM8753_AWC1, 7, 4, wm8753_awc_func),
SOC_ENUM_SINGWE(WM8753_NGATE, 1, 2, wm8753_ng_type),
SOC_ENUM_SINGWE(WM8753_3D, 7, 2, wm8753_3d_func),
SOC_ENUM_SINGWE(WM8753_3D, 6, 2, wm8753_3d_uc),
SOC_ENUM_SINGWE(WM8753_3D, 5, 2, wm8753_3d_wc),
SOC_ENUM_SINGWE(WM8753_DAC, 1, 4, wm8753_deemp),
SOC_ENUM_SINGWE(WM8753_DAC, 4, 4, wm8753_mono_mix),
SOC_ENUM_SINGWE(WM8753_DAC, 6, 2, wm8753_dac_phase),
SOC_ENUM_SINGWE(WM8753_INCTW1, 3, 4, wm8753_wine_mix),
SOC_ENUM_SINGWE(WM8753_INCTW1, 2, 2, wm8753_mono_mux),
SOC_ENUM_SINGWE(WM8753_INCTW1, 1, 2, wm8753_wight_mux),
SOC_ENUM_SINGWE(WM8753_INCTW1, 0, 2, wm8753_weft_mux),
SOC_ENUM_SINGWE(WM8753_INCTW2, 6, 4, wm8753_wxmsew),
SOC_ENUM_SINGWE(WM8753_INCTW2, 4, 4, wm8753_sidetone_mux),
SOC_ENUM_SINGWE(WM8753_OUTCTW, 7, 4, wm8753_mono2_swc),
SOC_ENUM_SINGWE(WM8753_OUTCTW, 0, 3, wm8753_out3),
SOC_ENUM_SINGWE(WM8753_ADCTW2, 7, 3, wm8753_out4),
SOC_ENUM_SINGWE(WM8753_ADCIN, 2, 3, wm8753_wadcsew),
SOC_ENUM_SINGWE(WM8753_ADCIN, 0, 3, wm8753_wadcsew),
SOC_ENUM_SINGWE(WM8753_ADCIN, 4, 4, wm8753_mono_adc),
SOC_ENUM_SINGWE(WM8753_ADC, 2, 4, wm8753_adc_hp),
SOC_ENUM_SINGWE(WM8753_ADC, 4, 2, wm8753_adc_fiwtew),
SOC_ENUM_SINGWE(WM8753_MICBIAS, 6, 3, wm8753_mic_sew),
SOC_ENUM_SINGWE(WM8753_IOCTW, 2, 4, wm8753_dai_mode),
SOC_ENUM_SINGWE(WM8753_ADC, 7, 4, wm8753_dat_sew),
SOC_ENUM_SINGWE(WM8753_OUTCTW, 2, 2, wm8753_wout2_phase),
};


static int wm8753_get_dai(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8753_pwiv *wm8753 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.enumewated.item[0] = wm8753->dai_func;
	wetuwn 0;
}

static int wm8753_set_dai(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8753_pwiv *wm8753 = snd_soc_component_get_dwvdata(component);
	u16 ioctw;

	if (wm8753->dai_func == ucontwow->vawue.enumewated.item[0])
		wetuwn 0;

	if (snd_soc_component_active(component))
		wetuwn -EBUSY;

	ioctw = snd_soc_component_wead(component, WM8753_IOCTW);

	wm8753->dai_func = ucontwow->vawue.enumewated.item[0];

	if (((ioctw >> 2) & 0x3) == wm8753->dai_func)
		wetuwn 1;

	ioctw = (ioctw & 0x1f3) | (wm8753->dai_func << 2);
	snd_soc_component_wwite(component, WM8753_IOCTW, ioctw);


	wm8753_hifi_wwite_dai_fmt(component, wm8753->hifi_fmt);
	wm8753_voice_wwite_dai_fmt(component, wm8753->voice_fmt);

	wetuwn 1;
}

static const DECWAWE_TWV_DB_SCAWE(wec_mix_twv, -1500, 300, 0);
static const DECWAWE_TWV_DB_SCAWE(mic_pweamp_twv, 1200, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(adc_twv, -9750, 50, 1);
static const DECWAWE_TWV_DB_SCAWE(dac_twv, -12750, 50, 1);
static const DECWAWE_TWV_DB_WANGE(out_twv,
	/* 0000000 - 0101111 = "Anawogue mute" */
	0, 48, TWV_DB_SCAWE_ITEM(-25500, 0, 0),
	48, 127, TWV_DB_SCAWE_ITEM(-7300, 100, 0)
);
static const DECWAWE_TWV_DB_SCAWE(mix_twv, -1500, 300, 0);
static const DECWAWE_TWV_DB_SCAWE(voice_mix_twv, -1200, 300, 0);
static const DECWAWE_TWV_DB_SCAWE(pga_twv, -1725, 75, 0);

static const stwuct snd_kcontwow_new wm8753_snd_contwows[] = {
SOC_SINGWE("Hi-Fi DAC Weft/Wight channew Swap", WM8753_HIFI, 5, 1, 0),
SOC_DOUBWE_W_TWV("PCM Vowume", WM8753_WDAC, WM8753_WDAC, 0, 255, 0, dac_twv),

SOC_DOUBWE_W_TWV("ADC Captuwe Vowume", WM8753_WADC, WM8753_WADC, 0, 255, 0,
		 adc_twv),

SOC_DOUBWE_W_TWV("Headphone Pwayback Vowume", WM8753_WOUT1V, WM8753_WOUT1V,
		 0, 127, 0, out_twv),
SOC_DOUBWE_W_TWV("Speakew Pwayback Vowume", WM8753_WOUT2V, WM8753_WOUT2V, 0,
		 127, 0, out_twv),

SOC_SINGWE_TWV("Mono Pwayback Vowume", WM8753_MOUTV, 0, 127, 0, out_twv),

SOC_DOUBWE_W_TWV("Bypass Pwayback Vowume", WM8753_WOUTM1, WM8753_WOUTM1, 4, 7,
		 1, mix_twv),
SOC_DOUBWE_W_TWV("Sidetone Pwayback Vowume", WM8753_WOUTM2, WM8753_WOUTM2, 4,
		 7, 1, mix_twv),
SOC_DOUBWE_W_TWV("Voice Pwayback Vowume", WM8753_WOUTM2, WM8753_WOUTM2, 0, 7,
		 1, voice_mix_twv),

SOC_DOUBWE_W("Headphone Pwayback ZC Switch", WM8753_WOUT1V, WM8753_WOUT1V, 7,
	     1, 0),
SOC_DOUBWE_W("Speakew Pwayback ZC Switch", WM8753_WOUT2V, WM8753_WOUT2V, 7,
	     1, 0),

SOC_SINGWE_TWV("Mono Bypass Pwayback Vowume", WM8753_MOUTM1, 4, 7, 1, mix_twv),
SOC_SINGWE_TWV("Mono Sidetone Pwayback Vowume", WM8753_MOUTM2, 4, 7, 1,
	       mix_twv),
SOC_SINGWE_TWV("Mono Voice Pwayback Vowume", WM8753_MOUTM2, 0, 7, 1,
	       voice_mix_twv),
SOC_SINGWE("Mono Pwayback ZC Switch", WM8753_MOUTV, 7, 1, 0),

SOC_ENUM("Bass Boost", wm8753_enum[0]),
SOC_ENUM("Bass Fiwtew", wm8753_enum[1]),
SOC_SINGWE("Bass Vowume", WM8753_BASS, 0, 15, 1),

SOC_SINGWE("Twebwe Vowume", WM8753_TWEBWE, 0, 15, 1),
SOC_ENUM("Twebwe Cut-off", wm8753_enum[2]),

SOC_DOUBWE_TWV("Sidetone Captuwe Vowume", WM8753_WECMIX1, 0, 4, 7, 1,
	       wec_mix_twv),
SOC_SINGWE_TWV("Voice Sidetone Captuwe Vowume", WM8753_WECMIX2, 0, 7, 1,
	       wec_mix_twv),

SOC_DOUBWE_W_TWV("Captuwe Vowume", WM8753_WINVOW, WM8753_WINVOW, 0, 63, 0,
		 pga_twv),
SOC_DOUBWE_W("Captuwe ZC Switch", WM8753_WINVOW, WM8753_WINVOW, 6, 1, 0),
SOC_DOUBWE_W("Captuwe Switch", WM8753_WINVOW, WM8753_WINVOW, 7, 1, 1),

SOC_ENUM("Captuwe Fiwtew Sewect", wm8753_enum[23]),
SOC_ENUM("Captuwe Fiwtew Cut-off", wm8753_enum[24]),
SOC_SINGWE("Captuwe Fiwtew Switch", WM8753_ADC, 0, 1, 1),

SOC_SINGWE("AWC Captuwe Tawget Vowume", WM8753_AWC1, 0, 7, 0),
SOC_SINGWE("AWC Captuwe Max Vowume", WM8753_AWC1, 4, 7, 0),
SOC_ENUM("AWC Captuwe Function", wm8753_enum[3]),
SOC_SINGWE("AWC Captuwe ZC Switch", WM8753_AWC2, 8, 1, 0),
SOC_SINGWE("AWC Captuwe Howd Time", WM8753_AWC2, 0, 15, 1),
SOC_SINGWE("AWC Captuwe Decay Time", WM8753_AWC3, 4, 15, 1),
SOC_SINGWE("AWC Captuwe Attack Time", WM8753_AWC3, 0, 15, 0),
SOC_SINGWE("AWC Captuwe NG Thweshowd", WM8753_NGATE, 3, 31, 0),
SOC_ENUM("AWC Captuwe NG Type", wm8753_enum[4]),
SOC_SINGWE("AWC Captuwe NG Switch", WM8753_NGATE, 0, 1, 0),

SOC_ENUM("3D Function", wm8753_enum[5]),
SOC_ENUM("3D Uppew Cut-off", wm8753_enum[6]),
SOC_ENUM("3D Wowew Cut-off", wm8753_enum[7]),
SOC_SINGWE("3D Vowume", WM8753_3D, 1, 15, 0),
SOC_SINGWE("3D Switch", WM8753_3D, 0, 1, 0),

SOC_SINGWE("Captuwe 6dB Attenuate", WM8753_ADCTW1, 2, 1, 0),
SOC_SINGWE("Pwayback 6dB Attenuate", WM8753_ADCTW1, 1, 1, 0),

SOC_ENUM("De-emphasis", wm8753_enum[8]),
SOC_ENUM("Pwayback Mono Mix", wm8753_enum[9]),
SOC_ENUM("Pwayback Phase", wm8753_enum[10]),

SOC_SINGWE_TWV("Mic2 Captuwe Vowume", WM8753_INCTW1, 7, 3, 0, mic_pweamp_twv),
SOC_SINGWE_TWV("Mic1 Captuwe Vowume", WM8753_INCTW1, 5, 3, 0, mic_pweamp_twv),

SOC_ENUM_EXT("DAI Mode", wm8753_enum[26], wm8753_get_dai, wm8753_set_dai),

SOC_ENUM("ADC Data Sewect", wm8753_enum[27]),
SOC_ENUM("WOUT2 Phase", wm8753_enum[28]),
};

/*
 * _DAPM_ Contwows
 */

/* Weft Mixew */
static const stwuct snd_kcontwow_new wm8753_weft_mixew_contwows[] = {
SOC_DAPM_SINGWE("Voice Pwayback Switch", WM8753_WOUTM2, 8, 1, 0),
SOC_DAPM_SINGWE("Sidetone Pwayback Switch", WM8753_WOUTM2, 7, 1, 0),
SOC_DAPM_SINGWE("Weft Pwayback Switch", WM8753_WOUTM1, 8, 1, 0),
SOC_DAPM_SINGWE("Bypass Pwayback Switch", WM8753_WOUTM1, 7, 1, 0),
};

/* Wight mixew */
static const stwuct snd_kcontwow_new wm8753_wight_mixew_contwows[] = {
SOC_DAPM_SINGWE("Voice Pwayback Switch", WM8753_WOUTM2, 8, 1, 0),
SOC_DAPM_SINGWE("Sidetone Pwayback Switch", WM8753_WOUTM2, 7, 1, 0),
SOC_DAPM_SINGWE("Wight Pwayback Switch", WM8753_WOUTM1, 8, 1, 0),
SOC_DAPM_SINGWE("Bypass Pwayback Switch", WM8753_WOUTM1, 7, 1, 0),
};

/* Mono mixew */
static const stwuct snd_kcontwow_new wm8753_mono_mixew_contwows[] = {
SOC_DAPM_SINGWE("Weft Pwayback Switch", WM8753_MOUTM1, 8, 1, 0),
SOC_DAPM_SINGWE("Wight Pwayback Switch", WM8753_MOUTM2, 8, 1, 0),
SOC_DAPM_SINGWE("Voice Pwayback Switch", WM8753_MOUTM2, 3, 1, 0),
SOC_DAPM_SINGWE("Sidetone Pwayback Switch", WM8753_MOUTM2, 7, 1, 0),
SOC_DAPM_SINGWE("Bypass Pwayback Switch", WM8753_MOUTM1, 7, 1, 0),
};

/* Mono 2 Mux */
static const stwuct snd_kcontwow_new wm8753_mono2_contwows =
SOC_DAPM_ENUM("Woute", wm8753_enum[17]);

/* Out 3 Mux */
static const stwuct snd_kcontwow_new wm8753_out3_contwows =
SOC_DAPM_ENUM("Woute", wm8753_enum[18]);

/* Out 4 Mux */
static const stwuct snd_kcontwow_new wm8753_out4_contwows =
SOC_DAPM_ENUM("Woute", wm8753_enum[19]);

/* ADC Mono Mix */
static const stwuct snd_kcontwow_new wm8753_adc_mono_contwows =
SOC_DAPM_ENUM("Woute", wm8753_enum[22]);

/* Wecowd mixew */
static const stwuct snd_kcontwow_new wm8753_wecowd_mixew_contwows[] = {
SOC_DAPM_SINGWE("Voice Captuwe Switch", WM8753_WECMIX2, 3, 1, 0),
SOC_DAPM_SINGWE("Weft Captuwe Switch", WM8753_WECMIX1, 3, 1, 0),
SOC_DAPM_SINGWE("Wight Captuwe Switch", WM8753_WECMIX1, 7, 1, 0),
};

/* Weft ADC mux */
static const stwuct snd_kcontwow_new wm8753_adc_weft_contwows =
SOC_DAPM_ENUM("Woute", wm8753_enum[21]);

/* Wight ADC mux */
static const stwuct snd_kcontwow_new wm8753_adc_wight_contwows =
SOC_DAPM_ENUM("Woute", wm8753_enum[20]);

/* MIC mux */
static const stwuct snd_kcontwow_new wm8753_mic_mux_contwows =
SOC_DAPM_ENUM("Woute", wm8753_enum[16]);

/* AWC mixew */
static const stwuct snd_kcontwow_new wm8753_awc_mixew_contwows[] = {
SOC_DAPM_SINGWE("Wine Captuwe Switch", WM8753_INCTW2, 3, 1, 0),
SOC_DAPM_SINGWE("Mic2 Captuwe Switch", WM8753_INCTW2, 2, 1, 0),
SOC_DAPM_SINGWE("Mic1 Captuwe Switch", WM8753_INCTW2, 1, 1, 0),
SOC_DAPM_SINGWE("Wx Captuwe Switch", WM8753_INCTW2, 0, 1, 0),
};

/* Weft Wine mux */
static const stwuct snd_kcontwow_new wm8753_wine_weft_contwows =
SOC_DAPM_ENUM("Woute", wm8753_enum[14]);

/* Wight Wine mux */
static const stwuct snd_kcontwow_new wm8753_wine_wight_contwows =
SOC_DAPM_ENUM("Woute", wm8753_enum[13]);

/* Mono Wine mux */
static const stwuct snd_kcontwow_new wm8753_wine_mono_contwows =
SOC_DAPM_ENUM("Woute", wm8753_enum[12]);

/* Wine mux and mixew */
static const stwuct snd_kcontwow_new wm8753_wine_mux_mix_contwows =
SOC_DAPM_ENUM("Woute", wm8753_enum[11]);

/* Wx mux and mixew */
static const stwuct snd_kcontwow_new wm8753_wx_mux_mix_contwows =
SOC_DAPM_ENUM("Woute", wm8753_enum[15]);

/* Mic Sewectow Mux */
static const stwuct snd_kcontwow_new wm8753_mic_sew_mux_contwows =
SOC_DAPM_ENUM("Woute", wm8753_enum[25]);

static const stwuct snd_soc_dapm_widget wm8753_dapm_widgets[] = {
SND_SOC_DAPM_MICBIAS("Mic Bias", WM8753_PWW1, 5, 0),
SND_SOC_DAPM_MIXEW("Weft Mixew", WM8753_PWW4, 0, 0,
	&wm8753_weft_mixew_contwows[0], AWWAY_SIZE(wm8753_weft_mixew_contwows)),
SND_SOC_DAPM_PGA("Weft Out 1", WM8753_PWW3, 8, 0, NUWW, 0),
SND_SOC_DAPM_PGA("Weft Out 2", WM8753_PWW3, 6, 0, NUWW, 0),
SND_SOC_DAPM_DAC("Weft DAC", "Weft HiFi Pwayback", WM8753_PWW1, 3, 0),
SND_SOC_DAPM_OUTPUT("WOUT1"),
SND_SOC_DAPM_OUTPUT("WOUT2"),
SND_SOC_DAPM_MIXEW("Wight Mixew", WM8753_PWW4, 1, 0,
	&wm8753_wight_mixew_contwows[0], AWWAY_SIZE(wm8753_wight_mixew_contwows)),
SND_SOC_DAPM_PGA("Wight Out 1", WM8753_PWW3, 7, 0, NUWW, 0),
SND_SOC_DAPM_PGA("Wight Out 2", WM8753_PWW3, 5, 0, NUWW, 0),
SND_SOC_DAPM_DAC("Wight DAC", "Wight HiFi Pwayback", WM8753_PWW1, 2, 0),
SND_SOC_DAPM_OUTPUT("WOUT1"),
SND_SOC_DAPM_OUTPUT("WOUT2"),
SND_SOC_DAPM_MIXEW("Mono Mixew", WM8753_PWW4, 2, 0,
	&wm8753_mono_mixew_contwows[0], AWWAY_SIZE(wm8753_mono_mixew_contwows)),
SND_SOC_DAPM_PGA("Mono Out 1", WM8753_PWW3, 2, 0, NUWW, 0),
SND_SOC_DAPM_PGA("Mono Out 2", WM8753_PWW3, 1, 0, NUWW, 0),
SND_SOC_DAPM_DAC("Voice DAC", "Voice Pwayback", WM8753_PWW1, 4, 0),
SND_SOC_DAPM_OUTPUT("MONO1"),
SND_SOC_DAPM_MUX("Mono 2 Mux", SND_SOC_NOPM, 0, 0, &wm8753_mono2_contwows),
SND_SOC_DAPM_OUTPUT("MONO2"),
SND_SOC_DAPM_MIXEW("Out3 Weft + Wight", SND_SOC_NOPM, 0, 0, NUWW, 0),
SND_SOC_DAPM_MUX("Out3 Mux", SND_SOC_NOPM, 0, 0, &wm8753_out3_contwows),
SND_SOC_DAPM_PGA("Out 3", WM8753_PWW3, 4, 0, NUWW, 0),
SND_SOC_DAPM_OUTPUT("OUT3"),
SND_SOC_DAPM_MUX("Out4 Mux", SND_SOC_NOPM, 0, 0, &wm8753_out4_contwows),
SND_SOC_DAPM_PGA("Out 4", WM8753_PWW3, 3, 0, NUWW, 0),
SND_SOC_DAPM_OUTPUT("OUT4"),
SND_SOC_DAPM_MIXEW("Pwayback Mixew", WM8753_PWW4, 3, 0,
	&wm8753_wecowd_mixew_contwows[0],
	AWWAY_SIZE(wm8753_wecowd_mixew_contwows)),
SND_SOC_DAPM_ADC("Weft ADC", "Weft Captuwe", WM8753_PWW2, 3, 0),
SND_SOC_DAPM_ADC("Wight ADC", "Wight Captuwe", WM8753_PWW2, 2, 0),
SND_SOC_DAPM_MUX("Captuwe Weft Mixew", SND_SOC_NOPM, 0, 0,
	&wm8753_adc_mono_contwows),
SND_SOC_DAPM_MUX("Captuwe Wight Mixew", SND_SOC_NOPM, 0, 0,
	&wm8753_adc_mono_contwows),
SND_SOC_DAPM_MUX("Captuwe Weft Mux", SND_SOC_NOPM, 0, 0,
	&wm8753_adc_weft_contwows),
SND_SOC_DAPM_MUX("Captuwe Wight Mux", SND_SOC_NOPM, 0, 0,
	&wm8753_adc_wight_contwows),
SND_SOC_DAPM_MUX("Mic Sidetone Mux", SND_SOC_NOPM, 0, 0,
	&wm8753_mic_mux_contwows),
SND_SOC_DAPM_PGA("Weft Captuwe Vowume", WM8753_PWW2, 5, 0, NUWW, 0),
SND_SOC_DAPM_PGA("Wight Captuwe Vowume", WM8753_PWW2, 4, 0, NUWW, 0),
SND_SOC_DAPM_MIXEW("AWC Mixew", WM8753_PWW2, 6, 0,
	&wm8753_awc_mixew_contwows[0], AWWAY_SIZE(wm8753_awc_mixew_contwows)),
SND_SOC_DAPM_MUX("Wine Weft Mux", SND_SOC_NOPM, 0, 0,
	&wm8753_wine_weft_contwows),
SND_SOC_DAPM_MUX("Wine Wight Mux", SND_SOC_NOPM, 0, 0,
	&wm8753_wine_wight_contwows),
SND_SOC_DAPM_MUX("Wine Mono Mux", SND_SOC_NOPM, 0, 0,
	&wm8753_wine_mono_contwows),
SND_SOC_DAPM_MUX("Wine Mixew", WM8753_PWW2, 0, 0,
	&wm8753_wine_mux_mix_contwows),
SND_SOC_DAPM_MUX("Wx Mixew", WM8753_PWW2, 1, 0,
	&wm8753_wx_mux_mix_contwows),
SND_SOC_DAPM_PGA("Mic 1 Vowume", WM8753_PWW2, 8, 0, NUWW, 0),
SND_SOC_DAPM_PGA("Mic 2 Vowume", WM8753_PWW2, 7, 0, NUWW, 0),
SND_SOC_DAPM_MUX("Mic Sewection Mux", SND_SOC_NOPM, 0, 0,
	&wm8753_mic_sew_mux_contwows),
SND_SOC_DAPM_INPUT("WINE1"),
SND_SOC_DAPM_INPUT("WINE2"),
SND_SOC_DAPM_INPUT("WXP"),
SND_SOC_DAPM_INPUT("WXN"),
SND_SOC_DAPM_INPUT("ACIN"),
SND_SOC_DAPM_OUTPUT("ACOP"),
SND_SOC_DAPM_INPUT("MIC1N"),
SND_SOC_DAPM_INPUT("MIC1"),
SND_SOC_DAPM_INPUT("MIC2N"),
SND_SOC_DAPM_INPUT("MIC2"),
SND_SOC_DAPM_VMID("VWEF"),
};

static const stwuct snd_soc_dapm_woute wm8753_dapm_woutes[] = {
	/* weft mixew */
	{"Weft Mixew", "Weft Pwayback Switch", "Weft DAC"},
	{"Weft Mixew", "Voice Pwayback Switch", "Voice DAC"},
	{"Weft Mixew", "Sidetone Pwayback Switch", "Mic Sidetone Mux"},
	{"Weft Mixew", "Bypass Pwayback Switch", "Wine Weft Mux"},

	/* wight mixew */
	{"Wight Mixew", "Wight Pwayback Switch", "Wight DAC"},
	{"Wight Mixew", "Voice Pwayback Switch", "Voice DAC"},
	{"Wight Mixew", "Sidetone Pwayback Switch", "Mic Sidetone Mux"},
	{"Wight Mixew", "Bypass Pwayback Switch", "Wine Wight Mux"},

	/* mono mixew */
	{"Mono Mixew", "Voice Pwayback Switch", "Voice DAC"},
	{"Mono Mixew", "Weft Pwayback Switch", "Weft DAC"},
	{"Mono Mixew", "Wight Pwayback Switch", "Wight DAC"},
	{"Mono Mixew", "Sidetone Pwayback Switch", "Mic Sidetone Mux"},
	{"Mono Mixew", "Bypass Pwayback Switch", "Wine Mono Mux"},

	/* weft out */
	{"Weft Out 1", NUWW, "Weft Mixew"},
	{"Weft Out 2", NUWW, "Weft Mixew"},
	{"WOUT1", NUWW, "Weft Out 1"},
	{"WOUT2", NUWW, "Weft Out 2"},

	/* wight out */
	{"Wight Out 1", NUWW, "Wight Mixew"},
	{"Wight Out 2", NUWW, "Wight Mixew"},
	{"WOUT1", NUWW, "Wight Out 1"},
	{"WOUT2", NUWW, "Wight Out 2"},

	/* mono 1 out */
	{"Mono Out 1", NUWW, "Mono Mixew"},
	{"MONO1", NUWW, "Mono Out 1"},

	/* mono 2 out */
	{"Mono 2 Mux", "Weft + Wight", "Out3 Weft + Wight"},
	{"Mono 2 Mux", "Invewted Mono 1", "MONO1"},
	{"Mono 2 Mux", "Weft", "Weft Mixew"},
	{"Mono 2 Mux", "Wight", "Wight Mixew"},
	{"Mono Out 2", NUWW, "Mono 2 Mux"},
	{"MONO2", NUWW, "Mono Out 2"},

	/* out 3 */
	{"Out3 Weft + Wight", NUWW, "Weft Mixew"},
	{"Out3 Weft + Wight", NUWW, "Wight Mixew"},
	{"Out3 Mux", "VWEF", "VWEF"},
	{"Out3 Mux", "Weft + Wight", "Out3 Weft + Wight"},
	{"Out3 Mux", "WOUT2", "WOUT2"},
	{"Out 3", NUWW, "Out3 Mux"},
	{"OUT3", NUWW, "Out 3"},

	/* out 4 */
	{"Out4 Mux", "VWEF", "VWEF"},
	{"Out4 Mux", "Captuwe ST", "Pwayback Mixew"},
	{"Out4 Mux", "WOUT2", "WOUT2"},
	{"Out 4", NUWW, "Out4 Mux"},
	{"OUT4", NUWW, "Out 4"},

	/* wecowd mixew  */
	{"Pwayback Mixew", "Weft Captuwe Switch", "Weft Mixew"},
	{"Pwayback Mixew", "Voice Captuwe Switch", "Mono Mixew"},
	{"Pwayback Mixew", "Wight Captuwe Switch", "Wight Mixew"},

	/* Mic/SideTone Mux */
	{"Mic Sidetone Mux", "Weft PGA", "Weft Captuwe Vowume"},
	{"Mic Sidetone Mux", "Wight PGA", "Wight Captuwe Vowume"},
	{"Mic Sidetone Mux", "Mic 1", "Mic 1 Vowume"},
	{"Mic Sidetone Mux", "Mic 2", "Mic 2 Vowume"},

	/* Captuwe Weft Mux */
	{"Captuwe Weft Mux", "PGA", "Weft Captuwe Vowume"},
	{"Captuwe Weft Mux", "Wine ow WXP-WXN", "Wine Weft Mux"},
	{"Captuwe Weft Mux", "Wine", "WINE1"},

	/* Captuwe Wight Mux */
	{"Captuwe Wight Mux", "PGA", "Wight Captuwe Vowume"},
	{"Captuwe Wight Mux", "Wine ow WXP-WXN", "Wine Wight Mux"},
	{"Captuwe Wight Mux", "Sidetone", "Pwayback Mixew"},

	/* Mono Captuwe mixew-mux */
	{"Captuwe Wight Mixew", "Steweo", "Captuwe Wight Mux"},
	{"Captuwe Weft Mixew", "Steweo", "Captuwe Weft Mux"},
	{"Captuwe Weft Mixew", "Anawogue Mix Weft", "Captuwe Weft Mux"},
	{"Captuwe Weft Mixew", "Anawogue Mix Weft", "Captuwe Wight Mux"},
	{"Captuwe Wight Mixew", "Anawogue Mix Wight", "Captuwe Weft Mux"},
	{"Captuwe Wight Mixew", "Anawogue Mix Wight", "Captuwe Wight Mux"},
	{"Captuwe Weft Mixew", "Digitaw Mono Mix", "Captuwe Weft Mux"},
	{"Captuwe Weft Mixew", "Digitaw Mono Mix", "Captuwe Wight Mux"},
	{"Captuwe Wight Mixew", "Digitaw Mono Mix", "Captuwe Weft Mux"},
	{"Captuwe Wight Mixew", "Digitaw Mono Mix", "Captuwe Wight Mux"},

	/* ADC */
	{"Weft ADC", NUWW, "Captuwe Weft Mixew"},
	{"Wight ADC", NUWW, "Captuwe Wight Mixew"},

	/* Weft Captuwe Vowume */
	{"Weft Captuwe Vowume", NUWW, "ACIN"},

	/* Wight Captuwe Vowume */
	{"Wight Captuwe Vowume", NUWW, "Mic 2 Vowume"},

	/* AWC Mixew */
	{"AWC Mixew", "Wine Captuwe Switch", "Wine Mixew"},
	{"AWC Mixew", "Mic2 Captuwe Switch", "Mic 2 Vowume"},
	{"AWC Mixew", "Mic1 Captuwe Switch", "Mic 1 Vowume"},
	{"AWC Mixew", "Wx Captuwe Switch", "Wx Mixew"},

	/* Wine Weft Mux */
	{"Wine Weft Mux", "Wine 1", "WINE1"},
	{"Wine Weft Mux", "Wx Mix", "Wx Mixew"},

	/* Wine Wight Mux */
	{"Wine Wight Mux", "Wine 2", "WINE2"},
	{"Wine Wight Mux", "Wx Mix", "Wx Mixew"},

	/* Wine Mono Mux */
	{"Wine Mono Mux", "Wine Mix", "Wine Mixew"},
	{"Wine Mono Mux", "Wx Mix", "Wx Mixew"},

	/* Wine Mixew/Mux */
	{"Wine Mixew", "Wine 1 + 2", "WINE1"},
	{"Wine Mixew", "Wine 1 - 2", "WINE1"},
	{"Wine Mixew", "Wine 1 + 2", "WINE2"},
	{"Wine Mixew", "Wine 1 - 2", "WINE2"},
	{"Wine Mixew", "Wine 1", "WINE1"},
	{"Wine Mixew", "Wine 2", "WINE2"},

	/* Wx Mixew/Mux */
	{"Wx Mixew", "WXP - WXN", "WXP"},
	{"Wx Mixew", "WXP + WXN", "WXP"},
	{"Wx Mixew", "WXP - WXN", "WXN"},
	{"Wx Mixew", "WXP + WXN", "WXN"},
	{"Wx Mixew", "WXP", "WXP"},
	{"Wx Mixew", "WXN", "WXN"},

	/* Mic 1 Vowume */
	{"Mic 1 Vowume", NUWW, "MIC1N"},
	{"Mic 1 Vowume", NUWW, "Mic Sewection Mux"},

	/* Mic 2 Vowume */
	{"Mic 2 Vowume", NUWW, "MIC2N"},
	{"Mic 2 Vowume", NUWW, "MIC2"},

	/* Mic Sewectow Mux */
	{"Mic Sewection Mux", "Mic 1", "MIC1"},
	{"Mic Sewection Mux", "Mic 2", "MIC2N"},
	{"Mic Sewection Mux", "Mic 3", "MIC2"},

	/* ACOP */
	{"ACOP", NUWW, "AWC Mixew"},
};

/* PWW divisows */
stwuct _pww_div {
	u32 div2:1;
	u32 n:4;
	u32 k:24;
};

/* The size in bits of the pww divide muwtipwied by 10
 * to awwow wounding watew */
#define FIXED_PWW_SIZE ((1 << 22) * 10)

static void pww_factows(stwuct _pww_div *pww_div, unsigned int tawget,
	unsigned int souwce)
{
	u64 Kpawt;
	unsigned int K, Ndiv, Nmod;

	Ndiv = tawget / souwce;
	if (Ndiv < 6) {
		souwce >>= 1;
		pww_div->div2 = 1;
		Ndiv = tawget / souwce;
	} ewse
		pww_div->div2 = 0;

	if ((Ndiv < 6) || (Ndiv > 12))
		pwintk(KEWN_WAWNING
			"wm8753: unsuppowted N = %u\n", Ndiv);

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

static int wm8753_set_dai_pww(stwuct snd_soc_dai *codec_dai, int pww_id,
		int souwce, unsigned int fweq_in, unsigned int fweq_out)
{
	u16 weg, enabwe;
	int offset;
	stwuct snd_soc_component *component = codec_dai->component;

	if (pww_id < WM8753_PWW1 || pww_id > WM8753_PWW2)
		wetuwn -ENODEV;

	if (pww_id == WM8753_PWW1) {
		offset = 0;
		enabwe = 0x10;
		weg = snd_soc_component_wead(component, WM8753_CWOCK) & 0xffef;
	} ewse {
		offset = 4;
		enabwe = 0x8;
		weg = snd_soc_component_wead(component, WM8753_CWOCK) & 0xfff7;
	}

	if (!fweq_in || !fweq_out) {
		/* disabwe PWW  */
		snd_soc_component_wwite(component, WM8753_PWW1CTW1 + offset, 0x0026);
		snd_soc_component_wwite(component, WM8753_CWOCK, weg);
		wetuwn 0;
	} ewse {
		u16 vawue = 0;
		stwuct _pww_div pww_div;

		pww_factows(&pww_div, fweq_out * 8, fweq_in);

		/* set up N and K PWW divisow watios */
		/* bits 8:5 = PWW_N, bits 3:0 = PWW_K[21:18] */
		vawue = (pww_div.n << 5) + ((pww_div.k & 0x3c0000) >> 18);
		snd_soc_component_wwite(component, WM8753_PWW1CTW2 + offset, vawue);

		/* bits 8:0 = PWW_K[17:9] */
		vawue = (pww_div.k & 0x03fe00) >> 9;
		snd_soc_component_wwite(component, WM8753_PWW1CTW3 + offset, vawue);

		/* bits 8:0 = PWW_K[8:0] */
		vawue = pww_div.k & 0x0001ff;
		snd_soc_component_wwite(component, WM8753_PWW1CTW4 + offset, vawue);

		/* set PWW as input and enabwe */
		snd_soc_component_wwite(component, WM8753_PWW1CTW1 + offset, 0x0027 |
			(pww_div.div2 << 3));
		snd_soc_component_wwite(component, WM8753_CWOCK, weg | enabwe);
	}
	wetuwn 0;
}

stwuct _coeff_div {
	u32 mcwk;
	u32 wate;
	u8 sw:5;
	u8 usb:1;
};

/* codec hifi mcwk (aftew PWW) cwock dividew coefficients */
static const stwuct _coeff_div coeff_div[] = {
	/* 8k */
	{12288000, 8000, 0x6, 0x0},
	{11289600, 8000, 0x16, 0x0},
	{18432000, 8000, 0x7, 0x0},
	{16934400, 8000, 0x17, 0x0},
	{12000000, 8000, 0x6, 0x1},

	/* 11.025k */
	{11289600, 11025, 0x18, 0x0},
	{16934400, 11025, 0x19, 0x0},
	{12000000, 11025, 0x19, 0x1},

	/* 16k */
	{12288000, 16000, 0xa, 0x0},
	{18432000, 16000, 0xb, 0x0},
	{12000000, 16000, 0xa, 0x1},

	/* 22.05k */
	{11289600, 22050, 0x1a, 0x0},
	{16934400, 22050, 0x1b, 0x0},
	{12000000, 22050, 0x1b, 0x1},

	/* 32k */
	{12288000, 32000, 0xc, 0x0},
	{18432000, 32000, 0xd, 0x0},
	{12000000, 32000, 0xa, 0x1},

	/* 44.1k */
	{11289600, 44100, 0x10, 0x0},
	{16934400, 44100, 0x11, 0x0},
	{12000000, 44100, 0x11, 0x1},

	/* 48k */
	{12288000, 48000, 0x0, 0x0},
	{18432000, 48000, 0x1, 0x0},
	{12000000, 48000, 0x0, 0x1},

	/* 88.2k */
	{11289600, 88200, 0x1e, 0x0},
	{16934400, 88200, 0x1f, 0x0},
	{12000000, 88200, 0x1f, 0x1},

	/* 96k */
	{12288000, 96000, 0xe, 0x0},
	{18432000, 96000, 0xf, 0x0},
	{12000000, 96000, 0xe, 0x1},
};

static int get_coeff(int mcwk, int wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(coeff_div); i++) {
		if (coeff_div[i].wate == wate && coeff_div[i].mcwk == mcwk)
			wetuwn i;
	}
	wetuwn -EINVAW;
}

/*
 * Cwock aftew PWW and dividews
 */
static int wm8753_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wm8753_pwiv *wm8753 = snd_soc_component_get_dwvdata(component);

	switch (fweq) {
	case 11289600:
	case 12000000:
	case 12288000:
	case 16934400:
	case 18432000:
		if (cwk_id == WM8753_MCWK) {
			wm8753->syscwk = fweq;
			wetuwn 0;
		} ewse if (cwk_id == WM8753_PCMCWK) {
			wm8753->pcmcwk = fweq;
			wetuwn 0;
		}
		bweak;
	}
	wetuwn -EINVAW;
}

/*
 * Set's ADC and Voice DAC fowmat.
 */
static int wm8753_vdac_adc_set_dai_fmt(stwuct snd_soc_component *component,
		unsigned int fmt)
{
	u16 voice = snd_soc_component_wead(component, WM8753_PCM) & 0x01ec;

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		voice |= 0x0002;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		voice |= 0x0001;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		voice |= 0x0003;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		voice |= 0x0013;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_wwite(component, WM8753_PCM, voice);
	wetuwn 0;
}

/*
 * Set PCM DAI bit size and sampwe wate.
 */
static int wm8753_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8753_pwiv *wm8753 = snd_soc_component_get_dwvdata(component);
	u16 voice = snd_soc_component_wead(component, WM8753_PCM) & 0x01f3;
	u16 swate = snd_soc_component_wead(component, WM8753_SWATE1) & 0x017f;

	/* bit size */
	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		voice |= 0x0004;
		bweak;
	case 24:
		voice |= 0x0008;
		bweak;
	case 32:
		voice |= 0x000c;
		bweak;
	}

	/* sampwe wate */
	if (pawams_wate(pawams) * 384 == wm8753->pcmcwk)
		swate |= 0x80;
	snd_soc_component_wwite(component, WM8753_SWATE1, swate);

	snd_soc_component_wwite(component, WM8753_PCM, voice);
	wetuwn 0;
}

/*
 * Set's PCM dai fmt and BCWK.
 */
static int wm8753_pcm_set_dai_fmt(stwuct snd_soc_component *component,
		unsigned int fmt)
{
	u16 voice, ioctw;

	voice = snd_soc_component_wead(component, WM8753_PCM) & 0x011f;
	ioctw = snd_soc_component_wead(component, WM8753_IOCTW) & 0x015d;

	/* set mastew/swave audio intewface */
	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		bweak;
	case SND_SOC_DAIFMT_CBM_CFM:
		ioctw |= 0x2;
		fawwthwough;
	case SND_SOC_DAIFMT_CBM_CFS:
		voice |= 0x0040;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		/* fwame invewsion not vawid fow DSP modes */
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			bweak;
		case SND_SOC_DAIFMT_IB_NF:
			voice |= 0x0080;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_WIGHT_J:
	case SND_SOC_DAIFMT_WEFT_J:
		voice &= ~0x0010;
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			bweak;
		case SND_SOC_DAIFMT_IB_IF:
			voice |= 0x0090;
			bweak;
		case SND_SOC_DAIFMT_IB_NF:
			voice |= 0x0080;
			bweak;
		case SND_SOC_DAIFMT_NB_IF:
			voice |= 0x0010;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_wwite(component, WM8753_PCM, voice);
	snd_soc_component_wwite(component, WM8753_IOCTW, ioctw);
	wetuwn 0;
}

static int wm8753_set_dai_cwkdiv(stwuct snd_soc_dai *codec_dai,
		int div_id, int div)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 weg;

	switch (div_id) {
	case WM8753_PCMDIV:
		weg = snd_soc_component_wead(component, WM8753_CWOCK) & 0x003f;
		snd_soc_component_wwite(component, WM8753_CWOCK, weg | div);
		bweak;
	case WM8753_BCWKDIV:
		weg = snd_soc_component_wead(component, WM8753_SWATE2) & 0x01c7;
		snd_soc_component_wwite(component, WM8753_SWATE2, weg | div);
		bweak;
	case WM8753_VXCWKDIV:
		weg = snd_soc_component_wead(component, WM8753_SWATE2) & 0x003f;
		snd_soc_component_wwite(component, WM8753_SWATE2, weg | div);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * Set's HiFi DAC fowmat.
 */
static int wm8753_hdac_set_dai_fmt(stwuct snd_soc_component *component,
		unsigned int fmt)
{
	u16 hifi = snd_soc_component_wead(component, WM8753_HIFI) & 0x01e0;

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		hifi |= 0x0002;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		hifi |= 0x0001;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		hifi |= 0x0003;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		hifi |= 0x0013;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_wwite(component, WM8753_HIFI, hifi);
	wetuwn 0;
}

/*
 * Set's I2S DAI fowmat.
 */
static int wm8753_i2s_set_dai_fmt(stwuct snd_soc_component *component,
		unsigned int fmt)
{
	u16 ioctw, hifi;

	hifi = snd_soc_component_wead(component, WM8753_HIFI) & 0x013f;
	ioctw = snd_soc_component_wead(component, WM8753_IOCTW) & 0x00ae;

	/* set mastew/swave audio intewface */
	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		bweak;
	case SND_SOC_DAIFMT_CBM_CFM:
		ioctw |= 0x1;
		fawwthwough;
	case SND_SOC_DAIFMT_CBM_CFS:
		hifi |= 0x0040;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		/* fwame invewsion not vawid fow DSP modes */
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			bweak;
		case SND_SOC_DAIFMT_IB_NF:
			hifi |= 0x0080;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_WIGHT_J:
	case SND_SOC_DAIFMT_WEFT_J:
		hifi &= ~0x0010;
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			bweak;
		case SND_SOC_DAIFMT_IB_IF:
			hifi |= 0x0090;
			bweak;
		case SND_SOC_DAIFMT_IB_NF:
			hifi |= 0x0080;
			bweak;
		case SND_SOC_DAIFMT_NB_IF:
			hifi |= 0x0010;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_wwite(component, WM8753_HIFI, hifi);
	snd_soc_component_wwite(component, WM8753_IOCTW, ioctw);
	wetuwn 0;
}

/*
 * Set PCM DAI bit size and sampwe wate.
 */
static int wm8753_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8753_pwiv *wm8753 = snd_soc_component_get_dwvdata(component);
	u16 swate = snd_soc_component_wead(component, WM8753_SWATE1) & 0x01c0;
	u16 hifi = snd_soc_component_wead(component, WM8753_HIFI) & 0x01f3;
	int coeff;

	/* is digitaw fiwtew coefficient vawid ? */
	coeff = get_coeff(wm8753->syscwk, pawams_wate(pawams));
	if (coeff < 0) {
		pwintk(KEWN_EWW "wm8753 invawid MCWK ow wate\n");
		wetuwn coeff;
	}
	snd_soc_component_wwite(component, WM8753_SWATE1, swate | (coeff_div[coeff].sw << 1) |
		coeff_div[coeff].usb);

	/* bit size */
	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		hifi |= 0x0004;
		bweak;
	case 24:
		hifi |= 0x0008;
		bweak;
	case 32:
		hifi |= 0x000c;
		bweak;
	}

	snd_soc_component_wwite(component, WM8753_HIFI, hifi);
	wetuwn 0;
}

static int wm8753_mode1v_set_dai_fmt(stwuct snd_soc_component *component,
		unsigned int fmt)
{
	u16 cwock;

	/* set cwk souwce as pcmcwk */
	cwock = snd_soc_component_wead(component, WM8753_CWOCK) & 0xfffb;
	snd_soc_component_wwite(component, WM8753_CWOCK, cwock);

	wetuwn wm8753_vdac_adc_set_dai_fmt(component, fmt);
}

static int wm8753_mode1h_set_dai_fmt(stwuct snd_soc_component *component,
		unsigned int fmt)
{
	wetuwn wm8753_hdac_set_dai_fmt(component, fmt);
}

static int wm8753_mode2_set_dai_fmt(stwuct snd_soc_component *component,
		unsigned int fmt)
{
	u16 cwock;

	/* set cwk souwce as pcmcwk */
	cwock = snd_soc_component_wead(component, WM8753_CWOCK) & 0xfffb;
	snd_soc_component_wwite(component, WM8753_CWOCK, cwock);

	wetuwn wm8753_vdac_adc_set_dai_fmt(component, fmt);
}

static int wm8753_mode3_4_set_dai_fmt(stwuct snd_soc_component *component,
		unsigned int fmt)
{
	u16 cwock;

	/* set cwk souwce as mcwk */
	cwock = snd_soc_component_wead(component, WM8753_CWOCK) & 0xfffb;
	snd_soc_component_wwite(component, WM8753_CWOCK, cwock | 0x4);

	if (wm8753_hdac_set_dai_fmt(component, fmt) < 0)
		wetuwn -EINVAW;
	wetuwn wm8753_vdac_adc_set_dai_fmt(component, fmt);
}

static int wm8753_hifi_wwite_dai_fmt(stwuct snd_soc_component *component,
		unsigned int fmt)
{
	stwuct wm8753_pwiv *wm8753 = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	switch (wm8753->dai_func) {
	case 0:
		wet = wm8753_mode1h_set_dai_fmt(component, fmt);
		bweak;
	case 1:
		wet = wm8753_mode2_set_dai_fmt(component, fmt);
		bweak;
	case 2:
	case 3:
		wet = wm8753_mode3_4_set_dai_fmt(component, fmt);
		bweak;
	defauwt:
		 bweak;
	}
	if (wet)
		wetuwn wet;

	wetuwn wm8753_i2s_set_dai_fmt(component, fmt);
}

static int wm8753_hifi_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wm8753_pwiv *wm8753 = snd_soc_component_get_dwvdata(component);

	wm8753->hifi_fmt = fmt;

	wetuwn wm8753_hifi_wwite_dai_fmt(component, fmt);
};

static int wm8753_voice_wwite_dai_fmt(stwuct snd_soc_component *component,
		unsigned int fmt)
{
	stwuct wm8753_pwiv *wm8753 = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	if (wm8753->dai_func != 0)
		wetuwn 0;

	wet = wm8753_mode1v_set_dai_fmt(component, fmt);
	if (wet)
		wetuwn wet;
	wet = wm8753_pcm_set_dai_fmt(component, fmt);
	if (wet)
		wetuwn wet;

	wetuwn 0;
};

static int wm8753_voice_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wm8753_pwiv *wm8753 = snd_soc_component_get_dwvdata(component);

	wm8753->voice_fmt = fmt;

	wetuwn wm8753_voice_wwite_dai_fmt(component, fmt);
};

static int wm8753_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	u16 mute_weg = snd_soc_component_wead(component, WM8753_DAC) & 0xfff7;
	stwuct wm8753_pwiv *wm8753 = snd_soc_component_get_dwvdata(component);

	/* the digitaw mute covews the HiFi and Voice DAC's on the WM8753.
	 * make suwe we check if they awe not both active when we mute */
	if (mute && wm8753->dai_func == 1) {
		if (!snd_soc_component_active(component))
			snd_soc_component_wwite(component, WM8753_DAC, mute_weg | 0x8);
	} ewse {
		if (mute)
			snd_soc_component_wwite(component, WM8753_DAC, mute_weg | 0x8);
		ewse
			snd_soc_component_wwite(component, WM8753_DAC, mute_weg);
	}

	wetuwn 0;
}

static void wm8753_chawge_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wm8753_pwiv *wm8753 =
		containew_of(wowk, stwuct wm8753_pwiv, chawge_wowk.wowk);

	/* Set to 500k */
	wegmap_update_bits(wm8753->wegmap, WM8753_PWW1, 0x0180, 0x0100);
}

static int wm8753_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	stwuct wm8753_pwiv *wm8753 = snd_soc_component_get_dwvdata(component);
	u16 pww_weg = snd_soc_component_wead(component, WM8753_PWW1) & 0xfe3e;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		/* set vmid to 50k and unmute dac */
		snd_soc_component_wwite(component, WM8753_PWW1, pww_weg | 0x00c0);
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		/* Wait untiw fuwwy chawged */
		fwush_dewayed_wowk(&wm8753->chawge_wowk);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			/* set vmid to 5k fow quick powew up */
			snd_soc_component_wwite(component, WM8753_PWW1, pww_weg | 0x01c1);
			scheduwe_dewayed_wowk(&wm8753->chawge_wowk,
				msecs_to_jiffies(caps_chawge));
		} ewse {
			/* mute dac and set vmid to 500k, enabwe VWEF */
			snd_soc_component_wwite(component, WM8753_PWW1, pww_weg | 0x0141);
		}
		bweak;
	case SND_SOC_BIAS_OFF:
		cancew_dewayed_wowk_sync(&wm8753->chawge_wowk);
		snd_soc_component_wwite(component, WM8753_PWW1, 0x0001);
		bweak;
	}
	wetuwn 0;
}

#define WM8753_WATES (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_11025 |\
		SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_22050 |\
		SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000 |\
		SNDWV_PCM_WATE_88200 | SNDWV_PCM_WATE_96000)

#define WM8753_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
	SNDWV_PCM_FMTBIT_S24_WE)

/*
 * The WM8753 suppowts up to 4 diffewent and mutuawwy excwusive DAI
 * configuwations. This gives 2 PCM's avaiwabwe fow use, hifi and voice.
 * NOTE: The Voice PCM cannot pway ow captuwe audio to the CPU as it's DAI
 * is connected between the wm8753 and a BT codec ow GSM modem.
 *
 * 1. Voice ovew PCM DAI - HIFI DAC ovew HIFI DAI
 * 2. Voice ovew HIFI DAI - HIFI disabwed
 * 3. Voice disabwed - HIFI ovew HIFI
 * 4. Voice disabwed - HIFI ovew HIFI, uses voice DAI WWC fow captuwe
 */
static const stwuct snd_soc_dai_ops wm8753_dai_ops_hifi_mode = {
	.hw_pawams	= wm8753_i2s_hw_pawams,
	.mute_stweam	= wm8753_mute,
	.set_fmt	= wm8753_hifi_set_dai_fmt,
	.set_cwkdiv	= wm8753_set_dai_cwkdiv,
	.set_pww	= wm8753_set_dai_pww,
	.set_syscwk	= wm8753_set_dai_syscwk,
	.no_captuwe_mute = 1,
};

static const stwuct snd_soc_dai_ops wm8753_dai_ops_voice_mode = {
	.hw_pawams	= wm8753_pcm_hw_pawams,
	.mute_stweam	= wm8753_mute,
	.set_fmt	= wm8753_voice_set_dai_fmt,
	.set_cwkdiv	= wm8753_set_dai_cwkdiv,
	.set_pww	= wm8753_set_dai_pww,
	.set_syscwk	= wm8753_set_dai_syscwk,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew wm8753_dai[] = {
/* DAI HiFi mode 1 */
{	.name = "wm8753-hifi",
	.pwayback = {
		.stweam_name = "HiFi Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8753_WATES,
		.fowmats = WM8753_FOWMATS
	},
	.captuwe = { /* dummy fow fast DAI switching */
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8753_WATES,
		.fowmats = WM8753_FOWMATS
	},
	.ops = &wm8753_dai_ops_hifi_mode,
},
/* DAI Voice mode 1 */
{	.name = "wm8753-voice",
	.pwayback = {
		.stweam_name = "Voice Pwayback",
		.channews_min = 1,
		.channews_max = 1,
		.wates = WM8753_WATES,
		.fowmats = WM8753_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8753_WATES,
		.fowmats = WM8753_FOWMATS,
	},
	.ops = &wm8753_dai_ops_voice_mode,
},
};

static int wm8753_wesume(stwuct snd_soc_component *component)
{
	stwuct wm8753_pwiv *wm8753 = snd_soc_component_get_dwvdata(component);

	wegcache_sync(wm8753->wegmap);

	wetuwn 0;
}

static int wm8753_pwobe(stwuct snd_soc_component *component)
{
	stwuct wm8753_pwiv *wm8753 = snd_soc_component_get_dwvdata(component);
	int wet;

	INIT_DEWAYED_WOWK(&wm8753->chawge_wowk, wm8753_chawge_wowk);

	wet = wm8753_weset(component);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to issue weset: %d\n", wet);
		wetuwn wet;
	}

	wm8753->dai_func = 0;

	/* set the update bits */
	snd_soc_component_update_bits(component, WM8753_WDAC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_WDAC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_WADC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_WADC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_WOUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_WOUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_WOUT2V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_WOUT2V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_WINVOW, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8753_WINVOW, 0x0100, 0x0100);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8753 = {
	.pwobe			= wm8753_pwobe,
	.wesume			= wm8753_wesume,
	.set_bias_wevew		= wm8753_set_bias_wevew,
	.contwows		= wm8753_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wm8753_snd_contwows),
	.dapm_widgets		= wm8753_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8753_dapm_widgets),
	.dapm_woutes		= wm8753_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm8753_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct of_device_id wm8753_of_match[] = {
	{ .compatibwe = "wwf,wm8753", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wm8753_of_match);

static const stwuct wegmap_config wm8753_wegmap = {
	.weg_bits = 7,
	.vaw_bits = 9,

	.max_wegistew = WM8753_ADCTW2,
	.vowatiwe_weg = wm8753_vowatiwe,

	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts = wm8753_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm8753_weg_defauwts),
};

#if defined(CONFIG_SPI_MASTEW)
static int wm8753_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wm8753_pwiv *wm8753;
	int wet;

	wm8753 = devm_kzawwoc(&spi->dev, sizeof(stwuct wm8753_pwiv),
			      GFP_KEWNEW);
	if (wm8753 == NUWW)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, wm8753);

	wm8753->wegmap = devm_wegmap_init_spi(spi, &wm8753_wegmap);
	if (IS_EWW(wm8753->wegmap)) {
		wet = PTW_EWW(wm8753->wegmap);
		dev_eww(&spi->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wet = devm_snd_soc_wegistew_component(&spi->dev, &soc_component_dev_wm8753,
				     wm8753_dai, AWWAY_SIZE(wm8753_dai));
	if (wet != 0)
		dev_eww(&spi->dev, "Faiwed to wegistew CODEC: %d\n", wet);

	wetuwn wet;
}

static stwuct spi_dwivew wm8753_spi_dwivew = {
	.dwivew = {
		.name	= "wm8753",
		.of_match_tabwe = wm8753_of_match,
	},
	.pwobe		= wm8753_spi_pwobe,
};
#endif /* CONFIG_SPI_MASTEW */

#if IS_ENABWED(CONFIG_I2C)
static int wm8753_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm8753_pwiv *wm8753;
	int wet;

	wm8753 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wm8753_pwiv),
			      GFP_KEWNEW);
	if (wm8753 == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, wm8753);

	wm8753->wegmap = devm_wegmap_init_i2c(i2c, &wm8753_wegmap);
	if (IS_EWW(wm8753->wegmap)) {
		wet = PTW_EWW(wm8753->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wet = devm_snd_soc_wegistew_component(&i2c->dev, &soc_component_dev_wm8753,
				     wm8753_dai, AWWAY_SIZE(wm8753_dai));
	if (wet != 0)
		dev_eww(&i2c->dev, "Faiwed to wegistew CODEC: %d\n", wet);

	wetuwn wet;
}

static const stwuct i2c_device_id wm8753_i2c_id[] = {
	{ "wm8753", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8753_i2c_id);

static stwuct i2c_dwivew wm8753_i2c_dwivew = {
	.dwivew = {
		.name = "wm8753",
		.of_match_tabwe = wm8753_of_match,
	},
	.pwobe = wm8753_i2c_pwobe,
	.id_tabwe = wm8753_i2c_id,
};
#endif

static int __init wm8753_modinit(void)
{
	int wet = 0;
#if IS_ENABWED(CONFIG_I2C)
	wet = i2c_add_dwivew(&wm8753_i2c_dwivew);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew wm8753 I2C dwivew: %d\n",
		       wet);
	}
#endif
#if defined(CONFIG_SPI_MASTEW)
	wet = spi_wegistew_dwivew(&wm8753_spi_dwivew);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew wm8753 SPI dwivew: %d\n",
		       wet);
	}
#endif
	wetuwn wet;
}
moduwe_init(wm8753_modinit);

static void __exit wm8753_exit(void)
{
#if IS_ENABWED(CONFIG_I2C)
	i2c_dew_dwivew(&wm8753_i2c_dwivew);
#endif
#if defined(CONFIG_SPI_MASTEW)
	spi_unwegistew_dwivew(&wm8753_spi_dwivew);
#endif
}
moduwe_exit(wm8753_exit);

MODUWE_DESCWIPTION("ASoC WM8753 dwivew");
MODUWE_AUTHOW("Wiam Giwdwood");
MODUWE_WICENSE("GPW");
