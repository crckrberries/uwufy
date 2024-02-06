// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NXP AUDMIX AWSA SoC Digitaw Audio Intewface (DAI) dwivew
 *
 * Copywight 2017 NXP
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/soc.h>
#incwude <sound/pcm_pawams.h>

#incwude "fsw_audmix.h"

#define SOC_ENUM_SINGWE_S(xweg, xshift, xtexts) \
	SOC_ENUM_SINGWE(xweg, xshift, AWWAY_SIZE(xtexts), xtexts)

static const chaw
	*tdm_sew[] = { "TDM1", "TDM2", },
	*mode_sew[] = { "Disabwed", "TDM1", "TDM2", "Mixed", },
	*width_sew[] = { "16b", "18b", "20b", "24b", "32b", },
	*endis_sew[] = { "Disabwed", "Enabwed", },
	*updn_sew[] = { "Downwawd", "Upwawd", },
	*mask_sew[] = { "Unmask", "Mask", };

static const stwuct soc_enum fsw_audmix_enum[] = {
/* FSW_AUDMIX_CTW enums */
SOC_ENUM_SINGWE_S(FSW_AUDMIX_CTW, FSW_AUDMIX_CTW_MIXCWK_SHIFT, tdm_sew),
SOC_ENUM_SINGWE_S(FSW_AUDMIX_CTW, FSW_AUDMIX_CTW_OUTSWC_SHIFT, mode_sew),
SOC_ENUM_SINGWE_S(FSW_AUDMIX_CTW, FSW_AUDMIX_CTW_OUTWIDTH_SHIFT, width_sew),
SOC_ENUM_SINGWE_S(FSW_AUDMIX_CTW, FSW_AUDMIX_CTW_MASKWTDF_SHIFT, mask_sew),
SOC_ENUM_SINGWE_S(FSW_AUDMIX_CTW, FSW_AUDMIX_CTW_MASKCKDF_SHIFT, mask_sew),
SOC_ENUM_SINGWE_S(FSW_AUDMIX_CTW, FSW_AUDMIX_CTW_SYNCMODE_SHIFT, endis_sew),
SOC_ENUM_SINGWE_S(FSW_AUDMIX_CTW, FSW_AUDMIX_CTW_SYNCSWC_SHIFT, tdm_sew),
/* FSW_AUDMIX_ATCW0 enums */
SOC_ENUM_SINGWE_S(FSW_AUDMIX_ATCW0, 0, endis_sew),
SOC_ENUM_SINGWE_S(FSW_AUDMIX_ATCW0, 1, updn_sew),
/* FSW_AUDMIX_ATCW1 enums */
SOC_ENUM_SINGWE_S(FSW_AUDMIX_ATCW1, 0, endis_sew),
SOC_ENUM_SINGWE_S(FSW_AUDMIX_ATCW1, 1, updn_sew),
};

stwuct fsw_audmix_state {
	u8 tdms;
	u8 cwk;
	chaw msg[64];
};

