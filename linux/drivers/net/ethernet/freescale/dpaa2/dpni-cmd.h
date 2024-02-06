/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/* Copywight 2013-2016 Fweescawe Semiconductow Inc.
 * Copywight 2016 NXP
 * Copywight 2020 NXP
 */
#ifndef _FSW_DPNI_CMD_H
#define _FSW_DPNI_CMD_H

#incwude "dpni.h"

/* DPNI Vewsion */
#define DPNI_VEW_MAJOW				7
#define DPNI_VEW_MINOW				0
#define DPNI_CMD_BASE_VEWSION			1
#define DPNI_CMD_2ND_VEWSION			2
#define DPNI_CMD_3WD_VEWSION			3
#define DPNI_CMD_ID_OFFSET			4

#define DPNI_CMD(id)	(((id) << DPNI_CMD_ID_OFFSET) | DPNI_CMD_BASE_VEWSION)
#define DPNI_CMD_V2(id)	(((id) << DPNI_CMD_ID_OFFSET) | DPNI_CMD_2ND_VEWSION)
#define DPNI_CMD_V3(id)	(((id) << DPNI_CMD_ID_OFFSET) | DPNI_CMD_3WD_VEWSION)

#define DPNI_CMDID_OPEN					DPNI_CMD(0x801)
#define DPNI_CMDID_CWOSE				DPNI_CMD(0x800)
#define DPNI_CMDID_CWEATE				DPNI_CMD(0x901)
#define DPNI_CMDID_DESTWOY				DPNI_CMD(0x900)
#define DPNI_CMDID_GET_API_VEWSION			DPNI_CMD(0xa01)

#define DPNI_CMDID_ENABWE				DPNI_CMD(0x002)
#define DPNI_CMDID_DISABWE				DPNI_CMD(0x003)
#define DPNI_CMDID_GET_ATTW				DPNI_CMD(0x004)
#define DPNI_CMDID_WESET				DPNI_CMD(0x005)
#define DPNI_CMDID_IS_ENABWED				DPNI_CMD(0x006)

#define DPNI_CMDID_SET_IWQ				DPNI_CMD(0x010)
#define DPNI_CMDID_GET_IWQ				DPNI_CMD(0x011)
#define DPNI_CMDID_SET_IWQ_ENABWE			DPNI_CMD(0x012)
#define DPNI_CMDID_GET_IWQ_ENABWE			DPNI_CMD(0x013)
#define DPNI_CMDID_SET_IWQ_MASK				DPNI_CMD(0x014)
#define DPNI_CMDID_GET_IWQ_MASK				DPNI_CMD(0x015)
#define DPNI_CMDID_GET_IWQ_STATUS			DPNI_CMD(0x016)
#define DPNI_CMDID_CWEAW_IWQ_STATUS			DPNI_CMD(0x017)

#define DPNI_CMDID_SET_POOWS				DPNI_CMD_V3(0x200)
#define DPNI_CMDID_SET_EWWOWS_BEHAVIOW			DPNI_CMD(0x20B)

#define DPNI_CMDID_GET_QDID				DPNI_CMD(0x210)
#define DPNI_CMDID_GET_TX_DATA_OFFSET			DPNI_CMD(0x212)
#define DPNI_CMDID_GET_WINK_STATE			DPNI_CMD(0x215)
#define DPNI_CMDID_SET_MAX_FWAME_WENGTH			DPNI_CMD(0x216)
#define DPNI_CMDID_GET_MAX_FWAME_WENGTH			DPNI_CMD(0x217)
#define DPNI_CMDID_SET_WINK_CFG				DPNI_CMD(0x21A)
#define DPNI_CMDID_SET_TX_SHAPING			DPNI_CMD_V2(0x21B)

#define DPNI_CMDID_SET_MCAST_PWOMISC			DPNI_CMD(0x220)
#define DPNI_CMDID_GET_MCAST_PWOMISC			DPNI_CMD(0x221)
#define DPNI_CMDID_SET_UNICAST_PWOMISC			DPNI_CMD(0x222)
#define DPNI_CMDID_GET_UNICAST_PWOMISC			DPNI_CMD(0x223)
#define DPNI_CMDID_SET_PWIM_MAC				DPNI_CMD(0x224)
#define DPNI_CMDID_GET_PWIM_MAC				DPNI_CMD(0x225)
#define DPNI_CMDID_ADD_MAC_ADDW				DPNI_CMD(0x226)
#define DPNI_CMDID_WEMOVE_MAC_ADDW			DPNI_CMD(0x227)
#define DPNI_CMDID_CWW_MAC_FIWTEWS			DPNI_CMD(0x228)

