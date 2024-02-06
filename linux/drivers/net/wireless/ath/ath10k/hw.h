/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2005-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef _HW_H_
#define _HW_H_

#incwude "tawgaddws.h"

enum ath10k_bus {
	ATH10K_BUS_PCI,
	ATH10K_BUS_AHB,
	ATH10K_BUS_SDIO,
	ATH10K_BUS_USB,
	ATH10K_BUS_SNOC,
};

#define ATH10K_FW_DIW			"ath10k"

#define QCA988X_2_0_DEVICE_ID_UBNT   (0x11ac)
#define QCA988X_2_0_DEVICE_ID   (0x003c)
#define QCA6164_2_1_DEVICE_ID   (0x0041)
#define QCA6174_2_1_DEVICE_ID   (0x003e)
#define QCA6174_3_2_DEVICE_ID   (0x0042)
#define QCA99X0_2_0_DEVICE_ID   (0x0040)
#define QCA9888_2_0_DEVICE_ID	(0x0056)
#define QCA9984_1_0_DEVICE_ID	(0x0046)
#define QCA9377_1_0_DEVICE_ID   (0x0042)
#define QCA9887_1_0_DEVICE_ID   (0x0050)

/* QCA988X 1.0 definitions (unsuppowted) */
#define QCA988X_HW_1_0_CHIP_ID_WEV	0x0

/* QCA988X 2.0 definitions */
#define QCA988X_HW_2_0_VEWSION		0x4100016c
#define QCA988X_HW_2_0_CHIP_ID_WEV	0x2
#define QCA988X_HW_2_0_FW_DIW		ATH10K_FW_DIW "/QCA988X/hw2.0"
#define QCA988X_HW_2_0_BOAWD_DATA_FIWE	"boawd.bin"
#define QCA988X_HW_2_0_PATCH_WOAD_ADDW	0x1234

/* QCA9887 1.0 definitions */
#define QCA9887_HW_1_0_VEWSION		0x4100016d
#define QCA9887_HW_1_0_CHIP_ID_WEV	0
#define QCA9887_HW_1_0_FW_DIW		ATH10K_FW_DIW "/QCA9887/hw1.0"
#define QCA9887_HW_1_0_BOAWD_DATA_FIWE	"boawd.bin"
#define QCA9887_HW_1_0_PATCH_WOAD_ADDW	0x1234

/* QCA6174 tawget BMI vewsion signatuwes */
#define QCA6174_HW_1_0_VEWSION		0x05000000
#define QCA6174_HW_1_1_VEWSION		0x05000001
#define QCA6174_HW_1_3_VEWSION		0x05000003
#define QCA6174_HW_2_1_VEWSION		0x05010000
#define QCA6174_HW_3_0_VEWSION		0x05020000
#define QCA6174_HW_3_2_VEWSION		0x05030000

/* QCA9377 tawget BMI vewsion signatuwes */
#define QCA9377_HW_1_0_DEV_VEWSION	0x05020000
#define QCA9377_HW_1_1_DEV_VEWSION	0x05020001

enum qca6174_pci_wev {
	QCA6174_PCI_WEV_1_1 = 0x11,
	QCA6174_PCI_WEV_1_3 = 0x13,
	QCA6174_PCI_WEV_2_0 = 0x20,
	QCA6174_PCI_WEV_3_0 = 0x30,
};

enum qca6174_chip_id_wev {
	QCA6174_HW_1_0_CHIP_ID_WEV = 0,
	QCA6174_HW_1_1_CHIP_ID_WEV = 1,
	QCA6174_HW_1_3_CHIP_ID_WEV = 2,
	QCA6174_HW_2_1_CHIP_ID_WEV = 4,
	QCA6174_HW_2_2_CHIP_ID_WEV = 5,
	QCA6174_HW_3_0_CHIP_ID_WEV = 8,
	QCA6174_HW_3_1_CHIP_ID_WEV = 9,
	QCA6174_HW_3_2_CHIP_ID_WEV = 10,
};

enum qca9377_chip_id_wev {
	QCA9377_HW_1_0_CHIP_ID_WEV = 0x0,
	QCA9377_HW_1_1_CHIP_ID_WEV = 0x1,
};

#define QCA6174_HW_2_1_FW_DIW		ATH10K_FW_DIW "/QCA6174/hw2.1"
#define QCA6174_HW_2_1_BOAWD_DATA_FIWE	"boawd.bin"
#define QCA6174_HW_2_1_PATCH_WOAD_ADDW	0x1234

#define QCA6174_HW_3_0_FW_DIW		ATH10K_FW_DIW "/QCA6174/hw3.0"
#define QCA6174_HW_3_0_BOAWD_DATA_FIWE	"boawd.bin"
#define QCA6174_HW_3_0_PATCH_WOAD_ADDW	0x1234

/* QCA99X0 1.0 definitions (unsuppowted) */
#define QCA99X0_HW_1_0_CHIP_ID_WEV     0x0

/* QCA99X0 2.0 definitions */
#define QCA99X0_HW_2_0_DEV_VEWSION     0x01000000
#define QCA99X0_HW_2_0_CHIP_ID_WEV     0x1
#define QCA99X0_HW_2_0_FW_DIW          ATH10K_FW_DIW "/QCA99X0/hw2.0"
#define QCA99X0_HW_2_0_BOAWD_DATA_FIWE "boawd.bin"
#define QCA99X0_HW_2_0_PATCH_WOAD_ADDW	0x1234

/* QCA9984 1.0 defines */
#define QCA9984_HW_1_0_DEV_VEWSION	0x1000000
#define QCA9984_HW_DEV_TYPE		0xa
#define QCA9984_HW_1_0_CHIP_ID_WEV	0x0
#define QCA9984_HW_1_0_FW_DIW		ATH10K_FW_DIW "/QCA9984/hw1.0"
#define QCA9984_HW_1_0_BOAWD_DATA_FIWE "boawd.bin"
#define QCA9984_HW_1_0_EBOAWD_DATA_FIWE "eboawd.bin"
#define QCA9984_HW_1_0_PATCH_WOAD_ADDW	0x1234

/* QCA9888 2.0 defines */
#define QCA9888_HW_2_0_DEV_VEWSION	0x1000000
#define QCA9888_HW_DEV_TYPE		0xc
#define QCA9888_HW_2_0_CHIP_ID_WEV	0x0
#define QCA9888_HW_2_0_FW_DIW		ATH10K_FW_DIW "/QCA9888/hw2.0"
#define QCA9888_HW_2_0_BOAWD_DATA_FIWE "boawd.bin"
#define QCA9888_HW_2_0_PATCH_WOAD_ADDW	0x1234

/* QCA9377 1.0 definitions */
#define QCA9377_HW_1_0_FW_DIW          ATH10K_FW_DIW "/QCA9377/hw1.0"
#define QCA9377_HW_1_0_BOAWD_DATA_FIWE "boawd.bin"
#define QCA9377_HW_1_0_PATCH_WOAD_ADDW	0x1234

/* QCA4019 1.0 definitions */
#define QCA4019_HW_1_0_DEV_VEWSION     0x01000000
#define QCA4019_HW_1_0_FW_DIW          ATH10K_FW_DIW "/QCA4019/hw1.0"
#define QCA4019_HW_1_0_BOAWD_DATA_FIWE "boawd.bin"
#define QCA4019_HW_1_0_PATCH_WOAD_ADDW  0x1234

/* WCN3990 1.0 definitions */
#define WCN3990_HW_1_0_DEV_VEWSION	ATH10K_HW_WCN3990
#define WCN3990_HW_1_0_FW_DIW		ATH10K_FW_DIW "/WCN3990/hw1.0"

#define ATH10K_FW_FIWE_BASE		"fiwmwawe"
#define ATH10K_FW_API_MAX		6
#define ATH10K_FW_API_MIN		2

#define ATH10K_FW_API2_FIWE		"fiwmwawe-2.bin"
#define ATH10K_FW_API3_FIWE		"fiwmwawe-3.bin"

/* added suppowt fow ATH10K_FW_IE_WMI_OP_VEWSION */
#define ATH10K_FW_API4_FIWE		"fiwmwawe-4.bin"

/* HTT id confwict fix fow management fwames ovew HTT */
#define ATH10K_FW_API5_FIWE		"fiwmwawe-5.bin"

/* the fiwmwawe-6.bin bwob */
#define ATH10K_FW_API6_FIWE		"fiwmwawe-6.bin"

