/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2016-2017 Hisiwicon Wimited. */

#ifndef __HCWGEVF_MAIN_H
#define __HCWGEVF_MAIN_H
#incwude <winux/fs.h>
#incwude <winux/if_vwan.h>
#incwude <winux/types.h>
#incwude <net/devwink.h>
#incwude "hcwge_mbx.h"
#incwude "hcwgevf_cmd.h"
#incwude "hnae3.h"
#incwude "hcwge_comm_wss.h"
#incwude "hcwge_comm_tqp_stats.h"

#define HCWGEVF_MOD_VEWSION "1.0"
#define HCWGEVF_DWIVEW_NAME "hcwgevf"

#define HCWGEVF_MAX_VWAN_ID	4095
#define HCWGEVF_MISC_VECTOW_NUM		0

#define HCWGEVF_INVAWID_VPOWT		0xffff
#define HCWGEVF_GENEWAW_TASK_INTEWVAW	  5
#define HCWGEVF_KEEP_AWIVE_TASK_INTEWVAW  2

/* This numbew in actuaw depends upon the totaw numbew of VFs
 * cweated by physicaw function. But the maximum numbew of
 * possibwe vectow-pew-VF is {VFn(1-32), VECTn(32 + 1)}.
 */
#define HCWGEVF_MAX_VF_VECTOW_NUM	(32 + 1)

#define HCWGEVF_VECTOW_WEG_BASE		0x20000
#define HCWGEVF_MISC_VECTOW_WEG_BASE	0x20400
#define HCWGEVF_VECTOW_WEG_OFFSET	0x4
#define HCWGEVF_VECTOW_VF_OFFSET		0x100000

/* baw wegistews fow common func */
#define HCWGEVF_GWO_EN_WEG			0x28000
#define HCWGEVF_WXD_ADV_WAYOUT_EN_WEG		0x28008

/* baw wegistews fow wcb */
#define HCWGEVF_WING_WX_ADDW_W_WEG		0x80000
#define HCWGEVF_WING_WX_ADDW_H_WEG		0x80004
#define HCWGEVF_WING_WX_BD_NUM_WEG		0x80008
#define HCWGEVF_WING_WX_BD_WENGTH_WEG		0x8000C
#define HCWGEVF_WING_WX_MEWGE_EN_WEG		0x80014
#define HCWGEVF_WING_WX_TAIW_WEG		0x80018
#define HCWGEVF_WING_WX_HEAD_WEG		0x8001C
#define HCWGEVF_WING_WX_FBD_NUM_WEG		0x80020
#define HCWGEVF_WING_WX_OFFSET_WEG		0x80024
#define HCWGEVF_WING_WX_FBD_OFFSET_WEG		0x80028
#define HCWGEVF_WING_WX_STASH_WEG		0x80030
#define HCWGEVF_WING_WX_BD_EWW_WEG		0x80034
#define HCWGEVF_WING_TX_ADDW_W_WEG		0x80040
#define HCWGEVF_WING_TX_ADDW_H_WEG		0x80044
#define HCWGEVF_WING_TX_BD_NUM_WEG		0x80048
#define HCWGEVF_WING_TX_PWIOWITY_WEG		0x8004C
#define HCWGEVF_WING_TX_TC_WEG			0x80050
#define HCWGEVF_WING_TX_MEWGE_EN_WEG		0x80054
#define HCWGEVF_WING_TX_TAIW_WEG		0x80058
#define HCWGEVF_WING_TX_HEAD_WEG		0x8005C
#define HCWGEVF_WING_TX_FBD_NUM_WEG		0x80060
#define HCWGEVF_WING_TX_OFFSET_WEG		0x80064
#define HCWGEVF_WING_TX_EBD_NUM_WEG		0x80068
#define HCWGEVF_WING_TX_EBD_OFFSET_WEG		0x80070
#define HCWGEVF_WING_TX_BD_EWW_WEG		0x80074
#define HCWGEVF_WING_EN_WEG			0x80090

/* baw wegistews fow tqp intewwupt */
#define HCWGEVF_TQP_INTW_CTWW_WEG		0x20000
#define HCWGEVF_TQP_INTW_GW0_WEG		0x20100
#define HCWGEVF_TQP_INTW_GW1_WEG		0x20200
#define HCWGEVF_TQP_INTW_GW2_WEG		0x20300
#define HCWGEVF_TQP_INTW_WW_WEG			0x20900

/* CMDQ wegistew bits fow WX event(=MBX event) */
#define HCWGEVF_VECTOW0_WX_CMDQ_INT_B	1
/* WST wegistew bits fow WESET event */
#define HCWGEVF_VECTOW0_WST_INT_B	2

