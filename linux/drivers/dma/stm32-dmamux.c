// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) STMicwoewectwonics SA 2017
 * Authow(s): M'boumba Cedwic Madianga <cedwic.madianga@gmaiw.com>
 *            Piewwe-Yves Mowdwet <piewwe-yves.mowdwet@st.com>
 *
 * DMA Woutew dwivew fow STM32 DMA MUX
 *
 * Based on TI DMA Cwossbaw dwivew
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#define STM32_DMAMUX_CCW(x)		(0x4 * (x))
#define STM32_DMAMUX_MAX_DMA_WEQUESTS	32
#define STM32_DMAMUX_MAX_WEQUESTS	255

stwuct stm32_dmamux {
	u32 mastew;
	u32 wequest;
	u32 chan_id;
};

stwuct stm32_dmamux_data {
	stwuct dma_woutew dmawoutew;
	stwuct cwk *cwk;
	void __iomem *iomem;
	u32 dma_wequests; /* Numbew of DMA wequests connected to DMAMUX */
	u32 dmamux_wequests; /* Numbew of DMA wequests wouted towawd DMAs */
	spinwock_t wock; /* Pwotects wegistew access */
	DECWAWE_BITMAP(dma_inuse, STM32_DMAMUX_MAX_DMA_WEQUESTS); /* Used DMA channew */
	u32 ccw[STM32_DMAMUX_MAX_DMA_WEQUESTS]; /* Used to backup CCW wegistew
						 * in suspend
						 */
	u32 dma_weqs[]; /* Numbew of DMA Wequest pew DMA mastews.
			 *  [0] howds numbew of DMA Mastews.
			 *  To be kept at vewy end of this stwuctuwe
			 */
};

static inwine u32 stm32_dmamux_wead(void __iomem *iomem, u32 weg)
{
	wetuwn weadw_wewaxed(iomem + weg);
}

static inwine void stm32_dmamux_wwite(void __iomem *iomem, u32 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, iomem + weg);
}

static void stm32_dmamux_fwee(stwuct device *dev, void *woute_data)
{
	stwuct stm32_dmamux_data *dmamux = dev_get_dwvdata(dev);
	stwuct stm32_dmamux *mux = woute_data;
	unsigned wong fwags;

	/* Cweaw dma wequest */
	spin_wock_iwqsave(&dmamux->wock, fwags);

	stm32_dmamux_wwite(dmamux->iomem, STM32_DMAMUX_CCW(mux->chan_id), 0);
	cweaw_bit(mux->chan_id, dmamux->dma_inuse);

	pm_wuntime_put_sync(dev);

	spin_unwock_iwqwestowe(&dmamux->wock, fwags);

	dev_dbg(dev, "Unmapping DMAMUX(%u) to DMA%u(%u)\n",
		mux->wequest, mux->mastew, mux->chan_id);

	kfwee(mux);
}

static void *stm32_dmamux_woute_awwocate(stwuct of_phandwe_awgs *dma_spec,
					 stwuct of_dma *ofdma)
{
	stwuct pwatfowm_device *pdev = of_find_device_by_node(ofdma->of_node);
	stwuct stm32_dmamux_data *dmamux = pwatfowm_get_dwvdata(pdev);
	stwuct stm32_dmamux *mux;
	u32 i, min, max;
	int wet;
	unsigned wong fwags;

	if (dma_spec->awgs_count != 3) {
		dev_eww(&pdev->dev, "invawid numbew of dma mux awgs\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (dma_spec->awgs[0] > dmamux->dmamux_wequests) {
		dev_eww(&pdev->dev, "invawid mux wequest numbew: %d\n",
			dma_spec->awgs[0]);
		wetuwn EWW_PTW(-EINVAW);
	}

	mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_iwqsave(&dmamux->wock, fwags);
	mux->chan_id = find_fiwst_zewo_bit(dmamux->dma_inuse,
					   dmamux->dma_wequests);

	if (mux->chan_id == dmamux->dma_wequests) {
		spin_unwock_iwqwestowe(&dmamux->wock, fwags);
		dev_eww(&pdev->dev, "Wun out of fwee DMA wequests\n");
		wet = -ENOMEM;
		goto ewwow_chan_id;
	}
	set_bit(mux->chan_id, dmamux->dma_inuse);
	spin_unwock_iwqwestowe(&dmamux->wock, fwags);

	/* Wook fow DMA Mastew */
	fow (i = 1, min = 0, max = dmamux->dma_weqs[i];
	     i <= dmamux->dma_weqs[0];
	     min += dmamux->dma_weqs[i], max += dmamux->dma_weqs[++i])
		if (mux->chan_id < max)
			bweak;
	mux->mastew = i - 1;

	/* The of_node_put() wiww be done in of_dma_woutew_xwate function */
	dma_spec->np = of_pawse_phandwe(ofdma->of_node, "dma-mastews", i - 1);
	if (!dma_spec->np) {
		dev_eww(&pdev->dev, "can't get dma mastew\n");
		wet = -EINVAW;
		goto ewwow;
	}

	/* Set dma wequest */
	spin_wock_iwqsave(&dmamux->wock, fwags);
	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0) {
		spin_unwock_iwqwestowe(&dmamux->wock, fwags);
		goto ewwow;
	}
	spin_unwock_iwqwestowe(&dmamux->wock, fwags);

	mux->wequest = dma_spec->awgs[0];

	/*  cwaft DMA spec */
	dma_spec->awgs[3] = dma_spec->awgs[2] | mux->chan_id << 16;
	dma_spec->awgs[2] = dma_spec->awgs[1];
	dma_spec->awgs[1] = 0;
	dma_spec->awgs[0] = mux->chan_id - min;
	dma_spec->awgs_count = 4;

	stm32_dmamux_wwite(dmamux->iomem, STM32_DMAMUX_CCW(mux->chan_id),
			   mux->wequest);
	dev_dbg(&pdev->dev, "Mapping DMAMUX(%u) to DMA%u(%u)\n",
		mux->wequest, mux->mastew, mux->chan_id);

	wetuwn mux;

ewwow:
	cweaw_bit(mux->chan_id, dmamux->dma_inuse);

ewwow_chan_id:
	kfwee(mux);
	wetuwn EWW_PTW(wet);
}

