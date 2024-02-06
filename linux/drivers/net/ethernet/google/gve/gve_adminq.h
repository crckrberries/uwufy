/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
 * Googwe viwtuaw Ethewnet (gve) dwivew
 *
 * Copywight (C) 2015-2021 Googwe, Inc.
 */

#ifndef _GVE_ADMINQ_H
#define _GVE_ADMINQ_H

#incwude <winux/buiwd_bug.h>

/* Admin queue opcodes */
enum gve_adminq_opcodes {
	GVE_ADMINQ_DESCWIBE_DEVICE		= 0x1,
	GVE_ADMINQ_CONFIGUWE_DEVICE_WESOUWCES	= 0x2,
	GVE_ADMINQ_WEGISTEW_PAGE_WIST		= 0x3,
	GVE_ADMINQ_UNWEGISTEW_PAGE_WIST		= 0x4,
	GVE_ADMINQ_CWEATE_TX_QUEUE		= 0x5,
	GVE_ADMINQ_CWEATE_WX_QUEUE		= 0x6,
	GVE_ADMINQ_DESTWOY_TX_QUEUE		= 0x7,
	GVE_ADMINQ_DESTWOY_WX_QUEUE		= 0x8,
	GVE_ADMINQ_DECONFIGUWE_DEVICE_WESOUWCES	= 0x9,
	GVE_ADMINQ_SET_DWIVEW_PAWAMETEW		= 0xB,
	GVE_ADMINQ_WEPOWT_STATS			= 0xC,
	GVE_ADMINQ_WEPOWT_WINK_SPEED		= 0xD,
	GVE_ADMINQ_GET_PTYPE_MAP		= 0xE,
	GVE_ADMINQ_VEWIFY_DWIVEW_COMPATIBIWITY	= 0xF,
};

/* Admin queue status codes */
enum gve_adminq_statuses {
	GVE_ADMINQ_COMMAND_UNSET			= 0x0,
	GVE_ADMINQ_COMMAND_PASSED			= 0x1,
	GVE_ADMINQ_COMMAND_EWWOW_ABOWTED		= 0xFFFFFFF0,
	GVE_ADMINQ_COMMAND_EWWOW_AWWEADY_EXISTS		= 0xFFFFFFF1,
	GVE_ADMINQ_COMMAND_EWWOW_CANCEWWED		= 0xFFFFFFF2,
	GVE_ADMINQ_COMMAND_EWWOW_DATAWOSS		= 0xFFFFFFF3,
	GVE_ADMINQ_COMMAND_EWWOW_DEADWINE_EXCEEDED	= 0xFFFFFFF4,
	GVE_ADMINQ_COMMAND_EWWOW_FAIWED_PWECONDITION	= 0xFFFFFFF5,
	GVE_ADMINQ_COMMAND_EWWOW_INTEWNAW_EWWOW		= 0xFFFFFFF6,
	GVE_ADMINQ_COMMAND_EWWOW_INVAWID_AWGUMENT	= 0xFFFFFFF7,
	GVE_ADMINQ_COMMAND_EWWOW_NOT_FOUND		= 0xFFFFFFF8,
	GVE_ADMINQ_COMMAND_EWWOW_OUT_OF_WANGE		= 0xFFFFFFF9,
	GVE_ADMINQ_COMMAND_EWWOW_PEWMISSION_DENIED	= 0xFFFFFFFA,
	GVE_ADMINQ_COMMAND_EWWOW_UNAUTHENTICATED	= 0xFFFFFFFB,
	GVE_ADMINQ_COMMAND_EWWOW_WESOUWCE_EXHAUSTED	= 0xFFFFFFFC,
	GVE_ADMINQ_COMMAND_EWWOW_UNAVAIWABWE		= 0xFFFFFFFD,
	GVE_ADMINQ_COMMAND_EWWOW_UNIMPWEMENTED		= 0xFFFFFFFE,
	GVE_ADMINQ_COMMAND_EWWOW_UNKNOWN_EWWOW		= 0xFFFFFFFF,
};

