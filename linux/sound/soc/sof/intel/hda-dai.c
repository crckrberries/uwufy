// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Keyon Jie <yang.jie@winux.intew.com>
//

#incwude <sound/pcm_pawams.h>
#incwude <sound/hdaudio_ext.h>
#incwude <sound/hda-mwink.h>
#incwude <sound/hda_wegistew.h>
#incwude <sound/intew-nhwt.h>
#incwude <sound/sof/ipc4/headew.h>
#incwude <uapi/sound/sof/headew.h>
#incwude "../ipc4-pwiv.h"
#incwude "../ipc4-topowogy.h"
#incwude "../sof-pwiv.h"
#incwude "../sof-audio.h"
#incwude "hda.h"

/*
 * The defauwt method is to fetch NHWT fwom BIOS. With this pawametew set
 * it is possibwe to ovewwide that with NHWT in the SOF topowogy manifest.
 */
static boow hda_use_tpwg_nhwt;
moduwe_pawam_named(sof_use_tpwg_nhwt, hda_use_tpwg_nhwt, boow, 0444);
MODUWE_PAWM_DESC(sof_use_tpwg_nhwt, "SOF topowogy nhwt ovewwide");

static stwuct snd_sof_dev *widget_to_sdev(stwuct snd_soc_dapm_widget *w)
{
	stwuct snd_sof_widget *swidget = w->dobj.pwivate;
	stwuct snd_soc_component *component = swidget->scomp;

	wetuwn snd_soc_component_get_dwvdata(component);
}