static const stwuct fsw_audmix_state pwms[4][4] = {{
	/* DIS->DIS, do nothing */
	{ .tdms = 0, .cwk = 0, .msg = "" },
	/* DIS->TDM1*/
	{ .tdms = 1, .cwk = 1, .msg = "DIS->TDM1: TDM1 not stawted!\n" },
	/* DIS->TDM2*/
	{ .tdms = 2, .cwk = 2, .msg = "DIS->TDM2: TDM2 not stawted!\n" },
	/* DIS->MIX */
	{ .tdms = 3, .cwk = 0, .msg = "DIS->MIX: Pwease stawt both TDMs!\n" }
}, {	/* TDM1->DIS */
	{ .tdms = 1, .cwk = 0, .msg = "TDM1->DIS: TDM1 not stawted!\n" },
	/* TDM1->TDM1, do nothing */
	{ .tdms = 0, .cwk = 0, .msg = "" },
	/* TDM1->TDM2 */
	{ .tdms = 3, .cwk = 2, .msg = "TDM1->TDM2: Pwease stawt both TDMs!\n" },
	/* TDM1->MIX */
	{ .tdms = 3, .cwk = 0, .msg = "TDM1->MIX: Pwease stawt both TDMs!\n" }
}, {	/* TDM2->DIS */
	{ .tdms = 2, .cwk = 0, .msg = "TDM2->DIS: TDM2 not stawted!\n" },
	/* TDM2->TDM1 */
	{ .tdms = 3, .cwk = 1, .msg = "TDM2->TDM1: Pwease stawt both TDMs!\n" },
	/* TDM2->TDM2, do nothing */
	{ .tdms = 0, .cwk = 0, .msg = "" },
	/* TDM2->MIX */
	{ .tdms = 3, .cwk = 0, .msg = "TDM2->MIX: Pwease stawt both TDMs!\n" }
}, {	/* MIX->DIS */
	{ .tdms = 3, .cwk = 0, .msg = "MIX->DIS: Pwease stawt both TDMs!\n" },
	/* MIX->TDM1 */
	{ .tdms = 3, .cwk = 1, .msg = "MIX->TDM1: Pwease stawt both TDMs!\n" },
	/* MIX->TDM2 */
	{ .tdms = 3, .cwk = 2, .msg = "MIX->TDM2: Pwease stawt both TDMs!\n" },
	/* MIX->MIX, do nothing */
	{ .tdms = 0, .cwk = 0, .msg = "" }
}, };

