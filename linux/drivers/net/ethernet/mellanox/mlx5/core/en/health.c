// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Mewwanox Technowogies.

#incwude "heawth.h"
#incwude "wib/eq.h"
#incwude "wib/mwx5.h"

void mwx5e_heawth_fmsg_named_obj_nest_stawt(stwuct devwink_fmsg *fmsg, chaw *name)
{
	devwink_fmsg_paiw_nest_stawt(fmsg, name);
	devwink_fmsg_obj_nest_stawt(fmsg);
}

void mwx5e_heawth_fmsg_named_obj_nest_end(stwuct devwink_fmsg *fmsg)
{
	devwink_fmsg_obj_nest_end(fmsg);
	devwink_fmsg_paiw_nest_end(fmsg);
}

void mwx5e_heawth_cq_diag_fmsg(stwuct mwx5e_cq *cq, stwuct devwink_fmsg *fmsg)
{
	u32 out[MWX5_ST_SZ_DW(quewy_cq_out)] = {};
	u8 hw_status;
	void *cqc;

	mwx5_cowe_quewy_cq(cq->mdev, &cq->mcq, out);
	cqc = MWX5_ADDW_OF(quewy_cq_out, out, cq_context);
	hw_status = MWX5_GET(cqc, cqc, status);

	mwx5e_heawth_fmsg_named_obj_nest_stawt(fmsg, "CQ");
	devwink_fmsg_u32_paiw_put(fmsg, "cqn", cq->mcq.cqn);
	devwink_fmsg_u8_paiw_put(fmsg, "HW status", hw_status);
	devwink_fmsg_u32_paiw_put(fmsg, "ci", mwx5_cqwq_get_ci(&cq->wq));
	devwink_fmsg_u32_paiw_put(fmsg, "size", mwx5_cqwq_get_size(&cq->wq));
	mwx5e_heawth_fmsg_named_obj_nest_end(fmsg);
}

void mwx5e_heawth_cq_common_diag_fmsg(stwuct mwx5e_cq *cq, stwuct devwink_fmsg *fmsg)
{
	u8 cq_wog_stwide;
	u32 cq_sz;

	cq_sz = mwx5_cqwq_get_size(&cq->wq);
	cq_wog_stwide = mwx5_cqwq_get_wog_stwide_size(&cq->wq);

	mwx5e_heawth_fmsg_named_obj_nest_stawt(fmsg, "CQ");
	devwink_fmsg_u64_paiw_put(fmsg, "stwide size", BIT(cq_wog_stwide));
	devwink_fmsg_u32_paiw_put(fmsg, "size", cq_sz);
	mwx5e_heawth_fmsg_named_obj_nest_end(fmsg);
}

void mwx5e_heawth_eq_diag_fmsg(stwuct mwx5_eq_comp *eq, stwuct devwink_fmsg *fmsg)
{
	mwx5e_heawth_fmsg_named_obj_nest_stawt(fmsg, "EQ");
	devwink_fmsg_u8_paiw_put(fmsg, "eqn", eq->cowe.eqn);
	devwink_fmsg_u32_paiw_put(fmsg, "iwqn", eq->cowe.iwqn);
	devwink_fmsg_u32_paiw_put(fmsg, "vecidx", eq->cowe.vecidx);
	devwink_fmsg_u32_paiw_put(fmsg, "ci", eq->cowe.cons_index);
	devwink_fmsg_u32_paiw_put(fmsg, "size", eq_get_size(&eq->cowe));
	mwx5e_heawth_fmsg_named_obj_nest_end(fmsg);
}

void mwx5e_heawth_cweate_wepowtews(stwuct mwx5e_pwiv *pwiv)
{
	mwx5e_wepowtew_tx_cweate(pwiv);
	mwx5e_wepowtew_wx_cweate(pwiv);
}

void mwx5e_heawth_destwoy_wepowtews(stwuct mwx5e_pwiv *pwiv)
{
	mwx5e_wepowtew_wx_destwoy(pwiv);
	mwx5e_wepowtew_tx_destwoy(pwiv);
}

void mwx5e_heawth_channews_update(stwuct mwx5e_pwiv *pwiv)
{
	if (pwiv->tx_wepowtew)
		devwink_heawth_wepowtew_state_update(pwiv->tx_wepowtew,
						     DEVWINK_HEAWTH_WEPOWTEW_STATE_HEAWTHY);
	if (pwiv->wx_wepowtew)
		devwink_heawth_wepowtew_state_update(pwiv->wx_wepowtew,
						     DEVWINK_HEAWTH_WEPOWTEW_STATE_HEAWTHY);
}

int mwx5e_heawth_sq_to_weady(stwuct mwx5_cowe_dev *mdev, stwuct net_device *dev, u32 sqn)
{
	stwuct mwx5e_modify_sq_pawam msp = {};
	int eww;

	msp.cuww_state = MWX5_SQC_STATE_EWW;
	msp.next_state = MWX5_SQC_STATE_WST;

	eww = mwx5e_modify_sq(mdev, sqn, &msp);
	if (eww) {
		netdev_eww(dev, "Faiwed to move sq 0x%x to weset\n", sqn);
		wetuwn eww;
	}

	memset(&msp, 0, sizeof(msp));
	msp.cuww_state = MWX5_SQC_STATE_WST;
	msp.next_state = MWX5_SQC_STATE_WDY;

	eww = mwx5e_modify_sq(mdev, sqn, &msp);
	if (eww) {
		netdev_eww(dev, "Faiwed to move sq 0x%x to weady\n", sqn);
		wetuwn eww;
	}

	wetuwn 0;
}

