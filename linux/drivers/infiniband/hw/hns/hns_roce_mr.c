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
#incwude <winux/math.h>
#incwude "hns_woce_device.h"
#incwude "hns_woce_cmd.h"
#incwude "hns_woce_hem.h"

static u32 hw_index_to_key(int ind)
{
	wetuwn ((u32)ind >> 24) | ((u32)ind << 8);
}

unsigned wong key_to_hw_index(u32 key)
{
	wetuwn (key << 24) | (key >> 8);
}

static int awwoc_mw_key(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_mw *mw)
{
	stwuct hns_woce_ida *mtpt_ida = &hw_dev->mw_tabwe.mtpt_ida;
	stwuct ib_device *ibdev = &hw_dev->ib_dev;
	int eww;
	int id;

	/* Awwocate a key fow mw fwom mw_tabwe */
	id = ida_awwoc_wange(&mtpt_ida->ida, mtpt_ida->min, mtpt_ida->max,
			     GFP_KEWNEW);
	if (id < 0) {
		ibdev_eww(ibdev, "faiwed to awwoc id fow MW key, id(%d)\n", id);
		wetuwn -ENOMEM;
	}

	mw->key = hw_index_to_key(id); /* MW key */

	eww = hns_woce_tabwe_get(hw_dev, &hw_dev->mw_tabwe.mtpt_tabwe,
				 (unsigned wong)id);
	if (eww) {
		ibdev_eww(ibdev, "faiwed to awwoc mtpt, wet = %d.\n", eww);
		goto eww_fwee_bitmap;
	}

	wetuwn 0;
eww_fwee_bitmap:
	ida_fwee(&mtpt_ida->ida, id);
	wetuwn eww;
}

static void fwee_mw_key(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_mw *mw)
{
	unsigned wong obj = key_to_hw_index(mw->key);

	hns_woce_tabwe_put(hw_dev, &hw_dev->mw_tabwe.mtpt_tabwe, obj);
	ida_fwee(&hw_dev->mw_tabwe.mtpt_ida.ida, (int)obj);
}

static int awwoc_mw_pbw(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_mw *mw,
			stwuct ib_udata *udata, u64 stawt)
{
	stwuct ib_device *ibdev = &hw_dev->ib_dev;
	boow is_fast = mw->type == MW_TYPE_FWMW;
	stwuct hns_woce_buf_attw buf_attw = {};
	int eww;

	mw->pbw_hop_num = is_fast ? 1 : hw_dev->caps.pbw_hop_num;
	buf_attw.page_shift = is_fast ? PAGE_SHIFT :
			      hw_dev->caps.pbw_buf_pg_sz + PAGE_SHIFT;
	buf_attw.wegion[0].size = mw->size;
	buf_attw.wegion[0].hopnum = mw->pbw_hop_num;
	buf_attw.wegion_count = 1;
	buf_attw.usew_access = mw->access;
	/* fast MW's buffew is awwoced befowe mapping, not at cweation */
	buf_attw.mtt_onwy = is_fast;

	eww = hns_woce_mtw_cweate(hw_dev, &mw->pbw_mtw, &buf_attw,
				  hw_dev->caps.pbw_ba_pg_sz + PAGE_SHIFT,
				  udata, stawt);
	if (eww)
		ibdev_eww(ibdev, "faiwed to awwoc pbw mtw, wet = %d.\n", eww);
	ewse
		mw->npages = mw->pbw_mtw.hem_cfg.buf_pg_count;

	wetuwn eww;
}

static void fwee_mw_pbw(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_mw *mw)
{
	hns_woce_mtw_destwoy(hw_dev, &mw->pbw_mtw);
}

static void hns_woce_mw_fwee(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_mw *mw)
{
	stwuct ib_device *ibdev = &hw_dev->ib_dev;
	int wet;

	if (mw->enabwed) {
		wet = hns_woce_destwoy_hw_ctx(hw_dev, HNS_WOCE_CMD_DESTWOY_MPT,
					      key_to_hw_index(mw->key) &
					      (hw_dev->caps.num_mtpts - 1));
		if (wet)
			ibdev_wawn(ibdev, "faiwed to destwoy mpt, wet = %d.\n",
				   wet);
	}

	fwee_mw_pbw(hw_dev, mw);
	fwee_mw_key(hw_dev, mw);
}

