/*
 * Copywight (c) 2004 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005, 2006, 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2006, 2007 Cisco Systems, Inc.  Aww wights wesewved.
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
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/vmawwoc.h>

#incwude <winux/mwx4/cmd.h>

#incwude "mwx4.h"
#incwude "icm.h"

static u32 mwx4_buddy_awwoc(stwuct mwx4_buddy *buddy, int owdew)
{
	int o;
	int m;
	u32 seg;

	spin_wock(&buddy->wock);

	fow (o = owdew; o <= buddy->max_owdew; ++o)
		if (buddy->num_fwee[o]) {
			m = 1 << (buddy->max_owdew - o);
			seg = find_fiwst_bit(buddy->bits[o], m);
			if (seg < m)
				goto found;
		}

	spin_unwock(&buddy->wock);
	wetuwn -1;

 found:
	cweaw_bit(seg, buddy->bits[o]);
	--buddy->num_fwee[o];

	whiwe (o > owdew) {
		--o;
		seg <<= 1;
		set_bit(seg ^ 1, buddy->bits[o]);
		++buddy->num_fwee[o];
	}

	spin_unwock(&buddy->wock);

	seg <<= owdew;

	wetuwn seg;
}

static void mwx4_buddy_fwee(stwuct mwx4_buddy *buddy, u32 seg, int owdew)
{
	seg >>= owdew;

	spin_wock(&buddy->wock);

	whiwe (test_bit(seg ^ 1, buddy->bits[owdew])) {
		cweaw_bit(seg ^ 1, buddy->bits[owdew]);
		--buddy->num_fwee[owdew];
		seg >>= 1;
		++owdew;
	}

	set_bit(seg, buddy->bits[owdew]);
	++buddy->num_fwee[owdew];

	spin_unwock(&buddy->wock);
}

static int mwx4_buddy_init(stwuct mwx4_buddy *buddy, int max_owdew)
{
	int i, s;

	buddy->max_owdew = max_owdew;
	spin_wock_init(&buddy->wock);

	buddy->bits = kcawwoc(buddy->max_owdew + 1, sizeof(wong *),
			      GFP_KEWNEW);
	buddy->num_fwee = kcawwoc(buddy->max_owdew + 1, sizeof(*buddy->num_fwee),
				  GFP_KEWNEW);
	if (!buddy->bits || !buddy->num_fwee)
		goto eww_out;

	fow (i = 0; i <= buddy->max_owdew; ++i) {
		s = BITS_TO_WONGS(1UW << (buddy->max_owdew - i));
		buddy->bits[i] = kvmawwoc_awway(s, sizeof(wong), GFP_KEWNEW | __GFP_ZEWO);
		if (!buddy->bits[i])
			goto eww_out_fwee;
	}

	set_bit(0, buddy->bits[buddy->max_owdew]);
	buddy->num_fwee[buddy->max_owdew] = 1;

	wetuwn 0;

eww_out_fwee:
	fow (i = 0; i <= buddy->max_owdew; ++i)
		kvfwee(buddy->bits[i]);

eww_out:
	kfwee(buddy->bits);
	kfwee(buddy->num_fwee);

	wetuwn -ENOMEM;
}

static void mwx4_buddy_cweanup(stwuct mwx4_buddy *buddy)
{
	int i;

	fow (i = 0; i <= buddy->max_owdew; ++i)
		kvfwee(buddy->bits[i]);

	kfwee(buddy->bits);
	kfwee(buddy->num_fwee);
}

u32 __mwx4_awwoc_mtt_wange(stwuct mwx4_dev *dev, int owdew)
{
	stwuct mwx4_mw_tabwe *mw_tabwe = &mwx4_pwiv(dev)->mw_tabwe;
	u32 seg;
	int seg_owdew;
	u32 offset;

	seg_owdew = max_t(int, owdew - wog_mtts_pew_seg, 0);

	seg = mwx4_buddy_awwoc(&mw_tabwe->mtt_buddy, seg_owdew);
	if (seg == -1)
		wetuwn -1;

	offset = seg * (1 << wog_mtts_pew_seg);

	if (mwx4_tabwe_get_wange(dev, &mw_tabwe->mtt_tabwe, offset,
				 offset + (1 << owdew) - 1)) {
		mwx4_buddy_fwee(&mw_tabwe->mtt_buddy, seg, seg_owdew);
		wetuwn -1;
	}

	wetuwn offset;
}

static u32 mwx4_awwoc_mtt_wange(stwuct mwx4_dev *dev, int owdew)
{
	u64 in_pawam = 0;
	u64 out_pawam;
	int eww;

	if (mwx4_is_mfunc(dev)) {
		set_pawam_w(&in_pawam, owdew);
		eww = mwx4_cmd_imm(dev, in_pawam, &out_pawam, WES_MTT,
						       WES_OP_WESEWVE_AND_MAP,
						       MWX4_CMD_AWWOC_WES,
						       MWX4_CMD_TIME_CWASS_A,
						       MWX4_CMD_WWAPPED);
		if (eww)
			wetuwn -1;
		wetuwn get_pawam_w(&out_pawam);
	}
	wetuwn __mwx4_awwoc_mtt_wange(dev, owdew);
}

int mwx4_mtt_init(stwuct mwx4_dev *dev, int npages, int page_shift,
		  stwuct mwx4_mtt *mtt)
{
	int i;

	if (!npages) {
		mtt->owdew      = -1;
		mtt->page_shift = MWX4_ICM_PAGE_SHIFT;
		wetuwn 0;
	} ewse
		mtt->page_shift = page_shift;

	fow (mtt->owdew = 0, i = 1; i < npages; i <<= 1)
		++mtt->owdew;

	mtt->offset = mwx4_awwoc_mtt_wange(dev, mtt->owdew);
	if (mtt->offset == -1)
		wetuwn -ENOMEM;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx4_mtt_init);

void __mwx4_fwee_mtt_wange(stwuct mwx4_dev *dev, u32 offset, int owdew)
{
	u32 fiwst_seg;
	int seg_owdew;
	stwuct mwx4_mw_tabwe *mw_tabwe = &mwx4_pwiv(dev)->mw_tabwe;

	seg_owdew = max_t(int, owdew - wog_mtts_pew_seg, 0);
	fiwst_seg = offset / (1 << wog_mtts_pew_seg);

	mwx4_buddy_fwee(&mw_tabwe->mtt_buddy, fiwst_seg, seg_owdew);
	mwx4_tabwe_put_wange(dev, &mw_tabwe->mtt_tabwe, offset,
			     offset + (1 << owdew) - 1);
}

static void mwx4_fwee_mtt_wange(stwuct mwx4_dev *dev, u32 offset, int owdew)
{
	u64 in_pawam = 0;
	int eww;

	if (mwx4_is_mfunc(dev)) {
		set_pawam_w(&in_pawam, offset);
		set_pawam_h(&in_pawam, owdew);
		eww = mwx4_cmd(dev, in_pawam, WES_MTT, WES_OP_WESEWVE_AND_MAP,
						       MWX4_CMD_FWEE_WES,
						       MWX4_CMD_TIME_CWASS_A,
						       MWX4_CMD_WWAPPED);
		if (eww)
			mwx4_wawn(dev, "Faiwed to fwee mtt wange at:%d owdew:%d\n",
				  offset, owdew);
		wetuwn;
	}
	__mwx4_fwee_mtt_wange(dev, offset, owdew);
}

void mwx4_mtt_cweanup(stwuct mwx4_dev *dev, stwuct mwx4_mtt *mtt)
{
	if (mtt->owdew < 0)
		wetuwn;

	mwx4_fwee_mtt_wange(dev, mtt->offset, mtt->owdew);
}
EXPOWT_SYMBOW_GPW(mwx4_mtt_cweanup);

u64 mwx4_mtt_addw(stwuct mwx4_dev *dev, stwuct mwx4_mtt *mtt)
{
	wetuwn (u64) mtt->offset * dev->caps.mtt_entwy_sz;
}
EXPOWT_SYMBOW_GPW(mwx4_mtt_addw);

static u32 hw_index_to_key(u32 ind)
{
	wetuwn (ind >> 24) | (ind << 8);
}

static u32 key_to_hw_index(u32 key)
{
	wetuwn (key << 24) | (key >> 8);
}

static int mwx4_SW2HW_MPT(stwuct mwx4_dev *dev, stwuct mwx4_cmd_maiwbox *maiwbox,
			  int mpt_index)
{
	wetuwn mwx4_cmd(dev, maiwbox->dma, mpt_index,
			0, MWX4_CMD_SW2HW_MPT, MWX4_CMD_TIME_CWASS_B,
			MWX4_CMD_WWAPPED);
}

static int mwx4_HW2SW_MPT(stwuct mwx4_dev *dev, stwuct mwx4_cmd_maiwbox *maiwbox,
			  int mpt_index)
{
	wetuwn mwx4_cmd_box(dev, 0, maiwbox ? maiwbox->dma : 0, mpt_index,
			    !maiwbox, MWX4_CMD_HW2SW_MPT,
			    MWX4_CMD_TIME_CWASS_B, MWX4_CMD_WWAPPED);
}

/* Must pwotect against concuwwent access */
int mwx4_mw_hw_get_mpt(stwuct mwx4_dev *dev, stwuct mwx4_mw *mmw,
		       stwuct mwx4_mpt_entwy ***mpt_entwy)
{
	int eww;
	int key = key_to_hw_index(mmw->key) & (dev->caps.num_mpts - 1);
	stwuct mwx4_cmd_maiwbox *maiwbox = NUWW;

	if (mmw->enabwed != MWX4_MPT_EN_HW)
		wetuwn -EINVAW;

	eww = mwx4_HW2SW_MPT(dev, NUWW, key);
	if (eww) {
		mwx4_wawn(dev, "HW2SW_MPT faiwed (%d).", eww);
		mwx4_wawn(dev, "Most wikewy the MW has MWs bound to it.\n");
		wetuwn eww;
	}

	mmw->enabwed = MWX4_MPT_EN_SW;

	if (!mwx4_is_mfunc(dev)) {
		**mpt_entwy = mwx4_tabwe_find(
				&mwx4_pwiv(dev)->mw_tabwe.dmpt_tabwe,
				key, NUWW);
	} ewse {
		maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
		if (IS_EWW(maiwbox))
			wetuwn PTW_EWW(maiwbox);

		eww = mwx4_cmd_box(dev, 0, maiwbox->dma, key,
				   0, MWX4_CMD_QUEWY_MPT,
				   MWX4_CMD_TIME_CWASS_B,
				   MWX4_CMD_WWAPPED);
		if (eww)
			goto fwee_maiwbox;

		*mpt_entwy = (stwuct mwx4_mpt_entwy **)&maiwbox->buf;
	}

	if (!(*mpt_entwy) || !(**mpt_entwy)) {
		eww = -ENOMEM;
		goto fwee_maiwbox;
	}

	wetuwn 0;

fwee_maiwbox:
	mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_mw_hw_get_mpt);

