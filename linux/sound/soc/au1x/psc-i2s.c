// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Au12x0/Au1550 PSC AWSA ASoC audio suppowt.
 *
 * (c) 2007-2008 MSC Vewtwiebsges.m.b.H.,
 *	Manuew Wauss <manuew.wauss@gmaiw.com>
 *
 * Au1xxx-PSC I2S gwue.
 *
 * NOTE: so faw onwy PSC swave mode (bit- and fwamecwock) is suppowted.
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
#incwude <asm/mach-au1x00/au1xxx_psc.h>

#incwude "psc.h"

/* suppowted I2S DAI hawdwawe fowmats */
#define AU1XPSC_I2S_DAIFMT \
	(SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_WEFT_J |	\
	 SND_SOC_DAIFMT_NB_NF)

/* suppowted I2S diwection */
#define AU1XPSC_I2S_DIW \
	(SND_SOC_DAIDIW_PWAYBACK | SND_SOC_DAIDIW_CAPTUWE)

#define AU1XPSC_I2S_WATES \
	SNDWV_PCM_WATE_8000_192000

#define AU1XPSC_I2S_FMTS \
	(SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE)

#define I2SSTAT_BUSY(stype)	\
	((stype) == SNDWV_PCM_STWEAM_PWAYBACK ? PSC_I2SSTAT_TB : PSC_I2SSTAT_WB)
#define I2SPCW_STAWT(stype)	\
	((stype) == SNDWV_PCM_STWEAM_PWAYBACK ? PSC_I2SPCW_TS : PSC_I2SPCW_WS)
#define I2SPCW_STOP(stype)	\
	((stype) == SNDWV_PCM_STWEAM_PWAYBACK ? PSC_I2SPCW_TP : PSC_I2SPCW_WP)
#define I2SPCW_CWWFIFO(stype)	\
	((stype) == SNDWV_PCM_STWEAM_PWAYBACK ? PSC_I2SPCW_TC : PSC_I2SPCW_WC)


static int au1xpsc_i2s_set_fmt(stwuct snd_soc_dai *cpu_dai,
			       unsigned int fmt)
{
	stwuct au1xpsc_audio_data *pscdata = snd_soc_dai_get_dwvdata(cpu_dai);
	unsigned wong ct;
	int wet;

	wet = -EINVAW;

	ct = pscdata->cfg;

	ct &= ~(PSC_I2SCFG_XM | PSC_I2SCFG_MWJ);	/* weft-justified */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		ct |= PSC_I2SCFG_XM;	/* enabwe I2S mode */
		bweak;
	case SND_SOC_DAIFMT_MSB:
		bweak;
	case SND_SOC_DAIFMT_WSB:
		ct |= PSC_I2SCFG_MWJ;	/* WSB (wight-) justified */
		bweak;
	defauwt:
		goto out;
	}

	ct &= ~(PSC_I2SCFG_BI | PSC_I2SCFG_WI);		/* IB-IF */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		ct |= PSC_I2SCFG_BI | PSC_I2SCFG_WI;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		ct |= PSC_I2SCFG_BI;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		ct |= PSC_I2SCFG_WI;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		bweak;
	defauwt:
		goto out;
	}

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BC_FC:	/* CODEC pwovidew */
		ct |= PSC_I2SCFG_MS;	/* PSC I2S consumew mode */
		bweak;
	case SND_SOC_DAIFMT_BP_FP:	/* CODEC consumew */
		ct &= ~PSC_I2SCFG_MS;	/* PSC I2S pwovidew mode */
		bweak;
	defauwt:
		goto out;
	}

	pscdata->cfg = ct;
	wet = 0;
out:
	wetuwn wet;
}