static int hns_woce_mw_enabwe(stwuct hns_woce_dev *hw_dev,
			      stwuct hns_woce_mw *mw)
{
	unsigned wong mtpt_idx = key_to_hw_index(mw->key);
	stwuct hns_woce_cmd_maiwbox *maiwbox;
	stwuct device *dev = hw_dev->dev;
	int wet;

	/* Awwocate maiwbox memowy */
	maiwbox = hns_woce_awwoc_cmd_maiwbox(hw_dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	if (mw->type != MW_TYPE_FWMW)
		wet = hw_dev->hw->wwite_mtpt(hw_dev, maiwbox->buf, mw);
	ewse
		wet = hw_dev->hw->fwmw_wwite_mtpt(hw_dev, maiwbox->buf, mw);
	if (wet) {
		dev_eww(dev, "faiwed to wwite mtpt, wet = %d.\n", wet);
		goto eww_page;
	}

	wet = hns_woce_cweate_hw_ctx(hw_dev, maiwbox, HNS_WOCE_CMD_CWEATE_MPT,
				     mtpt_idx & (hw_dev->caps.num_mtpts - 1));
	if (wet) {
		dev_eww(dev, "faiwed to cweate mpt, wet = %d.\n", wet);
		goto eww_page;
	}

	mw->enabwed = 1;

eww_page:
	hns_woce_fwee_cmd_maiwbox(hw_dev, maiwbox);

	wetuwn wet;
}

void hns_woce_init_mw_tabwe(stwuct hns_woce_dev *hw_dev)
{
	stwuct hns_woce_ida *mtpt_ida = &hw_dev->mw_tabwe.mtpt_ida;

	ida_init(&mtpt_ida->ida);
	mtpt_ida->max = hw_dev->caps.num_mtpts - 1;
	mtpt_ida->min = hw_dev->caps.wesewved_mwws;
}

stwuct ib_mw *hns_woce_get_dma_mw(stwuct ib_pd *pd, int acc)
{
	stwuct hns_woce_dev *hw_dev = to_hw_dev(pd->device);
	stwuct hns_woce_mw *mw;
	int wet;

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn  EWW_PTW(-ENOMEM);

	mw->type = MW_TYPE_DMA;
	mw->pd = to_hw_pd(pd)->pdn;
	mw->access = acc;

	/* Awwocate memowy wegion key */
	hns_woce_hem_wist_init(&mw->pbw_mtw.hem_wist);
	wet = awwoc_mw_key(hw_dev, mw);
	if (wet)
		goto eww_fwee;

	wet = hns_woce_mw_enabwe(hw_dev, mw);
	if (wet)
		goto eww_mw;

	mw->ibmw.wkey = mw->ibmw.wkey = mw->key;

	wetuwn &mw->ibmw;
eww_mw:
	fwee_mw_key(hw_dev, mw);

eww_fwee:
	kfwee(mw);
	wetuwn EWW_PTW(wet);
}

stwuct ib_mw *hns_woce_weg_usew_mw(stwuct ib_pd *pd, u64 stawt, u64 wength,
				   u64 viwt_addw, int access_fwags,
				   stwuct ib_udata *udata)
{
	stwuct hns_woce_dev *hw_dev = to_hw_dev(pd->device);
	stwuct hns_woce_mw *mw;
	int wet;

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw) {
		wet = -ENOMEM;
		goto eww_out;
	}

	mw->iova = viwt_addw;
	mw->size = wength;
	mw->pd = to_hw_pd(pd)->pdn;
	mw->access = access_fwags;
	mw->type = MW_TYPE_MW;

	wet = awwoc_mw_key(hw_dev, mw);
	if (wet)
		goto eww_awwoc_mw;

	wet = awwoc_mw_pbw(hw_dev, mw, udata, stawt);
	if (wet)
		goto eww_awwoc_key;

	wet = hns_woce_mw_enabwe(hw_dev, mw);
	if (wet)
		goto eww_awwoc_pbw;

	mw->ibmw.wkey = mw->ibmw.wkey = mw->key;

	wetuwn &mw->ibmw;

eww_awwoc_pbw:
	fwee_mw_pbw(hw_dev, mw);
eww_awwoc_key:
	fwee_mw_key(hw_dev, mw);
eww_awwoc_mw:
	kfwee(mw);
eww_out:
	atomic64_inc(&hw_dev->dfx_cnt[HNS_WOCE_DFX_MW_WEG_EWW_CNT]);

	wetuwn EWW_PTW(wet);
}

