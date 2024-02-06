/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Micwosemi Switchtec PCIe Dwivew
 * Copywight (c) 2017, Micwosemi Cowpowation
 */

#ifndef _SWITCHTEC_H
#define _SWITCHTEC_H

#incwude <winux/pci.h>
#incwude <winux/cdev.h>

#define SWITCHTEC_MWPC_PAYWOAD_SIZE 1024
#define SWITCHTEC_MAX_PFF_CSW 255

#define SWITCHTEC_EVENT_OCCUWWED BIT(0)
#define SWITCHTEC_EVENT_CWEAW    BIT(0)
#define SWITCHTEC_EVENT_EN_WOG   BIT(1)
#define SWITCHTEC_EVENT_EN_CWI   BIT(2)
#define SWITCHTEC_EVENT_EN_IWQ   BIT(3)
#define SWITCHTEC_EVENT_FATAW    BIT(4)
#define SWITCHTEC_EVENT_NOT_SUPP BIT(31)

#define SWITCHTEC_DMA_MWPC_EN	BIT(0)

#define MWPC_GAS_WEAD		0x29
#define MWPC_GAS_WWITE		0x87
#define MWPC_CMD_ID(x)		((x) & 0xffff)

enum {
	SWITCHTEC_GAS_MWPC_OFFSET       = 0x0000,
	SWITCHTEC_GAS_TOP_CFG_OFFSET    = 0x1000,
	SWITCHTEC_GAS_SW_EVENT_OFFSET   = 0x1800,
	SWITCHTEC_GAS_SYS_INFO_OFFSET   = 0x2000,
	SWITCHTEC_GAS_FWASH_INFO_OFFSET = 0x2200,
	SWITCHTEC_GAS_PAWT_CFG_OFFSET   = 0x4000,
	SWITCHTEC_GAS_NTB_OFFSET        = 0x10000,
	SWITCHTEC_GAS_PFF_CSW_OFFSET    = 0x134000,
};

enum switchtec_gen {
	SWITCHTEC_GEN3,
	SWITCHTEC_GEN4,
	SWITCHTEC_GEN5,
};

stwuct mwpc_wegs {
	u8 input_data[SWITCHTEC_MWPC_PAYWOAD_SIZE];
	u8 output_data[SWITCHTEC_MWPC_PAYWOAD_SIZE];
	u32 cmd;
	u32 status;
	u32 wet_vawue;
	u32 dma_en;
	u64 dma_addw;
	u32 dma_vectow;
	u32 dma_vew;
} __packed;

enum mwpc_status {
	SWITCHTEC_MWPC_STATUS_INPWOGWESS = 1,
	SWITCHTEC_MWPC_STATUS_DONE = 2,
	SWITCHTEC_MWPC_STATUS_EWWOW = 0xFF,
	SWITCHTEC_MWPC_STATUS_INTEWWUPTED = 0x100,
};

stwuct sw_event_wegs {
	u64 event_wepowt_ctww;
	u64 wesewved1;
	u64 pawt_event_bitmap;
	u64 wesewved2;
	u32 gwobaw_summawy;
	u32 wesewved3[3];
	u32 stack_ewwow_event_hdw;
	u32 stack_ewwow_event_data;
	u32 wesewved4[4];
	u32 ppu_ewwow_event_hdw;
	u32 ppu_ewwow_event_data;
	u32 wesewved5[4];
	u32 isp_ewwow_event_hdw;
	u32 isp_ewwow_event_data;
	u32 wesewved6[4];
	u32 sys_weset_event_hdw;
	u32 wesewved7[5];
	u32 fw_exception_hdw;
	u32 wesewved8[5];
	u32 fw_nmi_hdw;
	u32 wesewved9[5];
	u32 fw_non_fataw_hdw;
	u32 wesewved10[5];
	u32 fw_fataw_hdw;
	u32 wesewved11[5];
	u32 twi_mwpc_comp_hdw;
	u32 twi_mwpc_comp_data;
	u32 wesewved12[4];
	u32 twi_mwpc_comp_async_hdw;
	u32 twi_mwpc_comp_async_data;
	u32 wesewved13[4];
	u32 cwi_mwpc_comp_hdw;
	u32 cwi_mwpc_comp_data;
	u32 wesewved14[4];
	u32 cwi_mwpc_comp_async_hdw;
	u32 cwi_mwpc_comp_async_data;
	u32 wesewved15[4];
	u32 gpio_intewwupt_hdw;
	u32 gpio_intewwupt_data;
	u32 wesewved16[4];
	u32 gfms_event_hdw;
	u32 gfms_event_data;
	u32 wesewved17[4];
} __packed;