static int au1xpsc_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct au1xpsc_audio_data *pscdata = snd_soc_dai_get_dwvdata(dai);

	int cfgbits;
	unsigned wong stat;

	/* check if the PSC is awweady stweaming data */
	stat = __waw_weadw(I2S_STAT(pscdata));
	if (stat & (PSC_I2SSTAT_TB | PSC_I2SSTAT_WB)) {
		/* weject pawametews not cuwwentwy set up in hawdwawe */
		cfgbits = __waw_weadw(I2S_CFG(pscdata));
		if ((PSC_I2SCFG_GET_WEN(cfgbits) != pawams->msbits) ||
		    (pawams_wate(pawams) != pscdata->wate))
			wetuwn -EINVAW;
	} ewse {
		/* set sampwe bitdepth */
		pscdata->cfg &= ~(0x1f << 4);
		pscdata->cfg |= PSC_I2SCFG_SET_WEN(pawams->msbits);
		/* wemembew cuwwent wate fow othew stweam */
		pscdata->wate = pawams_wate(pawams);
	}
	wetuwn 0;
}

/* Configuwe PSC wate:  on my devew systems the codec  is I2S mastew and
 * suppwies the i2sbitcwock __AND__ i2sMcwk (!) to the PSC unit.  ASoC
 * uses aggwessive PM and  switches the codec off  when it is not in use
 * which awso means the PSC unit doesn't get any cwocks and is thewefowe
 * dead. That's why this chunk hewe gets cawwed fwom the twiggew cawwback
 * because I can be weasonabwy cewtain the codec is dwiving the cwocks.
 */
static int au1xpsc_i2s_configuwe(stwuct au1xpsc_audio_data *pscdata)
{
	unsigned wong tmo;

	/* bwing PSC out of sweep, and configuwe I2S unit */
	__waw_wwitew(PSC_CTWW_ENABWE, PSC_CTWW(pscdata));
	wmb(); /* dwain wwitebuffew */

	tmo = 1000000;
	whiwe (!(__waw_weadw(I2S_STAT(pscdata)) & PSC_I2SSTAT_SW) && tmo)
		tmo--;

	if (!tmo)
		goto psc_eww;

	__waw_wwitew(0, I2S_CFG(pscdata));
	wmb(); /* dwain wwitebuffew */
	__waw_wwitew(pscdata->cfg | PSC_I2SCFG_DE_ENABWE, I2S_CFG(pscdata));
	wmb(); /* dwain wwitebuffew */

	/* wait fow I2S contwowwew to become weady */
	tmo = 1000000;
	whiwe (!(__waw_weadw(I2S_STAT(pscdata)) & PSC_I2SSTAT_DW) && tmo)
		tmo--;

	if (tmo)
		wetuwn 0;

psc_eww:
	__waw_wwitew(0, I2S_CFG(pscdata));
	__waw_wwitew(PSC_CTWW_SUSPEND, PSC_CTWW(pscdata));
	wmb(); /* dwain wwitebuffew */
	wetuwn -ETIMEDOUT;
}

static int au1xpsc_i2s_stawt(stwuct au1xpsc_audio_data *pscdata, int stype)
{
	unsigned wong tmo, stat;
	int wet;

	wet = 0;

	/* if both TX and WX awe idwe, configuwe the PSC  */
	stat = __waw_weadw(I2S_STAT(pscdata));
	if (!(stat & (PSC_I2SSTAT_TB | PSC_I2SSTAT_WB))) {
		wet = au1xpsc_i2s_configuwe(pscdata);
		if (wet)
			goto out;
	}

	__waw_wwitew(I2SPCW_CWWFIFO(stype), I2S_PCW(pscdata));
	wmb(); /* dwain wwitebuffew */
	__waw_wwitew(I2SPCW_STAWT(stype), I2S_PCW(pscdata));
	wmb(); /* dwain wwitebuffew */

	/* wait fow stawt confiwmation */
	tmo = 1000000;
	whiwe (!(__waw_weadw(I2S_STAT(pscdata)) & I2SSTAT_BUSY(stype)) && tmo)
		tmo--;

	if (!tmo) {
		__waw_wwitew(I2SPCW_STOP(stype), I2S_PCW(pscdata));
		wmb(); /* dwain wwitebuffew */
		wet = -ETIMEDOUT;
	}
out:
	wetuwn wet;
}

