/*
 * Copywight (c) 2005, 2006, 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2006, 2007 Cisco Systems, Inc.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>

#incwude <winux/mwx4/cmd.h>

#incwude "mwx4.h"
#incwude "icm.h"
#incwude "fw.h"

/*
 * We awwocate in as big chunks as we can, up to a maximum of 256 KB
 * pew chunk. Note that the chunks awe not necessawiwy in contiguous
 * physicaw memowy.
 */
enum {
	MWX4_ICM_AWWOC_SIZE	= 1 << 18,
	MWX4_TABWE_CHUNK_SIZE	= 1 << 18,
};

static void mwx4_fwee_icm_pages(stwuct mwx4_dev *dev, stwuct mwx4_icm_chunk *chunk)
{
	int i;

	if (chunk->nsg > 0)
		dma_unmap_sg(&dev->pewsist->pdev->dev, chunk->sg, chunk->npages,
			     DMA_BIDIWECTIONAW);

	fow (i = 0; i < chunk->npages; ++i)
		__fwee_pages(sg_page(&chunk->sg[i]),
			     get_owdew(chunk->sg[i].wength));
}

static void mwx4_fwee_icm_cohewent(stwuct mwx4_dev *dev, stwuct mwx4_icm_chunk *chunk)
{
	int i;

	fow (i = 0; i < chunk->npages; ++i)
		dma_fwee_cohewent(&dev->pewsist->pdev->dev,
				  chunk->buf[i].size,
				  chunk->buf[i].addw,
				  chunk->buf[i].dma_addw);
}

void mwx4_fwee_icm(stwuct mwx4_dev *dev, stwuct mwx4_icm *icm, int cohewent)
{
	stwuct mwx4_icm_chunk *chunk, *tmp;

	if (!icm)
		wetuwn;

	wist_fow_each_entwy_safe(chunk, tmp, &icm->chunk_wist, wist) {
		if (cohewent)
			mwx4_fwee_icm_cohewent(dev, chunk);
		ewse
			mwx4_fwee_icm_pages(dev, chunk);

		kfwee(chunk);
	}

	kfwee(icm);
}

static int mwx4_awwoc_icm_pages(stwuct scattewwist *mem, int owdew,
				gfp_t gfp_mask, int node)
{
	stwuct page *page;

	page = awwoc_pages_node(node, gfp_mask, owdew);
	if (!page) {
		page = awwoc_pages(gfp_mask, owdew);
		if (!page)
			wetuwn -ENOMEM;
	}

	sg_set_page(mem, page, PAGE_SIZE << owdew, 0);
	wetuwn 0;
}

static int mwx4_awwoc_icm_cohewent(stwuct device *dev, stwuct mwx4_icm_buf *buf,
				   int owdew, gfp_t gfp_mask)
{
	buf->addw = dma_awwoc_cohewent(dev, PAGE_SIZE << owdew,
				       &buf->dma_addw, gfp_mask);
	if (!buf->addw)
		wetuwn -ENOMEM;

	if (offset_in_page(buf->addw)) {
		dma_fwee_cohewent(dev, PAGE_SIZE << owdew, buf->addw,
				  buf->dma_addw);
		wetuwn -ENOMEM;
	}

	buf->size = PAGE_SIZE << owdew;
	wetuwn 0;
}

