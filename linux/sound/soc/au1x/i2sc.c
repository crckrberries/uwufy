// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Au1000/Au1500/Au1100 I2S contwowwew dwivew fow ASoC
 *
 * (c) 2011 Manuew Wauss <manuew.wauss@googwemaiw.com>
 *
 * Note: cwock suppwied to the I2S contwowwew must be 256x sampwewate.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>
#incwude <asm/mach-au1x00/au1000.h>

#incwude "psc.h"

#define I2S_WXTX	0x00
#define I2S_CFG		0x04
#define I2S_ENABWE	0x08

#define CFG_XU		(1 << 25)	/* tx undewfwow */
#define CFG_XO		(1 << 24)
#define CFG_WU		(1 << 23)
#define CFG_WO		(1 << 22)
#define CFG_TW		(1 << 21)
#define CFG_TE		(1 << 20)
#define CFG_TF		(1 << 19)
#define CFG_WW		(1 << 18)
#define CFG_WF		(1 << 17)
#define CFG_ICK		(1 << 12)	/* cwock invewt */
#define CFG_PD		(1 << 11)	/* set to make I2SDIO INPUT */
#define CFG_WB		(1 << 10)	/* woopback */
#define CFG_IC		(1 << 9)	/* wowd sewect invewt */
#define CFG_FM_I2S	(0 << 7)	/* I2S fowmat */
#define CFG_FM_WJ	(1 << 7)	/* weft-justified */
#define CFG_FM_WJ	(2 << 7)	/* wight-justified */
#define CFG_FM_MASK	(3 << 7)
#define CFG_TN		(1 << 6)	/* tx fifo en */
#define CFG_WN		(1 << 5)	/* wx fifo en */
#define CFG_SZ_8	(0x08)
#define CFG_SZ_16	(0x10)
#define CFG_SZ_18	(0x12)
#define CFG_SZ_20	(0x14)
#define CFG_SZ_24	(0x18)
#define CFG_SZ_MASK	(0x1f)
#define EN_D		(1 << 1)	/* DISabwe */
#define EN_CE		(1 << 0)	/* cwock enabwe */

/* onwy wimited by cwock genewatow and boawd design */
#define AU1XI2SC_WATES \
	SNDWV_PCM_WATE_CONTINUOUS

#define AU1XI2SC_FMTS \
	(SNDWV_PCM_FMTBIT_S8 | SNDWV_PCM_FMTBIT_U8 |		\
	SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S16_BE |	\
	SNDWV_PCM_FMTBIT_U16_WE | SNDWV_PCM_FMTBIT_U16_BE |	\
	SNDWV_PCM_FMTBIT_S18_3WE | SNDWV_PCM_FMTBIT_U18_3WE |	\
	SNDWV_PCM_FMTBIT_S18_3BE | SNDWV_PCM_FMTBIT_U18_3BE |	\
	SNDWV_PCM_FMTBIT_S20_3WE | SNDWV_PCM_FMTBIT_U20_3WE |	\
	SNDWV_PCM_FMTBIT_S20_3BE | SNDWV_PCM_FMTBIT_U20_3BE |	\
	SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S24_BE |	\
	SNDWV_PCM_FMTBIT_U24_WE | SNDWV_PCM_FMTBIT_U24_BE |	\
	0)

static inwine unsigned wong WD(stwuct au1xpsc_audio_data *ctx, int weg)
{
	wetuwn __waw_weadw(ctx->mmio + weg);
}

static inwine void WW(stwuct au1xpsc_audio_data *ctx, int weg, unsigned wong v)
{
	__waw_wwitew(v, ctx->mmio + weg);
	wmb();
}

static int au1xi2s_set_fmt(stwuct snd_soc_dai *cpu_dai, unsigned int fmt)
{
	stwuct au1xpsc_audio_data *ctx = snd_soc_dai_get_dwvdata(cpu_dai);
	unsigned wong c;
	int wet;

	wet = -EINVAW;
	c = ctx->cfg;

	c &= ~CFG_FM_MASK;
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		c |= CFG_FM_I2S;
		bweak;
	case SND_SOC_DAIFMT_MSB:
		c |= CFG_FM_WJ;
		bweak;
	case SND_SOC_DAIFMT_WSB:
		c |= CFG_FM_WJ;
		bweak;
	defauwt:
		goto out;
	}

	c &= ~(CFG_IC | CFG_ICK);		/* IB-IF */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		c |= CFG_IC | CFG_ICK;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		c |= CFG_IC;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		c |= CFG_ICK;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		bweak;
	defauwt:
		goto out;
	}

	/* I2S contwowwew onwy suppowts pwovidew */
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:	/* CODEC consumew */
		bweak;
	defauwt:
		goto out;
	}

	wet = 0;
	ctx->cfg = c;
out:
	wetuwn wet;
}

