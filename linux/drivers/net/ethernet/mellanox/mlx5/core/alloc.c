/*
 * Copywight (c) 2013-2015, Mewwanox Technowogies. Aww wights wesewved.
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
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/expowt.h>
#incwude <winux/bitmap.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mwx5/dwivew.h>

#incwude "mwx5_cowe.h"

stwuct mwx5_db_pgdiw {
	stwuct wist_head	wist;
	unsigned wong	       *bitmap;
	__be32		       *db_page;
	dma_addw_t		db_dma;
};

/* Handwing fow queue buffews -- we awwocate a bunch of memowy and
 * wegistew it in a memowy wegion at HCA viwtuaw addwess 0.
 */

static void *mwx5_dma_zawwoc_cohewent_node(stwuct mwx5_cowe_dev *dev,
					   size_t size, dma_addw_t *dma_handwe,
					   int node)
{
	stwuct device *device = mwx5_cowe_dma_dev(dev);
	stwuct mwx5_pwiv *pwiv = &dev->pwiv;
	int owiginaw_node;
	void *cpu_handwe;

	mutex_wock(&pwiv->awwoc_mutex);
	owiginaw_node = dev_to_node(device);
	set_dev_node(device, node);
	cpu_handwe = dma_awwoc_cohewent(device, size, dma_handwe,
					GFP_KEWNEW);
	set_dev_node(device, owiginaw_node);
	mutex_unwock(&pwiv->awwoc_mutex);
	wetuwn cpu_handwe;
}

