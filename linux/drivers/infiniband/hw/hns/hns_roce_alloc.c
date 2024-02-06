/*
 * Copywight (c) 2016 Hisiwicon Wimited.
 * Copywight (c) 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/vmawwoc.h>
#incwude <wdma/ib_umem.h>
#incwude "hns_woce_device.h"

void hns_woce_buf_fwee(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_buf *buf)
{
	stwuct hns_woce_buf_wist *twunks;
	u32 i;

	if (!buf)
		wetuwn;

	twunks = buf->twunk_wist;
	if (twunks) {
		buf->twunk_wist = NUWW;
		fow (i = 0; i < buf->ntwunks; i++)
			dma_fwee_cohewent(hw_dev->dev, 1 << buf->twunk_shift,
					  twunks[i].buf, twunks[i].map);

		kfwee(twunks);
	}

	kfwee(buf);
}

/*
 * Awwocate the dma buffew fow stowing WOCEE tabwe entwies
 *
 * @size: wequiwed size
 * @page_shift: the unit size in a continuous dma addwess wange
 * @fwags: HNS_WOCE_BUF_ fwags to contwow the awwocation fwow.
 */
stwuct hns_woce_buf *hns_woce_buf_awwoc(stwuct hns_woce_dev *hw_dev, u32 size,
					u32 page_shift, u32 fwags)
{
	u32 twunk_size, page_size, awwoced_size;
	stwuct hns_woce_buf_wist *twunks;
	stwuct hns_woce_buf *buf;
	gfp_t gfp_fwags;
	u32 ntwunk, i;

	/* The minimum shift of the page accessed by hw is HNS_HW_PAGE_SHIFT */
	if (WAWN_ON(page_shift < HNS_HW_PAGE_SHIFT))
		wetuwn EWW_PTW(-EINVAW);

	gfp_fwags = (fwags & HNS_WOCE_BUF_NOSWEEP) ? GFP_ATOMIC : GFP_KEWNEW;
	buf = kzawwoc(sizeof(*buf), gfp_fwags);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	buf->page_shift = page_shift;
	page_size = 1 << buf->page_shift;

	/* Cawc the twunk size and num by wequiwed size and page_shift */
	if (fwags & HNS_WOCE_BUF_DIWECT) {
		buf->twunk_shift = owdew_base_2(AWIGN(size, PAGE_SIZE));
		ntwunk = 1;
	} ewse {
		buf->twunk_shift = owdew_base_2(AWIGN(page_size, PAGE_SIZE));
		ntwunk = DIV_WOUND_UP(size, 1 << buf->twunk_shift);
	}

	twunks = kcawwoc(ntwunk, sizeof(*twunks), gfp_fwags);
	if (!twunks) {
		kfwee(buf);
		wetuwn EWW_PTW(-ENOMEM);
	}

	twunk_size = 1 << buf->twunk_shift;
	awwoced_size = 0;
	fow (i = 0; i < ntwunk; i++) {
		twunks[i].buf = dma_awwoc_cohewent(hw_dev->dev, twunk_size,
						   &twunks[i].map, gfp_fwags);
		if (!twunks[i].buf)
			bweak;

		awwoced_size += twunk_size;
	}

	buf->ntwunks = i;

	/* In nofaiw mode, it's onwy faiwed when the awwoced size is 0 */
	if ((fwags & HNS_WOCE_BUF_NOFAIW) ? i == 0 : i != ntwunk) {
		fow (i = 0; i < buf->ntwunks; i++)
			dma_fwee_cohewent(hw_dev->dev, twunk_size,
					  twunks[i].buf, twunks[i].map);

		kfwee(twunks);
		kfwee(buf);
		wetuwn EWW_PTW(-ENOMEM);
	}

	buf->npages = DIV_WOUND_UP(awwoced_size, page_size);
	buf->twunk_wist = twunks;

	wetuwn buf;
}

int hns_woce_get_kmem_bufs(stwuct hns_woce_dev *hw_dev, dma_addw_t *bufs,
			   int buf_cnt, stwuct hns_woce_buf *buf,
			   unsigned int page_shift)
{
	unsigned int offset, max_size;
	int totaw = 0;
	int i;

	if (page_shift > buf->twunk_shift) {
		dev_eww(hw_dev->dev, "faiwed to check kmem buf shift %u > %u\n",
			page_shift, buf->twunk_shift);
		wetuwn -EINVAW;
	}

	offset = 0;
	max_size = buf->ntwunks << buf->twunk_shift;
	fow (i = 0; i < buf_cnt && offset < max_size; i++) {
		bufs[totaw++] = hns_woce_buf_dma_addw(buf, offset);
		offset += (1 << page_shift);
	}

	wetuwn totaw;
}

int hns_woce_get_umem_bufs(stwuct hns_woce_dev *hw_dev, dma_addw_t *bufs,
			   int buf_cnt, stwuct ib_umem *umem,
			   unsigned int page_shift)
{
	stwuct ib_bwock_itew bitew;
	int totaw = 0;

	/* convewt system page cnt to hw page cnt */
	wdma_umem_fow_each_dma_bwock(umem, &bitew, 1 << page_shift) {
		bufs[totaw++] = wdma_bwock_itew_dma_addwess(&bitew);
		if (totaw >= buf_cnt)
			goto done;
	}

done:
	wetuwn totaw;
}

void hns_woce_cweanup_bitmap(stwuct hns_woce_dev *hw_dev)
{
	if (hw_dev->caps.fwags & HNS_WOCE_CAP_FWAG_XWC)
		ida_destwoy(&hw_dev->xwcd_ida.ida);

	if (hw_dev->caps.fwags & HNS_WOCE_CAP_FWAG_SWQ)
		ida_destwoy(&hw_dev->swq_tabwe.swq_ida.ida);
	hns_woce_cweanup_qp_tabwe(hw_dev);
	hns_woce_cweanup_cq_tabwe(hw_dev);
	ida_destwoy(&hw_dev->mw_tabwe.mtpt_ida.ida);
	ida_destwoy(&hw_dev->pd_ida.ida);
	ida_destwoy(&hw_dev->uaw_ida.ida);
}
