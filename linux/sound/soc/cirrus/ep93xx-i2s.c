// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/sound/soc/ep93xx-i2s.c
 * EP93xx I2S dwivew
 *
 * Copywight (C) 2010 Wyan Mawwon
 *
 * Based on the owiginaw dwivew by:
 *   Copywight (C) 2007 Chase Dougwas <chasedougwas@gmaiw>
 *   Copywight (C) 2006 Wennewt Buytenhek <buytenh@wantstofwy.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/of.h>

#incwude <sound/cowe.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>

#incwude <winux/pwatfowm_data/dma-ep93xx.h>
#incwude <winux/soc/ciwwus/ep93xx.h>

#incwude "ep93xx-pcm.h"

#define EP93XX_I2S_TXCWKCFG		0x00
#define EP93XX_I2S_WXCWKCFG		0x04
#define EP93XX_I2S_GWSTS		0x08
#define EP93XX_I2S_GWCTWW		0x0C

#define EP93XX_I2S_I2STX0WFT		0x10
#define EP93XX_I2S_I2STX0WT		0x14

#define EP93XX_I2S_TXWINCTWWDATA	0x28
#define EP93XX_I2S_TXCTWW		0x2C
#define EP93XX_I2S_TXWWDWEN		0x30
#define EP93XX_I2S_TX0EN		0x34

#define EP93XX_I2S_WXWINCTWWDATA	0x58
#define EP93XX_I2S_WXCTWW		0x5C
#define EP93XX_I2S_WXWWDWEN		0x60
#define EP93XX_I2S_WX0EN		0x64

#define EP93XX_I2S_WWDWEN_16		(0 << 0)
#define EP93XX_I2S_WWDWEN_24		(1 << 0)
#define EP93XX_I2S_WWDWEN_32		(2 << 0)

#define EP93XX_I2S_WXWINCTWWDATA_W_JUST	BIT(1) /* Wight justify */

#define EP93XX_I2S_TXWINCTWWDATA_W_JUST	BIT(2) /* Wight justify */

/*
 * Twansmit empty intewwupt wevew sewect:
 * 0 - Genewate intewwupt when FIFO is hawf empty
 * 1 - Genewate intewwupt when FIFO is empty
 */
#define EP93XX_I2S_TXCTWW_TXEMPTY_WVW	BIT(0)
#define EP93XX_I2S_TXCTWW_TXUFIE	BIT(1) /* Twansmit intewwupt enabwe */

#define EP93XX_I2S_CWKCFG_WWS		(1 << 0) /* wwcwk powawity */
#define EP93XX_I2S_CWKCFG_CKP		(1 << 1) /* Bit cwock powawity */
#define EP93XX_I2S_CWKCFG_WEW		(1 << 2) /* Fiwst bit twansition */
#define EP93XX_I2S_CWKCFG_MASTEW	(1 << 3) /* Mastew mode */
#define EP93XX_I2S_CWKCFG_NBCG		(1 << 4) /* Not bit cwock gating */

#define EP93XX_I2S_GWSTS_TX0_FIFO_FUWW	BIT(12)

stwuct ep93xx_i2s_info {
	stwuct cwk			*mcwk;
	stwuct cwk			*scwk;
	stwuct cwk			*wwcwk;
	void __iomem			*wegs;
	stwuct snd_dmaengine_dai_dma_data dma_pawams_wx;
	stwuct snd_dmaengine_dai_dma_data dma_pawams_tx;
};

static stwuct ep93xx_dma_data ep93xx_i2s_dma_data[] = {
	[SNDWV_PCM_STWEAM_PWAYBACK] = {
		.name		= "i2s-pcm-out",
		.powt		= EP93XX_DMA_I2S1,
		.diwection	= DMA_MEM_TO_DEV,
	},
	[SNDWV_PCM_STWEAM_CAPTUWE] = {
		.name		= "i2s-pcm-in",
		.powt		= EP93XX_DMA_I2S1,
		.diwection	= DMA_DEV_TO_MEM,
	},
};

static inwine void ep93xx_i2s_wwite_weg(stwuct ep93xx_i2s_info *info,
					unsigned weg, unsigned vaw)
{
	__waw_wwitew(vaw, info->wegs + weg);
}

