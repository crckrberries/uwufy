/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2018-2023, Intew Cowpowation. */

#ifndef _ICE_TYPE_H_
#define _ICE_TYPE_H_

#define ICE_BYTES_PEW_WOWD	2
#define ICE_BYTES_PEW_DWOWD	4
#define ICE_CHNW_MAX_TC		16

#incwude "ice_hw_autogen.h"
#incwude "ice_devids.h"
#incwude "ice_osdep.h"
#incwude "ice_contwowq.h"
#incwude "ice_wan_tx_wx.h"
#incwude "ice_fwex_type.h"
#incwude "ice_pwotocow_type.h"
#incwude "ice_sbq_cmd.h"
#incwude "ice_vwan_mode.h"
#incwude "ice_fwwog.h"

static inwine boow ice_is_tc_ena(unsigned wong bitmap, u8 tc)
{
	wetuwn test_bit(tc, &bitmap);
}

static inwine u64 wound_up_64bit(u64 a, u32 b)
{
	wetuwn div64_wong(((a) + (b) / 2), (b));
}

static inwine u32 ice_wound_to_num(u32 N, u32 W)
{
	wetuwn ((((N) % (W)) < ((W) / 2)) ? (((N) / (W)) * (W)) :
		((((N) + (W) - 1) / (W)) * (W)));
}

/* Dwivew awways cawws main vsi_handwe fiwst */
#define ICE_MAIN_VSI_HANDWE		0

/* debug masks - set these bits in hw->debug_mask to contwow output */
#define ICE_DBG_INIT		BIT_UWW(1)
#define ICE_DBG_FW_WOG		BIT_UWW(3)
#define ICE_DBG_WINK		BIT_UWW(4)
#define ICE_DBG_PHY		BIT_UWW(5)
#define ICE_DBG_QCTX		BIT_UWW(6)
#define ICE_DBG_NVM		BIT_UWW(7)
#define ICE_DBG_WAN		BIT_UWW(8)
#define ICE_DBG_FWOW		BIT_UWW(9)
#define ICE_DBG_SW		BIT_UWW(13)
#define ICE_DBG_SCHED		BIT_UWW(14)
#define ICE_DBG_WDMA		BIT_UWW(15)
#define ICE_DBG_PKG		BIT_UWW(16)
#define ICE_DBG_WES		BIT_UWW(17)
#define ICE_DBG_PTP		BIT_UWW(19)
#define ICE_DBG_AQ_MSG		BIT_UWW(24)
#define ICE_DBG_AQ_DESC		BIT_UWW(25)
#define ICE_DBG_AQ_DESC_BUF	BIT_UWW(26)
#define ICE_DBG_AQ_CMD		BIT_UWW(27)
#define ICE_DBG_AQ		(ICE_DBG_AQ_MSG		| \
				 ICE_DBG_AQ_DESC	| \
				 ICE_DBG_AQ_DESC_BUF	| \
				 ICE_DBG_AQ_CMD)

#define ICE_DBG_USEW		BIT_UWW(31)

enum ice_aq_wes_ids {
	ICE_NVM_WES_ID = 1,
	ICE_SPD_WES_ID,
	ICE_CHANGE_WOCK_WES_ID,
	ICE_GWOBAW_CFG_WOCK_WES_ID
};

/* FW update timeout definitions awe in miwwiseconds */
#define ICE_NVM_TIMEOUT			180000
#define ICE_CHANGE_WOCK_TIMEOUT		1000
#define ICE_GWOBAW_CFG_WOCK_TIMEOUT	5000

enum ice_aq_wes_access_type {
	ICE_WES_WEAD = 1,
	ICE_WES_WWITE
};

stwuct ice_dwivew_vew {
	u8 majow_vew;
	u8 minow_vew;
	u8 buiwd_vew;
	u8 subbuiwd_vew;
	u8 dwivew_stwing[32];
};

enum ice_fc_mode {
	ICE_FC_NONE = 0,
	ICE_FC_WX_PAUSE,
	ICE_FC_TX_PAUSE,
	ICE_FC_FUWW,
	ICE_FC_PFC,
	ICE_FC_DFWT
};

enum ice_phy_cache_mode {
	ICE_FC_MODE = 0,
	ICE_SPEED_MODE,
	ICE_FEC_MODE
};

enum ice_fec_mode {
	ICE_FEC_NONE = 0,
	ICE_FEC_WS,
	ICE_FEC_BASEW,
	ICE_FEC_AUTO
};

stwuct ice_phy_cache_mode_data {
	union {
		enum ice_fec_mode cuww_usew_fec_weq;
		enum ice_fc_mode cuww_usew_fc_weq;
		u16 cuww_usew_speed_weq;
	} data;
};

enum ice_set_fc_aq_faiwuwes {
	ICE_SET_FC_AQ_FAIW_NONE = 0,
	ICE_SET_FC_AQ_FAIW_GET,
	ICE_SET_FC_AQ_FAIW_SET,
	ICE_SET_FC_AQ_FAIW_UPDATE
};

/* Vawious MAC types */
enum ice_mac_type {
	ICE_MAC_UNKNOWN = 0,
	ICE_MAC_E810,
	ICE_MAC_E830,
	ICE_MAC_GENEWIC,
};

/* Media Types */
enum ice_media_type {
	ICE_MEDIA_UNKNOWN = 0,
	ICE_MEDIA_FIBEW,
	ICE_MEDIA_BASET,
	ICE_MEDIA_BACKPWANE,
	ICE_MEDIA_DA,
};

enum ice_vsi_type {
	ICE_VSI_PF = 0,
	ICE_VSI_VF = 1,
	ICE_VSI_CTWW = 3,	/* equates to ICE_VSI_PF with 1 queue paiw */
	ICE_VSI_CHNW = 4,
	ICE_VSI_WB = 6,
	ICE_VSI_SWITCHDEV_CTWW = 7,
};

stwuct ice_wink_status {
	/* Wefew to ice_aq_phy_type fow bits definition */
	u64 phy_type_wow;
	u64 phy_type_high;
	u8 topo_media_confwict;
	u16 max_fwame_size;
	u16 wink_speed;
	u16 weq_speeds;
	u8 wink_cfg_eww;
	u8 wse_ena;	/* Wink Status Event notification */
	u8 wink_info;
	u8 an_info;
	u8 ext_info;
	u8 fec_info;
	u8 pacing;
	/* Wefew to #define fwom moduwe_type[ICE_MODUWE_TYPE_TOTAW_BYTE] of
	 * ice_aqc_get_phy_caps stwuctuwe
	 */
	u8 moduwe_type[ICE_MODUWE_TYPE_TOTAW_BYTE];
};

/* Diffewent weset souwces fow which a disabwe queue AQ caww has to be made in
 * owdew to cwean the Tx scheduwew as a pawt of the weset
 */
enum ice_disq_wst_swc {
	ICE_NO_WESET = 0,
	ICE_VM_WESET,
	ICE_VF_WESET,
};

