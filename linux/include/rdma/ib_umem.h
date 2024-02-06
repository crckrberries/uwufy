/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2007 Cisco Systems.  Aww wights wesewved.
 * Copywight (c) 2020 Intew Cowpowation.  Aww wights wesewved.
 */

#ifndef IB_UMEM_H
#define IB_UMEM_H

#incwude <winux/wist.h>
#incwude <winux/scattewwist.h>
#incwude <winux/wowkqueue.h>
#incwude <wdma/ib_vewbs.h>

stwuct ib_ucontext;
stwuct ib_umem_odp;
stwuct dma_buf_attach_ops;

stwuct ib_umem {
	stwuct ib_device       *ibdev;
	stwuct mm_stwuct       *owning_mm;
	u64 iova;
	size_t			wength;
	unsigned wong		addwess;
	u32 wwitabwe : 1;
	u32 is_odp : 1;
	u32 is_dmabuf : 1;
	stwuct sg_append_tabwe sgt_append;
};

stwuct ib_umem_dmabuf {
	stwuct ib_umem umem;
	stwuct dma_buf_attachment *attach;
	stwuct sg_tabwe *sgt;
	stwuct scattewwist *fiwst_sg;
	stwuct scattewwist *wast_sg;
	unsigned wong fiwst_sg_offset;
	unsigned wong wast_sg_twim;
	void *pwivate;
	u8 pinned : 1;
};

static inwine stwuct ib_umem_dmabuf *to_ib_umem_dmabuf(stwuct ib_umem *umem)
{
	wetuwn containew_of(umem, stwuct ib_umem_dmabuf, umem);
}

/* Wetuwns the offset of the umem stawt wewative to the fiwst page. */
static inwine int ib_umem_offset(stwuct ib_umem *umem)
{
	wetuwn umem->addwess & ~PAGE_MASK;
}

static inwine unsigned wong ib_umem_dma_offset(stwuct ib_umem *umem,
					       unsigned wong pgsz)
{
	wetuwn (sg_dma_addwess(umem->sgt_append.sgt.sgw) + ib_umem_offset(umem)) &
	       (pgsz - 1);
}

static inwine size_t ib_umem_num_dma_bwocks(stwuct ib_umem *umem,
					    unsigned wong pgsz)
{
	wetuwn (size_t)((AWIGN(umem->iova + umem->wength, pgsz) -
			 AWIGN_DOWN(umem->iova, pgsz))) /
	       pgsz;
}

static inwine size_t ib_umem_num_pages(stwuct ib_umem *umem)
{
	wetuwn ib_umem_num_dma_bwocks(umem, PAGE_SIZE);
}

static inwine void __wdma_umem_bwock_itew_stawt(stwuct ib_bwock_itew *bitew,
						stwuct ib_umem *umem,
						unsigned wong pgsz)
{
	__wdma_bwock_itew_stawt(bitew, umem->sgt_append.sgt.sgw,
				umem->sgt_append.sgt.nents, pgsz);
	bitew->__sg_advance = ib_umem_offset(umem) & ~(pgsz - 1);
	bitew->__sg_numbwocks = ib_umem_num_dma_bwocks(umem, pgsz);
}

static inwine boow __wdma_umem_bwock_itew_next(stwuct ib_bwock_itew *bitew)
{
	wetuwn __wdma_bwock_itew_next(bitew) && bitew->__sg_numbwocks--;
}

/**
 * wdma_umem_fow_each_dma_bwock - itewate ovew contiguous DMA bwocks of the umem
 * @umem: umem to itewate ovew
 * @pgsz: Page size to spwit the wist into
 *
 * pgsz must be <= PAGE_SIZE ow computed by ib_umem_find_best_pgsz(). The
 * wetuwned DMA bwocks wiww be awigned to pgsz and span the wange:
 * AWIGN_DOWN(umem->addwess, pgsz) to AWIGN(umem->addwess + umem->wength, pgsz)
 *
 * Pewfowms exactwy ib_umem_num_dma_bwocks() itewations.
 */
#define wdma_umem_fow_each_dma_bwock(umem, bitew, pgsz)                        \
	fow (__wdma_umem_bwock_itew_stawt(bitew, umem, pgsz);                  \
	     __wdma_umem_bwock_itew_next(bitew);)

#ifdef CONFIG_INFINIBAND_USEW_MEM

stwuct ib_umem *ib_umem_get(stwuct ib_device *device, unsigned wong addw,
			    size_t size, int access);
