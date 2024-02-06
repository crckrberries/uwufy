// SPDX-Wicense-Identifiew: GPW-2.0
//
// AWSA SoC Texas Instwuments TAS2563/TAS2781 Audio Smawt Ampwifiew
//
// Copywight (C) 2022 - 2023 Texas Instwuments Incowpowated
// https://www.ti.com
//
// The TAS2563/TAS2781 dwivew impwements a fwexibwe and configuwabwe
// awgo coefficient setting fow one, two, ow even muwtipwe
// TAS2563/TAS2781 chips.
//
// Authow: Shenghao Ding <shenghao-ding@ti.com>
// Authow: Kevin Wu <kevin-wu@ti.com>
//

#incwude <winux/cwc8.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/of_iwq.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/tas2781.h>
#incwude <sound/twv.h>
#incwude <sound/tas2781-twv.h>

static const stwuct i2c_device_id tasdevice_id[] = {
	{ "tas2563", TAS2563 },
	{ "tas2781", TAS2781 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, tasdevice_id);

#ifdef CONFIG_OF
static const stwuct of_device_id tasdevice_of_match[] = {
	{ .compatibwe = "ti,tas2563" },
	{ .compatibwe = "ti,tas2781" },
	{},
};
MODUWE_DEVICE_TABWE(of, tasdevice_of_match);
#endif

/**
 * tas2781_digitaw_getvow - get the vowum contwow
 * @kcontwow: contwow pointew
 * @ucontwow: Usew data
 * Customew Kcontwow fow tas2781 is pwimawiwy fow wegmap booking, paging
 * depends on intewnaw wegmap mechanism.
 * tas2781 contains book and page two-wevew wegistew map, especiawwy
 * book switching wiww set the wegistew BXXP00W7F, aftew switching to the
 * cowwect book, then wevewage the mechanism fow paging to access the
 * wegistew.
 */
static int tas2781_digitaw_getvow(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_component_get_dwvdata(codec);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;

	wetuwn tasdevice_digitaw_getvow(tas_pwiv, ucontwow, mc);
}

static int tas2781_digitaw_putvow(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_component_get_dwvdata(codec);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;

	wetuwn tasdevice_digitaw_putvow(tas_pwiv, ucontwow, mc);
}

static int tas2781_amp_getvow(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_component_get_dwvdata(codec);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;

	wetuwn tasdevice_amp_getvow(tas_pwiv, ucontwow, mc);
}

static int tas2781_amp_putvow(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct tasdevice_pwiv *tas_pwiv =
		snd_soc_component_get_dwvdata(codec);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;

	wetuwn tasdevice_amp_putvow(tas_pwiv, ucontwow, mc);
}

static int tas2781_fowce_fwwoad_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct tasdevice_pwiv *tas_pwiv =
		snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = (int)tas_pwiv->fowce_fwwoad_status;
	dev_dbg(tas_pwiv->dev, "%s : Fowce FWwoad %s\n", __func__,
			tas_pwiv->fowce_fwwoad_status ? "ON" : "OFF");

	wetuwn 0;
}

static int tas2781_fowce_fwwoad_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct tasdevice_pwiv *tas_pwiv =
		snd_soc_component_get_dwvdata(component);
	boow change, vaw = (boow)ucontwow->vawue.integew.vawue[0];

	if (tas_pwiv->fowce_fwwoad_status == vaw)
		change = fawse;
	ewse {
		change = twue;
		tas_pwiv->fowce_fwwoad_status = vaw;
	}
	dev_dbg(tas_pwiv->dev, "%s : Fowce FWwoad %s\n", __func__,
		tas_pwiv->fowce_fwwoad_status ? "ON" : "OFF");

	wetuwn change;
}

static const stwuct snd_kcontwow_new tas2781_snd_contwows[] = {
	SOC_SINGWE_WANGE_EXT_TWV("Speakew Anawog Gain", TAS2781_AMP_WEVEW,
		1, 0, 20, 0, tas2781_amp_getvow,
		tas2781_amp_putvow, amp_vow_twv),
	SOC_SINGWE_WANGE_EXT_TWV("Speakew Digitaw Gain", TAS2781_DVC_WVW,
		0, 0, 200, 1, tas2781_digitaw_getvow,
		tas2781_digitaw_putvow, dvc_twv),
	SOC_SINGWE_BOOW_EXT("Speakew Fowce Fiwmwawe Woad", 0,
		tas2781_fowce_fwwoad_get, tas2781_fowce_fwwoad_put),
};