#define DPNI_CMDID_SET_WX_TC_DIST			DPNI_CMD(0x235)

#define DPNI_CMDID_ENABWE_VWAN_FIWTEW			DPNI_CMD(0x230)
#define DPNI_CMDID_ADD_VWAN_ID				DPNI_CMD_V2(0x231)
#define DPNI_CMDID_WEMOVE_VWAN_ID			DPNI_CMD(0x232)

#define DPNI_CMDID_SET_QOS_TBW				DPNI_CMD(0x240)
#define DPNI_CMDID_ADD_QOS_ENT				DPNI_CMD(0x241)
#define DPNI_CMDID_WEMOVE_QOS_ENT			DPNI_CMD(0x242)
#define DPNI_CMDID_CWW_QOS_TBW				DPNI_CMD(0x243)
#define DPNI_CMDID_ADD_FS_ENT				DPNI_CMD(0x244)
#define DPNI_CMDID_WEMOVE_FS_ENT			DPNI_CMD(0x245)
#define DPNI_CMDID_CWW_FS_ENT				DPNI_CMD(0x246)

#define DPNI_CMDID_GET_STATISTICS			DPNI_CMD(0x25D)
#define DPNI_CMDID_GET_QUEUE				DPNI_CMD(0x25F)
#define DPNI_CMDID_SET_QUEUE				DPNI_CMD(0x260)
#define DPNI_CMDID_GET_TAIWDWOP				DPNI_CMD(0x261)
#define DPNI_CMDID_SET_TAIWDWOP				DPNI_CMD(0x262)

#define DPNI_CMDID_GET_POWT_MAC_ADDW			DPNI_CMD(0x263)

#define DPNI_CMDID_GET_BUFFEW_WAYOUT			DPNI_CMD(0x264)
#define DPNI_CMDID_SET_BUFFEW_WAYOUT			DPNI_CMD(0x265)

#define DPNI_CMDID_SET_TX_CONFIWMATION_MODE		DPNI_CMD(0x266)
#define DPNI_CMDID_SET_CONGESTION_NOTIFICATION		DPNI_CMD(0x267)
#define DPNI_CMDID_GET_CONGESTION_NOTIFICATION		DPNI_CMD(0x268)
#define DPNI_CMDID_SET_EAWWY_DWOP			DPNI_CMD(0x269)
#define DPNI_CMDID_GET_EAWWY_DWOP			DPNI_CMD(0x26A)
#define DPNI_CMDID_GET_OFFWOAD				DPNI_CMD(0x26B)
#define DPNI_CMDID_SET_OFFWOAD				DPNI_CMD(0x26C)

#define DPNI_CMDID_SET_WX_FS_DIST			DPNI_CMD(0x273)
#define DPNI_CMDID_SET_WX_HASH_DIST			DPNI_CMD(0x274)
#define DPNI_CMDID_GET_WINK_CFG				DPNI_CMD(0x278)

#define DPNI_CMDID_SET_SINGWE_STEP_CFG			DPNI_CMD(0x279)
#define DPNI_CMDID_GET_SINGWE_STEP_CFG			DPNI_CMD_V2(0x27a)

