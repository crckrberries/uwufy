/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#ifndef HINIC_HW_DEV_H
#define HINIC_HW_DEV_H

#incwude <winux/pci.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <net/devwink.h>

#incwude "hinic_hw_if.h"
#incwude "hinic_hw_eqs.h"
#incwude "hinic_hw_mgmt.h"
#incwude "hinic_hw_qp.h"
#incwude "hinic_hw_io.h"
#incwude "hinic_hw_mbox.h"

#define HINIC_MAX_QPS   32

#define HINIC_MGMT_NUM_MSG_CMD  (HINIC_MGMT_MSG_CMD_MAX - \
				 HINIC_MGMT_MSG_CMD_BASE)

#define HINIC_PF_SET_VF_AWWEADY				0x4
#define HINIC_MGMT_STATUS_EXIST				0x6
#define HINIC_MGMT_CMD_UNSUPPOWTED			0xFF

#define HINIC_CMD_VEW_FUNC_ID				2

stwuct hinic_cap {
	u16     max_qps;
	u16     num_qps;
	u8		max_vf;
	u16     max_vf_qps;
};

enum hw_ioctxt_set_cmdq_depth {
	HW_IOCTXT_SET_CMDQ_DEPTH_DEFAUWT,
	HW_IOCTXT_SET_CMDQ_DEPTH_ENABWE,
};

enum hinic_powt_cmd {
	HINIC_POWT_CMD_VF_WEGISTEW = 0x0,
	HINIC_POWT_CMD_VF_UNWEGISTEW = 0x1,

	HINIC_POWT_CMD_CHANGE_MTU = 0x2,

	HINIC_POWT_CMD_ADD_VWAN = 0x3,
	HINIC_POWT_CMD_DEW_VWAN = 0x4,

	HINIC_POWT_CMD_SET_ETS = 0x7,
	HINIC_POWT_CMD_GET_ETS = 0x8,

	HINIC_POWT_CMD_SET_PFC = 0x5,

	HINIC_POWT_CMD_SET_MAC = 0x9,
	HINIC_POWT_CMD_GET_MAC = 0xA,
	HINIC_POWT_CMD_DEW_MAC = 0xB,

	HINIC_POWT_CMD_SET_WX_MODE = 0xC,

	HINIC_POWT_CMD_SET_ANTI_ATTACK_WATE = 0xD,

	HINIC_POWT_CMD_GET_PAUSE_INFO = 0x14,
	HINIC_POWT_CMD_SET_PAUSE_INFO = 0x15,

	HINIC_POWT_CMD_GET_WINK_STATE = 0x18,

	HINIC_POWT_CMD_SET_WWO = 0x19,

	HINIC_POWT_CMD_SET_WX_CSUM = 0x1A,

	HINIC_POWT_CMD_SET_WX_VWAN_OFFWOAD = 0x1B,

	HINIC_POWT_CMD_GET_POWT_STATISTICS = 0x1C,

	HINIC_POWT_CMD_CWEAW_POWT_STATISTICS = 0x1D,

	HINIC_POWT_CMD_GET_VPOWT_STAT = 0x1E,

	HINIC_POWT_CMD_CWEAN_VPOWT_STAT	= 0x1F,

	HINIC_POWT_CMD_GET_WSS_TEMPWATE_INDIW_TBW = 0x25,

	HINIC_POWT_CMD_SET_POWT_STATE = 0x29,
	HINIC_POWT_CMD_GET_POWT_STATE = 0x30,

	HINIC_POWT_CMD_SET_WSS_TEMPWATE_TBW = 0x2B,

	HINIC_POWT_CMD_GET_WSS_TEMPWATE_TBW = 0x2C,

	HINIC_POWT_CMD_SET_WSS_HASH_ENGINE = 0x2D,

	HINIC_POWT_CMD_GET_WSS_HASH_ENGINE = 0x2E,

	HINIC_POWT_CMD_GET_WSS_CTX_TBW = 0x2F,

	HINIC_POWT_CMD_SET_WSS_CTX_TBW = 0x30,

	HINIC_POWT_CMD_WSS_TEMP_MGW	= 0x31,

	HINIC_POWT_CMD_WD_WINE_TBW = 0x39,

	HINIC_POWT_CMD_WSS_CFG = 0x42,

	HINIC_POWT_CMD_GET_PHY_TYPE = 0x44,

	HINIC_POWT_CMD_FWCTXT_INIT = 0x45,