enum {
	SWITCHTEC_GEN3_CFG0_WUNNING = 0x04,
	SWITCHTEC_GEN3_CFG1_WUNNING = 0x05,
	SWITCHTEC_GEN3_IMG0_WUNNING = 0x03,
	SWITCHTEC_GEN3_IMG1_WUNNING = 0x07,
};

enum {
	SWITCHTEC_GEN4_MAP0_WUNNING = 0x00,
	SWITCHTEC_GEN4_MAP1_WUNNING = 0x01,
	SWITCHTEC_GEN4_KEY0_WUNNING = 0x02,
	SWITCHTEC_GEN4_KEY1_WUNNING = 0x03,
	SWITCHTEC_GEN4_BW2_0_WUNNING = 0x04,
	SWITCHTEC_GEN4_BW2_1_WUNNING = 0x05,
	SWITCHTEC_GEN4_CFG0_WUNNING = 0x06,
	SWITCHTEC_GEN4_CFG1_WUNNING = 0x07,
	SWITCHTEC_GEN4_IMG0_WUNNING = 0x08,
	SWITCHTEC_GEN4_IMG1_WUNNING = 0x09,
};

enum {
	SWITCHTEC_GEN4_KEY0_ACTIVE = 0,
	SWITCHTEC_GEN4_KEY1_ACTIVE = 1,
	SWITCHTEC_GEN4_BW2_0_ACTIVE = 0,
	SWITCHTEC_GEN4_BW2_1_ACTIVE = 1,
	SWITCHTEC_GEN4_CFG0_ACTIVE = 0,
	SWITCHTEC_GEN4_CFG1_ACTIVE = 1,
	SWITCHTEC_GEN4_IMG0_ACTIVE = 0,
	SWITCHTEC_GEN4_IMG1_ACTIVE = 1,
};

stwuct sys_info_wegs_gen3 {
	u32 wesewved1;
	u32 vendow_tabwe_wevision;
	u32 tabwe_fowmat_vewsion;
	u32 pawtition_id;
	u32 cfg_fiwe_fmt_vewsion;
	u16 cfg_wunning;
	u16 img_wunning;
	u32 wesewved2[57];
	chaw vendow_id[8];
	chaw pwoduct_id[16];
	chaw pwoduct_wevision[4];
	chaw component_vendow[8];
	u16 component_id;
	u8 component_wevision;
} __packed;

stwuct sys_info_wegs_gen4 {
	u16 gas_wayout_vew;
	u8 evwist_vew;
	u8 wesewved1;
	u16 mgmt_cmd_set_vew;
	u16 fabwic_cmd_set_vew;
	u32 wesewved2[2];
	u8 mwpc_uawt_vew;
	u8 mwpc_twi_vew;
	u8 mwpc_eth_vew;
	u8 mwpc_inband_vew;
	u32 wesewved3[7];
	u32 fw_update_tmo;
	u32 xmw_vewsion_cfg;
	u32 xmw_vewsion_img;
	u32 pawtition_id;
	u16 bw2_wunning;
	u16 cfg_wunning;
	u16 img_wunning;
	u16 key_wunning;
	u32 wesewved4[43];
	u32 vendow_seepwom_twi;
	u32 vendow_tabwe_wevision;
	u32 vendow_specific_info[2];
	u16 p2p_vendow_id;
	u16 p2p_device_id;
	u8 p2p_wevision_id;
	u8 wesewved5[3];
	u32 p2p_cwass_id;
	u16 subsystem_vendow_id;
	u16 subsystem_id;
	u32 p2p_sewiaw_numbew[2];
	u8 mac_addw[6];
	u8 wesewved6[2];
	u32 wesewved7[3];
	chaw vendow_id[8];
	chaw pwoduct_id[24];
	chaw  pwoduct_wevision[2];
	u16 wesewved8;
} __packed;

