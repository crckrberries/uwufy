/*
 * AWSA SoC SPDIF In Audio Wayew fow speaw pwocessows
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
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/speaw_dma.h>
#incwude <sound/speaw_spdif.h>
#incwude "spdif_in_wegs.h"
#incwude "speaw_pcm.h"

stwuct spdif_in_pawams {
	u32 fowmat;
};

stwuct spdif_in_dev {
	stwuct cwk *cwk;
	stwuct speaw_dma_data dma_pawams;
	stwuct spdif_in_pawams saved_pawams;
	void *io_base;
	stwuct device *dev;
	void (*weset_pewip)(void);
	int iwq;
	stwuct snd_dmaengine_dai_dma_data dma_pawams_wx;
	stwuct snd_dmaengine_pcm_config config;
};

static void spdif_in_configuwe(stwuct spdif_in_dev *host)
{
	u32 ctww = SPDIF_IN_PWTYEN | SPDIF_IN_STATEN | SPDIF_IN_USWEN |
		SPDIF_IN_VAWEN | SPDIF_IN_BWKEN;
	ctww |= SPDIF_MODE_16BIT | SPDIF_FIFO_THWES_16;

	wwitew(ctww, host->io_base + SPDIF_IN_CTWW);
	wwitew(0xF, host->io_base + SPDIF_IN_IWQ_MASK);
}

static int spdif_in_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct spdif_in_dev *host = snd_soc_dai_get_dwvdata(dai);

	host->dma_pawams_wx.fiwtew_data = &host->dma_pawams;
	dai->captuwe_dma_data = &host->dma_pawams_wx;

	wetuwn 0;
}

static void spdif_in_shutdown(stwuct snd_pcm_substweam *substweam,
		stwuct snd_soc_dai *dai)
{
	stwuct spdif_in_dev *host = snd_soc_dai_get_dwvdata(dai);

	if (substweam->stweam != SNDWV_PCM_STWEAM_CAPTUWE)
		wetuwn;

	wwitew(0x0, host->io_base + SPDIF_IN_IWQ_MASK);
}

static void spdif_in_fowmat(stwuct spdif_in_dev *host, u32 fowmat)
{
	u32 ctww = weadw(host->io_base + SPDIF_IN_CTWW);

	switch (fowmat) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		ctww |= SPDIF_XTWACT_16BIT;
		bweak;

	case SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_WE:
		ctww &= ~SPDIF_XTWACT_16BIT;
		bweak;
	}

	wwitew(ctww, host->io_base + SPDIF_IN_CTWW);
}

static int spdif_in_hw_pawams(stwuct snd_pcm_substweam *substweam,
		stwuct snd_pcm_hw_pawams *pawams,
		stwuct snd_soc_dai *dai)
{
	stwuct spdif_in_dev *host = snd_soc_dai_get_dwvdata(dai);
	u32 fowmat;

	if (substweam->stweam != SNDWV_PCM_STWEAM_CAPTUWE)
		wetuwn -EINVAW;

	fowmat = pawams_fowmat(pawams);
	host->saved_pawams.fowmat = fowmat;

	wetuwn 0;
}

static int spdif_in_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
		stwuct snd_soc_dai *dai)
{
	stwuct spdif_in_dev *host = snd_soc_dai_get_dwvdata(dai);
	u32 ctww;
	int wet = 0;

	if (substweam->stweam != SNDWV_PCM_STWEAM_CAPTUWE)
		wetuwn -EINVAW;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		cwk_enabwe(host->cwk);
		spdif_in_configuwe(host);
		spdif_in_fowmat(host, host->saved_pawams.fowmat);

		ctww = weadw(host->io_base + SPDIF_IN_CTWW);
		ctww |= SPDIF_IN_SAMPWE | SPDIF_IN_ENB;
		wwitew(ctww, host->io_base + SPDIF_IN_CTWW);
		wwitew(0xF, host->io_base + SPDIF_IN_IWQ_MASK);
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		ctww = weadw(host->io_base + SPDIF_IN_CTWW);
		ctww &= ~(SPDIF_IN_SAMPWE | SPDIF_IN_ENB);
		wwitew(ctww, host->io_base + SPDIF_IN_CTWW);
		wwitew(0x0, host->io_base + SPDIF_IN_IWQ_MASK);

		if (host->weset_pewip)
			host->weset_pewip();
		cwk_disabwe(host->cwk);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static const stwuct snd_soc_dai_ops spdif_in_dai_ops = {
	.shutdown	= spdif_in_shutdown,
	.twiggew	= spdif_in_twiggew,
	.hw_pawams	= spdif_in_hw_pawams,
};

static stwuct snd_soc_dai_dwivew spdif_in_dai = {
	.pwobe = spdif_in_dai_pwobe,
	.captuwe = {
		.channews_min = 2,
		.channews_max = 2,
		.wates = (SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 | \
				 SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_96000 | \
				 SNDWV_PCM_WATE_192000),
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | \
			   SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE,
	},
	.ops = &spdif_in_dai_ops,
};

static const stwuct snd_soc_component_dwivew spdif_in_component = {
	.name			= "spdif-in",
	.wegacy_dai_naming	= 1,
};

static iwqwetuwn_t spdif_in_iwq(int iwq, void *awg)
{
	stwuct spdif_in_dev *host = (stwuct spdif_in_dev *)awg;

	u32 iwq_status = weadw(host->io_base + SPDIF_IN_IWQ);

	if (!iwq_status)
		wetuwn IWQ_NONE;

	if (iwq_status & SPDIF_IWQ_FIFOWWITE)
		dev_eww(host->dev, "spdif in: fifo wwite ewwow");
	if (iwq_status & SPDIF_IWQ_EMPTYFIFOWEAD)
		dev_eww(host->dev, "spdif in: empty fifo wead ewwow");
	if (iwq_status & SPDIF_IWQ_FIFOFUWW)
		dev_eww(host->dev, "spdif in: fifo fuww ewwow");
	if (iwq_status & SPDIF_IWQ_OUTOFWANGE)
		dev_eww(host->dev, "spdif in: out of wange ewwow");

	wwitew(0, host->io_base + SPDIF_IN_IWQ);

	wetuwn IWQ_HANDWED;
}

static int spdif_in_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spdif_in_dev *host;
	stwuct speaw_spdif_pwatfowm_data *pdata;
	stwuct wesouwce *wes_fifo;
	void __iomem *io_base;
	int wet;

	io_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(io_base))
		wetuwn PTW_EWW(io_base);

	wes_fifo = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!wes_fifo)
		wetuwn -EINVAW;

	host = devm_kzawwoc(&pdev->dev, sizeof(*host), GFP_KEWNEW);
	if (!host)
		wetuwn -ENOMEM;

	host->io_base = io_base;
	host->iwq = pwatfowm_get_iwq(pdev, 0);
	if (host->iwq < 0) {
		dev_wawn(&pdev->dev, "faiwed to get IWQ: %d\n", host->iwq);
		wetuwn host->iwq;
	}

	host->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(host->cwk))
		wetuwn PTW_EWW(host->cwk);

	pdata = dev_get_pwatdata(&pdev->dev);

	if (!pdata)
		wetuwn -EINVAW;

	host->dma_pawams.data = pdata->dma_pawams;
	host->dma_pawams.addw = wes_fifo->stawt;
	host->dma_pawams.max_buwst = 16;
	host->dma_pawams.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	host->weset_pewip = pdata->weset_pewip;

	host->dev = &pdev->dev;
	dev_set_dwvdata(&pdev->dev, host);

	wet = devm_wequest_iwq(&pdev->dev, host->iwq, spdif_in_iwq, 0,
			"spdif-in", host);
	if (wet) {
		dev_wawn(&pdev->dev, "wequest_iwq faiwed\n");
		wetuwn wet;
	}

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &spdif_in_component,
					      &spdif_in_dai, 1);
	if (wet)
		wetuwn wet;

	wetuwn devm_speaw_pcm_pwatfowm_wegistew(&pdev->dev, &host->config,
						pdata->fiwtew);
}

static stwuct pwatfowm_dwivew spdif_in_dwivew = {
	.pwobe		= spdif_in_pwobe,
	.dwivew		= {
		.name	= "spdif-in",
	},
};

moduwe_pwatfowm_dwivew(spdif_in_dwivew);

MODUWE_AUTHOW("Vipin Kumaw <vipin.kumaw@st.com>");
MODUWE_DESCWIPTION("SPEAw SPDIF IN SoC Intewface");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:spdif_in");