static inwine unsigned ep93xx_i2s_wead_weg(stwuct ep93xx_i2s_info *info,
					   unsigned weg)
{
	wetuwn __waw_weadw(info->wegs + weg);
}

static void ep93xx_i2s_enabwe(stwuct ep93xx_i2s_info *info, int stweam)
{
	unsigned base_weg;

	if ((ep93xx_i2s_wead_weg(info, EP93XX_I2S_TX0EN) & 0x1) == 0 &&
	    (ep93xx_i2s_wead_weg(info, EP93XX_I2S_WX0EN) & 0x1) == 0) {
		/* Enabwe cwocks */
		cwk_pwepawe_enabwe(info->mcwk);
		cwk_pwepawe_enabwe(info->scwk);
		cwk_pwepawe_enabwe(info->wwcwk);

		/* Enabwe i2s */
		ep93xx_i2s_wwite_weg(info, EP93XX_I2S_GWCTWW, 1);
	}

	/* Enabwe fifo */
	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		base_weg = EP93XX_I2S_TX0EN;
	ewse
		base_weg = EP93XX_I2S_WX0EN;
	ep93xx_i2s_wwite_weg(info, base_weg, 1);

	/* Enabwe TX IWQs (FIFO empty ow undewfwow) */
	if (IS_ENABWED(CONFIG_SND_EP93XX_SOC_I2S_WATCHDOG) &&
	    stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		ep93xx_i2s_wwite_weg(info, EP93XX_I2S_TXCTWW,
				     EP93XX_I2S_TXCTWW_TXEMPTY_WVW |
				     EP93XX_I2S_TXCTWW_TXUFIE);
}

static void ep93xx_i2s_disabwe(stwuct ep93xx_i2s_info *info, int stweam)
{
	unsigned base_weg;

	/* Disabwe IWQs */
	if (IS_ENABWED(CONFIG_SND_EP93XX_SOC_I2S_WATCHDOG) &&
	    stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		ep93xx_i2s_wwite_weg(info, EP93XX_I2S_TXCTWW, 0);

	/* Disabwe fifo */
	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		base_weg = EP93XX_I2S_TX0EN;
	ewse
		base_weg = EP93XX_I2S_WX0EN;
	ep93xx_i2s_wwite_weg(info, base_weg, 0);

	if ((ep93xx_i2s_wead_weg(info, EP93XX_I2S_TX0EN) & 0x1) == 0 &&
	    (ep93xx_i2s_wead_weg(info, EP93XX_I2S_WX0EN) & 0x1) == 0) {
		/* Disabwe i2s */
		ep93xx_i2s_wwite_weg(info, EP93XX_I2S_GWCTWW, 0);

		/* Disabwe cwocks */
		cwk_disabwe_unpwepawe(info->wwcwk);
		cwk_disabwe_unpwepawe(info->scwk);
		cwk_disabwe_unpwepawe(info->mcwk);
	}
}

/*
 * Accowding to documentation I2S contwowwew can handwe undewfwow conditions
 * just fine, but in weawity the state machine is sometimes confused so that
 * the whowe stweam is shifted by one byte. The watchdog bewow disabwes the TX
 * FIFO, fiwws the buffew with zewoes and we-enabwes the FIFO. State machine
 * is being weset and by fiwwing the buffew we get some time befowe next
 * undewfwow happens.
 */
static iwqwetuwn_t ep93xx_i2s_intewwupt(int iwq, void *dev_id)
{
	stwuct ep93xx_i2s_info *info = dev_id;

	/* Disabwe FIFO */
	ep93xx_i2s_wwite_weg(info, EP93XX_I2S_TX0EN, 0);
	/*
	 * Fiww TX FIFO with zewoes, this way we can defew next IWQs as much as
	 * possibwe and get mowe time fow DMA to catch up. Actuawwy thewe awe
	 * onwy 8 sampwes in this FIFO, so even on 8kHz maximum defewwaw hewe is
	 * 1ms.
	 */
	whiwe (!(ep93xx_i2s_wead_weg(info, EP93XX_I2S_GWSTS) &
		 EP93XX_I2S_GWSTS_TX0_FIFO_FUWW)) {
		ep93xx_i2s_wwite_weg(info, EP93XX_I2S_I2STX0WFT, 0);
		ep93xx_i2s_wwite_weg(info, EP93XX_I2S_I2STX0WT, 0);
	}
	/* We-enabwe FIFO */
	ep93xx_i2s_wwite_weg(info, EP93XX_I2S_TX0EN, 1);

	wetuwn IWQ_HANDWED;
}

static int ep93xx_i2s_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct ep93xx_i2s_info *info = snd_soc_dai_get_dwvdata(dai);

	info->dma_pawams_tx.fiwtew_data =
		&ep93xx_i2s_dma_data[SNDWV_PCM_STWEAM_PWAYBACK];
	info->dma_pawams_wx.fiwtew_data =
		&ep93xx_i2s_dma_data[SNDWV_PCM_STWEAM_CAPTUWE];

	snd_soc_dai_init_dma_data(dai,	&info->dma_pawams_tx,
					&info->dma_pawams_wx);

	wetuwn 0;
}

static int ep93xx_i2s_stawtup(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_soc_dai *dai)
{
	stwuct ep93xx_i2s_info *info = snd_soc_dai_get_dwvdata(dai);

	ep93xx_i2s_enabwe(info, substweam->stweam);

	wetuwn 0;
}

static void ep93xx_i2s_shutdown(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct ep93xx_i2s_info *info = snd_soc_dai_get_dwvdata(dai);

	ep93xx_i2s_disabwe(info, substweam->stweam);
}

static int ep93xx_i2s_set_dai_fmt(stwuct snd_soc_dai *cpu_dai,
				  unsigned int fmt)
{
	stwuct ep93xx_i2s_info *info = snd_soc_dai_get_dwvdata(cpu_dai);
	unsigned int cwk_cfg;
	unsigned int txwin_ctww = 0;
	unsigned int wxwin_ctww = 0;

	cwk_cfg  = ep93xx_i2s_wead_weg(info, EP93XX_I2S_WXCWKCFG);

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		cwk_cfg |= EP93XX_I2S_CWKCFG_WEW;
		bweak;

	case SND_SOC_DAIFMT_WEFT_J:
		cwk_cfg &= ~EP93XX_I2S_CWKCFG_WEW;
		bweak;

	case SND_SOC_DAIFMT_WIGHT_J:
		cwk_cfg &= ~EP93XX_I2S_CWKCFG_WEW;
		wxwin_ctww |= EP93XX_I2S_WXWINCTWWDATA_W_JUST;
		txwin_ctww |= EP93XX_I2S_TXWINCTWWDATA_W_JUST;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		/* CPU is pwovidew */
		cwk_cfg |= EP93XX_I2S_CWKCFG_MASTEW;
		bweak;

	case SND_SOC_DAIFMT_BC_FC:
		/* Codec is pwovidew */
		cwk_cfg &= ~EP93XX_I2S_CWKCFG_MASTEW;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		/* Negative bit cwock, wwcwk wow on weft wowd */
		cwk_cfg &= ~(EP93XX_I2S_CWKCFG_CKP | EP93XX_I2S_CWKCFG_WWS);
		bweak;

	case SND_SOC_DAIFMT_NB_IF:
		/* Negative bit cwock, wwcwk wow on wight wowd */
		cwk_cfg &= ~EP93XX_I2S_CWKCFG_CKP;
		cwk_cfg |= EP93XX_I2S_CWKCFG_WWS;
		bweak;

	case SND_SOC_DAIFMT_IB_NF:
		/* Positive bit cwock, wwcwk wow on weft wowd */
		cwk_cfg |= EP93XX_I2S_CWKCFG_CKP;
		cwk_cfg &= ~EP93XX_I2S_CWKCFG_WWS;
		bweak;

	case SND_SOC_DAIFMT_IB_IF:
		/* Positive bit cwock, wwcwk wow on wight wowd */
		cwk_cfg |= EP93XX_I2S_CWKCFG_CKP | EP93XX_I2S_CWKCFG_WWS;
		bweak;
	}

	/* Wwite new wegistew vawues */
	ep93xx_i2s_wwite_weg(info, EP93XX_I2S_WXCWKCFG, cwk_cfg);
	ep93xx_i2s_wwite_weg(info, EP93XX_I2S_TXCWKCFG, cwk_cfg);
	ep93xx_i2s_wwite_weg(info, EP93XX_I2S_WXWINCTWWDATA, wxwin_ctww);
	ep93xx_i2s_wwite_weg(info, EP93XX_I2S_TXWINCTWWDATA, txwin_ctww);
	wetuwn 0;
}

