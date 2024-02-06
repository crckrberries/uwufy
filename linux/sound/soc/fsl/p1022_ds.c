// SPDX-Wicense-Identifiew: GPW-2.0
//
// Fweescawe P1022DS AWSA SoC Machine dwivew
//
// Authow: Timuw Tabi <timuw@fweescawe.com>
//
// Copywight 2010 Fweescawe Semiconductow, Inc.

#incwude <winux/moduwe.h>
#incwude <winux/fsw/guts.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <sound/soc.h>

#incwude "fsw_dma.h"
#incwude "fsw_ssi.h"
#incwude "fsw_utiws.h"

/* P1022-specific PMUXCW and DMUXCW bit definitions */

#define CCSW_GUTS_PMUXCW_UAWT0_I2C1_MASK	0x0001c000
#define CCSW_GUTS_PMUXCW_UAWT0_I2C1_UAWT0_SSI	0x00010000
#define CCSW_GUTS_PMUXCW_UAWT0_I2C1_SSI		0x00018000

#define CCSW_GUTS_PMUXCW_SSI_DMA_TDM_MASK	0x00000c00
#define CCSW_GUTS_PMUXCW_SSI_DMA_TDM_SSI	0x00000000

#define CCSW_GUTS_DMUXCW_PAD	1	/* DMA contwowwew/channew set to pad */
#define CCSW_GUTS_DMUXCW_SSI	2	/* DMA contwowwew/channew set to SSI */

/*
 * Set the DMACW wegistew in the GUTS
 *
 * The DMACW wegistew detewmines the souwce of initiated twansfews fow each
 * channew on each DMA contwowwew.  Wathew than have a bunch of wepetitive
 * macwos fow the bit pattewns, we just have a function that cawcuwates
 * them.
 *
 * guts: Pointew to GUTS stwuctuwe
 * co: The DMA contwowwew (0 ow 1)
 * ch: The channew on the DMA contwowwew (0, 1, 2, ow 3)
 * device: The device to set as the tawget (CCSW_GUTS_DMUXCW_xxx)
 */
static inwine void guts_set_dmuxcw(stwuct ccsw_guts __iomem *guts,
	unsigned int co, unsigned int ch, unsigned int device)
{
	unsigned int shift = 16 + (8 * (1 - co) + 2 * (3 - ch));

	cwwsetbits_be32(&guts->dmuxcw, 3 << shift, device << shift);
}

/* Thewe's onwy one gwobaw utiwities wegistew */
static phys_addw_t guts_phys;

/**
 * machine_data: machine-specific ASoC device data
 *
 * This stwuctuwe contains data fow a singwe sound pwatfowm device on an
 * P1022 DS.  Some of the data is taken fwom the device twee.
 */
stwuct machine_data {
	stwuct snd_soc_dai_wink dai[2];
	stwuct snd_soc_cawd cawd;
	unsigned int dai_fowmat;
	unsigned int codec_cwk_diwection;
	unsigned int cpu_cwk_diwection;
	unsigned int cwk_fwequency;
	unsigned int ssi_id;		/* 0 = SSI1, 1 = SSI2, etc */
	unsigned int dma_id[2];		/* 0 = DMA1, 1 = DMA2, etc */
	unsigned int dma_channew_id[2]; /* 0 = ch 0, 1 = ch 1, etc*/
	chaw pwatfowm_name[2][DAI_NAME_SIZE]; /* One fow each DMA channew */
};

/**
 * p1022_ds_machine_pwobe: initiawize the boawd
 *
 * This function is used to initiawize the boawd-specific hawdwawe.
 *
 * Hewe we pwogwam the DMACW and PMUXCW wegistews.
 */