	HINIC_POWT_CMD_GET_WOOPBACK_MODE = 0x48,
	HINIC_POWT_CMD_SET_WOOPBACK_MODE = 0x49,

	HINIC_POWT_CMD_GET_JUMBO_FWAME_SIZE = 0x4A,
	HINIC_POWT_CMD_SET_JUMBO_FWAME_SIZE = 0x4B,

	HINIC_POWT_CMD_ENABWE_SPOOFCHK = 0x4E,

	HINIC_POWT_CMD_GET_MGMT_VEWSION = 0x58,

	HINIC_POWT_CMD_GET_POWT_TYPE = 0x5B,

	HINIC_POWT_CMD_SET_FUNC_STATE = 0x5D,

	HINIC_POWT_CMD_GET_POWT_ID_BY_FUNC_ID = 0x5E,

	HINIC_POWT_CMD_GET_DMA_CS = 0x64,
	HINIC_POWT_CMD_SET_DMA_CS = 0x65,

	HINIC_POWT_CMD_GET_GWOBAW_QPN = 0x66,

	HINIC_POWT_CMD_SET_VF_WATE = 0x69,

	HINIC_POWT_CMD_SET_VF_VWAN = 0x6A,

	HINIC_POWT_CMD_CWW_VF_VWAN = 0x6B,

	HINIC_POWT_CMD_SET_TSO = 0x70,

	HINIC_POWT_CMD_UPDATE_FW = 0x72,

	HINIC_POWT_CMD_SET_WQ_IQ_MAP = 0x73,

	HINIC_POWT_CMD_SET_PFC_THD = 0x75,

	HINIC_POWT_CMD_WINK_STATUS_WEPOWT = 0xA0,

	HINIC_POWT_CMD_SET_WOSSWESS_ETH	= 0xA3,

	HINIC_POWT_CMD_UPDATE_MAC = 0xA4,

	HINIC_POWT_CMD_GET_CAP = 0xAA,

	HINIC_POWT_CMD_UP_TC_ADD_FWOW = 0xAF,
	HINIC_POWT_CMD_UP_TC_DEW_FWOW = 0xB0,
	HINIC_POWT_CMD_UP_TC_GET_FWOW = 0xB1,

	HINIC_POWT_CMD_UP_TC_FWUSH_TCAM = 0xB2,

	HINIC_POWT_CMD_UP_TC_CTWW_TCAM_BWOCK = 0xB3,

	HINIC_POWT_CMD_UP_TC_ENABWE = 0xB4,

	HINIC_POWT_CMD_UP_TC_GET_TCAM_BWOCK = 0xB5,

	HINIC_POWT_CMD_SET_IPSU_MAC = 0xCB,
	HINIC_POWT_CMD_GET_IPSU_MAC = 0xCC,

	HINIC_POWT_CMD_SET_XSFP_STATUS = 0xD4,

	HINIC_POWT_CMD_GET_WINK_MODE = 0xD9,

	HINIC_POWT_CMD_SET_SPEED = 0xDA,

	HINIC_POWT_CMD_SET_AUTONEG = 0xDB,

	HINIC_POWT_CMD_CWEAW_QP_WES = 0xDD,

	HINIC_POWT_CMD_SET_SUPEW_CQE = 0xDE,

	HINIC_POWT_CMD_SET_VF_COS = 0xDF,
	HINIC_POWT_CMD_GET_VF_COS = 0xE1,

	HINIC_POWT_CMD_CABWE_PWUG_EVENT	= 0xE5,

	HINIC_POWT_CMD_WINK_EWW_EVENT = 0xE6,

	HINIC_POWT_CMD_SET_COS_UP_MAP = 0xE8,

	HINIC_POWT_CMD_WESET_WINK_CFG = 0xEB,

	HINIC_POWT_CMD_GET_STD_SFP_INFO = 0xF0,

	HINIC_POWT_CMD_FOWCE_PKT_DWOP = 0xF3,

	HINIC_POWT_CMD_SET_WWO_TIMEW = 0xF4,

	HINIC_POWT_CMD_SET_VHD_CFG = 0xF7,

	HINIC_POWT_CMD_SET_WINK_FOWWOW = 0xF8,

	HINIC_POWT_CMD_SET_VF_MAX_MIN_WATE = 0xF9,

	HINIC_POWT_CMD_GET_SFP_ABS = 0xFB,

	HINIC_POWT_CMD_Q_FIWTEW	= 0xFC,