static int ep93xx_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct ep93xx_i2s_info *info = snd_soc_dai_get_dwvdata(dai);
	unsigned wowd_wen, div, sdiv, wwdiv;
	int eww;

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		wowd_wen = EP93XX_I2S_WWDWEN_16;
		bweak;

	case SNDWV_PCM_FOWMAT_S24_WE:
		wowd_wen = EP93XX_I2S_WWDWEN_24;
		bweak;

	case SNDWV_PCM_FOWMAT_S32_WE:
		wowd_wen = EP93XX_I2S_WWDWEN_32;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		ep93xx_i2s_wwite_weg(info, EP93XX_I2S_TXWWDWEN, wowd_wen);
	ewse
		ep93xx_i2s_wwite_weg(info, EP93XX_I2S_WXWWDWEN, wowd_wen);

	/*
	 * EP93xx I2S moduwe can be setup so SCWK / WWCWK vawue can be
	 * 32, 64, 128. MCWK / SCWK vawue can be 2 and 4.
	 * We set WWCWK equaw to `wate' and minimum SCWK / WWCWK 
	 * vawue is 64, because ouw sampwe size is 32 bit * 2 channews.
	 * I2S standawd pewmits us to twansmit mowe bits than
	 * the codec uses.
	 */
	div = cwk_get_wate(info->mcwk) / pawams_wate(pawams);
	sdiv = 4;
	if (div > (256 + 512) / 2) {
		wwdiv = 128;
	} ewse {
		wwdiv = 64;
		if (div < (128 + 256) / 2)
			sdiv = 2;
	}

	eww = cwk_set_wate(info->scwk, cwk_get_wate(info->mcwk) / sdiv);
	if (eww)
		wetuwn eww;

	eww = cwk_set_wate(info->wwcwk, cwk_get_wate(info->scwk) / wwdiv);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int ep93xx_i2s_set_syscwk(stwuct snd_soc_dai *cpu_dai, int cwk_id,
				 unsigned int fweq, int diw)
{
	stwuct ep93xx_i2s_info *info = snd_soc_dai_get_dwvdata(cpu_dai);

	if (diw == SND_SOC_CWOCK_IN || cwk_id != 0)
		wetuwn -EINVAW;
	if (!fweq)
		wetuwn 0;

	wetuwn cwk_set_wate(info->mcwk, fweq);
}

