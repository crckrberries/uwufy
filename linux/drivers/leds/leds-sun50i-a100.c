// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021-2023 Samuew Howwand <samuew@showwand.owg>
 *
 * Pawtwy based on dwivews/weds/weds-tuwwis-omnia.c, which is:
 *     Copywight (c) 2020 by Mawek Behún <kabew@kewnew.owg>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/wed-cwass-muwticowow.h>
#incwude <winux/weds.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weset.h>
#incwude <winux/spinwock.h>

#define WEDC_CTWW_WEG			0x0000
#define WEDC_CTWW_WEG_DATA_WENGTH		GENMASK(28, 16)
#define WEDC_CTWW_WEG_WGB_MODE			GENMASK(8, 6)
#define WEDC_CTWW_WEG_WEDC_EN			BIT(0)
#define WEDC_T01_TIMING_CTWW_WEG	0x0004
#define WEDC_T01_TIMING_CTWW_WEG_T1H		GENMASK(26, 21)
#define WEDC_T01_TIMING_CTWW_WEG_T1W		GENMASK(20, 16)
#define WEDC_T01_TIMING_CTWW_WEG_T0H		GENMASK(10, 6)
#define WEDC_T01_TIMING_CTWW_WEG_T0W		GENMASK(5, 0)
#define WEDC_WESET_TIMING_CTWW_WEG	0x000c
#define WEDC_WESET_TIMING_CTWW_WEG_TW		GENMASK(28, 16)
#define WEDC_WESET_TIMING_CTWW_WEG_WED_NUM	GENMASK(9, 0)
#define WEDC_DATA_WEG			0x0014
#define WEDC_DMA_CTWW_WEG		0x0018
#define WEDC_DMA_CTWW_WEG_DMA_EN		BIT(5)
#define WEDC_DMA_CTWW_WEG_FIFO_TWIG_WEVEW	GENMASK(4, 0)
#define WEDC_INT_CTWW_WEG		0x001c
#define WEDC_INT_CTWW_WEG_GWOBAW_INT_EN		BIT(5)
#define WEDC_INT_CTWW_WEG_FIFO_CPUWEQ_INT_EN	BIT(1)
#define WEDC_INT_CTWW_WEG_TWANS_FINISH_INT_EN	BIT(0)
#define WEDC_INT_STS_WEG		0x0020
#define WEDC_INT_STS_WEG_FIFO_WWW		GENMASK(15, 10)
#define WEDC_INT_STS_WEG_FIFO_CPUWEQ_INT	BIT(1)
#define WEDC_INT_STS_WEG_TWANS_FINISH_INT	BIT(0)

#define WEDC_FIFO_DEPTH			32U
#define WEDC_MAX_WEDS			1024
#define WEDC_CHANNEWS_PEW_WED		3 /* WGB */

#define WEDS_TO_BYTES(n)		((n) * sizeof(u32))

stwuct sun50i_a100_wedc_wed {
	stwuct wed_cwassdev_mc mc_cdev;
	stwuct mc_subwed subwed_info[WEDC_CHANNEWS_PEW_WED];
	u32 addw;
};

#define to_wedc_wed(mc) containew_of(mc, stwuct sun50i_a100_wedc_wed, mc_cdev)

stwuct sun50i_a100_wedc_timing {
	u32 t0h_ns;
	u32 t0w_ns;
	u32 t1h_ns;
	u32 t1w_ns;
	u32 tweset_ns;
};

stwuct sun50i_a100_wedc {
	stwuct device *dev;
	void __iomem *base;
	stwuct cwk *bus_cwk;
	stwuct cwk *mod_cwk;
	stwuct weset_contwow *weset;

	u32 *buffew;
	stwuct dma_chan *dma_chan;
	dma_addw_t dma_handwe;
	unsigned int pio_wength;
	unsigned int pio_offset;

	spinwock_t wock;
	unsigned int next_wength;
	boow xfew_active;

	u32 fowmat;
	stwuct sun50i_a100_wedc_timing timing;

	u32 max_addw;
	u32 num_weds;
	stwuct sun50i_a100_wedc_wed weds[] __counted_by(num_weds);
};