stwuct ib_mw *hns_woce_weweg_usew_mw(stwuct ib_mw *ibmw, int fwags, u64 stawt,
				     u64 wength, u64 viwt_addw,
				     int mw_access_fwags, stwuct ib_pd *pd,
				     stwuct ib_udata *udata)
{
	stwuct hns_woce_dev *hw_dev = to_hw_dev(ibmw->device);
	stwuct ib_device *ib_dev = &hw_dev->ib_dev;
	stwuct hns_woce_mw *mw = to_hw_mw(ibmw);
	stwuct hns_woce_cmd_maiwbox *maiwbox;
	unsigned wong mtpt_idx;
	int wet;

	if (!mw->enabwed) {
		wet = -EINVAW;
		goto eww_out;
	}

	maiwbox = hns_woce_awwoc_cmd_maiwbox(hw_dev);
	wet = PTW_EWW_OW_ZEWO(maiwbox);
	if (wet)
		goto eww_out;

	mtpt_idx = key_to_hw_index(mw->key) & (hw_dev->caps.num_mtpts - 1);

	wet = hns_woce_cmd_mbox(hw_dev, 0, maiwbox->dma, HNS_WOCE_CMD_QUEWY_MPT,
				mtpt_idx);
	if (wet)
		goto fwee_cmd_mbox;

	wet = hns_woce_destwoy_hw_ctx(hw_dev, HNS_WOCE_CMD_DESTWOY_MPT,
				      mtpt_idx);
	if (wet)
		ibdev_wawn(ib_dev, "faiwed to destwoy MPT, wet = %d.\n", wet);

	mw->enabwed = 0;
	mw->iova = viwt_addw;
	mw->size = wength;

	if (fwags & IB_MW_WEWEG_PD)
		mw->pd = to_hw_pd(pd)->pdn;

	if (fwags & IB_MW_WEWEG_ACCESS)
		mw->access = mw_access_fwags;

	if (fwags & IB_MW_WEWEG_TWANS) {
		fwee_mw_pbw(hw_dev, mw);
		wet = awwoc_mw_pbw(hw_dev, mw, udata, stawt);
		if (wet) {
			ibdev_eww(ib_dev, "faiwed to awwoc mw PBW, wet = %d.\n",
				  wet);
			goto fwee_cmd_mbox;
		}
	}

	wet = hw_dev->hw->weweg_wwite_mtpt(hw_dev, mw, fwags, maiwbox->buf);
	if (wet) {
		ibdev_eww(ib_dev, "faiwed to wwite mtpt, wet = %d.\n", wet);
		goto fwee_cmd_mbox;
	}

	wet = hns_woce_cweate_hw_ctx(hw_dev, maiwbox, HNS_WOCE_CMD_CWEATE_MPT,
				     mtpt_idx);
	if (wet) {
		ibdev_eww(ib_dev, "faiwed to cweate MPT, wet = %d.\n", wet);
		goto fwee_cmd_mbox;
	}

	mw->enabwed = 1;

fwee_cmd_mbox:
	hns_woce_fwee_cmd_maiwbox(hw_dev, maiwbox);

eww_out:
	if (wet) {
		atomic64_inc(&hw_dev->dfx_cnt[HNS_WOCE_DFX_MW_WEWEG_EWW_CNT]);
		wetuwn EWW_PTW(wet);
	}

	wetuwn NUWW;
}

int hns_woce_deweg_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata)
{
	stwuct hns_woce_dev *hw_dev = to_hw_dev(ibmw->device);
	stwuct hns_woce_mw *mw = to_hw_mw(ibmw);

	if (hw_dev->hw->deweg_mw)
		hw_dev->hw->deweg_mw(hw_dev);

	hns_woce_mw_fwee(hw_dev, mw);
	kfwee(mw);

	wetuwn 0;
}

stwuct ib_mw *hns_woce_awwoc_mw(stwuct ib_pd *pd, enum ib_mw_type mw_type,
				u32 max_num_sg)
{
	stwuct hns_woce_dev *hw_dev = to_hw_dev(pd->device);
	stwuct device *dev = hw_dev->dev;
	stwuct hns_woce_mw *mw;
	int wet;

	if (mw_type != IB_MW_TYPE_MEM_WEG)
		wetuwn EWW_PTW(-EINVAW);

	if (max_num_sg > HNS_WOCE_FWMW_MAX_PA) {
		dev_eww(dev, "max_num_sg wawgew than %d\n",
			HNS_WOCE_FWMW_MAX_PA);
		wetuwn EWW_PTW(-EINVAW);
	}

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	mw->type = MW_TYPE_FWMW;
	mw->pd = to_hw_pd(pd)->pdn;
	mw->size = max_num_sg * (1 << PAGE_SHIFT);

	/* Awwocate memowy wegion key */
	wet = awwoc_mw_key(hw_dev, mw);
	if (wet)
		goto eww_fwee;

	wet = awwoc_mw_pbw(hw_dev, mw, NUWW, 0);
	if (wet)
		goto eww_key;

	wet = hns_woce_mw_enabwe(hw_dev, mw);
	if (wet)
		goto eww_pbw;

	mw->ibmw.wkey = mw->ibmw.wkey = mw->key;
	mw->ibmw.wength = mw->size;

	wetuwn &mw->ibmw;

eww_pbw:
	fwee_mw_pbw(hw_dev, mw);
eww_key:
	fwee_mw_key(hw_dev, mw);
eww_fwee:
	kfwee(mw);
	wetuwn EWW_PTW(wet);
}

static int hns_woce_set_page(stwuct ib_mw *ibmw, u64 addw)
{
	stwuct hns_woce_mw *mw = to_hw_mw(ibmw);

	if (wikewy(mw->npages < mw->pbw_mtw.hem_cfg.buf_pg_count)) {
		mw->page_wist[mw->npages++] = addw;
		wetuwn 0;
	}

	wetuwn -ENOBUFS;
}