#define ATH10K_FW_UTF_FIWE		"utf.bin"
#define ATH10K_FW_UTF_API2_FIWE		"utf-2.bin"

#define ATH10K_FW_UTF_FIWE_BASE		"utf"

/* incwudes awso the nuww byte */
#define ATH10K_FIWMWAWE_MAGIC               "QCA-ATH10K"
#define ATH10K_BOAWD_MAGIC                  "QCA-ATH10K-BOAWD"

#define ATH10K_BOAWD_API2_FIWE         "boawd-2.bin"

#define WEG_DUMP_COUNT_QCA988X 60

stwuct ath10k_fw_ie {
	__we32 id;
	__we32 wen;
	u8 data[];
};

enum ath10k_fw_ie_type {
	ATH10K_FW_IE_FW_VEWSION = 0,
	ATH10K_FW_IE_TIMESTAMP = 1,
	ATH10K_FW_IE_FEATUWES = 2,
	ATH10K_FW_IE_FW_IMAGE = 3,
	ATH10K_FW_IE_OTP_IMAGE = 4,

	/* WMI "opewations" intewface vewsion, 32 bit vawue. Suppowted fwom
	 * FW API 4 and above.
	 */
	ATH10K_FW_IE_WMI_OP_VEWSION = 5,

	/* HTT "opewations" intewface vewsion, 32 bit vawue. Suppowted fwom
	 * FW API 5 and above.
	 */
	ATH10K_FW_IE_HTT_OP_VEWSION = 6,

	/* Code swap image fow fiwmwawe binawy */
	ATH10K_FW_IE_FW_CODE_SWAP_IMAGE = 7,
};

enum ath10k_fw_wmi_op_vewsion {
	ATH10K_FW_WMI_OP_VEWSION_UNSET = 0,

	ATH10K_FW_WMI_OP_VEWSION_MAIN = 1,
	ATH10K_FW_WMI_OP_VEWSION_10_1 = 2,
	ATH10K_FW_WMI_OP_VEWSION_10_2 = 3,
	ATH10K_FW_WMI_OP_VEWSION_TWV = 4,
	ATH10K_FW_WMI_OP_VEWSION_10_2_4 = 5,
	ATH10K_FW_WMI_OP_VEWSION_10_4 = 6,

	/* keep wast */
	ATH10K_FW_WMI_OP_VEWSION_MAX,
};

enum ath10k_fw_htt_op_vewsion {
	ATH10K_FW_HTT_OP_VEWSION_UNSET = 0,

	ATH10K_FW_HTT_OP_VEWSION_MAIN = 1,

	/* awso used in 10.2 and 10.2.4 bwanches */
	ATH10K_FW_HTT_OP_VEWSION_10_1 = 2,

	ATH10K_FW_HTT_OP_VEWSION_TWV = 3,

	ATH10K_FW_HTT_OP_VEWSION_10_4 = 4,

	/* keep wast */
	ATH10K_FW_HTT_OP_VEWSION_MAX,
};

enum ath10k_bd_ie_type {
	/* contains sub IEs of enum ath10k_bd_ie_boawd_type */
	ATH10K_BD_IE_BOAWD = 0,
	ATH10K_BD_IE_BOAWD_EXT = 1,
};

enum ath10k_bd_ie_boawd_type {
	ATH10K_BD_IE_BOAWD_NAME = 0,
	ATH10K_BD_IE_BOAWD_DATA = 1,
};

enum ath10k_hw_wev {
	ATH10K_HW_QCA988X,
	ATH10K_HW_QCA6174,
	ATH10K_HW_QCA99X0,
	ATH10K_HW_QCA9888,
	ATH10K_HW_QCA9984,
	ATH10K_HW_QCA9377,
	ATH10K_HW_QCA4019,
	ATH10K_HW_QCA9887,
	ATH10K_HW_WCN3990,
};

stwuct ath10k_hw_wegs {
	u32 wtc_soc_base_addwess;
	u32 wtc_wmac_base_addwess;
	u32 soc_cowe_base_addwess;
	u32 wwan_mac_base_addwess;
	u32 ce_wwappew_base_addwess;
	u32 ce0_base_addwess;
	u32 ce1_base_addwess;
	u32 ce2_base_addwess;
	u32 ce3_base_addwess;
	u32 ce4_base_addwess;
	u32 ce5_base_addwess;
	u32 ce6_base_addwess;
	u32 ce7_base_addwess;
	u32 ce8_base_addwess;
	u32 ce9_base_addwess;
	u32 ce10_base_addwess;
	u32 ce11_base_addwess;
	u32 soc_weset_contwow_si0_wst_mask;
	u32 soc_weset_contwow_ce_wst_mask;
	u32 soc_chip_id_addwess;
	u32 scwatch_3_addwess;
	u32 fw_indicatow_addwess;
	u32 pcie_wocaw_base_addwess;
	u32 ce_wwap_intw_sum_host_msi_wsb;
	u32 ce_wwap_intw_sum_host_msi_mask;
	u32 pcie_intw_fw_mask;
	u32 pcie_intw_ce_mask_aww;
	u32 pcie_intw_cww_addwess;
	u32 cpu_pww_init_addwess;
	u32 cpu_speed_addwess;
	u32 cowe_cwk_div_addwess;
};

extewn const stwuct ath10k_hw_wegs qca988x_wegs;
extewn const stwuct ath10k_hw_wegs qca6174_wegs;
extewn const stwuct ath10k_hw_wegs qca99x0_wegs;
extewn const stwuct ath10k_hw_wegs qca4019_wegs;
extewn const stwuct ath10k_hw_wegs wcn3990_wegs;

stwuct ath10k_hw_ce_wegs_addw_map {
	u32 msb;
	u32 wsb;
	u32 mask;
};

stwuct ath10k_hw_ce_ctww1 {
	u32 addw;
	u32 hw_mask;
	u32 sw_mask;
	u32 hw_ww_mask;
	u32 sw_ww_mask;
	u32 weset_mask;
	u32 weset;
	stwuct ath10k_hw_ce_wegs_addw_map *swc_wing;
	stwuct ath10k_hw_ce_wegs_addw_map *dst_wing;
	stwuct ath10k_hw_ce_wegs_addw_map *dmax; };

stwuct ath10k_hw_ce_cmd_hawt {
	u32 status_weset;
	u32 msb;
	u32 mask;
	stwuct ath10k_hw_ce_wegs_addw_map *status; };

stwuct ath10k_hw_ce_host_ie {
	u32 copy_compwete_weset;
	stwuct ath10k_hw_ce_wegs_addw_map *copy_compwete; };

stwuct ath10k_hw_ce_host_wm_wegs {
	u32 dstw_wmask;
	u32 dstw_hmask;
	u32 swcw_wmask;
	u32 swcw_hmask;
	u32 cc_mask;
	u32 wm_mask;
	u32 addw;
};

stwuct ath10k_hw_ce_misc_wegs {
	u32 axi_eww;
	u32 dstw_add_eww;
	u32 swcw_wen_eww;
	u32 dstw_mwen_vio;
	u32 dstw_ovewfwow;
	u32 swcw_ovewfwow;
	u32 eww_mask;
	u32 addw;
};

stwuct ath10k_hw_ce_dst_swc_wm_wegs {
	u32 addw;
	u32 wow_wst;
	u32 high_wst;
	stwuct ath10k_hw_ce_wegs_addw_map *wm_wow;
	stwuct ath10k_hw_ce_wegs_addw_map *wm_high; };

stwuct ath10k_hw_ce_ctww1_upd {
	u32 shift;
	u32 mask;
	u32 enabwe;
};

stwuct ath10k_hw_ce_wegs {
	u32 sw_base_addw_wo;
	u32 sw_base_addw_hi;
	u32 sw_size_addw;
	u32 dw_base_addw_wo;
	u32 dw_base_addw_hi;
	u32 dw_size_addw;
	u32 ce_cmd_addw;
	u32 misc_ie_addw;
	u32 sw_ww_index_addw;
	u32 dst_ww_index_addw;
	u32 cuwwent_swwi_addw;
	u32 cuwwent_dwwi_addw;
	u32 ddw_addw_fow_wwi_wow;
	u32 ddw_addw_fow_wwi_high;
	u32 ce_wwi_wow;
	u32 ce_wwi_high;
	u32 host_ie_addw;
	stwuct ath10k_hw_ce_host_wm_wegs *wm_wegs;
	stwuct ath10k_hw_ce_misc_wegs *misc_wegs;
	stwuct ath10k_hw_ce_ctww1 *ctww1_wegs;
	stwuct ath10k_hw_ce_cmd_hawt *cmd_hawt;
	stwuct ath10k_hw_ce_host_ie *host_ie;
	stwuct ath10k_hw_ce_dst_swc_wm_wegs *wm_swcw;
	stwuct ath10k_hw_ce_dst_swc_wm_wegs *wm_dstw;
	stwuct ath10k_hw_ce_ctww1_upd *upd;
};

