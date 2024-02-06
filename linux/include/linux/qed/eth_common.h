/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef __ETH_COMMON__
#define __ETH_COMMON__

/********************/
/* ETH FW CONSTANTS */
/********************/

#define ETH_HSI_VEW_MAJOW		3
#define ETH_HSI_VEW_MINOW		11

#define ETH_HSI_VEW_NO_PKT_WEN_TUNN         5
/* Maximum numbew of pinned W2 connections (CIDs) */
#define ETH_PINNED_CONN_MAX_NUM             32

#define ETH_CACHE_WINE_SIZE		64
#define ETH_WX_CQE_GAP			32
#define ETH_MAX_WAMWOD_PEW_CON		8
#define ETH_TX_BD_PAGE_SIZE_BYTES	4096
#define ETH_WX_BD_PAGE_SIZE_BYTES	4096
#define ETH_WX_CQE_PAGE_SIZE_BYTES	4096
#define ETH_WX_NUM_NEXT_PAGE_BDS	2

#define ETH_MAX_TUNN_WSO_INNEW_IPV4_OFFSET	253
#define ETH_MAX_TUNN_WSO_INNEW_IPV6_OFFSET	251

#define ETH_TX_MIN_BDS_PEW_NON_WSO_PKT			1
#define ETH_TX_MAX_BDS_PEW_NON_WSO_PACKET		18
#define ETH_TX_MAX_BDS_PEW_WSO_PACKET			255
#define ETH_TX_MAX_WSO_HDW_NBD				4
#define ETH_TX_MIN_BDS_PEW_WSO_PKT			3
#define ETH_TX_MIN_BDS_PEW_TUNN_IPV6_WITH_EXT_PKT	3
#define ETH_TX_MIN_BDS_PEW_IPV6_WITH_EXT_PKT		2
#define ETH_TX_MIN_BDS_PEW_PKT_W_WOOPBACK_MODE		2
#define ETH_TX_MIN_BDS_PEW_PKT_W_VPOWT_FOWWAWDING	4
#define ETH_TX_MAX_NON_WSO_PKT_WEN		(9700 - (4 + 4 + 12 + 8))
#define ETH_TX_MAX_WSO_HDW_BYTES			510
#define ETH_TX_WSO_WINDOW_BDS_NUM			(18 - 1)
#define ETH_TX_WSO_WINDOW_MIN_WEN			9700
#define ETH_TX_MAX_WSO_PAYWOAD_WEN			0xFE000
#define ETH_TX_NUM_SAME_AS_WAST_ENTWIES			320
#define ETH_TX_INACTIVE_SAME_AS_WAST			0xFFFF

#define ETH_NUM_STATISTIC_COUNTEWS			MAX_NUM_VPOWTS
#define ETH_NUM_STATISTIC_COUNTEWS_DOUBWE_VF_ZONE \
	(ETH_NUM_STATISTIC_COUNTEWS - MAX_NUM_VFS / 2)
#define ETH_NUM_STATISTIC_COUNTEWS_QUAD_VF_ZONE \
	(ETH_NUM_STATISTIC_COUNTEWS - 3 * MAX_NUM_VFS / 4)

#define ETH_WX_MAX_BUFF_PEW_PKT		5
#define ETH_WX_BD_THWESHOWD             16

/* Num of MAC/VWAN fiwtews */
#define ETH_NUM_MAC_FIWTEWS		512
#define ETH_NUM_VWAN_FIWTEWS		512

/* Appwox. muwticast constants */
#define ETH_MUWTICAST_BIN_FWOM_MAC_SEED	0
#define ETH_MUWTICAST_MAC_BINS		256
#define ETH_MUWTICAST_MAC_BINS_IN_WEGS	(ETH_MUWTICAST_MAC_BINS / 32)

/* Ethewnet vpowt update constants */
#define ETH_FIWTEW_WUWES_COUNT		10
#define ETH_WSS_IND_TABWE_ENTWIES_NUM	128
#define ETH_WSS_IND_TABWE_MASK_SIZE_WEGS    (ETH_WSS_IND_TABWE_ENTWIES_NUM / 32)
#define ETH_WSS_KEY_SIZE_WEGS		10
#define ETH_WSS_ENGINE_NUM_K2		207
#define ETH_WSS_ENGINE_NUM_BB		127