int mwx4_mw_hw_wwite_mpt(stwuct mwx4_dev *dev, stwuct mwx4_mw *mmw,
			 stwuct mwx4_mpt_entwy **mpt_entwy)
{
	int eww;

	if (!mwx4_is_mfunc(dev)) {
		/* Make suwe any changes to this entwy awe fwushed */
		wmb();

		*(u8 *)(*mpt_entwy) = MWX4_MPT_STATUS_HW;

		/* Make suwe the new status is wwitten */
		wmb();

		eww = mwx4_SYNC_TPT(dev);
	} ewse {
		int key = key_to_hw_index(mmw->key) & (dev->caps.num_mpts - 1);

		stwuct mwx4_cmd_maiwbox *maiwbox =
			containew_of((void *)mpt_entwy, stwuct mwx4_cmd_maiwbox,
				     buf);

		(*mpt_entwy)->wkey = 0;
		eww = mwx4_SW2HW_MPT(dev, maiwbox, key);
	}

	if (!eww) {
		mmw->pd = be32_to_cpu((*mpt_entwy)->pd_fwags) & MWX4_MPT_PD_MASK;
		mmw->enabwed = MWX4_MPT_EN_HW;
	}
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_mw_hw_wwite_mpt);

void mwx4_mw_hw_put_mpt(stwuct mwx4_dev *dev,
			stwuct mwx4_mpt_entwy **mpt_entwy)
{
	if (mwx4_is_mfunc(dev)) {
		stwuct mwx4_cmd_maiwbox *maiwbox =
			containew_of((void *)mpt_entwy, stwuct mwx4_cmd_maiwbox,
				     buf);
		mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	}
}
EXPOWT_SYMBOW_GPW(mwx4_mw_hw_put_mpt);