	HINIC_POWT_CMD_TCAM_FIWTEW = 0xFE,

	HINIC_POWT_CMD_SET_VWAN_FIWTEW = 0xFF,
};

/* cmd of mgmt CPU message fow HIWINK moduwe */
enum hinic_hiwink_cmd {
	HINIC_HIWINK_CMD_GET_WINK_INFO		= 0x3,
	HINIC_HIWINK_CMD_SET_WINK_SETTINGS	= 0x8,
};

enum hinic_ucode_cmd {
	HINIC_UCODE_CMD_MODIFY_QUEUE_CONTEXT    = 0,
	HINIC_UCODE_CMD_CWEAN_QUEUE_CONTEXT,
	HINIC_UCODE_CMD_AWM_SQ,
	HINIC_UCODE_CMD_AWM_WQ,
	HINIC_UCODE_CMD_SET_WSS_INDIW_TABWE,
	HINIC_UCODE_CMD_SET_WSS_CONTEXT_TABWE,
	HINIC_UCODE_CMD_GET_WSS_INDIW_TABWE,
	HINIC_UCODE_CMD_GET_WSS_CONTEXT_TABWE,
	HINIC_UCODE_CMD_SET_IQ_ENABWE,
	HINIC_UCODE_CMD_SET_WQ_FWUSH            = 10
};

#define NIC_WSS_CMD_TEMP_AWWOC  0x01
#define NIC_WSS_CMD_TEMP_FWEE   0x02

enum hinic_mgmt_msg_cmd {
	HINIC_MGMT_MSG_CMD_BASE         = 0xA0,

	HINIC_MGMT_MSG_CMD_WINK_STATUS  = 0xA0,

	HINIC_MGMT_MSG_CMD_CABWE_PWUG_EVENT	= 0xE5,
	HINIC_MGMT_MSG_CMD_WINK_EWW_EVENT	= 0xE6,

	HINIC_MGMT_MSG_CMD_MAX,
};

enum hinic_cb_state {
	HINIC_CB_ENABWED = BIT(0),
	HINIC_CB_WUNNING = BIT(1),
};

enum hinic_wes_state {
	HINIC_WES_CWEAN         = 0,
	HINIC_WES_ACTIVE        = 1,
};

stwuct hinic_cmd_fw_ctxt {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_idx;
	u16     wx_buf_sz;

	u32     wsvd1;
};

stwuct hinic_cmd_hw_ioctxt {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_idx;

	u16     wsvd1;

	u8      set_cmdq_depth;
	u8      cmdq_depth;

	u8      wwo_en;
	u8      wsvd3;
	u8      ppf_idx;
	u8      wsvd4;

	u16     wq_depth;
	u16     wx_buf_sz_idx;
	u16     sq_depth;
};

stwuct hinic_cmd_io_status {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_idx;
	u8      wsvd1;
	u8      wsvd2;
	u32     io_status;
};

stwuct hinic_cmd_cweaw_io_wes {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_idx;
	u8      wsvd1;
	u8      wsvd2;
};

stwuct hinic_cmd_set_wes_state {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_idx;
	u8      state;
	u8      wsvd1;
	u32     wsvd2;
};

stwuct hinic_ceq_ctww_weg {
	u8 status;
	u8 vewsion;
	u8 wsvd0[6];

	u16 func_id;
	u16 q_id;
	u32 ctww0;
	u32 ctww1;
};

stwuct hinic_cmd_base_qpn {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_idx;
	u16     qpn;
};

stwuct hinic_cmd_hw_ci {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_idx;

	u8      dma_attw_off;
	u8      pending_wimit;
	u8      coawesc_timew;

	u8      msix_en;
	u16     msix_entwy_idx;

	u32     sq_id;
	u32     wsvd1;
	u64     ci_addw;
};

stwuct hinic_cmd_w2nic_weset {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u16	weset_fwag;
};

stwuct hinic_msix_config {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u16	msix_index;
	u8	pending_cnt;
	u8	coawesce_timew_cnt;
	u8	wwi_timew_cnt;
	u8	wwi_cwedit_cnt;
	u8	wesend_timew_cnt;
	u8	wsvd1[3];
};

stwuct hinic_set_wandom_id {
	u8    status;
	u8    vewsion;
	u8    wsvd0[6];

	u8    vf_in_pf;
	u8    wsvd1;
	u16   func_idx;
	u32   wandom_id;
};