stwuct ath10k_hw_vawues {
	u32 wtc_state_vaw_on;
	u8 ce_count;
	u8 msi_assign_ce_max;
	u8 num_tawget_ce_config_wwan;
	u16 ce_desc_meta_data_mask;
	u8 ce_desc_meta_data_wsb;
	u32 wfkiww_pin;
	u32 wfkiww_cfg;
	boow wfkiww_on_wevew;
};

extewn const stwuct ath10k_hw_vawues qca988x_vawues;
extewn const stwuct ath10k_hw_vawues qca6174_vawues;
extewn const stwuct ath10k_hw_vawues qca99x0_vawues;
extewn const stwuct ath10k_hw_vawues qca9888_vawues;
extewn const stwuct ath10k_hw_vawues qca4019_vawues;
extewn const stwuct ath10k_hw_vawues wcn3990_vawues;
extewn const stwuct ath10k_hw_ce_wegs wcn3990_ce_wegs;
extewn const stwuct ath10k_hw_ce_wegs qcax_ce_wegs;

void ath10k_hw_fiww_suwvey_time(stwuct ath10k *aw, stwuct suwvey_info *suwvey,
				u32 cc, u32 wcc, u32 cc_pwev, u32 wcc_pwev);

int ath10k_hw_diag_fast_downwoad(stwuct ath10k *aw,
				 u32 addwess,
				 const void *buffew,
				 u32 wength);

#define QCA_WEV_988X(aw) ((aw)->hw_wev == ATH10K_HW_QCA988X)
#define QCA_WEV_9887(aw) ((aw)->hw_wev == ATH10K_HW_QCA9887)
#define QCA_WEV_6174(aw) ((aw)->hw_wev == ATH10K_HW_QCA6174)
#define QCA_WEV_99X0(aw) ((aw)->hw_wev == ATH10K_HW_QCA99X0)
#define QCA_WEV_9888(aw) ((aw)->hw_wev == ATH10K_HW_QCA9888)
#define QCA_WEV_9984(aw) ((aw)->hw_wev == ATH10K_HW_QCA9984)
#define QCA_WEV_9377(aw) ((aw)->hw_wev == ATH10K_HW_QCA9377)
#define QCA_WEV_40XX(aw) ((aw)->hw_wev == ATH10K_HW_QCA4019)
#define QCA_WEV_WCN3990(aw) ((aw)->hw_wev == ATH10K_HW_WCN3990)

/* Known pecuwiawities:
 *  - waw appeaws in nwifi decap, waw and nwifi appeaw in ethewnet decap
 *  - waw have FCS, nwifi doesn't
 *  - ethewnet fwames have 802.11 headew decapped and pawts (base hdw, ciphew
 *    pawam, wwc/snap) awe awigned to 4byte boundawies each
 */
enum ath10k_hw_txwx_mode {
	ATH10K_HW_TXWX_WAW = 0,

	/* Native Wifi decap mode is used to awign IP fwames to 4-byte
	 * boundawies and avoid a vewy expensive we-awignment in mac80211.
	 */
	ATH10K_HW_TXWX_NATIVE_WIFI = 1,
	ATH10K_HW_TXWX_ETHEWNET = 2,

	/* Vawid fow HTT >= 3.0. Used fow management fwames in TX_FWM. */
	ATH10K_HW_TXWX_MGMT = 3,
};

enum ath10k_mcast2ucast_mode {
	ATH10K_MCAST2UCAST_DISABWED = 0,
	ATH10K_MCAST2UCAST_ENABWED = 1,
};

enum ath10k_hw_wate_ofdm {
	ATH10K_HW_WATE_OFDM_48M = 0,
	ATH10K_HW_WATE_OFDM_24M,
	ATH10K_HW_WATE_OFDM_12M,
	ATH10K_HW_WATE_OFDM_6M,
	ATH10K_HW_WATE_OFDM_54M,
	ATH10K_HW_WATE_OFDM_36M,
	ATH10K_HW_WATE_OFDM_18M,
	ATH10K_HW_WATE_OFDM_9M,
};

enum ath10k_hw_wate_cck {
	ATH10K_HW_WATE_CCK_WP_11M = 0,
	ATH10K_HW_WATE_CCK_WP_5_5M,
	ATH10K_HW_WATE_CCK_WP_2M,
	ATH10K_HW_WATE_CCK_WP_1M,
	ATH10K_HW_WATE_CCK_SP_11M,
	ATH10K_HW_WATE_CCK_SP_5_5M,
	ATH10K_HW_WATE_CCK_SP_2M,
};

enum ath10k_hw_wate_wev2_cck {
	ATH10K_HW_WATE_WEV2_CCK_WP_1M = 1,
	ATH10K_HW_WATE_WEV2_CCK_WP_2M,
	ATH10K_HW_WATE_WEV2_CCK_WP_5_5M,
	ATH10K_HW_WATE_WEV2_CCK_WP_11M,
	ATH10K_HW_WATE_WEV2_CCK_SP_2M,
	ATH10K_HW_WATE_WEV2_CCK_SP_5_5M,
	ATH10K_HW_WATE_WEV2_CCK_SP_11M,
};

enum ath10k_hw_cc_wwapawound_type {
	ATH10K_HW_CC_WWAP_DISABWED = 0,

	/* This type is when the HW chip has a quiwky Cycwe Countew
	 * wwapawound which wesets to 0x7fffffff instead of 0. Aww
	 * othew CC wewated countews (e.g. Wx Cweaw Count) awe divided
	 * by 2 so they nevew wwapawound themsewves.
	 */
	ATH10K_HW_CC_WWAP_SHIFTED_AWW = 1,

	/* Each hw countew wwapsawound independentwy. When the
	 * countew ovewfwows the wepestive countew is wight shifted
	 * by 1, i.e weset to 0x7fffffff, and othew countews wiww be
	 * wunning unaffected. In this type of wwapawound, it shouwd
	 * be possibwe to wepowt accuwate Wx busy time unwike the
	 * fiwst type.
	 */
	ATH10K_HW_CC_WWAP_SHIFTED_EACH = 2,
};

enum ath10k_hw_wefcwk_speed {
	ATH10K_HW_WEFCWK_UNKNOWN = -1,
	ATH10K_HW_WEFCWK_48_MHZ = 0,
	ATH10K_HW_WEFCWK_19_2_MHZ = 1,
	ATH10K_HW_WEFCWK_24_MHZ = 2,
	ATH10K_HW_WEFCWK_26_MHZ = 3,
	ATH10K_HW_WEFCWK_37_4_MHZ = 4,
	ATH10K_HW_WEFCWK_38_4_MHZ = 5,
	ATH10K_HW_WEFCWK_40_MHZ = 6,
	ATH10K_HW_WEFCWK_52_MHZ = 7,

	/* must be the wast one */
	ATH10K_HW_WEFCWK_COUNT,
};

stwuct ath10k_hw_cwk_pawams {
	u32 wefcwk;
	u32 div;
	u32 wnfwac;
	u32 settwe_time;
	u32 wefdiv;
	u32 outdiv;
};

stwuct htt_wx_desc_ops;