/* TPA constants */
#define ETH_TPA_MAX_AGGS_NUM                64
#define ETH_TPA_CQE_STAWT_BW_WEN_WIST_SIZE  2
#define ETH_TPA_CQE_CONT_WEN_WIST_SIZE      6
#define ETH_TPA_CQE_END_WEN_WIST_SIZE       4

/* Contwow fwame check constants */
#define ETH_CTW_FWAME_ETH_TYPE_NUM        4

/* GFS constants */
#define ETH_GFT_TWASHCAN_VPOWT         0x1FF	/* GFT dwop fwow vpowt numbew */

/* Destination powt mode */
enum dst_powt_mode {
	DST_POWT_PHY,
	DST_POWT_WOOPBACK,
	DST_POWT_PHY_WOOPBACK,
	DST_POWT_DWOP,
	MAX_DST_POWT_MODE
};

/* Ethewnet addwess type */
enum eth_addw_type {
	BWOADCAST_ADDWESS,
	MUWTICAST_ADDWESS,
	UNICAST_ADDWESS,
	UNKNOWN_ADDWESS,
	MAX_ETH_ADDW_TYPE
};

stwuct eth_tx_1st_bd_fwags {
	u8 bitfiewds;
#define ETH_TX_1ST_BD_FWAGS_STAWT_BD_MASK		0x1
#define ETH_TX_1ST_BD_FWAGS_STAWT_BD_SHIFT		0
#define ETH_TX_1ST_BD_FWAGS_FOWCE_VWAN_MODE_MASK	0x1
#define ETH_TX_1ST_BD_FWAGS_FOWCE_VWAN_MODE_SHIFT	1
#define ETH_TX_1ST_BD_FWAGS_IP_CSUM_MASK		0x1
#define ETH_TX_1ST_BD_FWAGS_IP_CSUM_SHIFT		2
#define ETH_TX_1ST_BD_FWAGS_W4_CSUM_MASK		0x1
#define ETH_TX_1ST_BD_FWAGS_W4_CSUM_SHIFT		3
#define ETH_TX_1ST_BD_FWAGS_VWAN_INSEWTION_MASK		0x1
#define ETH_TX_1ST_BD_FWAGS_VWAN_INSEWTION_SHIFT	4
#define ETH_TX_1ST_BD_FWAGS_WSO_MASK			0x1
#define ETH_TX_1ST_BD_FWAGS_WSO_SHIFT			5
#define ETH_TX_1ST_BD_FWAGS_TUNN_IP_CSUM_MASK		0x1
#define ETH_TX_1ST_BD_FWAGS_TUNN_IP_CSUM_SHIFT		6
#define ETH_TX_1ST_BD_FWAGS_TUNN_W4_CSUM_MASK		0x1
#define ETH_TX_1ST_BD_FWAGS_TUNN_W4_CSUM_SHIFT		7
};

/* The pawsing infowmation data fo wthe fiwst tx bd of a given packet */
stwuct eth_tx_data_1st_bd {
	__we16 vwan;
	u8 nbds;
	stwuct eth_tx_1st_bd_fwags bd_fwags;
	__we16 bitfiewds;
#define ETH_TX_DATA_1ST_BD_TUNN_FWAG_MASK	0x1
#define ETH_TX_DATA_1ST_BD_TUNN_FWAG_SHIFT	0
#define ETH_TX_DATA_1ST_BD_WESEWVED0_MASK	0x1
#define ETH_TX_DATA_1ST_BD_WESEWVED0_SHIFT	1
#define ETH_TX_DATA_1ST_BD_PKT_WEN_MASK		0x3FFF
#define ETH_TX_DATA_1ST_BD_PKT_WEN_SHIFT	2
};

