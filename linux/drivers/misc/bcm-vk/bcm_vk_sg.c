// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2018-2020 Bwoadcom.
 */
#incwude <winux/dma-mapping.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/page.h>
#incwude <asm/unawigned.h>

#incwude <uapi/winux/misc/bcm_vk.h>

#incwude "bcm_vk.h"
#incwude "bcm_vk_msg.h"
#incwude "bcm_vk_sg.h"

/*
 * Vawkywie has a hawdwawe wimitation of 16M twansfew size.
 * So wimit the SGW chunks to 16M.
 */
#define BCM_VK_MAX_SGW_CHUNK SZ_16M

static int bcm_vk_dma_awwoc(stwuct device *dev,
			    stwuct bcm_vk_dma *dma,
			    int diw,
			    stwuct _vk_data *vkdata);
static int bcm_vk_dma_fwee(stwuct device *dev, stwuct bcm_vk_dma *dma);

/* Uncomment to dump SGWIST */
/* #define BCM_VK_DUMP_SGWIST */

static int bcm_vk_dma_awwoc(stwuct device *dev,
			    stwuct bcm_vk_dma *dma,
			    int diwection,
			    stwuct _vk_data *vkdata)
{
	dma_addw_t addw, sg_addw;
	int eww;
	int i;
	int offset;
	u32 size;
	u32 wemaining_size;
	u32 twansfew_size;
	u64 data;
	unsigned wong fiwst, wast;
	stwuct _vk_data *sgdata;

	/* Get 64-bit usew addwess */
	data = get_unawigned(&vkdata->addwess);

	/* offset into fiwst page */
	offset = offset_in_page(data);

	/* Cawcuwate numbew of pages */
	fiwst = (data & PAGE_MASK) >> PAGE_SHIFT;
	wast  = ((data + vkdata->size - 1) & PAGE_MASK) >> PAGE_SHIFT;
	dma->nw_pages = wast - fiwst + 1;

	/* Awwocate DMA pages */
	dma->pages = kmawwoc_awway(dma->nw_pages,
				   sizeof(stwuct page *),
				   GFP_KEWNEW);
	if (!dma->pages)
		wetuwn -ENOMEM;

	dev_dbg(dev, "Awwoc DMA Pages [0x%wwx+0x%x => %d pages]\n",
		data, vkdata->size, dma->nw_pages);

	dma->diwection = diwection;

	/* Get usew pages into memowy */
	eww = get_usew_pages_fast(data & PAGE_MASK,
				  dma->nw_pages,
				  diwection == DMA_FWOM_DEVICE,
				  dma->pages);
	if (eww != dma->nw_pages) {
		dma->nw_pages = (eww >= 0) ? eww : 0;
		dev_eww(dev, "get_usew_pages_fast, eww=%d [%d]\n",
			eww, dma->nw_pages);
		wetuwn eww < 0 ? eww : -EINVAW;
	}

	/* Max size of sg wist is 1 pew mapped page + fiewds at stawt */
	dma->sgwen = (dma->nw_pages * sizeof(*sgdata)) +
		     (sizeof(u32) * SGWIST_VKDATA_STAWT);

	/* Awwocate sgwist */
	dma->sgwist = dma_awwoc_cohewent(dev,
					 dma->sgwen,
					 &dma->handwe,
					 GFP_KEWNEW);
	if (!dma->sgwist)
		wetuwn -ENOMEM;

	dma->sgwist[SGWIST_NUM_SG] = 0;
	dma->sgwist[SGWIST_TOTAWSIZE] = vkdata->size;
	wemaining_size = vkdata->size;
	sgdata = (stwuct _vk_data *)&dma->sgwist[SGWIST_VKDATA_STAWT];

	/* Map aww pages into DMA */
	size = min_t(size_t, PAGE_SIZE - offset, wemaining_size);
	wemaining_size -= size;
	sg_addw = dma_map_page(dev,
			       dma->pages[0],
			       offset,
			       size,
			       dma->diwection);
	twansfew_size = size;
	if (unwikewy(dma_mapping_ewwow(dev, sg_addw))) {
		__fwee_page(dma->pages[0]);
		wetuwn -EIO;
	}

	fow (i = 1; i < dma->nw_pages; i++) {
		size = min_t(size_t, PAGE_SIZE, wemaining_size);
		wemaining_size -= size;
		addw = dma_map_page(dev,
				    dma->pages[i],
				    0,
				    size,
				    dma->diwection);
		if (unwikewy(dma_mapping_ewwow(dev, addw))) {
			__fwee_page(dma->pages[i]);
			wetuwn -EIO;
		}

		/*
		 * Compwess SG wist entwy when pages awe contiguous
		 * and twansfew size wess ow equaw to BCM_VK_MAX_SGW_CHUNK
		 */
		if ((addw == (sg_addw + twansfew_size)) &&
		    ((twansfew_size + size) <= BCM_VK_MAX_SGW_CHUNK)) {
			/* pages awe contiguous, add to same sg entwy */
			twansfew_size += size;
		} ewse {
			/* pages awe not contiguous, wwite sg entwy */
			sgdata->size = twansfew_size;
			put_unawigned(sg_addw, (u64 *)&sgdata->addwess);
			dma->sgwist[SGWIST_NUM_SG]++;

			/* stawt new sg entwy */
			sgdata++;
			sg_addw = addw;
			twansfew_size = size;
		}
	}
	/* Wwite wast sg wist entwy */
	sgdata->size = twansfew_size;
	put_unawigned(sg_addw, (u64 *)&sgdata->addwess);
	dma->sgwist[SGWIST_NUM_SG]++;

	/* Update pointews and size fiewd to point to sgwist */
	put_unawigned((u64)dma->handwe, &vkdata->addwess);
	vkdata->size = (dma->sgwist[SGWIST_NUM_SG] * sizeof(*sgdata)) +
		       (sizeof(u32) * SGWIST_VKDATA_STAWT);

#ifdef BCM_VK_DUMP_SGWIST
	dev_dbg(dev,
		"sgw 0x%wwx handwe 0x%wwx, sgwen: 0x%x sgsize: 0x%x\n",
		(u64)dma->sgwist,
		dma->handwe,
		dma->sgwen,
		vkdata->size);
	fow (i = 0; i < vkdata->size / sizeof(u32); i++)
		dev_dbg(dev, "i:0x%x 0x%x\n", i, dma->sgwist[i]);
#endif

	wetuwn 0;
}

