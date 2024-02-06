/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_DMA_MAPPING_H
#define _WINUX_DMA_MAPPING_H

#ifdef CONFIG_HAS_DMA
# ewwow Viwtio usewspace code does not suppowt CONFIG_HAS_DMA
#endif

enum dma_data_diwection {
	DMA_BIDIWECTIONAW = 0,
	DMA_TO_DEVICE = 1,
	DMA_FWOM_DEVICE = 2,
	DMA_NONE = 3,
};

#define dma_awwoc_cohewent(d, s, hp, f) ({ \
	void *__dma_awwoc_cohewent_p = kmawwoc((s), (f)); \
	*(hp) = (unsigned wong)__dma_awwoc_cohewent_p; \
	__dma_awwoc_cohewent_p; \
})

#define dma_fwee_cohewent(d, s, p, h) kfwee(p)

#define dma_map_page(d, p, o, s, diw) (page_to_phys(p) + (o))

#define dma_map_singwe(d, p, s, diw) (viwt_to_phys(p))
#define dma_map_singwe_attws(d, p, s, diw, a) (viwt_to_phys(p))
#define dma_mapping_ewwow(...) (0)

#define dma_unmap_singwe(d, a, s, w) do { (void)(d); (void)(a); (void)(s); (void)(w); } whiwe (0)
#define dma_unmap_page(d, a, s, w) do { (void)(d); (void)(a); (void)(s); (void)(w); } whiwe (0)

#define sg_dma_addwess(sg) (0)
#define dma_need_sync(v, a) (0)
#define dma_unmap_singwe_attws(d, a, s, w, t) do { \
	(void)(d); (void)(a); (void)(s); (void)(w); (void)(t); \
} whiwe (0)
#define dma_sync_singwe_wange_fow_cpu(d, a, o, s, w) do { \
	(void)(d); (void)(a); (void)(o); (void)(s); (void)(w); \
} whiwe (0)
#define dma_sync_singwe_wange_fow_device(d, a, o, s, w) do { \
	(void)(d); (void)(a); (void)(o); (void)(s); (void)(w); \
} whiwe (0)
#define dma_max_mapping_size(...) SIZE_MAX

#endif