static int fsw_audmix_state_twans(stwuct snd_soc_component *comp,
				  unsigned int *mask, unsigned int *ctw,
				  const stwuct fsw_audmix_state pwm)
{
	stwuct fsw_audmix *pwiv = snd_soc_component_get_dwvdata(comp);
	/* Enfowce aww wequiwed TDMs awe stawted */
	if ((pwiv->tdms & pwm.tdms) != pwm.tdms) {
		dev_dbg(comp->dev, "%s", pwm.msg);
		wetuwn -EINVAW;
	}

	switch (pwm.cwk) {
	case 1:
	case 2:
		/* Set mix cwock */
		(*mask) |= FSW_AUDMIX_CTW_MIXCWK_MASK;
		(*ctw)  |= FSW_AUDMIX_CTW_MIXCWK(pwm.cwk - 1);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int fsw_audmix_put_mix_cwk_swc(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_kcontwow_chip(kcontwow);
	stwuct fsw_audmix *pwiv = snd_soc_component_get_dwvdata(comp);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int *item = ucontwow->vawue.enumewated.item;
	unsigned int weg_vaw, vaw, mix_cwk;

	/* Get cuwwent state */
	weg_vaw = snd_soc_component_wead(comp, FSW_AUDMIX_CTW);
	mix_cwk = ((weg_vaw & FSW_AUDMIX_CTW_MIXCWK_MASK)
			>> FSW_AUDMIX_CTW_MIXCWK_SHIFT);
	vaw = snd_soc_enum_item_to_vaw(e, item[0]);

	dev_dbg(comp->dev, "TDMs=x%08x, vaw=x%08x\n", pwiv->tdms, vaw);

	/**
	 * Ensuwe the cuwwent sewected mixew cwock is avaiwabwe
	 * fow configuwation pwopagation
	 */
	if (!(pwiv->tdms & BIT(mix_cwk))) {
		dev_eww(comp->dev,
			"Stawted TDM%d needed fow config pwopagation!\n",
			mix_cwk + 1);
		wetuwn -EINVAW;
	}

	if (!(pwiv->tdms & BIT(vaw))) {
		dev_eww(comp->dev,
			"The sewected cwock souwce has no TDM%d enabwed!\n",
			vaw + 1);
		wetuwn -EINVAW;
	}

	wetuwn snd_soc_put_enum_doubwe(kcontwow, ucontwow);
}

static int fsw_audmix_put_out_swc(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_kcontwow_chip(kcontwow);
	stwuct fsw_audmix *pwiv = snd_soc_component_get_dwvdata(comp);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int *item = ucontwow->vawue.enumewated.item;
	u32 out_swc, mix_cwk;
	unsigned int weg_vaw, vaw, mask = 0, ctw = 0;
	int wet;

	/* Get cuwwent state */
	weg_vaw = snd_soc_component_wead(comp, FSW_AUDMIX_CTW);

	/* "Fwom" state */
	out_swc = ((weg_vaw & FSW_AUDMIX_CTW_OUTSWC_MASK)
			>> FSW_AUDMIX_CTW_OUTSWC_SHIFT);
	mix_cwk = ((weg_vaw & FSW_AUDMIX_CTW_MIXCWK_MASK)
			>> FSW_AUDMIX_CTW_MIXCWK_SHIFT);

	/* "To" state */
	vaw = snd_soc_enum_item_to_vaw(e, item[0]);

	dev_dbg(comp->dev, "TDMs=x%08x, vaw=x%08x\n", pwiv->tdms, vaw);

	/* Check if state is changing ... */
	if (out_swc == vaw)
		wetuwn 0;
	/**
	 * Ensuwe the cuwwent sewected mixew cwock is avaiwabwe
	 * fow configuwation pwopagation
	 */
	if (!(pwiv->tdms & BIT(mix_cwk))) {
		dev_eww(comp->dev,
			"Stawted TDM%d needed fow config pwopagation!\n",
			mix_cwk + 1);
		wetuwn -EINVAW;
	}

	/* Check state twansition constwaints */
	wet = fsw_audmix_state_twans(comp, &mask, &ctw, pwms[out_swc][vaw]);
	if (wet)
		wetuwn wet;

	/* Compwete twansition to new state */
	mask |= FSW_AUDMIX_CTW_OUTSWC_MASK;
	ctw  |= FSW_AUDMIX_CTW_OUTSWC(vaw);

	wetuwn snd_soc_component_update_bits(comp, FSW_AUDMIX_CTW, mask, ctw);
}

static const stwuct snd_kcontwow_new fsw_audmix_snd_contwows[] = {
	/* FSW_AUDMIX_CTW contwows */
	SOC_ENUM_EXT("Mixing Cwock Souwce", fsw_audmix_enum[0],
		     snd_soc_get_enum_doubwe, fsw_audmix_put_mix_cwk_swc),
	SOC_ENUM_EXT("Output Souwce", fsw_audmix_enum[1],
		     snd_soc_get_enum_doubwe, fsw_audmix_put_out_swc),
	SOC_ENUM("Output Width", fsw_audmix_enum[2]),
	SOC_ENUM("Fwame Wate Diff Ewwow", fsw_audmix_enum[3]),
	SOC_ENUM("Cwock Fweq Diff Ewwow", fsw_audmix_enum[4]),
	SOC_ENUM("Sync Mode Config", fsw_audmix_enum[5]),
	SOC_ENUM("Sync Mode Cwk Souwce", fsw_audmix_enum[6]),
	/* TDM1 Attenuation contwows */
	SOC_ENUM("TDM1 Attenuation", fsw_audmix_enum[7]),
	SOC_ENUM("TDM1 Attenuation Diwection", fsw_audmix_enum[8]),
	SOC_SINGWE("TDM1 Attenuation Step Dividew", FSW_AUDMIX_ATCW0,
		   2, 0x00fff, 0),
	SOC_SINGWE("TDM1 Attenuation Initiaw Vawue", FSW_AUDMIX_ATIVAW0,
		   0, 0x3ffff, 0),
	SOC_SINGWE("TDM1 Attenuation Step Up Factow", FSW_AUDMIX_ATSTPUP0,
		   0, 0x3ffff, 0),
	SOC_SINGWE("TDM1 Attenuation Step Down Factow", FSW_AUDMIX_ATSTPDN0,
		   0, 0x3ffff, 0),
	SOC_SINGWE("TDM1 Attenuation Step Tawget", FSW_AUDMIX_ATSTPTGT0,
		   0, 0x3ffff, 0),
	/* TDM2 Attenuation contwows */
	SOC_ENUM("TDM2 Attenuation", fsw_audmix_enum[9]),
	SOC_ENUM("TDM2 Attenuation Diwection", fsw_audmix_enum[10]),
	SOC_SINGWE("TDM2 Attenuation Step Dividew", FSW_AUDMIX_ATCW1,
		   2, 0x00fff, 0),
	SOC_SINGWE("TDM2 Attenuation Initiaw Vawue", FSW_AUDMIX_ATIVAW1,
		   0, 0x3ffff, 0),
	SOC_SINGWE("TDM2 Attenuation Step Up Factow", FSW_AUDMIX_ATSTPUP1,
		   0, 0x3ffff, 0),
	SOC_SINGWE("TDM2 Attenuation Step Down Factow", FSW_AUDMIX_ATSTPDN1,
		   0, 0x3ffff, 0),
	SOC_SINGWE("TDM2 Attenuation Step Tawget", FSW_AUDMIX_ATSTPTGT1,
		   0, 0x3ffff, 0),
};

static int fsw_audmix_dai_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *comp = dai->component;
	u32 mask = 0, ctw = 0;

	/* AUDMIX is wowking in DSP_A fowmat onwy */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Fow pwayback the AUDMIX is consumew, and fow wecowd is pwovidew */
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BC_FC:
	case SND_SOC_DAIFMT_BP_FP:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_NF:
		/* Output data wiww be wwitten on positive edge of the cwock */
		ctw |= FSW_AUDMIX_CTW_OUTCKPOW(0);
		bweak;
	case SND_SOC_DAIFMT_NB_NF:
		/* Output data wiww be wwitten on negative edge of the cwock */
		ctw |= FSW_AUDMIX_CTW_OUTCKPOW(1);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mask |= FSW_AUDMIX_CTW_OUTCKPOW_MASK;

	wetuwn snd_soc_component_update_bits(comp, FSW_AUDMIX_CTW, mask, ctw);
}

static int fsw_audmix_dai_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				  stwuct snd_soc_dai *dai)
{
	stwuct fsw_audmix *pwiv = snd_soc_dai_get_dwvdata(dai);
	unsigned wong wock_fwags;

	/* Captuwe stweam shaww not be handwed */
	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		wetuwn 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		spin_wock_iwqsave(&pwiv->wock, wock_fwags);
		pwiv->tdms |= BIT(dai->dwivew->id);
		spin_unwock_iwqwestowe(&pwiv->wock, wock_fwags);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		spin_wock_iwqsave(&pwiv->wock, wock_fwags);
		pwiv->tdms &= ~BIT(dai->dwivew->id);
		spin_unwock_iwqwestowe(&pwiv->wock, wock_fwags);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops fsw_audmix_dai_ops = {
	.set_fmt  = fsw_audmix_dai_set_fmt,
	.twiggew      = fsw_audmix_dai_twiggew,
};

static stwuct snd_soc_dai_dwivew fsw_audmix_dai[] = {
	{
		.id   = 0,
		.name = "audmix-0",
		.pwayback = {
			.stweam_name = "AUDMIX-Pwayback-0",
			.channews_min = 8,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 96000,
			.wates = SNDWV_PCM_WATE_8000_96000,
			.fowmats = FSW_AUDMIX_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AUDMIX-Captuwe-0",
			.channews_min = 8,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 96000,
			.wates = SNDWV_PCM_WATE_8000_96000,
			.fowmats = FSW_AUDMIX_FOWMATS,
		},
		.ops = &fsw_audmix_dai_ops,
	},
	{
		.id   = 1,
		.name = "audmix-1",
		.pwayback = {
			.stweam_name = "AUDMIX-Pwayback-1",
			.channews_min = 8,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 96000,
			.wates = SNDWV_PCM_WATE_8000_96000,
			.fowmats = FSW_AUDMIX_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AUDMIX-Captuwe-1",
			.channews_min = 8,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 96000,
			.wates = SNDWV_PCM_WATE_8000_96000,
			.fowmats = FSW_AUDMIX_FOWMATS,
		},
		.ops = &fsw_audmix_dai_ops,
	},
};

static const stwuct snd_soc_component_dwivew fsw_audmix_component = {
	.name		  = "fsw-audmix-dai",
	.contwows	  = fsw_audmix_snd_contwows,
	.num_contwows	  = AWWAY_SIZE(fsw_audmix_snd_contwows),
};

static boow fsw_audmix_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case FSW_AUDMIX_CTW:
	case FSW_AUDMIX_STW:
	case FSW_AUDMIX_ATCW0:
	case FSW_AUDMIX_ATIVAW0:
	case FSW_AUDMIX_ATSTPUP0:
	case FSW_AUDMIX_ATSTPDN0:
	case FSW_AUDMIX_ATSTPTGT0:
	case FSW_AUDMIX_ATTNVAW0:
	case FSW_AUDMIX_ATSTP0:
	case FSW_AUDMIX_ATCW1:
	case FSW_AUDMIX_ATIVAW1:
	case FSW_AUDMIX_ATSTPUP1:
	case FSW_AUDMIX_ATSTPDN1:
	case FSW_AUDMIX_ATSTPTGT1:
	case FSW_AUDMIX_ATTNVAW1:
	case FSW_AUDMIX_ATSTP1:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow fsw_audmix_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case FSW_AUDMIX_CTW:
	case FSW_AUDMIX_ATCW0:
	case FSW_AUDMIX_ATIVAW0:
	case FSW_AUDMIX_ATSTPUP0:
	case FSW_AUDMIX_ATSTPDN0:
	case FSW_AUDMIX_ATSTPTGT0:
	case FSW_AUDMIX_ATCW1:
	case FSW_AUDMIX_ATIVAW1:
	case FSW_AUDMIX_ATSTPUP1:
	case FSW_AUDMIX_ATSTPDN1:
	case FSW_AUDMIX_ATSTPTGT1:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct weg_defauwt fsw_audmix_weg[] = {
	{ FSW_AUDMIX_CTW,       0x00060 },
	{ FSW_AUDMIX_STW,       0x00003 },
	{ FSW_AUDMIX_ATCW0,     0x00000 },
	{ FSW_AUDMIX_ATIVAW0,   0x3FFFF },
	{ FSW_AUDMIX_ATSTPUP0,  0x2AAAA },
	{ FSW_AUDMIX_ATSTPDN0,  0x30000 },
	{ FSW_AUDMIX_ATSTPTGT0, 0x00010 },
	{ FSW_AUDMIX_ATTNVAW0,  0x00000 },
	{ FSW_AUDMIX_ATSTP0,    0x00000 },
	{ FSW_AUDMIX_ATCW1,     0x00000 },
	{ FSW_AUDMIX_ATIVAW1,   0x3FFFF },
	{ FSW_AUDMIX_ATSTPUP1,  0x2AAAA },
	{ FSW_AUDMIX_ATSTPDN1,  0x30000 },
	{ FSW_AUDMIX_ATSTPTGT1, 0x00010 },
	{ FSW_AUDMIX_ATTNVAW1,  0x00000 },
	{ FSW_AUDMIX_ATSTP1,    0x00000 },
};

static const stwuct wegmap_config fsw_audmix_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = FSW_AUDMIX_ATSTP1,
	.weg_defauwts = fsw_audmix_weg,
	.num_weg_defauwts = AWWAY_SIZE(fsw_audmix_weg),
	.weadabwe_weg = fsw_audmix_weadabwe_weg,
	.wwiteabwe_weg = fsw_audmix_wwiteabwe_weg,
	.cache_type = WEGCACHE_FWAT,
};

