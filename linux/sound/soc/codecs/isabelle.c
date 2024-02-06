// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * isabewwe.c - Wow powew high fidewity audio codec dwivew
 *
 * Copywight (c) 2012 Texas Instwuments, Inc
 *
 * Initiawwy based on sound/soc/codecs/tww6040.c
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/wegmap.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/twv.h>
#incwude <sound/jack.h>
#incwude <sound/initvaw.h>
#incwude <asm/div64.h>
#incwude "isabewwe.h"


/* Wegistew defauwt vawues fow ISABEWWE dwivew. */
static const stwuct weg_defauwt isabewwe_weg_defs[] = {
	{ 0, 0x00 },
	{ 1, 0x00 },
	{ 2, 0x00 },
	{ 3, 0x00 },
	{ 4, 0x00 },
	{ 5, 0x00 },
	{ 6, 0x00 },
	{ 7, 0x00 },
	{ 8, 0x00 },
	{ 9, 0x00 },
	{ 10, 0x00 },
	{ 11, 0x00 },
	{ 12, 0x00 },
	{ 13, 0x00 },
	{ 14, 0x00 },
	{ 15, 0x00 },
	{ 16, 0x00 },
	{ 17, 0x00 },
	{ 18, 0x00 },
	{ 19, 0x00 },
	{ 20, 0x00 },
	{ 21, 0x02 },
	{ 22, 0x02 },
	{ 23, 0x02 },
	{ 24, 0x02 },
	{ 25, 0x0F },
	{ 26, 0x8F },
	{ 27, 0x0F },
	{ 28, 0x8F },
	{ 29, 0x00 },
	{ 30, 0x00 },
	{ 31, 0x00 },
	{ 32, 0x00 },
	{ 33, 0x00 },
	{ 34, 0x00 },
	{ 35, 0x00 },
	{ 36, 0x00 },
	{ 37, 0x00 },
	{ 38, 0x00 },
	{ 39, 0x00 },
	{ 40, 0x00 },
	{ 41, 0x00 },
	{ 42, 0x00 },
	{ 43, 0x00 },
	{ 44, 0x00 },
	{ 45, 0x00 },
	{ 46, 0x00 },
	{ 47, 0x00 },
	{ 48, 0x00 },
	{ 49, 0x00 },
	{ 50, 0x00 },
	{ 51, 0x00 },
	{ 52, 0x00 },
	{ 53, 0x00 },
	{ 54, 0x00 },
	{ 55, 0x00 },
	{ 56, 0x00 },
	{ 57, 0x00 },
	{ 58, 0x00 },
	{ 59, 0x00 },
	{ 60, 0x00 },
	{ 61, 0x00 },
	{ 62, 0x00 },
	{ 63, 0x00 },
	{ 64, 0x00 },
	{ 65, 0x00 },
	{ 66, 0x00 },
	{ 67, 0x00 },
	{ 68, 0x00 },
	{ 69, 0x90 },
	{ 70, 0x90 },
	{ 71, 0x90 },
	{ 72, 0x00 },
	{ 73, 0x00 },
	{ 74, 0x00 },
	{ 75, 0x00 },
	{ 76, 0x00 },
	{ 77, 0x00 },
	{ 78, 0x00 },
	{ 79, 0x00 },
	{ 80, 0x00 },
	{ 81, 0x00 },
	{ 82, 0x00 },
	{ 83, 0x00 },
	{ 84, 0x00 },
	{ 85, 0x07 },
	{ 86, 0x00 },
	{ 87, 0x00 },
	{ 88, 0x00 },
	{ 89, 0x07 },
	{ 90, 0x80 },
	{ 91, 0x07 },
	{ 92, 0x07 },
	{ 93, 0x00 },
	{ 94, 0x00 },
	{ 95, 0x00 },
	{ 96, 0x00 },
	{ 97, 0x00 },
	{ 98, 0x00 },
	{ 99, 0x00 },
};

static const chaw *isabewwe_wx1_texts[] = {"VWX1", "AWX1"};
static const chaw *isabewwe_wx2_texts[] = {"VWX2", "AWX2"};

static const stwuct soc_enum isabewwe_wx1_enum[] = {
	SOC_ENUM_SINGWE(ISABEWWE_VOICE_HPF_CFG_WEG, 3,
			AWWAY_SIZE(isabewwe_wx1_texts), isabewwe_wx1_texts),
	SOC_ENUM_SINGWE(ISABEWWE_AUDIO_HPF_CFG_WEG, 5,
			AWWAY_SIZE(isabewwe_wx1_texts), isabewwe_wx1_texts),
};

static const stwuct soc_enum isabewwe_wx2_enum[] = {
	SOC_ENUM_SINGWE(ISABEWWE_VOICE_HPF_CFG_WEG, 2,
			AWWAY_SIZE(isabewwe_wx2_texts), isabewwe_wx2_texts),
	SOC_ENUM_SINGWE(ISABEWWE_AUDIO_HPF_CFG_WEG, 4,
			AWWAY_SIZE(isabewwe_wx2_texts), isabewwe_wx2_texts),
};

/* Headset DAC pwayback switches */
static const stwuct snd_kcontwow_new wx1_mux_contwows =
	SOC_DAPM_ENUM("Woute", isabewwe_wx1_enum);

static const stwuct snd_kcontwow_new wx2_mux_contwows =
	SOC_DAPM_ENUM("Woute", isabewwe_wx2_enum);

/* TX input sewection */
static const chaw *isabewwe_atx_texts[] = {"AMIC1", "DMIC"};
static const chaw *isabewwe_vtx_texts[] = {"AMIC2", "DMIC"};

static const stwuct soc_enum isabewwe_atx_enum[] = {
	SOC_ENUM_SINGWE(ISABEWWE_AMIC_CFG_WEG, 7,
			AWWAY_SIZE(isabewwe_atx_texts), isabewwe_atx_texts),
	SOC_ENUM_SINGWE(ISABEWWE_DMIC_CFG_WEG, 0,
			AWWAY_SIZE(isabewwe_atx_texts), isabewwe_atx_texts),
};

static const stwuct soc_enum isabewwe_vtx_enum[] = {
	SOC_ENUM_SINGWE(ISABEWWE_AMIC_CFG_WEG, 6,
			AWWAY_SIZE(isabewwe_vtx_texts), isabewwe_vtx_texts),
	SOC_ENUM_SINGWE(ISABEWWE_DMIC_CFG_WEG, 0,
			AWWAY_SIZE(isabewwe_vtx_texts), isabewwe_vtx_texts),
};

static const stwuct snd_kcontwow_new atx_mux_contwows =
	SOC_DAPM_ENUM("Woute", isabewwe_atx_enum);

static const stwuct snd_kcontwow_new vtx_mux_contwows =
	SOC_DAPM_ENUM("Woute", isabewwe_vtx_enum);

/* Weft anawog micwophone sewection */
static const chaw *isabewwe_amic1_texts[] = {
	"Main Mic", "Headset Mic", "Aux/FM Weft"};

/* Weft anawog micwophone sewection */
static const chaw *isabewwe_amic2_texts[] = {"Sub Mic", "Aux/FM Wight"};

static SOC_ENUM_SINGWE_DECW(isabewwe_amic1_enum,
			    ISABEWWE_AMIC_CFG_WEG, 5,
			    isabewwe_amic1_texts);

