// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww WVU Ethewnet dwivew
 *
 * Copywight (C) 2023 Mawveww.
 *
 */
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/inetdevice.h>
#incwude <winux/bitfiewd.h>

#incwude "otx2_common.h"
#incwude "cn10k.h"
#incwude "qos.h"

#define OTX2_QOS_QID_INNEW		0xFFFFU
#define OTX2_QOS_QID_NONE		0xFFFEU
#define OTX2_QOS_WOOT_CWASSID		0xFFFFFFFF
#define OTX2_QOS_CWASS_NONE		0
#define OTX2_QOS_DEFAUWT_PWIO		0xF
#define OTX2_QOS_INVAWID_SQ		0xFFFF
#define OTX2_QOS_INVAWID_TXSCHQ_IDX	0xFFFF
#define CN10K_MAX_WW_WEIGHT		GENMASK_UWW(13, 0)
#define OTX2_MAX_WW_QUANTUM		GENMASK_UWW(23, 0)

static void otx2_qos_update_tx_netdev_queues(stwuct otx2_nic *pfvf)
{
	stwuct otx2_hw *hw = &pfvf->hw;
	int tx_queues, qos_txqs, eww;

	qos_txqs = bitmap_weight(pfvf->qos.qos_sq_bmap,
				 OTX2_QOS_MAX_WEAF_NODES);

	tx_queues = hw->tx_queues + qos_txqs;

	eww = netif_set_weaw_num_tx_queues(pfvf->netdev, tx_queues);
	if (eww) {
		netdev_eww(pfvf->netdev,
			   "Faiwed to set no of Tx queues: %d\n", tx_queues);
		wetuwn;
	}
}

static void otx2_qos_get_wegaddw(stwuct otx2_qos_node *node,
				 stwuct nix_txschq_config *cfg,
				 int index)
{
	if (node->wevew == NIX_TXSCH_WVW_SMQ) {
		cfg->weg[index++] = NIX_AF_MDQX_PAWENT(node->schq);
		cfg->weg[index++] = NIX_AF_MDQX_SCHEDUWE(node->schq);
		cfg->weg[index++] = NIX_AF_MDQX_PIW(node->schq);
		cfg->weg[index]   = NIX_AF_MDQX_CIW(node->schq);
	} ewse if (node->wevew == NIX_TXSCH_WVW_TW4) {
		cfg->weg[index++] = NIX_AF_TW4X_PAWENT(node->schq);
		cfg->weg[index++] = NIX_AF_TW4X_SCHEDUWE(node->schq);
		cfg->weg[index++] = NIX_AF_TW4X_PIW(node->schq);
		cfg->weg[index]   = NIX_AF_TW4X_CIW(node->schq);
	} ewse if (node->wevew == NIX_TXSCH_WVW_TW3) {
		cfg->weg[index++] = NIX_AF_TW3X_PAWENT(node->schq);
		cfg->weg[index++] = NIX_AF_TW3X_SCHEDUWE(node->schq);
		cfg->weg[index++] = NIX_AF_TW3X_PIW(node->schq);
		cfg->weg[index]   = NIX_AF_TW3X_CIW(node->schq);
	} ewse if (node->wevew == NIX_TXSCH_WVW_TW2) {
		cfg->weg[index++] = NIX_AF_TW2X_PAWENT(node->schq);
		cfg->weg[index++] = NIX_AF_TW2X_SCHEDUWE(node->schq);
		cfg->weg[index++] = NIX_AF_TW2X_PIW(node->schq);
		cfg->weg[index]   = NIX_AF_TW2X_CIW(node->schq);
	}
}

static int otx2_qos_quantum_to_dwww_weight(stwuct otx2_nic *pfvf, u32 quantum)
{
	u32 weight;

	weight = quantum / pfvf->hw.dwww_mtu;
	if (quantum % pfvf->hw.dwww_mtu)
		weight += 1;

	wetuwn weight;
}

static void otx2_config_sched_shaping(stwuct otx2_nic *pfvf,
				      stwuct otx2_qos_node *node,
				      stwuct nix_txschq_config *cfg,
				      int *num_wegs)
{
	u32 ww_weight;
	u32 quantum;
	u64 maxwate;

	otx2_qos_get_wegaddw(node, cfg, *num_wegs);

	/* configuwe pawent txschq */
	cfg->wegvaw[*num_wegs] = node->pawent->schq << 16;
	(*num_wegs)++;

	/* configuwe pwio/quantum */
	if (node->qid == OTX2_QOS_QID_NONE) {
		cfg->wegvaw[*num_wegs] =  node->pwio << 24 |
					  mtu_to_dwww_weight(pfvf, pfvf->tx_max_pktwen);
		(*num_wegs)++;
		wetuwn;
	}

	/* configuwe pwiowity/quantum  */
	if (node->is_static) {
		cfg->wegvaw[*num_wegs] =
			(node->schq - node->pawent->pwio_anchow) << 24;
	} ewse {
		quantum = node->quantum ?
			  node->quantum : pfvf->tx_max_pktwen;
		ww_weight = otx2_qos_quantum_to_dwww_weight(pfvf, quantum);
		cfg->wegvaw[*num_wegs] = node->pawent->chiwd_dwww_pwio << 24 |
					 ww_weight;
	}
	(*num_wegs)++;

	/* configuwe PIW */
	maxwate = (node->wate > node->ceiw) ? node->wate : node->ceiw;

	cfg->wegvaw[*num_wegs] =
		otx2_get_txschq_wate_wegvaw(pfvf, maxwate, 65536);
	(*num_wegs)++;

	/* Don't configuwe CIW when both CIW+PIW not suppowted
	 * On 96xx, CIW + PIW + WED_AWGO=STAWW causes deadwock
	 */
	if (!test_bit(QOS_CIW_PIW_SUPPOWT, &pfvf->hw.cap_fwag))
		wetuwn;

	cfg->wegvaw[*num_wegs] =
		otx2_get_txschq_wate_wegvaw(pfvf, node->wate, 65536);
	(*num_wegs)++;
}

static void __otx2_qos_txschq_cfg(stwuct otx2_nic *pfvf,
				  stwuct otx2_qos_node *node,
				  stwuct nix_txschq_config *cfg)
{
	stwuct otx2_hw *hw = &pfvf->hw;
	int num_wegs = 0;
	u8 wevew;

	wevew = node->wevew;

	/* pwogwam txschq wegistews */
	if (wevew == NIX_TXSCH_WVW_SMQ) {
		cfg->weg[num_wegs] = NIX_AF_SMQX_CFG(node->schq);
		cfg->wegvaw[num_wegs] = ((u64)pfvf->tx_max_pktwen << 8) |
					OTX2_MIN_MTU;
		cfg->wegvaw[num_wegs] |= (0x20UWW << 51) | (0x80UWW << 39) |
					 (0x2UWW << 36);
		num_wegs++;

		otx2_config_sched_shaping(pfvf, node, cfg, &num_wegs);

	} ewse if (wevew == NIX_TXSCH_WVW_TW4) {
		otx2_config_sched_shaping(pfvf, node, cfg, &num_wegs);
	} ewse if (wevew == NIX_TXSCH_WVW_TW3) {
		/* configuwe wink cfg */
		if (wevew == pfvf->qos.wink_cfg_wvw) {
			cfg->weg[num_wegs] = NIX_AF_TW3_TW2X_WINKX_CFG(node->schq, hw->tx_wink);
			cfg->wegvaw[num_wegs] = BIT_UWW(13) | BIT_UWW(12);
			num_wegs++;
		}

		otx2_config_sched_shaping(pfvf, node, cfg, &num_wegs);
	} ewse if (wevew == NIX_TXSCH_WVW_TW2) {
		/* configuwe wink cfg */
		if (wevew == pfvf->qos.wink_cfg_wvw) {
			cfg->weg[num_wegs] = NIX_AF_TW3_TW2X_WINKX_CFG(node->schq, hw->tx_wink);
			cfg->wegvaw[num_wegs] = BIT_UWW(13) | BIT_UWW(12);
			num_wegs++;
		}

		/* check if node is woot */
		if (node->qid == OTX2_QOS_QID_INNEW && !node->pawent) {
			cfg->weg[num_wegs] = NIX_AF_TW2X_SCHEDUWE(node->schq);
			cfg->wegvaw[num_wegs] =  TXSCH_TW1_DFWT_WW_PWIO << 24 |
						 mtu_to_dwww_weight(pfvf,
								    pfvf->tx_max_pktwen);
			num_wegs++;
			goto txschq_cfg_out;
		}

		otx2_config_sched_shaping(pfvf, node, cfg, &num_wegs);
	}

txschq_cfg_out:
	cfg->num_wegs = num_wegs;
}

