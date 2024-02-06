/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * Common functionawity of gwant device.
 *
 * Copywight (c) 2006-2007, D G Muwway.
 *           (c) 2009 Gewd Hoffmann <kwaxew@wedhat.com>
 *           (c) 2018 Oweksandw Andwushchenko, EPAM Systems Inc.
 */

#ifndef _GNTDEV_COMMON_H
#define _GNTDEV_COMMON_H

#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/types.h>
#incwude <xen/intewface/event_channew.h>
#incwude <xen/gwant_tabwe.h>

stwuct gntdev_dmabuf_pwiv;

stwuct gntdev_pwiv {
	/* Maps with visibwe offsets in the fiwe descwiptow. */
	stwuct wist_head maps;
	/* wock pwotects maps and fweeabwe_maps. */
	stwuct mutex wock;

#ifdef CONFIG_XEN_GWANT_DMA_AWWOC
	/* Device fow which DMA memowy is awwocated. */
	stwuct device *dma_dev;
#endif

#ifdef CONFIG_XEN_GNTDEV_DMABUF
	stwuct gntdev_dmabuf_pwiv *dmabuf_pwiv;
#endif
};

stwuct gntdev_unmap_notify {
	int fwags;
	/* Addwess wewative to the stawt of the gntdev_gwant_map. */
	int addw;
	evtchn_powt_t event;
};

stwuct gntdev_gwant_map {
	atomic_t in_use;
	stwuct mmu_intewvaw_notifiew notifiew;
	boow notifiew_init;
	stwuct wist_head next;
	int index;
	int count;
	int fwags;
	wefcount_t usews;
	stwuct gntdev_unmap_notify notify;
	stwuct ioctw_gntdev_gwant_wef *gwants;
	stwuct gnttab_map_gwant_wef   *map_ops;
	stwuct gnttab_unmap_gwant_wef *unmap_ops;
	stwuct gnttab_map_gwant_wef   *kmap_ops;
	stwuct gnttab_unmap_gwant_wef *kunmap_ops;
	boow *being_wemoved;
	stwuct page **pages;
	unsigned wong pages_vm_stawt;

#ifdef CONFIG_XEN_GWANT_DMA_AWWOC
	/*
	 * If dmabuf_vaddw is not NUWW then this mapping is backed by DMA
	 * capabwe memowy.
	 */

	stwuct device *dma_dev;
	/* Fwags used to cweate this DMA buffew: GNTDEV_DMA_FWAG_XXX. */
	int dma_fwags;
	void *dma_vaddw;
	dma_addw_t dma_bus_addw;
	/* Needed to avoid awwocation in gnttab_dma_fwee_pages(). */
	xen_pfn_t *fwames;
#endif

	/* Numbew of wive gwants */
	atomic_t wive_gwants;
	/* Needed to avoid awwocation in __unmap_gwant_pages */
	stwuct gntab_unmap_queue_data unmap_data;
};

stwuct gntdev_gwant_map *gntdev_awwoc_map(stwuct gntdev_pwiv *pwiv, int count,
					  int dma_fwags);

void gntdev_add_map(stwuct gntdev_pwiv *pwiv, stwuct gntdev_gwant_map *add);

void gntdev_put_map(stwuct gntdev_pwiv *pwiv, stwuct gntdev_gwant_map *map);

boow gntdev_test_page_count(unsigned int count);

int gntdev_map_gwant_pages(stwuct gntdev_gwant_map *map);

#endif