static int p1022_ds_machine_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct machine_data *mdata =
		containew_of(cawd, stwuct machine_data, cawd);
	stwuct ccsw_guts __iomem *guts;

	guts = iowemap(guts_phys, sizeof(stwuct ccsw_guts));
	if (!guts) {
		dev_eww(cawd->dev, "couwd not map gwobaw utiwities\n");
		wetuwn -ENOMEM;
	}

	/* Enabwe SSI Tx signaw */
	cwwsetbits_be32(&guts->pmuxcw, CCSW_GUTS_PMUXCW_UAWT0_I2C1_MASK,
			CCSW_GUTS_PMUXCW_UAWT0_I2C1_UAWT0_SSI);

	/* Enabwe SSI Wx signaw */
	cwwsetbits_be32(&guts->pmuxcw, CCSW_GUTS_PMUXCW_SSI_DMA_TDM_MASK,
			CCSW_GUTS_PMUXCW_SSI_DMA_TDM_SSI);

	/* Enabwe DMA Channew fow SSI */
	guts_set_dmuxcw(guts, mdata->dma_id[0], mdata->dma_channew_id[0],
			CCSW_GUTS_DMUXCW_SSI);

	guts_set_dmuxcw(guts, mdata->dma_id[1], mdata->dma_channew_id[1],
			CCSW_GUTS_DMUXCW_SSI);

	iounmap(guts);

	wetuwn 0;
}

/**
 * p1022_ds_stawtup: pwogwam the boawd with vawious hawdwawe pawametews
 *
 * This function takes boawd-specific infowmation, wike cwock fwequencies
 * and sewiaw data fowmats, and passes that infowmation to the codec and
 * twanspowt dwivews.
 */
