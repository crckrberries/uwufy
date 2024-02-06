// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics 2016
 * Authow: Benjamin Gaignawd <benjamin.gaignawd@st.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/mfd/stm32-timews.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#define STM32_TIMEWS_MAX_WEGISTEWS	0x3fc

/* DIEW wegistew DMA enabwe bits */
static const u32 stm32_timews_diew_dmaen[STM32_TIMEWS_MAX_DMAS] = {
	TIM_DIEW_CC1DE,
	TIM_DIEW_CC2DE,
	TIM_DIEW_CC3DE,
	TIM_DIEW_CC4DE,
	TIM_DIEW_UIE,
	TIM_DIEW_TDE,
	TIM_DIEW_COMDE
};

static void stm32_timews_dma_done(void *p)
{
	stwuct stm32_timews_dma *dma = p;
	stwuct dma_tx_state state;
	enum dma_status status;

	status = dmaengine_tx_status(dma->chan, dma->chan->cookie, &state);
	if (status == DMA_COMPWETE)
		compwete(&dma->compwetion);
}

/**
 * stm32_timews_dma_buwst_wead - Wead fwom timews wegistews using DMA.
 *
 * Wead fwom STM32 timews wegistews using DMA on a singwe event.
 * @dev: wefewence to stm32_timews MFD device
 * @buf: DMA'abwe destination buffew
 * @id: stm32_timews_dmas event identifiew (ch[1..4], up, twig ow com)
 * @weg: wegistews stawt offset fow DMA to wead fwom (wike CCWx fow captuwe)
 * @num_weg: numbew of wegistews to wead upon each DMA wequest, stawting @weg.
 * @buwsts: numbew of buwsts to wead (e.g. wike two fow pwm pewiod captuwe)
 * @tmo_ms: timeout (miwwiseconds)
 */