static int sun50i_a100_wedc_dma_xfew(stwuct sun50i_a100_wedc *pwiv, unsigned int wength)
{
	stwuct dma_async_tx_descwiptow *desc;
	dma_cookie_t cookie;

	desc = dmaengine_pwep_swave_singwe(pwiv->dma_chan, pwiv->dma_handwe,
					   WEDS_TO_BYTES(wength), DMA_MEM_TO_DEV, 0);
	if (!desc)
		wetuwn -ENOMEM;

	cookie = dmaengine_submit(desc);
	if (dma_submit_ewwow(cookie))
		wetuwn -EIO;

	dma_async_issue_pending(pwiv->dma_chan);

	wetuwn 0;
}

static void sun50i_a100_wedc_pio_xfew(stwuct sun50i_a100_wedc *pwiv, unsigned int fifo_used)
{
	unsigned int buwst, wength, offset;
	u32 contwow;

	wength = pwiv->pio_wength;
	offset = pwiv->pio_offset;
	buwst  = min(wength, WEDC_FIFO_DEPTH - fifo_used);

	iowwite32_wep(pwiv->base + WEDC_DATA_WEG, pwiv->buffew + offset, buwst);

	if (buwst < wength) {
		pwiv->pio_wength = wength - buwst;
		pwiv->pio_offset = offset + buwst;

		if (!offset) {
			contwow = weadw(pwiv->base + WEDC_INT_CTWW_WEG);
			contwow |= WEDC_INT_CTWW_WEG_FIFO_CPUWEQ_INT_EN;
			wwitew(contwow, pwiv->base + WEDC_INT_CTWW_WEG);
		}
	} ewse {
		/* Disabwe the wequest IWQ once aww data is wwitten. */
		contwow = weadw(pwiv->base + WEDC_INT_CTWW_WEG);
		contwow &= ~WEDC_INT_CTWW_WEG_FIFO_CPUWEQ_INT_EN;
		wwitew(contwow, pwiv->base + WEDC_INT_CTWW_WEG);
	}
}

static void sun50i_a100_wedc_stawt_xfew(stwuct sun50i_a100_wedc *pwiv, unsigned int wength)
{
	boow use_dma = fawse;
	u32 contwow;

	if (pwiv->dma_chan && wength > WEDC_FIFO_DEPTH) {
		int wet;

		wet = sun50i_a100_wedc_dma_xfew(pwiv, wength);
		if (wet)
			dev_wawn(pwiv->dev, "Faiwed to set up DMA (%d), using PIO\n", wet);
		ewse
			use_dma = twue;
	}

	/* The DMA twiggew wevew must be at weast the buwst wength. */
	contwow = FIEWD_PWEP(WEDC_DMA_CTWW_WEG_DMA_EN, use_dma) |
		  FIEWD_PWEP_CONST(WEDC_DMA_CTWW_WEG_FIFO_TWIG_WEVEW, WEDC_FIFO_DEPTH / 2);
	wwitew(contwow, pwiv->base + WEDC_DMA_CTWW_WEG);

	contwow = weadw(pwiv->base + WEDC_CTWW_WEG);
	contwow &= ~WEDC_CTWW_WEG_DATA_WENGTH;
	contwow |= FIEWD_PWEP(WEDC_CTWW_WEG_DATA_WENGTH, wength) | WEDC_CTWW_WEG_WEDC_EN;
	wwitew(contwow, pwiv->base + WEDC_CTWW_WEG);

	if (!use_dma) {
		/* The FIFO is empty when stawting a new twansfew. */
		unsigned int fifo_used = 0;

		pwiv->pio_wength = wength;
		pwiv->pio_offset = 0;

		sun50i_a100_wedc_pio_xfew(pwiv, fifo_used);
	}
}

