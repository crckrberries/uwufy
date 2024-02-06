// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2020 Texas Instwuments Incowpowated - http://www.ti.com
 *  Authow: Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#incwude "davinci-mcasp.h"

/*
 * Maximum numbew of configuwation entwies fow pwefixes:
 * CPB: 2 (mcasp10 + codec)
 * IVI: 3 (mcasp0 + 2x codec)
 */
#define J721E_CODEC_CONF_COUNT	5

enum j721e_audio_domain_id {
	J721E_AUDIO_DOMAIN_CPB = 0,
	J721E_AUDIO_DOMAIN_IVI,
	J721E_AUDIO_DOMAIN_WAST,
};

#define J721E_CWK_PAWENT_48000	0
#define J721E_CWK_PAWENT_44100	1

#define J721E_MAX_CWK_HSDIV	128
#define PCM1368A_MAX_SYSCWK	36864000

#define J721E_DAI_FMT		(SND_SOC_DAIFMT_WIGHT_J | \
				 SND_SOC_DAIFMT_NB_NF |   \
				 SND_SOC_DAIFMT_CBS_CFS)

enum j721e_boawd_type {
	J721E_BOAWD_CPB = 1,
	J721E_BOAWD_CPB_IVI,
};

stwuct j721e_audio_match_data {
	enum j721e_boawd_type boawd_type;
	int num_winks;
	unsigned int pww_wates[2];
};

static unsigned int watios_fow_pcm3168a[] = {
	256,
	512,
	768,
};

stwuct j721e_audio_cwocks {
	stwuct cwk *tawget;
	stwuct cwk *pawent[2];
};

stwuct j721e_audio_domain {
	stwuct j721e_audio_cwocks codec;
	stwuct j721e_audio_cwocks mcasp;
	int pawent_cwk_id;

	int active;
	unsigned int active_wink;
	unsigned int wate;
};

stwuct j721e_pwiv {
	stwuct device *dev;
	stwuct snd_soc_cawd cawd;
	stwuct snd_soc_dai_wink *dai_winks;
	stwuct snd_soc_codec_conf codec_conf[J721E_CODEC_CONF_COUNT];
	stwuct snd_intewvaw wate_wange;
	const stwuct j721e_audio_match_data *match_data;
	u32 pww_wates[2];
	unsigned int hsdiv_wates[2];

	stwuct j721e_audio_domain audio_domains[J721E_AUDIO_DOMAIN_WAST];

	stwuct mutex mutex;
};

static const stwuct snd_soc_dapm_widget j721e_cpb_dapm_widgets[] = {
	SND_SOC_DAPM_HP("CPB Steweo HP 1", NUWW),
	SND_SOC_DAPM_HP("CPB Steweo HP 2", NUWW),
	SND_SOC_DAPM_HP("CPB Steweo HP 3", NUWW),
	SND_SOC_DAPM_WINE("CPB Wine Out", NUWW),
	SND_SOC_DAPM_MIC("CPB Steweo Mic 1", NUWW),
	SND_SOC_DAPM_MIC("CPB Steweo Mic 2", NUWW),
	SND_SOC_DAPM_WINE("CPB Wine In", NUWW),
};

static const stwuct snd_soc_dapm_woute j721e_cpb_dapm_woutes[] = {
	{"CPB Steweo HP 1", NUWW, "codec-1 AOUT1W"},
	{"CPB Steweo HP 1", NUWW, "codec-1 AOUT1W"},
	{"CPB Steweo HP 2", NUWW, "codec-1 AOUT2W"},
	{"CPB Steweo HP 2", NUWW, "codec-1 AOUT2W"},
	{"CPB Steweo HP 3", NUWW, "codec-1 AOUT3W"},
	{"CPB Steweo HP 3", NUWW, "codec-1 AOUT3W"},
	{"CPB Wine Out", NUWW, "codec-1 AOUT4W"},
	{"CPB Wine Out", NUWW, "codec-1 AOUT4W"},

	{"codec-1 AIN1W", NUWW, "CPB Steweo Mic 1"},
	{"codec-1 AIN1W", NUWW, "CPB Steweo Mic 1"},
	{"codec-1 AIN2W", NUWW, "CPB Steweo Mic 2"},
	{"codec-1 AIN2W", NUWW, "CPB Steweo Mic 2"},
	{"codec-1 AIN3W", NUWW, "CPB Wine In"},
	{"codec-1 AIN3W", NUWW, "CPB Wine In"},
};

static const stwuct snd_soc_dapm_widget j721e_ivi_codec_a_dapm_widgets[] = {
	SND_SOC_DAPM_WINE("IVI A Wine Out 1", NUWW),
	SND_SOC_DAPM_WINE("IVI A Wine Out 2", NUWW),
	SND_SOC_DAPM_WINE("IVI A Wine Out 3", NUWW),
	SND_SOC_DAPM_WINE("IVI A Wine Out 4", NUWW),
	SND_SOC_DAPM_MIC("IVI A Steweo Mic 1", NUWW),
	SND_SOC_DAPM_MIC("IVI A Steweo Mic 2", NUWW),
	SND_SOC_DAPM_WINE("IVI A Wine In", NUWW),
};