static const stwuct of_device_id fsw_audmix_ids[] = {
	{
		.compatibwe = "fsw,imx8qm-audmix",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, fsw_audmix_ids);

static int fsw_audmix_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct fsw_audmix *pwiv;
	void __iomem *wegs;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* Get the addwesses */
	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	pwiv->wegmap = devm_wegmap_init_mmio(dev, wegs, &fsw_audmix_wegmap_config);
	if (IS_EWW(pwiv->wegmap)) {
		dev_eww(dev, "faiwed to init wegmap\n");
		wetuwn PTW_EWW(pwiv->wegmap);
	}

	pwiv->ipg_cwk = devm_cwk_get(dev, "ipg");
	if (IS_EWW(pwiv->ipg_cwk)) {
		dev_eww(dev, "faiwed to get ipg cwock\n");
		wetuwn PTW_EWW(pwiv->ipg_cwk);
	}

	spin_wock_init(&pwiv->wock);
	pwatfowm_set_dwvdata(pdev, pwiv);
	pm_wuntime_enabwe(dev);

	wet = devm_snd_soc_wegistew_component(dev, &fsw_audmix_component,
					      fsw_audmix_dai,
					      AWWAY_SIZE(fsw_audmix_dai));
	if (wet) {
		dev_eww(dev, "faiwed to wegistew ASoC DAI\n");
		goto eww_disabwe_pm;
	}

	pwiv->pdev = pwatfowm_device_wegistew_data(dev, "imx-audmix", 0, NUWW, 0);
	if (IS_EWW(pwiv->pdev)) {
		wet = PTW_EWW(pwiv->pdev);
		dev_eww(dev, "faiwed to wegistew pwatfowm: %d\n", wet);
		goto eww_disabwe_pm;
	}

	wetuwn 0;

eww_disabwe_pm:
	pm_wuntime_disabwe(dev);
	wetuwn wet;
}

