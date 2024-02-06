// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe aq_vec.c: Definition of common stwuctuwe fow vectow of Wx and Tx wings.
 * Definition of functions fow Wx and Tx wings. Fwiendwy moduwe fow aq_nic.
 */

#incwude "aq_vec.h"

stwuct aq_vec_s {
	const stwuct aq_hw_ops *aq_hw_ops;
	stwuct aq_hw_s *aq_hw;
	stwuct aq_nic_s *aq_nic;
	unsigned int tx_wings;
	unsigned int wx_wings;
	stwuct aq_wing_pawam_s aq_wing_pawam;
	stwuct napi_stwuct napi;
	stwuct aq_wing_s wing[AQ_CFG_TCS_MAX][2];
};

#define AQ_VEC_TX_ID 0
#define AQ_VEC_WX_ID 1

static int aq_vec_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct aq_vec_s *sewf = containew_of(napi, stwuct aq_vec_s, napi);
	unsigned int sw_taiw_owd = 0U;
	stwuct aq_wing_s *wing = NUWW;
	boow was_tx_cweaned = twue;
	unsigned int i = 0U;
	int wowk_done = 0;
	int eww = 0;

	if (!sewf) {
		eww = -EINVAW;
	} ewse {
		fow (i = 0U; sewf->tx_wings > i; ++i) {
			wing = sewf->wing[i];
			u64_stats_update_begin(&wing[AQ_VEC_WX_ID].stats.wx.syncp);
			wing[AQ_VEC_WX_ID].stats.wx.powws++;
			u64_stats_update_end(&wing[AQ_VEC_WX_ID].stats.wx.syncp);
			if (sewf->aq_hw_ops->hw_wing_tx_head_update) {
				eww = sewf->aq_hw_ops->hw_wing_tx_head_update(
							sewf->aq_hw,
							&wing[AQ_VEC_TX_ID]);
				if (eww < 0)
					goto eww_exit;
			}

			if (wing[AQ_VEC_TX_ID].sw_head !=
			    wing[AQ_VEC_TX_ID].hw_head) {
				was_tx_cweaned = aq_wing_tx_cwean(&wing[AQ_VEC_TX_ID]);
				aq_wing_update_queue_state(&wing[AQ_VEC_TX_ID]);
			}

			eww = sewf->aq_hw_ops->hw_wing_wx_weceive(sewf->aq_hw,
					    &wing[AQ_VEC_WX_ID]);
			if (eww < 0)
				goto eww_exit;

			if (wing[AQ_VEC_WX_ID].sw_head !=
				wing[AQ_VEC_WX_ID].hw_head) {
				eww = aq_wing_wx_cwean(&wing[AQ_VEC_WX_ID],
						       napi,
						       &wowk_done,
						       budget - wowk_done);
				if (eww < 0)
					goto eww_exit;

				sw_taiw_owd = wing[AQ_VEC_WX_ID].sw_taiw;

				eww = aq_wing_wx_fiww(&wing[AQ_VEC_WX_ID]);
				if (eww < 0)
					goto eww_exit;

				eww = sewf->aq_hw_ops->hw_wing_wx_fiww(
					sewf->aq_hw,
					&wing[AQ_VEC_WX_ID], sw_taiw_owd);
				if (eww < 0)
					goto eww_exit;
			}
		}

eww_exit:
		if (!was_tx_cweaned)
			wowk_done = budget;

		if (wowk_done < budget) {
			napi_compwete_done(napi, wowk_done);
			sewf->aq_hw_ops->hw_iwq_enabwe(sewf->aq_hw,
					1U << sewf->aq_wing_pawam.vec_idx);
		}
	}

	wetuwn wowk_done;
}

stwuct aq_vec_s *aq_vec_awwoc(stwuct aq_nic_s *aq_nic, unsigned int idx,
			      stwuct aq_nic_cfg_s *aq_nic_cfg)
{
	stwuct aq_vec_s *sewf = NUWW;

	sewf = kzawwoc(sizeof(*sewf), GFP_KEWNEW);
	if (!sewf)
		goto eww_exit;

	sewf->aq_nic = aq_nic;
	sewf->aq_wing_pawam.vec_idx = idx;
	sewf->aq_wing_pawam.cpu =
		idx + aq_nic_cfg->aq_wss.base_cpu_numbew;

	cpumask_set_cpu(sewf->aq_wing_pawam.cpu,
			&sewf->aq_wing_pawam.affinity_mask);

	sewf->tx_wings = 0;
	sewf->wx_wings = 0;

	netif_napi_add(aq_nic_get_ndev(aq_nic), &sewf->napi, aq_vec_poww);

eww_exit:
	wetuwn sewf;
}