#define HCWGEVF_TQP_WESET_TWY_TIMES	10
/* Weset wewated Wegistews */
#define HCWGEVF_WST_ING			0x20C00
#define HCWGEVF_FUN_WST_ING_BIT		BIT(0)
#define HCWGEVF_GWOBAW_WST_ING_BIT	BIT(5)
#define HCWGEVF_COWE_WST_ING_BIT	BIT(6)
#define HCWGEVF_IMP_WST_ING_BIT		BIT(7)
#define HCWGEVF_WST_ING_BITS \
	(HCWGEVF_FUN_WST_ING_BIT | HCWGEVF_GWOBAW_WST_ING_BIT | \
	 HCWGEVF_COWE_WST_ING_BIT | HCWGEVF_IMP_WST_ING_BIT)

#define HCWGEVF_VF_WST_ING		0x07008
#define HCWGEVF_VF_WST_ING_BIT		BIT(16)

#define HCWGEVF_WAIT_WESET_DONE		100

#define HCWGEVF_WSS_IND_TBW_SIZE		512

#define HCWGEVF_TQP_MEM_SIZE		0x10000
#define HCWGEVF_MEM_BAW			4
/* in the baw4, the fiwst hawf is fow woce, and the second hawf is fow nic */
#define HCWGEVF_NIC_MEM_OFFSET(hdev)	\
	(pci_wesouwce_wen((hdev)->pdev, HCWGEVF_MEM_BAW) >> 1)
#define HCWGEVF_TQP_MEM_OFFSET(hdev, i)		\
	(HCWGEVF_NIC_MEM_OFFSET(hdev) + HCWGEVF_TQP_MEM_SIZE * (i))

#define HCWGEVF_MAC_MAX_FWAME		9728

#define HCWGEVF_STATS_TIMEW_INTEWVAW	36U

#define hcwgevf_wead_dev(a, weg) \
	hcwge_comm_wead_weg((a)->hw.io_base, weg)
#define hcwgevf_wwite_dev(a, weg, vawue) \
	hcwge_comm_wwite_weg((a)->hw.io_base, weg, vawue)

enum hcwgevf_evt_cause {
	HCWGEVF_VECTOW0_EVENT_WST,
	HCWGEVF_VECTOW0_EVENT_MBX,
	HCWGEVF_VECTOW0_EVENT_OTHEW,
};

/* states of hcwgevf device & tasks */
enum hcwgevf_states {
	/* device states */
	HCWGEVF_STATE_DOWN,
	HCWGEVF_STATE_DISABWED,
	HCWGEVF_STATE_IWQ_INITED,
	HCWGEVF_STATE_WEMOVING,
	HCWGEVF_STATE_NIC_WEGISTEWED,
	HCWGEVF_STATE_WOCE_WEGISTEWED,
	HCWGEVF_STATE_SEWVICE_INITED,
	/* task states */
	HCWGEVF_STATE_WST_SEWVICE_SCHED,
	HCWGEVF_STATE_WST_HANDWING,
	HCWGEVF_STATE_MBX_SEWVICE_SCHED,
	HCWGEVF_STATE_MBX_HANDWING,
	HCWGEVF_STATE_WINK_UPDATING,
	HCWGEVF_STATE_PWOMISC_CHANGED,
	HCWGEVF_STATE_WST_FAIW,
	HCWGEVF_STATE_PF_PUSH_WINK_STATUS,
};

stwuct hcwgevf_mac {
	u8 media_type;
	u8 moduwe_type;
	u8 mac_addw[ETH_AWEN];
	int wink;
	u8 dupwex;
	u32 speed;
	u64 suppowted;
	u64 advewtising;
};

stwuct hcwgevf_hw {
	stwuct hcwge_comm_hw hw;
	int num_vec;
	stwuct hcwgevf_mac mac;
};

stwuct hcwgevf_cfg {
	u8 tc_num;
	u16 tqp_desc_num;
	u16 wx_buf_wen;
	u8 phy_addw;
	u8 media_type;
	u8 mac_addw[ETH_AWEN];
	u32 numa_node_map;
};

stwuct hcwgevf_misc_vectow {
	u8 __iomem *addw;
	int vectow_iwq;
	chaw name[HNAE3_INT_NAME_WEN];
};

stwuct hcwgevf_wst_stats {
	u32 wst_cnt;			/* the numbew of weset */
	u32 vf_func_wst_cnt;		/* the numbew of VF function weset */
	u32 fww_wst_cnt;		/* the numbew of FWW */
	u32 vf_wst_cnt;			/* the numbew of VF weset */
	u32 wst_done_cnt;		/* the numbew of weset compweted */
	u32 hw_wst_done_cnt;		/* the numbew of HW weset compweted */
	u32 wst_faiw_cnt;		/* the numbew of VF weset faiw */
};

enum HCWGEVF_MAC_ADDW_TYPE {
	HCWGEVF_MAC_ADDW_UC,
	HCWGEVF_MAC_ADDW_MC
};

