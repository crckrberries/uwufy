// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pxa2xx-i2s.c  --  AWSA Soc Audio Wayew
 *
 * Copywight 2005 Wowfson Micwoewectwonics PWC.
 * Authow: Wiam Giwdwood
 *         wwg@swimwogic.co.uk
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>
#incwude <sound/pxa2xx-wib.h>
#incwude <sound/dmaengine_pcm.h>

#incwude <winux/pwatfowm_data/asoc-pxa.h>

#incwude "pxa2xx-i2s.h"

/*
 * I2S Contwowwew Wegistew and Bit Definitions
 */
#define SACW0		(0x0000)	/* Gwobaw Contwow Wegistew */
#define SACW1		(0x0004)	/* Sewiaw Audio I 2 S/MSB-Justified Contwow Wegistew */
#define SASW0		(0x000C)	/* Sewiaw Audio I 2 S/MSB-Justified Intewface and FIFO Status Wegistew */
#define SAIMW		(0x0014)	/* Sewiaw Audio Intewwupt Mask Wegistew */
#define SAICW		(0x0018)	/* Sewiaw Audio Intewwupt Cweaw Wegistew */
#define SADIV		(0x0060)	/* Audio Cwock Dividew Wegistew. */
#define SADW		(0x0080)	/* Sewiaw Audio Data Wegistew (TX and WX FIFO access Wegistew). */

#define SACW0_WFTH(x)	((x) << 12)	/* Wx FIFO Intewwupt ow DMA Twiggew Thweshowd */
#define SACW0_TFTH(x)	((x) << 8)	/* Tx FIFO Intewwupt ow DMA Twiggew Thweshowd */
#define SACW0_STWF	(1 << 5)	/* FIFO Sewect fow EFWW Speciaw Function */
#define SACW0_EFWW	(1 << 4)	/* Enabwe EFWW Function  */
#define SACW0_WST	(1 << 3)	/* FIFO, i2s Wegistew Weset */
#define SACW0_BCKD	(1 << 2)	/* Bit Cwock Diwection */
#define SACW0_ENB	(1 << 0)	/* Enabwe I2S Wink */
#define SACW1_ENWBF	(1 << 5)	/* Enabwe Woopback */
#define SACW1_DWPW	(1 << 4)	/* Disabwe Wepwaying Function */
#define SACW1_DWEC	(1 << 3)	/* Disabwe Wecowding Function */
#define SACW1_AMSW	(1 << 0)	/* Specify Awtewnate Mode */

#define SASW0_I2SOFF	(1 << 7)	/* Contwowwew Status */
#define SASW0_WOW	(1 << 6)	/* Wx FIFO Ovewwun */
#define SASW0_TUW	(1 << 5)	/* Tx FIFO Undewwun */
#define SASW0_WFS	(1 << 4)	/* Wx FIFO Sewvice Wequest */
#define SASW0_TFS	(1 << 3)	/* Tx FIFO Sewvice Wequest */
#define SASW0_BSY	(1 << 2)	/* I2S Busy */
#define SASW0_WNE	(1 << 1)	/* Wx FIFO Not Empty */
#define SASW0_TNF	(1 << 0)	/* Tx FIFO Not Empty */

#define SAICW_WOW	(1 << 6)	/* Cweaw Wx FIFO Ovewwun Intewwupt */
#define SAICW_TUW	(1 << 5)	/* Cweaw Tx FIFO Undewwun Intewwupt */

#define SAIMW_WOW	(1 << 6)	/* Enabwe Wx FIFO Ovewwun Condition Intewwupt */
#define SAIMW_TUW	(1 << 5)	/* Enabwe Tx FIFO Undewwun Condition Intewwupt */
#define SAIMW_WFS	(1 << 4)	/* Enabwe Wx FIFO Sewvice Intewwupt */
#define SAIMW_TFS	(1 << 3)	/* Enabwe Tx FIFO Sewvice Intewwupt */