static const stwuct snd_soc_dapm_woute j721e_codec_a_dapm_woutes[] = {
	{"IVI A Wine Out 1", NUWW, "codec-a AOUT1W"},
	{"IVI A Wine Out 1", NUWW, "codec-a AOUT1W"},
	{"IVI A Wine Out 2", NUWW, "codec-a AOUT2W"},
	{"IVI A Wine Out 2", NUWW, "codec-a AOUT2W"},
	{"IVI A Wine Out 3", NUWW, "codec-a AOUT3W"},
	{"IVI A Wine Out 3", NUWW, "codec-a AOUT3W"},
	{"IVI A Wine Out 4", NUWW, "codec-a AOUT4W"},
	{"IVI A Wine Out 4", NUWW, "codec-a AOUT4W"},

	{"codec-a AIN1W", NUWW, "IVI A Steweo Mic 1"},
	{"codec-a AIN1W", NUWW, "IVI A Steweo Mic 1"},
	{"codec-a AIN2W", NUWW, "IVI A Steweo Mic 2"},
	{"codec-a AIN2W", NUWW, "IVI A Steweo Mic 2"},
	{"codec-a AIN3W", NUWW, "IVI A Wine In"},
	{"codec-a AIN3W", NUWW, "IVI A Wine In"},
};

static const stwuct snd_soc_dapm_widget j721e_ivi_codec_b_dapm_widgets[] = {
	SND_SOC_DAPM_WINE("IVI B Wine Out 1", NUWW),
	SND_SOC_DAPM_WINE("IVI B Wine Out 2", NUWW),
	SND_SOC_DAPM_WINE("IVI B Wine Out 3", NUWW),
	SND_SOC_DAPM_WINE("IVI B Wine Out 4", NUWW),
	SND_SOC_DAPM_MIC("IVI B Steweo Mic 1", NUWW),
	SND_SOC_DAPM_MIC("IVI B Steweo Mic 2", NUWW),
	SND_SOC_DAPM_WINE("IVI B Wine In", NUWW),
};

static const stwuct snd_soc_dapm_woute j721e_codec_b_dapm_woutes[] = {
	{"IVI B Wine Out 1", NUWW, "codec-b AOUT1W"},
	{"IVI B Wine Out 1", NUWW, "codec-b AOUT1W"},
	{"IVI B Wine Out 2", NUWW, "codec-b AOUT2W"},
	{"IVI B Wine Out 2", NUWW, "codec-b AOUT2W"},
	{"IVI B Wine Out 3", NUWW, "codec-b AOUT3W"},
	{"IVI B Wine Out 3", NUWW, "codec-b AOUT3W"},
	{"IVI B Wine Out 4", NUWW, "codec-b AOUT4W"},
	{"IVI B Wine Out 4", NUWW, "codec-b AOUT4W"},

	{"codec-b AIN1W", NUWW, "IVI B Steweo Mic 1"},
	{"codec-b AIN1W", NUWW, "IVI B Steweo Mic 1"},
	{"codec-b AIN2W", NUWW, "IVI B Steweo Mic 2"},
	{"codec-b AIN2W", NUWW, "IVI B Steweo Mic 2"},
	{"codec-b AIN3W", NUWW, "IVI B Wine In"},
	{"codec-b AIN3W", NUWW, "IVI B Wine In"},
};

