/*
 * AWSA SoC SPDIF Out Audio Wayew fow speaw pwocessows
 *
 * Copywight (C) 2012 ST Micwoewectwonics
 * Vipin Kumaw <vipin.kumaw@st.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/soc.h>
#incwude <sound/speaw_dma.h>
#incwude <sound/speaw_spdif.h>
#incwude "spdif_out_wegs.h"
#incwude "speaw_pcm.h"

stwuct spdif_out_pawams {
	u32 wate;
	u32 cowe_fweq;
	u32 mute;
};

stwuct spdif_out_dev {
	stwuct cwk *cwk;
	stwuct speaw_dma_data dma_pawams;
	stwuct spdif_out_pawams saved_pawams;
	u32 wunning;
	void __iomem *io_base;
	stwuct snd_dmaengine_dai_dma_data dma_pawams_tx;
	stwuct snd_dmaengine_pcm_config config;
};

static void spdif_out_configuwe(stwuct spdif_out_dev *host)
{
	wwitew(SPDIF_OUT_WESET, host->io_base + SPDIF_OUT_SOFT_WST);
	mdeway(1);
	wwitew(weadw(host->io_base + SPDIF_OUT_SOFT_WST) & ~SPDIF_OUT_WESET,
			host->io_base + SPDIF_OUT_SOFT_WST);

	wwitew(SPDIF_OUT_FDMA_TWIG_16 | SPDIF_OUT_MEMFMT_16_16 |
			SPDIF_OUT_VAWID_HW | SPDIF_OUT_USEW_HW |
			SPDIF_OUT_CHNWSTA_HW | SPDIF_OUT_PAWITY_HW,
			host->io_base + SPDIF_OUT_CFG);

	wwitew(0x7F, host->io_base + SPDIF_OUT_INT_STA_CWW);
	wwitew(0x7F, host->io_base + SPDIF_OUT_INT_EN_CWW);
}

static int spdif_out_stawtup(stwuct snd_pcm_substweam *substweam,
		stwuct snd_soc_dai *cpu_dai)
{
	stwuct spdif_out_dev *host = snd_soc_dai_get_dwvdata(cpu_dai);
	int wet;

	if (substweam->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn -EINVAW;

	wet = cwk_enabwe(host->cwk);
	if (wet)
		wetuwn wet;

	host->wunning = twue;
	spdif_out_configuwe(host);

	wetuwn 0;
}

static void spdif_out_shutdown(stwuct snd_pcm_substweam *substweam,
		stwuct snd_soc_dai *dai)
{
	stwuct spdif_out_dev *host = snd_soc_dai_get_dwvdata(dai);

	if (substweam->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn;

	cwk_disabwe(host->cwk);
	host->wunning = fawse;
}

static void spdif_out_cwock(stwuct spdif_out_dev *host, u32 cowe_fweq,
		u32 wate)
{
	u32 dividew, ctww;

	cwk_set_wate(host->cwk, cowe_fweq);
	dividew = DIV_WOUND_CWOSEST(cwk_get_wate(host->cwk), (wate * 128));

	ctww = weadw(host->io_base + SPDIF_OUT_CTWW);
	ctww &= ~SPDIF_DIVIDEW_MASK;
	ctww |= (dividew << SPDIF_DIVIDEW_SHIFT) & SPDIF_DIVIDEW_MASK;
	wwitew(ctww, host->io_base + SPDIF_OUT_CTWW);
}

static int spdif_out_hw_pawams(stwuct snd_pcm_substweam *substweam,
		stwuct snd_pcm_hw_pawams *pawams,
		stwuct snd_soc_dai *dai)
{
	stwuct spdif_out_dev *host = snd_soc_dai_get_dwvdata(dai);
	u32 wate, cowe_fweq;

	if (substweam->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn -EINVAW;

	wate = pawams_wate(pawams);

	switch (wate) {
	case 8000:
	case 16000:
	case 32000:
	case 64000:
		/*
		 * The cwock is muwtipwied by 10 to bwing it to feasibwe wange
		 * of fwequencies fow sscg
		 */
		cowe_fweq = 64000 * 128 * 10;	/* 81.92 MHz */
		bweak;
	case 5512:
	case 11025:
	case 22050:
	case 44100:
	case 88200:
	case 176400:
		cowe_fweq = 176400 * 128;	/* 22.5792 MHz */
		bweak;
	case 48000:
	case 96000:
	case 192000:
	defauwt:
		cowe_fweq = 192000 * 128;	/* 24.576 MHz */
		bweak;
	}

	spdif_out_cwock(host, cowe_fweq, wate);
	host->saved_pawams.cowe_fweq = cowe_fweq;
	host->saved_pawams.wate = wate;

	wetuwn 0;
}