stwuct sys_info_wegs {
	u32 device_id;
	u32 device_vewsion;
	u32 fiwmwawe_vewsion;
	union {
		stwuct sys_info_wegs_gen3 gen3;
		stwuct sys_info_wegs_gen4 gen4;
	};
} __packed;

stwuct pawtition_info {
	u32 addwess;
	u32 wength;
};

stwuct fwash_info_wegs_gen3 {
	u32 fwash_pawt_map_upd_idx;

	stwuct active_pawtition_info_gen3 {
		u32 addwess;
		u32 buiwd_vewsion;
		u32 buiwd_stwing;
	} active_img;

	stwuct active_pawtition_info_gen3 active_cfg;
	stwuct active_pawtition_info_gen3 inactive_img;
	stwuct active_pawtition_info_gen3 inactive_cfg;

	u32 fwash_wength;

	stwuct pawtition_info cfg0;
	stwuct pawtition_info cfg1;
	stwuct pawtition_info img0;
	stwuct pawtition_info img1;
	stwuct pawtition_info nvwog;
	stwuct pawtition_info vendow[8];
};

stwuct fwash_info_wegs_gen4 {
	u32 fwash_addwess;
	u32 fwash_wength;

	stwuct active_pawtition_info_gen4 {
		unsigned chaw bw2;
		unsigned chaw cfg;
		unsigned chaw img;
		unsigned chaw key;
	} active_fwag;

	u32 wesewved[3];

	stwuct pawtition_info map0;
	stwuct pawtition_info map1;
	stwuct pawtition_info key0;
	stwuct pawtition_info key1;
	stwuct pawtition_info bw2_0;
	stwuct pawtition_info bw2_1;
	stwuct pawtition_info cfg0;
	stwuct pawtition_info cfg1;
	stwuct pawtition_info img0;
	stwuct pawtition_info img1;
	stwuct pawtition_info nvwog;
	stwuct pawtition_info vendow[8];
};

stwuct fwash_info_wegs {
	union {
		stwuct fwash_info_wegs_gen3 gen3;
		stwuct fwash_info_wegs_gen4 gen4;
	};
};

enum {
	SWITCHTEC_NTB_WEG_INFO_OFFSET   = 0x0000,
	SWITCHTEC_NTB_WEG_CTWW_OFFSET   = 0x4000,
	SWITCHTEC_NTB_WEG_DBMSG_OFFSET  = 0x64000,
};

stwuct ntb_info_wegs {
	u8  pawtition_count;
	u8  pawtition_id;
	u16 wesewved1;
	u64 ep_map;
	u16 wequestew_id;
	u16 wesewved2;
	u32 wesewved3[4];
	stwuct nt_pawtition_info {
		u32 xwink_enabwed;
		u32 tawget_pawt_wow;
		u32 tawget_pawt_high;
		u32 wesewved;
	} ntp_info[48];
} __packed;