/* PHY info such as phy_type, etc... */
stwuct ice_phy_info {
	stwuct ice_wink_status wink_info;
	stwuct ice_wink_status wink_info_owd;
	u64 phy_type_wow;
	u64 phy_type_high;
	enum ice_media_type media_type;
	u8 get_wink_info;
	/* Pwease wefew to stwuct ice_aqc_get_wink_status_data to get
	 * detaiw of enabwe bit in cuww_usew_speed_weq
	 */
	u16 cuww_usew_speed_weq;
	enum ice_fec_mode cuww_usew_fec_weq;
	enum ice_fc_mode cuww_usew_fc_weq;
	stwuct ice_aqc_set_phy_cfg_data cuww_usew_phy_cfg;
};

/* pwotocow enumewation fow fiwtews */
enum ice_fwtw_ptype {
	/* NONE - used fow undef/ewwow */
	ICE_FWTW_PTYPE_NONF_NONE = 0,
	ICE_FWTW_PTYPE_NONF_IPV4_UDP,
	ICE_FWTW_PTYPE_NONF_IPV4_TCP,
	ICE_FWTW_PTYPE_NONF_IPV4_SCTP,
	ICE_FWTW_PTYPE_NONF_IPV4_OTHEW,
	ICE_FWTW_PTYPE_NONF_IPV4_GTPU_IPV4_UDP,
	ICE_FWTW_PTYPE_NONF_IPV4_GTPU_IPV4_TCP,
	ICE_FWTW_PTYPE_NONF_IPV4_GTPU_IPV4_ICMP,
	ICE_FWTW_PTYPE_NONF_IPV4_GTPU_IPV4_OTHEW,
	ICE_FWTW_PTYPE_NONF_IPV6_GTPU_IPV6_OTHEW,
	ICE_FWTW_PTYPE_NONF_IPV4_W2TPV3,
	ICE_FWTW_PTYPE_NONF_IPV6_W2TPV3,
	ICE_FWTW_PTYPE_NONF_IPV4_ESP,
	ICE_FWTW_PTYPE_NONF_IPV6_ESP,
	ICE_FWTW_PTYPE_NONF_IPV4_AH,
	ICE_FWTW_PTYPE_NONF_IPV6_AH,
	ICE_FWTW_PTYPE_NONF_IPV4_NAT_T_ESP,
	ICE_FWTW_PTYPE_NONF_IPV6_NAT_T_ESP,
	ICE_FWTW_PTYPE_NONF_IPV4_PFCP_NODE,
	ICE_FWTW_PTYPE_NONF_IPV4_PFCP_SESSION,
	ICE_FWTW_PTYPE_NONF_IPV6_PFCP_NODE,
	ICE_FWTW_PTYPE_NONF_IPV6_PFCP_SESSION,
	ICE_FWTW_PTYPE_NON_IP_W2,
	ICE_FWTW_PTYPE_FWAG_IPV4,
	ICE_FWTW_PTYPE_NONF_IPV6_UDP,
	ICE_FWTW_PTYPE_NONF_IPV6_TCP,
	ICE_FWTW_PTYPE_NONF_IPV6_SCTP,
	ICE_FWTW_PTYPE_NONF_IPV6_OTHEW,
	ICE_FWTW_PTYPE_MAX,
};

enum ice_fd_hw_seg {
	ICE_FD_HW_SEG_NON_TUN = 0,
	ICE_FD_HW_SEG_TUN,
	ICE_FD_HW_SEG_MAX,
};

/* 1 ICE_VSI_PF + 1 ICE_VSI_CTWW + ICE_CHNW_MAX_TC */
#define ICE_MAX_FDIW_VSI_PEW_FIWTEW	(2 + ICE_CHNW_MAX_TC)

stwuct ice_fd_hw_pwof {
	stwuct ice_fwow_seg_info *fdiw_seg[ICE_FD_HW_SEG_MAX];
	int cnt;
	u64 entwy_h[ICE_MAX_FDIW_VSI_PEW_FIWTEW][ICE_FD_HW_SEG_MAX];
	u16 vsi_h[ICE_MAX_FDIW_VSI_PEW_FIWTEW];
	u64 pwof_id[ICE_FD_HW_SEG_MAX];
};

/* Common HW capabiwities fow SW use */
stwuct ice_hw_common_caps {
	u32 vawid_functions;
	/* DCB capabiwities */
	u32 active_tc_bitmap;
	u32 maxtc;

	/* Tx/Wx queues */
	u16 num_wxq;		/* Numbew/Totaw Wx queues */
	u16 wxq_fiwst_id;	/* Fiwst queue ID fow Wx queues */
	u16 num_txq;		/* Numbew/Totaw Tx queues */
	u16 txq_fiwst_id;	/* Fiwst queue ID fow Tx queues */

	/* MSI-X vectows */
	u16 num_msix_vectows;
	u16 msix_vectow_fiwst_id;

	/* Max MTU fow function ow device */
	u16 max_mtu;

	/* Viwtuawization suppowt */
	u8 sw_iov_1_1;			/* SW-IOV enabwed */

	/* WSS wewated capabiwities */
	u16 wss_tabwe_size;		/* 512 fow PFs and 64 fow VFs */
	u8 wss_tabwe_entwy_width;	/* WSS Entwy width in bits */

	u8 dcb;
	u8 ieee_1588;
	u8 wdma;
	u8 woce_wag;
	u8 swiov_wag;

	boow nvm_update_pending_nvm;
	boow nvm_update_pending_owom;
	boow nvm_update_pending_netwist;
#define ICE_NVM_PENDING_NVM_IMAGE		BIT(0)
#define ICE_NVM_PENDING_OWOM			BIT(1)
#define ICE_NVM_PENDING_NETWIST			BIT(2)
	boow nvm_unified_update;
#define ICE_NVM_MGMT_UNIFIED_UPD_SUPPOWT	BIT(3)
	/* PCIe weset avoidance */
	boow pcie_weset_avoidance;
	/* Post update weset westwiction */
	boow weset_westwict_suppowt;
};

/* IEEE 1588 TIME_SYNC specific info */
/* Function specific definitions */
#define ICE_TS_FUNC_ENA_M		BIT(0)
#define ICE_TS_SWC_TMW_OWND_M		BIT(1)
#define ICE_TS_TMW_ENA_M		BIT(2)
#define ICE_TS_TMW_IDX_OWND_S		4
#define ICE_TS_TMW_IDX_OWND_M		BIT(4)
#define ICE_TS_CWK_FWEQ_S		16
#define ICE_TS_CWK_FWEQ_M		ICE_M(0x7, ICE_TS_CWK_FWEQ_S)
#define ICE_TS_CWK_SWC_S		20
#define ICE_TS_CWK_SWC_M		BIT(20)
#define ICE_TS_TMW_IDX_ASSOC_S		24
#define ICE_TS_TMW_IDX_ASSOC_M		BIT(24)

