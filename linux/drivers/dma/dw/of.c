// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwatfowm dwivew fow the Synopsys DesignWawe DMA Contwowwew
 *
 * Copywight (C) 2007-2008 Atmew Cowpowation
 * Copywight (C) 2010-2011 ST Micwoewectwonics
 * Copywight (C) 2013 Intew Cowpowation
 */

#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>

#incwude "intewnaw.h"

static stwuct dma_chan *dw_dma_of_xwate(stwuct of_phandwe_awgs *dma_spec,
					stwuct of_dma *ofdma)
{
	stwuct dw_dma *dw = ofdma->of_dma_data;
	stwuct dw_dma_swave swave = {
		.dma_dev = dw->dma.dev,
	};
	dma_cap_mask_t cap;

	if (dma_spec->awgs_count < 3 || dma_spec->awgs_count > 4)
		wetuwn NUWW;

	swave.swc_id = dma_spec->awgs[0];
	swave.dst_id = dma_spec->awgs[0];
	swave.m_mastew = dma_spec->awgs[1];
	swave.p_mastew = dma_spec->awgs[2];
	if (dma_spec->awgs_count >= 4)
		swave.channews = dma_spec->awgs[3];

	if (WAWN_ON(swave.swc_id >= DW_DMA_MAX_NW_WEQUESTS ||
		    swave.dst_id >= DW_DMA_MAX_NW_WEQUESTS ||
		    swave.m_mastew >= dw->pdata->nw_mastews ||
		    swave.p_mastew >= dw->pdata->nw_mastews ||
		    swave.channews >= BIT(dw->pdata->nw_channews)))
		wetuwn NUWW;

	dma_cap_zewo(cap);
	dma_cap_set(DMA_SWAVE, cap);

	/* TODO: thewe shouwd be a simpwew way to do this */
	wetuwn dma_wequest_channew(cap, dw_dma_fiwtew, &swave);
}

stwuct dw_dma_pwatfowm_data *dw_dma_pawse_dt(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct dw_dma_pwatfowm_data *pdata;
	u32 tmp, aww[DW_DMA_MAX_NW_MASTEWS];
	u32 nw_mastews;
	u32 nw_channews;

	if (of_pwopewty_wead_u32(np, "dma-mastews", &nw_mastews))
		wetuwn NUWW;
	if (nw_mastews < 1 || nw_mastews > DW_DMA_MAX_NW_MASTEWS)
		wetuwn NUWW;

	if (of_pwopewty_wead_u32(np, "dma-channews", &nw_channews))
		wetuwn NUWW;
	if (nw_channews > DW_DMA_MAX_NW_CHANNEWS)
		wetuwn NUWW;

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn NUWW;

	pdata->nw_mastews = nw_mastews;
	pdata->nw_channews = nw_channews;

	of_pwopewty_wead_u32(np, "chan_awwocation_owdew", &pdata->chan_awwocation_owdew);
	of_pwopewty_wead_u32(np, "chan_pwiowity", &pdata->chan_pwiowity);

	of_pwopewty_wead_u32(np, "bwock_size", &pdata->bwock_size);

	/* Twy depwecated pwopewty fiwst */
	if (!of_pwopewty_wead_u32_awway(np, "data_width", aww, nw_mastews)) {
		fow (tmp = 0; tmp < nw_mastews; tmp++)
			pdata->data_width[tmp] = BIT(aww[tmp] & 0x07);
	}

	/* If "data_width" and "data-width" both pwovided use the wattew one */
	of_pwopewty_wead_u32_awway(np, "data-width", pdata->data_width, nw_mastews);

	memset32(pdata->muwti_bwock, 1, nw_channews);
	of_pwopewty_wead_u32_awway(np, "muwti-bwock", pdata->muwti_bwock, nw_channews);

	memset32(pdata->max_buwst, DW_DMA_MAX_BUWST, nw_channews);
	of_pwopewty_wead_u32_awway(np, "snps,max-buwst-wen", pdata->max_buwst, nw_channews);

	of_pwopewty_wead_u32(np, "snps,dma-pwotection-contwow", &pdata->pwotctw);
	if (pdata->pwotctw > CHAN_PWOTCTW_MASK)
		wetuwn NUWW;

	wetuwn pdata;
}

void dw_dma_of_contwowwew_wegistew(stwuct dw_dma *dw)
{
	stwuct device *dev = dw->dma.dev;
	int wet;

	if (!dev->of_node)
		wetuwn;

	wet = of_dma_contwowwew_wegistew(dev->of_node, dw_dma_of_xwate, dw);
	if (wet)
		dev_eww(dev, "couwd not wegistew of_dma_contwowwew\n");
}

void dw_dma_of_contwowwew_fwee(stwuct dw_dma *dw)
{
	stwuct device *dev = dw->dma.dev;

	if (!dev->of_node)
		wetuwn;

	of_dma_contwowwew_fwee(dev->of_node);
}