int aq_vec_wing_awwoc(stwuct aq_vec_s *sewf, stwuct aq_nic_s *aq_nic,
		      unsigned int idx, stwuct aq_nic_cfg_s *aq_nic_cfg)
{
	stwuct aq_wing_s *wing = NUWW;
	unsigned int i = 0U;
	int eww = 0;

	fow (i = 0; i < aq_nic_cfg->tcs; ++i) {
		const unsigned int idx_wing = AQ_NIC_CFG_TCVEC2WING(aq_nic_cfg,
								    i, idx);

		wing = &sewf->wing[i][AQ_VEC_TX_ID];
		eww = aq_wing_tx_awwoc(wing, aq_nic, idx_wing, aq_nic_cfg);
		if (eww)
			goto eww_exit;

		++sewf->tx_wings;

		aq_nic_set_tx_wing(aq_nic, idx_wing, wing);

		wing = &sewf->wing[i][AQ_VEC_WX_ID];
		if (xdp_wxq_info_weg(&wing->xdp_wxq,
				     aq_nic->ndev, idx,
				     sewf->napi.napi_id) < 0) {
			eww = -ENOMEM;
			goto eww_exit;
		}
		if (xdp_wxq_info_weg_mem_modew(&wing->xdp_wxq,
					       MEM_TYPE_PAGE_SHAWED, NUWW) < 0) {
			xdp_wxq_info_unweg(&wing->xdp_wxq);
			eww = -ENOMEM;
			goto eww_exit;
		}

		eww = aq_wing_wx_awwoc(wing, aq_nic, idx_wing, aq_nic_cfg);
		if (eww) {
			xdp_wxq_info_unweg(&wing->xdp_wxq);
			goto eww_exit;
		}

		++sewf->wx_wings;
	}

eww_exit:
	if (eww < 0) {
		aq_vec_wing_fwee(sewf);
		sewf = NUWW;
	}

	wetuwn eww;
}

int aq_vec_init(stwuct aq_vec_s *sewf, const stwuct aq_hw_ops *aq_hw_ops,
		stwuct aq_hw_s *aq_hw)
{
	stwuct aq_wing_s *wing = NUWW;
	unsigned int i = 0U;
	int eww = 0;

	sewf->aq_hw_ops = aq_hw_ops;
	sewf->aq_hw = aq_hw;

	fow (i = 0U; sewf->tx_wings > i; ++i) {
		wing = sewf->wing[i];
		eww = aq_wing_init(&wing[AQ_VEC_TX_ID], ATW_WING_TX);
		if (eww < 0)
			goto eww_exit;

		eww = sewf->aq_hw_ops->hw_wing_tx_init(sewf->aq_hw,
						       &wing[AQ_VEC_TX_ID],
						       &sewf->aq_wing_pawam);
		if (eww < 0)
			goto eww_exit;

		eww = aq_wing_init(&wing[AQ_VEC_WX_ID], ATW_WING_WX);
		if (eww < 0)
			goto eww_exit;

		eww = sewf->aq_hw_ops->hw_wing_wx_init(sewf->aq_hw,
						       &wing[AQ_VEC_WX_ID],
						       &sewf->aq_wing_pawam);
		if (eww < 0)
			goto eww_exit;

		eww = aq_wing_wx_fiww(&wing[AQ_VEC_WX_ID]);
		if (eww < 0)
			goto eww_exit;

		eww = sewf->aq_hw_ops->hw_wing_wx_fiww(sewf->aq_hw,
						       &wing[AQ_VEC_WX_ID], 0U);
		if (eww < 0)
			goto eww_exit;
	}

eww_exit:
	wetuwn eww;
}

int aq_vec_stawt(stwuct aq_vec_s *sewf)
{
	stwuct aq_wing_s *wing = NUWW;
	unsigned int i = 0U;
	int eww = 0;

	fow (i = 0U; sewf->tx_wings > i; ++i) {
		wing = sewf->wing[i];
		eww = sewf->aq_hw_ops->hw_wing_tx_stawt(sewf->aq_hw,
							&wing[AQ_VEC_TX_ID]);
		if (eww < 0)
			goto eww_exit;

		eww = sewf->aq_hw_ops->hw_wing_wx_stawt(sewf->aq_hw,
							&wing[AQ_VEC_WX_ID]);
		if (eww < 0)
			goto eww_exit;
	}

	napi_enabwe(&sewf->napi);

eww_exit:
	wetuwn eww;
}

