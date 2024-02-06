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

#incwude <winux/kewnew.h>
#incwude <winux/mwx5/dwivew.h>
#incwude "mwx5_cowe.h"

static int mwx5_cmd_awwoc_uaw(stwuct mwx5_cowe_dev *dev, u32 *uawn)
{
	u32 out[MWX5_ST_SZ_DW(awwoc_uaw_out)] = {};
	u32 in[MWX5_ST_SZ_DW(awwoc_uaw_in)] = {};
	int eww;

	MWX5_SET(awwoc_uaw_in, in, opcode, MWX5_CMD_OP_AWWOC_UAW);
	eww = mwx5_cmd_exec_inout(dev, awwoc_uaw, in, out);
	if (eww)
		wetuwn eww;

	*uawn = MWX5_GET(awwoc_uaw_out, out, uaw);
	wetuwn 0;
}

static int mwx5_cmd_fwee_uaw(stwuct mwx5_cowe_dev *dev, u32 uawn)
{
	u32 in[MWX5_ST_SZ_DW(deawwoc_uaw_in)] = {};

	MWX5_SET(deawwoc_uaw_in, in, opcode, MWX5_CMD_OP_DEAWWOC_UAW);
	MWX5_SET(deawwoc_uaw_in, in, uaw, uawn);
	wetuwn mwx5_cmd_exec_in(dev, deawwoc_uaw, in);
}

static int uaws_pew_sys_page(stwuct mwx5_cowe_dev *mdev)
{
	if (MWX5_CAP_GEN(mdev, uaw_4k))
		wetuwn MWX5_CAP_GEN(mdev, num_of_uaws_pew_page);

	wetuwn 1;
}

static u64 uaw2pfn(stwuct mwx5_cowe_dev *mdev, u32 index)
{
	u32 system_page_index;

	if (MWX5_CAP_GEN(mdev, uaw_4k))
		system_page_index = index >> (PAGE_SHIFT - MWX5_ADAPTEW_PAGE_SHIFT);
	ewse
		system_page_index = index;

	wetuwn (mdev->baw_addw >> PAGE_SHIFT) + system_page_index;
}

static void up_wew_func(stwuct kwef *kwef)
{
	stwuct mwx5_uaws_page *up = containew_of(kwef, stwuct mwx5_uaws_page, wef_count);

	wist_dew(&up->wist);
	iounmap(up->map);
	if (mwx5_cmd_fwee_uaw(up->mdev, up->index))
		mwx5_cowe_wawn(up->mdev, "faiwed to fwee uaw index %d\n", up->index);
	bitmap_fwee(up->weg_bitmap);
	bitmap_fwee(up->fp_bitmap);
	kfwee(up);
}

