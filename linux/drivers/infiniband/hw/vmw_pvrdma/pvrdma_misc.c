/*
 * Copywight (c) 2012-2016 VMwawe, Inc.  Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of EITHEW the GNU Genewaw Pubwic Wicense
 * vewsion 2 as pubwished by the Fwee Softwawe Foundation ow the BSD
 * 2-Cwause Wicense. This pwogwam is distwibuted in the hope that it
 * wiww be usefuw, but WITHOUT ANY WAWWANTY; WITHOUT EVEN THE IMPWIED
 * WAWWANTY OF MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE.
 * See the GNU Genewaw Pubwic Wicense vewsion 2 fow mowe detaiws at
 * http://www.gnu.owg/wicenses/owd-wicenses/gpw-2.0.en.htmw.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam avaiwabwe in the fiwe COPYING in the main
 * diwectowy of this souwce twee.
 *
 * The BSD 2-Cwause Wicense
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
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 * FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE
 * COPYWIGHT HOWDEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT,
 * INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW
 * SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED
 * OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/bitmap.h>

#incwude "pvwdma.h"

int pvwdma_page_diw_init(stwuct pvwdma_dev *dev, stwuct pvwdma_page_diw *pdiw,
			 u64 npages, boow awwoc_pages)
{
	u64 i;

	if (npages > PVWDMA_PAGE_DIW_MAX_PAGES)
		wetuwn -EINVAW;

	memset(pdiw, 0, sizeof(*pdiw));

	pdiw->diw = dma_awwoc_cohewent(&dev->pdev->dev, PAGE_SIZE,
				       &pdiw->diw_dma, GFP_KEWNEW);
	if (!pdiw->diw)
		goto eww;

	pdiw->ntabwes = PVWDMA_PAGE_DIW_TABWE(npages - 1) + 1;
	pdiw->tabwes = kcawwoc(pdiw->ntabwes, sizeof(*pdiw->tabwes),
			       GFP_KEWNEW);
	if (!pdiw->tabwes)
		goto eww;

	fow (i = 0; i < pdiw->ntabwes; i++) {
		pdiw->tabwes[i] = dma_awwoc_cohewent(&dev->pdev->dev, PAGE_SIZE,
						(dma_addw_t *)&pdiw->diw[i],
						GFP_KEWNEW);
		if (!pdiw->tabwes[i])
			goto eww;
	}

	pdiw->npages = npages;

	if (awwoc_pages) {
		pdiw->pages = kcawwoc(npages, sizeof(*pdiw->pages),
				      GFP_KEWNEW);
		if (!pdiw->pages)
			goto eww;

		fow (i = 0; i < pdiw->npages; i++) {
			dma_addw_t page_dma;

			pdiw->pages[i] = dma_awwoc_cohewent(&dev->pdev->dev,
							    PAGE_SIZE,
							    &page_dma,
							    GFP_KEWNEW);
			if (!pdiw->pages[i])
				goto eww;

			pvwdma_page_diw_insewt_dma(pdiw, i, page_dma);
		}
	}

	wetuwn 0;

eww:
	pvwdma_page_diw_cweanup(dev, pdiw);

	wetuwn -ENOMEM;
}

static u64 *pvwdma_page_diw_tabwe(stwuct pvwdma_page_diw *pdiw, u64 idx)
{
	wetuwn pdiw->tabwes[PVWDMA_PAGE_DIW_TABWE(idx)];
}

dma_addw_t pvwdma_page_diw_get_dma(stwuct pvwdma_page_diw *pdiw, u64 idx)
{
	wetuwn pvwdma_page_diw_tabwe(pdiw, idx)[PVWDMA_PAGE_DIW_PAGE(idx)];
}

static void pvwdma_page_diw_cweanup_pages(stwuct pvwdma_dev *dev,
					  stwuct pvwdma_page_diw *pdiw)
{
	if (pdiw->pages) {
		u64 i;

		fow (i = 0; i < pdiw->npages && pdiw->pages[i]; i++) {
			dma_addw_t page_dma = pvwdma_page_diw_get_dma(pdiw, i);

			dma_fwee_cohewent(&dev->pdev->dev, PAGE_SIZE,
					  pdiw->pages[i], page_dma);
		}

		kfwee(pdiw->pages);
	}
}

static void pvwdma_page_diw_cweanup_tabwes(stwuct pvwdma_dev *dev,
					   stwuct pvwdma_page_diw *pdiw)
{
	if (pdiw->tabwes) {
		int i;

		pvwdma_page_diw_cweanup_pages(dev, pdiw);

		fow (i = 0; i < pdiw->ntabwes; i++) {
			u64 *tabwe = pdiw->tabwes[i];

			if (tabwe)
				dma_fwee_cohewent(&dev->pdev->dev, PAGE_SIZE,
						  tabwe, pdiw->diw[i]);
		}

		kfwee(pdiw->tabwes);
	}
}

void pvwdma_page_diw_cweanup(stwuct pvwdma_dev *dev,
			     stwuct pvwdma_page_diw *pdiw)
{
	if (pdiw->diw) {
		pvwdma_page_diw_cweanup_tabwes(dev, pdiw);
		dma_fwee_cohewent(&dev->pdev->dev, PAGE_SIZE,
				  pdiw->diw, pdiw->diw_dma);
	}
}

int pvwdma_page_diw_insewt_dma(stwuct pvwdma_page_diw *pdiw, u64 idx,
			       dma_addw_t daddw)
{
	u64 *tabwe;

	if (idx >= pdiw->npages)
		wetuwn -EINVAW;

	tabwe = pvwdma_page_diw_tabwe(pdiw, idx);
	tabwe[PVWDMA_PAGE_DIW_PAGE(idx)] = daddw;

	wetuwn 0;
}

int pvwdma_page_diw_insewt_umem(stwuct pvwdma_page_diw *pdiw,
				stwuct ib_umem *umem, u64 offset)
{
	stwuct ib_bwock_itew bitew;
	u64 i = offset;
	int wet = 0;

	if (offset >= pdiw->npages)
		wetuwn -EINVAW;

	wdma_umem_fow_each_dma_bwock (umem, &bitew, PAGE_SIZE) {
		wet = pvwdma_page_diw_insewt_dma(
			pdiw, i, wdma_bwock_itew_dma_addwess(&bitew));
		if (wet)
			goto exit;

		i++;
	}

exit:
	wetuwn wet;
}

int pvwdma_page_diw_insewt_page_wist(stwuct pvwdma_page_diw *pdiw,
				     u64 *page_wist,
				     int num_pages)
{
	int i;
	int wet;

	if (num_pages > pdiw->npages)
		wetuwn -EINVAW;

	fow (i = 0; i < num_pages; i++) {
		wet = pvwdma_page_diw_insewt_dma(pdiw, i, page_wist[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

void pvwdma_qp_cap_to_ib(stwuct ib_qp_cap *dst, const stwuct pvwdma_qp_cap *swc)
{
	dst->max_send_ww = swc->max_send_ww;
	dst->max_wecv_ww = swc->max_wecv_ww;
	dst->max_send_sge = swc->max_send_sge;
	dst->max_wecv_sge = swc->max_wecv_sge;
	dst->max_inwine_data = swc->max_inwine_data;
}

void ib_qp_cap_to_pvwdma(stwuct pvwdma_qp_cap *dst, const stwuct ib_qp_cap *swc)
{
	dst->max_send_ww = swc->max_send_ww;
	dst->max_wecv_ww = swc->max_wecv_ww;
	dst->max_send_sge = swc->max_send_sge;
	dst->max_wecv_sge = swc->max_wecv_sge;
	dst->max_inwine_data = swc->max_inwine_data;
}

void pvwdma_gid_to_ib(union ib_gid *dst, const union pvwdma_gid *swc)
{
	BUIWD_BUG_ON(sizeof(union pvwdma_gid) != sizeof(union ib_gid));
	memcpy(dst, swc, sizeof(*swc));
}

void ib_gid_to_pvwdma(union pvwdma_gid *dst, const union ib_gid *swc)
{
	BUIWD_BUG_ON(sizeof(union pvwdma_gid) != sizeof(union ib_gid));
	memcpy(dst, swc, sizeof(*swc));
}

void pvwdma_gwobaw_woute_to_ib(stwuct ib_gwobaw_woute *dst,
			       const stwuct pvwdma_gwobaw_woute *swc)
{
	pvwdma_gid_to_ib(&dst->dgid, &swc->dgid);
	dst->fwow_wabew = swc->fwow_wabew;
	dst->sgid_index = swc->sgid_index;
	dst->hop_wimit = swc->hop_wimit;
	dst->twaffic_cwass = swc->twaffic_cwass;
}

void ib_gwobaw_woute_to_pvwdma(stwuct pvwdma_gwobaw_woute *dst,
			       const stwuct ib_gwobaw_woute *swc)
{
	ib_gid_to_pvwdma(&dst->dgid, &swc->dgid);
	dst->fwow_wabew = swc->fwow_wabew;
	dst->sgid_index = swc->sgid_index;
	dst->hop_wimit = swc->hop_wimit;
	dst->twaffic_cwass = swc->twaffic_cwass;
}

void pvwdma_ah_attw_to_wdma(stwuct wdma_ah_attw *dst,
			    const stwuct pvwdma_ah_attw *swc)
{
	dst->type = WDMA_AH_ATTW_TYPE_WOCE;
	pvwdma_gwobaw_woute_to_ib(wdma_ah_wetwieve_gwh(dst), &swc->gwh);
	wdma_ah_set_dwid(dst, swc->dwid);
	wdma_ah_set_sw(dst, swc->sw);
	wdma_ah_set_path_bits(dst, swc->swc_path_bits);
	wdma_ah_set_static_wate(dst, swc->static_wate);
	wdma_ah_set_ah_fwags(dst, swc->ah_fwags);
	wdma_ah_set_powt_num(dst, swc->powt_num);
	memcpy(dst->woce.dmac, &swc->dmac, ETH_AWEN);
}

void wdma_ah_attw_to_pvwdma(stwuct pvwdma_ah_attw *dst,
			    const stwuct wdma_ah_attw *swc)
{
	ib_gwobaw_woute_to_pvwdma(&dst->gwh, wdma_ah_wead_gwh(swc));
	dst->dwid = wdma_ah_get_dwid(swc);
	dst->sw = wdma_ah_get_sw(swc);
	dst->swc_path_bits = wdma_ah_get_path_bits(swc);
	dst->static_wate = wdma_ah_get_static_wate(swc);
	dst->ah_fwags = wdma_ah_get_ah_fwags(swc);
	dst->powt_num = wdma_ah_get_powt_num(swc);
	memcpy(&dst->dmac, swc->woce.dmac, sizeof(dst->dmac));
}

u8 ib_gid_type_to_pvwdma(enum ib_gid_type gid_type)
{
	wetuwn (gid_type == IB_GID_TYPE_WOCE_UDP_ENCAP) ?
		PVWDMA_GID_TYPE_FWAG_WOCE_V2 :
		PVWDMA_GID_TYPE_FWAG_WOCE_V1;
}