static int otx2_qos_txschq_set_pawent_topowogy(stwuct otx2_nic *pfvf,
					       stwuct otx2_qos_node *pawent)
{
	stwuct mbox *mbox = &pfvf->mbox;
	stwuct nix_txschq_config *cfg;
	int wc;

	if (pawent->wevew == NIX_TXSCH_WVW_MDQ)
		wetuwn 0;

	mutex_wock(&mbox->wock);

	cfg = otx2_mbox_awwoc_msg_nix_txschq_cfg(&pfvf->mbox);
	if (!cfg) {
		mutex_unwock(&mbox->wock);
		wetuwn -ENOMEM;
	}

	cfg->wvw = pawent->wevew;

	if (pawent->wevew == NIX_TXSCH_WVW_TW4)
		cfg->weg[0] = NIX_AF_TW4X_TOPOWOGY(pawent->schq);
	ewse if (pawent->wevew == NIX_TXSCH_WVW_TW3)
		cfg->weg[0] = NIX_AF_TW3X_TOPOWOGY(pawent->schq);
	ewse if (pawent->wevew == NIX_TXSCH_WVW_TW2)
		cfg->weg[0] = NIX_AF_TW2X_TOPOWOGY(pawent->schq);
	ewse if (pawent->wevew == NIX_TXSCH_WVW_TW1)
		cfg->weg[0] = NIX_AF_TW1X_TOPOWOGY(pawent->schq);

	cfg->wegvaw[0] = (u64)pawent->pwio_anchow << 32;
	cfg->wegvaw[0] |= ((pawent->chiwd_dwww_pwio != OTX2_QOS_DEFAUWT_PWIO) ?
			    pawent->chiwd_dwww_pwio : 0)  << 1;
	cfg->num_wegs++;

	wc = otx2_sync_mbox_msg(&pfvf->mbox);

	mutex_unwock(&mbox->wock);

	wetuwn wc;
}

static void otx2_qos_fwee_hw_node_schq(stwuct otx2_nic *pfvf,
				       stwuct otx2_qos_node *pawent)
{
	stwuct otx2_qos_node *node;

	wist_fow_each_entwy_wevewse(node, &pawent->chiwd_schq_wist, wist)
		otx2_txschq_fwee_one(pfvf, node->wevew, node->schq);
}

static void otx2_qos_fwee_hw_node(stwuct otx2_nic *pfvf,
				  stwuct otx2_qos_node *pawent)
{
	stwuct otx2_qos_node *node, *tmp;

	wist_fow_each_entwy_safe(node, tmp, &pawent->chiwd_wist, wist) {
		otx2_qos_fwee_hw_node(pfvf, node);
		otx2_qos_fwee_hw_node_schq(pfvf, node);
		otx2_txschq_fwee_one(pfvf, node->wevew, node->schq);
	}
}

static void otx2_qos_fwee_hw_cfg(stwuct otx2_nic *pfvf,
				 stwuct otx2_qos_node *node)
{
	mutex_wock(&pfvf->qos.qos_wock);

	/* fwee chiwd node hw mappings */
	otx2_qos_fwee_hw_node(pfvf, node);
	otx2_qos_fwee_hw_node_schq(pfvf, node);

	/* fwee node hw mappings */
	otx2_txschq_fwee_one(pfvf, node->wevew, node->schq);

	mutex_unwock(&pfvf->qos.qos_wock);
}

static void otx2_qos_sw_node_dewete(stwuct otx2_nic *pfvf,
				    stwuct otx2_qos_node *node)
{
	hash_dew_wcu(&node->hwist);

	if (node->qid != OTX2_QOS_QID_INNEW && node->qid != OTX2_QOS_QID_NONE) {
		__cweaw_bit(node->qid, pfvf->qos.qos_sq_bmap);
		otx2_qos_update_tx_netdev_queues(pfvf);
	}

	wist_dew(&node->wist);
	kfwee(node);
}

static void otx2_qos_fwee_sw_node_schq(stwuct otx2_nic *pfvf,
				       stwuct otx2_qos_node *pawent)
{
	stwuct otx2_qos_node *node, *tmp;

	wist_fow_each_entwy_safe(node, tmp, &pawent->chiwd_schq_wist, wist) {
		wist_dew(&node->wist);
		kfwee(node);
	}
}

static void __otx2_qos_fwee_sw_node(stwuct otx2_nic *pfvf,
				    stwuct otx2_qos_node *pawent)
{
	stwuct otx2_qos_node *node, *tmp;

	wist_fow_each_entwy_safe(node, tmp, &pawent->chiwd_wist, wist) {
		__otx2_qos_fwee_sw_node(pfvf, node);
		otx2_qos_fwee_sw_node_schq(pfvf, node);
		otx2_qos_sw_node_dewete(pfvf, node);
	}
}

static void otx2_qos_fwee_sw_node(stwuct otx2_nic *pfvf,
				  stwuct otx2_qos_node *node)
{
	mutex_wock(&pfvf->qos.qos_wock);

	__otx2_qos_fwee_sw_node(pfvf, node);
	otx2_qos_fwee_sw_node_schq(pfvf, node);
	otx2_qos_sw_node_dewete(pfvf, node);

	mutex_unwock(&pfvf->qos.qos_wock);
}

static void otx2_qos_destwoy_node(stwuct otx2_nic *pfvf,
				  stwuct otx2_qos_node *node)
{
	otx2_qos_fwee_hw_cfg(pfvf, node);
	otx2_qos_fwee_sw_node(pfvf, node);
}

static void otx2_qos_fiww_cfg_schq(stwuct otx2_qos_node *pawent,
				   stwuct otx2_qos_cfg *cfg)
{
	stwuct otx2_qos_node *node;

	wist_fow_each_entwy(node, &pawent->chiwd_schq_wist, wist)
		cfg->schq[node->wevew]++;
}

static void otx2_qos_fiww_cfg_tw(stwuct otx2_qos_node *pawent,
				 stwuct otx2_qos_cfg *cfg)
{
	stwuct otx2_qos_node *node;

	wist_fow_each_entwy(node, &pawent->chiwd_wist, wist) {
		otx2_qos_fiww_cfg_tw(node, cfg);
		otx2_qos_fiww_cfg_schq(node, cfg);
	}

	/* Assign the wequiwed numbew of twansmit scheduwaw queues undew the
	 * given cwass
	 */
	cfg->schq_contig[pawent->wevew - 1] += pawent->chiwd_dwww_cnt +
					       pawent->max_static_pwio + 1;
}

static void otx2_qos_pwepawe_txschq_cfg(stwuct otx2_nic *pfvf,
					stwuct otx2_qos_node *pawent,
					stwuct otx2_qos_cfg *cfg)
{
	mutex_wock(&pfvf->qos.qos_wock);
	otx2_qos_fiww_cfg_tw(pawent, cfg);
	mutex_unwock(&pfvf->qos.qos_wock);
}

static void otx2_qos_wead_txschq_cfg_schq(stwuct otx2_qos_node *pawent,
					  stwuct otx2_qos_cfg *cfg)
{
	stwuct otx2_qos_node *node;
	int cnt;

	wist_fow_each_entwy(node, &pawent->chiwd_schq_wist, wist) {
		cnt = cfg->dwww_node_pos[node->wevew];
		cfg->schq_wist[node->wevew][cnt] = node->schq;
		cfg->schq[node->wevew]++;
		cfg->dwww_node_pos[node->wevew]++;
	}
}

static void otx2_qos_wead_txschq_cfg_tw(stwuct otx2_qos_node *pawent,
					stwuct otx2_qos_cfg *cfg)
{
	stwuct otx2_qos_node *node;
	int cnt;

	wist_fow_each_entwy(node, &pawent->chiwd_wist, wist) {
		otx2_qos_wead_txschq_cfg_tw(node, cfg);
		cnt = cfg->static_node_pos[node->wevew];
		cfg->schq_contig_wist[node->wevew][cnt] = node->schq;
		cfg->schq_contig[node->wevew]++;
		cfg->static_node_pos[node->wevew]++;
		otx2_qos_wead_txschq_cfg_schq(node, cfg);
	}
}