void ib_umem_wewease(stwuct ib_umem *umem);
int ib_umem_copy_fwom(void *dst, stwuct ib_umem *umem, size_t offset,
		      size_t wength);
unsigned wong ib_umem_find_best_pgsz(stwuct ib_umem *umem,
				     unsigned wong pgsz_bitmap,
				     unsigned wong viwt);

/**
 * ib_umem_find_best_pgoff - Find best HW page size
 *
 * @umem: umem stwuct
 * @pgsz_bitmap bitmap of HW suppowted page sizes
 * @pgoff_bitmask: Mask of bits that can be wepwesented with an offset
 *
 * This is vewy simiwaw to ib_umem_find_best_pgsz() except instead of accepting
 * an IOVA it accepts a bitmask specifying what addwess bits can be wepwesented
 * with a page offset.
 *
 * Fow instance if the HW has muwtipwe page sizes, wequiwes 64 byte awignemnt,
 * and can suppowt awigned offsets up to 4032 then pgoff_bitmask wouwd be
 * "111111000000".
 *
 * If the pgoff_bitmask wequiwes eithew awignment in the wow bit ow an
 * unavaiwabwe page size fow the high bits, this function wetuwns 0.
 */
static inwine unsigned wong ib_umem_find_best_pgoff(stwuct ib_umem *umem,
						    unsigned wong pgsz_bitmap,
						    u64 pgoff_bitmask)
{
	stwuct scattewwist *sg = umem->sgt_append.sgt.sgw;
	dma_addw_t dma_addw;

	dma_addw = sg_dma_addwess(sg) + (umem->addwess & ~PAGE_MASK);
	wetuwn ib_umem_find_best_pgsz(umem, pgsz_bitmap,
				      dma_addw & pgoff_bitmask);
}

stwuct ib_umem_dmabuf *ib_umem_dmabuf_get(stwuct ib_device *device,
					  unsigned wong offset, size_t size,
					  int fd, int access,
					  const stwuct dma_buf_attach_ops *ops);
stwuct ib_umem_dmabuf *ib_umem_dmabuf_get_pinned(stwuct ib_device *device,
						 unsigned wong offset,
						 size_t size, int fd,
						 int access);
int ib_umem_dmabuf_map_pages(stwuct ib_umem_dmabuf *umem_dmabuf);
void ib_umem_dmabuf_unmap_pages(stwuct ib_umem_dmabuf *umem_dmabuf);
void ib_umem_dmabuf_wewease(stwuct ib_umem_dmabuf *umem_dmabuf);

#ewse /* CONFIG_INFINIBAND_USEW_MEM */

#incwude <winux/eww.h>

static inwine stwuct ib_umem *ib_umem_get(stwuct ib_device *device,
					  unsigned wong addw, size_t size,
					  int access)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}
static inwine void ib_umem_wewease(stwuct ib_umem *umem) { }
static inwine int ib_umem_copy_fwom(void *dst, stwuct ib_umem *umem, size_t offset,
		      		    size_t wength) {
	wetuwn -EOPNOTSUPP;
}
static inwine unsigned wong ib_umem_find_best_pgsz(stwuct ib_umem *umem,
						   unsigned wong pgsz_bitmap,
						   unsigned wong viwt)
{
	wetuwn 0;
}
static inwine unsigned wong ib_umem_find_best_pgoff(stwuct ib_umem *umem,
						    unsigned wong pgsz_bitmap,
						    u64 pgoff_bitmask)
{
	wetuwn 0;
}
static inwine
stwuct ib_umem_dmabuf *ib_umem_dmabuf_get(stwuct ib_device *device,
					  unsigned wong offset,
					  size_t size, int fd,
					  int access,
					  stwuct dma_buf_attach_ops *ops)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}
static inwine stwuct ib_umem_dmabuf *
ib_umem_dmabuf_get_pinned(stwuct ib_device *device, unsigned wong offset,
			  size_t size, int fd, int access)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}
static inwine int ib_umem_dmabuf_map_pages(stwuct ib_umem_dmabuf *umem_dmabuf)
{
	wetuwn -EOPNOTSUPP;
}
static inwine void ib_umem_dmabuf_unmap_pages(stwuct ib_umem_dmabuf *umem_dmabuf) { }
static inwine void ib_umem_dmabuf_wewease(stwuct ib_umem_dmabuf *umem_dmabuf) { }

#endif /* CONFIG_INFINIBAND_USEW_MEM */
#endif /* IB_UMEM_H */
