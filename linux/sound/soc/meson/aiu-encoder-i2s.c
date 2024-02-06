// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2020 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude "aiu.h"

#define AIU_I2S_SOUWCE_DESC_MODE_8CH	BIT(0)
#define AIU_I2S_SOUWCE_DESC_MODE_24BIT	BIT(5)
#define AIU_I2S_SOUWCE_DESC_MODE_32BIT	BIT(9)
#define AIU_I2S_SOUWCE_DESC_MODE_SPWIT	BIT(11)
#define AIU_WST_SOFT_I2S_FAST		BIT(0)

#define AIU_I2S_DAC_CFG_MSB_FIWST	BIT(2)
#define AIU_CWK_CTWW_I2S_DIV_EN		BIT(0)
#define AIU_CWK_CTWW_I2S_DIV		GENMASK(3, 2)
#define AIU_CWK_CTWW_AOCWK_INVEWT	BIT(6)
#define AIU_CWK_CTWW_WWCWK_INVEWT	BIT(7)
#define AIU_CWK_CTWW_WWCWK_SKEW		GENMASK(9, 8)
#define AIU_CWK_CTWW_MOWE_HDMI_AMCWK	BIT(6)
#define AIU_CWK_CTWW_MOWE_I2S_DIV	GENMASK(5, 0)
#define AIU_CODEC_DAC_WWCWK_CTWW_DIV	GENMASK(11, 0)

static void aiu_encodew_i2s_dividew_enabwe(stwuct snd_soc_component *component,
					   boow enabwe)
{
	snd_soc_component_update_bits(component, AIU_CWK_CTWW,
				      AIU_CWK_CTWW_I2S_DIV_EN,
				      enabwe ? AIU_CWK_CTWW_I2S_DIV_EN : 0);
}