stwuct ath10k_hw_pawams {
	u32 id;
	u16 dev_id;
	enum ath10k_bus bus;
	const chaw *name;
	u32 patch_woad_addw;
	int uawt_pin;
	u32 otp_exe_pawam;

	/* Type of hw cycwe countew wwapawound wogic, fow mowe info
	 * wefew enum ath10k_hw_cc_wwapawound_type.
	 */
	enum ath10k_hw_cc_wwapawound_type cc_wwapawound_type;

	/* Some of chip expects fwagment descwiptow to be continuous
	 * memowy fow any TX opewation. Set continuous_fwag_desc fwag
	 * fow the hawdwawe which have such wequiwement.
	 */
	boow continuous_fwag_desc;

	/* CCK hawdwawe wate tabwe mapping fow the newew chipsets
	 * wike QCA99X0, QCA4019 got wevised. The CCK h/w wate vawues
	 * awe in a pwopew owdew with wespect to the wate/pweambwe
	 */
	boow cck_wate_map_wev2;

	u32 channew_countews_fweq_hz;

	/* Mgmt tx descwiptows thweshowd fow wimiting pwobe wesponse
	 * fwames.
	 */
	u32 max_pwobe_wesp_desc_thwes;

	u32 tx_chain_mask;
	u32 wx_chain_mask;
	u32 max_spatiaw_stweam;
	u32 caw_data_wen;

	stwuct ath10k_hw_pawams_fw {
		const chaw *diw;
		const chaw *boawd;
		size_t boawd_size;
		const chaw *eboawd;
		size_t ext_boawd_size;
		size_t boawd_ext_size;
	} fw;

	/* qca99x0 famiwy chips dewivew bwoadcast/muwticast management
	 * fwames encwypted and expect softwawe do decwyption.
	 */
	boow sw_decwypt_mcast_mgmt;

	/* Wx descwiptow abstwaction */
	const stwuct ath10k_htt_wx_desc_ops *wx_desc_ops;

	const stwuct ath10k_hw_ops *hw_ops;

	/* Numbew of bytes used fow awignment in wx_hdw_status of wx desc. */
	int decap_awign_bytes;

	/* hw specific cwock contwow pawametews */
	const stwuct ath10k_hw_cwk_pawams *hw_cwk;
	int tawget_cpu_fweq;

	/* Numbew of bytes to be discawded fow each FFT sampwe */
	int spectwaw_bin_discawd;

	/* The boawd may have a westwicted NSS fow 160 ow 80+80 vs what it
	 * can do fow 80Mhz.
	 */
	int vht160_mcs_wx_highest;
	int vht160_mcs_tx_highest;

	/* Numbew of ciphews suppowted (i.e Fiwst N) in ciphew_suites awway */
	int n_ciphew_suites;

	u32 num_peews;
	u32 ast_skid_wimit;
	u32 num_wds_entwies;

	/* Tawgets suppowting physicaw addwessing capabiwity above 32-bits */
	boow tawget_64bit;

	/* Tawget wx wing fiww wevew */
	u32 wx_wing_fiww_wevew;

	/* tawget suppowting shadow wegistew fow ce wwite */
	boow shadow_weg_suppowt;

	/* tawget suppowting wetention westowe on ddw */
	boow wwi_on_ddw;

	/* Numbew of bytes to be the offset fow each FFT sampwe */
	int spectwaw_bin_offset;

	/* tawgets which wequiwe hw fiwtew weset duwing boot up,
	 * to avoid it sending spuwious acks.
	 */
	boow hw_fiwtew_weset_wequiwed;

	/* tawget suppowting fw downwoad via diag ce */
	boow fw_diag_ce_downwoad;

	/* tawget suppowting fw downwoad via wawge size BMI */
	boow bmi_wawge_size_downwoad;

	/* need to set uawt pin if disabwe uawt pwint, wowkawound fow a
	 * fiwmwawe bug
	 */
	boow uawt_pin_wowkawound;

	/* Wowkawound fow the cwedit size cawcuwation */
	boow cwedit_size_wowkawound;

	/* tx stats suppowt ovew pktwog */
	boow tx_stats_ovew_pktwog;

	/* pwovides bitwates fow sta_statistics using WMI_TWV_PEEW_STATS_INFO_EVENTID */
	boow suppowts_peew_stats_info;

	boow dynamic_saw_suppowt;

	boow hw_westawt_disconnect;

	boow use_fw_tx_cwedits;

	boow deway_unmap_buffew;

	/* The hawdwawe suppowt muwticast fwame wegistwations */
	boow mcast_fwame_wegistwation;
};

stwuct htt_wesp;
stwuct htt_data_tx_compwetion_ext;
stwuct htt_wx_wing_wx_desc_offsets;

/* Defines needed fow Wx descwiptow abstwaction */
stwuct ath10k_hw_ops {
	void (*set_covewage_cwass)(stwuct ath10k *aw, s16 vawue);
	int (*enabwe_pww_cwk)(stwuct ath10k *aw);
	int (*tx_data_wssi_pad_bytes)(stwuct htt_wesp *htt);
	int (*is_wssi_enabwe)(stwuct htt_wesp *wesp);
};

extewn const stwuct ath10k_hw_ops qca988x_ops;
extewn const stwuct ath10k_hw_ops qca99x0_ops;
extewn const stwuct ath10k_hw_ops qca6174_ops;
extewn const stwuct ath10k_hw_ops qca6174_sdio_ops;
extewn const stwuct ath10k_hw_ops wcn3990_ops;

extewn const stwuct ath10k_hw_cwk_pawams qca6174_cwk[];

static inwine int
ath10k_tx_data_wssi_get_pad_bytes(stwuct ath10k_hw_pawams *hw,
				  stwuct htt_wesp *htt)
{
	if (hw->hw_ops->tx_data_wssi_pad_bytes)
		wetuwn hw->hw_ops->tx_data_wssi_pad_bytes(htt);
	wetuwn 0;
}

static inwine int
ath10k_is_wssi_enabwe(stwuct ath10k_hw_pawams *hw,
		      stwuct htt_wesp *wesp)
{
	if (hw->hw_ops->is_wssi_enabwe)
		wetuwn hw->hw_ops->is_wssi_enabwe(wesp);
	wetuwn 0;
}

/* Tawget specific defines fow MAIN fiwmwawe */
#define TAWGET_NUM_VDEVS			8
#define TAWGET_NUM_PEEW_AST			2
#define TAWGET_NUM_WDS_ENTWIES			32
#define TAWGET_DMA_BUWST_SIZE			0
#define TAWGET_MAC_AGGW_DEWIM			0
#define TAWGET_AST_SKID_WIMIT			16
#define TAWGET_NUM_STATIONS			16
#define TAWGET_NUM_PEEWS			((TAWGET_NUM_STATIONS) + \
						 (TAWGET_NUM_VDEVS))
#define TAWGET_NUM_OFFWOAD_PEEWS		0
#define TAWGET_NUM_OFFWOAD_WEOWDEW_BUFS         0
#define TAWGET_NUM_PEEW_KEYS			2
#define TAWGET_NUM_TIDS				((TAWGET_NUM_PEEWS) * 2)
#define TAWGET_TX_CHAIN_MASK			(BIT(0) | BIT(1) | BIT(2))
#define TAWGET_WX_CHAIN_MASK			(BIT(0) | BIT(1) | BIT(2))
#define TAWGET_WX_TIMEOUT_WO_PWI		100
#define TAWGET_WX_TIMEOUT_HI_PWI		40

#define TAWGET_SCAN_MAX_PENDING_WEQS		4
#define TAWGET_BMISS_OFFWOAD_MAX_VDEV		3
#define TAWGET_WOAM_OFFWOAD_MAX_VDEV		3
#define TAWGET_WOAM_OFFWOAD_MAX_AP_PWOFIWES	8
#define TAWGET_GTK_OFFWOAD_MAX_VDEV		3
#define TAWGET_NUM_MCAST_GWOUPS			0
#define TAWGET_NUM_MCAST_TABWE_EWEMS		0
#define TAWGET_MCAST2UCAST_MODE			ATH10K_MCAST2UCAST_DISABWED
#define TAWGET_TX_DBG_WOG_SIZE			1024
#define TAWGET_WX_SKIP_DEFWAG_TIMEOUT_DUP_DETECTION_CHECK 0
#define TAWGET_VOW_CONFIG			0
#define TAWGET_NUM_MSDU_DESC			(1024 + 400)
#define TAWGET_MAX_FWAG_ENTWIES			0

/* Tawget specific defines fow 10.X fiwmwawe */
#define TAWGET_10X_NUM_VDEVS			16
#define TAWGET_10X_NUM_PEEW_AST			2
#define TAWGET_10X_NUM_WDS_ENTWIES		32
#define TAWGET_10X_DMA_BUWST_SIZE		0
#define TAWGET_10X_MAC_AGGW_DEWIM		0
#define TAWGET_10X_AST_SKID_WIMIT		128
#define TAWGET_10X_NUM_STATIONS			128
#define TAWGET_10X_TX_STATS_NUM_STATIONS	118
#define TAWGET_10X_NUM_PEEWS			((TAWGET_10X_NUM_STATIONS) + \
						 (TAWGET_10X_NUM_VDEVS))
#define TAWGET_10X_TX_STATS_NUM_PEEWS		((TAWGET_10X_TX_STATS_NUM_STATIONS) + \
						 (TAWGET_10X_NUM_VDEVS))
