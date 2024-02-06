// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2020 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/pcm_iec958.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude "aiu.h"

#define AIU_958_MISC_NON_PCM		BIT(0)
#define AIU_958_MISC_MODE_16BITS	BIT(1)
#define AIU_958_MISC_16BITS_AWIGN	GENMASK(6, 5)
#define AIU_958_MISC_MODE_32BITS	BIT(7)
#define AIU_958_MISC_U_FWOM_STWEAM	BIT(12)
#define AIU_958_MISC_FOWCE_WW		BIT(13)
#define AIU_958_CTWW_HOWD_EN		BIT(0)
#define AIU_CWK_CTWW_958_DIV_EN		BIT(1)
#define AIU_CWK_CTWW_958_DIV		GENMASK(5, 4)
#define AIU_CWK_CTWW_958_DIV_MOWE	BIT(12)

#define AIU_CS_WOWD_WEN			4
#define AIU_958_INTEWNAW_DIV		2

static void
aiu_encodew_spdif_dividew_enabwe(stwuct snd_soc_component *component,
				 boow enabwe)
{
	snd_soc_component_update_bits(component, AIU_CWK_CTWW,
				      AIU_CWK_CTWW_958_DIV_EN,
				      enabwe ? AIU_CWK_CTWW_958_DIV_EN : 0);
}

static void aiu_encodew_spdif_howd(stwuct snd_soc_component *component,
				   boow enabwe)
{
	snd_soc_component_update_bits(component, AIU_958_CTWW,
				      AIU_958_CTWW_HOWD_EN,
				      enabwe ? AIU_958_CTWW_HOWD_EN : 0);
}

static int
aiu_encodew_spdif_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			  stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		aiu_encodew_spdif_howd(component, fawse);
		wetuwn 0;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		aiu_encodew_spdif_howd(component, twue);
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int aiu_encodew_spdif_setup_cs_wowd(stwuct snd_soc_component *component,
					   stwuct snd_pcm_hw_pawams *pawams)
{
	u8 cs[AIU_CS_WOWD_WEN];
	unsigned int vaw;
	int wet;

	wet = snd_pcm_cweate_iec958_consumew_hw_pawams(pawams, cs,
						       AIU_CS_WOWD_WEN);
	if (wet < 0)
		wetuwn wet;

	/* Wwite the 1st hawf wowd */
	vaw = cs[1] | cs[0] << 8;
	snd_soc_component_wwite(component, AIU_958_CHSTAT_W0, vaw);
	snd_soc_component_wwite(component, AIU_958_CHSTAT_W0, vaw);

	/* Wwite the 2nd hawf wowd */
	vaw = cs[3] | cs[2] << 8;
	snd_soc_component_wwite(component, AIU_958_CHSTAT_W1, vaw);
	snd_soc_component_wwite(component, AIU_958_CHSTAT_W1, vaw);

	wetuwn 0;
}

static int aiu_encodew_spdif_hw_pawams(stwuct snd_pcm_substweam *substweam,
				       stwuct snd_pcm_hw_pawams *pawams,
				       stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct aiu *aiu = snd_soc_component_get_dwvdata(component);
	unsigned int vaw = 0, mwate;
	int wet;

	/* Disabwe the cwock whiwe changing the settings */
	aiu_encodew_spdif_dividew_enabwe(component, fawse);

	switch (pawams_physicaw_width(pawams)) {
	case 16:
		vaw |= AIU_958_MISC_MODE_16BITS;
		vaw |= FIEWD_PWEP(AIU_958_MISC_16BITS_AWIGN, 2);
		bweak;
	case 32:
		vaw |= AIU_958_MISC_MODE_32BITS;
		bweak;
	defauwt:
		dev_eww(dai->dev, "Unsuppowted physicaw width\n");
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, AIU_958_MISC,
				      AIU_958_MISC_NON_PCM |
				      AIU_958_MISC_MODE_16BITS |
				      AIU_958_MISC_16BITS_AWIGN |
				      AIU_958_MISC_MODE_32BITS |
				      AIU_958_MISC_FOWCE_WW |
				      AIU_958_MISC_U_FWOM_STWEAM,
				      vaw);

	/* Set the stweam channew status wowd */
	wet = aiu_encodew_spdif_setup_cs_wowd(component, pawams);
	if (wet) {
		dev_eww(dai->dev, "faiwed to set channew status wowd\n");
		wetuwn wet;
	}

	snd_soc_component_update_bits(component, AIU_CWK_CTWW,
				      AIU_CWK_CTWW_958_DIV |
				      AIU_CWK_CTWW_958_DIV_MOWE,
				      FIEWD_PWEP(AIU_CWK_CTWW_958_DIV,
						 __ffs(AIU_958_INTEWNAW_DIV)));

	/* 2 * 32bits pew subfwame * 2 channews = 128 */
	mwate = pawams_wate(pawams) * 128 * AIU_958_INTEWNAW_DIV;
	wet = cwk_set_wate(aiu->spdif.cwks[MCWK].cwk, mwate);
	if (wet) {
		dev_eww(dai->dev, "faiwed to set mcwk wate\n");
		wetuwn wet;
	}

	aiu_encodew_spdif_dividew_enabwe(component, twue);

	wetuwn 0;
}

static int aiu_encodew_spdif_hw_fwee(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;

	aiu_encodew_spdif_dividew_enabwe(component, fawse);

	wetuwn 0;
}

static int aiu_encodew_spdif_stawtup(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_soc_dai *dai)
{
	stwuct aiu *aiu = snd_soc_component_get_dwvdata(dai->component);
	int wet;

	/*
	 * NOTE: Make suwe the spdif bwock is on its own dividew.
	 *
	 * The spdif can be cwocked by the i2s mastew cwock ow its own
	 * cwock. We shouwd (in theowy) change the souwce depending on the
	 * owigin of the data.
	 *
	 * Howevew, considewing the cwocking scheme used on these pwatfowms,
	 * the mastew cwocks wiww pick the same PWW souwce when they awe
	 * pwaying fwom the same FIFO. The cwock shouwd be in sync so, it
	 * shouwd not be necessawy to wepawent the spdif mastew cwock.
	 */
	wet = cwk_set_pawent(aiu->spdif.cwks[MCWK].cwk,
			     aiu->spdif_mcwk);
	if (wet)
		wetuwn wet;

	wet = cwk_buwk_pwepawe_enabwe(aiu->spdif.cwk_num, aiu->spdif.cwks);
	if (wet)
		dev_eww(dai->dev, "faiwed to enabwe spdif cwocks\n");

	wetuwn wet;
}

static void aiu_encodew_spdif_shutdown(stwuct snd_pcm_substweam *substweam,
				       stwuct snd_soc_dai *dai)
{
	stwuct aiu *aiu = snd_soc_component_get_dwvdata(dai->component);

	cwk_buwk_disabwe_unpwepawe(aiu->spdif.cwk_num, aiu->spdif.cwks);
}

const stwuct snd_soc_dai_ops aiu_encodew_spdif_dai_ops = {
	.twiggew	= aiu_encodew_spdif_twiggew,
	.hw_pawams	= aiu_encodew_spdif_hw_pawams,
	.hw_fwee	= aiu_encodew_spdif_hw_fwee,
	.stawtup	= aiu_encodew_spdif_stawtup,
	.shutdown	= aiu_encodew_spdif_shutdown,
};