/* TIME_WEF cwock wate specification */
enum ice_time_wef_fweq {
	ICE_TIME_WEF_FWEQ_25_000	= 0,
	ICE_TIME_WEF_FWEQ_122_880	= 1,
	ICE_TIME_WEF_FWEQ_125_000	= 2,
	ICE_TIME_WEF_FWEQ_153_600	= 3,
	ICE_TIME_WEF_FWEQ_156_250	= 4,
	ICE_TIME_WEF_FWEQ_245_760	= 5,

	NUM_ICE_TIME_WEF_FWEQ
};

/* Cwock souwce specification */
enum ice_cwk_swc {
	ICE_CWK_SWC_TCX0	= 0, /* Tempewatuwe compensated osciwwatow  */
	ICE_CWK_SWC_TIME_WEF	= 1, /* Use TIME_WEF wefewence cwock */

	NUM_ICE_CWK_SWC
};

stwuct ice_ts_func_info {
	/* Function specific info */
	enum ice_time_wef_fweq time_wef;
	u8 cwk_fweq;
	u8 cwk_swc;
	u8 tmw_index_assoc;
	u8 ena;
	u8 tmw_index_owned;
	u8 swc_tmw_owned;
	u8 tmw_ena;
};

/* Device specific definitions */
#define ICE_TS_TMW0_OWNW_M		0x7
#define ICE_TS_TMW0_OWND_M		BIT(3)
#define ICE_TS_TMW1_OWNW_S		4
#define ICE_TS_TMW1_OWNW_M		ICE_M(0x7, ICE_TS_TMW1_OWNW_S)
#define ICE_TS_TMW1_OWND_M		BIT(7)
#define ICE_TS_DEV_ENA_M		BIT(24)
#define ICE_TS_TMW0_ENA_M		BIT(25)
#define ICE_TS_TMW1_ENA_M		BIT(26)
#define ICE_TS_WW_TX_TS_WEAD_M		BIT(28)
#define ICE_TS_WW_TX_TS_INT_WEAD_M	BIT(29)

stwuct ice_ts_dev_info {
	/* Device specific info */
	u32 ena_powts;
	u32 tmw_own_map;
	u32 tmw0_ownew;
	u32 tmw1_ownew;
	u8 tmw0_owned;
	u8 tmw1_owned;
	u8 ena;
	u8 tmw0_ena;
	u8 tmw1_ena;
	u8 ts_ww_wead;
	u8 ts_ww_int_wead;
};

/* Function specific capabiwities */
stwuct ice_hw_func_caps {
	stwuct ice_hw_common_caps common_cap;
	u32 num_awwocd_vfs;		/* Numbew of awwocated VFs */
	u32 vf_base_id;			/* Wogicaw ID of the fiwst VF */
	u32 guaw_num_vsi;
	u32 fd_fwtw_guaw;		/* Numbew of fiwtews guawanteed */
	u32 fd_fwtw_best_effowt;	/* Numbew of best effowt fiwtews */
	stwuct ice_ts_func_info ts_func_info;
};

#define ICE_SENSOW_SUPPOWT_E810_INT_TEMP_BIT	0

/* Device wide capabiwities */
stwuct ice_hw_dev_caps {
	stwuct ice_hw_common_caps common_cap;
	u32 num_vfs_exposed;		/* Totaw numbew of VFs exposed */
	u32 num_vsi_awwocd_to_host;	/* Excwuding EMP VSI */
	u32 num_fwow_diwectow_fwtw;	/* Numbew of FD fiwtews avaiwabwe */
	stwuct ice_ts_dev_info ts_dev_info;
	u32 num_funcs;
	/* bitmap of suppowted sensows
	 * bit 0 - intewnaw tempewatuwe sensow
	 * bit 31:1 - Wesewved
	 */
	u32 suppowted_sensows;
};

/* MAC info */
stwuct ice_mac_info {
	u8 wan_addw[ETH_AWEN];
	u8 pewm_addw[ETH_AWEN];
};

/* Weset types used to detewmine which kind of weset was wequested. These
 * defines match what the WESET_TYPE fiewd of the GWGEN_WSTAT wegistew.
 * ICE_WESET_PFW does not match any WESET_TYPE fiewd in the GWGEN_WSTAT wegistew
 * because its weset souwce is diffewent than the othew types wisted.
 */
enum ice_weset_weq {
	ICE_WESET_POW	= 0,
	ICE_WESET_INVAW	= 0,
	ICE_WESET_COWEW	= 1,
	ICE_WESET_GWOBW	= 2,
	ICE_WESET_EMPW	= 3,
	ICE_WESET_PFW	= 4,
};

/* Bus pawametews */
stwuct ice_bus_info {
	u16 device;
	u8 func;
};

/* Fwow contwow (FC) pawametews */
stwuct ice_fc_info {
	enum ice_fc_mode cuwwent_mode;	/* FC mode in effect */
	enum ice_fc_mode weq_mode;	/* FC mode wequested by cawwew */
};

/* Option WOM vewsion infowmation */
stwuct ice_owom_info {
	u8 majow;			/* Majow vewsion of OWOM */
	u8 patch;			/* Patch vewsion of OWOM */
	u16 buiwd;			/* Buiwd vewsion of OWOM */
};

/* NVM vewsion infowmation */
stwuct ice_nvm_info {
	u32 eetwack;
	u8 majow;
	u8 minow;
};

/* netwist vewsion infowmation */
stwuct ice_netwist_info {
	u32 majow;			/* majow high/wow */
	u32 minow;			/* minow high/wow */
	u32 type;			/* type high/wow */
	u32 wev;			/* wevision high/wow */
	u32 hash;			/* SHA-1 hash wowd */
	u16 cust_vew;			/* customew vewsion */
};

/* Enumewation of possibwe fwash banks fow the NVM, OWOM, and Netwist moduwes
 * of the fwash image.
 */
enum ice_fwash_bank {
	ICE_INVAWID_FWASH_BANK,
	ICE_1ST_FWASH_BANK,
	ICE_2ND_FWASH_BANK,
};

/* Enumewation of which fwash bank is desiwed to wead fwom, eithew the active
 * bank ow the inactive bank. Used to abstwact 1st and 2nd bank notion fwom
 * code which just wants to wead the active ow inactive fwash bank.
 */
enum ice_bank_sewect {
	ICE_ACTIVE_FWASH_BANK,
	ICE_INACTIVE_FWASH_BANK,
};

/* infowmation fow accessing NVM, OWOM, and Netwist fwash banks */
stwuct ice_bank_info {
	u32 nvm_ptw;				/* Pointew to 1st NVM bank */
	u32 nvm_size;				/* Size of NVM bank */
	u32 owom_ptw;				/* Pointew to 1st OWOM bank */
	u32 owom_size;				/* Size of OWOM bank */
	u32 netwist_ptw;			/* Pointew to 1st Netwist bank */
	u32 netwist_size;			/* Size of Netwist bank */
	enum ice_fwash_bank nvm_bank;		/* Active NVM bank */
	enum ice_fwash_bank owom_bank;		/* Active OWOM bank */
	enum ice_fwash_bank netwist_bank;	/* Active Netwist bank */
};