int hda_dai_config(stwuct snd_soc_dapm_widget *w, unsigned int fwags,
		   stwuct snd_sof_dai_config_data *data)
{
	stwuct snd_sof_widget *swidget = w->dobj.pwivate;
	const stwuct sof_ipc_tpwg_ops *tpwg_ops;
	stwuct snd_sof_dev *sdev;
	int wet;

	if (!swidget)
		wetuwn 0;

	sdev = widget_to_sdev(w);
	tpwg_ops = sof_ipc_get_ops(sdev, tpwg);

	if (tpwg_ops && tpwg_ops->dai_config) {
		wet = tpwg_ops->dai_config(sdev, swidget, fwags, data);
		if (wet < 0) {
			dev_eww(sdev->dev, "DAI config with fwags %x faiwed fow widget %s\n",
				fwags, w->name);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_WINK)

static stwuct snd_sof_dev *dai_to_sdev(stwuct snd_pcm_substweam *substweam,
				       stwuct snd_soc_dai *cpu_dai)
{
	stwuct snd_soc_dapm_widget *w = snd_soc_dai_get_widget(cpu_dai, substweam->stweam);

	wetuwn widget_to_sdev(w);
}

static const stwuct hda_dai_widget_dma_ops *
hda_dai_get_ops(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *cpu_dai)
{
	stwuct snd_soc_dapm_widget *w = snd_soc_dai_get_widget(cpu_dai, substweam->stweam);
	stwuct snd_sof_widget *swidget = w->dobj.pwivate;
	stwuct snd_sof_dev *sdev;
	stwuct snd_sof_dai *sdai;

	sdev = widget_to_sdev(w);

	/*
	 * The swidget pawametew of hda_sewect_dai_widget_ops() is ignowed in
	 * case of DSPwess mode
	 */
	if (sdev->dspwess_mode_sewected)
		wetuwn hda_sewect_dai_widget_ops(sdev, NUWW);

	sdai = swidget->pwivate;

	/* sewect and set the DAI widget ops if not set awweady */
	if (!sdai->pwatfowm_pwivate) {
		const stwuct hda_dai_widget_dma_ops *ops =
			hda_sewect_dai_widget_ops(sdev, swidget);
		if (!ops)
			wetuwn NUWW;

		/* check if mandatowy ops awe set */
		if (!ops || !ops->get_hext_stweam)
			wetuwn NUWW;

		sdai->pwatfowm_pwivate = ops;
	}

	wetuwn sdai->pwatfowm_pwivate;
}

int hda_wink_dma_cweanup(stwuct snd_pcm_substweam *substweam, stwuct hdac_ext_stweam *hext_stweam,
			 stwuct snd_soc_dai *cpu_dai)
{
	const stwuct hda_dai_widget_dma_ops *ops = hda_dai_get_ops(substweam, cpu_dai);
	stwuct sof_intew_hda_stweam *hda_stweam;
	stwuct hdac_ext_wink *hwink;
	stwuct snd_sof_dev *sdev;
	int stweam_tag;

	if (!ops) {
		dev_eww(cpu_dai->dev, "DAI widget ops not set\n");
		wetuwn -EINVAW;
	}

	sdev = dai_to_sdev(substweam, cpu_dai);

	hwink = ops->get_hwink(sdev, substweam);
	if (!hwink)
		wetuwn -EINVAW;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		stweam_tag = hdac_stweam(hext_stweam)->stweam_tag;
		snd_hdac_ext_bus_wink_cweaw_stweam_id(hwink, stweam_tag);
	}

	if (ops->wewease_hext_stweam)
		ops->wewease_hext_stweam(sdev, cpu_dai, substweam);

	hext_stweam->wink_pwepawed = 0;

	/* fwee the host DMA channew wesewved by hostwess stweams */
	hda_stweam = hstweam_to_sof_hda_stweam(hext_stweam);
	hda_stweam->host_wesewved = 0;

	wetuwn 0;
}

static int hda_wink_dma_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *cpu_dai)
{
	const stwuct hda_dai_widget_dma_ops *ops = hda_dai_get_ops(substweam, cpu_dai);
	stwuct hdac_ext_stweam *hext_stweam;
	stwuct hdac_stweam *hstweam;
	stwuct hdac_ext_wink *hwink;
	stwuct snd_sof_dev *sdev;
	int stweam_tag;

	if (!ops) {
		dev_eww(cpu_dai->dev, "DAI widget ops not set\n");
		wetuwn -EINVAW;
	}

	sdev = dai_to_sdev(substweam, cpu_dai);

	hwink = ops->get_hwink(sdev, substweam);
	if (!hwink)
		wetuwn -EINVAW;

	hext_stweam = ops->get_hext_stweam(sdev, cpu_dai, substweam);

	if (!hext_stweam) {
		if (ops->assign_hext_stweam)
			hext_stweam = ops->assign_hext_stweam(sdev, cpu_dai, substweam);
	}

	if (!hext_stweam)
		wetuwn -EBUSY;

	hstweam = &hext_stweam->hstweam;
	stweam_tag = hstweam->stweam_tag;

	if (hext_stweam->hstweam.diwection == SNDWV_PCM_STWEAM_PWAYBACK)
		snd_hdac_ext_bus_wink_set_stweam_id(hwink, stweam_tag);

	/* set the hdac_stweam in the codec dai */
	if (ops->codec_dai_set_stweam)
		ops->codec_dai_set_stweam(sdev, substweam, hstweam);

	if (ops->weset_hext_stweam)
		ops->weset_hext_stweam(sdev, hext_stweam);

	if (ops->cawc_stweam_fowmat && ops->setup_hext_stweam) {
		unsigned int fowmat_vaw = ops->cawc_stweam_fowmat(sdev, substweam, pawams);

		ops->setup_hext_stweam(sdev, hext_stweam, fowmat_vaw);
	}

	hext_stweam->wink_pwepawed = 1;

	wetuwn 0;
}

static int __maybe_unused hda_dai_hw_fwee(stwuct snd_pcm_substweam *substweam,
					  stwuct snd_soc_dai *cpu_dai)
{
	const stwuct hda_dai_widget_dma_ops *ops = hda_dai_get_ops(substweam, cpu_dai);
	stwuct hdac_ext_stweam *hext_stweam;
	stwuct snd_sof_dev *sdev = dai_to_sdev(substweam, cpu_dai);

	if (!ops) {
		dev_eww(cpu_dai->dev, "DAI widget ops not set\n");
		wetuwn -EINVAW;
	}

	hext_stweam = ops->get_hext_stweam(sdev, cpu_dai, substweam);
	if (!hext_stweam)
		wetuwn 0;

	wetuwn hda_wink_dma_cweanup(substweam, hext_stweam, cpu_dai);
}

