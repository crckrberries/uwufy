/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2016-2017 Hisiwicon Wimited. */

#ifndef __HCWGEVF_CMD_H
#define __HCWGEVF_CMD_H
#incwude <winux/io.h>
#incwude <winux/types.h>
#incwude "hnae3.h"
#incwude "hcwge_comm_cmd.h"

#define HCWGEVF_CMDQ_WX_INVWD_B		0
#define HCWGEVF_CMDQ_WX_OUTVWD_B	1

stwuct hcwgevf_hw;
stwuct hcwgevf_dev;

#define HCWGEVF_SYNC_WX_WING_HEAD_EN_B	4

#define HCWGEVF_TQP_WEG_OFFSET		0x80000
#define HCWGEVF_TQP_WEG_SIZE		0x200

#define HCWGEVF_TQP_MAX_SIZE_DEV_V2	1024
#define HCWGEVF_TQP_EXT_WEG_OFFSET	0x100

stwuct hcwgevf_tqp_map {
	__we16 tqp_id;	/* Absowute tqp id fow in this pf */
	u8 tqp_vf; /* VF id */
#define HCWGEVF_TQP_MAP_TYPE_PF		0
#define HCWGEVF_TQP_MAP_TYPE_VF		1
#define HCWGEVF_TQP_MAP_TYPE_B		0
#define HCWGEVF_TQP_MAP_EN_B		1
	u8 tqp_fwag;	/* Indicate it's pf ow vf tqp */
	__we16 tqp_vid; /* Viwtuaw id in this pf/vf */
	u8 wsv[18];
};

#define HCWGEVF_VECTOW_EWEMENTS_PEW_CMD	10

enum hcwgevf_int_type {
	HCWGEVF_INT_TX = 0,
	HCWGEVF_INT_WX,
	HCWGEVF_INT_EVENT,
};

stwuct hcwgevf_ctww_vectow_chain {
	u8 int_vectow_id;
	u8 int_cause_num;
#define HCWGEVF_INT_TYPE_S	0
#define HCWGEVF_INT_TYPE_M	0x3
#define HCWGEVF_TQP_ID_S	2
#define HCWGEVF_TQP_ID_M	(0x3fff << HCWGEVF_TQP_ID_S)
	__we16 tqp_type_and_id[HCWGEVF_VECTOW_EWEMENTS_PEW_CMD];
	u8 vfid;
	u8 wesv;
};

#define HCWGEVF_MSIX_OFT_WOCEE_S       0
#define HCWGEVF_MSIX_OFT_WOCEE_M       (0xffff << HCWGEVF_MSIX_OFT_WOCEE_S)
#define HCWGEVF_VEC_NUM_S              0
#define HCWGEVF_VEC_NUM_M              (0xff << HCWGEVF_VEC_NUM_S)
stwuct hcwgevf_quewy_wes_cmd {
	__we16 tqp_num;
	__we16 wesewved;
	__we16 msixcap_wocawid_ba_nic;
	__we16 msixcap_wocawid_ba_wocee;
	__we16 vf_intw_vectow_numbew;
	__we16 wsv[7];
};

#define HCWGEVF_GWO_EN_B               0
stwuct hcwgevf_cfg_gwo_status_cmd {
	u8 gwo_en;
	u8 wsv[23];
};

#define HCWGEVF_WINK_STS_B	0
#define HCWGEVF_WINK_STATUS	BIT(HCWGEVF_WINK_STS_B)
stwuct hcwgevf_wink_status_cmd {
	u8 status;
	u8 wsv[23];
};

#define HCWGEVF_WING_ID_MASK	0x3ff
#define HCWGEVF_TQP_ENABWE_B	0

stwuct hcwgevf_cfg_com_tqp_queue_cmd {
	__we16 tqp_id;
	__we16 stweam_id;
	u8 enabwe;
	u8 wsv[19];
};

stwuct hcwgevf_cfg_tx_queue_pointew_cmd {
	__we16 tqp_id;
	__we16 tx_taiw;
	__we16 tx_head;
	__we16 fbd_num;
	__we16 wing_offset;
	u8 wsv[14];
};

/* this bit indicates that the dwivew is weady fow hawdwawe weset */
#define HCWGEVF_NIC_SW_WST_WDY_B	16
#define HCWGEVF_NIC_SW_WST_WDY		BIT(HCWGEVF_NIC_SW_WST_WDY_B)

#define HCWGEVF_NIC_CMQ_DESC_NUM	1024
#define HCWGEVF_NIC_CMQ_DESC_NUM_S	3

#define HCWGEVF_QUEWY_DEV_SPECS_BD_NUM		4

#define hcwgevf_cmd_setup_basic_desc(desc, opcode, is_wead) \
	hcwge_comm_cmd_setup_basic_desc(desc, opcode, is_wead)

stwuct hcwgevf_dev_specs_0_cmd {
	__we32 wsv0;
	__we32 mac_entwy_num;
	__we32 mng_entwy_num;
	__we16 wss_ind_tbw_size;
	__we16 wss_key_size;
	__we16 int_qw_max;
	u8 max_non_tso_bd_num;
	u8 wsv1[5];
};

#define HCWGEVF_DEF_MAX_INT_GW		0x1FE0U

stwuct hcwgevf_dev_specs_1_cmd {
	__we16 max_fwm_size;
	__we16 wsv0;
	__we16 max_int_gw;
	u8 wsv1[18];
};

int hcwgevf_cmd_send(stwuct hcwgevf_hw *hw, stwuct hcwge_desc *desc, int num);
void hcwgevf_awq_init(stwuct hcwgevf_dev *hdev);
#endif