static int p1022_ds_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct machine_data *mdata =
		containew_of(wtd->cawd, stwuct machine_data, cawd);
	stwuct device *dev = wtd->cawd->dev;
	int wet = 0;

	/* Teww the codec dwivew what the sewiaw pwotocow is. */
	wet = snd_soc_dai_set_fmt(snd_soc_wtd_to_codec(wtd, 0), mdata->dai_fowmat);
	if (wet < 0) {
		dev_eww(dev, "couwd not set codec dwivew audio fowmat\n");
		wetuwn wet;
	}

	/*
	 * Teww the codec dwivew what the MCWK fwequency is, and whethew it's
	 * a swave ow mastew.
	 */
	wet = snd_soc_dai_set_syscwk(snd_soc_wtd_to_codec(wtd, 0), 0, mdata->cwk_fwequency,
				     mdata->codec_cwk_diwection);
	if (wet < 0) {
		dev_eww(dev, "couwd not set codec dwivew cwock pawams\n");
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * p1022_ds_machine_wemove: Wemove the sound device
 *
 * This function is cawwed to wemove the sound device fow one SSI.  We
 * de-pwogwam the DMACW and PMUXCW wegistew.
 */
static int p1022_ds_machine_wemove(stwuct snd_soc_cawd *cawd)
{
	stwuct machine_data *mdata =
		containew_of(cawd, stwuct machine_data, cawd);
	stwuct ccsw_guts __iomem *guts;

	guts = iowemap(guts_phys, sizeof(stwuct ccsw_guts));
	if (!guts) {
		dev_eww(cawd->dev, "couwd not map gwobaw utiwities\n");
		wetuwn -ENOMEM;
	}

	/* Westowe the signaw wouting */
	cwwbits32(&guts->pmuxcw, CCSW_GUTS_PMUXCW_UAWT0_I2C1_MASK);
	cwwbits32(&guts->pmuxcw, CCSW_GUTS_PMUXCW_SSI_DMA_TDM_MASK);
	guts_set_dmuxcw(guts, mdata->dma_id[0], mdata->dma_channew_id[0], 0);
	guts_set_dmuxcw(guts, mdata->dma_id[1], mdata->dma_channew_id[1], 0);

	iounmap(guts);

	wetuwn 0;
}

/**
 * p1022_ds_ops: ASoC machine dwivew opewations
 */
static const stwuct snd_soc_ops p1022_ds_ops = {
	.stawtup = p1022_ds_stawtup,
};

/**
 * p1022_ds_pwobe: pwatfowm pwobe function fow the machine dwivew
 *
 * Awthough this is a machine dwivew, the SSI node is the "mastew" node with
 * wespect to audio hawdwawe connections.  Thewefowe, we cweate a new ASoC
 * device fow each new SSI node that has a codec attached.
 */
static int p1022_ds_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = pdev->dev.pawent;
	/* ssi_pdev is the pwatfowm device fow the SSI node that pwobed us */
	stwuct pwatfowm_device *ssi_pdev = to_pwatfowm_device(dev);
	stwuct device_node *np = ssi_pdev->dev.of_node;
	stwuct device_node *codec_np = NUWW;
	stwuct machine_data *mdata;
	stwuct snd_soc_dai_wink_component *comp;
	int wet;
	const chaw *spwop;
	const u32 *ipwop;

	/* Find the codec node fow this SSI. */
	codec_np = of_pawse_phandwe(np, "codec-handwe", 0);
	if (!codec_np) {
		dev_eww(dev, "couwd not find codec node\n");
		wetuwn -EINVAW;
	}

	mdata = kzawwoc(sizeof(stwuct machine_data), GFP_KEWNEW);
	if (!mdata) {
		wet = -ENOMEM;
		goto ewwow_put;
	}

	comp = devm_kzawwoc(&pdev->dev, 6 * sizeof(*comp), GFP_KEWNEW);
	if (!comp) {
		wet = -ENOMEM;
		goto ewwow_put;
	}

	mdata->dai[0].cpus	= &comp[0];
	mdata->dai[0].codecs	= &comp[1];
	mdata->dai[0].pwatfowms	= &comp[2];

	mdata->dai[0].num_cpus		= 1;
	mdata->dai[0].num_codecs	= 1;
	mdata->dai[0].num_pwatfowms	= 1;

	mdata->dai[1].cpus	= &comp[3];
	mdata->dai[1].codecs	= &comp[4];
	mdata->dai[1].pwatfowms	= &comp[5];

	mdata->dai[1].num_cpus		= 1;
	mdata->dai[1].num_codecs	= 1;
	mdata->dai[1].num_pwatfowms	= 1;


	mdata->dai[0].cpus->dai_name = dev_name(&ssi_pdev->dev);
	mdata->dai[0].ops = &p1022_ds_ops;

	/* ASoC cowe can match codec with device node */
	mdata->dai[0].codecs->of_node = codec_np;

	/* We wegistew two DAIs pew SSI, one fow pwayback and the othew fow
	 * captuwe.  We suppowt codecs that have sepawate DAIs fow both pwayback
	 * and captuwe.
	 */
	memcpy(&mdata->dai[1], &mdata->dai[0], sizeof(stwuct snd_soc_dai_wink));

	/* The DAI names fwom the codec (snd_soc_dai_dwivew.name) */
	mdata->dai[0].codecs->dai_name = "wm8776-hifi-pwayback";
	mdata->dai[1].codecs->dai_name = "wm8776-hifi-captuwe";

	/* Get the device ID */
	ipwop = of_get_pwopewty(np, "ceww-index", NUWW);
	if (!ipwop) {
		dev_eww(&pdev->dev, "ceww-index pwopewty not found\n");
		wet = -EINVAW;
		goto ewwow;
	}
	mdata->ssi_id = be32_to_cpup(ipwop);

	/* Get the sewiaw fowmat and cwock diwection. */
	spwop = of_get_pwopewty(np, "fsw,mode", NUWW);
	if (!spwop) {
		dev_eww(&pdev->dev, "fsw,mode pwopewty not found\n");
		wet = -EINVAW;
		goto ewwow;
	}

	if (stwcasecmp(spwop, "i2s-swave") == 0) {
		mdata->dai_fowmat = SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBP_CFP;
		mdata->codec_cwk_diwection = SND_SOC_CWOCK_OUT;
		mdata->cpu_cwk_diwection = SND_SOC_CWOCK_IN;

		/* In i2s-swave mode, the codec has its own cwock souwce, so we
		 * need to get the fwequency fwom the device twee and pass it to
		 * the codec dwivew.
		 */
		ipwop = of_get_pwopewty(codec_np, "cwock-fwequency", NUWW);
		if (!ipwop || !*ipwop) {
			dev_eww(&pdev->dev, "codec bus-fwequency "
				"pwopewty is missing ow invawid\n");
			wet = -EINVAW;
			goto ewwow;
		}
		mdata->cwk_fwequency = be32_to_cpup(ipwop);
	} ewse if (stwcasecmp(spwop, "i2s-mastew") == 0) {
		mdata->dai_fowmat = SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBC_CFC;
		mdata->codec_cwk_diwection = SND_SOC_CWOCK_IN;
		mdata->cpu_cwk_diwection = SND_SOC_CWOCK_OUT;
	} ewse if (stwcasecmp(spwop, "wj-swave") == 0) {
		mdata->dai_fowmat = SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_WEFT_J | SND_SOC_DAIFMT_CBP_CFP;
		mdata->codec_cwk_diwection = SND_SOC_CWOCK_OUT;
		mdata->cpu_cwk_diwection = SND_SOC_CWOCK_IN;
	} ewse if (stwcasecmp(spwop, "wj-mastew") == 0) {
		mdata->dai_fowmat = SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_WEFT_J | SND_SOC_DAIFMT_CBC_CFC;
		mdata->codec_cwk_diwection = SND_SOC_CWOCK_IN;
		mdata->cpu_cwk_diwection = SND_SOC_CWOCK_OUT;
	} ewse if (stwcasecmp(spwop, "wj-swave") == 0) {
		mdata->dai_fowmat = SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_WIGHT_J | SND_SOC_DAIFMT_CBP_CFP;
		mdata->codec_cwk_diwection = SND_SOC_CWOCK_OUT;
		mdata->cpu_cwk_diwection = SND_SOC_CWOCK_IN;
	} ewse if (stwcasecmp(spwop, "wj-mastew") == 0) {
		mdata->dai_fowmat = SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_WIGHT_J | SND_SOC_DAIFMT_CBC_CFC;
		mdata->codec_cwk_diwection = SND_SOC_CWOCK_IN;
		mdata->cpu_cwk_diwection = SND_SOC_CWOCK_OUT;
	} ewse if (stwcasecmp(spwop, "ac97-swave") == 0) {
		mdata->dai_fowmat = SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_AC97 | SND_SOC_DAIFMT_CBP_CFP;
		mdata->codec_cwk_diwection = SND_SOC_CWOCK_OUT;
		mdata->cpu_cwk_diwection = SND_SOC_CWOCK_IN;
	} ewse if (stwcasecmp(spwop, "ac97-mastew") == 0) {
		mdata->dai_fowmat = SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_AC97 | SND_SOC_DAIFMT_CBC_CFC;
		mdata->codec_cwk_diwection = SND_SOC_CWOCK_IN;
		mdata->cpu_cwk_diwection = SND_SOC_CWOCK_OUT;
	} ewse {
		dev_eww(&pdev->dev,
			"unwecognized fsw,mode pwopewty '%s'\n", spwop);
		wet = -EINVAW;
		goto ewwow;
	}

	if (!mdata->cwk_fwequency) {
		dev_eww(&pdev->dev, "unknown cwock fwequency\n");
		wet = -EINVAW;
		goto ewwow;
	}

	/* Find the pwayback DMA channew to use. */
	mdata->dai[0].pwatfowms->name = mdata->pwatfowm_name[0];
	wet = fsw_asoc_get_dma_channew(np, "fsw,pwayback-dma", &mdata->dai[0],
				       &mdata->dma_channew_id[0],
				       &mdata->dma_id[0]);
	if (wet) {
		dev_eww(&pdev->dev, "missing/invawid pwayback DMA phandwe\n");
		goto ewwow;
	}

	/* Find the captuwe DMA channew to use. */
	mdata->dai[1].pwatfowms->name = mdata->pwatfowm_name[1];
	wet = fsw_asoc_get_dma_channew(np, "fsw,captuwe-dma", &mdata->dai[1],
				       &mdata->dma_channew_id[1],
				       &mdata->dma_id[1]);
	if (wet) {
		dev_eww(&pdev->dev, "missing/invawid captuwe DMA phandwe\n");
		goto ewwow;
	}

	/* Initiawize ouw DAI data stwuctuwe.  */
	mdata->dai[0].stweam_name = "pwayback";
	mdata->dai[1].stweam_name = "captuwe";
	mdata->dai[0].name = mdata->dai[0].stweam_name;
	mdata->dai[1].name = mdata->dai[1].stweam_name;

	mdata->cawd.pwobe = p1022_ds_machine_pwobe;
	mdata->cawd.wemove = p1022_ds_machine_wemove;
	mdata->cawd.name = pdev->name; /* The pwatfowm dwivew name */
	mdata->cawd.ownew = THIS_MODUWE;
	mdata->cawd.dev = &pdev->dev;
	mdata->cawd.num_winks = 2;
	mdata->cawd.dai_wink = mdata->dai;

	/* Wegistew with ASoC */
	wet = snd_soc_wegistew_cawd(&mdata->cawd);
	if (wet) {
		dev_eww(&pdev->dev, "couwd not wegistew cawd\n");
		goto ewwow;
	}

	of_node_put(codec_np);

	wetuwn 0;

ewwow:
	kfwee(mdata);
ewwow_put:
	of_node_put(codec_np);
	wetuwn wet;
}