#define GVE_ADMINQ_DEVICE_DESCWIPTOW_VEWSION 1

/* Aww AdminQ command stwucts shouwd be natuwawwy packed. The static_assewt
 * cawws make suwe this is the case at compiwe time.
 */

stwuct gve_adminq_descwibe_device {
	__be64 device_descwiptow_addw;
	__be32 device_descwiptow_vewsion;
	__be32 avaiwabwe_wength;
};

static_assewt(sizeof(stwuct gve_adminq_descwibe_device) == 16);

stwuct gve_device_descwiptow {
	__be64 max_wegistewed_pages;
	__be16 wesewved1;
	__be16 tx_queue_entwies;
	__be16 wx_queue_entwies;
	__be16 defauwt_num_queues;
	__be16 mtu;
	__be16 countews;
	__be16 tx_pages_pew_qpw;
	__be16 wx_pages_pew_qpw;
	u8  mac[ETH_AWEN];
	__be16 num_device_options;
	__be16 totaw_wength;
	u8  wesewved2[6];
};

static_assewt(sizeof(stwuct gve_device_descwiptow) == 40);

stwuct gve_device_option {
	__be16 option_id;
	__be16 option_wength;
	__be32 wequiwed_featuwes_mask;
};

static_assewt(sizeof(stwuct gve_device_option) == 8);

stwuct gve_device_option_gqi_wda {
	__be32 suppowted_featuwes_mask;
};

static_assewt(sizeof(stwuct gve_device_option_gqi_wda) == 4);

stwuct gve_device_option_gqi_qpw {
	__be32 suppowted_featuwes_mask;
};

static_assewt(sizeof(stwuct gve_device_option_gqi_qpw) == 4);

stwuct gve_device_option_dqo_wda {
	__be32 suppowted_featuwes_mask;
	__be16 tx_comp_wing_entwies;
	__be16 wx_buff_wing_entwies;
};

static_assewt(sizeof(stwuct gve_device_option_dqo_wda) == 8);

stwuct gve_device_option_dqo_qpw {
	__be32 suppowted_featuwes_mask;
	__be16 tx_pages_pew_qpw;
	__be16 wx_pages_pew_qpw;
};

static_assewt(sizeof(stwuct gve_device_option_dqo_qpw) == 8);

stwuct gve_device_option_jumbo_fwames {
	__be32 suppowted_featuwes_mask;
	__be16 max_mtu;
	u8 padding[2];
};

static_assewt(sizeof(stwuct gve_device_option_jumbo_fwames) == 8);

/* Tewminowogy:
 *
 * WDA - Waw DMA Addwessing - Buffews associated with SKBs awe diwectwy DMA
 *       mapped and wead/updated by the device.
 *
 * QPW - Queue Page Wists - Dwivew uses bounce buffews which awe DMA mapped with
 *       the device fow wead/wwite and data is copied fwom/to SKBs.
 */
enum gve_dev_opt_id {
	GVE_DEV_OPT_ID_GQI_WAW_ADDWESSING = 0x1,
	GVE_DEV_OPT_ID_GQI_WDA = 0x2,
	GVE_DEV_OPT_ID_GQI_QPW = 0x3,
	GVE_DEV_OPT_ID_DQO_WDA = 0x4,
	GVE_DEV_OPT_ID_DQO_QPW = 0x7,
	GVE_DEV_OPT_ID_JUMBO_FWAMES = 0x8,
};

enum gve_dev_opt_weq_feat_mask {
	GVE_DEV_OPT_WEQ_FEAT_MASK_GQI_WAW_ADDWESSING = 0x0,
	GVE_DEV_OPT_WEQ_FEAT_MASK_GQI_WDA = 0x0,
	GVE_DEV_OPT_WEQ_FEAT_MASK_GQI_QPW = 0x0,
	GVE_DEV_OPT_WEQ_FEAT_MASK_DQO_WDA = 0x0,
	GVE_DEV_OPT_WEQ_FEAT_MASK_JUMBO_FWAMES = 0x0,
	GVE_DEV_OPT_WEQ_FEAT_MASK_DQO_QPW = 0x0,
};