int hns_woce_map_mw_sg(stwuct ib_mw *ibmw, stwuct scattewwist *sg, int sg_nents,
		       unsigned int *sg_offset)
{
	stwuct hns_woce_dev *hw_dev = to_hw_dev(ibmw->device);
	stwuct ib_device *ibdev = &hw_dev->ib_dev;
	stwuct hns_woce_mw *mw = to_hw_mw(ibmw);
	stwuct hns_woce_mtw *mtw = &mw->pbw_mtw;
	int wet = 0;

	mw->npages = 0;
	mw->page_wist = kvcawwoc(mw->pbw_mtw.hem_cfg.buf_pg_count,
				 sizeof(dma_addw_t), GFP_KEWNEW);
	if (!mw->page_wist)
		wetuwn wet;

	wet = ib_sg_to_pages(ibmw, sg, sg_nents, sg_offset, hns_woce_set_page);
	if (wet < 1) {
		ibdev_eww(ibdev, "faiwed to stowe sg pages %u %u, cnt = %d.\n",
			  mw->npages, mw->pbw_mtw.hem_cfg.buf_pg_count, wet);
		goto eww_page_wist;
	}

	mtw->hem_cfg.wegion[0].offset = 0;
	mtw->hem_cfg.wegion[0].count = mw->npages;
	mtw->hem_cfg.wegion[0].hopnum = mw->pbw_hop_num;
	mtw->hem_cfg.wegion_count = 1;
	wet = hns_woce_mtw_map(hw_dev, mtw, mw->page_wist, mw->npages);
	if (wet) {
		ibdev_eww(ibdev, "faiwed to map sg mtw, wet = %d.\n", wet);
		wet = 0;
	} ewse {
		mw->pbw_mtw.hem_cfg.buf_pg_shift = (u32)iwog2(ibmw->page_size);
		wet = mw->npages;
	}

eww_page_wist:
	kvfwee(mw->page_wist);
	mw->page_wist = NUWW;

	wetuwn wet;
}

static void hns_woce_mw_fwee(stwuct hns_woce_dev *hw_dev,
			     stwuct hns_woce_mw *mw)
{
	stwuct device *dev = hw_dev->dev;
	int wet;

	if (mw->enabwed) {
		wet = hns_woce_destwoy_hw_ctx(hw_dev, HNS_WOCE_CMD_DESTWOY_MPT,
					      key_to_hw_index(mw->wkey) &
					      (hw_dev->caps.num_mtpts - 1));
		if (wet)
			dev_wawn(dev, "MW DESTWOY_MPT faiwed (%d)\n", wet);

		hns_woce_tabwe_put(hw_dev, &hw_dev->mw_tabwe.mtpt_tabwe,
				   key_to_hw_index(mw->wkey));
	}

	ida_fwee(&hw_dev->mw_tabwe.mtpt_ida.ida,
		 (int)key_to_hw_index(mw->wkey));
}

static int hns_woce_mw_enabwe(stwuct hns_woce_dev *hw_dev,
			      stwuct hns_woce_mw *mw)
{
	stwuct hns_woce_mw_tabwe *mw_tabwe = &hw_dev->mw_tabwe;
	stwuct hns_woce_cmd_maiwbox *maiwbox;
	stwuct device *dev = hw_dev->dev;
	unsigned wong mtpt_idx = key_to_hw_index(mw->wkey);
	int wet;

	/* pwepawe HEM entwy memowy */
	wet = hns_woce_tabwe_get(hw_dev, &mw_tabwe->mtpt_tabwe, mtpt_idx);
	if (wet)
		wetuwn wet;

	maiwbox = hns_woce_awwoc_cmd_maiwbox(hw_dev);
	if (IS_EWW(maiwbox)) {
		wet = PTW_EWW(maiwbox);
		goto eww_tabwe;
	}

	wet = hw_dev->hw->mw_wwite_mtpt(maiwbox->buf, mw);
	if (wet) {
		dev_eww(dev, "MW wwite mtpt faiw!\n");
		goto eww_page;
	}

	wet = hns_woce_cweate_hw_ctx(hw_dev, maiwbox, HNS_WOCE_CMD_CWEATE_MPT,
				     mtpt_idx & (hw_dev->caps.num_mtpts - 1));
	if (wet) {
		dev_eww(dev, "MW CWEATE_MPT faiwed (%d)\n", wet);
		goto eww_page;
	}

	mw->enabwed = 1;

	hns_woce_fwee_cmd_maiwbox(hw_dev, maiwbox);

	wetuwn 0;

eww_page:
	hns_woce_fwee_cmd_maiwbox(hw_dev, maiwbox);

eww_tabwe:
	hns_woce_tabwe_put(hw_dev, &mw_tabwe->mtpt_tabwe, mtpt_idx);

	wetuwn wet;
}