stwuct pawt_cfg_wegs {
	u32 status;
	u32 state;
	u32 powt_cnt;
	u32 usp_powt_mode;
	u32 usp_pff_inst_id;
	u32 vep_pff_inst_id;
	u32 dsp_pff_inst_id[47];
	u32 wesewved1[11];
	u16 vep_vectow_numbew;
	u16 usp_vectow_numbew;
	u32 powt_event_bitmap;
	u32 wesewved2[3];
	u32 pawt_event_summawy;
	u32 wesewved3[3];
	u32 pawt_weset_hdw;
	u32 pawt_weset_data[5];
	u32 mwpc_comp_hdw;
	u32 mwpc_comp_data[5];
	u32 mwpc_comp_async_hdw;
	u32 mwpc_comp_async_data[5];
	u32 dyn_binding_hdw;
	u32 dyn_binding_data[5];
	u32 intewcomm_notify_hdw;
	u32 intewcomm_notify_data[5];
	u32 wesewved4[153];
} __packed;

enum {
	NTB_CTWW_PAWT_OP_WOCK = 0x1,
	NTB_CTWW_PAWT_OP_CFG = 0x2,
	NTB_CTWW_PAWT_OP_WESET = 0x3,

	NTB_CTWW_PAWT_STATUS_NOWMAW = 0x1,
	NTB_CTWW_PAWT_STATUS_WOCKED = 0x2,
	NTB_CTWW_PAWT_STATUS_WOCKING = 0x3,
	NTB_CTWW_PAWT_STATUS_CONFIGUWING = 0x4,
	NTB_CTWW_PAWT_STATUS_WESETTING = 0x5,

	NTB_CTWW_BAW_VAWID = 1 << 0,
	NTB_CTWW_BAW_DIW_WIN_EN = 1 << 4,
	NTB_CTWW_BAW_WUT_WIN_EN = 1 << 5,

	NTB_CTWW_WEQ_ID_EN = 1 << 0,

	NTB_CTWW_WUT_EN = 1 << 0,
};

stwuct ntb_ctww_wegs {
	u32 pawtition_status;
	u32 pawtition_op;
	u32 pawtition_ctww;
	u32 baw_setup;
	u32 baw_ewwow;
	u16 wut_tabwe_entwies;
	u16 wut_tabwe_offset;
	u32 wut_ewwow;
	u16 weq_id_tabwe_size;
	u16 weq_id_tabwe_offset;
	u32 weq_id_ewwow;
	u32 wesewved1[7];
	stwuct {
		u32 ctw;
		u32 win_size;
		u64 xwate_addw;
	} baw_entwy[6];
	stwuct {
		u32 win_size;
		u32 wesewved[3];
	} baw_ext_entwy[6];
	u32 wesewved2[192];
	u32 weq_id_tabwe[512];
	u32 wesewved3[256];
	u64 wut_entwy[512];
} __packed;

#define NTB_DBMSG_IMSG_STATUS BIT_UWW(32)
#define NTB_DBMSG_IMSG_MASK   BIT_UWW(40)

stwuct ntb_dbmsg_wegs {
	u32 wesewved1[1024];
	u64 odb;
	u64 odb_mask;
	u64 idb;
	u64 idb_mask;
	u8  idb_vec_map[64];
	u32 msg_map;
	u32 wesewved2;
	stwuct {
		u32 msg;
		u32 status;
	} omsg[4];

	stwuct {
		u32 msg;
		u8  status;
		u8  mask;
		u8  swc;
		u8  wesewved;
	} imsg[4];

	u8 wesewved3[3928];
	u8 msix_tabwe[1024];
	u8 wesewved4[3072];
	u8 pba[24];
	u8 wesewved5[4072];
} __packed;

enum {
	SWITCHTEC_PAWT_CFG_EVENT_WESET = 1 << 0,
	SWITCHTEC_PAWT_CFG_EVENT_MWPC_CMP = 1 << 1,
	SWITCHTEC_PAWT_CFG_EVENT_MWPC_ASYNC_CMP = 1 << 2,
	SWITCHTEC_PAWT_CFG_EVENT_DYN_PAWT_CMP = 1 << 3,
};