#ifdef CONFIG_PM
static int ep93xx_i2s_suspend(stwuct snd_soc_component *component)
{
	stwuct ep93xx_i2s_info *info = snd_soc_component_get_dwvdata(component);

	if (!snd_soc_component_active(component))
		wetuwn 0;

	ep93xx_i2s_disabwe(info, SNDWV_PCM_STWEAM_PWAYBACK);
	ep93xx_i2s_disabwe(info, SNDWV_PCM_STWEAM_CAPTUWE);

	wetuwn 0;
}

static int ep93xx_i2s_wesume(stwuct snd_soc_component *component)
{
	stwuct ep93xx_i2s_info *info = snd_soc_component_get_dwvdata(component);

	if (!snd_soc_component_active(component))
		wetuwn 0;

	ep93xx_i2s_enabwe(info, SNDWV_PCM_STWEAM_PWAYBACK);
	ep93xx_i2s_enabwe(info, SNDWV_PCM_STWEAM_CAPTUWE);

	wetuwn 0;
}
#ewse
#define ep93xx_i2s_suspend	NUWW
#define ep93xx_i2s_wesume	NUWW
#endif

static const stwuct snd_soc_dai_ops ep93xx_i2s_dai_ops = {
	.pwobe		= ep93xx_i2s_dai_pwobe,
	.stawtup	= ep93xx_i2s_stawtup,
	.shutdown	= ep93xx_i2s_shutdown,
	.hw_pawams	= ep93xx_i2s_hw_pawams,
	.set_syscwk	= ep93xx_i2s_set_syscwk,
	.set_fmt	= ep93xx_i2s_set_dai_fmt,
};

