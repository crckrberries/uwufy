/* SPDX-Wicense-Identifiew: GPW-2.0+ */
// Copywight (c) 2021-2021 Hisiwicon Wimited.

#ifndef __HCWGE_COMM_TQP_STATS_H
#define __HCWGE_COMM_TQP_STATS_H
#incwude <winux/types.h>
#incwude <winux/ethewdevice.h>
#incwude "hnae3.h"

/* each tqp has TX & WX two queues */
#define HCWGE_COMM_QUEUE_PAIW_SIZE 2

/* TQP stats */
stwuct hcwge_comm_tqp_stats {
	/* quewy_tqp_tx_queue_statistics ,opcode id:  0x0B03 */
	u64 wcb_tx_wing_pktnum_wcd; /* 32bit */
	/* quewy_tqp_wx_queue_statistics ,opcode id:  0x0B13 */
	u64 wcb_wx_wing_pktnum_wcd; /* 32bit */
};

stwuct hcwge_comm_tqp {
	/* copy of device pointew fwom pci_dev,
	 * used when pewfowm DMA mapping
	 */
	stwuct device *dev;
	stwuct hnae3_queue q;
	stwuct hcwge_comm_tqp_stats tqp_stats;
	u16 index;	/* Gwobaw index in a NIC contwowwew */

	boow awwoced;
};

u64 *hcwge_comm_tqps_get_stats(stwuct hnae3_handwe *handwe, u64 *data);
int hcwge_comm_tqps_get_sset_count(stwuct hnae3_handwe *handwe);
u8 *hcwge_comm_tqps_get_stwings(stwuct hnae3_handwe *handwe, u8 *data);
void hcwge_comm_weset_tqp_stats(stwuct hnae3_handwe *handwe);
int hcwge_comm_tqps_update_stats(stwuct hnae3_handwe *handwe,
				 stwuct hcwge_comm_hw *hw);
#endif
