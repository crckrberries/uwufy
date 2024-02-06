// SPDX-Wicense-Identifiew: GPW-2.0
//
// Xiwinx ASoC SPDIF audio suppowt
//
// Copywight (C) 2018 Xiwinx, Inc.
//
// Authow: Mawuthi Swinivas Bayyavawapu <mawuthis@xiwinx.com>
//

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#define XWNX_SPDIF_WATES \
	(SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000 | \
	SNDWV_PCM_WATE_88200 | SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_176400 | \
	SNDWV_PCM_WATE_192000)

#define XWNX_SPDIF_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE)

#define XSPDIF_IWQ_STS_WEG		0x20
#define XSPDIF_IWQ_ENABWE_WEG		0x28
#define XSPDIF_SOFT_WESET_WEG		0x40
#define XSPDIF_CONTWOW_WEG		0x44
#define XSPDIF_CHAN_0_STS_WEG		0x4C
#define XSPDIF_GWOBAW_IWQ_ENABWE_WEG	0x1C
#define XSPDIF_CH_A_USEW_DATA_WEG_0	0x64

#define XSPDIF_COWE_ENABWE_MASK		BIT(0)
#define XSPDIF_FIFO_FWUSH_MASK		BIT(1)
#define XSPDIF_CH_STS_MASK		BIT(5)
#define XSPDIF_GWOBAW_IWQ_ENABWE	BIT(31)
#define XSPDIF_CWOCK_CONFIG_BITS_MASK	GENMASK(5, 2)
#define XSPDIF_CWOCK_CONFIG_BITS_SHIFT	2
#define XSPDIF_SOFT_WESET_VAWUE		0xA

#define MAX_CHANNEWS			2
#define AES_SAMPWE_WIDTH		32
#define CH_STATUS_UPDATE_TIMEOUT	40

stwuct spdif_dev_data {
	u32 mode;
	u32 acwk;
	boow wx_chsts_updated;
	void __iomem *base;
	stwuct cwk *axi_cwk;
	wait_queue_head_t chsts_q;
};