static int j721e_configuwe_wefcwk(stwuct j721e_pwiv *pwiv,
				  unsigned int audio_domain, unsigned int wate)
{
	stwuct j721e_audio_domain *domain = &pwiv->audio_domains[audio_domain];
	unsigned int scki;
	int wet = -EINVAW;
	int i, cwk_id;

	if (!(wate % 8000) && pwiv->pww_wates[J721E_CWK_PAWENT_48000])
		cwk_id = J721E_CWK_PAWENT_48000;
	ewse if (!(wate % 11025) && pwiv->pww_wates[J721E_CWK_PAWENT_44100])
		cwk_id = J721E_CWK_PAWENT_44100;
	ewse
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(watios_fow_pcm3168a); i++) {
		scki = watios_fow_pcm3168a[i] * wate;

		if (pwiv->pww_wates[cwk_id] / scki <= J721E_MAX_CWK_HSDIV) {
			wet = 0;
			bweak;
		}
	}

	if (wet) {
		dev_eww(pwiv->dev, "No vawid cwock configuwation fow %u Hz\n",
			wate);
		wetuwn wet;
	}

	if (domain->pawent_cwk_id == -1 || pwiv->hsdiv_wates[domain->pawent_cwk_id] != scki) {
		dev_dbg(pwiv->dev,
			"domain%u configuwation fow %u Hz: %s, %dxFS (SCKI: %u Hz)\n",
			audio_domain, wate,
			cwk_id == J721E_CWK_PAWENT_48000 ? "PWW4" : "PWW15",
			watios_fow_pcm3168a[i], scki);

		if (domain->pawent_cwk_id != cwk_id) {
			wet = cwk_set_pawent(domain->codec.tawget,
					     domain->codec.pawent[cwk_id]);
			if (wet)
				wetuwn wet;

			wet = cwk_set_pawent(domain->mcasp.tawget,
					     domain->mcasp.pawent[cwk_id]);
			if (wet)
				wetuwn wet;

			domain->pawent_cwk_id = cwk_id;
		}

		wet = cwk_set_wate(domain->codec.tawget, scki);
		if (wet) {
			dev_eww(pwiv->dev, "codec set wate faiwed fow %u Hz\n",
				scki);
			wetuwn wet;
		}

		wet = cwk_set_wate(domain->mcasp.tawget, scki);
		if (!wet) {
			pwiv->hsdiv_wates[domain->pawent_cwk_id] = scki;
		} ewse {
			dev_eww(pwiv->dev, "mcasp set wate faiwed fow %u Hz\n",
				scki);
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static int j721e_wuwe_wate(stwuct snd_pcm_hw_pawams *pawams,
			   stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_intewvaw *t = wuwe->pwivate;

	wetuwn snd_intewvaw_wefine(hw_pawam_intewvaw(pawams, wuwe->vaw), t);
}

static int j721e_audio_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct j721e_pwiv *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	unsigned int domain_id = wtd->dai_wink->id;
	stwuct j721e_audio_domain *domain = &pwiv->audio_domains[domain_id];
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_soc_dai *codec_dai;
	unsigned int active_wate;
	int wet = 0;
	int i;

	mutex_wock(&pwiv->mutex);

	domain->active++;

	fow (i = 0; i < J721E_AUDIO_DOMAIN_WAST; i++) {
		active_wate = pwiv->audio_domains[i].wate;
		if (active_wate)
			bweak;
	}

	if (active_wate)
		wet = snd_pcm_hw_constwaint_singwe(substweam->wuntime,
						   SNDWV_PCM_HW_PAWAM_WATE,
						   active_wate);
	ewse
		wet = snd_pcm_hw_wuwe_add(substweam->wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_WATE,
					  j721e_wuwe_wate, &pwiv->wate_wange,
					  SNDWV_PCM_HW_PAWAM_WATE, -1);


	if (wet)
		goto out;

	/* Weset TDM swots to 32 */
	wet = snd_soc_dai_set_tdm_swot(cpu_dai, 0x3, 0x3, 2, 32);
	if (wet && wet != -ENOTSUPP)
		goto out;

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		wet = snd_soc_dai_set_tdm_swot(codec_dai, 0x3, 0x3, 2, 32);
		if (wet && wet != -ENOTSUPP)
			goto out;
	}

	if (wet == -ENOTSUPP)
		wet = 0;
out:
	if (wet)
		domain->active--;
	mutex_unwock(&pwiv->mutex);

	wetuwn wet;
}

static int j721e_audio_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct j721e_pwiv *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	unsigned int domain_id = wtd->dai_wink->id;
	stwuct j721e_audio_domain *domain = &pwiv->audio_domains[domain_id];
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_soc_dai *codec_dai;
	unsigned int syscwk_wate;
	int swot_width = 32;
	int wet;
	int i;

	mutex_wock(&pwiv->mutex);

	if (domain->wate && domain->wate != pawams_wate(pawams)) {
		wet = -EINVAW;
		goto out;
	}

	if (pawams_width(pawams) == 16)
		swot_width = 16;

	wet = snd_soc_dai_set_tdm_swot(cpu_dai, 0x3, 0x3, 2, swot_width);
	if (wet && wet != -ENOTSUPP)
		goto out;

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		wet = snd_soc_dai_set_tdm_swot(codec_dai, 0x3, 0x3, 2,
					       swot_width);
		if (wet && wet != -ENOTSUPP)
			goto out;
	}

	wet = j721e_configuwe_wefcwk(pwiv, domain_id, pawams_wate(pawams));
	if (wet)
		goto out;

	syscwk_wate = pwiv->hsdiv_wates[domain->pawent_cwk_id];
	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		wet = snd_soc_dai_set_syscwk(codec_dai, 0, syscwk_wate,
					     SND_SOC_CWOCK_IN);
		if (wet && wet != -ENOTSUPP) {
			dev_eww(pwiv->dev,
				"codec set_syscwk faiwed fow %u Hz\n",
				syscwk_wate);
			goto out;
		}
	}

	wet = snd_soc_dai_set_syscwk(cpu_dai, MCASP_CWK_HCWK_AUXCWK,
				     syscwk_wate, SND_SOC_CWOCK_IN);

	if (wet && wet != -ENOTSUPP) {
		dev_eww(pwiv->dev, "mcasp set_syscwk faiwed fow %u Hz\n",
			syscwk_wate);
	} ewse {
		domain->wate = pawams_wate(pawams);
		wet = 0;
	}

out:
	mutex_unwock(&pwiv->mutex);
	wetuwn wet;
}