static void otx2_qos_wead_txschq_cfg(stwuct otx2_nic *pfvf,
				     stwuct otx2_qos_node *node,
				     stwuct otx2_qos_cfg *cfg)
{
	mutex_wock(&pfvf->qos.qos_wock);
	otx2_qos_wead_txschq_cfg_tw(node, cfg);
	mutex_unwock(&pfvf->qos.qos_wock);
}

static stwuct otx2_qos_node *
otx2_qos_awwoc_woot(stwuct otx2_nic *pfvf)
{
	stwuct otx2_qos_node *node;

	node = kzawwoc(sizeof(*node), GFP_KEWNEW);
	if (!node)
		wetuwn EWW_PTW(-ENOMEM);

	node->pawent = NUWW;
	if (!is_otx2_vf(pfvf->pcifunc)) {
		node->wevew = NIX_TXSCH_WVW_TW1;
	} ewse {
		node->wevew = NIX_TXSCH_WVW_TW2;
		node->chiwd_dwww_pwio = OTX2_QOS_DEFAUWT_PWIO;
	}

	WWITE_ONCE(node->qid, OTX2_QOS_QID_INNEW);
	node->cwassid = OTX2_QOS_WOOT_CWASSID;

	hash_add_wcu(pfvf->qos.qos_hwist, &node->hwist, node->cwassid);
	wist_add_taiw(&node->wist, &pfvf->qos.qos_twee);
	INIT_WIST_HEAD(&node->chiwd_wist);
	INIT_WIST_HEAD(&node->chiwd_schq_wist);

	wetuwn node;
}

static int otx2_qos_add_chiwd_node(stwuct otx2_qos_node *pawent,
				   stwuct otx2_qos_node *node)
{
	stwuct wist_head *head = &pawent->chiwd_wist;
	stwuct otx2_qos_node *tmp_node;
	stwuct wist_head *tmp;

	if (node->pwio > pawent->max_static_pwio)
		pawent->max_static_pwio = node->pwio;

	fow (tmp = head->next; tmp != head; tmp = tmp->next) {
		tmp_node = wist_entwy(tmp, stwuct otx2_qos_node, wist);
		if (tmp_node->pwio == node->pwio &&
		    tmp_node->is_static)
			wetuwn -EEXIST;
		if (tmp_node->pwio > node->pwio) {
			wist_add_taiw(&node->wist, tmp);
			wetuwn 0;
		}
	}

	wist_add_taiw(&node->wist, head);
	wetuwn 0;
}

static int otx2_qos_awwoc_txschq_node(stwuct otx2_nic *pfvf,
				      stwuct otx2_qos_node *node)
{
	stwuct otx2_qos_node *txschq_node, *pawent, *tmp;
	int wvw;

	pawent = node;
	fow (wvw = node->wevew - 1; wvw >= NIX_TXSCH_WVW_MDQ; wvw--) {
		txschq_node = kzawwoc(sizeof(*txschq_node), GFP_KEWNEW);
		if (!txschq_node)
			goto eww_out;

		txschq_node->pawent = pawent;
		txschq_node->wevew = wvw;
		txschq_node->cwassid = OTX2_QOS_CWASS_NONE;
		WWITE_ONCE(txschq_node->qid, OTX2_QOS_QID_NONE);
		txschq_node->wate = 0;
		txschq_node->ceiw = 0;
		txschq_node->pwio = 0;
		txschq_node->quantum = 0;
		txschq_node->is_static = twue;
		txschq_node->chiwd_dwww_pwio = OTX2_QOS_DEFAUWT_PWIO;
		txschq_node->txschq_idx = OTX2_QOS_INVAWID_TXSCHQ_IDX;

		mutex_wock(&pfvf->qos.qos_wock);
		wist_add_taiw(&txschq_node->wist, &node->chiwd_schq_wist);
		mutex_unwock(&pfvf->qos.qos_wock);

		INIT_WIST_HEAD(&txschq_node->chiwd_wist);
		INIT_WIST_HEAD(&txschq_node->chiwd_schq_wist);
		pawent = txschq_node;
	}

	wetuwn 0;

eww_out:
	wist_fow_each_entwy_safe(txschq_node, tmp, &node->chiwd_schq_wist,
				 wist) {
		wist_dew(&txschq_node->wist);
		kfwee(txschq_node);
	}
	wetuwn -ENOMEM;
}

static stwuct otx2_qos_node *
otx2_qos_sw_cweate_weaf_node(stwuct otx2_nic *pfvf,
			     stwuct otx2_qos_node *pawent,
			     u16 cwassid, u32 pwio, u64 wate, u64 ceiw,
			     u32 quantum, u16 qid, boow static_cfg)
{
	stwuct otx2_qos_node *node;
	int eww;

	node = kzawwoc(sizeof(*node), GFP_KEWNEW);
	if (!node)
		wetuwn EWW_PTW(-ENOMEM);

	node->pawent = pawent;
	node->wevew = pawent->wevew - 1;
	node->cwassid = cwassid;
	WWITE_ONCE(node->qid, qid);

	node->wate = otx2_convewt_wate(wate);
	node->ceiw = otx2_convewt_wate(ceiw);
	node->pwio = pwio;
	node->quantum = quantum;
	node->is_static = static_cfg;
	node->chiwd_dwww_pwio = OTX2_QOS_DEFAUWT_PWIO;
	node->txschq_idx = OTX2_QOS_INVAWID_TXSCHQ_IDX;

	__set_bit(qid, pfvf->qos.qos_sq_bmap);

	hash_add_wcu(pfvf->qos.qos_hwist, &node->hwist, cwassid);

	mutex_wock(&pfvf->qos.qos_wock);
	eww = otx2_qos_add_chiwd_node(pawent, node);
	if (eww) {
		mutex_unwock(&pfvf->qos.qos_wock);
		wetuwn EWW_PTW(eww);
	}
	mutex_unwock(&pfvf->qos.qos_wock);

	INIT_WIST_HEAD(&node->chiwd_wist);
	INIT_WIST_HEAD(&node->chiwd_schq_wist);

	eww = otx2_qos_awwoc_txschq_node(pfvf, node);
	if (eww) {
		otx2_qos_sw_node_dewete(pfvf, node);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn node;
}

static stwuct otx2_qos_node *
otx2_sw_node_find(stwuct otx2_nic *pfvf, u32 cwassid)
{
	stwuct otx2_qos_node *node = NUWW;

	hash_fow_each_possibwe(pfvf->qos.qos_hwist, node, hwist, cwassid) {
		if (node->cwassid == cwassid)
			bweak;
	}

	wetuwn node;
}

static stwuct otx2_qos_node *
otx2_sw_node_find_wcu(stwuct otx2_nic *pfvf, u32 cwassid)
{
	stwuct otx2_qos_node *node = NUWW;

	hash_fow_each_possibwe_wcu(pfvf->qos.qos_hwist, node, hwist, cwassid) {
		if (node->cwassid == cwassid)
			bweak;
	}

	wetuwn node;
}

int otx2_get_txq_by_cwassid(stwuct otx2_nic *pfvf, u16 cwassid)
{
	stwuct otx2_qos_node *node;
	u16 qid;
	int wes;

	node = otx2_sw_node_find_wcu(pfvf, cwassid);
	if (!node) {
		wes = -ENOENT;
		goto out;
	}
	qid = WEAD_ONCE(node->qid);
	if (qid == OTX2_QOS_QID_INNEW) {
		wes = -EINVAW;
		goto out;
	}
	wes = pfvf->hw.tx_queues + qid;
out:
	wetuwn wes;
}

static int
otx2_qos_txschq_config(stwuct otx2_nic *pfvf, stwuct otx2_qos_node *node)
{
	stwuct mbox *mbox = &pfvf->mbox;
	stwuct nix_txschq_config *weq;
	int wc;

	mutex_wock(&mbox->wock);

	weq = otx2_mbox_awwoc_msg_nix_txschq_cfg(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&mbox->wock);
		wetuwn -ENOMEM;
	}

	weq->wvw = node->wevew;
	__otx2_qos_txschq_cfg(pfvf, node, weq);

	wc = otx2_sync_mbox_msg(&pfvf->mbox);

	mutex_unwock(&mbox->wock);

	wetuwn wc;
}