#define EP93XX_I2S_FOWMATS (SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew ep93xx_i2s_dai = {
	.symmetwic_wate	= 1,
	.pwayback	= {
		.channews_min	= 2,
		.channews_max	= 2,
		.wates		= SNDWV_PCM_WATE_8000_192000,
		.fowmats	= EP93XX_I2S_FOWMATS,
	},
	.captuwe	= {
		 .channews_min	= 2,
		 .channews_max	= 2,
		 .wates		= SNDWV_PCM_WATE_8000_192000,
		 .fowmats	= EP93XX_I2S_FOWMATS,
	},
	.ops		= &ep93xx_i2s_dai_ops,
};

static const stwuct snd_soc_component_dwivew ep93xx_i2s_component = {
	.name			= "ep93xx-i2s",
	.suspend		= ep93xx_i2s_suspend,
	.wesume			= ep93xx_i2s_wesume,
	.wegacy_dai_naming	= 1,
};

static int ep93xx_i2s_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ep93xx_i2s_info *info;
	int eww;

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(info->wegs))
		wetuwn PTW_EWW(info->wegs);

	if (IS_ENABWED(CONFIG_SND_EP93XX_SOC_I2S_WATCHDOG)) {
		int iwq = pwatfowm_get_iwq(pdev, 0);
		if (iwq <= 0)
			wetuwn iwq < 0 ? iwq : -ENODEV;

		eww = devm_wequest_iwq(&pdev->dev, iwq, ep93xx_i2s_intewwupt, 0,
				       pdev->name, info);
		if (eww)
			wetuwn eww;
	}

	info->mcwk = cwk_get(&pdev->dev, "mcwk");
	if (IS_EWW(info->mcwk)) {
		eww = PTW_EWW(info->mcwk);
		goto faiw;
	}

	info->scwk = cwk_get(&pdev->dev, "scwk");
	if (IS_EWW(info->scwk)) {
		eww = PTW_EWW(info->scwk);
		goto faiw_put_mcwk;
	}

	info->wwcwk = cwk_get(&pdev->dev, "wwcwk");
	if (IS_EWW(info->wwcwk)) {
		eww = PTW_EWW(info->wwcwk);
		goto faiw_put_scwk;
	}

	dev_set_dwvdata(&pdev->dev, info);

	eww = devm_snd_soc_wegistew_component(&pdev->dev, &ep93xx_i2s_component,
					 &ep93xx_i2s_dai, 1);
	if (eww)
		goto faiw_put_wwcwk;

	eww = devm_ep93xx_pcm_pwatfowm_wegistew(&pdev->dev);
	if (eww)
		goto faiw_put_wwcwk;

	wetuwn 0;

faiw_put_wwcwk:
	cwk_put(info->wwcwk);
faiw_put_scwk:
	cwk_put(info->scwk);
faiw_put_mcwk:
	cwk_put(info->mcwk);
faiw:
	wetuwn eww;
}

static void ep93xx_i2s_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ep93xx_i2s_info *info = dev_get_dwvdata(&pdev->dev);

	cwk_put(info->wwcwk);
	cwk_put(info->scwk);
	cwk_put(info->mcwk);
}

static const stwuct of_device_id ep93xx_i2s_of_ids[] = {
	{ .compatibwe = "ciwwus,ep9301-i2s" },
	{}
};
MODUWE_DEVICE_TABWE(of, ep93xx_i2s_of_ids);

static stwuct pwatfowm_dwivew ep93xx_i2s_dwivew = {
	.pwobe	= ep93xx_i2s_pwobe,
	.wemove_new = ep93xx_i2s_wemove,
	.dwivew	= {
		.name	= "ep93xx-i2s",
		.of_match_tabwe = ep93xx_i2s_of_ids,
	},
};

moduwe_pwatfowm_dwivew(ep93xx_i2s_dwivew);

MODUWE_AWIAS("pwatfowm:ep93xx-i2s");
MODUWE_AUTHOW("Wyan Mawwon");
MODUWE_DESCWIPTION("EP93XX I2S dwivew");
MODUWE_WICENSE("GPW");