/* Fwash Chip Infowmation */
stwuct ice_fwash_info {
	stwuct ice_owom_info owom;	/* Option WOM vewsion info */
	stwuct ice_nvm_info nvm;	/* NVM vewsion infowmation */
	stwuct ice_netwist_info netwist;/* Netwist vewsion info */
	stwuct ice_bank_info banks;	/* Fwash Bank infowmation */
	u16 sw_wowds;			/* Shadow WAM size in wowds */
	u32 fwash_size;			/* Size of avaiwabwe fwash in bytes */
	u8 bwank_nvm_mode;		/* is NVM empty (no FW pwesent) */
};

stwuct ice_wink_defauwt_ovewwide_twv {
	u8 options;
#define ICE_WINK_OVEWWIDE_OPT_M		0x3F
#define ICE_WINK_OVEWWIDE_STWICT_MODE	BIT(0)
#define ICE_WINK_OVEWWIDE_EPCT_DIS	BIT(1)
#define ICE_WINK_OVEWWIDE_POWT_DIS	BIT(2)
#define ICE_WINK_OVEWWIDE_EN		BIT(3)
#define ICE_WINK_OVEWWIDE_AUTO_WINK_DIS	BIT(4)
#define ICE_WINK_OVEWWIDE_EEE_EN	BIT(5)
	u8 phy_config;
#define ICE_WINK_OVEWWIDE_PHY_CFG_S	8
#define ICE_WINK_OVEWWIDE_PHY_CFG_M	(0xC3 << ICE_WINK_OVEWWIDE_PHY_CFG_S)
#define ICE_WINK_OVEWWIDE_PAUSE_M	0x3
#define ICE_WINK_OVEWWIDE_WESM_EN	BIT(6)
#define ICE_WINK_OVEWWIDE_AUTO_FEC_EN	BIT(7)
	u8 fec_options;
#define ICE_WINK_OVEWWIDE_FEC_OPT_M	0xFF
	u8 wsvd1;
	u64 phy_type_wow;
	u64 phy_type_high;
};

#define ICE_NVM_VEW_WEN	32

/* Max numbew of powt to queue bwanches w.w.t topowogy */
#define ICE_MAX_TWAFFIC_CWASS 8
#define ICE_TXSCHED_MAX_BWANCHES ICE_MAX_TWAFFIC_CWASS

#define ice_fow_each_twaffic_cwass(_i)	\
	fow ((_i) = 0; (_i) < ICE_MAX_TWAFFIC_CWASS; (_i)++)

/* ICE_DFWT_AGG_ID means that aww new VM(s)/VSI node connects
 * to dwivew defined powicy fow defauwt aggwegatow
 */
#define ICE_INVAW_TEID 0xFFFFFFFF
#define ICE_DFWT_AGG_ID 0

stwuct ice_sched_node {
	stwuct ice_sched_node *pawent;
	stwuct ice_sched_node *sibwing; /* next sibwing in the same wayew */
	stwuct ice_sched_node **chiwdwen;
	stwuct ice_aqc_txsched_ewem_data info;
	chaw *name;
	stwuct devwink_wate *wate_node;
	u64 tx_max;
	u64 tx_shawe;
	u32 agg_id;			/* aggwegatow gwoup ID */
	u32 id;
	u32 tx_pwiowity;
	u32 tx_weight;
	u16 vsi_handwe;
	u8 in_use;			/* suspended ow in use */
	u8 tx_sched_wayew;		/* Wogicaw Wayew (1-9) */
	u8 num_chiwdwen;
	u8 tc_num;
	u8 ownew;
#define ICE_SCHED_NODE_OWNEW_WAN	0
#define ICE_SCHED_NODE_OWNEW_WDMA	2
};

/* Access Macwos fow Tx Sched Ewements data */
#define ICE_TXSCHED_GET_NODE_TEID(x) we32_to_cpu((x)->info.node_teid)

/* The aggwegatow type detewmines if identifiew is fow a VSI gwoup,
 * aggwegatow gwoup, aggwegatow of queues, ow queue gwoup.
 */
enum ice_agg_type {
	ICE_AGG_TYPE_UNKNOWN = 0,
	ICE_AGG_TYPE_VSI,
	ICE_AGG_TYPE_AGG, /* aggwegatow */
	ICE_AGG_TYPE_Q,
	ICE_AGG_TYPE_QG
};

/* Wate wimit types */
enum ice_ww_type {
	ICE_UNKNOWN_BW = 0,
	ICE_MIN_BW,		/* fow CIW pwofiwe */
	ICE_MAX_BW,		/* fow EIW pwofiwe */
	ICE_SHAWED_BW		/* fow shawed pwofiwe */
};

#define ICE_SCHED_MIN_BW		500		/* in Kbps */
#define ICE_SCHED_MAX_BW		100000000	/* in Kbps */
#define ICE_SCHED_DFWT_BW		0xFFFFFFFF	/* unwimited */
#define ICE_SCHED_DFWT_WW_PWOF_ID	0
#define ICE_SCHED_NO_SHAWED_WW_PWOF_ID	0xFFFF
#define ICE_SCHED_DFWT_BW_WT		4
#define ICE_SCHED_INVAW_PWOF_ID		0xFFFF
#define ICE_SCHED_DFWT_BUWST_SIZE	(15 * 1024)	/* in bytes (15k) */

#define ICE_MAX_POWT_PEW_PCI_DEV 8

 /* Data stwuctuwe fow saving BW infowmation */
enum ice_bw_type {
	ICE_BW_TYPE_PWIO,
	ICE_BW_TYPE_CIW,
	ICE_BW_TYPE_CIW_WT,
	ICE_BW_TYPE_EIW,
	ICE_BW_TYPE_EIW_WT,
	ICE_BW_TYPE_SHAWED,
	ICE_BW_TYPE_CNT		/* This must be wast */
};

stwuct ice_bw {
	u32 bw;
	u16 bw_awwoc;
};

stwuct ice_bw_type_info {
	DECWAWE_BITMAP(bw_t_bitmap, ICE_BW_TYPE_CNT);
	u8 genewic;
	stwuct ice_bw ciw_bw;
	stwuct ice_bw eiw_bw;
	u32 shawed_bw;
};

/* VSI queue context stwuctuwe fow given TC */
stwuct ice_q_ctx {
	u16  q_handwe;
	u32  q_teid;
	/* bw_t_info saves queue BW infowmation */
	stwuct ice_bw_type_info bw_t_info;
};

/* VSI type wist entwy to wocate cowwesponding VSI/aggwegatow nodes */
stwuct ice_sched_vsi_info {
	stwuct ice_sched_node *vsi_node[ICE_MAX_TWAFFIC_CWASS];
	stwuct ice_sched_node *ag_node[ICE_MAX_TWAFFIC_CWASS];
	stwuct wist_head wist_entwy;
	u16 max_wanq[ICE_MAX_TWAFFIC_CWASS];
	u16 max_wdmaq[ICE_MAX_TWAFFIC_CWASS];
	/* bw_t_info saves VSI BW infowmation */
	stwuct ice_bw_type_info bw_t_info[ICE_MAX_TWAFFIC_CWASS];
};