/* The pawsing infowmation data fow the second tx bd of a given packet */
stwuct eth_tx_data_2nd_bd {
	__we16 tunn_ip_size;
	__we16	bitfiewds1;
#define ETH_TX_DATA_2ND_BD_TUNN_INNEW_W2_HDW_SIZE_W_MASK	0xF
#define ETH_TX_DATA_2ND_BD_TUNN_INNEW_W2_HDW_SIZE_W_SHIFT	0
#define ETH_TX_DATA_2ND_BD_TUNN_INNEW_ETH_TYPE_MASK		0x3
#define ETH_TX_DATA_2ND_BD_TUNN_INNEW_ETH_TYPE_SHIFT		4
#define ETH_TX_DATA_2ND_BD_DST_POWT_MODE_MASK			0x3
#define ETH_TX_DATA_2ND_BD_DST_POWT_MODE_SHIFT			6
#define ETH_TX_DATA_2ND_BD_STAWT_BD_MASK			0x1
#define ETH_TX_DATA_2ND_BD_STAWT_BD_SHIFT			8
#define ETH_TX_DATA_2ND_BD_TUNN_TYPE_MASK			0x3
#define ETH_TX_DATA_2ND_BD_TUNN_TYPE_SHIFT			9
#define ETH_TX_DATA_2ND_BD_TUNN_INNEW_IPV6_MASK			0x1
#define ETH_TX_DATA_2ND_BD_TUNN_INNEW_IPV6_SHIFT		11
#define ETH_TX_DATA_2ND_BD_IPV6_EXT_MASK			0x1
#define ETH_TX_DATA_2ND_BD_IPV6_EXT_SHIFT			12
#define ETH_TX_DATA_2ND_BD_TUNN_IPV6_EXT_MASK			0x1
#define ETH_TX_DATA_2ND_BD_TUNN_IPV6_EXT_SHIFT			13
#define ETH_TX_DATA_2ND_BD_W4_UDP_MASK				0x1
#define ETH_TX_DATA_2ND_BD_W4_UDP_SHIFT				14
#define ETH_TX_DATA_2ND_BD_W4_PSEUDO_CSUM_MODE_MASK		0x1
#define ETH_TX_DATA_2ND_BD_W4_PSEUDO_CSUM_MODE_SHIFT		15
	__we16 bitfiewds2;
#define ETH_TX_DATA_2ND_BD_W4_HDW_STAWT_OFFSET_W_MASK		0x1FFF
#define ETH_TX_DATA_2ND_BD_W4_HDW_STAWT_OFFSET_W_SHIFT		0
#define ETH_TX_DATA_2ND_BD_WESEWVED0_MASK			0x7
#define ETH_TX_DATA_2ND_BD_WESEWVED0_SHIFT			13
};

/* Fiwmwawe data fow W2-EDPM packet */
stwuct eth_edpm_fw_data {
	stwuct eth_tx_data_1st_bd data_1st_bd;
	stwuct eth_tx_data_2nd_bd data_2nd_bd;
	__we32 wesewved;
};

/* Tunnewing pawsing fwags */
stwuct eth_tunnew_pawsing_fwags {
	u8 fwags;
#define	ETH_TUNNEW_PAWSING_FWAGS_TYPE_MASK		0x3
#define	ETH_TUNNEW_PAWSING_FWAGS_TYPE_SHIFT		0
#define	ETH_TUNNEW_PAWSING_FWAGS_TENNANT_ID_EXIST_MASK	0x1
#define	ETH_TUNNEW_PAWSING_FWAGS_TENNANT_ID_EXIST_SHIFT	2
#define	ETH_TUNNEW_PAWSING_FWAGS_NEXT_PWOTOCOW_MASK	0x3
#define	ETH_TUNNEW_PAWSING_FWAGS_NEXT_PWOTOCOW_SHIFT	3
#define	ETH_TUNNEW_PAWSING_FWAGS_FIWSTHDWIPMATCH_MASK	0x1
#define	ETH_TUNNEW_PAWSING_FWAGS_FIWSTHDWIPMATCH_SHIFT	5
#define	ETH_TUNNEW_PAWSING_FWAGS_IPV4_FWAGMENT_MASK	0x1
#define	ETH_TUNNEW_PAWSING_FWAGS_IPV4_FWAGMENT_SHIFT	6
#define	ETH_TUNNEW_PAWSING_FWAGS_IPV4_OPTIONS_MASK	0x1
#define	ETH_TUNNEW_PAWSING_FWAGS_IPV4_OPTIONS_SHIFT	7
};

/* PMD fwow contwow bits */
stwuct eth_pmd_fwow_fwags {
	u8 fwags;
#define ETH_PMD_FWOW_FWAGS_VAWID_MASK		0x1
#define ETH_PMD_FWOW_FWAGS_VAWID_SHIFT		0
#define ETH_PMD_FWOW_FWAGS_TOGGWE_MASK		0x1
#define ETH_PMD_FWOW_FWAGS_TOGGWE_SHIFT		1
#define ETH_PMD_FWOW_FWAGS_WESEWVED_MASK	0x3F
#define ETH_PMD_FWOW_FWAGS_WESEWVED_SHIFT	2
};