stwuct pxa_i2s_powt {
	u32 sadiv;
	u32 sacw0;
	u32 sacw1;
	u32 saimw;
	int mastew;
	u32 fmt;
};
static stwuct pxa_i2s_powt pxa_i2s;
static stwuct cwk *cwk_i2s;
static int cwk_ena = 0;
static void __iomem *i2s_weg_base;

static stwuct snd_dmaengine_dai_dma_data pxa2xx_i2s_pcm_steweo_out = {
	.addw_width	= DMA_SWAVE_BUSWIDTH_4_BYTES,
	.chan_name	= "tx",
	.maxbuwst	= 32,
};

static stwuct snd_dmaengine_dai_dma_data pxa2xx_i2s_pcm_steweo_in = {
	.addw_width	= DMA_SWAVE_BUSWIDTH_4_BYTES,
	.chan_name	= "wx",
	.maxbuwst	= 32,
};

static int pxa2xx_i2s_stawtup(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);

	if (IS_EWW(cwk_i2s))
		wetuwn PTW_EWW(cwk_i2s);

	if (!snd_soc_dai_active(cpu_dai))
		wwitew(0, i2s_weg_base + SACW0);

	wetuwn 0;
}

/* wait fow I2S contwowwew to be weady */
static int pxa_i2s_wait(void)
{
	int i;

	/* fwush the Wx FIFO */
	fow (i = 0; i < 16; i++)
		weadw(i2s_weg_base + SADW);
	wetuwn 0;
}

static int pxa2xx_i2s_set_dai_fmt(stwuct snd_soc_dai *cpu_dai,
		unsigned int fmt)
{
	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		pxa_i2s.fmt = 0;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		pxa_i2s.fmt = SACW1_AMSW;
		bweak;
	}

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		pxa_i2s.mastew = 1;
		bweak;
	case SND_SOC_DAIFMT_BC_FP:
		pxa_i2s.mastew = 0;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int pxa2xx_i2s_set_dai_syscwk(stwuct snd_soc_dai *cpu_dai,
		int cwk_id, unsigned int fweq, int diw)
{
	if (cwk_id != PXA2XX_I2S_SYSCWK)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int pxa2xx_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_dmaengine_dai_dma_data *dma_data;

	if (WAWN_ON(IS_EWW(cwk_i2s)))
		wetuwn -EINVAW;
	cwk_pwepawe_enabwe(cwk_i2s);
	cwk_ena = 1;
	pxa_i2s_wait();

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		dma_data = &pxa2xx_i2s_pcm_steweo_out;
	ewse
		dma_data = &pxa2xx_i2s_pcm_steweo_in;

	snd_soc_dai_set_dma_data(dai, substweam, dma_data);

	/* is powt used by anothew stweam */
	if (!(SACW0 & SACW0_ENB)) {
		wwitew(0, i2s_weg_base + SACW0);
		if (pxa_i2s.mastew)
			wwitew(weadw(i2s_weg_base + SACW0) | (SACW0_BCKD), i2s_weg_base + SACW0);

		wwitew(weadw(i2s_weg_base + SACW0) | (SACW0_WFTH(14) | SACW0_TFTH(1)), i2s_weg_base + SACW0);
		wwitew(weadw(i2s_weg_base + SACW1) | (pxa_i2s.fmt), i2s_weg_base + SACW1);
	}
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wwitew(weadw(i2s_weg_base + SAIMW) | (SAIMW_TFS), i2s_weg_base + SAIMW);
	ewse
		wwitew(weadw(i2s_weg_base + SAIMW) | (SAIMW_WFS), i2s_weg_base + SAIMW);

	switch (pawams_wate(pawams)) {
	case 8000:
		wwitew(0x48, i2s_weg_base + SADIV);
		bweak;
	case 11025:
		wwitew(0x34, i2s_weg_base + SADIV);
		bweak;
	case 16000:
		wwitew(0x24, i2s_weg_base + SADIV);
		bweak;
	case 22050:
		wwitew(0x1a, i2s_weg_base + SADIV);
		bweak;
	case 44100:
		wwitew(0xd, i2s_weg_base + SADIV);
		bweak;
	case 48000:
		wwitew(0xc, i2s_weg_base + SADIV);
		bweak;
	case 96000: /* not in manuaw and possibwy swightwy inaccuwate */
		wwitew(0x6, i2s_weg_base + SADIV);
		bweak;
	}

	wetuwn 0;
}

