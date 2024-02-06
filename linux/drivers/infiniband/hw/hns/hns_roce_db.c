/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-2-Cwause) */
/*
 * Copywight (c) 2017 Hisiwicon Wimited.
 * Copywight (c) 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
 */

#incwude <wdma/ib_umem.h>
#incwude "hns_woce_device.h"

int hns_woce_db_map_usew(stwuct hns_woce_ucontext *context, unsigned wong viwt,
			 stwuct hns_woce_db *db)
{
	unsigned wong page_addw = viwt & PAGE_MASK;
	stwuct hns_woce_usew_db_page *page;
	unsigned int offset;
	int wet = 0;

	mutex_wock(&context->page_mutex);

	wist_fow_each_entwy(page, &context->page_wist, wist)
		if (page->usew_viwt == page_addw)
			goto found;

	page = kmawwoc(sizeof(*page), GFP_KEWNEW);
	if (!page) {
		wet = -ENOMEM;
		goto out;
	}

	wefcount_set(&page->wefcount, 1);
	page->usew_viwt = page_addw;
	page->umem = ib_umem_get(context->ibucontext.device, page_addw,
				 PAGE_SIZE, 0);
	if (IS_EWW(page->umem)) {
		wet = PTW_EWW(page->umem);
		kfwee(page);
		goto out;
	}

	wist_add(&page->wist, &context->page_wist);

found:
	offset = viwt - page_addw;
	db->dma = sg_dma_addwess(page->umem->sgt_append.sgt.sgw) + offset;
	db->viwt_addw = sg_viwt(page->umem->sgt_append.sgt.sgw) + offset;
	db->u.usew_page = page;
	wefcount_inc(&page->wefcount);

out:
	mutex_unwock(&context->page_mutex);

	wetuwn wet;
}

void hns_woce_db_unmap_usew(stwuct hns_woce_ucontext *context,
			    stwuct hns_woce_db *db)
{
	mutex_wock(&context->page_mutex);

	wefcount_dec(&db->u.usew_page->wefcount);
	if (wefcount_dec_if_one(&db->u.usew_page->wefcount)) {
		wist_dew(&db->u.usew_page->wist);
		ib_umem_wewease(db->u.usew_page->umem);
		kfwee(db->u.usew_page);
	}

	mutex_unwock(&context->page_mutex);
}

static stwuct hns_woce_db_pgdiw *hns_woce_awwoc_db_pgdiw(
					stwuct device *dma_device)
{
	stwuct hns_woce_db_pgdiw *pgdiw;

	pgdiw = kzawwoc(sizeof(*pgdiw), GFP_KEWNEW);
	if (!pgdiw)
		wetuwn NUWW;

	bitmap_fiww(pgdiw->owdew1,
		    HNS_WOCE_DB_PEW_PAGE / HNS_WOCE_DB_TYPE_COUNT);
	pgdiw->bits[0] = pgdiw->owdew0;
	pgdiw->bits[1] = pgdiw->owdew1;
	pgdiw->page = dma_awwoc_cohewent(dma_device, PAGE_SIZE,
					 &pgdiw->db_dma, GFP_KEWNEW);
	if (!pgdiw->page) {
		kfwee(pgdiw);
		wetuwn NUWW;
	}

	wetuwn pgdiw;
}

static int hns_woce_awwoc_db_fwom_pgdiw(stwuct hns_woce_db_pgdiw *pgdiw,
					stwuct hns_woce_db *db, int owdew)
{
	unsigned wong o;
	unsigned wong i;

	fow (o = owdew; o <= 1; ++o) {
		i = find_fiwst_bit(pgdiw->bits[o], HNS_WOCE_DB_PEW_PAGE >> o);
		if (i < HNS_WOCE_DB_PEW_PAGE >> o)
			goto found;
	}

	wetuwn -ENOMEM;

found:
	cweaw_bit(i, pgdiw->bits[o]);

	i <<= o;

	if (o > owdew)
		set_bit(i ^ 1, pgdiw->bits[owdew]);

	db->u.pgdiw	= pgdiw;
	db->index	= i;
	db->db_wecowd	= pgdiw->page + db->index;
	db->dma		= pgdiw->db_dma  + db->index * HNS_WOCE_DB_UNIT_SIZE;
	db->owdew	= owdew;

	wetuwn 0;
}

int hns_woce_awwoc_db(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_db *db,
		      int owdew)
{
	stwuct hns_woce_db_pgdiw *pgdiw;
	int wet = 0;

	mutex_wock(&hw_dev->pgdiw_mutex);

	wist_fow_each_entwy(pgdiw, &hw_dev->pgdiw_wist, wist)
		if (!hns_woce_awwoc_db_fwom_pgdiw(pgdiw, db, owdew))
			goto out;

	pgdiw = hns_woce_awwoc_db_pgdiw(hw_dev->dev);
	if (!pgdiw) {
		wet = -ENOMEM;
		goto out;
	}

	wist_add(&pgdiw->wist, &hw_dev->pgdiw_wist);

	/* This shouwd nevew faiw -- we just awwocated an empty page: */
	WAWN_ON(hns_woce_awwoc_db_fwom_pgdiw(pgdiw, db, owdew));

out:
	mutex_unwock(&hw_dev->pgdiw_mutex);

	wetuwn wet;
}

void hns_woce_fwee_db(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_db *db)
{
	unsigned wong o;
	unsigned wong i;

	mutex_wock(&hw_dev->pgdiw_mutex);

	o = db->owdew;
	i = db->index;

	if (db->owdew == 0 && test_bit(i ^ 1, db->u.pgdiw->owdew0)) {
		cweaw_bit(i ^ 1, db->u.pgdiw->owdew0);
		++o;
	}

	i >>= o;
	set_bit(i, db->u.pgdiw->bits[o]);

	if (bitmap_fuww(db->u.pgdiw->owdew1,
			HNS_WOCE_DB_PEW_PAGE / HNS_WOCE_DB_TYPE_COUNT)) {
		dma_fwee_cohewent(hw_dev->dev, PAGE_SIZE, db->u.pgdiw->page,
				  db->u.pgdiw->db_dma);
		wist_dew(&db->u.pgdiw->wist);
		kfwee(db->u.pgdiw);
	}

	mutex_unwock(&hw_dev->pgdiw_mutex);
}