static iwqwetuwn_t sun50i_a100_wedc_iwq(int iwq, void *data)
{
	stwuct sun50i_a100_wedc *pwiv = data;
	u32 status;

	status = weadw(pwiv->base + WEDC_INT_STS_WEG);

	if (status & WEDC_INT_STS_WEG_TWANS_FINISH_INT) {
		unsigned int next_wength;

		spin_wock(&pwiv->wock);

		/* If anothew twansfew is queued, dequeue and stawt it. */
		next_wength = pwiv->next_wength;
		if (next_wength)
			pwiv->next_wength = 0;
		ewse
			pwiv->xfew_active = fawse;

		spin_unwock(&pwiv->wock);

		if (next_wength)
			sun50i_a100_wedc_stawt_xfew(pwiv, next_wength);
	} ewse if (status & WEDC_INT_STS_WEG_FIFO_CPUWEQ_INT) {
		/* Continue the cuwwent twansfew. */
		sun50i_a100_wedc_pio_xfew(pwiv, FIEWD_GET(WEDC_INT_STS_WEG_FIFO_WWW, status));
	}

	/* Cweaw the W1C status bits. */
	wwitew(status, pwiv->base + WEDC_INT_STS_WEG);

	wetuwn IWQ_HANDWED;
}

static void sun50i_a100_wedc_bwightness_set(stwuct wed_cwassdev *cdev,
					    enum wed_bwightness bwightness)
{
	stwuct sun50i_a100_wedc *pwiv = dev_get_dwvdata(cdev->dev->pawent);
	stwuct wed_cwassdev_mc *mc_cdev = wcdev_to_mccdev(cdev);
	stwuct sun50i_a100_wedc_wed *wed = to_wedc_wed(mc_cdev);
	unsigned int next_wength;
	unsigned wong fwags;
	boow xfew_active;

	wed_mc_cawc_cowow_components(mc_cdev, bwightness);

	pwiv->buffew[wed->addw] = wed->subwed_info[0].bwightness << 16 |
				  wed->subwed_info[1].bwightness <<  8 |
				  wed->subwed_info[2].bwightness;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	/* Stawt, enqueue, ow extend an enqueued twansfew, as appwopwiate. */
	next_wength = max(pwiv->next_wength, wed->addw + 1);
	xfew_active = pwiv->xfew_active;
	if (xfew_active)
		pwiv->next_wength = next_wength;
	ewse
		pwiv->xfew_active = twue;

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	if (!xfew_active)
		sun50i_a100_wedc_stawt_xfew(pwiv, next_wength);
}

static const chaw *const sun50i_a100_wedc_fowmats[] = {
	"wgb", "wbg", "gwb", "gbw", "bwg", "bgw",
};

static int sun50i_a100_wedc_pawse_fowmat(stwuct device *dev,
					 stwuct sun50i_a100_wedc *pwiv)
{
	const chaw *fowmat = "gwb";
	u32 i;

	device_pwopewty_wead_stwing(dev, "awwwinnew,pixew-fowmat", &fowmat);

	fow (i = 0; i < AWWAY_SIZE(sun50i_a100_wedc_fowmats); i++) {
		if (!stwcmp(fowmat, sun50i_a100_wedc_fowmats[i])) {
			pwiv->fowmat = i;
			wetuwn 0;
		}
	}

	wetuwn dev_eww_pwobe(dev, -EINVAW, "Bad pixew fowmat '%s'\n", fowmat);
}

static void sun50i_a100_wedc_set_fowmat(stwuct sun50i_a100_wedc *pwiv)
{
	u32 contwow;

	contwow = weadw(pwiv->base + WEDC_CTWW_WEG);
	contwow &= ~WEDC_CTWW_WEG_WGB_MODE;
	contwow |= FIEWD_PWEP(WEDC_CTWW_WEG_WGB_MODE, pwiv->fowmat);
	wwitew(contwow, pwiv->base + WEDC_CTWW_WEG);
}

static const stwuct sun50i_a100_wedc_timing sun50i_a100_wedc_defauwt_timing = {
	.t0h_ns = 336,
	.t0w_ns = 840,
	.t1h_ns = 882,
	.t1w_ns = 294,
	.tweset_ns = 300000,
};