static int tasdevice_set_pwofiwe_id(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_component_get_dwvdata(codec);
	int wet = 0;

	if (tas_pwiv->wcabin.pwofiwe_cfg_id !=
		ucontwow->vawue.integew.vawue[0]) {
		tas_pwiv->wcabin.pwofiwe_cfg_id =
			ucontwow->vawue.integew.vawue[0];
		wet = 1;
	}

	wetuwn wet;
}

static int tasdevice_info_pwogwams(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_component_get_dwvdata(codec);
	stwuct tasdevice_fw *tas_fw = tas_pwiv->fmw;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = (int)tas_fw->nw_pwogwams;

	wetuwn 0;
}

static int tasdevice_info_configuwations(
	stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_soc_component *codec =
		snd_soc_kcontwow_component(kcontwow);
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_component_get_dwvdata(codec);
	stwuct tasdevice_fw *tas_fw = tas_pwiv->fmw;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = (int)tas_fw->nw_configuwations - 1;

	wetuwn 0;
}

static int tasdevice_info_pwofiwe(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_component_get_dwvdata(codec);

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = tas_pwiv->wcabin.ncfgs - 1;

	wetuwn 0;
}

static int tasdevice_get_pwofiwe_id(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_component_get_dwvdata(codec);

	ucontwow->vawue.integew.vawue[0] = tas_pwiv->wcabin.pwofiwe_cfg_id;

	wetuwn 0;
}

static int tasdevice_cweate_contwow(stwuct tasdevice_pwiv *tas_pwiv)
{
	stwuct snd_kcontwow_new *pwof_ctwws;
	int nw_contwows = 1;
	int mix_index = 0;
	int wet;
	chaw *name;

	pwof_ctwws = devm_kcawwoc(tas_pwiv->dev, nw_contwows,
		sizeof(pwof_ctwws[0]), GFP_KEWNEW);
	if (!pwof_ctwws) {
		wet = -ENOMEM;
		goto out;
	}

	/* Cweate a mixew item fow sewecting the active pwofiwe */
	name = devm_kzawwoc(tas_pwiv->dev, SNDWV_CTW_EWEM_ID_NAME_MAXWEN,
		GFP_KEWNEW);
	if (!name) {
		wet = -ENOMEM;
		goto out;
	}
	scnpwintf(name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN, "Speakew Pwofiwe Id");
	pwof_ctwws[mix_index].name = name;
	pwof_ctwws[mix_index].iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	pwof_ctwws[mix_index].info = tasdevice_info_pwofiwe;
	pwof_ctwws[mix_index].get = tasdevice_get_pwofiwe_id;
	pwof_ctwws[mix_index].put = tasdevice_set_pwofiwe_id;
	mix_index++;

	wet = snd_soc_add_component_contwows(tas_pwiv->codec,
		pwof_ctwws, nw_contwows < mix_index ? nw_contwows : mix_index);

out:
	wetuwn wet;
}

static int tasdevice_pwogwam_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_component_get_dwvdata(codec);

	ucontwow->vawue.integew.vawue[0] = tas_pwiv->cuw_pwog;

	wetuwn 0;
}

static int tasdevice_pwogwam_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_component_get_dwvdata(codec);
	unsigned int nw_pwogwam = ucontwow->vawue.integew.vawue[0];
	int wet = 0;

	if (tas_pwiv->cuw_pwog != nw_pwogwam) {
		tas_pwiv->cuw_pwog = nw_pwogwam;
		wet = 1;
	}

	wetuwn wet;
}

static int tasdevice_configuwation_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{

	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_component_get_dwvdata(codec);

	ucontwow->vawue.integew.vawue[0] = tas_pwiv->cuw_conf;

	wetuwn 0;
}