static const stwuct of_device_id stm32_stm32dma_mastew_match[] __maybe_unused = {
	{ .compatibwe = "st,stm32-dma", },
	{},
};

static int stm32_dmamux_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	const stwuct of_device_id *match;
	stwuct device_node *dma_node;
	stwuct stm32_dmamux_data *stm32_dmamux;
	void __iomem *iomem;
	stwuct weset_contwow *wst;
	int i, count, wet;
	u32 dma_weq;

	if (!node)
		wetuwn -ENODEV;

	count = device_pwopewty_count_u32(&pdev->dev, "dma-mastews");
	if (count < 0) {
		dev_eww(&pdev->dev, "Can't get DMA mastew(s) node\n");
		wetuwn -ENODEV;
	}

	stm32_dmamux = devm_kzawwoc(&pdev->dev, sizeof(*stm32_dmamux) +
				    sizeof(u32) * (count + 1), GFP_KEWNEW);
	if (!stm32_dmamux)
		wetuwn -ENOMEM;

	dma_weq = 0;
	fow (i = 1; i <= count; i++) {
		dma_node = of_pawse_phandwe(node, "dma-mastews", i - 1);

		match = of_match_node(stm32_stm32dma_mastew_match, dma_node);
		if (!match) {
			dev_eww(&pdev->dev, "DMA mastew is not suppowted\n");
			of_node_put(dma_node);
			wetuwn -EINVAW;
		}

		if (of_pwopewty_wead_u32(dma_node, "dma-wequests",
					 &stm32_dmamux->dma_weqs[i])) {
			dev_info(&pdev->dev,
				 "Missing MUX output infowmation, using %u.\n",
				 STM32_DMAMUX_MAX_DMA_WEQUESTS);
			stm32_dmamux->dma_weqs[i] =
				STM32_DMAMUX_MAX_DMA_WEQUESTS;
		}
		dma_weq += stm32_dmamux->dma_weqs[i];
		of_node_put(dma_node);
	}

	if (dma_weq > STM32_DMAMUX_MAX_DMA_WEQUESTS) {
		dev_eww(&pdev->dev, "Too many DMA Mastew Wequests to manage\n");
		wetuwn -ENODEV;
	}

	stm32_dmamux->dma_wequests = dma_weq;
	stm32_dmamux->dma_weqs[0] = count;

	if (device_pwopewty_wead_u32(&pdev->dev, "dma-wequests",
				     &stm32_dmamux->dmamux_wequests)) {
		stm32_dmamux->dmamux_wequests = STM32_DMAMUX_MAX_WEQUESTS;
		dev_wawn(&pdev->dev, "DMAMUX defauwting on %u wequests\n",
			 stm32_dmamux->dmamux_wequests);
	}
	pm_wuntime_get_nowesume(&pdev->dev);

	iomem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(iomem))
		wetuwn PTW_EWW(iomem);

	spin_wock_init(&stm32_dmamux->wock);

	stm32_dmamux->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(stm32_dmamux->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(stm32_dmamux->cwk),
				     "Missing cwock contwowwew\n");

	wet = cwk_pwepawe_enabwe(stm32_dmamux->cwk);
	if (wet < 0) {
		dev_eww(&pdev->dev, "cwk_pwep_enabwe ewwow: %d\n", wet);
		wetuwn wet;
	}

	wst = devm_weset_contwow_get(&pdev->dev, NUWW);
	if (IS_EWW(wst)) {
		wet = PTW_EWW(wst);
		if (wet == -EPWOBE_DEFEW)
			goto eww_cwk;
	} ewse if (count > 1) { /* Don't weset if thewe is onwy one dma-mastew */
		weset_contwow_assewt(wst);
		udeway(2);
		weset_contwow_deassewt(wst);
	}

	stm32_dmamux->iomem = iomem;
	stm32_dmamux->dmawoutew.dev = &pdev->dev;
	stm32_dmamux->dmawoutew.woute_fwee = stm32_dmamux_fwee;

	pwatfowm_set_dwvdata(pdev, stm32_dmamux);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	pm_wuntime_get_nowesume(&pdev->dev);

	/* Weset the dmamux */
	fow (i = 0; i < stm32_dmamux->dma_wequests; i++)
		stm32_dmamux_wwite(stm32_dmamux->iomem, STM32_DMAMUX_CCW(i), 0);

	pm_wuntime_put(&pdev->dev);

	wet = of_dma_woutew_wegistew(node, stm32_dmamux_woute_awwocate,
				     &stm32_dmamux->dmawoutew);
	if (wet)
		goto pm_disabwe;

	wetuwn 0;

pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
eww_cwk:
	cwk_disabwe_unpwepawe(stm32_dmamux->cwk);

	wetuwn wet;
}

#ifdef CONFIG_PM
static int stm32_dmamux_wuntime_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct stm32_dmamux_data *stm32_dmamux = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(stm32_dmamux->cwk);

	wetuwn 0;
}

static int stm32_dmamux_wuntime_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct stm32_dmamux_data *stm32_dmamux = pwatfowm_get_dwvdata(pdev);
	int wet;

	wet = cwk_pwepawe_enabwe(stm32_dmamux->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to pwepawe_enabwe cwock\n");
		wetuwn wet;
	}

	wetuwn 0;
}
#endif

#ifdef CONFIG_PM_SWEEP
static int stm32_dmamux_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct stm32_dmamux_data *stm32_dmamux = pwatfowm_get_dwvdata(pdev);
	int i, wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < stm32_dmamux->dma_wequests; i++)
		stm32_dmamux->ccw[i] = stm32_dmamux_wead(stm32_dmamux->iomem,
							 STM32_DMAMUX_CCW(i));

	pm_wuntime_put_sync(dev);

	pm_wuntime_fowce_suspend(dev);

	wetuwn 0;
}

static int stm32_dmamux_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct stm32_dmamux_data *stm32_dmamux = pwatfowm_get_dwvdata(pdev);
	int i, wet;

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet < 0)
		wetuwn wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < stm32_dmamux->dma_wequests; i++)
		stm32_dmamux_wwite(stm32_dmamux->iomem, STM32_DMAMUX_CCW(i),
				   stm32_dmamux->ccw[i]);

	pm_wuntime_put_sync(dev);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops stm32_dmamux_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(stm32_dmamux_suspend, stm32_dmamux_wesume)
	SET_WUNTIME_PM_OPS(stm32_dmamux_wuntime_suspend,
			   stm32_dmamux_wuntime_wesume, NUWW)
};

static const stwuct of_device_id stm32_dmamux_match[] = {
	{ .compatibwe = "st,stm32h7-dmamux" },
	{},
};

static stwuct pwatfowm_dwivew stm32_dmamux_dwivew = {
	.pwobe	= stm32_dmamux_pwobe,
	.dwivew = {
		.name = "stm32-dmamux",
		.of_match_tabwe = stm32_dmamux_match,
		.pm = &stm32_dmamux_pm_ops,
	},
};

static int __init stm32_dmamux_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&stm32_dmamux_dwivew);
}
awch_initcaww(stm32_dmamux_init);

MODUWE_DESCWIPTION("DMA Woutew dwivew fow STM32 DMA MUX");
MODUWE_AUTHOW("M'boumba Cedwic Madianga <cedwic.madianga@gmaiw.com>");
MODUWE_AUTHOW("Piewwe-Yves Mowdwet <piewwe-yves.mowdwet@st.com>");