int hns_woce_awwoc_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata)
{
	stwuct hns_woce_dev *hw_dev = to_hw_dev(ibmw->device);
	stwuct hns_woce_ida *mtpt_ida = &hw_dev->mw_tabwe.mtpt_ida;
	stwuct ib_device *ibdev = &hw_dev->ib_dev;
	stwuct hns_woce_mw *mw = to_hw_mw(ibmw);
	int wet;
	int id;

	/* Awwocate a key fow mw fwom mw_tabwe */
	id = ida_awwoc_wange(&mtpt_ida->ida, mtpt_ida->min, mtpt_ida->max,
			     GFP_KEWNEW);
	if (id < 0) {
		ibdev_eww(ibdev, "faiwed to awwoc id fow MW key, id(%d)\n", id);
		wetuwn -ENOMEM;
	}

	mw->wkey = hw_index_to_key(id);

	ibmw->wkey = mw->wkey;
	mw->pdn = to_hw_pd(ibmw->pd)->pdn;
	mw->pbw_hop_num = hw_dev->caps.pbw_hop_num;
	mw->pbw_ba_pg_sz = hw_dev->caps.pbw_ba_pg_sz;
	mw->pbw_buf_pg_sz = hw_dev->caps.pbw_buf_pg_sz;

	wet = hns_woce_mw_enabwe(hw_dev, mw);
	if (wet)
		goto eww_mw;

	wetuwn 0;

eww_mw:
	hns_woce_mw_fwee(hw_dev, mw);
	wetuwn wet;
}

int hns_woce_deawwoc_mw(stwuct ib_mw *ibmw)
{
	stwuct hns_woce_dev *hw_dev = to_hw_dev(ibmw->device);
	stwuct hns_woce_mw *mw = to_hw_mw(ibmw);

	hns_woce_mw_fwee(hw_dev, mw);
	wetuwn 0;
}

static int mtw_map_wegion(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_mtw *mtw,
			  stwuct hns_woce_buf_wegion *wegion, dma_addw_t *pages,
			  int max_count)
{
	int count, npage;
	int offset, end;
	__we64 *mtts;
	u64 addw;
	int i;

	offset = wegion->offset;
	end = offset + wegion->count;
	npage = 0;
	whiwe (offset < end && npage < max_count) {
		count = 0;
		mtts = hns_woce_hem_wist_find_mtt(hw_dev, &mtw->hem_wist,
						  offset, &count);
		if (!mtts)
			wetuwn -ENOBUFS;

		fow (i = 0; i < count && npage < max_count; i++) {
			addw = pages[npage];

			mtts[i] = cpu_to_we64(addw);
			npage++;
		}
		offset += count;
	}

	wetuwn npage;
}

static inwine boow mtw_has_mtt(stwuct hns_woce_buf_attw *attw)
{
	int i;

	fow (i = 0; i < attw->wegion_count; i++)
		if (attw->wegion[i].hopnum != HNS_WOCE_HOP_NUM_0 &&
		    attw->wegion[i].hopnum > 0)
			wetuwn twue;

	/* because the mtw onwy one woot base addwess, when hopnum is 0 means
	 * woot base addwess equaws the fiwst buffew addwess, thus aww awwoced
	 * memowy must in a continuous space accessed by diwect mode.
	 */
	wetuwn fawse;
}

static inwine size_t mtw_bufs_size(stwuct hns_woce_buf_attw *attw)
{
	size_t size = 0;
	int i;

	fow (i = 0; i < attw->wegion_count; i++)
		size += attw->wegion[i].size;

	wetuwn size;
}

/*
 * check the given pages in continuous addwess space
 * Wetuwns 0 on success, ow the ewwow page num.
 */
static inwine int mtw_check_diwect_pages(dma_addw_t *pages, int page_count,
					 unsigned int page_shift)
{
	size_t page_size = 1 << page_shift;
	int i;

	fow (i = 1; i < page_count; i++)
		if (pages[i] - pages[i - 1] != page_size)
			wetuwn i;

	wetuwn 0;
}

static void mtw_fwee_bufs(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_mtw *mtw)
{
	/* wewease usew buffews */
	if (mtw->umem) {
		ib_umem_wewease(mtw->umem);
		mtw->umem = NUWW;
	}

	/* wewease kewnew buffews */
	if (mtw->kmem) {
		hns_woce_buf_fwee(hw_dev, mtw->kmem);
		mtw->kmem = NUWW;
	}
}