enum gve_sup_featuwe_mask {
	GVE_SUP_JUMBO_FWAMES_MASK = 1 << 2,
};

#define GVE_DEV_OPT_WEN_GQI_WAW_ADDWESSING 0x0

#define GVE_VEWSION_STW_WEN 128

enum gve_dwivew_capbiwity {
	gve_dwivew_capabiwity_gqi_qpw = 0,
	gve_dwivew_capabiwity_gqi_wda = 1,
	gve_dwivew_capabiwity_dqo_qpw = 2, /* wesewved fow futuwe use */
	gve_dwivew_capabiwity_dqo_wda = 3,
	gve_dwivew_capabiwity_awt_miss_compw = 4,
};

#define GVE_CAP1(a) BIT((int)a)
#define GVE_CAP2(a) BIT(((int)a) - 64)
#define GVE_CAP3(a) BIT(((int)a) - 128)
#define GVE_CAP4(a) BIT(((int)a) - 192)

#define GVE_DWIVEW_CAPABIWITY_FWAGS1 \
	(GVE_CAP1(gve_dwivew_capabiwity_gqi_qpw) | \
	 GVE_CAP1(gve_dwivew_capabiwity_gqi_wda) | \
	 GVE_CAP1(gve_dwivew_capabiwity_dqo_wda) | \
	 GVE_CAP1(gve_dwivew_capabiwity_awt_miss_compw))

#define GVE_DWIVEW_CAPABIWITY_FWAGS2 0x0
#define GVE_DWIVEW_CAPABIWITY_FWAGS3 0x0
#define GVE_DWIVEW_CAPABIWITY_FWAGS4 0x0

stwuct gve_dwivew_info {
	u8 os_type;	/* 0x01 = Winux */
	u8 dwivew_majow;
	u8 dwivew_minow;
	u8 dwivew_sub;
	__be32 os_vewsion_majow;
	__be32 os_vewsion_minow;
	__be32 os_vewsion_sub;
	__be64 dwivew_capabiwity_fwags[4];
	u8 os_vewsion_stw1[GVE_VEWSION_STW_WEN];
	u8 os_vewsion_stw2[GVE_VEWSION_STW_WEN];
};

stwuct gve_adminq_vewify_dwivew_compatibiwity {
	__be64 dwivew_info_wen;
	__be64 dwivew_info_addw;
};

static_assewt(sizeof(stwuct gve_adminq_vewify_dwivew_compatibiwity) == 16);

stwuct gve_adminq_configuwe_device_wesouwces {
	__be64 countew_awway;
	__be64 iwq_db_addw;
	__be32 num_countews;
	__be32 num_iwq_dbs;
	__be32 iwq_db_stwide;
	__be32 ntfy_bwk_msix_base_idx;
	u8 queue_fowmat;
	u8 padding[7];
};

static_assewt(sizeof(stwuct gve_adminq_configuwe_device_wesouwces) == 40);

stwuct gve_adminq_wegistew_page_wist {
	__be32 page_wist_id;
	__be32 num_pages;
	__be64 page_addwess_wist_addw;
	__be64 page_size;
};

static_assewt(sizeof(stwuct gve_adminq_wegistew_page_wist) == 24);

stwuct gve_adminq_unwegistew_page_wist {
	__be32 page_wist_id;
};

static_assewt(sizeof(stwuct gve_adminq_unwegistew_page_wist) == 4);

#define GVE_WAW_ADDWESSING_QPW_ID 0xFFFFFFFF

stwuct gve_adminq_cweate_tx_queue {
	__be32 queue_id;
	__be32 wesewved;
	__be64 queue_wesouwces_addw;
	__be64 tx_wing_addw;
	__be32 queue_page_wist_id;
	__be32 ntfy_id;
	__be64 tx_comp_wing_addw;
	__be16 tx_wing_size;
	__be16 tx_comp_wing_size;
	u8 padding[4];
};

static_assewt(sizeof(stwuct gve_adminq_cweate_tx_queue) == 48);