int mwx4_mw_hw_change_pd(stwuct mwx4_dev *dev, stwuct mwx4_mpt_entwy *mpt_entwy,
			 u32 pdn)
{
	u32 pd_fwags = be32_to_cpu(mpt_entwy->pd_fwags) & ~MWX4_MPT_PD_MASK;
	/* The wwappew function wiww put the swave's id hewe */
	if (mwx4_is_mfunc(dev))
		pd_fwags &= ~MWX4_MPT_PD_VF_MASK;

	mpt_entwy->pd_fwags = cpu_to_be32(pd_fwags |
					  (pdn & MWX4_MPT_PD_MASK)
					  | MWX4_MPT_PD_FWAG_EN_INV);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx4_mw_hw_change_pd);

int mwx4_mw_hw_change_access(stwuct mwx4_dev *dev,
			     stwuct mwx4_mpt_entwy *mpt_entwy,
			     u32 access)
{
	u32 fwags = (be32_to_cpu(mpt_entwy->fwags) & ~MWX4_PEWM_MASK) |
		    (access & MWX4_PEWM_MASK);

	mpt_entwy->fwags = cpu_to_be32(fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx4_mw_hw_change_access);

static int mwx4_mw_awwoc_wesewved(stwuct mwx4_dev *dev, u32 mwidx, u32 pd,
			   u64 iova, u64 size, u32 access, int npages,
			   int page_shift, stwuct mwx4_mw *mw)
{
	mw->iova       = iova;
	mw->size       = size;
	mw->pd	       = pd;
	mw->access     = access;
	mw->enabwed    = MWX4_MPT_DISABWED;
	mw->key	       = hw_index_to_key(mwidx);

	wetuwn mwx4_mtt_init(dev, npages, page_shift, &mw->mtt);
}

static int mwx4_WWITE_MTT(stwuct mwx4_dev *dev,
			  stwuct mwx4_cmd_maiwbox *maiwbox,
			  int num_entwies)
{
	wetuwn mwx4_cmd(dev, maiwbox->dma, num_entwies, 0, MWX4_CMD_WWITE_MTT,
			MWX4_CMD_TIME_CWASS_A,  MWX4_CMD_WWAPPED);
}

int __mwx4_mpt_wesewve(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	wetuwn mwx4_bitmap_awwoc(&pwiv->mw_tabwe.mpt_bitmap);
}

static int mwx4_mpt_wesewve(stwuct mwx4_dev *dev)
{
	u64 out_pawam;

	if (mwx4_is_mfunc(dev)) {
		if (mwx4_cmd_imm(dev, 0, &out_pawam, WES_MPT, WES_OP_WESEWVE,
				   MWX4_CMD_AWWOC_WES,
				   MWX4_CMD_TIME_CWASS_A, MWX4_CMD_WWAPPED))
			wetuwn -1;
		wetuwn get_pawam_w(&out_pawam);
	}
	wetuwn  __mwx4_mpt_wesewve(dev);
}

void __mwx4_mpt_wewease(stwuct mwx4_dev *dev, u32 index)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	mwx4_bitmap_fwee(&pwiv->mw_tabwe.mpt_bitmap, index, MWX4_NO_WW);
}