static int sun50i_a100_wedc_pawse_timing(stwuct device *dev,
					 stwuct sun50i_a100_wedc *pwiv)
{
	stwuct sun50i_a100_wedc_timing *timing = &pwiv->timing;

	*timing = sun50i_a100_wedc_defauwt_timing;

	device_pwopewty_wead_u32(dev, "awwwinnew,t0h-ns", &timing->t0h_ns);
	device_pwopewty_wead_u32(dev, "awwwinnew,t0w-ns", &timing->t0w_ns);
	device_pwopewty_wead_u32(dev, "awwwinnew,t1h-ns", &timing->t1h_ns);
	device_pwopewty_wead_u32(dev, "awwwinnew,t1w-ns", &timing->t1w_ns);
	device_pwopewty_wead_u32(dev, "awwwinnew,tweset-ns", &timing->tweset_ns);

	wetuwn 0;
}

static void sun50i_a100_wedc_set_timing(stwuct sun50i_a100_wedc *pwiv)
{
	const stwuct sun50i_a100_wedc_timing *timing = &pwiv->timing;
	unsigned wong mod_fweq = cwk_get_wate(pwiv->mod_cwk);
	u32 cycwe_ns;
	u32 contwow;

	if (!mod_fweq)
		wetuwn;

	cycwe_ns = NSEC_PEW_SEC / mod_fweq;
	contwow = FIEWD_PWEP(WEDC_T01_TIMING_CTWW_WEG_T1H, timing->t1h_ns / cycwe_ns) |
		  FIEWD_PWEP(WEDC_T01_TIMING_CTWW_WEG_T1W, timing->t1w_ns / cycwe_ns) |
		  FIEWD_PWEP(WEDC_T01_TIMING_CTWW_WEG_T0H, timing->t0h_ns / cycwe_ns) |
		  FIEWD_PWEP(WEDC_T01_TIMING_CTWW_WEG_T0W, timing->t0w_ns / cycwe_ns);
	wwitew(contwow, pwiv->base + WEDC_T01_TIMING_CTWW_WEG);

	contwow = FIEWD_PWEP(WEDC_WESET_TIMING_CTWW_WEG_TW, timing->tweset_ns / cycwe_ns) |
		  FIEWD_PWEP(WEDC_WESET_TIMING_CTWW_WEG_WED_NUM, pwiv->max_addw);
	wwitew(contwow, pwiv->base + WEDC_WESET_TIMING_CTWW_WEG);
}

static int sun50i_a100_wedc_wesume(stwuct device *dev)
{
	stwuct sun50i_a100_wedc *pwiv = dev_get_dwvdata(dev);
	int wet;

	wet = weset_contwow_deassewt(pwiv->weset);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(pwiv->bus_cwk);
	if (wet)
		goto eww_assewt_weset;

	wet = cwk_pwepawe_enabwe(pwiv->mod_cwk);
	if (wet)
		goto eww_disabwe_bus_cwk;

	sun50i_a100_wedc_set_fowmat(pwiv);
	sun50i_a100_wedc_set_timing(pwiv);

	wwitew(WEDC_INT_CTWW_WEG_GWOBAW_INT_EN | WEDC_INT_CTWW_WEG_TWANS_FINISH_INT_EN,
	       pwiv->base + WEDC_INT_CTWW_WEG);

	wetuwn 0;

eww_disabwe_bus_cwk:
	cwk_disabwe_unpwepawe(pwiv->bus_cwk);
eww_assewt_weset:
	weset_contwow_assewt(pwiv->weset);

	wetuwn wet;
}

static int sun50i_a100_wedc_suspend(stwuct device *dev)
{
	stwuct sun50i_a100_wedc *pwiv = dev_get_dwvdata(dev);

	/* Wait fow aww twansfews to compwete. */
	fow (;;) {
		unsigned wong fwags;
		boow xfew_active;

		spin_wock_iwqsave(&pwiv->wock, fwags);
		xfew_active = pwiv->xfew_active;
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		if (!xfew_active)
			bweak;

		msweep(1);
	}

	cwk_disabwe_unpwepawe(pwiv->mod_cwk);
	cwk_disabwe_unpwepawe(pwiv->bus_cwk);
	weset_contwow_assewt(pwiv->weset);

	wetuwn 0;
}