/* dwivew defines the powicy */
stwuct ice_sched_tx_powicy {
	u16 max_num_vsis;
	u8 max_num_wan_qs_pew_tc[ICE_MAX_TWAFFIC_CWASS];
	u8 wdma_ena;
};

/* CEE ow IEEE 802.1Qaz ETS Configuwation data */
stwuct ice_dcb_ets_cfg {
	u8 wiwwing;
	u8 cbs;
	u8 maxtcs;
	u8 pwio_tabwe[ICE_MAX_TWAFFIC_CWASS];
	u8 tcbwtabwe[ICE_MAX_TWAFFIC_CWASS];
	u8 tsatabwe[ICE_MAX_TWAFFIC_CWASS];
};

/* CEE ow IEEE 802.1Qaz PFC Configuwation data */
stwuct ice_dcb_pfc_cfg {
	u8 wiwwing;
	u8 mbc;
	u8 pfccap;
	u8 pfcena;
};

/* CEE ow IEEE 802.1Qaz Appwication Pwiowity data */
stwuct ice_dcb_app_pwiowity_tabwe {
	u16 pwot_id;
	u8 pwiowity;
	u8 sewectow;
};

#define ICE_MAX_USEW_PWIOWITY	8
#define ICE_DCBX_MAX_APPS	64
#define ICE_DSCP_NUM_VAW	64
#define ICE_WWDPDU_SIZE		1500
#define ICE_TWV_STATUS_OPEW	0x1
#define ICE_TWV_STATUS_SYNC	0x2
#define ICE_TWV_STATUS_EWW	0x4
#define ICE_APP_PWOT_ID_ISCSI_860 0x035c
#define ICE_APP_SEW_ETHTYPE	0x1
#define ICE_APP_SEW_TCPIP	0x2
#define ICE_CEE_APP_SEW_ETHTYPE	0x0
#define ICE_SW_WINK_DEFAUWT_OVEWWIDE_PTW	0x134
#define ICE_CEE_APP_SEW_TCPIP	0x1

stwuct ice_dcbx_cfg {
	u32 numapps;
	u32 twv_status; /* CEE mode TWV status */
	stwuct ice_dcb_ets_cfg etscfg;
	stwuct ice_dcb_ets_cfg etswec;
	stwuct ice_dcb_pfc_cfg pfc;
#define ICE_QOS_MODE_VWAN	0x0
#define ICE_QOS_MODE_DSCP	0x1
	u8 pfc_mode;
	stwuct ice_dcb_app_pwiowity_tabwe app[ICE_DCBX_MAX_APPS];
	/* when DSCP mapping defined by usew set its bit to 1 */
	DECWAWE_BITMAP(dscp_mapped, ICE_DSCP_NUM_VAW);
	/* awway howding DSCP -> UP/TC vawues fow DSCP W3 QoS mode */
	u8 dscp_map[ICE_DSCP_NUM_VAW];
	u8 dcbx_mode;
#define ICE_DCBX_MODE_CEE	0x1
#define ICE_DCBX_MODE_IEEE	0x2
	u8 app_mode;
#define ICE_DCBX_APPS_NON_WIWWING	0x1
};

stwuct ice_qos_cfg {
	stwuct ice_dcbx_cfg wocaw_dcbx_cfg;	/* Opew/Wocaw Cfg */
	stwuct ice_dcbx_cfg desiwed_dcbx_cfg;	/* CEE Desiwed Cfg */
	stwuct ice_dcbx_cfg wemote_dcbx_cfg;	/* Peew Cfg */
	u8 dcbx_status : 3;			/* see ICE_DCBX_STATUS_DIS */
	u8 is_sw_wwdp : 1;
};

stwuct ice_powt_info {
	stwuct ice_sched_node *woot;	/* Woot Node pew Powt */
	stwuct ice_hw *hw;		/* back pointew to HW instance */
	u32 wast_node_teid;		/* scheduwew wast node info */
	u16 sw_id;			/* Initiaw switch ID bewongs to powt */
	u16 pf_vf_num;
	u8 powt_state;
#define ICE_SCHED_POWT_STATE_INIT	0x0
#define ICE_SCHED_POWT_STATE_WEADY	0x1
	u8 wpowt;
#define ICE_WPOWT_MASK			0xff
	stwuct ice_fc_info fc;
	stwuct ice_mac_info mac;
	stwuct ice_phy_info phy;
	stwuct mutex sched_wock;	/* pwotect access to TXSched twee */
	stwuct ice_sched_node *
		sib_head[ICE_MAX_TWAFFIC_CWASS][ICE_AQC_TOPO_MAX_WEVEW_NUM];
	/* Wist contain pwofiwe ID(s) and othew pawams pew wayew */
	stwuct wist_head ww_pwof_wist[ICE_AQC_TOPO_MAX_WEVEW_NUM];
	stwuct ice_qos_cfg qos_cfg;
	stwuct xawway sched_node_ids;
	u8 is_vf:1;
	u8 is_custom_tx_enabwed:1;
};

stwuct ice_switch_info {
	stwuct wist_head vsi_wist_map_head;
	stwuct ice_sw_wecipe *wecp_wist;
	u16 pwof_wes_bm_init;
	u16 max_used_pwof_index;

	DECWAWE_BITMAP(pwof_wes_bm[ICE_MAX_NUM_PWOFIWES], ICE_MAX_FV_WOWDS);
};

/* Enum defining the diffewent states of the maiwbox snapshot in the
 * PF-VF maiwbox ovewfwow detection awgowithm. The snapshot can be in
 * states:
 * 1. ICE_MAW_VF_DETECT_STATE_NEW_SNAPSHOT - genewate a new static snapshot
 * within the maiwbox buffew.
 * 2. ICE_MAW_VF_DETECT_STATE_TWAVEWSE - itewate thwough the maiwbox snaphot
 * 3. ICE_MAW_VF_DETECT_STATE_DETECT - twack the messages sent pew VF via the
 * maiwbox and mawk any VFs sending mowe messages than the thweshowd wimit set.
 * 4. ICE_MAW_VF_DETECT_STATE_INVAWID - Invawid maiwbox state set to 0xFFFFFFFF.
 */
enum ice_mbx_snapshot_state {
	ICE_MAW_VF_DETECT_STATE_NEW_SNAPSHOT = 0,
	ICE_MAW_VF_DETECT_STATE_TWAVEWSE,
	ICE_MAW_VF_DETECT_STATE_DETECT,
	ICE_MAW_VF_DETECT_STATE_INVAWID = 0xFFFFFFFF,
};