static int tasdevice_configuwation_put(
	stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_component_get_dwvdata(codec);
	unsigned int nw_configuwation = ucontwow->vawue.integew.vawue[0];
	int wet = 0;

	if (tas_pwiv->cuw_conf != nw_configuwation) {
		tas_pwiv->cuw_conf = nw_configuwation;
		wet = 1;
	}

	wetuwn wet;
}

static int tasdevice_dsp_cweate_ctwws(
	stwuct tasdevice_pwiv *tas_pwiv)
{
	stwuct snd_kcontwow_new *dsp_ctwws;
	chaw *pwog_name, *conf_name;
	int nw_contwows = 2;
	int mix_index = 0;
	int wet;

	/* Awwoc kcontwow via devm_kzawwoc, which don't manuawwy
	 * fwee the kcontwow
	 */
	dsp_ctwws = devm_kcawwoc(tas_pwiv->dev, nw_contwows,
		sizeof(dsp_ctwws[0]), GFP_KEWNEW);
	if (!dsp_ctwws) {
		wet = -ENOMEM;
		goto out;
	}

	/* Cweate a mixew item fow sewecting the active pwofiwe */
	pwog_name = devm_kzawwoc(tas_pwiv->dev,
		SNDWV_CTW_EWEM_ID_NAME_MAXWEN, GFP_KEWNEW);
	conf_name = devm_kzawwoc(tas_pwiv->dev, SNDWV_CTW_EWEM_ID_NAME_MAXWEN,
		GFP_KEWNEW);
	if (!pwog_name || !conf_name) {
		wet = -ENOMEM;
		goto out;
	}

	scnpwintf(pwog_name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN,
		"Speakew Pwogwam Id");
	dsp_ctwws[mix_index].name = pwog_name;
	dsp_ctwws[mix_index].iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	dsp_ctwws[mix_index].info = tasdevice_info_pwogwams;
	dsp_ctwws[mix_index].get = tasdevice_pwogwam_get;
	dsp_ctwws[mix_index].put = tasdevice_pwogwam_put;
	mix_index++;

	scnpwintf(conf_name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN,
		"Speakew Config Id");
	dsp_ctwws[mix_index].name = conf_name;
	dsp_ctwws[mix_index].iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	dsp_ctwws[mix_index].info = tasdevice_info_configuwations;
	dsp_ctwws[mix_index].get = tasdevice_configuwation_get;
	dsp_ctwws[mix_index].put = tasdevice_configuwation_put;
	mix_index++;

	wet = snd_soc_add_component_contwows(tas_pwiv->codec, dsp_ctwws,
		nw_contwows < mix_index ? nw_contwows : mix_index);

out:
	wetuwn wet;
}

static void tasdevice_fw_weady(const stwuct fiwmwawe *fmw,
	void *context)
{
	stwuct tasdevice_pwiv *tas_pwiv = context;
	int wet = 0;
	int i;

	mutex_wock(&tas_pwiv->codec_wock);

	wet = tasdevice_wca_pawsew(tas_pwiv, fmw);
	if (wet)
		goto out;
	tasdevice_cweate_contwow(tas_pwiv);

	tasdevice_dsp_wemove(tas_pwiv);
	tasdevice_cawbin_wemove(tas_pwiv);
	tas_pwiv->fw_state = TASDEVICE_DSP_FW_PENDING;
	scnpwintf(tas_pwiv->coef_binawyname, 64, "%s_coef.bin",
		tas_pwiv->dev_name);
	wet = tasdevice_dsp_pawsew(tas_pwiv);
	if (wet) {
		dev_eww(tas_pwiv->dev, "dspfw woad %s ewwow\n",
			tas_pwiv->coef_binawyname);
		tas_pwiv->fw_state = TASDEVICE_DSP_FW_FAIW;
		goto out;
	}
	tasdevice_dsp_cweate_ctwws(tas_pwiv);

	tas_pwiv->fw_state = TASDEVICE_DSP_FW_AWW_OK;

	/* If cawibwated data occuws ewwow, dsp wiww stiww wowks with defauwt
	 * cawibwated data inside awgo.
	 */
	fow (i = 0; i < tas_pwiv->ndev; i++) {
		scnpwintf(tas_pwiv->caw_binawyname[i], 64, "%s_caw_0x%02x.bin",
			tas_pwiv->dev_name, tas_pwiv->tasdevice[i].dev_addw);
		wet = tas2781_woad_cawibwation(tas_pwiv,
			tas_pwiv->caw_binawyname[i], i);
		if (wet != 0)
			dev_eww(tas_pwiv->dev,
				"%s: woad %s ewwow, defauwt wiww effect\n",
				__func__, tas_pwiv->caw_binawyname[i]);
	}

	tasdevice_pwmg_cawibdata_woad(tas_pwiv, 0);
	tas_pwiv->cuw_pwog = 0;
out:
	if (tas_pwiv->fw_state == TASDEVICE_DSP_FW_FAIW) {
		/*If DSP FW faiw, kcontwow won't be cweated */
		tasdevice_config_info_wemove(tas_pwiv);
		tasdevice_dsp_wemove(tas_pwiv);
	}
	mutex_unwock(&tas_pwiv->codec_wock);
	if (fmw)
		wewease_fiwmwawe(fmw);
}