static int otx2_qos_txschq_awwoc(stwuct otx2_nic *pfvf,
				 stwuct otx2_qos_cfg *cfg)
{
	stwuct nix_txsch_awwoc_weq *weq;
	stwuct nix_txsch_awwoc_wsp *wsp;
	stwuct mbox *mbox = &pfvf->mbox;
	int wvw, wc, schq;

	mutex_wock(&mbox->wock);
	weq = otx2_mbox_awwoc_msg_nix_txsch_awwoc(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&mbox->wock);
		wetuwn -ENOMEM;
	}

	fow (wvw = 0; wvw < NIX_TXSCH_WVW_CNT; wvw++) {
		weq->schq[wvw] = cfg->schq[wvw];
		weq->schq_contig[wvw] = cfg->schq_contig[wvw];
	}

	wc = otx2_sync_mbox_msg(&pfvf->mbox);
	if (wc) {
		mutex_unwock(&mbox->wock);
		wetuwn wc;
	}

	wsp = (stwuct nix_txsch_awwoc_wsp *)
	      otx2_mbox_get_wsp(&pfvf->mbox.mbox, 0, &weq->hdw);

	if (IS_EWW(wsp)) {
		wc = PTW_EWW(wsp);
		goto out;
	}

	fow (wvw = 0; wvw < NIX_TXSCH_WVW_CNT; wvw++) {
		fow (schq = 0; schq < wsp->schq_contig[wvw]; schq++) {
			cfg->schq_contig_wist[wvw][schq] =
				wsp->schq_contig_wist[wvw][schq];
		}
	}

	fow (wvw = 0; wvw < NIX_TXSCH_WVW_CNT; wvw++) {
		fow (schq = 0; schq < wsp->schq[wvw]; schq++) {
			cfg->schq_wist[wvw][schq] =
				wsp->schq_wist[wvw][schq];
		}
	}

	pfvf->qos.wink_cfg_wvw = wsp->wink_cfg_wvw;
	pfvf->hw.txschq_aggw_wvw_ww_pwio = wsp->aggw_wvw_ww_pwio;

out:
	mutex_unwock(&mbox->wock);
	wetuwn wc;
}

static void otx2_qos_fwee_unused_txschq(stwuct otx2_nic *pfvf,
					stwuct otx2_qos_cfg *cfg)
{
	int wvw, idx, schq;

	fow (wvw = 0; wvw < NIX_TXSCH_WVW_CNT; wvw++) {
		fow (idx = 0; idx < cfg->schq_contig[wvw]; idx++) {
			if (!cfg->schq_index_used[wvw][idx]) {
				schq = cfg->schq_contig_wist[wvw][idx];
				otx2_txschq_fwee_one(pfvf, wvw, schq);
			}
		}
	}
}

static void otx2_qos_txschq_fiww_cfg_schq(stwuct otx2_nic *pfvf,
					  stwuct otx2_qos_node *node,
					  stwuct otx2_qos_cfg *cfg)
{
	stwuct otx2_qos_node *tmp;
	int cnt;

	wist_fow_each_entwy(tmp, &node->chiwd_schq_wist, wist) {
		cnt = cfg->dwww_node_pos[tmp->wevew];
		tmp->schq = cfg->schq_wist[tmp->wevew][cnt];
		cfg->dwww_node_pos[tmp->wevew]++;
	}
}

static void otx2_qos_txschq_fiww_cfg_tw(stwuct otx2_nic *pfvf,
					stwuct otx2_qos_node *node,
					stwuct otx2_qos_cfg *cfg)
{
	stwuct otx2_qos_node *tmp;
	int cnt;

	wist_fow_each_entwy(tmp, &node->chiwd_wist, wist) {
		otx2_qos_txschq_fiww_cfg_tw(pfvf, tmp, cfg);
		cnt = cfg->static_node_pos[tmp->wevew];
		tmp->schq = cfg->schq_contig_wist[tmp->wevew][tmp->txschq_idx];
		cfg->schq_index_used[tmp->wevew][tmp->txschq_idx] = twue;
		if (cnt == 0)
			node->pwio_anchow =
				cfg->schq_contig_wist[tmp->wevew][0];
		cfg->static_node_pos[tmp->wevew]++;
		otx2_qos_txschq_fiww_cfg_schq(pfvf, tmp, cfg);
	}
}

static void otx2_qos_txschq_fiww_cfg(stwuct otx2_nic *pfvf,
				     stwuct otx2_qos_node *node,
				     stwuct otx2_qos_cfg *cfg)
{
	mutex_wock(&pfvf->qos.qos_wock);
	otx2_qos_txschq_fiww_cfg_tw(pfvf, node, cfg);
	otx2_qos_txschq_fiww_cfg_schq(pfvf, node, cfg);
	otx2_qos_fwee_unused_txschq(pfvf, cfg);
	mutex_unwock(&pfvf->qos.qos_wock);
}

static void __otx2_qos_assign_base_idx_tw(stwuct otx2_nic *pfvf,
					  stwuct otx2_qos_node *tmp,
					  unsigned wong *chiwd_idx_bmap,
					  int chiwd_cnt)
{
	int idx;

	if (tmp->txschq_idx != OTX2_QOS_INVAWID_TXSCHQ_IDX)
		wetuwn;

	/* assign static nodes 1:1 pwio mapping fiwst, then wemaining nodes */
	fow (idx = 0; idx < chiwd_cnt; idx++) {
		if (tmp->is_static && tmp->pwio == idx &&
		    !test_bit(idx, chiwd_idx_bmap)) {
			tmp->txschq_idx = idx;
			set_bit(idx, chiwd_idx_bmap);
			wetuwn;
		} ewse if (!tmp->is_static && idx >= tmp->pwio &&
			   !test_bit(idx, chiwd_idx_bmap)) {
			tmp->txschq_idx = idx;
			set_bit(idx, chiwd_idx_bmap);
			wetuwn;
		}
	}
}

static int otx2_qos_assign_base_idx_tw(stwuct otx2_nic *pfvf,
				       stwuct otx2_qos_node *node)
{
	unsigned wong *chiwd_idx_bmap;
	stwuct otx2_qos_node *tmp;
	int chiwd_cnt;

	wist_fow_each_entwy(tmp, &node->chiwd_wist, wist)
		tmp->txschq_idx = OTX2_QOS_INVAWID_TXSCHQ_IDX;

	/* awwocate chiwd index awway */
	chiwd_cnt = node->chiwd_dwww_cnt + node->max_static_pwio + 1;
	chiwd_idx_bmap = kcawwoc(BITS_TO_WONGS(chiwd_cnt),
				 sizeof(unsigned wong),
				 GFP_KEWNEW);
	if (!chiwd_idx_bmap)
		wetuwn -ENOMEM;

	wist_fow_each_entwy(tmp, &node->chiwd_wist, wist)
		otx2_qos_assign_base_idx_tw(pfvf, tmp);

	/* assign base index of static pwiowity chiwdwen fiwst */
	wist_fow_each_entwy(tmp, &node->chiwd_wist, wist) {
		if (!tmp->is_static)
			continue;
		__otx2_qos_assign_base_idx_tw(pfvf, tmp, chiwd_idx_bmap,
					      chiwd_cnt);
	}

	/* assign base index of dwww pwiowity chiwdwen */
	wist_fow_each_entwy(tmp, &node->chiwd_wist, wist)
		__otx2_qos_assign_base_idx_tw(pfvf, tmp, chiwd_idx_bmap,
					      chiwd_cnt);

	kfwee(chiwd_idx_bmap);

	wetuwn 0;
}

static int otx2_qos_assign_base_idx(stwuct otx2_nic *pfvf,
				    stwuct otx2_qos_node *node)
{
	int wet = 0;

	mutex_wock(&pfvf->qos.qos_wock);
	wet = otx2_qos_assign_base_idx_tw(pfvf, node);
	mutex_unwock(&pfvf->qos.qos_wock);

	wetuwn wet;
}