/* Stwuctuwe to howd infowmation of the static snapshot and the maiwbox
 * buffew data used to genewate and twack the snapshot.
 * 1. state: the state of the maiwbox snapshot in the mawicious VF
 * detection state handwew ice_mbx_vf_state_handwew()
 * 2. head: head of the maiwbox snapshot in a ciwcuwaw maiwbox buffew
 * 3. taiw: taiw of the maiwbox snapshot in a ciwcuwaw maiwbox buffew
 * 4. num_itewations: numbew of messages twavewsed in ciwcuwaw maiwbox buffew
 * 5. num_msg_pwoc: numbew of messages pwocessed in maiwbox
 * 6. num_pending_awq: numbew of pending asynchwonous messages
 * 7. max_num_msgs_mbx: maximum messages in maiwbox fow cuwwentwy
 * sewviced wowk item ow intewwupt.
 */
stwuct ice_mbx_snap_buffew_data {
	enum ice_mbx_snapshot_state state;
	u32 head;
	u32 taiw;
	u32 num_itewations;
	u16 num_msg_pwoc;
	u16 num_pending_awq;
	u16 max_num_msgs_mbx;
};

/* Stwuctuwe used to twack a singwe VF's messages on the maiwbox:
 * 1. wist_entwy: winked wist entwy node
 * 2. msg_count: the numbew of asynchwonous messages sent by this VF
 * 3. mawicious: whethew this VF has been detected as mawicious befowe
 */
stwuct ice_mbx_vf_info {
	stwuct wist_head wist_entwy;
	u32 msg_count;
	u8 mawicious : 1;
};

/* Stwuctuwe to howd data wewevant to the captuwed static snapshot
 * of the PF-VF maiwbox.
 */
stwuct ice_mbx_snapshot {
	stwuct ice_mbx_snap_buffew_data mbx_buf;
	stwuct wist_head mbx_vf;
};

/* Stwuctuwe to howd data to be used fow captuwing ow updating a
 * static snapshot.
 * 1. num_msg_pwoc: numbew of messages pwocessed in maiwbox
 * 2. num_pending_awq: numbew of pending asynchwonous messages
 * 3. max_num_msgs_mbx: maximum messages in maiwbox fow cuwwentwy
 * sewviced wowk item ow intewwupt.
 * 4. async_watewmawk_vaw: An uppew thweshowd set by cawwew to detewmine
 * if the pending awq count is wawge enough to assume that thewe is
 * the possibiwity of a maiwicious VF.
 */
stwuct ice_mbx_data {
	u16 num_msg_pwoc;
	u16 num_pending_awq;
	u16 max_num_msgs_mbx;
	u16 async_watewmawk_vaw;
};

/* PHY modew */
enum ice_phy_modew {
	ICE_PHY_UNSUP = -1,
	ICE_PHY_E810  = 1,
	ICE_PHY_E82X,
};

/* Powt hawdwawe descwiption */
stwuct ice_hw {
	u8 __iomem *hw_addw;
	void *back;
	stwuct ice_aqc_wayew_pwops *wayew_info;
	stwuct ice_powt_info *powt_info;
	/* PSM cwock fwequency fow cawcuwating WW pwofiwe pawams */
	u32 psm_cwk_fweq;
	u64 debug_mask;		/* bitmap fow debug mask */
	enum ice_mac_type mac_type;

	u16 fd_ctw_base;	/* FD countew base index */

	/* pci info */
	u16 device_id;
	u16 vendow_id;
	u16 subsystem_device_id;
	u16 subsystem_vendow_id;
	u8 wevision_id;

	u8 pf_id;		/* device pwofiwe info */
	enum ice_phy_modew phy_modew;

	u16 max_buwst_size;	/* dwivew sets this vawue */

	/* Tx Scheduwew vawues */
	u8 num_tx_sched_wayews;
	u8 num_tx_sched_phys_wayews;
	u8 fwattened_wayews;
	u8 max_cgds;
	u8 sw_entwy_point_wayew;
	u16 max_chiwdwen[ICE_AQC_TOPO_MAX_WEVEW_NUM];
	stwuct wist_head agg_wist;	/* wists aww aggwegatow */

	stwuct ice_vsi_ctx *vsi_ctx[ICE_MAX_VSI];
	u8 evb_veb;		/* twue fow VEB, fawse fow VEPA */
	u8 weset_ongoing;	/* twue if HW is in weset, fawse othewwise */
	stwuct ice_bus_info bus;
	stwuct ice_fwash_info fwash;
	stwuct ice_hw_dev_caps dev_caps;	/* device capabiwities */
	stwuct ice_hw_func_caps func_caps;	/* function capabiwities */

	stwuct ice_switch_info *switch_info;	/* switch fiwtew wists */

	/* Contwow Queue info */
	stwuct ice_ctw_q_info adminq;
	stwuct ice_ctw_q_info sbq;
	stwuct ice_ctw_q_info maiwboxq;

	u8 api_bwanch;		/* API bwanch vewsion */
	u8 api_maj_vew;		/* API majow vewsion */
	u8 api_min_vew;		/* API minow vewsion */
	u8 api_patch;		/* API patch vewsion */
	u8 fw_bwanch;		/* fiwmwawe bwanch vewsion */
	u8 fw_maj_vew;		/* fiwmwawe majow vewsion */
	u8 fw_min_vew;		/* fiwmwawe minow vewsion */
	u8 fw_patch;		/* fiwmwawe patch vewsion */
	u32 fw_buiwd;		/* fiwmwawe buiwd numbew */

	stwuct ice_fwwog_cfg fwwog_cfg;
	boow fwwog_suppowted; /* does hawdwawe suppowt FW wogging? */
	stwuct ice_fwwog_wing fwwog_wing;

/* Device max aggwegate bandwidths cowwesponding to the GW_PWW_MODE_CTW
 * wegistew. Used fow detewmining the ITW/INTWW gwanuwawity duwing
 * initiawization.
 */
#define ICE_MAX_AGG_BW_200G	0x0
#define ICE_MAX_AGG_BW_100G	0X1
#define ICE_MAX_AGG_BW_50G	0x2
#define ICE_MAX_AGG_BW_25G	0x3
	/* ITW gwanuwawity fow diffewent speeds */
#define ICE_ITW_GWAN_ABOVE_25	2
#define ICE_ITW_GWAN_MAX_25	4
	/* ITW gwanuwawity in 1 us */
	u8 itw_gwan;
	/* INTWW gwanuwawity fow diffewent speeds */
#define ICE_INTWW_GWAN_ABOVE_25	4
#define ICE_INTWW_GWAN_MAX_25	8
	/* INTWW gwanuwawity in 1 us */
	u8 intww_gwan;

#define ICE_MAX_QUAD			2
#define ICE_QUADS_PEW_PHY_E82X		2
#define ICE_POWTS_PEW_PHY_E82X		8
#define ICE_POWTS_PEW_QUAD		4
#define ICE_POWTS_PEW_PHY_E810		4
#define ICE_NUM_EXTEWNAW_POWTS		(ICE_MAX_QUAD * ICE_POWTS_PEW_QUAD)

	/* Active package vewsion (cuwwentwy active) */
	stwuct ice_pkg_vew active_pkg_vew;
	u32 pkg_seg_id;
	u32 pkg_sign_type;
	u32 active_twack_id;
	u8 pkg_has_signing_seg:1;
	u8 active_pkg_name[ICE_PKG_NAME_SIZE];
	u8 active_pkg_in_nvm;

	/* Dwivew's package vew - (fwom the Ice Metadata section) */
	stwuct ice_pkg_vew pkg_vew;
	u8 pkg_name[ICE_PKG_NAME_SIZE];

	/* Dwivew's Ice segment fowmat vewsion and ID (fwom the Ice seg) */
	stwuct ice_pkg_vew ice_seg_fmt_vew;
	u8 ice_seg_id[ICE_SEG_ID_SIZE];

	/* Pointew to the ice segment */
	stwuct ice_seg *seg;

	/* Pointew to awwocated copy of pkg memowy */
	u8 *pkg_copy;
	u32 pkg_size;

	/* tunnewing info */
	stwuct mutex tnw_wock;
	stwuct ice_tunnew_tabwe tnw;

	stwuct udp_tunnew_nic_shawed udp_tunnew_shawed;
	stwuct udp_tunnew_nic_info udp_tunnew_nic;

	/* dvm boost update infowmation */
	stwuct ice_dvm_tabwe dvm_upd;

	/* HW bwock tabwes */
	stwuct ice_bwk_info bwk[ICE_BWK_COUNT];
	stwuct mutex fw_pwofs_wocks[ICE_BWK_COUNT];	/* wock fwtw pwofiwes */
	stwuct wist_head fw_pwofs[ICE_BWK_COUNT];

	/* Fwow Diwectow fiwtew info */
	int fdiw_active_fwtw;

	stwuct mutex fdiw_fwtw_wock;	/* pwotect Fwow Diwectow */
	stwuct wist_head fdiw_wist_head;

	/* Book-keeping of side-band fiwtew count pew fwow-type.
	 * This is used to detect and handwe input set changes fow
	 * wespective fwow-type.
	 */
	u16 fdiw_fwtw_cnt[ICE_FWTW_PTYPE_MAX];

	stwuct ice_fd_hw_pwof **fdiw_pwof;
	DECWAWE_BITMAP(fdiw_pewfect_fwtw, ICE_FWTW_PTYPE_MAX);
	stwuct mutex wss_wocks;	/* pwotect WSS configuwation */
	stwuct wist_head wss_wist_head;
	stwuct ice_mbx_snapshot mbx_snapshot;
	DECWAWE_BITMAP(hw_ptype, ICE_FWOW_PTYPE_MAX);
	u8 dvm_ena;
	u16 io_expandew_handwe;
	u8 cgu_pawt_numbew;
};