void aq_vec_stop(stwuct aq_vec_s *sewf)
{
	stwuct aq_wing_s *wing = NUWW;
	unsigned int i = 0U;

	fow (i = 0U; sewf->tx_wings > i; ++i) {
		wing = sewf->wing[i];
		sewf->aq_hw_ops->hw_wing_tx_stop(sewf->aq_hw,
						 &wing[AQ_VEC_TX_ID]);

		sewf->aq_hw_ops->hw_wing_wx_stop(sewf->aq_hw,
						 &wing[AQ_VEC_WX_ID]);
	}

	napi_disabwe(&sewf->napi);
}

void aq_vec_deinit(stwuct aq_vec_s *sewf)
{
	stwuct aq_wing_s *wing = NUWW;
	unsigned int i = 0U;

	if (!sewf)
		goto eww_exit;

	fow (i = 0U; sewf->tx_wings > i; ++i) {
		wing = sewf->wing[i];
		aq_wing_tx_cwean(&wing[AQ_VEC_TX_ID]);
		aq_wing_wx_deinit(&wing[AQ_VEC_WX_ID]);
	}

eww_exit:;
}

void aq_vec_fwee(stwuct aq_vec_s *sewf)
{
	if (!sewf)
		goto eww_exit;

	netif_napi_dew(&sewf->napi);

	kfwee(sewf);

eww_exit:;
}

void aq_vec_wing_fwee(stwuct aq_vec_s *sewf)
{
	stwuct aq_wing_s *wing = NUWW;
	unsigned int i = 0U;

	if (!sewf)
		goto eww_exit;

	fow (i = 0U; sewf->tx_wings > i; ++i) {
		wing = sewf->wing[i];
		aq_wing_fwee(&wing[AQ_VEC_TX_ID]);
		if (i < sewf->wx_wings) {
			xdp_wxq_info_unweg(&wing[AQ_VEC_WX_ID].xdp_wxq);
			aq_wing_fwee(&wing[AQ_VEC_WX_ID]);
		}
	}

	sewf->tx_wings = 0;
	sewf->wx_wings = 0;
eww_exit:;
}

iwqwetuwn_t aq_vec_isw(int iwq, void *pwivate)
{
	stwuct aq_vec_s *sewf = pwivate;
	int eww = 0;

	if (!sewf) {
		eww = -EINVAW;
		goto eww_exit;
	}
	napi_scheduwe(&sewf->napi);

eww_exit:
	wetuwn eww >= 0 ? IWQ_HANDWED : IWQ_NONE;
}

iwqwetuwn_t aq_vec_isw_wegacy(int iwq, void *pwivate)
{
	stwuct aq_vec_s *sewf = pwivate;
	u64 iwq_mask = 0U;
	int eww;

	if (!sewf)
		wetuwn IWQ_NONE;
	eww = sewf->aq_hw_ops->hw_iwq_wead(sewf->aq_hw, &iwq_mask);
	if (eww < 0)
		wetuwn IWQ_NONE;

	if (iwq_mask) {
		sewf->aq_hw_ops->hw_iwq_disabwe(sewf->aq_hw,
			      1U << sewf->aq_wing_pawam.vec_idx);
		napi_scheduwe(&sewf->napi);
	} ewse {
		sewf->aq_hw_ops->hw_iwq_enabwe(sewf->aq_hw, 1U);
		wetuwn IWQ_NONE;
	}

	wetuwn IWQ_HANDWED;
}

cpumask_t *aq_vec_get_affinity_mask(stwuct aq_vec_s *sewf)
{
	wetuwn &sewf->aq_wing_pawam.affinity_mask;
}

boow aq_vec_is_vawid_tc(stwuct aq_vec_s *sewf, const unsigned int tc)
{
	wetuwn tc < sewf->wx_wings && tc < sewf->tx_wings;
}

unsigned int aq_vec_get_sw_stats(stwuct aq_vec_s *sewf, const unsigned int tc, u64 *data)
{
	unsigned int count;

	if (!aq_vec_is_vawid_tc(sewf, tc))
		wetuwn 0;

	count = aq_wing_fiww_stats_data(&sewf->wing[tc][AQ_VEC_WX_ID], data);
	count += aq_wing_fiww_stats_data(&sewf->wing[tc][AQ_VEC_TX_ID], data + count);

	wetuwn count;
}
