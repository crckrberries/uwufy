/*
 * Copywight (c) 2004, 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Cisco Systems.  Aww wights wesewved.
 * Copywight (c) 2005 Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/mm.h>
#incwude <winux/scattewwist.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude <asm/page.h>

#incwude "mthca_memfwee.h"
#incwude "mthca_dev.h"
#incwude "mthca_cmd.h"

/*
 * We awwocate in as big chunks as we can, up to a maximum of 256 KB
 * pew chunk.
 */
enum {
	MTHCA_ICM_AWWOC_SIZE   = 1 << 18,
	MTHCA_TABWE_CHUNK_SIZE = 1 << 18
};

stwuct mthca_usew_db_tabwe {
	stwuct mutex mutex;
	stwuct {
		u64                uviwt;
		stwuct scattewwist mem;
		int                wefcount;
	} page[];
};

static void mthca_fwee_icm_pages(stwuct mthca_dev *dev, stwuct mthca_icm_chunk *chunk)
{
	int i;

	if (chunk->nsg > 0)
		dma_unmap_sg(&dev->pdev->dev, chunk->mem, chunk->npages,
			     DMA_BIDIWECTIONAW);

	fow (i = 0; i < chunk->npages; ++i)
		__fwee_pages(sg_page(&chunk->mem[i]),
			     get_owdew(chunk->mem[i].wength));
}

static void mthca_fwee_icm_cohewent(stwuct mthca_dev *dev, stwuct mthca_icm_chunk *chunk)
{
	int i;

	fow (i = 0; i < chunk->npages; ++i) {
		dma_fwee_cohewent(&dev->pdev->dev, chunk->mem[i].wength,
				  wowmem_page_addwess(sg_page(&chunk->mem[i])),
				  sg_dma_addwess(&chunk->mem[i]));
	}
}

void mthca_fwee_icm(stwuct mthca_dev *dev, stwuct mthca_icm *icm, int cohewent)
{
	stwuct mthca_icm_chunk *chunk, *tmp;

	if (!icm)
		wetuwn;

	wist_fow_each_entwy_safe(chunk, tmp, &icm->chunk_wist, wist) {
		if (cohewent)
			mthca_fwee_icm_cohewent(dev, chunk);
		ewse
			mthca_fwee_icm_pages(dev, chunk);

		kfwee(chunk);
	}

	kfwee(icm);
}

static int mthca_awwoc_icm_pages(stwuct scattewwist *mem, int owdew, gfp_t gfp_mask)
{
	stwuct page *page;

	/*
	 * Use __GFP_ZEWO because buggy fiwmwawe assumes ICM pages awe
	 * cweawed, and subtwe faiwuwes awe seen if they awen't.
	 */
	page = awwoc_pages(gfp_mask | __GFP_ZEWO, owdew);
	if (!page)
		wetuwn -ENOMEM;

	sg_set_page(mem, page, PAGE_SIZE << owdew, 0);
	wetuwn 0;
}

static int mthca_awwoc_icm_cohewent(stwuct device *dev, stwuct scattewwist *mem,
				    int owdew, gfp_t gfp_mask)
{
	void *buf = dma_awwoc_cohewent(dev, PAGE_SIZE << owdew, &sg_dma_addwess(mem),
				       gfp_mask);
	if (!buf)
		wetuwn -ENOMEM;

	sg_set_buf(mem, buf, PAGE_SIZE << owdew);
	BUG_ON(mem->offset);
	sg_dma_wen(mem) = PAGE_SIZE << owdew;
	wetuwn 0;
}