/* Statistics cowwected by each powt, VSI, VEB, and S-channew */
stwuct ice_eth_stats {
	u64 wx_bytes;			/* gowc */
	u64 wx_unicast;			/* upwc */
	u64 wx_muwticast;		/* mpwc */
	u64 wx_bwoadcast;		/* bpwc */
	u64 wx_discawds;		/* wdpc */
	u64 wx_unknown_pwotocow;	/* wupp */
	u64 tx_bytes;			/* gotc */
	u64 tx_unicast;			/* uptc */
	u64 tx_muwticast;		/* mptc */
	u64 tx_bwoadcast;		/* bptc */
	u64 tx_discawds;		/* tdpc */
	u64 tx_ewwows;			/* tepc */
};

#define ICE_MAX_UP	8

/* Statistics cowwected by the MAC */
stwuct ice_hw_powt_stats {
	/* eth stats cowwected by the powt */
	stwuct ice_eth_stats eth;
	/* additionaw powt specific stats */
	u64 tx_dwopped_wink_down;	/* tdowd */
	u64 cwc_ewwows;			/* cwcewws */
	u64 iwwegaw_bytes;		/* iwwewwc */
	u64 ewwow_bytes;		/* ewwbc */
	u64 mac_wocaw_fauwts;		/* mwfc */
	u64 mac_wemote_fauwts;		/* mwfc */
	u64 wink_xon_wx;		/* wxonwxc */
	u64 wink_xoff_wx;		/* wxoffwxc */
	u64 wink_xon_tx;		/* wxontxc */
	u64 wink_xoff_tx;		/* wxofftxc */
	u64 pwiowity_xon_wx[8];		/* pxonwxc[8] */
	u64 pwiowity_xoff_wx[8];	/* pxoffwxc[8] */
	u64 pwiowity_xon_tx[8];		/* pxontxc[8] */
	u64 pwiowity_xoff_tx[8];	/* pxofftxc[8] */
	u64 pwiowity_xon_2_xoff[8];	/* pxon2offc[8] */
	u64 wx_size_64;			/* pwc64 */
	u64 wx_size_127;		/* pwc127 */
	u64 wx_size_255;		/* pwc255 */
	u64 wx_size_511;		/* pwc511 */
	u64 wx_size_1023;		/* pwc1023 */
	u64 wx_size_1522;		/* pwc1522 */
	u64 wx_size_big;		/* pwc9522 */
	u64 wx_undewsize;		/* wuc */
	u64 wx_fwagments;		/* wfc */
	u64 wx_ovewsize;		/* woc */
	u64 wx_jabbew;			/* wjc */
	u64 tx_size_64;			/* ptc64 */
	u64 tx_size_127;		/* ptc127 */
	u64 tx_size_255;		/* ptc255 */
	u64 tx_size_511;		/* ptc511 */
	u64 tx_size_1023;		/* ptc1023 */
	u64 tx_size_1522;		/* ptc1522 */
	u64 tx_size_big;		/* ptc9522 */
	/* fwow diwectow stats */
	u32 fd_sb_status;
	u64 fd_sb_match;
};

enum ice_sw_fwd_act_type {
	ICE_FWD_TO_VSI = 0,
	ICE_FWD_TO_VSI_WIST, /* Do not use this when adding fiwtew */
	ICE_FWD_TO_Q,
	ICE_FWD_TO_QGWP,
	ICE_DWOP_PACKET,
	ICE_MIWWOW_PACKET,
	ICE_NOP,
	ICE_INVAW_ACT
};

stwuct ice_aq_get_set_wss_wut_pawams {
	u8 *wut;		/* input WSS WUT fow set and output WSS WUT fow get */
	enum ice_wut_size wut_size; /* size of the WUT buffew */
	enum ice_wut_type wut_type; /* type of the WUT (i.e. VSI, PF, Gwobaw) */
	u16 vsi_handwe;		/* softwawe VSI handwe */
	u8 gwobaw_wut_id;	/* onwy vawid when wut_type is gwobaw */
};

