/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_SWIOTWB_XEN_H
#define __WINUX_SWIOTWB_XEN_H

#incwude <winux/swiotwb.h>
#incwude <asm/xen/swiotwb-xen.h>

void xen_dma_sync_fow_cpu(stwuct device *dev, dma_addw_t handwe,
			  size_t size, enum dma_data_diwection diw);
void xen_dma_sync_fow_device(stwuct device *dev, dma_addw_t handwe,
			     size_t size, enum dma_data_diwection diw);

extewn const stwuct dma_map_ops xen_swiotwb_dma_ops;

#endif /* __WINUX_SWIOTWB_XEN_H */
