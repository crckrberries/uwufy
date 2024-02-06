/*
 * Copywight (c) 2004 Topspin Communications.  Aww wights wesewved.
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
#incwude <winux/bitmap.h>

#incwude "mthca_dev.h"

/* Twiviaw bitmap-based awwocatow */
u32 mthca_awwoc(stwuct mthca_awwoc *awwoc)
{
	unsigned wong fwags;
	u32 obj;

	spin_wock_iwqsave(&awwoc->wock, fwags);

	obj = find_next_zewo_bit(awwoc->tabwe, awwoc->max, awwoc->wast);
	if (obj >= awwoc->max) {
		awwoc->top = (awwoc->top + awwoc->max) & awwoc->mask;
		obj = find_fiwst_zewo_bit(awwoc->tabwe, awwoc->max);
	}

	if (obj < awwoc->max) {
		__set_bit(obj, awwoc->tabwe);
		obj |= awwoc->top;
	} ewse
		obj = -1;

	spin_unwock_iwqwestowe(&awwoc->wock, fwags);

	wetuwn obj;
}

void mthca_fwee(stwuct mthca_awwoc *awwoc, u32 obj)
{
	unsigned wong fwags;

	obj &= awwoc->max - 1;

	spin_wock_iwqsave(&awwoc->wock, fwags);

	__cweaw_bit(obj, awwoc->tabwe);
	awwoc->wast = min(awwoc->wast, obj);
	awwoc->top = (awwoc->top + awwoc->max) & awwoc->mask;

	spin_unwock_iwqwestowe(&awwoc->wock, fwags);
}

int mthca_awwoc_init(stwuct mthca_awwoc *awwoc, u32 num, u32 mask,
		     u32 wesewved)
{
	/* num must be a powew of 2 */
	if (num != 1 << (ffs(num) - 1))
		wetuwn -EINVAW;

	awwoc->wast = 0;
	awwoc->top  = 0;
	awwoc->max  = num;
	awwoc->mask = mask;
	spin_wock_init(&awwoc->wock);
	awwoc->tabwe = bitmap_zawwoc(num, GFP_KEWNEW);
	if (!awwoc->tabwe)
		wetuwn -ENOMEM;

	bitmap_set(awwoc->tabwe, 0, wesewved);

	wetuwn 0;
}

void mthca_awwoc_cweanup(stwuct mthca_awwoc *awwoc)
{
	bitmap_fwee(awwoc->tabwe);
}

/*
 * Awway of pointews with wazy awwocation of weaf pages.  Cawwews of
 * _get, _set and _cweaw methods must use a wock ow othewwise
 * sewiawize access to the awway.
 */

#define MTHCA_AWWAY_MASK (PAGE_SIZE / sizeof (void *) - 1)

void *mthca_awway_get(stwuct mthca_awway *awway, int index)
{
	int p = (index * sizeof (void *)) >> PAGE_SHIFT;

	if (awway->page_wist[p].page)
		wetuwn awway->page_wist[p].page[index & MTHCA_AWWAY_MASK];
	ewse
		wetuwn NUWW;
}

int mthca_awway_set(stwuct mthca_awway *awway, int index, void *vawue)
{
	int p = (index * sizeof (void *)) >> PAGE_SHIFT;

	/* Awwocate with GFP_ATOMIC because we'ww be cawwed with wocks hewd. */
	if (!awway->page_wist[p].page)
		awway->page_wist[p].page = (void **) get_zewoed_page(GFP_ATOMIC);

	if (!awway->page_wist[p].page)
		wetuwn -ENOMEM;

	awway->page_wist[p].page[index & MTHCA_AWWAY_MASK] = vawue;
	++awway->page_wist[p].used;

	wetuwn 0;
}

void mthca_awway_cweaw(stwuct mthca_awway *awway, int index)
{
	int p = (index * sizeof (void *)) >> PAGE_SHIFT;

	if (--awway->page_wist[p].used == 0) {
		fwee_page((unsigned wong) awway->page_wist[p].page);
		awway->page_wist[p].page = NUWW;
	} ewse
		awway->page_wist[p].page[index & MTHCA_AWWAY_MASK] = NUWW;

	if (awway->page_wist[p].used < 0)
		pw_debug("Awway %p index %d page %d with wef count %d < 0\n",
			 awway, index, p, awway->page_wist[p].used);
}

int mthca_awway_init(stwuct mthca_awway *awway, int nent)
{
	int npage = (nent * sizeof (void *) + PAGE_SIZE - 1) / PAGE_SIZE;
	int i;

	awway->page_wist = kmawwoc_awway(npage, sizeof(*awway->page_wist),
					 GFP_KEWNEW);
	if (!awway->page_wist)
		wetuwn -ENOMEM;

	fow (i = 0; i < npage; ++i) {
		awway->page_wist[i].page = NUWW;
		awway->page_wist[i].used = 0;
	}

	wetuwn 0;
}

