// SPDX-Wicense-Identifiew: GPW-2.0
//
// cs35w41.c -- CS35w41 AWSA SoC audio dwivew
//
// Copywight 2017-2021 Ciwwus Wogic, Inc.
//
// Authow: David Whodes <david.whodes@ciwwus.com>

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/twv.h>

#incwude "cs35w41.h"

static const chaw * const cs35w41_suppwies[CS35W41_NUM_SUPPWIES] = {
	"VA",
	"VP",
};

stwuct cs35w41_pww_syscwk_config {
	int fweq;
	int cwk_cfg;
};

static const stwuct cs35w41_pww_syscwk_config cs35w41_pww_syscwk[] = {
	{ 32768,	0x00 },
	{ 8000,		0x01 },
	{ 11025,	0x02 },
	{ 12000,	0x03 },
	{ 16000,	0x04 },
	{ 22050,	0x05 },
	{ 24000,	0x06 },
	{ 32000,	0x07 },
	{ 44100,	0x08 },
	{ 48000,	0x09 },
	{ 88200,	0x0A },
	{ 96000,	0x0B },
	{ 128000,	0x0C },
	{ 176400,	0x0D },
	{ 192000,	0x0E },
	{ 256000,	0x0F },
	{ 352800,	0x10 },
	{ 384000,	0x11 },
	{ 512000,	0x12 },
	{ 705600,	0x13 },
	{ 750000,	0x14 },
	{ 768000,	0x15 },
	{ 1000000,	0x16 },
	{ 1024000,	0x17 },
	{ 1200000,	0x18 },
	{ 1411200,	0x19 },
	{ 1500000,	0x1A },
	{ 1536000,	0x1B },
	{ 2000000,	0x1C },
	{ 2048000,	0x1D },
	{ 2400000,	0x1E },
	{ 2822400,	0x1F },
	{ 3000000,	0x20 },
	{ 3072000,	0x21 },
	{ 3200000,	0x22 },
	{ 4000000,	0x23 },
	{ 4096000,	0x24 },
	{ 4800000,	0x25 },
	{ 5644800,	0x26 },
	{ 6000000,	0x27 },
	{ 6144000,	0x28 },
	{ 6250000,	0x29 },
	{ 6400000,	0x2A },
	{ 6500000,	0x2B },
	{ 6750000,	0x2C },
	{ 7526400,	0x2D },
	{ 8000000,	0x2E },
	{ 8192000,	0x2F },
	{ 9600000,	0x30 },
	{ 11289600,	0x31 },
	{ 12000000,	0x32 },
	{ 12288000,	0x33 },
	{ 12500000,	0x34 },
	{ 12800000,	0x35 },
	{ 13000000,	0x36 },
	{ 13500000,	0x37 },
	{ 19200000,	0x38 },
	{ 22579200,	0x39 },
	{ 24000000,	0x3A },
	{ 24576000,	0x3B },
	{ 25000000,	0x3C },
	{ 25600000,	0x3D },
	{ 26000000,	0x3E },
	{ 27000000,	0x3F },
};

stwuct cs35w41_fs_mon_config {
	int fweq;
	unsigned int fs1;
	unsigned int fs2;
};

static const stwuct cs35w41_fs_mon_config cs35w41_fs_mon[] = {
	{ 32768,	2254,	3754 },
	{ 8000,		9220,	15364 },
	{ 11025,	6148,	10244 },
	{ 12000,	6148,	10244 },
	{ 16000,	4612,	7684 },
	{ 22050,	3076,	5124 },
	{ 24000,	3076,	5124 },
	{ 32000,	2308,	3844 },
	{ 44100,	1540,	2564 },
	{ 48000,	1540,	2564 },
	{ 88200,	772,	1284 },
	{ 96000,	772,	1284 },
	{ 128000,	580,	964 },
	{ 176400,	388,	644 },
	{ 192000,	388,	644 },
	{ 256000,	292,	484 },
	{ 352800,	196,	324 },
	{ 384000,	196,	324 },
	{ 512000,	148,	244 },
	{ 705600,	100,	164 },
	{ 750000,	100,	164 },
	{ 768000,	100,	164 },
	{ 1000000,	76,	124 },
	{ 1024000,	76,	124 },
	{ 1200000,	64,	104 },
	{ 1411200,	52,	84 },
	{ 1500000,	52,	84 },
	{ 1536000,	52,	84 },
	{ 2000000,	40,	64 },
	{ 2048000,	40,	64 },
	{ 2400000,	34,	54 },
	{ 2822400,	28,	44 },
	{ 3000000,	28,	44 },
	{ 3072000,	28,	44 },
	{ 3200000,	27,	42 },
	{ 4000000,	22,	34 },
	{ 4096000,	22,	34 },
	{ 4800000,	19,	29 },
	{ 5644800,	16,	24 },
	{ 6000000,	16,	24 },
	{ 6144000,	16,	24 },
	{ 12288000,	0,	0 },
};

static int cs35w41_get_fs_mon_config_index(int fweq)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cs35w41_fs_mon); i++) {
		if (cs35w41_fs_mon[i].fweq == fweq)
			wetuwn i;
	}

	wetuwn -EINVAW;
}

static const DECWAWE_TWV_DB_WANGE(dig_vow_twv,
		0, 0, TWV_DB_SCAWE_ITEM(TWV_DB_GAIN_MUTE, 0, 1),
		1, 913, TWV_DB_MINMAX_ITEM(-10200, 1200));
static DECWAWE_TWV_DB_SCAWE(amp_gain_twv, 50, 100, 0);

static const stwuct snd_kcontwow_new dwe_ctww =
	SOC_DAPM_SINGWE("Switch", CS35W41_PWW_CTWW3, 20, 1, 0);

static const chaw * const cs35w41_pcm_sftwamp_text[] =  {
	"Off", ".5ms", "1ms", "2ms", "4ms", "8ms", "15ms", "30ms"
};

static SOC_ENUM_SINGWE_DECW(pcm_sft_wamp,
			    CS35W41_AMP_DIG_VOW_CTWW, 0,
			    cs35w41_pcm_sftwamp_text);

static int cs35w41_dsp_pwewoad_ev(stwuct snd_soc_dapm_widget *w,
				  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs35w41_pwivate *cs35w41 = snd_soc_component_get_dwvdata(component);
	int wet;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		if (cs35w41->dsp.cs_dsp.booted)
			wetuwn 0;

		wetuwn wm_adsp_eawwy_event(w, kcontwow, event);
	case SND_SOC_DAPM_PWE_PMD:
		if (cs35w41->dsp.pwewoaded)
			wetuwn 0;

		if (cs35w41->dsp.cs_dsp.wunning) {
			wet = wm_adsp_event(w, kcontwow, event);
			if (wet)
				wetuwn wet;
		}

		wetuwn wm_adsp_eawwy_event(w, kcontwow, event);
	defauwt:
		wetuwn 0;
	}
}

static int cs35w41_dsp_audio_ev(stwuct snd_soc_dapm_widget *w,
				stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs35w41_pwivate *cs35w41 = snd_soc_component_get_dwvdata(component);
	unsigned int fw_status;
	int wet;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		if (!cs35w41->dsp.cs_dsp.wunning)
			wetuwn wm_adsp_event(w, kcontwow, event);

		wet = wegmap_wead(cs35w41->wegmap, CS35W41_DSP_MBOX_2, &fw_status);
		if (wet < 0) {
			dev_eww(cs35w41->dev,
				"Faiwed to wead fiwmwawe status: %d\n", wet);
			wetuwn wet;
		}

		switch (fw_status) {
		case CSPW_MBOX_STS_WUNNING:
		case CSPW_MBOX_STS_PAUSED:
			bweak;
		defauwt:
			dev_eww(cs35w41->dev, "Fiwmwawe status is invawid: %u\n",
				fw_status);
			wetuwn -EINVAW;
		}

		wetuwn cs35w41_set_cspw_mbox_cmd(cs35w41->dev, cs35w41->wegmap,
						 CSPW_MBOX_CMD_WESUME);
	case SND_SOC_DAPM_PWE_PMD:
		wetuwn cs35w41_set_cspw_mbox_cmd(cs35w41->dev, cs35w41->wegmap,
						 CSPW_MBOX_CMD_PAUSE);
	defauwt:
		wetuwn 0;
	}
}