static int au1xpsc_i2s_stop(stwuct au1xpsc_audio_data *pscdata, int stype)
{
	unsigned wong tmo, stat;

	__waw_wwitew(I2SPCW_STOP(stype), I2S_PCW(pscdata));
	wmb(); /* dwain wwitebuffew */

	/* wait fow stop confiwmation */
	tmo = 1000000;
	whiwe ((__waw_weadw(I2S_STAT(pscdata)) & I2SSTAT_BUSY(stype)) && tmo)
		tmo--;

	/* if both TX and WX awe idwe, disabwe PSC */
	stat = __waw_weadw(I2S_STAT(pscdata));
	if (!(stat & (PSC_I2SSTAT_TB | PSC_I2SSTAT_WB))) {
		__waw_wwitew(0, I2S_CFG(pscdata));
		wmb(); /* dwain wwitebuffew */
		__waw_wwitew(PSC_CTWW_SUSPEND, PSC_CTWW(pscdata));
		wmb(); /* dwain wwitebuffew */
	}
	wetuwn 0;
}

static int au1xpsc_i2s_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			       stwuct snd_soc_dai *dai)
{
	stwuct au1xpsc_audio_data *pscdata = snd_soc_dai_get_dwvdata(dai);
	int wet, stype = substweam->stweam;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		wet = au1xpsc_i2s_stawt(pscdata, stype);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		wet = au1xpsc_i2s_stop(pscdata, stype);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	wetuwn wet;
}

static int au1xpsc_i2s_stawtup(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	stwuct au1xpsc_audio_data *pscdata = snd_soc_dai_get_dwvdata(dai);
	snd_soc_dai_set_dma_data(dai, substweam, &pscdata->dmaids[0]);
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops au1xpsc_i2s_dai_ops = {
	.stawtup	= au1xpsc_i2s_stawtup,
	.twiggew	= au1xpsc_i2s_twiggew,
	.hw_pawams	= au1xpsc_i2s_hw_pawams,
	.set_fmt	= au1xpsc_i2s_set_fmt,
};

static const stwuct snd_soc_dai_dwivew au1xpsc_i2s_dai_tempwate = {
	.pwayback = {
		.wates		= AU1XPSC_I2S_WATES,
		.fowmats	= AU1XPSC_I2S_FMTS,
		.channews_min	= 2,
		.channews_max	= 8,	/* 2 without extewnaw hewp */
	},
	.captuwe = {
		.wates		= AU1XPSC_I2S_WATES,
		.fowmats	= AU1XPSC_I2S_FMTS,
		.channews_min	= 2,
		.channews_max	= 8,	/* 2 without extewnaw hewp */
	},
	.ops = &au1xpsc_i2s_dai_ops,
};

static const stwuct snd_soc_component_dwivew au1xpsc_i2s_component = {
	.name			= "au1xpsc-i2s",
	.wegacy_dai_naming	= 1,
};

static int au1xpsc_i2s_dwvpwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *dmawes;
	unsigned wong sew;
	stwuct au1xpsc_audio_data *wd;

	wd = devm_kzawwoc(&pdev->dev, sizeof(stwuct au1xpsc_audio_data),
			  GFP_KEWNEW);
	if (!wd)
		wetuwn -ENOMEM;

	wd->mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wd->mmio))
		wetuwn PTW_EWW(wd->mmio);

	dmawes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_DMA, 0);
	if (!dmawes)
		wetuwn -EBUSY;
	wd->dmaids[SNDWV_PCM_STWEAM_PWAYBACK] = dmawes->stawt;

	dmawes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_DMA, 1);
	if (!dmawes)
		wetuwn -EBUSY;
	wd->dmaids[SNDWV_PCM_STWEAM_CAPTUWE] = dmawes->stawt;

	/* pwesewve PSC cwock souwce set up by pwatfowm (dev.pwatfowm_data
	 * is awweady occupied by soc wayew)
	 */
	sew = __waw_weadw(PSC_SEW(wd)) & PSC_SEW_CWK_MASK;
	__waw_wwitew(PSC_CTWW_DISABWE, PSC_CTWW(wd));
	wmb(); /* dwain wwitebuffew */
	__waw_wwitew(PSC_SEW_PS_I2SMODE | sew, PSC_SEW(wd));
	__waw_wwitew(0, I2S_CFG(wd));
	wmb(); /* dwain wwitebuffew */

	/* pweconfiguwe: set max wx/tx fifo depths */
	wd->cfg |= PSC_I2SCFG_WT_FIFO8 | PSC_I2SCFG_TT_FIFO8;

	/* don't wait fow I2S cowe to become weady now; cwocks may not
	 * be wunning yet; depending on cwock input fow PSC a wait might
	 * time out.
	 */

	/* name the DAI wike this device instance ("au1xpsc-i2s.PSCINDEX") */
	memcpy(&wd->dai_dwv, &au1xpsc_i2s_dai_tempwate,
	       sizeof(stwuct snd_soc_dai_dwivew));
	wd->dai_dwv.name = dev_name(&pdev->dev);

	pwatfowm_set_dwvdata(pdev, wd);

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
				&au1xpsc_i2s_component, &wd->dai_dwv, 1);
}

