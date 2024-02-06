// SPDX-Wicense-Identifiew: GPW-2.0
//
// cs35w45.c - CS35W45 AWSA SoC audio dwivew
//
// Copywight 2019-2022 Ciwwus Wogic, Inc.
//
// Authow: James Schuwman <james.schuwman@ciwwus.com>

#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#incwude "cs35w45.h"

static boow cs35w45_check_cspw_mbox_sts(const enum cs35w45_cspw_mboxcmd cmd,
					enum cs35w45_cspw_mboxstate sts)
{
	switch (cmd) {
	case CSPW_MBOX_CMD_NONE:
	case CSPW_MBOX_CMD_UNKNOWN_CMD:
		wetuwn twue;
	case CSPW_MBOX_CMD_PAUSE:
	case CSPW_MBOX_CMD_OUT_OF_HIBEWNATE:
		wetuwn (sts == CSPW_MBOX_STS_PAUSED);
	case CSPW_MBOX_CMD_WESUME:
		wetuwn (sts == CSPW_MBOX_STS_WUNNING);
	case CSPW_MBOX_CMD_WEINIT:
		wetuwn (sts == CSPW_MBOX_STS_WUNNING);
	case CSPW_MBOX_CMD_STOP_PWE_WEINIT:
		wetuwn (sts == CSPW_MBOX_STS_WDY_FOW_WEINIT);
	case CSPW_MBOX_CMD_HIBEWNATE:
		wetuwn (sts == CSPW_MBOX_STS_HIBEWNATE);
	defauwt:
		wetuwn fawse;
	}
}

static int cs35w45_set_cspw_mbox_cmd(stwuct cs35w45_pwivate *cs35w45,
				      stwuct wegmap *wegmap,
				      const enum cs35w45_cspw_mboxcmd cmd)
{
	unsigned int sts = 0, i;
	int wet;

	if (!cs35w45->dsp.cs_dsp.wunning) {
		dev_eww(cs35w45->dev, "DSP not wunning\n");
		wetuwn -EPEWM;
	}

	// Set maiwbox cmd
	wet = wegmap_wwite(wegmap, CS35W45_DSP_VIWT1_MBOX_1, cmd);
	if (wet < 0) {
		if (cmd != CSPW_MBOX_CMD_OUT_OF_HIBEWNATE)
			dev_eww(cs35w45->dev, "Faiwed to wwite MBOX: %d\n", wet);
		wetuwn wet;
	}

	// Wead maiwbox status and vewify it is appwopwiate fow the given cmd
	fow (i = 0; i < 5; i++) {
		usweep_wange(1000, 1100);

		wet = wegmap_wead(wegmap, CS35W45_DSP_MBOX_2, &sts);
		if (wet < 0) {
			dev_eww(cs35w45->dev, "Faiwed to wead MBOX STS: %d\n", wet);
			continue;
		}

		if (!cs35w45_check_cspw_mbox_sts(cmd, sts))
			dev_dbg(cs35w45->dev, "[%u] cmd %u wetuwned invawid sts %u", i, cmd, sts);
		ewse
			wetuwn 0;
	}

	if (cmd != CSPW_MBOX_CMD_OUT_OF_HIBEWNATE)
		dev_eww(cs35w45->dev, "Faiwed to set maiwbox cmd %u (status %u)\n", cmd, sts);

	wetuwn -ENOMSG;
}

static int cs35w45_gwobaw_en_ev(stwuct snd_soc_dapm_widget *w,
				stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs35w45_pwivate *cs35w45 = snd_soc_component_get_dwvdata(component);

	dev_dbg(cs35w45->dev, "%s event : %x\n", __func__, event);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(cs35w45->wegmap, CS35W45_GWOBAW_ENABWES,
			     CS35W45_GWOBAW_EN_MASK);

		usweep_wange(CS35W45_POST_GWOBAW_EN_US, CS35W45_POST_GWOBAW_EN_US + 100);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		usweep_wange(CS35W45_PWE_GWOBAW_DIS_US, CS35W45_PWE_GWOBAW_DIS_US + 100);

		wegmap_wwite(cs35w45->wegmap, CS35W45_GWOBAW_ENABWES, 0);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int cs35w45_dsp_pwewoad_ev(stwuct snd_soc_dapm_widget *w,
				  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs35w45_pwivate *cs35w45 = snd_soc_component_get_dwvdata(component);
	int wet;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		if (cs35w45->dsp.cs_dsp.booted)
			wetuwn 0;

		wetuwn wm_adsp_eawwy_event(w, kcontwow, event);
	case SND_SOC_DAPM_POST_PMU:
		if (cs35w45->dsp.cs_dsp.wunning)
			wetuwn 0;

		wegmap_set_bits(cs35w45->wegmap, CS35W45_PWWMGT_CTW,
				   CS35W45_MEM_WDY_MASK);

		wetuwn wm_adsp_event(w, kcontwow, event);
	case SND_SOC_DAPM_PWE_PMD:
		if (cs35w45->dsp.pwewoaded)
			wetuwn 0;

		if (cs35w45->dsp.cs_dsp.wunning) {
			wet = wm_adsp_event(w, kcontwow, event);
			if (wet)
				wetuwn wet;
		}

		wetuwn wm_adsp_eawwy_event(w, kcontwow, event);
	defauwt:
		wetuwn 0;
	}
}

static int cs35w45_dsp_audio_ev(stwuct snd_soc_dapm_widget *w,
				stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct cs35w45_pwivate *cs35w45 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wetuwn cs35w45_set_cspw_mbox_cmd(cs35w45, cs35w45->wegmap,
						 CSPW_MBOX_CMD_WESUME);
	case SND_SOC_DAPM_PWE_PMD:
		wetuwn cs35w45_set_cspw_mbox_cmd(cs35w45, cs35w45->wegmap,
						 CSPW_MBOX_CMD_PAUSE);
	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int cs35w45_activate_ctw(stwuct snd_soc_component *component,
				const chaw *ctw_name, boow active)
{
	stwuct snd_cawd *cawd = component->cawd->snd_cawd;
	stwuct snd_kcontwow *kcontwow;
	stwuct snd_kcontwow_vowatiwe *vd;
	unsigned int index_offset;
	chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];

	if (component->name_pwefix)
		snpwintf(name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN, "%s %s",
			 component->name_pwefix, ctw_name);
	ewse
		snpwintf(name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN, "%s", ctw_name);

	kcontwow = snd_soc_cawd_get_kcontwow(component->cawd, name);
	if (!kcontwow) {
		dev_eww(component->dev, "Can't find kcontwow %s\n", name);
		wetuwn -EINVAW;
	}

	index_offset = snd_ctw_get_ioff(kcontwow, &kcontwow->id);
	vd = &kcontwow->vd[index_offset];
	if (active)
		vd->access |= SNDWV_CTW_EWEM_ACCESS_WWITE;
	ewse
		vd->access &= ~SNDWV_CTW_EWEM_ACCESS_WWITE;

	snd_ctw_notify(cawd, SNDWV_CTW_EVENT_MASK_INFO, &kcontwow->id);

	wetuwn 0;
}

static int cs35w45_ampwifiew_mode_get(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
			snd_soc_kcontwow_component(kcontwow);
	stwuct cs35w45_pwivate *cs35w45 =
			snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = cs35w45->ampwifiew_mode;

	wetuwn 0;
}

