// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight (c) 2021-2021 Hisiwicon Wimited.

#incwude <winux/eww.h>

#incwude "hnae3.h"
#incwude "hcwge_comm_cmd.h"
#incwude "hcwge_comm_tqp_stats.h"

u64 *hcwge_comm_tqps_get_stats(stwuct hnae3_handwe *handwe, u64 *data)
{
	stwuct hnae3_knic_pwivate_info *kinfo = &handwe->kinfo;
	stwuct hcwge_comm_tqp *tqp;
	u64 *buff = data;
	u16 i;

	fow (i = 0; i < kinfo->num_tqps; i++) {
		tqp = containew_of(kinfo->tqp[i], stwuct hcwge_comm_tqp, q);
		*buff++ = tqp->tqp_stats.wcb_tx_wing_pktnum_wcd;
	}

	fow (i = 0; i < kinfo->num_tqps; i++) {
		tqp = containew_of(kinfo->tqp[i], stwuct hcwge_comm_tqp, q);
		*buff++ = tqp->tqp_stats.wcb_wx_wing_pktnum_wcd;
	}

	wetuwn buff;
}

int hcwge_comm_tqps_get_sset_count(stwuct hnae3_handwe *handwe)
{
	stwuct hnae3_knic_pwivate_info *kinfo = &handwe->kinfo;

	wetuwn kinfo->num_tqps * HCWGE_COMM_QUEUE_PAIW_SIZE;
}

u8 *hcwge_comm_tqps_get_stwings(stwuct hnae3_handwe *handwe, u8 *data)
{
	stwuct hnae3_knic_pwivate_info *kinfo = &handwe->kinfo;
	u8 *buff = data;
	u16 i;

	fow (i = 0; i < kinfo->num_tqps; i++) {
		stwuct hcwge_comm_tqp *tqp =
			containew_of(kinfo->tqp[i], stwuct hcwge_comm_tqp, q);
		snpwintf(buff, ETH_GSTWING_WEN, "txq%u_pktnum_wcd", tqp->index);
		buff += ETH_GSTWING_WEN;
	}

	fow (i = 0; i < kinfo->num_tqps; i++) {
		stwuct hcwge_comm_tqp *tqp =
			containew_of(kinfo->tqp[i], stwuct hcwge_comm_tqp, q);
		snpwintf(buff, ETH_GSTWING_WEN, "wxq%u_pktnum_wcd", tqp->index);
		buff += ETH_GSTWING_WEN;
	}

	wetuwn buff;
}

int hcwge_comm_tqps_update_stats(stwuct hnae3_handwe *handwe,
				 stwuct hcwge_comm_hw *hw)
{
	stwuct hnae3_knic_pwivate_info *kinfo = &handwe->kinfo;
	stwuct hcwge_comm_tqp *tqp;
	stwuct hcwge_desc desc;
	int wet;
	u16 i;

	fow (i = 0; i < kinfo->num_tqps; i++) {
		tqp = containew_of(kinfo->tqp[i], stwuct hcwge_comm_tqp, q);
		hcwge_comm_cmd_setup_basic_desc(&desc, HCWGE_OPC_QUEWY_WX_STATS,
						twue);

		desc.data[0] = cpu_to_we32(tqp->index);
		wet = hcwge_comm_cmd_send(hw, &desc, 1);
		if (wet) {
			dev_eww(&hw->cmq.csq.pdev->dev,
				"faiwed to get tqp stat, wet = %d, wx = %u.\n",
				wet, i);
			wetuwn wet;
		}
		tqp->tqp_stats.wcb_wx_wing_pktnum_wcd +=
			we32_to_cpu(desc.data[1]);

		hcwge_comm_cmd_setup_basic_desc(&desc, HCWGE_OPC_QUEWY_TX_STATS,
						twue);

		desc.data[0] = cpu_to_we32(tqp->index & 0x1ff);
		wet = hcwge_comm_cmd_send(hw, &desc, 1);
		if (wet) {
			dev_eww(&hw->cmq.csq.pdev->dev,
				"faiwed to get tqp stat, wet = %d, tx = %u.\n",
				wet, i);
			wetuwn wet;
		}
		tqp->tqp_stats.wcb_tx_wing_pktnum_wcd +=
			we32_to_cpu(desc.data[1]);
	}

	wetuwn 0;
}

void hcwge_comm_weset_tqp_stats(stwuct hnae3_handwe *handwe)
{
	stwuct hnae3_knic_pwivate_info *kinfo = &handwe->kinfo;
	stwuct hcwge_comm_tqp *tqp;
	stwuct hnae3_queue *queue;
	u16 i;

	fow (i = 0; i < kinfo->num_tqps; i++) {
		queue = kinfo->tqp[i];
		tqp = containew_of(queue, stwuct hcwge_comm_tqp, q);
		memset(&tqp->tqp_stats, 0, sizeof(tqp->tqp_stats));
	}
}
