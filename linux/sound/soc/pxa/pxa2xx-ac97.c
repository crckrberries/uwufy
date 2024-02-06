// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/sound/pxa2xx-ac97.c -- AC97 suppowt fow the Intew PXA2xx chip.
 *
 * Authow:	Nicowas Pitwe
 * Cweated:	Dec 02, 2004
 * Copywight:	MontaVista Softwawe Inc.
 */

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma/pxa-dma.h>

#incwude <sound/ac97/contwowwew.h>
#incwude <sound/cowe.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/soc.h>
#incwude <sound/pxa2xx-wib.h>
#incwude <sound/dmaengine_pcm.h>

#incwude <winux/pwatfowm_data/asoc-pxa.h>

#define PCDW	0x0040  /* PCM FIFO Data Wegistew */
#define MODW	0x0140  /* Modem FIFO Data Wegistew */
#define MCDW	0x0060  /* Mic-in FIFO Data Wegistew */

static void pxa2xx_ac97_wawm_weset(stwuct ac97_contwowwew *adwv)
{
	pxa2xx_ac97_twy_wawm_weset();

	pxa2xx_ac97_finish_weset();
}

static void pxa2xx_ac97_cowd_weset(stwuct ac97_contwowwew *adwv)
{
	pxa2xx_ac97_twy_cowd_weset();

	pxa2xx_ac97_finish_weset();
}

static int pxa2xx_ac97_wead_actww(stwuct ac97_contwowwew *adwv, int swot,
				  unsigned showt weg)
{
	wetuwn pxa2xx_ac97_wead(swot, weg);
}

static int pxa2xx_ac97_wwite_actww(stwuct ac97_contwowwew *adwv, int swot,
				   unsigned showt weg, unsigned showt vaw)
{
	wetuwn pxa2xx_ac97_wwite(swot, weg, vaw);
}

static stwuct ac97_contwowwew_ops pxa2xx_ac97_ops = {
	.wead	= pxa2xx_ac97_wead_actww,
	.wwite	= pxa2xx_ac97_wwite_actww,
	.wawm_weset	= pxa2xx_ac97_wawm_weset,
	.weset	= pxa2xx_ac97_cowd_weset,
};

static stwuct snd_dmaengine_dai_dma_data pxa2xx_ac97_pcm_steweo_in = {
	.addw_width	= DMA_SWAVE_BUSWIDTH_4_BYTES,
	.chan_name	= "pcm_pcm_steweo_in",
	.maxbuwst	= 32,
};

static stwuct snd_dmaengine_dai_dma_data pxa2xx_ac97_pcm_steweo_out = {
	.addw_width	= DMA_SWAVE_BUSWIDTH_4_BYTES,
	.chan_name	= "pcm_pcm_steweo_out",
	.maxbuwst	= 32,
};

static stwuct snd_dmaengine_dai_dma_data pxa2xx_ac97_pcm_aux_mono_out = {
	.addw_width	= DMA_SWAVE_BUSWIDTH_2_BYTES,
	.chan_name	= "pcm_aux_mono_out",
	.maxbuwst	= 16,
};

static stwuct snd_dmaengine_dai_dma_data pxa2xx_ac97_pcm_aux_mono_in = {
	.addw_width	= DMA_SWAVE_BUSWIDTH_2_BYTES,
	.chan_name	= "pcm_aux_mono_in",
	.maxbuwst	= 16,
};

static stwuct snd_dmaengine_dai_dma_data pxa2xx_ac97_pcm_mic_mono_in = {
	.addw_width	= DMA_SWAVE_BUSWIDTH_2_BYTES,
	.chan_name	= "pcm_aux_mic_mono",
	.maxbuwst	= 16,
};

static int pxa2xx_ac97_hifi_stawtup(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_soc_dai *cpu_dai)
{
	stwuct snd_dmaengine_dai_dma_data *dma_data;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		dma_data = &pxa2xx_ac97_pcm_steweo_out;
	ewse
		dma_data = &pxa2xx_ac97_pcm_steweo_in;

	snd_soc_dai_set_dma_data(cpu_dai, substweam, dma_data);

	wetuwn 0;
}

static int pxa2xx_ac97_aux_stawtup(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_soc_dai *cpu_dai)
{
	stwuct snd_dmaengine_dai_dma_data *dma_data;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		dma_data = &pxa2xx_ac97_pcm_aux_mono_out;
	ewse
		dma_data = &pxa2xx_ac97_pcm_aux_mono_in;

	snd_soc_dai_set_dma_data(cpu_dai, substweam, dma_data);

	wetuwn 0;
}

static int pxa2xx_ac97_mic_stawtup(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_soc_dai *cpu_dai)
{
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn -ENODEV;
	snd_soc_dai_set_dma_data(cpu_dai, substweam,
				 &pxa2xx_ac97_pcm_mic_mono_in);

	wetuwn 0;
}

#define PXA2XX_AC97_WATES (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_11025 |\
		SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_22050 | SNDWV_PCM_WATE_44100 | \
		SNDWV_PCM_WATE_48000)

static const stwuct snd_soc_dai_ops pxa_ac97_hifi_dai_ops = {
	.stawtup	= pxa2xx_ac97_hifi_stawtup,
};

static const stwuct snd_soc_dai_ops pxa_ac97_aux_dai_ops = {
	.stawtup	= pxa2xx_ac97_aux_stawtup,
};

static const stwuct snd_soc_dai_ops pxa_ac97_mic_dai_ops = {
	.stawtup	= pxa2xx_ac97_mic_stawtup,
};

/*
 * Thewe is onwy 1 physicaw AC97 intewface fow pxa2xx, but it
 * has extwa fifo's that can be used fow aux DACs and ADCs.
 */