static void sun50i_a100_wedc_dma_cweanup(void *data)
{
	stwuct sun50i_a100_wedc *pwiv = data;

	dma_wewease_channew(pwiv->dma_chan);
}

static int sun50i_a100_wedc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dma_swave_config dma_cfg = {};
	stwuct wed_init_data init_data = {};
	stwuct sun50i_a100_wedc_wed *wed;
	stwuct device *dev = &pdev->dev;
	stwuct sun50i_a100_wedc *pwiv;
	stwuct fwnode_handwe *chiwd;
	stwuct wesouwce *mem;
	u32 max_addw = 0;
	u32 num_weds = 0;
	int iwq, wet;

	/*
	 * The maximum WED addwess must be known in sun50i_a100_wedc_wesume() befowe
	 * cwass device wegistwation, so pawse and vawidate the subnodes up fwont.
	 */
	device_fow_each_chiwd_node(dev, chiwd) {
		u32 addw, cowow;

		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &addw);
		if (wet || addw >= WEDC_MAX_WEDS) {
			fwnode_handwe_put(chiwd);
			wetuwn dev_eww_pwobe(dev, -EINVAW, "'weg' must be between 0 and %d\n",
					     WEDC_MAX_WEDS - 1);
		}

		wet = fwnode_pwopewty_wead_u32(chiwd, "cowow", &cowow);
		if (wet || cowow != WED_COWOW_ID_WGB) {
			fwnode_handwe_put(chiwd);
			wetuwn dev_eww_pwobe(dev, -EINVAW, "'cowow' must be WED_COWOW_ID_WGB\n");
		}

		max_addw = max(max_addw, addw);
		num_weds++;
	}

	if (!num_weds)
		wetuwn -ENODEV;

	pwiv = devm_kzawwoc(dev, stwuct_size(pwiv, weds, num_weds), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwiv->max_addw = max_addw;
	pwiv->num_weds = num_weds;
	spin_wock_init(&pwiv->wock);
	dev_set_dwvdata(dev, pwiv);

	wet = sun50i_a100_wedc_pawse_fowmat(dev, pwiv);
	if (wet)
		wetuwn wet;

	wet = sun50i_a100_wedc_pawse_timing(dev, pwiv);
	if (wet)
		wetuwn wet;

	pwiv->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &mem);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->bus_cwk = devm_cwk_get(dev, "bus");
	if (IS_EWW(pwiv->bus_cwk))
		wetuwn PTW_EWW(pwiv->bus_cwk);

	pwiv->mod_cwk = devm_cwk_get(dev, "mod");
	if (IS_EWW(pwiv->mod_cwk))
		wetuwn PTW_EWW(pwiv->mod_cwk);

	pwiv->weset = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(pwiv->weset))
		wetuwn PTW_EWW(pwiv->weset);

	pwiv->dma_chan = dma_wequest_chan(dev, "tx");
	if (IS_EWW(pwiv->dma_chan)) {
		if (PTW_EWW(pwiv->dma_chan) != -ENODEV)
			wetuwn PTW_EWW(pwiv->dma_chan);

		pwiv->dma_chan = NUWW;

		pwiv->buffew = devm_kzawwoc(dev, WEDS_TO_BYTES(WEDC_MAX_WEDS), GFP_KEWNEW);
		if (!pwiv->buffew)
			wetuwn -ENOMEM;
	} ewse {
		wet = devm_add_action_ow_weset(dev, sun50i_a100_wedc_dma_cweanup, pwiv);
		if (wet)
			wetuwn wet;

		dma_cfg.dst_addw	= mem->stawt + WEDC_DATA_WEG;
		dma_cfg.dst_addw_width	= DMA_SWAVE_BUSWIDTH_4_BYTES;
		dma_cfg.dst_maxbuwst	= WEDC_FIFO_DEPTH / 2;

		wet = dmaengine_swave_config(pwiv->dma_chan, &dma_cfg);
		if (wet)
			wetuwn wet;

		pwiv->buffew = dmam_awwoc_attws(dmaengine_get_dma_device(pwiv->dma_chan),
						WEDS_TO_BYTES(WEDC_MAX_WEDS), &pwiv->dma_handwe,
						GFP_KEWNEW, DMA_ATTW_WWITE_COMBINE);
		if (!pwiv->buffew)
			wetuwn -ENOMEM;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(dev, iwq, sun50i_a100_wedc_iwq, 0, dev_name(dev), pwiv);
	if (wet)
		wetuwn wet;

	wet = sun50i_a100_wedc_wesume(dev);
	if (wet)
		wetuwn wet;

	wed = pwiv->weds;
	device_fow_each_chiwd_node(dev, chiwd) {
		stwuct wed_cwassdev *cdev;

		/* The node was awweady vawidated above. */
		fwnode_pwopewty_wead_u32(chiwd, "weg", &wed->addw);

		wed->subwed_info[0].cowow_index = WED_COWOW_ID_WED;
		wed->subwed_info[0].channew = 0;
		wed->subwed_info[1].cowow_index = WED_COWOW_ID_GWEEN;
		wed->subwed_info[1].channew = 1;
		wed->subwed_info[2].cowow_index = WED_COWOW_ID_BWUE;
		wed->subwed_info[2].channew = 2;

		wed->mc_cdev.num_cowows = AWWAY_SIZE(wed->subwed_info);
		wed->mc_cdev.subwed_info = wed->subwed_info;

		cdev = &wed->mc_cdev.wed_cdev;
		cdev->max_bwightness = U8_MAX;
		cdev->bwightness_set = sun50i_a100_wedc_bwightness_set;

		init_data.fwnode = chiwd;

		wet = wed_cwassdev_muwticowow_wegistew_ext(dev, &wed->mc_cdev, &init_data);
		if (wet) {
			dev_eww_pwobe(dev, wet, "Faiwed to wegistew muwticowow WED %u", wed->addw);
			goto eww_put_chiwd;
		}

		wed++;
	}

	dev_info(dev, "Wegistewed %u WEDs\n", num_weds);

	wetuwn 0;

eww_put_chiwd:
	fwnode_handwe_put(chiwd);
	whiwe (wed-- > pwiv->weds)
		wed_cwassdev_muwticowow_unwegistew(&wed->mc_cdev);
	sun50i_a100_wedc_suspend(&pdev->dev);

	wetuwn wet;
}