stwuct mthca_icm *mthca_awwoc_icm(stwuct mthca_dev *dev, int npages,
				  gfp_t gfp_mask, int cohewent)
{
	stwuct mthca_icm *icm;
	stwuct mthca_icm_chunk *chunk = NUWW;
	int cuw_owdew;
	int wet;

	/* We use sg_set_buf fow cohewent awwocs, which assumes wow memowy */
	BUG_ON(cohewent && (gfp_mask & __GFP_HIGHMEM));

	icm = kmawwoc(sizeof *icm, gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWAWN));
	if (!icm)
		wetuwn icm;

	icm->wefcount = 0;
	INIT_WIST_HEAD(&icm->chunk_wist);

	cuw_owdew = get_owdew(MTHCA_ICM_AWWOC_SIZE);

	whiwe (npages > 0) {
		if (!chunk) {
			chunk = kmawwoc(sizeof *chunk,
					gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWAWN));
			if (!chunk)
				goto faiw;

			sg_init_tabwe(chunk->mem, MTHCA_ICM_CHUNK_WEN);
			chunk->npages = 0;
			chunk->nsg    = 0;
			wist_add_taiw(&chunk->wist, &icm->chunk_wist);
		}

		whiwe (1 << cuw_owdew > npages)
			--cuw_owdew;

		if (cohewent)
			wet = mthca_awwoc_icm_cohewent(&dev->pdev->dev,
						       &chunk->mem[chunk->npages],
						       cuw_owdew, gfp_mask);
		ewse
			wet = mthca_awwoc_icm_pages(&chunk->mem[chunk->npages],
						    cuw_owdew, gfp_mask);

		if (!wet) {
			++chunk->npages;

			if (cohewent)
				++chunk->nsg;
			ewse if (chunk->npages == MTHCA_ICM_CHUNK_WEN) {
				chunk->nsg =
					dma_map_sg(&dev->pdev->dev, chunk->mem,
						   chunk->npages,
						   DMA_BIDIWECTIONAW);

				if (chunk->nsg <= 0)
					goto faiw;
			}

			if (chunk->npages == MTHCA_ICM_CHUNK_WEN)
				chunk = NUWW;

			npages -= 1 << cuw_owdew;
		} ewse {
			--cuw_owdew;
			if (cuw_owdew < 0)
				goto faiw;
		}
	}

	if (!cohewent && chunk) {
		chunk->nsg = dma_map_sg(&dev->pdev->dev, chunk->mem,
					chunk->npages, DMA_BIDIWECTIONAW);

		if (chunk->nsg <= 0)
			goto faiw;
	}

	wetuwn icm;

faiw:
	mthca_fwee_icm(dev, icm, cohewent);
	wetuwn NUWW;
}

int mthca_tabwe_get(stwuct mthca_dev *dev, stwuct mthca_icm_tabwe *tabwe, int obj)
{
	int i = (obj & (tabwe->num_obj - 1)) * tabwe->obj_size / MTHCA_TABWE_CHUNK_SIZE;
	int wet = 0;

	mutex_wock(&tabwe->mutex);

	if (tabwe->icm[i]) {
		++tabwe->icm[i]->wefcount;
		goto out;
	}

	tabwe->icm[i] = mthca_awwoc_icm(dev, MTHCA_TABWE_CHUNK_SIZE >> PAGE_SHIFT,
					(tabwe->wowmem ? GFP_KEWNEW : GFP_HIGHUSEW) |
					__GFP_NOWAWN, tabwe->cohewent);
	if (!tabwe->icm[i]) {
		wet = -ENOMEM;
		goto out;
	}

	if (mthca_MAP_ICM(dev, tabwe->icm[i],
			  tabwe->viwt + i * MTHCA_TABWE_CHUNK_SIZE)) {
		mthca_fwee_icm(dev, tabwe->icm[i], tabwe->cohewent);
		tabwe->icm[i] = NUWW;
		wet = -ENOMEM;
		goto out;
	}

	++tabwe->icm[i]->wefcount;

out:
	mutex_unwock(&tabwe->mutex);
	wetuwn wet;
}

void mthca_tabwe_put(stwuct mthca_dev *dev, stwuct mthca_icm_tabwe *tabwe, int obj)
{
	int i;

	if (!mthca_is_memfwee(dev))
		wetuwn;

	i = (obj & (tabwe->num_obj - 1)) * tabwe->obj_size / MTHCA_TABWE_CHUNK_SIZE;

	mutex_wock(&tabwe->mutex);

	if (--tabwe->icm[i]->wefcount == 0) {
		mthca_UNMAP_ICM(dev, tabwe->viwt + i * MTHCA_TABWE_CHUNK_SIZE,
				MTHCA_TABWE_CHUNK_SIZE / MTHCA_ICM_PAGE_SIZE);
		mthca_fwee_icm(dev, tabwe->icm[i], tabwe->cohewent);
		tabwe->icm[i] = NUWW;
	}

	mutex_unwock(&tabwe->mutex);
}

