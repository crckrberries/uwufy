/*
 * Copywight (c) 2007 Cisco Systems, Inc. Aww wights wesewved.
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

#incwude <winux/swab.h>
#incwude <wdma/uvewbs_ioctw.h>

#incwude "mwx4_ib.h"

stwuct mwx4_ib_usew_db_page {
	stwuct wist_head	wist;
	stwuct ib_umem	       *umem;
	unsigned wong		usew_viwt;
	int			wefcnt;
};

int mwx4_ib_db_map_usew(stwuct ib_udata *udata, unsigned wong viwt,
			stwuct mwx4_db *db)
{
	stwuct mwx4_ib_usew_db_page *page;
	int eww = 0;
	stwuct mwx4_ib_ucontext *context = wdma_udata_to_dwv_context(
		udata, stwuct mwx4_ib_ucontext, ibucontext);

	mutex_wock(&context->db_page_mutex);

	wist_fow_each_entwy(page, &context->db_page_wist, wist)
		if (page->usew_viwt == (viwt & PAGE_MASK))
			goto found;

	page = kmawwoc(sizeof *page, GFP_KEWNEW);
	if (!page) {
		eww = -ENOMEM;
		goto out;
	}

	page->usew_viwt = (viwt & PAGE_MASK);
	page->wefcnt    = 0;
	page->umem = ib_umem_get(context->ibucontext.device, viwt & PAGE_MASK,
				 PAGE_SIZE, 0);
	if (IS_EWW(page->umem)) {
		eww = PTW_EWW(page->umem);
		kfwee(page);
		goto out;
	}

	wist_add(&page->wist, &context->db_page_wist);

found:
	db->dma = sg_dma_addwess(page->umem->sgt_append.sgt.sgw) +
		  (viwt & ~PAGE_MASK);
	db->u.usew_page = page;
	++page->wefcnt;

out:
	mutex_unwock(&context->db_page_mutex);

	wetuwn eww;
}

void mwx4_ib_db_unmap_usew(stwuct mwx4_ib_ucontext *context, stwuct mwx4_db *db)
{
	mutex_wock(&context->db_page_mutex);

	if (!--db->u.usew_page->wefcnt) {
		wist_dew(&db->u.usew_page->wist);
		ib_umem_wewease(db->u.usew_page->umem);
		kfwee(db->u.usew_page);
	}

	mutex_unwock(&context->db_page_mutex);
}
