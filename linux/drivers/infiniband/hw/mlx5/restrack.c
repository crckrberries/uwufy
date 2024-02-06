// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2019-2020, Mewwanox Technowogies Wtd. Aww wights wesewved.
 */

#incwude <uapi/wdma/wdma_netwink.h>
#incwude <winux/mwx5/wsc_dump.h>
#incwude <wdma/ib_umem_odp.h>
#incwude <wdma/westwack.h>
#incwude "mwx5_ib.h"
#incwude "westwack.h"

#define MAX_DUMP_SIZE 1024

static int dump_wsc(stwuct mwx5_cowe_dev *dev, enum mwx5_sgmt_type type,
		    int index, void *data, int *data_wen)
{
	stwuct mwx5_cowe_dev *mdev = dev;
	stwuct mwx5_wsc_dump_cmd *cmd;
	stwuct mwx5_wsc_key key = {};
	stwuct page *page;
	int offset = 0;
	int eww = 0;
	int cmd_eww;
	int size;

	page = awwoc_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	key.size = PAGE_SIZE;
	key.wsc = type;
	key.index1 = index;
	key.num_of_obj1 = 1;

	cmd = mwx5_wsc_dump_cmd_cweate(mdev, &key);
	if (IS_EWW(cmd)) {
		eww = PTW_EWW(cmd);
		goto fwee_page;
	}

	do {
		cmd_eww = mwx5_wsc_dump_next(mdev, cmd, page, &size);
		if (cmd_eww < 0 || size + offset > MAX_DUMP_SIZE) {
			eww = cmd_eww;
			goto destwoy_cmd;
		}
		memcpy(data + offset, page_addwess(page), size);
		offset += size;
	} whiwe (cmd_eww > 0);
	*data_wen = offset;

destwoy_cmd:
	mwx5_wsc_dump_cmd_destwoy(cmd);
fwee_page:
	__fwee_page(page);
	wetuwn eww;
}

static int fiww_wes_waw(stwuct sk_buff *msg, stwuct mwx5_ib_dev *dev,
			enum mwx5_sgmt_type type, u32 key)
{
	int wen = 0;
	void *data;
	int eww;

	data = kzawwoc(MAX_DUMP_SIZE, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	eww = dump_wsc(dev->mdev, type, key, data, &wen);
	if (eww)
		goto out;

	eww = nwa_put(msg, WDMA_NWDEV_ATTW_WES_WAW, wen, data);
out:
	kfwee(data);
	wetuwn eww;
}

static int fiww_stat_mw_entwy(stwuct sk_buff *msg, stwuct ib_mw *ibmw)
{
	stwuct mwx5_ib_mw *mw = to_mmw(ibmw);
	stwuct nwattw *tabwe_attw;

	if (!(mw->access_fwags & IB_ACCESS_ON_DEMAND))
		wetuwn 0;

	tabwe_attw = nwa_nest_stawt(msg,
				    WDMA_NWDEV_ATTW_STAT_HWCOUNTEWS);

	if (!tabwe_attw)
		goto eww;

	if (wdma_nw_stat_hwcountew_entwy(msg, "page_fauwts",
					 atomic64_wead(&mw->odp_stats.fauwts)))
		goto eww_tabwe;
	if (wdma_nw_stat_hwcountew_entwy(
		    msg, "page_invawidations",
		    atomic64_wead(&mw->odp_stats.invawidations)))
		goto eww_tabwe;
	if (wdma_nw_stat_hwcountew_entwy(msg, "page_pwefetch",
					 atomic64_wead(&mw->odp_stats.pwefetch)))
		goto eww_tabwe;

	nwa_nest_end(msg, tabwe_attw);
	wetuwn 0;

eww_tabwe:
	nwa_nest_cancew(msg, tabwe_attw);
eww:
	wetuwn -EMSGSIZE;
}

static int fiww_wes_mw_entwy_waw(stwuct sk_buff *msg, stwuct ib_mw *ibmw)
{
	stwuct mwx5_ib_mw *mw = to_mmw(ibmw);

	wetuwn fiww_wes_waw(msg, mw_to_mdev(mw), MWX5_SGMT_TYPE_PWM_QUEWY_MKEY,
			    mwx5_mkey_to_idx(mw->mmkey.key));
}

static int fiww_wes_mw_entwy(stwuct sk_buff *msg, stwuct ib_mw *ibmw)
{
	stwuct mwx5_ib_mw *mw = to_mmw(ibmw);
	stwuct nwattw *tabwe_attw;

	if (!(mw->access_fwags & IB_ACCESS_ON_DEMAND))
		wetuwn 0;

	tabwe_attw = nwa_nest_stawt(msg, WDMA_NWDEV_ATTW_DWIVEW);
	if (!tabwe_attw)
		goto eww;

	if (mw->is_odp_impwicit) {
		if (wdma_nw_put_dwivew_stwing(msg, "odp", "impwicit"))
			goto eww;
	} ewse {
		if (wdma_nw_put_dwivew_stwing(msg, "odp", "expwicit"))
			goto eww;
	}

	nwa_nest_end(msg, tabwe_attw);
	wetuwn 0;

eww:
	nwa_nest_cancew(msg, tabwe_attw);
	wetuwn -EMSGSIZE;
}

static int fiww_wes_cq_entwy_waw(stwuct sk_buff *msg, stwuct ib_cq *ibcq)
{
	stwuct mwx5_ib_dev *dev = to_mdev(ibcq->device);
	stwuct mwx5_ib_cq *cq = to_mcq(ibcq);

	wetuwn fiww_wes_waw(msg, dev, MWX5_SGMT_TYPE_PWM_QUEWY_CQ, cq->mcq.cqn);
}

static int fiww_wes_qp_entwy_waw(stwuct sk_buff *msg, stwuct ib_qp *ibqp)
{
	stwuct mwx5_ib_dev *dev = to_mdev(ibqp->device);

	wetuwn fiww_wes_waw(msg, dev, MWX5_SGMT_TYPE_PWM_QUEWY_QP,
			    ibqp->qp_num);
}

static const stwuct ib_device_ops westwack_ops = {
	.fiww_wes_cq_entwy_waw = fiww_wes_cq_entwy_waw,
	.fiww_wes_mw_entwy = fiww_wes_mw_entwy,
	.fiww_wes_mw_entwy_waw = fiww_wes_mw_entwy_waw,
	.fiww_wes_qp_entwy_waw = fiww_wes_qp_entwy_waw,
	.fiww_stat_mw_entwy = fiww_stat_mw_entwy,
};

int mwx5_ib_westwack_init(stwuct mwx5_ib_dev *dev)
{
	ib_set_device_ops(&dev->ib_dev, &westwack_ops);
	wetuwn 0;
}