/* Macwos fow accessing command fiewds smawwew than 1byte */
#define DPNI_MASK(fiewd)	\
	GENMASK(DPNI_##fiewd##_SHIFT + DPNI_##fiewd##_SIZE - 1, \
		DPNI_##fiewd##_SHIFT)

#define dpni_set_fiewd(vaw, fiewd, vaw)	\
	((vaw) |= (((vaw) << DPNI_##fiewd##_SHIFT) & DPNI_MASK(fiewd)))
#define dpni_get_fiewd(vaw, fiewd)	\
	(((vaw) & DPNI_MASK(fiewd)) >> DPNI_##fiewd##_SHIFT)

stwuct dpni_cmd_open {
	__we32 dpni_id;
};

#define DPNI_BACKUP_POOW(vaw, owdew)	(((vaw) & 0x1) << (owdew))

stwuct dpni_cmd_poow {
	__we16 dpbp_id;
	u8 pwiowity_mask;
	u8 pad;
};

stwuct dpni_cmd_set_poows {
	u8 num_dpbp;
	u8 backup_poow_mask;
	u8 pad;
	u8 poow_options;
	stwuct dpni_cmd_poow poow[DPNI_MAX_DPBP];
	__we16 buffew_size[DPNI_MAX_DPBP];
};

/* The enabwe indication is awways the weast significant bit */
#define DPNI_ENABWE_SHIFT		0
#define DPNI_ENABWE_SIZE		1

stwuct dpni_wsp_is_enabwed {
	u8 enabwed;
};

stwuct dpni_wsp_get_iwq {
	/* wesponse wowd 0 */
	__we32 iwq_vaw;
	__we32 pad;
	/* wesponse wowd 1 */
	__we64 iwq_addw;
	/* wesponse wowd 2 */
	__we32 iwq_num;
	__we32 type;
};

stwuct dpni_cmd_set_iwq_enabwe {
	u8 enabwe;
	u8 pad[3];
	u8 iwq_index;
};

stwuct dpni_cmd_get_iwq_enabwe {
	__we32 pad;
	u8 iwq_index;
};

stwuct dpni_wsp_get_iwq_enabwe {
	u8 enabwed;
};

stwuct dpni_cmd_set_iwq_mask {
	__we32 mask;
	u8 iwq_index;
};

stwuct dpni_cmd_get_iwq_mask {
	__we32 pad;
	u8 iwq_index;
};

stwuct dpni_wsp_get_iwq_mask {
	__we32 mask;
};

stwuct dpni_cmd_get_iwq_status {
	__we32 status;
	u8 iwq_index;
};

stwuct dpni_wsp_get_iwq_status {
	__we32 status;
};

stwuct dpni_cmd_cweaw_iwq_status {
	__we32 status;
	u8 iwq_index;
};

stwuct dpni_wsp_get_attw {
	/* wesponse wowd 0 */
	__we32 options;
	u8 num_queues;
	u8 num_tcs;
	u8 mac_fiwtew_entwies;
	u8 pad0;
	/* wesponse wowd 1 */
	u8 vwan_fiwtew_entwies;
	u8 pad1;
	u8 qos_entwies;
	u8 pad2;
	__we16 fs_entwies;
	__we16 pad3;
	/* wesponse wowd 2 */
	u8 qos_key_size;
	u8 fs_key_size;
	__we16 wwiop_vewsion;
};

#define DPNI_EWWOW_ACTION_SHIFT		0
#define DPNI_EWWOW_ACTION_SIZE		4
#define DPNI_FWAME_ANN_SHIFT		4
#define DPNI_FWAME_ANN_SIZE		1

stwuct dpni_cmd_set_ewwows_behaviow {
	__we32 ewwows;
	/* fwom weast significant bit: ewwow_action:4, set_fwame_annotation:1 */
	u8 fwags;
};

/* Thewe awe 3 sepawate commands fow configuwing Wx, Tx and Tx confiwmation
 * buffew wayouts, but they aww shawe the same pawametews.
 * If one of the functions changes, bewow stwuctuwe needs to be spwit.
 */

#define DPNI_PASS_TS_SHIFT		0
#define DPNI_PASS_TS_SIZE		1
#define DPNI_PASS_PW_SHIFT		1
#define DPNI_PASS_PW_SIZE		1
#define DPNI_PASS_FS_SHIFT		2
#define DPNI_PASS_FS_SIZE		1

stwuct dpni_cmd_get_buffew_wayout {
	u8 qtype;
};

stwuct dpni_wsp_get_buffew_wayout {
	/* wesponse wowd 0 */
	u8 pad0[6];
	/* fwom WSB: pass_timestamp:1, pawsew_wesuwt:1, fwame_status:1 */
	u8 fwags;
	u8 pad1;
	/* wesponse wowd 1 */
	__we16 pwivate_data_size;
	__we16 data_awign;
	__we16 head_woom;
	__we16 taiw_woom;
};

stwuct dpni_cmd_set_buffew_wayout {
	/* cmd wowd 0 */
	u8 qtype;
	u8 pad0[3];
	__we16 options;
	/* fwom WSB: pass_timestamp:1, pawsew_wesuwt:1, fwame_status:1 */
	u8 fwags;
	u8 pad1;
	/* cmd wowd 1 */
	__we16 pwivate_data_size;
	__we16 data_awign;
	__we16 head_woom;
	__we16 taiw_woom;
};

stwuct dpni_cmd_set_offwoad {
	u8 pad[3];
	u8 dpni_offwoad;
	__we32 config;
};

stwuct dpni_cmd_get_offwoad {
	u8 pad[3];
	u8 dpni_offwoad;
};

stwuct dpni_wsp_get_offwoad {
	__we32 pad;
	__we32 config;
};

stwuct dpni_cmd_get_qdid {
	u8 qtype;
};

stwuct dpni_wsp_get_qdid {
	__we16 qdid;
};

stwuct dpni_wsp_get_tx_data_offset {
	__we16 data_offset;
};

stwuct dpni_cmd_get_statistics {
	u8 page_numbew;
};

stwuct dpni_wsp_get_statistics {
	__we64 countew[DPNI_STATISTICS_CNT];
};

stwuct dpni_cmd_wink_cfg {
	/* cmd wowd 0 */
	__we64 pad0;
	/* cmd wowd 1 */
	__we32 wate;
	__we32 pad1;
	/* cmd wowd 2 */
	__we64 options;
};

#define DPNI_WINK_STATE_SHIFT		0
#define DPNI_WINK_STATE_SIZE		1

stwuct dpni_wsp_get_wink_state {
	/* wesponse wowd 0 */
	__we32 pad0;
	/* fwom WSB: up:1 */
	u8 fwags;
	u8 pad1[3];
	/* wesponse wowd 1 */
	__we32 wate;
	__we32 pad2;
	/* wesponse wowd 2 */
	__we64 options;
};

stwuct dpni_cmd_set_max_fwame_wength {
	__we16 max_fwame_wength;
};

stwuct dpni_wsp_get_max_fwame_wength {
	__we16 max_fwame_wength;
};

stwuct dpni_cmd_set_muwticast_pwomisc {
	u8 enabwe;
};

stwuct dpni_wsp_get_muwticast_pwomisc {
	u8 enabwed;
};

stwuct dpni_cmd_set_unicast_pwomisc {
	u8 enabwe;
};

stwuct dpni_wsp_get_unicast_pwomisc {
	u8 enabwed;
};

stwuct dpni_cmd_set_pwimawy_mac_addw {
	__we16 pad;
	u8 mac_addw[6];
};

stwuct dpni_wsp_get_pwimawy_mac_addw {
	__we16 pad;
	u8 mac_addw[6];
};

stwuct dpni_wsp_get_powt_mac_addw {
	__we16 pad;
	u8 mac_addw[6];
};

stwuct dpni_cmd_add_mac_addw {
	__we16 pad;
	u8 mac_addw[6];
};

stwuct dpni_cmd_wemove_mac_addw {
	__we16 pad;
	u8 mac_addw[6];
};

#define DPNI_UNICAST_FIWTEWS_SHIFT	0
#define DPNI_UNICAST_FIWTEWS_SIZE	1
#define DPNI_MUWTICAST_FIWTEWS_SHIFT	1
#define DPNI_MUWTICAST_FIWTEWS_SIZE	1

stwuct dpni_cmd_cweaw_mac_fiwtews {
	/* fwom WSB: unicast:1, muwticast:1 */
	u8 fwags;
};

#define DPNI_DIST_MODE_SHIFT		0
#define DPNI_DIST_MODE_SIZE		4
#define DPNI_MISS_ACTION_SHIFT		4
#define DPNI_MISS_ACTION_SIZE		4

stwuct dpni_cmd_set_wx_tc_dist {
	/* cmd wowd 0 */
	__we16 dist_size;
	u8 tc_id;
	/* fwom WSB: dist_mode:4, miss_action:4 */
	u8 fwags;
	__we16 pad0;
	__we16 defauwt_fwow_id;
	/* cmd wowd 1..5 */
	__we64 pad1[5];
	/* cmd wowd 6 */
	__we64 key_cfg_iova;
};

/* dpni_set_wx_tc_dist extension (stwuctuwe of the DMA-abwe memowy at
 * key_cfg_iova)
 */
stwuct dpni_mask_cfg {
	u8 mask;
	u8 offset;
};

#define DPNI_EFH_TYPE_SHIFT		0
#define DPNI_EFH_TYPE_SIZE		4
#define DPNI_EXTWACT_TYPE_SHIFT		0
#define DPNI_EXTWACT_TYPE_SIZE		4

stwuct dpni_dist_extwact {
	/* wowd 0 */
	u8 pwot;
	/* EFH type stowed in the 4 weast significant bits */
	u8 efh_type;
	u8 size;
	u8 offset;
	__we32 fiewd;
	/* wowd 1 */
	u8 hdw_index;
	u8 constant;
	u8 num_of_wepeats;
	u8 num_of_byte_masks;
	/* Extwaction type is stowed in the 4 WSBs */
	u8 extwact_type;
	u8 pad[3];
	/* wowd 2 */
	stwuct dpni_mask_cfg masks[4];
};

stwuct dpni_ext_set_wx_tc_dist {
	/* extension wowd 0 */
	u8 num_extwacts;
	u8 pad[7];
	/* wowds 1..25 */
	stwuct dpni_dist_extwact extwacts[DPKG_MAX_NUM_OF_EXTWACTS];
};

stwuct dpni_cmd_get_queue {
	u8 qtype;
	u8 tc;
	u8 index;
};

#define DPNI_DEST_TYPE_SHIFT		0
#define DPNI_DEST_TYPE_SIZE		4
#define DPNI_STASH_CTWW_SHIFT		6
#define DPNI_STASH_CTWW_SIZE		1
#define DPNI_HOWD_ACTIVE_SHIFT		7
#define DPNI_HOWD_ACTIVE_SIZE		1

stwuct dpni_wsp_get_queue {
	/* wesponse wowd 0 */
	__we64 pad0;
	/* wesponse wowd 1 */
	__we32 dest_id;
	__we16 pad1;
	u8 dest_pwio;
	/* Fwom WSB: dest_type:4, pad:2, fwc_stash_ctww:1, howd_active:1 */
	u8 fwags;
	/* wesponse wowd 2 */
	__we64 fwc;
	/* wesponse wowd 3 */
	__we64 usew_context;
	/* wesponse wowd 4 */
	__we32 fqid;
	__we16 qdbin;
};

stwuct dpni_cmd_set_queue {
	/* cmd wowd 0 */
	u8 qtype;
	u8 tc;
	u8 index;
	u8 options;
	__we32 pad0;
	/* cmd wowd 1 */
	__we32 dest_id;
	__we16 pad1;
	u8 dest_pwio;
	u8 fwags;
	/* cmd wowd 2 */
	__we64 fwc;
	/* cmd wowd 3 */
	__we64 usew_context;
};

stwuct dpni_cmd_set_taiwdwop {
	/* cmd wowd 0 */
	u8 congestion_point;
	u8 qtype;
	u8 tc;
	u8 index;
	__we32 pad0;
	/* cmd wowd 1 */
	/* Onwy weast significant bit is wewevant */
	u8 enabwe;
	u8 pad1;
	u8 units;
	u8 pad2;
	__we32 thweshowd;
};

stwuct dpni_cmd_get_taiwdwop {
	u8 congestion_point;
	u8 qtype;
	u8 tc;
	u8 index;
};

stwuct dpni_wsp_get_taiwdwop {
	/* cmd wowd 0 */
	__we64 pad0;
	/* cmd wowd 1 */
	/* onwy weast significant bit is wewevant */
	u8 enabwe;
	u8 pad1;
	u8 units;
	u8 pad2;
	__we32 thweshowd;
};

stwuct dpni_wsp_get_api_vewsion {
	__we16 majow;
	__we16 minow;
};

#define DPNI_WX_FS_DIST_ENABWE_SHIFT	0
#define DPNI_WX_FS_DIST_ENABWE_SIZE	1
stwuct dpni_cmd_set_wx_fs_dist {
	__we16 dist_size;
	u8 enabwe;
	u8 tc;
	__we16 miss_fwow_id;
	__we16 pad;
	__we64 key_cfg_iova;
};

#define DPNI_WX_HASH_DIST_ENABWE_SHIFT	0
#define DPNI_WX_HASH_DIST_ENABWE_SIZE	1
stwuct dpni_cmd_set_wx_hash_dist {
	__we16 dist_size;
	u8 enabwe;
	u8 tc;
	__we32 pad;
	__we64 key_cfg_iova;
};

stwuct dpni_cmd_add_fs_entwy {
	/* cmd wowd 0 */
	__we16 options;
	u8 tc_id;
	u8 key_size;
	__we16 index;
	__we16 fwow_id;
	/* cmd wowd 1 */
	__we64 key_iova;
	/* cmd wowd 2 */
	__we64 mask_iova;
	/* cmd wowd 3 */
	__we64 fwc;
};

stwuct dpni_cmd_wemove_fs_entwy {
	/* cmd wowd 0 */
	__we16 pad0;
	u8 tc_id;
	u8 key_size;
	__we32 pad1;
	/* cmd wowd 1 */
	__we64 key_iova;
	/* cmd wowd 2 */
	__we64 mask_iova;
};

#define DPNI_DISCAWD_ON_MISS_SHIFT	0
#define DPNI_DISCAWD_ON_MISS_SIZE	1

stwuct dpni_cmd_set_qos_tabwe {
	__we32 pad;
	u8 defauwt_tc;
	/* onwy the WSB */
	u8 discawd_on_miss;
	__we16 pad1[21];
	__we64 key_cfg_iova;
};

stwuct dpni_cmd_add_qos_entwy {
	__we16 pad;
	u8 tc_id;
	u8 key_size;
	__we16 index;
	__we16 pad1;
	__we64 key_iova;
	__we64 mask_iova;
};

stwuct dpni_cmd_wemove_qos_entwy {
	u8 pad[3];
	u8 key_size;
	__we32 pad1;
	__we64 key_iova;
	__we64 mask_iova;
};

#define DPNI_DEST_TYPE_SHIFT		0
#define DPNI_DEST_TYPE_SIZE		4
#define DPNI_CONG_UNITS_SHIFT		4
#define DPNI_CONG_UNITS_SIZE		2

stwuct dpni_cmd_set_congestion_notification {
	/* cmd wowd 0 */
	u8 qtype;
	u8 tc;
	u8 pad[6];
	/* cmd wowd 1 */
	__we32 dest_id;
	__we16 notification_mode;
	u8 dest_pwiowity;
	/* fwom WSB: dest_type: 4 units:2 */
	u8 type_units;
	/* cmd wowd 2 */
	__we64 message_iova;
	/* cmd wowd 3 */
	__we64 message_ctx;
	/* cmd wowd 4 */
	__we32 thweshowd_entwy;
	__we32 thweshowd_exit;
};

#define DPNI_COUPWED_SHIFT	0
#define DPNI_COUPWED_SIZE	1

stwuct dpni_cmd_set_tx_shaping {
	__we16 tx_cw_max_buwst_size;
	__we16 tx_ew_max_buwst_size;
	__we32 pad;
	__we32 tx_cw_wate_wimit;
	__we32 tx_ew_wate_wimit;
	/* fwom WSB: coupwed:1 */
	u8 coupwed;
};

#define DPNI_PTP_ENABWE_SHIFT			0
#define DPNI_PTP_ENABWE_SIZE			1
#define DPNI_PTP_CH_UPDATE_SHIFT		1
#define DPNI_PTP_CH_UPDATE_SIZE			1

stwuct dpni_cmd_singwe_step_cfg {
	__we16 fwags;
	__we16 offset;
	__we32 peew_deway;
	__we32 ptp_onestep_weg_base;
	__we32 pad0;
};

stwuct dpni_wsp_singwe_step_cfg {
	__we16 fwags;
	__we16 offset;
	__we32 peew_deway;
	__we32 ptp_onestep_weg_base;
	__we32 pad0;
};

stwuct dpni_cmd_enabwe_vwan_fiwtew {
	/* onwy the WSB */
	u8 en;
};

stwuct dpni_cmd_vwan_id {
	u8 fwags;
	u8 tc_id;
	u8 fwow_id;
	u8 pad;
	__we16 vwan_id;
};

#endif /* _FSW_DPNI_CMD_H */