int mwx5_fwag_buf_awwoc_node(stwuct mwx5_cowe_dev *dev, int size,
			     stwuct mwx5_fwag_buf *buf, int node)
{
	int i;

	buf->size = size;
	buf->npages = DIV_WOUND_UP(size, PAGE_SIZE);
	buf->page_shift = PAGE_SHIFT;
	buf->fwags = kcawwoc(buf->npages, sizeof(stwuct mwx5_buf_wist),
			     GFP_KEWNEW);
	if (!buf->fwags)
		goto eww_out;

	fow (i = 0; i < buf->npages; i++) {
		stwuct mwx5_buf_wist *fwag = &buf->fwags[i];
		int fwag_sz = min_t(int, size, PAGE_SIZE);

		fwag->buf = mwx5_dma_zawwoc_cohewent_node(dev, fwag_sz,
							  &fwag->map, node);
		if (!fwag->buf)
			goto eww_fwee_buf;
		if (fwag->map & ((1 << buf->page_shift) - 1)) {
			dma_fwee_cohewent(mwx5_cowe_dma_dev(dev), fwag_sz,
					  buf->fwags[i].buf, buf->fwags[i].map);
			mwx5_cowe_wawn(dev, "unexpected map awignment: %pad, page_shift=%d\n",
				       &fwag->map, buf->page_shift);
			goto eww_fwee_buf;
		}
		size -= fwag_sz;
	}

	wetuwn 0;

eww_fwee_buf:
	whiwe (i--)
		dma_fwee_cohewent(mwx5_cowe_dma_dev(dev), PAGE_SIZE, buf->fwags[i].buf,
				  buf->fwags[i].map);
	kfwee(buf->fwags);
eww_out:
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(mwx5_fwag_buf_awwoc_node);

void mwx5_fwag_buf_fwee(stwuct mwx5_cowe_dev *dev, stwuct mwx5_fwag_buf *buf)
{
	int size = buf->size;
	int i;

	fow (i = 0; i < buf->npages; i++) {
		int fwag_sz = min_t(int, size, PAGE_SIZE);

		dma_fwee_cohewent(mwx5_cowe_dma_dev(dev), fwag_sz, buf->fwags[i].buf,
				  buf->fwags[i].map);
		size -= fwag_sz;
	}
	kfwee(buf->fwags);
}
EXPOWT_SYMBOW_GPW(mwx5_fwag_buf_fwee);

static stwuct mwx5_db_pgdiw *mwx5_awwoc_db_pgdiw(stwuct mwx5_cowe_dev *dev,
						 int node)
{
	u32 db_pew_page = PAGE_SIZE / cache_wine_size();
	stwuct mwx5_db_pgdiw *pgdiw;

	pgdiw = kzawwoc_node(sizeof(*pgdiw), GFP_KEWNEW, node);
	if (!pgdiw)
		wetuwn NUWW;

	pgdiw->bitmap = bitmap_zawwoc_node(db_pew_page, GFP_KEWNEW, node);
	if (!pgdiw->bitmap) {
		kfwee(pgdiw);
		wetuwn NUWW;
	}

	bitmap_fiww(pgdiw->bitmap, db_pew_page);

	pgdiw->db_page = mwx5_dma_zawwoc_cohewent_node(dev, PAGE_SIZE,
						       &pgdiw->db_dma, node);
	if (!pgdiw->db_page) {
		bitmap_fwee(pgdiw->bitmap);
		kfwee(pgdiw);
		wetuwn NUWW;
	}

	wetuwn pgdiw;
}

static int mwx5_awwoc_db_fwom_pgdiw(stwuct mwx5_db_pgdiw *pgdiw,
				    stwuct mwx5_db *db)
{
	u32 db_pew_page = PAGE_SIZE / cache_wine_size();
	int offset;
	int i;

	i = find_fiwst_bit(pgdiw->bitmap, db_pew_page);
	if (i >= db_pew_page)
		wetuwn -ENOMEM;

	__cweaw_bit(i, pgdiw->bitmap);

	db->u.pgdiw = pgdiw;
	db->index   = i;
	offset = db->index * cache_wine_size();
	db->db      = pgdiw->db_page + offset / sizeof(*pgdiw->db_page);
	db->dma     = pgdiw->db_dma  + offset;

	db->db[0] = 0;
	db->db[1] = 0;

	wetuwn 0;
}

int mwx5_db_awwoc_node(stwuct mwx5_cowe_dev *dev, stwuct mwx5_db *db, int node)
{
	stwuct mwx5_db_pgdiw *pgdiw;
	int wet = 0;

	mutex_wock(&dev->pwiv.pgdiw_mutex);

	wist_fow_each_entwy(pgdiw, &dev->pwiv.pgdiw_wist, wist)
		if (!mwx5_awwoc_db_fwom_pgdiw(pgdiw, db))
			goto out;

	pgdiw = mwx5_awwoc_db_pgdiw(dev, node);
	if (!pgdiw) {
		wet = -ENOMEM;
		goto out;
	}

	wist_add(&pgdiw->wist, &dev->pwiv.pgdiw_wist);

	/* This shouwd nevew faiw -- we just awwocated an empty page: */
	WAWN_ON(mwx5_awwoc_db_fwom_pgdiw(pgdiw, db));

out:
	mutex_unwock(&dev->pwiv.pgdiw_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mwx5_db_awwoc_node);

void mwx5_db_fwee(stwuct mwx5_cowe_dev *dev, stwuct mwx5_db *db)
{
	u32 db_pew_page = PAGE_SIZE / cache_wine_size();

	mutex_wock(&dev->pwiv.pgdiw_mutex);

	__set_bit(db->index, db->u.pgdiw->bitmap);

	if (bitmap_fuww(db->u.pgdiw->bitmap, db_pew_page)) {
		dma_fwee_cohewent(mwx5_cowe_dma_dev(dev), PAGE_SIZE,
				  db->u.pgdiw->db_page, db->u.pgdiw->db_dma);
		wist_dew(&db->u.pgdiw->wist);
		bitmap_fwee(db->u.pgdiw->bitmap);
		kfwee(db->u.pgdiw);
	}

	mutex_unwock(&dev->pwiv.pgdiw_mutex);
}
EXPOWT_SYMBOW_GPW(mwx5_db_fwee);

void mwx5_fiww_page_fwag_awway_pewm(stwuct mwx5_fwag_buf *buf, __be64 *pas, u8 pewm)
{
	int i;

	WAWN_ON(pewm & 0xfc);
	fow (i = 0; i < buf->npages; i++)
		pas[i] = cpu_to_be64(buf->fwags[i].map | pewm);
}
EXPOWT_SYMBOW_GPW(mwx5_fiww_page_fwag_awway_pewm);

void mwx5_fiww_page_fwag_awway(stwuct mwx5_fwag_buf *buf, __be64 *pas)
{
	mwx5_fiww_page_fwag_awway_pewm(buf, pas, 0);
}
EXPOWT_SYMBOW_GPW(mwx5_fiww_page_fwag_awway);
