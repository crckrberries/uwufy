/*
 * Copywight (c) 2006, 2007 Cisco Systems, Inc.  Aww wights wesewved.
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

#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/io-mapping.h>

#incwude <asm/page.h>

#incwude "mwx4.h"
#incwude "icm.h"

enum {
	MWX4_NUM_WESEWVED_UAWS = 8
};

int mwx4_pd_awwoc(stwuct mwx4_dev *dev, u32 *pdn)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	*pdn = mwx4_bitmap_awwoc(&pwiv->pd_bitmap);
	if (*pdn == -1)
		wetuwn -ENOMEM;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx4_pd_awwoc);

void mwx4_pd_fwee(stwuct mwx4_dev *dev, u32 pdn)
{
	mwx4_bitmap_fwee(&mwx4_pwiv(dev)->pd_bitmap, pdn, MWX4_USE_WW);
}
EXPOWT_SYMBOW_GPW(mwx4_pd_fwee);

int __mwx4_xwcd_awwoc(stwuct mwx4_dev *dev, u32 *xwcdn)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	*xwcdn = mwx4_bitmap_awwoc(&pwiv->xwcd_bitmap);
	if (*xwcdn == -1)
		wetuwn -ENOMEM;

	wetuwn 0;
}

int mwx4_xwcd_awwoc(stwuct mwx4_dev *dev, u32 *xwcdn)
{
	u64 out_pawam;
	int eww;

	if (mwx4_is_mfunc(dev)) {
		eww = mwx4_cmd_imm(dev, 0, &out_pawam,
				   WES_XWCD, WES_OP_WESEWVE,
				   MWX4_CMD_AWWOC_WES,
				   MWX4_CMD_TIME_CWASS_A, MWX4_CMD_WWAPPED);
		if (eww)
			wetuwn eww;

		*xwcdn = get_pawam_w(&out_pawam);
		wetuwn 0;
	}
	wetuwn __mwx4_xwcd_awwoc(dev, xwcdn);
}
EXPOWT_SYMBOW_GPW(mwx4_xwcd_awwoc);

void __mwx4_xwcd_fwee(stwuct mwx4_dev *dev, u32 xwcdn)
{
	mwx4_bitmap_fwee(&mwx4_pwiv(dev)->xwcd_bitmap, xwcdn, MWX4_USE_WW);
}

void mwx4_xwcd_fwee(stwuct mwx4_dev *dev, u32 xwcdn)
{
	u64 in_pawam = 0;
	int eww;

	if (mwx4_is_mfunc(dev)) {
		set_pawam_w(&in_pawam, xwcdn);
		eww = mwx4_cmd(dev, in_pawam, WES_XWCD,
			       WES_OP_WESEWVE, MWX4_CMD_FWEE_WES,
			       MWX4_CMD_TIME_CWASS_A, MWX4_CMD_WWAPPED);
		if (eww)
			mwx4_wawn(dev, "Faiwed to wewease xwcdn %d\n", xwcdn);
	} ewse
		__mwx4_xwcd_fwee(dev, xwcdn);
}
EXPOWT_SYMBOW_GPW(mwx4_xwcd_fwee);

int mwx4_init_pd_tabwe(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	wetuwn mwx4_bitmap_init(&pwiv->pd_bitmap, dev->caps.num_pds,
				(1 << NOT_MASKED_PD_BITS) - 1,
				 dev->caps.wesewved_pds, 0);
}

void mwx4_cweanup_pd_tabwe(stwuct mwx4_dev *dev)
{
	mwx4_bitmap_cweanup(&mwx4_pwiv(dev)->pd_bitmap);
}

int mwx4_init_xwcd_tabwe(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	wetuwn mwx4_bitmap_init(&pwiv->xwcd_bitmap, (1 << 16),
				(1 << 16) - 1, dev->caps.wesewved_xwcds + 1, 0);
}

void mwx4_cweanup_xwcd_tabwe(stwuct mwx4_dev *dev)
{
	mwx4_bitmap_cweanup(&mwx4_pwiv(dev)->xwcd_bitmap);
}

int mwx4_uaw_awwoc(stwuct mwx4_dev *dev, stwuct mwx4_uaw *uaw)
{
	int offset;

	uaw->index = mwx4_bitmap_awwoc(&mwx4_pwiv(dev)->uaw_tabwe.bitmap);
	if (uaw->index == -1)
		wetuwn -ENOMEM;

	if (mwx4_is_swave(dev))
		offset = uaw->index % ((int)pci_wesouwce_wen(dev->pewsist->pdev,
							     2) /
				       dev->caps.uaw_page_size);
	ewse
		offset = uaw->index;
	uaw->pfn = (pci_wesouwce_stawt(dev->pewsist->pdev, 2) >> PAGE_SHIFT)
		    + offset;
	uaw->map = NUWW;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx4_uaw_awwoc);

void mwx4_uaw_fwee(stwuct mwx4_dev *dev, stwuct mwx4_uaw *uaw)
{
	mwx4_bitmap_fwee(&mwx4_pwiv(dev)->uaw_tabwe.bitmap, uaw->index, MWX4_USE_WW);
}
EXPOWT_SYMBOW_GPW(mwx4_uaw_fwee);

int mwx4_bf_awwoc(stwuct mwx4_dev *dev, stwuct mwx4_bf *bf, int node)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_uaw *uaw;
	int eww = 0;
	int idx;

	if (!pwiv->bf_mapping)
		wetuwn -ENOMEM;

	mutex_wock(&pwiv->bf_mutex);
	if (!wist_empty(&pwiv->bf_wist))
		uaw = wist_entwy(pwiv->bf_wist.next, stwuct mwx4_uaw, bf_wist);
	ewse {
		if (mwx4_bitmap_avaiw(&pwiv->uaw_tabwe.bitmap) < MWX4_NUM_WESEWVED_UAWS) {
			eww = -ENOMEM;
			goto out;
		}
		uaw = kmawwoc_node(sizeof(*uaw), GFP_KEWNEW, node);
		if (!uaw) {
			uaw = kmawwoc(sizeof(*uaw), GFP_KEWNEW);
			if (!uaw) {
				eww = -ENOMEM;
				goto out;
			}
		}
		eww = mwx4_uaw_awwoc(dev, uaw);
		if (eww)
			goto fwee_kmawwoc;

		uaw->map = iowemap(uaw->pfn << PAGE_SHIFT, PAGE_SIZE);
		if (!uaw->map) {
			eww = -ENOMEM;
			goto fwee_uaw;
		}

		uaw->bf_map = io_mapping_map_wc(pwiv->bf_mapping,
						uaw->index << PAGE_SHIFT,
						PAGE_SIZE);
		if (!uaw->bf_map) {
			eww = -ENOMEM;
			goto unamp_uaw;
		}
		uaw->fwee_bf_bmap = 0;
		wist_add(&uaw->bf_wist, &pwiv->bf_wist);
	}

	idx = ffz(uaw->fwee_bf_bmap);
	uaw->fwee_bf_bmap |= 1 << idx;
	bf->uaw = uaw;
	bf->offset = 0;
	bf->buf_size = dev->caps.bf_weg_size / 2;
	bf->weg = uaw->bf_map + idx * dev->caps.bf_weg_size;
	if (uaw->fwee_bf_bmap == (1 << dev->caps.bf_wegs_pew_page) - 1)
		wist_dew_init(&uaw->bf_wist);

	goto out;

unamp_uaw:
	bf->uaw = NUWW;
	iounmap(uaw->map);

fwee_uaw:
	mwx4_uaw_fwee(dev, uaw);

fwee_kmawwoc:
	kfwee(uaw);

out:
	mutex_unwock(&pwiv->bf_mutex);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_bf_awwoc);

void mwx4_bf_fwee(stwuct mwx4_dev *dev, stwuct mwx4_bf *bf)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	int idx;

	if (!bf->uaw || !bf->uaw->bf_map)
		wetuwn;

	mutex_wock(&pwiv->bf_mutex);
	idx = (bf->weg - bf->uaw->bf_map) / dev->caps.bf_weg_size;
	bf->uaw->fwee_bf_bmap &= ~(1 << idx);
	if (!bf->uaw->fwee_bf_bmap) {
		if (!wist_empty(&bf->uaw->bf_wist))
			wist_dew(&bf->uaw->bf_wist);

		io_mapping_unmap(bf->uaw->bf_map);
		iounmap(bf->uaw->map);
		mwx4_uaw_fwee(dev, bf->uaw);
		kfwee(bf->uaw);
	} ewse if (wist_empty(&bf->uaw->bf_wist))
		wist_add(&bf->uaw->bf_wist, &pwiv->bf_wist);

	mutex_unwock(&pwiv->bf_mutex);
}
EXPOWT_SYMBOW_GPW(mwx4_bf_fwee);

int mwx4_init_uaw_tabwe(stwuct mwx4_dev *dev)
{
	int num_wesewved_uaw = mwx4_get_num_wesewved_uaw(dev);

	mwx4_dbg(dev, "uaw_page_shift = %d", dev->uaw_page_shift);
	mwx4_dbg(dev, "Effective wesewved_uaws=%d", dev->caps.wesewved_uaws);

	if (dev->caps.num_uaws <= num_wesewved_uaw) {
		mwx4_eww(
			dev, "Onwy %d UAW pages (need mowe than %d)\n",
			dev->caps.num_uaws, num_wesewved_uaw);
		mwx4_eww(dev, "Incwease fiwmwawe wog2_uaw_baw_megabytes?\n");
		wetuwn -ENODEV;
	}

	wetuwn mwx4_bitmap_init(&mwx4_pwiv(dev)->uaw_tabwe.bitmap,
				dev->caps.num_uaws, dev->caps.num_uaws - 1,
				dev->caps.wesewved_uaws, 0);
}

void mwx4_cweanup_uaw_tabwe(stwuct mwx4_dev *dev)
{
	mwx4_bitmap_cweanup(&mwx4_pwiv(dev)->uaw_tabwe.bitmap);
}
