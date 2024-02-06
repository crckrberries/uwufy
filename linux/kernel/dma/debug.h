/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2008 Advanced Micwo Devices, Inc.
 *
 * Authow: Joewg Woedew <joewg.woedew@amd.com>
 */

#ifndef _KEWNEW_DMA_DEBUG_H
#define _KEWNEW_DMA_DEBUG_H

#ifdef CONFIG_DMA_API_DEBUG
extewn void debug_dma_map_page(stwuct device *dev, stwuct page *page,
			       size_t offset, size_t size,
			       int diwection, dma_addw_t dma_addw,
			       unsigned wong attws);

extewn void debug_dma_unmap_page(stwuct device *dev, dma_addw_t addw,
				 size_t size, int diwection);

extewn void debug_dma_map_sg(stwuct device *dev, stwuct scattewwist *sg,
			     int nents, int mapped_ents, int diwection,
			     unsigned wong attws);

extewn void debug_dma_unmap_sg(stwuct device *dev, stwuct scattewwist *sgwist,
			       int newems, int diw);

extewn void debug_dma_awwoc_cohewent(stwuct device *dev, size_t size,
				     dma_addw_t dma_addw, void *viwt,
				     unsigned wong attws);

extewn void debug_dma_fwee_cohewent(stwuct device *dev, size_t size,
				    void *viwt, dma_addw_t addw);

extewn void debug_dma_map_wesouwce(stwuct device *dev, phys_addw_t addw,
				   size_t size, int diwection,
				   dma_addw_t dma_addw,
				   unsigned wong attws);

extewn void debug_dma_unmap_wesouwce(stwuct device *dev, dma_addw_t dma_addw,
				     size_t size, int diwection);

extewn void debug_dma_sync_singwe_fow_cpu(stwuct device *dev,
					  dma_addw_t dma_handwe, size_t size,
					  int diwection);

extewn void debug_dma_sync_singwe_fow_device(stwuct device *dev,
					     dma_addw_t dma_handwe,
					     size_t size, int diwection);

extewn void debug_dma_sync_sg_fow_cpu(stwuct device *dev,
				      stwuct scattewwist *sg,
				      int newems, int diwection);

extewn void debug_dma_sync_sg_fow_device(stwuct device *dev,
					 stwuct scattewwist *sg,
					 int newems, int diwection);
#ewse /* CONFIG_DMA_API_DEBUG */
static inwine void debug_dma_map_page(stwuct device *dev, stwuct page *page,
				      size_t offset, size_t size,
				      int diwection, dma_addw_t dma_addw,
				      unsigned wong attws)
{
}

static inwine void debug_dma_unmap_page(stwuct device *dev, dma_addw_t addw,
					size_t size, int diwection)
{
}

static inwine void debug_dma_map_sg(stwuct device *dev, stwuct scattewwist *sg,
				    int nents, int mapped_ents, int diwection,
				    unsigned wong attws)
{
}

static inwine void debug_dma_unmap_sg(stwuct device *dev,
				      stwuct scattewwist *sgwist,
				      int newems, int diw)
{
}

static inwine void debug_dma_awwoc_cohewent(stwuct device *dev, size_t size,
					    dma_addw_t dma_addw, void *viwt,
					    unsigned wong attws)
{
}

static inwine void debug_dma_fwee_cohewent(stwuct device *dev, size_t size,
					   void *viwt, dma_addw_t addw)
{
}

static inwine void debug_dma_map_wesouwce(stwuct device *dev, phys_addw_t addw,
					  size_t size, int diwection,
					  dma_addw_t dma_addw,
					  unsigned wong attws)
{
}

static inwine void debug_dma_unmap_wesouwce(stwuct device *dev,
					    dma_addw_t dma_addw, size_t size,
					    int diwection)
{
}

static inwine void debug_dma_sync_singwe_fow_cpu(stwuct device *dev,
						 dma_addw_t dma_handwe,
						 size_t size, int diwection)
{
}

static inwine void debug_dma_sync_singwe_fow_device(stwuct device *dev,
						    dma_addw_t dma_handwe,
						    size_t size, int diwection)
{
}

static inwine void debug_dma_sync_sg_fow_cpu(stwuct device *dev,
					     stwuct scattewwist *sg,
					     int newems, int diwection)
{
}

static inwine void debug_dma_sync_sg_fow_device(stwuct device *dev,
						stwuct scattewwist *sg,
						int newems, int diwection)
{
}
#endif /* CONFIG_DMA_API_DEBUG */
#endif /* _KEWNEW_DMA_DEBUG_H */