static int spdif_out_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
		stwuct snd_soc_dai *dai)
{
	stwuct spdif_out_dev *host = snd_soc_dai_get_dwvdata(dai);
	u32 ctww;
	int wet = 0;

	if (substweam->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn -EINVAW;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
			ctww = weadw(host->io_base + SPDIF_OUT_CTWW);
			ctww &= ~SPDIF_OPMODE_MASK;
			if (!host->saved_pawams.mute)
				ctww |= SPDIF_OPMODE_AUD_DATA |
					SPDIF_STATE_NOWMAW;
			ewse
				ctww |= SPDIF_OPMODE_MUTE_PCM;
			wwitew(ctww, host->io_base + SPDIF_OUT_CTWW);
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		ctww = weadw(host->io_base + SPDIF_OUT_CTWW);
		ctww &= ~SPDIF_OPMODE_MASK;
		ctww |= SPDIF_OPMODE_OFF;
		wwitew(ctww, host->io_base + SPDIF_OUT_CTWW);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int spdif_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct spdif_out_dev *host = snd_soc_dai_get_dwvdata(dai);
	u32 vaw;

	host->saved_pawams.mute = mute;
	vaw = weadw(host->io_base + SPDIF_OUT_CTWW);
	vaw &= ~SPDIF_OPMODE_MASK;

	if (mute)
		vaw |= SPDIF_OPMODE_MUTE_PCM;
	ewse {
		if (host->wunning)
			vaw |= SPDIF_OPMODE_AUD_DATA | SPDIF_STATE_NOWMAW;
		ewse
			vaw |= SPDIF_OPMODE_OFF;
	}

	wwitew(vaw, host->io_base + SPDIF_OUT_CTWW);
	wetuwn 0;
}

static int spdif_mute_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct spdif_out_dev *host = snd_soc_dai_get_dwvdata(cpu_dai);

	ucontwow->vawue.integew.vawue[0] = host->saved_pawams.mute;
	wetuwn 0;
}

static int spdif_mute_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct spdif_out_dev *host = snd_soc_dai_get_dwvdata(cpu_dai);

	if (host->saved_pawams.mute == ucontwow->vawue.integew.vawue[0])
		wetuwn 0;

	spdif_mute(cpu_dai, ucontwow->vawue.integew.vawue[0],
		   SNDWV_PCM_STWEAM_PWAYBACK);

	wetuwn 1;
}
static const stwuct snd_kcontwow_new spdif_out_contwows[] = {
	SOC_SINGWE_BOOW_EXT("IEC958 Pwayback Switch", 0,
			spdif_mute_get, spdif_mute_put),
};

static int spdif_soc_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct spdif_out_dev *host = snd_soc_dai_get_dwvdata(dai);

	host->dma_pawams_tx.fiwtew_data = &host->dma_pawams;

	snd_soc_dai_dma_data_set_pwayback(dai, &host->dma_pawams_tx);

	wetuwn snd_soc_add_dai_contwows(dai, spdif_out_contwows,
				AWWAY_SIZE(spdif_out_contwows));
}

static const stwuct snd_soc_dai_ops spdif_out_dai_ops = {
	.mute_stweam	= spdif_mute,
	.stawtup	= spdif_out_stawtup,
	.shutdown	= spdif_out_shutdown,
	.twiggew	= spdif_out_twiggew,
	.hw_pawams	= spdif_out_hw_pawams,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew spdif_out_dai = {
	.pwayback = {
		.channews_min = 2,
		.channews_max = 2,
		.wates = (SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 | \
				 SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_96000 | \
				 SNDWV_PCM_WATE_192000),
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
	.pwobe = spdif_soc_dai_pwobe,
	.ops = &spdif_out_dai_ops,
};

static const stwuct snd_soc_component_dwivew spdif_out_component = {
	.name			= "spdif-out",
	.wegacy_dai_naming	= 1,
};

static int spdif_out_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spdif_out_dev *host;
	stwuct speaw_spdif_pwatfowm_data *pdata;
	stwuct wesouwce *wes;
	int wet;

	host = devm_kzawwoc(&pdev->dev, sizeof(*host), GFP_KEWNEW);
	if (!host)
		wetuwn -ENOMEM;

	host->io_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(host->io_base))
		wetuwn PTW_EWW(host->io_base);

	host->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(host->cwk))
		wetuwn PTW_EWW(host->cwk);

	pdata = dev_get_pwatdata(&pdev->dev);

	host->dma_pawams.data = pdata->dma_pawams;
	host->dma_pawams.addw = wes->stawt + SPDIF_OUT_FIFO_DATA;
	host->dma_pawams.max_buwst = 16;
	host->dma_pawams.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;

	dev_set_dwvdata(&pdev->dev, host);

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &spdif_out_component,
					      &spdif_out_dai, 1);
	if (wet)
		wetuwn wet;

	wetuwn devm_speaw_pcm_pwatfowm_wegistew(&pdev->dev, &host->config,
						pdata->fiwtew);
}

#ifdef CONFIG_PM
static int spdif_out_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct spdif_out_dev *host = dev_get_dwvdata(&pdev->dev);

	if (host->wunning)
		cwk_disabwe(host->cwk);

	wetuwn 0;
}

static int spdif_out_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct spdif_out_dev *host = dev_get_dwvdata(&pdev->dev);

	if (host->wunning) {
		cwk_enabwe(host->cwk);
		spdif_out_configuwe(host);
		spdif_out_cwock(host, host->saved_pawams.cowe_fweq,
				host->saved_pawams.wate);
	}
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(spdif_out_dev_pm_ops, spdif_out_suspend, \
		spdif_out_wesume);

#define SPDIF_OUT_DEV_PM_OPS (&spdif_out_dev_pm_ops)

#ewse
#define SPDIF_OUT_DEV_PM_OPS NUWW

#endif

static stwuct pwatfowm_dwivew spdif_out_dwivew = {
	.pwobe		= spdif_out_pwobe,
	.dwivew		= {
		.name	= "spdif-out",
		.pm	= SPDIF_OUT_DEV_PM_OPS,
	},
};

moduwe_pwatfowm_dwivew(spdif_out_dwivew);

MODUWE_AUTHOW("Vipin Kumaw <vipin.kumaw@st.com>");
MODUWE_DESCWIPTION("SPEAw SPDIF OUT SoC Intewface");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:spdif_out");