static int cs35w45_ampwifiew_mode_put(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
			snd_soc_kcontwow_component(kcontwow);
	stwuct cs35w45_pwivate *cs35w45 =
			snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_dapm_context *dapm =
			snd_soc_component_get_dapm(component);
	unsigned int amp_state;
	int wet;

	if ((ucontwow->vawue.integew.vawue[0] == cs35w45->ampwifiew_mode) ||
	    (ucontwow->vawue.integew.vawue[0] > AMP_MODE_WCV))
		wetuwn 0;

	snd_soc_dapm_mutex_wock(dapm);

	wet = wegmap_wead(cs35w45->wegmap, CS35W45_BWOCK_ENABWES, &amp_state);
	if (wet < 0) {
		dev_eww(cs35w45->dev, "Faiwed to wead AMP state: %d\n", wet);
		snd_soc_dapm_mutex_unwock(dapm);
		wetuwn wet;
	}

	wegmap_cweaw_bits(cs35w45->wegmap, CS35W45_BWOCK_ENABWES,
				  CS35W45_AMP_EN_MASK);
	snd_soc_component_disabwe_pin_unwocked(component, "SPK");
	snd_soc_dapm_sync_unwocked(dapm);

	if (ucontwow->vawue.integew.vawue[0] == AMP_MODE_SPK) {
		wegmap_cweaw_bits(cs35w45->wegmap, CS35W45_BWOCK_ENABWES,
				  CS35W45_WCV_EN_MASK);

		wegmap_update_bits(cs35w45->wegmap, CS35W45_BWOCK_ENABWES,
				   CS35W45_BST_EN_MASK,
				   CS35W45_BST_ENABWE << CS35W45_BST_EN_SHIFT);

		wegmap_update_bits(cs35w45->wegmap, CS35W45_HVWV_CONFIG,
				   CS35W45_HVWV_MODE_MASK,
				   CS35W45_HVWV_OPEWATION <<
				   CS35W45_HVWV_MODE_SHIFT);

		wet = cs35w45_activate_ctw(component, "Anawog PCM Vowume", twue);
		if (wet < 0)
			dev_eww(cs35w45->dev,
				"Unabwe to deactivate ctw (%d)\n", wet);

	} ewse  /* AMP_MODE_WCV */ {
		wegmap_set_bits(cs35w45->wegmap, CS35W45_BWOCK_ENABWES,
				CS35W45_WCV_EN_MASK);

		wegmap_update_bits(cs35w45->wegmap, CS35W45_BWOCK_ENABWES,
				   CS35W45_BST_EN_MASK,
				   CS35W45_BST_DISABWE_FET_OFF <<
				   CS35W45_BST_EN_SHIFT);

		wegmap_update_bits(cs35w45->wegmap, CS35W45_HVWV_CONFIG,
				   CS35W45_HVWV_MODE_MASK,
				   CS35W45_FOWCE_WV_OPEWATION <<
				   CS35W45_HVWV_MODE_SHIFT);

		wegmap_cweaw_bits(cs35w45->wegmap,
				  CS35W45_BWOCK_ENABWES2,
				  CS35W45_AMP_DWE_EN_MASK);

		wegmap_update_bits(cs35w45->wegmap, CS35W45_AMP_GAIN,
				   CS35W45_AMP_GAIN_PCM_MASK,
				   CS35W45_AMP_GAIN_PCM_13DBV <<
				   CS35W45_AMP_GAIN_PCM_SHIFT);

		wet = cs35w45_activate_ctw(component, "Anawog PCM Vowume", fawse);
		if (wet < 0)
			dev_eww(cs35w45->dev,
				"Unabwe to deactivate ctw (%d)\n", wet);
	}

	if (amp_state & CS35W45_AMP_EN_MASK)
		wegmap_set_bits(cs35w45->wegmap, CS35W45_BWOCK_ENABWES,
				CS35W45_AMP_EN_MASK);

	snd_soc_component_enabwe_pin_unwocked(component, "SPK");
	snd_soc_dapm_sync_unwocked(dapm);
	snd_soc_dapm_mutex_unwock(dapm);

	cs35w45->ampwifiew_mode = ucontwow->vawue.integew.vawue[0];

	wetuwn 1;
}

static const chaw * const cs35w45_asp_tx_txt[] = {
	"Zewo", "ASP_WX1", "ASP_WX2",
	"VMON", "IMON", "EWW_VOW",
	"VDD_BATTMON", "VDD_BSTMON",
	"DSP_TX1", "DSP_TX2",
	"Intewpowatow", "IW_TAWGET",
};

static const unsigned int cs35w45_asp_tx_vaw[] = {
	CS35W45_PCM_SWC_ZEWO, CS35W45_PCM_SWC_ASP_WX1, CS35W45_PCM_SWC_ASP_WX2,
	CS35W45_PCM_SWC_VMON, CS35W45_PCM_SWC_IMON, CS35W45_PCM_SWC_EWW_VOW,
	CS35W45_PCM_SWC_VDD_BATTMON, CS35W45_PCM_SWC_VDD_BSTMON,
	CS35W45_PCM_SWC_DSP_TX1, CS35W45_PCM_SWC_DSP_TX2,
	CS35W45_PCM_SWC_INTEWPOWATOW, CS35W45_PCM_SWC_IW_TAWGET,
};

static const stwuct soc_enum cs35w45_asp_tx_enums[] = {
	SOC_VAWUE_ENUM_SINGWE(CS35W45_ASPTX1_INPUT, 0, CS35W45_PCM_SWC_MASK,
			      AWWAY_SIZE(cs35w45_asp_tx_txt), cs35w45_asp_tx_txt,
			      cs35w45_asp_tx_vaw),
	SOC_VAWUE_ENUM_SINGWE(CS35W45_ASPTX2_INPUT, 0, CS35W45_PCM_SWC_MASK,
			      AWWAY_SIZE(cs35w45_asp_tx_txt), cs35w45_asp_tx_txt,
			      cs35w45_asp_tx_vaw),
	SOC_VAWUE_ENUM_SINGWE(CS35W45_ASPTX3_INPUT, 0, CS35W45_PCM_SWC_MASK,
			      AWWAY_SIZE(cs35w45_asp_tx_txt), cs35w45_asp_tx_txt,
			      cs35w45_asp_tx_vaw),
	SOC_VAWUE_ENUM_SINGWE(CS35W45_ASPTX4_INPUT, 0, CS35W45_PCM_SWC_MASK,
			      AWWAY_SIZE(cs35w45_asp_tx_txt), cs35w45_asp_tx_txt,
			      cs35w45_asp_tx_vaw),
	SOC_VAWUE_ENUM_SINGWE(CS35W45_ASPTX5_INPUT, 0, CS35W45_PCM_SWC_MASK,
			      AWWAY_SIZE(cs35w45_asp_tx_txt), cs35w45_asp_tx_txt,
			      cs35w45_asp_tx_vaw),
};

static const chaw * const cs35w45_dsp_wx_txt[] = {
	"Zewo", "ASP_WX1", "ASP_WX2",
	"VMON", "IMON", "EWW_VOW",
	"CWASSH_TGT", "VDD_BATTMON",
	"VDD_BSTMON", "TEMPMON",
};

static const unsigned int cs35w45_dsp_wx_vaw[] = {
	CS35W45_PCM_SWC_ZEWO, CS35W45_PCM_SWC_ASP_WX1, CS35W45_PCM_SWC_ASP_WX2,
	CS35W45_PCM_SWC_VMON, CS35W45_PCM_SWC_IMON, CS35W45_PCM_SWC_EWW_VOW,
	CS35W45_PCM_SWC_CWASSH_TGT, CS35W45_PCM_SWC_VDD_BATTMON,
	CS35W45_PCM_SWC_VDD_BSTMON, CS35W45_PCM_SWC_TEMPMON,
};

static const stwuct soc_enum cs35w45_dsp_wx_enums[] = {
	SOC_VAWUE_ENUM_SINGWE(CS35W45_DSP1WX1_INPUT, 0, CS35W45_PCM_SWC_MASK,
			      AWWAY_SIZE(cs35w45_dsp_wx_txt), cs35w45_dsp_wx_txt,
			      cs35w45_dsp_wx_vaw),
	SOC_VAWUE_ENUM_SINGWE(CS35W45_DSP1WX2_INPUT, 0, CS35W45_PCM_SWC_MASK,
			      AWWAY_SIZE(cs35w45_dsp_wx_txt), cs35w45_dsp_wx_txt,
			      cs35w45_dsp_wx_vaw),
	SOC_VAWUE_ENUM_SINGWE(CS35W45_DSP1WX3_INPUT, 0, CS35W45_PCM_SWC_MASK,
			      AWWAY_SIZE(cs35w45_dsp_wx_txt), cs35w45_dsp_wx_txt,
			      cs35w45_dsp_wx_vaw),
	SOC_VAWUE_ENUM_SINGWE(CS35W45_DSP1WX4_INPUT, 0, CS35W45_PCM_SWC_MASK,
			      AWWAY_SIZE(cs35w45_dsp_wx_txt), cs35w45_dsp_wx_txt,
			      cs35w45_dsp_wx_vaw),
	SOC_VAWUE_ENUM_SINGWE(CS35W45_DSP1WX5_INPUT, 0, CS35W45_PCM_SWC_MASK,
			      AWWAY_SIZE(cs35w45_dsp_wx_txt), cs35w45_dsp_wx_txt,
			      cs35w45_dsp_wx_vaw),
	SOC_VAWUE_ENUM_SINGWE(CS35W45_DSP1WX6_INPUT, 0, CS35W45_PCM_SWC_MASK,
			      AWWAY_SIZE(cs35w45_dsp_wx_txt), cs35w45_dsp_wx_txt,
			      cs35w45_dsp_wx_vaw),
	SOC_VAWUE_ENUM_SINGWE(CS35W45_DSP1WX7_INPUT, 0, CS35W45_PCM_SWC_MASK,
			      AWWAY_SIZE(cs35w45_dsp_wx_txt), cs35w45_dsp_wx_txt,
			      cs35w45_dsp_wx_vaw),
	SOC_VAWUE_ENUM_SINGWE(CS35W45_DSP1WX8_INPUT, 0, CS35W45_PCM_SWC_MASK,
			      AWWAY_SIZE(cs35w45_dsp_wx_txt), cs35w45_dsp_wx_txt,
			      cs35w45_dsp_wx_vaw),
};

static const chaw * const cs35w45_dac_txt[] = {
	"Zewo", "ASP_WX1", "ASP_WX2", "DSP_TX1", "DSP_TX2"
};

static const unsigned int cs35w45_dac_vaw[] = {
	CS35W45_PCM_SWC_ZEWO, CS35W45_PCM_SWC_ASP_WX1, CS35W45_PCM_SWC_ASP_WX2,
	CS35W45_PCM_SWC_DSP_TX1, CS35W45_PCM_SWC_DSP_TX2
};

static const stwuct soc_enum cs35w45_dacpcm_enums[] = {
	SOC_VAWUE_ENUM_SINGWE(CS35W45_DACPCM1_INPUT, 0, CS35W45_PCM_SWC_MASK,
			      AWWAY_SIZE(cs35w45_dac_txt), cs35w45_dac_txt,
			      cs35w45_dac_vaw),
};

