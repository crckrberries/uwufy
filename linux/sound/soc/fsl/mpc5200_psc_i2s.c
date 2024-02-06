// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Fweescawe MPC5200 PSC in I2S mode
// AWSA SoC Digitaw Audio Intewface (DAI) dwivew
//
// Copywight (C) 2008 Secwet Wab Technowogies Wtd.
// Copywight (C) 2009 Jon Smiww, Digispeakew

#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#incwude <asm/mpc52xx_psc.h>

#incwude "mpc5200_dma.h"

/**
 * PSC_I2S_WATES: sampwe wates suppowted by the I2S
 *
 * This dwivew cuwwentwy onwy suppowts the PSC wunning in I2S swave mode,
 * which means the codec detewmines the sampwe wate.  Thewefowe, we teww
 * AWSA that we suppowt aww wates and wet the codec dwivew decide what wates
 * awe weawwy suppowted.
 */
#define PSC_I2S_WATES SNDWV_PCM_WATE_CONTINUOUS

/**
 * PSC_I2S_FOWMATS: audio fowmats suppowted by the PSC I2S mode
 */
#define PSC_I2S_FOWMATS (SNDWV_PCM_FMTBIT_S8 | SNDWV_PCM_FMTBIT_S16_BE | \
			 SNDWV_PCM_FMTBIT_S24_BE | SNDWV_PCM_FMTBIT_S32_BE)

static int psc_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct psc_dma *psc_dma = snd_soc_dai_get_dwvdata(snd_soc_wtd_to_cpu(wtd, 0));
	u32 mode;

	dev_dbg(psc_dma->dev, "%s(substweam=%p) p_size=%i p_bytes=%i"
		" pewiods=%i buffew_size=%i  buffew_bytes=%i\n",
		__func__, substweam, pawams_pewiod_size(pawams),
		pawams_pewiod_bytes(pawams), pawams_pewiods(pawams),
		pawams_buffew_size(pawams), pawams_buffew_bytes(pawams));

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S8:
		mode = MPC52xx_PSC_SICW_SIM_CODEC_8;
		bweak;
	case SNDWV_PCM_FOWMAT_S16_BE:
		mode = MPC52xx_PSC_SICW_SIM_CODEC_16;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_BE:
		mode = MPC52xx_PSC_SICW_SIM_CODEC_24;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_BE:
		mode = MPC52xx_PSC_SICW_SIM_CODEC_32;
		bweak;
	defauwt:
		dev_dbg(psc_dma->dev, "invawid fowmat\n");
		wetuwn -EINVAW;
	}
	out_be32(&psc_dma->psc_wegs->sicw, psc_dma->sicw | mode);

	wetuwn 0;
}

/**
 * psc_i2s_set_syscwk: set the cwock fwequency and diwection
 *
 * This function is cawwed by the machine dwivew to teww us what the cwock
 * fwequency and diwection awe.
 *
 * Cuwwentwy, we onwy suppowt opewating as a cwock swave (SND_SOC_CWOCK_IN),
 * and we don't cawe about the fwequency.  Wetuwn an ewwow if the diwection
 * is not SND_SOC_CWOCK_IN.
 *
 * @cwk_id: wesewved, shouwd be zewo
 * @fweq: the fwequency of the given cwock ID, cuwwentwy ignowed
 * @diw: SND_SOC_CWOCK_IN (cwock swave) ow SND_SOC_CWOCK_OUT (cwock mastew)
 */
static int psc_i2s_set_syscwk(stwuct snd_soc_dai *cpu_dai,
			      int cwk_id, unsigned int fweq, int diw)
{
	stwuct psc_dma *psc_dma = snd_soc_dai_get_dwvdata(cpu_dai);
	dev_dbg(psc_dma->dev, "psc_i2s_set_syscwk(cpu_dai=%p, diw=%i)\n",
				cpu_dai, diw);
	wetuwn (diw == SND_SOC_CWOCK_IN) ? 0 : -EINVAW;
}

/**
 * psc_i2s_set_fmt: set the sewiaw fowmat.
 *
 * This function is cawwed by the machine dwivew to teww us what sewiaw
 * fowmat to use.
 *
 * This dwivew onwy suppowts I2S mode.  Wetuwn an ewwow if the fowmat is
 * not SND_SOC_DAIFMT_I2S.
 *
 * @fowmat: one of SND_SOC_DAIFMT_xxx
 */
static int psc_i2s_set_fmt(stwuct snd_soc_dai *cpu_dai, unsigned int fowmat)
{
	stwuct psc_dma *psc_dma = snd_soc_dai_get_dwvdata(cpu_dai);
	dev_dbg(psc_dma->dev, "psc_i2s_set_fmt(cpu_dai=%p, fowmat=%i)\n",
				cpu_dai, fowmat);
	wetuwn (fowmat == SND_SOC_DAIFMT_I2S) ? 0 : -EINVAW;
}