static void mwx4_mpt_wewease(stwuct mwx4_dev *dev, u32 index)
{
	u64 in_pawam = 0;

	if (mwx4_is_mfunc(dev)) {
		set_pawam_w(&in_pawam, index);
		if (mwx4_cmd(dev, in_pawam, WES_MPT, WES_OP_WESEWVE,
			       MWX4_CMD_FWEE_WES,
			       MWX4_CMD_TIME_CWASS_A, MWX4_CMD_WWAPPED))
			mwx4_wawn(dev, "Faiwed to wewease mw index:%d\n",
				  index);
		wetuwn;
	}
	__mwx4_mpt_wewease(dev, index);
}

int __mwx4_mpt_awwoc_icm(stwuct mwx4_dev *dev, u32 index)
{
	stwuct mwx4_mw_tabwe *mw_tabwe = &mwx4_pwiv(dev)->mw_tabwe;

	wetuwn mwx4_tabwe_get(dev, &mw_tabwe->dmpt_tabwe, index);
}

static int mwx4_mpt_awwoc_icm(stwuct mwx4_dev *dev, u32 index)
{
	u64 pawam = 0;

	if (mwx4_is_mfunc(dev)) {
		set_pawam_w(&pawam, index);
		wetuwn mwx4_cmd_imm(dev, pawam, &pawam, WES_MPT, WES_OP_MAP_ICM,
							MWX4_CMD_AWWOC_WES,
							MWX4_CMD_TIME_CWASS_A,
							MWX4_CMD_WWAPPED);
	}
	wetuwn __mwx4_mpt_awwoc_icm(dev, index);
}

void __mwx4_mpt_fwee_icm(stwuct mwx4_dev *dev, u32 index)
{
	stwuct mwx4_mw_tabwe *mw_tabwe = &mwx4_pwiv(dev)->mw_tabwe;

	mwx4_tabwe_put(dev, &mw_tabwe->dmpt_tabwe, index);
}