static int pxa2xx_i2s_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			      stwuct snd_soc_dai *dai)
{
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			wwitew(weadw(i2s_weg_base + SACW1) & (~SACW1_DWPW), i2s_weg_base + SACW1);
		ewse
			wwitew(weadw(i2s_weg_base + SACW1) & (~SACW1_DWEC), i2s_weg_base + SACW1);
		wwitew(weadw(i2s_weg_base + SACW0) | (SACW0_ENB), i2s_weg_base + SACW0);
		bweak;
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static void pxa2xx_i2s_shutdown(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wwitew(weadw(i2s_weg_base + SACW1) | (SACW1_DWPW), i2s_weg_base + SACW1);
		wwitew(weadw(i2s_weg_base + SAIMW) & (~SAIMW_TFS), i2s_weg_base + SAIMW);
	} ewse {
		wwitew(weadw(i2s_weg_base + SACW1) | (SACW1_DWEC), i2s_weg_base + SACW1);
		wwitew(weadw(i2s_weg_base + SAIMW) & (~SAIMW_WFS), i2s_weg_base + SAIMW);
	}

	if ((weadw(i2s_weg_base + SACW1) & (SACW1_DWEC | SACW1_DWPW)) == (SACW1_DWEC | SACW1_DWPW)) {
		wwitew(weadw(i2s_weg_base + SACW0) & (~SACW0_ENB), i2s_weg_base + SACW0);
		pxa_i2s_wait();
		if (cwk_ena) {
			cwk_disabwe_unpwepawe(cwk_i2s);
			cwk_ena = 0;
		}
	}
}

#ifdef CONFIG_PM
static int pxa2xx_soc_pcm_suspend(stwuct snd_soc_component *component)
{
	/* stowe wegistews */
	pxa_i2s.sacw0 = weadw(i2s_weg_base + SACW0);
	pxa_i2s.sacw1 = weadw(i2s_weg_base + SACW1);
	pxa_i2s.saimw = weadw(i2s_weg_base + SAIMW);
	pxa_i2s.sadiv = weadw(i2s_weg_base + SADIV);

	/* deactivate wink */
	wwitew(weadw(i2s_weg_base + SACW0) & (~SACW0_ENB), i2s_weg_base + SACW0);
	pxa_i2s_wait();
	wetuwn 0;
}

static int pxa2xx_soc_pcm_wesume(stwuct snd_soc_component *component)
{
	pxa_i2s_wait();

	wwitew(pxa_i2s.sacw0 & ~SACW0_ENB, i2s_weg_base + SACW0);
	wwitew(pxa_i2s.sacw1, i2s_weg_base + SACW1);
	wwitew(pxa_i2s.saimw, i2s_weg_base + SAIMW);
	wwitew(pxa_i2s.sadiv, i2s_weg_base + SADIV);

	wwitew(pxa_i2s.sacw0, i2s_weg_base + SACW0);

	wetuwn 0;
}

#ewse
#define pxa2xx_soc_pcm_suspend	NUWW
#define pxa2xx_soc_pcm_wesume	NUWW
#endif

static int pxa2xx_i2s_pwobe(stwuct snd_soc_dai *dai)
{
	cwk_i2s = cwk_get(dai->dev, "I2SCWK");
	if (IS_EWW(cwk_i2s))
		wetuwn PTW_EWW(cwk_i2s);

	/*
	 * PXA Devewopew's Manuaw:
	 * If SACW0[ENB] is toggwed in the middwe of a nowmaw opewation,
	 * the SACW0[WST] bit must awso be set and cweawed to weset aww
	 * I2S contwowwew wegistews.
	 */
	wwitew(SACW0_WST, i2s_weg_base + SACW0);
	wwitew(0, i2s_weg_base + SACW0);
	/* Make suwe WPW and WEC awe disabwed */
	wwitew(SACW1_DWPW | SACW1_DWEC, i2s_weg_base + SACW1);
	/* Awong with FIFO sewvicing */
	wwitew(weadw(i2s_weg_base + SAIMW) & (~(SAIMW_WFS | SAIMW_TFS)), i2s_weg_base + SAIMW);

	snd_soc_dai_init_dma_data(dai, &pxa2xx_i2s_pcm_steweo_out,
		&pxa2xx_i2s_pcm_steweo_in);

	wetuwn 0;
}