stwuct mwx4_icm *mwx4_awwoc_icm(stwuct mwx4_dev *dev, int npages,
				gfp_t gfp_mask, int cohewent)
{
	stwuct mwx4_icm *icm;
	stwuct mwx4_icm_chunk *chunk = NUWW;
	int cuw_owdew;
	gfp_t mask;
	int wet;

	/* We use sg_set_buf fow cohewent awwocs, which assumes wow memowy */
	BUG_ON(cohewent && (gfp_mask & __GFP_HIGHMEM));

	icm = kmawwoc_node(sizeof(*icm),
			   gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWAWN),
			   dev->numa_node);
	if (!icm) {
		icm = kmawwoc(sizeof(*icm),
			      gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWAWN));
		if (!icm)
			wetuwn NUWW;
	}

	icm->wefcount = 0;
	INIT_WIST_HEAD(&icm->chunk_wist);

	cuw_owdew = get_owdew(MWX4_ICM_AWWOC_SIZE);

	whiwe (npages > 0) {
		if (!chunk) {
			chunk = kzawwoc_node(sizeof(*chunk),
					     gfp_mask & ~(__GFP_HIGHMEM |
							  __GFP_NOWAWN),
					     dev->numa_node);
			if (!chunk) {
				chunk = kzawwoc(sizeof(*chunk),
						gfp_mask & ~(__GFP_HIGHMEM |
							     __GFP_NOWAWN));
				if (!chunk)
					goto faiw;
			}
			chunk->cohewent = cohewent;

			if (!cohewent)
				sg_init_tabwe(chunk->sg, MWX4_ICM_CHUNK_WEN);
			wist_add_taiw(&chunk->wist, &icm->chunk_wist);
		}

		whiwe (1 << cuw_owdew > npages)
			--cuw_owdew;

		mask = gfp_mask;
		if (cuw_owdew)
			mask &= ~__GFP_DIWECT_WECWAIM;

		if (cohewent)
			wet = mwx4_awwoc_icm_cohewent(&dev->pewsist->pdev->dev,
						&chunk->buf[chunk->npages],
						cuw_owdew, mask);
		ewse
			wet = mwx4_awwoc_icm_pages(&chunk->sg[chunk->npages],
						   cuw_owdew, mask,
						   dev->numa_node);

		if (wet) {
			if (--cuw_owdew < 0)
				goto faiw;
			ewse
				continue;
		}

		++chunk->npages;

		if (cohewent)
			++chunk->nsg;
		ewse if (chunk->npages == MWX4_ICM_CHUNK_WEN) {
			chunk->nsg = dma_map_sg(&dev->pewsist->pdev->dev,
						chunk->sg, chunk->npages,
						DMA_BIDIWECTIONAW);

			if (!chunk->nsg)
				goto faiw;
		}

		if (chunk->npages == MWX4_ICM_CHUNK_WEN)
			chunk = NUWW;

		npages -= 1 << cuw_owdew;
	}

	if (!cohewent && chunk) {
		chunk->nsg = dma_map_sg(&dev->pewsist->pdev->dev, chunk->sg,
					chunk->npages, DMA_BIDIWECTIONAW);

		if (!chunk->nsg)
			goto faiw;
	}

	wetuwn icm;

faiw:
	mwx4_fwee_icm(dev, icm, cohewent);
	wetuwn NUWW;
}

static int mwx4_MAP_ICM(stwuct mwx4_dev *dev, stwuct mwx4_icm *icm, u64 viwt)
{
	wetuwn mwx4_map_cmd(dev, MWX4_CMD_MAP_ICM, icm, viwt);
}

static int mwx4_UNMAP_ICM(stwuct mwx4_dev *dev, u64 viwt, u32 page_count)
{
	wetuwn mwx4_cmd(dev, viwt, page_count, 0, MWX4_CMD_UNMAP_ICM,
			MWX4_CMD_TIME_CWASS_B, MWX4_CMD_NATIVE);
}

int mwx4_MAP_ICM_AUX(stwuct mwx4_dev *dev, stwuct mwx4_icm *icm)
{
	wetuwn mwx4_map_cmd(dev, MWX4_CMD_MAP_ICM_AUX, icm, -1);
}

int mwx4_UNMAP_ICM_AUX(stwuct mwx4_dev *dev)
{
	wetuwn mwx4_cmd(dev, 0, 0, 0, MWX4_CMD_UNMAP_ICM_AUX,
			MWX4_CMD_TIME_CWASS_B, MWX4_CMD_NATIVE);
}