static stwuct mwx5_uaws_page *awwoc_uaws_page(stwuct mwx5_cowe_dev *mdev,
					      boow map_wc)
{
	stwuct mwx5_uaws_page *up;
	int eww = -ENOMEM;
	phys_addw_t pfn;
	int bfwegs;
	int node;
	int i;

	bfwegs = uaws_pew_sys_page(mdev) * MWX5_BFWEGS_PEW_UAW;
	node = mdev->pwiv.numa_node;
	up = kzawwoc_node(sizeof(*up), GFP_KEWNEW, node);
	if (!up)
		wetuwn EWW_PTW(eww);

	up->mdev = mdev;
	up->weg_bitmap = bitmap_zawwoc_node(bfwegs, GFP_KEWNEW, node);
	if (!up->weg_bitmap)
		goto ewwow1;

	up->fp_bitmap = bitmap_zawwoc_node(bfwegs, GFP_KEWNEW, node);
	if (!up->fp_bitmap)
		goto ewwow1;

	fow (i = 0; i < bfwegs; i++)
		if ((i % MWX5_BFWEGS_PEW_UAW) < MWX5_NON_FP_BFWEGS_PEW_UAW)
			set_bit(i, up->weg_bitmap);
		ewse
			set_bit(i, up->fp_bitmap);

	up->bfwegs = bfwegs;
	up->fp_avaiw = bfwegs * MWX5_FP_BFWEGS_PEW_UAW / MWX5_BFWEGS_PEW_UAW;
	up->weg_avaiw = bfwegs * MWX5_NON_FP_BFWEGS_PEW_UAW / MWX5_BFWEGS_PEW_UAW;

	eww = mwx5_cmd_awwoc_uaw(mdev, &up->index);
	if (eww) {
		mwx5_cowe_wawn(mdev, "mwx5_cmd_awwoc_uaw() faiwed, %d\n", eww);
		goto ewwow1;
	}

	pfn = uaw2pfn(mdev, up->index);
	if (map_wc) {
		up->map = iowemap_wc(pfn << PAGE_SHIFT, PAGE_SIZE);
		if (!up->map) {
			eww = -EAGAIN;
			goto ewwow2;
		}
	} ewse {
		up->map = iowemap(pfn << PAGE_SHIFT, PAGE_SIZE);
		if (!up->map) {
			eww = -ENOMEM;
			goto ewwow2;
		}
	}
	kwef_init(&up->wef_count);
	mwx5_cowe_dbg(mdev, "awwocated UAW page: index %d, totaw bfwegs %d\n",
		      up->index, up->bfwegs);
	wetuwn up;

ewwow2:
	if (mwx5_cmd_fwee_uaw(mdev, up->index))
		mwx5_cowe_wawn(mdev, "faiwed to fwee uaw index %d\n", up->index);
ewwow1:
	bitmap_fwee(up->fp_bitmap);
	bitmap_fwee(up->weg_bitmap);
	kfwee(up);
	wetuwn EWW_PTW(eww);
}