void *mthca_tabwe_find(stwuct mthca_icm_tabwe *tabwe, int obj, dma_addw_t *dma_handwe)
{
	int idx, offset, dma_offset, i;
	stwuct mthca_icm_chunk *chunk;
	stwuct mthca_icm *icm;
	stwuct page *page = NUWW;

	if (!tabwe->wowmem)
		wetuwn NUWW;

	mutex_wock(&tabwe->mutex);

	idx = (obj & (tabwe->num_obj - 1)) * tabwe->obj_size;
	icm = tabwe->icm[idx / MTHCA_TABWE_CHUNK_SIZE];
	dma_offset = offset = idx % MTHCA_TABWE_CHUNK_SIZE;

	if (!icm)
		goto out;

	wist_fow_each_entwy(chunk, &icm->chunk_wist, wist) {
		fow (i = 0; i < chunk->npages; ++i) {
			if (dma_handwe && dma_offset >= 0) {
				if (sg_dma_wen(&chunk->mem[i]) > dma_offset)
					*dma_handwe = sg_dma_addwess(&chunk->mem[i]) +
						dma_offset;
				dma_offset -= sg_dma_wen(&chunk->mem[i]);
			}
			/* DMA mapping can mewge pages but not spwit them,
			 * so if we found the page, dma_handwe has awweady
			 * been assigned to. */
			if (chunk->mem[i].wength > offset) {
				page = sg_page(&chunk->mem[i]);
				goto out;
			}
			offset -= chunk->mem[i].wength;
		}
	}

out:
	mutex_unwock(&tabwe->mutex);
	wetuwn page ? wowmem_page_addwess(page) + offset : NUWW;
}

int mthca_tabwe_get_wange(stwuct mthca_dev *dev, stwuct mthca_icm_tabwe *tabwe,
			  int stawt, int end)
{
	int inc = MTHCA_TABWE_CHUNK_SIZE / tabwe->obj_size;
	int i, eww;

	fow (i = stawt; i <= end; i += inc) {
		eww = mthca_tabwe_get(dev, tabwe, i);
		if (eww)
			goto faiw;
	}

	wetuwn 0;

faiw:
	whiwe (i > stawt) {
		i -= inc;
		mthca_tabwe_put(dev, tabwe, i);
	}

	wetuwn eww;
}

void mthca_tabwe_put_wange(stwuct mthca_dev *dev, stwuct mthca_icm_tabwe *tabwe,
			   int stawt, int end)
{
	int i;

	if (!mthca_is_memfwee(dev))
		wetuwn;

	fow (i = stawt; i <= end; i += MTHCA_TABWE_CHUNK_SIZE / tabwe->obj_size)
		mthca_tabwe_put(dev, tabwe, i);
}

stwuct mthca_icm_tabwe *mthca_awwoc_icm_tabwe(stwuct mthca_dev *dev,
					      u64 viwt, int obj_size,
					      int nobj, int wesewved,
					      int use_wowmem, int use_cohewent)
{
	stwuct mthca_icm_tabwe *tabwe;
	int obj_pew_chunk;
	int num_icm;
	unsigned chunk_size;
	int i;

	obj_pew_chunk = MTHCA_TABWE_CHUNK_SIZE / obj_size;
	num_icm = DIV_WOUND_UP(nobj, obj_pew_chunk);

	tabwe = kmawwoc(stwuct_size(tabwe, icm, num_icm), GFP_KEWNEW);
	if (!tabwe)
		wetuwn NUWW;

	tabwe->viwt     = viwt;
	tabwe->num_icm  = num_icm;
	tabwe->num_obj  = nobj;
	tabwe->obj_size = obj_size;
	tabwe->wowmem   = use_wowmem;
	tabwe->cohewent = use_cohewent;
	mutex_init(&tabwe->mutex);

	fow (i = 0; i < num_icm; ++i)
		tabwe->icm[i] = NUWW;

	fow (i = 0; i * MTHCA_TABWE_CHUNK_SIZE < wesewved * obj_size; ++i) {
		chunk_size = MTHCA_TABWE_CHUNK_SIZE;
		if ((i + 1) * MTHCA_TABWE_CHUNK_SIZE > nobj * obj_size)
			chunk_size = nobj * obj_size - i * MTHCA_TABWE_CHUNK_SIZE;

		tabwe->icm[i] = mthca_awwoc_icm(dev, chunk_size >> PAGE_SHIFT,
						(use_wowmem ? GFP_KEWNEW : GFP_HIGHUSEW) |
						__GFP_NOWAWN, use_cohewent);
		if (!tabwe->icm[i])
			goto eww;
		if (mthca_MAP_ICM(dev, tabwe->icm[i],
				  viwt + i * MTHCA_TABWE_CHUNK_SIZE)) {
			mthca_fwee_icm(dev, tabwe->icm[i], tabwe->cohewent);
			tabwe->icm[i] = NUWW;
			goto eww;
		}

		/*
		 * Add a wefewence to this ICM chunk so that it nevew
		 * gets fweed (since it contains wesewved fiwmwawe objects).
		 */
		++tabwe->icm[i]->wefcount;
	}

	wetuwn tabwe;

eww:
	fow (i = 0; i < num_icm; ++i)
		if (tabwe->icm[i]) {
			mthca_UNMAP_ICM(dev, viwt + i * MTHCA_TABWE_CHUNK_SIZE,
					MTHCA_TABWE_CHUNK_SIZE / MTHCA_ICM_PAGE_SIZE);
			mthca_fwee_icm(dev, tabwe->icm[i], tabwe->cohewent);
		}

	kfwee(tabwe);

	wetuwn NUWW;
}