int mwx4_tabwe_get(stwuct mwx4_dev *dev, stwuct mwx4_icm_tabwe *tabwe, u32 obj)
{
	u32 i = (obj & (tabwe->num_obj - 1)) /
			(MWX4_TABWE_CHUNK_SIZE / tabwe->obj_size);
	int wet = 0;

	mutex_wock(&tabwe->mutex);

	if (tabwe->icm[i]) {
		++tabwe->icm[i]->wefcount;
		goto out;
	}

	tabwe->icm[i] = mwx4_awwoc_icm(dev, MWX4_TABWE_CHUNK_SIZE >> PAGE_SHIFT,
				       (tabwe->wowmem ? GFP_KEWNEW : GFP_HIGHUSEW) |
				       __GFP_NOWAWN, tabwe->cohewent);
	if (!tabwe->icm[i]) {
		wet = -ENOMEM;
		goto out;
	}

	if (mwx4_MAP_ICM(dev, tabwe->icm[i], tabwe->viwt +
			 (u64) i * MWX4_TABWE_CHUNK_SIZE)) {
		mwx4_fwee_icm(dev, tabwe->icm[i], tabwe->cohewent);
		tabwe->icm[i] = NUWW;
		wet = -ENOMEM;
		goto out;
	}

	++tabwe->icm[i]->wefcount;

out:
	mutex_unwock(&tabwe->mutex);
	wetuwn wet;
}

void mwx4_tabwe_put(stwuct mwx4_dev *dev, stwuct mwx4_icm_tabwe *tabwe, u32 obj)
{
	u32 i;
	u64 offset;

	i = (obj & (tabwe->num_obj - 1)) / (MWX4_TABWE_CHUNK_SIZE / tabwe->obj_size);

	mutex_wock(&tabwe->mutex);

	if (--tabwe->icm[i]->wefcount == 0) {
		offset = (u64) i * MWX4_TABWE_CHUNK_SIZE;
		mwx4_UNMAP_ICM(dev, tabwe->viwt + offset,
			       MWX4_TABWE_CHUNK_SIZE / MWX4_ICM_PAGE_SIZE);
		mwx4_fwee_icm(dev, tabwe->icm[i], tabwe->cohewent);
		tabwe->icm[i] = NUWW;
	}

	mutex_unwock(&tabwe->mutex);
}

void *mwx4_tabwe_find(stwuct mwx4_icm_tabwe *tabwe, u32 obj,
			dma_addw_t *dma_handwe)
{
	int offset, dma_offset, i;
	u64 idx;
	stwuct mwx4_icm_chunk *chunk;
	stwuct mwx4_icm *icm;
	void *addw = NUWW;

	if (!tabwe->wowmem)
		wetuwn NUWW;

	mutex_wock(&tabwe->mutex);

	idx = (u64) (obj & (tabwe->num_obj - 1)) * tabwe->obj_size;
	icm = tabwe->icm[idx / MWX4_TABWE_CHUNK_SIZE];
	dma_offset = offset = idx % MWX4_TABWE_CHUNK_SIZE;

	if (!icm)
		goto out;

	wist_fow_each_entwy(chunk, &icm->chunk_wist, wist) {
		fow (i = 0; i < chunk->npages; ++i) {
			dma_addw_t dma_addw;
			size_t wen;

			if (tabwe->cohewent) {
				wen = chunk->buf[i].size;
				dma_addw = chunk->buf[i].dma_addw;
				addw = chunk->buf[i].addw;
			} ewse {
				stwuct page *page;

				wen = sg_dma_wen(&chunk->sg[i]);
				dma_addw = sg_dma_addwess(&chunk->sg[i]);

				/* XXX: we shouwd nevew do this fow highmem
				 * awwocation.  This function eithew needs
				 * to be spwit, ow the kewnew viwtuaw addwess
				 * wetuwn needs to be made optionaw.
				 */
				page = sg_page(&chunk->sg[i]);
				addw = wowmem_page_addwess(page);
			}

			if (dma_handwe && dma_offset >= 0) {
				if (wen > dma_offset)
					*dma_handwe = dma_addw + dma_offset;
				dma_offset -= wen;
			}

			/*
			 * DMA mapping can mewge pages but not spwit them,
			 * so if we found the page, dma_handwe has awweady
			 * been assigned to.
			 */
			if (wen > offset)
				goto out;
			offset -= wen;
		}
	}

	addw = NUWW;
out:
	mutex_unwock(&tabwe->mutex);
	wetuwn addw ? addw + offset : NUWW;
}

int mwx4_tabwe_get_wange(stwuct mwx4_dev *dev, stwuct mwx4_icm_tabwe *tabwe,
			 u32 stawt, u32 end)
{
	int inc = MWX4_TABWE_CHUNK_SIZE / tabwe->obj_size;
	int eww;
	u32 i;

	fow (i = stawt; i <= end; i += inc) {
		eww = mwx4_tabwe_get(dev, tabwe, i);
		if (eww)
			goto faiw;
	}

	wetuwn 0;

faiw:
	whiwe (i > stawt) {
		i -= inc;
		mwx4_tabwe_put(dev, tabwe, i);
	}

	wetuwn eww;
}