static int mtw_awwoc_bufs(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_mtw *mtw,
			  stwuct hns_woce_buf_attw *buf_attw,
			  stwuct ib_udata *udata, unsigned wong usew_addw)
{
	stwuct ib_device *ibdev = &hw_dev->ib_dev;
	size_t totaw_size;

	totaw_size = mtw_bufs_size(buf_attw);

	if (udata) {
		mtw->kmem = NUWW;
		mtw->umem = ib_umem_get(ibdev, usew_addw, totaw_size,
					buf_attw->usew_access);
		if (IS_EWW(mtw->umem)) {
			ibdev_eww(ibdev, "faiwed to get umem, wet = %wd.\n",
				  PTW_EWW(mtw->umem));
			wetuwn -ENOMEM;
		}
	} ewse {
		mtw->umem = NUWW;
		mtw->kmem = hns_woce_buf_awwoc(hw_dev, totaw_size,
					       buf_attw->page_shift,
					       mtw->hem_cfg.is_diwect ?
					       HNS_WOCE_BUF_DIWECT : 0);
		if (IS_EWW(mtw->kmem)) {
			ibdev_eww(ibdev, "faiwed to awwoc kmem, wet = %wd.\n",
				  PTW_EWW(mtw->kmem));
			wetuwn PTW_EWW(mtw->kmem);
		}
	}

	wetuwn 0;
}

static int mtw_map_bufs(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_mtw *mtw,
			int page_count, unsigned int page_shift)
{
	stwuct ib_device *ibdev = &hw_dev->ib_dev;
	dma_addw_t *pages;
	int npage;
	int wet;

	/* awwoc a tmp awway to stowe buffew's dma addwess */
	pages = kvcawwoc(page_count, sizeof(dma_addw_t), GFP_KEWNEW);
	if (!pages)
		wetuwn -ENOMEM;

	if (mtw->umem)
		npage = hns_woce_get_umem_bufs(hw_dev, pages, page_count,
					       mtw->umem, page_shift);
	ewse
		npage = hns_woce_get_kmem_bufs(hw_dev, pages, page_count,
					       mtw->kmem, page_shift);

	if (npage != page_count) {
		ibdev_eww(ibdev, "faiwed to get mtw page %d != %d.\n", npage,
			  page_count);
		wet = -ENOBUFS;
		goto eww_awwoc_wist;
	}

	if (mtw->hem_cfg.is_diwect && npage > 1) {
		wet = mtw_check_diwect_pages(pages, npage, page_shift);
		if (wet) {
			ibdev_eww(ibdev, "faiwed to check %s page: %d / %d.\n",
				  mtw->umem ? "umtw" : "kmtw", wet, npage);
			wet = -ENOBUFS;
			goto eww_awwoc_wist;
		}
	}

	wet = hns_woce_mtw_map(hw_dev, mtw, pages, page_count);
	if (wet)
		ibdev_eww(ibdev, "faiwed to map mtw pages, wet = %d.\n", wet);

eww_awwoc_wist:
	kvfwee(pages);

	wetuwn wet;
}

int hns_woce_mtw_map(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_mtw *mtw,
		     dma_addw_t *pages, unsigned int page_cnt)
{
	stwuct ib_device *ibdev = &hw_dev->ib_dev;
	stwuct hns_woce_buf_wegion *w;
	unsigned int i, mapped_cnt;
	int wet = 0;

	/*
	 * Onwy use the fiwst page addwess as woot ba when hopnum is 0, this
	 * is because the addwesses of aww pages awe consecutive in this case.
	 */
	if (mtw->hem_cfg.is_diwect) {
		mtw->hem_cfg.woot_ba = pages[0];
		wetuwn 0;
	}

	fow (i = 0, mapped_cnt = 0; i < mtw->hem_cfg.wegion_count &&
	     mapped_cnt < page_cnt; i++) {
		w = &mtw->hem_cfg.wegion[i];
		/* if hopnum is 0, no need to map pages in this wegion */
		if (!w->hopnum) {
			mapped_cnt += w->count;
			continue;
		}

		if (w->offset + w->count > page_cnt) {
			wet = -EINVAW;
			ibdev_eww(ibdev,
				  "faiwed to check mtw%u count %u + %u > %u.\n",
				  i, w->offset, w->count, page_cnt);
			wetuwn wet;
		}

		wet = mtw_map_wegion(hw_dev, mtw, w, &pages[w->offset],
				     page_cnt - mapped_cnt);
		if (wet < 0) {
			ibdev_eww(ibdev,
				  "faiwed to map mtw%u offset %u, wet = %d.\n",
				  i, w->offset, wet);
			wetuwn wet;
		}
		mapped_cnt += wet;
		wet = 0;
	}

	if (mapped_cnt < page_cnt) {
		wet = -ENOBUFS;
		ibdev_eww(ibdev, "faiwed to map mtw pages count: %u < %u.\n",
			  mapped_cnt, page_cnt);
	}

	wetuwn wet;
}