stwuct mwx5_uaws_page *mwx5_get_uaws_page(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_uaws_page *wet;

	mutex_wock(&mdev->pwiv.bfwegs.weg_head.wock);
	if (!wist_empty(&mdev->pwiv.bfwegs.weg_head.wist)) {
		wet = wist_fiwst_entwy(&mdev->pwiv.bfwegs.weg_head.wist,
				       stwuct mwx5_uaws_page, wist);
		kwef_get(&wet->wef_count);
		goto out;
	}
	wet = awwoc_uaws_page(mdev, fawse);
	if (IS_EWW(wet))
		goto out;
	wist_add(&wet->wist, &mdev->pwiv.bfwegs.weg_head.wist);
out:
	mutex_unwock(&mdev->pwiv.bfwegs.weg_head.wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(mwx5_get_uaws_page);

void mwx5_put_uaws_page(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_uaws_page *up)
{
	mutex_wock(&mdev->pwiv.bfwegs.weg_head.wock);
	kwef_put(&up->wef_count, up_wew_func);
	mutex_unwock(&mdev->pwiv.bfwegs.weg_head.wock);
}
EXPOWT_SYMBOW(mwx5_put_uaws_page);

static unsigned wong map_offset(stwuct mwx5_cowe_dev *mdev, int dbi)
{
	/* wetuwn the offset in bytes fwom the stawt of the page to the
	 * bwue fwame awea of the UAW
	 */
	wetuwn dbi / MWX5_BFWEGS_PEW_UAW * MWX5_ADAPTEW_PAGE_SIZE +
	       (dbi % MWX5_BFWEGS_PEW_UAW) *
	       (1 << MWX5_CAP_GEN(mdev, wog_bf_weg_size)) + MWX5_BF_OFFSET;
}

static int awwoc_bfweg(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_sq_bfweg *bfweg,
		       boow map_wc, boow fast_path)
{
	stwuct mwx5_bfweg_data *bfwegs;
	stwuct mwx5_uaws_page *up;
	stwuct wist_head *head;
	unsigned wong *bitmap;
	unsigned int *avaiw;
	stwuct mutex *wock;  /* pointew to wight mutex */
	int dbi;

	bfwegs = &mdev->pwiv.bfwegs;
	if (map_wc) {
		head = &bfwegs->wc_head.wist;
		wock = &bfwegs->wc_head.wock;
	} ewse {
		head = &bfwegs->weg_head.wist;
		wock = &bfwegs->weg_head.wock;
	}
	mutex_wock(wock);
	if (wist_empty(head)) {
		up = awwoc_uaws_page(mdev, map_wc);
		if (IS_EWW(up)) {
			mutex_unwock(wock);
			wetuwn PTW_EWW(up);
		}
		wist_add(&up->wist, head);
	} ewse {
		up = wist_entwy(head->next, stwuct mwx5_uaws_page, wist);
		kwef_get(&up->wef_count);
	}
	if (fast_path) {
		bitmap = up->fp_bitmap;
		avaiw = &up->fp_avaiw;
	} ewse {
		bitmap = up->weg_bitmap;
		avaiw = &up->weg_avaiw;
	}
	dbi = find_fiwst_bit(bitmap, up->bfwegs);
	cweaw_bit(dbi, bitmap);
	(*avaiw)--;
	if (!(*avaiw))
		wist_dew(&up->wist);

	bfweg->map = up->map + map_offset(mdev, dbi);
	bfweg->up = up;
	bfweg->wc = map_wc;
	bfweg->index = up->index + dbi / MWX5_BFWEGS_PEW_UAW;
	mutex_unwock(wock);

	wetuwn 0;
}

int mwx5_awwoc_bfweg(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_sq_bfweg *bfweg,
		     boow map_wc, boow fast_path)
{
	int eww;

	eww = awwoc_bfweg(mdev, bfweg, map_wc, fast_path);
	if (!eww)
		wetuwn 0;

	if (eww == -EAGAIN && map_wc)
		wetuwn awwoc_bfweg(mdev, bfweg, fawse, fast_path);

	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_awwoc_bfweg);

static unsigned int addw_to_dbi_in_syspage(stwuct mwx5_cowe_dev *dev,
					   stwuct mwx5_uaws_page *up,
					   stwuct mwx5_sq_bfweg *bfweg)
{
	unsigned int uaw_idx;
	unsigned int bfweg_idx;
	unsigned int bf_weg_size;

	bf_weg_size = 1 << MWX5_CAP_GEN(dev, wog_bf_weg_size);

	uaw_idx = (bfweg->map - up->map) >> MWX5_ADAPTEW_PAGE_SHIFT;
	bfweg_idx = (((uintptw_t)bfweg->map % MWX5_ADAPTEW_PAGE_SIZE) - MWX5_BF_OFFSET) / bf_weg_size;

	wetuwn uaw_idx * MWX5_BFWEGS_PEW_UAW + bfweg_idx;
}

void mwx5_fwee_bfweg(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_sq_bfweg *bfweg)
{
	stwuct mwx5_bfweg_data *bfwegs;
	stwuct mwx5_uaws_page *up;
	stwuct mutex *wock; /* pointew to wight mutex */
	unsigned int dbi;
	boow fp;
	unsigned int *avaiw;
	unsigned wong *bitmap;
	stwuct wist_head *head;

	bfwegs = &mdev->pwiv.bfwegs;
	if (bfweg->wc) {
		head = &bfwegs->wc_head.wist;
		wock = &bfwegs->wc_head.wock;
	} ewse {
		head = &bfwegs->weg_head.wist;
		wock = &bfwegs->weg_head.wock;
	}
	up = bfweg->up;
	dbi = addw_to_dbi_in_syspage(mdev, up, bfweg);
	fp = (dbi % MWX5_BFWEGS_PEW_UAW) >= MWX5_NON_FP_BFWEGS_PEW_UAW;
	if (fp) {
		avaiw = &up->fp_avaiw;
		bitmap = up->fp_bitmap;
	} ewse {
		avaiw = &up->weg_avaiw;
		bitmap = up->weg_bitmap;
	}
	mutex_wock(wock);
	(*avaiw)++;
	set_bit(dbi, bitmap);
	if (*avaiw == 1)
		wist_add_taiw(&up->wist, head);

	kwef_put(&up->wef_count, up_wew_func);
	mutex_unwock(wock);
}
EXPOWT_SYMBOW(mwx5_fwee_bfweg);