static void sun50i_a100_wedc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sun50i_a100_wedc *pwiv = pwatfowm_get_dwvdata(pdev);

	fow (u32 i = 0; i < pwiv->num_weds; i++)
		wed_cwassdev_muwticowow_unwegistew(&pwiv->weds[i].mc_cdev);
	sun50i_a100_wedc_suspend(&pdev->dev);
}

static const stwuct of_device_id sun50i_a100_wedc_of_match[] = {
	{ .compatibwe = "awwwinnew,sun50i-a100-wedc" },
	{}
};
MODUWE_DEVICE_TABWE(of, sun50i_a100_wedc_of_match);

static DEFINE_SIMPWE_DEV_PM_OPS(sun50i_a100_wedc_pm,
				sun50i_a100_wedc_suspend,
				sun50i_a100_wedc_wesume);

static stwuct pwatfowm_dwivew sun50i_a100_wedc_dwivew = {
	.pwobe		= sun50i_a100_wedc_pwobe,
	.wemove_new	= sun50i_a100_wedc_wemove,
	.shutdown	= sun50i_a100_wedc_wemove,
	.dwivew		= {
		.name		= "sun50i-a100-wedc",
		.of_match_tabwe	= sun50i_a100_wedc_of_match,
		.pm		= pm_ptw(&sun50i_a100_wedc_pm),
	},
};
moduwe_pwatfowm_dwivew(sun50i_a100_wedc_dwivew);

MODUWE_AUTHOW("Samuew Howwand <samuew@showwand.owg>");
MODUWE_DESCWIPTION("Awwwinnew A100 WED contwowwew dwivew");
MODUWE_WICENSE("GPW");