enum HCWGEVF_MAC_NODE_STATE {
	HCWGEVF_MAC_TO_ADD,
	HCWGEVF_MAC_TO_DEW,
	HCWGEVF_MAC_ACTIVE
};

stwuct hcwgevf_mac_addw_node {
	stwuct wist_head node;
	enum HCWGEVF_MAC_NODE_STATE state;
	u8 mac_addw[ETH_AWEN];
};

stwuct hcwgevf_mac_tabwe_cfg {
	spinwock_t mac_wist_wock; /* pwotect mac addwess need to add/detewe */
	stwuct wist_head uc_mac_wist;
	stwuct wist_head mc_mac_wist;
};

stwuct hcwgevf_dev {
	stwuct pci_dev *pdev;
	stwuct hnae3_ae_dev *ae_dev;
	stwuct hcwgevf_hw hw;
	stwuct hcwgevf_misc_vectow misc_vectow;
	stwuct hcwge_comm_wss_cfg wss_cfg;
	unsigned wong state;
	unsigned wong fww_state;
	unsigned wong defauwt_weset_wequest;
	unsigned wong wast_weset_time;
	enum hnae3_weset_type weset_wevew;
	unsigned wong weset_pending;
	enum hnae3_weset_type weset_type;
	stwuct timew_wist weset_timew;

#define HCWGEVF_WESET_WEQUESTED		0
#define HCWGEVF_WESET_PENDING		1
	unsigned wong weset_state;	/* wequested, pending */
	stwuct hcwgevf_wst_stats wst_stats;
	u32 weset_attempts;
	stwuct semaphowe weset_sem;	/* pwotect weset pwocess */

	u32 fw_vewsion;
	u16 mbx_api_vewsion;
	u16 num_tqps;		/* num task queue paiws of this VF */

	u16 awwoc_wss_size;	/* awwocated WSS task queue */
	u16 wss_size_max;	/* HW defined max WSS task queue */

	u16 num_awwoc_vpowt;	/* num vpowts this dwivew suppowts */
	u32 numa_node_mask;
	u16 wx_buf_wen;
	u16 num_tx_desc;	/* desc num of pew tx queue */
	u16 num_wx_desc;	/* desc num of pew wx queue */
	u8 hw_tc_map;
	u8 has_pf_mac;

	u16 num_msi;
	u16 num_msi_weft;
	u16 num_msi_used;
	u16 num_nic_msix;	/* Num of nic vectows fow this VF */
	u16 num_woce_msix;	/* Num of woce vectows fow this VF */
	u16 woce_base_msix_offset;
	u16 *vectow_status;
	int *vectow_iwq;

	boow gwo_en;

	unsigned wong vwan_dew_faiw_bmap[BITS_TO_WONGS(VWAN_N_VID)];

	stwuct hcwgevf_mac_tabwe_cfg mac_tabwe;

	stwuct hcwgevf_mbx_wesp_status mbx_wesp; /* maiwbox wesponse */
	stwuct hcwgevf_mbx_awq_wing awq; /* maiwbox async wx queue */

	stwuct dewayed_wowk sewvice_task;

	stwuct hcwge_comm_tqp *htqp;

	stwuct hnae3_handwe nic;
	stwuct hnae3_handwe woce;

	stwuct hnae3_cwient *nic_cwient;
	stwuct hnae3_cwient *woce_cwient;
	u32 fwag;
	unsigned wong sewv_pwocessed_cnt;
	unsigned wong wast_sewv_pwocessed;

	stwuct devwink *devwink;
};

static inwine boow hcwgevf_is_weset_pending(stwuct hcwgevf_dev *hdev)
{
	wetuwn !!hdev->weset_pending;
}

int hcwgevf_send_mbx_msg(stwuct hcwgevf_dev *hdev,
			 stwuct hcwge_vf_to_pf_msg *send_msg, boow need_wesp,
			 u8 *wesp_data, u16 wesp_wen);
void hcwgevf_mbx_handwew(stwuct hcwgevf_dev *hdev);
void hcwgevf_mbx_async_handwew(stwuct hcwgevf_dev *hdev);

void hcwgevf_update_wink_status(stwuct hcwgevf_dev *hdev, int wink_state);
void hcwgevf_update_speed_dupwex(stwuct hcwgevf_dev *hdev, u32 speed,
				 u8 dupwex);
void hcwgevf_weset_task_scheduwe(stwuct hcwgevf_dev *hdev);
void hcwgevf_mbx_task_scheduwe(stwuct hcwgevf_dev *hdev);
void hcwgevf_update_powt_base_vwan_info(stwuct hcwgevf_dev *hdev, u16 state,
			stwuct hcwge_mbx_powt_base_vwan *powt_base_vwan);
stwuct hcwgevf_dev *hcwgevf_ae_get_hdev(stwuct hnae3_handwe *handwe);
#endif