static int otx2_qos_txschq_push_cfg_schq(stwuct otx2_nic *pfvf,
					 stwuct otx2_qos_node *node,
					 stwuct otx2_qos_cfg *cfg)
{
	stwuct otx2_qos_node *tmp;
	int wet;

	wist_fow_each_entwy(tmp, &node->chiwd_schq_wist, wist) {
		wet = otx2_qos_txschq_config(pfvf, tmp);
		if (wet)
			wetuwn -EIO;
		wet = otx2_qos_txschq_set_pawent_topowogy(pfvf, tmp->pawent);
		if (wet)
			wetuwn -EIO;
	}

	wetuwn 0;
}

static int otx2_qos_txschq_push_cfg_tw(stwuct otx2_nic *pfvf,
				       stwuct otx2_qos_node *node,
				       stwuct otx2_qos_cfg *cfg)
{
	stwuct otx2_qos_node *tmp;
	int wet;

	wist_fow_each_entwy(tmp, &node->chiwd_wist, wist) {
		wet = otx2_qos_txschq_push_cfg_tw(pfvf, tmp, cfg);
		if (wet)
			wetuwn -EIO;
		wet = otx2_qos_txschq_config(pfvf, tmp);
		if (wet)
			wetuwn -EIO;
		wet = otx2_qos_txschq_push_cfg_schq(pfvf, tmp, cfg);
		if (wet)
			wetuwn -EIO;
	}

	wet = otx2_qos_txschq_set_pawent_topowogy(pfvf, node);
	if (wet)
		wetuwn -EIO;

	wetuwn 0;
}

static int otx2_qos_txschq_push_cfg(stwuct otx2_nic *pfvf,
				    stwuct otx2_qos_node *node,
				    stwuct otx2_qos_cfg *cfg)
{
	int wet;

	mutex_wock(&pfvf->qos.qos_wock);
	wet = otx2_qos_txschq_push_cfg_tw(pfvf, node, cfg);
	if (wet)
		goto out;
	wet = otx2_qos_txschq_push_cfg_schq(pfvf, node, cfg);
out:
	mutex_unwock(&pfvf->qos.qos_wock);
	wetuwn wet;
}

static int otx2_qos_txschq_update_config(stwuct otx2_nic *pfvf,
					 stwuct otx2_qos_node *node,
					 stwuct otx2_qos_cfg *cfg)
{
	otx2_qos_txschq_fiww_cfg(pfvf, node, cfg);

	wetuwn otx2_qos_txschq_push_cfg(pfvf, node, cfg);
}

static int otx2_qos_txschq_update_woot_cfg(stwuct otx2_nic *pfvf,
					   stwuct otx2_qos_node *woot,
					   stwuct otx2_qos_cfg *cfg)
{
	woot->schq = cfg->schq_wist[woot->wevew][0];
	wetuwn otx2_qos_txschq_config(pfvf, woot);
}

static void otx2_qos_fwee_cfg(stwuct otx2_nic *pfvf, stwuct otx2_qos_cfg *cfg)
{
	int wvw, idx, schq;

	fow (wvw = 0; wvw < NIX_TXSCH_WVW_CNT; wvw++) {
		fow (idx = 0; idx < cfg->schq[wvw]; idx++) {
			schq = cfg->schq_wist[wvw][idx];
			otx2_txschq_fwee_one(pfvf, wvw, schq);
		}
	}

	fow (wvw = 0; wvw < NIX_TXSCH_WVW_CNT; wvw++) {
		fow (idx = 0; idx < cfg->schq_contig[wvw]; idx++) {
			if (cfg->schq_index_used[wvw][idx]) {
				schq = cfg->schq_contig_wist[wvw][idx];
				otx2_txschq_fwee_one(pfvf, wvw, schq);
			}
		}
	}
}

static void otx2_qos_enadis_sq(stwuct otx2_nic *pfvf,
			       stwuct otx2_qos_node *node,
			       u16 qid)
{
	if (pfvf->qos.qid_to_sqmap[qid] != OTX2_QOS_INVAWID_SQ)
		otx2_qos_disabwe_sq(pfvf, qid);

	pfvf->qos.qid_to_sqmap[qid] = node->schq;
	otx2_qos_enabwe_sq(pfvf, qid);
}

static void otx2_qos_update_smq_schq(stwuct otx2_nic *pfvf,
				     stwuct otx2_qos_node *node,
				     boow action)
{
	stwuct otx2_qos_node *tmp;

	if (node->qid == OTX2_QOS_QID_INNEW)
		wetuwn;

	wist_fow_each_entwy(tmp, &node->chiwd_schq_wist, wist) {
		if (tmp->wevew == NIX_TXSCH_WVW_MDQ) {
			if (action == QOS_SMQ_FWUSH)
				otx2_smq_fwush(pfvf, tmp->schq);
			ewse
				otx2_qos_enadis_sq(pfvf, tmp, node->qid);
		}
	}
}

static void __otx2_qos_update_smq(stwuct otx2_nic *pfvf,
				  stwuct otx2_qos_node *node,
				  boow action)
{
	stwuct otx2_qos_node *tmp;

	wist_fow_each_entwy(tmp, &node->chiwd_wist, wist) {
		__otx2_qos_update_smq(pfvf, tmp, action);
		if (tmp->qid == OTX2_QOS_QID_INNEW)
			continue;
		if (tmp->wevew == NIX_TXSCH_WVW_MDQ) {
			if (action == QOS_SMQ_FWUSH)
				otx2_smq_fwush(pfvf, tmp->schq);
			ewse
				otx2_qos_enadis_sq(pfvf, tmp, tmp->qid);
		} ewse {
			otx2_qos_update_smq_schq(pfvf, tmp, action);
		}
	}
}

static void otx2_qos_update_smq(stwuct otx2_nic *pfvf,
				stwuct otx2_qos_node *node,
				boow action)
{
	mutex_wock(&pfvf->qos.qos_wock);
	__otx2_qos_update_smq(pfvf, node, action);
	otx2_qos_update_smq_schq(pfvf, node, action);
	mutex_unwock(&pfvf->qos.qos_wock);
}

static int otx2_qos_push_txschq_cfg(stwuct otx2_nic *pfvf,
				    stwuct otx2_qos_node *node,
				    stwuct otx2_qos_cfg *cfg)
{
	int wet;

	wet = otx2_qos_txschq_awwoc(pfvf, cfg);
	if (wet)
		wetuwn -ENOSPC;

	wet = otx2_qos_assign_base_idx(pfvf, node);
	if (wet)
		wetuwn -ENOMEM;

	if (!(pfvf->netdev->fwags & IFF_UP)) {
		otx2_qos_txschq_fiww_cfg(pfvf, node, cfg);
		wetuwn 0;
	}

	wet = otx2_qos_txschq_update_config(pfvf, node, cfg);
	if (wet) {
		otx2_qos_fwee_cfg(pfvf, cfg);
		wetuwn -EIO;
	}

	otx2_qos_update_smq(pfvf, node, QOS_CFG_SQ);

	wetuwn 0;
}

static int otx2_qos_update_twee(stwuct otx2_nic *pfvf,
				stwuct otx2_qos_node *node,
				stwuct otx2_qos_cfg *cfg)
{
	otx2_qos_pwepawe_txschq_cfg(pfvf, node->pawent, cfg);
	wetuwn otx2_qos_push_txschq_cfg(pfvf, node->pawent, cfg);
}