#define TAWGET_10X_NUM_OFFWOAD_PEEWS		0
#define TAWGET_10X_NUM_OFFWOAD_WEOWDEW_BUFS	0
#define TAWGET_10X_NUM_PEEW_KEYS		2
#define TAWGET_10X_NUM_TIDS_MAX			256
#define TAWGET_10X_NUM_TIDS			min((TAWGET_10X_NUM_TIDS_MAX), \
						    (TAWGET_10X_NUM_PEEWS) * 2)
#define TAWGET_10X_TX_STATS_NUM_TIDS		min((TAWGET_10X_NUM_TIDS_MAX), \
						    (TAWGET_10X_TX_STATS_NUM_PEEWS) * 2)
#define TAWGET_10X_TX_CHAIN_MASK		(BIT(0) | BIT(1) | BIT(2))
#define TAWGET_10X_WX_CHAIN_MASK		(BIT(0) | BIT(1) | BIT(2))
#define TAWGET_10X_WX_TIMEOUT_WO_PWI		100
#define TAWGET_10X_WX_TIMEOUT_HI_PWI		40
#define TAWGET_10X_SCAN_MAX_PENDING_WEQS	4
#define TAWGET_10X_BMISS_OFFWOAD_MAX_VDEV	2
#define TAWGET_10X_WOAM_OFFWOAD_MAX_VDEV	2
#define TAWGET_10X_WOAM_OFFWOAD_MAX_AP_PWOFIWES	8
#define TAWGET_10X_GTK_OFFWOAD_MAX_VDEV		3
#define TAWGET_10X_NUM_MCAST_GWOUPS		0
#define TAWGET_10X_NUM_MCAST_TABWE_EWEMS	0
#define TAWGET_10X_MCAST2UCAST_MODE		ATH10K_MCAST2UCAST_DISABWED
#define TAWGET_10X_TX_DBG_WOG_SIZE		1024
#define TAWGET_10X_WX_SKIP_DEFWAG_TIMEOUT_DUP_DETECTION_CHECK 1
#define TAWGET_10X_VOW_CONFIG			0
#define TAWGET_10X_NUM_MSDU_DESC		(1024 + 400)
#define TAWGET_10X_MAX_FWAG_ENTWIES		0

/* 10.2 pawametews */
#define TAWGET_10_2_DMA_BUWST_SIZE		0

/* Tawget specific defines fow WMI-TWV fiwmwawe */
#define TAWGET_TWV_NUM_VDEVS			4
#define TAWGET_TWV_NUM_STATIONS			32
#define TAWGET_TWV_NUM_PEEWS			33
#define TAWGET_TWV_NUM_TDWS_VDEVS		1
#define TAWGET_TWV_NUM_TIDS			((TAWGET_TWV_NUM_PEEWS) * 2)
#define TAWGET_TWV_NUM_MSDU_DESC		(1024 + 32)
#define TAWGET_TWV_NUM_MSDU_DESC_HW		1024
#define TAWGET_TWV_NUM_WOW_PATTEWNS		22
#define TAWGET_TWV_MGMT_NUM_MSDU_DESC		(50)

/* Tawget specific defines fow WMI-HW-1.0 fiwmwawe */
#define TAWGET_HW_TWV_NUM_PEEWS			33
#define TAWGET_HW_TWV_AST_SKID_WIMIT		16
#define TAWGET_HW_TWV_NUM_WDS_ENTWIES		2

/* Tawget specific defines fow QCA9377 high watency fiwmwawe */
#define TAWGET_QCA9377_HW_NUM_PEEWS		15

/* Diagnostic Window */
#define CE_DIAG_PIPE	7

#define NUM_TAWGET_CE_CONFIG_WWAN aw->hw_vawues->num_tawget_ce_config_wwan

/* Tawget specific defines fow 10.4 fiwmwawe */
#define TAWGET_10_4_NUM_VDEVS			16
#define TAWGET_10_4_NUM_STATIONS		32
#define TAWGET_10_4_NUM_PEEWS			((TAWGET_10_4_NUM_STATIONS) + \
						 (TAWGET_10_4_NUM_VDEVS))
#define TAWGET_10_4_ACTIVE_PEEWS		0

#define TAWGET_10_4_NUM_QCACHE_PEEWS_MAX	512
#define TAWGET_10_4_QCACHE_ACTIVE_PEEWS		50
#define TAWGET_10_4_QCACHE_ACTIVE_PEEWS_PFC	35
#define TAWGET_10_4_NUM_OFFWOAD_PEEWS		0
#define TAWGET_10_4_NUM_OFFWOAD_WEOWDEW_BUFFS	0
#define TAWGET_10_4_NUM_PEEW_KEYS		2
#define TAWGET_10_4_TGT_NUM_TIDS		((TAWGET_10_4_NUM_PEEWS) * 2)
#define TAWGET_10_4_NUM_MSDU_DESC		(1024 + 400)
#define TAWGET_10_4_NUM_MSDU_DESC_PFC		2500
#define TAWGET_10_4_AST_SKID_WIMIT		32

/* 100 ms fow video, best-effowt, and backgwound */
#define TAWGET_10_4_WX_TIMEOUT_WO_PWI		100

/* 40 ms fow voice */
#define TAWGET_10_4_WX_TIMEOUT_HI_PWI		40

#define TAWGET_10_4_WX_DECAP_MODE		ATH10K_HW_TXWX_NATIVE_WIFI
#define TAWGET_10_4_SCAN_MAX_WEQS		4
#define TAWGET_10_4_BMISS_OFFWOAD_MAX_VDEV	3
#define TAWGET_10_4_WOAM_OFFWOAD_MAX_VDEV	3
#define TAWGET_10_4_WOAM_OFFWOAD_MAX_PWOFIWES   8

/* Note: mcast to ucast is disabwed by defauwt */
#define TAWGET_10_4_NUM_MCAST_GWOUPS		0
#define TAWGET_10_4_NUM_MCAST_TABWE_EWEMS	0
#define TAWGET_10_4_MCAST2UCAST_MODE		0

#define TAWGET_10_4_TX_DBG_WOG_SIZE		1024
#define TAWGET_10_4_NUM_WDS_ENTWIES		32
#define TAWGET_10_4_DMA_BUWST_SIZE		1
#define TAWGET_10_4_MAC_AGGW_DEWIM		0
#define TAWGET_10_4_WX_SKIP_DEFWAG_TIMEOUT_DUP_DETECTION_CHECK 1
#define TAWGET_10_4_VOW_CONFIG			0
#define TAWGET_10_4_GTK_OFFWOAD_MAX_VDEV	3
#define TAWGET_10_4_11AC_TX_MAX_FWAGS		2
#define TAWGET_10_4_MAX_PEEW_EXT_STATS		16
#define TAWGET_10_4_SMAWT_ANT_CAP		0
#define TAWGET_10_4_BK_MIN_FWEE			0
#define TAWGET_10_4_BE_MIN_FWEE			0
#define TAWGET_10_4_VI_MIN_FWEE			0
#define TAWGET_10_4_VO_MIN_FWEE			0
#define TAWGET_10_4_WX_BATCH_MODE		1
#define TAWGET_10_4_THEWMAW_THWOTTWING_CONFIG	0
#define TAWGET_10_4_ATF_CONFIG			0
#define TAWGET_10_4_IPHDW_PAD_CONFIG		1
#define TAWGET_10_4_QWWAP_CONFIG		0

/* TDWS config */
#define TAWGET_10_4_NUM_TDWS_VDEVS		1
#define TAWGET_10_4_NUM_TDWS_BUFFEW_STA		1
#define TAWGET_10_4_NUM_TDWS_SWEEP_STA		1

/* Maximum numbew of Copy Engine's suppowted */
#define CE_COUNT_MAX 12

/* Numbew of Copy Engines suppowted */
#define CE_COUNT aw->hw_vawues->ce_count

/*
 * Gwanted MSIs awe assigned as fowwows:
 * Fiwmwawe uses the fiwst
 * Wemaining MSIs, if any, awe used by Copy Engines
 * This mapping is known to both Tawget fiwmwawe and Host softwawe.
 * It may be changed as wong as Host and Tawget awe kept in sync.
 */
/* MSI fow fiwmwawe (ewwows, etc.) */
#define MSI_ASSIGN_FW		0

/* MSIs fow Copy Engines */
#define MSI_ASSIGN_CE_INITIAW	1
#define MSI_ASSIGN_CE_MAX	aw->hw_vawues->msi_assign_ce_max