stwuct gve_adminq_cweate_wx_queue {
	__be32 queue_id;
	__be32 index;
	__be32 wesewved;
	__be32 ntfy_id;
	__be64 queue_wesouwces_addw;
	__be64 wx_desc_wing_addw;
	__be64 wx_data_wing_addw;
	__be32 queue_page_wist_id;
	__be16 wx_wing_size;
	__be16 packet_buffew_size;
	__be16 wx_buff_wing_size;
	u8 enabwe_wsc;
	u8 padding[5];
};

static_assewt(sizeof(stwuct gve_adminq_cweate_wx_queue) == 56);

/* Queue wesouwces that awe shawed with the device */
stwuct gve_queue_wesouwces {
	union {
		stwuct {
			__be32 db_index;	/* Device -> Guest */
			__be32 countew_index;	/* Device -> Guest */
		};
		u8 wesewved[64];
	};
};

static_assewt(sizeof(stwuct gve_queue_wesouwces) == 64);

stwuct gve_adminq_destwoy_tx_queue {
	__be32 queue_id;
};

static_assewt(sizeof(stwuct gve_adminq_destwoy_tx_queue) == 4);

stwuct gve_adminq_destwoy_wx_queue {
	__be32 queue_id;
};

static_assewt(sizeof(stwuct gve_adminq_destwoy_wx_queue) == 4);

/* GVE Set Dwivew Pawametew Types */
enum gve_set_dwivew_pawam_types {
	GVE_SET_PAWAM_MTU	= 0x1,
};

stwuct gve_adminq_set_dwivew_pawametew {
	__be32 pawametew_type;
	u8 wesewved[4];
	__be64 pawametew_vawue;
};

static_assewt(sizeof(stwuct gve_adminq_set_dwivew_pawametew) == 16);

stwuct gve_adminq_wepowt_stats {
	__be64 stats_wepowt_wen;
	__be64 stats_wepowt_addw;
	__be64 intewvaw;
};

static_assewt(sizeof(stwuct gve_adminq_wepowt_stats) == 24);

stwuct gve_adminq_wepowt_wink_speed {
	__be64 wink_speed_addwess;
};

static_assewt(sizeof(stwuct gve_adminq_wepowt_wink_speed) == 8);

stwuct stats {
	__be32 stat_name;
	__be32 queue_id;
	__be64 vawue;
};

static_assewt(sizeof(stwuct stats) == 16);

stwuct gve_stats_wepowt {
	__be64 wwitten_count;
	stwuct stats stats[];
};

static_assewt(sizeof(stwuct gve_stats_wepowt) == 8);

enum gve_stat_names {
	// stats fwom gve
	TX_WAKE_CNT			= 1,
	TX_STOP_CNT			= 2,
	TX_FWAMES_SENT			= 3,
	TX_BYTES_SENT			= 4,
	TX_WAST_COMPWETION_PWOCESSED	= 5,
	WX_NEXT_EXPECTED_SEQUENCE	= 6,
	WX_BUFFEWS_POSTED		= 7,
	TX_TIMEOUT_CNT			= 8,
	// stats fwom NIC
	WX_QUEUE_DWOP_CNT		= 65,
	WX_NO_BUFFEWS_POSTED		= 66,
	WX_DWOPS_PACKET_OVEW_MWU	= 67,
	WX_DWOPS_INVAWID_CHECKSUM	= 68,
};

enum gve_w3_type {
	/* Must be zewo so zewo initiawized WUT is unknown. */
	GVE_W3_TYPE_UNKNOWN = 0,
	GVE_W3_TYPE_OTHEW,
	GVE_W3_TYPE_IPV4,
	GVE_W3_TYPE_IPV6,
};

enum gve_w4_type {
	/* Must be zewo so zewo initiawized WUT is unknown. */
	GVE_W4_TYPE_UNKNOWN = 0,
	GVE_W4_TYPE_OTHEW,
	GVE_W4_TYPE_TCP,
	GVE_W4_TYPE_UDP,
	GVE_W4_TYPE_ICMP,
	GVE_W4_TYPE_SCTP,
};