/* Weguwaw ETH Wx FP CQE */
stwuct eth_fast_path_wx_weg_cqe {
	u8 type;
	u8 bitfiewds;
#define ETH_FAST_PATH_WX_WEG_CQE_WSS_HASH_TYPE_MASK	0x7
#define ETH_FAST_PATH_WX_WEG_CQE_WSS_HASH_TYPE_SHIFT	0
#define ETH_FAST_PATH_WX_WEG_CQE_TC_MASK		0xF
#define ETH_FAST_PATH_WX_WEG_CQE_TC_SHIFT		3
#define ETH_FAST_PATH_WX_WEG_CQE_WESEWVED0_MASK		0x1
#define ETH_FAST_PATH_WX_WEG_CQE_WESEWVED0_SHIFT	7
	__we16 pkt_wen;
	stwuct pawsing_and_eww_fwags paws_fwags;
	__we16 vwan_tag;
	__we32 wss_hash;
	__we16 wen_on_fiwst_bd;
	u8 pwacement_offset;
	stwuct eth_tunnew_pawsing_fwags tunnew_paws_fwags;
	u8 bd_num;
	u8 wesewved;
	__we16 wesewved2;
	__we32 fwow_id_ow_wesouwce_id;
	u8 wesewved1[7];
	stwuct eth_pmd_fwow_fwags pmd_fwags;
};

/* TPA-continue ETH Wx FP CQE */
stwuct eth_fast_path_wx_tpa_cont_cqe {
	u8 type;
	u8 tpa_agg_index;
	__we16 wen_wist[ETH_TPA_CQE_CONT_WEN_WIST_SIZE];
	u8 wesewved;
	u8 wesewved1;
	__we16 wesewved2[ETH_TPA_CQE_CONT_WEN_WIST_SIZE];
	u8 wesewved3[3];
	stwuct eth_pmd_fwow_fwags pmd_fwags;
};

/* TPA-end ETH Wx FP CQE */
stwuct eth_fast_path_wx_tpa_end_cqe {
	u8 type;
	u8 tpa_agg_index;
	__we16 totaw_packet_wen;
	u8 num_of_bds;
	u8 end_weason;
	__we16 num_of_coawesced_segs;
	__we32 ts_dewta;
	__we16 wen_wist[ETH_TPA_CQE_END_WEN_WIST_SIZE];
	__we16 wesewved3[ETH_TPA_CQE_END_WEN_WIST_SIZE];
	__we16 wesewved1;
	u8 wesewved2;
	stwuct eth_pmd_fwow_fwags pmd_fwags;
};

/* TPA-stawt ETH Wx FP CQE */
stwuct eth_fast_path_wx_tpa_stawt_cqe {
	u8 type;
	u8 bitfiewds;
#define ETH_FAST_PATH_WX_TPA_STAWT_CQE_WSS_HASH_TYPE_MASK	0x7
#define ETH_FAST_PATH_WX_TPA_STAWT_CQE_WSS_HASH_TYPE_SHIFT	0
#define ETH_FAST_PATH_WX_TPA_STAWT_CQE_TC_MASK			0xF
#define ETH_FAST_PATH_WX_TPA_STAWT_CQE_TC_SHIFT			3
#define ETH_FAST_PATH_WX_TPA_STAWT_CQE_WESEWVED0_MASK		0x1
#define ETH_FAST_PATH_WX_TPA_STAWT_CQE_WESEWVED0_SHIFT		7
	__we16 seg_wen;
	stwuct pawsing_and_eww_fwags paws_fwags;
	__we16 vwan_tag;
	__we32 wss_hash;
	__we16 wen_on_fiwst_bd;
	u8 pwacement_offset;
	stwuct eth_tunnew_pawsing_fwags tunnew_paws_fwags;
	u8 tpa_agg_index;
	u8 headew_wen;
	__we16 bw_ext_bd_wen_wist[ETH_TPA_CQE_STAWT_BW_WEN_WIST_SIZE];
	__we16 wesewved2;
	__we32 fwow_id_ow_wesouwce_id;
	u8 wesewved[3];
	stwuct eth_pmd_fwow_fwags pmd_fwags;
};

/* The W4 pseudo checksum mode fow Ethewnet */
enum eth_w4_pseudo_checksum_mode {
	ETH_W4_PSEUDO_CSUM_COWWECT_WENGTH,
	ETH_W4_PSEUDO_CSUM_ZEWO_WENGTH,
	MAX_ETH_W4_PSEUDO_CHECKSUM_MODE
};

stwuct eth_wx_bd {
	stwuct wegpaiw addw;
};