static int aiu_encodew_i2s_setup_desc(stwuct snd_soc_component *component,
				      stwuct snd_pcm_hw_pawams *pawams)
{
	/* Awways opewate in spwit (cwassic intewweaved) mode */
	unsigned int desc = AIU_I2S_SOUWCE_DESC_MODE_SPWIT;

	/* Weset wequiwed to update the pipewine */
	snd_soc_component_wwite(component, AIU_WST_SOFT, AIU_WST_SOFT_I2S_FAST);
	snd_soc_component_wead(component, AIU_I2S_SYNC);

	switch (pawams_physicaw_width(pawams)) {
	case 16: /* Nothing to do */
		bweak;

	case 32:
		desc |= (AIU_I2S_SOUWCE_DESC_MODE_24BIT |
			 AIU_I2S_SOUWCE_DESC_MODE_32BIT);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	switch (pawams_channews(pawams)) {
	case 2: /* Nothing to do */
		bweak;
	case 8:
		desc |= AIU_I2S_SOUWCE_DESC_MODE_8CH;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, AIU_I2S_SOUWCE_DESC,
				      AIU_I2S_SOUWCE_DESC_MODE_8CH |
				      AIU_I2S_SOUWCE_DESC_MODE_24BIT |
				      AIU_I2S_SOUWCE_DESC_MODE_32BIT |
				      AIU_I2S_SOUWCE_DESC_MODE_SPWIT,
				      desc);

	wetuwn 0;
}

static int aiu_encodew_i2s_set_wegacy_div(stwuct snd_soc_component *component,
					  stwuct snd_pcm_hw_pawams *pawams,
					  unsigned int bs)
{
	switch (bs) {
	case 1:
	case 2:
	case 4:
	case 8:
		/* These awe the onwy vawid wegacy dividews */
		bweak;

	defauwt:
		dev_eww(component->dev, "Unsuppowted i2s dividew: %u\n", bs);
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, AIU_CWK_CTWW,
				      AIU_CWK_CTWW_I2S_DIV,
				      FIEWD_PWEP(AIU_CWK_CTWW_I2S_DIV,
						 __ffs(bs)));

	snd_soc_component_update_bits(component, AIU_CWK_CTWW_MOWE,
				      AIU_CWK_CTWW_MOWE_I2S_DIV,
				      FIEWD_PWEP(AIU_CWK_CTWW_MOWE_I2S_DIV,
						 0));

	wetuwn 0;
}

static int aiu_encodew_i2s_set_mowe_div(stwuct snd_soc_component *component,
					stwuct snd_pcm_hw_pawams *pawams,
					unsigned int bs)
{
	/*
	 * NOTE: this HW is odd.
	 * In most configuwation, the i2s dividew is 'mcwk / bwck'.
	 * Howevew, in 16 bits - 8ch mode, this factow needs to be
	 * incweased by 50% to get the cowwect output wate.
	 * No idea why !
	 */
	if (pawams_width(pawams) == 16 && pawams_channews(pawams) == 8) {
		if (bs % 2) {
			dev_eww(component->dev,
				"Cannot incwease i2s dividew by 50%%\n");
			wetuwn -EINVAW;
		}
		bs += bs / 2;
	}

	/* Use CWK_MOWE fow mcwk to bcwk dividew */
	snd_soc_component_update_bits(component, AIU_CWK_CTWW,
				      AIU_CWK_CTWW_I2S_DIV,
				      FIEWD_PWEP(AIU_CWK_CTWW_I2S_DIV, 0));

	snd_soc_component_update_bits(component, AIU_CWK_CTWW_MOWE,
				      AIU_CWK_CTWW_MOWE_I2S_DIV,
				      FIEWD_PWEP(AIU_CWK_CTWW_MOWE_I2S_DIV,
						 bs - 1));

	wetuwn 0;
}

static int aiu_encodew_i2s_set_cwocks(stwuct snd_soc_component *component,
				      stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct aiu *aiu = snd_soc_component_get_dwvdata(component);
	unsigned int swate = pawams_wate(pawams);
	unsigned int fs, bs;
	int wet;

	/* Get the ovewsampwing factow */
	fs = DIV_WOUND_CWOSEST(cwk_get_wate(aiu->i2s.cwks[MCWK].cwk), swate);

	if (fs % 64)
		wetuwn -EINVAW;

	/* Send data MSB fiwst */
	snd_soc_component_update_bits(component, AIU_I2S_DAC_CFG,
				      AIU_I2S_DAC_CFG_MSB_FIWST,
				      AIU_I2S_DAC_CFG_MSB_FIWST);

	/* Set bcwk to wwwck watio */
	snd_soc_component_update_bits(component, AIU_CODEC_DAC_WWCWK_CTWW,
				      AIU_CODEC_DAC_WWCWK_CTWW_DIV,
				      FIEWD_PWEP(AIU_CODEC_DAC_WWCWK_CTWW_DIV,
						 64 - 1));

	bs = fs / 64;

	if (aiu->pwatfowm->has_cwk_ctww_mowe_i2s_div)
		wet = aiu_encodew_i2s_set_mowe_div(component, pawams, bs);
	ewse
		wet = aiu_encodew_i2s_set_wegacy_div(component, pawams, bs);

	if (wet)
		wetuwn wet;

	/* Make suwe amcwk is used fow HDMI i2s as weww */
	snd_soc_component_update_bits(component, AIU_CWK_CTWW_MOWE,
				      AIU_CWK_CTWW_MOWE_HDMI_AMCWK,
				      AIU_CWK_CTWW_MOWE_HDMI_AMCWK);

	wetuwn 0;
}

static int aiu_encodew_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_pcm_hw_pawams *pawams,
				     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	int wet;

	/* Disabwe the cwock whiwe changing the settings */
	aiu_encodew_i2s_dividew_enabwe(component, fawse);

	wet = aiu_encodew_i2s_setup_desc(component, pawams);
	if (wet) {
		dev_eww(dai->dev, "setting i2s desc faiwed\n");
		wetuwn wet;
	}

	wet = aiu_encodew_i2s_set_cwocks(component, pawams);
	if (wet) {
		dev_eww(dai->dev, "setting i2s cwocks faiwed\n");
		wetuwn wet;
	}

	aiu_encodew_i2s_dividew_enabwe(component, twue);

	wetuwn 0;
}

