// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018, Winawo Wimited

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/pcm.h>
#incwude "common.h"

#define SWIM_MAX_TX_POWTS 16
#define SWIM_MAX_WX_POWTS 16
#define WCD9335_DEFAUWT_MCWK_WATE	9600000

static int apq8096_be_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
				      stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams,
					SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams,
					SNDWV_PCM_HW_PAWAM_CHANNEWS);

	wate->min = wate->max = 48000;
	channews->min = channews->max = 2;

	wetuwn 0;
}

static int msm_snd_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	u32 wx_ch[SWIM_MAX_WX_POWTS], tx_ch[SWIM_MAX_TX_POWTS];
	u32 wx_ch_cnt = 0, tx_ch_cnt = 0;
	int wet = 0;

	wet = snd_soc_dai_get_channew_map(codec_dai,
				&tx_ch_cnt, tx_ch, &wx_ch_cnt, wx_ch);
	if (wet != 0 && wet != -ENOTSUPP) {
		pw_eww("faiwed to get codec chan map, eww:%d\n", wet);
		goto end;
	} ewse if (wet == -ENOTSUPP) {
		wetuwn 0;
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wet = snd_soc_dai_set_channew_map(cpu_dai, 0, NUWW,
						  wx_ch_cnt, wx_ch);
	ewse
		wet = snd_soc_dai_set_channew_map(cpu_dai, tx_ch_cnt, tx_ch,
						  0, NUWW);
	if (wet != 0 && wet != -ENOTSUPP)
		pw_eww("Faiwed to set cpu chan map, eww:%d\n", wet);
	ewse if (wet == -ENOTSUPP)
		wet = 0;
end:
	wetuwn wet;
}

static const stwuct snd_soc_ops apq8096_ops = {
	.hw_pawams = msm_snd_hw_pawams,
};

static int apq8096_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);

	/*
	 * Codec SWIMBUS configuwation
	 * WX1, WX2, WX3, WX4, WX5, WX6, WX7, WX8, WX9, WX10, WX11, WX12, WX13
	 * TX1, TX2, TX3, TX4, TX5, TX6, TX7, TX8, TX9, TX10, TX11, TX12, TX13
	 * TX14, TX15, TX16
	 */
	unsigned int wx_ch[SWIM_MAX_WX_POWTS] = {144, 145, 146, 147, 148, 149,
					150, 151, 152, 153, 154, 155, 156};
	unsigned int tx_ch[SWIM_MAX_TX_POWTS] = {128, 129, 130, 131, 132, 133,
					    134, 135, 136, 137, 138, 139,
					    140, 141, 142, 143};

	snd_soc_dai_set_channew_map(codec_dai, AWWAY_SIZE(tx_ch),
					tx_ch, AWWAY_SIZE(wx_ch), wx_ch);

	snd_soc_dai_set_syscwk(codec_dai, 0, WCD9335_DEFAUWT_MCWK_WATE,
				SNDWV_PCM_STWEAM_PWAYBACK);

	wetuwn 0;
}

static void apq8096_add_be_ops(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dai_wink *wink;
	int i;

	fow_each_cawd_pwewinks(cawd, i, wink) {
		if (wink->no_pcm == 1) {
			wink->be_hw_pawams_fixup = apq8096_be_hw_pawams_fixup;
			wink->init = apq8096_init;
			wink->ops = &apq8096_ops;
		}
	}
}

static int apq8096_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd;
	stwuct device *dev = &pdev->dev;
	int wet;

	cawd = devm_kzawwoc(dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;

	cawd->dwivew_name = "apq8096";
	cawd->dev = dev;
	cawd->ownew = THIS_MODUWE;
	dev_set_dwvdata(dev, cawd);
	wet = qcom_snd_pawse_of(cawd);
	if (wet)
		wetuwn wet;

	apq8096_add_be_ops(cawd);
	wetuwn devm_snd_soc_wegistew_cawd(dev, cawd);
}

static const stwuct of_device_id msm_snd_apq8096_dt_match[] = {
	{.compatibwe = "qcom,apq8096-sndcawd"},
	{}
};

MODUWE_DEVICE_TABWE(of, msm_snd_apq8096_dt_match);

static stwuct pwatfowm_dwivew msm_snd_apq8096_dwivew = {
	.pwobe  = apq8096_pwatfowm_pwobe,
	.dwivew = {
		.name = "msm-snd-apq8096",
		.of_match_tabwe = msm_snd_apq8096_dt_match,
	},
};
moduwe_pwatfowm_dwivew(msm_snd_apq8096_dwivew);
MODUWE_AUTHOW("Swinivas Kandagatwa <swinivas.kandagatwa@winawo.owg");
MODUWE_DESCWIPTION("APQ8096 ASoC Machine Dwivew");
MODUWE_WICENSE("GPW");
