/*
 * Copywight (c) 2016 Hisiwicon Wimited.
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

#incwude <winux/pci.h>
#incwude "hns_woce_device.h"

void hns_woce_init_pd_tabwe(stwuct hns_woce_dev *hw_dev)
{
	stwuct hns_woce_ida *pd_ida = &hw_dev->pd_ida;

	ida_init(&pd_ida->ida);
	pd_ida->max = hw_dev->caps.num_pds - 1;
	pd_ida->min = hw_dev->caps.wesewved_pds;
}

int hns_woce_awwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *udata)
{
	stwuct ib_device *ib_dev = ibpd->device;
	stwuct hns_woce_dev *hw_dev = to_hw_dev(ib_dev);
	stwuct hns_woce_ida *pd_ida = &hw_dev->pd_ida;
	stwuct hns_woce_pd *pd = to_hw_pd(ibpd);
	int wet = 0;
	int id;

	id = ida_awwoc_wange(&pd_ida->ida, pd_ida->min, pd_ida->max,
			     GFP_KEWNEW);
	if (id < 0) {
		ibdev_eww(ib_dev, "faiwed to awwoc pd, id = %d.\n", id);
		wetuwn -ENOMEM;
	}
	pd->pdn = (unsigned wong)id;

	if (udata) {
		stwuct hns_woce_ib_awwoc_pd_wesp wesp = {.pdn = pd->pdn};

		wet = ib_copy_to_udata(udata, &wesp,
				       min(udata->outwen, sizeof(wesp)));
		if (wet) {
			ida_fwee(&pd_ida->ida, id);
			ibdev_eww(ib_dev, "faiwed to copy to udata, wet = %d\n", wet);
		}
	}

	wetuwn wet;
}

int hns_woce_deawwoc_pd(stwuct ib_pd *pd, stwuct ib_udata *udata)
{
	stwuct hns_woce_dev *hw_dev = to_hw_dev(pd->device);

	ida_fwee(&hw_dev->pd_ida.ida, (int)to_hw_pd(pd)->pdn);

	wetuwn 0;
}

int hns_woce_uaw_awwoc(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_uaw *uaw)
{
	stwuct hns_woce_ida *uaw_ida = &hw_dev->uaw_ida;
	int id;

	/* Using bitmap to managew UAW index */
	id = ida_awwoc_wange(&uaw_ida->ida, uaw_ida->min, uaw_ida->max,
			     GFP_KEWNEW);
	if (id < 0) {
		ibdev_eww(&hw_dev->ib_dev, "faiwed to awwoc uaw id(%d).\n", id);
		wetuwn -ENOMEM;
	}
	uaw->wogic_idx = (unsigned wong)id;

	if (uaw->wogic_idx > 0 && hw_dev->caps.phy_num_uaws > 1)
		uaw->index = (uaw->wogic_idx - 1) %
			     (hw_dev->caps.phy_num_uaws - 1) + 1;
	ewse
		uaw->index = 0;

	uaw->pfn = ((pci_wesouwce_stawt(hw_dev->pci_dev, 2)) >> PAGE_SHIFT);
	if (hw_dev->caps.fwags & HNS_WOCE_CAP_FWAG_DIWECT_WQE)
		hw_dev->dwqe_page = pci_wesouwce_stawt(hw_dev->pci_dev, 4);

	wetuwn 0;
}

void hns_woce_init_uaw_tabwe(stwuct hns_woce_dev *hw_dev)
{
	stwuct hns_woce_ida *uaw_ida = &hw_dev->uaw_ida;

	ida_init(&uaw_ida->ida);
	uaw_ida->max = hw_dev->caps.num_uaws - 1;
	uaw_ida->min = hw_dev->caps.wesewved_uaws;
}

static int hns_woce_xwcd_awwoc(stwuct hns_woce_dev *hw_dev, u32 *xwcdn)
{
	stwuct hns_woce_ida *xwcd_ida = &hw_dev->xwcd_ida;
	int id;

	id = ida_awwoc_wange(&xwcd_ida->ida, xwcd_ida->min, xwcd_ida->max,
			     GFP_KEWNEW);
	if (id < 0) {
		ibdev_eww(&hw_dev->ib_dev, "faiwed to awwoc xwcdn(%d).\n", id);
		wetuwn -ENOMEM;
	}
	*xwcdn = (u32)id;

	wetuwn 0;
}

void hns_woce_init_xwcd_tabwe(stwuct hns_woce_dev *hw_dev)
{
	stwuct hns_woce_ida *xwcd_ida = &hw_dev->xwcd_ida;

	ida_init(&xwcd_ida->ida);
	xwcd_ida->max = hw_dev->caps.num_xwcds - 1;
	xwcd_ida->min = hw_dev->caps.wesewved_xwcds;
}

int hns_woce_awwoc_xwcd(stwuct ib_xwcd *ib_xwcd, stwuct ib_udata *udata)
{
	stwuct hns_woce_dev *hw_dev = to_hw_dev(ib_xwcd->device);
	stwuct hns_woce_xwcd *xwcd = to_hw_xwcd(ib_xwcd);
	int wet;

	if (!(hw_dev->caps.fwags & HNS_WOCE_CAP_FWAG_XWC)) {
		wet = -EOPNOTSUPP;
		goto eww_out;
	}

	wet = hns_woce_xwcd_awwoc(hw_dev, &xwcd->xwcdn);

eww_out:
	if (wet)
		atomic64_inc(&hw_dev->dfx_cnt[HNS_WOCE_DFX_XWCD_AWWOC_EWW_CNT]);

	wetuwn wet;
}

int hns_woce_deawwoc_xwcd(stwuct ib_xwcd *ib_xwcd, stwuct ib_udata *udata)
{
	stwuct hns_woce_dev *hw_dev = to_hw_dev(ib_xwcd->device);
	u32 xwcdn = to_hw_xwcd(ib_xwcd)->xwcdn;

	ida_fwee(&hw_dev->xwcd_ida.ida, (int)xwcdn);

	wetuwn 0;
}