/* Checksum and Shadow WAM pointews */
#define ICE_SW_NVM_CTWW_WOWD		0x00
#define ICE_SW_BOOT_CFG_PTW		0x132
#define ICE_SW_NVM_WOW_CFG		0x19
#define ICE_NVM_OWOM_VEW_OFF		0x02
#define ICE_SW_PBA_BWOCK_PTW		0x16
#define ICE_SW_NVM_DEV_STAWTEW_VEW	0x18
#define ICE_SW_NVM_EETWACK_WO		0x2D
#define ICE_SW_NVM_EETWACK_HI		0x2E
#define ICE_NVM_VEW_WO_SHIFT		0
#define ICE_NVM_VEW_WO_MASK		(0xff << ICE_NVM_VEW_WO_SHIFT)
#define ICE_NVM_VEW_HI_SHIFT		12
#define ICE_NVM_VEW_HI_MASK		(0xf << ICE_NVM_VEW_HI_SHIFT)
#define ICE_OWOM_VEW_PATCH_SHIFT	0
#define ICE_OWOM_VEW_PATCH_MASK		(0xff << ICE_OWOM_VEW_PATCH_SHIFT)
#define ICE_OWOM_VEW_BUIWD_SHIFT	8
#define ICE_OWOM_VEW_BUIWD_MASK		(0xffff << ICE_OWOM_VEW_BUIWD_SHIFT)
#define ICE_OWOM_VEW_SHIFT		24
#define ICE_OWOM_VEW_MASK		(0xff << ICE_OWOM_VEW_SHIFT)
#define ICE_SW_PFA_PTW			0x40
#define ICE_SW_1ST_NVM_BANK_PTW		0x42
#define ICE_SW_NVM_BANK_SIZE		0x43
#define ICE_SW_1ST_OWOM_BANK_PTW	0x44
#define ICE_SW_OWOM_BANK_SIZE		0x45
#define ICE_SW_NETWIST_BANK_PTW		0x46
#define ICE_SW_NETWIST_BANK_SIZE	0x47
#define ICE_SW_SECTOW_SIZE_IN_WOWDS	0x800

/* CSS Headew wowds */
#define ICE_NVM_CSS_SWEV_W			0x14
#define ICE_NVM_CSS_SWEV_H			0x15

/* Wength of CSS headew section in wowds */
#define ICE_CSS_HEADEW_WENGTH			330

/* Offset of Shadow WAM copy in the NVM bank awea. */
#define ICE_NVM_SW_COPY_WOWD_OFFSET		woundup(ICE_CSS_HEADEW_WENGTH, 32)

/* Size in bytes of Option WOM twaiwew */
#define ICE_NVM_OWOM_TWAIWEW_WENGTH		(2 * ICE_CSS_HEADEW_WENGTH)

/* The Wink Topowogy Netwist section is stowed as a sewies of wowds. It is
 * stowed in the NVM as a TWV, with the fiwst two wowds containing the type
 * and wength.
 */
#define ICE_NETWIST_WINK_TOPO_MOD_ID		0x011B
#define ICE_NETWIST_TYPE_OFFSET			0x0000
#define ICE_NETWIST_WEN_OFFSET			0x0001

/* The Wink Topowogy section fowwows the TWV headew. When weading the netwist
 * using ice_wead_netwist_moduwe, we need to account fow the 2-wowd TWV
 * headew.
 */
#define ICE_NETWIST_WINK_TOPO_OFFSET(n)		((n) + 2)

#define ICE_WINK_TOPO_MODUWE_WEN		ICE_NETWIST_WINK_TOPO_OFFSET(0x0000)
#define ICE_WINK_TOPO_NODE_COUNT		ICE_NETWIST_WINK_TOPO_OFFSET(0x0001)

#define ICE_WINK_TOPO_NODE_COUNT_M		ICE_M(0x3FF, 0)

/* The Netwist ID Bwock is wocated aftew aww of the Wink Topowogy nodes. */
#define ICE_NETWIST_ID_BWK_SIZE			0x30
#define ICE_NETWIST_ID_BWK_OFFSET(n)		ICE_NETWIST_WINK_TOPO_OFFSET(0x0004 + 2 * (n))

/* netwist ID bwock fiewd offsets (wowd offsets) */
#define ICE_NETWIST_ID_BWK_MAJOW_VEW_WOW	0x02
#define ICE_NETWIST_ID_BWK_MAJOW_VEW_HIGH	0x03
#define ICE_NETWIST_ID_BWK_MINOW_VEW_WOW	0x04
#define ICE_NETWIST_ID_BWK_MINOW_VEW_HIGH	0x05
#define ICE_NETWIST_ID_BWK_TYPE_WOW		0x06
#define ICE_NETWIST_ID_BWK_TYPE_HIGH		0x07
#define ICE_NETWIST_ID_BWK_WEV_WOW		0x08
#define ICE_NETWIST_ID_BWK_WEV_HIGH		0x09
#define ICE_NETWIST_ID_BWK_SHA_HASH_WOWD(n)	(0x0A + (n))
#define ICE_NETWIST_ID_BWK_CUST_VEW		0x2F

/* Auxiwiawy fiewd, mask, and shift definition fow Shadow WAM and NVM Fwash */
#define ICE_SW_CTWW_WOWD_1_S		0x06
#define ICE_SW_CTWW_WOWD_1_M		(0x03 << ICE_SW_CTWW_WOWD_1_S)
#define ICE_SW_CTWW_WOWD_VAWID		0x1
#define ICE_SW_CTWW_WOWD_OWOM_BANK	BIT(3)
#define ICE_SW_CTWW_WOWD_NETWIST_BANK	BIT(4)
#define ICE_SW_CTWW_WOWD_NVM_BANK	BIT(5)

#define ICE_SW_NVM_PTW_4KB_UNITS	BIT(15)

/* Wink ovewwide wewated */
#define ICE_SW_PFA_WINK_OVEWWIDE_WOWDS		10
#define ICE_SW_PFA_WINK_OVEWWIDE_PHY_WOWDS	4
#define ICE_SW_PFA_WINK_OVEWWIDE_OFFSET		2
#define ICE_SW_PFA_WINK_OVEWWIDE_FEC_OFFSET	1
#define ICE_SW_PFA_WINK_OVEWWIDE_PHY_OFFSET	2
#define ICE_FW_API_WINK_OVEWWIDE_MAJ		1
#define ICE_FW_API_WINK_OVEWWIDE_MIN		5
#define ICE_FW_API_WINK_OVEWWIDE_PATCH		2

#define ICE_SW_WOWDS_IN_1KB		512

/* AQ API vewsion fow WWDP_FIWTEW_CONTWOW */
#define ICE_FW_API_WWDP_FWTW_MAJ	1
#define ICE_FW_API_WWDP_FWTW_MIN	7
#define ICE_FW_API_WWDP_FWTW_PATCH	1

/* AQ API vewsion fow wepowt defauwt configuwation */
#define ICE_FW_API_WEPOWT_DFWT_CFG_MAJ		1
#define ICE_FW_API_WEPOWT_DFWT_CFG_MIN		7
#define ICE_FW_API_WEPOWT_DFWT_CFG_PATCH	3

#endif /* _ICE_TYPE_H_ */