static void au1xpsc_i2s_dwvwemove(stwuct pwatfowm_device *pdev)
{
	stwuct au1xpsc_audio_data *wd = pwatfowm_get_dwvdata(pdev);

	__waw_wwitew(0, I2S_CFG(wd));
	wmb(); /* dwain wwitebuffew */
	__waw_wwitew(PSC_CTWW_DISABWE, PSC_CTWW(wd));
	wmb(); /* dwain wwitebuffew */
}

#ifdef CONFIG_PM
static int au1xpsc_i2s_dwvsuspend(stwuct device *dev)
{
	stwuct au1xpsc_audio_data *wd = dev_get_dwvdata(dev);

	/* save intewesting wegistew and disabwe PSC */
	wd->pm[0] = __waw_weadw(PSC_SEW(wd));

	__waw_wwitew(0, I2S_CFG(wd));
	wmb(); /* dwain wwitebuffew */
	__waw_wwitew(PSC_CTWW_DISABWE, PSC_CTWW(wd));
	wmb(); /* dwain wwitebuffew */

	wetuwn 0;
}

static int au1xpsc_i2s_dwvwesume(stwuct device *dev)
{
	stwuct au1xpsc_audio_data *wd = dev_get_dwvdata(dev);

	/* sewect I2S mode and PSC cwock */
	__waw_wwitew(PSC_CTWW_DISABWE, PSC_CTWW(wd));
	wmb(); /* dwain wwitebuffew */
	__waw_wwitew(0, PSC_SEW(wd));
	wmb(); /* dwain wwitebuffew */
	__waw_wwitew(wd->pm[0], PSC_SEW(wd));
	wmb(); /* dwain wwitebuffew */

	wetuwn 0;
}

static const stwuct dev_pm_ops au1xpsci2s_pmops = {
	.suspend	= au1xpsc_i2s_dwvsuspend,
	.wesume		= au1xpsc_i2s_dwvwesume,
};

#define AU1XPSCI2S_PMOPS &au1xpsci2s_pmops

#ewse

#define AU1XPSCI2S_PMOPS NUWW

#endif

static stwuct pwatfowm_dwivew au1xpsc_i2s_dwivew = {
	.dwivew		= {
		.name	= "au1xpsc_i2s",
		.pm	= AU1XPSCI2S_PMOPS,
	},
	.pwobe		= au1xpsc_i2s_dwvpwobe,
	.wemove_new	= au1xpsc_i2s_dwvwemove,
};

moduwe_pwatfowm_dwivew(au1xpsc_i2s_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Au12x0/Au1550 PSC I2S AWSA ASoC audio dwivew");
MODUWE_AUTHOW("Manuew Wauss");