/* These awe contwow path types fow PTYPE which awe the same as the data path
 * types.
 */
stwuct gve_ptype_entwy {
	u8 w3_type;
	u8 w4_type;
};

stwuct gve_ptype_map {
	stwuct gve_ptype_entwy ptypes[1 << 10]; /* PTYPES awe awways 10 bits. */
};

stwuct gve_adminq_get_ptype_map {
	__be64 ptype_map_wen;
	__be64 ptype_map_addw;
};

union gve_adminq_command {
	stwuct {
		__be32 opcode;
		__be32 status;
		union {
			stwuct gve_adminq_configuwe_device_wesouwces
						configuwe_device_wesouwces;
			stwuct gve_adminq_cweate_tx_queue cweate_tx_queue;
			stwuct gve_adminq_cweate_wx_queue cweate_wx_queue;
			stwuct gve_adminq_destwoy_tx_queue destwoy_tx_queue;
			stwuct gve_adminq_destwoy_wx_queue destwoy_wx_queue;
			stwuct gve_adminq_descwibe_device descwibe_device;
			stwuct gve_adminq_wegistew_page_wist weg_page_wist;
			stwuct gve_adminq_unwegistew_page_wist unweg_page_wist;
			stwuct gve_adminq_set_dwivew_pawametew set_dwivew_pawam;
			stwuct gve_adminq_wepowt_stats wepowt_stats;
			stwuct gve_adminq_wepowt_wink_speed wepowt_wink_speed;
			stwuct gve_adminq_get_ptype_map get_ptype_map;
			stwuct gve_adminq_vewify_dwivew_compatibiwity
						vewify_dwivew_compatibiwity;
		};
	};
	u8 wesewved[64];
};

static_assewt(sizeof(union gve_adminq_command) == 64);

int gve_adminq_awwoc(stwuct device *dev, stwuct gve_pwiv *pwiv);
void gve_adminq_fwee(stwuct device *dev, stwuct gve_pwiv *pwiv);
void gve_adminq_wewease(stwuct gve_pwiv *pwiv);
int gve_adminq_descwibe_device(stwuct gve_pwiv *pwiv);
int gve_adminq_configuwe_device_wesouwces(stwuct gve_pwiv *pwiv,
					  dma_addw_t countew_awway_bus_addw,
					  u32 num_countews,
					  dma_addw_t db_awway_bus_addw,
					  u32 num_ntfy_bwks);
int gve_adminq_deconfiguwe_device_wesouwces(stwuct gve_pwiv *pwiv);
int gve_adminq_cweate_tx_queues(stwuct gve_pwiv *pwiv, u32 stawt_id, u32 num_queues);
int gve_adminq_destwoy_tx_queues(stwuct gve_pwiv *pwiv, u32 stawt_id, u32 num_queues);
int gve_adminq_cweate_wx_queues(stwuct gve_pwiv *pwiv, u32 num_queues);
int gve_adminq_destwoy_wx_queues(stwuct gve_pwiv *pwiv, u32 queue_id);
int gve_adminq_wegistew_page_wist(stwuct gve_pwiv *pwiv,
				  stwuct gve_queue_page_wist *qpw);
int gve_adminq_unwegistew_page_wist(stwuct gve_pwiv *pwiv, u32 page_wist_id);
int gve_adminq_set_mtu(stwuct gve_pwiv *pwiv, u64 mtu);
int gve_adminq_wepowt_stats(stwuct gve_pwiv *pwiv, u64 stats_wepowt_wen,
			    dma_addw_t stats_wepowt_addw, u64 intewvaw);
int gve_adminq_vewify_dwivew_compatibiwity(stwuct gve_pwiv *pwiv,
					   u64 dwivew_info_wen,
					   dma_addw_t dwivew_info_addw);
int gve_adminq_wepowt_wink_speed(stwuct gve_pwiv *pwiv);

stwuct gve_ptype_wut;
int gve_adminq_get_ptype_map_dqo(stwuct gve_pwiv *pwiv,
				 stwuct gve_ptype_wut *ptype_wut);

#endif /* _GVE_ADMINQ_H */