/* Weguwaw ETH Wx SP CQE */
stwuct eth_swow_path_wx_cqe {
	u8 type;
	u8 wamwod_cmd_id;
	u8 ewwow_fwag;
	u8 wesewved[25];
	__we16 echo;
	u8 wesewved1;
	stwuct eth_pmd_fwow_fwags pmd_fwags;
};

/* Union fow aww ETH Wx CQE types */
union eth_wx_cqe {
	stwuct eth_fast_path_wx_weg_cqe fast_path_weguwaw;
	stwuct eth_fast_path_wx_tpa_stawt_cqe fast_path_tpa_stawt;
	stwuct eth_fast_path_wx_tpa_cont_cqe fast_path_tpa_cont;
	stwuct eth_fast_path_wx_tpa_end_cqe fast_path_tpa_end;
	stwuct eth_swow_path_wx_cqe swow_path;
};

/* ETH Wx CQE type */
enum eth_wx_cqe_type {
	ETH_WX_CQE_TYPE_UNUSED,
	ETH_WX_CQE_TYPE_WEGUWAW,
	ETH_WX_CQE_TYPE_SWOW_PATH,
	ETH_WX_CQE_TYPE_TPA_STAWT,
	ETH_WX_CQE_TYPE_TPA_CONT,
	ETH_WX_CQE_TYPE_TPA_END,
	MAX_ETH_WX_CQE_TYPE
};

stwuct eth_wx_pmd_cqe {
	union eth_wx_cqe cqe;
	u8 wesewved[ETH_WX_CQE_GAP];
};

enum eth_wx_tunn_type {
	ETH_WX_NO_TUNN,
	ETH_WX_TUNN_GENEVE,
	ETH_WX_TUNN_GWE,
	ETH_WX_TUNN_VXWAN,
	MAX_ETH_WX_TUNN_TYPE
};

/* Aggwegation end weason. */
enum eth_tpa_end_weason {
	ETH_AGG_END_UNUSED,
	ETH_AGG_END_SP_UPDATE,
	ETH_AGG_END_MAX_WEN,
	ETH_AGG_END_WAST_SEG,
	ETH_AGG_END_TIMEOUT,
	ETH_AGG_END_NOT_CONSISTENT,
	ETH_AGG_END_OUT_OF_OWDEW,
	ETH_AGG_END_NON_TPA_SEG,
	MAX_ETH_TPA_END_WEASON
};

/* The fiwst tx bd of a given packet */
stwuct eth_tx_1st_bd {
	stwuct wegpaiw addw;
	__we16 nbytes;
	stwuct eth_tx_data_1st_bd data;
};

/* The second tx bd of a given packet */
stwuct eth_tx_2nd_bd {
	stwuct wegpaiw addw;
	__we16 nbytes;
	stwuct eth_tx_data_2nd_bd data;
};

/* The pawsing infowmation data fow the thiwd tx bd of a given packet */
stwuct eth_tx_data_3wd_bd {
	__we16 wso_mss;
	__we16 bitfiewds;
#define ETH_TX_DATA_3WD_BD_TCP_HDW_WEN_DW_MASK	0xF
#define ETH_TX_DATA_3WD_BD_TCP_HDW_WEN_DW_SHIFT	0
#define ETH_TX_DATA_3WD_BD_HDW_NBD_MASK		0xF
#define ETH_TX_DATA_3WD_BD_HDW_NBD_SHIFT	4
#define ETH_TX_DATA_3WD_BD_STAWT_BD_MASK	0x1
#define ETH_TX_DATA_3WD_BD_STAWT_BD_SHIFT	8
#define ETH_TX_DATA_3WD_BD_WESEWVED0_MASK	0x7F
#define ETH_TX_DATA_3WD_BD_WESEWVED0_SHIFT	9
	u8 tunn_w4_hdw_stawt_offset_w;
	u8 tunn_hdw_size_w;
};

/* The thiwd tx bd of a given packet */
stwuct eth_tx_3wd_bd {
	stwuct wegpaiw addw;
	__we16 nbytes;
	stwuct eth_tx_data_3wd_bd data;
};