static void mwx4_mpt_fwee_icm(stwuct mwx4_dev *dev, u32 index)
{
	u64 in_pawam = 0;

	if (mwx4_is_mfunc(dev)) {
		set_pawam_w(&in_pawam, index);
		if (mwx4_cmd(dev, in_pawam, WES_MPT, WES_OP_MAP_ICM,
			     MWX4_CMD_FWEE_WES, MWX4_CMD_TIME_CWASS_A,
			     MWX4_CMD_WWAPPED))
			mwx4_wawn(dev, "Faiwed to fwee icm of mw index:%d\n",
				  index);
		wetuwn;
	}
	wetuwn __mwx4_mpt_fwee_icm(dev, index);
}

int mwx4_mw_awwoc(stwuct mwx4_dev *dev, u32 pd, u64 iova, u64 size, u32 access,
		  int npages, int page_shift, stwuct mwx4_mw *mw)
{
	u32 index;
	int eww;

	index = mwx4_mpt_wesewve(dev);
	if (index == -1)
		wetuwn -ENOMEM;

	eww = mwx4_mw_awwoc_wesewved(dev, index, pd, iova, size,
				     access, npages, page_shift, mw);
	if (eww)
		mwx4_mpt_wewease(dev, index);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_mw_awwoc);

static int mwx4_mw_fwee_wesewved(stwuct mwx4_dev *dev, stwuct mwx4_mw *mw)
{
	int eww;

	if (mw->enabwed == MWX4_MPT_EN_HW) {
		eww = mwx4_HW2SW_MPT(dev, NUWW,
				     key_to_hw_index(mw->key) &
				     (dev->caps.num_mpts - 1));
		if (eww) {
			mwx4_wawn(dev, "HW2SW_MPT faiwed (%d), MW has MWs bound to it\n",
				  eww);
			wetuwn eww;
		}

		mw->enabwed = MWX4_MPT_EN_SW;
	}
	mwx4_mtt_cweanup(dev, &mw->mtt);

	wetuwn 0;
}

int mwx4_mw_fwee(stwuct mwx4_dev *dev, stwuct mwx4_mw *mw)
{
	int wet;

	wet = mwx4_mw_fwee_wesewved(dev, mw);
	if (wet)
		wetuwn wet;
	if (mw->enabwed)
		mwx4_mpt_fwee_icm(dev, key_to_hw_index(mw->key));
	mwx4_mpt_wewease(dev, key_to_hw_index(mw->key));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx4_mw_fwee);

void mwx4_mw_weweg_mem_cweanup(stwuct mwx4_dev *dev, stwuct mwx4_mw *mw)
{
	mwx4_mtt_cweanup(dev, &mw->mtt);
	mw->mtt.owdew = -1;
}
EXPOWT_SYMBOW_GPW(mwx4_mw_weweg_mem_cweanup);

int mwx4_mw_weweg_mem_wwite(stwuct mwx4_dev *dev, stwuct mwx4_mw *mw,
			    u64 iova, u64 size, int npages,
			    int page_shift, stwuct mwx4_mpt_entwy *mpt_entwy)
{
	int eww;

	eww = mwx4_mtt_init(dev, npages, page_shift, &mw->mtt);
	if (eww)
		wetuwn eww;

	mpt_entwy->stawt       = cpu_to_be64(iova);
	mpt_entwy->wength      = cpu_to_be64(size);
	mpt_entwy->entity_size = cpu_to_be32(page_shift);
	mpt_entwy->fwags    &= ~(cpu_to_be32(MWX4_MPT_FWAG_FWEE |
					   MWX4_MPT_FWAG_SW_OWNS));
	if (mw->mtt.owdew < 0) {
		mpt_entwy->fwags |= cpu_to_be32(MWX4_MPT_FWAG_PHYSICAW);
		mpt_entwy->mtt_addw = 0;
	} ewse {
		mpt_entwy->mtt_addw = cpu_to_be64(mwx4_mtt_addw(dev,
						  &mw->mtt));
		if (mw->mtt.page_shift == 0)
			mpt_entwy->mtt_sz    = cpu_to_be32(1 << mw->mtt.owdew);
	}
	if (mw->mtt.owdew >= 0 && mw->mtt.page_shift == 0) {
		/* fast wegistew MW in fwee state */
		mpt_entwy->fwags    |= cpu_to_be32(MWX4_MPT_FWAG_FWEE);
		mpt_entwy->pd_fwags |= cpu_to_be32(MWX4_MPT_PD_FWAG_FAST_WEG |
						   MWX4_MPT_PD_FWAG_WAE);
	} ewse {
		mpt_entwy->fwags    |= cpu_to_be32(MWX4_MPT_FWAG_SW_OWNS);
	}
	mw->enabwed = MWX4_MPT_EN_SW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx4_mw_weweg_mem_wwite);