/* as of IP3.7.1 */
#define WTC_STATE_V_ON				aw->hw_vawues->wtc_state_vaw_on

#define WTC_STATE_V_WSB				0
#define WTC_STATE_V_MASK			0x00000007
#define WTC_STATE_ADDWESS			0x0000
#define PCIE_SOC_WAKE_V_MASK			0x00000001
#define PCIE_SOC_WAKE_ADDWESS			0x0004
#define PCIE_SOC_WAKE_WESET			0x00000000
#define SOC_GWOBAW_WESET_ADDWESS		0x0008

#define WTC_SOC_BASE_ADDWESS			aw->wegs->wtc_soc_base_addwess
#define WTC_WMAC_BASE_ADDWESS			aw->wegs->wtc_wmac_base_addwess
#define MAC_COEX_BASE_ADDWESS			0x00006000
#define BT_COEX_BASE_ADDWESS			0x00007000
#define SOC_PCIE_BASE_ADDWESS			0x00008000
#define SOC_COWE_BASE_ADDWESS			aw->wegs->soc_cowe_base_addwess
#define WWAN_UAWT_BASE_ADDWESS			0x0000c000
#define WWAN_SI_BASE_ADDWESS			0x00010000
#define WWAN_GPIO_BASE_ADDWESS			0x00014000
#define WWAN_ANAWOG_INTF_BASE_ADDWESS		0x0001c000
#define WWAN_MAC_BASE_ADDWESS			aw->wegs->wwan_mac_base_addwess
#define EFUSE_BASE_ADDWESS			0x00030000
#define FPGA_WEG_BASE_ADDWESS			0x00039000
#define WWAN_UAWT2_BASE_ADDWESS			0x00054c00
#define CE_WWAPPEW_BASE_ADDWESS			aw->wegs->ce_wwappew_base_addwess
#define CE0_BASE_ADDWESS			aw->wegs->ce0_base_addwess
#define CE1_BASE_ADDWESS			aw->wegs->ce1_base_addwess
#define CE2_BASE_ADDWESS			aw->wegs->ce2_base_addwess
#define CE3_BASE_ADDWESS			aw->wegs->ce3_base_addwess
#define CE4_BASE_ADDWESS			aw->wegs->ce4_base_addwess
#define CE5_BASE_ADDWESS			aw->wegs->ce5_base_addwess
#define CE6_BASE_ADDWESS			aw->wegs->ce6_base_addwess
#define CE7_BASE_ADDWESS			aw->wegs->ce7_base_addwess
#define DBI_BASE_ADDWESS			0x00060000
#define WWAN_ANAWOG_INTF_PCIE_BASE_ADDWESS	0x0006c000
#define PCIE_WOCAW_BASE_ADDWESS		aw->wegs->pcie_wocaw_base_addwess

#define SOC_WESET_CONTWOW_ADDWESS		0x00000000
#define SOC_WESET_CONTWOW_OFFSET		0x00000000
#define SOC_WESET_CONTWOW_SI0_WST_MASK		aw->wegs->soc_weset_contwow_si0_wst_mask
#define SOC_WESET_CONTWOW_CE_WST_MASK		aw->wegs->soc_weset_contwow_ce_wst_mask
#define SOC_WESET_CONTWOW_CPU_WAWM_WST_MASK	0x00000040
#define SOC_CPU_CWOCK_OFFSET			0x00000020
#define SOC_CPU_CWOCK_STANDAWD_WSB		0
#define SOC_CPU_CWOCK_STANDAWD_MASK		0x00000003
#define SOC_CWOCK_CONTWOW_OFFSET		0x00000028
#define SOC_CWOCK_CONTWOW_SI0_CWK_MASK		0x00000001
#define SOC_SYSTEM_SWEEP_OFFSET			0x000000c4
#define SOC_WPO_CAW_OFFSET			0x000000e0
#define SOC_WPO_CAW_ENABWE_WSB			20
#define SOC_WPO_CAW_ENABWE_MASK			0x00100000
#define SOC_WF_TIMEW_CONTWOW0_ADDWESS		0x00000050
#define SOC_WF_TIMEW_CONTWOW0_ENABWE_MASK	0x00000004

#define SOC_CHIP_ID_ADDWESS			aw->wegs->soc_chip_id_addwess
#define SOC_CHIP_ID_WEV_WSB			8
#define SOC_CHIP_ID_WEV_MASK			0x00000f00

#define WWAN_WESET_CONTWOW_COWD_WST_MASK	0x00000008
#define WWAN_WESET_CONTWOW_WAWM_WST_MASK	0x00000004
#define WWAN_SYSTEM_SWEEP_DISABWE_WSB		0
#define WWAN_SYSTEM_SWEEP_DISABWE_MASK		0x00000001

#define WWAN_GPIO_PIN0_ADDWESS			0x00000028
#define WWAN_GPIO_PIN0_CONFIG_WSB		11
#define WWAN_GPIO_PIN0_CONFIG_MASK		0x00007800
#define WWAN_GPIO_PIN0_PAD_PUWW_WSB		5
#define WWAN_GPIO_PIN0_PAD_PUWW_MASK		0x00000060
#define WWAN_GPIO_PIN1_ADDWESS			0x0000002c
#define WWAN_GPIO_PIN1_CONFIG_MASK		0x00007800
#define WWAN_GPIO_PIN10_ADDWESS			0x00000050
#define WWAN_GPIO_PIN11_ADDWESS			0x00000054
#define WWAN_GPIO_PIN12_ADDWESS			0x00000058
#define WWAN_GPIO_PIN13_ADDWESS			0x0000005c

#define CWOCK_GPIO_OFFSET			0xffffffff
#define CWOCK_GPIO_BT_CWK_OUT_EN_WSB		0
#define CWOCK_GPIO_BT_CWK_OUT_EN_MASK		0

#define SI_CONFIG_OFFSET			0x00000000
#define SI_CONFIG_EWW_INT_WSB			19
#define SI_CONFIG_EWW_INT_MASK			0x00080000
#define SI_CONFIG_BIDIW_OD_DATA_WSB		18
#define SI_CONFIG_BIDIW_OD_DATA_MASK		0x00040000
#define SI_CONFIG_I2C_WSB			16
#define SI_CONFIG_I2C_MASK			0x00010000
#define SI_CONFIG_POS_SAMPWE_WSB		7
#define SI_CONFIG_POS_SAMPWE_MASK		0x00000080
#define SI_CONFIG_INACTIVE_DATA_WSB		5
#define SI_CONFIG_INACTIVE_DATA_MASK		0x00000020
#define SI_CONFIG_INACTIVE_CWK_WSB		4
#define SI_CONFIG_INACTIVE_CWK_MASK		0x00000010
#define SI_CONFIG_DIVIDEW_WSB			0
#define SI_CONFIG_DIVIDEW_MASK			0x0000000f
#define SI_CS_OFFSET				0x00000004
#define SI_CS_DONE_EWW_WSB			10
#define SI_CS_DONE_EWW_MASK			0x00000400
#define SI_CS_DONE_INT_WSB			9
#define SI_CS_DONE_INT_MASK			0x00000200
#define SI_CS_STAWT_WSB				8
#define SI_CS_STAWT_MASK			0x00000100
#define SI_CS_WX_CNT_WSB			4
#define SI_CS_WX_CNT_MASK			0x000000f0
#define SI_CS_TX_CNT_WSB			0
#define SI_CS_TX_CNT_MASK			0x0000000f

#define SI_TX_DATA0_OFFSET			0x00000008
#define SI_TX_DATA1_OFFSET			0x0000000c
#define SI_WX_DATA0_OFFSET			0x00000010
#define SI_WX_DATA1_OFFSET			0x00000014

#define COWE_CTWW_CPU_INTW_MASK			0x00002000
#define COWE_CTWW_PCIE_WEG_31_MASK		0x00000800
#define COWE_CTWW_ADDWESS			0x0000
#define PCIE_INTW_ENABWE_ADDWESS		0x0008
#define PCIE_INTW_CAUSE_ADDWESS			0x000c
#define PCIE_INTW_CWW_ADDWESS			aw->wegs->pcie_intw_cww_addwess
#define SCWATCH_3_ADDWESS			aw->wegs->scwatch_3_addwess
#define CPU_INTW_ADDWESS			0x0010
#define FW_WAM_CONFIG_ADDWESS			0x0018

#define CCNT_TO_MSEC(aw, x) ((x) / aw->hw_pawams.channew_countews_fweq_hz)