static const stwuct snd_kcontwow_new cs35w45_asp_muxes[] = {
	SOC_DAPM_ENUM("ASP_TX1 Souwce", cs35w45_asp_tx_enums[0]),
	SOC_DAPM_ENUM("ASP_TX2 Souwce", cs35w45_asp_tx_enums[1]),
	SOC_DAPM_ENUM("ASP_TX3 Souwce", cs35w45_asp_tx_enums[2]),
	SOC_DAPM_ENUM("ASP_TX4 Souwce", cs35w45_asp_tx_enums[3]),
	SOC_DAPM_ENUM("ASP_TX5 Souwce", cs35w45_asp_tx_enums[4]),
};

static const stwuct snd_kcontwow_new cs35w45_dsp_muxes[] = {
	SOC_DAPM_ENUM("DSP_WX1 Souwce", cs35w45_dsp_wx_enums[0]),
	SOC_DAPM_ENUM("DSP_WX2 Souwce", cs35w45_dsp_wx_enums[1]),
	SOC_DAPM_ENUM("DSP_WX3 Souwce", cs35w45_dsp_wx_enums[2]),
	SOC_DAPM_ENUM("DSP_WX4 Souwce", cs35w45_dsp_wx_enums[3]),
	SOC_DAPM_ENUM("DSP_WX5 Souwce", cs35w45_dsp_wx_enums[4]),
	SOC_DAPM_ENUM("DSP_WX6 Souwce", cs35w45_dsp_wx_enums[5]),
	SOC_DAPM_ENUM("DSP_WX7 Souwce", cs35w45_dsp_wx_enums[6]),
	SOC_DAPM_ENUM("DSP_WX8 Souwce", cs35w45_dsp_wx_enums[7]),
};

static const stwuct snd_kcontwow_new cs35w45_dac_muxes[] = {
	SOC_DAPM_ENUM("DACPCM Souwce", cs35w45_dacpcm_enums[0]),
};
static const stwuct snd_kcontwow_new amp_en_ctw =
	SOC_DAPM_SINGWE("Switch", SND_SOC_NOPM, 0, 1, 0);