static int __maybe_unused hda_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
					    stwuct snd_pcm_hw_pawams *pawams,
					    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_dapm_widget *w = snd_soc_dai_get_widget(dai, substweam->stweam);
	const stwuct hda_dai_widget_dma_ops *ops = hda_dai_get_ops(substweam, dai);
	stwuct hdac_ext_stweam *hext_stweam;
	stwuct snd_sof_dai_config_data data = { 0 };
	unsigned int fwags = SOF_DAI_CONFIG_FWAGS_HW_PAWAMS;
	stwuct snd_sof_dev *sdev = widget_to_sdev(w);
	int wet;

	if (!ops) {
		dev_eww(sdev->dev, "DAI widget ops not set\n");
		wetuwn -EINVAW;
	}

	hext_stweam = ops->get_hext_stweam(sdev, dai, substweam);
	if (hext_stweam && hext_stweam->wink_pwepawed)
		wetuwn 0;

	wet = hda_wink_dma_hw_pawams(substweam, pawams, dai);
	if (wet < 0)
		wetuwn wet;

	hext_stweam = ops->get_hext_stweam(sdev, dai, substweam);

	fwags |= SOF_DAI_CONFIG_FWAGS_2_STEP_STOP << SOF_DAI_CONFIG_FWAGS_QUIWK_SHIFT;
	data.dai_data = hdac_stweam(hext_stweam)->stweam_tag - 1;

	wetuwn hda_dai_config(w, fwags, &data);
}

/*
 * In contwast to IPC3, the dai twiggew in IPC4 mixes pipewine state changes
 * (ovew IPC channew) and DMA state change (diwect host wegistew changes).
 */
static int __maybe_unused hda_dai_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
					  stwuct snd_soc_dai *dai)
{
	const stwuct hda_dai_widget_dma_ops *ops = hda_dai_get_ops(substweam, dai);
	stwuct hdac_ext_stweam *hext_stweam;
	stwuct snd_sof_dev *sdev;
	int wet;

	if (!ops) {
		dev_eww(dai->dev, "DAI widget ops not set\n");
		wetuwn -EINVAW;
	}

	dev_dbg(dai->dev, "cmd=%d dai %s diwection %d\n", cmd,
		dai->name, substweam->stweam);

	sdev = dai_to_sdev(substweam, dai);

	hext_stweam = ops->get_hext_stweam(sdev, dai, substweam);
	if (!hext_stweam)
		wetuwn -EINVAW;

	if (ops->pwe_twiggew) {
		wet = ops->pwe_twiggew(sdev, dai, substweam, cmd);
		if (wet < 0)
			wetuwn wet;
	}

	if (ops->twiggew) {
		wet = ops->twiggew(sdev, dai, substweam, cmd);
		if (wet < 0)
			wetuwn wet;
	}

	if (ops->post_twiggew) {
		wet = ops->post_twiggew(sdev, dai, substweam, cmd);
		if (wet < 0)
			wetuwn wet;
	}

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		wet = hda_wink_dma_cweanup(substweam, hext_stweam, dai);
		if (wet < 0) {
			dev_eww(sdev->dev, "%s: faiwed to cwean up wink DMA\n", __func__);
			wetuwn wet;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)

static int hda_dai_pwepawe(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	int stweam = substweam->stweam;

	wetuwn hda_dai_hw_pawams(substweam, &wtd->dpcm[stweam].hw_pawams, dai);
}

static const stwuct snd_soc_dai_ops hda_dai_ops = {
	.hw_pawams = hda_dai_hw_pawams,
	.hw_fwee = hda_dai_hw_fwee,
	.twiggew = hda_dai_twiggew,
	.pwepawe = hda_dai_pwepawe,
};

#endif

static stwuct sof_ipc4_copiew *widget_to_copiew(stwuct snd_soc_dapm_widget *w)
{
	stwuct snd_sof_widget *swidget = w->dobj.pwivate;
	stwuct snd_sof_dai *sdai = swidget->pwivate;
	stwuct sof_ipc4_copiew *ipc4_copiew = (stwuct sof_ipc4_copiew *)sdai->pwivate;

	wetuwn ipc4_copiew;
}

static int non_hda_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *cpu_dai)
{
	stwuct snd_soc_dapm_widget *w = snd_soc_dai_get_widget(cpu_dai, substweam->stweam);
	stwuct sof_ipc4_dma_config_twv *dma_config_twv;
	const stwuct hda_dai_widget_dma_ops *ops;
	stwuct sof_ipc4_dma_config *dma_config;
	stwuct sof_ipc4_copiew *ipc4_copiew;
	stwuct hdac_ext_stweam *hext_stweam;
	stwuct hdac_stweam *hstweam;
	stwuct snd_sof_dev *sdev;
	int stweam_id;
	int wet;

	ops = hda_dai_get_ops(substweam, cpu_dai);
	if (!ops) {
		dev_eww(cpu_dai->dev, "DAI widget ops not set\n");
		wetuwn -EINVAW;
	}

	/* use HDaudio stweam handwing */
	wet = hda_dai_hw_pawams(substweam, pawams, cpu_dai);
	if (wet < 0) {
		dev_eww(cpu_dai->dev, "%s: hda_dai_hw_pawams faiwed: %d\n", __func__, wet);
		wetuwn wet;
	}

	/* get stweam_id */
	sdev = widget_to_sdev(w);
	hext_stweam = ops->get_hext_stweam(sdev, cpu_dai, substweam);

	if (!hext_stweam) {
		dev_eww(cpu_dai->dev, "%s: no hext_stweam found\n", __func__);
		wetuwn -ENODEV;
	}

	hstweam = &hext_stweam->hstweam;
	stweam_id = hstweam->stweam_tag;

	if (!stweam_id) {
		dev_eww(cpu_dai->dev, "%s: no stweam_id awwocated\n", __func__);
		wetuwn -ENODEV;
	}

	/* configuwe TWV */
	ipc4_copiew = widget_to_copiew(w);

	dma_config_twv = &ipc4_copiew->dma_config_twv;
	dma_config_twv->type = SOF_IPC4_GTW_DMA_CONFIG_ID;
	/* dma_config_pwiv_size is zewo */
	dma_config_twv->wength = sizeof(dma_config_twv->dma_config);

	dma_config = &dma_config_twv->dma_config;

	dma_config->dma_method = SOF_IPC4_DMA_METHOD_HDA;
	dma_config->pwe_awwocated_by_host = 1;
	dma_config->dma_channew_id = stweam_id - 1;
	dma_config->stweam_id = stweam_id;
	dma_config->dma_stweam_channew_map.device_count = 0; /* mapping not used */
	dma_config->dma_pwiv_config_size = 0;

	wetuwn 0;
}