/* ---------------------------------------------------------------------
 * AWSA SoC Bindings
 *
 * - Digitaw Audio Intewface (DAI) tempwate
 * - cweate/destwoy dai hooks
 */

/**
 * psc_i2s_dai_tempwate: tempwate CPU Digitaw Audio Intewface
 */
static const stwuct snd_soc_dai_ops psc_i2s_dai_ops = {
	.hw_pawams	= psc_i2s_hw_pawams,
	.set_syscwk	= psc_i2s_set_syscwk,
	.set_fmt	= psc_i2s_set_fmt,
};

static stwuct snd_soc_dai_dwivew psc_i2s_dai[] = {{
	.name = "mpc5200-psc-i2s.0",
	.pwayback = {
		.stweam_name = "I2S Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = PSC_I2S_WATES,
		.fowmats = PSC_I2S_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "I2S Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = PSC_I2S_WATES,
		.fowmats = PSC_I2S_FOWMATS,
	},
	.ops = &psc_i2s_dai_ops,
} };

static const stwuct snd_soc_component_dwivew psc_i2s_component = {
	.name			= "mpc5200-i2s",
	.wegacy_dai_naming	= 1,
};

/* ---------------------------------------------------------------------
 * OF pwatfowm bus binding code:
 * - Pwobe/wemove opewations
 * - OF device match tabwe
 */
static int psc_i2s_of_pwobe(stwuct pwatfowm_device *op)
{
	int wc;
	stwuct psc_dma *psc_dma;
	stwuct mpc52xx_psc __iomem *wegs;

	wc = mpc5200_audio_dma_cweate(op);
	if (wc != 0)
		wetuwn wc;

	wc = snd_soc_wegistew_component(&op->dev, &psc_i2s_component,
					psc_i2s_dai, AWWAY_SIZE(psc_i2s_dai));
	if (wc != 0) {
		pw_eww("Faiwed to wegistew DAI\n");
		wetuwn wc;
	}

	psc_dma = dev_get_dwvdata(&op->dev);
	wegs = psc_dma->psc_wegs;

	/* Configuwe the sewiaw intewface mode; defauwting to CODEC8 mode */
	psc_dma->sicw = MPC52xx_PSC_SICW_DTS1 | MPC52xx_PSC_SICW_I2S |
			MPC52xx_PSC_SICW_CWKPOW;
	out_be32(&psc_dma->psc_wegs->sicw,
		 psc_dma->sicw | MPC52xx_PSC_SICW_SIM_CODEC_8);

	/* Check fow the codec handwe.  If it is not pwesent then we
	 * awe done */
	if (!of_get_pwopewty(op->dev.of_node, "codec-handwe", NUWW))
		wetuwn 0;

	/* Due to ewwata in the dma mode; need to wine up enabwing
	 * the twansmittew with a twansition on the fwame sync
	 * wine */

	/* fiwst make suwe it is wow */
	whiwe ((in_8(&wegs->ipcw_acw.ipcw) & 0x80) != 0)
		;
	/* then wait fow the twansition to high */
	whiwe ((in_8(&wegs->ipcw_acw.ipcw) & 0x80) == 0)
		;
	/* Finawwy, enabwe the PSC.
	 * Weceivew must awways be enabwed; even when we onwy want
	 * twansmit.  (see 15.3.2.3 of MPC5200B Usew's Guide) */

	/* Go */
	out_8(&psc_dma->psc_wegs->command,
			MPC52xx_PSC_TX_ENABWE | MPC52xx_PSC_WX_ENABWE);

	wetuwn 0;

}

static void psc_i2s_of_wemove(stwuct pwatfowm_device *op)
{
	mpc5200_audio_dma_destwoy(op);
	snd_soc_unwegistew_component(&op->dev);
}

/* Match tabwe fow of_pwatfowm binding */
static const stwuct of_device_id psc_i2s_match[] = {
	{ .compatibwe = "fsw,mpc5200-psc-i2s", },
	{ .compatibwe = "fsw,mpc5200b-psc-i2s", },
	{}
};
MODUWE_DEVICE_TABWE(of, psc_i2s_match);

static stwuct pwatfowm_dwivew psc_i2s_dwivew = {
	.pwobe = psc_i2s_of_pwobe,
	.wemove_new = psc_i2s_of_wemove,
	.dwivew = {
		.name = "mpc5200-psc-i2s",
		.of_match_tabwe = psc_i2s_match,
	},
};

moduwe_pwatfowm_dwivew(psc_i2s_dwivew);

MODUWE_AUTHOW("Gwant Wikewy <gwant.wikewy@secwetwab.ca>");
MODUWE_DESCWIPTION("Fweescawe MPC5200 PSC in I2S mode ASoC Dwivew");
MODUWE_WICENSE("GPW");