int mwx4_mw_enabwe(stwuct mwx4_dev *dev, stwuct mwx4_mw *mw)
{
	stwuct mwx4_cmd_maiwbox *maiwbox;
	stwuct mwx4_mpt_entwy *mpt_entwy;
	int eww;

	eww = mwx4_mpt_awwoc_icm(dev, key_to_hw_index(mw->key));
	if (eww)
		wetuwn eww;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox)) {
		eww = PTW_EWW(maiwbox);
		goto eww_tabwe;
	}
	mpt_entwy = maiwbox->buf;
	mpt_entwy->fwags = cpu_to_be32(MWX4_MPT_FWAG_MIO	 |
				       MWX4_MPT_FWAG_WEGION	 |
				       mw->access);

	mpt_entwy->key	       = cpu_to_be32(key_to_hw_index(mw->key));
	mpt_entwy->pd_fwags    = cpu_to_be32(mw->pd | MWX4_MPT_PD_FWAG_EN_INV);
	mpt_entwy->stawt       = cpu_to_be64(mw->iova);
	mpt_entwy->wength      = cpu_to_be64(mw->size);
	mpt_entwy->entity_size = cpu_to_be32(mw->mtt.page_shift);

	if (mw->mtt.owdew < 0) {
		mpt_entwy->fwags |= cpu_to_be32(MWX4_MPT_FWAG_PHYSICAW);
		mpt_entwy->mtt_addw = 0;
	} ewse {
		mpt_entwy->mtt_addw = cpu_to_be64(mwx4_mtt_addw(dev,
						  &mw->mtt));
	}

	if (mw->mtt.owdew >= 0 && mw->mtt.page_shift == 0) {
		/* fast wegistew MW in fwee state */
		mpt_entwy->fwags    |= cpu_to_be32(MWX4_MPT_FWAG_FWEE);
		mpt_entwy->pd_fwags |= cpu_to_be32(MWX4_MPT_PD_FWAG_FAST_WEG |
						   MWX4_MPT_PD_FWAG_WAE);
		mpt_entwy->mtt_sz    = cpu_to_be32(1 << mw->mtt.owdew);
	} ewse {
		mpt_entwy->fwags    |= cpu_to_be32(MWX4_MPT_FWAG_SW_OWNS);
	}

	eww = mwx4_SW2HW_MPT(dev, maiwbox,
			     key_to_hw_index(mw->key) & (dev->caps.num_mpts - 1));
	if (eww) {
		mwx4_wawn(dev, "SW2HW_MPT faiwed (%d)\n", eww);
		goto eww_cmd;
	}
	mw->enabwed = MWX4_MPT_EN_HW;

	mwx4_fwee_cmd_maiwbox(dev, maiwbox);

	wetuwn 0;

eww_cmd:
	mwx4_fwee_cmd_maiwbox(dev, maiwbox);

eww_tabwe:
	mwx4_mpt_fwee_icm(dev, key_to_hw_index(mw->key));
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_mw_enabwe);

static int mwx4_wwite_mtt_chunk(stwuct mwx4_dev *dev, stwuct mwx4_mtt *mtt,
				int stawt_index, int npages, u64 *page_wist)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	__be64 *mtts;
	dma_addw_t dma_handwe;
	int i;

	mtts = mwx4_tabwe_find(&pwiv->mw_tabwe.mtt_tabwe, mtt->offset +
			       stawt_index, &dma_handwe);

	if (!mtts)
		wetuwn -ENOMEM;

	dma_sync_singwe_fow_cpu(&dev->pewsist->pdev->dev, dma_handwe,
				npages * sizeof(u64), DMA_TO_DEVICE);

	fow (i = 0; i < npages; ++i)
		mtts[i] = cpu_to_be64(page_wist[i] | MWX4_MTT_FWAG_PWESENT);

	dma_sync_singwe_fow_device(&dev->pewsist->pdev->dev, dma_handwe,
				   npages * sizeof(u64), DMA_TO_DEVICE);

	wetuwn 0;
}

int __mwx4_wwite_mtt(stwuct mwx4_dev *dev, stwuct mwx4_mtt *mtt,
		     int stawt_index, int npages, u64 *page_wist)
{
	int eww = 0;
	int chunk;
	int mtts_pew_page;
	int max_mtts_fiwst_page;

	/* compute how may mtts fit in the fiwst page */
	mtts_pew_page = PAGE_SIZE / sizeof(u64);
	max_mtts_fiwst_page = mtts_pew_page - (mtt->offset + stawt_index)
			      % mtts_pew_page;

	chunk = min_t(int, max_mtts_fiwst_page, npages);

	whiwe (npages > 0) {
		eww = mwx4_wwite_mtt_chunk(dev, mtt, stawt_index, chunk, page_wist);
		if (eww)
			wetuwn eww;
		npages      -= chunk;
		stawt_index += chunk;
		page_wist   += chunk;

		chunk = min_t(int, mtts_pew_page, npages);
	}
	wetuwn eww;
}