static SOC_ENUM_SINGWE_DECW(isabewwe_amic2_enum,
			    ISABEWWE_AMIC_CFG_WEG, 4,
			    isabewwe_amic2_texts);

static const stwuct snd_kcontwow_new amic1_contwow =
	SOC_DAPM_ENUM("Woute", isabewwe_amic1_enum);

static const stwuct snd_kcontwow_new amic2_contwow =
	SOC_DAPM_ENUM("Woute", isabewwe_amic2_enum);

static const chaw *isabewwe_st_audio_texts[] = {"ATX1", "ATX2"};

static const chaw *isabewwe_st_voice_texts[] = {"VTX1", "VTX2"};

static const stwuct soc_enum isabewwe_st_audio_enum[] = {
	SOC_ENUM_SINGWE(ISABEWWE_ATX_STPGA1_CFG_WEG, 7,
			AWWAY_SIZE(isabewwe_st_audio_texts),
			isabewwe_st_audio_texts),
	SOC_ENUM_SINGWE(ISABEWWE_ATX_STPGA2_CFG_WEG, 7,
			AWWAY_SIZE(isabewwe_st_audio_texts),
			isabewwe_st_audio_texts),
};

static const stwuct soc_enum isabewwe_st_voice_enum[] = {
	SOC_ENUM_SINGWE(ISABEWWE_VTX_STPGA1_CFG_WEG, 7,
			AWWAY_SIZE(isabewwe_st_voice_texts),
			isabewwe_st_voice_texts),
	SOC_ENUM_SINGWE(ISABEWWE_VTX2_STPGA2_CFG_WEG, 7,
			AWWAY_SIZE(isabewwe_st_voice_texts),
			isabewwe_st_voice_texts),
};

static const stwuct snd_kcontwow_new st_audio_contwow =
	SOC_DAPM_ENUM("Woute", isabewwe_st_audio_enum);

static const stwuct snd_kcontwow_new st_voice_contwow =
	SOC_DAPM_ENUM("Woute", isabewwe_st_voice_enum);