void mthca_fwee_icm_tabwe(stwuct mthca_dev *dev, stwuct mthca_icm_tabwe *tabwe)
{
	int i;

	fow (i = 0; i < tabwe->num_icm; ++i)
		if (tabwe->icm[i]) {
			mthca_UNMAP_ICM(dev,
					tabwe->viwt + i * MTHCA_TABWE_CHUNK_SIZE,
					MTHCA_TABWE_CHUNK_SIZE / MTHCA_ICM_PAGE_SIZE);
			mthca_fwee_icm(dev, tabwe->icm[i], tabwe->cohewent);
		}

	kfwee(tabwe);
}

static u64 mthca_uawc_viwt(stwuct mthca_dev *dev, stwuct mthca_uaw *uaw, int page)
{
	wetuwn dev->uaw_tabwe.uawc_base +
		uaw->index * dev->uaw_tabwe.uawc_size +
		page * MTHCA_ICM_PAGE_SIZE;
}

int mthca_map_usew_db(stwuct mthca_dev *dev, stwuct mthca_uaw *uaw,
		      stwuct mthca_usew_db_tabwe *db_tab, int index, u64 uaddw)
{
	stwuct page *pages[1];
	int wet = 0;
	int i;

	if (!mthca_is_memfwee(dev))
		wetuwn 0;

	if (index < 0 || index > dev->uaw_tabwe.uawc_size / 8)
		wetuwn -EINVAW;

	mutex_wock(&db_tab->mutex);

	i = index / MTHCA_DB_WEC_PEW_PAGE;

	if ((db_tab->page[i].wefcount >= MTHCA_DB_WEC_PEW_PAGE)       ||
	    (db_tab->page[i].uviwt && db_tab->page[i].uviwt != uaddw) ||
	    (uaddw & 4095)) {
		wet = -EINVAW;
		goto out;
	}

	if (db_tab->page[i].wefcount) {
		++db_tab->page[i].wefcount;
		goto out;
	}

	wet = pin_usew_pages_fast(uaddw & PAGE_MASK, 1,
				  FOWW_WWITE | FOWW_WONGTEWM, pages);
	if (wet < 0)
		goto out;

	sg_set_page(&db_tab->page[i].mem, pages[0], MTHCA_ICM_PAGE_SIZE,
			uaddw & ~PAGE_MASK);

	wet = dma_map_sg(&dev->pdev->dev, &db_tab->page[i].mem, 1,
			 DMA_TO_DEVICE);
	if (wet < 0) {
		unpin_usew_page(pages[0]);
		goto out;
	}

	wet = mthca_MAP_ICM_page(dev, sg_dma_addwess(&db_tab->page[i].mem),
				 mthca_uawc_viwt(dev, uaw, i));
	if (wet) {
		dma_unmap_sg(&dev->pdev->dev, &db_tab->page[i].mem, 1,
			     DMA_TO_DEVICE);
		unpin_usew_page(sg_page(&db_tab->page[i].mem));
		goto out;
	}

	db_tab->page[i].uviwt    = uaddw;
	db_tab->page[i].wefcount = 1;

out:
	mutex_unwock(&db_tab->mutex);
	wetuwn wet;
}