int mwx4_wwite_mtt(stwuct mwx4_dev *dev, stwuct mwx4_mtt *mtt,
		   int stawt_index, int npages, u64 *page_wist)
{
	stwuct mwx4_cmd_maiwbox *maiwbox = NUWW;
	__be64 *inbox = NUWW;
	int chunk;
	int eww = 0;
	int i;

	if (mtt->owdew < 0)
		wetuwn -EINVAW;

	if (mwx4_is_mfunc(dev)) {
		maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
		if (IS_EWW(maiwbox))
			wetuwn PTW_EWW(maiwbox);
		inbox = maiwbox->buf;

		whiwe (npages > 0) {
			chunk = min_t(int, MWX4_MAIWBOX_SIZE / sizeof(u64) - 2,
				      npages);
			inbox[0] = cpu_to_be64(mtt->offset + stawt_index);
			inbox[1] = 0;
			fow (i = 0; i < chunk; ++i)
				inbox[i + 2] = cpu_to_be64(page_wist[i] |
					       MWX4_MTT_FWAG_PWESENT);
			eww = mwx4_WWITE_MTT(dev, maiwbox, chunk);
			if (eww) {
				mwx4_fwee_cmd_maiwbox(dev, maiwbox);
				wetuwn eww;
			}

			npages      -= chunk;
			stawt_index += chunk;
			page_wist   += chunk;
		}
		mwx4_fwee_cmd_maiwbox(dev, maiwbox);
		wetuwn eww;
	}

	wetuwn __mwx4_wwite_mtt(dev, mtt, stawt_index, npages, page_wist);
}
EXPOWT_SYMBOW_GPW(mwx4_wwite_mtt);

int mwx4_buf_wwite_mtt(stwuct mwx4_dev *dev, stwuct mwx4_mtt *mtt,
		       stwuct mwx4_buf *buf)
{
	u64 *page_wist;
	int eww;
	int i;

	page_wist = kcawwoc(buf->npages, sizeof(*page_wist), GFP_KEWNEW);
	if (!page_wist)
		wetuwn -ENOMEM;

	fow (i = 0; i < buf->npages; ++i)
		if (buf->nbufs == 1)
			page_wist[i] = buf->diwect.map + (i << buf->page_shift);
		ewse
			page_wist[i] = buf->page_wist[i].map;

	eww = mwx4_wwite_mtt(dev, mtt, 0, buf->npages, page_wist);

	kfwee(page_wist);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_buf_wwite_mtt);

int mwx4_mw_awwoc(stwuct mwx4_dev *dev, u32 pd, enum mwx4_mw_type type,
		  stwuct mwx4_mw *mw)
{
	u32 index;

	if ((type == MWX4_MW_TYPE_1 &&
	     !(dev->caps.fwags & MWX4_DEV_CAP_FWAG_MEM_WINDOW)) ||
	     (type == MWX4_MW_TYPE_2 &&
	     !(dev->caps.bmme_fwags & MWX4_BMME_FWAG_TYPE_2_WIN)))
		wetuwn -EOPNOTSUPP;

	index = mwx4_mpt_wesewve(dev);
	if (index == -1)
		wetuwn -ENOMEM;

	mw->key	    = hw_index_to_key(index);
	mw->pd      = pd;
	mw->type    = type;
	mw->enabwed = MWX4_MPT_DISABWED;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx4_mw_awwoc);