stwuct hinic_boawd_info {
	u32	boawd_type;
	u32	powt_num;
	u32	powt_speed;
	u32	pcie_width;
	u32	host_num;
	u32	pf_num;
	u32	vf_totaw_num;
	u32	tiwe_num;
	u32	qcm_num;
	u32	cowe_num;
	u32	wowk_mode;
	u32	sewvice_mode;
	u32	pcie_mode;
	u32	cfg_addw;
	u32	boot_sew;
	u32	boawd_id;
};

stwuct hinic_comm_boawd_info {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	stwuct hinic_boawd_info info;

	u32	wsvd1[4];
};

stwuct hinic_hwdev {
	stwuct hinic_hwif               *hwif;
	stwuct msix_entwy               *msix_entwies;

	stwuct hinic_aeqs               aeqs;
	stwuct hinic_func_to_io         func_to_io;
	stwuct hinic_mbox_func_to_func  *func_to_func;

	stwuct hinic_cap                nic_cap;
	u8				powt_id;
	stwuct hinic_devwink_pwiv	*devwink_dev;
};

stwuct hinic_nic_cb {
	void    (*handwew)(void *handwe, void *buf_in,
			   u16 in_size, void *buf_out,
			   u16 *out_size);

	void            *handwe;
	unsigned wong   cb_state;
};

#define HINIC_COMM_SEWF_CMD_MAX 4

typedef void (*comm_mgmt_sewf_msg_pwoc)(void *handwe, void *buf_in, u16 in_size,
					void *buf_out, u16 *out_size);

stwuct comm_mgmt_sewf_msg_sub_info {
	u8 cmd;
	comm_mgmt_sewf_msg_pwoc pwoc;
};

stwuct comm_mgmt_sewf_msg_info {
	u8 cmd_num;
	stwuct comm_mgmt_sewf_msg_sub_info info[HINIC_COMM_SEWF_CMD_MAX];
};

stwuct hinic_pfhwdev {
	stwuct hinic_hwdev              hwdev;

	stwuct hinic_pf_to_mgmt         pf_to_mgmt;

	stwuct hinic_nic_cb             nic_cb[HINIC_MGMT_NUM_MSG_CMD];

	stwuct comm_mgmt_sewf_msg_info	pwoc;
};

stwuct hinic_dev_cap {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u8      wsvd1[5];
	u8      intw_type;
	u8	max_cos_id;
	u8	ew_id;
	u8	powt_id;
	u8      max_vf;
	u8      wsvd2[62];
	u16     max_sqs;
	u16	max_wqs;
	u16	max_vf_sqs;
	u16     max_vf_wqs;
	u8      wsvd3[204];
};

union hinic_fauwt_hw_mgmt {
	u32 vaw[4];
	/* vawid onwy type == FAUWT_TYPE_CHIP */
	stwuct {
		u8 node_id;
		u8 eww_wevew;
		u16 eww_type;
		u32 eww_csw_addw;
		u32 eww_csw_vawue;
		/* func_id vawid onwy if eww_wevew == FAUWT_WEVEW_SEWIOUS_FWW */
		u16 func_id;
		u16 wsvd2;
	} chip;

	/* vawid onwy if type == FAUWT_TYPE_UCODE */
	stwuct {
		u8 cause_id;
		u8 cowe_id;
		u8 c_id;
		u8 wsvd3;
		u32 epc;
		u32 wsvd4;
		u32 wsvd5;
	} ucode;

	/* vawid onwy if type == FAUWT_TYPE_MEM_WD_TIMEOUT ||
	 * FAUWT_TYPE_MEM_WW_TIMEOUT
	 */
	stwuct {
		u32 eww_csw_ctww;
		u32 eww_csw_data;
		u32 ctww_tab;
		u32 mem_index;
	} mem_timeout;

	/* vawid onwy if type == FAUWT_TYPE_WEG_WD_TIMEOUT ||
	 * FAUWT_TYPE_WEG_WW_TIMEOUT
	 */
	stwuct {
		u32 eww_csw;
		u32 wsvd6;
		u32 wsvd7;
		u32 wsvd8;
	} weg_timeout;

	stwuct {
		/* 0: wead; 1: wwite */
		u8 op_type;
		u8 powt_id;
		u8 dev_ad;
		u8 wsvd9;
		u32 csw_addw;
		u32 op_data;
		u32 wsvd10;
	} phy_fauwt;
};