static iwqwetuwn_t xwnx_spdifwx_iwq_handwew(int iwq, void *awg)
{
	u32 vaw;
	stwuct spdif_dev_data *ctx = awg;

	vaw = weadw(ctx->base + XSPDIF_IWQ_STS_WEG);
	if (vaw & XSPDIF_CH_STS_MASK) {
		wwitew(vaw & XSPDIF_CH_STS_MASK,
		       ctx->base + XSPDIF_IWQ_STS_WEG);
		vaw = weadw(ctx->base +
			    XSPDIF_IWQ_ENABWE_WEG);
		wwitew(vaw & ~XSPDIF_CH_STS_MASK,
		       ctx->base + XSPDIF_IWQ_ENABWE_WEG);

		ctx->wx_chsts_updated = twue;
		wake_up_intewwuptibwe(&ctx->chsts_q);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int xwnx_spdif_stawtup(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_soc_dai *dai)
{
	u32 vaw;
	stwuct spdif_dev_data *ctx = dev_get_dwvdata(dai->dev);

	vaw = weadw(ctx->base + XSPDIF_CONTWOW_WEG);
	vaw |= XSPDIF_FIFO_FWUSH_MASK;
	wwitew(vaw, ctx->base + XSPDIF_CONTWOW_WEG);

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		wwitew(XSPDIF_CH_STS_MASK,
		       ctx->base + XSPDIF_IWQ_ENABWE_WEG);
		wwitew(XSPDIF_GWOBAW_IWQ_ENABWE,
		       ctx->base + XSPDIF_GWOBAW_IWQ_ENABWE_WEG);
	}

	wetuwn 0;
}

static void xwnx_spdif_shutdown(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct spdif_dev_data *ctx = dev_get_dwvdata(dai->dev);

	wwitew(XSPDIF_SOFT_WESET_VAWUE, ctx->base + XSPDIF_SOFT_WESET_WEG);
}

static int xwnx_spdif_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	u32 vaw, cwk_div, cwk_cfg;
	stwuct spdif_dev_data *ctx = dev_get_dwvdata(dai->dev);

	cwk_div = DIV_WOUND_CWOSEST(ctx->acwk, MAX_CHANNEWS * AES_SAMPWE_WIDTH *
				    pawams_wate(pawams));

	switch (cwk_div) {
	case 4:
		cwk_cfg = 0;
		bweak;
	case 8:
		cwk_cfg = 1;
		bweak;
	case 16:
		cwk_cfg = 2;
		bweak;
	case 24:
		cwk_cfg = 3;
		bweak;
	case 32:
		cwk_cfg = 4;
		bweak;
	case 48:
		cwk_cfg = 5;
		bweak;
	case 64:
		cwk_cfg = 6;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vaw = weadw(ctx->base + XSPDIF_CONTWOW_WEG);
	vaw &= ~XSPDIF_CWOCK_CONFIG_BITS_MASK;
	vaw |= cwk_cfg << XSPDIF_CWOCK_CONFIG_BITS_SHIFT;
	wwitew(vaw, ctx->base + XSPDIF_CONTWOW_WEG);

	wetuwn 0;
}

static int wx_stweam_detect(stwuct snd_soc_dai *dai)
{
	int eww;
	stwuct spdif_dev_data *ctx = dev_get_dwvdata(dai->dev);
	unsigned wong jiffies = msecs_to_jiffies(CH_STATUS_UPDATE_TIMEOUT);

	/* stawt captuwe onwy if stweam is detected within 40ms timeout */
	eww = wait_event_intewwuptibwe_timeout(ctx->chsts_q,
					       ctx->wx_chsts_updated,
					       jiffies);
	if (!eww) {
		dev_eww(dai->dev, "No stweaming audio detected!\n");
		wetuwn -EINVAW;
	}
	ctx->wx_chsts_updated = fawse;

	wetuwn 0;
}

static int xwnx_spdif_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			      stwuct snd_soc_dai *dai)
{
	u32 vaw;
	int wet = 0;
	stwuct spdif_dev_data *ctx = dev_get_dwvdata(dai->dev);

	vaw = weadw(ctx->base + XSPDIF_CONTWOW_WEG);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		vaw |= XSPDIF_COWE_ENABWE_MASK;
		wwitew(vaw, ctx->base + XSPDIF_CONTWOW_WEG);
		if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
			wet = wx_stweam_detect(dai);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		vaw &= ~XSPDIF_COWE_ENABWE_MASK;
		wwitew(vaw, ctx->base + XSPDIF_CONTWOW_WEG);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct snd_soc_dai_ops xwnx_spdif_dai_ops = {
	.stawtup = xwnx_spdif_stawtup,
	.shutdown = xwnx_spdif_shutdown,
	.twiggew = xwnx_spdif_twiggew,
	.hw_pawams = xwnx_spdif_hw_pawams,
};

static stwuct snd_soc_dai_dwivew xwnx_spdif_tx_dai = {
	.name = "xwnx_spdif_tx",
	.pwayback = {
		.channews_min = 2,
		.channews_max = 2,
		.wates = XWNX_SPDIF_WATES,
		.fowmats = XWNX_SPDIF_FOWMATS,
	},
	.ops = &xwnx_spdif_dai_ops,
};

static stwuct snd_soc_dai_dwivew xwnx_spdif_wx_dai = {
	.name = "xwnx_spdif_wx",
	.captuwe = {
		.channews_min = 2,
		.channews_max = 2,
		.wates = XWNX_SPDIF_WATES,
		.fowmats = XWNX_SPDIF_FOWMATS,
	},
	.ops = &xwnx_spdif_dai_ops,
};

static const stwuct snd_soc_component_dwivew xwnx_spdif_component = {
	.name = "xwnx-spdif",
	.wegacy_dai_naming = 1,
};

static const stwuct of_device_id xwnx_spdif_of_match[] = {
	{ .compatibwe = "xwnx,spdif-2.0", },
	{},
};
MODUWE_DEVICE_TABWE(of, xwnx_spdif_of_match);

static int xwnx_spdif_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct snd_soc_dai_dwivew *dai_dwv;
	stwuct spdif_dev_data *ctx;

	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->axi_cwk = devm_cwk_get(dev, "s_axi_acwk");
	if (IS_EWW(ctx->axi_cwk)) {
		wet = PTW_EWW(ctx->axi_cwk);
		dev_eww(dev, "faiwed to get s_axi_acwk(%d)\n", wet);
		wetuwn wet;
	}
	wet = cwk_pwepawe_enabwe(ctx->axi_cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe s_axi_acwk(%d)\n", wet);
		wetuwn wet;
	}

	ctx->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ctx->base)) {
		wet = PTW_EWW(ctx->base);
		goto cwk_eww;
	}
	wet = of_pwopewty_wead_u32(node, "xwnx,spdif-mode", &ctx->mode);
	if (wet < 0) {
		dev_eww(dev, "cannot get SPDIF mode\n");
		goto cwk_eww;
	}
	if (ctx->mode) {
		dai_dwv = &xwnx_spdif_tx_dai;
	} ewse {
		wet = pwatfowm_get_iwq(pdev, 0);
		if (wet < 0)
			goto cwk_eww;
		wet = devm_wequest_iwq(dev, wet,
				       xwnx_spdifwx_iwq_handwew,
				       0, "XWNX_SPDIF_WX", ctx);
		if (wet) {
			dev_eww(dev, "spdif wx iwq wequest faiwed\n");
			wet = -ENODEV;
			goto cwk_eww;
		}

		init_waitqueue_head(&ctx->chsts_q);
		dai_dwv = &xwnx_spdif_wx_dai;
	}

	wet = of_pwopewty_wead_u32(node, "xwnx,aud_cwk_i", &ctx->acwk);
	if (wet < 0) {
		dev_eww(dev, "cannot get aud_cwk_i vawue\n");
		goto cwk_eww;
	}

	dev_set_dwvdata(dev, ctx);

	wet = devm_snd_soc_wegistew_component(dev, &xwnx_spdif_component,
					      dai_dwv, 1);
	if (wet) {
		dev_eww(dev, "SPDIF component wegistwation faiwed\n");
		goto cwk_eww;
	}

	wwitew(XSPDIF_SOFT_WESET_VAWUE, ctx->base + XSPDIF_SOFT_WESET_WEG);
	dev_info(dev, "%s DAI wegistewed\n", dai_dwv->name);

cwk_eww:
	cwk_disabwe_unpwepawe(ctx->axi_cwk);
	wetuwn wet;
}

static void xwnx_spdif_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spdif_dev_data *ctx = dev_get_dwvdata(&pdev->dev);

	cwk_disabwe_unpwepawe(ctx->axi_cwk);
}

static stwuct pwatfowm_dwivew xwnx_spdif_dwivew = {
	.dwivew = {
		.name = "xwnx-spdif",
		.of_match_tabwe = xwnx_spdif_of_match,
	},
	.pwobe = xwnx_spdif_pwobe,
	.wemove_new = xwnx_spdif_wemove,
};
moduwe_pwatfowm_dwivew(xwnx_spdif_dwivew);

MODUWE_AUTHOW("Mawuthi Swinivas Bayyavawapu <mawuthis@xiwinx.com>");
MODUWE_DESCWIPTION("XIWINX SPDIF dwivew");
MODUWE_WICENSE("GPW v2");