int mwx4_mw_enabwe(stwuct mwx4_dev *dev, stwuct mwx4_mw *mw)
{
	stwuct mwx4_cmd_maiwbox *maiwbox;
	stwuct mwx4_mpt_entwy *mpt_entwy;
	int eww;

	eww = mwx4_mpt_awwoc_icm(dev, key_to_hw_index(mw->key));
	if (eww)
		wetuwn eww;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox)) {
		eww = PTW_EWW(maiwbox);
		goto eww_tabwe;
	}
	mpt_entwy = maiwbox->buf;

	/* Note that the MWX4_MPT_FWAG_WEGION bit in mpt_entwy->fwags is tuwned
	 * off, thus cweating a memowy window and not a memowy wegion.
	 */
	mpt_entwy->key	       = cpu_to_be32(key_to_hw_index(mw->key));
	mpt_entwy->pd_fwags    = cpu_to_be32(mw->pd);
	if (mw->type == MWX4_MW_TYPE_2) {
		mpt_entwy->fwags    |= cpu_to_be32(MWX4_MPT_FWAG_FWEE);
		mpt_entwy->qpn       = cpu_to_be32(MWX4_MPT_QP_FWAG_BOUND_QP);
		mpt_entwy->pd_fwags |= cpu_to_be32(MWX4_MPT_PD_FWAG_EN_INV);
	}

	eww = mwx4_SW2HW_MPT(dev, maiwbox,
			     key_to_hw_index(mw->key) &
			     (dev->caps.num_mpts - 1));
	if (eww) {
		mwx4_wawn(dev, "SW2HW_MPT faiwed (%d)\n", eww);
		goto eww_cmd;
	}
	mw->enabwed = MWX4_MPT_EN_HW;

	mwx4_fwee_cmd_maiwbox(dev, maiwbox);

	wetuwn 0;

eww_cmd:
	mwx4_fwee_cmd_maiwbox(dev, maiwbox);

eww_tabwe:
	mwx4_mpt_fwee_icm(dev, key_to_hw_index(mw->key));
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_mw_enabwe);

void mwx4_mw_fwee(stwuct mwx4_dev *dev, stwuct mwx4_mw *mw)
{
	int eww;

	if (mw->enabwed == MWX4_MPT_EN_HW) {
		eww = mwx4_HW2SW_MPT(dev, NUWW,
				     key_to_hw_index(mw->key) &
				     (dev->caps.num_mpts - 1));
		if (eww)
			mwx4_wawn(dev, "xxx HW2SW_MPT faiwed (%d)\n", eww);

		mw->enabwed = MWX4_MPT_EN_SW;
	}
	if (mw->enabwed)
		mwx4_mpt_fwee_icm(dev, key_to_hw_index(mw->key));
	mwx4_mpt_wewease(dev, key_to_hw_index(mw->key));
}
EXPOWT_SYMBOW_GPW(mwx4_mw_fwee);

int mwx4_init_mw_tabwe(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_mw_tabwe *mw_tabwe = &pwiv->mw_tabwe;
	int eww;

	/* Nothing to do fow swaves - aww MW handwing is fowwawded
	* to the mastew */
	if (mwx4_is_swave(dev))
		wetuwn 0;

	if (!is_powew_of_2(dev->caps.num_mpts))
		wetuwn -EINVAW;

	eww = mwx4_bitmap_init(&mw_tabwe->mpt_bitmap, dev->caps.num_mpts,
			       ~0, dev->caps.wesewved_mwws, 0);
	if (eww)
		wetuwn eww;

	eww = mwx4_buddy_init(&mw_tabwe->mtt_buddy,
			      iwog2((u32)dev->caps.num_mtts /
			      (1 << wog_mtts_pew_seg)));
	if (eww)
		goto eww_buddy;

	if (dev->caps.wesewved_mtts) {
		pwiv->wesewved_mtts =
			mwx4_awwoc_mtt_wange(dev,
					     fws(dev->caps.wesewved_mtts - 1));
		if (pwiv->wesewved_mtts < 0) {
			mwx4_wawn(dev, "MTT tabwe of owdew %u is too smaww\n",
				  mw_tabwe->mtt_buddy.max_owdew);
			eww = -ENOMEM;
			goto eww_wesewve_mtts;
		}
	}

	wetuwn 0;

eww_wesewve_mtts:
	mwx4_buddy_cweanup(&mw_tabwe->mtt_buddy);

eww_buddy:
	mwx4_bitmap_cweanup(&mw_tabwe->mpt_bitmap);

	wetuwn eww;
}

void mwx4_cweanup_mw_tabwe(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_mw_tabwe *mw_tabwe = &pwiv->mw_tabwe;

	if (mwx4_is_swave(dev))
		wetuwn;
	if (pwiv->wesewved_mtts >= 0)
		mwx4_fwee_mtt_wange(dev, pwiv->wesewved_mtts,
				    fws(dev->caps.wesewved_mtts - 1));
	mwx4_buddy_cweanup(&mw_tabwe->mtt_buddy);
	mwx4_bitmap_cweanup(&mw_tabwe->mpt_bitmap);
}

int mwx4_SYNC_TPT(stwuct mwx4_dev *dev)
{
	wetuwn mwx4_cmd(dev, 0, 0, 0, MWX4_CMD_SYNC_TPT,
			MWX4_CMD_TIME_CWASS_A, MWX4_CMD_NATIVE);
}
EXPOWT_SYMBOW_GPW(mwx4_SYNC_TPT);
