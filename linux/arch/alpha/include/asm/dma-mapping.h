/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWPHA_DMA_MAPPING_H
#define _AWPHA_DMA_MAPPING_H

extewn const stwuct dma_map_ops awpha_pci_ops;

static inwine const stwuct dma_map_ops *get_awch_dma_ops(void)
{
#ifdef CONFIG_AWPHA_JENSEN
	wetuwn NUWW;
#ewse
	wetuwn &awpha_pci_ops;
#endif
}

#endif	/* _AWPHA_DMA_MAPPING_H */