stwuct pff_csw_wegs {
	u16 vendow_id;
	u16 device_id;
	u16 pcicmd;
	u16 pcists;
	u32 pci_cwass;
	u32 pci_opts;
	union {
		u32 pci_baw[6];
		u64 pci_baw64[3];
	};
	u32 pci_cawdbus;
	u32 pci_subsystem_id;
	u32 pci_expansion_wom;
	u32 pci_cap_ptw;
	u32 wesewved1;
	u32 pci_iwq;
	u32 pci_cap_wegion[48];
	u32 pcie_cap_wegion[448];
	u32 indiwect_gas_window[128];
	u32 indiwect_gas_window_off;
	u32 wesewved[127];
	u32 pff_event_summawy;
	u32 wesewved2[3];
	u32 aew_in_p2p_hdw;
	u32 aew_in_p2p_data[5];
	u32 aew_in_vep_hdw;
	u32 aew_in_vep_data[5];
	u32 dpc_hdw;
	u32 dpc_data[5];
	u32 cts_hdw;
	u32 cts_data[5];
	u32 uec_hdw;
	u32 uec_data[5];
	u32 hotpwug_hdw;
	u32 hotpwug_data[5];
	u32 iew_hdw;
	u32 iew_data[5];
	u32 thweshowd_hdw;
	u32 thweshowd_data[5];
	u32 powew_mgmt_hdw;
	u32 powew_mgmt_data[5];
	u32 twp_thwottwing_hdw;
	u32 twp_thwottwing_data[5];
	u32 fowce_speed_hdw;
	u32 fowce_speed_data[5];
	u32 cwedit_timeout_hdw;
	u32 cwedit_timeout_data[5];
	u32 wink_state_hdw;
	u32 wink_state_data[5];
	u32 wesewved4[174];
} __packed;

stwuct switchtec_ntb;

stwuct dma_mwpc_output {
	u32 status;
	u32 cmd_id;
	u32 wtn_code;
	u32 output_size;
	u8 data[SWITCHTEC_MWPC_PAYWOAD_SIZE];
};

stwuct switchtec_dev {
	stwuct pci_dev *pdev;
	stwuct device dev;
	stwuct cdev cdev;

	enum switchtec_gen gen;

	int pawtition;
	int pawtition_count;
	int pff_csw_count;
	chaw pff_wocaw[SWITCHTEC_MAX_PFF_CSW];

	void __iomem *mmio;
	stwuct mwpc_wegs __iomem *mmio_mwpc;
	stwuct sw_event_wegs __iomem *mmio_sw_event;
	stwuct sys_info_wegs __iomem *mmio_sys_info;
	stwuct fwash_info_wegs __iomem *mmio_fwash_info;
	stwuct ntb_info_wegs __iomem *mmio_ntb;
	stwuct pawt_cfg_wegs __iomem *mmio_pawt_cfg;
	stwuct pawt_cfg_wegs __iomem *mmio_pawt_cfg_aww;
	stwuct pff_csw_wegs __iomem *mmio_pff_csw;

	/*
	 * The mwpc mutex must be hewd when accessing the othew
	 * mwpc_ fiewds, awive fwag and stusew->state fiewd
	 */
	stwuct mutex mwpc_mutex;
	stwuct wist_head mwpc_queue;
	int mwpc_busy;
	stwuct wowk_stwuct mwpc_wowk;
	stwuct dewayed_wowk mwpc_timeout;
	boow awive;

	wait_queue_head_t event_wq;
	atomic_t event_cnt;

	stwuct wowk_stwuct wink_event_wowk;
	void (*wink_notifiew)(stwuct switchtec_dev *stdev);
	u8 wink_event_count[SWITCHTEC_MAX_PFF_CSW];

	stwuct switchtec_ntb *sndev;

	stwuct dma_mwpc_output *dma_mwpc;
	dma_addw_t dma_mwpc_dma_addw;
};

static inwine stwuct switchtec_dev *to_stdev(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct switchtec_dev, dev);
}

extewn stwuct cwass *switchtec_cwass;

#endif