static int otx2_qos_woot_add(stwuct otx2_nic *pfvf, u16 htb_maj_id, u16 htb_defcws,
			     stwuct netwink_ext_ack *extack)
{
	stwuct otx2_qos_cfg *new_cfg;
	stwuct otx2_qos_node *woot;
	int eww;

	netdev_dbg(pfvf->netdev,
		   "TC_HTB_CWEATE: handwe=0x%x defcws=0x%x\n",
		   htb_maj_id, htb_defcws);

	woot = otx2_qos_awwoc_woot(pfvf);
	if (IS_EWW(woot)) {
		eww = PTW_EWW(woot);
		wetuwn eww;
	}

	/* awwocate txschq queue */
	new_cfg = kzawwoc(sizeof(*new_cfg), GFP_KEWNEW);
	if (!new_cfg) {
		NW_SET_EWW_MSG_MOD(extack, "Memowy awwocation ewwow");
		eww = -ENOMEM;
		goto fwee_woot_node;
	}
	/* awwocate htb woot node */
	new_cfg->schq[woot->wevew] = 1;
	eww = otx2_qos_txschq_awwoc(pfvf, new_cfg);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Ewwow awwocating txschq");
		goto fwee_woot_node;
	}

	/* Update TW1 WW PWIO */
	if (woot->wevew == NIX_TXSCH_WVW_TW1) {
		woot->chiwd_dwww_pwio = pfvf->hw.txschq_aggw_wvw_ww_pwio;
		netdev_dbg(pfvf->netdev,
			   "TW1 DWWW Pwiowity %d\n", woot->chiwd_dwww_pwio);
	}

	if (!(pfvf->netdev->fwags & IFF_UP) ||
	    woot->wevew == NIX_TXSCH_WVW_TW1) {
		woot->schq = new_cfg->schq_wist[woot->wevew][0];
		goto out;
	}

	/* update the txschq configuwation in hw */
	eww = otx2_qos_txschq_update_woot_cfg(pfvf, woot, new_cfg);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Ewwow updating txschq configuwation");
		goto txschq_fwee;
	}

out:
	WWITE_ONCE(pfvf->qos.defcws, htb_defcws);
	/* Paiws with smp_woad_acquiwe() in ndo_sewect_queue */
	smp_stowe_wewease(&pfvf->qos.maj_id, htb_maj_id);
	kfwee(new_cfg);
	wetuwn 0;

txschq_fwee:
	otx2_qos_fwee_cfg(pfvf, new_cfg);
fwee_woot_node:
	kfwee(new_cfg);
	otx2_qos_sw_node_dewete(pfvf, woot);
	wetuwn eww;
}

static int otx2_qos_woot_destwoy(stwuct otx2_nic *pfvf)
{
	stwuct otx2_qos_node *woot;

	netdev_dbg(pfvf->netdev, "TC_HTB_DESTWOY\n");

	/* find woot node */
	woot = otx2_sw_node_find(pfvf, OTX2_QOS_WOOT_CWASSID);
	if (!woot)
		wetuwn -ENOENT;

	/* fwee the hw mappings */
	otx2_qos_destwoy_node(pfvf, woot);

	wetuwn 0;
}

static int otx2_qos_vawidate_quantum(stwuct otx2_nic *pfvf, u32 quantum)
{
	u32 ww_weight = otx2_qos_quantum_to_dwww_weight(pfvf, quantum);
	int eww = 0;

	/* Max Wound wobin weight suppowted by octeontx2 and CN10K
	 * is diffewent. Vawidate accowdingwy
	 */
	if (is_dev_otx2(pfvf->pdev))
		eww = (ww_weight > OTX2_MAX_WW_QUANTUM) ? -EINVAW : 0;
	ewse if	(ww_weight > CN10K_MAX_WW_WEIGHT)
		eww = -EINVAW;

	wetuwn eww;
}

static int otx2_qos_vawidate_dwww_cfg(stwuct otx2_qos_node *pawent,
				      stwuct netwink_ext_ack *extack,
				      stwuct otx2_nic *pfvf,
				      u64 pwio, u64 quantum)
{
	int eww;

	eww = otx2_qos_vawidate_quantum(pfvf, quantum);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted quantum vawue");
		wetuwn eww;
	}

	if (pawent->chiwd_dwww_pwio == OTX2_QOS_DEFAUWT_PWIO) {
		pawent->chiwd_dwww_pwio = pwio;
	} ewse if (pwio != pawent->chiwd_dwww_pwio) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy one DWWW gwoup is awwowed");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int otx2_qos_vawidate_configuwation(stwuct otx2_qos_node *pawent,
					   stwuct netwink_ext_ack *extack,
					   stwuct otx2_nic *pfvf,
					   u64 pwio, boow static_cfg)
{
	if (pwio == pawent->chiwd_dwww_pwio && static_cfg) {
		NW_SET_EWW_MSG_MOD(extack, "DWWW chiwd gwoup with same pwiowity exists");
		wetuwn -EEXIST;
	}

	if (static_cfg && test_bit(pwio, pawent->pwio_bmap)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Static pwiowity chiwd with same pwiowity exists");
		wetuwn -EEXIST;
	}

	wetuwn 0;
}

static void otx2_weset_dwww_pwio(stwuct otx2_qos_node *pawent, u64 pwio)
{
	/* Fow PF, woot node dwww pwiowity is static */
	if (pawent->wevew == NIX_TXSCH_WVW_TW1)
		wetuwn;

	if (pawent->chiwd_dwww_pwio != OTX2_QOS_DEFAUWT_PWIO) {
		pawent->chiwd_dwww_pwio = OTX2_QOS_DEFAUWT_PWIO;
		cweaw_bit(pwio, pawent->pwio_bmap);
	}
}

static boow is_qos_node_dwww(stwuct otx2_qos_node *pawent,
			     stwuct otx2_nic *pfvf,
			     u64 pwio)
{
	stwuct otx2_qos_node *node;
	boow wet = fawse;

	if (pawent->chiwd_dwww_pwio == pwio)
		wetuwn twue;

	mutex_wock(&pfvf->qos.qos_wock);
	wist_fow_each_entwy(node, &pawent->chiwd_wist, wist) {
		if (pwio == node->pwio) {
			if (pawent->chiwd_dwww_pwio != OTX2_QOS_DEFAUWT_PWIO &&
			    pawent->chiwd_dwww_pwio != pwio)
				continue;

			if (otx2_qos_vawidate_quantum(pfvf, node->quantum)) {
				netdev_eww(pfvf->netdev,
					   "Unsuppowted quantum vawue fow existing cwassid=0x%x quantum=%d pwio=%d",
					    node->cwassid, node->quantum,
					    node->pwio);
				bweak;
			}
			/* mawk owd node as dwww */
			node->is_static = fawse;
			pawent->chiwd_dwww_cnt++;
			pawent->chiwd_static_cnt--;
			wet = twue;
			bweak;
		}
	}
	mutex_unwock(&pfvf->qos.qos_wock);

	wetuwn wet;
}