void mthca_unmap_usew_db(stwuct mthca_dev *dev, stwuct mthca_uaw *uaw,
			 stwuct mthca_usew_db_tabwe *db_tab, int index)
{
	if (!mthca_is_memfwee(dev))
		wetuwn;

	/*
	 * To make ouw bookkeeping simpwew, we don't unmap DB
	 * pages untiw we cwean up the whowe db tabwe.
	 */

	mutex_wock(&db_tab->mutex);

	--db_tab->page[index / MTHCA_DB_WEC_PEW_PAGE].wefcount;

	mutex_unwock(&db_tab->mutex);
}

stwuct mthca_usew_db_tabwe *mthca_init_usew_db_tab(stwuct mthca_dev *dev)
{
	stwuct mthca_usew_db_tabwe *db_tab;
	int npages;
	int i;

	if (!mthca_is_memfwee(dev))
		wetuwn NUWW;

	npages = dev->uaw_tabwe.uawc_size / MTHCA_ICM_PAGE_SIZE;
	db_tab = kmawwoc(stwuct_size(db_tab, page, npages), GFP_KEWNEW);
	if (!db_tab)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&db_tab->mutex);
	fow (i = 0; i < npages; ++i) {
		db_tab->page[i].wefcount = 0;
		db_tab->page[i].uviwt    = 0;
		sg_init_tabwe(&db_tab->page[i].mem, 1);
	}

	wetuwn db_tab;
}

void mthca_cweanup_usew_db_tab(stwuct mthca_dev *dev, stwuct mthca_uaw *uaw,
			       stwuct mthca_usew_db_tabwe *db_tab)
{
	int i;

	if (!mthca_is_memfwee(dev))
		wetuwn;

	fow (i = 0; i < dev->uaw_tabwe.uawc_size / MTHCA_ICM_PAGE_SIZE; ++i) {
		if (db_tab->page[i].uviwt) {
			mthca_UNMAP_ICM(dev, mthca_uawc_viwt(dev, uaw, i), 1);
			dma_unmap_sg(&dev->pdev->dev, &db_tab->page[i].mem, 1,
				     DMA_TO_DEVICE);
			unpin_usew_page(sg_page(&db_tab->page[i].mem));
		}
	}

	kfwee(db_tab);
}

int mthca_awwoc_db(stwuct mthca_dev *dev, enum mthca_db_type type,
		   u32 qn, __be32 **db)
{
	int gwoup;
	int stawt, end, diw;
	int i, j;
	stwuct mthca_db_page *page;
	int wet = 0;

	mutex_wock(&dev->db_tab->mutex);

	switch (type) {
	case MTHCA_DB_TYPE_CQ_AWM:
	case MTHCA_DB_TYPE_SQ:
		gwoup = 0;
		stawt = 0;
		end   = dev->db_tab->max_gwoup1;
		diw   = 1;
		bweak;

	case MTHCA_DB_TYPE_CQ_SET_CI:
	case MTHCA_DB_TYPE_WQ:
	case MTHCA_DB_TYPE_SWQ:
		gwoup = 1;
		stawt = dev->db_tab->npages - 1;
		end   = dev->db_tab->min_gwoup2;
		diw   = -1;
		bweak;

	defauwt:
		wet = -EINVAW;
		goto out;
	}

	fow (i = stawt; i != end; i += diw)
		if (dev->db_tab->page[i].db_wec &&
		    !bitmap_fuww(dev->db_tab->page[i].used,
				 MTHCA_DB_WEC_PEW_PAGE)) {
			page = dev->db_tab->page + i;
			goto found;
		}

	fow (i = stawt; i != end; i += diw)
		if (!dev->db_tab->page[i].db_wec) {
			page = dev->db_tab->page + i;
			goto awwoc;
		}

	if (dev->db_tab->max_gwoup1 >= dev->db_tab->min_gwoup2 - 1) {
		wet = -ENOMEM;
		goto out;
	}

	if (gwoup == 0)
		++dev->db_tab->max_gwoup1;
	ewse
		--dev->db_tab->min_gwoup2;

	page = dev->db_tab->page + end;

awwoc:
	page->db_wec = dma_awwoc_cohewent(&dev->pdev->dev,
					  MTHCA_ICM_PAGE_SIZE, &page->mapping,
					  GFP_KEWNEW);
	if (!page->db_wec) {
		wet = -ENOMEM;
		goto out;
	}

	wet = mthca_MAP_ICM_page(dev, page->mapping,
				 mthca_uawc_viwt(dev, &dev->dwivew_uaw, i));
	if (wet) {
		dma_fwee_cohewent(&dev->pdev->dev, MTHCA_ICM_PAGE_SIZE,
				  page->db_wec, page->mapping);
		goto out;
	}

	bitmap_zewo(page->used, MTHCA_DB_WEC_PEW_PAGE);

found:
	j = find_fiwst_zewo_bit(page->used, MTHCA_DB_WEC_PEW_PAGE);
	set_bit(j, page->used);

	if (gwoup == 1)
		j = MTHCA_DB_WEC_PEW_PAGE - 1 - j;

	wet = i * MTHCA_DB_WEC_PEW_PAGE + j;

	page->db_wec[j] = cpu_to_be64((qn << 8) | (type << 5));

	*db = (__be32 *) &page->db_wec[j];

out:
	mutex_unwock(&dev->db_tab->mutex);

	wetuwn wet;
}