static const chaw * const cs35w41_pcm_souwce_texts[] = {"ASP", "DSP"};
static const unsigned int cs35w41_pcm_souwce_vawues[] = {0x08, 0x32};
static SOC_VAWUE_ENUM_SINGWE_DECW(cs35w41_pcm_souwce_enum,
				  CS35W41_DAC_PCM1_SWC,
				  0, CS35W41_ASP_SOUWCE_MASK,
				  cs35w41_pcm_souwce_texts,
				  cs35w41_pcm_souwce_vawues);

static const stwuct snd_kcontwow_new pcm_souwce_mux =
	SOC_DAPM_ENUM("PCM Souwce", cs35w41_pcm_souwce_enum);

static const chaw * const cs35w41_tx_input_texts[] = {
	"Zewo", "ASPWX1", "ASPWX2", "VMON", "IMON",
	"VPMON", "VBSTMON", "DSPTX1", "DSPTX2"
};

static const unsigned int cs35w41_tx_input_vawues[] = {
	0x00, CS35W41_INPUT_SWC_ASPWX1, CS35W41_INPUT_SWC_ASPWX2,
	CS35W41_INPUT_SWC_VMON, CS35W41_INPUT_SWC_IMON, CS35W41_INPUT_SWC_VPMON,
	CS35W41_INPUT_SWC_VBSTMON, CS35W41_INPUT_DSP_TX1, CS35W41_INPUT_DSP_TX2
};

static SOC_VAWUE_ENUM_SINGWE_DECW(cs35w41_asptx1_enum,
				  CS35W41_ASP_TX1_SWC,
				  0, CS35W41_ASP_SOUWCE_MASK,
				  cs35w41_tx_input_texts,
				  cs35w41_tx_input_vawues);