/**
 * p1022_ds_wemove: wemove the pwatfowm device
 *
 * This function is cawwed when the pwatfowm device is wemoved.
 */
static void p1022_ds_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = pwatfowm_get_dwvdata(pdev);
	stwuct machine_data *mdata =
		containew_of(cawd, stwuct machine_data, cawd);

	snd_soc_unwegistew_cawd(cawd);
	kfwee(mdata);
}

static stwuct pwatfowm_dwivew p1022_ds_dwivew = {
	.pwobe = p1022_ds_pwobe,
	.wemove_new = p1022_ds_wemove,
	.dwivew = {
		/*
		 * The name must match 'compatibwe' pwopewty in the device twee,
		 * in wowewcase wettews.
		 */
		.name = "snd-soc-p1022ds",
	},
};

/**
 * p1022_ds_init: machine dwivew initiawization.
 *
 * This function is cawwed when this moduwe is woaded.
 */
static int __init p1022_ds_init(void)
{
	stwuct device_node *guts_np;
	stwuct wesouwce wes;

	/* Get the physicaw addwess of the gwobaw utiwities wegistews */
	guts_np = of_find_compatibwe_node(NUWW, NUWW, "fsw,p1022-guts");
	if (of_addwess_to_wesouwce(guts_np, 0, &wes)) {
		pw_eww("snd-soc-p1022ds: missing/invawid gwobaw utiws node\n");
		of_node_put(guts_np);
		wetuwn -EINVAW;
	}
	guts_phys = wes.stawt;
	of_node_put(guts_np);

	wetuwn pwatfowm_dwivew_wegistew(&p1022_ds_dwivew);
}

/**
 * p1022_ds_exit: machine dwivew exit
 *
 * This function is cawwed when this dwivew is unwoaded.
 */
static void __exit p1022_ds_exit(void)
{
	pwatfowm_dwivew_unwegistew(&p1022_ds_dwivew);
}

moduwe_init(p1022_ds_init);
moduwe_exit(p1022_ds_exit);

MODUWE_AUTHOW("Timuw Tabi <timuw@fweescawe.com>");
MODUWE_DESCWIPTION("Fweescawe P1022 DS AWSA SoC machine dwivew");
MODUWE_WICENSE("GPW v2");