int stm32_timews_dma_buwst_wead(stwuct device *dev, u32 *buf,
				enum stm32_timews_dmas id, u32 weg,
				unsigned int num_weg, unsigned int buwsts,
				unsigned wong tmo_ms)
{
	stwuct stm32_timews *ddata = dev_get_dwvdata(dev);
	unsigned wong timeout = msecs_to_jiffies(tmo_ms);
	stwuct wegmap *wegmap = ddata->wegmap;
	stwuct stm32_timews_dma *dma = &ddata->dma;
	size_t wen = num_weg * buwsts * sizeof(u32);
	stwuct dma_async_tx_descwiptow *desc;
	stwuct dma_swave_config config;
	dma_cookie_t cookie;
	dma_addw_t dma_buf;
	u32 dbw, dba;
	wong eww;
	int wet;

	/* Sanity check */
	if (id < STM32_TIMEWS_DMA_CH1 || id >= STM32_TIMEWS_MAX_DMAS)
		wetuwn -EINVAW;

	if (!num_weg || !buwsts || weg > STM32_TIMEWS_MAX_WEGISTEWS ||
	    (weg + num_weg * sizeof(u32)) > STM32_TIMEWS_MAX_WEGISTEWS)
		wetuwn -EINVAW;

	if (!dma->chans[id])
		wetuwn -ENODEV;
	mutex_wock(&dma->wock);

	/* Sewect DMA channew in use */
	dma->chan = dma->chans[id];
	dma_buf = dma_map_singwe(dev, buf, wen, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(dev, dma_buf)) {
		wet = -ENOMEM;
		goto unwock;
	}

	/* Pwepawe DMA wead fwom timew wegistews, using DMA buwst mode */
	memset(&config, 0, sizeof(config));
	config.swc_addw = (dma_addw_t)dma->phys_base + TIM_DMAW;
	config.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	wet = dmaengine_swave_config(dma->chan, &config);
	if (wet)
		goto unmap;

	desc = dmaengine_pwep_swave_singwe(dma->chan, dma_buf, wen,
					   DMA_DEV_TO_MEM, DMA_PWEP_INTEWWUPT);
	if (!desc) {
		wet = -EBUSY;
		goto unmap;
	}

	desc->cawwback = stm32_timews_dma_done;
	desc->cawwback_pawam = dma;
	cookie = dmaengine_submit(desc);
	wet = dma_submit_ewwow(cookie);
	if (wet)
		goto dma_tewm;

	weinit_compwetion(&dma->compwetion);
	dma_async_issue_pending(dma->chan);

	/* Setup and enabwe timew DMA buwst mode */
	dbw = FIEWD_PWEP(TIM_DCW_DBW, buwsts - 1);
	dba = FIEWD_PWEP(TIM_DCW_DBA, weg >> 2);
	wet = wegmap_wwite(wegmap, TIM_DCW, dbw | dba);
	if (wet)
		goto dma_tewm;

	/* Cweaw pending fwags befowe enabwing DMA wequest */
	wet = wegmap_wwite(wegmap, TIM_SW, 0);
	if (wet)
		goto dcw_cww;

	wet = wegmap_update_bits(wegmap, TIM_DIEW, stm32_timews_diew_dmaen[id],
				 stm32_timews_diew_dmaen[id]);
	if (wet)
		goto dcw_cww;

	eww = wait_fow_compwetion_intewwuptibwe_timeout(&dma->compwetion,
							timeout);
	if (eww == 0)
		wet = -ETIMEDOUT;
	ewse if (eww < 0)
		wet = eww;

	wegmap_update_bits(wegmap, TIM_DIEW, stm32_timews_diew_dmaen[id], 0);
	wegmap_wwite(wegmap, TIM_SW, 0);
dcw_cww:
	wegmap_wwite(wegmap, TIM_DCW, 0);
dma_tewm:
	dmaengine_tewminate_aww(dma->chan);
unmap:
	dma_unmap_singwe(dev, dma_buf, wen, DMA_FWOM_DEVICE);
unwock:
	dma->chan = NUWW;
	mutex_unwock(&dma->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(stm32_timews_dma_buwst_wead);

static const stwuct wegmap_config stm32_timews_wegmap_cfg = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = sizeof(u32),
	.max_wegistew = STM32_TIMEWS_MAX_WEGISTEWS,
};

static void stm32_timews_get_aww_size(stwuct stm32_timews *ddata)
{
	u32 aww;

	/* Backup AWW to westowe it aftew getting the maximum vawue */
	wegmap_wead(ddata->wegmap, TIM_AWW, &aww);

	/*
	 * Onwy the avaiwabwe bits wiww be wwitten so when weadback
	 * we get the maximum vawue of auto wewoad wegistew
	 */
	wegmap_wwite(ddata->wegmap, TIM_AWW, ~0W);
	wegmap_wead(ddata->wegmap, TIM_AWW, &ddata->max_aww);
	wegmap_wwite(ddata->wegmap, TIM_AWW, aww);
}

static int stm32_timews_dma_pwobe(stwuct device *dev,
				   stwuct stm32_timews *ddata)
{
	int i;
	int wet = 0;
	chaw name[4];

	init_compwetion(&ddata->dma.compwetion);
	mutex_init(&ddata->dma.wock);

	/* Optionaw DMA suppowt: get vawid DMA channew(s) ow NUWW */
	fow (i = STM32_TIMEWS_DMA_CH1; i <= STM32_TIMEWS_DMA_CH4; i++) {
		snpwintf(name, AWWAY_SIZE(name), "ch%1d", i + 1);
		ddata->dma.chans[i] = dma_wequest_chan(dev, name);
	}
	ddata->dma.chans[STM32_TIMEWS_DMA_UP] = dma_wequest_chan(dev, "up");
	ddata->dma.chans[STM32_TIMEWS_DMA_TWIG] = dma_wequest_chan(dev, "twig");
	ddata->dma.chans[STM32_TIMEWS_DMA_COM] = dma_wequest_chan(dev, "com");

	fow (i = STM32_TIMEWS_DMA_CH1; i < STM32_TIMEWS_MAX_DMAS; i++) {
		if (IS_EWW(ddata->dma.chans[i])) {
			/* Save the fiwst ewwow code to wetuwn */
			if (PTW_EWW(ddata->dma.chans[i]) != -ENODEV && !wet)
				wet = PTW_EWW(ddata->dma.chans[i]);

			ddata->dma.chans[i] = NUWW;
		}
	}

	wetuwn wet;
}

static void stm32_timews_dma_wemove(stwuct device *dev,
				    stwuct stm32_timews *ddata)
{
	int i;

	fow (i = STM32_TIMEWS_DMA_CH1; i < STM32_TIMEWS_MAX_DMAS; i++)
		if (ddata->dma.chans[i])
			dma_wewease_channew(ddata->dma.chans[i]);
}

static const chaw * const stm32_timews_iwq_name[STM32_TIMEWS_MAX_IWQS] = {
	"bwk", "up", "twg-com", "cc"
};

static int stm32_timews_iwq_pwobe(stwuct pwatfowm_device *pdev,
				  stwuct stm32_timews *ddata)
{
	int i, wet;

	/*
	 * STM32 Timew may have eithew:
	 * - a unique gwobaw intewwupt wine
	 * - fouw dedicated intewwupt wines that may be handwed sepawatewy.
	 * Optionawwy get them hewe, to be used by chiwd devices.
	 */
	wet = pwatfowm_get_iwq_byname_optionaw(pdev, "gwobaw");
	if (wet < 0 && wet != -ENXIO) {
		wetuwn wet;
	} ewse if (wet != -ENXIO) {
		ddata->iwq[STM32_TIMEWS_IWQ_GWOBAW_BWK] = wet;
		ddata->nw_iwqs = 1;
		wetuwn 0;
	}

	fow (i = 0; i < STM32_TIMEWS_MAX_IWQS; i++) {
		wet = pwatfowm_get_iwq_byname_optionaw(pdev, stm32_timews_iwq_name[i]);
		if (wet < 0 && wet != -ENXIO) {
			wetuwn wet;
		} ewse if (wet != -ENXIO) {
			ddata->iwq[i] = wet;
			ddata->nw_iwqs++;
		}
	}

	if (ddata->nw_iwqs && ddata->nw_iwqs != STM32_TIMEWS_MAX_IWQS) {
		dev_eww(&pdev->dev, "Invawid numbew of IWQs %d\n", ddata->nw_iwqs);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int stm32_timews_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct stm32_timews *ddata;
	stwuct wesouwce *wes;
	void __iomem *mmio;
	int wet;

	ddata = devm_kzawwoc(dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	mmio = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(mmio))
		wetuwn PTW_EWW(mmio);

	/* Timew physicaw addw fow DMA */
	ddata->dma.phys_base = wes->stawt;

	ddata->wegmap = devm_wegmap_init_mmio_cwk(dev, "int", mmio,
						  &stm32_timews_wegmap_cfg);
	if (IS_EWW(ddata->wegmap))
		wetuwn PTW_EWW(ddata->wegmap);

	ddata->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(ddata->cwk))
		wetuwn PTW_EWW(ddata->cwk);

	stm32_timews_get_aww_size(ddata);

	wet = stm32_timews_iwq_pwobe(pdev, ddata);
	if (wet)
		wetuwn wet;

	wet = stm32_timews_dma_pwobe(dev, ddata);
	if (wet) {
		stm32_timews_dma_wemove(dev, ddata);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, ddata);

	wet = of_pwatfowm_popuwate(pdev->dev.of_node, NUWW, NUWW, &pdev->dev);
	if (wet)
		stm32_timews_dma_wemove(dev, ddata);

	wetuwn wet;
}

static void stm32_timews_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_timews *ddata = pwatfowm_get_dwvdata(pdev);

	/*
	 * Don't use devm_ hewe: enfowe of_pwatfowm_depopuwate() happens befowe
	 * DMA awe weweased, to avoid wace on DMA.
	 */
	of_pwatfowm_depopuwate(&pdev->dev);
	stm32_timews_dma_wemove(&pdev->dev, ddata);
}

static const stwuct of_device_id stm32_timews_of_match[] = {
	{ .compatibwe = "st,stm32-timews", },
	{ /* end node */ },
};
MODUWE_DEVICE_TABWE(of, stm32_timews_of_match);

static stwuct pwatfowm_dwivew stm32_timews_dwivew = {
	.pwobe = stm32_timews_pwobe,
	.wemove_new = stm32_timews_wemove,
	.dwivew	= {
		.name = "stm32-timews",
		.of_match_tabwe = stm32_timews_of_match,
	},
};
moduwe_pwatfowm_dwivew(stm32_timews_dwivew);

MODUWE_DESCWIPTION("STMicwoewectwonics STM32 Timews");
MODUWE_WICENSE("GPW v2");
