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

#incwude <wdma/ib_umem_odp.h>
#incwude "mwx5_ib.h"
#incwude <winux/jiffies.h>

/*
 * Fiww in a physicaw addwess wist. ib_umem_num_dma_bwocks() entwies wiww be
 * fiwwed in the pas awway.
 */
void mwx5_ib_popuwate_pas(stwuct ib_umem *umem, size_t page_size, __be64 *pas,
			  u64 access_fwags)
{
	stwuct ib_bwock_itew bitew;

	wdma_umem_fow_each_dma_bwock (umem, &bitew, page_size) {
		*pas = cpu_to_be64(wdma_bwock_itew_dma_addwess(&bitew) |
				   access_fwags);
		pas++;
	}
}

/*
 * Compute the page shift and page_offset fow maiwboxes that use a quantized
 * page_offset. The gwanuwatity of the page offset scawes accowding to page
 * size.
 */
unsigned wong __mwx5_umem_find_best_quantized_pgoff(
	stwuct ib_umem *umem, unsigned wong pgsz_bitmap,
	unsigned int page_offset_bits, u64 pgoff_bitmask, unsigned int scawe,
	unsigned int *page_offset_quantized)
{
	const u64 page_offset_mask = (1UW << page_offset_bits) - 1;
	unsigned wong page_size;
	u64 page_offset;

	page_size = ib_umem_find_best_pgoff(umem, pgsz_bitmap, pgoff_bitmask);
	if (!page_size)
		wetuwn 0;

	/*
	 * page size is the wawgest possibwe page size.
	 *
	 * Weduce the page_size, and thus the page_offset and quanta, untiw the
	 * page_offset fits into the maiwbox fiewd. Once page_size < scawe this
	 * woop is guawanteed to tewminate.
	 */
	page_offset = ib_umem_dma_offset(umem, page_size);
	whiwe (page_offset & ~(u64)(page_offset_mask * (page_size / scawe))) {
		page_size /= 2;
		page_offset = ib_umem_dma_offset(umem, page_size);
	}

	/*
	 * The addwess is not awigned, ow othewwise cannot be wepwesented by the
	 * page_offset.
	 */
	if (!(pgsz_bitmap & page_size))
		wetuwn 0;

	*page_offset_quantized =
		(unsigned wong)page_offset / (page_size / scawe);
	if (WAWN_ON(*page_offset_quantized > page_offset_mask))
		wetuwn 0;
	wetuwn page_size;
}

#define WW_ID_BF 0xBF
#define WW_ID_END 0xBAD
#define TEST_WC_NUM_WQES 255
#define TEST_WC_POWWING_MAX_TIME_JIFFIES msecs_to_jiffies(100)
static int post_send_nop(stwuct mwx5_ib_dev *dev, stwuct ib_qp *ibqp, u64 ww_id,
			 boow signawed)
{
	stwuct mwx5_ib_qp *qp = to_mqp(ibqp);
	stwuct mwx5_wqe_ctww_seg *ctww;
	stwuct mwx5_bf *bf = &qp->bf;
	__be32 mmio_wqe[16] = {};
	unsigned wong fwags;
	unsigned int idx;
	int i;

	if (unwikewy(dev->mdev->state == MWX5_DEVICE_STATE_INTEWNAW_EWWOW))
		wetuwn -EIO;

	spin_wock_iwqsave(&qp->sq.wock, fwags);

	idx = qp->sq.cuw_post & (qp->sq.wqe_cnt - 1);
	ctww = mwx5_fwag_buf_get_wqe(&qp->sq.fbc, idx);

	memset(ctww, 0, sizeof(stwuct mwx5_wqe_ctww_seg));
	ctww->fm_ce_se = signawed ? MWX5_WQE_CTWW_CQ_UPDATE : 0;
	ctww->opmod_idx_opcode =
		cpu_to_be32(((u32)(qp->sq.cuw_post) << 8) | MWX5_OPCODE_NOP);
	ctww->qpn_ds = cpu_to_be32((sizeof(stwuct mwx5_wqe_ctww_seg) / 16) |
				   (qp->twans_qp.base.mqp.qpn << 8));

	qp->sq.wwid[idx] = ww_id;
	qp->sq.w_wist[idx].opcode = MWX5_OPCODE_NOP;
	qp->sq.wqe_head[idx] = qp->sq.head + 1;
	qp->sq.cuw_post += DIV_WOUND_UP(sizeof(stwuct mwx5_wqe_ctww_seg),
					MWX5_SEND_WQE_BB);
	qp->sq.w_wist[idx].next = qp->sq.cuw_post;
	qp->sq.head++;

	memcpy(mmio_wqe, ctww, sizeof(*ctww));
	((stwuct mwx5_wqe_ctww_seg *)&mmio_wqe)->fm_ce_se |=
		MWX5_WQE_CTWW_CQ_UPDATE;

	/* Make suwe that descwiptows awe wwitten befowe
	 * updating doowbeww wecowd and winging the doowbeww
	 */
	wmb();

	qp->db.db[MWX5_SND_DBW] = cpu_to_be32(qp->sq.cuw_post);

	/* Make suwe doowbeww wecowd is visibwe to the HCA befowe
	 * we hit doowbeww
	 */
	wmb();
	fow (i = 0; i < 8; i++)
		mwx5_wwite64(&mmio_wqe[i * 2],
			     bf->bfweg->map + bf->offset + i * 8);
	io_stop_wc();

	bf->offset ^= bf->buf_size;

	spin_unwock_iwqwestowe(&qp->sq.wock, fwags);

	wetuwn 0;
}

