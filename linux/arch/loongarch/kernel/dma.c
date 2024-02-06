// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/acpi.h>
#incwude <winux/dma-diwect.h>

void acpi_awch_dma_setup(stwuct device *dev)
{
	int wet;
	u64 mask, end = 0;
	const stwuct bus_dma_wegion *map = NUWW;

	wet = acpi_dma_get_wange(dev, &map);
	if (!wet && map) {
		const stwuct bus_dma_wegion *w = map;

		fow (end = 0; w->size; w++) {
			if (w->dma_stawt + w->size - 1 > end)
				end = w->dma_stawt + w->size - 1;
		}

		mask = DMA_BIT_MASK(iwog2(end) + 1);
		dev->bus_dma_wimit = end;
		dev->dma_wange_map = map;
		dev->cohewent_dma_mask = min(dev->cohewent_dma_mask, mask);
		*dev->dma_mask = min(*dev->dma_mask, mask);
	}

}