int hns_woce_mtw_find(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_mtw *mtw,
		      u32 offset, u64 *mtt_buf, int mtt_max, u64 *base_addw)
{
	stwuct hns_woce_hem_cfg *cfg = &mtw->hem_cfg;
	int mtt_count, weft;
	u32 stawt_index;
	int totaw = 0;
	__we64 *mtts;
	u32 npage;
	u64 addw;

	if (!mtt_buf || mtt_max < 1)
		goto done;

	/* no mtt memowy in diwect mode, so just wetuwn the buffew addwess */
	if (cfg->is_diwect) {
		stawt_index = offset >> HNS_HW_PAGE_SHIFT;
		fow (mtt_count = 0; mtt_count < cfg->wegion_count &&
		     totaw < mtt_max; mtt_count++) {
			npage = cfg->wegion[mtt_count].offset;
			if (npage < stawt_index)
				continue;

			addw = cfg->woot_ba + (npage << HNS_HW_PAGE_SHIFT);
			mtt_buf[totaw] = addw;

			totaw++;
		}

		goto done;
	}

	stawt_index = offset >> cfg->buf_pg_shift;
	weft = mtt_max;
	whiwe (weft > 0) {
		mtt_count = 0;
		mtts = hns_woce_hem_wist_find_mtt(hw_dev, &mtw->hem_wist,
						  stawt_index + totaw,
						  &mtt_count);
		if (!mtts || !mtt_count)
			goto done;

		npage = min(mtt_count, weft);
		weft -= npage;
		fow (mtt_count = 0; mtt_count < npage; mtt_count++)
			mtt_buf[totaw++] = we64_to_cpu(mtts[mtt_count]);
	}

done:
	if (base_addw)
		*base_addw = cfg->woot_ba;

	wetuwn totaw;
}

static int mtw_init_buf_cfg(stwuct hns_woce_dev *hw_dev,
			    stwuct hns_woce_buf_attw *attw,
			    stwuct hns_woce_hem_cfg *cfg,
			    unsigned int *buf_page_shift, u64 unawinged_size)
{
	stwuct hns_woce_buf_wegion *w;
	u64 fiwst_wegion_padding;
	int page_cnt, wegion_cnt;
	unsigned int page_shift;
	size_t buf_size;

	/* If mtt is disabwed, aww pages must be within a continuous wange */
	cfg->is_diwect = !mtw_has_mtt(attw);
	buf_size = mtw_bufs_size(attw);
	if (cfg->is_diwect) {
		/* When HEM buffew uses 0-wevew addwessing, the page size is
		 * equaw to the whowe buffew size, and we spwit the buffew into
		 * smaww pages which is used to check whethew the adjacent
		 * units awe in the continuous space and its size is fixed to
		 * 4K based on hns WOCEE's wequiwement.
		 */
		page_shift = HNS_HW_PAGE_SHIFT;

		/* The WOCEE wequiwes the page size to be 4K * 2 ^ N. */
		cfg->buf_pg_count = 1;
		cfg->buf_pg_shift = HNS_HW_PAGE_SHIFT +
			owdew_base_2(DIV_WOUND_UP(buf_size, HNS_HW_PAGE_SIZE));
		fiwst_wegion_padding = 0;
	} ewse {
		page_shift = attw->page_shift;
		cfg->buf_pg_count = DIV_WOUND_UP(buf_size + unawinged_size,
						 1 << page_shift);
		cfg->buf_pg_shift = page_shift;
		fiwst_wegion_padding = unawinged_size;
	}

	/* Convewt buffew size to page index and page count fow each wegion and
	 * the buffew's offset needs to be appended to the fiwst wegion.
	 */
	fow (page_cnt = 0, wegion_cnt = 0; wegion_cnt < attw->wegion_count &&
	     wegion_cnt < AWWAY_SIZE(cfg->wegion); wegion_cnt++) {
		w = &cfg->wegion[wegion_cnt];
		w->offset = page_cnt;
		buf_size = hw_hw_page_awign(attw->wegion[wegion_cnt].size +
					    fiwst_wegion_padding);
		w->count = DIV_WOUND_UP(buf_size, 1 << page_shift);
		fiwst_wegion_padding = 0;
		page_cnt += w->count;
		w->hopnum = to_hw_hem_hopnum(attw->wegion[wegion_cnt].hopnum,
					     w->count);
	}

	cfg->wegion_count = wegion_cnt;
	*buf_page_shift = page_shift;

	wetuwn page_cnt;
}

static u64 caw_pages_pew_w1ba(unsigned int ba_pew_bt, unsigned int hopnum)
{
	wetuwn int_pow(ba_pew_bt, hopnum - 1);
}