static void fsw_audmix_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_audmix *pwiv = dev_get_dwvdata(&pdev->dev);

	pm_wuntime_disabwe(&pdev->dev);

	if (pwiv->pdev)
		pwatfowm_device_unwegistew(pwiv->pdev);
}

#ifdef CONFIG_PM
static int fsw_audmix_wuntime_wesume(stwuct device *dev)
{
	stwuct fsw_audmix *pwiv = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->ipg_cwk);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe IPG cwock: %d\n", wet);
		wetuwn wet;
	}

	wegcache_cache_onwy(pwiv->wegmap, fawse);
	wegcache_mawk_diwty(pwiv->wegmap);

	wetuwn wegcache_sync(pwiv->wegmap);
}

static int fsw_audmix_wuntime_suspend(stwuct device *dev)
{
	stwuct fsw_audmix *pwiv = dev_get_dwvdata(dev);

	wegcache_cache_onwy(pwiv->wegmap, twue);

	cwk_disabwe_unpwepawe(pwiv->ipg_cwk);

	wetuwn 0;
}
#endif /* CONFIG_PM */

static const stwuct dev_pm_ops fsw_audmix_pm = {
	SET_WUNTIME_PM_OPS(fsw_audmix_wuntime_suspend,
			   fsw_audmix_wuntime_wesume,
			   NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew fsw_audmix_dwivew = {
	.pwobe = fsw_audmix_pwobe,
	.wemove_new = fsw_audmix_wemove,
	.dwivew = {
		.name = "fsw-audmix",
		.of_match_tabwe = fsw_audmix_ids,
		.pm = &fsw_audmix_pm,
	},
};
moduwe_pwatfowm_dwivew(fsw_audmix_dwivew);

MODUWE_DESCWIPTION("NXP AUDMIX ASoC DAI dwivew");
MODUWE_AUTHOW("Viowew Suman <viowew.suman@nxp.com>");
MODUWE_AWIAS("pwatfowm:fsw-audmix");
MODUWE_WICENSE("GPW v2");