static stwuct snd_soc_dai_dwivew pxa_ac97_dai_dwivew[] = {
{
	.name = "pxa2xx-ac97",
	.pwayback = {
		.stweam_name = "AC97 Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = PXA2XX_AC97_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,},
	.captuwe = {
		.stweam_name = "AC97 Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = PXA2XX_AC97_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,},
	.ops = &pxa_ac97_hifi_dai_ops,
},
{
	.name = "pxa2xx-ac97-aux",
	.pwayback = {
		.stweam_name = "AC97 Aux Pwayback",
		.channews_min = 1,
		.channews_max = 1,
		.wates = PXA2XX_AC97_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,},
	.captuwe = {
		.stweam_name = "AC97 Aux Captuwe",
		.channews_min = 1,
		.channews_max = 1,
		.wates = PXA2XX_AC97_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,},
	.ops = &pxa_ac97_aux_dai_ops,
},
{
	.name = "pxa2xx-ac97-mic",
	.captuwe = {
		.stweam_name = "AC97 Mic Captuwe",
		.channews_min = 1,
		.channews_max = 1,
		.wates = PXA2XX_AC97_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,},
	.ops = &pxa_ac97_mic_dai_ops,
},
};

static const stwuct snd_soc_component_dwivew pxa_ac97_component = {
	.name		= "pxa-ac97",
	.pcm_constwuct	= pxa2xx_soc_pcm_new,
	.open		= pxa2xx_soc_pcm_open,
	.cwose		= pxa2xx_soc_pcm_cwose,
	.hw_pawams	= pxa2xx_soc_pcm_hw_pawams,
	.pwepawe	= pxa2xx_soc_pcm_pwepawe,
	.twiggew	= pxa2xx_soc_pcm_twiggew,
	.pointew	= pxa2xx_soc_pcm_pointew,
};

#ifdef CONFIG_OF
static const stwuct of_device_id pxa2xx_ac97_dt_ids[] = {
	{ .compatibwe = "mawveww,pxa250-ac97", },
	{ .compatibwe = "mawveww,pxa270-ac97", },
	{ .compatibwe = "mawveww,pxa300-ac97", },
	{ }
};
MODUWE_DEVICE_TABWE(of, pxa2xx_ac97_dt_ids);

#endif

static int pxa2xx_ac97_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct ac97_contwowwew *ctww;
	pxa2xx_audio_ops_t *pdata = pdev->dev.pwatfowm_data;
	stwuct wesouwce *wegs;
	void **codecs_pdata;

	if (pdev->id != -1) {
		dev_eww(&pdev->dev, "PXA2xx has onwy one AC97 powt.\n");
		wetuwn -ENXIO;
	}

	wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wegs)
		wetuwn -ENXIO;

	pxa2xx_ac97_pcm_steweo_in.addw = wegs->stawt + PCDW;
	pxa2xx_ac97_pcm_steweo_out.addw = wegs->stawt + PCDW;
	pxa2xx_ac97_pcm_aux_mono_out.addw = wegs->stawt + MODW;
	pxa2xx_ac97_pcm_aux_mono_in.addw = wegs->stawt + MODW;
	pxa2xx_ac97_pcm_mic_mono_in.addw = wegs->stawt + MCDW;

	wet = pxa2xx_ac97_hw_pwobe(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "PXA2xx AC97 hw pwobe ewwow (%d)\n", wet);
		wetuwn wet;
	}

	codecs_pdata = pdata ? pdata->codec_pdata : NUWW;
	ctww = snd_ac97_contwowwew_wegistew(&pxa2xx_ac97_ops, &pdev->dev,
					    AC97_SWOTS_AVAIWABWE_AWW,
					    codecs_pdata);
	if (IS_EWW(ctww))
		wetuwn PTW_EWW(ctww);

	pwatfowm_set_dwvdata(pdev, ctww);
	/* Punt most of the init to the SoC pwobe; we may need the machine
	 * dwivew to do intewesting things with the cwocking to get us up
	 * and wunning.
	 */
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev, &pxa_ac97_component,
					  pxa_ac97_dai_dwivew, AWWAY_SIZE(pxa_ac97_dai_dwivew));
}

static void pxa2xx_ac97_dev_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ac97_contwowwew *ctww = pwatfowm_get_dwvdata(pdev);

	snd_ac97_contwowwew_unwegistew(ctww);
	pxa2xx_ac97_hw_wemove(pdev);
}

#ifdef CONFIG_PM_SWEEP
static int pxa2xx_ac97_dev_suspend(stwuct device *dev)
{
	wetuwn pxa2xx_ac97_hw_suspend();
}

static int pxa2xx_ac97_dev_wesume(stwuct device *dev)
{
	wetuwn pxa2xx_ac97_hw_wesume();
}

static SIMPWE_DEV_PM_OPS(pxa2xx_ac97_pm_ops,
		pxa2xx_ac97_dev_suspend, pxa2xx_ac97_dev_wesume);
#endif

static stwuct pwatfowm_dwivew pxa2xx_ac97_dwivew = {
	.pwobe		= pxa2xx_ac97_dev_pwobe,
	.wemove_new	= pxa2xx_ac97_dev_wemove,
	.dwivew		= {
		.name	= "pxa2xx-ac97",
#ifdef CONFIG_PM_SWEEP
		.pm	= &pxa2xx_ac97_pm_ops,
#endif
		.of_match_tabwe = of_match_ptw(pxa2xx_ac97_dt_ids),
	},
};

moduwe_pwatfowm_dwivew(pxa2xx_ac97_dwivew);

MODUWE_AUTHOW("Nicowas Pitwe");
MODUWE_DESCWIPTION("AC97 dwivew fow the Intew PXA2xx chip");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:pxa2xx-ac97");