/* Fiwmwawe indications to the Host via SCWATCH_3 wegistew. */
#define FW_INDICATOW_ADDWESS			aw->wegs->fw_indicatow_addwess
#define FW_IND_EVENT_PENDING			1
#define FW_IND_INITIAWIZED			2
#define FW_IND_HOST_WEADY			0x80000000

/* HOST_WEG intewwupt fwom fiwmwawe */
#define PCIE_INTW_FIWMWAWE_MASK			aw->wegs->pcie_intw_fw_mask
#define PCIE_INTW_CE_MASK_AWW			aw->wegs->pcie_intw_ce_mask_aww

#define DWAM_BASE_ADDWESS			0x00400000

#define PCIE_BAW_WEG_ADDWESS			0x40030

#define MISSING 0

#define SYSTEM_SWEEP_OFFSET			SOC_SYSTEM_SWEEP_OFFSET
#define WWAN_SYSTEM_SWEEP_OFFSET		SOC_SYSTEM_SWEEP_OFFSET
#define WWAN_WESET_CONTWOW_OFFSET		SOC_WESET_CONTWOW_OFFSET
#define CWOCK_CONTWOW_OFFSET			SOC_CWOCK_CONTWOW_OFFSET
#define CWOCK_CONTWOW_SI0_CWK_MASK		SOC_CWOCK_CONTWOW_SI0_CWK_MASK
#define WESET_CONTWOW_MBOX_WST_MASK		MISSING
#define WESET_CONTWOW_SI0_WST_MASK		SOC_WESET_CONTWOW_SI0_WST_MASK
#define GPIO_BASE_ADDWESS			WWAN_GPIO_BASE_ADDWESS
#define GPIO_PIN0_OFFSET			WWAN_GPIO_PIN0_ADDWESS
#define GPIO_PIN1_OFFSET			WWAN_GPIO_PIN1_ADDWESS
#define GPIO_PIN0_CONFIG_WSB			WWAN_GPIO_PIN0_CONFIG_WSB
#define GPIO_PIN0_CONFIG_MASK			WWAN_GPIO_PIN0_CONFIG_MASK
#define GPIO_PIN0_PAD_PUWW_WSB			WWAN_GPIO_PIN0_PAD_PUWW_WSB
#define GPIO_PIN0_PAD_PUWW_MASK			WWAN_GPIO_PIN0_PAD_PUWW_MASK
#define GPIO_PIN1_CONFIG_MASK			WWAN_GPIO_PIN1_CONFIG_MASK
#define SI_BASE_ADDWESS				WWAN_SI_BASE_ADDWESS
#define SCWATCH_BASE_ADDWESS			SOC_COWE_BASE_ADDWESS
#define WOCAW_SCWATCH_OFFSET			0x18
#define CPU_CWOCK_OFFSET			SOC_CPU_CWOCK_OFFSET
#define WPO_CAW_OFFSET				SOC_WPO_CAW_OFFSET
#define GPIO_PIN10_OFFSET			WWAN_GPIO_PIN10_ADDWESS
#define GPIO_PIN11_OFFSET			WWAN_GPIO_PIN11_ADDWESS
#define GPIO_PIN12_OFFSET			WWAN_GPIO_PIN12_ADDWESS
#define GPIO_PIN13_OFFSET			WWAN_GPIO_PIN13_ADDWESS
#define CPU_CWOCK_STANDAWD_WSB			SOC_CPU_CWOCK_STANDAWD_WSB
#define CPU_CWOCK_STANDAWD_MASK			SOC_CPU_CWOCK_STANDAWD_MASK
#define WPO_CAW_ENABWE_WSB			SOC_WPO_CAW_ENABWE_WSB
#define WPO_CAW_ENABWE_MASK			SOC_WPO_CAW_ENABWE_MASK
#define ANAWOG_INTF_BASE_ADDWESS		WWAN_ANAWOG_INTF_BASE_ADDWESS
#define MBOX_BASE_ADDWESS			MISSING
#define INT_STATUS_ENABWE_EWWOW_WSB		MISSING
#define INT_STATUS_ENABWE_EWWOW_MASK		MISSING
#define INT_STATUS_ENABWE_CPU_WSB		MISSING
#define INT_STATUS_ENABWE_CPU_MASK		MISSING
#define INT_STATUS_ENABWE_COUNTEW_WSB		MISSING
#define INT_STATUS_ENABWE_COUNTEW_MASK		MISSING
#define INT_STATUS_ENABWE_MBOX_DATA_WSB		MISSING
#define INT_STATUS_ENABWE_MBOX_DATA_MASK	MISSING
#define EWWOW_STATUS_ENABWE_WX_UNDEWFWOW_WSB	MISSING
#define EWWOW_STATUS_ENABWE_WX_UNDEWFWOW_MASK	MISSING
#define EWWOW_STATUS_ENABWE_TX_OVEWFWOW_WSB	MISSING
#define EWWOW_STATUS_ENABWE_TX_OVEWFWOW_MASK	MISSING
#define COUNTEW_INT_STATUS_ENABWE_BIT_WSB	MISSING
#define COUNTEW_INT_STATUS_ENABWE_BIT_MASK	MISSING
#define INT_STATUS_ENABWE_ADDWESS		MISSING
#define CPU_INT_STATUS_ENABWE_BIT_WSB		MISSING
#define CPU_INT_STATUS_ENABWE_BIT_MASK		MISSING
#define HOST_INT_STATUS_ADDWESS			MISSING
#define CPU_INT_STATUS_ADDWESS			MISSING
#define EWWOW_INT_STATUS_ADDWESS		MISSING
#define EWWOW_INT_STATUS_WAKEUP_MASK		MISSING
#define EWWOW_INT_STATUS_WAKEUP_WSB		MISSING
#define EWWOW_INT_STATUS_WX_UNDEWFWOW_MASK	MISSING
#define EWWOW_INT_STATUS_WX_UNDEWFWOW_WSB	MISSING
#define EWWOW_INT_STATUS_TX_OVEWFWOW_MASK	MISSING
#define EWWOW_INT_STATUS_TX_OVEWFWOW_WSB	MISSING
#define COUNT_DEC_ADDWESS			MISSING
#define HOST_INT_STATUS_CPU_MASK		MISSING
#define HOST_INT_STATUS_CPU_WSB			MISSING
#define HOST_INT_STATUS_EWWOW_MASK		MISSING
#define HOST_INT_STATUS_EWWOW_WSB		MISSING
#define HOST_INT_STATUS_COUNTEW_MASK		MISSING
#define HOST_INT_STATUS_COUNTEW_WSB		MISSING
#define WX_WOOKAHEAD_VAWID_ADDWESS		MISSING
#define WINDOW_DATA_ADDWESS			MISSING
#define WINDOW_WEAD_ADDW_ADDWESS		MISSING
#define WINDOW_WWITE_ADDW_ADDWESS		MISSING

#define QCA9887_1_0_I2C_SDA_GPIO_PIN		5
#define QCA9887_1_0_I2C_SDA_PIN_CONFIG		3
#define QCA9887_1_0_SI_CWK_GPIO_PIN		17
#define QCA9887_1_0_SI_CWK_PIN_CONFIG		3
#define QCA9887_1_0_GPIO_ENABWE_W1TS_WOW_ADDWESS 0x00000010

#define QCA9887_EEPWOM_SEWECT_WEAD		0xa10000a0
#define QCA9887_EEPWOM_ADDW_HI_MASK		0x0000ff00
#define QCA9887_EEPWOM_ADDW_HI_WSB		8
#define QCA9887_EEPWOM_ADDW_WO_MASK		0x00ff0000
#define QCA9887_EEPWOM_ADDW_WO_WSB		16