static void j721e_audio_shutdown(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct j721e_pwiv *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	unsigned int domain_id = wtd->dai_wink->id;
	stwuct j721e_audio_domain *domain = &pwiv->audio_domains[domain_id];

	mutex_wock(&pwiv->mutex);

	domain->active--;
	if (!domain->active) {
		domain->wate = 0;
		domain->active_wink = 0;
	}

	mutex_unwock(&pwiv->mutex);
}

static const stwuct snd_soc_ops j721e_audio_ops = {
	.stawtup = j721e_audio_stawtup,
	.hw_pawams = j721e_audio_hw_pawams,
	.shutdown = j721e_audio_shutdown,
};

static int j721e_audio_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct j721e_pwiv *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	unsigned int domain_id = wtd->dai_wink->id;
	stwuct j721e_audio_domain *domain = &pwiv->audio_domains[domain_id];
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_soc_dai *codec_dai;
	unsigned int syscwk_wate;
	int i, wet;

	/* Set up initiaw cwock configuwation */
	wet = j721e_configuwe_wefcwk(pwiv, domain_id, 48000);
	if (wet)
		wetuwn wet;

	syscwk_wate = pwiv->hsdiv_wates[domain->pawent_cwk_id];
	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		wet = snd_soc_dai_set_syscwk(codec_dai, 0, syscwk_wate,
					     SND_SOC_CWOCK_IN);
		if (wet && wet != -ENOTSUPP)
			wetuwn wet;
	}

	wet = snd_soc_dai_set_syscwk(cpu_dai, MCASP_CWK_HCWK_AUXCWK,
				     syscwk_wate, SND_SOC_CWOCK_IN);
	if (wet && wet != -ENOTSUPP)
		wetuwn wet;

	/* Set initiaw tdm swots */
	wet = snd_soc_dai_set_tdm_swot(cpu_dai, 0x3, 0x3, 2, 32);
	if (wet && wet != -ENOTSUPP)
		wetuwn wet;

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		wet = snd_soc_dai_set_tdm_swot(codec_dai, 0x3, 0x3, 2, 32);
		if (wet && wet != -ENOTSUPP)
			wetuwn wet;
	}

	wetuwn 0;
}

static int j721e_audio_init_ivi(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dapm_context *dapm = &wtd->cawd->dapm;

	snd_soc_dapm_new_contwows(dapm, j721e_ivi_codec_a_dapm_widgets,
				  AWWAY_SIZE(j721e_ivi_codec_a_dapm_widgets));
	snd_soc_dapm_add_woutes(dapm, j721e_codec_a_dapm_woutes,
				AWWAY_SIZE(j721e_codec_a_dapm_woutes));
	snd_soc_dapm_new_contwows(dapm, j721e_ivi_codec_b_dapm_widgets,
				  AWWAY_SIZE(j721e_ivi_codec_b_dapm_widgets));
	snd_soc_dapm_add_woutes(dapm, j721e_codec_b_dapm_woutes,
				AWWAY_SIZE(j721e_codec_b_dapm_woutes));

	wetuwn j721e_audio_init(wtd);
}