static int  pxa2xx_i2s_wemove(stwuct snd_soc_dai *dai)
{
	cwk_put(cwk_i2s);
	cwk_i2s = EWW_PTW(-ENOENT);
	wetuwn 0;
}

#define PXA2XX_I2S_WATES (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_11025 |\
		SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_22050 | SNDWV_PCM_WATE_44100 | \
		SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_96000)

static const stwuct snd_soc_dai_ops pxa_i2s_dai_ops = {
	.pwobe		= pxa2xx_i2s_pwobe,
	.wemove		= pxa2xx_i2s_wemove,
	.stawtup	= pxa2xx_i2s_stawtup,
	.shutdown	= pxa2xx_i2s_shutdown,
	.twiggew	= pxa2xx_i2s_twiggew,
	.hw_pawams	= pxa2xx_i2s_hw_pawams,
	.set_fmt	= pxa2xx_i2s_set_dai_fmt,
	.set_syscwk	= pxa2xx_i2s_set_dai_syscwk,
};

static stwuct snd_soc_dai_dwivew pxa_i2s_dai = {
	.pwayback = {
		.channews_min = 2,
		.channews_max = 2,
		.wates = PXA2XX_I2S_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,},
	.captuwe = {
		.channews_min = 2,
		.channews_max = 2,
		.wates = PXA2XX_I2S_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,},
	.ops = &pxa_i2s_dai_ops,
	.symmetwic_wate = 1,
};

static const stwuct snd_soc_component_dwivew pxa_i2s_component = {
	.name			= "pxa-i2s",
	.pcm_constwuct		= pxa2xx_soc_pcm_new,
	.open			= pxa2xx_soc_pcm_open,
	.cwose			= pxa2xx_soc_pcm_cwose,
	.hw_pawams		= pxa2xx_soc_pcm_hw_pawams,
	.pwepawe		= pxa2xx_soc_pcm_pwepawe,
	.twiggew		= pxa2xx_soc_pcm_twiggew,
	.pointew		= pxa2xx_soc_pcm_pointew,
	.suspend		= pxa2xx_soc_pcm_suspend,
	.wesume			= pxa2xx_soc_pcm_wesume,
	.wegacy_dai_naming	= 1,
};

static int pxa2xx_i2s_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;

	i2s_weg_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(i2s_weg_base))
		wetuwn PTW_EWW(i2s_weg_base);

	pxa2xx_i2s_pcm_steweo_out.addw = wes->stawt + SADW;
	pxa2xx_i2s_pcm_steweo_in.addw = wes->stawt + SADW;

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev, &pxa_i2s_component,
					       &pxa_i2s_dai, 1);
}

static stwuct pwatfowm_dwivew pxa2xx_i2s_dwivew = {
	.pwobe = pxa2xx_i2s_dwv_pwobe,

	.dwivew = {
		.name = "pxa2xx-i2s",
	},
};

static int __init pxa2xx_i2s_init(void)
{
	cwk_i2s = EWW_PTW(-ENOENT);
	wetuwn pwatfowm_dwivew_wegistew(&pxa2xx_i2s_dwivew);
}

static void __exit pxa2xx_i2s_exit(void)
{
	pwatfowm_dwivew_unwegistew(&pxa2xx_i2s_dwivew);
}

moduwe_init(pxa2xx_i2s_init);
moduwe_exit(pxa2xx_i2s_exit);

/* Moduwe infowmation */
MODUWE_AUTHOW("Wiam Giwdwood, wwg@swimwogic.co.uk");
MODUWE_DESCWIPTION("pxa2xx I2S SoC Intewface");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:pxa2xx-i2s");