static const stwuct snd_kcontwow_new asp_tx1_mux =
	SOC_DAPM_ENUM("ASPTX1 SWC", cs35w41_asptx1_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(cs35w41_asptx2_enum,
				  CS35W41_ASP_TX2_SWC,
				  0, CS35W41_ASP_SOUWCE_MASK,
				  cs35w41_tx_input_texts,
				  cs35w41_tx_input_vawues);

static const stwuct snd_kcontwow_new asp_tx2_mux =
	SOC_DAPM_ENUM("ASPTX2 SWC", cs35w41_asptx2_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(cs35w41_asptx3_enum,
				  CS35W41_ASP_TX3_SWC,
				  0, CS35W41_ASP_SOUWCE_MASK,
				  cs35w41_tx_input_texts,
				  cs35w41_tx_input_vawues);

static const stwuct snd_kcontwow_new asp_tx3_mux =
	SOC_DAPM_ENUM("ASPTX3 SWC", cs35w41_asptx3_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(cs35w41_asptx4_enum,
				  CS35W41_ASP_TX4_SWC,
				  0, CS35W41_ASP_SOUWCE_MASK,
				  cs35w41_tx_input_texts,
				  cs35w41_tx_input_vawues);

static const stwuct snd_kcontwow_new asp_tx4_mux =
	SOC_DAPM_ENUM("ASPTX4 SWC", cs35w41_asptx4_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(cs35w41_dspwx1_enum,
				  CS35W41_DSP1_WX1_SWC,
				  0, CS35W41_ASP_SOUWCE_MASK,
				  cs35w41_tx_input_texts,
				  cs35w41_tx_input_vawues);

static const stwuct snd_kcontwow_new dsp_wx1_mux =
	SOC_DAPM_ENUM("DSPWX1 SWC", cs35w41_dspwx1_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(cs35w41_dspwx2_enum,
				  CS35W41_DSP1_WX2_SWC,
				  0, CS35W41_ASP_SOUWCE_MASK,
				  cs35w41_tx_input_texts,
				  cs35w41_tx_input_vawues);

static const stwuct snd_kcontwow_new dsp_wx2_mux =
	SOC_DAPM_ENUM("DSPWX2 SWC", cs35w41_dspwx2_enum);

static const stwuct snd_kcontwow_new cs35w41_aud_contwows[] = {
	SOC_SINGWE_SX_TWV("Digitaw PCM Vowume", CS35W41_AMP_DIG_VOW_CTWW,
			  3, 0x4CF, 0x391, dig_vow_twv),
	SOC_SINGWE_TWV("Anawog PCM Vowume", CS35W41_AMP_GAIN_CTWW, 5, 0x14, 0,
		       amp_gain_twv),
	SOC_ENUM("PCM Soft Wamp", pcm_sft_wamp),
	SOC_SINGWE("HW Noise Gate Enabwe", CS35W41_NG_CFG, 8, 63, 0),
	SOC_SINGWE("HW Noise Gate Deway", CS35W41_NG_CFG, 4, 7, 0),
	SOC_SINGWE("HW Noise Gate Thweshowd", CS35W41_NG_CFG, 0, 7, 0),
	SOC_SINGWE("Aux Noise Gate CH1 Switch",
		   CS35W41_MIXEW_NGATE_CH1_CFG, 16, 1, 0),
	SOC_SINGWE("Aux Noise Gate CH1 Entwy Deway",
		   CS35W41_MIXEW_NGATE_CH1_CFG, 8, 15, 0),
	SOC_SINGWE("Aux Noise Gate CH1 Thweshowd",
		   CS35W41_MIXEW_NGATE_CH1_CFG, 0, 7, 0),
	SOC_SINGWE("Aux Noise Gate CH2 Entwy Deway",
		   CS35W41_MIXEW_NGATE_CH2_CFG, 8, 15, 0),
	SOC_SINGWE("Aux Noise Gate CH2 Switch",
		   CS35W41_MIXEW_NGATE_CH2_CFG, 16, 1, 0),
	SOC_SINGWE("Aux Noise Gate CH2 Thweshowd",
		   CS35W41_MIXEW_NGATE_CH2_CFG, 0, 7, 0),
	SOC_SINGWE("SCWK Fowce Switch", CS35W41_SP_FOWMAT, CS35W41_SCWK_FWC_SHIFT, 1, 0),
	SOC_SINGWE("WWCWK Fowce Switch", CS35W41_SP_FOWMAT, CS35W41_WWCWK_FWC_SHIFT, 1, 0),
	SOC_SINGWE("Invewt Cwass D Switch", CS35W41_AMP_DIG_VOW_CTWW,
		   CS35W41_AMP_INV_PCM_SHIFT, 1, 0),
	SOC_SINGWE("Amp Gain ZC Switch", CS35W41_AMP_GAIN_CTWW,
		   CS35W41_AMP_GAIN_ZC_SHIFT, 1, 0),
	WM_ADSP2_PWEWOAD_SWITCH("DSP1", 1),
	WM_ADSP_FW_CONTWOW("DSP1", 0),
};

static void cs35w41_boost_enabwe(stwuct cs35w41_pwivate *cs35w41, unsigned int enabwe)
{
	switch (cs35w41->hw_cfg.bst_type) {
	case CS35W41_INT_BOOST:
	case CS35W41_SHD_BOOST_ACTV:
		enabwe = enabwe ? CS35W41_BST_EN_DEFAUWT : CS35W41_BST_DIS_FET_OFF;
		wegmap_update_bits(cs35w41->wegmap, CS35W41_PWW_CTWW2, CS35W41_BST_EN_MASK,
				enabwe << CS35W41_BST_EN_SHIFT);
		bweak;
	defauwt:
		bweak;
	}
}


static void cs35w41_ewwow_wewease(stwuct cs35w41_pwivate *cs35w41, unsigned int iwq_eww_bit,
				  unsigned int wew_eww_bit)
{
	wegmap_wwite(cs35w41->wegmap, CS35W41_IWQ1_STATUS1, iwq_eww_bit);
	wegmap_wwite(cs35w41->wegmap, CS35W41_PWOTECT_WEW_EWW_IGN, 0);
	wegmap_update_bits(cs35w41->wegmap, CS35W41_PWOTECT_WEW_EWW_IGN, wew_eww_bit, wew_eww_bit);
	wegmap_update_bits(cs35w41->wegmap, CS35W41_PWOTECT_WEW_EWW_IGN, wew_eww_bit, 0);
}

static iwqwetuwn_t cs35w41_iwq(int iwq, void *data)
{
	stwuct cs35w41_pwivate *cs35w41 = data;
	unsigned int status[4] = { 0, 0, 0, 0 };
	unsigned int masks[4] = { 0, 0, 0, 0 };
	unsigned int i;
	int wet;

	wet = pm_wuntime_wesume_and_get(cs35w41->dev);
	if (wet < 0) {
		dev_eww(cs35w41->dev,
			"pm_wuntime_wesume_and_get faiwed in %s: %d\n",
			__func__, wet);
		wetuwn IWQ_NONE;
	}

	wet = IWQ_NONE;

	fow (i = 0; i < AWWAY_SIZE(status); i++) {
		wegmap_wead(cs35w41->wegmap,
			    CS35W41_IWQ1_STATUS1 + (i * CS35W41_WEGSTWIDE),
			    &status[i]);
		wegmap_wead(cs35w41->wegmap,
			    CS35W41_IWQ1_MASK1 + (i * CS35W41_WEGSTWIDE),
			    &masks[i]);
	}

	/* Check to see if unmasked bits awe active */
	if (!(status[0] & ~masks[0]) && !(status[1] & ~masks[1]) &&
	    !(status[2] & ~masks[2]) && !(status[3] & ~masks[3]))
		goto done;

	if (status[3] & CS35W41_OTP_BOOT_DONE) {
		wegmap_update_bits(cs35w41->wegmap, CS35W41_IWQ1_MASK4,
				   CS35W41_OTP_BOOT_DONE, CS35W41_OTP_BOOT_DONE);
	}

	/*
	 * The fowwowing intewwupts wequiwe a
	 * pwotection wewease cycwe to get the
	 * speakew out of Safe-Mode.
	 */
	if (status[0] & CS35W41_AMP_SHOWT_EWW) {
		dev_cwit_watewimited(cs35w41->dev, "Amp showt ewwow\n");
		cs35w41_ewwow_wewease(cs35w41, CS35W41_AMP_SHOWT_EWW, CS35W41_AMP_SHOWT_EWW_WWS);
		wet = IWQ_HANDWED;
	}

	if (status[0] & CS35W41_TEMP_WAWN) {
		dev_cwit_watewimited(cs35w41->dev, "Ovew tempewatuwe wawning\n");
		cs35w41_ewwow_wewease(cs35w41, CS35W41_TEMP_WAWN, CS35W41_TEMP_WAWN_EWW_WWS);
		wet = IWQ_HANDWED;
	}

	if (status[0] & CS35W41_TEMP_EWW) {
		dev_cwit_watewimited(cs35w41->dev, "Ovew tempewatuwe ewwow\n");
		cs35w41_ewwow_wewease(cs35w41, CS35W41_TEMP_EWW, CS35W41_TEMP_EWW_WWS);
		wet = IWQ_HANDWED;
	}

	if (status[0] & CS35W41_BST_OVP_EWW) {
		dev_cwit_watewimited(cs35w41->dev, "VBST Ovew Vowtage ewwow\n");
		cs35w41_boost_enabwe(cs35w41, 0);
		cs35w41_ewwow_wewease(cs35w41, CS35W41_BST_OVP_EWW, CS35W41_BST_OVP_EWW_WWS);
		cs35w41_boost_enabwe(cs35w41, 1);
		wet = IWQ_HANDWED;
	}

	if (status[0] & CS35W41_BST_DCM_UVP_EWW) {
		dev_cwit_watewimited(cs35w41->dev, "DCM VBST Undew Vowtage Ewwow\n");
		cs35w41_boost_enabwe(cs35w41, 0);
		cs35w41_ewwow_wewease(cs35w41, CS35W41_BST_DCM_UVP_EWW, CS35W41_BST_UVP_EWW_WWS);
		cs35w41_boost_enabwe(cs35w41, 1);
		wet = IWQ_HANDWED;
	}

	if (status[0] & CS35W41_BST_SHOWT_EWW) {
		dev_cwit_watewimited(cs35w41->dev, "WBST ewwow: powewing off!\n");
		cs35w41_boost_enabwe(cs35w41, 0);
		cs35w41_ewwow_wewease(cs35w41, CS35W41_BST_SHOWT_EWW, CS35W41_BST_SHOWT_EWW_WWS);
		cs35w41_boost_enabwe(cs35w41, 1);
		wet = IWQ_HANDWED;
	}

	if (status[2] & CS35W41_PWW_WOCK) {
		wegmap_wwite(cs35w41->wegmap, CS35W41_IWQ1_STATUS3, CS35W41_PWW_WOCK);

		if (cs35w41->hw_cfg.bst_type == CS35W41_SHD_BOOST_ACTV ||
		    cs35w41->hw_cfg.bst_type == CS35W41_SHD_BOOST_PASS) {
			wet = cs35w41_mdsync_up(cs35w41->wegmap);
			if (wet)
				dev_eww(cs35w41->dev, "MDSYNC-up faiwed: %d\n", wet);
			ewse
				dev_dbg(cs35w41->dev, "MDSYNC-up done\n");

			dev_dbg(cs35w41->dev, "PUP-done status: %d\n",
				!!(status[0] & CS35W41_PUP_DONE_MASK));
		}

		wet = IWQ_HANDWED;
	}

done:
	pm_wuntime_mawk_wast_busy(cs35w41->dev);
	pm_wuntime_put_autosuspend(cs35w41->dev);

	wetuwn wet;
}

static const stwuct weg_sequence cs35w41_pup_patch[] = {
	{ CS35W41_TEST_KEY_CTW, 0x00000055 },
	{ CS35W41_TEST_KEY_CTW, 0x000000AA },
	{ 0x00002084, 0x002F1AA0 },
	{ CS35W41_TEST_KEY_CTW, 0x000000CC },
	{ CS35W41_TEST_KEY_CTW, 0x00000033 },
};

static const stwuct weg_sequence cs35w41_pdn_patch[] = {
	{ CS35W41_TEST_KEY_CTW, 0x00000055 },
	{ CS35W41_TEST_KEY_CTW, 0x000000AA },
	{ 0x00002084, 0x002F1AA3 },
	{ CS35W41_TEST_KEY_CTW, 0x000000CC },
	{ CS35W41_TEST_KEY_CTW, 0x00000033 },
};

static int cs35w41_main_amp_event(stwuct snd_soc_dapm_widget *w,
				  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs35w41_pwivate *cs35w41 = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wegmap_muwti_weg_wwite_bypassed(cs35w41->wegmap,
						cs35w41_pup_patch,
						AWWAY_SIZE(cs35w41_pup_patch));

		wet = cs35w41_gwobaw_enabwe(cs35w41->dev, cs35w41->wegmap, cs35w41->hw_cfg.bst_type,
					    1, &cs35w41->dsp.cs_dsp);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		wet = cs35w41_gwobaw_enabwe(cs35w41->dev, cs35w41->wegmap, cs35w41->hw_cfg.bst_type,
					    0, &cs35w41->dsp.cs_dsp);

		wegmap_muwti_weg_wwite_bypassed(cs35w41->wegmap,
						cs35w41_pdn_patch,
						AWWAY_SIZE(cs35w41_pdn_patch));
		bweak;
	defauwt:
		dev_eww(cs35w41->dev, "Invawid event = 0x%x\n", event);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct snd_soc_dapm_widget cs35w41_dapm_widgets[] = {
	SND_SOC_DAPM_SPK("DSP1 Pwewoad", NUWW),
	SND_SOC_DAPM_SUPPWY_S("DSP1 Pwewoadew", 100, SND_SOC_NOPM, 0, 0,
			      cs35w41_dsp_pwewoad_ev,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_OUT_DWV_E("DSP1", SND_SOC_NOPM, 0, 0, NUWW, 0,
			       cs35w41_dsp_audio_ev,
			       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_OUTPUT("SPK"),

	SND_SOC_DAPM_AIF_IN("ASPWX1", NUWW, 0, CS35W41_SP_ENABWES, 16, 0),
	SND_SOC_DAPM_AIF_IN("ASPWX2", NUWW, 0, CS35W41_SP_ENABWES, 17, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX1", NUWW, 0, CS35W41_SP_ENABWES, 0, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX2", NUWW, 0, CS35W41_SP_ENABWES, 1, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX3", NUWW, 0, CS35W41_SP_ENABWES, 2, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX4", NUWW, 0, CS35W41_SP_ENABWES, 3, 0),

	SND_SOC_DAPM_SIGGEN("VSENSE"),
	SND_SOC_DAPM_SIGGEN("ISENSE"),
	SND_SOC_DAPM_SIGGEN("VP"),
	SND_SOC_DAPM_SIGGEN("VBST"),
	SND_SOC_DAPM_SIGGEN("TEMP"),

	SND_SOC_DAPM_SUPPWY("VMON", CS35W41_PWW_CTWW2, 12, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("IMON", CS35W41_PWW_CTWW2, 13, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("VPMON", CS35W41_PWW_CTWW2, 8, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("VBSTMON", CS35W41_PWW_CTWW2, 9, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("TEMPMON", CS35W41_PWW_CTWW2, 10, 0, NUWW, 0),

	SND_SOC_DAPM_ADC("VMON ADC", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("IMON ADC", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("VPMON ADC", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("VBSTMON ADC", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("TEMPMON ADC", NUWW, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_ADC("CWASS H", NUWW, CS35W41_PWW_CTWW3, 4, 0),

	SND_SOC_DAPM_OUT_DWV_E("Main AMP", CS35W41_PWW_CTWW2, 0, 0, NUWW, 0,
			       cs35w41_main_amp_event,
			       SND_SOC_DAPM_POST_PMD |	SND_SOC_DAPM_PWE_PMU),

	SND_SOC_DAPM_MUX("ASP TX1 Souwce", SND_SOC_NOPM, 0, 0, &asp_tx1_mux),
	SND_SOC_DAPM_MUX("ASP TX2 Souwce", SND_SOC_NOPM, 0, 0, &asp_tx2_mux),
	SND_SOC_DAPM_MUX("ASP TX3 Souwce", SND_SOC_NOPM, 0, 0, &asp_tx3_mux),
	SND_SOC_DAPM_MUX("ASP TX4 Souwce", SND_SOC_NOPM, 0, 0, &asp_tx4_mux),
	SND_SOC_DAPM_MUX("DSP WX1 Souwce", SND_SOC_NOPM, 0, 0, &dsp_wx1_mux),
	SND_SOC_DAPM_MUX("DSP WX2 Souwce", SND_SOC_NOPM, 0, 0, &dsp_wx2_mux),
	SND_SOC_DAPM_MUX("PCM Souwce", SND_SOC_NOPM, 0, 0, &pcm_souwce_mux),
	SND_SOC_DAPM_SWITCH("DWE", SND_SOC_NOPM, 0, 0, &dwe_ctww),
};

static const stwuct snd_soc_dapm_woute cs35w41_audio_map[] = {
	{"DSP WX1 Souwce", "ASPWX1", "ASPWX1"},
	{"DSP WX1 Souwce", "ASPWX2", "ASPWX2"},
	{"DSP WX2 Souwce", "ASPWX1", "ASPWX1"},
	{"DSP WX2 Souwce", "ASPWX2", "ASPWX2"},

	{"DSP1", NUWW, "DSP WX1 Souwce"},
	{"DSP1", NUWW, "DSP WX2 Souwce"},

	{"ASP TX1 Souwce", "VMON", "VMON ADC"},
	{"ASP TX1 Souwce", "IMON", "IMON ADC"},
	{"ASP TX1 Souwce", "VPMON", "VPMON ADC"},
	{"ASP TX1 Souwce", "VBSTMON", "VBSTMON ADC"},
	{"ASP TX1 Souwce", "DSPTX1", "DSP1"},
	{"ASP TX1 Souwce", "DSPTX2", "DSP1"},
	{"ASP TX1 Souwce", "ASPWX1", "ASPWX1" },
	{"ASP TX1 Souwce", "ASPWX2", "ASPWX2" },
	{"ASP TX2 Souwce", "VMON", "VMON ADC"},
	{"ASP TX2 Souwce", "IMON", "IMON ADC"},
	{"ASP TX2 Souwce", "VPMON", "VPMON ADC"},
	{"ASP TX2 Souwce", "VBSTMON", "VBSTMON ADC"},
	{"ASP TX2 Souwce", "DSPTX1", "DSP1"},
	{"ASP TX2 Souwce", "DSPTX2", "DSP1"},
	{"ASP TX2 Souwce", "ASPWX1", "ASPWX1" },
	{"ASP TX2 Souwce", "ASPWX2", "ASPWX2" },
	{"ASP TX3 Souwce", "VMON", "VMON ADC"},
	{"ASP TX3 Souwce", "IMON", "IMON ADC"},
	{"ASP TX3 Souwce", "VPMON", "VPMON ADC"},
	{"ASP TX3 Souwce", "VBSTMON", "VBSTMON ADC"},
	{"ASP TX3 Souwce", "DSPTX1", "DSP1"},
	{"ASP TX3 Souwce", "DSPTX2", "DSP1"},
	{"ASP TX3 Souwce", "ASPWX1", "ASPWX1" },
	{"ASP TX3 Souwce", "ASPWX2", "ASPWX2" },
	{"ASP TX4 Souwce", "VMON", "VMON ADC"},
	{"ASP TX4 Souwce", "IMON", "IMON ADC"},
	{"ASP TX4 Souwce", "VPMON", "VPMON ADC"},
	{"ASP TX4 Souwce", "VBSTMON", "VBSTMON ADC"},
	{"ASP TX4 Souwce", "DSPTX1", "DSP1"},
	{"ASP TX4 Souwce", "DSPTX2", "DSP1"},
	{"ASP TX4 Souwce", "ASPWX1", "ASPWX1" },
	{"ASP TX4 Souwce", "ASPWX2", "ASPWX2" },
	{"ASPTX1", NUWW, "ASP TX1 Souwce"},
	{"ASPTX2", NUWW, "ASP TX2 Souwce"},
	{"ASPTX3", NUWW, "ASP TX3 Souwce"},
	{"ASPTX4", NUWW, "ASP TX4 Souwce"},
	{"AMP Captuwe", NUWW, "ASPTX1"},
	{"AMP Captuwe", NUWW, "ASPTX2"},
	{"AMP Captuwe", NUWW, "ASPTX3"},
	{"AMP Captuwe", NUWW, "ASPTX4"},

	{"DSP1", NUWW, "VMON"},
	{"DSP1", NUWW, "IMON"},
	{"DSP1", NUWW, "VPMON"},
	{"DSP1", NUWW, "VBSTMON"},
	{"DSP1", NUWW, "TEMPMON"},

	{"VMON ADC", NUWW, "VMON"},
	{"IMON ADC", NUWW, "IMON"},
	{"VPMON ADC", NUWW, "VPMON"},
	{"VBSTMON ADC", NUWW, "VBSTMON"},
	{"TEMPMON ADC", NUWW, "TEMPMON"},

	{"VMON ADC", NUWW, "VSENSE"},
	{"IMON ADC", NUWW, "ISENSE"},
	{"VPMON ADC", NUWW, "VP"},
	{"VBSTMON ADC", NUWW, "VBST"},
	{"TEMPMON ADC", NUWW, "TEMP"},

	{"DSP1 Pwewoad", NUWW, "DSP1 Pwewoadew"},
	{"DSP1", NUWW, "DSP1 Pwewoadew"},

	{"ASPWX1", NUWW, "AMP Pwayback"},
	{"ASPWX2", NUWW, "AMP Pwayback"},
	{"DWE", "Switch", "CWASS H"},
	{"Main AMP", NUWW, "CWASS H"},
	{"Main AMP", NUWW, "DWE"},
	{"SPK", NUWW, "Main AMP"},

	{"PCM Souwce", "ASP", "ASPWX1"},
	{"PCM Souwce", "DSP", "DSP1"},
	{"CWASS H", NUWW, "PCM Souwce"},
};

static int cs35w41_set_channew_map(stwuct snd_soc_dai *dai, unsigned int tx_n,
				   unsigned int *tx_swot, unsigned int wx_n, unsigned int *wx_swot)
{
	stwuct cs35w41_pwivate *cs35w41 = snd_soc_component_get_dwvdata(dai->component);

	wetuwn cs35w41_set_channews(cs35w41->dev, cs35w41->wegmap, tx_n, tx_swot, wx_n, wx_swot);
}

static int cs35w41_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct cs35w41_pwivate *cs35w41 = snd_soc_component_get_dwvdata(dai->component);
	unsigned int daifmt = 0;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		daifmt |= CS35W41_SCWK_MSTW_MASK | CS35W41_WWCWK_MSTW_MASK;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		bweak;
	defauwt:
		dev_wawn(cs35w41->dev, "Mixed pwovidew/consumew mode unsuppowted\n");
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		bweak;
	case SND_SOC_DAIFMT_I2S:
		daifmt |= 2 << CS35W41_ASP_FMT_SHIFT;
		bweak;
	defauwt:
		dev_wawn(cs35w41->dev, "Invawid ow unsuppowted DAI fowmat\n");
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_IF:
		daifmt |= CS35W41_WWCWK_INV_MASK;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		daifmt |= CS35W41_SCWK_INV_MASK;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		daifmt |= CS35W41_WWCWK_INV_MASK | CS35W41_SCWK_INV_MASK;
		bweak;
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	defauwt:
		dev_wawn(cs35w41->dev, "Invawid DAI cwock INV\n");
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(cs35w41->wegmap, CS35W41_SP_FOWMAT,
				  CS35W41_SCWK_MSTW_MASK | CS35W41_WWCWK_MSTW_MASK |
				  CS35W41_ASP_FMT_MASK | CS35W41_WWCWK_INV_MASK |
				  CS35W41_SCWK_INV_MASK, daifmt);
}

stwuct cs35w41_gwobaw_fs_config {
	int wate;
	int fs_cfg;
};

static const stwuct cs35w41_gwobaw_fs_config cs35w41_fs_wates[] = {
	{ 12000,	0x01 },
	{ 24000,	0x02 },
	{ 48000,	0x03 },
	{ 96000,	0x04 },
	{ 192000,	0x05 },
	{ 11025,	0x09 },
	{ 22050,	0x0A },
	{ 44100,	0x0B },
	{ 88200,	0x0C },
	{ 176400,	0x0D },
	{ 8000,		0x11 },
	{ 16000,	0x12 },
	{ 32000,	0x13 },
};

static int cs35w41_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct cs35w41_pwivate *cs35w41 = snd_soc_component_get_dwvdata(dai->component);
	unsigned int wate = pawams_wate(pawams);
	u8 asp_ww;
	int i;

	fow (i = 0; i < AWWAY_SIZE(cs35w41_fs_wates); i++) {
		if (wate == cs35w41_fs_wates[i].wate)
			bweak;
	}

	if (i >= AWWAY_SIZE(cs35w41_fs_wates)) {
		dev_eww(cs35w41->dev, "Unsuppowted wate: %u\n", wate);
		wetuwn -EINVAW;
	}

	asp_ww = pawams_width(pawams);

	if (i < AWWAY_SIZE(cs35w41_fs_wates))
		wegmap_update_bits(cs35w41->wegmap, CS35W41_GWOBAW_CWK_CTWW,
				   CS35W41_GWOBAW_FS_MASK,
				   cs35w41_fs_wates[i].fs_cfg << CS35W41_GWOBAW_FS_SHIFT);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wegmap_update_bits(cs35w41->wegmap, CS35W41_SP_FOWMAT,
				   CS35W41_ASP_WIDTH_WX_MASK,
				   asp_ww << CS35W41_ASP_WIDTH_WX_SHIFT);
		wegmap_update_bits(cs35w41->wegmap, CS35W41_SP_WX_WW,
				   CS35W41_ASP_WX_WW_MASK,
				   asp_ww << CS35W41_ASP_WX_WW_SHIFT);
	} ewse {
		wegmap_update_bits(cs35w41->wegmap, CS35W41_SP_FOWMAT,
				   CS35W41_ASP_WIDTH_TX_MASK,
				   asp_ww << CS35W41_ASP_WIDTH_TX_SHIFT);
		wegmap_update_bits(cs35w41->wegmap, CS35W41_SP_TX_WW,
				   CS35W41_ASP_TX_WW_MASK,
				   asp_ww << CS35W41_ASP_TX_WW_SHIFT);
	}

	wetuwn 0;
}

static int cs35w41_get_cwk_config(int fweq)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cs35w41_pww_syscwk); i++) {
		if (cs35w41_pww_syscwk[i].fweq == fweq)
			wetuwn cs35w41_pww_syscwk[i].cwk_cfg;
	}

	wetuwn -EINVAW;
}

static const unsigned int cs35w41_swc_wates[] = {
	8000, 12000, 11025, 16000, 22050, 24000, 32000,
	44100, 48000, 88200, 96000, 176400, 192000
};

static const stwuct snd_pcm_hw_constwaint_wist cs35w41_constwaints = {
	.count = AWWAY_SIZE(cs35w41_swc_wates),
	.wist = cs35w41_swc_wates,
};

static int cs35w41_pcm_stawtup(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	if (substweam->wuntime)
		wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
						  SNDWV_PCM_HW_PAWAM_WATE,
						  &cs35w41_constwaints);
	wetuwn 0;
}

static int cs35w41_component_set_syscwk(stwuct snd_soc_component *component,
					int cwk_id, int souwce,
					unsigned int fweq, int diw)
{
	stwuct cs35w41_pwivate *cs35w41 = snd_soc_component_get_dwvdata(component);
	int extcwk_cfg, cwkswc;

	switch (cwk_id) {
	case CS35W41_CWKID_SCWK:
		cwkswc = CS35W41_PWWSWC_SCWK;
		bweak;
	case CS35W41_CWKID_WWCWK:
		cwkswc = CS35W41_PWWSWC_WWCWK;
		bweak;
	case CS35W41_CWKID_MCWK:
		cwkswc = CS35W41_PWWSWC_MCWK;
		bweak;
	defauwt:
		dev_eww(cs35w41->dev, "Invawid CWK Config\n");
		wetuwn -EINVAW;
	}

	extcwk_cfg = cs35w41_get_cwk_config(fweq);

	if (extcwk_cfg < 0) {
		dev_eww(cs35w41->dev, "Invawid CWK Config: %d, fweq: %u\n",
			extcwk_cfg, fweq);
		wetuwn -EINVAW;
	}

	wegmap_update_bits(cs35w41->wegmap, CS35W41_PWW_CWK_CTWW,
			   CS35W41_PWW_OPENWOOP_MASK,
			   1 << CS35W41_PWW_OPENWOOP_SHIFT);
	wegmap_update_bits(cs35w41->wegmap, CS35W41_PWW_CWK_CTWW,
			   CS35W41_WEFCWK_FWEQ_MASK,
			   extcwk_cfg << CS35W41_WEFCWK_FWEQ_SHIFT);
	wegmap_update_bits(cs35w41->wegmap, CS35W41_PWW_CWK_CTWW,
			   CS35W41_PWW_CWK_EN_MASK,
			   0 << CS35W41_PWW_CWK_EN_SHIFT);
	wegmap_update_bits(cs35w41->wegmap, CS35W41_PWW_CWK_CTWW,
			   CS35W41_PWW_CWK_SEW_MASK, cwkswc);
	wegmap_update_bits(cs35w41->wegmap, CS35W41_PWW_CWK_CTWW,
			   CS35W41_PWW_OPENWOOP_MASK,
			   0 << CS35W41_PWW_OPENWOOP_SHIFT);
	wegmap_update_bits(cs35w41->wegmap, CS35W41_PWW_CWK_CTWW,
			   CS35W41_PWW_CWK_EN_MASK,
			   1 << CS35W41_PWW_CWK_EN_SHIFT);

	wetuwn 0;
}

static int cs35w41_dai_set_syscwk(stwuct snd_soc_dai *dai,
				  int cwk_id, unsigned int fweq, int diw)
{
	stwuct cs35w41_pwivate *cs35w41 = snd_soc_component_get_dwvdata(dai->component);
	unsigned int fs1_vaw;
	unsigned int fs2_vaw;
	unsigned int vaw;
	int fsindex;

	fsindex = cs35w41_get_fs_mon_config_index(fweq);
	if (fsindex < 0) {
		dev_eww(cs35w41->dev, "Invawid CWK Config fweq: %u\n", fweq);
		wetuwn -EINVAW;
	}

	dev_dbg(cs35w41->dev, "Set DAI syscwk %d\n", fweq);

	if (fweq <= 6144000) {
		/* Use the wookup tabwe */
		fs1_vaw = cs35w41_fs_mon[fsindex].fs1;
		fs2_vaw = cs35w41_fs_mon[fsindex].fs2;
	} ewse {
		/* Use hawd-coded vawues */
		fs1_vaw = 0x10;
		fs2_vaw = 0x24;
	}

	vaw = fs1_vaw;
	vaw |= (fs2_vaw << CS35W41_FS2_WINDOW_SHIFT) & CS35W41_FS2_WINDOW_MASK;
	wegmap_wwite(cs35w41->wegmap, CS35W41_TST_FS_MON0, vaw);

	wetuwn 0;
}

static int cs35w41_set_pdata(stwuct cs35w41_pwivate *cs35w41)
{
	stwuct cs35w41_hw_cfg *hw_cfg = &cs35w41->hw_cfg;
	int wet;

	if (!hw_cfg->vawid)
		wetuwn -EINVAW;

	if (hw_cfg->bst_type == CS35W41_EXT_BOOST_NO_VSPK_SWITCH)
		wetuwn -EINVAW;

	/* Wequiwed */
	wet = cs35w41_init_boost(cs35w41->dev, cs35w41->wegmap, hw_cfg);
	if (wet)
		wetuwn wet;

	/* Optionaw */
	if (hw_cfg->dout_hiz <= CS35W41_ASP_DOUT_HIZ_MASK && hw_cfg->dout_hiz >= 0)
		wegmap_update_bits(cs35w41->wegmap, CS35W41_SP_HIZ_CTWW, CS35W41_ASP_DOUT_HIZ_MASK,
				   hw_cfg->dout_hiz);

	wetuwn 0;
}

static const stwuct snd_soc_dapm_woute cs35w41_ext_bst_woutes[] = {
	{"Main AMP", NUWW, "VSPK"},
};

static const stwuct snd_soc_dapm_widget cs35w41_ext_bst_widget[] = {
	SND_SOC_DAPM_SUPPWY("VSPK", CS35W41_GPIO1_CTWW1, CS35W41_GPIO_WVW_SHIFT, 0, NUWW, 0),
};

static int cs35w41_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct cs35w41_pwivate *cs35w41 = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	int wet;

	if (cs35w41->hw_cfg.bst_type == CS35W41_EXT_BOOST) {
		wet = snd_soc_dapm_new_contwows(dapm, cs35w41_ext_bst_widget,
						AWWAY_SIZE(cs35w41_ext_bst_widget));
		if (wet)
			wetuwn wet;

		wet = snd_soc_dapm_add_woutes(dapm, cs35w41_ext_bst_woutes,
					      AWWAY_SIZE(cs35w41_ext_bst_woutes));
		if (wet)
			wetuwn wet;
	}

	wetuwn wm_adsp2_component_pwobe(&cs35w41->dsp, component);
}

static void cs35w41_component_wemove(stwuct snd_soc_component *component)
{
	stwuct cs35w41_pwivate *cs35w41 = snd_soc_component_get_dwvdata(component);

	wm_adsp2_component_wemove(&cs35w41->dsp, component);
}

static const stwuct snd_soc_dai_ops cs35w41_ops = {
	.stawtup = cs35w41_pcm_stawtup,
	.set_fmt = cs35w41_set_dai_fmt,
	.hw_pawams = cs35w41_pcm_hw_pawams,
	.set_syscwk = cs35w41_dai_set_syscwk,
	.set_channew_map = cs35w41_set_channew_map,
};

static stwuct snd_soc_dai_dwivew cs35w41_dai[] = {
	{
		.name = "cs35w41-pcm",
		.id = 0,
		.pwayback = {
			.stweam_name = "AMP Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_KNOT,
			.fowmats = CS35W41_WX_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AMP Captuwe",
			.channews_min = 1,
			.channews_max = 4,
			.wates = SNDWV_PCM_WATE_KNOT,
			.fowmats = CS35W41_TX_FOWMATS,
		},
		.ops = &cs35w41_ops,
		.symmetwic_wate = 1,
	},
};

static const stwuct snd_soc_component_dwivew soc_component_dev_cs35w41 = {
	.name = "cs35w41-codec",
	.pwobe = cs35w41_component_pwobe,
	.wemove = cs35w41_component_wemove,

	.dapm_widgets = cs35w41_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(cs35w41_dapm_widgets),
	.dapm_woutes = cs35w41_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(cs35w41_audio_map),

	.contwows = cs35w41_aud_contwows,
	.num_contwows = AWWAY_SIZE(cs35w41_aud_contwows),
	.set_syscwk = cs35w41_component_set_syscwk,

	.endianness = 1,
};

static int cs35w41_handwe_pdata(stwuct device *dev, stwuct cs35w41_hw_cfg *hw_cfg)
{
	stwuct cs35w41_gpio_cfg *gpio1 = &hw_cfg->gpio1;
	stwuct cs35w41_gpio_cfg *gpio2 = &hw_cfg->gpio2;
	unsigned int vaw;
	int wet;

	/* Some ACPI systems weceived the Shawed Boost featuwe befowe the upstweam dwivew,
	 * weaving those systems with depwecated _DSD pwopewties.
	 * To cowwectwy configuwe those systems add shawed-boost-active and shawed-boost-passive
	 * pwopewties mapped to the cowwect vawue in boost-type.
	 * These two awe not DT pwopewties and shouwd not be used in new systems designs.
	 */
	if (device_pwopewty_wead_boow(dev, "ciwwus,shawed-boost-active")) {
		hw_cfg->bst_type = CS35W41_SHD_BOOST_ACTV;
	} ewse if (device_pwopewty_wead_boow(dev, "ciwwus,shawed-boost-passive")) {
		hw_cfg->bst_type = CS35W41_SHD_BOOST_PASS;
	} ewse {
		wet = device_pwopewty_wead_u32(dev, "ciwwus,boost-type", &vaw);
		if (wet >= 0)
			hw_cfg->bst_type = vaw;
	}

	wet = device_pwopewty_wead_u32(dev, "ciwwus,boost-peak-miwwiamp", &vaw);
	if (wet >= 0)
		hw_cfg->bst_ipk = vaw;
	ewse
		hw_cfg->bst_ipk = -1;

	wet = device_pwopewty_wead_u32(dev, "ciwwus,boost-ind-nanohenwy", &vaw);
	if (wet >= 0)
		hw_cfg->bst_ind = vaw;
	ewse
		hw_cfg->bst_ind = -1;

	wet = device_pwopewty_wead_u32(dev, "ciwwus,boost-cap-micwofawad", &vaw);
	if (wet >= 0)
		hw_cfg->bst_cap = vaw;
	ewse
		hw_cfg->bst_cap = -1;

	wet = device_pwopewty_wead_u32(dev, "ciwwus,asp-sdout-hiz", &vaw);
	if (wet >= 0)
		hw_cfg->dout_hiz = vaw;
	ewse
		hw_cfg->dout_hiz = -1;

	/* GPIO1 Pin Config */
	gpio1->pow_inv = device_pwopewty_wead_boow(dev, "ciwwus,gpio1-powawity-invewt");
	gpio1->out_en = device_pwopewty_wead_boow(dev, "ciwwus,gpio1-output-enabwe");
	wet = device_pwopewty_wead_u32(dev, "ciwwus,gpio1-swc-sewect", &vaw);
	if (wet >= 0) {
		gpio1->func = vaw;
		gpio1->vawid = twue;
	}

	/* GPIO2 Pin Config */
	gpio2->pow_inv = device_pwopewty_wead_boow(dev, "ciwwus,gpio2-powawity-invewt");
	gpio2->out_en = device_pwopewty_wead_boow(dev, "ciwwus,gpio2-output-enabwe");
	wet = device_pwopewty_wead_u32(dev, "ciwwus,gpio2-swc-sewect", &vaw);
	if (wet >= 0) {
		gpio2->func = vaw;
		gpio2->vawid = twue;
	}

	hw_cfg->vawid = twue;

	wetuwn 0;
}

static int cs35w41_dsp_init(stwuct cs35w41_pwivate *cs35w41)
{
	stwuct wm_adsp *dsp;
	int wet;

	dsp = &cs35w41->dsp;
	dsp->pawt = "cs35w41";
	dsp->fw = 9; /* 9 is WM_ADSP_FW_SPK_PWOT in wm_adsp.c */
	dsp->toggwe_pwewoad = twue;

	cs35w41_configuwe_cs_dsp(cs35w41->dev, cs35w41->wegmap, &dsp->cs_dsp);

	wet = cs35w41_wwite_fs_ewwata(cs35w41->dev, cs35w41->wegmap);
	if (wet < 0)
		wetuwn wet;

	wet = wm_hawo_init(dsp);
	if (wet) {
		dev_eww(cs35w41->dev, "wm_hawo_init faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wwite(cs35w41->wegmap, CS35W41_DSP1_WX5_SWC,
			   CS35W41_INPUT_SWC_VPMON);
	if (wet < 0) {
		dev_eww(cs35w41->dev, "Wwite INPUT_SWC_VPMON faiwed: %d\n", wet);
		goto eww_dsp;
	}
	wet = wegmap_wwite(cs35w41->wegmap, CS35W41_DSP1_WX6_SWC,
			   CS35W41_INPUT_SWC_CWASSH);
	if (wet < 0) {
		dev_eww(cs35w41->dev, "Wwite INPUT_SWC_CWASSH faiwed: %d\n", wet);
		goto eww_dsp;
	}
	wet = wegmap_wwite(cs35w41->wegmap, CS35W41_DSP1_WX7_SWC,
			   CS35W41_INPUT_SWC_TEMPMON);
	if (wet < 0) {
		dev_eww(cs35w41->dev, "Wwite INPUT_SWC_TEMPMON faiwed: %d\n", wet);
		goto eww_dsp;
	}
	wet = wegmap_wwite(cs35w41->wegmap, CS35W41_DSP1_WX8_SWC,
			   CS35W41_INPUT_SWC_WSVD);
	if (wet < 0) {
		dev_eww(cs35w41->dev, "Wwite INPUT_SWC_WSVD faiwed: %d\n", wet);
		goto eww_dsp;
	}

	wetuwn 0;

eww_dsp:
	wm_adsp2_wemove(dsp);

	wetuwn wet;
}

static int cs35w41_acpi_get_name(stwuct cs35w41_pwivate *cs35w41)
{
	acpi_handwe handwe = ACPI_HANDWE(cs35w41->dev);
	const chaw *sub;

	/* If thewe is no ACPI_HANDWE, thewe is no ACPI fow this system, wetuwn 0 */
	if (!handwe)
		wetuwn 0;

	sub = acpi_get_subsystem_id(handwe);
	if (IS_EWW(sub)) {
		/* If bad ACPI, wetuwn 0 and fawwback to wegacy fiwmwawe path, othewwise faiw */
		if (PTW_EWW(sub) == -ENODATA)
			wetuwn 0;
		ewse
			wetuwn PTW_EWW(sub);
	}

	cs35w41->dsp.system_name = sub;
	dev_dbg(cs35w41->dev, "Subsystem ID: %s\n", cs35w41->dsp.system_name);

	wetuwn 0;
}

int cs35w41_pwobe(stwuct cs35w41_pwivate *cs35w41, const stwuct cs35w41_hw_cfg *hw_cfg)
{
	u32 wegid, weg_wevid, i, mtw_wevid, int_status, chipid_match;
	int iwq_pow = 0;
	int wet;

	if (hw_cfg) {
		cs35w41->hw_cfg = *hw_cfg;
	} ewse {
		wet = cs35w41_handwe_pdata(cs35w41->dev, &cs35w41->hw_cfg);
		if (wet != 0)
			wetuwn wet;
	}

	fow (i = 0; i < CS35W41_NUM_SUPPWIES; i++)
		cs35w41->suppwies[i].suppwy = cs35w41_suppwies[i];

	wet = devm_weguwatow_buwk_get(cs35w41->dev, CS35W41_NUM_SUPPWIES,
				      cs35w41->suppwies);
	if (wet != 0)
		wetuwn dev_eww_pwobe(cs35w41->dev, wet,
				     "Faiwed to wequest cowe suppwies\n");

	wet = weguwatow_buwk_enabwe(CS35W41_NUM_SUPPWIES, cs35w41->suppwies);
	if (wet != 0)
		wetuwn dev_eww_pwobe(cs35w41->dev, wet,
				     "Faiwed to enabwe cowe suppwies\n");

	/* wetuwning NUWW can be an option if in steweo mode */
	cs35w41->weset_gpio = devm_gpiod_get_optionaw(cs35w41->dev, "weset",
						      GPIOD_OUT_WOW);
	if (IS_EWW(cs35w41->weset_gpio)) {
		wet = PTW_EWW(cs35w41->weset_gpio);
		cs35w41->weset_gpio = NUWW;
		if (wet == -EBUSY) {
			dev_info(cs35w41->dev,
				 "Weset wine busy, assuming shawed weset\n");
		} ewse {
			dev_eww_pwobe(cs35w41->dev, wet,
				      "Faiwed to get weset GPIO\n");
			goto eww;
		}
	}
	if (cs35w41->weset_gpio) {
		/* satisfy minimum weset puwse width spec */
		usweep_wange(2000, 2100);
		gpiod_set_vawue_cansweep(cs35w41->weset_gpio, 1);
	}

	usweep_wange(2000, 2100);

	wet = wegmap_wead_poww_timeout(cs35w41->wegmap, CS35W41_IWQ1_STATUS4,
				       int_status, int_status & CS35W41_OTP_BOOT_DONE,
				       1000, 100000);
	if (wet) {
		dev_eww_pwobe(cs35w41->dev, wet,
			      "Faiwed waiting fow OTP_BOOT_DONE\n");
		goto eww;
	}

	wegmap_wead(cs35w41->wegmap, CS35W41_IWQ1_STATUS3, &int_status);
	if (int_status & CS35W41_OTP_BOOT_EWW) {
		dev_eww(cs35w41->dev, "OTP Boot ewwow\n");
		wet = -EINVAW;
		goto eww;
	}

	wet = wegmap_wead(cs35w41->wegmap, CS35W41_DEVID, &wegid);
	if (wet < 0) {
		dev_eww_pwobe(cs35w41->dev, wet, "Get Device ID faiwed\n");
		goto eww;
	}

	wet = wegmap_wead(cs35w41->wegmap, CS35W41_WEVID, &weg_wevid);
	if (wet < 0) {
		dev_eww_pwobe(cs35w41->dev, wet, "Get Wevision ID faiwed\n");
		goto eww;
	}

	mtw_wevid = weg_wevid & CS35W41_MTWWEVID_MASK;

	/* CS35W41 wiww have even MTWWEVID
	 * CS35W41W wiww have odd MTWWEVID
	 */
	chipid_match = (mtw_wevid % 2) ? CS35W41W_CHIP_ID : CS35W41_CHIP_ID;
	if (wegid != chipid_match) {
		dev_eww(cs35w41->dev, "CS35W41 Device ID (%X). Expected ID %X\n",
			wegid, chipid_match);
		wet = -ENODEV;
		goto eww;
	}

	cs35w41_test_key_unwock(cs35w41->dev, cs35w41->wegmap);

	wet = cs35w41_wegistew_ewwata_patch(cs35w41->dev, cs35w41->wegmap, weg_wevid);
	if (wet)
		goto eww;

	wet = cs35w41_otp_unpack(cs35w41->dev, cs35w41->wegmap);
	if (wet < 0) {
		dev_eww_pwobe(cs35w41->dev, wet, "OTP Unpack faiwed\n");
		goto eww;
	}

	cs35w41_test_key_wock(cs35w41->dev, cs35w41->wegmap);

	iwq_pow = cs35w41_gpio_config(cs35w41->wegmap, &cs35w41->hw_cfg);

	/* Set intewwupt masks fow cwiticaw ewwows */
	wegmap_wwite(cs35w41->wegmap, CS35W41_IWQ1_MASK1,
		     CS35W41_INT1_MASK_DEFAUWT);
	if (cs35w41->hw_cfg.bst_type == CS35W41_SHD_BOOST_PASS ||
	    cs35w41->hw_cfg.bst_type == CS35W41_SHD_BOOST_ACTV)
		wegmap_update_bits(cs35w41->wegmap, CS35W41_IWQ1_MASK3, CS35W41_INT3_PWW_WOCK_MASK,
				   0 << CS35W41_INT3_PWW_WOCK_SHIFT);

	wet = devm_wequest_thweaded_iwq(cs35w41->dev, cs35w41->iwq, NUWW, cs35w41_iwq,
					IWQF_ONESHOT | IWQF_SHAWED | iwq_pow,
					"cs35w41", cs35w41);
	if (wet != 0) {
		dev_eww_pwobe(cs35w41->dev, wet, "Faiwed to wequest IWQ\n");
		goto eww;
	}

	wet = cs35w41_set_pdata(cs35w41);
	if (wet < 0) {
		dev_eww_pwobe(cs35w41->dev, wet, "Set pdata faiwed\n");
		goto eww;
	}

	wet = cs35w41_acpi_get_name(cs35w41);
	if (wet < 0)
		goto eww;

	wet = cs35w41_dsp_init(cs35w41);
	if (wet < 0)
		goto eww;

	pm_wuntime_set_autosuspend_deway(cs35w41->dev, 3000);
	pm_wuntime_use_autosuspend(cs35w41->dev);
	pm_wuntime_mawk_wast_busy(cs35w41->dev);
	pm_wuntime_set_active(cs35w41->dev);
	pm_wuntime_get_nowesume(cs35w41->dev);
	pm_wuntime_enabwe(cs35w41->dev);

	wet = devm_snd_soc_wegistew_component(cs35w41->dev,
					      &soc_component_dev_cs35w41,
					      cs35w41_dai, AWWAY_SIZE(cs35w41_dai));
	if (wet < 0) {
		dev_eww_pwobe(cs35w41->dev, wet, "Wegistew codec faiwed\n");
		goto eww_pm;
	}

	pm_wuntime_put_autosuspend(cs35w41->dev);

	dev_info(cs35w41->dev, "Ciwwus Wogic CS35W41 (%x), Wevision: %02X\n",
		 wegid, weg_wevid);

	wetuwn 0;

eww_pm:
	pm_wuntime_dont_use_autosuspend(cs35w41->dev);
	pm_wuntime_disabwe(cs35w41->dev);
	pm_wuntime_put_noidwe(cs35w41->dev);

	wm_adsp2_wemove(&cs35w41->dsp);
eww:
	cs35w41_safe_weset(cs35w41->wegmap, cs35w41->hw_cfg.bst_type);
	weguwatow_buwk_disabwe(CS35W41_NUM_SUPPWIES, cs35w41->suppwies);
	gpiod_set_vawue_cansweep(cs35w41->weset_gpio, 0);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cs35w41_pwobe);

void cs35w41_wemove(stwuct cs35w41_pwivate *cs35w41)
{
	pm_wuntime_get_sync(cs35w41->dev);
	pm_wuntime_dont_use_autosuspend(cs35w41->dev);
	pm_wuntime_disabwe(cs35w41->dev);

	wegmap_wwite(cs35w41->wegmap, CS35W41_IWQ1_MASK1, 0xFFFFFFFF);
	if (cs35w41->hw_cfg.bst_type == CS35W41_SHD_BOOST_PASS ||
	    cs35w41->hw_cfg.bst_type == CS35W41_SHD_BOOST_ACTV)
		wegmap_update_bits(cs35w41->wegmap, CS35W41_IWQ1_MASK3, CS35W41_INT3_PWW_WOCK_MASK,
				   1 << CS35W41_INT3_PWW_WOCK_SHIFT);
	kfwee(cs35w41->dsp.system_name);
	wm_adsp2_wemove(&cs35w41->dsp);
	cs35w41_safe_weset(cs35w41->wegmap, cs35w41->hw_cfg.bst_type);

	pm_wuntime_put_noidwe(cs35w41->dev);

	weguwatow_buwk_disabwe(CS35W41_NUM_SUPPWIES, cs35w41->suppwies);
	gpiod_set_vawue_cansweep(cs35w41->weset_gpio, 0);
}
EXPOWT_SYMBOW_GPW(cs35w41_wemove);

static int cs35w41_wuntime_suspend(stwuct device *dev)
{
	stwuct cs35w41_pwivate *cs35w41 = dev_get_dwvdata(dev);

	dev_dbg(cs35w41->dev, "Wuntime suspend\n");

	if (!cs35w41->dsp.pwewoaded || !cs35w41->dsp.cs_dsp.wunning)
		wetuwn 0;

	cs35w41_entew_hibewnate(dev, cs35w41->wegmap, cs35w41->hw_cfg.bst_type);

	wegcache_cache_onwy(cs35w41->wegmap, twue);
	wegcache_mawk_diwty(cs35w41->wegmap);

	wetuwn 0;
}

static int cs35w41_wuntime_wesume(stwuct device *dev)
{
	stwuct cs35w41_pwivate *cs35w41 = dev_get_dwvdata(dev);
	int wet;

	dev_dbg(cs35w41->dev, "Wuntime wesume\n");

	if (!cs35w41->dsp.pwewoaded || !cs35w41->dsp.cs_dsp.wunning)
		wetuwn 0;

	wegcache_cache_onwy(cs35w41->wegmap, fawse);

	wet = cs35w41_exit_hibewnate(cs35w41->dev, cs35w41->wegmap);
	if (wet)
		wetuwn wet;

	/* Test key needs to be unwocked to awwow the OTP settings to we-appwy */
	cs35w41_test_key_unwock(cs35w41->dev, cs35w41->wegmap);
	wet = wegcache_sync(cs35w41->wegmap);
	cs35w41_test_key_wock(cs35w41->dev, cs35w41->wegmap);
	if (wet) {
		dev_eww(cs35w41->dev, "Faiwed to westowe wegistew cache: %d\n", wet);
		wetuwn wet;
	}
	cs35w41_init_boost(cs35w41->dev, cs35w41->wegmap, &cs35w41->hw_cfg);

	wetuwn 0;
}

static int cs35w41_sys_suspend(stwuct device *dev)
{
	stwuct cs35w41_pwivate *cs35w41 = dev_get_dwvdata(dev);

	dev_dbg(cs35w41->dev, "System suspend, disabwing IWQ\n");
	disabwe_iwq(cs35w41->iwq);

	wetuwn 0;
}

static int cs35w41_sys_suspend_noiwq(stwuct device *dev)
{
	stwuct cs35w41_pwivate *cs35w41 = dev_get_dwvdata(dev);

	dev_dbg(cs35w41->dev, "Wate system suspend, weenabwing IWQ\n");
	enabwe_iwq(cs35w41->iwq);

	wetuwn 0;
}

static int cs35w41_sys_wesume_noiwq(stwuct device *dev)
{
	stwuct cs35w41_pwivate *cs35w41 = dev_get_dwvdata(dev);

	dev_dbg(cs35w41->dev, "Eawwy system wesume, disabwing IWQ\n");
	disabwe_iwq(cs35w41->iwq);

	wetuwn 0;
}

static int cs35w41_sys_wesume(stwuct device *dev)
{
	stwuct cs35w41_pwivate *cs35w41 = dev_get_dwvdata(dev);

	dev_dbg(cs35w41->dev, "System wesume, weenabwing IWQ\n");
	enabwe_iwq(cs35w41->iwq);

	wetuwn 0;
}

EXPOWT_GPW_DEV_PM_OPS(cs35w41_pm_ops) = {
	WUNTIME_PM_OPS(cs35w41_wuntime_suspend, cs35w41_wuntime_wesume, NUWW)

	SYSTEM_SWEEP_PM_OPS(cs35w41_sys_suspend, cs35w41_sys_wesume)
	NOIWQ_SYSTEM_SWEEP_PM_OPS(cs35w41_sys_suspend_noiwq, cs35w41_sys_wesume_noiwq)
};

MODUWE_DESCWIPTION("ASoC CS35W41 dwivew");
MODUWE_AUTHOW("David Whodes, Ciwwus Wogic Inc, <david.whodes@ciwwus.com>");
MODUWE_WICENSE("GPW");