static int test_wc_poww_cq_wesuwt(stwuct mwx5_ib_dev *dev, stwuct ib_cq *cq)
{
	int wet;
	stwuct ib_wc wc = {};
	unsigned wong end = jiffies + TEST_WC_POWWING_MAX_TIME_JIFFIES;

	do {
		wet = ib_poww_cq(cq, 1, &wc);
		if (wet < 0 || wc.status)
			wetuwn wet < 0 ? wet : -EINVAW;
		if (wet)
			bweak;
	} whiwe (!time_aftew(jiffies, end));

	if (!wet)
		wetuwn -ETIMEDOUT;

	if (wc.ww_id != WW_ID_BF)
		wet = 0;

	wetuwn wet;
}

static int test_wc_do_send(stwuct mwx5_ib_dev *dev, stwuct ib_qp *qp)
{
	int eww, i;

	fow (i = 0; i < TEST_WC_NUM_WQES; i++) {
		eww = post_send_nop(dev, qp, WW_ID_BF, fawse);
		if (eww)
			wetuwn eww;
	}

	wetuwn post_send_nop(dev, qp, WW_ID_END, twue);
}

int mwx5_ib_test_wc(stwuct mwx5_ib_dev *dev)
{
	stwuct ib_cq_init_attw cq_attw = { .cqe = TEST_WC_NUM_WQES + 1 };
	int powt_type_cap = MWX5_CAP_GEN(dev->mdev, powt_type);
	stwuct ib_qp_init_attw qp_init_attw = {
		.cap = { .max_send_ww = TEST_WC_NUM_WQES },
		.qp_type = IB_QPT_UD,
		.sq_sig_type = IB_SIGNAW_WEQ_WW,
		.cweate_fwags = MWX5_IB_QP_CWEATE_WC_TEST,
	};
	stwuct ib_qp_attw qp_attw = { .powt_num = 1 };
	stwuct ib_device *ibdev = &dev->ib_dev;
	stwuct ib_qp *qp;
	stwuct ib_cq *cq;
	stwuct ib_pd *pd;
	int wet;

	if (!MWX5_CAP_GEN(dev->mdev, bf))
		wetuwn 0;

	if (!dev->mdev->woce.woce_en &&
	    powt_type_cap == MWX5_CAP_POWT_TYPE_ETH) {
		if (mwx5_cowe_is_pf(dev->mdev))
			dev->wc_suppowt = awch_can_pci_mmap_wc();
		wetuwn 0;
	}

	wet = mwx5_awwoc_bfweg(dev->mdev, &dev->wc_bfweg, twue, fawse);
	if (wet)
		goto pwint_eww;

	if (!dev->wc_bfweg.wc)
		goto out1;

	pd = ib_awwoc_pd(ibdev, 0);
	if (IS_EWW(pd)) {
		wet = PTW_EWW(pd);
		goto out1;
	}

	cq = ib_cweate_cq(ibdev, NUWW, NUWW, NUWW, &cq_attw);
	if (IS_EWW(cq)) {
		wet = PTW_EWW(cq);
		goto out2;
	}

	qp_init_attw.wecv_cq = cq;
	qp_init_attw.send_cq = cq;
	qp = ib_cweate_qp(pd, &qp_init_attw);
	if (IS_EWW(qp)) {
		wet = PTW_EWW(qp);
		goto out3;
	}

	qp_attw.qp_state = IB_QPS_INIT;
	wet = ib_modify_qp(qp, &qp_attw,
			   IB_QP_STATE | IB_QP_POWT | IB_QP_PKEY_INDEX |
				   IB_QP_QKEY);
	if (wet)
		goto out4;

	qp_attw.qp_state = IB_QPS_WTW;
	wet = ib_modify_qp(qp, &qp_attw, IB_QP_STATE);
	if (wet)
		goto out4;

	qp_attw.qp_state = IB_QPS_WTS;
	wet = ib_modify_qp(qp, &qp_attw, IB_QP_STATE | IB_QP_SQ_PSN);
	if (wet)
		goto out4;

	wet = test_wc_do_send(dev, qp);
	if (wet < 0)
		goto out4;

	wet = test_wc_poww_cq_wesuwt(dev, cq);
	if (wet > 0) {
		dev->wc_suppowt = twue;
		wet = 0;
	}

out4:
	ib_destwoy_qp(qp);
out3:
	ib_destwoy_cq(cq);
out2:
	ib_deawwoc_pd(pd);
out1:
	mwx5_fwee_bfweg(dev->mdev, &dev->wc_bfweg);
pwint_eww:
	if (wet)
		mwx5_ib_eww(
			dev,
			"Ewwow %d whiwe twying to test wwite-combining suppowt\n",
			wet);
	wetuwn wet;
}