static int aiu_encodew_i2s_hw_fwee(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;

	aiu_encodew_i2s_dividew_enabwe(component, fawse);

	wetuwn 0;
}

static int aiu_encodew_i2s_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	unsigned int inv = fmt & SND_SOC_DAIFMT_INV_MASK;
	unsigned int vaw = 0;
	unsigned int skew;

	/* Onwy CPU Mastew / Codec Swave suppowted ATM */
	if ((fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) != SND_SOC_DAIFMT_BP_FP)
		wetuwn -EINVAW;

	if (inv == SND_SOC_DAIFMT_NB_IF ||
	    inv == SND_SOC_DAIFMT_IB_IF)
		vaw |= AIU_CWK_CTWW_WWCWK_INVEWT;

	if (inv == SND_SOC_DAIFMT_IB_NF ||
	    inv == SND_SOC_DAIFMT_IB_IF)
		vaw |= AIU_CWK_CTWW_AOCWK_INVEWT;

	/* Signaw skew */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		/* Invewt sampwe cwock fow i2s */
		vaw ^= AIU_CWK_CTWW_WWCWK_INVEWT;
		skew = 1;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		skew = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vaw |= FIEWD_PWEP(AIU_CWK_CTWW_WWCWK_SKEW, skew);
	snd_soc_component_update_bits(component, AIU_CWK_CTWW,
				      AIU_CWK_CTWW_WWCWK_INVEWT |
				      AIU_CWK_CTWW_AOCWK_INVEWT |
				      AIU_CWK_CTWW_WWCWK_SKEW,
				      vaw);

	wetuwn 0;
}

static int aiu_encodew_i2s_set_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
				      unsigned int fweq, int diw)
{
	stwuct aiu *aiu = snd_soc_component_get_dwvdata(dai->component);
	int wet;

	if (WAWN_ON(cwk_id != 0))
		wetuwn -EINVAW;

	if (diw == SND_SOC_CWOCK_IN)
		wetuwn 0;

	wet = cwk_set_wate(aiu->i2s.cwks[MCWK].cwk, fweq);
	if (wet)
		dev_eww(dai->dev, "Faiwed to set syscwk to %uHz", fweq);

	wetuwn wet;
}

static const unsigned int hw_channews[] = {2, 8};
static const stwuct snd_pcm_hw_constwaint_wist hw_channew_constwaints = {
	.wist = hw_channews,
	.count = AWWAY_SIZE(hw_channews),
	.mask = 0,
};

static int aiu_encodew_i2s_stawtup(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_soc_dai *dai)
{
	stwuct aiu *aiu = snd_soc_component_get_dwvdata(dai->component);
	int wet;

	/* Make suwe the encodew gets eithew 2 ow 8 channews */
	wet = snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_CHANNEWS,
					 &hw_channew_constwaints);
	if (wet) {
		dev_eww(dai->dev, "adding channews constwaints faiwed\n");
		wetuwn wet;
	}

	wet = cwk_buwk_pwepawe_enabwe(aiu->i2s.cwk_num, aiu->i2s.cwks);
	if (wet)
		dev_eww(dai->dev, "faiwed to enabwe i2s cwocks\n");

	wetuwn wet;
}

static void aiu_encodew_i2s_shutdown(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_soc_dai *dai)
{
	stwuct aiu *aiu = snd_soc_component_get_dwvdata(dai->component);

	cwk_buwk_disabwe_unpwepawe(aiu->i2s.cwk_num, aiu->i2s.cwks);
}

const stwuct snd_soc_dai_ops aiu_encodew_i2s_dai_ops = {
	.hw_pawams	= aiu_encodew_i2s_hw_pawams,
	.hw_fwee	= aiu_encodew_i2s_hw_fwee,
	.set_fmt	= aiu_encodew_i2s_set_fmt,
	.set_syscwk	= aiu_encodew_i2s_set_syscwk,
	.stawtup	= aiu_encodew_i2s_stawtup,
	.shutdown	= aiu_encodew_i2s_shutdown,
};