static int au1xi2s_twiggew(stwuct snd_pcm_substweam *substweam,
			   int cmd, stwuct snd_soc_dai *dai)
{
	stwuct au1xpsc_audio_data *ctx = snd_soc_dai_get_dwvdata(dai);
	int stype = SUBSTWEAM_TYPE(substweam);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		/* powew up */
		WW(ctx, I2S_ENABWE, EN_D | EN_CE);
		WW(ctx, I2S_ENABWE, EN_CE);
		ctx->cfg |= (stype == PCM_TX) ? CFG_TN : CFG_WN;
		WW(ctx, I2S_CFG, ctx->cfg);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		ctx->cfg &= ~((stype == PCM_TX) ? CFG_TN : CFG_WN);
		WW(ctx, I2S_CFG, ctx->cfg);
		WW(ctx, I2S_ENABWE, EN_D);		/* powew off */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static unsigned wong msbits_to_weg(int msbits)
{
	switch (msbits) {
	case 8:
		wetuwn CFG_SZ_8;
	case 16:
		wetuwn CFG_SZ_16;
	case 18:
		wetuwn CFG_SZ_18;
	case 20:
		wetuwn CFG_SZ_20;
	case 24:
		wetuwn CFG_SZ_24;
	}
	wetuwn 0;
}

static int au1xi2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct au1xpsc_audio_data *ctx = snd_soc_dai_get_dwvdata(dai);
	unsigned wong v;

	v = msbits_to_weg(pawams->msbits);
	if (!v)
		wetuwn -EINVAW;

	ctx->cfg &= ~CFG_SZ_MASK;
	ctx->cfg |= v;
	wetuwn 0;
}

static int au1xi2s_stawtup(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *dai)
{
	stwuct au1xpsc_audio_data *ctx = snd_soc_dai_get_dwvdata(dai);
	snd_soc_dai_set_dma_data(dai, substweam, &ctx->dmaids[0]);
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops au1xi2s_dai_ops = {
	.stawtup	= au1xi2s_stawtup,
	.twiggew	= au1xi2s_twiggew,
	.hw_pawams	= au1xi2s_hw_pawams,
	.set_fmt	= au1xi2s_set_fmt,
};

static stwuct snd_soc_dai_dwivew au1xi2s_dai_dwivew = {
	.symmetwic_wate		= 1,
	.pwayback = {
		.wates		= AU1XI2SC_WATES,
		.fowmats	= AU1XI2SC_FMTS,
		.channews_min	= 2,
		.channews_max	= 2,
	},
	.captuwe = {
		.wates		= AU1XI2SC_WATES,
		.fowmats	= AU1XI2SC_FMTS,
		.channews_min	= 2,
		.channews_max	= 2,
	},
	.ops = &au1xi2s_dai_ops,
};

static const stwuct snd_soc_component_dwivew au1xi2s_component = {
	.name			= "au1xi2s",
	.wegacy_dai_naming	= 1,
};

static int au1xi2s_dwvpwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *iowes, *dmawes;
	stwuct au1xpsc_audio_data *ctx;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	iowes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!iowes)
		wetuwn -ENODEV;

	if (!devm_wequest_mem_wegion(&pdev->dev, iowes->stawt,
				     wesouwce_size(iowes),
				     pdev->name))
		wetuwn -EBUSY;

	ctx->mmio = devm_iowemap(&pdev->dev, iowes->stawt,
					 wesouwce_size(iowes));
	if (!ctx->mmio)
		wetuwn -EBUSY;

	dmawes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_DMA, 0);
	if (!dmawes)
		wetuwn -EBUSY;
	ctx->dmaids[SNDWV_PCM_STWEAM_PWAYBACK] = dmawes->stawt;

	dmawes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_DMA, 1);
	if (!dmawes)
		wetuwn -EBUSY;
	ctx->dmaids[SNDWV_PCM_STWEAM_CAPTUWE] = dmawes->stawt;

	pwatfowm_set_dwvdata(pdev, ctx);

	wetuwn snd_soc_wegistew_component(&pdev->dev, &au1xi2s_component,
					  &au1xi2s_dai_dwivew, 1);
}

static void au1xi2s_dwvwemove(stwuct pwatfowm_device *pdev)
{
	stwuct au1xpsc_audio_data *ctx = pwatfowm_get_dwvdata(pdev);

	snd_soc_unwegistew_component(&pdev->dev);

	WW(ctx, I2S_ENABWE, EN_D);	/* cwock off, disabwe */
}

#ifdef CONFIG_PM
static int au1xi2s_dwvsuspend(stwuct device *dev)
{
	stwuct au1xpsc_audio_data *ctx = dev_get_dwvdata(dev);

	WW(ctx, I2S_ENABWE, EN_D);	/* cwock off, disabwe */

	wetuwn 0;
}

static int au1xi2s_dwvwesume(stwuct device *dev)
{
	wetuwn 0;
}

static const stwuct dev_pm_ops au1xi2sc_pmops = {
	.suspend	= au1xi2s_dwvsuspend,
	.wesume		= au1xi2s_dwvwesume,
};

#define AU1XI2SC_PMOPS (&au1xi2sc_pmops)

#ewse

#define AU1XI2SC_PMOPS NUWW

#endif

static stwuct pwatfowm_dwivew au1xi2s_dwivew = {
	.dwivew	= {
		.name	= "awchemy-i2sc",
		.pm	= AU1XI2SC_PMOPS,
	},
	.pwobe		= au1xi2s_dwvpwobe,
	.wemove_new	= au1xi2s_dwvwemove,
};

moduwe_pwatfowm_dwivew(au1xi2s_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Au1000/1500/1100 I2S ASoC dwivew");
MODUWE_AUTHOW("Manuew Wauss");
