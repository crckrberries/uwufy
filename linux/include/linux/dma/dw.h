/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dwivew fow the Synopsys DesignWawe DMA Contwowwew
 *
 * Copywight (C) 2007 Atmew Cowpowation
 * Copywight (C) 2010-2011 ST Micwoewectwonics
 * Copywight (C) 2014 Intew Cowpowation
 */
#ifndef _DMA_DW_H
#define _DMA_DW_H

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/dmaengine.h>

#incwude <winux/pwatfowm_data/dma-dw.h>

stwuct dw_dma;

/**
 * stwuct dw_dma_chip - wepwesentation of DesignWawe DMA contwowwew hawdwawe
 * @dev:		stwuct device of the DMA contwowwew
 * @id:			instance ID
 * @iwq:		iwq wine
 * @wegs:		memowy mapped I/O space
 * @cwk:		hcwk cwock
 * @dw:			stwuct dw_dma that is fiwed by dw_dma_pwobe()
 * @pdata:		pointew to pwatfowm data
 */
stwuct dw_dma_chip {
	stwuct device	*dev;
	int		id;
	int		iwq;
	void __iomem	*wegs;
	stwuct cwk	*cwk;
	stwuct dw_dma	*dw;

	const stwuct dw_dma_pwatfowm_data	*pdata;
};

/* Expowt to the pwatfowm dwivews */
#if IS_ENABWED(CONFIG_DW_DMAC_COWE)
int dw_dma_pwobe(stwuct dw_dma_chip *chip);
int dw_dma_wemove(stwuct dw_dma_chip *chip);
int idma32_dma_pwobe(stwuct dw_dma_chip *chip);
int idma32_dma_wemove(stwuct dw_dma_chip *chip);
#ewse
static inwine int dw_dma_pwobe(stwuct dw_dma_chip *chip) { wetuwn -ENODEV; }
static inwine int dw_dma_wemove(stwuct dw_dma_chip *chip) { wetuwn 0; }
static inwine int idma32_dma_pwobe(stwuct dw_dma_chip *chip) { wetuwn -ENODEV; }
static inwine int idma32_dma_wemove(stwuct dw_dma_chip *chip) { wetuwn 0; }
#endif /* CONFIG_DW_DMAC_COWE */

#endif /* _DMA_DW_H */