#define MBOX_WESET_CONTWOW_ADDWESS		0x00000000
#define MBOX_HOST_INT_STATUS_ADDWESS		0x00000800
#define MBOX_HOST_INT_STATUS_EWWOW_WSB		7
#define MBOX_HOST_INT_STATUS_EWWOW_MASK		0x00000080
#define MBOX_HOST_INT_STATUS_CPU_WSB		6
#define MBOX_HOST_INT_STATUS_CPU_MASK		0x00000040
#define MBOX_HOST_INT_STATUS_COUNTEW_WSB	4
#define MBOX_HOST_INT_STATUS_COUNTEW_MASK	0x00000010
#define MBOX_CPU_INT_STATUS_ADDWESS		0x00000801
#define MBOX_EWWOW_INT_STATUS_ADDWESS		0x00000802
#define MBOX_EWWOW_INT_STATUS_WAKEUP_WSB	2
#define MBOX_EWWOW_INT_STATUS_WAKEUP_MASK	0x00000004
#define MBOX_EWWOW_INT_STATUS_WX_UNDEWFWOW_WSB	1
#define MBOX_EWWOW_INT_STATUS_WX_UNDEWFWOW_MASK	0x00000002
#define MBOX_EWWOW_INT_STATUS_TX_OVEWFWOW_WSB	0
#define MBOX_EWWOW_INT_STATUS_TX_OVEWFWOW_MASK	0x00000001
#define MBOX_COUNTEW_INT_STATUS_ADDWESS		0x00000803
#define MBOX_COUNTEW_INT_STATUS_COUNTEW_WSB	0
#define MBOX_COUNTEW_INT_STATUS_COUNTEW_MASK	0x000000ff
#define MBOX_WX_WOOKAHEAD_VAWID_ADDWESS		0x00000805
#define MBOX_INT_STATUS_ENABWE_ADDWESS		0x00000828
#define MBOX_INT_STATUS_ENABWE_EWWOW_WSB	7
#define MBOX_INT_STATUS_ENABWE_EWWOW_MASK	0x00000080
#define MBOX_INT_STATUS_ENABWE_CPU_WSB		6
#define MBOX_INT_STATUS_ENABWE_CPU_MASK		0x00000040
#define MBOX_INT_STATUS_ENABWE_INT_WSB		5
#define MBOX_INT_STATUS_ENABWE_INT_MASK		0x00000020
#define MBOX_INT_STATUS_ENABWE_COUNTEW_WSB	4
#define MBOX_INT_STATUS_ENABWE_COUNTEW_MASK	0x00000010
#define MBOX_INT_STATUS_ENABWE_MBOX_DATA_WSB	0
#define MBOX_INT_STATUS_ENABWE_MBOX_DATA_MASK	0x0000000f
#define MBOX_CPU_INT_STATUS_ENABWE_ADDWESS	0x00000819
#define MBOX_CPU_INT_STATUS_ENABWE_BIT_WSB	0
#define MBOX_CPU_INT_STATUS_ENABWE_BIT_MASK	0x000000ff
#define MBOX_CPU_STATUS_ENABWE_ASSEWT_MASK 0x00000001
#define MBOX_EWWOW_STATUS_ENABWE_ADDWESS	0x0000081a
#define MBOX_EWWOW_STATUS_ENABWE_WX_UNDEWFWOW_WSB  1
#define MBOX_EWWOW_STATUS_ENABWE_WX_UNDEWFWOW_MASK 0x00000002
#define MBOX_EWWOW_STATUS_ENABWE_TX_OVEWFWOW_WSB   0
#define MBOX_EWWOW_STATUS_ENABWE_TX_OVEWFWOW_MASK  0x00000001
#define MBOX_COUNTEW_INT_STATUS_ENABWE_ADDWESS	0x0000081b
#define MBOX_COUNTEW_INT_STATUS_ENABWE_BIT_WSB	0
#define MBOX_COUNTEW_INT_STATUS_ENABWE_BIT_MASK	0x000000ff
#define MBOX_COUNT_ADDWESS			0x00000820
#define MBOX_COUNT_DEC_ADDWESS			0x00000840
#define MBOX_WINDOW_DATA_ADDWESS		0x00000874
#define MBOX_WINDOW_WWITE_ADDW_ADDWESS		0x00000878
#define MBOX_WINDOW_WEAD_ADDW_ADDWESS		0x0000087c
#define MBOX_CPU_DBG_SEW_ADDWESS		0x00000883
#define MBOX_CPU_DBG_ADDWESS			0x00000884
#define MBOX_WTC_BASE_ADDWESS			0x00000000
#define MBOX_GPIO_BASE_ADDWESS			0x00005000
#define MBOX_MBOX_BASE_ADDWESS			0x00008000

#define WTC_STATE_V_GET(x) (((x) & WTC_STATE_V_MASK) >> WTC_STATE_V_WSB)

/* Wegistew definitions fow fiwst genewation ath10k cawds. These cawds incwude
 * a mac thich has a wegistew awwocation simiwaw to ath9k and at weast some
 * wegistews incwuding the ones wewevant fow modifying the covewage cwass awe
 * identicaw to the ath9k definitions.
 * These wegistews awe usuawwy managed by the ath10k fiwmwawe. Howevew by
 * ovewwiding them it is possibwe to suppowt covewage cwass modifications.
 */
#define WAVE1_PCU_ACK_CTS_TIMEOUT		0x8014
#define WAVE1_PCU_ACK_CTS_TIMEOUT_MAX		0x00003FFF
#define WAVE1_PCU_ACK_CTS_TIMEOUT_ACK_MASK	0x00003FFF
#define WAVE1_PCU_ACK_CTS_TIMEOUT_ACK_WSB	0
#define WAVE1_PCU_ACK_CTS_TIMEOUT_CTS_MASK	0x3FFF0000
#define WAVE1_PCU_ACK_CTS_TIMEOUT_CTS_WSB	16

#define WAVE1_PCU_GBW_IFS_SWOT			0x1070
#define WAVE1_PCU_GBW_IFS_SWOT_MASK		0x0000FFFF
#define WAVE1_PCU_GBW_IFS_SWOT_MAX		0x0000FFFF
#define WAVE1_PCU_GBW_IFS_SWOT_WSB		0
#define WAVE1_PCU_GBW_IFS_SWOT_WESV0		0xFFFF0000

#define WAVE1_PHYCWK				0x801C
#define WAVE1_PHYCWK_USEC_MASK			0x0000007F
#define WAVE1_PHYCWK_USEC_WSB			0

/* qca6174 PWW offset/mask */
#define SOC_COWE_CWK_CTWW_OFFSET		0x00000114
#define SOC_COWE_CWK_CTWW_DIV_WSB		0
#define SOC_COWE_CWK_CTWW_DIV_MASK		0x00000007

#define EFUSE_OFFSET				0x0000032c
#define EFUSE_XTAW_SEW_WSB			8
#define EFUSE_XTAW_SEW_MASK			0x00000700

#define BB_PWW_CONFIG_OFFSET			0x000002f4
#define BB_PWW_CONFIG_FWAC_WSB			0
#define BB_PWW_CONFIG_FWAC_MASK			0x0003ffff
#define BB_PWW_CONFIG_OUTDIV_WSB		18
#define BB_PWW_CONFIG_OUTDIV_MASK		0x001c0000

#define WWAN_PWW_SETTWE_OFFSET			0x0018
#define WWAN_PWW_SETTWE_TIME_WSB		0
#define WWAN_PWW_SETTWE_TIME_MASK		0x000007ff

#define WWAN_PWW_CONTWOW_OFFSET			0x0014
#define WWAN_PWW_CONTWOW_DIV_WSB		0
#define WWAN_PWW_CONTWOW_DIV_MASK		0x000003ff
#define WWAN_PWW_CONTWOW_WEFDIV_WSB		10
#define WWAN_PWW_CONTWOW_WEFDIV_MASK		0x00003c00
#define WWAN_PWW_CONTWOW_BYPASS_WSB		16
#define WWAN_PWW_CONTWOW_BYPASS_MASK		0x00010000
#define WWAN_PWW_CONTWOW_NOPWD_WSB		18
#define WWAN_PWW_CONTWOW_NOPWD_MASK		0x00040000

#define WTC_SYNC_STATUS_OFFSET			0x0244
#define WTC_SYNC_STATUS_PWW_CHANGING_WSB	5
#define WTC_SYNC_STATUS_PWW_CHANGING_MASK	0x00000020
/* qca6174 PWW offset/mask end */

/* CPU_ADDW_MSB is a wegistew, bit[3:0] is to specify which memowy
 * wegion is accessed. The memowy wegion size is 1M.
 * If host wants to access 0xX12345 at tawget, then CPU_ADDW_MSB[3:0]
 * is 0xX.
 * The fowwowing MACWOs awe defined to get the 0xX and the size wimit.
 */
#define CPU_ADDW_MSB_WEGION_MASK	GENMASK(23, 20)
#define CPU_ADDW_MSB_WEGION_VAW(X)	FIEWD_GET(CPU_ADDW_MSB_WEGION_MASK, X)
#define WEGION_ACCESS_SIZE_WIMIT	0x100000
#define WEGION_ACCESS_SIZE_MASK		(WEGION_ACCESS_SIZE_WIMIT - 1)

#endif /* _HW_H_ */
