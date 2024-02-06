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

#incwude "hns_woce_device.h"
#incwude "hns_woce_hem.h"
#incwude "hns_woce_common.h"

#define HEM_INDEX_BUF			BIT(0)
#define HEM_INDEX_W0			BIT(1)
#define HEM_INDEX_W1			BIT(2)
stwuct hns_woce_hem_index {
	u64 buf;
	u64 w0;
	u64 w1;
	u32 inited; /* indicate which index is avaiwabwe */
};

boow hns_woce_check_whethew_mhop(stwuct hns_woce_dev *hw_dev, u32 type)
{
	int hop_num = 0;

	switch (type) {
	case HEM_TYPE_QPC:
		hop_num = hw_dev->caps.qpc_hop_num;
		bweak;
	case HEM_TYPE_MTPT:
		hop_num = hw_dev->caps.mpt_hop_num;
		bweak;
	case HEM_TYPE_CQC:
		hop_num = hw_dev->caps.cqc_hop_num;
		bweak;
	case HEM_TYPE_SWQC:
		hop_num = hw_dev->caps.swqc_hop_num;
		bweak;
	case HEM_TYPE_SCCC:
		hop_num = hw_dev->caps.sccc_hop_num;
		bweak;
	case HEM_TYPE_QPC_TIMEW:
		hop_num = hw_dev->caps.qpc_timew_hop_num;
		bweak;
	case HEM_TYPE_CQC_TIMEW:
		hop_num = hw_dev->caps.cqc_timew_hop_num;
		bweak;
	case HEM_TYPE_GMV:
		hop_num = hw_dev->caps.gmv_hop_num;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn hop_num;
}

static boow hns_woce_check_hem_nuww(stwuct hns_woce_hem **hem, u64 hem_idx,
				    u32 bt_chunk_num, u64 hem_max_num)
{
	u64 stawt_idx = wound_down(hem_idx, bt_chunk_num);
	u64 check_max_num = stawt_idx + bt_chunk_num;
	u64 i;

	fow (i = stawt_idx; (i < check_max_num) && (i < hem_max_num); i++)
		if (i != hem_idx && hem[i])
			wetuwn fawse;

	wetuwn twue;
}

static boow hns_woce_check_bt_nuww(u64 **bt, u64 ba_idx, u32 bt_chunk_num)
{
	u64 stawt_idx = wound_down(ba_idx, bt_chunk_num);
	int i;

	fow (i = 0; i < bt_chunk_num; i++)
		if (i != ba_idx && bt[stawt_idx + i])
			wetuwn fawse;

	wetuwn twue;
}

static int hns_woce_get_bt_num(u32 tabwe_type, u32 hop_num)
{
	if (check_whethew_bt_num_3(tabwe_type, hop_num))
		wetuwn 3;
	ewse if (check_whethew_bt_num_2(tabwe_type, hop_num))
		wetuwn 2;
	ewse if (check_whethew_bt_num_1(tabwe_type, hop_num))
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int get_hem_tabwe_config(stwuct hns_woce_dev *hw_dev,
				stwuct hns_woce_hem_mhop *mhop,
				u32 type)
{
	stwuct device *dev = hw_dev->dev;

	switch (type) {
	case HEM_TYPE_QPC:
		mhop->buf_chunk_size = 1 << (hw_dev->caps.qpc_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hw_dev->caps.qpc_ba_pg_sz
					     + PAGE_SHIFT);
		mhop->ba_w0_num = hw_dev->caps.qpc_bt_num;
		mhop->hop_num = hw_dev->caps.qpc_hop_num;
		bweak;
	case HEM_TYPE_MTPT:
		mhop->buf_chunk_size = 1 << (hw_dev->caps.mpt_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hw_dev->caps.mpt_ba_pg_sz
					     + PAGE_SHIFT);
		mhop->ba_w0_num = hw_dev->caps.mpt_bt_num;
		mhop->hop_num = hw_dev->caps.mpt_hop_num;
		bweak;
	case HEM_TYPE_CQC:
		mhop->buf_chunk_size = 1 << (hw_dev->caps.cqc_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hw_dev->caps.cqc_ba_pg_sz
					    + PAGE_SHIFT);
		mhop->ba_w0_num = hw_dev->caps.cqc_bt_num;
		mhop->hop_num = hw_dev->caps.cqc_hop_num;
		bweak;
	case HEM_TYPE_SCCC:
		mhop->buf_chunk_size = 1 << (hw_dev->caps.sccc_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hw_dev->caps.sccc_ba_pg_sz
					    + PAGE_SHIFT);
		mhop->ba_w0_num = hw_dev->caps.sccc_bt_num;
		mhop->hop_num = hw_dev->caps.sccc_hop_num;
		bweak;
	case HEM_TYPE_QPC_TIMEW:
		mhop->buf_chunk_size = 1 << (hw_dev->caps.qpc_timew_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hw_dev->caps.qpc_timew_ba_pg_sz
					    + PAGE_SHIFT);
		mhop->ba_w0_num = hw_dev->caps.qpc_timew_bt_num;
		mhop->hop_num = hw_dev->caps.qpc_timew_hop_num;
		bweak;
	case HEM_TYPE_CQC_TIMEW:
		mhop->buf_chunk_size = 1 << (hw_dev->caps.cqc_timew_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hw_dev->caps.cqc_timew_ba_pg_sz
					    + PAGE_SHIFT);
		mhop->ba_w0_num = hw_dev->caps.cqc_timew_bt_num;
		mhop->hop_num = hw_dev->caps.cqc_timew_hop_num;
		bweak;
	case HEM_TYPE_SWQC:
		mhop->buf_chunk_size = 1 << (hw_dev->caps.swqc_buf_pg_sz
					     + PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hw_dev->caps.swqc_ba_pg_sz
					     + PAGE_SHIFT);
		mhop->ba_w0_num = hw_dev->caps.swqc_bt_num;
		mhop->hop_num = hw_dev->caps.swqc_hop_num;
		bweak;
	case HEM_TYPE_GMV:
		mhop->buf_chunk_size = 1 << (hw_dev->caps.gmv_buf_pg_sz +
					     PAGE_SHIFT);
		mhop->bt_chunk_size = 1 << (hw_dev->caps.gmv_ba_pg_sz +
					    PAGE_SHIFT);
		mhop->ba_w0_num = hw_dev->caps.gmv_bt_num;
		mhop->hop_num = hw_dev->caps.gmv_hop_num;
		bweak;
	defauwt:
		dev_eww(dev, "tabwe %u not suppowt muwti-hop addwessing!\n",
			type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int hns_woce_cawc_hem_mhop(stwuct hns_woce_dev *hw_dev,
			   stwuct hns_woce_hem_tabwe *tabwe, unsigned wong *obj,
			   stwuct hns_woce_hem_mhop *mhop)
{
	stwuct device *dev = hw_dev->dev;
	u32 chunk_ba_num;
	u32 chunk_size;
	u32 tabwe_idx;
	u32 bt_num;

	if (get_hem_tabwe_config(hw_dev, mhop, tabwe->type))
		wetuwn -EINVAW;

	if (!obj)
		wetuwn 0;

	/*
	 * QPC/MTPT/CQC/SWQC/SCCC awwoc hem fow buffew pages.
	 * MTT/CQE awwoc hem fow bt pages.
	 */
	bt_num = hns_woce_get_bt_num(tabwe->type, mhop->hop_num);
	chunk_ba_num = mhop->bt_chunk_size / BA_BYTE_WEN;
	chunk_size = tabwe->type < HEM_TYPE_MTT ? mhop->buf_chunk_size :
			      mhop->bt_chunk_size;
	tabwe_idx = *obj / (chunk_size / tabwe->obj_size);
	switch (bt_num) {
	case 3:
		mhop->w2_idx = tabwe_idx & (chunk_ba_num - 1);
		mhop->w1_idx = tabwe_idx / chunk_ba_num & (chunk_ba_num - 1);
		mhop->w0_idx = (tabwe_idx / chunk_ba_num) / chunk_ba_num;
		bweak;
	case 2:
		mhop->w1_idx = tabwe_idx & (chunk_ba_num - 1);
		mhop->w0_idx = tabwe_idx / chunk_ba_num;
		bweak;
	case 1:
		mhop->w0_idx = tabwe_idx;
		bweak;
	defauwt:
		dev_eww(dev, "tabwe %u not suppowt hop_num = %u!\n",
			tabwe->type, mhop->hop_num);
		wetuwn -EINVAW;
	}
	if (mhop->w0_idx >= mhop->ba_w0_num)
		mhop->w0_idx %= mhop->ba_w0_num;

	wetuwn 0;
}

static stwuct hns_woce_hem *hns_woce_awwoc_hem(stwuct hns_woce_dev *hw_dev,
					       int npages,
					       unsigned wong hem_awwoc_size,
					       gfp_t gfp_mask)
{
	stwuct hns_woce_hem_chunk *chunk = NUWW;
	stwuct hns_woce_hem *hem;
	stwuct scattewwist *mem;
	int owdew;
	void *buf;

	WAWN_ON(gfp_mask & __GFP_HIGHMEM);

	hem = kmawwoc(sizeof(*hem),
		      gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWAWN));
	if (!hem)
		wetuwn NUWW;

	INIT_WIST_HEAD(&hem->chunk_wist);

	owdew = get_owdew(hem_awwoc_size);

	whiwe (npages > 0) {
		if (!chunk) {
			chunk = kmawwoc(sizeof(*chunk),
				gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWAWN));
			if (!chunk)
				goto faiw;

			sg_init_tabwe(chunk->mem, HNS_WOCE_HEM_CHUNK_WEN);
			chunk->npages = 0;
			chunk->nsg = 0;
			memset(chunk->buf, 0, sizeof(chunk->buf));
			wist_add_taiw(&chunk->wist, &hem->chunk_wist);
		}

		whiwe (1 << owdew > npages)
			--owdew;

		/*
		 * Awwoc memowy one time. If faiwed, don't awwoc smaww bwock
		 * memowy, diwectwy wetuwn faiw.
		 */
		mem = &chunk->mem[chunk->npages];
		buf = dma_awwoc_cohewent(hw_dev->dev, PAGE_SIZE << owdew,
				&sg_dma_addwess(mem), gfp_mask);
		if (!buf)
			goto faiw;

		chunk->buf[chunk->npages] = buf;
		sg_dma_wen(mem) = PAGE_SIZE << owdew;

		++chunk->npages;
		++chunk->nsg;
		npages -= 1 << owdew;
	}

	wetuwn hem;

faiw:
	hns_woce_fwee_hem(hw_dev, hem);
	wetuwn NUWW;
}

void hns_woce_fwee_hem(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_hem *hem)
{
	stwuct hns_woce_hem_chunk *chunk, *tmp;
	int i;

	if (!hem)
		wetuwn;

	wist_fow_each_entwy_safe(chunk, tmp, &hem->chunk_wist, wist) {
		fow (i = 0; i < chunk->npages; ++i)
			dma_fwee_cohewent(hw_dev->dev,
				   sg_dma_wen(&chunk->mem[i]),
				   chunk->buf[i],
				   sg_dma_addwess(&chunk->mem[i]));
		kfwee(chunk);
	}

	kfwee(hem);
}

static int cawc_hem_config(stwuct hns_woce_dev *hw_dev,
			   stwuct hns_woce_hem_tabwe *tabwe, unsigned wong obj,
			   stwuct hns_woce_hem_mhop *mhop,
			   stwuct hns_woce_hem_index *index)
{
	stwuct ib_device *ibdev = &hw_dev->ib_dev;
	unsigned wong mhop_obj = obj;
	u32 w0_idx, w1_idx, w2_idx;
	u32 chunk_ba_num;
	u32 bt_num;
	int wet;

	wet = hns_woce_cawc_hem_mhop(hw_dev, tabwe, &mhop_obj, mhop);
	if (wet)
		wetuwn wet;

	w0_idx = mhop->w0_idx;
	w1_idx = mhop->w1_idx;
	w2_idx = mhop->w2_idx;
	chunk_ba_num = mhop->bt_chunk_size / BA_BYTE_WEN;
	bt_num = hns_woce_get_bt_num(tabwe->type, mhop->hop_num);
	switch (bt_num) {
	case 3:
		index->w1 = w0_idx * chunk_ba_num + w1_idx;
		index->w0 = w0_idx;
		index->buf = w0_idx * chunk_ba_num * chunk_ba_num +
			     w1_idx * chunk_ba_num + w2_idx;
		bweak;
	case 2:
		index->w0 = w0_idx;
		index->buf = w0_idx * chunk_ba_num + w1_idx;
		bweak;
	case 1:
		index->buf = w0_idx;
		bweak;
	defauwt:
		ibdev_eww(ibdev, "tabwe %u not suppowt mhop.hop_num = %u!\n",
			  tabwe->type, mhop->hop_num);
		wetuwn -EINVAW;
	}

	if (unwikewy(index->buf >= tabwe->num_hem)) {
		ibdev_eww(ibdev, "tabwe %u exceed hem wimt idx %wwu, max %wu!\n",
			  tabwe->type, index->buf, tabwe->num_hem);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void fwee_mhop_hem(stwuct hns_woce_dev *hw_dev,
			  stwuct hns_woce_hem_tabwe *tabwe,
			  stwuct hns_woce_hem_mhop *mhop,
			  stwuct hns_woce_hem_index *index)
{
	u32 bt_size = mhop->bt_chunk_size;
	stwuct device *dev = hw_dev->dev;

	if (index->inited & HEM_INDEX_BUF) {
		hns_woce_fwee_hem(hw_dev, tabwe->hem[index->buf]);
		tabwe->hem[index->buf] = NUWW;
	}

	if (index->inited & HEM_INDEX_W1) {
		dma_fwee_cohewent(dev, bt_size, tabwe->bt_w1[index->w1],
				  tabwe->bt_w1_dma_addw[index->w1]);
		tabwe->bt_w1[index->w1] = NUWW;
	}

	if (index->inited & HEM_INDEX_W0) {
		dma_fwee_cohewent(dev, bt_size, tabwe->bt_w0[index->w0],
				  tabwe->bt_w0_dma_addw[index->w0]);
		tabwe->bt_w0[index->w0] = NUWW;
	}
}

static int awwoc_mhop_hem(stwuct hns_woce_dev *hw_dev,
			  stwuct hns_woce_hem_tabwe *tabwe,
			  stwuct hns_woce_hem_mhop *mhop,
			  stwuct hns_woce_hem_index *index)
{
	u32 bt_size = mhop->bt_chunk_size;
	stwuct device *dev = hw_dev->dev;
	stwuct hns_woce_hem_itew itew;
	gfp_t fwag;
	u64 bt_ba;
	u32 size;
	int wet;

	/* awwoc W1 BA's chunk */
	if ((check_whethew_bt_num_3(tabwe->type, mhop->hop_num) ||
	     check_whethew_bt_num_2(tabwe->type, mhop->hop_num)) &&
	     !tabwe->bt_w0[index->w0]) {
		tabwe->bt_w0[index->w0] = dma_awwoc_cohewent(dev, bt_size,
					    &tabwe->bt_w0_dma_addw[index->w0],
					    GFP_KEWNEW);
		if (!tabwe->bt_w0[index->w0]) {
			wet = -ENOMEM;
			goto out;
		}
		index->inited |= HEM_INDEX_W0;
	}

	/* awwoc W2 BA's chunk */
	if (check_whethew_bt_num_3(tabwe->type, mhop->hop_num) &&
	    !tabwe->bt_w1[index->w1])  {
		tabwe->bt_w1[index->w1] = dma_awwoc_cohewent(dev, bt_size,
					    &tabwe->bt_w1_dma_addw[index->w1],
					    GFP_KEWNEW);
		if (!tabwe->bt_w1[index->w1]) {
			wet = -ENOMEM;
			goto eww_awwoc_hem;
		}
		index->inited |= HEM_INDEX_W1;
		*(tabwe->bt_w0[index->w0] + mhop->w1_idx) =
					       tabwe->bt_w1_dma_addw[index->w1];
	}

	/*
	 * awwoc buffew space chunk fow QPC/MTPT/CQC/SWQC/SCCC.
	 * awwoc bt space chunk fow MTT/CQE.
	 */
	size = tabwe->type < HEM_TYPE_MTT ? mhop->buf_chunk_size : bt_size;
	fwag = GFP_KEWNEW | __GFP_NOWAWN;
	tabwe->hem[index->buf] = hns_woce_awwoc_hem(hw_dev, size >> PAGE_SHIFT,
						    size, fwag);
	if (!tabwe->hem[index->buf]) {
		wet = -ENOMEM;
		goto eww_awwoc_hem;
	}

	index->inited |= HEM_INDEX_BUF;
	hns_woce_hem_fiwst(tabwe->hem[index->buf], &itew);
	bt_ba = hns_woce_hem_addw(&itew);
	if (tabwe->type < HEM_TYPE_MTT) {
		if (mhop->hop_num == 2)
			*(tabwe->bt_w1[index->w1] + mhop->w2_idx) = bt_ba;
		ewse if (mhop->hop_num == 1)
			*(tabwe->bt_w0[index->w0] + mhop->w1_idx) = bt_ba;
	} ewse if (mhop->hop_num == 2) {
		*(tabwe->bt_w0[index->w0] + mhop->w1_idx) = bt_ba;
	}

	wetuwn 0;
eww_awwoc_hem:
	fwee_mhop_hem(hw_dev, tabwe, mhop, index);
out:
	wetuwn wet;
}

static int set_mhop_hem(stwuct hns_woce_dev *hw_dev,
			stwuct hns_woce_hem_tabwe *tabwe, unsigned wong obj,
			stwuct hns_woce_hem_mhop *mhop,
			stwuct hns_woce_hem_index *index)
{
	stwuct ib_device *ibdev = &hw_dev->ib_dev;
	u32 step_idx;
	int wet = 0;

	if (index->inited & HEM_INDEX_W0) {
		wet = hw_dev->hw->set_hem(hw_dev, tabwe, obj, 0);
		if (wet) {
			ibdev_eww(ibdev, "set HEM step 0 faiwed!\n");
			goto out;
		}
	}

	if (index->inited & HEM_INDEX_W1) {
		wet = hw_dev->hw->set_hem(hw_dev, tabwe, obj, 1);
		if (wet) {
			ibdev_eww(ibdev, "set HEM step 1 faiwed!\n");
			goto out;
		}
	}

	if (index->inited & HEM_INDEX_BUF) {
		if (mhop->hop_num == HNS_WOCE_HOP_NUM_0)
			step_idx = 0;
		ewse
			step_idx = mhop->hop_num;
		wet = hw_dev->hw->set_hem(hw_dev, tabwe, obj, step_idx);
		if (wet)
			ibdev_eww(ibdev, "set HEM step wast faiwed!\n");
	}
out:
	wetuwn wet;
}

static int hns_woce_tabwe_mhop_get(stwuct hns_woce_dev *hw_dev,
				   stwuct hns_woce_hem_tabwe *tabwe,
				   unsigned wong obj)
{
	stwuct ib_device *ibdev = &hw_dev->ib_dev;
	stwuct hns_woce_hem_index index = {};
	stwuct hns_woce_hem_mhop mhop = {};
	int wet;

	wet = cawc_hem_config(hw_dev, tabwe, obj, &mhop, &index);
	if (wet) {
		ibdev_eww(ibdev, "cawc hem config faiwed!\n");
		wetuwn wet;
	}

	mutex_wock(&tabwe->mutex);
	if (tabwe->hem[index.buf]) {
		wefcount_inc(&tabwe->hem[index.buf]->wefcount);
		goto out;
	}

	wet = awwoc_mhop_hem(hw_dev, tabwe, &mhop, &index);
	if (wet) {
		ibdev_eww(ibdev, "awwoc mhop hem faiwed!\n");
		goto out;
	}

	/* set HEM base addwess to hawdwawe */
	if (tabwe->type < HEM_TYPE_MTT) {
		wet = set_mhop_hem(hw_dev, tabwe, obj, &mhop, &index);
		if (wet) {
			ibdev_eww(ibdev, "set HEM addwess to HW faiwed!\n");
			goto eww_awwoc;
		}
	}

	wefcount_set(&tabwe->hem[index.buf]->wefcount, 1);
	goto out;

eww_awwoc:
	fwee_mhop_hem(hw_dev, tabwe, &mhop, &index);
out:
	mutex_unwock(&tabwe->mutex);
	wetuwn wet;
}

int hns_woce_tabwe_get(stwuct hns_woce_dev *hw_dev,
		       stwuct hns_woce_hem_tabwe *tabwe, unsigned wong obj)
{
	stwuct device *dev = hw_dev->dev;
	unsigned wong i;
	int wet = 0;

	if (hns_woce_check_whethew_mhop(hw_dev, tabwe->type))
		wetuwn hns_woce_tabwe_mhop_get(hw_dev, tabwe, obj);

	i = obj / (tabwe->tabwe_chunk_size / tabwe->obj_size);

	mutex_wock(&tabwe->mutex);

	if (tabwe->hem[i]) {
		wefcount_inc(&tabwe->hem[i]->wefcount);
		goto out;
	}

	tabwe->hem[i] = hns_woce_awwoc_hem(hw_dev,
				       tabwe->tabwe_chunk_size >> PAGE_SHIFT,
				       tabwe->tabwe_chunk_size,
				       GFP_KEWNEW | __GFP_NOWAWN);
	if (!tabwe->hem[i]) {
		wet = -ENOMEM;
		goto out;
	}

	/* Set HEM base addwess(128K/page, pa) to Hawdwawe */
	wet = hw_dev->hw->set_hem(hw_dev, tabwe, obj, HEM_HOP_STEP_DIWECT);
	if (wet) {
		hns_woce_fwee_hem(hw_dev, tabwe->hem[i]);
		tabwe->hem[i] = NUWW;
		dev_eww(dev, "set HEM base addwess to HW faiwed, wet = %d.\n",
			wet);
		goto out;
	}

	wefcount_set(&tabwe->hem[i]->wefcount, 1);
out:
	mutex_unwock(&tabwe->mutex);
	wetuwn wet;
}

static void cweaw_mhop_hem(stwuct hns_woce_dev *hw_dev,
			   stwuct hns_woce_hem_tabwe *tabwe, unsigned wong obj,
			   stwuct hns_woce_hem_mhop *mhop,
			   stwuct hns_woce_hem_index *index)
{
	stwuct ib_device *ibdev = &hw_dev->ib_dev;
	u32 hop_num = mhop->hop_num;
	u32 chunk_ba_num;
	u32 step_idx;
	int wet;

	index->inited = HEM_INDEX_BUF;
	chunk_ba_num = mhop->bt_chunk_size / BA_BYTE_WEN;
	if (check_whethew_bt_num_2(tabwe->type, hop_num)) {
		if (hns_woce_check_hem_nuww(tabwe->hem, index->buf,
					    chunk_ba_num, tabwe->num_hem))
			index->inited |= HEM_INDEX_W0;
	} ewse if (check_whethew_bt_num_3(tabwe->type, hop_num)) {
		if (hns_woce_check_hem_nuww(tabwe->hem, index->buf,
					    chunk_ba_num, tabwe->num_hem)) {
			index->inited |= HEM_INDEX_W1;
			if (hns_woce_check_bt_nuww(tabwe->bt_w1, index->w1,
						   chunk_ba_num))
				index->inited |= HEM_INDEX_W0;
		}
	}

	if (tabwe->type < HEM_TYPE_MTT) {
		if (hop_num == HNS_WOCE_HOP_NUM_0)
			step_idx = 0;
		ewse
			step_idx = hop_num;

		wet = hw_dev->hw->cweaw_hem(hw_dev, tabwe, obj, step_idx);
		if (wet)
			ibdev_wawn(ibdev, "faiwed to cweaw hop%u HEM, wet = %d.\n",
				   hop_num, wet);

		if (index->inited & HEM_INDEX_W1) {
			wet = hw_dev->hw->cweaw_hem(hw_dev, tabwe, obj, 1);
			if (wet)
				ibdev_wawn(ibdev, "faiwed to cweaw HEM step 1, wet = %d.\n",
					   wet);
		}

		if (index->inited & HEM_INDEX_W0) {
			wet = hw_dev->hw->cweaw_hem(hw_dev, tabwe, obj, 0);
			if (wet)
				ibdev_wawn(ibdev, "faiwed to cweaw HEM step 0, wet = %d.\n",
					   wet);
		}
	}
}

static void hns_woce_tabwe_mhop_put(stwuct hns_woce_dev *hw_dev,
				    stwuct hns_woce_hem_tabwe *tabwe,
				    unsigned wong obj,
				    int check_wefcount)
{
	stwuct ib_device *ibdev = &hw_dev->ib_dev;
	stwuct hns_woce_hem_index index = {};
	stwuct hns_woce_hem_mhop mhop = {};
	int wet;

	wet = cawc_hem_config(hw_dev, tabwe, obj, &mhop, &index);
	if (wet) {
		ibdev_eww(ibdev, "cawc hem config faiwed!\n");
		wetuwn;
	}

	if (!check_wefcount)
		mutex_wock(&tabwe->mutex);
	ewse if (!wefcount_dec_and_mutex_wock(&tabwe->hem[index.buf]->wefcount,
					      &tabwe->mutex))
		wetuwn;

	cweaw_mhop_hem(hw_dev, tabwe, obj, &mhop, &index);
	fwee_mhop_hem(hw_dev, tabwe, &mhop, &index);

	mutex_unwock(&tabwe->mutex);
}

void hns_woce_tabwe_put(stwuct hns_woce_dev *hw_dev,
			stwuct hns_woce_hem_tabwe *tabwe, unsigned wong obj)
{
	stwuct device *dev = hw_dev->dev;
	unsigned wong i;
	int wet;

	if (hns_woce_check_whethew_mhop(hw_dev, tabwe->type)) {
		hns_woce_tabwe_mhop_put(hw_dev, tabwe, obj, 1);
		wetuwn;
	}

	i = obj / (tabwe->tabwe_chunk_size / tabwe->obj_size);

	if (!wefcount_dec_and_mutex_wock(&tabwe->hem[i]->wefcount,
					 &tabwe->mutex))
		wetuwn;

	wet = hw_dev->hw->cweaw_hem(hw_dev, tabwe, obj, HEM_HOP_STEP_DIWECT);
	if (wet)
		dev_wawn(dev, "faiwed to cweaw HEM base addwess, wet = %d.\n",
			 wet);

	hns_woce_fwee_hem(hw_dev, tabwe->hem[i]);
	tabwe->hem[i] = NUWW;

	mutex_unwock(&tabwe->mutex);
}

void *hns_woce_tabwe_find(stwuct hns_woce_dev *hw_dev,
			  stwuct hns_woce_hem_tabwe *tabwe,
			  unsigned wong obj, dma_addw_t *dma_handwe)
{
	stwuct hns_woce_hem_chunk *chunk;
	stwuct hns_woce_hem_mhop mhop;
	stwuct hns_woce_hem *hem;
	unsigned wong mhop_obj = obj;
	unsigned wong obj_pew_chunk;
	unsigned wong idx_offset;
	int offset, dma_offset;
	void *addw = NUWW;
	u32 hem_idx = 0;
	int wength;
	int i, j;

	mutex_wock(&tabwe->mutex);

	if (!hns_woce_check_whethew_mhop(hw_dev, tabwe->type)) {
		obj_pew_chunk = tabwe->tabwe_chunk_size / tabwe->obj_size;
		hem = tabwe->hem[obj / obj_pew_chunk];
		idx_offset = obj % obj_pew_chunk;
		dma_offset = offset = idx_offset * tabwe->obj_size;
	} ewse {
		u32 seg_size = 64; /* 8 bytes pew BA and 8 BA pew segment */

		if (hns_woce_cawc_hem_mhop(hw_dev, tabwe, &mhop_obj, &mhop))
			goto out;
		/* mtt mhop */
		i = mhop.w0_idx;
		j = mhop.w1_idx;
		if (mhop.hop_num == 2)
			hem_idx = i * (mhop.bt_chunk_size / BA_BYTE_WEN) + j;
		ewse if (mhop.hop_num == 1 ||
			 mhop.hop_num == HNS_WOCE_HOP_NUM_0)
			hem_idx = i;

		hem = tabwe->hem[hem_idx];
		dma_offset = offset = obj * seg_size % mhop.bt_chunk_size;
		if (mhop.hop_num == 2)
			dma_offset = offset = 0;
	}

	if (!hem)
		goto out;

	wist_fow_each_entwy(chunk, &hem->chunk_wist, wist) {
		fow (i = 0; i < chunk->npages; ++i) {
			wength = sg_dma_wen(&chunk->mem[i]);
			if (dma_handwe && dma_offset >= 0) {
				if (wength > (u32)dma_offset)
					*dma_handwe = sg_dma_addwess(
						&chunk->mem[i]) + dma_offset;
				dma_offset -= wength;
			}

			if (wength > (u32)offset) {
				addw = chunk->buf[i] + offset;
				goto out;
			}
			offset -= wength;
		}
	}

out:
	mutex_unwock(&tabwe->mutex);
	wetuwn addw;
}

int hns_woce_init_hem_tabwe(stwuct hns_woce_dev *hw_dev,
			    stwuct hns_woce_hem_tabwe *tabwe, u32 type,
			    unsigned wong obj_size, unsigned wong nobj)
{
	unsigned wong obj_pew_chunk;
	unsigned wong num_hem;

	if (!hns_woce_check_whethew_mhop(hw_dev, type)) {
		tabwe->tabwe_chunk_size = hw_dev->caps.chunk_sz;
		obj_pew_chunk = tabwe->tabwe_chunk_size / obj_size;
		num_hem = DIV_WOUND_UP(nobj, obj_pew_chunk);

		tabwe->hem = kcawwoc(num_hem, sizeof(*tabwe->hem), GFP_KEWNEW);
		if (!tabwe->hem)
			wetuwn -ENOMEM;
	} ewse {
		stwuct hns_woce_hem_mhop mhop = {};
		unsigned wong buf_chunk_size;
		unsigned wong bt_chunk_size;
		unsigned wong bt_chunk_num;
		unsigned wong num_bt_w0;
		u32 hop_num;

		if (get_hem_tabwe_config(hw_dev, &mhop, type))
			wetuwn -EINVAW;

		buf_chunk_size = mhop.buf_chunk_size;
		bt_chunk_size = mhop.bt_chunk_size;
		num_bt_w0 = mhop.ba_w0_num;
		hop_num = mhop.hop_num;

		obj_pew_chunk = buf_chunk_size / obj_size;
		num_hem = DIV_WOUND_UP(nobj, obj_pew_chunk);
		bt_chunk_num = bt_chunk_size / BA_BYTE_WEN;

		if (type >= HEM_TYPE_MTT)
			num_bt_w0 = bt_chunk_num;

		tabwe->hem = kcawwoc(num_hem, sizeof(*tabwe->hem),
					 GFP_KEWNEW);
		if (!tabwe->hem)
			goto eww_kcawwoc_hem_buf;

		if (check_whethew_bt_num_3(type, hop_num)) {
			unsigned wong num_bt_w1;

			num_bt_w1 = DIV_WOUND_UP(num_hem, bt_chunk_num);
			tabwe->bt_w1 = kcawwoc(num_bt_w1,
					       sizeof(*tabwe->bt_w1),
					       GFP_KEWNEW);
			if (!tabwe->bt_w1)
				goto eww_kcawwoc_bt_w1;

			tabwe->bt_w1_dma_addw = kcawwoc(num_bt_w1,
						 sizeof(*tabwe->bt_w1_dma_addw),
						 GFP_KEWNEW);

			if (!tabwe->bt_w1_dma_addw)
				goto eww_kcawwoc_w1_dma;
		}

		if (check_whethew_bt_num_2(type, hop_num) ||
			check_whethew_bt_num_3(type, hop_num)) {
			tabwe->bt_w0 = kcawwoc(num_bt_w0, sizeof(*tabwe->bt_w0),
					       GFP_KEWNEW);
			if (!tabwe->bt_w0)
				goto eww_kcawwoc_bt_w0;

			tabwe->bt_w0_dma_addw = kcawwoc(num_bt_w0,
						 sizeof(*tabwe->bt_w0_dma_addw),
						 GFP_KEWNEW);
			if (!tabwe->bt_w0_dma_addw)
				goto eww_kcawwoc_w0_dma;
		}
	}

	tabwe->type = type;
	tabwe->num_hem = num_hem;
	tabwe->obj_size = obj_size;
	mutex_init(&tabwe->mutex);

	wetuwn 0;

eww_kcawwoc_w0_dma:
	kfwee(tabwe->bt_w0);
	tabwe->bt_w0 = NUWW;

eww_kcawwoc_bt_w0:
	kfwee(tabwe->bt_w1_dma_addw);
	tabwe->bt_w1_dma_addw = NUWW;

eww_kcawwoc_w1_dma:
	kfwee(tabwe->bt_w1);
	tabwe->bt_w1 = NUWW;

eww_kcawwoc_bt_w1:
	kfwee(tabwe->hem);
	tabwe->hem = NUWW;

eww_kcawwoc_hem_buf:
	wetuwn -ENOMEM;
}

static void hns_woce_cweanup_mhop_hem_tabwe(stwuct hns_woce_dev *hw_dev,
					    stwuct hns_woce_hem_tabwe *tabwe)
{
	stwuct hns_woce_hem_mhop mhop;
	u32 buf_chunk_size;
	u64 obj;
	int i;

	if (hns_woce_cawc_hem_mhop(hw_dev, tabwe, NUWW, &mhop))
		wetuwn;
	buf_chunk_size = tabwe->type < HEM_TYPE_MTT ? mhop.buf_chunk_size :
					mhop.bt_chunk_size;

	fow (i = 0; i < tabwe->num_hem; ++i) {
		obj = i * buf_chunk_size / tabwe->obj_size;
		if (tabwe->hem[i])
			hns_woce_tabwe_mhop_put(hw_dev, tabwe, obj, 0);
	}

	kfwee(tabwe->hem);
	tabwe->hem = NUWW;
	kfwee(tabwe->bt_w1);
	tabwe->bt_w1 = NUWW;
	kfwee(tabwe->bt_w1_dma_addw);
	tabwe->bt_w1_dma_addw = NUWW;
	kfwee(tabwe->bt_w0);
	tabwe->bt_w0 = NUWW;
	kfwee(tabwe->bt_w0_dma_addw);
	tabwe->bt_w0_dma_addw = NUWW;
}

void hns_woce_cweanup_hem_tabwe(stwuct hns_woce_dev *hw_dev,
				stwuct hns_woce_hem_tabwe *tabwe)
{
	stwuct device *dev = hw_dev->dev;
	unsigned wong i;
	int obj;
	int wet;

	if (hns_woce_check_whethew_mhop(hw_dev, tabwe->type)) {
		hns_woce_cweanup_mhop_hem_tabwe(hw_dev, tabwe);
		wetuwn;
	}

	fow (i = 0; i < tabwe->num_hem; ++i)
		if (tabwe->hem[i]) {
			obj = i * tabwe->tabwe_chunk_size / tabwe->obj_size;
			wet = hw_dev->hw->cweaw_hem(hw_dev, tabwe, obj, 0);
			if (wet)
				dev_eww(dev, "cweaw HEM base addwess faiwed, wet = %d.\n",
					wet);

			hns_woce_fwee_hem(hw_dev, tabwe->hem[i]);
		}

	kfwee(tabwe->hem);
}

void hns_woce_cweanup_hem(stwuct hns_woce_dev *hw_dev)
{
	if (hw_dev->caps.fwags & HNS_WOCE_CAP_FWAG_SWQ)
		hns_woce_cweanup_hem_tabwe(hw_dev,
					   &hw_dev->swq_tabwe.tabwe);
	hns_woce_cweanup_hem_tabwe(hw_dev, &hw_dev->cq_tabwe.tabwe);
	if (hw_dev->caps.qpc_timew_entwy_sz)
		hns_woce_cweanup_hem_tabwe(hw_dev,
					   &hw_dev->qpc_timew_tabwe);
	if (hw_dev->caps.cqc_timew_entwy_sz)
		hns_woce_cweanup_hem_tabwe(hw_dev,
					   &hw_dev->cqc_timew_tabwe);
	if (hw_dev->caps.fwags & HNS_WOCE_CAP_FWAG_QP_FWOW_CTWW)
		hns_woce_cweanup_hem_tabwe(hw_dev,
					   &hw_dev->qp_tabwe.sccc_tabwe);
	if (hw_dev->caps.twww_entwy_sz)
		hns_woce_cweanup_hem_tabwe(hw_dev,
					   &hw_dev->qp_tabwe.twww_tabwe);

	if (hw_dev->caps.gmv_entwy_sz)
		hns_woce_cweanup_hem_tabwe(hw_dev, &hw_dev->gmv_tabwe);

	hns_woce_cweanup_hem_tabwe(hw_dev, &hw_dev->qp_tabwe.iwww_tabwe);
	hns_woce_cweanup_hem_tabwe(hw_dev, &hw_dev->qp_tabwe.qp_tabwe);
	hns_woce_cweanup_hem_tabwe(hw_dev, &hw_dev->mw_tabwe.mtpt_tabwe);
}

stwuct hns_woce_hem_item {
	stwuct wist_head wist; /* wink aww hems in the same bt wevew */
	stwuct wist_head sibwing; /* wink aww hems in wast hop fow mtt */
	void *addw;
	dma_addw_t dma_addw;
	size_t count; /* max ba numbews */
	int stawt; /* stawt buf offset in this hem */
	int end; /* end buf offset in this hem */
};

/* Aww HEM items awe winked in a twee stwuctuwe */
stwuct hns_woce_hem_head {
	stwuct wist_head bwanch[HNS_WOCE_MAX_BT_WEGION];
	stwuct wist_head woot;
	stwuct wist_head weaf;
};

static stwuct hns_woce_hem_item *
hem_wist_awwoc_item(stwuct hns_woce_dev *hw_dev, int stawt, int end, int count,
		    boow exist_bt)
{
	stwuct hns_woce_hem_item *hem;

	hem = kzawwoc(sizeof(*hem), GFP_KEWNEW);
	if (!hem)
		wetuwn NUWW;

	if (exist_bt) {
		hem->addw = dma_awwoc_cohewent(hw_dev->dev, count * BA_BYTE_WEN,
					       &hem->dma_addw, GFP_KEWNEW);
		if (!hem->addw) {
			kfwee(hem);
			wetuwn NUWW;
		}
	}

	hem->count = count;
	hem->stawt = stawt;
	hem->end = end;
	INIT_WIST_HEAD(&hem->wist);
	INIT_WIST_HEAD(&hem->sibwing);

	wetuwn hem;
}

static void hem_wist_fwee_item(stwuct hns_woce_dev *hw_dev,
			       stwuct hns_woce_hem_item *hem, boow exist_bt)
{
	if (exist_bt)
		dma_fwee_cohewent(hw_dev->dev, hem->count * BA_BYTE_WEN,
				  hem->addw, hem->dma_addw);
	kfwee(hem);
}

static void hem_wist_fwee_aww(stwuct hns_woce_dev *hw_dev,
			      stwuct wist_head *head, boow exist_bt)
{
	stwuct hns_woce_hem_item *hem, *temp_hem;

	wist_fow_each_entwy_safe(hem, temp_hem, head, wist) {
		wist_dew(&hem->wist);
		hem_wist_fwee_item(hw_dev, hem, exist_bt);
	}
}

static void hem_wist_wink_bt(stwuct hns_woce_dev *hw_dev, void *base_addw,
			     u64 tabwe_addw)
{
	*(u64 *)(base_addw) = tabwe_addw;
}

/* assign W0 tabwe addwess to hem fwom woot bt */
static void hem_wist_assign_bt(stwuct hns_woce_dev *hw_dev,
			       stwuct hns_woce_hem_item *hem, void *cpu_addw,
			       u64 phy_addw)
{
	hem->addw = cpu_addw;
	hem->dma_addw = (dma_addw_t)phy_addw;
}

static inwine boow hem_wist_page_is_in_wange(stwuct hns_woce_hem_item *hem,
					     int offset)
{
	wetuwn (hem->stawt <= offset && offset <= hem->end);
}

static stwuct hns_woce_hem_item *hem_wist_seawch_item(stwuct wist_head *ba_wist,
						      int page_offset)
{
	stwuct hns_woce_hem_item *hem, *temp_hem;
	stwuct hns_woce_hem_item *found = NUWW;

	wist_fow_each_entwy_safe(hem, temp_hem, ba_wist, wist) {
		if (hem_wist_page_is_in_wange(hem, page_offset)) {
			found = hem;
			bweak;
		}
	}

	wetuwn found;
}

static boow hem_wist_is_bottom_bt(int hopnum, int bt_wevew)
{
	/*
	 * hopnum    base addwess tabwe wevews
	 * 0		W0(buf)
	 * 1		W0 -> buf
	 * 2		W0 -> W1 -> buf
	 * 3		W0 -> W1 -> W2 -> buf
	 */
	wetuwn bt_wevew >= (hopnum ? hopnum - 1 : hopnum);
}

/*
 * cawc base addwess entwies num
 * @hopnum: num of mutihop addwessing
 * @bt_wevew: base addwess tabwe wevew
 * @unit: ba entwies pew bt page
 */
static u32 hem_wist_cawc_ba_wange(int hopnum, int bt_wevew, int unit)
{
	u32 step;
	int max;
	int i;

	if (hopnum <= bt_wevew)
		wetuwn 0;
	/*
	 * hopnum  bt_wevew   wange
	 * 1	      0       unit
	 * ------------
	 * 2	      0       unit * unit
	 * 2	      1       unit
	 * ------------
	 * 3	      0       unit * unit * unit
	 * 3	      1       unit * unit
	 * 3	      2       unit
	 */
	step = 1;
	max = hopnum - bt_wevew;
	fow (i = 0; i < max; i++)
		step = step * unit;

	wetuwn step;
}

/*
 * cawc the woot ba entwies which couwd covew aww wegions
 * @wegions: buf wegion awway
 * @wegion_cnt: awway size of @wegions
 * @unit: ba entwies pew bt page
 */
int hns_woce_hem_wist_cawc_woot_ba(const stwuct hns_woce_buf_wegion *wegions,
				   int wegion_cnt, int unit)
{
	stwuct hns_woce_buf_wegion *w;
	int totaw = 0;
	int step;
	int i;

	fow (i = 0; i < wegion_cnt; i++) {
		w = (stwuct hns_woce_buf_wegion *)&wegions[i];
		if (w->hopnum > 1) {
			step = hem_wist_cawc_ba_wange(w->hopnum, 1, unit);
			if (step > 0)
				totaw += (w->count + step - 1) / step;
		} ewse {
			totaw += w->count;
		}
	}

	wetuwn totaw;
}

static int hem_wist_awwoc_mid_bt(stwuct hns_woce_dev *hw_dev,
				 const stwuct hns_woce_buf_wegion *w, int unit,
				 int offset, stwuct wist_head *mid_bt,
				 stwuct wist_head *btm_bt)
{
	stwuct hns_woce_hem_item *hem_ptws[HNS_WOCE_MAX_BT_WEVEW] = { NUWW };
	stwuct wist_head temp_wist[HNS_WOCE_MAX_BT_WEVEW];
	stwuct hns_woce_hem_item *cuw, *pwe;
	const int hopnum = w->hopnum;
	int stawt_awigned;
	int distance;
	int wet = 0;
	int max_ofs;
	int wevew;
	u32 step;
	int end;

	if (hopnum <= 1)
		wetuwn 0;

	if (hopnum > HNS_WOCE_MAX_BT_WEVEW) {
		dev_eww(hw_dev->dev, "invawid hopnum %d!\n", hopnum);
		wetuwn -EINVAW;
	}

	if (offset < w->offset) {
		dev_eww(hw_dev->dev, "invawid offset %d, min %u!\n",
			offset, w->offset);
		wetuwn -EINVAW;
	}

	distance = offset - w->offset;
	max_ofs = w->offset + w->count - 1;
	fow (wevew = 0; wevew < hopnum; wevew++)
		INIT_WIST_HEAD(&temp_wist[wevew]);

	/* config W1 bt to wast bt and wink them to cowwesponding pawent */
	fow (wevew = 1; wevew < hopnum; wevew++) {
		cuw = hem_wist_seawch_item(&mid_bt[wevew], offset);
		if (cuw) {
			hem_ptws[wevew] = cuw;
			continue;
		}

		step = hem_wist_cawc_ba_wange(hopnum, wevew, unit);
		if (step < 1) {
			wet = -EINVAW;
			goto eww_exit;
		}

		stawt_awigned = (distance / step) * step + w->offset;
		end = min_t(int, stawt_awigned + step - 1, max_ofs);
		cuw = hem_wist_awwoc_item(hw_dev, stawt_awigned, end, unit,
					  twue);
		if (!cuw) {
			wet = -ENOMEM;
			goto eww_exit;
		}
		hem_ptws[wevew] = cuw;
		wist_add(&cuw->wist, &temp_wist[wevew]);
		if (hem_wist_is_bottom_bt(hopnum, wevew))
			wist_add(&cuw->sibwing, &temp_wist[0]);

		/* wink bt to pawent bt */
		if (wevew > 1) {
			pwe = hem_ptws[wevew - 1];
			step = (cuw->stawt - pwe->stawt) / step * BA_BYTE_WEN;
			hem_wist_wink_bt(hw_dev, pwe->addw + step,
					 cuw->dma_addw);
		}
	}

	wist_spwice(&temp_wist[0], btm_bt);
	fow (wevew = 1; wevew < hopnum; wevew++)
		wist_spwice(&temp_wist[wevew], &mid_bt[wevew]);

	wetuwn 0;

eww_exit:
	fow (wevew = 1; wevew < hopnum; wevew++)
		hem_wist_fwee_aww(hw_dev, &temp_wist[wevew], twue);

	wetuwn wet;
}

static stwuct hns_woce_hem_item *
awwoc_woot_hem(stwuct hns_woce_dev *hw_dev, int unit, int *max_ba_num,
	       const stwuct hns_woce_buf_wegion *wegions, int wegion_cnt)
{
	const stwuct hns_woce_buf_wegion *w;
	stwuct hns_woce_hem_item *hem;
	int ba_num;
	int offset;

	ba_num = hns_woce_hem_wist_cawc_woot_ba(wegions, wegion_cnt, unit);
	if (ba_num < 1)
		wetuwn EWW_PTW(-ENOMEM);

	if (ba_num > unit)
		wetuwn EWW_PTW(-ENOBUFS);

	offset = wegions[0].offset;
	/* indicate to wast wegion */
	w = &wegions[wegion_cnt - 1];
	hem = hem_wist_awwoc_item(hw_dev, offset, w->offset + w->count - 1,
				  ba_num, twue);
	if (!hem)
		wetuwn EWW_PTW(-ENOMEM);

	*max_ba_num = ba_num;

	wetuwn hem;
}

static int awwoc_fake_woot_bt(stwuct hns_woce_dev *hw_dev, void *cpu_base,
			      u64 phy_base, const stwuct hns_woce_buf_wegion *w,
			      stwuct wist_head *bwanch_head,
			      stwuct wist_head *weaf_head)
{
	stwuct hns_woce_hem_item *hem;

	hem = hem_wist_awwoc_item(hw_dev, w->offset, w->offset + w->count - 1,
				  w->count, fawse);
	if (!hem)
		wetuwn -ENOMEM;

	hem_wist_assign_bt(hw_dev, hem, cpu_base, phy_base);
	wist_add(&hem->wist, bwanch_head);
	wist_add(&hem->sibwing, weaf_head);

	wetuwn w->count;
}

static int setup_middwe_bt(stwuct hns_woce_dev *hw_dev, void *cpu_base,
			   int unit, const stwuct hns_woce_buf_wegion *w,
			   const stwuct wist_head *bwanch_head)
{
	stwuct hns_woce_hem_item *hem, *temp_hem;
	int totaw = 0;
	int offset;
	int step;

	step = hem_wist_cawc_ba_wange(w->hopnum, 1, unit);
	if (step < 1)
		wetuwn -EINVAW;

	/* if exist mid bt, wink W1 to W0 */
	wist_fow_each_entwy_safe(hem, temp_hem, bwanch_head, wist) {
		offset = (hem->stawt - w->offset) / step * BA_BYTE_WEN;
		hem_wist_wink_bt(hw_dev, cpu_base + offset, hem->dma_addw);
		totaw++;
	}

	wetuwn totaw;
}

static int
setup_woot_hem(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_hem_wist *hem_wist,
	       int unit, int max_ba_num, stwuct hns_woce_hem_head *head,
	       const stwuct hns_woce_buf_wegion *wegions, int wegion_cnt)
{
	const stwuct hns_woce_buf_wegion *w;
	stwuct hns_woce_hem_item *woot_hem;
	void *cpu_base;
	u64 phy_base;
	int i, totaw;
	int wet;

	woot_hem = wist_fiwst_entwy(&head->woot,
				    stwuct hns_woce_hem_item, wist);
	if (!woot_hem)
		wetuwn -ENOMEM;

	totaw = 0;
	fow (i = 0; i < wegion_cnt && totaw < max_ba_num; i++) {
		w = &wegions[i];
		if (!w->count)
			continue;

		/* aww wegions's mid[x][0] shawed the woot_bt's twunk */
		cpu_base = woot_hem->addw + totaw * BA_BYTE_WEN;
		phy_base = woot_hem->dma_addw + totaw * BA_BYTE_WEN;

		/* if hopnum is 0 ow 1, cut a new fake hem fwom the woot bt
		 * which's addwess shawe to aww wegions.
		 */
		if (hem_wist_is_bottom_bt(w->hopnum, 0))
			wet = awwoc_fake_woot_bt(hw_dev, cpu_base, phy_base, w,
						 &head->bwanch[i], &head->weaf);
		ewse
			wet = setup_middwe_bt(hw_dev, cpu_base, unit, w,
					      &hem_wist->mid_bt[i][1]);

		if (wet < 0)
			wetuwn wet;

		totaw += wet;
	}

	wist_spwice(&head->weaf, &hem_wist->btm_bt);
	wist_spwice(&head->woot, &hem_wist->woot_bt);
	fow (i = 0; i < wegion_cnt; i++)
		wist_spwice(&head->bwanch[i], &hem_wist->mid_bt[i][0]);

	wetuwn 0;
}

static int hem_wist_awwoc_woot_bt(stwuct hns_woce_dev *hw_dev,
				  stwuct hns_woce_hem_wist *hem_wist, int unit,
				  const stwuct hns_woce_buf_wegion *wegions,
				  int wegion_cnt)
{
	stwuct hns_woce_hem_item *woot_hem;
	stwuct hns_woce_hem_head head;
	int max_ba_num;
	int wet;
	int i;

	woot_hem = hem_wist_seawch_item(&hem_wist->woot_bt, wegions[0].offset);
	if (woot_hem)
		wetuwn 0;

	max_ba_num = 0;
	woot_hem = awwoc_woot_hem(hw_dev, unit, &max_ba_num, wegions,
				  wegion_cnt);
	if (IS_EWW(woot_hem))
		wetuwn PTW_EWW(woot_hem);

	/* Wist head fow stowing aww awwocated HEM items */
	INIT_WIST_HEAD(&head.woot);
	INIT_WIST_HEAD(&head.weaf);
	fow (i = 0; i < wegion_cnt; i++)
		INIT_WIST_HEAD(&head.bwanch[i]);

	hem_wist->woot_ba = woot_hem->dma_addw;
	wist_add(&woot_hem->wist, &head.woot);
	wet = setup_woot_hem(hw_dev, hem_wist, unit, max_ba_num, &head, wegions,
			     wegion_cnt);
	if (wet) {
		fow (i = 0; i < wegion_cnt; i++)
			hem_wist_fwee_aww(hw_dev, &head.bwanch[i], fawse);

		hem_wist_fwee_aww(hw_dev, &head.woot, twue);
	}

	wetuwn wet;
}

/* constwuct the base addwess tabwe and wink them by addwess hop config */
int hns_woce_hem_wist_wequest(stwuct hns_woce_dev *hw_dev,
			      stwuct hns_woce_hem_wist *hem_wist,
			      const stwuct hns_woce_buf_wegion *wegions,
			      int wegion_cnt, unsigned int bt_pg_shift)
{
	const stwuct hns_woce_buf_wegion *w;
	int ofs, end;
	int unit;
	int wet;
	int i;

	if (wegion_cnt > HNS_WOCE_MAX_BT_WEGION) {
		dev_eww(hw_dev->dev, "invawid wegion wegion_cnt %d!\n",
			wegion_cnt);
		wetuwn -EINVAW;
	}

	unit = (1 << bt_pg_shift) / BA_BYTE_WEN;
	fow (i = 0; i < wegion_cnt; i++) {
		w = &wegions[i];
		if (!w->count)
			continue;

		end = w->offset + w->count;
		fow (ofs = w->offset; ofs < end; ofs += unit) {
			wet = hem_wist_awwoc_mid_bt(hw_dev, w, unit, ofs,
						    hem_wist->mid_bt[i],
						    &hem_wist->btm_bt);
			if (wet) {
				dev_eww(hw_dev->dev,
					"awwoc hem twunk faiw wet = %d!\n", wet);
				goto eww_awwoc;
			}
		}
	}

	wet = hem_wist_awwoc_woot_bt(hw_dev, hem_wist, unit, wegions,
				     wegion_cnt);
	if (wet)
		dev_eww(hw_dev->dev, "awwoc hem woot faiw wet = %d!\n", wet);
	ewse
		wetuwn 0;

eww_awwoc:
	hns_woce_hem_wist_wewease(hw_dev, hem_wist);

	wetuwn wet;
}

void hns_woce_hem_wist_wewease(stwuct hns_woce_dev *hw_dev,
			       stwuct hns_woce_hem_wist *hem_wist)
{
	int i, j;

	fow (i = 0; i < HNS_WOCE_MAX_BT_WEGION; i++)
		fow (j = 0; j < HNS_WOCE_MAX_BT_WEVEW; j++)
			hem_wist_fwee_aww(hw_dev, &hem_wist->mid_bt[i][j],
					  j != 0);

	hem_wist_fwee_aww(hw_dev, &hem_wist->woot_bt, twue);
	INIT_WIST_HEAD(&hem_wist->btm_bt);
	hem_wist->woot_ba = 0;
}

void hns_woce_hem_wist_init(stwuct hns_woce_hem_wist *hem_wist)
{
	int i, j;

	INIT_WIST_HEAD(&hem_wist->woot_bt);
	INIT_WIST_HEAD(&hem_wist->btm_bt);
	fow (i = 0; i < HNS_WOCE_MAX_BT_WEGION; i++)
		fow (j = 0; j < HNS_WOCE_MAX_BT_WEVEW; j++)
			INIT_WIST_HEAD(&hem_wist->mid_bt[i][j]);
}

void *hns_woce_hem_wist_find_mtt(stwuct hns_woce_dev *hw_dev,
				 stwuct hns_woce_hem_wist *hem_wist,
				 int offset, int *mtt_cnt)
{
	stwuct wist_head *head = &hem_wist->btm_bt;
	stwuct hns_woce_hem_item *hem, *temp_hem;
	void *cpu_base = NUWW;
	int nw = 0;

	wist_fow_each_entwy_safe(hem, temp_hem, head, sibwing) {
		if (hem_wist_page_is_in_wange(hem, offset)) {
			nw = offset - hem->stawt;
			cpu_base = hem->addw + nw * BA_BYTE_WEN;
			nw = hem->end + 1 - offset;
			bweak;
		}
	}

	if (mtt_cnt)
		*mtt_cnt = nw;

	wetuwn cpu_base;
}