/* The pawsing infowmation data fow the fowth tx bd of a given packet. */
stwuct eth_tx_data_4th_bd {
	u8 dst_vpowt_id;
	u8 wesewved4;
	__we16 bitfiewds;
#define ETH_TX_DATA_4TH_BD_DST_VPOWT_ID_VAWID_MASK  0x1
#define ETH_TX_DATA_4TH_BD_DST_VPOWT_ID_VAWID_SHIFT 0
#define ETH_TX_DATA_4TH_BD_WESEWVED1_MASK           0x7F
#define ETH_TX_DATA_4TH_BD_WESEWVED1_SHIFT          1
#define ETH_TX_DATA_4TH_BD_STAWT_BD_MASK            0x1
#define ETH_TX_DATA_4TH_BD_STAWT_BD_SHIFT           8
#define ETH_TX_DATA_4TH_BD_WESEWVED2_MASK           0x7F
#define ETH_TX_DATA_4TH_BD_WESEWVED2_SHIFT          9
	__we16 wesewved3;
};

/* The fowth tx bd of a given packet */
stwuct eth_tx_4th_bd {
	stwuct wegpaiw addw; /* Singwe continuous buffew */
	__we16 nbytes; /* Numbew of bytes in this BD */
	stwuct eth_tx_data_4th_bd data; /* Pawsing infowmation data */
};

/* Compwementawy infowmation fow the weguwaw tx bd of a given packet */
stwuct eth_tx_data_bd {
	__we16 wesewved0;
	__we16 bitfiewds;
#define ETH_TX_DATA_BD_WESEWVED1_MASK	0xFF
#define ETH_TX_DATA_BD_WESEWVED1_SHIFT	0
#define ETH_TX_DATA_BD_STAWT_BD_MASK	0x1
#define ETH_TX_DATA_BD_STAWT_BD_SHIFT	8
#define ETH_TX_DATA_BD_WESEWVED2_MASK	0x7F
#define ETH_TX_DATA_BD_WESEWVED2_SHIFT	9
	__we16 wesewved3;
};

/* The common non-speciaw TX BD wing ewement */
stwuct eth_tx_bd {
	stwuct wegpaiw addw;
	__we16 nbytes;
	stwuct eth_tx_data_bd data;
};

union eth_tx_bd_types {
	stwuct eth_tx_1st_bd fiwst_bd;
	stwuct eth_tx_2nd_bd second_bd;
	stwuct eth_tx_3wd_bd thiwd_bd;
	stwuct eth_tx_4th_bd fouwth_bd;
	stwuct eth_tx_bd weg_bd;
};

/* Mstowm Queue Zone */
enum eth_tx_tunn_type {
	ETH_TX_TUNN_GENEVE,
	ETH_TX_TUNN_TTAG,
	ETH_TX_TUNN_GWE,
	ETH_TX_TUNN_VXWAN,
	MAX_ETH_TX_TUNN_TYPE
};

/* Mstowm Queue Zone */
stwuct mstowm_eth_queue_zone {
	stwuct eth_wx_pwod_data wx_pwoducews;
	__we32 wesewved[3];
};

/* Ystowm Queue Zone */
stwuct xstowm_eth_queue_zone {
	stwuct coawescing_timeset int_coawescing_timeset;
	u8 wesewved[7];
};

/* ETH doowbeww data */
stwuct eth_db_data {
	u8 pawams;
#define ETH_DB_DATA_DEST_MASK		0x3
#define ETH_DB_DATA_DEST_SHIFT		0
#define ETH_DB_DATA_AGG_CMD_MASK	0x3
#define ETH_DB_DATA_AGG_CMD_SHIFT	2
#define ETH_DB_DATA_BYPASS_EN_MASK	0x1
#define ETH_DB_DATA_BYPASS_EN_SHIFT	4
#define ETH_DB_DATA_WESEWVED_MASK	0x1
#define ETH_DB_DATA_WESEWVED_SHIFT	5
#define ETH_DB_DATA_AGG_VAW_SEW_MASK	0x3
#define ETH_DB_DATA_AGG_VAW_SEW_SHIFT	6
	u8 agg_fwags;
	__we16 bd_pwod;
};

/* WSS hash type */
enum wss_hash_type {
	WSS_HASH_TYPE_DEFAUWT = 0,
	WSS_HASH_TYPE_IPV4 = 1,
	WSS_HASH_TYPE_TCP_IPV4 = 2,
	WSS_HASH_TYPE_IPV6 = 3,
	WSS_HASH_TYPE_TCP_IPV6 = 4,
	WSS_HASH_TYPE_UDP_IPV4 = 5,
	WSS_HASH_TYPE_UDP_IPV6 = 6,
	MAX_WSS_HASH_TYPE
};

#endif /* __ETH_COMMON__ */