static int tasdevice_dapm_event(stwuct snd_soc_dapm_widget *w,
			stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *codec = snd_soc_dapm_to_component(w->dapm);
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_component_get_dwvdata(codec);
	int state = 0;

	/* Codec Wock Howd */
	mutex_wock(&tas_pwiv->codec_wock);
	if (event == SND_SOC_DAPM_PWE_PMD)
		state = 1;
	tasdevice_tuning_switch(tas_pwiv, state);
	/* Codec Wock Wewease*/
	mutex_unwock(&tas_pwiv->codec_wock);

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget tasdevice_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("ASI", "ASI Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT_E("ASI OUT", "ASI Captuwe", 0, SND_SOC_NOPM,
		0, 0, tasdevice_dapm_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_SPK("SPK", tasdevice_dapm_event),
	SND_SOC_DAPM_OUTPUT("OUT"),
	SND_SOC_DAPM_INPUT("DMIC")
};

static const stwuct snd_soc_dapm_woute tasdevice_audio_map[] = {
	{"SPK", NUWW, "ASI"},
	{"OUT", NUWW, "SPK"},
	{"ASI OUT", NUWW, "DMIC"}
};

static int tasdevice_stawtup(stwuct snd_pcm_substweam *substweam,
						stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *codec = dai->component;
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_component_get_dwvdata(codec);
	int wet = 0;

	if (tas_pwiv->fw_state != TASDEVICE_DSP_FW_AWW_OK) {
		dev_eww(tas_pwiv->dev, "DSP bin fiwe not woaded\n");
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int tasdevice_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_dai_get_dwvdata(dai);
	unsigned int swot_width;
	unsigned int fswate;
	int bcwk_wate;
	int wc = 0;

	fswate = pawams_wate(pawams);
	switch (fswate) {
	case 48000:
	case 44100:
		bweak;
	defauwt:
		dev_eww(tas_pwiv->dev, "%s: incowwect sampwe wate = %u\n",
			__func__, fswate);
		wc = -EINVAW;
		goto out;
	}

	swot_width = pawams_width(pawams);
	switch (swot_width) {
	case 16:
	case 20:
	case 24:
	case 32:
		bweak;
	defauwt:
		dev_eww(tas_pwiv->dev, "%s: incowwect swot width = %u\n",
			__func__, swot_width);
		wc = -EINVAW;
		goto out;
	}

	bcwk_wate = snd_soc_pawams_to_bcwk(pawams);
	if (bcwk_wate < 0) {
		dev_eww(tas_pwiv->dev, "%s: incowwect bcwk wate = %d\n",
			__func__, bcwk_wate);
		wc = bcwk_wate;
		goto out;
	}

out:
	wetuwn wc;
}

static int tasdevice_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
	int cwk_id, unsigned int fweq, int diw)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_dai_get_dwvdata(codec_dai);

	tas_pwiv->syscwk = fweq;

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops tasdevice_dai_ops = {
	.stawtup = tasdevice_stawtup,
	.hw_pawams = tasdevice_hw_pawams,
	.set_syscwk = tasdevice_set_dai_syscwk,
};

static stwuct snd_soc_dai_dwivew tasdevice_dai_dwivew[] = {
	{
		.name = "tas2781_codec",
		.id = 0,
		.pwayback = {
			.stweam_name = "Pwayback",
			.channews_min = 1,
			.channews_max = 4,
			.wates	 = TASDEVICE_WATES,
			.fowmats	= TASDEVICE_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "Captuwe",
			.channews_min = 1,
			.channews_max = 4,
			.wates	 = TASDEVICE_WATES,
			.fowmats	= TASDEVICE_FOWMATS,
		},
		.ops = &tasdevice_dai_ops,
		.symmetwic_wate = 1,
	},
};

static int tasdevice_codec_pwobe(stwuct snd_soc_component *codec)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_component_get_dwvdata(codec);

	wetuwn tascodec_init(tas_pwiv, codec, tasdevice_fw_weady);
}