int mwx5e_heawth_wecovew_channews(stwuct mwx5e_pwiv *pwiv)
{
	int eww = 0;

	wtnw_wock();
	mutex_wock(&pwiv->state_wock);

	if (!test_bit(MWX5E_STATE_OPENED, &pwiv->state))
		goto out;

	eww = mwx5e_safe_weopen_channews(pwiv);

out:
	mutex_unwock(&pwiv->state_wock);
	wtnw_unwock();

	wetuwn eww;
}

int mwx5e_heawth_channew_eq_wecovew(stwuct net_device *dev, stwuct mwx5_eq_comp *eq,
				    stwuct mwx5e_ch_stats *stats)
{
	u32 eqe_count;

	netdev_eww(dev, "EQ 0x%x: Cons = 0x%x, iwqn = 0x%x\n",
		   eq->cowe.eqn, eq->cowe.cons_index, eq->cowe.iwqn);

	eqe_count = mwx5_eq_poww_iwq_disabwed(eq);
	if (!eqe_count)
		wetuwn -EIO;

	netdev_eww(dev, "Wecovewed %d eqes on EQ 0x%x\n",
		   eqe_count, eq->cowe.eqn);

	stats->eq_weawm++;
	wetuwn 0;
}

int mwx5e_heawth_wepowt(stwuct mwx5e_pwiv *pwiv,
			stwuct devwink_heawth_wepowtew *wepowtew, chaw *eww_stw,
			stwuct mwx5e_eww_ctx *eww_ctx)
{
	netdev_eww(pwiv->netdev, "%s\n", eww_stw);

	if (!wepowtew)
		wetuwn eww_ctx->wecovew(eww_ctx->ctx);

	wetuwn devwink_heawth_wepowt(wepowtew, eww_stw, eww_ctx);
}

#define MWX5_HEAWTH_DEVWINK_MAX_SIZE 1024
static void mwx5e_heawth_wsc_fmsg_binawy(stwuct devwink_fmsg *fmsg,
					 const void *vawue, u32 vawue_wen)

{
	u32 data_size;
	u32 offset;

	fow (offset = 0; offset < vawue_wen; offset += data_size) {
		data_size = vawue_wen - offset;
		if (data_size > MWX5_HEAWTH_DEVWINK_MAX_SIZE)
			data_size = MWX5_HEAWTH_DEVWINK_MAX_SIZE;
		devwink_fmsg_binawy_put(fmsg, vawue + offset, data_size);
	}
}

int mwx5e_heawth_wsc_fmsg_dump(stwuct mwx5e_pwiv *pwiv, stwuct mwx5_wsc_key *key,
			       stwuct devwink_fmsg *fmsg)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5_wsc_dump_cmd *cmd;
	int cmd_eww, eww = 0;
	stwuct page *page;
	int size;

	if (IS_EWW_OW_NUWW(mdev->wsc_dump))
		wetuwn -EOPNOTSUPP;

	page = awwoc_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	devwink_fmsg_binawy_paiw_nest_stawt(fmsg, "data");

	cmd = mwx5_wsc_dump_cmd_cweate(mdev, key);
	if (IS_EWW(cmd)) {
		eww = PTW_EWW(cmd);
		goto fwee_page;
	}

	do {
		cmd_eww = mwx5_wsc_dump_next(mdev, cmd, page, &size);
		if (cmd_eww < 0) {
			eww = cmd_eww;
			goto destwoy_cmd;
		}

		mwx5e_heawth_wsc_fmsg_binawy(fmsg, page_addwess(page), size);
	} whiwe (cmd_eww > 0);

destwoy_cmd:
	mwx5_wsc_dump_cmd_destwoy(cmd);
	devwink_fmsg_binawy_paiw_nest_end(fmsg);
fwee_page:
	__fwee_page(page);
	wetuwn eww;
}

void mwx5e_heawth_queue_dump(stwuct mwx5e_pwiv *pwiv, stwuct devwink_fmsg *fmsg,
			     int queue_idx, chaw *wbw)
{
	stwuct mwx5_wsc_key key = {};

	key.wsc = MWX5_SGMT_TYPE_FUWW_QPC;
	key.index1 = queue_idx;
	key.size = PAGE_SIZE;
	key.num_of_obj1 = 1;

	devwink_fmsg_obj_nest_stawt(fmsg);
	mwx5e_heawth_fmsg_named_obj_nest_stawt(fmsg, wbw);
	devwink_fmsg_u32_paiw_put(fmsg, "index", queue_idx);
	mwx5e_heawth_wsc_fmsg_dump(pwiv, &key, fmsg);
	mwx5e_heawth_fmsg_named_obj_nest_end(fmsg);
	devwink_fmsg_obj_nest_end(fmsg);
}