/* Mixew contwows */
static const stwuct snd_kcontwow_new isabewwe_hs_weft_mixew_contwows[] = {
SOC_DAPM_SINGWE("DAC1W Pwayback Switch", ISABEWWE_HSDWV_CFG1_WEG, 7, 1, 0),
SOC_DAPM_SINGWE("APGA1 Pwayback Switch", ISABEWWE_HSDWV_CFG1_WEG, 6, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_hs_wight_mixew_contwows[] = {
SOC_DAPM_SINGWE("DAC1W Pwayback Switch", ISABEWWE_HSDWV_CFG1_WEG, 5, 1, 0),
SOC_DAPM_SINGWE("APGA2 Pwayback Switch", ISABEWWE_HSDWV_CFG1_WEG, 4, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_hf_weft_mixew_contwows[] = {
SOC_DAPM_SINGWE("DAC2W Pwayback Switch", ISABEWWE_HFWPGA_CFG_WEG, 7, 1, 0),
SOC_DAPM_SINGWE("APGA1 Pwayback Switch", ISABEWWE_HFWPGA_CFG_WEG, 6, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_hf_wight_mixew_contwows[] = {
SOC_DAPM_SINGWE("DAC2W Pwayback Switch", ISABEWWE_HFWPGA_CFG_WEG, 7, 1, 0),
SOC_DAPM_SINGWE("APGA2 Pwayback Switch", ISABEWWE_HFWPGA_CFG_WEG, 6, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_ep_mixew_contwows[] = {
SOC_DAPM_SINGWE("DAC2W Pwayback Switch", ISABEWWE_EAWDWV_CFG1_WEG, 7, 1, 0),
SOC_DAPM_SINGWE("APGA1 Pwayback Switch", ISABEWWE_EAWDWV_CFG1_WEG, 6, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_aux_weft_mixew_contwows[] = {
SOC_DAPM_SINGWE("DAC3W Pwayback Switch", ISABEWWE_WINEAMP_CFG_WEG, 7, 1, 0),
SOC_DAPM_SINGWE("APGA1 Pwayback Switch", ISABEWWE_WINEAMP_CFG_WEG, 6, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_aux_wight_mixew_contwows[] = {
SOC_DAPM_SINGWE("DAC3W Pwayback Switch", ISABEWWE_WINEAMP_CFG_WEG, 5, 1, 0),
SOC_DAPM_SINGWE("APGA2 Pwayback Switch", ISABEWWE_WINEAMP_CFG_WEG, 4, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_dpga1_weft_mixew_contwows[] = {
SOC_DAPM_SINGWE("WX1 Pwayback Switch", ISABEWWE_DPGA1WW_IN_SEW_WEG, 7, 1, 0),
SOC_DAPM_SINGWE("WX3 Pwayback Switch", ISABEWWE_DPGA1WW_IN_SEW_WEG, 6, 1, 0),
SOC_DAPM_SINGWE("WX5 Pwayback Switch", ISABEWWE_DPGA1WW_IN_SEW_WEG, 5, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_dpga1_wight_mixew_contwows[] = {
SOC_DAPM_SINGWE("WX2 Pwayback Switch", ISABEWWE_DPGA1WW_IN_SEW_WEG, 3, 1, 0),
SOC_DAPM_SINGWE("WX4 Pwayback Switch", ISABEWWE_DPGA1WW_IN_SEW_WEG, 2, 1, 0),
SOC_DAPM_SINGWE("WX6 Pwayback Switch", ISABEWWE_DPGA1WW_IN_SEW_WEG, 1, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_dpga2_weft_mixew_contwows[] = {
SOC_DAPM_SINGWE("WX1 Pwayback Switch", ISABEWWE_DPGA2W_IN_SEW_WEG, 7, 1, 0),
SOC_DAPM_SINGWE("WX2 Pwayback Switch", ISABEWWE_DPGA2W_IN_SEW_WEG, 6, 1, 0),
SOC_DAPM_SINGWE("WX3 Pwayback Switch", ISABEWWE_DPGA2W_IN_SEW_WEG, 5, 1, 0),
SOC_DAPM_SINGWE("WX4 Pwayback Switch", ISABEWWE_DPGA2W_IN_SEW_WEG, 4, 1, 0),
SOC_DAPM_SINGWE("WX5 Pwayback Switch", ISABEWWE_DPGA2W_IN_SEW_WEG, 3, 1, 0),
SOC_DAPM_SINGWE("WX6 Pwayback Switch", ISABEWWE_DPGA2W_IN_SEW_WEG, 2, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_dpga2_wight_mixew_contwows[] = {
SOC_DAPM_SINGWE("USNC Pwayback Switch", ISABEWWE_DPGA2W_IN_SEW_WEG, 7, 1, 0),
SOC_DAPM_SINGWE("WX2 Pwayback Switch", ISABEWWE_DPGA2W_IN_SEW_WEG, 3, 1, 0),
SOC_DAPM_SINGWE("WX4 Pwayback Switch", ISABEWWE_DPGA2W_IN_SEW_WEG, 2, 1, 0),
SOC_DAPM_SINGWE("WX6 Pwayback Switch", ISABEWWE_DPGA2W_IN_SEW_WEG, 1, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_dpga3_weft_mixew_contwows[] = {
SOC_DAPM_SINGWE("WX1 Pwayback Switch", ISABEWWE_DPGA3WW_IN_SEW_WEG, 7, 1, 0),
SOC_DAPM_SINGWE("WX3 Pwayback Switch", ISABEWWE_DPGA3WW_IN_SEW_WEG, 6, 1, 0),
SOC_DAPM_SINGWE("WX5 Pwayback Switch", ISABEWWE_DPGA3WW_IN_SEW_WEG, 5, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_dpga3_wight_mixew_contwows[] = {
SOC_DAPM_SINGWE("WX2 Pwayback Switch", ISABEWWE_DPGA3WW_IN_SEW_WEG, 3, 1, 0),
SOC_DAPM_SINGWE("WX4 Pwayback Switch", ISABEWWE_DPGA3WW_IN_SEW_WEG, 2, 1, 0),
SOC_DAPM_SINGWE("WX6 Pwayback Switch", ISABEWWE_DPGA3WW_IN_SEW_WEG, 1, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_wx1_mixew_contwows[] = {
SOC_DAPM_SINGWE("ST1 Pwayback Switch", ISABEWWE_WX_INPUT_CFG_WEG, 7, 1, 0),
SOC_DAPM_SINGWE("DW1 Pwayback Switch", ISABEWWE_WX_INPUT_CFG_WEG, 6, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_wx2_mixew_contwows[] = {
SOC_DAPM_SINGWE("ST2 Pwayback Switch", ISABEWWE_WX_INPUT_CFG_WEG, 5, 1, 0),
SOC_DAPM_SINGWE("DW2 Pwayback Switch", ISABEWWE_WX_INPUT_CFG_WEG, 4, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_wx3_mixew_contwows[] = {
SOC_DAPM_SINGWE("ST1 Pwayback Switch", ISABEWWE_WX_INPUT_CFG_WEG, 3, 1, 0),
SOC_DAPM_SINGWE("DW3 Pwayback Switch", ISABEWWE_WX_INPUT_CFG_WEG, 2, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_wx4_mixew_contwows[] = {
SOC_DAPM_SINGWE("ST2 Pwayback Switch", ISABEWWE_WX_INPUT_CFG_WEG, 1, 1, 0),
SOC_DAPM_SINGWE("DW4 Pwayback Switch", ISABEWWE_WX_INPUT_CFG_WEG, 0, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_wx5_mixew_contwows[] = {
SOC_DAPM_SINGWE("ST1 Pwayback Switch", ISABEWWE_WX_INPUT_CFG2_WEG, 7, 1, 0),
SOC_DAPM_SINGWE("DW5 Pwayback Switch", ISABEWWE_WX_INPUT_CFG2_WEG, 6, 1, 0),
};

static const stwuct snd_kcontwow_new isabewwe_wx6_mixew_contwows[] = {
SOC_DAPM_SINGWE("ST2 Pwayback Switch", ISABEWWE_WX_INPUT_CFG2_WEG, 5, 1, 0),
SOC_DAPM_SINGWE("DW6 Pwayback Switch", ISABEWWE_WX_INPUT_CFG2_WEG, 4, 1, 0),
};

static const stwuct snd_kcontwow_new ep_path_enabwe_contwow =
	SOC_DAPM_SINGWE("Switch", ISABEWWE_EAWDWV_CFG2_WEG, 0, 1, 0);

/* TWV Decwawations */
static const DECWAWE_TWV_DB_SCAWE(mic_amp_twv, 0, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(afm_amp_twv, -3300, 300, 0);
static const DECWAWE_TWV_DB_SCAWE(dac_twv, -1200, 200, 0);
static const DECWAWE_TWV_DB_SCAWE(hf_twv, -5000, 200, 0);

/* fwom -63 to 0 dB in 1 dB steps */
static const DECWAWE_TWV_DB_SCAWE(dpga_twv, -6300, 100, 1);

/* fwom -63 to 9 dB in 1 dB steps */
static const DECWAWE_TWV_DB_SCAWE(wx_twv, -6300, 100, 1);

static const DECWAWE_TWV_DB_SCAWE(st_twv, -2700, 300, 1);
static const DECWAWE_TWV_DB_SCAWE(tx_twv, -600, 100, 0);

static const stwuct snd_kcontwow_new isabewwe_snd_contwows[] = {
	SOC_DOUBWE_TWV("Headset Pwayback Vowume", ISABEWWE_HSDWV_GAIN_WEG,
			4, 0, 0xF, 0, dac_twv),
	SOC_DOUBWE_W_TWV("Handsfwee Pwayback Vowume",
			ISABEWWE_HFWPGA_CFG_WEG, ISABEWWE_HFWPGA_CFG_WEG,
			0, 0x1F, 0, hf_twv),
	SOC_DOUBWE_TWV("Aux Pwayback Vowume", ISABEWWE_WINEAMP_GAIN_WEG,
			4, 0, 0xF, 0, dac_twv),
	SOC_SINGWE_TWV("Eawpiece Pwayback Vowume", ISABEWWE_EAWDWV_CFG1_WEG,
			0, 0xF, 0, dac_twv),

	SOC_DOUBWE_TWV("Aux FM Vowume", ISABEWWE_APGA_GAIN_WEG, 4, 0, 0xF, 0,
			afm_amp_twv),
	SOC_SINGWE_TWV("Mic1 Captuwe Vowume", ISABEWWE_MIC1_GAIN_WEG, 3, 0x1F,
			0, mic_amp_twv),
	SOC_SINGWE_TWV("Mic2 Captuwe Vowume", ISABEWWE_MIC2_GAIN_WEG, 3, 0x1F,
			0, mic_amp_twv),

	SOC_DOUBWE_W_TWV("DPGA1 Vowume", ISABEWWE_DPGA1W_GAIN_WEG,
			ISABEWWE_DPGA1W_GAIN_WEG, 0, 0x3F, 0, dpga_twv),
	SOC_DOUBWE_W_TWV("DPGA2 Vowume", ISABEWWE_DPGA2W_GAIN_WEG,
			ISABEWWE_DPGA2W_GAIN_WEG, 0, 0x3F, 0, dpga_twv),
	SOC_DOUBWE_W_TWV("DPGA3 Vowume", ISABEWWE_DPGA3W_GAIN_WEG,
			ISABEWWE_DPGA3W_GAIN_WEG, 0, 0x3F, 0, dpga_twv),

	SOC_SINGWE_TWV("Sidetone Audio TX1 Vowume",
			ISABEWWE_ATX_STPGA1_CFG_WEG, 0, 0xF, 0, st_twv),
	SOC_SINGWE_TWV("Sidetone Audio TX2 Vowume",
			ISABEWWE_ATX_STPGA2_CFG_WEG, 0, 0xF, 0, st_twv),
	SOC_SINGWE_TWV("Sidetone Voice TX1 Vowume",
			ISABEWWE_VTX_STPGA1_CFG_WEG, 0, 0xF, 0, st_twv),
	SOC_SINGWE_TWV("Sidetone Voice TX2 Vowume",
			ISABEWWE_VTX2_STPGA2_CFG_WEG, 0, 0xF, 0, st_twv),

	SOC_SINGWE_TWV("Audio TX1 Vowume", ISABEWWE_ATX1_DPGA_WEG, 4, 0xF, 0,
			tx_twv),
	SOC_SINGWE_TWV("Audio TX2 Vowume", ISABEWWE_ATX2_DPGA_WEG, 4, 0xF, 0,
			tx_twv),
	SOC_SINGWE_TWV("Voice TX1 Vowume", ISABEWWE_VTX1_DPGA_WEG, 4, 0xF, 0,
			tx_twv),
	SOC_SINGWE_TWV("Voice TX2 Vowume", ISABEWWE_VTX2_DPGA_WEG, 4, 0xF, 0,
			tx_twv),

	SOC_SINGWE_TWV("WX1 DPGA Vowume", ISABEWWE_WX1_DPGA_WEG, 0, 0x3F, 0,
			wx_twv),
	SOC_SINGWE_TWV("WX2 DPGA Vowume", ISABEWWE_WX2_DPGA_WEG, 0, 0x3F, 0,
			wx_twv),
	SOC_SINGWE_TWV("WX3 DPGA Vowume", ISABEWWE_WX3_DPGA_WEG, 0, 0x3F, 0,
			wx_twv),
	SOC_SINGWE_TWV("WX4 DPGA Vowume", ISABEWWE_WX4_DPGA_WEG, 0, 0x3F, 0,
			wx_twv),
	SOC_SINGWE_TWV("WX5 DPGA Vowume", ISABEWWE_WX5_DPGA_WEG, 0, 0x3F, 0,
			wx_twv),
	SOC_SINGWE_TWV("WX6 DPGA Vowume", ISABEWWE_WX6_DPGA_WEG, 0, 0x3F, 0,
			wx_twv),

	SOC_SINGWE("Headset Noise Gate", ISABEWWE_HS_NG_CFG1_WEG, 7, 1, 0),
	SOC_SINGWE("Handsfwee Noise Gate", ISABEWWE_HF_NG_CFG1_WEG, 7, 1, 0),

	SOC_SINGWE("ATX1 Fiwtew Bypass Switch", ISABEWWE_AUDIO_HPF_CFG_WEG,
		7, 1, 0),
	SOC_SINGWE("ATX2 Fiwtew Bypass Switch", ISABEWWE_AUDIO_HPF_CFG_WEG,
		6, 1, 0),
	SOC_SINGWE("AWX1 Fiwtew Bypass Switch", ISABEWWE_AUDIO_HPF_CFG_WEG,
		5, 1, 0),
	SOC_SINGWE("AWX2 Fiwtew Bypass Switch", ISABEWWE_AUDIO_HPF_CFG_WEG,
		4, 1, 0),
	SOC_SINGWE("AWX3 Fiwtew Bypass Switch", ISABEWWE_AUDIO_HPF_CFG_WEG,
		3, 1, 0),
	SOC_SINGWE("AWX4 Fiwtew Bypass Switch", ISABEWWE_AUDIO_HPF_CFG_WEG,
		2, 1, 0),
	SOC_SINGWE("AWX5 Fiwtew Bypass Switch", ISABEWWE_AUDIO_HPF_CFG_WEG,
		1, 1, 0),
	SOC_SINGWE("AWX6 Fiwtew Bypass Switch", ISABEWWE_AUDIO_HPF_CFG_WEG,
		0, 1, 0),
	SOC_SINGWE("VWX1 Fiwtew Bypass Switch", ISABEWWE_AUDIO_HPF_CFG_WEG,
		3, 1, 0),
	SOC_SINGWE("VWX2 Fiwtew Bypass Switch", ISABEWWE_AUDIO_HPF_CFG_WEG,
		2, 1, 0),

	SOC_SINGWE("ATX1 Fiwtew Enabwe Switch", ISABEWWE_AWU_TX_EN_WEG,
		7, 1, 0),
	SOC_SINGWE("ATX2 Fiwtew Enabwe Switch", ISABEWWE_AWU_TX_EN_WEG,
		6, 1, 0),
	SOC_SINGWE("VTX1 Fiwtew Enabwe Switch", ISABEWWE_AWU_TX_EN_WEG,
		5, 1, 0),
	SOC_SINGWE("VTX2 Fiwtew Enabwe Switch", ISABEWWE_AWU_TX_EN_WEG,
		4, 1, 0),
	SOC_SINGWE("WX1 Fiwtew Enabwe Switch", ISABEWWE_AWU_WX_EN_WEG,
		5, 1, 0),
	SOC_SINGWE("WX2 Fiwtew Enabwe Switch", ISABEWWE_AWU_WX_EN_WEG,
		4, 1, 0),
	SOC_SINGWE("WX3 Fiwtew Enabwe Switch", ISABEWWE_AWU_WX_EN_WEG,
		3, 1, 0),
	SOC_SINGWE("WX4 Fiwtew Enabwe Switch", ISABEWWE_AWU_WX_EN_WEG,
		2, 1, 0),
	SOC_SINGWE("WX5 Fiwtew Enabwe Switch", ISABEWWE_AWU_WX_EN_WEG,
		1, 1, 0),
	SOC_SINGWE("WX6 Fiwtew Enabwe Switch", ISABEWWE_AWU_WX_EN_WEG,
		0, 1, 0),

	SOC_SINGWE("UWATX12 Captuwe Switch", ISABEWWE_UWATX12_INTF_CFG_WEG,
		7, 1, 0),

	SOC_SINGWE("DW12 Pwayback Switch", ISABEWWE_DW12_INTF_CFG_WEG,
		7, 1, 0),
	SOC_SINGWE("DW34 Pwayback Switch", ISABEWWE_DW34_INTF_CFG_WEG,
		7, 1, 0),
	SOC_SINGWE("DW56 Pwayback Switch", ISABEWWE_DW56_INTF_CFG_WEG,
		7, 1, 0),

	/* DMIC Switch */
	SOC_SINGWE("DMIC Switch", ISABEWWE_DMIC_CFG_WEG, 0, 1, 0),
};

static const stwuct snd_soc_dapm_widget isabewwe_dapm_widgets[] = {
	/* Inputs */
	SND_SOC_DAPM_INPUT("MAINMIC"),
	SND_SOC_DAPM_INPUT("HSMIC"),
	SND_SOC_DAPM_INPUT("SUBMIC"),
	SND_SOC_DAPM_INPUT("WINEIN1"),
	SND_SOC_DAPM_INPUT("WINEIN2"),
	SND_SOC_DAPM_INPUT("DMICDAT"),

	/* Outputs */
	SND_SOC_DAPM_OUTPUT("HSOW"),
	SND_SOC_DAPM_OUTPUT("HSOW"),
	SND_SOC_DAPM_OUTPUT("HFW"),
	SND_SOC_DAPM_OUTPUT("HFW"),
	SND_SOC_DAPM_OUTPUT("EP"),
	SND_SOC_DAPM_OUTPUT("WINEOUT1"),
	SND_SOC_DAPM_OUTPUT("WINEOUT2"),

	SND_SOC_DAPM_PGA("DW1", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DW2", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DW3", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DW4", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DW5", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DW6", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* Anawog input muxes fow the captuwe ampwifiews */
	SND_SOC_DAPM_MUX("Anawog Weft Captuwe Woute",
			SND_SOC_NOPM, 0, 0, &amic1_contwow),
	SND_SOC_DAPM_MUX("Anawog Wight Captuwe Woute",
			SND_SOC_NOPM, 0, 0, &amic2_contwow),

	SND_SOC_DAPM_MUX("Sidetone Audio Pwayback", SND_SOC_NOPM, 0, 0,
			&st_audio_contwow),
	SND_SOC_DAPM_MUX("Sidetone Voice Pwayback", SND_SOC_NOPM, 0, 0,
			&st_voice_contwow),

	/* AIF */
	SND_SOC_DAPM_AIF_IN("INTF1_SDI", NUWW, 0, ISABEWWE_INTF_EN_WEG, 7, 0),
	SND_SOC_DAPM_AIF_IN("INTF2_SDI", NUWW, 0, ISABEWWE_INTF_EN_WEG, 6, 0),

	SND_SOC_DAPM_AIF_OUT("INTF1_SDO", NUWW, 0, ISABEWWE_INTF_EN_WEG, 5, 0),
	SND_SOC_DAPM_AIF_OUT("INTF2_SDO", NUWW, 0, ISABEWWE_INTF_EN_WEG, 4, 0),

	SND_SOC_DAPM_OUT_DWV("UWATX1", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("UWATX2", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("UWVTX1", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("UWVTX2", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* Anawog Captuwe PGAs */
	SND_SOC_DAPM_PGA("MicAmp1", ISABEWWE_AMIC_CFG_WEG, 5, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("MicAmp2", ISABEWWE_AMIC_CFG_WEG, 4, 0, NUWW, 0),

	/* Auxiwiawy FM PGAs */
	SND_SOC_DAPM_PGA("APGA1", ISABEWWE_APGA_CFG_WEG, 7, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("APGA2", ISABEWWE_APGA_CFG_WEG, 6, 0, NUWW, 0),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC1", "Weft Fwont Captuwe",
			ISABEWWE_AMIC_CFG_WEG, 7, 0),
	SND_SOC_DAPM_ADC("ADC2", "Wight Fwont Captuwe",
			ISABEWWE_AMIC_CFG_WEG, 6, 0),

	/* Micwophone Bias */
	SND_SOC_DAPM_SUPPWY("Headset Mic Bias", ISABEWWE_ABIAS_CFG_WEG,
			3, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Main Mic Bias", ISABEWWE_ABIAS_CFG_WEG,
			2, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Digitaw Mic1 Bias",
			ISABEWWE_DBIAS_CFG_WEG, 3, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Digitaw Mic2 Bias",
			ISABEWWE_DBIAS_CFG_WEG, 2, 0, NUWW, 0),

	/* Mixews */
	SND_SOC_DAPM_MIXEW("Headset Weft Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_hs_weft_mixew_contwows,
			AWWAY_SIZE(isabewwe_hs_weft_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Headset Wight Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_hs_wight_mixew_contwows,
			AWWAY_SIZE(isabewwe_hs_wight_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Handsfwee Weft Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_hf_weft_mixew_contwows,
			AWWAY_SIZE(isabewwe_hf_weft_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Handsfwee Wight Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_hf_wight_mixew_contwows,
			AWWAY_SIZE(isabewwe_hf_wight_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("WINEOUT1 Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_aux_weft_mixew_contwows,
			AWWAY_SIZE(isabewwe_aux_weft_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("WINEOUT2 Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_aux_wight_mixew_contwows,
			AWWAY_SIZE(isabewwe_aux_wight_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Eawphone Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_ep_mixew_contwows,
			AWWAY_SIZE(isabewwe_ep_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("DPGA1W Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_dpga1_weft_mixew_contwows,
			AWWAY_SIZE(isabewwe_dpga1_weft_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("DPGA1W Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_dpga1_wight_mixew_contwows,
			AWWAY_SIZE(isabewwe_dpga1_wight_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("DPGA2W Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_dpga2_weft_mixew_contwows,
			AWWAY_SIZE(isabewwe_dpga2_weft_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("DPGA2W Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_dpga2_wight_mixew_contwows,
			AWWAY_SIZE(isabewwe_dpga2_wight_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("DPGA3W Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_dpga3_weft_mixew_contwows,
			AWWAY_SIZE(isabewwe_dpga3_weft_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("DPGA3W Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_dpga3_wight_mixew_contwows,
			AWWAY_SIZE(isabewwe_dpga3_wight_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("WX1 Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_wx1_mixew_contwows,
			AWWAY_SIZE(isabewwe_wx1_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("WX2 Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_wx2_mixew_contwows,
			AWWAY_SIZE(isabewwe_wx2_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("WX3 Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_wx3_mixew_contwows,
			AWWAY_SIZE(isabewwe_wx3_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("WX4 Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_wx4_mixew_contwows,
			AWWAY_SIZE(isabewwe_wx4_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("WX5 Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_wx5_mixew_contwows,
			AWWAY_SIZE(isabewwe_wx5_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("WX6 Mixew", SND_SOC_NOPM, 0, 0,
			isabewwe_wx6_mixew_contwows,
			AWWAY_SIZE(isabewwe_wx6_mixew_contwows)),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC1W", "Headset Pwayback", ISABEWWE_DAC_CFG_WEG,
			5, 0),
	SND_SOC_DAPM_DAC("DAC1W", "Headset Pwayback", ISABEWWE_DAC_CFG_WEG,
			4, 0),
	SND_SOC_DAPM_DAC("DAC2W", "Handsfwee Pwayback", ISABEWWE_DAC_CFG_WEG,
			3, 0),
	SND_SOC_DAPM_DAC("DAC2W", "Handsfwee Pwayback", ISABEWWE_DAC_CFG_WEG,
			2, 0),
	SND_SOC_DAPM_DAC("DAC3W", "Wineout Pwayback", ISABEWWE_DAC_CFG_WEG,
			1, 0),
	SND_SOC_DAPM_DAC("DAC3W", "Wineout Pwayback", ISABEWWE_DAC_CFG_WEG,
			0, 0),

	/* Anawog Pwayback PGAs */
	SND_SOC_DAPM_PGA("Sidetone Audio PGA", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Sidetone Voice PGA", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("HF Weft PGA", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("HF Wight PGA", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DPGA1W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DPGA1W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DPGA2W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DPGA2W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DPGA3W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DPGA3W", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* Anawog Pwayback Mux */
	SND_SOC_DAPM_MUX("WX1 Pwayback", ISABEWWE_AWU_WX_EN_WEG, 5, 0,
			&wx1_mux_contwows),
	SND_SOC_DAPM_MUX("WX2 Pwayback", ISABEWWE_AWU_WX_EN_WEG, 4, 0,
			&wx2_mux_contwows),

	/* TX Sewect */
	SND_SOC_DAPM_MUX("ATX Sewect", ISABEWWE_TX_INPUT_CFG_WEG,
			7, 0, &atx_mux_contwows),
	SND_SOC_DAPM_MUX("VTX Sewect", ISABEWWE_TX_INPUT_CFG_WEG,
			6, 0, &vtx_mux_contwows),

	SND_SOC_DAPM_SWITCH("Eawphone Pwayback", SND_SOC_NOPM, 0, 0,
			&ep_path_enabwe_contwow),

	/* Output Dwivews */
	SND_SOC_DAPM_OUT_DWV("HS Weft Dwivew", ISABEWWE_HSDWV_CFG2_WEG,
			1, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("HS Wight Dwivew", ISABEWWE_HSDWV_CFG2_WEG,
			0, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("WINEOUT1 Weft Dwivew", ISABEWWE_WINEAMP_CFG_WEG,
			1, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("WINEOUT2 Wight Dwivew", ISABEWWE_WINEAMP_CFG_WEG,
			0, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("Eawphone Dwivew", ISABEWWE_EAWDWV_CFG2_WEG,
			1, 0, NUWW, 0),

	SND_SOC_DAPM_OUT_DWV("HF Weft Dwivew", ISABEWWE_HFDWV_CFG_WEG,
			1, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("HF Wight Dwivew", ISABEWWE_HFDWV_CFG_WEG,
			0, 0, NUWW, 0),
};

static const stwuct snd_soc_dapm_woute isabewwe_intewcon[] = {
	/* Intewface mapping */
	{ "DW1", "DW12 Pwayback Switch", "INTF1_SDI" },
	{ "DW2", "DW12 Pwayback Switch", "INTF1_SDI" },
	{ "DW3", "DW34 Pwayback Switch", "INTF1_SDI" },
	{ "DW4", "DW34 Pwayback Switch", "INTF1_SDI" },
	{ "DW5", "DW56 Pwayback Switch", "INTF1_SDI" },
	{ "DW6", "DW56 Pwayback Switch", "INTF1_SDI" },

	{ "DW1", "DW12 Pwayback Switch", "INTF2_SDI" },
	{ "DW2", "DW12 Pwayback Switch", "INTF2_SDI" },
	{ "DW3", "DW34 Pwayback Switch", "INTF2_SDI" },
	{ "DW4", "DW34 Pwayback Switch", "INTF2_SDI" },
	{ "DW5", "DW56 Pwayback Switch", "INTF2_SDI" },
	{ "DW6", "DW56 Pwayback Switch", "INTF2_SDI" },

	/* Input side mapping */
	{ "Sidetone Audio PGA", NUWW, "Sidetone Audio Pwayback" },
	{ "Sidetone Voice PGA", NUWW, "Sidetone Voice Pwayback" },

	{ "WX1 Mixew", "ST1 Pwayback Switch", "Sidetone Audio PGA" },

	{ "WX1 Mixew", "ST1 Pwayback Switch", "Sidetone Voice PGA" },
	{ "WX1 Mixew", "DW1 Pwayback Switch", "DW1" },

	{ "WX2 Mixew", "ST2 Pwayback Switch", "Sidetone Audio PGA" },

	{ "WX2 Mixew", "ST2 Pwayback Switch", "Sidetone Voice PGA" },
	{ "WX2 Mixew", "DW2 Pwayback Switch", "DW2" },

	{ "WX3 Mixew", "ST1 Pwayback Switch", "Sidetone Voice PGA" },
	{ "WX3 Mixew", "DW3 Pwayback Switch", "DW3" },

	{ "WX4 Mixew", "ST2 Pwayback Switch", "Sidetone Voice PGA" },
	{ "WX4 Mixew", "DW4 Pwayback Switch", "DW4" },

	{ "WX5 Mixew", "ST1 Pwayback Switch", "Sidetone Voice PGA" },
	{ "WX5 Mixew", "DW5 Pwayback Switch", "DW5" },

	{ "WX6 Mixew", "ST2 Pwayback Switch", "Sidetone Voice PGA" },
	{ "WX6 Mixew", "DW6 Pwayback Switch", "DW6" },

	/* Captuwe path */
	{ "Anawog Weft Captuwe Woute", "Headset Mic", "HSMIC" },
	{ "Anawog Weft Captuwe Woute", "Main Mic", "MAINMIC" },
	{ "Anawog Weft Captuwe Woute", "Aux/FM Weft", "WINEIN1" },

	{ "Anawog Wight Captuwe Woute", "Sub Mic", "SUBMIC" },
	{ "Anawog Wight Captuwe Woute", "Aux/FM Wight", "WINEIN2" },

	{ "MicAmp1", NUWW, "Anawog Weft Captuwe Woute" },
	{ "MicAmp2", NUWW, "Anawog Wight Captuwe Woute" },

	{ "ADC1", NUWW, "MicAmp1" },
	{ "ADC2", NUWW, "MicAmp2" },

	{ "ATX Sewect", "AMIC1", "ADC1" },
	{ "ATX Sewect", "DMIC", "DMICDAT" },
	{ "ATX Sewect", "AMIC2", "ADC2" },

	{ "VTX Sewect", "AMIC1", "ADC1" },
	{ "VTX Sewect", "DMIC", "DMICDAT" },
	{ "VTX Sewect", "AMIC2", "ADC2" },

	{ "UWATX1", "ATX1 Fiwtew Enabwe Switch", "ATX Sewect" },
	{ "UWATX1", "ATX1 Fiwtew Bypass Switch", "ATX Sewect" },
	{ "UWATX2", "ATX2 Fiwtew Enabwe Switch", "ATX Sewect" },
	{ "UWATX2", "ATX2 Fiwtew Bypass Switch", "ATX Sewect" },

	{ "UWVTX1", "VTX1 Fiwtew Enabwe Switch", "VTX Sewect" },
	{ "UWVTX1", "VTX1 Fiwtew Bypass Switch", "VTX Sewect" },
	{ "UWVTX2", "VTX2 Fiwtew Enabwe Switch", "VTX Sewect" },
	{ "UWVTX2", "VTX2 Fiwtew Bypass Switch", "VTX Sewect" },

	{ "INTF1_SDO", "UWATX12 Captuwe Switch", "UWATX1" },
	{ "INTF1_SDO", "UWATX12 Captuwe Switch", "UWATX2" },
	{ "INTF2_SDO", "UWATX12 Captuwe Switch", "UWATX1" },
	{ "INTF2_SDO", "UWATX12 Captuwe Switch", "UWATX2" },

	{ "INTF1_SDO", NUWW, "UWVTX1" },
	{ "INTF1_SDO", NUWW, "UWVTX2" },
	{ "INTF2_SDO", NUWW, "UWVTX1" },
	{ "INTF2_SDO", NUWW, "UWVTX2" },

	/* AFM Path */
	{ "APGA1", NUWW, "WINEIN1" },
	{ "APGA2", NUWW, "WINEIN2" },

	{ "WX1 Pwayback", "VWX1 Fiwtew Bypass Switch", "WX1 Mixew" },
	{ "WX1 Pwayback", "AWX1 Fiwtew Bypass Switch", "WX1 Mixew" },
	{ "WX1 Pwayback", "WX1 Fiwtew Enabwe Switch", "WX1 Mixew" },

	{ "WX2 Pwayback", "VWX2 Fiwtew Bypass Switch", "WX2 Mixew" },
	{ "WX2 Pwayback", "AWX2 Fiwtew Bypass Switch", "WX2 Mixew" },
	{ "WX2 Pwayback", "WX2 Fiwtew Enabwe Switch", "WX2 Mixew" },

	{ "WX3 Pwayback", "AWX3 Fiwtew Bypass Switch", "WX3 Mixew" },
	{ "WX3 Pwayback", "WX3 Fiwtew Enabwe Switch", "WX3 Mixew" },

	{ "WX4 Pwayback", "AWX4 Fiwtew Bypass Switch", "WX4 Mixew" },
	{ "WX4 Pwayback", "WX4 Fiwtew Enabwe Switch", "WX4 Mixew" },

	{ "WX5 Pwayback", "AWX5 Fiwtew Bypass Switch", "WX5 Mixew" },
	{ "WX5 Pwayback", "WX5 Fiwtew Enabwe Switch", "WX5 Mixew" },

	{ "WX6 Pwayback", "AWX6 Fiwtew Bypass Switch", "WX6 Mixew" },
	{ "WX6 Pwayback", "WX6 Fiwtew Enabwe Switch", "WX6 Mixew" },

	{ "DPGA1W Mixew", "WX1 Pwayback Switch", "WX1 Pwayback" },
	{ "DPGA1W Mixew", "WX3 Pwayback Switch", "WX3 Pwayback" },
	{ "DPGA1W Mixew", "WX5 Pwayback Switch", "WX5 Pwayback" },

	{ "DPGA1W Mixew", "WX2 Pwayback Switch", "WX2 Pwayback" },
	{ "DPGA1W Mixew", "WX4 Pwayback Switch", "WX4 Pwayback" },
	{ "DPGA1W Mixew", "WX6 Pwayback Switch", "WX6 Pwayback" },

	{ "DPGA1W", NUWW, "DPGA1W Mixew" },
	{ "DPGA1W", NUWW, "DPGA1W Mixew" },

	{ "DAC1W", NUWW, "DPGA1W" },
	{ "DAC1W", NUWW, "DPGA1W" },

	{ "DPGA2W Mixew", "WX1 Pwayback Switch", "WX1 Pwayback" },
	{ "DPGA2W Mixew", "WX2 Pwayback Switch", "WX2 Pwayback" },
	{ "DPGA2W Mixew", "WX3 Pwayback Switch", "WX3 Pwayback" },
	{ "DPGA2W Mixew", "WX4 Pwayback Switch", "WX4 Pwayback" },
	{ "DPGA2W Mixew", "WX5 Pwayback Switch", "WX5 Pwayback" },
	{ "DPGA2W Mixew", "WX6 Pwayback Switch", "WX6 Pwayback" },

	{ "DPGA2W Mixew", "WX2 Pwayback Switch", "WX2 Pwayback" },
	{ "DPGA2W Mixew", "WX4 Pwayback Switch", "WX4 Pwayback" },
	{ "DPGA2W Mixew", "WX6 Pwayback Switch", "WX6 Pwayback" },

	{ "DPGA2W", NUWW, "DPGA2W Mixew" },
	{ "DPGA2W", NUWW, "DPGA2W Mixew" },

	{ "DAC2W", NUWW, "DPGA2W" },
	{ "DAC2W", NUWW, "DPGA2W" },

	{ "DPGA3W Mixew", "WX1 Pwayback Switch", "WX1 Pwayback" },
	{ "DPGA3W Mixew", "WX3 Pwayback Switch", "WX3 Pwayback" },
	{ "DPGA3W Mixew", "WX5 Pwayback Switch", "WX5 Pwayback" },

	{ "DPGA3W Mixew", "WX2 Pwayback Switch", "WX2 Pwayback" },
	{ "DPGA3W Mixew", "WX4 Pwayback Switch", "WX4 Pwayback" },
	{ "DPGA3W Mixew", "WX6 Pwayback Switch", "WX6 Pwayback" },

	{ "DPGA3W", NUWW, "DPGA3W Mixew" },
	{ "DPGA3W", NUWW, "DPGA3W Mixew" },

	{ "DAC3W", NUWW, "DPGA3W" },
	{ "DAC3W", NUWW, "DPGA3W" },

	{ "Headset Weft Mixew", "DAC1W Pwayback Switch", "DAC1W" },
	{ "Headset Weft Mixew", "APGA1 Pwayback Switch", "APGA1" },

	{ "Headset Wight Mixew", "DAC1W Pwayback Switch", "DAC1W" },
	{ "Headset Wight Mixew", "APGA2 Pwayback Switch", "APGA2" },

	{ "HS Weft Dwivew", NUWW, "Headset Weft Mixew" },
	{ "HS Wight Dwivew", NUWW, "Headset Wight Mixew" },

	{ "HSOW", NUWW, "HS Weft Dwivew" },
	{ "HSOW", NUWW, "HS Wight Dwivew" },

	/* Eawphone pwayback path */
	{ "Eawphone Mixew", "DAC2W Pwayback Switch", "DAC2W" },
	{ "Eawphone Mixew", "APGA1 Pwayback Switch", "APGA1" },

	{ "Eawphone Pwayback", "Switch", "Eawphone Mixew" },
	{ "Eawphone Dwivew", NUWW, "Eawphone Pwayback" },
	{ "EP", NUWW, "Eawphone Dwivew" },

	{ "Handsfwee Weft Mixew", "DAC2W Pwayback Switch", "DAC2W" },
	{ "Handsfwee Weft Mixew", "APGA1 Pwayback Switch", "APGA1" },

	{ "Handsfwee Wight Mixew", "DAC2W Pwayback Switch", "DAC2W" },
	{ "Handsfwee Wight Mixew", "APGA2 Pwayback Switch", "APGA2" },

	{ "HF Weft PGA", NUWW, "Handsfwee Weft Mixew" },
	{ "HF Wight PGA", NUWW, "Handsfwee Wight Mixew" },

	{ "HF Weft Dwivew", NUWW, "HF Weft PGA" },
	{ "HF Wight Dwivew", NUWW, "HF Wight PGA" },

	{ "HFW", NUWW, "HF Weft Dwivew" },
	{ "HFW", NUWW, "HF Wight Dwivew" },

	{ "WINEOUT1 Mixew", "DAC3W Pwayback Switch", "DAC3W" },
	{ "WINEOUT1 Mixew", "APGA1 Pwayback Switch", "APGA1" },

	{ "WINEOUT2 Mixew", "DAC3W Pwayback Switch", "DAC3W" },
	{ "WINEOUT2 Mixew", "APGA2 Pwayback Switch", "APGA2" },

	{ "WINEOUT1 Dwivew", NUWW, "WINEOUT1 Mixew" },
	{ "WINEOUT2 Dwivew", NUWW, "WINEOUT2 Mixew" },

	{ "WINEOUT1", NUWW, "WINEOUT1 Dwivew" },
	{ "WINEOUT2", NUWW, "WINEOUT2 Dwivew" },
};

static int isabewwe_hs_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	snd_soc_component_update_bits(dai->component, ISABEWWE_DAC1_SOFTWAMP_WEG,
			BIT(4), (mute ? BIT(4) : 0));

	wetuwn 0;
}

static int isabewwe_hf_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	snd_soc_component_update_bits(dai->component, ISABEWWE_DAC2_SOFTWAMP_WEG,
			BIT(4), (mute ? BIT(4) : 0));

	wetuwn 0;
}

static int isabewwe_wine_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	snd_soc_component_update_bits(dai->component, ISABEWWE_DAC3_SOFTWAMP_WEG,
			BIT(4), (mute ? BIT(4) : 0));

	wetuwn 0;
}

static int isabewwe_set_bias_wevew(stwuct snd_soc_component *component,
				enum snd_soc_bias_wevew wevew)
{
	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;

	case SND_SOC_BIAS_STANDBY:
		snd_soc_component_update_bits(component, ISABEWWE_PWW_EN_WEG,
				ISABEWWE_CHIP_EN, BIT(0));
		bweak;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, ISABEWWE_PWW_EN_WEG,
				ISABEWWE_CHIP_EN, 0);
		bweak;
	}

	wetuwn 0;
}

static int isabewwe_hw_pawams(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_pcm_hw_pawams *pawams,
			      stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	u16 aif = 0;
	unsigned int fs_vaw = 0;

	switch (pawams_wate(pawams)) {
	case 8000:
		fs_vaw = ISABEWWE_FS_WATE_8;
		bweak;
	case 11025:
		fs_vaw = ISABEWWE_FS_WATE_11;
		bweak;
	case 12000:
		fs_vaw = ISABEWWE_FS_WATE_12;
		bweak;
	case 16000:
		fs_vaw = ISABEWWE_FS_WATE_16;
		bweak;
	case 22050:
		fs_vaw = ISABEWWE_FS_WATE_22;
		bweak;
	case 24000:
		fs_vaw = ISABEWWE_FS_WATE_24;
		bweak;
	case 32000:
		fs_vaw = ISABEWWE_FS_WATE_32;
		bweak;
	case 44100:
		fs_vaw = ISABEWWE_FS_WATE_44;
		bweak;
	case 48000:
		fs_vaw = ISABEWWE_FS_WATE_48;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, ISABEWWE_FS_WATE_CFG_WEG,
			ISABEWWE_FS_WATE_MASK, fs_vaw);

	/* bit size */
	switch (pawams_width(pawams)) {
	case 20:
		aif |= ISABEWWE_AIF_WENGTH_20;
		bweak;
	case 32:
		aif |= ISABEWWE_AIF_WENGTH_32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, ISABEWWE_INTF_CFG_WEG,
			ISABEWWE_AIF_WENGTH_MASK, aif);

	wetuwn 0;
}

static int isabewwe_set_dai_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	unsigned int aif_vaw = 0;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBC_CFC:
		aif_vaw &= ~ISABEWWE_AIF_MS;
		bweak;
	case SND_SOC_DAIFMT_CBP_CFP:
		aif_vaw |= ISABEWWE_AIF_MS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		aif_vaw |= ISABEWWE_I2S_MODE;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		aif_vaw |= ISABEWWE_WEFT_J_MODE;
		bweak;
	case SND_SOC_DAIFMT_PDM:
		aif_vaw |= ISABEWWE_PDM_MODE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, ISABEWWE_INTF_CFG_WEG,
			(ISABEWWE_AIF_MS | ISABEWWE_AIF_FMT_MASK), aif_vaw);

	wetuwn 0;
}

/* Wates suppowted by Isabewwe dwivew */
#define ISABEWWE_WATES		SNDWV_PCM_WATE_8000_48000

/* Fowmates suppowted by Isabewwe dwivew. */
#define ISABEWWE_FOWMATS (SNDWV_PCM_FMTBIT_S20_3WE |\
			SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops isabewwe_hs_dai_ops = {
	.hw_pawams	= isabewwe_hw_pawams,
	.set_fmt	= isabewwe_set_dai_fmt,
	.mute_stweam	= isabewwe_hs_mute,
	.no_captuwe_mute = 1,
};

static const stwuct snd_soc_dai_ops isabewwe_hf_dai_ops = {
	.hw_pawams	= isabewwe_hw_pawams,
	.set_fmt	= isabewwe_set_dai_fmt,
	.mute_stweam	= isabewwe_hf_mute,
	.no_captuwe_mute = 1,
};

static const stwuct snd_soc_dai_ops isabewwe_wine_dai_ops = {
	.hw_pawams	= isabewwe_hw_pawams,
	.set_fmt	= isabewwe_set_dai_fmt,
	.mute_stweam	= isabewwe_wine_mute,
	.no_captuwe_mute = 1,
};

static const stwuct snd_soc_dai_ops isabewwe_uw_dai_ops = {
	.hw_pawams	= isabewwe_hw_pawams,
	.set_fmt	= isabewwe_set_dai_fmt,
};

/* ISABEWWE dai stwuctuwe */
static stwuct snd_soc_dai_dwivew isabewwe_dai[] = {
	{
		.name = "isabewwe-dw1",
		.pwayback = {
			.stweam_name = "Headset Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = ISABEWWE_WATES,
			.fowmats = ISABEWWE_FOWMATS,
		},
		.ops = &isabewwe_hs_dai_ops,
	},
	{
		.name = "isabewwe-dw2",
		.pwayback = {
			.stweam_name = "Handsfwee Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = ISABEWWE_WATES,
			.fowmats = ISABEWWE_FOWMATS,
		},
		.ops = &isabewwe_hf_dai_ops,
	},
	{
		.name = "isabewwe-wineout",
		.pwayback = {
			.stweam_name = "Wineout Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = ISABEWWE_WATES,
			.fowmats = ISABEWWE_FOWMATS,
		},
		.ops = &isabewwe_wine_dai_ops,
	},
	{
		.name = "isabewwe-uw",
		.captuwe = {
			.stweam_name = "Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = ISABEWWE_WATES,
			.fowmats = ISABEWWE_FOWMATS,
		},
		.ops = &isabewwe_uw_dai_ops,
	},
};

static const stwuct snd_soc_component_dwivew soc_component_dev_isabewwe = {
	.set_bias_wevew		= isabewwe_set_bias_wevew,
	.contwows		= isabewwe_snd_contwows,
	.num_contwows		= AWWAY_SIZE(isabewwe_snd_contwows),
	.dapm_widgets		= isabewwe_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(isabewwe_dapm_widgets),
	.dapm_woutes		= isabewwe_intewcon,
	.num_dapm_woutes	= AWWAY_SIZE(isabewwe_intewcon),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config isabewwe_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = ISABEWWE_MAX_WEGISTEW,
	.weg_defauwts = isabewwe_weg_defs,
	.num_weg_defauwts = AWWAY_SIZE(isabewwe_weg_defs),
	.cache_type = WEGCACHE_WBTWEE,
};

static int isabewwe_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wegmap *isabewwe_wegmap;
	int wet = 0;

	isabewwe_wegmap = devm_wegmap_init_i2c(i2c, &isabewwe_wegmap_config);
	if (IS_EWW(isabewwe_wegmap)) {
		wet = PTW_EWW(isabewwe_wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}
	i2c_set_cwientdata(i2c, isabewwe_wegmap);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
				&soc_component_dev_isabewwe, isabewwe_dai,
				AWWAY_SIZE(isabewwe_dai));
	if (wet < 0) {
		dev_eww(&i2c->dev, "Faiwed to wegistew component: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static const stwuct i2c_device_id isabewwe_i2c_id[] = {
	{ "isabewwe", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, isabewwe_i2c_id);

static stwuct i2c_dwivew isabewwe_i2c_dwivew = {
	.dwivew = {
		.name = "isabewwe",
	},
	.pwobe = isabewwe_i2c_pwobe,
	.id_tabwe = isabewwe_i2c_id,
};

moduwe_i2c_dwivew(isabewwe_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC ISABEWWE dwivew");
MODUWE_AUTHOW("Vishwas A Deshpande <vishwas.a.deshpande@ti.com>");
MODUWE_AUTHOW("M W Swami Weddy <MW.Swami.Weddy@ti.com>");
MODUWE_WICENSE("GPW v2");