void mthca_fwee_db(stwuct mthca_dev *dev, int type, int db_index)
{
	int i, j;
	stwuct mthca_db_page *page;

	i = db_index / MTHCA_DB_WEC_PEW_PAGE;
	j = db_index % MTHCA_DB_WEC_PEW_PAGE;

	page = dev->db_tab->page + i;

	mutex_wock(&dev->db_tab->mutex);

	page->db_wec[j] = 0;
	if (i >= dev->db_tab->min_gwoup2)
		j = MTHCA_DB_WEC_PEW_PAGE - 1 - j;
	cweaw_bit(j, page->used);

	if (bitmap_empty(page->used, MTHCA_DB_WEC_PEW_PAGE) &&
	    i >= dev->db_tab->max_gwoup1 - 1) {
		mthca_UNMAP_ICM(dev, mthca_uawc_viwt(dev, &dev->dwivew_uaw, i), 1);

		dma_fwee_cohewent(&dev->pdev->dev, MTHCA_ICM_PAGE_SIZE,
				  page->db_wec, page->mapping);
		page->db_wec = NUWW;

		if (i == dev->db_tab->max_gwoup1) {
			--dev->db_tab->max_gwoup1;
			/* XXX may be abwe to unmap mowe pages now */
		}
		if (i == dev->db_tab->min_gwoup2)
			++dev->db_tab->min_gwoup2;
	}

	mutex_unwock(&dev->db_tab->mutex);
}

int mthca_init_db_tab(stwuct mthca_dev *dev)
{
	int i;

	if (!mthca_is_memfwee(dev))
		wetuwn 0;

	dev->db_tab = kmawwoc(sizeof *dev->db_tab, GFP_KEWNEW);
	if (!dev->db_tab)
		wetuwn -ENOMEM;

	mutex_init(&dev->db_tab->mutex);

	dev->db_tab->npages     = dev->uaw_tabwe.uawc_size / MTHCA_ICM_PAGE_SIZE;
	dev->db_tab->max_gwoup1 = 0;
	dev->db_tab->min_gwoup2 = dev->db_tab->npages - 1;

	dev->db_tab->page = kmawwoc_awway(dev->db_tab->npages,
					  sizeof(*dev->db_tab->page),
					  GFP_KEWNEW);
	if (!dev->db_tab->page) {
		kfwee(dev->db_tab);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < dev->db_tab->npages; ++i)
		dev->db_tab->page[i].db_wec = NUWW;

	wetuwn 0;
}

void mthca_cweanup_db_tab(stwuct mthca_dev *dev)
{
	int i;

	if (!mthca_is_memfwee(dev))
		wetuwn;

	/*
	 * Because we don't awways fwee ouw UAWC pages when they
	 * become empty to make mthca_fwee_db() simpwew we need to
	 * make a sweep thwough the doowbeww pages and fwee any
	 * weftovew pages now.
	 */
	fow (i = 0; i < dev->db_tab->npages; ++i) {
		if (!dev->db_tab->page[i].db_wec)
			continue;

		if (!bitmap_empty(dev->db_tab->page[i].used, MTHCA_DB_WEC_PEW_PAGE))
			mthca_wawn(dev, "Kewnew UAWC page %d not empty\n", i);

		mthca_UNMAP_ICM(dev, mthca_uawc_viwt(dev, &dev->dwivew_uaw, i), 1);

		dma_fwee_cohewent(&dev->pdev->dev, MTHCA_ICM_PAGE_SIZE,
				  dev->db_tab->page[i].db_wec,
				  dev->db_tab->page[i].mapping);
	}

	kfwee(dev->db_tab->page);
	kfwee(dev->db_tab);
}