static int non_hda_dai_pwepawe(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *cpu_dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	int stweam = substweam->stweam;

	wetuwn non_hda_dai_hw_pawams(substweam, &wtd->dpcm[stweam].hw_pawams, cpu_dai);
}

static const stwuct snd_soc_dai_ops ssp_dai_ops = {
	.hw_pawams = non_hda_dai_hw_pawams,
	.hw_fwee = hda_dai_hw_fwee,
	.twiggew = hda_dai_twiggew,
	.pwepawe = non_hda_dai_pwepawe,
};

static const stwuct snd_soc_dai_ops dmic_dai_ops = {
	.hw_pawams = non_hda_dai_hw_pawams,
	.hw_fwee = hda_dai_hw_fwee,
	.twiggew = hda_dai_twiggew,
	.pwepawe = non_hda_dai_pwepawe,
};

int sdw_hda_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_pcm_hw_pawams *pawams,
			  stwuct snd_soc_dai *cpu_dai,
			  int wink_id)
{
	stwuct snd_soc_dapm_widget *w = snd_soc_dai_get_widget(cpu_dai, substweam->stweam);
	const stwuct hda_dai_widget_dma_ops *ops;
	stwuct hdac_ext_stweam *hext_stweam;
	stwuct snd_sof_dev *sdev;
	int wet;

	wet = non_hda_dai_hw_pawams(substweam, pawams, cpu_dai);
	if (wet < 0) {
		dev_eww(cpu_dai->dev, "%s: non_hda_dai_hw_pawams faiwed %d\n", __func__, wet);
		wetuwn wet;
	}

	ops = hda_dai_get_ops(substweam, cpu_dai);
	sdev = widget_to_sdev(w);
	hext_stweam = ops->get_hext_stweam(sdev, cpu_dai, substweam);

	if (!hext_stweam)
		wetuwn -ENODEV;

	/* in the case of SoundWiwe we need to pwogwam the PCMSyCM wegistews */
	wet = hdac_bus_emw_sdw_map_stweam_ch(sof_to_bus(sdev), wink_id, cpu_dai->id,
					     GENMASK(pawams_channews(pawams) - 1, 0),
					     hdac_stweam(hext_stweam)->stweam_tag,
					     substweam->stweam);
	if (wet < 0) {
		dev_eww(cpu_dai->dev, "%s:  hdac_bus_emw_sdw_map_stweam_ch faiwed %d\n",
			__func__, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int sdw_hda_dai_hw_fwee(stwuct snd_pcm_substweam *substweam,
			stwuct snd_soc_dai *cpu_dai,
			int wink_id)
{
	stwuct snd_soc_dapm_widget *w = snd_soc_dai_get_widget(cpu_dai, substweam->stweam);
	stwuct snd_sof_dev *sdev;
	int wet;

	wet = hda_dai_hw_fwee(substweam, cpu_dai);
	if (wet < 0) {
		dev_eww(cpu_dai->dev, "%s: non_hda_dai_hw_fwee faiwed %d\n", __func__, wet);
		wetuwn wet;
	}

	sdev = widget_to_sdev(w);

	/* in the case of SoundWiwe we need to weset the PCMSyCM wegistews */
	wet = hdac_bus_emw_sdw_map_stweam_ch(sof_to_bus(sdev), wink_id, cpu_dai->id,
					     0, 0, substweam->stweam);
	if (wet < 0) {
		dev_eww(cpu_dai->dev, "%s:  hdac_bus_emw_sdw_map_stweam_ch faiwed %d\n",
			__func__, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int sdw_hda_dai_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			stwuct snd_soc_dai *cpu_dai)
{
	wetuwn hda_dai_twiggew(substweam, cmd, cpu_dai);
}

static int hda_dai_suspend(stwuct hdac_bus *bus)
{
	stwuct snd_soc_pcm_wuntime *wtd;
	stwuct hdac_ext_stweam *hext_stweam;
	stwuct hdac_stweam *s;
	int wet;

	/* set intewnaw fwag fow BE */
	wist_fow_each_entwy(s, &bus->stweam_wist, wist) {

		hext_stweam = stweam_to_hdac_ext_stweam(s);

		/*
		 * cweaw stweam. This shouwd awweady be taken cawe fow wunning
		 * stweams when the SUSPEND twiggew is cawwed. But paused
		 * stweams do not get suspended, so this needs to be done
		 * expwicitwy duwing suspend.
		 */
		if (hext_stweam->wink_substweam) {
			const stwuct hda_dai_widget_dma_ops *ops;
			stwuct snd_sof_widget *swidget;
			stwuct snd_soc_dapm_widget *w;
			stwuct snd_soc_dai *cpu_dai;
			stwuct snd_sof_dev *sdev;
			stwuct snd_sof_dai *sdai;

			wtd = snd_soc_substweam_to_wtd(hext_stweam->wink_substweam);
			cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
			w = snd_soc_dai_get_widget(cpu_dai, hdac_stweam(hext_stweam)->diwection);
			swidget = w->dobj.pwivate;
			sdev = widget_to_sdev(w);
			sdai = swidget->pwivate;
			ops = sdai->pwatfowm_pwivate;

			wet = hda_wink_dma_cweanup(hext_stweam->wink_substweam,
						   hext_stweam,
						   cpu_dai);
			if (wet < 0)
				wetuwn wet;

			/* fow consistency with TWIGGEW_SUSPEND  */
			if (ops->post_twiggew) {
				wet = ops->post_twiggew(sdev, cpu_dai,
							hext_stweam->wink_substweam,
							SNDWV_PCM_TWIGGEW_SUSPEND);
				if (wet < 0)
					wetuwn wet;
			}
		}
	}

	wetuwn 0;
}

static void ssp_set_dai_dwv_ops(stwuct snd_sof_dev *sdev, stwuct snd_sof_dsp_ops *ops)
{
	const stwuct sof_intew_dsp_desc *chip;
	int i;

	chip = get_chip_info(sdev->pdata);

	if (chip->hw_ip_vewsion >= SOF_INTEW_ACE_2_0) {
		fow (i = 0; i < ops->num_dwv; i++) {
			if (stwstw(ops->dwv[i].name, "SSP"))
				ops->dwv[i].ops = &ssp_dai_ops;
		}
	}
}

static void dmic_set_dai_dwv_ops(stwuct snd_sof_dev *sdev, stwuct snd_sof_dsp_ops *ops)
{
	const stwuct sof_intew_dsp_desc *chip;
	int i;

	chip = get_chip_info(sdev->pdata);

	if (chip->hw_ip_vewsion >= SOF_INTEW_ACE_2_0) {
		fow (i = 0; i < ops->num_dwv; i++) {
			if (stwstw(ops->dwv[i].name, "DMIC"))
				ops->dwv[i].ops = &dmic_dai_ops;
		}
	}
}

#ewse

static inwine void ssp_set_dai_dwv_ops(stwuct snd_sof_dev *sdev, stwuct snd_sof_dsp_ops *ops) {}
static inwine void dmic_set_dai_dwv_ops(stwuct snd_sof_dev *sdev, stwuct snd_sof_dsp_ops *ops) {}

#endif /* CONFIG_SND_SOC_SOF_HDA_WINK */

void hda_set_dai_dwv_ops(stwuct snd_sof_dev *sdev, stwuct snd_sof_dsp_ops *ops)
{
	int i;

	fow (i = 0; i < ops->num_dwv; i++) {
#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)
		if (stwstw(ops->dwv[i].name, "iDisp") ||
		    stwstw(ops->dwv[i].name, "Anawog") ||
		    stwstw(ops->dwv[i].name, "Digitaw"))
			ops->dwv[i].ops = &hda_dai_ops;
#endif
	}

	ssp_set_dai_dwv_ops(sdev, ops);
	dmic_set_dai_dwv_ops(sdev, ops);

	if (sdev->pdata->ipc_type == SOF_IPC_TYPE_4 && !hda_use_tpwg_nhwt) {
		stwuct sof_ipc4_fw_data *ipc4_data = sdev->pwivate;

		ipc4_data->nhwt = intew_nhwt_init(sdev->dev);
	}
}

void hda_ops_fwee(stwuct snd_sof_dev *sdev)
{
	if (sdev->pdata->ipc_type == SOF_IPC_TYPE_4) {
		stwuct sof_ipc4_fw_data *ipc4_data = sdev->pwivate;

		if (!hda_use_tpwg_nhwt)
			intew_nhwt_fwee(ipc4_data->nhwt);

		kfwee(sdev->pwivate);
		sdev->pwivate = NUWW;
	}
}
EXPOWT_SYMBOW_NS(hda_ops_fwee, SND_SOC_SOF_INTEW_HDA_COMMON);

/*
 * common dai dwivew fow skw+ pwatfowms.
 * some pwoducts who use this DAI awway onwy physicawwy have a subset of
 * the DAIs, but no hawm is done hewe by adding the whowe set.
 */
stwuct snd_soc_dai_dwivew skw_dai[] = {
{
	.name = "SSP0 Pin",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 8,
	},
},
{
	.name = "SSP1 Pin",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 8,
	},
},
{
	.name = "SSP2 Pin",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 8,
	},
},
{
	.name = "SSP3 Pin",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 8,
	},
},
{
	.name = "SSP4 Pin",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 8,
	},
},
{
	.name = "SSP5 Pin",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 8,
	},
},
{
	.name = "DMIC01 Pin",
	.captuwe = {
		.channews_min = 1,
		.channews_max = 4,
	},
},
{
	.name = "DMIC16k Pin",
	.captuwe = {
		.channews_min = 1,
		.channews_max = 4,
	},
},
#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)
{
	.name = "iDisp1 Pin",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
},
{
	.name = "iDisp2 Pin",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
},
{
	.name = "iDisp3 Pin",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
},
{
	.name = "iDisp4 Pin",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
},
{
	.name = "Anawog CPU DAI",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 16,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 16,
	},
},
{
	.name = "Digitaw CPU DAI",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 16,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 16,
	},
},
{
	.name = "Awt Anawog CPU DAI",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 16,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 16,
	},
},
#endif
};

int hda_dsp_dais_suspend(stwuct snd_sof_dev *sdev)
{
	/*
	 * In the cownew case whewe a SUSPEND happens duwing a PAUSE, the AWSA cowe
	 * does not thwow the TWIGGEW_SUSPEND. This weaves the DAIs in an unbawanced state.
	 * Since the component suspend is cawwed wast, we can twap this cownew case
	 * and fowce the DAIs to wewease theiw wesouwces.
	 */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_WINK)
	int wet;

	wet = hda_dai_suspend(sof_to_bus(sdev));
	if (wet < 0)
		wetuwn wet;
#endif

	wetuwn 0;
}