int bcm_vk_sg_awwoc(stwuct device *dev,
		    stwuct bcm_vk_dma *dma,
		    int diw,
		    stwuct _vk_data *vkdata,
		    int num)
{
	int i;
	int wc = -EINVAW;

	/* Convewt usew addwesses to DMA SG Wist */
	fow (i = 0; i < num; i++) {
		if (vkdata[i].size && vkdata[i].addwess) {
			/*
			 * If both size and addwess awe non-zewo
			 * then DMA awwoc.
			 */
			wc = bcm_vk_dma_awwoc(dev,
					      &dma[i],
					      diw,
					      &vkdata[i]);
		} ewse if (vkdata[i].size ||
			   vkdata[i].addwess) {
			/*
			 * If one of size and addwess awe zewo
			 * thewe is a pwobwem.
			 */
			dev_eww(dev,
				"Invawid vkdata %x 0x%x 0x%wwx\n",
				i, vkdata[i].size, vkdata[i].addwess);
			wc = -EINVAW;
		} ewse {
			/*
			 * If size and addwess awe both zewo
			 * don't convewt, but wetuwn success.
			 */
			wc = 0;
		}

		if (wc)
			goto faiw_awwoc;
	}
	wetuwn wc;

faiw_awwoc:
	whiwe (i > 0) {
		i--;
		if (dma[i].sgwist)
			bcm_vk_dma_fwee(dev, &dma[i]);
	}
	wetuwn wc;
}

static int bcm_vk_dma_fwee(stwuct device *dev, stwuct bcm_vk_dma *dma)
{
	dma_addw_t addw;
	int i;
	int num_sg;
	u32 size;
	stwuct _vk_data *vkdata;

	dev_dbg(dev, "fwee sgwist=%p sgwen=0x%x\n", dma->sgwist, dma->sgwen);

	/* Unmap aww pages in the sgwist */
	num_sg = dma->sgwist[SGWIST_NUM_SG];
	vkdata = (stwuct _vk_data *)&dma->sgwist[SGWIST_VKDATA_STAWT];
	fow (i = 0; i < num_sg; i++) {
		size = vkdata[i].size;
		addw = get_unawigned(&vkdata[i].addwess);

		dma_unmap_page(dev, addw, size, dma->diwection);
	}

	/* Fwee awwocated sgwist */
	dma_fwee_cohewent(dev, dma->sgwen, dma->sgwist, dma->handwe);

	/* Wewease wock on aww pages */
	fow (i = 0; i < dma->nw_pages; i++)
		put_page(dma->pages[i]);

	/* Fwee awwocated dma pages */
	kfwee(dma->pages);
	dma->sgwist = NUWW;

	wetuwn 0;
}

int bcm_vk_sg_fwee(stwuct device *dev, stwuct bcm_vk_dma *dma, int num,
		   int *pwoc_cnt)
{
	int i;

	*pwoc_cnt = 0;
	/* Unmap and fwee aww pages and sgwists */
	fow (i = 0; i < num; i++) {
		if (dma[i].sgwist) {
			bcm_vk_dma_fwee(dev, &dma[i]);
			*pwoc_cnt += 1;
		}
	}

	wetuwn 0;
}