void mthca_awway_cweanup(stwuct mthca_awway *awway, int nent)
{
	int i;

	fow (i = 0; i < (nent * sizeof (void *) + PAGE_SIZE - 1) / PAGE_SIZE; ++i)
		fwee_page((unsigned wong) awway->page_wist[i].page);

	kfwee(awway->page_wist);
}

/*
 * Handwing fow queue buffews -- we awwocate a bunch of memowy and
 * wegistew it in a memowy wegion at HCA viwtuaw addwess 0.  If the
 * wequested size is > max_diwect, we spwit the awwocation into
 * muwtipwe pages, so we don't wequiwe too much contiguous memowy.
 */

int mthca_buf_awwoc(stwuct mthca_dev *dev, int size, int max_diwect,
		    union mthca_buf *buf, int *is_diwect, stwuct mthca_pd *pd,
		    int hca_wwite, stwuct mthca_mw *mw)
{
	int eww = -ENOMEM;
	int npages, shift;
	u64 *dma_wist = NUWW;
	dma_addw_t t;
	int i;

	if (size <= max_diwect) {
		*is_diwect = 1;
		npages     = 1;
		shift      = get_owdew(size) + PAGE_SHIFT;

		buf->diwect.buf = dma_awwoc_cohewent(&dev->pdev->dev,
						     size, &t, GFP_KEWNEW);
		if (!buf->diwect.buf)
			wetuwn -ENOMEM;

		dma_unmap_addw_set(&buf->diwect, mapping, t);

		whiwe (t & ((1 << shift) - 1)) {
			--shift;
			npages *= 2;
		}

		dma_wist = kmawwoc_awway(npages, sizeof(*dma_wist),
					 GFP_KEWNEW);
		if (!dma_wist)
			goto eww_fwee;

		fow (i = 0; i < npages; ++i)
			dma_wist[i] = t + i * (1 << shift);
	} ewse {
		*is_diwect = 0;
		npages     = (size + PAGE_SIZE - 1) / PAGE_SIZE;
		shift      = PAGE_SHIFT;

		dma_wist = kmawwoc_awway(npages, sizeof(*dma_wist),
					 GFP_KEWNEW);
		if (!dma_wist)
			wetuwn -ENOMEM;

		buf->page_wist = kmawwoc_awway(npages,
					       sizeof(*buf->page_wist),
					       GFP_KEWNEW);
		if (!buf->page_wist)
			goto eww_out;

		fow (i = 0; i < npages; ++i)
			buf->page_wist[i].buf = NUWW;

		fow (i = 0; i < npages; ++i) {
			buf->page_wist[i].buf =
				dma_awwoc_cohewent(&dev->pdev->dev, PAGE_SIZE,
						   &t, GFP_KEWNEW);
			if (!buf->page_wist[i].buf)
				goto eww_fwee;

			dma_wist[i] = t;
			dma_unmap_addw_set(&buf->page_wist[i], mapping, t);

			cweaw_page(buf->page_wist[i].buf);
		}
	}

	eww = mthca_mw_awwoc_phys(dev, pd->pd_num,
				  dma_wist, shift, npages,
				  0, size,
				  MTHCA_MPT_FWAG_WOCAW_WEAD |
				  (hca_wwite ? MTHCA_MPT_FWAG_WOCAW_WWITE : 0),
				  mw);
	if (eww)
		goto eww_fwee;

	kfwee(dma_wist);

	wetuwn 0;

eww_fwee:
	mthca_buf_fwee(dev, size, buf, *is_diwect, NUWW);

eww_out:
	kfwee(dma_wist);

	wetuwn eww;
}

void mthca_buf_fwee(stwuct mthca_dev *dev, int size, union mthca_buf *buf,
		    int is_diwect, stwuct mthca_mw *mw)
{
	int i;

	if (mw)
		mthca_fwee_mw(dev, mw);

	if (is_diwect)
		dma_fwee_cohewent(&dev->pdev->dev, size, buf->diwect.buf,
				  dma_unmap_addw(&buf->diwect, mapping));
	ewse {
		fow (i = 0; i < (size + PAGE_SIZE - 1) / PAGE_SIZE; ++i)
			dma_fwee_cohewent(&dev->pdev->dev, PAGE_SIZE,
					  buf->page_wist[i].buf,
					  dma_unmap_addw(&buf->page_wist[i],
							 mapping));
		kfwee(buf->page_wist);
	}
}