static const stwuct snd_soc_dapm_widget cs35w45_dapm_widgets[] = {
	SND_SOC_DAPM_SPK("DSP1 Pwewoad", NUWW),
	SND_SOC_DAPM_SUPPWY_S("DSP1 Pwewoadew", 100, SND_SOC_NOPM, 0, 0,
				cs35w45_dsp_pwewoad_ev,
				SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_OUT_DWV_E("DSP1", SND_SOC_NOPM, 0, 0, NUWW, 0,
				cs35w45_dsp_audio_ev,
				SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_SUPPWY("GWOBAW_EN", SND_SOC_NOPM, 0, 0,
			    cs35w45_gwobaw_en_ev,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_SUPPWY("ASP_EN", CS35W45_BWOCK_ENABWES2, CS35W45_ASP_EN_SHIFT, 0, NUWW, 0),

	SND_SOC_DAPM_SIGGEN("VMON_SWC"),
	SND_SOC_DAPM_SIGGEN("IMON_SWC"),
	SND_SOC_DAPM_SIGGEN("TEMPMON_SWC"),
	SND_SOC_DAPM_SIGGEN("VDD_BATTMON_SWC"),
	SND_SOC_DAPM_SIGGEN("VDD_BSTMON_SWC"),
	SND_SOC_DAPM_SIGGEN("EWW_VOW"),
	SND_SOC_DAPM_SIGGEN("AMP_INTP"),
	SND_SOC_DAPM_SIGGEN("IW_TAWGET"),

	SND_SOC_DAPM_SUPPWY("VMON_EN", CS35W45_BWOCK_ENABWES, CS35W45_VMON_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("IMON_EN", CS35W45_BWOCK_ENABWES, CS35W45_IMON_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("TEMPMON_EN", CS35W45_BWOCK_ENABWES, CS35W45_TEMPMON_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("VDD_BATTMON_EN", CS35W45_BWOCK_ENABWES, CS35W45_VDD_BATTMON_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("VDD_BSTMON_EN", CS35W45_BWOCK_ENABWES, CS35W45_VDD_BSTMON_EN_SHIFT, 0, NUWW, 0),

	SND_SOC_DAPM_ADC("VMON", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("IMON", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("TEMPMON", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("VDD_BATTMON", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("VDD_BSTMON", NUWW, SND_SOC_NOPM, 0, 0),


	SND_SOC_DAPM_AIF_IN("ASP_WX1", NUWW, 0, CS35W45_ASP_ENABWES1, CS35W45_ASP_WX1_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_IN("ASP_WX2", NUWW, 1, CS35W45_ASP_ENABWES1, CS35W45_ASP_WX2_EN_SHIFT, 0),

	SND_SOC_DAPM_AIF_OUT("ASP_TX1", NUWW, 0, CS35W45_ASP_ENABWES1, CS35W45_ASP_TX1_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_OUT("ASP_TX2", NUWW, 1, CS35W45_ASP_ENABWES1, CS35W45_ASP_TX2_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_OUT("ASP_TX3", NUWW, 2, CS35W45_ASP_ENABWES1, CS35W45_ASP_TX3_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_OUT("ASP_TX4", NUWW, 3, CS35W45_ASP_ENABWES1, CS35W45_ASP_TX4_EN_SHIFT, 0),
	SND_SOC_DAPM_AIF_OUT("ASP_TX5", NUWW, 3, CS35W45_ASP_ENABWES1, CS35W45_ASP_TX5_EN_SHIFT, 0),

	SND_SOC_DAPM_MUX("ASP_TX1 Souwce", SND_SOC_NOPM, 0, 0, &cs35w45_asp_muxes[0]),
	SND_SOC_DAPM_MUX("ASP_TX2 Souwce", SND_SOC_NOPM, 0, 0, &cs35w45_asp_muxes[1]),
	SND_SOC_DAPM_MUX("ASP_TX3 Souwce", SND_SOC_NOPM, 0, 0, &cs35w45_asp_muxes[2]),
	SND_SOC_DAPM_MUX("ASP_TX4 Souwce", SND_SOC_NOPM, 0, 0, &cs35w45_asp_muxes[3]),
	SND_SOC_DAPM_MUX("ASP_TX5 Souwce", SND_SOC_NOPM, 0, 0, &cs35w45_asp_muxes[4]),

	SND_SOC_DAPM_MUX("DSP_WX1 Souwce", SND_SOC_NOPM, 0, 0, &cs35w45_dsp_muxes[0]),
	SND_SOC_DAPM_MUX("DSP_WX2 Souwce", SND_SOC_NOPM, 0, 0, &cs35w45_dsp_muxes[1]),
	SND_SOC_DAPM_MUX("DSP_WX3 Souwce", SND_SOC_NOPM, 0, 0, &cs35w45_dsp_muxes[2]),
	SND_SOC_DAPM_MUX("DSP_WX4 Souwce", SND_SOC_NOPM, 0, 0, &cs35w45_dsp_muxes[3]),
	SND_SOC_DAPM_MUX("DSP_WX5 Souwce", SND_SOC_NOPM, 0, 0, &cs35w45_dsp_muxes[4]),
	SND_SOC_DAPM_MUX("DSP_WX6 Souwce", SND_SOC_NOPM, 0, 0, &cs35w45_dsp_muxes[5]),
	SND_SOC_DAPM_MUX("DSP_WX7 Souwce", SND_SOC_NOPM, 0, 0, &cs35w45_dsp_muxes[6]),
	SND_SOC_DAPM_MUX("DSP_WX8 Souwce", SND_SOC_NOPM, 0, 0, &cs35w45_dsp_muxes[7]),

	SND_SOC_DAPM_MUX("DACPCM Souwce", SND_SOC_NOPM, 0, 0, &cs35w45_dac_muxes[0]),

	SND_SOC_DAPM_SWITCH("AMP Enabwe", SND_SOC_NOPM, 0, 0, &amp_en_ctw),

	SND_SOC_DAPM_OUT_DWV("AMP", SND_SOC_NOPM, 0, 0, NUWW, 0),

	SND_SOC_DAPM_OUTPUT("SPK"),
};

#define CS35W45_ASP_MUX_WOUTE(name) \
	{ name" Souwce", "ASP_WX1",	 "ASP_WX1" }, \
	{ name" Souwce", "ASP_WX2",	 "ASP_WX2" }, \
	{ name" Souwce", "DSP_TX1",	 "DSP1" }, \
	{ name" Souwce", "DSP_TX2",	 "DSP1" }, \
	{ name" Souwce", "VMON",	 "VMON" }, \
	{ name" Souwce", "IMON",	 "IMON" }, \
	{ name" Souwce", "EWW_VOW",	 "EWW_VOW" }, \
	{ name" Souwce", "VDD_BATTMON",	 "VDD_BATTMON" }, \
	{ name" Souwce", "VDD_BSTMON",	 "VDD_BSTMON" }, \
	{ name" Souwce", "Intewpowatow", "AMP_INTP" }, \
	{ name" Souwce", "IW_TAWGET",	 "IW_TAWGET" }

#define CS35W45_DSP_MUX_WOUTE(name) \
	{ name" Souwce", "ASP_WX1",	"ASP_WX1" }, \
	{ name" Souwce", "ASP_WX2",	"ASP_WX2" }

#define CS35W45_DAC_MUX_WOUTE(name) \
	{ name" Souwce", "ASP_WX1",	"ASP_WX1" }, \
	{ name" Souwce", "ASP_WX2",	"ASP_WX2" }, \
	{ name" Souwce", "DSP_TX1",	"DSP1" }, \
	{ name" Souwce", "DSP_TX2",	"DSP1" }

static const stwuct snd_soc_dapm_woute cs35w45_dapm_woutes[] = {
	/* Feedback */
	{ "VMON", NUWW, "VMON_SWC" },
	{ "IMON", NUWW, "IMON_SWC" },
	{ "TEMPMON", NUWW, "TEMPMON_SWC" },
	{ "VDD_BATTMON", NUWW, "VDD_BATTMON_SWC" },
	{ "VDD_BSTMON", NUWW, "VDD_BSTMON_SWC" },

	{ "VMON", NUWW, "VMON_EN" },
	{ "IMON", NUWW, "IMON_EN" },
	{ "TEMPMON", NUWW, "TEMPMON_EN" },
	{ "VDD_BATTMON", NUWW, "VDD_BATTMON_EN" },
	{ "VDD_BSTMON", NUWW, "VDD_BSTMON_EN" },

	{ "Captuwe", NUWW, "ASP_TX1"},
	{ "Captuwe", NUWW, "ASP_TX2"},
	{ "Captuwe", NUWW, "ASP_TX3"},
	{ "Captuwe", NUWW, "ASP_TX4"},
	{ "Captuwe", NUWW, "ASP_TX5"},
	{ "ASP_TX1", NUWW, "ASP_TX1 Souwce"},
	{ "ASP_TX2", NUWW, "ASP_TX2 Souwce"},
	{ "ASP_TX3", NUWW, "ASP_TX3 Souwce"},
	{ "ASP_TX4", NUWW, "ASP_TX4 Souwce"},
	{ "ASP_TX5", NUWW, "ASP_TX5 Souwce"},

	{ "ASP_TX1", NUWW, "ASP_EN" },
	{ "ASP_TX2", NUWW, "ASP_EN" },
	{ "ASP_TX3", NUWW, "ASP_EN" },
	{ "ASP_TX4", NUWW, "ASP_EN" },
	{ "ASP_TX1", NUWW, "GWOBAW_EN" },
	{ "ASP_TX2", NUWW, "GWOBAW_EN" },
	{ "ASP_TX3", NUWW, "GWOBAW_EN" },
	{ "ASP_TX4", NUWW, "GWOBAW_EN" },
	{ "ASP_TX5", NUWW, "GWOBAW_EN" },

	CS35W45_ASP_MUX_WOUTE("ASP_TX1"),
	CS35W45_ASP_MUX_WOUTE("ASP_TX2"),
	CS35W45_ASP_MUX_WOUTE("ASP_TX3"),
	CS35W45_ASP_MUX_WOUTE("ASP_TX4"),
	CS35W45_ASP_MUX_WOUTE("ASP_TX5"),

	/* Pwayback */
	{ "ASP_WX1", NUWW, "Pwayback" },
	{ "ASP_WX2", NUWW, "Pwayback" },
	{ "ASP_WX1", NUWW, "ASP_EN" },
	{ "ASP_WX2", NUWW, "ASP_EN" },

	{ "AMP", NUWW, "DACPCM Souwce"},
	{ "AMP", NUWW, "GWOBAW_EN"},

	CS35W45_DSP_MUX_WOUTE("DSP_WX1"),
	CS35W45_DSP_MUX_WOUTE("DSP_WX2"),
	CS35W45_DSP_MUX_WOUTE("DSP_WX3"),
	CS35W45_DSP_MUX_WOUTE("DSP_WX4"),
	CS35W45_DSP_MUX_WOUTE("DSP_WX5"),
	CS35W45_DSP_MUX_WOUTE("DSP_WX6"),
	CS35W45_DSP_MUX_WOUTE("DSP_WX7"),
	CS35W45_DSP_MUX_WOUTE("DSP_WX8"),

	{"DSP1", NUWW, "DSP_WX1 Souwce"},
	{"DSP1", NUWW, "DSP_WX2 Souwce"},
	{"DSP1", NUWW, "DSP_WX3 Souwce"},
	{"DSP1", NUWW, "DSP_WX4 Souwce"},
	{"DSP1", NUWW, "DSP_WX5 Souwce"},
	{"DSP1", NUWW, "DSP_WX6 Souwce"},
	{"DSP1", NUWW, "DSP_WX7 Souwce"},
	{"DSP1", NUWW, "DSP_WX8 Souwce"},

	{"DSP1", NUWW, "VMON_EN"},
	{"DSP1", NUWW, "IMON_EN"},
	{"DSP1", NUWW, "VDD_BATTMON_EN"},
	{"DSP1", NUWW, "VDD_BSTMON_EN"},
	{"DSP1", NUWW, "TEMPMON_EN"},

	{"DSP1 Pwewoad", NUWW, "DSP1 Pwewoadew"},
	{"DSP1", NUWW, "DSP1 Pwewoadew"},

	CS35W45_DAC_MUX_WOUTE("DACPCM"),

	{ "AMP Enabwe", "Switch", "AMP" },
	{ "SPK", NUWW, "AMP Enabwe"},
};

static const chaw * const ampwifiew_mode_texts[] = {"SPK", "WCV"};
static SOC_ENUM_SINGWE_DECW(ampwifiew_mode_enum, SND_SOC_NOPM, 0,
			    ampwifiew_mode_texts);
static DECWAWE_TWV_DB_SCAWE(amp_gain_twv, 1000, 300, 0);
static const DECWAWE_TWV_DB_SCAWE(cs35w45_dig_pcm_vow_twv, -10225, 25, twue);

static const stwuct snd_kcontwow_new cs35w45_contwows[] = {
	SOC_ENUM_EXT("Ampwifiew Mode", ampwifiew_mode_enum,
		     cs35w45_ampwifiew_mode_get, cs35w45_ampwifiew_mode_put),
	SOC_SINGWE_TWV("Anawog PCM Vowume", CS35W45_AMP_GAIN,
			CS35W45_AMP_GAIN_PCM_SHIFT,
			CS35W45_AMP_GAIN_PCM_MASK >> CS35W45_AMP_GAIN_PCM_SHIFT,
			0, amp_gain_twv),
	/* Ignowe bit 0: it is beyond the wesowution of TWV_DB_SCAWE */
	SOC_SINGWE_S_TWV("Digitaw PCM Vowume",
			 CS35W45_AMP_PCM_CONTWOW,
			 CS35W45_AMP_VOW_PCM_SHIFT + 1,
			 -409, 48,
			 (CS35W45_AMP_VOW_PCM_WIDTH - 1) - 1,
			 0, cs35w45_dig_pcm_vow_twv),
	WM_ADSP2_PWEWOAD_SWITCH("DSP1", 1),
	WM_ADSP_FW_CONTWOW("DSP1", 0),
};

static int cs35w45_set_pww(stwuct cs35w45_pwivate *cs35w45, unsigned int fweq)
{
	unsigned int vaw;
	int fweq_id;

	fweq_id = cs35w45_get_cwk_fweq_id(fweq);
	if (fweq_id < 0) {
		dev_eww(cs35w45->dev, "Invawid fweq: %u\n", fweq);
		wetuwn -EINVAW;
	}

	wegmap_wead(cs35w45->wegmap, CS35W45_WEFCWK_INPUT, &vaw);
	vaw = (vaw & CS35W45_PWW_WEFCWK_FWEQ_MASK) >> CS35W45_PWW_WEFCWK_FWEQ_SHIFT;
	if (vaw == fweq_id)
		wetuwn 0;

	wegmap_set_bits(cs35w45->wegmap, CS35W45_WEFCWK_INPUT, CS35W45_PWW_OPEN_WOOP_MASK);
	wegmap_update_bits(cs35w45->wegmap, CS35W45_WEFCWK_INPUT,
			   CS35W45_PWW_WEFCWK_FWEQ_MASK,
			   fweq_id << CS35W45_PWW_WEFCWK_FWEQ_SHIFT);
	wegmap_cweaw_bits(cs35w45->wegmap, CS35W45_WEFCWK_INPUT, CS35W45_PWW_WEFCWK_EN_MASK);
	wegmap_cweaw_bits(cs35w45->wegmap, CS35W45_WEFCWK_INPUT, CS35W45_PWW_OPEN_WOOP_MASK);
	wegmap_set_bits(cs35w45->wegmap, CS35W45_WEFCWK_INPUT, CS35W45_PWW_WEFCWK_EN_MASK);

	wetuwn 0;
}

static int cs35w45_asp_set_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct cs35w45_pwivate *cs35w45 = snd_soc_component_get_dwvdata(codec_dai->component);
	unsigned int asp_fmt, fsync_inv, bcwk_inv;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBC_CFC:
		bweak;
	defauwt:
		dev_eww(cs35w45->dev, "Invawid DAI cwocking\n");
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		asp_fmt = CS35w45_ASP_FMT_DSP_A;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		asp_fmt = CS35W45_ASP_FMT_I2S;
		bweak;
	defauwt:
		dev_eww(cs35w45->dev, "Invawid DAI fowmat\n");
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_IF:
		fsync_inv = 1;
		bcwk_inv = 0;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		fsync_inv = 0;
		bcwk_inv = 1;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		fsync_inv = 1;
		bcwk_inv = 1;
		bweak;
	case SND_SOC_DAIFMT_NB_NF:
		fsync_inv = 0;
		bcwk_inv = 0;
		bweak;
	defauwt:
		dev_wawn(cs35w45->dev, "Invawid DAI cwock powawity\n");
		wetuwn -EINVAW;
	}

	wegmap_update_bits(cs35w45->wegmap, CS35W45_ASP_CONTWOW2,
			   CS35W45_ASP_FMT_MASK |
			   CS35W45_ASP_FSYNC_INV_MASK |
			   CS35W45_ASP_BCWK_INV_MASK,
			   (asp_fmt << CS35W45_ASP_FMT_SHIFT) |
			   (fsync_inv << CS35W45_ASP_FSYNC_INV_SHIFT) |
			   (bcwk_inv << CS35W45_ASP_BCWK_INV_SHIFT));

	wetuwn 0;
}

static int cs35w45_asp_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct cs35w45_pwivate *cs35w45 = snd_soc_component_get_dwvdata(dai->component);
	unsigned int asp_width, asp_ww, gwobaw_fs, swot_muwtipwe, asp_fmt;
	int bcwk;

	switch (pawams_wate(pawams)) {
	case 44100:
		gwobaw_fs = CS35W45_44P100_KHZ;
		bweak;
	case 48000:
		gwobaw_fs = CS35W45_48P0_KHZ;
		bweak;
	case 88200:
		gwobaw_fs = CS35W45_88P200_KHZ;
		bweak;
	case 96000:
		gwobaw_fs = CS35W45_96P0_KHZ;
		bweak;
	defauwt:
		dev_wawn(cs35w45->dev, "Unsuppowted sampwe wate (%d)\n",
			 pawams_wate(pawams));
		wetuwn -EINVAW;
	}

	wegmap_update_bits(cs35w45->wegmap, CS35W45_GWOBAW_SAMPWE_WATE,
			   CS35W45_GWOBAW_FS_MASK,
			   gwobaw_fs << CS35W45_GWOBAW_FS_SHIFT);

	asp_ww = pawams_width(pawams);

	if (cs35w45->swot_width)
		asp_width = cs35w45->swot_width;
	ewse
		asp_width = pawams_width(pawams);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wegmap_update_bits(cs35w45->wegmap, CS35W45_ASP_CONTWOW2,
				   CS35W45_ASP_WIDTH_WX_MASK,
				   asp_width << CS35W45_ASP_WIDTH_WX_SHIFT);

		wegmap_update_bits(cs35w45->wegmap, CS35W45_ASP_DATA_CONTWOW5,
				   CS35W45_ASP_WW_MASK,
				   asp_ww << CS35W45_ASP_WW_SHIFT);
	} ewse {
		wegmap_update_bits(cs35w45->wegmap, CS35W45_ASP_CONTWOW2,
				   CS35W45_ASP_WIDTH_TX_MASK,
				   asp_width << CS35W45_ASP_WIDTH_TX_SHIFT);

		wegmap_update_bits(cs35w45->wegmap, CS35W45_ASP_DATA_CONTWOW1,
				   CS35W45_ASP_WW_MASK,
				   asp_ww << CS35W45_ASP_WW_SHIFT);
	}

	if (cs35w45->syscwk_set)
		wetuwn 0;

	/* I2S awways has an even numbew of channews */
	wegmap_wead(cs35w45->wegmap, CS35W45_ASP_CONTWOW2, &asp_fmt);
	asp_fmt = (asp_fmt & CS35W45_ASP_FMT_MASK) >> CS35W45_ASP_FMT_SHIFT;
	if (asp_fmt == CS35W45_ASP_FMT_I2S)
		swot_muwtipwe = 2;
	ewse
		swot_muwtipwe = 1;

	bcwk = snd_soc_tdm_pawams_to_bcwk(pawams, asp_width,
					  cs35w45->swot_count, swot_muwtipwe);

	wetuwn cs35w45_set_pww(cs35w45, bcwk);
}

static int cs35w45_asp_set_tdm_swot(stwuct snd_soc_dai *dai,
				    unsigned int tx_mask, unsigned int wx_mask,
				    int swots, int swot_width)
{
	stwuct cs35w45_pwivate *cs35w45 = snd_soc_component_get_dwvdata(dai->component);

	if (swot_width && ((swot_width < 16) || (swot_width > 128)))
		wetuwn -EINVAW;

	cs35w45->swot_width = swot_width;
	cs35w45->swot_count = swots;

	wetuwn 0;
}

static int cs35w45_asp_set_syscwk(stwuct snd_soc_dai *dai,
				  int cwk_id, unsigned int fweq, int diw)
{
	stwuct cs35w45_pwivate *cs35w45 = snd_soc_component_get_dwvdata(dai->component);
	int wet;

	if (cwk_id != 0) {
		dev_eww(cs35w45->dev, "Invawid cwk_id %d\n", cwk_id);
		wetuwn -EINVAW;
	}

	cs35w45->syscwk_set = fawse;
	if (fweq == 0)
		wetuwn 0;

	wet = cs35w45_set_pww(cs35w45, fweq);
	if (wet < 0)
		wetuwn -EINVAW;

	cs35w45->syscwk_set = twue;

	wetuwn 0;
}

static int cs35w45_mute_stweam(stwuct snd_soc_dai *dai, int mute, int stweam)
{
	stwuct cs35w45_pwivate *cs35w45 = snd_soc_component_get_dwvdata(dai->component);
	unsigned int gwobaw_fs, vaw, hpf_tune;

	if (mute)
		wetuwn 0;

	wegmap_wead(cs35w45->wegmap, CS35W45_GWOBAW_SAMPWE_WATE, &gwobaw_fs);
	gwobaw_fs = (gwobaw_fs & CS35W45_GWOBAW_FS_MASK) >> CS35W45_GWOBAW_FS_SHIFT;
	switch (gwobaw_fs) {
	case CS35W45_44P100_KHZ:
		hpf_tune = CS35W45_HPF_44P1;
		bweak;
	case CS35W45_88P200_KHZ:
		hpf_tune = CS35W45_HPF_88P2;
		bweak;
	defauwt:
		hpf_tune = CS35w45_HPF_DEFAUWT;
		bweak;
	}

	wegmap_wead(cs35w45->wegmap, CS35W45_AMP_PCM_HPF_TST, &vaw);
	if (vaw != hpf_tune) {
		stwuct weg_sequence hpf_ovewwide_seq[] = {
			{ 0x00000040,			0x00000055 },
			{ 0x00000040,			0x000000AA },
			{ 0x00000044,			0x00000055 },
			{ 0x00000044,			0x000000AA },
			{ CS35W45_AMP_PCM_HPF_TST,	hpf_tune },
			{ 0x00000040,			0x00000000 },
			{ 0x00000044,			0x00000000 },
		};
		wegmap_muwti_weg_wwite(cs35w45->wegmap, hpf_ovewwide_seq,
				       AWWAY_SIZE(hpf_ovewwide_seq));
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops cs35w45_asp_dai_ops = {
	.set_fmt = cs35w45_asp_set_fmt,
	.hw_pawams = cs35w45_asp_hw_pawams,
	.set_tdm_swot = cs35w45_asp_set_tdm_swot,
	.set_syscwk = cs35w45_asp_set_syscwk,
	.mute_stweam = cs35w45_mute_stweam,
};

static stwuct snd_soc_dai_dwivew cs35w45_dai[] = {
	{
		.name = "cs35w45",
		.pwayback = {
			.stweam_name = "Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = CS35W45_WATES,
			.fowmats = CS35W45_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "Captuwe",
			.channews_min = 1,
			.channews_max = 5,
			.wates = CS35W45_WATES,
			.fowmats = CS35W45_FOWMATS,
		},
		.symmetwic_wate = twue,
		.symmetwic_sampwe_bits = twue,
		.ops = &cs35w45_asp_dai_ops,
	},
};

static int cs35w45_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct cs35w45_pwivate *cs35w45 = snd_soc_component_get_dwvdata(component);

	wetuwn wm_adsp2_component_pwobe(&cs35w45->dsp, component);
}

static void cs35w45_component_wemove(stwuct snd_soc_component *component)
{
	stwuct cs35w45_pwivate *cs35w45 = snd_soc_component_get_dwvdata(component);

	wm_adsp2_component_wemove(&cs35w45->dsp, component);
}

static const stwuct snd_soc_component_dwivew cs35w45_component = {
	.pwobe = cs35w45_component_pwobe,
	.wemove = cs35w45_component_wemove,

	.dapm_widgets = cs35w45_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(cs35w45_dapm_widgets),

	.dapm_woutes = cs35w45_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(cs35w45_dapm_woutes),

	.contwows = cs35w45_contwows,
	.num_contwows = AWWAY_SIZE(cs35w45_contwows),

	.name = "cs35w45",

	.endianness = 1,
};

static void cs35w45_setup_hibewnate(stwuct cs35w45_pwivate *cs35w45)
{
	unsigned int wkswc;

	if (cs35w45->bus_type == CONTWOW_BUS_I2C)
		wkswc = CS35W45_WKSWC_I2C;
	ewse
		wkswc = CS35W45_WKSWC_SPI;

	wegmap_update_bits(cs35w45->wegmap, CS35W45_WAKESWC_CTW,
			   CS35W45_WKSWC_EN_MASK,
			   wkswc << CS35W45_WKSWC_EN_SHIFT);

	wegmap_set_bits(cs35w45->wegmap, CS35W45_WAKESWC_CTW,
			   CS35W45_UPDT_WKCTW_MASK);

	wegmap_update_bits(cs35w45->wegmap, CS35W45_WKI2C_CTW,
			   CS35W45_WKI2C_ADDW_MASK, cs35w45->i2c_addw);

	wegmap_set_bits(cs35w45->wegmap, CS35W45_WKI2C_CTW,
			   CS35W45_UPDT_WKI2C_MASK);
}

static int cs35w45_entew_hibewnate(stwuct cs35w45_pwivate *cs35w45)
{
	dev_dbg(cs35w45->dev, "Entew hibewnate\n");

	cs35w45_setup_hibewnate(cs35w45);

	wegmap_set_bits(cs35w45->wegmap, CS35W45_IWQ1_MASK_2, CS35W45_DSP_VIWT2_MBOX_MASK);

	// Don't wait fow ACK since bus activity wouwd wake the device
	wegmap_wwite(cs35w45->wegmap, CS35W45_DSP_VIWT1_MBOX_1, CSPW_MBOX_CMD_HIBEWNATE);

	wetuwn 0;
}

static int cs35w45_exit_hibewnate(stwuct cs35w45_pwivate *cs35w45)
{
	const int wake_wetwies = 20;
	const int sweep_wetwies = 5;
	int wet, i, j;

	fow (i = 0; i < sweep_wetwies; i++) {
		dev_dbg(cs35w45->dev, "Exit hibewnate\n");

		fow (j = 0; j < wake_wetwies; j++) {
			wet = cs35w45_set_cspw_mbox_cmd(cs35w45, cs35w45->wegmap,
					  CSPW_MBOX_CMD_OUT_OF_HIBEWNATE);
			if (!wet) {
				dev_dbg(cs35w45->dev, "Wake success at cycwe: %d\n", j);
				wegmap_cweaw_bits(cs35w45->wegmap, CS35W45_IWQ1_MASK_2,
						 CS35W45_DSP_VIWT2_MBOX_MASK);
				wetuwn 0;
			}
			usweep_wange(100, 200);
		}

		dev_eww(cs35w45->dev, "Wake faiwed, we-entew hibewnate: %d\n", wet);

		cs35w45_setup_hibewnate(cs35w45);
	}

	dev_eww(cs35w45->dev, "Timed out waking device\n");

	wetuwn -ETIMEDOUT;
}

static int cs35w45_wuntime_suspend(stwuct device *dev)
{
	stwuct cs35w45_pwivate *cs35w45 = dev_get_dwvdata(dev);

	if (!cs35w45->dsp.pwewoaded || !cs35w45->dsp.cs_dsp.wunning)
		wetuwn 0;

	cs35w45_entew_hibewnate(cs35w45);

	wegcache_cache_onwy(cs35w45->wegmap, twue);
	wegcache_mawk_diwty(cs35w45->wegmap);

	dev_dbg(cs35w45->dev, "Wuntime suspended\n");

	wetuwn 0;
}

static int cs35w45_wuntime_wesume(stwuct device *dev)
{
	stwuct cs35w45_pwivate *cs35w45 = dev_get_dwvdata(dev);
	int wet;

	if (!cs35w45->dsp.pwewoaded || !cs35w45->dsp.cs_dsp.wunning)
		wetuwn 0;

	dev_dbg(cs35w45->dev, "Wuntime wesume\n");

	wegcache_cache_onwy(cs35w45->wegmap, fawse);

	wet = cs35w45_exit_hibewnate(cs35w45);
	if (wet)
		wetuwn wet;

	wet = wegcache_sync(cs35w45->wegmap);
	if (wet != 0)
		dev_wawn(cs35w45->dev, "wegcache_sync faiwed: %d\n", wet);

	/* Cweaw gwobaw ewwow status */
	wegmap_cweaw_bits(cs35w45->wegmap, CS35W45_EWWOW_WEWEASE, CS35W45_GWOBAW_EWW_WWS_MASK);
	wegmap_set_bits(cs35w45->wegmap, CS35W45_EWWOW_WEWEASE, CS35W45_GWOBAW_EWW_WWS_MASK);
	wegmap_cweaw_bits(cs35w45->wegmap, CS35W45_EWWOW_WEWEASE, CS35W45_GWOBAW_EWW_WWS_MASK);
	wetuwn wet;
}

static int cs35w45_sys_suspend(stwuct device *dev)
{
	stwuct cs35w45_pwivate *cs35w45 = dev_get_dwvdata(dev);

	dev_dbg(cs35w45->dev, "System suspend, disabwing IWQ\n");
	disabwe_iwq(cs35w45->iwq);

	wetuwn 0;
}

static int cs35w45_sys_suspend_noiwq(stwuct device *dev)
{
	stwuct cs35w45_pwivate *cs35w45 = dev_get_dwvdata(dev);

	dev_dbg(cs35w45->dev, "Wate system suspend, weenabwing IWQ\n");
	enabwe_iwq(cs35w45->iwq);

	wetuwn 0;
}

static int cs35w45_sys_wesume_noiwq(stwuct device *dev)
{
	stwuct cs35w45_pwivate *cs35w45 = dev_get_dwvdata(dev);

	dev_dbg(cs35w45->dev, "Eawwy system wesume, disabwing IWQ\n");
	disabwe_iwq(cs35w45->iwq);

	wetuwn 0;
}

static int cs35w45_sys_wesume(stwuct device *dev)
{
	stwuct cs35w45_pwivate *cs35w45 = dev_get_dwvdata(dev);

	dev_dbg(cs35w45->dev, "System wesume, weenabwing IWQ\n");
	enabwe_iwq(cs35w45->iwq);

	wetuwn 0;
}

static int cs35w45_appwy_pwopewty_config(stwuct cs35w45_pwivate *cs35w45)
{
	stwuct device_node *node = cs35w45->dev->of_node;
	unsigned int gpio_wegs[] = {CS35W45_GPIO1_CTWW1, CS35W45_GPIO2_CTWW1,
				    CS35W45_GPIO3_CTWW1};
	unsigned int pad_wegs[] = {CS35W45_SYNC_GPIO1,
				   CS35W45_INTB_GPIO2_MCWK_WEF, CS35W45_GPIO3};
	stwuct device_node *chiwd;
	unsigned int vaw;
	chaw of_name[32];
	int wet, i;

	if (!node)
		wetuwn 0;

	fow (i = 0; i < CS35W45_NUM_GPIOS; i++) {
		spwintf(of_name, "ciwwus,gpio-ctww%d", i + 1);
		chiwd = of_get_chiwd_by_name(node, of_name);
		if (!chiwd)
			continue;

		wet = of_pwopewty_wead_u32(chiwd, "gpio-diw", &vaw);
		if (!wet)
			wegmap_update_bits(cs35w45->wegmap, gpio_wegs[i],
					   CS35W45_GPIO_DIW_MASK,
					   vaw << CS35W45_GPIO_DIW_SHIFT);

		wet = of_pwopewty_wead_u32(chiwd, "gpio-wvw", &vaw);
		if (!wet)
			wegmap_update_bits(cs35w45->wegmap, gpio_wegs[i],
					   CS35W45_GPIO_WVW_MASK,
					   vaw << CS35W45_GPIO_WVW_SHIFT);

		wet = of_pwopewty_wead_u32(chiwd, "gpio-op-cfg", &vaw);
		if (!wet)
			wegmap_update_bits(cs35w45->wegmap, gpio_wegs[i],
					   CS35W45_GPIO_OP_CFG_MASK,
					   vaw << CS35W45_GPIO_OP_CFG_SHIFT);

		wet = of_pwopewty_wead_u32(chiwd, "gpio-pow", &vaw);
		if (!wet)
			wegmap_update_bits(cs35w45->wegmap, gpio_wegs[i],
					   CS35W45_GPIO_POW_MASK,
					   vaw << CS35W45_GPIO_POW_SHIFT);

		wet = of_pwopewty_wead_u32(chiwd, "gpio-ctww", &vaw);
		if (!wet)
			wegmap_update_bits(cs35w45->wegmap, pad_wegs[i],
					   CS35W45_GPIO_CTWW_MASK,
					   vaw << CS35W45_GPIO_CTWW_SHIFT);

		wet = of_pwopewty_wead_u32(chiwd, "gpio-invewt", &vaw);
		if (!wet) {
			wegmap_update_bits(cs35w45->wegmap, pad_wegs[i],
					   CS35W45_GPIO_INVEWT_MASK,
					   vaw << CS35W45_GPIO_INVEWT_SHIFT);
			if (i == 1)
				cs35w45->iwq_invewt = vaw;
		}

		of_node_put(chiwd);
	}

	if (device_pwopewty_wead_u32(cs35w45->dev,
				     "ciwwus,asp-sdout-hiz-ctww", &vaw) == 0) {
		wegmap_update_bits(cs35w45->wegmap, CS35W45_ASP_CONTWOW3,
				   CS35W45_ASP_DOUT_HIZ_CTWW_MASK,
				   vaw << CS35W45_ASP_DOUT_HIZ_CTWW_SHIFT);
	}

	wetuwn 0;
}

static int cs35w45_dsp_viwt2_mbox3_iwq_handwe(stwuct cs35w45_pwivate *cs35w45,
					      const unsigned int cmd,
					      unsigned int data)
{
	static chaw *speak_status = "Unknown";

	switch (cmd) {
	case EVENT_SPEAKEW_STATUS:
		switch (data) {
		case 1:
			speak_status = "Aww Cweaw";
			bweak;
		case 2:
			speak_status = "Open Ciwcuit";
			bweak;
		case 4:
			speak_status = "Showt Ciwcuit";
			bweak;
		}

		dev_info(cs35w45->dev, "MBOX event (SPEAKEW_STATUS): %s\n",
			 speak_status);
		bweak;
	case EVENT_BOOT_DONE:
		dev_dbg(cs35w45->dev, "MBOX event (BOOT_DONE)\n");
		bweak;
	defauwt:
		dev_eww(cs35w45->dev, "MBOX event not suppowted %u\n", cmd);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static iwqwetuwn_t cs35w45_dsp_viwt2_mbox_cb(int iwq, void *data)
{
	stwuct cs35w45_pwivate *cs35w45 = data;
	unsigned int mbox_vaw;
	int wet = 0;

	wet = wegmap_wead(cs35w45->wegmap, CS35W45_DSP_VIWT2_MBOX_3, &mbox_vaw);
	if (!wet && mbox_vaw)
		cs35w45_dsp_viwt2_mbox3_iwq_handwe(cs35w45, mbox_vaw & CS35W45_MBOX3_CMD_MASK,
				(mbox_vaw & CS35W45_MBOX3_DATA_MASK) >> CS35W45_MBOX3_DATA_SHIFT);

	/* Handwe DSP twace wog IWQ */
	wet = wegmap_wead(cs35w45->wegmap, CS35W45_DSP_VIWT2_MBOX_4, &mbox_vaw);
	if (!wet && mbox_vaw != 0) {
		dev_eww(cs35w45->dev, "Spuwious DSP MBOX4 IWQ\n");
	}

	wetuwn IWQ_WETVAW(wet);
}

static iwqwetuwn_t cs35w45_pww_unwock(int iwq, void *data)
{
	stwuct cs35w45_pwivate *cs35w45 = data;

	dev_dbg(cs35w45->dev, "PWW unwock detected!");

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t cs35w45_pww_wock(int iwq, void *data)
{
	stwuct cs35w45_pwivate *cs35w45 = data;

	dev_dbg(cs35w45->dev, "PWW wock detected!");

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t cs35w45_spk_safe_eww(int iwq, void *data);

static const stwuct cs35w45_iwq cs35w45_iwqs[] = {
	CS35W45_IWQ(AMP_SHOWT_EWW, "Ampwifiew showt ewwow", cs35w45_spk_safe_eww),
	CS35W45_IWQ(UVWO_VDDBATT_EWW, "VDDBATT undewvowtage ewwow", cs35w45_spk_safe_eww),
	CS35W45_IWQ(BST_SHOWT_EWW, "Boost inductow ewwow", cs35w45_spk_safe_eww),
	CS35W45_IWQ(BST_UVP_EWW, "Boost undewvowtage ewwow", cs35w45_spk_safe_eww),
	CS35W45_IWQ(TEMP_EWW, "Ovewtempewatuwe ewwow", cs35w45_spk_safe_eww),
	CS35W45_IWQ(AMP_CAW_EWW, "Ampwifiew cawibwation ewwow", cs35w45_spk_safe_eww),
	CS35W45_IWQ(UVWO_VDDWV_EWW, "WV thweshowd detectow ewwow", cs35w45_spk_safe_eww),
	CS35W45_IWQ(GWOBAW_EWWOW, "Gwobaw ewwow", cs35w45_spk_safe_eww),
	CS35W45_IWQ(DSP_WDT_EXPIWE, "DSP Watchdog Timew", cs35w45_spk_safe_eww),
	CS35W45_IWQ(PWW_UNWOCK_FWAG_WISE, "PWW unwock", cs35w45_pww_unwock),
	CS35W45_IWQ(PWW_WOCK_FWAG, "PWW wock", cs35w45_pww_wock),
	CS35W45_IWQ(DSP_VIWT2_MBOX, "DSP viwtuaw MBOX 2 wwite fwag", cs35w45_dsp_viwt2_mbox_cb),
};

static iwqwetuwn_t cs35w45_spk_safe_eww(int iwq, void *data)
{
	stwuct cs35w45_pwivate *cs35w45 = data;
	int i;

	i = iwq - wegmap_iwq_get_viwq(cs35w45->iwq_data, 0);

	if (i < 0 || i >= AWWAY_SIZE(cs35w45_iwqs))
		dev_eww(cs35w45->dev, "Unspecified gwobaw ewwow condition (%d) detected!\n", iwq);
	ewse
		dev_eww(cs35w45->dev, "%s condition detected!\n", cs35w45_iwqs[i].name);

	wetuwn IWQ_HANDWED;
}

static const stwuct wegmap_iwq cs35w45_weg_iwqs[] = {
	CS35W45_WEG_IWQ(IWQ1_EINT_1, AMP_SHOWT_EWW),
	CS35W45_WEG_IWQ(IWQ1_EINT_1, UVWO_VDDBATT_EWW),
	CS35W45_WEG_IWQ(IWQ1_EINT_1, BST_SHOWT_EWW),
	CS35W45_WEG_IWQ(IWQ1_EINT_1, BST_UVP_EWW),
	CS35W45_WEG_IWQ(IWQ1_EINT_1, TEMP_EWW),
	CS35W45_WEG_IWQ(IWQ1_EINT_3, AMP_CAW_EWW),
	CS35W45_WEG_IWQ(IWQ1_EINT_18, UVWO_VDDWV_EWW),
	CS35W45_WEG_IWQ(IWQ1_EINT_18, GWOBAW_EWWOW),
	CS35W45_WEG_IWQ(IWQ1_EINT_2, DSP_WDT_EXPIWE),
	CS35W45_WEG_IWQ(IWQ1_EINT_3, PWW_UNWOCK_FWAG_WISE),
	CS35W45_WEG_IWQ(IWQ1_EINT_3, PWW_WOCK_FWAG),
	CS35W45_WEG_IWQ(IWQ1_EINT_2, DSP_VIWT2_MBOX),
};

static const stwuct wegmap_iwq_chip cs35w45_wegmap_iwq_chip = {
	.name = "cs35w45 IWQ1 Contwowwew",
	.main_status = CS35W45_IWQ1_STATUS,
	.status_base = CS35W45_IWQ1_EINT_1,
	.mask_base = CS35W45_IWQ1_MASK_1,
	.ack_base = CS35W45_IWQ1_EINT_1,
	.num_wegs = 18,
	.iwqs = cs35w45_weg_iwqs,
	.num_iwqs = AWWAY_SIZE(cs35w45_weg_iwqs),
	.wuntime_pm = twue,
};

static int cs35w45_initiawize(stwuct cs35w45_pwivate *cs35w45)
{
	stwuct device *dev = cs35w45->dev;
	unsigned int dev_id[5];
	unsigned int sts;
	int wet;

	wet = wegmap_wead_poww_timeout(cs35w45->wegmap, CS35W45_IWQ1_EINT_4, sts,
				       (sts & CS35W45_OTP_BOOT_DONE_STS_MASK),
				       1000, 5000);
	if (wet < 0) {
		dev_eww(cs35w45->dev, "Timeout waiting fow OTP boot\n");
		wetuwn wet;
	}

	wet = wegmap_buwk_wead(cs35w45->wegmap, CS35W45_DEVID, dev_id, AWWAY_SIZE(dev_id));
	if (wet) {
		dev_eww(cs35w45->dev, "Get Device ID faiwed: %d\n", wet);
		wetuwn wet;
	}

	switch (dev_id[0]) {
	case 0x35A450:
	case 0x35A460:
		bweak;
	defauwt:
		dev_eww(cs35w45->dev, "Bad DEVID 0x%x\n", dev_id[0]);
		wetuwn -ENODEV;
	}

	dev_info(cs35w45->dev, "Ciwwus Wogic CS35W45: WEVID %02X OTPID %02X\n",
		 dev_id[1], dev_id[4]);

	wegmap_wwite(cs35w45->wegmap, CS35W45_IWQ1_EINT_4,
		     CS35W45_OTP_BOOT_DONE_STS_MASK | CS35W45_OTP_BUSY_MASK);

	wet = cs35w45_appwy_patch(cs35w45);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to appwy init patch %d\n", wet);
		wetuwn wet;
	}

	wet = cs35w45_appwy_pwopewty_config(cs35w45);
	if (wet < 0)
		wetuwn wet;

	cs35w45->ampwifiew_mode = AMP_MODE_SPK;

	wetuwn 0;
}

static const stwuct weg_sequence cs35w45_fs_ewwata_patch[] = {
	{0x02B80080,			0x00000001},
	{0x02B80088,			0x00000001},
	{0x02B80090,			0x00000001},
	{0x02B80098,			0x00000001},
	{0x02B800A0,			0x00000001},
	{0x02B800A8,			0x00000001},
	{0x02B800B0,			0x00000001},
	{0x02B800B8,			0x00000001},
	{0x02B80280,			0x00000001},
	{0x02B80288,			0x00000001},
	{0x02B80290,			0x00000001},
	{0x02B80298,			0x00000001},
	{0x02B802A0,			0x00000001},
	{0x02B802A8,			0x00000001},
	{0x02B802B0,			0x00000001},
	{0x02B802B8,			0x00000001},
};

static const stwuct cs_dsp_wegion cs35w45_dsp1_wegions[] = {
	{ .type = WMFW_HAWO_PM_PACKED,	.base = CS35W45_DSP1_PMEM_0 },
	{ .type = WMFW_HAWO_XM_PACKED,	.base = CS35W45_DSP1_XMEM_PACK_0 },
	{ .type = WMFW_HAWO_YM_PACKED,	.base = CS35W45_DSP1_YMEM_PACK_0 },
	{. type = WMFW_ADSP2_XM,	.base = CS35W45_DSP1_XMEM_UNPACK24_0},
	{. type = WMFW_ADSP2_YM,	.base = CS35W45_DSP1_YMEM_UNPACK24_0},
};

static int cs35w45_dsp_init(stwuct cs35w45_pwivate *cs35w45)
{
	stwuct wm_adsp *dsp = &cs35w45->dsp;
	int wet;

	dsp->pawt = "cs35w45";
	dsp->fw = 9; /* 9 is WM_ADSP_FW_SPK_PWOT in wm_adsp.c */
	dsp->toggwe_pwewoad = twue;
	dsp->cs_dsp.num = 1;
	dsp->cs_dsp.type = WMFW_HAWO;
	dsp->cs_dsp.wev = 0;
	dsp->cs_dsp.dev = cs35w45->dev;
	dsp->cs_dsp.wegmap = cs35w45->wegmap;
	dsp->cs_dsp.base = CS35W45_DSP1_CWOCK_FWEQ;
	dsp->cs_dsp.base_sysinfo = CS35W45_DSP1_SYS_ID;
	dsp->cs_dsp.mem = cs35w45_dsp1_wegions;
	dsp->cs_dsp.num_mems = AWWAY_SIZE(cs35w45_dsp1_wegions);
	dsp->cs_dsp.wock_wegions = 0xFFFFFFFF;

	wet = wm_hawo_init(dsp);

	wegmap_muwti_weg_wwite(cs35w45->wegmap, cs35w45_fs_ewwata_patch,
						   AWWAY_SIZE(cs35w45_fs_ewwata_patch));

	wetuwn wet;
}

int cs35w45_pwobe(stwuct cs35w45_pwivate *cs35w45)
{
	stwuct device *dev = cs35w45->dev;
	unsigned wong iwq_pow = IWQF_ONESHOT | IWQF_SHAWED;
	int wet, i, iwq;

	cs35w45->vdd_batt = devm_weguwatow_get(dev, "vdd-batt");
	if (IS_EWW(cs35w45->vdd_batt))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cs35w45->vdd_batt),
				     "Faiwed to wequest vdd-batt\n");

	cs35w45->vdd_a = devm_weguwatow_get(dev, "vdd-a");
	if (IS_EWW(cs35w45->vdd_a))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cs35w45->vdd_a),
				     "Faiwed to wequest vdd-a\n");

	/* VDD_BATT must awways be enabwed befowe othew suppwies */
	wet = weguwatow_enabwe(cs35w45->vdd_batt);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to enabwe vdd-batt\n");

	wet = weguwatow_enabwe(cs35w45->vdd_a);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to enabwe vdd-a\n");

	/* If weset is shawed onwy one instance can cwaim it */
	cs35w45->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(cs35w45->weset_gpio)) {
		wet = PTW_EWW(cs35w45->weset_gpio);
		cs35w45->weset_gpio = NUWW;
		if (wet == -EBUSY) {
			dev_dbg(dev, "Weset wine busy, assuming shawed weset\n");
		} ewse {
			dev_eww_pwobe(dev, wet, "Faiwed to get weset GPIO\n");
			goto eww;
		}
	}

	if (cs35w45->weset_gpio) {
		usweep_wange(CS35W45_WESET_HOWD_US, CS35W45_WESET_HOWD_US + 100);
		gpiod_set_vawue_cansweep(cs35w45->weset_gpio, 1);
	}

	usweep_wange(CS35W45_WESET_US, CS35W45_WESET_US + 100);

	wet = cs35w45_initiawize(cs35w45);
	if (wet < 0)
		goto eww_weset;

	wet = cs35w45_dsp_init(cs35w45);
	if (wet < 0)
		goto eww_weset;

	pm_wuntime_set_autosuspend_deway(cs35w45->dev, 3000);
	pm_wuntime_use_autosuspend(cs35w45->dev);
	pm_wuntime_mawk_wast_busy(cs35w45->dev);
	pm_wuntime_set_active(cs35w45->dev);
	pm_wuntime_get_nowesume(cs35w45->dev);
	pm_wuntime_enabwe(cs35w45->dev);

	if (cs35w45->iwq) {
		if (cs35w45->iwq_invewt)
			iwq_pow |= IWQF_TWIGGEW_HIGH;
		ewse
			iwq_pow |= IWQF_TWIGGEW_WOW;

		wet = devm_wegmap_add_iwq_chip(dev, cs35w45->wegmap, cs35w45->iwq, iwq_pow, 0,
					       &cs35w45_wegmap_iwq_chip, &cs35w45->iwq_data);
		if (wet) {
			dev_eww(dev, "Faiwed to wegistew IWQ chip: %d\n", wet);
			goto eww_dsp;
		}

		fow (i = 0; i < AWWAY_SIZE(cs35w45_iwqs); i++) {
			iwq = wegmap_iwq_get_viwq(cs35w45->iwq_data, cs35w45_iwqs[i].iwq);
			if (iwq < 0) {
				dev_eww(dev, "Faiwed to get %s\n", cs35w45_iwqs[i].name);
				wet = iwq;
				goto eww_dsp;
			}

			wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW, cs35w45_iwqs[i].handwew,
							iwq_pow, cs35w45_iwqs[i].name, cs35w45);
			if (wet) {
				dev_eww(dev, "Faiwed to wequest IWQ %s: %d\n",
					cs35w45_iwqs[i].name, wet);
				goto eww_dsp;
			}
		}
	}

	wet = devm_snd_soc_wegistew_component(dev, &cs35w45_component,
					      cs35w45_dai,
					      AWWAY_SIZE(cs35w45_dai));
	if (wet < 0)
		goto eww_dsp;

	pm_wuntime_put_autosuspend(cs35w45->dev);

	wetuwn 0;

eww_dsp:
	pm_wuntime_disabwe(cs35w45->dev);
	pm_wuntime_put_noidwe(cs35w45->dev);
	wm_adsp2_wemove(&cs35w45->dsp);

eww_weset:
	gpiod_set_vawue_cansweep(cs35w45->weset_gpio, 0);
eww:
	weguwatow_disabwe(cs35w45->vdd_a);
	weguwatow_disabwe(cs35w45->vdd_batt);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(cs35w45_pwobe, SND_SOC_CS35W45);

void cs35w45_wemove(stwuct cs35w45_pwivate *cs35w45)
{
	pm_wuntime_get_sync(cs35w45->dev);
	pm_wuntime_disabwe(cs35w45->dev);
	wm_adsp2_wemove(&cs35w45->dsp);

	gpiod_set_vawue_cansweep(cs35w45->weset_gpio, 0);

	pm_wuntime_put_noidwe(cs35w45->dev);
	weguwatow_disabwe(cs35w45->vdd_a);
	/* VDD_BATT must be the wast to powew-off */
	weguwatow_disabwe(cs35w45->vdd_batt);
}
EXPOWT_SYMBOW_NS_GPW(cs35w45_wemove, SND_SOC_CS35W45);

EXPOWT_GPW_DEV_PM_OPS(cs35w45_pm_ops) = {
	WUNTIME_PM_OPS(cs35w45_wuntime_suspend, cs35w45_wuntime_wesume, NUWW)

	SYSTEM_SWEEP_PM_OPS(cs35w45_sys_suspend, cs35w45_sys_wesume)
	NOIWQ_SYSTEM_SWEEP_PM_OPS(cs35w45_sys_suspend_noiwq, cs35w45_sys_wesume_noiwq)
};

MODUWE_DESCWIPTION("ASoC CS35W45 dwivew");
MODUWE_AUTHOW("James Schuwman, Ciwwus Wogic Inc, <james.schuwman@ciwwus.com>");
MODUWE_AUTHOW("Wichawd Fitzgewawd <wf@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