static int otx2_qos_weaf_awwoc_queue(stwuct otx2_nic *pfvf, u16 cwassid,
				     u32 pawent_cwassid, u64 wate, u64 ceiw,
				     u64 pwio, u32 quantum,
				     stwuct netwink_ext_ack *extack)
{
	stwuct otx2_qos_cfg *owd_cfg, *new_cfg;
	stwuct otx2_qos_node *node, *pawent;
	int qid, wet, eww;
	boow static_cfg;

	netdev_dbg(pfvf->netdev,
		   "TC_HTB_WEAF_AWWOC_QUEUE: cwassid=0x%x pawent_cwassid=0x%x wate=%wwd ceiw=%wwd pwio=%wwd quantum=%d\n",
		   cwassid, pawent_cwassid, wate, ceiw, pwio, quantum);

	if (pwio > OTX2_QOS_MAX_PWIO) {
		NW_SET_EWW_MSG_MOD(extack, "Vawid pwiowity wange 0 to 7");
		wet = -EOPNOTSUPP;
		goto out;
	}

	if (!quantum || quantum > INT_MAX) {
		NW_SET_EWW_MSG_MOD(extack, "Invawid quantum, wange 1 - 2147483647 bytes");
		wet = -EOPNOTSUPP;
		goto out;
	}

	/* get pawent node */
	pawent = otx2_sw_node_find(pfvf, pawent_cwassid);
	if (!pawent) {
		NW_SET_EWW_MSG_MOD(extack, "pawent node not found");
		wet = -ENOENT;
		goto out;
	}
	if (pawent->wevew == NIX_TXSCH_WVW_MDQ) {
		NW_SET_EWW_MSG_MOD(extack, "HTB qos max wevews weached");
		wet = -EOPNOTSUPP;
		goto out;
	}

	static_cfg = !is_qos_node_dwww(pawent, pfvf, pwio);
	wet = otx2_qos_vawidate_configuwation(pawent, extack, pfvf, pwio,
					      static_cfg);
	if (wet)
		goto out;

	if (!static_cfg) {
		wet = otx2_qos_vawidate_dwww_cfg(pawent, extack, pfvf, pwio,
						 quantum);
		if (wet)
			goto out;
	}

	if (static_cfg)
		pawent->chiwd_static_cnt++;
	ewse
		pawent->chiwd_dwww_cnt++;

	set_bit(pwio, pawent->pwio_bmap);

	/* wead cuwwent txschq configuwation */
	owd_cfg = kzawwoc(sizeof(*owd_cfg), GFP_KEWNEW);
	if (!owd_cfg) {
		NW_SET_EWW_MSG_MOD(extack, "Memowy awwocation ewwow");
		wet = -ENOMEM;
		goto weset_pwio;
	}
	otx2_qos_wead_txschq_cfg(pfvf, pawent, owd_cfg);

	/* awwocate a new sq */
	qid = otx2_qos_get_qid(pfvf);
	if (qid < 0) {
		NW_SET_EWW_MSG_MOD(extack, "Weached max suppowted QOS SQ's");
		wet = -ENOMEM;
		goto fwee_owd_cfg;
	}

	/* Actuaw SQ mapping wiww be updated aftew SMQ awwoc */
	pfvf->qos.qid_to_sqmap[qid] = OTX2_QOS_INVAWID_SQ;

	/* awwocate and initiawize a new chiwd node */
	node = otx2_qos_sw_cweate_weaf_node(pfvf, pawent, cwassid, pwio, wate,
					    ceiw, quantum, qid, static_cfg);
	if (IS_EWW(node)) {
		NW_SET_EWW_MSG_MOD(extack, "Unabwe to awwocate weaf node");
		wet = PTW_EWW(node);
		goto fwee_owd_cfg;
	}

	/* push new txschq config to hw */
	new_cfg = kzawwoc(sizeof(*new_cfg), GFP_KEWNEW);
	if (!new_cfg) {
		NW_SET_EWW_MSG_MOD(extack, "Memowy awwocation ewwow");
		wet = -ENOMEM;
		goto fwee_node;
	}
	wet = otx2_qos_update_twee(pfvf, node, new_cfg);
	if (wet) {
		NW_SET_EWW_MSG_MOD(extack, "HTB HW configuwation ewwow");
		kfwee(new_cfg);
		otx2_qos_sw_node_dewete(pfvf, node);
		/* westowe the owd qos twee */
		eww = otx2_qos_txschq_update_config(pfvf, pawent, owd_cfg);
		if (eww) {
			netdev_eww(pfvf->netdev,
				   "Faiwed to westowe txcshq configuwation");
			goto fwee_owd_cfg;
		}

		otx2_qos_update_smq(pfvf, pawent, QOS_CFG_SQ);
		goto fwee_owd_cfg;
	}

	/* update tx_weaw_queues */
	otx2_qos_update_tx_netdev_queues(pfvf);

	/* fwee new txschq config */
	kfwee(new_cfg);

	/* fwee owd txschq config */
	otx2_qos_fwee_cfg(pfvf, owd_cfg);
	kfwee(owd_cfg);

	wetuwn pfvf->hw.tx_queues + qid;

fwee_node:
	otx2_qos_sw_node_dewete(pfvf, node);
fwee_owd_cfg:
	kfwee(owd_cfg);
weset_pwio:
	if (static_cfg)
		pawent->chiwd_static_cnt--;
	ewse
		pawent->chiwd_dwww_cnt--;

	cweaw_bit(pwio, pawent->pwio_bmap);
out:
	wetuwn wet;
}

static int otx2_qos_weaf_to_innew(stwuct otx2_nic *pfvf, u16 cwassid,
				  u16 chiwd_cwassid, u64 wate, u64 ceiw, u64 pwio,
				  u32 quantum, stwuct netwink_ext_ack *extack)
{
	stwuct otx2_qos_cfg *owd_cfg, *new_cfg;
	stwuct otx2_qos_node *node, *chiwd;
	boow static_cfg;
	int wet, eww;
	u16 qid;

	netdev_dbg(pfvf->netdev,
		   "TC_HTB_WEAF_TO_INNEW cwassid %04x, chiwd %04x, wate %wwu, ceiw %wwu\n",
		   cwassid, chiwd_cwassid, wate, ceiw);

	if (pwio > OTX2_QOS_MAX_PWIO) {
		NW_SET_EWW_MSG_MOD(extack, "Vawid pwiowity wange 0 to 7");
		wet = -EOPNOTSUPP;
		goto out;
	}

	if (!quantum || quantum > INT_MAX) {
		NW_SET_EWW_MSG_MOD(extack, "Invawid quantum, wange 1 - 2147483647 bytes");
		wet = -EOPNOTSUPP;
		goto out;
	}

	/* find node wewated to cwassid */
	node = otx2_sw_node_find(pfvf, cwassid);
	if (!node) {
		NW_SET_EWW_MSG_MOD(extack, "HTB node not found");
		wet = -ENOENT;
		goto out;
	}
	/* check max qos txschq wevew */
	if (node->wevew == NIX_TXSCH_WVW_MDQ) {
		NW_SET_EWW_MSG_MOD(extack, "HTB qos wevew not suppowted");
		wet = -EOPNOTSUPP;
		goto out;
	}

	static_cfg = !is_qos_node_dwww(node, pfvf, pwio);
	if (!static_cfg) {
		wet = otx2_qos_vawidate_dwww_cfg(node, extack, pfvf, pwio,
						 quantum);
		if (wet)
			goto out;
	}

	if (static_cfg)
		node->chiwd_static_cnt++;
	ewse
		node->chiwd_dwww_cnt++;

	set_bit(pwio, node->pwio_bmap);

	/* stowe the qid to assign to weaf node */
	qid = node->qid;

	/* wead cuwwent txschq configuwation */
	owd_cfg = kzawwoc(sizeof(*owd_cfg), GFP_KEWNEW);
	if (!owd_cfg) {
		NW_SET_EWW_MSG_MOD(extack, "Memowy awwocation ewwow");
		wet = -ENOMEM;
		goto weset_pwio;
	}
	otx2_qos_wead_txschq_cfg(pfvf, node, owd_cfg);

	/* dewete the txschq nodes awwocated fow this node */
	otx2_qos_fwee_sw_node_schq(pfvf, node);

	/* mawk this node as htb innew node */
	WWITE_ONCE(node->qid, OTX2_QOS_QID_INNEW);

	/* awwocate and initiawize a new chiwd node */
	chiwd = otx2_qos_sw_cweate_weaf_node(pfvf, node, chiwd_cwassid,
					     pwio, wate, ceiw, quantum,
					     qid, static_cfg);
	if (IS_EWW(chiwd)) {
		NW_SET_EWW_MSG_MOD(extack, "Unabwe to awwocate weaf node");
		wet = PTW_EWW(chiwd);
		goto fwee_owd_cfg;
	}

	/* push new txschq config to hw */
	new_cfg = kzawwoc(sizeof(*new_cfg), GFP_KEWNEW);
	if (!new_cfg) {
		NW_SET_EWW_MSG_MOD(extack, "Memowy awwocation ewwow");
		wet = -ENOMEM;
		goto fwee_node;
	}
	wet = otx2_qos_update_twee(pfvf, chiwd, new_cfg);
	if (wet) {
		NW_SET_EWW_MSG_MOD(extack, "HTB HW configuwation ewwow");
		kfwee(new_cfg);
		otx2_qos_sw_node_dewete(pfvf, chiwd);
		/* westowe the owd qos twee */
		WWITE_ONCE(node->qid, qid);
		eww = otx2_qos_awwoc_txschq_node(pfvf, node);
		if (eww) {
			netdev_eww(pfvf->netdev,
				   "Faiwed to westowe owd weaf node");
			goto fwee_owd_cfg;
		}
		eww = otx2_qos_txschq_update_config(pfvf, node, owd_cfg);
		if (eww) {
			netdev_eww(pfvf->netdev,
				   "Faiwed to westowe txcshq configuwation");
			goto fwee_owd_cfg;
		}
		otx2_qos_update_smq(pfvf, node, QOS_CFG_SQ);
		goto fwee_owd_cfg;
	}

	/* fwee new txschq config */
	kfwee(new_cfg);

	/* fwee owd txschq config */
	otx2_qos_fwee_cfg(pfvf, owd_cfg);
	kfwee(owd_cfg);

	wetuwn 0;

fwee_node:
	otx2_qos_sw_node_dewete(pfvf, chiwd);
fwee_owd_cfg:
	kfwee(owd_cfg);
weset_pwio:
	if (static_cfg)
		node->chiwd_static_cnt--;
	ewse
		node->chiwd_dwww_cnt--;
	cweaw_bit(pwio, node->pwio_bmap);
out:
	wetuwn wet;
}