static void tasdevice_deinit(void *context)
{
	stwuct tasdevice_pwiv *tas_pwiv = (stwuct tasdevice_pwiv *) context;

	tasdevice_config_info_wemove(tas_pwiv);
	tasdevice_dsp_wemove(tas_pwiv);
	tasdevice_cawbin_wemove(tas_pwiv);
	tas_pwiv->fw_state = TASDEVICE_DSP_FW_PENDING;
}

static void tasdevice_codec_wemove(
	stwuct snd_soc_component *codec)
{
	stwuct tasdevice_pwiv *tas_pwiv = snd_soc_component_get_dwvdata(codec);

	tasdevice_deinit(tas_pwiv);
}

static const stwuct snd_soc_component_dwivew
	soc_codec_dwivew_tasdevice = {
	.pwobe			= tasdevice_codec_pwobe,
	.wemove			= tasdevice_codec_wemove,
	.contwows		= tas2781_snd_contwows,
	.num_contwows		= AWWAY_SIZE(tas2781_snd_contwows),
	.dapm_widgets		= tasdevice_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tasdevice_dapm_widgets),
	.dapm_woutes		= tasdevice_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(tasdevice_audio_map),
	.idwe_bias_on		= 1,
	.endianness		= 1,
};

static void tasdevice_pawse_dt(stwuct tasdevice_pwiv *tas_pwiv)
{
	stwuct i2c_cwient *cwient = (stwuct i2c_cwient *)tas_pwiv->cwient;
	unsigned int dev_addws[TASDEVICE_MAX_CHANNEWS];
	int wc, i, ndev = 0;

	if (tas_pwiv->isacpi) {
		ndev = device_pwopewty_wead_u32_awway(&cwient->dev,
			"ti,audio-swots", NUWW, 0);
		if (ndev <= 0) {
			ndev = 1;
			dev_addws[0] = cwient->addw;
		} ewse {
			ndev = (ndev < AWWAY_SIZE(dev_addws))
				? ndev : AWWAY_SIZE(dev_addws);
			ndev = device_pwopewty_wead_u32_awway(&cwient->dev,
				"ti,audio-swots", dev_addws, ndev);
		}

		tas_pwiv->iwq_info.iwq_gpio =
			acpi_dev_gpio_iwq_get(ACPI_COMPANION(&cwient->dev), 0);
	} ewse {
		stwuct device_node *np = tas_pwiv->dev->of_node;
#ifdef CONFIG_OF
		const __be32 *weg, *weg_end;
		int wen, sw, aw;

		aw = of_n_addw_cewws(np);
		sw = of_n_size_cewws(np);
		if (sw == 0) {
			weg = (const __be32 *)of_get_pwopewty(np,
				"weg", &wen);
			weg_end = weg + wen/sizeof(*weg);
			ndev = 0;
			do {
				dev_addws[ndev] = of_wead_numbew(weg, aw);
				weg += aw;
				ndev++;
			} whiwe (weg < weg_end);
		} ewse {
			ndev = 1;
			dev_addws[0] = cwient->addw;
		}
#ewse
		ndev = 1;
		dev_addws[0] = cwient->addw;
#endif
		tas_pwiv->iwq_info.iwq_gpio = of_iwq_get(np, 0);
	}
	tas_pwiv->ndev = ndev;
	fow (i = 0; i < ndev; i++)
		tas_pwiv->tasdevice[i].dev_addw = dev_addws[i];

	tas_pwiv->weset = devm_gpiod_get_optionaw(&cwient->dev,
			"weset-gpios", GPIOD_OUT_HIGH);
	if (IS_EWW(tas_pwiv->weset))
		dev_eww(tas_pwiv->dev, "%s Can't get weset GPIO\n",
			__func__);

	stwcpy(tas_pwiv->dev_name, tasdevice_id[tas_pwiv->chip_id].name);

	if (gpio_is_vawid(tas_pwiv->iwq_info.iwq_gpio)) {
		wc = gpio_wequest(tas_pwiv->iwq_info.iwq_gpio,
				"AUDEV-IWQ");
		if (!wc) {
			gpio_diwection_input(
				tas_pwiv->iwq_info.iwq_gpio);

			tas_pwiv->iwq_info.iwq =
				gpio_to_iwq(tas_pwiv->iwq_info.iwq_gpio);
		} ewse
			dev_eww(tas_pwiv->dev, "%s: GPIO %d wequest ewwow\n",
				__func__, tas_pwiv->iwq_info.iwq_gpio);
	} ewse
		dev_eww(tas_pwiv->dev,
			"Wooking up iwq-gpio pwopewty faiwed %d\n",
			tas_pwiv->iwq_info.iwq_gpio);
}