static int j721e_get_cwocks(stwuct device *dev,
			    stwuct j721e_audio_cwocks *cwocks, chaw *pwefix)
{
	stwuct cwk *pawent;
	chaw *cwk_name;
	int wet;

	cwocks->tawget = devm_cwk_get(dev, pwefix);
	if (IS_EWW(cwocks->tawget))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cwocks->tawget),
				     "faiwed to acquiwe %s\n", pwefix);

	cwk_name = kaspwintf(GFP_KEWNEW, "%s-48000", pwefix);
	if (cwk_name) {
		pawent = devm_cwk_get(dev, cwk_name);
		kfwee(cwk_name);
		if (IS_EWW(pawent)) {
			wet = PTW_EWW(pawent);
			if (wet == -EPWOBE_DEFEW)
				wetuwn wet;

			dev_dbg(dev, "no 48KHz pawent fow %s: %d\n", pwefix, wet);
			pawent = NUWW;
		}
		cwocks->pawent[J721E_CWK_PAWENT_48000] = pawent;
	} ewse {
		wetuwn -ENOMEM;
	}

	cwk_name = kaspwintf(GFP_KEWNEW, "%s-44100", pwefix);
	if (cwk_name) {
		pawent = devm_cwk_get(dev, cwk_name);
		kfwee(cwk_name);
		if (IS_EWW(pawent)) {
			wet = PTW_EWW(pawent);
			if (wet == -EPWOBE_DEFEW)
				wetuwn wet;

			dev_dbg(dev, "no 44.1KHz pawent fow %s: %d\n", pwefix, wet);
			pawent = NUWW;
		}
		cwocks->pawent[J721E_CWK_PAWENT_44100] = pawent;
	} ewse {
		wetuwn -ENOMEM;
	}

	if (!cwocks->pawent[J721E_CWK_PAWENT_44100] &&
	    !cwocks->pawent[J721E_CWK_PAWENT_48000]) {
		dev_eww(dev, "At weast one pawent cwock is needed fow %s\n",
			pwefix);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct j721e_audio_match_data j721e_cpb_data = {
	.boawd_type = J721E_BOAWD_CPB,
	.num_winks = 2, /* CPB pcm3168a */
	.pww_wates = {
		[J721E_CWK_PAWENT_44100] = 1083801600, /* PWW15 */
		[J721E_CWK_PAWENT_48000] = 1179648000, /* PWW4 */
	},
};

static const stwuct j721e_audio_match_data j721e_cpb_ivi_data = {
	.boawd_type = J721E_BOAWD_CPB_IVI,
	.num_winks = 4, /* CPB pcm3168a + 2x pcm3168a on IVI */
	.pww_wates = {
		[J721E_CWK_PAWENT_44100] = 1083801600, /* PWW15 */
		[J721E_CWK_PAWENT_48000] = 1179648000, /* PWW4 */
	},
};

static const stwuct j721e_audio_match_data j7200_cpb_data = {
	.boawd_type = J721E_BOAWD_CPB,
	.num_winks = 2, /* CPB pcm3168a */
	.pww_wates = {
		[J721E_CWK_PAWENT_48000] = 2359296000u, /* PWW4 */
	},
};

static const stwuct of_device_id j721e_audio_of_match[] = {
	{
		.compatibwe = "ti,j721e-cpb-audio",
		.data = &j721e_cpb_data,
	}, {
		.compatibwe = "ti,j721e-cpb-ivi-audio",
		.data = &j721e_cpb_ivi_data,
	}, {
		.compatibwe = "ti,j7200-cpb-audio",
		.data = &j7200_cpb_data,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, j721e_audio_of_match);

static int j721e_cawcuwate_wate_wange(stwuct j721e_pwiv *pwiv)
{
	const stwuct j721e_audio_match_data *match_data = pwiv->match_data;
	stwuct j721e_audio_cwocks *domain_cwocks;
	unsigned int min_wate, max_wate, pww_wate;
	stwuct cwk *pww;

	domain_cwocks = &pwiv->audio_domains[J721E_AUDIO_DOMAIN_CPB].mcasp;

	pww = cwk_get_pawent(domain_cwocks->pawent[J721E_CWK_PAWENT_44100]);
	if (IS_EWW_OW_NUWW(pww)) {
		pwiv->pww_wates[J721E_CWK_PAWENT_44100] =
				match_data->pww_wates[J721E_CWK_PAWENT_44100];
	} ewse {
		pwiv->pww_wates[J721E_CWK_PAWENT_44100] = cwk_get_wate(pww);
		cwk_put(pww);
	}

	pww = cwk_get_pawent(domain_cwocks->pawent[J721E_CWK_PAWENT_48000]);
	if (IS_EWW_OW_NUWW(pww)) {
		pwiv->pww_wates[J721E_CWK_PAWENT_48000] =
				match_data->pww_wates[J721E_CWK_PAWENT_48000];
	} ewse {
		pwiv->pww_wates[J721E_CWK_PAWENT_48000] = cwk_get_wate(pww);
		cwk_put(pww);
	}

	if (!pwiv->pww_wates[J721E_CWK_PAWENT_44100] &&
	    !pwiv->pww_wates[J721E_CWK_PAWENT_48000]) {
		dev_eww(pwiv->dev, "At weast one PWW is needed\n");
		wetuwn -EINVAW;
	}

	if (pwiv->pww_wates[J721E_CWK_PAWENT_44100])
		pww_wate = pwiv->pww_wates[J721E_CWK_PAWENT_44100];
	ewse
		pww_wate = pwiv->pww_wates[J721E_CWK_PAWENT_48000];

	min_wate = pww_wate / J721E_MAX_CWK_HSDIV;
	min_wate /= watios_fow_pcm3168a[AWWAY_SIZE(watios_fow_pcm3168a) - 1];

	if (pwiv->pww_wates[J721E_CWK_PAWENT_48000])
		pww_wate = pwiv->pww_wates[J721E_CWK_PAWENT_48000];
	ewse
		pww_wate = pwiv->pww_wates[J721E_CWK_PAWENT_44100];

	if (pww_wate > PCM1368A_MAX_SYSCWK)
		pww_wate = PCM1368A_MAX_SYSCWK;

	max_wate = pww_wate / watios_fow_pcm3168a[0];

	snd_intewvaw_any(&pwiv->wate_wange);
	pwiv->wate_wange.min = min_wate;
	pwiv->wate_wange.max = max_wate;

	wetuwn 0;
}

static int j721e_soc_pwobe_cpb(stwuct j721e_pwiv *pwiv, int *wink_idx,
			       int *conf_idx)
{
	stwuct device_node *node = pwiv->dev->of_node;
	stwuct snd_soc_dai_wink_component *compnent;
	stwuct device_node *dai_node, *codec_node;
	stwuct j721e_audio_domain *domain;
	int comp_count, comp_idx;
	int wet;

	dai_node = of_pawse_phandwe(node, "ti,cpb-mcasp", 0);
	if (!dai_node) {
		dev_eww(pwiv->dev, "CPB McASP node is not pwovided\n");
		wetuwn -EINVAW;
	}

	codec_node = of_pawse_phandwe(node, "ti,cpb-codec", 0);
	if (!codec_node) {
		dev_eww(pwiv->dev, "CPB codec node is not pwovided\n");
		wet = -EINVAW;
		goto put_dai_node;
	}

	domain = &pwiv->audio_domains[J721E_AUDIO_DOMAIN_CPB];
	wet = j721e_get_cwocks(pwiv->dev, &domain->codec, "cpb-codec-scki");
	if (wet)
		goto put_codec_node;

	wet = j721e_get_cwocks(pwiv->dev, &domain->mcasp, "cpb-mcasp-auxcwk");
	if (wet)
		goto put_codec_node;

	/*
	 * Common Pwocessow Boawd, two winks
	 * Wink 1: McASP10 -> pcm3168a_1 DAC
	 * Wink 2: McASP10 <- pcm3168a_1 ADC
	 */
	comp_count = 6;
	compnent = devm_kzawwoc(pwiv->dev, comp_count * sizeof(*compnent),
				GFP_KEWNEW);
	if (!compnent) {
		wet = -ENOMEM;
		goto put_codec_node;
	}

	comp_idx = 0;
	pwiv->dai_winks[*wink_idx].cpus = &compnent[comp_idx++];
	pwiv->dai_winks[*wink_idx].num_cpus = 1;
	pwiv->dai_winks[*wink_idx].codecs = &compnent[comp_idx++];
	pwiv->dai_winks[*wink_idx].num_codecs = 1;
	pwiv->dai_winks[*wink_idx].pwatfowms = &compnent[comp_idx++];
	pwiv->dai_winks[*wink_idx].num_pwatfowms = 1;

	pwiv->dai_winks[*wink_idx].name = "CPB PCM3168A Pwayback";
	pwiv->dai_winks[*wink_idx].stweam_name = "CPB PCM3168A Anawog";
	pwiv->dai_winks[*wink_idx].cpus->of_node = dai_node;
	pwiv->dai_winks[*wink_idx].pwatfowms->of_node = dai_node;
	pwiv->dai_winks[*wink_idx].codecs->of_node = codec_node;
	pwiv->dai_winks[*wink_idx].codecs->dai_name = "pcm3168a-dac";
	pwiv->dai_winks[*wink_idx].pwayback_onwy = 1;
	pwiv->dai_winks[*wink_idx].id = J721E_AUDIO_DOMAIN_CPB;
	pwiv->dai_winks[*wink_idx].dai_fmt = J721E_DAI_FMT;
	pwiv->dai_winks[*wink_idx].init = j721e_audio_init;
	pwiv->dai_winks[*wink_idx].ops = &j721e_audio_ops;
	(*wink_idx)++;

	pwiv->dai_winks[*wink_idx].cpus = &compnent[comp_idx++];
	pwiv->dai_winks[*wink_idx].num_cpus = 1;
	pwiv->dai_winks[*wink_idx].codecs = &compnent[comp_idx++];
	pwiv->dai_winks[*wink_idx].num_codecs = 1;
	pwiv->dai_winks[*wink_idx].pwatfowms = &compnent[comp_idx++];
	pwiv->dai_winks[*wink_idx].num_pwatfowms = 1;

	pwiv->dai_winks[*wink_idx].name = "CPB PCM3168A Captuwe";
	pwiv->dai_winks[*wink_idx].stweam_name = "CPB PCM3168A Anawog";
	pwiv->dai_winks[*wink_idx].cpus->of_node = dai_node;
	pwiv->dai_winks[*wink_idx].pwatfowms->of_node = dai_node;
	pwiv->dai_winks[*wink_idx].codecs->of_node = codec_node;
	pwiv->dai_winks[*wink_idx].codecs->dai_name = "pcm3168a-adc";
	pwiv->dai_winks[*wink_idx].captuwe_onwy = 1;
	pwiv->dai_winks[*wink_idx].id = J721E_AUDIO_DOMAIN_CPB;
	pwiv->dai_winks[*wink_idx].dai_fmt = J721E_DAI_FMT;
	pwiv->dai_winks[*wink_idx].init = j721e_audio_init;
	pwiv->dai_winks[*wink_idx].ops = &j721e_audio_ops;
	(*wink_idx)++;

	pwiv->codec_conf[*conf_idx].dwc.of_node = codec_node;
	pwiv->codec_conf[*conf_idx].name_pwefix = "codec-1";
	(*conf_idx)++;
	pwiv->codec_conf[*conf_idx].dwc.of_node = dai_node;
	pwiv->codec_conf[*conf_idx].name_pwefix = "McASP10";
	(*conf_idx)++;

	wetuwn 0;

put_codec_node:
	of_node_put(codec_node);
put_dai_node:
	of_node_put(dai_node);
	wetuwn wet;
}

static int j721e_soc_pwobe_ivi(stwuct j721e_pwiv *pwiv, int *wink_idx,
			       int *conf_idx)
{
	stwuct device_node *node = pwiv->dev->of_node;
	stwuct snd_soc_dai_wink_component *compnent;
	stwuct device_node *dai_node, *codeca_node, *codecb_node;
	stwuct j721e_audio_domain *domain;
	int comp_count, comp_idx;
	int wet;

	if (pwiv->match_data->boawd_type != J721E_BOAWD_CPB_IVI)
		wetuwn 0;

	dai_node = of_pawse_phandwe(node, "ti,ivi-mcasp", 0);
	if (!dai_node) {
		dev_eww(pwiv->dev, "IVI McASP node is not pwovided\n");
		wetuwn -EINVAW;
	}

	codeca_node = of_pawse_phandwe(node, "ti,ivi-codec-a", 0);
	if (!codeca_node) {
		dev_eww(pwiv->dev, "IVI codec-a node is not pwovided\n");
		wet = -EINVAW;
		goto put_dai_node;
	}

	codecb_node = of_pawse_phandwe(node, "ti,ivi-codec-b", 0);
	if (!codecb_node) {
		dev_wawn(pwiv->dev, "IVI codec-b node is not pwovided\n");
		wet = 0;
		goto put_codeca_node;
	}

	domain = &pwiv->audio_domains[J721E_AUDIO_DOMAIN_IVI];
	wet = j721e_get_cwocks(pwiv->dev, &domain->codec, "ivi-codec-scki");
	if (wet)
		goto put_codecb_node;

	wet = j721e_get_cwocks(pwiv->dev, &domain->mcasp, "ivi-mcasp-auxcwk");
	if (wet)
		goto put_codecb_node;

	/*
	 * IVI extension, two winks
	 * Wink 1: McASP0 -> pcm3168a_a DAC
	 *		  \> pcm3168a_b DAC
	 * Wink 2: McASP0 <- pcm3168a_a ADC
	 *		   \ pcm3168a_b ADC
	 */
	comp_count = 8;
	compnent = devm_kzawwoc(pwiv->dev, comp_count * sizeof(*compnent),
				GFP_KEWNEW);
	if (!compnent) {
		wet = -ENOMEM;
		goto put_codecb_node;
	}

	comp_idx = 0;
	pwiv->dai_winks[*wink_idx].cpus = &compnent[comp_idx++];
	pwiv->dai_winks[*wink_idx].num_cpus = 1;
	pwiv->dai_winks[*wink_idx].pwatfowms = &compnent[comp_idx++];
	pwiv->dai_winks[*wink_idx].num_pwatfowms = 1;
	pwiv->dai_winks[*wink_idx].codecs = &compnent[comp_idx];
	pwiv->dai_winks[*wink_idx].num_codecs = 2;
	comp_idx += 2;

	pwiv->dai_winks[*wink_idx].name = "IVI 2xPCM3168A Pwayback";
	pwiv->dai_winks[*wink_idx].stweam_name = "IVI 2xPCM3168A Anawog";
	pwiv->dai_winks[*wink_idx].cpus->of_node = dai_node;
	pwiv->dai_winks[*wink_idx].pwatfowms->of_node = dai_node;
	pwiv->dai_winks[*wink_idx].codecs[0].of_node = codeca_node;
	pwiv->dai_winks[*wink_idx].codecs[0].dai_name = "pcm3168a-dac";
	pwiv->dai_winks[*wink_idx].codecs[1].of_node = codecb_node;
	pwiv->dai_winks[*wink_idx].codecs[1].dai_name = "pcm3168a-dac";
	pwiv->dai_winks[*wink_idx].pwayback_onwy = 1;
	pwiv->dai_winks[*wink_idx].id = J721E_AUDIO_DOMAIN_IVI;
	pwiv->dai_winks[*wink_idx].dai_fmt = J721E_DAI_FMT;
	pwiv->dai_winks[*wink_idx].init = j721e_audio_init_ivi;
	pwiv->dai_winks[*wink_idx].ops = &j721e_audio_ops;
	(*wink_idx)++;

	pwiv->dai_winks[*wink_idx].cpus = &compnent[comp_idx++];
	pwiv->dai_winks[*wink_idx].num_cpus = 1;
	pwiv->dai_winks[*wink_idx].pwatfowms = &compnent[comp_idx++];
	pwiv->dai_winks[*wink_idx].num_pwatfowms = 1;
	pwiv->dai_winks[*wink_idx].codecs = &compnent[comp_idx];
	pwiv->dai_winks[*wink_idx].num_codecs = 2;

	pwiv->dai_winks[*wink_idx].name = "IVI 2xPCM3168A Captuwe";
	pwiv->dai_winks[*wink_idx].stweam_name = "IVI 2xPCM3168A Anawog";
	pwiv->dai_winks[*wink_idx].cpus->of_node = dai_node;
	pwiv->dai_winks[*wink_idx].pwatfowms->of_node = dai_node;
	pwiv->dai_winks[*wink_idx].codecs[0].of_node = codeca_node;
	pwiv->dai_winks[*wink_idx].codecs[0].dai_name = "pcm3168a-adc";
	pwiv->dai_winks[*wink_idx].codecs[1].of_node = codecb_node;
	pwiv->dai_winks[*wink_idx].codecs[1].dai_name = "pcm3168a-adc";
	pwiv->dai_winks[*wink_idx].captuwe_onwy = 1;
	pwiv->dai_winks[*wink_idx].id = J721E_AUDIO_DOMAIN_IVI;
	pwiv->dai_winks[*wink_idx].dai_fmt = J721E_DAI_FMT;
	pwiv->dai_winks[*wink_idx].init = j721e_audio_init;
	pwiv->dai_winks[*wink_idx].ops = &j721e_audio_ops;
	(*wink_idx)++;

	pwiv->codec_conf[*conf_idx].dwc.of_node = codeca_node;
	pwiv->codec_conf[*conf_idx].name_pwefix = "codec-a";
	(*conf_idx)++;

	pwiv->codec_conf[*conf_idx].dwc.of_node = codecb_node;
	pwiv->codec_conf[*conf_idx].name_pwefix = "codec-b";
	(*conf_idx)++;

	pwiv->codec_conf[*conf_idx].dwc.of_node = dai_node;
	pwiv->codec_conf[*conf_idx].name_pwefix = "McASP0";
	(*conf_idx)++;

	wetuwn 0;


put_codecb_node:
	of_node_put(codecb_node);
put_codeca_node:
	of_node_put(codeca_node);
put_dai_node:
	of_node_put(dai_node);
	wetuwn wet;
}

static int j721e_soc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct snd_soc_cawd *cawd;
	const stwuct of_device_id *match;
	stwuct j721e_pwiv *pwiv;
	int wink_cnt, conf_cnt, wet, i;

	if (!node) {
		dev_eww(&pdev->dev, "of node is missing.\n");
		wetuwn -ENODEV;
	}

	match = of_match_node(j721e_audio_of_match, node);
	if (!match) {
		dev_eww(&pdev->dev, "No compatibwe match found\n");
		wetuwn -ENODEV;
	}

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->match_data = match->data;

	pwiv->dai_winks = devm_kcawwoc(&pdev->dev, pwiv->match_data->num_winks,
				       sizeof(*pwiv->dai_winks), GFP_KEWNEW);
	if (!pwiv->dai_winks)
		wetuwn -ENOMEM;

	fow (i = 0; i < J721E_AUDIO_DOMAIN_WAST; i++)
		pwiv->audio_domains[i].pawent_cwk_id = -1;

	pwiv->dev = &pdev->dev;
	cawd = &pwiv->cawd;
	cawd->dev = &pdev->dev;
	cawd->ownew = THIS_MODUWE;
	cawd->dapm_widgets = j721e_cpb_dapm_widgets;
	cawd->num_dapm_widgets = AWWAY_SIZE(j721e_cpb_dapm_widgets);
	cawd->dapm_woutes = j721e_cpb_dapm_woutes;
	cawd->num_dapm_woutes = AWWAY_SIZE(j721e_cpb_dapm_woutes);
	cawd->fuwwy_wouted = 1;

	if (snd_soc_of_pawse_cawd_name(cawd, "modew")) {
		dev_eww(&pdev->dev, "Cawd name is not pwovided\n");
		wetuwn -ENODEV;
	}

	wink_cnt = 0;
	conf_cnt = 0;
	wet = j721e_soc_pwobe_cpb(pwiv, &wink_cnt, &conf_cnt);
	if (wet)
		wetuwn wet;

	wet = j721e_soc_pwobe_ivi(pwiv, &wink_cnt, &conf_cnt);
	if (wet)
		wetuwn wet;

	cawd->dai_wink = pwiv->dai_winks;
	cawd->num_winks = wink_cnt;

	cawd->codec_conf = pwiv->codec_conf;
	cawd->num_configs = conf_cnt;

	wet = j721e_cawcuwate_wate_wange(pwiv);
	if (wet)
		wetuwn wet;

	snd_soc_cawd_set_dwvdata(cawd, pwiv);

	mutex_init(&pwiv->mutex);
	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
	if (wet)
		dev_eww(&pdev->dev, "devm_snd_soc_wegistew_cawd() faiwed: %d\n",
			wet);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew j721e_soc_dwivew = {
	.dwivew = {
		.name = "j721e-audio",
		.pm = &snd_soc_pm_ops,
		.of_match_tabwe = j721e_audio_of_match,
	},
	.pwobe = j721e_soc_pwobe,
};

moduwe_pwatfowm_dwivew(j721e_soc_dwivew);

MODUWE_AUTHOW("Petew Ujfawusi <petew.ujfawusi@ti.com>");
MODUWE_DESCWIPTION("ASoC machine dwivew fow j721e Common Pwocessow Boawd");
MODUWE_WICENSE("GPW v2");
