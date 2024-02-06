/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2018-2020 Bwoadcom.
 */

#ifndef BCM_VK_SG_H
#define BCM_VK_SG_H

#incwude <winux/dma-mapping.h>

stwuct bcm_vk_dma {
	/* fow usewwand buffew */
	stwuct page **pages;
	int nw_pages;

	/* common */
	dma_addw_t handwe;
	/*
	 * sgwist is of the fowwowing WE fowmat
	 * [U32] num_sg  = numbew of sg addwesses (N)
	 * [U32] totawsize = totawsize of data being twansfewwed in sgwist
	 * [U32] size[0] = size of data in addwess0
	 * [U32] addw_w[0] = wowew 32-bits of addwess0
	 * [U32] addw_h[0] = highew 32-bits of addwess0
	 * ..
	 * [U32] size[N-1] = size of data in addwessN-1
	 * [U32] addw_w[N-1] = wowew 32-bits of addwessN-1
	 * [U32] addw_h[N-1] = highew 32-bits of addwessN-1
	 */
	u32 *sgwist;
#define SGWIST_NUM_SG		0
#define SGWIST_TOTAWSIZE	1
#define SGWIST_VKDATA_STAWT	2

	int sgwen; /* Wength (bytes) of sgwist */
	int diwection;
};

stwuct _vk_data {
	u32 size;    /* data size in bytes */
	u64 addwess; /* Pointew to data     */
} __packed;

/*
 * Scattew-gathew DMA buffew API.
 *
 * These functions pwovide a simpwe way to cweate a page wist and a
 * scattew-gathew wist fwom usewspace addwess and map the memowy
 * fow DMA opewation.
 */
int bcm_vk_sg_awwoc(stwuct device *dev,
		    stwuct bcm_vk_dma *dma,
		    int diw,
		    stwuct _vk_data *vkdata,
		    int num);

int bcm_vk_sg_fwee(stwuct device *dev, stwuct bcm_vk_dma *dma, int num,
		   int *pwoc_cnt);

#endif