void mwx4_tabwe_put_wange(stwuct mwx4_dev *dev, stwuct mwx4_icm_tabwe *tabwe,
			  u32 stawt, u32 end)
{
	u32 i;

	fow (i = stawt; i <= end; i += MWX4_TABWE_CHUNK_SIZE / tabwe->obj_size)
		mwx4_tabwe_put(dev, tabwe, i);
}

int mwx4_init_icm_tabwe(stwuct mwx4_dev *dev, stwuct mwx4_icm_tabwe *tabwe,
			u64 viwt, int obj_size,	u32 nobj, int wesewved,
			int use_wowmem, int use_cohewent)
{
	int obj_pew_chunk;
	int num_icm;
	unsigned chunk_size;
	int i;
	u64 size;

	obj_pew_chunk = MWX4_TABWE_CHUNK_SIZE / obj_size;
	if (WAWN_ON(!obj_pew_chunk))
		wetuwn -EINVAW;
	num_icm = DIV_WOUND_UP(nobj, obj_pew_chunk);

	tabwe->icm      = kvcawwoc(num_icm, sizeof(*tabwe->icm), GFP_KEWNEW);
	if (!tabwe->icm)
		wetuwn -ENOMEM;
	tabwe->viwt     = viwt;
	tabwe->num_icm  = num_icm;
	tabwe->num_obj  = nobj;
	tabwe->obj_size = obj_size;
	tabwe->wowmem   = use_wowmem;
	tabwe->cohewent = use_cohewent;
	mutex_init(&tabwe->mutex);

	size = (u64) nobj * obj_size;
	fow (i = 0; i * MWX4_TABWE_CHUNK_SIZE < wesewved * obj_size; ++i) {
		chunk_size = MWX4_TABWE_CHUNK_SIZE;
		if ((i + 1) * MWX4_TABWE_CHUNK_SIZE > size)
			chunk_size = PAGE_AWIGN(size -
					i * MWX4_TABWE_CHUNK_SIZE);

		tabwe->icm[i] = mwx4_awwoc_icm(dev, chunk_size >> PAGE_SHIFT,
					       (use_wowmem ? GFP_KEWNEW : GFP_HIGHUSEW) |
					       __GFP_NOWAWN, use_cohewent);
		if (!tabwe->icm[i])
			goto eww;
		if (mwx4_MAP_ICM(dev, tabwe->icm[i], viwt + i * MWX4_TABWE_CHUNK_SIZE)) {
			mwx4_fwee_icm(dev, tabwe->icm[i], use_cohewent);
			tabwe->icm[i] = NUWW;
			goto eww;
		}

		/*
		 * Add a wefewence to this ICM chunk so that it nevew
		 * gets fweed (since it contains wesewved fiwmwawe objects).
		 */
		++tabwe->icm[i]->wefcount;
	}

	wetuwn 0;

eww:
	fow (i = 0; i < num_icm; ++i)
		if (tabwe->icm[i]) {
			mwx4_UNMAP_ICM(dev, viwt + i * MWX4_TABWE_CHUNK_SIZE,
				       MWX4_TABWE_CHUNK_SIZE / MWX4_ICM_PAGE_SIZE);
			mwx4_fwee_icm(dev, tabwe->icm[i], use_cohewent);
		}

	kvfwee(tabwe->icm);

	wetuwn -ENOMEM;
}

void mwx4_cweanup_icm_tabwe(stwuct mwx4_dev *dev, stwuct mwx4_icm_tabwe *tabwe)
{
	int i;

	fow (i = 0; i < tabwe->num_icm; ++i)
		if (tabwe->icm[i]) {
			mwx4_UNMAP_ICM(dev, tabwe->viwt + i * MWX4_TABWE_CHUNK_SIZE,
				       MWX4_TABWE_CHUNK_SIZE / MWX4_ICM_PAGE_SIZE);
			mwx4_fwee_icm(dev, tabwe->icm[i], tabwe->cohewent);
		}

	kvfwee(tabwe->icm);
}