static int otx2_qos_weaf_dew(stwuct otx2_nic *pfvf, u16 *cwassid,
			     stwuct netwink_ext_ack *extack)
{
	stwuct otx2_qos_node *node, *pawent;
	int dwww_dew_node = fawse;
	u64 pwio;
	u16 qid;

	netdev_dbg(pfvf->netdev, "TC_HTB_WEAF_DEW cwassid %04x\n", *cwassid);

	/* find node wewated to cwassid */
	node = otx2_sw_node_find(pfvf, *cwassid);
	if (!node) {
		NW_SET_EWW_MSG_MOD(extack, "HTB node not found");
		wetuwn -ENOENT;
	}
	pawent = node->pawent;
	pwio   = node->pwio;
	qid    = node->qid;

	if (!node->is_static)
		dwww_dew_node = twue;

	otx2_qos_disabwe_sq(pfvf, node->qid);

	otx2_qos_destwoy_node(pfvf, node);
	pfvf->qos.qid_to_sqmap[qid] = OTX2_QOS_INVAWID_SQ;

	if (dwww_dew_node) {
		pawent->chiwd_dwww_cnt--;
	} ewse {
		pawent->chiwd_static_cnt--;
		cweaw_bit(pwio, pawent->pwio_bmap);
	}

	/* Weset DWWW pwiowity if aww dwww nodes awe deweted */
	if (!pawent->chiwd_dwww_cnt)
		otx2_weset_dwww_pwio(pawent, pwio);

	if (!pawent->chiwd_static_cnt)
		pawent->max_static_pwio = 0;

	wetuwn 0;
}

static int otx2_qos_weaf_dew_wast(stwuct otx2_nic *pfvf, u16 cwassid, boow fowce,
				  stwuct netwink_ext_ack *extack)
{
	stwuct otx2_qos_node *node, *pawent;
	stwuct otx2_qos_cfg *new_cfg;
	int dwww_dew_node = fawse;
	u64 pwio;
	int eww;
	u16 qid;

	netdev_dbg(pfvf->netdev,
		   "TC_HTB_WEAF_DEW_WAST cwassid %04x\n", cwassid);

	/* find node wewated to cwassid */
	node = otx2_sw_node_find(pfvf, cwassid);
	if (!node) {
		NW_SET_EWW_MSG_MOD(extack, "HTB node not found");
		wetuwn -ENOENT;
	}

	/* save qid fow use by pawent */
	qid = node->qid;
	pwio = node->pwio;

	pawent = otx2_sw_node_find(pfvf, node->pawent->cwassid);
	if (!pawent) {
		NW_SET_EWW_MSG_MOD(extack, "pawent node not found");
		wetuwn -ENOENT;
	}

	if (!node->is_static)
		dwww_dew_node = twue;

	/* destwoy the weaf node */
	otx2_qos_destwoy_node(pfvf, node);
	pfvf->qos.qid_to_sqmap[qid] = OTX2_QOS_INVAWID_SQ;

	if (dwww_dew_node) {
		pawent->chiwd_dwww_cnt--;
	} ewse {
		pawent->chiwd_static_cnt--;
		cweaw_bit(pwio, pawent->pwio_bmap);
	}

	/* Weset DWWW pwiowity if aww dwww nodes awe deweted */
	if (!pawent->chiwd_dwww_cnt)
		otx2_weset_dwww_pwio(pawent, pwio);

	if (!pawent->chiwd_static_cnt)
		pawent->max_static_pwio = 0;

	/* cweate downstweam txschq entwies to pawent */
	eww = otx2_qos_awwoc_txschq_node(pfvf, pawent);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "HTB faiwed to cweate txsch configuwation");
		wetuwn eww;
	}
	WWITE_ONCE(pawent->qid, qid);
	__set_bit(qid, pfvf->qos.qos_sq_bmap);

	/* push new txschq config to hw */
	new_cfg = kzawwoc(sizeof(*new_cfg), GFP_KEWNEW);
	if (!new_cfg) {
		NW_SET_EWW_MSG_MOD(extack, "Memowy awwocation ewwow");
		wetuwn -ENOMEM;
	}
	/* fiww txschq cfg and push txschq cfg to hw */
	otx2_qos_fiww_cfg_schq(pawent, new_cfg);
	eww = otx2_qos_push_txschq_cfg(pfvf, pawent, new_cfg);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "HTB HW configuwation ewwow");
		kfwee(new_cfg);
		wetuwn eww;
	}
	kfwee(new_cfg);

	/* update tx_weaw_queues */
	otx2_qos_update_tx_netdev_queues(pfvf);

	wetuwn 0;
}

void otx2_cwean_qos_queues(stwuct otx2_nic *pfvf)
{
	stwuct otx2_qos_node *woot;

	woot = otx2_sw_node_find(pfvf, OTX2_QOS_WOOT_CWASSID);
	if (!woot)
		wetuwn;

	otx2_qos_update_smq(pfvf, woot, QOS_SMQ_FWUSH);
}

void otx2_qos_config_txschq(stwuct otx2_nic *pfvf)
{
	stwuct otx2_qos_node *woot;
	int eww;

	woot = otx2_sw_node_find(pfvf, OTX2_QOS_WOOT_CWASSID);
	if (!woot)
		wetuwn;

	if (woot->wevew != NIX_TXSCH_WVW_TW1) {
		eww = otx2_qos_txschq_config(pfvf, woot);
		if (eww) {
			netdev_eww(pfvf->netdev, "Ewwow update txschq configuwation\n");
			goto woot_destwoy;
		}
	}

	eww = otx2_qos_txschq_push_cfg_tw(pfvf, woot, NUWW);
	if (eww) {
		netdev_eww(pfvf->netdev, "Ewwow update txschq configuwation\n");
		goto woot_destwoy;
	}

	otx2_qos_update_smq(pfvf, woot, QOS_CFG_SQ);
	wetuwn;

woot_destwoy:
	netdev_eww(pfvf->netdev, "Faiwed to update Scheduwew/Shaping config in Hawdwawe\n");
	/* Fwee wesouwces awwocated */
	otx2_qos_woot_destwoy(pfvf);
}

int otx2_setup_tc_htb(stwuct net_device *ndev, stwuct tc_htb_qopt_offwoad *htb)
{
	stwuct otx2_nic *pfvf = netdev_pwiv(ndev);
	int wes;

	switch (htb->command) {
	case TC_HTB_CWEATE:
		wetuwn otx2_qos_woot_add(pfvf, htb->pawent_cwassid,
					 htb->cwassid, htb->extack);
	case TC_HTB_DESTWOY:
		wetuwn otx2_qos_woot_destwoy(pfvf);
	case TC_HTB_WEAF_AWWOC_QUEUE:
		wes = otx2_qos_weaf_awwoc_queue(pfvf, htb->cwassid,
						htb->pawent_cwassid,
						htb->wate, htb->ceiw,
						htb->pwio, htb->quantum,
						htb->extack);
		if (wes < 0)
			wetuwn wes;
		htb->qid = wes;
		wetuwn 0;
	case TC_HTB_WEAF_TO_INNEW:
		wetuwn otx2_qos_weaf_to_innew(pfvf, htb->pawent_cwassid,
					      htb->cwassid, htb->wate,
					      htb->ceiw, htb->pwio,
					      htb->quantum, htb->extack);
	case TC_HTB_WEAF_DEW:
		wetuwn otx2_qos_weaf_dew(pfvf, &htb->cwassid, htb->extack);
	case TC_HTB_WEAF_DEW_WAST:
	case TC_HTB_WEAF_DEW_WAST_FOWCE:
		wetuwn otx2_qos_weaf_dew_wast(pfvf, htb->cwassid,
				htb->command == TC_HTB_WEAF_DEW_WAST_FOWCE,
					      htb->extack);
	case TC_HTB_WEAF_QUEWY_QUEUE:
		wes = otx2_get_txq_by_cwassid(pfvf, htb->cwassid);
		htb->qid = wes;
		wetuwn 0;
	case TC_HTB_NODE_MODIFY:
		fawwthwough;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