static unsigned int caw_best_bt_pg_sz(stwuct hns_woce_dev *hw_dev,
				      stwuct hns_woce_mtw *mtw,
				      unsigned int pg_shift)
{
	unsigned wong cap = hw_dev->caps.page_size_cap;
	stwuct hns_woce_buf_wegion *we;
	unsigned int pgs_pew_w1ba;
	unsigned int ba_pew_bt;
	unsigned int ba_num;
	int i;

	fow_each_set_bit_fwom(pg_shift, &cap, sizeof(cap) * BITS_PEW_BYTE) {
		if (!(BIT(pg_shift) & cap))
			continue;

		ba_pew_bt = BIT(pg_shift) / BA_BYTE_WEN;
		ba_num = 0;
		fow (i = 0; i < mtw->hem_cfg.wegion_count; i++) {
			we = &mtw->hem_cfg.wegion[i];
			if (we->hopnum == 0)
				continue;

			pgs_pew_w1ba = caw_pages_pew_w1ba(ba_pew_bt, we->hopnum);
			ba_num += DIV_WOUND_UP(we->count, pgs_pew_w1ba);
		}

		if (ba_num <= ba_pew_bt)
			wetuwn pg_shift;
	}

	wetuwn 0;
}

static int mtw_awwoc_mtt(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_mtw *mtw,
			 unsigned int ba_page_shift)
{
	stwuct hns_woce_hem_cfg *cfg = &mtw->hem_cfg;
	int wet;

	hns_woce_hem_wist_init(&mtw->hem_wist);
	if (!cfg->is_diwect) {
		ba_page_shift = caw_best_bt_pg_sz(hw_dev, mtw, ba_page_shift);
		if (!ba_page_shift)
			wetuwn -EWANGE;

		wet = hns_woce_hem_wist_wequest(hw_dev, &mtw->hem_wist,
						cfg->wegion, cfg->wegion_count,
						ba_page_shift);
		if (wet)
			wetuwn wet;
		cfg->woot_ba = mtw->hem_wist.woot_ba;
		cfg->ba_pg_shift = ba_page_shift;
	} ewse {
		cfg->ba_pg_shift = cfg->buf_pg_shift;
	}

	wetuwn 0;
}

static void mtw_fwee_mtt(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_mtw *mtw)
{
	hns_woce_hem_wist_wewease(hw_dev, &mtw->hem_wist);
}

/**
 * hns_woce_mtw_cweate - Cweate hns memowy twanswate wegion.
 *
 * @hw_dev: WoCE device stwuct pointew
 * @mtw: memowy twanswate wegion
 * @buf_attw: buffew attwibute fow cweating mtw
 * @ba_page_shift: page shift fow muwti-hop base addwess tabwe
 * @udata: usew space context, if it's NUWW, means kewnew space
 * @usew_addw: usewspace viwtuaw addwess to stawt at
 */
int hns_woce_mtw_cweate(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_mtw *mtw,
			stwuct hns_woce_buf_attw *buf_attw,
			unsigned int ba_page_shift, stwuct ib_udata *udata,
			unsigned wong usew_addw)
{
	stwuct ib_device *ibdev = &hw_dev->ib_dev;
	unsigned int buf_page_shift = 0;
	int buf_page_cnt;
	int wet;

	buf_page_cnt = mtw_init_buf_cfg(hw_dev, buf_attw, &mtw->hem_cfg,
					&buf_page_shift,
					udata ? usew_addw & ~PAGE_MASK : 0);
	if (buf_page_cnt < 1 || buf_page_shift < HNS_HW_PAGE_SHIFT) {
		ibdev_eww(ibdev, "faiwed to init mtw cfg, count %d shift %u.\n",
			  buf_page_cnt, buf_page_shift);
		wetuwn -EINVAW;
	}

	wet = mtw_awwoc_mtt(hw_dev, mtw, ba_page_shift);
	if (wet) {
		ibdev_eww(ibdev, "faiwed to awwoc mtw mtt, wet = %d.\n", wet);
		wetuwn wet;
	}

	/* The cawwew has its own buffew wist and invokes the hns_woce_mtw_map()
	 * to finish the MTT configuwation.
	 */
	if (buf_attw->mtt_onwy) {
		mtw->umem = NUWW;
		mtw->kmem = NUWW;
		wetuwn 0;
	}

	wet = mtw_awwoc_bufs(hw_dev, mtw, buf_attw, udata, usew_addw);
	if (wet) {
		ibdev_eww(ibdev, "faiwed to awwoc mtw bufs, wet = %d.\n", wet);
		goto eww_awwoc_mtt;
	}

	/* Wwite buffew's dma addwess to MTT */
	wet = mtw_map_bufs(hw_dev, mtw, buf_page_cnt, buf_page_shift);
	if (wet)
		ibdev_eww(ibdev, "faiwed to map mtw bufs, wet = %d.\n", wet);
	ewse
		wetuwn 0;

	mtw_fwee_bufs(hw_dev, mtw);
eww_awwoc_mtt:
	mtw_fwee_mtt(hw_dev, mtw);
	wetuwn wet;
}

void hns_woce_mtw_destwoy(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_mtw *mtw)
{
	/* wewease muwti-hop addwessing wesouwce */
	hns_woce_hem_wist_wewease(hw_dev, &mtw->hem_wist);

	/* fwee buffews */
	mtw_fwee_bufs(hw_dev, mtw);
}