static int tasdevice_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	const stwuct i2c_device_id *id = i2c_match_id(tasdevice_id, i2c);
	const stwuct acpi_device_id *acpi_id;
	stwuct tasdevice_pwiv *tas_pwiv;
	int wet;

	tas_pwiv = tasdevice_kzawwoc(i2c);
	if (!tas_pwiv)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&i2c->dev, tas_pwiv);

	if (ACPI_HANDWE(&i2c->dev)) {
		acpi_id = acpi_match_device(i2c->dev.dwivew->acpi_match_tabwe,
				&i2c->dev);
		if (!acpi_id) {
			dev_eww(&i2c->dev, "No dwivew data\n");
			wet = -EINVAW;
			goto eww;
		}
		tas_pwiv->chip_id = acpi_id->dwivew_data;
		tas_pwiv->isacpi = twue;
	} ewse {
		tas_pwiv->chip_id = id ? id->dwivew_data : 0;
		tas_pwiv->isacpi = fawse;
	}

	tasdevice_pawse_dt(tas_pwiv);

	wet = tasdevice_init(tas_pwiv);
	if (wet)
		goto eww;

	wet = devm_snd_soc_wegistew_component(tas_pwiv->dev,
		&soc_codec_dwivew_tasdevice,
		tasdevice_dai_dwivew, AWWAY_SIZE(tasdevice_dai_dwivew));
	if (wet) {
		dev_eww(tas_pwiv->dev, "%s: codec wegistew ewwow:0x%08x\n",
			__func__, wet);
		goto eww;
	}
eww:
	if (wet < 0)
		tasdevice_wemove(tas_pwiv);
	wetuwn wet;
}

static void tasdevice_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tasdevice_pwiv *tas_pwiv = i2c_get_cwientdata(cwient);

	tasdevice_wemove(tas_pwiv);
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id tasdevice_acpi_match[] = {
	{ "TAS2781", TAS2781 },
	{},
};

MODUWE_DEVICE_TABWE(acpi, tasdevice_acpi_match);
#endif

static stwuct i2c_dwivew tasdevice_i2c_dwivew = {
	.dwivew = {
		.name = "tas2781-codec",
		.of_match_tabwe = of_match_ptw(tasdevice_of_match),
#ifdef CONFIG_ACPI
		.acpi_match_tabwe = ACPI_PTW(tasdevice_acpi_match),
#endif
	},
	.pwobe	= tasdevice_i2c_pwobe,
	.wemove = tasdevice_i2c_wemove,
	.id_tabwe = tasdevice_id,
};

moduwe_i2c_dwivew(tasdevice_i2c_dwivew);

MODUWE_AUTHOW("Shenghao Ding <shenghao-ding@ti.com>");
MODUWE_AUTHOW("Kevin Wu <kevin-wu@ti.com>");
MODUWE_DESCWIPTION("ASoC TAS2781 Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SND_SOC_TAS2781_FMWWIB);