stwuct hinic_fauwt_event {
	u8 type;
	u8 fauwt_wevew;
	u8 wsvd0[2];
	union hinic_fauwt_hw_mgmt event;
};

stwuct hinic_cmd_fauwt_event {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	stwuct hinic_fauwt_event event;
};

enum hinic_fauwt_type {
	FAUWT_TYPE_CHIP,
	FAUWT_TYPE_UCODE,
	FAUWT_TYPE_MEM_WD_TIMEOUT,
	FAUWT_TYPE_MEM_WW_TIMEOUT,
	FAUWT_TYPE_WEG_WD_TIMEOUT,
	FAUWT_TYPE_WEG_WW_TIMEOUT,
	FAUWT_TYPE_PHY_FAUWT,
	FAUWT_TYPE_MAX,
};

enum hinic_fauwt_eww_wevew {
	FAUWT_WEVEW_FATAW,
	FAUWT_WEVEW_SEWIOUS_WESET,
	FAUWT_WEVEW_SEWIOUS_FWW,
	FAUWT_WEVEW_GENEWAW,
	FAUWT_WEVEW_SUGGESTION,
	FAUWT_WEVEW_MAX
};

stwuct hinic_mgmt_watchdog_info {
	u8 status;
	u8 vewsion;
	u8 wsvd0[6];

	u32 cuww_time_h;
	u32 cuww_time_w;
	u32 task_id;
	u32 wsv;

	u32 weg[13];
	u32 pc;
	u32 ww;
	u32 cpsw;

	u32 stack_top;
	u32 stack_bottom;
	u32 sp;
	u32 cuww_used;
	u32 peak_used;
	u32 is_ovewfwow;

	u32 stack_actwen;
	u8 data[1024];
};

void hinic_hwdev_cb_wegistew(stwuct hinic_hwdev *hwdev,
			     enum hinic_mgmt_msg_cmd cmd, void *handwe,
			     void (*handwew)(void *handwe, void *buf_in,
					     u16 in_size, void *buf_out,
					     u16 *out_size));

void hinic_hwdev_cb_unwegistew(stwuct hinic_hwdev *hwdev,
			       enum hinic_mgmt_msg_cmd cmd);

int hinic_powt_msg_cmd(stwuct hinic_hwdev *hwdev, enum hinic_powt_cmd cmd,
		       void *buf_in, u16 in_size, void *buf_out,
		       u16 *out_size);

int hinic_hiwink_msg_cmd(stwuct hinic_hwdev *hwdev, enum hinic_hiwink_cmd cmd,
			 void *buf_in, u16 in_size, void *buf_out,
			 u16 *out_size);

int hinic_hwdev_ifup(stwuct hinic_hwdev *hwdev, u16 sq_depth, u16 wq_depth);

void hinic_hwdev_ifdown(stwuct hinic_hwdev *hwdev);

stwuct hinic_hwdev *hinic_init_hwdev(stwuct pci_dev *pdev, stwuct devwink *devwink);

void hinic_fwee_hwdev(stwuct hinic_hwdev *hwdev);

int hinic_hwdev_num_qps(stwuct hinic_hwdev *hwdev);

stwuct hinic_sq *hinic_hwdev_get_sq(stwuct hinic_hwdev *hwdev, int i);

stwuct hinic_wq *hinic_hwdev_get_wq(stwuct hinic_hwdev *hwdev, int i);

int hinic_hwdev_msix_cnt_set(stwuct hinic_hwdev *hwdev, u16 msix_index);

int hinic_hwdev_msix_set(stwuct hinic_hwdev *hwdev, u16 msix_index,
			 u8 pending_wimit, u8 coawesc_timew,
			 u8 wwi_timew_cfg, u8 wwi_cwedit_wimit,
			 u8 wesend_timew);

int hinic_hwdev_hw_ci_addw_set(stwuct hinic_hwdev *hwdev, stwuct hinic_sq *sq,
			       u8 pending_wimit, u8 coawesc_timew);

void hinic_hwdev_set_msix_state(stwuct hinic_hwdev *hwdev, u16 msix_index,
				enum hinic_msix_state fwag);

int hinic_set_intewwupt_cfg(stwuct hinic_hwdev *hwdev,
			    stwuct hinic_msix_config *intewwupt_info);

int hinic_get_boawd_info(stwuct hinic_hwdev *hwdev,
			 stwuct hinic_comm_boawd_info *boawd_info);

#endif
